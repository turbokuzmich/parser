//
//  parser.c
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include "globals.h"
#include "parser.h"
#include "expat.h"
#include "organization.h"
#include "position.h"
#include "person.h"
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct parser_t {
    FILE *file;
    XML_Parser xml_parser;
    MYSQL *connection;
    Organization organization_stack[ORGANIZATION_STACK_SIZE];
    unsigned int organization_stack_offset;
    int functional_block_codes[FUNCTIONAL_BLOCK_NAMES_SIZE];
    char *functional_block_names[FUNCTIONAL_BLOCK_NAMES_SIZE];
    Person person;
};

static void set_zero_functional_block(Parser p)
{
    p->functional_block_names[0] = (char *)malloc(1 * sizeof(char));
    strcpy(p->functional_block_names[0], "");
}

char *get_functional_block_name(Parser p, unsigned int code)
{
    char *name = p->functional_block_names[0];
    
    for (int i = 0; i < FUNCTIONAL_BLOCK_NAMES_SIZE; i++) {
        if (p->functional_block_codes[i] == code) {
            name = p->functional_block_names[i];
            break;
        }
    }
    
    return strdup(name);
}

static Organization *get_current_organization(Parser p)
{
    return p->organization_stack + p->organization_stack_offset;
}

static void set_organization_functional_blocks(Parser p)
{
    Organization *o = get_current_organization(p);
    
    if (o->functionalblockcode == 0) {
        if (p->organization_stack_offset > 0) {
            int prev_organization_stack_offset = p->organization_stack_offset - 1;
            Organization *c;
            
            do {
                c = p->organization_stack + prev_organization_stack_offset;
                
                if (c->functionalblockcode > 0) {
                    o->functionalblockcode = c->functionalblockcode;
                    break;
                }
                
                prev_organization_stack_offset--;
            } while(prev_organization_stack_offset > -1);
        }
    }
    
    o->functionalblockname = get_functional_block_name(p, o->functionalblockcode);
}

static void set_organization_parent(Parser p)
{
    Organization *o = get_current_organization(p);
    
    if (p->organization_stack_offset == 0) {
        o->parent_id = 0;
        o->admin_id = 0;
        o->path = strdup("/0");
    } else {
        Organization *parent = p->organization_stack + (p->organization_stack_offset - 1);
        o->parent_id = parent->id;
        o->admin_id = parent->admin_id;
        
        Organization *ancestor;
        char path[150];
        char buffer[20];
        int i = 0, c = 0;
        
        memset(path, 0, sizeof(path));
        memset(buffer, 0, sizeof(buffer));
        strcat(path, "/0");
        c = (int)strlen(path);

        while (i < p->organization_stack_offset) {
            ancestor = p->organization_stack + i;
            
            sprintf(buffer, "/%s", ancestor->idorg);
            strcat(path + c, buffer);
            c = (int)strlen(path);
            memset(buffer, 0, sizeof(buffer));

            i++;
        }
        
        o->path = strdup(path);
    }
}

static void parse_functional_block(Parser p, const char **attrs)
{
    unsigned int code = 0;
    const char *name = NULL;
    const char **attr = attrs;
    
    while (*attr != NULL) {
        if (strcmp(*attr, "code") == 0) {
            code = atoi(*(attr + 1));
        }
        if (strcmp(*attr, "name") == 0) {
            name = *(attr + 1);
        }
        
        attr++;
    }
    
    if (code > 0 && name != NULL) {
        for (int i = 1; i < FUNCTIONAL_BLOCK_NAMES_SIZE; i++) {
            if (p->functional_block_codes[i] == 0) {
                p->functional_block_codes[i] = code;
                p->functional_block_names[i] = strdup(name);
                break;
            }
        }
    }
}

int check_organization_stack_is_dirty(Parser p)
{
    int result = 0;
    int stack_offset = p->organization_stack_offset;
    
    do {
        Organization *c = p->organization_stack + stack_offset;
        
        if (c != NULL && c->is_dirty) {
            result = 1;
            break;
        }
        
        stack_offset--;
    } while (stack_offset > -1);
    
    return result;
}

static void XMLCALL xml_start_element(void *data, const char *name, const char **attrs)
{
    Parser p = data;
    MYSQL *connection = p->connection;
    
    if (strcmp(name, "functionalblock") == 0) {
        parse_functional_block(p, attrs);
    }
    if (strcmp(name, "organization") == 0) {
        Organization *o = get_current_organization(p);
        if (check_organization_stack_is_dirty(p)) {
            o->is_dirty = 1;
            return;
        }
        organization_from_attrs(o, attrs);
        if (o->name == NULL || strlen(o->name) == 0) {
            o->is_dirty = 1;
            return;
        }
        set_organization_functional_blocks(p);
        set_organization_parent(p);
        insert_organization(connection, o);
        p->organization_stack_offset++;
    }
    if (strcmp(name, "person") == 0) {
        if (check_organization_stack_is_dirty(p)) {
            return;
        }
        Position position = { 0 };
        position_from_attrs(&position, attrs);
        insert_position(connection, &position);
        person_from_attrs(&(p->person), attrs);
        p->person.organization_id = get_current_organization(p)->id;
        p->person.admin_id = get_current_organization(p)->admin_id;
        p->person.position_id = position.id;
        insert_person(connection, &(p->person));
        position_clear(&position);
    }
}

static void XMLCALL xml_end_element(void *data, const char *name)
{
    Parser p = data;
    
    if (strcmp(name, "organization") == 0) {
        p->organization_stack_offset--;
        organization_clear(p->organization_stack + p->organization_stack_offset);
    }
    if (strcmp(name, "person") == 0) {
        person_clear(&(p->person));
    }
}

Parser parser_create()
{
    Parser parser = malloc(sizeof(struct parser_t));
    
    memset(parser, 0, sizeof(*parser));
    set_zero_functional_block(parser);
    
    return parser;
}

int parser_db_connect(Parser p, const char *host, const char *user, const char *passwd, const char *db)
{
    MYSQL *connection = mysql_init(NULL);
    
    if (connection == NULL) {
        fprintf(stderr, "Unable to init mysql connection\n");
        return 1;
    }
    
    if (mysql_real_connect(connection, host, user, passwd, db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Unable to connect\n");
        return 1;
    }
    
    mysql_query(connection, "SET NAMES 'utf8'");
    
    p->connection = connection;
    
    return 0;
}

int parser_parse(Parser p, const char *filename)
{
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) return 1;
    
    char buffer[BUFSIZ];
    int done = 0;
    
    p->file = file;
    p->xml_parser = XML_ParserCreate(NULL);
    p->organization_stack_offset = 0;
    
    XML_SetUserData(p->xml_parser, p);
    XML_SetElementHandler(p->xml_parser, xml_start_element, xml_end_element);
    
    do {
        size_t len = fread(buffer, 1, sizeof(buffer), p->file);
        if (len < sizeof(buffer)) {
            done = 1;
        }
        
        if (XML_Parse(p->xml_parser, buffer, (int)len, done) == XML_STATUS_ERROR) {
            fprintf(stderr, "%s at line %d\n", XML_ErrorString(XML_GetErrorCode(p->xml_parser)), (int)XML_GetCurrentLineNumber(p->xml_parser));
            return 1;
        }
    } while(!done);
    
    return 0;
}

void parser_destroy(Parser p)
{
    fclose(p->file);
    XML_ParserFree(p->xml_parser);
    mysql_close(p->connection);
    
    for (int i = 0; i < FUNCTIONAL_BLOCK_NAMES_SIZE; i++) {
        if (p->functional_block_names[i] != NULL) {
            free(p->functional_block_names[i]);
        }
    }
    
    free(p);
}
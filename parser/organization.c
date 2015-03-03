//
//  organization.c
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include "organization.h"
#include "globals.h"
#include "current_time.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CHRPARAMSNOTEQUAL(entity_1, entity_2, param) (entity_1->param == NULL && entity_2->param != NULL && strlen(entity_2->param) > 1) || (entity_2->param == NULL && entity_1->param != NULL && strlen(entity_1->param) > 1) || (entity_1->param != NULL && entity_2->param != NULL && strcmp(entity_1->param, entity_2->param) != 0)

#define INTPARAMNOTEQUAL(entity_1, entity_2, param) (entity_1->param != entity_2->param)

void organization_from_attrs(Organization *o, const char **attrs)
{
    if (o != NULL) {
        const char **i = attrs;
        while (*i != NULL) {
            CMPANDSAVEINTATTR(o, id, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, idorg, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, name, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, path, *i, *(i + 1));
            CMPANDSAVEINTATTR(o, functionalblockcode, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, functionalblockname, *i, *(i + 1));
            CMPANDSAVEINTATTR(o, integrity_validated_at, *i, *(i + 1));
            CMPANDSAVEINTATTR(o, integrity_valid, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, integrity_invalid_reason, *i, *(i + 1));
            CMPANDSAVEINTATTR(o, integrity_invalid_root, *i, *(i + 1));
            
            CMPANDSAVECHARATTR(o, aspk_idsbrf, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, bankcode, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, baseuid, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, createdate, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, dbid, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, dismissdate, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, idsbrf, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, idtb, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, orgcode, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, status, *i, *(i + 1));
            CMPANDSAVECHARATTR(o, uid, *i, *(i + 1));
            
            CMPANDSAVEINTATTR(o, admin_id, *i, *(i + 1));
            CMPANDSAVEINTATTR(o, parent_id, *i, *(i + 1));
            
            i += 2;
        }
    }
}

void organization_from_mysql(Organization *o, MYSQL_RES *result)
{
    MYSQL_ROW row = mysql_row_seek(result, 0)->data;
    MYSQL_FIELD *fields = mysql_fetch_fields(result);
    MYSQL_FIELD *field;
    unsigned int field_count = mysql_num_fields(result);
    
    for (unsigned int i = 0; i < field_count; i++) {
        field = (fields + i);
        
        CMPANDSAVEINTATTR(o, id, field->name, row[i]);
        CMPANDSAVECHARATTR(o, idorg, field->name, row[i]);
        CMPANDSAVECHARATTR(o, name, field->name, row[i]);
        CMPANDSAVECHARATTR(o, path, field->name, row[i]);
        CMPANDSAVEINTATTR(o, functionalblockcode, field->name, row[i]);
        CMPANDSAVECHARATTR(o, functionalblockname, field->name, row[i]);
        
        CMPANDSAVECHARATTR(o, aspk_idsbrf, field->name, row[i]);
        CMPANDSAVECHARATTR(o, bankcode, field->name, row[i]);
        CMPANDSAVECHARATTR(o, baseuid, field->name, row[i]);
        CMPANDSAVECHARATTR(o, createdate, field->name, row[i]);
        CMPANDSAVECHARATTR(o, dbid, field->name, row[i]);
        CMPANDSAVECHARATTR(o, dismissdate, field->name, row[i]);
        CMPANDSAVECHARATTR(o, idsbrf, field->name, row[i]);
        CMPANDSAVECHARATTR(o, idtb, field->name, row[i]);
        CMPANDSAVECHARATTR(o, orgcode, field->name, row[i]);
        CMPANDSAVECHARATTR(o, status, field->name, row[i]);
        CMPANDSAVECHARATTR(o, uid, field->name, row[i]);
        
        CMPANDSAVEINTATTR(o, admin_id, field->name, row[i]);
        CMPANDSAVEINTATTR(o, parent_id, field->name, row[i]);
    }
}

void organization_clear(Organization *o)
{
    SETCHARATTR(o, idorg, NULL);
    SETCHARATTR(o, name, NULL);
    SETCHARATTR(o, path, NULL);
    SETCHARATTR(o, functionalblockname, NULL);
    SETCHARATTR(o, integrity_invalid_reason, NULL);
    
    SETCHARATTR(o, aspk_idsbrf, NULL);
    SETCHARATTR(o, bankcode, NULL);
    SETCHARATTR(o, baseuid, NULL);
    SETCHARATTR(o, createdate, NULL);
    SETCHARATTR(o, dbid, NULL);
    SETCHARATTR(o, dismissdate, NULL);
    SETCHARATTR(o, idsbrf, NULL);
    SETCHARATTR(o, idtb, NULL);
    SETCHARATTR(o, orgcode, NULL);
    SETCHARATTR(o, status, NULL);
    SETCHARATTR(o, uid, NULL);
    
    memset(o, 0, sizeof(Organization));
}

int organization_is_equal(Organization *o1, Organization *o2)
{
    int equal = 1;
    
    if (CHRPARAMSNOTEQUAL(o1, o2, name)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, path)) {
        equal = 0;
    }
    if (equal && INTPARAMNOTEQUAL(o1, o2, functionalblockcode)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, functionalblockname)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, aspk_idsbrf)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, bankcode)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, baseuid)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, createdate)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, dbid)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, dismissdate)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, idsbrf)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, idtb)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, orgcode)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, status)) {
        equal = 0;
    }
    if (equal && CHRPARAMSNOTEQUAL(o1, o2, uid)) {
        equal = 0;
    }
    if (equal && INTPARAMNOTEQUAL(o1, o2, parent_id)) {
        equal = 0;
    }
    
    return equal;
}

MYSQL_RES *organization_get_subordinates(MYSQL *connection, Organization *o)
{
    char query[4 * 1024];
    char *path = o->path;
    char *idorg = o->idorg;
    
    memset(query, 0, sizeof(query));
    sprintf(query, "SELECT `id` FROM `organizations` WHERE `path` LIKE '%s/%s%%'", path, idorg);
    
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    return mysql_store_result(connection);
}

void organization_handle_subordinate_change(MYSQL *connection, Organization *o, const char *path)
{
    MYSQL_RES *subordinates_result = organization_get_subordinates(connection, o);
    if (subordinates_result == NULL) {
        DUMPSQLERROR(connection, "");
    }
    
    char subordinates_ids[4 * 1024];
    char query[8 * 1024];
    int offset = 0;
    int subordinates_count = (int)mysql_num_rows(subordinates_result);
    MYSQL_ROW row;
    char date[19];
    
    memset(subordinates_ids, 0, sizeof(subordinates_ids));
    memset(query, 0, sizeof(query));
    memset(date, 0, sizeof(date));
    
    current_time(date, 19);
    
    for (int i = 0; i < subordinates_count; i++) {
        mysql_data_seek(subordinates_result, i);
        row = mysql_fetch_row(subordinates_result);
        if (i == 0) {
            strcat(subordinates_ids, row[i]);
        } else {
            sprintf(subordinates_ids + offset, ", %s", row[i]);
            offset += 2;
        }
        offset += strlen(row[i]);
    }
    
    sprintf(subordinates_ids, ", %d", o->id);
    
    sprintf(query, "UPDATE `organizations` SET `admin_id`=-1 WHERE `id` IN (%s)", subordinates_ids);
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    memset(query, 0, sizeof(query));
    sprintf(query, "UPDATE `people` SET `admin_id`=-1 WHERE `organization_id` IN (%s)", subordinates_ids);
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    memset(query, 0, sizeof(query));
    sprintf(query, "UPDATE `organizations` SET `path`=REPLACE(`path`, '%s', '%s'), `updatedAt`='%s' WHERE `id` IN (%s)", o->path, path, (char *)date, subordinates_ids);
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    mysql_free_result(subordinates_result);
}

void insert_organization(MYSQL *connection, Organization *o)
{
    char query[4 * 1024];
    char name[1024];
    char functionalblockname[200];
    char date[19];
    
    memset(query, 0, sizeof(query));
    memset(name, 0, sizeof(name));
    memset(functionalblockname, 0, sizeof(functionalblockname));
    memset(date, 0, sizeof(date));

    ESCAPE(connection, name, o->name)
    ESCAPE(connection, functionalblockname, o->functionalblockname)
    
    sprintf(query, "SELECT * FROM `organizations` WHERE `idorg`=%s", o->idorg);
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL) {
        DUMPSQLERROR(connection, "");
    }
    
    if (mysql_num_rows(result)) {
        Organization fetched_o = { 0 };
        organization_from_mysql(&fetched_o, result);
        
        o->id = fetched_o.id;
        o->admin_id = fetched_o.admin_id;
        
        if (organization_is_equal(o, &fetched_o) == 0) {
            if (o->parent_id != fetched_o.parent_id) {
                organization_handle_subordinate_change(connection, &fetched_o, o->path);
            }
            
            current_time(date, 19);
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE `organizations` SET `idorg`='%s', `name`='%s', `path`='%s', `functionalblockcode`=%d, `functionalblockname`='%s', `parent_id`=%d, `admin_id`=%d, `aspk_idsbrf`='%s', `bankcode`='%s', `baseuid`='%s', `createdate`='%s', `dbid`='%s', `dismissdate`='%s', `idsbrf`='%s', `idtb`='%s', `orgcode`='%s', `status`='%s', `uid`='%s', `updatedAt`='%s'",
                    o->idorg, name, o->path, o->functionalblockcode, functionalblockname, o->parent_id, o->admin_id, o->aspk_idsbrf, o->bankcode, o->baseuid, o->createdate, o->dbid, o->dismissdate, o->idsbrf, o->idtb, o->orgcode, o->status, o->uid, (char *)date);
        }
        
        organization_clear(&fetched_o);
    } else {
        current_time(date, 19);
        memset(query, 0, sizeof(query));
        sprintf(query, "INSERT INTO `organizations`(`idorg`, `name`, `path`, `functionalblockcode`, `functionalblockname`, `parent_id`, `admin_id`, `aspk_idsbrf`, `bankcode`, `baseuid`, `createdate`, `dbid`, `dismissdate`, `idsbrf`, `idtb`, `orgcode`, `status`, `uid`, `createdAt`, `updatedAt`) VALUES('%s', '%s', '%s', %d, '%s', %d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                o->idorg, name, o->path, o->functionalblockcode, functionalblockname, o->parent_id, o->admin_id, (o->aspk_idsbrf == NULL) ? "" : o->aspk_idsbrf, (o->bankcode == NULL) ? "" : o->bankcode, (o->baseuid == NULL) ? "" : o->baseuid, (o->createdate == NULL) ? "" : o->createdate, (o->dbid == NULL) ? "" : o->dbid, (o->dismissdate == NULL) ? "" : o->dismissdate, (o->idsbrf == NULL) ? "" : o->idsbrf, (o->idtb == NULL) ? "" : o->idtb, (o->orgcode == NULL) ? "" : o->orgcode, (o->status == NULL) ? "" : o->status, (o->uid == NULL) ? "" : o->uid, (char *)date, (char *)date);
        
        if (mysql_query(connection, query)) {
            DUMPSQLERROR(connection, query);
        }
        
        o->id = (int)mysql_insert_id(connection);
    }
    
    mysql_free_result(result);
}
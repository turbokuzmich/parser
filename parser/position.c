//
//  position.c
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include "position.h"
#include "globals.h"
#include "current_time.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void position_from_attrs(Position *p, const char **attrs)
{
    if (p != NULL) {
        const char **i = attrs;
        while (*i != NULL) {
            CMPANDSAVECHARATTR(p, positionname, *i, *(i + 1));
            
            i += 2;
        }
    }
}

void position_clear(Position *p)
{
    SETCHARATTR(p, positionname, NULL);
    
    memset(p, 0, sizeof(*p));
}

void insert_position(MYSQL *connection, Position *position)
{
    char query_buffer[1024];
    char positionname[1024];
    char date[19];
    
    memset(query_buffer, 0, sizeof(query_buffer));
    memset(positionname, 0, sizeof(positionname));
    memset(date, 0, sizeof(date));
    
    ESCAPE(connection, positionname, position->positionname)
    
    sprintf(query_buffer, "SELECT * FROM `positions` WHERE `positionname`='%s'", positionname);
    if (mysql_query(connection, query_buffer)) {
        DUMPSQLERROR(connection, query_buffer);
    }
    
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL) {
        DUMPSQLERROR(connection, "");
    }
    
    if (mysql_num_rows(result)) {
        MYSQL_ROW row = mysql_row_seek(result, 0)->data;
        MYSQL_FIELD *field = mysql_fetch_fields(result);
        unsigned int field_count = mysql_num_fields(result);
        
        for (unsigned int i = 0; i < field_count; i++) {
            if (strcmp((field + i)->name, "id") == 0) {
                position->id = atoi(row[i]);
                break;
            }
        }
    } else {
        current_time(date, 19);
        memset(query_buffer, 0, sizeof(query_buffer));
        sprintf(query_buffer, "INSERT INTO `positions`(`positionname`, `createdAt`, `updatedAt`) VALUES('%s', '%s', '%s')", positionname, (char *)date, (char *)date);
        if (mysql_query(connection, query_buffer)) {
            DUMPSQLERROR(connection, query_buffer);
        }
        position->id = (int)mysql_insert_id(connection);
    }
    
    mysql_free_result(result);
}
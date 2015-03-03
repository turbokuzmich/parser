//
//  person.c
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include "person.h"
#include "globals.h"
#include "current_time.h"
#include "transliterate.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void person_from_attrs(Person *p, const char **attrs)
{
    if (p != NULL) {
        const char **i = attrs;
        while (*i != NULL) {
            CMPANDSAVEINTATTR(p, id, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, idpers, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, username, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, password, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, password_sha, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, firstname, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, parentname, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, surname, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, email_secondary, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, status, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, saba_export, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, is_initialized, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, saba_id, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, blocked, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, main, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, activation_reason, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, deactivation_reason, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, activation_changed, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, to_sync, *i, *(i + 1));
            CMPANDSAVEINTATTR(p, copyValidatedAt, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, bankcode, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, dismissdate, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, education, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, email, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, inn, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, ischief, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, isopk, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, lengthofservicebank, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, lengthofservicesb, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, orgcode, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, possibleid, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, realpositiondates, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, retirementins, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, sex, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, skip, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, telcity, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, tellocal, *i, *(i + 1));
            CMPANDSAVECHARATTR(p, uid, *i, *(i + 1));
            
            i += 2;
        }
    }
}

void person_clear(Person *p)
{
    SETCHARATTR(p, idpers, NULL);
    SETCHARATTR(p, username, NULL);
    SETCHARATTR(p, password, NULL);
    SETCHARATTR(p, password_sha, NULL);
    SETCHARATTR(p, firstname, NULL);
    SETCHARATTR(p, parentname, NULL);
    SETCHARATTR(p, surname, NULL);
    SETCHARATTR(p, email_secondary, NULL);
    SETCHARATTR(p, activation_reason, NULL);
    SETCHARATTR(p, deactivation_reason, NULL);
    SETCHARATTR(p, bankcode, NULL);
    SETCHARATTR(p, dismissdate, NULL);
    SETCHARATTR(p, education, NULL);
    SETCHARATTR(p, email, NULL);
    SETCHARATTR(p, inn, NULL);
    SETCHARATTR(p, ischief, NULL);
    SETCHARATTR(p, isopk, NULL);
    SETCHARATTR(p, lengthofservicebank, NULL);
    SETCHARATTR(p, lengthofservicesb, NULL);
    SETCHARATTR(p, orgcode, NULL);
    SETCHARATTR(p, possibleid, NULL);
    SETCHARATTR(p, realpositiondates, NULL);
    SETCHARATTR(p, retirementins, NULL);
    SETCHARATTR(p, sex, NULL);
    SETCHARATTR(p, skip, NULL);
    SETCHARATTR(p, telcity, NULL);
    SETCHARATTR(p, tellocal, NULL);
    SETCHARATTR(p, uid, NULL);

    memset(p, 0, sizeof(*p));
}

char *new_person_username(MYSQL *connection, char *firstname, char *parentname, char *surname)
{
    
}

void insert_person(MYSQL *connection, Person *p)
{
    char query[8 * 1024];
    char firstname[256];
    char parentname[256];
    char surname[256];
    char education[1024];
    char lengthofservicebank[8 * 1024];
    char lengthofservicesb[8 * 1024];
    char realpositiondates[1024];
    char retirementins[2014];
    char date[19];
    
    memset(query, 0, sizeof(query));
    memset(firstname, 0, sizeof(firstname));
    memset(parentname, 0, sizeof(parentname));
    memset(surname, 0, sizeof(surname));
    memset(education, 0, sizeof(education));
    memset(lengthofservicebank, 0, sizeof(lengthofservicebank));
    memset(lengthofservicesb, 0, sizeof(lengthofservicesb));
    memset(realpositiondates, 0, sizeof(realpositiondates));
    memset(retirementins, 0, sizeof(retirementins));
    memset(date, 0, sizeof(date));

    ESCAPE(connection, firstname, p->firstname)
    ESCAPE(connection, parentname, p->parentname)
    ESCAPE(connection, surname, p->surname)
    ESCAPE(connection, education, p->education)
    ESCAPE(connection, lengthofservicebank, p->lengthofservicebank)
    ESCAPE(connection, lengthofservicesb, p->lengthofservicesb)
    ESCAPE(connection, realpositiondates, p->realpositiondates)
    ESCAPE(connection, retirementins, p->retirementins)
    
    sprintf(query, "SELECT * FROM `people` WHERE `idpers`='%s'", p->idpers);
    if (mysql_query(connection, query)) {
        DUMPSQLERROR(connection, query);
    }
    
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL) {
        DUMPSQLERROR(connection, "");
    }
    
    if (mysql_num_rows(result)) {
        
    } else {
        current_time(date, 19);
        memset(query, 0, sizeof(query));
        
//        sprintf(query, "INSERT INTO `people`(`idpers`, `username`) VALUES('%s', '%s')",
//                p->idpers, p->username);
    }
    
    mysql_free_result(result);
}
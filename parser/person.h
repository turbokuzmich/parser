//
//  person.h
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include <mysql.h>

#ifndef __parser__person__
#define __parser__person__

struct person_t {
    unsigned int id;
    char *idpers;
    char *username;
    char *password;
    char *password_sha;
    char *firstname;
    char *parentname;
    char *surname;
    char *email_secondary;
    unsigned int status;
    unsigned int saba_export;
    unsigned int is_initialized;
    unsigned int saba_id;
    unsigned int blocked;
    unsigned int main;
    char *activation_reason;
    char *deactivation_reason;
    unsigned int activation_changed;
    unsigned int to_sync;
    unsigned int copyValidatedAt;
    unsigned int admin_id;
    unsigned int organization_id;
    unsigned int position_id;
    unsigned int copy_id;
    char *bankcode;
    char *birthdate;
    char *dismissdate;
    char *education;
    char *email;
    char *inn;
    char *ischief;
    char *isopk;
    char *lengthofservicebank;
    char *lengthofservicesb;
    char *orgcode;
    char *positiondate;
    char *possibleid;
    char *realpositiondates;
    char *retirementins;
    char *sex;
    char *skip;
    char *telcity;
    char *tellocal;
    char *uid;
};
typedef struct person_t Person;

void person_from_attrs(Person *p, const char **attrs);

void person_clear(Person *p);

void insert_person(MYSQL *connection, Person *p);

#endif /* defined(__parser__person__) */

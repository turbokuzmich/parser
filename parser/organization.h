//
//  organization.h
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include <mysql.h>

#ifndef __parser__organization__
#define __parser__organization__

struct organization_t
{
    unsigned int id;
    char *idorg;
    char *name;
    char *path;
    unsigned int functionalblockcode;
    char *functionalblockname;
    unsigned int integrity_validated_at;
    unsigned int integrity_valid;
    char *integrity_invalid_reason;
    unsigned int integrity_invalid_root;
    char *aspk_idsbrf;
    char *bankcode;
    char *baseuid;
    char *createdate;
    char *dbid;
    char *dismissdate;
    char *idsbrf;
    char *idtb;
    char *orgcode;
    char *status;
    char *uid;
    unsigned int admin_id;
    unsigned int parent_id;
    
    int is_dirty;
};

typedef struct organization_t Organization;

void organization_from_attrs(Organization *o, const char **attrs);

void organization_clear(Organization *o);

void insert_organization(MYSQL *connection, Organization *o);

#endif /* defined(__parser__organization__) */

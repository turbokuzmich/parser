//
//  position.h
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include <mysql.h>

#ifndef __parser__position__
#define __parser__position__

struct position_t
{
    unsigned int id;
    char *positionname;
};
typedef struct position_t Position;

void position_from_attrs(Position *p, const char **attrs);

void position_clear(Position *p);

void insert_position(MYSQL *connection, Position *position);

#endif /* defined(__parser__position__) */

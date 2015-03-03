//
//  Header.h
//  parser
//
//  Created by ricky on 09/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#ifndef parser_globals_h
#define parser_globals_h

#define SETCHARATTR(ent, name, val)             if (ent->name != NULL) { \
                                                    free(ent->name); \
                                                } \
                                                if (val == NULL) { \
                                                    ent->name = NULL; \
                                                } else { \
                                                    ent->name = strdup(val); \
                                                }

#define SETINTATTR(ent, name, val)              ent->name = atoi(val);

#define CMPATTR(ent, name, key, val, iftrue)    if (strcmp(key, #name) == 0) { \
                                                    iftrue(ent, name, val) \
                                                }

#define CMPANDSAVECHARATTR(ent, name, key, val) CMPATTR(ent, name, key, val, SETCHARATTR)

#define CMPANDSAVEINTATTR(ent, name, key, val)  CMPATTR(ent, name, key, val, SETINTATTR)


#define DUMPSQLERROR(connection, query) fprintf(stderr, "%s\n", mysql_error(connection)); fprintf(stderr, "%s\n\n", query); exit;

#define ESCAPE(connection, output, input)   if (input != NULL) { \
                                                mysql_real_escape_string(connection, output, input, strlen(input)); \
                                            }

#endif

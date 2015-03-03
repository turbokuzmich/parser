//
//  main.c
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include "parser.h"

int main(int argc, const char * argv[]) {
    Parser p = parser_create();
    
    parser_db_connect(p, "192.168.0.4", "converter-dev", "rjydthnth", "converter2");
    parser_parse(p, "obf.xml");
    
    parser_destroy(p);
    
    return 0;
}

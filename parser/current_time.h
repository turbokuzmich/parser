//
//  current_time.h
//  parser
//
//  Created by ricky on 11/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include <time.h>

#ifndef parser_current_time_h
#define parser_current_time_h

static void current_time(char *date, size_t length)
{
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(date, length, "%Y-%m-%d %H:%M:%S", timeinfo);
}

#endif

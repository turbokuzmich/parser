//
//  utf8.h
//  parser
//
//  Created by ricky on 01/03/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#ifndef __parser__utf8__
#define __parser__utf8__

#include <stdlib.h>
#include <stdbool.h>

bool utf8_is_continuation(char c);
bool utf8_validate(char * s);
bool utf8_is_single_byte(char * c);
bool utf8_is_double_byte(char * c);
bool utf8_is_triple_byte(char * c);
bool utf8_is_quadruple_byte(char * c);

size_t utf8_strlen(char * s);
char * utf8_remove_trailing_newline(char * s);
char * utf8_remove_char(char * s, size_t n);
char * utf8_add_char(char * s, char * c, size_t n);
char * utf8_replace(char * needle, char * replace, char * haystack);
char * utf8_replace_all(char * needle, char * replace, char * haystack);
size_t utf8_num_bytes(char * s);

// Escape the null bytes in the given string that has the given length
char * utf8_escape_null_bytes(const char * s, size_t num);

#endif /* defined(__parser__utf8__) */

//
//  transliterate.c
//  parser
//
//  Created by ricky on 01/03/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#include <string.h>
#include "transliterate.h"
#include "utf8.h"


static char *clet1 = "А";
static char *llet1 = "а";
static char *clet2 = "Б";
static char *llet2 = "б";
static char *clet3 = "В";
static char *llet3 = "в";
static char *clet4 = "Г";
static char *llet4 = "г";
static char *clet5 = "Д";
static char *llet5 = "д";
static char *clet6 = "Е";
static char *llet6 = "е";
static char *clet7 = "Ё";
static char *llet7 = "ё";
static char *clet8 = "Ж";
static char *llet8 = "ж";
static char *clet9 = "З";
static char *llet9 = "з";
static char *clet10 = "И";
static char *llet10 = "и";
static char *clet11 = "Й";
static char *llet11 = "й";
static char *clet12 = "К";
static char *llet12 = "к";
static char *clet13 = "Л";
static char *llet13 = "л";
static char *clet14 = "М";
static char *llet14 = "м";
static char *clet15 = "Н";
static char *llet15 = "н";
static char *clet16 = "О";
static char *llet16 = "о";
static char *clet17 = "П";
static char *llet17 = "п";
static char *clet18 = "Р";
static char *llet18 = "р";
static char *clet19 = "С";
static char *llet19 = "с";
static char *clet20 = "Т";
static char *llet20 = "т";
static char *clet21 = "У";
static char *llet21 = "у";
static char *clet22 = "Ф";
static char *llet22 = "ф";
static char *clet23 = "Х";
static char *llet23 = "х";
static char *clet24 = "Ц";
static char *llet24 = "ц";
static char *clet25 = "Ч";
static char *llet25 = "ч";
static char *clet26 = "Ш";
static char *llet26 = "ш";
static char *clet27 = "Щ";
static char *llet27 = "щ";
static char *clet28 = "Ъ";
static char *llet28 = "ъ";
static char *clet29 = "Ы";
static char *llet29 = "ы";
static char *clet30 = "Ь";
static char *llet30 = "ь";
static char *clet31 = "Э";
static char *llet31 = "э";
static char *clet32 = "Ю";
static char *llet32 = "ю";
static char *clet33 = "Я";
static char *llet33 = "я";

static char *ctra1 = "A";
static char *ltra1 = "a";
static char *ctra2 = "B";
static char *ltra2 = "b";
static char *ctra3 = "V";
static char *ltra3 = "v";
static char *ctra4 = "G";
static char *ltra4 = "g";
static char *ctra5 = "D";
static char *ltra5 = "d";
static char *ctra6 = "E";
static char *ltra6 = "e";
static char *ctra7 = "E";
static char *ltra7 = "e";
static char *ctra8 = "Zh";
static char *ltra8 = "zh";
static char *ctra9 = "Z";
static char *ltra9 = "z";
static char *ctra10 = "I";
static char *ltra10 = "i";
static char *ctra11 = "Y";
static char *ltra11 = "y";
static char *ctra12 = "K";
static char *ltra12 = "k";
static char *ctra13 = "L";
static char *ltra13 = "l";
static char *ctra14 = "M";
static char *ltra14 = "m";
static char *ctra15 = "N";
static char *ltra15 = "n";
static char *ctra16 = "O";
static char *ltra16 = "o";
static char *ctra17 = "P";
static char *ltra17 = "p";
static char *ctra18 = "R";
static char *ltra18 = "r";
static char *ctra19 = "S";
static char *ltra19 = "s";
static char *ctra20 = "T";
static char *ltra20 = "t";
static char *ctra21 = "U";
static char *ltra21 = "u";
static char *ctra22 = "F";
static char *ltra22 = "f";
static char *ctra23 = "Kh";
static char *ltra23 = "kh";
static char *ctra24 = "Ts";
static char *ltra24 = "ts";
static char *ctra25 = "Ch";
static char *ltra25 = "ch";
static char *ctra26 = "Sh";
static char *ltra26 = "sh";
static char *ctra27 = "Sch";
static char *ltra27 = "sch";
static char *ctra28 = "";
static char *ltra28 = "";
static char *ctra29 = "Y";
static char *ltra29 = "y";
static char *ctra30 = "";
static char *ltra30 = "";
static char *ctra31 = "E";
static char *ltra31 = "e";
static char *ctra32 = "Yu";
static char *ltra32 = "yu";
static char *ctra33 = "Ya";
static char *ltra33 = "ya";

char *translit_create(const char *input)
{
    char *russianLetters[66] = {
        clet1, llet1,
        clet2, llet2,
        clet3, llet3,
        clet4, llet4,
        clet5, llet5,
        clet6, llet6,
        clet7, llet7,
        clet8, llet8,
        clet9, llet9,
        clet10, llet10,
        clet11, llet11,
        clet12, llet12,
        clet13, llet13,
        clet14, llet14,
        clet15, llet15,
        clet16, llet16,
        clet17, llet17,
        clet18, llet18,
        clet19, llet19,
        clet20, llet20,
        clet21, llet21,
        clet22, llet22,
        clet23, llet23,
        clet24, llet24,
        clet25, llet25,
        clet26, llet26,
        clet27, llet27,
        clet28, llet28,
        clet29, llet29,
        clet30, llet30,
        clet31, llet31,
        clet32, llet32,
        clet33, llet33,
    };
    char *latinLetters[66] = {
        ctra1, ltra1,
        ctra2, ltra2,
        ctra3, ltra3,
        ctra4, ltra4,
        ctra5, ltra5,
        ctra6, ltra6,
        ctra7, ltra7,
        ctra8, ltra8,
        ctra9, ltra9,
        ctra10, ltra10,
        ctra11, ltra11,
        ctra12, ltra12,
        ctra13, ltra13,
        ctra14, ltra14,
        ctra15, ltra15,
        ctra16, ltra16,
        ctra17, ltra17,
        ctra18, ltra18,
        ctra19, ltra19,
        ctra20, ltra20,
        ctra21, ltra21,
        ctra22, ltra22,
        ctra23, ltra23,
        ctra24, ltra24,
        ctra25, ltra25,
        ctra26, ltra26,
        ctra27, ltra27,
        ctra28, ltra28,
        ctra29, ltra29,
        ctra30, ltra30,
        ctra31, ltra31,
        ctra32, ltra32,
        ctra33, ltra33,
    };
    
    size_t length = strlen(input);
    size_t num_letters = sizeof(russianLetters) / sizeof(void *);
    char *output = malloc(length + 1);
    size_t store_size = 5;
    char store[store_size];
    char *loc;
    bool found = false;
    unsigned int offset = 0;
    unsigned int num_bytes = 0;
    unsigned int i = 0;
    
    memset(output, 0, length + 1);
    memset(store, 0, store_size);
    
    if (length > 0) {
        while (offset < length) {
            loc = (char *)input + offset;
            num_bytes = (unsigned int)utf8_num_bytes(loc);
            memset(store, 0, store_size);
            memcpy(store, loc, num_bytes);
            found = false;
            for (i = 0; i < num_letters; i++) {
                if (strcmp(store, russianLetters[i]) == 0) {
                    strcat(output, latinLetters[i]);
                    found = true;
                }
            }
            if (found == false) {
                strcat(output, store);
            }
            offset += num_bytes;
        }
    }
    
    return output;
}













































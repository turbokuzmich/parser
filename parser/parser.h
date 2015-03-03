//
//  parser.h
//  parser
//
//  Created by ricky on 06/02/2015.
//  Copyright (c) 2015 Imagespark. All rights reserved.
//

#ifndef __parser__parser__
#define __parser__parser__

#define ORGANIZATION_STACK_SIZE 20
#define FUNCTIONAL_BLOCK_NAMES_SIZE 20

typedef struct parser_t *Parser;

/**
 * конструктор парсера
 */
Parser parser_create();

/**
 * подключение к базе данных
 */
int parser_db_connect(Parser p, const char *host, const char *user, const char *passwd, const char *db);

/**
 * деструктор парсера
 */
void parser_destroy(Parser p);

/**
 * парсинг SAP-файла
 */
int parser_parse(Parser p, const char *filename);

#endif /* defined(__parser__parser__) */

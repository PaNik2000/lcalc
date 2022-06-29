/*
 * Lexer
 */

#ifndef __LCALC_LEXER_H
#define __LCALC_LEXER_H

#include "list.h"

#include <stdlib.h>

struct token {
	int type;
	char *value;
	size_t len;
};

extern struct list_op token_list_op;

/*
 * lexer_create_token
 */
void *lexer_create_token(unsigned count, va_list args);

/*
 * lexer_delete_token
 */
void lexer_delete_token(void *token);

/*
 * lexer_get_token_list
 */
struct list *lexer_get_token_list(char *str, size_t len);

/*
 * lexer_delete_token_list
 */
void lexer_delete_token_list(struct list *token_list);

/*
 * token_type_to_str
 */
const char *token_type_to_str(int type);

#endif

#include "lexer.h"
#include "list.h"

#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#ifdef DBG
#include <stdio.h> /* DBG */
#endif

#define TOKEN_TYPE_NUMBER		0
#define TOKEN_TYPE_OPERATION		1

#define TOKEN_TYPE_NUMBER_STR		"number"
#define TOKEN_TYPE_OPERATION_STR	"operation"
#define TOKEN_TYPE_UNDEFINED_STR	"undefined"

void *lexer_create_token(unsigned count, va_list args)
{
	struct token *new_token;

#ifdef DBG
	printf("DBG [lexer_create_token]  begin\n");
#endif

	if (count != 3) {
		errno = EINVAL;
		return NULL;
	}

	new_token = malloc(sizeof(*new_token));
	if (!new_token)
		return NULL;

	new_token->type		= va_arg(args, int);
	new_token->value	= va_arg(args, char *);
	new_token->len		= va_arg(args, size_t);

#ifdef DBG
	printf("DBG [lexer_create_token]  type = %d\n", new_token->type);
	printf("DBG [lexer_create_token]  end\n");
#endif

	return new_token;
}

void lexer_delete_token(void *token)
{
	free(token);
}

static int __isnum(char c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

struct list *lexer_get_token_list(char *str, size_t len)
{
	size_t i;
	struct list *token_list = NULL;
	struct list *list_iter = NULL;
	struct list *list_elem = NULL;
	size_t value_len;
	int token_type;

#ifdef DBG
	printf("DBG [lexer_get_token_list]  len = %lu\n", len);
#endif

	for (i = 0; i != len;) {
#ifdef DBG
		printf("DBG [lexer_get_token_list]  i = %lu\n", i);
#endif
		value_len = 0;

		switch (str[i]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			while (__isnum(str[i + value_len]))
				value_len++;
			token_type = TOKEN_TYPE_NUMBER;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			value_len = 1;
			token_type = TOKEN_TYPE_OPERATION;
			break;
		case ' ':
		case '\0':
			i++;
			continue;
		default:
			errno = EINVAL;
			goto free_list;
		}

		if (!token_list) {
			token_list = lcalc_list_create(&token_list_op, 3, token_type, &str[i], value_len);
			if (!token_list)
				return NULL;
			list_iter = token_list;
		} else {
			list_elem = lcalc_list_add(list_iter, &token_list_op, 3, token_type, &str[i], value_len);
			if (!list_elem)
				goto free_list;
			list_iter = list_elem;
		}
#ifdef DBG
		printf("DBG [lexer_get_token_list]  list_iter->type = %s\n", token_type_to_str(((struct token *)list_iter->value)->type));
#endif

		i += value_len;
	}

	return token_list;

free_list:
	if (token_list)
		lcalc_list_delete(token_list);

	return NULL;
}

void lexer_delete_token_list(struct list *token_list)
{
	lcalc_list_delete(token_list);
}

const char *token_type_to_str(int type)
{
	switch (type) {
	case TOKEN_TYPE_NUMBER:
		return TOKEN_TYPE_NUMBER_STR;
	case TOKEN_TYPE_OPERATION:
		return TOKEN_TYPE_OPERATION_STR;
	default:
		return NULL;
	}
}

struct list_op token_list_op = {
	lexer_create_token,
	lexer_delete_token
};

/*
 * modules
 *  - preproc
 *  - lexer
 *  - parser
 *  - calc
 *
 * operations
 *  - (+)
 *  - (-)
 *  - (*)
 *  - (/)
 */

#include "list.h"
#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct list *token_list;
	struct list *list_iter;
	struct token *token;
	char *str;
	size_t str_len;
	const char input[] = "1 - 4   / 23 * 5 - 323 + 4   "; 
/*	const char input[] = "=";*/ 

	str_len = sizeof(input);
	
	str = malloc(str_len);
	if (!str)
		return EXIT_FAILURE;

	strncpy(str, input, str_len); 

	token_list = lexer_get_token_list(str, str_len); 
	if (!token_list) {
		printf("Failed to get token list. Error %d\n", errno);
		return EXIT_FAILURE;
	}

	list_iter = token_list;
	while (list_iter) {
		token = (struct token *) list_iter->value;
		printf("[%s]  %.*s\n", token_type_to_str(token->type), (int) token->len, token->value);
		list_iter = list_iter->right;
	}

	free(str);
	lexer_delete_token_list(token_list);

	return 0;
}

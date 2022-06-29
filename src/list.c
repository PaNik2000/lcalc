#include "list.h"

#include <stdlib.h>
#include <stdarg.h>

static struct list *__create_elem(struct list *left, struct list *right, struct list_op *op, int count, va_list args) 
{
	struct list *new_elem;
	void *value;

	if (op && op->create) {
		value = op->create(count, args);
		if (!value)
			return NULL;
	}

	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
		return NULL;

	new_elem->left	= left;
	new_elem->right	= right;
	new_elem->value	= value;
	new_elem->op 	= op;

	return new_elem;
}

struct list *lcalc_list_add(struct list *list, struct list_op *op, int count, ...)
{
	struct list *new_elem;
	va_list args;

	va_start(args, count);

	new_elem = __create_elem(list, list->right, op, count, args);
	if (!new_elem)
		return NULL;
	list->right = new_elem;

	va_end(args);

	return new_elem;
}

struct list *lcalc_list_remove(struct list *list)
{
	struct list *left;
	struct list *right;

	if (!list)
		return NULL;

	left = list->left;
	right = list->right;

	if (list->op && list->op->delete)
		list->op->delete(list->value);
	free(list);

	if (left)
		left->right = right;

	if (right)
		right->left = left;

	return (left ? left : right);
}

struct list *lcalc_list_create(struct list_op *op, int count, ...)
{
	struct list *new_elem;
	va_list args;

	va_start(args, count);

	new_elem = __create_elem(NULL, NULL, op, count, args);
	if (!new_elem)
		return NULL;

	va_end(args);

	return new_elem;
}

void lcalc_list_delete(struct list *list)
{
	while (list)
		list = lcalc_list_remove(list);
}

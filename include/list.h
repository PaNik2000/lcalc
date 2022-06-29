#ifndef __LCALC_LIST_H
#define __LCALC_LIST_H

#include <stdarg.h>

struct list_op {
	void *(*create) (unsigned count, va_list args);
	void (*delete) (void *value);
};

struct list {
	void *value;
	struct list *left;
	struct list *right;
	struct list_op *op;
};

/*
 * lcalc_list_add - add new element to list
 * params:
 *  - list - element after which new element has to be inserted
 *  - value - value for new list element
 * returns:
 *  pointer to new element in list or NULL if error occurred
 */
struct list *lcalc_list_add(struct list *list, struct list_op *op, int count, ...);

/*
 * lcalc_list_remove
 */
struct list *lcalc_list_remove(struct list *list);

/*
 * lcalc_list_create
 */
struct list *lcalc_list_create(struct list_op *op, int count, ...);

/*
 * lcalc_list_delete
 */
void lcalc_list_delete(struct list *list);

#endif

#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct node {
    struct node *next;
    struct node *prev;
    void *data;
} node_t;

typedef struct {
    node_t *first;
    node_t *last;
    size_t size;
} list_t;

void list_init(list_t *l);
void list_finish(list_t *l);
bool list_empty(list_t *l);
node_t *list_get_first(list_t *l);
node_t *list_get_last(list_t *l);
size_t list_size(list_t *l);
void list_insert(list_t *l, void *data);
void list_remove(list_t *l, node_t *node);

#endif /* __LIST_H__ */

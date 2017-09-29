#include "list.h"
#include <assert.h>
#include <search.h>
#include <stdlib.h>

void list_init(list_t *l)
{
    l->first = NULL;
    l->last = NULL;
    l->size = 0u;
}

void list_finish(list_t *l)
{
    assert(l->first == NULL);
    assert(l->last == NULL);
}

bool list_empty(list_t *l)
{
    return l->first == NULL;
}

node_t *list_get_first(list_t *l)
{
    return l->first;
}

node_t *list_get_last(list_t *l)
{
    return l->last;
}

size_t list_size(list_t *l)
{
    return l->size;
}

void list_insert(list_t *l, void *data)
{
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    if (list_empty(l)) {
        l->first = node;
        insque(node, NULL);
    } else {
        insque(node, l->last);
    }
    l->last = node;
    l->size++;
}

void list_remove(list_t *l, node_t *node)
{
    if (node == l->first) {
        l->first = node->next;
    }
    if (node == l->last) {
        l->last = node->prev;
    }
    remque(node);
    free(node);
    l->size--;
}

#include <stdlib.h>
#include "ut.h"
#include "list.h"

static int basic(void)
{
    list_t l;
    list_init(&l);
    /* Insert. */
    int *data;
    for (int i = 0; i < 10; ++i) {
        data = (int *)malloc(sizeof(int));
        *data = i;
        list_insert(&l, (void *)data);
    }
    ASSERT(10 == list_size(&l));
    node_t *n = list_get_first(&l);
    node_t *n5;
    for (int i = 0; i < 10; ++i) {
        data = (int *)n->data;
        ASSERT(i == *data);
        n = n->next;
        if (i == 5)
            n5 = n;
    }
    /* Remove first. */
    n = list_get_first(&l);
    free(n->data);
    list_remove(&l, n);
    data = (int *)list_get_first(&l)->data;
    ASSERT(1 == *data);
    ASSERT(9 == list_size(&l));
    /* Remove last. */
    n = list_get_last(&l);
    free(n->data);
    list_remove(&l, n);
    data = (int *)list_get_last(&l)->data;
    ASSERT(8 == *data);
    ASSERT(8 == list_size(&l));
    /* Remove middle. */
    free(n5->data);
    list_remove(&l, n5);
    data = (int *)list_get_last(&l)->data;
    ASSERT(8 == *data);
    ASSERT(7 == list_size(&l));
    /* Clear list. */
    while (!list_empty(&l)) {
        n = list_get_first(&l);
        free(n->data);
        list_remove(&l, n);
    }
    ASSERT(0 == list_size(&l));
    list_finish(&l);
    return 0;
}

void list_test(void)
{
    ut_run(basic);
}

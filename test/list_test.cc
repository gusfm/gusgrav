#include <gtest/gtest.h>
extern "C" {
#include "list.h"
}

TEST(list_test, basic)
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
    EXPECT_EQ(10, list_size(&l));
    node_t *n = list_get_first(&l);
    node_t *n5 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data = (int *)n->data;
        EXPECT_EQ(i, *data);
        n = n->next;
        if (i == 5)
            n5 = n;
    }
    ASSERT_NE(n5, nullptr);
    /* Remove first. */
    n = list_get_first(&l);
    free(n->data);
    list_remove(&l, n);
    data = (int *)list_get_first(&l)->data;
    EXPECT_EQ(1, *data);
    EXPECT_EQ(9, list_size(&l));
    /* Remove last. */
    n = list_get_last(&l);
    free(n->data);
    list_remove(&l, n);
    data = (int *)list_get_last(&l)->data;
    EXPECT_EQ(8, *data);
    EXPECT_EQ(8, list_size(&l));
    /* Remove middle. */
    free(n5->data);
    list_remove(&l, n5);
    data = (int *)list_get_last(&l)->data;
    EXPECT_EQ(8, *data);
    EXPECT_EQ(7, list_size(&l));
    /* Clear list. */
    while (!list_empty(&l)) {
        n = list_get_first(&l);
        free(n->data);
        list_remove(&l, n);
    }
    EXPECT_EQ(0, list_size(&l));
    list_finish(&l);
}

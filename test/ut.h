#ifndef UT_H
#define UT_H

#include <stdio.h>

struct ut {
    unsigned int run;
    unsigned int failed;
};

extern struct ut unit_test;

#define ASSERT(test)                                                    \
    do {                                                                \
        if (!(test)) {                                                  \
            printf("%s:%d: assertion failed: %s\n", __FILE__, __LINE__, \
                   #test);                                              \
            unit_test.failed++;                                         \
            return -1;                                                  \
        }                                                               \
    } while (0)

#define ASSERTD(test, val1, val2, fmt)  \
    do {                                \
        printf("val1: " fmt "\n", val1); \
        printf("val2: " fmt "\n", val2); \
        ASSERT(test);                   \
    } while (0)

#define ut_run(test)                                                    \
    do {                                                                \
        int result = test();                                            \
        unit_test.run++;                                                \
        printf("%s.%s: %s\n", __func__, #test, result ? "FAIL" : "OK"); \
    } while (0)

#define ut_result()                                      \
    do {                                                 \
        printf("%u tests executed ", unit_test.run);     \
        if (unit_test.failed == 0) {                     \
            printf("successfully\n");                    \
        } else {                                         \
            printf("and %u failed\n", unit_test.failed); \
            return -1;                                   \
        }                                                \
    } while (0)

#endif /* UT_H */

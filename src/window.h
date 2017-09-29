#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stddef.h>

int window_init(const char *name, size_t width, size_t height);
void window_terminate(void);
void window_main_loop(void);

#endif /* __WINDOW_H__ */

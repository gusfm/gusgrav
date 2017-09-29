#ifndef __UNIVERSE_H__
#define __UNIVERSE_H__

#include <stddef.h>
#include "vector.h"

void universe_init(size_t size_x, size_t size_y);
void universe_finish(void);
void universe_toggle_render_info(void);
void universe_render(void);
void universe_process(void);
void universe_select_body(vector_t *pos);
void universe_create_body(vector_t *pos);

#endif /* __UNIVERSE_H__ */

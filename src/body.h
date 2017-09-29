#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdbool.h>
#include "vector.h"

typedef struct {
    vector_t pos;          /* body position */
    vector_t vel;          /* body velocity */
    unsigned int mass;     /* the mass changes when two bodies merge */
    vector_t accel;        /* body acceleration */
    float radius;          /* radius is calculated based on the body mass */
    vector_t accel_render; /* acceleration vector to be rendered */
    vector_t vel_render;   /* velocity vector to be rendered */
    bool selected;         /* true if the body is selected */
} body_t;

body_t *body_create(vector_t *pos, vector_t *vel, unsigned int mass);
void body_destroy(body_t *b);
void body_clear_accel(body_t *b);
void body_calc_accel(body_t *i, body_t *j);
void body_process(body_t *b);
double body_distance(body_t *b1, body_t *b2);
void body_merge(body_t *b1, body_t *b2);
bool body_is_inside(body_t *b1, body_t *b2);
void body_render(body_t *b);
void body_render_info(body_t *b);
void body_process_render_info(body_t *b, double scale);
void body_select(body_t *b, vector_t *point);

#endif /* __OBJECT_H__ */

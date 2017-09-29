#include "vector.h"
#include <math.h>

void vector_set(vector_t *v, double x, double y)
{
    v->x = x;
    v->y = y;
}

void vector_add(vector_t *v, const vector_t *v1, const vector_t *v2)
{
    v->x = v1->x + v2->x;
    v->y = v1->y + v2->y;
}

void vector_add_eq(vector_t *v, const vector_t *v1)
{
    v->x += v1->x;
    v->y += v1->y;
}

void vector_add_scalar_eq(vector_t *v, double s)
{
    v->x += s;
    v->y += s;
}

void vector_sub(vector_t *v, const vector_t *v1, const vector_t *v2)
{
    v->x = v1->x - v2->x;
    v->y = v1->y - v2->y;
}

void vector_mult_scalar(vector_t *v, const vector_t *v1, double s)
{
    v->x = v1->x * s;
    v->y = v1->y * s;
}

void vector_mult_scalar_eq(vector_t *v, double s)
{
    v->x *= s;
    v->y *= s;
}

void vector_div_scalar(vector_t *v, const vector_t *v1, double s)
{
    v->x = v1->x / s;
    v->y = v1->y / s;
}

double vector_dot(const vector_t *v1, const vector_t *v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

double vector_distance(vector_t *v1, vector_t *v2)
{
    double xdiff, ydiff, x2, y2;
    xdiff = v1->x - v2->x;
    ydiff = v1->y - v2->y;
    x2 = (xdiff * xdiff);
    y2 = (ydiff * ydiff);
    return sqrt(x2 + y2);
}

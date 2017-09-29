#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
    double x;
    double y;
} vector_t;

void vector_set(vector_t *v, double x, double y);
void vector_add(vector_t *v, const vector_t *v1, const vector_t *v2);
void vector_add_eq(vector_t *v, const vector_t *v1);
void vector_add_scalar_eq(vector_t *v, double s);
void vector_sub(vector_t *v, const vector_t *v1, const vector_t *v2);
void vector_mult_scalar(vector_t *v, const vector_t *v1, double s);
void vector_mult_scalar_eq(vector_t *v, double s);
void vector_div_scalar(vector_t *v, const vector_t *v1, double s);
double vector_dot(const vector_t *v1, const vector_t *v2);
double vector_distance(vector_t *v1, vector_t *v2);

#endif /* __VECTOR_H__ */

#include "body.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>

#define EPS2 7.389056099l
#define G 6.67300E-3l /* Values too small makes forces too weak */

float calc_radius(unsigned int mass)
{
    return sqrtf(mass / M_PI);
}

body_t *body_create(vector_t *pos, vector_t *vel, unsigned int mass)
{
    body_t *b = malloc(sizeof(body_t));
    b->pos = *pos;
    b->vel = *vel;
    b->mass = mass;
    vector_set(&b->accel, 0, 0);
    b->radius = calc_radius(mass);
    vector_set(&b->accel_render, 0, 0);
    vector_set(&b->vel_render, 0, 0);
    b->selected = false;
    return b;
}

void body_destroy(body_t *b)
{
    free(b);
}

static void render_circle(vector_t *pos, float r, int num_segments)
{
    float theta = 2 * M_PI / (float)num_segments;
    float c = cosf(theta);  // pre-calculate the sine and cosine
    float s = sinf(theta);
    float x = r;  // we start at angle = 0
    float y = 0;
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        glVertex2f(x + pos->x, y + pos->y);  // output vertex
        // apply the rotation matrix
        float t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void body_render(body_t *b)
{
    if (b->selected) {
        glColor3d(128, 0, 128);
    }
    float r = b->radius;
    render_circle(&b->pos, r, 3 + r);
}

void body_clear_accel(body_t *b)
{
    vector_set(&b->accel, 0.0, 0.0);
}

/* Calculate acceleration of body i. */
void body_calc_accel(body_t *i, body_t *j)
{
    vector_t r_ij;
    /* dist_sqr = (ri - rj)^2 + EPS^2 */
    vector_sub(&r_ij, &j->pos, &i->pos);
    double dist_sqr = vector_dot(&r_ij, &r_ij) + EPS2;
    /* inv_dist3_sqr = (dist_sqr)^3/2 */
    double inv_dist3_sqr = 1.0l / sqrt(dist_sqr * dist_sqr * dist_sqr);
    /* s = G * m_j * inv_dist3_sqr */
    double s = G * j->mass * inv_dist3_sqr;
    /* a_i =  a_i + s * r_ij */
    vector_mult_scalar_eq(&r_ij, s);
    vector_add_eq(&i->accel, &r_ij);
}

static void vector_render(vector_t *p0, vector_t *p1)
{
    glBegin(GL_LINES);
    glVertex2f(p0->x, p0->y);
    glVertex2f(p1->x, p1->y);
    glEnd();
}

void body_render_info(body_t *b)
{
    glColor3f(1.0, 0.0, 0.0);
    vector_render(&b->pos, &b->accel_render);
    glColor3f(0.0, 1.0, 0.0);
    vector_render(&b->pos, &b->vel_render);
}

void body_process_render_info(body_t *b, double scale)
{
    /* Scale and translate vectors. */
    vector_mult_scalar(&b->accel_render, &b->accel, scale);
    vector_add_eq(&b->accel_render, &b->pos);
    vector_mult_scalar(&b->vel_render, &b->vel, scale / 50);
    vector_add_eq(&b->vel_render, &b->pos);
}

void body_process(body_t *b)
{
    vector_add_eq(&b->vel, &b->accel);
    vector_add_eq(&b->pos, &b->vel);
}

double body_distance(body_t *b1, body_t *b2)
{
    return vector_distance(&b1->pos, &b2->pos);
}

void body_merge(body_t *b1, body_t *b2)
{
    /* Momentum formula: p = m.v; p = p1 + p2; */
    vector_t p, p1, p2;
    vector_mult_scalar(&p1, &b1->vel, b1->mass);
    vector_mult_scalar(&p2, &b2->vel, b2->mass);
    vector_add(&p, &p1, &p2);
    b1->mass += b2->mass;
    vector_div_scalar(&b1->vel, &p, b1->mass);
    b1->radius = calc_radius(b1->mass);
}

static bool is_inside(body_t *b, vector_t *point)
{
    /* (p.x - circle.x)^2 + (p.y - circle.y)^2 < circle.radius^2 */
    double dx = (point->x - b->pos.x);
    double dy = (point->y - b->pos.y);
    double radius = b->radius;
    return (dx * dx) + (dy * dy) < radius * radius;
}

bool body_is_inside(body_t *b1, body_t *b2)
{
    return is_inside(b1, &b2->pos);
}

void body_select(body_t *b, vector_t *point)
{
    if (is_inside(b, point))
        b->selected = !b->selected;
}

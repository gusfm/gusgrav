#include "universe.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>
#include "body.h"
#include "list.h"

list_t bodies_;
bool render_info_;

void create_random_bodies(size_t number, size_t size_x, size_t size_y)
{
    srand(time(NULL));
    for (size_t i = 0; i < number; ++i) {
        vector_t pos = {rand() % size_x, rand() % size_y};
        vector_t vel = {((rand() % 10) - 5) / 5.0, ((rand() % 10) - 5) / 5.0};
        list_insert(&bodies_, body_create(&pos, &vel, 1 + (rand() % 100)));
    }
}

void universe_init(size_t size_x, size_t size_y)
{
    render_info_ = false;
    list_init(&bodies_);
    create_random_bodies(1000, size_x, size_y);
}

void universe_finish(void)
{
    while (!list_empty(&bodies_)) {
        node_t *node = list_get_first(&bodies_);
        body_destroy((body_t *)node->data);
        list_remove(&bodies_, node);
    }
    list_finish(&bodies_);
}

void universe_toggle_render_info(void)
{
    render_info_ = !render_info_;
}

void universe_render(void)
{
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *body = node->data;
        glColor3f(1.0, 1.0, 1.0);
        body_render(body);
        if (render_info_)
            body_render_info(body);
        node = node->next;
    }
}

static void calc_body_accel(body_t *body)
{
    body_clear_accel(body);
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *btmp = node->data;
        if (body != btmp)
            body_calc_accel(body, btmp);
        node = node->next;
    }
    body_process(body);
    if (render_info_)
        body_process_render_info(body, 1000);
}

static void calc_nbody_accel(void)
{
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *body = node->data;
        calc_body_accel(body);
        node = node->next;
    }
}

static void check_close_bodies(body_t *body)
{
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *btmp = node->data;
        if (body != btmp) {
            /* TODO: it's probably better to check for the distance. */
            if (body_is_inside(body, btmp)) {
                body_merge(body, btmp);
                body_destroy(btmp);
                node_t *ntmp = node->next;
                list_remove(&bodies_, node);
                node = ntmp;
                continue;
            }
        }
        node = node->next;
    }
}

static void check_close_bodies_all(void)
{
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *body = node->data;
        check_close_bodies(body);
        node = node->next;
    }
}

void universe_process(void)
{
    calc_nbody_accel();
    check_close_bodies_all();
}

void universe_select_body(vector_t *pos)
{
    node_t *node = list_get_first(&bodies_);
    while (node != NULL) {
        body_t *body = node->data;
        body_select(body, pos);
        node = node->next;
    }
}

void universe_create_body(vector_t *pos)
{
    vector_t vel = {0, 0};
    list_insert(&bodies_, body_create(pos, &vel, 1 + (rand() % 100)));
}

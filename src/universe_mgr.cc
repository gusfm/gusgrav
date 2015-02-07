#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>

#include "universe_mgr.h"
#include "point2d.h"
#include "universe.h"

#define GM_FONT_SIZE 16

// TODO: This file should probably be all c
typedef struct {
    Point2D *size;
    Universe *universe;
    FTGLPixmapFont *font;
    GLFWwindow *window;
} universe_mgr_t;

static universe_mgr_t universe_mgr;

static void universe_mgr_error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void universe_mgr_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_ESCAPE:
            /* Quit. */
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;

#if 0
        case GLFW_KEY_E:
            /* Enable energy button. */
            if (action == 1)
                universe_mgr.button_bmp ^= GM_ENERGY_BTN;
            break;

        case GLFW_KEY_G:
            /* Enable genome button. */
            if (action == 1)
                universe_mgr.button_bmp ^= GM_GENOME_BTN;
            break;

        case GLFW_KEY_S:
            /* Enable speed button. */
            if (action == 1)
                universe_mgr.button_bmp ^= GM_SPEED_BTN;
            break;
#endif

        default:
            break;
    }
}

static void universe_mgr_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
#if 0
    if (yoffset > 0 && universe_mgr.zoom > 20)
        return;
    if (yoffset < 0 && universe_mgr.zoom < 0)
        return;
    universe_mgr.zoom += yoffset * 10;
    glfwGetCursorPos(window, &universe_mgr.zoom_center.x, &universe_mgr.zoom_center.y);
    printf("(%lf, %lf), zoom=%f\n", universe_mgr.zoom_center.x, universe_mgr.zoom_center.y, universe_mgr.zoom);
#endif
}

static void universe_mgr_resize_callback(GLFWwindow* window, int width, int height)
{
    universe_mgr.size->set_x(width);
    universe_mgr.size->set_y(height);
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    /* Select the projection matrix. */
    glMatrixMode(GL_PROJECTION);
    /* Reset the projection matrix. */
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
}

static GLFWwindow *universe_mgr_create_window(const char *name, Point2D *size)
{
    GLFWwindow *window;
    /* Set an error callback. */
    glfwSetErrorCallback(universe_mgr_error_callback);
    /* Initialize window. */
    if (!glfwInit())
        return NULL;
    /* Creating a window and context. */
    window = glfwCreateWindow(size->get_x(), size->get_y(), name, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return NULL;
    }
    /* Make the OpenGL context current. */
    glfwMakeContextCurrent(window);
    /* Set a key input callback. */
    glfwSetKeyCallback(window, universe_mgr_key_callback);
    glfwSetScrollCallback(window, universe_mgr_scroll_callback);
    glfwSetFramebufferSizeCallback(window, universe_mgr_resize_callback);
    return window;
}

static void universe_mgr_gl_init(Point2D *size)
{
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)size->get_x(), (GLsizei)size->get_y());
    /* Change to the projection matrix, reset the matrix and set up orthagonal projection. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Paramters: left, right, bottom, top, near, far. */
    glOrtho(0.0f, size->get_x(), 0.0f, size->get_y(), 0.0f, 1.0f);
    /* ----- OpenGL settings ----- */
    /* Enable (gouraud) shading. */
    glEnable(GL_SMOOTH);
    /* Disable depth testing. */
    glDisable(GL_DEPTH_TEST);
#if 0
    /* Enable blending (used for alpha) and blending function to use. */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
    /* Set a 'chunky' line width. */
    glLineWidth(5.0f);
    /* Enable anti-aliasing on lines. */
    glEnable(GL_LINE_SMOOTH);
    /* Set a 'chunky' point size. */
    glPointSize(5.0f);
    /* Enable anti-aliasing on points. */
    glEnable(GL_POINT_SMOOTH);
}

int universe_mgr_init(const char *name, int sizeX, int sizeY)
{
    universe_mgr.size = new Point2D(sizeX, sizeY);
    /* Create window. */
    universe_mgr.window = universe_mgr_create_window(name, universe_mgr.size);
    if (universe_mgr.window == NULL) {
        return -1;
    }
    /* Create universe. */
    universe_mgr.universe = new Universe();
    /* Create a pixmap font from a TrueType file. */
    universe_mgr.font = new FTGLPixmapFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
    if (universe_mgr.font->Error()) {
        universe_mgr_terminate();
        return -1;
    }
    /* Set the font size. */
    universe_mgr.font->FaceSize(GM_FONT_SIZE, GM_FONT_SIZE);
    /* Initialize OpenGl. */
    universe_mgr_gl_init(universe_mgr.size);
    return 0;
}

void universe_mgr_terminate(void)
{
    if (universe_mgr.font) {
        delete universe_mgr.font;
    }
    if (universe_mgr.universe) {
        delete universe_mgr.universe;
    }
    if (universe_mgr.window) {
        glfwDestroyWindow(universe_mgr.window);
        glfwTerminate();
    }
}

#if 0
static void game_gmr_render_help(universe_mgr_t *universe_mgr)
{
    glRasterPos2f(0, universe_mgr->size.y - GM_FONT_SIZE);
    universe_mgr.font->Render("[q] quit game; [e] cell energy; [g] cell genome;");
}

static void universe_mgr_render_cell_count(universe_mgr_t *universe_mgr)
{
    char str[30];
    snprintf(str, sizeof(str), "cell count: %u", game_get_cell_count(universe_mgr->game));
    glRasterPos2f(universe_mgr->size.x - strlen(str) * 10, universe_mgr->size.y - GM_FONT_SIZE);
    universe_mgr.font->Render(str);
}

static void universe_mgr_render_cell_energy(universe_mgr_t *universe_mgr)
{
    char str[100];
    game_get_cell_energy_str(universe_mgr->game, str,  sizeof(str));
    glRasterPos2f(0, 3);
    universe_mgr.font->Render(str);
}
#endif

#if 0
static void universe_mgr_render_info(universe_mgr_t *universe_mgr)
{
    glPushMatrix();
    glColor3f(1.f, 1.f, 1.f);
    game_gmr_render_help(universe_mgr);
    universe_mgr_render_cell_count(universe_mgr);

    if (universe_mgr->button_bmp & GM_ENERGY_BTN) {
        /* Print the energy of all cells. */
        universe_mgr_render_cell_energy(universe_mgr);
    }
    glPopMatrix();
}
#endif

static void universe_mgr_render(void)
{
    /* Clear the screen. */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Reset the matrix. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* Draw stuff. */
    universe_mgr.universe->Render();
#if 0
    universe_mgr_draw_info(&universe_mgr);
#endif
    /* Do other glfw things. */
    glfwSwapBuffers(universe_mgr.window);
    glfwPollEvents();
}

void universe_mgr_main_loop(void)
{
    int loop_cnt = 0;
    struct timespec reqtime;
    reqtime.tv_sec = 0;
    reqtime.tv_nsec = 100000000; /* 100 ms */
    while (!glfwWindowShouldClose(universe_mgr.window)) {
        universe_mgr_render();
        if (loop_cnt++ % 10 == 0) {
            //game_process(universe_mgr.game);
        }
        nanosleep(&reqtime, NULL);
    }
}


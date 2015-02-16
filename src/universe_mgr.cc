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
#define ZOOM_SCALE 1.2L
#define PAN_STEP 10

// TODO: This file should probably be all c
typedef struct {
    Point2d *window_size;
    double zoom;
    Point2d pan;
    Point2d zoom_center;
    Universe *universe;
    FTGLPixmapFont *font;
    GLFWwindow *window;
} universe_mgr_t;

static universe_mgr_t universe_mgr;

static void universe_mgr_error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void universe_mgr_zoom(double factor)
{
    universe_mgr.zoom *= factor;
}

static void universe_mgr_pan(double dx, double dy)
{
    double zoom = universe_mgr.zoom;
    universe_mgr.pan.incr(dx / zoom, dy / zoom);
}

static void universe_mgr_zoom_at(double x, double y, double factor)
{
    universe_mgr_pan(-x, -y);
    universe_mgr_zoom(factor);
    universe_mgr_pan(x, y);
}

static void universe_mgr_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            /* Quit. */
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;

        case GLFW_KEY_A:
            /* Toggle acceleration vector rendering. */
            if (action == 1)
                universe_mgr.universe->toggle_render_acceleration();
            break;

        case GLFW_KEY_M:
            /* Toggle bodies merge. */
            if (action == 1)
                universe_mgr.universe->toggle_merge_bodies();
            break;

        case GLFW_KEY_LEFT:
            universe_mgr_pan(PAN_STEP, 0);
            break;

        case GLFW_KEY_RIGHT:
            universe_mgr_pan(-PAN_STEP, 0);
            break;

        case GLFW_KEY_DOWN:
            universe_mgr_pan(0, PAN_STEP);
            break;

        case GLFW_KEY_UP:
            universe_mgr_pan(0, -PAN_STEP);
            break;

        default:
            break;
    }
}

static void universe_mgr_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    double x, y;
    double height = universe_mgr.window_size->get_y();
    glfwGetCursorPos(window, &x, &y);
    y = height - y;
    if (yoffset > 0)
        universe_mgr_zoom_at(x, y, ZOOM_SCALE);
    else if (yoffset < 0)
        universe_mgr_zoom_at(x, y, 1/ZOOM_SCALE);
}

static void universe_mgr_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double x, y;
    double height = universe_mgr.window_size->get_y();
    glfwGetCursorPos(window, &x, &y);
    y = height - y;
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        std::cout << "x=" << x << " y=" << y << std::endl;
        Point2d p(x, y);
        universe_mgr.universe->SelectBodyAtPoint(p);
    }
}

static void universe_mgr_resize_callback(GLFWwindow* window, int width, int height)
{
    universe_mgr.window_size->set_x(width);
    universe_mgr.window_size->set_y(height);
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    /* Select the projection matrix. */
    glMatrixMode(GL_PROJECTION);
    /* Reset the projection matrix. */
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
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

static void game_mgr_render_help()
{
    glRasterPos2f(0, universe_mgr.window_size->get_y() - GM_FONT_SIZE);
    universe_mgr.font->Render("[q] quit; [a] render body info; [m] merge close bodies;");
}

static void universe_mgr_render_body_count()
{
    char str[30];
    snprintf(str, sizeof(str), "body count: %u", universe_mgr.universe->get_num_bodies());
    glRasterPos2f(universe_mgr.window_size->get_x() - strlen(str) * 10, universe_mgr.window_size->get_y() - GM_FONT_SIZE);
    universe_mgr.font->Render(str);
}

static void universe_mgr_render_info()
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    game_mgr_render_help();
    universe_mgr_render_body_count();
    glPopMatrix();
}

static void universe_mgr_render(void)
{
    /* Clear the screen. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset the matrix. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* Render info before scale and translate. */
    universe_mgr_render_info();
    /* Scale and translate. */
    glScalef(universe_mgr.zoom, universe_mgr.zoom, 1);
    glTranslatef(universe_mgr.pan.get_x(), universe_mgr.pan.get_y(), 0);
    /* Draw stuff. */
    universe_mgr.universe->Render();
    /* Do other glfw things. */
    glfwSwapBuffers(universe_mgr.window);
    glfwPollEvents();
}

static void universe_mgr_gl_init(Point2d *size)
{
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)size->get_x(), (GLsizei)size->get_y());
    /* Change to the projection matrix, reset the matrix and set up orthagonal projection. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Paramters: left, right, bottom, top, near, far. */
    glOrtho(0.0f, size->get_x(), 0.0f, size->get_y(), -1.0f, 1.0f);
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
    glLineWidth(1.0f);
    /* Enable anti-aliasing on lines. */
    glEnable(GL_LINE_SMOOTH);
    /* Set a 'chunky' point size. */
    glPointSize(1.0f);
    /* Enable anti-aliasing on points. */
    glEnable(GL_POINT_SMOOTH);
}

static GLFWwindow *universe_mgr_create_window(const char *name, Point2d *size)
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
    glfwSetMouseButtonCallback(window, universe_mgr_mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, universe_mgr_resize_callback);
    return window;
}

int universe_mgr_init(const char *name, int sizeX, int sizeY)
{
    universe_mgr.window_size = new Point2d(sizeX, sizeY);
    universe_mgr.zoom = 1.0;
    universe_mgr.zoom_center.set(universe_mgr.window_size->get_x() / 2, universe_mgr.window_size->get_y() / 2);
    /* Create window. */
    universe_mgr.window = universe_mgr_create_window(name, universe_mgr.window_size);
    if (universe_mgr.window == NULL) {
        return -1;
    }
    /* Create universe. */
    universe_mgr.universe = new Universe(*universe_mgr.window_size);
    /* Create a pixmap font from a TrueType file. */
    universe_mgr.font = new FTGLPixmapFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
    if (universe_mgr.font->Error()) {
        universe_mgr_terminate();
        return -1;
    }
    /* Set the font size. */
    universe_mgr.font->FaceSize(GM_FONT_SIZE, GM_FONT_SIZE);
    /* Initialize OpenGl. */
    universe_mgr_gl_init(universe_mgr.window_size);
    return 0;
}

void universe_mgr_main_loop(void)
{
    int loop_cnt = 0;
    struct timespec reqtime;
    reqtime.tv_sec = 0;
    reqtime.tv_nsec = 1000000; /* 1 ms */
    while (!glfwWindowShouldClose(universe_mgr.window)) {
        universe_mgr_render();
        if (loop_cnt++ % 10 == 0) {
            universe_mgr.universe->Process();
        }
        nanosleep(&reqtime, NULL);
    }
}


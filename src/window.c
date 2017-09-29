#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "universe.h"
#include "vector.h"

#define ZOOM_SCALE 1.2L
#define PAN_STEP 10

size_t window_width_;
size_t window_height_;
double window_zoom_;
double window_zoom_center_x_;
double window_zoom_center_y_;
double window_pan_x_;
double window_pan_y_;
GLFWwindow *glfw_window_;

static void window_error_callback(int error, const char *description)
{
    fprintf(stderr, "ERROR: %d: %s\n", error, description);
}

static void window_pan(double dx, double dy)
{
    double zoom = window_zoom_;
    window_pan_x_ += dx / zoom;
    window_pan_y_ += dy / zoom;
}

static void window_zoom_at(double x, double y, double factor)
{
    window_pan(-x, -y);
    window_zoom_ *= factor;
    window_pan(x, y);
}

static void window_reset_zoom_pan()
{
    window_zoom_ = 1.0;
    window_pan_x_ += 0.0;
    window_pan_y_ += 0.0;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods)
{
    (void)scancode;
    (void)mods;
    switch (key) {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            /* Quit. */
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;

        case GLFW_KEY_A:
            /* Toggle acceleration vector rendering. */
            if (action == 1)
                universe_toggle_render_info();
            break;

        case GLFW_KEY_LEFT:
            window_pan(PAN_STEP, 0);
            break;

        case GLFW_KEY_RIGHT:
            window_pan(-PAN_STEP, 0);
            break;

        case GLFW_KEY_DOWN:
            window_pan(0, PAN_STEP);
            break;

        case GLFW_KEY_UP:
            window_pan(0, -PAN_STEP);
            break;

        case GLFW_KEY_SPACE:
            window_reset_zoom_pan();
            break;

        default:
            break;
    }
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    (void)xoffset;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    y = (double)window_height_ - y;
    if (yoffset > 0)
        window_zoom_at(x, y, ZOOM_SCALE);
    else if (yoffset < 0)
        window_zoom_at(x, y, 1 / ZOOM_SCALE);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods)
{
    (void)mods;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    y = (double)window_height_ - y;
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        vector_t point = {x, y};
        universe_select_body(&point);
    } else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS) {
        vector_t point = {x, y};
        universe_create_body(&point);
    }
}

static void resize_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    window_width_ = width;
    window_height_ = height;
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    /* Select the projection matrix. */
    glMatrixMode(GL_PROJECTION);
    /* Reset the projection matrix. */
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

void window_terminate(void)
{
    universe_finish();
    if (glfw_window_) {
        glfwDestroyWindow(glfw_window_);
        glfwTerminate();
    }
}

static void window_render(void)
{
    /* Clear the screen. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset the matrix. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* Render info before scale and translate. */
    // window_render_info();
    /* Scale and translate. */
    glScalef(window_zoom_, window_zoom_, 1);
    glTranslatef(window_pan_x_, window_pan_y_, 0);
    /* Draw stuff. */
    universe_render();
    /* Do other glfw things. */
    glfwSwapBuffers(glfw_window_);
    glfwPollEvents();
}

static void gl_init(size_t width, size_t height)
{
    /* Setup our viewport to be the entire size of the window. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    /* Change to the projection matrix, reset the matrix and set up orthagonal
     * projection. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Paramters: left, right, bottom, top, near, far. */
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    /* ----- OpenGL settings ----- */
    /* Enable (gouraud) shading. */
    glEnable(GL_SMOOTH);
    /* Disable depth testing. */
    glDisable(GL_DEPTH_TEST);
    /* Set a 'chunky' line width. */
    glLineWidth(1.0f);
    /* Enable anti-aliasing on lines. */
    glEnable(GL_LINE_SMOOTH);
    /* Set a 'chunky' point size. */
    glPointSize(1.0f);
    /* Enable anti-aliasing on points. */
    glEnable(GL_POINT_SMOOTH);
}

static GLFWwindow *glfw_init(const char *name, size_t width, size_t height)
{
    GLFWwindow *window;
    /* Set an error callback. */
    glfwSetErrorCallback(window_error_callback);
    /* Initialize window. */
    if (!glfwInit())
        return NULL;
    /* Creating a window and context. */
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return NULL;
    }
    /* Make the OpenGL context current. */
    glfwMakeContextCurrent(window);
    /* Set a key input callback. */
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    return window;
}

int window_init(const char *name, size_t width, size_t height)
{
    window_width_ = width;
    window_height_ = height;
    window_zoom_ = 1.0;
    window_zoom_center_x_ = width / 2;
    window_zoom_center_y_ = height / 2;
    /* Create window. */
    glfw_window_ = glfw_init(name, width, height);
    if (glfw_window_ == NULL) {
        return -1;
    }
    /* Create universe. */
    universe_init(width, height);
    /* Initialize OpenGl. */
    gl_init(width, height);
    return 0;
}

static void check_fps(void)
{
    static double last_time_1s = 0;
    static unsigned int frames_1s = 0;
    double cur_time = glfwGetTime();
    frames_1s++;
    double dt = cur_time - last_time_1s;
    if (dt >= 1.0) {
        printf("%f fps\n", frames_1s / dt);
        last_time_1s = cur_time;
        frames_1s = 0;
    }
}

void window_main_loop(void)
{
    while (!glfwWindowShouldClose(glfw_window_)) {
        window_render();
        universe_process();
        check_fps();
    }
}

#include <cmath>
#include <GL/gl.h>
#include "object.h"

Object::Object(const Point2D &position, const Vector2D &velocity, unsigned int mass) :
    position_(position), velocity_(velocity), mass_(mass)
{
}

Object::~Object()
{
}

static void DrawCircle(const Point2D &p, float r, int num_segments)
{
    float theta = 2 * M_PI / (float)num_segments;
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = r;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        glVertex2f(x + p.get_x(), y + p.get_y());//output vertex
        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Object::Render()
{
    DrawCircle(position_, mass_, 10);
}

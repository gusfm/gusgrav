#include <cmath>
#include <GL/gl.h>
#include "body.h"

#define EPS2 7.389056099

Body::Body(const Point2d &position, const Vector2d &velocity, unsigned int mass) :
    position_(position), velocity_(velocity), acceleration_(Point2d(0, 0)), mass_(mass)
{
}

Body::~Body()
{
}

static void DrawCircle(const Point2d &p, float r, int num_segments)
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

void Body::Render()
{
    DrawCircle(position_, mass_, 10);
    acceleration_.Render(position_);
}

unsigned int Body::get_mass() const
{
    return mass_;
}

const Point2d &Body::get_velocity()
{
    return velocity_;
}

void Body::ClearAcceleration()
{
    acceleration_.set(0.0, 0.0);
}

void Body::CalculateAcceleration(const Body *j)
{
    // r_ij  [3 FLOPS]
    Vector2d r_ij = Vector2d(j->position_ - position_);
    // distSqr = dot(r_ij, r_ij) + EPS^2  [6 FLOPS]
    double distSqr = r_ij.dot(r_ij) + EPS2;
    // invDistCube =1/distSqr^(3/2)  [4 FLOPS (2 mul, 1 sqrt, 1 inv)]
    double distSixth = distSqr * distSqr * distSqr;
    double invDistCube = 1.0f / sqrt(distSixth);
    // s = m_j * invDistCube [1 FLOP]
    double s = j->get_mass() * invDistCube;
    // a_i =  a_i + s * r_ij [6 FLOPS]
    acceleration_ += r_ij * s;
}

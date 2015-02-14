#include <cmath>
#include <GL/gl.h>
#include "body.h"

#define EPS2 7.389056099


Body::Body(const Point2d &position, const Vector2d &velocity, unsigned int mass) :
    position_(position), velocity_(velocity), acceleration_(Point2d(0, 0)), mass_(mass)
{
    UpdateRadius();
}

Body::~Body()
{
}

void Body::UpdateRadius()
{
    radius_ = sqrtf(mass_ / M_PI);
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
    DrawCircle(position_, radius_, 2 + radius_);
}

void Body::RenderInfo()
{
    glColor3f(1.0, 0.0, 0.0);
    acceleration_render_.Render();
    glColor3f(0.0, 1.0, 0.0);
    velocity_render_.Render();
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
    double invDistCube = 1.0L / sqrt(distSixth);
    // s = m_j * invDistCube [1 FLOP]
    double s = j->get_mass() * invDistCube;
    // a_i =  a_i + s * r_ij [6 FLOPS]
    acceleration_ += r_ij * s;
}

void Body::ProcessInfoRender(double scale)
{
    acceleration_render_ = acceleration_ * scale;
    acceleration_render_.translate(position_);
    velocity_render_ = velocity_ * (scale / 10);
    velocity_render_.translate(position_);
}

void Body::Process()
{
    velocity_ += acceleration_;
    position_ += velocity_;
    //std::cout << "v=" << *this << " t0=" << translation_p0_ << " t1=" << translation_p1_ << std::endl;
}

double Body::Distance(Body *body)
{
    return position_.Distance(body->position_);
}

void Body::Merge(Body *body)
{
    /* Momentum formula: p = m.v; p = p1 + p2; */
    Vector2d p = (velocity_ * (double)mass_) + (body->velocity_ * (double)body->mass_);
    mass_ += body->mass_;
    velocity_ = p / (double)mass_;
    UpdateRadius();
}

bool Body::IsInside(Body *body)
{
    /* (p.x - circle.x)^2 + (p.y - circle.y)^2 < circle.radius^2 */
    double dx = (body->position_.get_x() - position_.get_x());
    double dy = (body->position_.get_y() - position_.get_y());
    return (dx * dx) + (dy * dy) < radius_ * radius_;
}

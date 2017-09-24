#include "vector2d.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>

Vector2d::Vector2d()
    : Point2d(1, 0), translation_p0_(0, 0), translation_p1_(0, 0)
{
}

Vector2d::Vector2d(const Point2d &point) : Point2d(point)
{
}

void Vector2d::set(double x, double y)
{
    Point2d::set(x, y);
}

void Vector2d::translate(const Point2d &translation)
{
    translation_p0_ = translation;
    translation_p1_ = Point2d(*this + translation);
}

void Vector2d::Render()
{
    glBegin(GL_LINES);
    glVertex2f(translation_p0_.get_x(), translation_p0_.get_y());
    glVertex2f(translation_p1_.get_x(), translation_p1_.get_y());
    glEnd();
}

Vector2d &Vector2d::operator*=(const double s)
{
    Point2d::operator*=(s);
    return *this;
}

Vector2d operator*(Vector2d lhs, const double s)
{
    lhs *= s;
    return lhs;
}

Vector2d &Vector2d::operator/=(const double s)
{
    Point2d::operator/=(s);
    return *this;
}

Vector2d operator/(Vector2d lhs, const double s)
{
    lhs /= s;
    return lhs;
}

double Vector2d::dot(const Vector2d &v)
{
    return get_x() * v.get_x() + get_y() * v.get_y();
}

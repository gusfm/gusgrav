#include <cmath>
#include <GL/gl.h>
#include <iostream>
#include "vector2d.h"

Vector2d::Vector2d() : Point2d(1, 0)
{

}

Vector2d::Vector2d(const Point2d &point) : Point2d(point)
{

}

void Vector2d::set(double x, double y)
{
    Point2d::set(x, y);
}

void Vector2d::Render(Point2d translation)
{
    Point2d p = Point2d(*this + translation);
    std::cout << "a=" << *this << " t=" << p << std::endl;
    glBegin(GL_LINES);
    glVertex2f(translation.get_x(), translation.get_y());
    glVertex2f(p.get_x() * 2, p.get_y() * 2);
    glEnd();
}

void Vector2d::rotate(double rad)
{
#if 0
    double sinTmp, cosTmp, dirX, dirY;

    sinTmp = sin(rad);
    cosTmp = cos(rad);

    dirX = direction_.get_x();
    dirY = direction_.get_y();

    direction_.set_x(dirX * cosTmp - dirY * sinTmp);
    direction_.set_y(dirX * sinTmp + dirY * cosTmp);
#endif
}

#if 0
Vector2d& Vector2d::operator+=(const Vector2d& v)
{
    (Point2d)this += (Point2d)v;
    return *this;
}

Vector2d operator+(Vector2d v1, const Vector2d& v2)
{
    v1 += v2;
    return v1;
}
#endif

Vector2d& Vector2d::operator*=(const double s)
{
    Point2d::operator*=(s);
    return *this;
}

Vector2d operator*(Vector2d lhs, const double s)
{
    lhs *= s;
    return lhs;
}

double Vector2d::dot(const Vector2d &v)
{
    return get_x() * v.get_x() + get_y() * v.get_y();
}

#include <cmath>
#include "point2d.h"

Point2D::Point2D(double x, double y) :x(x), y(y)
{

}

double Point2D::getX()
{
    return x;
}

void Point2D::setX(double x)
{
    this->x = x;
}

double Point2D::getY()
{
    return y;
}

void Point2D::setY(double y)
{
    this->y = y;
}

double Point2D::distance(Point2D& c)
{
    double xdiff, ydiff, x2, y2;

    xdiff = x - c.x;
    ydiff = y - c.y;

    x2 = (xdiff * xdiff);
    y2 = (ydiff * ydiff);

    return sqrt(x2 + y2);
}

void Point2D::render()
{
    // TODO
}

Point2D& Point2D::operator+=(const Point2D& point)
{
    x += point.x;
    y += point.y;
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& point)
{
    x -= point.x;
    y -= point.y;
    return *this;
}

Point2D operator+(Point2D lhs, const Point2D& rhs)
{
    lhs += rhs;
    return lhs;
}

Point2D operator-(Point2D lhs, const Point2D& rhs)
{
    lhs -= rhs;
    return lhs;
}

bool operator==(Point2D& lhs, Point2D& rhs)
{
    return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY());
}

std::ostream& operator<<(std::ostream& os, Point2D& point)
{
    os << "(" << point.getX() << ", " << point.getY() << ")";
    return os;
}

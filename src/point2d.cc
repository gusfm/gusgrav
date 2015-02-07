#include <cmath>
#include "point2d.h"

Point2D::Point2D(double x, double y) : x_(x), y_(y)
{

}

Point2D::Point2D() : x_(0), y_(0)
{

}

double Point2D::get_x() const
{
    return x_;
}

void Point2D::set_x(double x)
{
    this->x_ = x;
}

double Point2D::get_y() const
{
    return y_;
}

void Point2D::set_y(double y)
{
    this->y_ = y;
}

double Point2D::Distance(Point2D& c)
{
    double xdiff, ydiff, x2, y2;

    xdiff = x_ - c.x_;
    ydiff = y_ - c.y_;

    x2 = (xdiff * xdiff);
    y2 = (ydiff * ydiff);

    return sqrt(x2 + y2);
}

void Point2D::Render()
{
    // TODO
}

Point2D& Point2D::operator+=(const Point2D& point)
{
    x_ += point.x_;
    y_ += point.y_;
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& point)
{
    x_ -= point.x_;
    y_ -= point.y_;
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
    return (lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y());
}

std::ostream& operator<<(std::ostream& os, Point2D& point)
{
    os << "(" << point.get_x() << ", " << point.get_y() << ")";
    return os;
}

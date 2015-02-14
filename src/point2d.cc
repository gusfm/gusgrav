#include <cmath>
#include "point2d.h"

Point2d::Point2d(double x, double y) : x_(x), y_(y)
{

}

Point2d::Point2d() : x_(0), y_(0)
{

}

void Point2d::set(double x, double y)
{
    x_ = x;
    y_ = y;
}

double Point2d::get_x() const
{
    return x_;
}

void Point2d::set_x(double x)
{
    this->x_ = x;
}

double Point2d::get_y() const
{
    return y_;
}

void Point2d::set_y(double y)
{
    this->y_ = y;
}

double Point2d::Distance(Point2d& c)
{
    double xdiff, ydiff, x2, y2;

    xdiff = x_ - c.x_;
    ydiff = y_ - c.y_;

    x2 = (xdiff * xdiff);
    y2 = (ydiff * ydiff);

    return sqrt(x2 + y2);
}

void Point2d::Render()
{
    // TODO
}

Point2d& Point2d::operator*=(const double s)
{
    x_ *= s;
    y_ *= s;
    return *this;
}

Point2d& Point2d::operator/=(const double s)
{
    x_ /= s;
    y_ /= s;
    return *this;
}

Point2d operator*(Point2d lhs, const double s)
{
    lhs *= s;
    return lhs;
}

Point2d operator/(Point2d lhs, const double s)
{
    lhs /= s;
    return lhs;
}

Point2d& Point2d::operator+=(const Point2d& point)
{
    x_ += point.x_;
    y_ += point.y_;
    return *this;
}

Point2d& Point2d::operator-=(const Point2d& point)
{
    x_ -= point.x_;
    y_ -= point.y_;
    return *this;
}

Point2d operator+(Point2d lhs, const Point2d& rhs)
{
    lhs += rhs;
    return lhs;
}

Point2d operator-(Point2d lhs, const Point2d& rhs)
{
    lhs -= rhs;
    return lhs;
}

bool operator==(Point2d& lhs, Point2d& rhs)
{
    return (lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y());
}

std::ostream& operator<<(std::ostream& os, const Point2d& point)
{
    os << "(" << point.get_x() << ", " << point.get_y() << ")";
    return os;
}

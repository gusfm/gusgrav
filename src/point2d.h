#ifndef GUSGRAV_SRC_POINT2D_H_
#define GUSGRAV_SRC_POINT2D_H_

#include <iostream>

class Point2d {
   private:
    double x_;
    double y_;

   public:
    Point2d();
    Point2d(double x, double y);
    void set(double x, double y);
    double get_x() const;
    void set_x(double x);
    double get_y() const;
    void set_y(double y);
    double Distance(Point2d& c);
    void Render();
    Point2d& operator+=(const Point2d& point);
    Point2d& operator-=(const Point2d& point);
    Point2d& operator*=(const double s);
    Point2d& operator/=(const double s);
};

Point2d operator+(Point2d lhs, const Point2d& rhs);
Point2d operator-(Point2d lhs, const Point2d& rhs);
Point2d operator*(Point2d lhs, const double s);
Point2d operator/(Point2d lhs, const double s);
bool operator==(const Point2d& lhs, const Point2d& rhs);
std::ostream& operator<<(std::ostream& os, const Point2d& point);

#endif /* GUSGRAV_SRC_POINT2D_H_ */

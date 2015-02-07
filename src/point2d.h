#ifndef GUSGRAV_SRC_POINT2D_H_
#define GUSGRAV_SRC_POINT2D_H_

#include <iostream>

class Point2D {
    private:
        double x_;
        double y_;

    public:
        Point2D();
        Point2D(double x, double y);
        double get_x() const;
        void set_x(double x);
        double get_y() const;
        void set_y(double y);
        double Distance(Point2D& c);
        void Render();
        Point2D& operator+=(const Point2D& point);
        Point2D& operator-=(const Point2D& point);
};

Point2D operator+(Point2D lhs, const Point2D& rhs);
Point2D operator-(Point2D lhs, const Point2D& rhs);
bool operator==(const Point2D& lhs, const Point2D& rhs);
std::ostream& operator<<(std::ostream& os, const Point2D& point);

#endif /* GUSGRAV_SRC_POINT2D_H_ */

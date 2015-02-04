#ifndef GUSGRAV_SRC_POINT2D_H_
#define GUSGRAV_SRC_POINT2D_H_

#include <iostream>

class Point2D {
    private:
        double x;
        double y;

    public:
        Point2D(double x, double y);
        double getX();
        void setX(double x);
        double getY();
        void setY(double y);
        double distance(Point2D& c);
        void render();
        Point2D& operator+=(const Point2D& point);
        Point2D& operator-=(const Point2D& point);
};

Point2D operator+(Point2D lhs, const Point2D& rhs);
Point2D operator-(Point2D lhs, const Point2D& rhs);
bool operator==(const Point2D& lhs, const Point2D& rhs);
std::ostream& operator<<(std::ostream& os, const Point2D& point);

#endif /* GUSGRAV_SRC_POINT2D_H_ */

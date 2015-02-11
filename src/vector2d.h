#ifndef GUSGRAV_SRC_VECTOR2D_H_
#define GUSGRAV_SRC_VECTOR2D_H_

#include "point2d.h"

class Vector2d : public Point2d {
   public:
    Vector2d();
    Vector2d(const Point2d &point);
    void set(double x, double y);
    void Render(Point2d translation);
    void rotate(double rad);
    double dot(const Vector2d &v);
    Vector2d& operator*=(const double s);
};

Vector2d operator*(Vector2d lhs, const double s);

#endif /* GUSGRAV_SRC_VECTOR2D_H_ */

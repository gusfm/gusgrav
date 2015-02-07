#ifndef GUSGRAV_SRC_VECTOR2D_H_
#define GUSGRAV_SRC_VECTOR2D_H_

#include "point2d.h"

class Vector2D {
   public:
    Vector2D();
    Vector2D(double x, double y);
    void rotate(double rad);
   private:
    Point2D direction_;
};

#endif /* GUSGRAV_SRC_VECTOR2D_H_ */

#ifndef GUSGRAV_SRC_VECTOR2D_H_
#define GUSGRAV_SRC_VECTOR2D_H_

#include "point2d.h"

class Vector2D {
    private:
        Point2D direction;
    public:
        Vector2D(double x, double y);
        void rotate(double rad);
};

#endif /* GUSGRAV_SRC_VECTOR2D_H_ */

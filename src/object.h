#ifndef GUSGRAV_SRC_OBJECT_H_
#define GUSGRAV_SRC_OBJECT_H_

#include "point2d.h"
#include "vector2d.h"

class Object {
   public:
    Object(const Point2D &position, const Vector2D &velocity, unsigned int mass);
    ~Object();
    void Render();
   private:
    Point2D position_;
    Vector2D velocity_;
    unsigned int mass_;
};

#endif /* GUSGRAV_SRC_OBJECT_H_ */

#ifndef GUSGRAV_SRC_OBJECT_H_
#define GUSGRAV_SRC_OBJECT_H_

#include "point2d.h"
#include "vector2d.h"

class Body {
   public:
    Body(const Point2d &position, const Vector2d &velocity, unsigned int mass);
    ~Body();
    void Render();
    unsigned int get_mass() const;
    const Point2d &get_velocity();
    void CalculateAcceleration(const Body *j);
    void ClearAcceleration();
   protected:
    Point2d position_;
    Vector2d velocity_;
    Vector2d acceleration_;
    unsigned int mass_;
};

#endif /* GUSGRAV_SRC_OBJECT_H_ */
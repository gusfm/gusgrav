#ifndef GUSGRAV_SRC_PARTICLE_H_
#define GUSGRAV_SRC_PARTICLE_H_

#include "point2d.h"
#include "object.h"

class Particle : public Object {
   public:
    Particle(const Point2D &position, const Vector2D &velocity, unsigned int mass);
    ~Particle();
};

#endif /* GUSGRAV_SRC_PARTICLE_H_ */

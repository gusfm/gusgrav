#include "particle.h"

Particle::Particle(const Point2D &position, const Vector2D &velocity, unsigned int mass) :
    Object(position, velocity, mass)
{
}

Particle::~Particle()
{
}

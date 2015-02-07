#include <GL/gl.h>
#include "universe.h"

void Universe::CreateRandomParticlesSameMass(int number)
{
    for (int i = 0; i < number; ++i) {
        const Point2D pos(i * 20 + 300, 300);
        const Vector2D vel(1, 0);
        particle_list_.push_back(new Particle(pos, vel, 1U));
    }
}

Universe::Universe()
{
    CreateRandomParticlesSameMass(10);
}

Universe::~Universe()
{
}

void Universe::Render()
{
    std::list<Particle *>::const_iterator iter;
    glColor3f(1.0, 0.0, 0.0);
    for(iter = particle_list_.begin(); iter != particle_list_.end(); iter++) {
        (*iter)->Render();
    }
}

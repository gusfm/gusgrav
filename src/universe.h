#ifndef GUSGRAV_SRC_UNIVERSE_H_
#define GUSGRAV_SRC_UNIVERSE_H_

#include <list>
#include "particle.h"

class Universe {
   public:
    Universe();
    ~Universe();
    void Render();
   private:
    void CreateRandomParticlesSameMass(int number);
    std::list<Particle *> particle_list_;
};


#endif /* GUSGRAV_SRC_UNIVERSE_H_ */

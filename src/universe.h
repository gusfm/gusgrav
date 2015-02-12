#ifndef GUSGRAV_SRC_UNIVERSE_H_
#define GUSGRAV_SRC_UNIVERSE_H_

#include <list>
#include "body.h"

class Universe {
   public:
    Universe();
    ~Universe();
    void Render();
    void Process();
    void toggle_render_acceleration();
   private:
    void CreateRandomBodiesSameMass(int number);
    void CalculateBodyAcceleration(Body *body);
    void CalculateNBodyAcceleration();
    std::list<Body *> body_list_;
    bool render_acceleration_;
};


#endif /* GUSGRAV_SRC_UNIVERSE_H_ */

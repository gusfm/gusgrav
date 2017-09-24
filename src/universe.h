#ifndef GUSGRAV_SRC_UNIVERSE_H_
#define GUSGRAV_SRC_UNIVERSE_H_

#include <list>
#include "body.h"

class Universe
{
   public:
    Universe(Point2d &size);
    ~Universe();
    void Render();
    void Process();
    void toggle_render_acceleration();
    void toggle_merge_bodies();
    unsigned int get_num_bodies();
    void SelectBodyAtPoint(Point2d &point);
    void CreateBodyAtPosition(Point2d &pos);

   private:
    void CreateRandomBodies(int number);
    void CalculateBodyAcceleration(Body *body);
    void CalculateNBodyAcceleration();
    void CheckCloseBodies(Body *body);
    void CheckCloseBodiesAll();
    Point2d size_;
    bool render_info_;
    bool merge_bodies_;
    std::list<Body *> body_list_;
};

#endif /* GUSGRAV_SRC_UNIVERSE_H_ */

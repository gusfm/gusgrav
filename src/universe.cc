#include <GL/gl.h>
#include "universe.h"

void Universe::CreateRandomBodies(int number)
{
    srand(time(NULL));
    for (int i = 0; i < number; ++i) {
        const Point2d pos(rand() % (int)size_.get_x(), rand() % (int)size_.get_y());
        const Vector2d vel(Point2d(0, 0));
        body_list_.push_back(new Body(pos, vel, 1 + (rand() % 10)));
    }
}

Universe::Universe(Point2d &size) : size_(size), render_info_(false), merge_bodies_(false)
{
    CreateRandomBodies(1000);
}

Universe::~Universe()
{
}

void Universe::toggle_render_acceleration()
{
    render_info_ = !render_info_;
}

void Universe::toggle_merge_bodies()
{
    merge_bodies_ = !merge_bodies_;
}

void Universe::Render()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        glColor3f(1.0, 1.0, 1.0);
        (*iter)->Render();
        if (render_info_) {
            (*iter)->RenderInfo();
        }
    }

}

void Universe::CalculateBodyAcceleration(Body *body)
{
    std::list<Body *>::const_iterator iter;
    body->ClearAcceleration();
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        if (body != *iter)
            body->CalculateAcceleration(*iter);
    }
    /* First update the position, and than process accel rendering. */
    body->Process();
    if (render_info_)
        body->ProcessInfoRender(300);
}

void Universe::CalculateNBodyAcceleration()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        CalculateBodyAcceleration(*iter);
    }
}

void Universe::CheckCloseBodies(Body *body)
{
    std::list<Body *>::iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        if (*iter != body) {
            if (body->IsInside(*iter)) {
                body->Merge(*iter);
                delete *iter;
                iter = body_list_.erase(iter);
            }
        }
    }
}

void Universe::CheckCloseBodiesAll()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        CheckCloseBodies(*iter);
    }
}

void Universe::Process()
{
    CalculateNBodyAcceleration();
    if (merge_bodies_)
        CheckCloseBodiesAll();
}

unsigned int Universe::get_num_bodies()
{
    return body_list_.size();
}

void Universe::SelectBodyAtPoint(Point2d &point)
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        (*iter)->Select(point);
    }
}

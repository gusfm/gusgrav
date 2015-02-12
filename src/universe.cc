#include <GL/gl.h>
#include "universe.h"

void Universe::CreateRandomBodiesSameMass(int number)
{
    for (int i = 0; i < number; ++i) {
        const Point2d pos(i * 20 + 300, 300);
        const Vector2d vel(Point2d(0, 0));
        body_list_.push_back(new Body(pos, vel, 1U));
    }
    const Point2d pos(200, 500);
    const Vector2d vel(Point2d(0, 0));
    body_list_.push_back(new Body(pos, vel, 100U));
    const Point2d pos2(500, 100);
    body_list_.push_back(new Body(pos2, vel, 100U));
}

Universe::Universe() : render_acceleration_(false)
{
    CreateRandomBodiesSameMass(10);
}

Universe::~Universe()
{
}

void Universe::toggle_render_acceleration()
{
    render_acceleration_ = !render_acceleration_;
}

void Universe::Render()
{
    std::list<Body *>::const_iterator iter;
    glColor3f(1.0, 1.0, 1.0);
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        (*iter)->Render();
        if (render_acceleration_)
            (*iter)->RenderAcceleration();
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
    body->ProcessAcceleration();
    if (render_acceleration_)
        body->ProcessAccelerationRender(10);
}

void Universe::CalculateNBodyAcceleration()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        CalculateBodyAcceleration(*iter);
    }
}

#if 0
void Universe::CheckClose()
{
}

void Universe::MergeCloseBodies()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        CalculateBodyAcceleration(*iter);
    }
}
#endif

void Universe::Process()
{
    CalculateNBodyAcceleration();
}

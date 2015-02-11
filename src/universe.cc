#include <GL/gl.h>
#include "universe.h"

void Universe::CreateRandomBodiesSameMass(int number)
{
    for (int i = 0; i < number; ++i) {
        const Point2d pos(i * 20 + 300, 300);
        const Vector2d vel(Point2d(1, 0));
        body_list_.push_back(new Body(pos, vel, 1U));
    }
}

Universe::Universe()
{
    CreateRandomBodiesSameMass(10);
}

Universe::~Universe()
{
}

void Universe::Render()
{
    std::list<Body *>::const_iterator iter;
    glColor3f(1.0, 0.0, 0.0);
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        (*iter)->Render();
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
}

void Universe::CalculateNBodyAcceleration()
{
    std::list<Body *>::const_iterator iter;
    for (iter = body_list_.begin(); iter != body_list_.end(); iter++) {
        CalculateBodyAcceleration(*iter);
    }
}

void Universe::Process()
{
    CalculateNBodyAcceleration();
}

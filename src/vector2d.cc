#include <cmath>
#include "vector2d.h"

Vector2D::Vector2D() : direction_(1, 0)
{

}

Vector2D::Vector2D(double x, double y) : direction_(x, y)
{

}

void Vector2D::rotate(double rad)
{
    double sinTmp, cosTmp, dirX, dirY;

    sinTmp = sin(rad);
    cosTmp = cos(rad);

    dirX = direction_.get_x();
    dirY = direction_.get_y();

    direction_.set_x(dirX * cosTmp - dirY * sinTmp);
    direction_.set_y(dirX * sinTmp + dirY * cosTmp);
}

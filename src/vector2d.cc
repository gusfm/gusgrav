#include <cmath>
#include "vector2d.h"

Vector2D::Vector2D(double x, double y) :direction(x, y)
{

}

void Vector2D::rotate(double rad)
{
    double sinTmp, cosTmp, dirX, dirY;

    sinTmp = sin(rad);
    cosTmp = cos(rad);

    dirX = direction.getX();
    dirY = direction.getY();

    direction.setX(dirX * cosTmp - dirY * sinTmp);
    direction.setY(dirX * sinTmp + dirY * cosTmp);
}

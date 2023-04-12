#include "roundedrectangle.hh"


RoundedRectangle::RoundedRectangle()
{

}

RoundedRectangle::~RoundedRectangle()
{

}

float RoundedRectangle::getCurvatureParameter() const
{
    return curvatureParameter;
}

void RoundedRectangle::setCurvatureParameter(float newCurvatureParameter)
{
    curvatureParameter = newCurvatureParameter;
}

const QRectF &RoundedRectangle::getRectangle() const
{
    return rectangle;
}

void RoundedRectangle::updateRectParameters(float curve, float sidesRatio)
{
    rectangle.setRect(getPositionX(), getPositionY(), getSize(), getSize()*sidesRatio);
    setCurvatureParameter(curve);
}

void RoundedRectangle::translate(int x, int y)
{
    rectangle.translate(x, y);
}

#include "drawableobject.hh"

DrawableObject::DrawableObject()
{
    positionX = 0;
    positionY = 0;
    rotation = 0;
    size = 0;
}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::updateParameters(float x, float y, float r, float s)
{
    positionX = x;
    positionY = y;
    rotation = r;
    size = s;
}

float DrawableObject::getPositionX() const
{
    return positionX;
}

void DrawableObject::setPositionX(float newPositionX)
{
    positionX = newPositionX;
}

float DrawableObject::getPositionY() const
{
    return positionY;
}

void DrawableObject::setPositionY(float newPositionY)
{
    positionY = newPositionY;
}

float DrawableObject::getRotation() const
{
    return rotation;
}

void DrawableObject::setRotation(float newRotation)
{
    rotation = newRotation;
}

float DrawableObject::getSize() const
{
    return size;
}

void DrawableObject::setSize(float newSize)
{
    size = newSize;
}

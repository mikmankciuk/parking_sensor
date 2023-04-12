#include "image.hh"

Image::Image()
{
    setPositionX(0);
    setPositionY(0);
    setRotation(0);
    setSize(0);
}

Image::Image(QPixmap image)
{
    setPositionX(0);
    setPositionY(0);
    setRotation(0);
    setSize(0);

    setPixmap(image);
}

Image::Image(float x, float y, float r, float s, QPixmap image)
{
    setPositionX(x);
    setPositionY(y);
    setRotation(r);
    setSize(s);

    setPixmap(image);
}

Image::~Image()
{

}

const QPixmap &Image::getPixmap() const
{
    return pixmap;
}

void Image::setPixmap(const QPixmap &newImagePixmap)
{
    pixmap = newImagePixmap;
}


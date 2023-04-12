#include "zone.hh"

Zone::Zone()
{
    setPositionX(0);
    setPositionY(0);
    setRotation(0);
    setSize(0);

    startTop.setX(0);
    startTop.setY(0);

    startBottom.setX(0);
    startBottom.setY(0);

    endTop.setX(0);
    endTop.setY(0);

    endBottom.setX(0);
    endBottom.setY(0);

    transitionTop.setX(0);
    transitionTop.setY(0);

    transitionBottom.setX(0);
    transitionBottom.setY(0);
}

Zone::Zone(float x, float y, float r, float s)
{
    setPositionX(x);
    setPositionY(y);
    setRotation(r);
    setSize(s);

    startTop.setX(0);
    startTop.setY(0);

    startBottom.setX(0);
    startBottom.setY(0);

    endTop.setX(0);
    endTop.setY(0);

    endBottom.setX(0);
    endBottom.setY(0);

    transitionTop.setX(0);
    transitionTop.setY(0);

    transitionBottom.setX(0);
    transitionBottom.setY(0);
}

Zone::~Zone()
{

}

QPoint Zone::getStartTop() const
{
    return startTop;
}

void Zone::setStartTop(QPoint newStartTop)
{
    startTop = newStartTop;
}

QPoint Zone::getStartBottom() const
{
    return startBottom;
}

void Zone::setStartBottom(QPoint newStartBottom)
{
    startBottom = newStartBottom;
}

QPoint Zone::getEndTop() const
{
    return endTop;
}

void Zone::setEndTop(QPoint newEndTop)
{
    endTop = newEndTop;
}

QPoint Zone::getEndBottom() const
{
    return endBottom;
}

void Zone::setEndBottom(QPoint newEndBottom)
{
    endBottom = newEndBottom;
}

QPoint Zone::getTransitionTop() const
{
    return transitionTop;
}

void Zone::setTransitionTop(QPoint newTransitionTop)
{
    transitionTop = newTransitionTop;
}

QPoint Zone::getTransitionBottom() const
{
    return transitionBottom;
}

void Zone::setTransitionBottom(QPoint newTransitionBottom)
{
    transitionBottom = newTransitionBottom;
}

void Zone::updatePoints()
{
    if(getRotation() > 0)
    {
        startTop.setX(getPositionX());
        startTop.setY(getPositionY());

        startBottom.setX(getPositionX());
        startBottom.setY(getPositionY() + 100);

        endTop.setX(getPositionX() + 75 + 3*getSize());
        endTop.setY(getPositionY() + getRotation()/2);

        endBottom.setX(getPositionX() + 75 + 3*getSize() - 2*getRotation()/5);
        endBottom.setY(getPositionY() + 100 + 2*getRotation()/5);

        transitionTop.setX(getPositionX() + 50 + 3*getSize()/2);
        transitionTop.setY(getPositionY());

        transitionBottom.setX(getPositionX() + 50 + 3*getSize()/2 - getRotation()/4);
        transitionBottom.setY(getPositionY() + 100);
    }
    else
    {
        startTop.setX(getPositionX());
        startTop.setY(getPositionY());

        startBottom.setX(getPositionX());
        startBottom.setY(getPositionY() + 100);

        endTop.setX(getPositionX() + 75 + 3*getSize() + 2*getRotation()/5);
        endTop.setY(getPositionY() + 2*getRotation()/5);

        endBottom.setX(getPositionX() + 75 + 3*getSize());
        endBottom.setY(getPositionY() + 100 + getRotation()/2);

        transitionTop.setX(getPositionX() + 50 + 3*getSize()/2 + 2*getRotation()/5);
        transitionTop.setY(getPositionY());

        transitionBottom.setX(getPositionX() + 50 + 3*getSize()/2);
        transitionBottom.setY(getPositionY() + 100);
    }
}

void Zone::updateColor(int value)
{
    if(value < 100)
    {   //  red -> yellow
        zoneColor.setRed(200 + 0.4 * value);
        zoneColor.setGreen(0 + 2.3 * value);
        zoneColor.setBlue(0 + 0.5 * value);
    }
    else
    {   //  yellow -> green
        zoneColor.setRed(std::max(240 - 1.9 * (value - 100),0.0));
        zoneColor.setGreen(200 - 0.3 * (value - 100));
        zoneColor.setBlue(0 + 0.5 * (value - 100));
    }
}

const QColor &Zone::getZoneColor() const
{
    return zoneColor;
}

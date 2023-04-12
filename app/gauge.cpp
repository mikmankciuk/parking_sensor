#include "gauge.hh"

Gauge::Gauge()
{
    setPositionX(0);
    setPositionY(0);
    setRotation(0);
    setSize(0);

    gaugeTop.setX(0);
    gaugeTop.setY(0);

    gaugeLeft.setX(0);
    gaugeLeft.setY(0);

    gaugeRight.setX(0);
    gaugeRight.setY(0);

    gaugeBottom.setX(0);
    gaugeBottom.setY(0);

    gaugeCenter.setX(0);
    gaugeCenter.setY(0);

    gaugeCenter.setX(0);
    gaugeCenter.setY(0);
}

Gauge::Gauge(float x, float y, float r, float s)
{
    setPositionX(x);
    setPositionY(y);
    setRotation(r);
    setSize(s);

    gaugeTop.setX(0);
    gaugeTop.setY(-s);

    gaugeLeft.setX(-s/6);
    gaugeLeft.setY(0);

    gaugeRight.setX(s/6);
    gaugeRight.setY(0);

    gaugeBottom.setX(0);
    gaugeBottom.setY(s/3);

    gaugeCenter.setX(0);
    gaugeCenter.setY(0);
}

Gauge::~Gauge()
{

}

QPointF Gauge::getGaugeTop() const
{
    return gaugeTop;
}

void Gauge::setGaugeTop(QPointF newGaugeTop)
{
    gaugeTop = newGaugeTop;
}

QPointF Gauge::getGaugeLeft() const
{
    return gaugeLeft;
}

void Gauge::setGaugeLeft(QPointF newGaugeLeft)
{
    gaugeLeft = newGaugeLeft;
}

QPointF Gauge::getGaugeRight() const
{
    return gaugeRight;
}

void Gauge::setGaugeRight(QPointF newGaugeRight)
{
    gaugeRight = newGaugeRight;
}

QPointF Gauge::getGaugeBottom() const
{
    return gaugeBottom;
}

void Gauge::setGaugeBottom(QPointF newGaugeBottom)
{
    gaugeBottom = newGaugeBottom;
}

QPointF Gauge::getGaugeCenter() const
{
    return gaugeCenter;
}

void Gauge::setGaugeCenter(QPointF newGaugeCenter)
{
    gaugeCenter = newGaugeCenter;
}

void Gauge::updatePoints()
{
    gaugeTop.setX(0);
    gaugeTop.setY(-getSize());

    gaugeLeft.setX(-getSize()/6);
    gaugeLeft.setY(0);

    gaugeRight.setX(getSize()/6);
    gaugeRight.setY(0);

    gaugeBottom.setX(0);
    gaugeBottom.setY(getSize()/3);
}

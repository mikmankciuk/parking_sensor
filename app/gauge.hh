/// \file
/// \brief gauge.h

#ifndef GAUGE_H
#define GAUGE_H

#include <QPointF>
#include <QPolygon>
#include <QPainterPath>
#include "drawableobject.hh"


//! \brief Class containing basic information about gauge required for it to be drawn. Reffering to a point as uppermost is used to describe uppermost point when rotation of the gauge is equal to 0. Same applies to other directions.
class Gauge : public DrawableObject
{
public:
    /*! Default constructor */
    Gauge();

    //! Constructor allowing creation of gauge with predefined parameters.
    /*!
      \param[in] x - float type argument representing position of the center of the gauge in X axis
      \param[in] y - float type argument representing position of the center of the gauge in Y axis
      \param[in] r - float type argument representing rotation of the gauge around Z axis
      \param[in] s - float type argument representing size of the gauge
    */
    Gauge(float x, float y, float r, float s);

    /*! Default destructor */
    ~Gauge();

    //! Return position of the uppermost point of the gauge.
    /*! \retval gaugeTop - coordinates of the uppermost point of the gauge
     */
    QPointF getGaugeTop() const;

    //! Pass point coordinates as new coordiantes of the uppermost point of the gauge.
    /*!
      \param[in] newGaugeTop - QPointF class variable passed as new uppermost point coordinates
    */
    void setGaugeTop(QPointF newGaugeTop);


    //! Return position of leftmost point of the gauge.
    /*! \retval gaugeLeft - coordinates of the leftmost point of the gauge
     */
    QPointF getGaugeLeft() const;

    //! Pass point coordinates as new coordiantes of the leftmost point of the gauge.
    /*!
      \param newGaugeLeft - QPointF class variable passed as new leftmost point coordinates
    */
    void setGaugeLeft(QPointF newGaugeLeft);


    //! Return position of the rightmost point of the gauge.
    /*! \retval gaugeRight - coordinates of the rightmost point of the gauge
     */
    QPointF getGaugeRight() const;

    //! Pass point coordinates as new coordiantes of the rightmost point of the gauge.
    /*!
      \param[in] newGaugeRight - QPointF class variable passed as new rightmost point coordinates
    */
    void setGaugeRight(QPointF newGaugeRight);


    //! Return position of the bottommost point of the gauge.
    /*! \retval gaugeBottom - coordinates of the bottommost point of the gauge.
     */
    QPointF getGaugeBottom() const;

    //! Pass point coordinates as new coordiantes of the bottommost point of the gauge.
    /*!
      \param[in] newGaugeBottom - QPointF class variable passed as new bottommost point coordinates
    */
    void setGaugeBottom(QPointF newGaugeBottom);


    //! Return position of the center of the gauge.
    /*! \retval gaugeCenter - coordinates of the central point of the gauge
     */
    QPointF getGaugeCenter() const;

    //! Pass point coordinates as new coordiantes of the center of the gauge.
    /*!
      \param[in] newGaugeCenter - QPointF class variable passed as new central point coordinates
    */
    void setGaugeCenter(QPointF newGaugeCenter);


    //! Calculate gauges points positions based on its position in X and Y axis and its size.
    void updatePoints();


private:
    //! QPointF class variable representing uppermost point of the gauge.
    QPointF gaugeTop;
    //! QPointF class variable representing leftmost point of the gauge.
    QPointF gaugeLeft;
    //! QPointF class variable representing rightmost point of the gauge.
    QPointF gaugeRight;
    //!QPointF class variable representing bottommost point of the gauge.
    QPointF gaugeBottom;
    //! QPointF class variable representing center of the gauge.
    QPointF gaugeCenter;
};

#endif // GAUGE_H

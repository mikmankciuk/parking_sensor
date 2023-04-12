/// \file
/// \brief zone.h
#ifndef ZONE_HH
#define ZONE_HH

#include <QPoint>
#include <QPainterPath>
#include <QColor>
#include "drawableobject.hh"
#include <algorithm>

//! \brief Class containing basic information about zone required for it to be drawn.
class Zone : public DrawableObject
{
public:
    /*! Default constructor */
    Zone();
    //! Constructor allowing creation of zone with predefined parameters.
    /*!
      \param[in] x - float type argument representing position of the zone in X axis
      \param[in] y - float type argument representing position of the zone in Y axis
      \param[in] r - float type argument representing rotation of the zone around Z axis
      \param[in] s - float type argument representing size of the zone
    */
    Zone(float x, float y, float r, float s);

    /*! Default destructor */
    ~Zone();

    //! Return point representing upper located point attached to the car.
    /*! \retval startTop - coordinates of the upper located point attached to the car
     */
    QPoint getStartTop() const;

    //! Pass point coordinates as new coordiantes for the upper located point attached to the car.
    /*!
      \param newStartTop - QPoint class variable passed as new upper located point attached to the car coordinates
      
    */
    void setStartTop(QPoint newStartTop);

    //! Return point representing lower located point attached to the car.
    /*! \retval startBottom - coordinates of the lower located point attached to the car
     */
    QPoint getStartBottom() const;

    //! Pass point coordinates as new coordiantes for the lower located point attached to the car.
    /*!
      \param newStartBottom - QPoint class variable passed as new lower located point attached to the car coordinates
      
    */
    void setStartBottom(QPoint newStartBottom);

    //! Return point representing upper located point at the end of the zone.
    /*! \retval startTop - coordinates of the upper located point at the end of the zone
     */
    QPoint getEndTop() const;

    //! Pass point coordinates as new coordiantes for the upper located point at the end of the zone.
    /*!
      \param newStartTop - QPoint class variable passed as new upper located point at the end of the zone coordinates
      
    */
    void setEndTop(QPoint newEndTop);


    //! Return point representing lower located point at the end of the zone.
    /*! \retval startTop - coordinates of the lower located point at the end of the zone
     */
    QPoint getEndBottom() const;

    //! Pass point coordinates as new coordiantes for the lower located point at the end of the zone.
    /*!
      \param newStartTop - QPoint class variable passed as new lower located point at the end of the zone coordinates
      
    */
    void setEndBottom(QPoint newEndBottom);

    //! Return point responsible for upper curve of the zone.
    /*! \retval startTop - coordinates of the point responsible for upper curve of the zone
     */
    QPoint getTransitionTop() const;

    //! Pass point coordinates as new coordiantes for the point responsible for upper curve of the zone.
    /*!
      \param newStartTop - QPoint class variable passed as new point responsible for upper curve of the zone
      
    */
    void setTransitionTop(QPoint newTransitionTop);

     //! Return point responsible for lower curve of the zone.
    /*! \retval startTop - coordinates of the point responsible for lower curve of the zone
     */
    QPoint getTransitionBottom() const;

    //! Pass point coordinates as new coordiantes for the point responsible for lower curve of the zone.
    /*!
      \param newStartTop - QPoint class variable passed as new point responsible for lower curve of the zone
      
    */
    void setTransitionBottom(QPoint newTransitionBottom);

    //! Return value of the color of the zone filling.
    /*! \retval  zoneColor - current color of the zone filling.
     */
    const QColor &getZoneColor() const;

    //! Update points used to draw zone based on its current parameter values.
    void updatePoints();

    //! Update color of the Zone based on given value.
    /*! \param[in] value - variable used to calculate transition of zones color from red (at 0) to green (at 200), when equal to 400 it will result in blue color
     */
    void updateColor(int value);

private:
    //! QPoint class variable representing upper located point attached to the car.
    QPoint startTop;
    //! QPoint class variable representing lower located point attached to the car.
    QPoint startBottom;
    //! QPoint class variable representing upper located point at the end of the zone.
    QPoint endTop;
    //! QPoint class variable representing lower located point at the end of the zone.
    QPoint endBottom;
    //! QPoint class variable representing point responsible for upper curve of the zone.
    QPoint transitionTop;
    //! QPoint class variable representing point responsible for lower curve of the zone.
    QPoint transitionBottom;
    //! QColor class variable representing the color of the zone.
    QColor zoneColor;
};

#endif // ZONE_HH

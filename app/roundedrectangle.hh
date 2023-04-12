/// \file
/// \brief roundedrectangle.h

#ifndef ROUNDEDRECTANGLE_HH
#define ROUNDEDRECTANGLE_HH

#include <QRectF>
#include "drawableobject.hh"

//!  Class containing basic information about rounded rectangle.
class RoundedRectangle : public DrawableObject
{
public:
    /*! Default constructor */
    RoundedRectangle();
    /*! Default destructor */
    ~RoundedRectangle();

    //! Return the curvature parameter of the rounded rectangle.
    /*!
      \retval curvatureParameter - radius of curve at the edge of rounded rectangle
    */
    float getCurvatureParameter() const;

    //! Set new curvature parameter for the rounded rectangle.
    /*!
      \param[in] newCurvatureParameter - float type variable representing radius of curve at the edge of rounded rectangle
    */
    void setCurvatureParameter(float newCurvatureParameter);

    //! Return the rectangle on which rounded rectangle is based.
    /*!
      \retval rectangle - variable used as base to draw a rounded rectangle
    */
    const QRectF &getRectangle() const;

    //! Update parameters based on current positions in X and Y axis, given new curvature parameter and ratio between sides of rectangle.
    /*!
      \param[in] curve - float value of curvature parameter
      \param[in] sidesRatio - float ratio between sides of rectangle
    */
    void updateRectParameters(float curve, float sidesRatio);

    //! Translate rectangle in X and Y axis by x and y.
    /*!
      \param[in] x - int value by which X coordinate is increased
      \param[in] y - int value by which Y coordinate is increased
    */
    void translate(int x, int y);

private:
    //! QRectf class variable used as base to draw a rounded rectangle.
    QRectF rectangle;
    //! Float type variable representing radius of curve at the edge of rounded rectangle.
    float curvatureParameter;

};

#endif // ROUNDEDRECTANGLE_HH

/// \file
/// \brief drawablebject.h
#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

//! \brief Class containing basic information about object that can be drawn.
class DrawableObject
{
public:
    /*! Default constructor */
    DrawableObject();
    /*! Default destructor */
    ~DrawableObject();


    //! Updating parameters of the object.
    /*!
      \param[in] x - float type argument representing position of the object in X axis
      \param[in] y - float type argument representing position of the object in Y axis
      \param[in] r - float type argument representing rotation of the object around Z axis
      \param[in] s - float type argument representing size of the object
    */
    void updateParameters(float x, float y, float r, float s);

    //! Return position of the object in X axis.
    /*!
      \retval positionX - position of the object in X axis
    */
    float getPositionX() const;

    //! Set new postion in X axis for the object.
    /*!
      \param[in] newPositionX - float type argument representing desired position of the object in X axis.
    */
    void setPositionX(float newPositionX);

    //! Return position of the object in Y axis.
    /*!
      \retval positionY - position of the object in Y axis
    */
    float getPositionY() const;

    //! Set new postion in Y axis for the object.
    /*!
      \param[in] newPositionX - float type argument representing desired position of the object in Y axis.
    */
    void setPositionY(float newPositionY);

    //! Return current rotation angle of the object around Z axis.
    /*!
      \retval rotation - current rotation angle of the object
    */
    float getRotation() const;

    //! Set new rotation angle for the object.
    /*!
      \param[in] newRotation - float type argument representing desired angle of rotation of the object around Z axis.
    */
    void setRotation(float newRotation);

    //! Return current size of the object.
    /*!
      \retval size - current size of the object
    */
    float getSize() const;

    //! Set new size for the object.
    /*!
      \param[in] newSize - float type argument representing desired size of the object.
    */
    void setSize(float newSize);

private:
    //! Float type variable representing position of the object in X axis.
    float positionX;

    //! Float type variable representing position of the object in Y axis.
    float positionY;

    //! Float type variable representing angle of rotation of the object around Z axis.
    float rotation;

    //! Float type variable representing size of the object.
    float size;
};

#endif // DRAWABLEOBJECT_H

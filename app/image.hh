/// \file
/// \brief image.h

#ifndef IMAGE_HH
#define IMAGE_HH

#include <QPixmap>
#include "drawableobject.hh"
//#include <QWidget>

//! \brief Class used to store iamges.
class Image : public DrawableObject
{
public:
    /*! Default constructor*/
    Image();

   //! Constructor allowing creation of image with predefined pixmap storing its image to display.
    /*!
      \param[in] image - QPixmap image stored to be displayed
    */
    Image(QPixmap image);


    //! Constructor allowing creation of image with predefined pixmap and parameters
    /*!
       \param[in] x - float type argument representing position of the center of the gauge in X axis
      \param[in] y - float type argument representing position of the center of the gauge in Y axis
      \param[in] r - float type argument representing rotation of the gauge around Z axis
      \param[in] s - float type argument representing size of the gauge
      \param[in] image - QPixmap image stored to be displayed
    */
    Image(float x, float y, float rot, float size, QPixmap image);

    /*! Default destructor */
    ~Image();

    //! Return stored image as a pixmap.
    /*!
      \retval pixmap - currant image stored as a pixmap
    */
    const QPixmap &getPixmap() const;

    //! Set new image to be stored in a pixmap
    /*!
      \param[im] newImagePixmap - const QPixmap class variable used to store an image
    */
    void setPixmap(const QPixmap &newImagePixmap);

private:
    //! QPixmap type variable used to store an image.
    QPixmap pixmap;

};

#endif // IMAGE_HH

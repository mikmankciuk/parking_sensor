/// \file
/// \brief mainwindow.h

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtCore/QTimer>
#include <QtCore/QElapsedTimer>
#include <QtCore/QDebug>

#include <QColor>
#include <QPainter>
#include <QPen>
#include "image.hh"
#include "gauge.hh"
#include "zone.hh"
#include "roundedrectangle.hh"

#include <QDialog>
#include <QSerialPort>
#include <time.h>
#include <math.h>
#include <iostream>
#include <QString>
#include <QTranslator>


/** 
 * \brief Structure to read data from the serial port.
 */
typedef struct sensorData
{
   /**
    * \param Sign - char type variable used for recognizing packages.
    * \param Get1 - float type variable used for reading first value from data package.
    * \param Get2 - float type variable used for reading second value from data package.
    * \param Get3 - float type variable used for reading third value from data package.
    * \param Dist1 - float type variable used for storing value optained from first distance sensor.
    * \param Dist2 - float type variable used for storing value optained from secod distance sensor.
    * \param Dist3 - float type variable used for storing value optained from third distance sensor.
    * \param SpeedX - float type variable used for storing value of speed in X axis obtained from the accelerometer.
    * \param SpeedY - float type variable used for storing value of speed in Y axis obtained from the accelerometer.
    * \param DegreeZ - float type variable used for storing value of rotation around Z axis obtained from the gyroscope.
    */

    char Sign;
    float Get1;
    float Get2;
    float Get3;
    float Dist1;
    float Dist2;
    float Dist3;
    float SpeedX;
    float SpeedY;
    float DegreeZ;

} sensorData;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



//! \brief Class for reading data and drawing inside a window.
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    //! Main window initialization.
    /*!
      \param[in] *parent - unused parameter, because main window has no parent
    */
    explicit MainWindow(QWidget *parent = nullptr);

    //! Destructor */
    ~MainWindow();


signals:
    //! A signal which tells if data was read properly from the serial port.
    /*!
      \param[in] measured - pointer to the structure sensorData, which contains ifnormation about data read from the serial port
    */
    void parsedMeasurementReady(sensorData measured);

public slots:
    //! Public slot responsible for updating main window by passing values to LCDs, progress bar and calling function update().
    /*!
      \param[in] rotation - double type variable containing current rotation of device
      \param[in] speed - double type variable containing current speed of device
      \param[in] distance1 - double type variable containing read and calculated value of distance obtained from first distance sensor
      \param[in] distance2 - double type variable containing read and calculated value of distance obtained from second distance sensor
      \param[in] distance3 - double type variable containing read and calculated value of distance obtained from third distance sensor
    */
    void updateImage(double rotation, double speed, double distance1, double distance2, double distance3);

private slots:
    //! A private slot for Search button, which searches for serial ports and adds them to the ComboBox.
    /*!
    */
    void on_pushButtonSearch_clicked();

    //! A private slot for Connect button, which starts reading data from the serial port.
    /*!
    */
    void on_pushButtonConnect_clicked();

    //! A private slot for Disconnect button, which stops reading data from the serial port.
    /*!
    */
    void on_pushButtonDisconnect_clicked();

    //! A private slot for iniciating process of reading data from serial port.
    /*!
    */
    void readFromPort();

private:
    //! Pointer to user interface elements
    Ui::MainWindow *ui;

    //! Painter used to draw objects inside the window
    QPainter *windowPainter;

    //! Timer used to update drawn images and displayed values.
    QTimer *timer;

    //! QSerialPort pointer used to servicing serial port.
    QSerialPort *device;

    //! Private function to process a line from the input.
    /*!
      \param[in] line - QString received from serial port.
    */
    void process_line(QString line);

    //! QString variable used to store a line from the serial port.
    QString serialBuffer;

    //! QPixmap variable containing image of steering wheel.
    QPixmap imageSteeringWheel;

    //! QPixmap variable containing image of speedometer.
    QPixmap imageSpeedometer;

    //! Image object representing speedometer
    Image speedometer;

    //! Image object representing steering wheel.
    Image steeringWheel;

    //! Gauge object representing gauge of the speedometer.
    Gauge speedGauge;

    //! Zone object representing safety zone.
    Zone safetyZone;

    //! RoundedRectangle representing front top wheel.
    RoundedRectangle wheelFrontTop;
    //! RoundedRectangle representing front bottom wheel.
    RoundedRectangle wheelFrontBottom;
    //! RoundedRectangle representing rear top wheel.
    RoundedRectangle wheelRearTop;
    //! RoundedRectangle representing rear bottom wheel.
    RoundedRectangle wheelRearBottom;
    //! RoundedRectangle representing car main body.
    RoundedRectangle car;

    //! RoundedRectangle representing first obstacle.
    RoundedRectangle obstacle1;
    //! RoundedRectangle representing second obstacle.
    RoundedRectangle obstacle2;
    //! RoundedRectangle representing third obstacle.
    RoundedRectangle obstacle3;
    //! RoundedRectangle representing fourth obstacle.
    RoundedRectangle obstacle4;

    //! Pen used to draw points
    QPen pointPen;
    //! Pen used to draw gauge
    QPen gaugePen;
    //! Pen used to draw lines
    QPen linePen;

    //! Float type variable containing current speed value.
    float speed = 0;
    //! Float type variable containing current rotation angle.
    double rotation = 0;
    //! Float type variable containing current distance between first sensor and obstacle.
    double distance1 = 0;
    //! Float type variable containing current distance between second sensor and obstacle.
    double distance2 = 0;
    //! Float type variable containing current distance between second sensor and obstacle.
    double distance3 = 0;

protected:
    //! Event used to update the drawings
    /*!
      \param[in] event - unused parameter
    */
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_HH

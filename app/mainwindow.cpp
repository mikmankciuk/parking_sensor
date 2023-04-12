#include "mainwindow.hh"
#include "image.hh"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <sstream>
#include <QDebug>
#include <iostream>
#include <cstring>
#include <string>
#include <cassert>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define CRC_INIT       0xffff
#define CRC_POLYNOMIAL 0x1021
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
    serialBuffer = "";

    /*
     *  Setting thee names in ui.
     */

    QString name_window = tr("Czujnik Parkowania");
    setWindowTitle(name_window);
    QString name_Connect = tr("Połącz");
    ui->pushButtonConnect->setText(name_Connect);
    QString name_Disconnect = tr("Rozłącz");
    ui->pushButtonDisconnect->setText(name_Disconnect);
    QString name_Search = tr("Szukaj");
    ui->pushButtonSearch->setText(name_Search);


    /*
     *  prepare pens
     */
    pointPen.setColor(Qt::black);
    pointPen.setWidth(3);

    gaugePen.setColor(Qt::red);
    gaugePen.setWidth(1);

    linePen.setColor(Qt::black);
    linePen.setWidth(4);

    /*  set up timer to draw images
     */
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(readFromPort()));
    timer->start(1000/5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Search for serial ports and add them to the comboBox
void MainWindow::on_pushButtonSearch_clicked()
{
    QList<QSerialPortInfo> devices;
    qDebug() << "Searching...";
    ui->comboBoxDevices->clear();
    devices = QSerialPortInfo::availablePorts();
    for(int i = 0; i < devices.count(); i++) {
      ui->comboBoxDevices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}


// Read from the serial port
void MainWindow::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0) {
      qDebug() << "No device found";
      return;
    }

    QString portName = ui->comboBoxDevices->currentText().split("\t").first();
    this->device->setPortName(portName);
    qDebug() << portName;

    if(!device->isOpen())
    {
        if(device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud115200);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            qDebug() << "Serial port opened";

            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));

        }
        else
        {
            qDebug() << "Couldn't open the serial port" ;
        }
    }
    else
    {
        qDebug() << "Port already opened";
        return;
    }
}


// Check CRC16
unsigned short int ComputeCRC16_CCITT_FALSE(const char* pData, int Length)
{
    short int i;
    unsigned short int wCrc = CRC_INIT;

    while (Length--) {
        wCrc ^= *(unsigned const char *)pData++ << 8;
        for (i=0; i < 8; i++)
            wCrc = wCrc & 0x8000 ? (wCrc << 1) ^ CRC_POLYNOMIAL : wCrc << 1;
    }
    return wCrc;
}


// Parse data from the read line
int ParseDataFrame( const char *pDataFrame, sensorData &sensor)
{

  std::istringstream IStrm(pDataFrame);
  char  FHeader;
  unsigned int CRC16;

  IStrm >> FHeader >> sensor.Get1 >> sensor.Get2 >> sensor.Get3 >> hex >> CRC16;
  if(!IStrm.fail())
  {
      switch(FHeader){
       case 'Z':
          sensor.Sign = FHeader;
          sensor.SpeedX = sensor.Get1;
          sensor.SpeedY = sensor.Get2;
          sensor.DegreeZ = sensor.Get3;
          break;
       case 'X':
          sensor.Sign = FHeader;
          sensor.Dist1 = sensor.Get1;
          sensor.Dist2 = sensor.Get2;
          sensor.Dist3 = sensor.Get3;
          break;
       default:
          break;
       }
    return static_cast<unsigned short int>(CRC16) == ComputeCRC16_CCITT_FALSE(pDataFrame,strlen(pDataFrame)-4);
  }
  else
      return false;
}


inline
bool ParseDataFrame( const std::string &rDataFrame, sensorData &sensor)
{

    return ParseDataFrame(rDataFrame.c_str(),sensor);
}


// Stop reading from the serial port.
void MainWindow::on_pushButtonDisconnect_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      qDebug() << "Port closed";
    } else {
      qDebug() << "Port not opened";
      return;
    }
}


// Reading while it is possible
void MainWindow::readFromPort()
{
  //  clock_t time =clock();
   while(this->device->canReadLine())
   {

      process_line(device->readLine());

   };
}


// Process a line from the input
void MainWindow::process_line(QString line)
{

    int flag=0;
    QString terminator = "\r";
    int pos = line.lastIndexOf(terminator);

    sensorData sensor;
    if( ParseDataFrame(line.left(pos).toStdString(), sensor) )
    {

        emit parsedMeasurementReady(sensor);
        qDebug() << line.left(pos);
        flag=1;

    }
        else
    {
        qDebug() << line.left(pos);
        qDebug() << "BIADA";
        flag=-1;
    }

    if(flag==1)
    {
        if(sensor.Sign=='X')
        {

            if(sensor.Dist1 <= 200 && sensor.Dist1 >=2)
            {
                sensor.Dist1 = roundf(sensor.Dist1 * 100) / 100;
                distance1=sensor.Dist1;
            }
            else if(sensor.Dist1 > 200)
                distance1=400;   //bo ianczej na start jest 0 i nie wiem czy potem się też nie zeruje przy updatecie
            else if(sensor.Dist1 < 2)
                distance1=2;

            if(sensor.Dist2 <= 200 && sensor.Dist2 >=2)
            {
                sensor.Dist2 = roundf(sensor.Dist2 * 100) / 100;
                distance2=sensor.Dist2;
            }
            else if(sensor.Dist2 > 200)
                distance2=400;   //bo ianczej na start jest 0 i nie wiem czy potem się też nie zeruje przy updatecie
            else if(sensor.Dist2 < 2)
                distance2=2;

            if(sensor.Dist3 <= 200 && sensor.Dist3 >=2)
            {
                sensor.Dist3 = roundf(sensor.Dist3 * 100) / 100;
                distance3=sensor.Dist3;
            }
            else if(sensor.Dist3 > 200)
                distance3=400;   //bo ianczej na start jest 0 i nie wiem czy potem się też nie zeruje przy updatecie
            else if(sensor.Dist3 < 2)
                distance3=2;

        }
        else if(sensor.Sign=='Z')
        {

            speed = sqrt(pow(sensor.SpeedX, 2) + pow(sensor.SpeedY, 2));

            speed = roundf(speed * 100) / 100;
            if(speed < 0)
                speed = 0;
            //else if(speed > 20)
              //  speed = 20;

            rotation = sensor.DegreeZ;
            rotation = roundf(rotation * 100) / 100;
            if(rotation > 90)
                rotation = 90;
            else if(rotation < -90)
                rotation = -90;
        }

        qDebug() << "----------------------------\n";
        qDebug() << "dist1:  "  << distance1 << "\n";
        qDebug() << "dist2:  "  << distance2 << "\n";
        qDebug() << "dist3:  "  << distance3 << "\n";
        qDebug() << "speed:  "  << speed     << "\n";
        qDebug() << "degree: "  << rotation  << "\n";

        updateImage(rotation, speed, distance1, distance2, distance3);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    /*  prepare painter and paths
     */
    windowPainter = new QPainter(this);
    windowPainter->setRenderHint(QPainter::Antialiasing);

    windowPainter->scale(width() / 900.0, height() / 600.0);
    windowPainter->setPen(linePen);

    int offsetX = 100;
    int offsetY = 45;

    QPainterPath objectsPath, zonePath, upperWheelPath, lowerWheelPath, gaugePath;
    QPolygonF gaugePolygon;


    /***********************************************************************/

    /*  update objects parameters
     */

    /***********************************************************************/

    car.updateParameters(offsetX, offsetY + 75, 0, 275);
    car.updateRectParameters(15.0, 0.5454);

    obstacle1.updateParameters(offsetX + 200,offsetY + 5, 0, 50);
    obstacle1.updateRectParameters(15.0, 1);
    obstacle2.updateParameters(offsetX + 200,offsetY + 90, 0, 50);
    obstacle2.updateRectParameters(15.0, 1);
    obstacle3.updateParameters(offsetX + 200,offsetY + 155, 0, 50);
    obstacle3.updateRectParameters(15.0, 1);
    obstacle4.updateParameters(offsetX + 200,offsetY + 240, 0, 50);
    obstacle4.updateRectParameters(15.0, 1);

    wheelRearTop.updateParameters(offsetX + 195,offsetY + 65, 0, 50);
    wheelRearTop.updateRectParameters(5.0, 0.4);
    wheelRearBottom.updateParameters(offsetX + 195,offsetY + 215, 0, 50);
    wheelRearBottom.updateRectParameters(5.0, 0.4);

    // front wheels are drawn differently, their centers position has to be predefined;
    int wheelFrontTopX = offsetX + 45, wheelFrontTopY = offsetY + 75;
    int wheelFrontBottomX = offsetX + 45, wheelFrontBottomY = offsetY + 225;

    wheelFrontTop.updateParameters(-25, -10, rotation/2, 50);
    wheelFrontTop.updateRectParameters(5.0, 0.4);
    wheelFrontBottom.updateParameters(-25, -10, rotation/2, 50);
    wheelFrontBottom.updateRectParameters(5.0, 0.4);

    /***********************************************************************/

    /*  draw safety zone behind car
     */

    /***********************************************************************/

    //  prepare zone parameters before drawing
    safetyZone.updateParameters(offsetX + 275, offsetY + 100, rotation, speed * 6);
    safetyZone.updatePoints();
    //zonePath.clear();
    zonePath.moveTo(safetyZone.getStartTop());
    zonePath.cubicTo(safetyZone.getStartTop(), safetyZone.getTransitionTop(), safetyZone.getEndTop());
    zonePath.lineTo(safetyZone.getEndBottom());
    zonePath.cubicTo(safetyZone.getEndBottom(), safetyZone.getTransitionBottom(), safetyZone.getStartBottom());
    zonePath.lineTo(safetyZone.getStartTop());
    safetyZone.updateColor(min(min(distance1,distance2),distance3));

    //  draw zone
    windowPainter->fillPath(zonePath,safetyZone.getZoneColor());
    windowPainter->drawPath(zonePath);

    /***********************************************************************/

    /*  draw car model
     */

    /***********************************************************************/

    windowPainter->drawRoundedRect(car.getRectangle(),car.getCurvatureParameter(),car.getCurvatureParameter());

    /***********************************************************************/

    /*  draw obstacles, car and rear wheels
     */

    /***********************************************************************/

    //  translate obstacles to their position
    obstacle1.translate(offsetX + 150 + distance1,0);
    obstacle2.translate(offsetX + 150 + distance2,0);
    obstacle3.translate(offsetX + 150 + distance2,0);
    obstacle4.translate(offsetX + 150 + distance3,0);

    //  add wheels and obstacles to path
    objectsPath.addRoundedRect(obstacle1.getRectangle(), obstacle1.getCurvatureParameter(), obstacle1.getCurvatureParameter());
    objectsPath.addRoundedRect(obstacle2.getRectangle(), obstacle2.getCurvatureParameter(), obstacle2.getCurvatureParameter());
    objectsPath.addRoundedRect(obstacle3.getRectangle(), obstacle3.getCurvatureParameter(), obstacle3.getCurvatureParameter());
    objectsPath.addRoundedRect(obstacle4.getRectangle(), obstacle4.getCurvatureParameter(), obstacle4.getCurvatureParameter());
    objectsPath.addRoundedRect(wheelRearTop.getRectangle(),wheelRearTop.getCurvatureParameter(),wheelRearTop.getCurvatureParameter());
    objectsPath.addRoundedRect(wheelRearBottom.getRectangle(),wheelRearBottom.getCurvatureParameter(),wheelRearBottom.getCurvatureParameter());

    //  draw and fill path
    windowPainter->fillPath(objectsPath,Qt::black);
    windowPainter->drawPath(objectsPath);

    /***********************************************************************/

    /*  draw front wheels of the car
     */

    /***********************************************************************/

    //  upper (right) wheel
    upperWheelPath.addRoundedRect(wheelFrontTop.getRectangle(),wheelFrontTop.getCurvatureParameter(),wheelFrontTop.getCurvatureParameter());
    windowPainter->translate(wheelFrontTopX,wheelFrontTopY);
    windowPainter->rotate(-wheelFrontTop.getRotation());
    windowPainter->fillPath(upperWheelPath,Qt::black);
    windowPainter->drawPath(upperWheelPath);
    windowPainter->rotate(wheelFrontTop.getRotation());
    windowPainter->translate(-wheelFrontTopX,-wheelFrontTopY);

    //  lower (left) wheel
    lowerWheelPath.addRoundedRect(wheelFrontBottom.getRectangle(),wheelFrontBottom.getCurvatureParameter(),wheelFrontBottom.getCurvatureParameter());
    windowPainter->translate(wheelFrontBottomX,wheelFrontBottomY);
    windowPainter->rotate(-wheelFrontBottom.getRotation());
    windowPainter->fillPath(lowerWheelPath,Qt::black);
    windowPainter->drawPath(lowerWheelPath);
    windowPainter->rotate(wheelFrontBottom.getRotation());
    windowPainter->translate(-wheelFrontBottomX,-wheelFrontBottomY);

    /***********************************************************************/

    /*  draw speed gauge
     *  positionX and positionY define center point of the gauge,
     */

    /***********************************************************************/

    //  prepare gauge parameters for it to display speed value
    speedGauge.updateParameters(offsetX + 380, offsetY + 395, speed, 30);
    speedGauge.updatePoints();

    gaugePolygon << speedGauge.getGaugeTop() << speedGauge.getGaugeRight() << speedGauge.getGaugeBottom() << speedGauge.getGaugeLeft();
    gaugePath.addPolygon(gaugePolygon);

    //  move painter
    windowPainter->translate(speedGauge.getPositionX(), speedGauge.getPositionY());
    windowPainter->rotate(speedGauge.getRotation()*73 - 110);

    //  draw polygon part of the gauge
    windowPainter->setPen(gaugePen);
    windowPainter->drawPath(gaugePath);
    windowPainter->fillPath(gaugePath,Qt::red);

    //  draw point in the center of the gauge
    windowPainter->setPen(pointPen);
    windowPainter->drawPoint(speedGauge.getGaugeCenter());

    //  undo rotation and move pointer back to (0,0)
    windowPainter->rotate(-speedGauge.getRotation()*73 + 110);
    windowPainter->translate(-speedGauge.getPositionX(), -speedGauge.getPositionY());

    /***********************************************************************/

    /*  draw speedometer
     *  positonX and positionY define center of the image,
     *  hence drawing starts at -size/2
     */

    /***********************************************************************/

    //  load image and update values for speedometer location
    imageSpeedometer.load(":speedGraph.png");
    speedometer.setPixmap(imageSpeedometer);
    speedometer.updateParameters(offsetX + 380, offsetY + 395, 0, 140);

    //  move painter
    windowPainter->translate(speedometer.getPositionX(), speedometer.getPositionY());

    //  draw pixmap of speedometer
    windowPainter->drawPixmap(-speedometer.getSize()/2, -speedometer.getSize()/2,
                              speedometer.getSize(), 7*speedometer.getSize()/10,
                              speedometer.getPixmap());

    //  move painter back to (0,0)
    windowPainter->translate(-speedometer.getPositionX(),-speedometer.getPositionY());

    /***********************************************************************/

    /*  draw steering wheel
     * positonX and positionY define center of the image
     */

    /***********************************************************************/

    //  load image and update values for steering wheel location and rotation
    imageSteeringWheel.load(":steeringWheel.png");
    steeringWheel.setPixmap(imageSteeringWheel);
    steeringWheel.updateParameters(offsetX + 110, offsetY + 365, rotation, 120);

    //  move and rotate painter
    windowPainter->translate(steeringWheel.getPositionX(), steeringWheel.getPositionY());
    windowPainter->rotate(-steeringWheel.getRotation());

    //  draw pixmap of steering wheel
    windowPainter->drawPixmap(-steeringWheel.getSize()/2, -steeringWheel.getSize()/2,
                              steeringWheel.getSize(), steeringWheel.getSize(),
                              steeringWheel.getPixmap());

    //  move painter back to (0,0) and reset rotation
    windowPainter->rotate(steeringWheel.getRotation());
    windowPainter->translate(-steeringWheel.getPositionX(), -steeringWheel.getPositionY());

    /***********************************************************************/

    /*  reset painter
     */
    windowPainter->end();
}

void MainWindow::updateImage(double rotation, double speed, double distance1, double distance2, double distance3)
{
    if(min(min(distance1,distance2),distance3)>100)
    {
        ui->progressBar->setValue(0);
    }
    else
        ui->progressBar->setValue(100 - min(min(distance1,distance2),distance3));

    if(min(min(distance1,distance2),distance3) < 10)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: red; }");
    else if(min(min(distance1,distance2),distance3) < 25)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: orangered; }");
    else if(min(min(distance1,distance2),distance3) < 40)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: orange; }");
    else if(min(min(distance1,distance2),distance3) < 55)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: yellow; }");
    else if(min(min(distance1,distance2),distance3) < 80)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: greenyellow; }");
    else if(min(min(distance1,distance2),distance3) <= 100)
        ui->progressBar->setStyleSheet(ui->progressBar->property("defaultStyleSheet").toString() + " QProgressBar::chunk { background: green; }");

    ui->lcd_rot->display(-rotation);
    ui->lcd_speed->display(speed);
    ui->lcd_dist->display(min(min(distance1,distance2),distance3));

    update();
}

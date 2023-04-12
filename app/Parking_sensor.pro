QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawableobject.cpp \
    gauge.cpp \
    image.cpp \
    main.cpp \
    mainwindow.cpp \
    roundedrectangle.cpp \
    zone.cpp

HEADERS += \
    drawableobject.hh \
    gauge.hh \
    image.hh \
    mainwindow.hh \
    roundedrectangle.hh \
    zone.hh

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Parking_sensor_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    speedGraph.png \
    steeringWheel.png

RESOURCES += \
    images.qrc \
    lang.qrc

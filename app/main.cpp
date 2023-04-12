#include "mainwindow.hh"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    translator.load(":/Parking_sensor_en_GB.qm");

    //If you want an english verison of the widnow, just uncomment phrase below.
    app.installTranslator(&translator);


    MainWindow w;

    w.show();
    return app.exec();
}

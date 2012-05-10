#include <QtGui/QApplication>
#include <QDir>
#include <QDebug>
#include "clientrunner.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QFile fil(QApplication::applicationDirPath() + QDir::separator() + "settings.ini");
    QString confData;
    bool confFileExists;
    if (fil.exists()) {
        if (fil.open(QIODevice::ReadOnly)) {
            confData = fil.readAll();
            //qDebug() << confData;
            confFileExists = true;
            fil.close();
        }
    }

    if (confFileExists) {
        QStringList settings = confData.split(";");
        for (int i = 0; i < settings.count(); i++) {
            QStringList setting = settings.at(i).split("=");
            if (setting.count() == 2) {
                QString settingName = setting.at(0);
                QString settingValue = setting.at(1);
                if (settingName == "UpdateLocation") {
                    QString updatePath = settingValue;
                    QDir updateDir(updatePath);
                    //QString versionTextPath =
                }
            }
        }
    }

    ClientRunner runer;
    runer.start();
    qDebug() << "Thread started";
    while (runer.isRunning()) {

    }
    qDebug() << "Thread stoppped";
    return a.exec();
}

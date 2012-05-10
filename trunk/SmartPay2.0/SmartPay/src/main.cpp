#include <QtGui>
#include "mainwindow.h"
#include <QtSql>
#include <QFile>

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


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("kapsadmin");
    db.setDatabaseName("payroll");
    if (confFileExists) {
        QStringList settings = confData.split(";");
        for (int i = 0; i < settings.count(); i++) {
            QStringList setting = settings.at(i).split("=");
            if (setting.count() == 2) {
                QString settingName = setting.at(0);
                QString settingValue = setting.at(1);
                if (settingName == "host")
                    db.setHostName(settingValue);
                if (settingName == "user")
                    db.setUserName(settingValue);
                if (settingName == "password")
                    db.setPassword(settingValue);
                if (settingName == "database")
                    db.setDatabaseName(settingValue);
                if (settingName == "port")
                    db.setPort(settingValue.toInt());
                if (settingName == "style")
                    qApp->setStyle(settingValue);
            }
        }
    } else {
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPort(3306);
        db.setPassword("kapsadmin");
        db.setDatabaseName("payroll");
    }

    if (db.open()) {
        qDebug() << "Connected to mysql://" + db.userName() + "@" + db.hostName() + ":" + QString::number(db.port()) + "/" + db.databaseName();
        MainWindow *w = new MainWindow(0, db);
        w->showMaximized();
        return a.exec();
    } else {
        QMessageBox::critical(0, "Database Error", "<h2>" + db.lastError().text() + "</h2>This application will now exit.");
        return 0;
    }
}

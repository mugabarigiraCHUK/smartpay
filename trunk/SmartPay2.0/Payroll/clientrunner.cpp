#include "clientrunner.h"
#include <QApplication>
#include <QDir>
#include <QProcess>
void ClientRunner::run() {
    QProcess *payrollProcess = new QProcess(0);
    payrollProcess->start(QApplication::applicationDirPath() + QDir::separator() + "\SmartPay.exe");

    //connect(payrollProcess, SIGNAL(finished(int)), SLOT(quit()));
}

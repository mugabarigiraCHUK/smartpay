#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"

#include "employees.h"
#include "lists.h"
#include "leaves.h"
#include "payroll.h"
#include "attendance.h"
#include "timetable.h"
#include "admin.h"

#include "userlogin.h"
#include "myaccount.h"

MainWindow::MainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = database;

    QString baseName = QApplication::style()->objectName();
#ifdef Q_WS_X11
    if (baseName == QLatin1String("windows")) {
        // Sometimes we get the standard windows 95 style as a fallback
        // e.g. if we are running on a KDE4 desktop
        QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
        if (desktopEnvironment == "kde")
            baseName = QLatin1String("plastique");
        else
            baseName = QLatin1String("cleanlooks");
    }
#endif
    qApp->setStyle(new ManhattanStyle(baseName));
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));

    logIn();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatabase(QSqlDatabase database)
{
    db =database;
}

void MainWindow::logOff()
{
    for (int i = 0; i <= count; i++) {
        ui->widget->removeTab(i);
    }
    delete (m_employees);
    delete (m_lists);
    delete (m_leaves);
    delete (m_payroll);
    delete (m_attendance);
    delete (m_timeTable);
    delete (m_admin);
    delete (m_acc);

    logIn();
}

void MainWindow::logIn()
{
    UserLogin *l = new UserLogin(this, db);
    m_employees = new Employees(this, db);
    m_lists = new Lists(this, db);
    m_leaves = new Leaves(this, db);
    m_attendance = new Attendance(this, db);
    m_timeTable = new Timetable(this, db);
    m_payroll = new Payroll(this, db);
    m_admin = new Admin(this, db);
    m_acc = new MyAccount(this, db);

    count = 0;
    if (l->exec() == QDialog::Accepted) {
        ui->widget->insertTab(m_employees);
        count++;
        ui->widget->insertTab(m_lists);
        count++;
        if (!l->EditHR)
        {
            m_employees->hideHR();
        }
        if (!l->EditFinance) {
            m_employees->hideFinance();
        }
        if (l->EditLeaves) {
            ui->widget->insertTab(m_leaves);
            count++;
        }
        if (l->EditAttendance) {
            ui->widget->insertTab(m_timeTable);
            count++;
            ui->widget->insertTab(m_attendance);
            count++;
        }
        if (l->EditPayroll) {
            ui->widget->insertTab(m_payroll);
            count++;
            ui->widget->insertTab(m_admin);
            count++;
        }
        //ui->widget->insertTab(m_acc);
        count++;
        connect (m_acc, SIGNAL(logOff()), SLOT(logOff()));
    } else {
        this->close();
        qApp->quit();
    }
}

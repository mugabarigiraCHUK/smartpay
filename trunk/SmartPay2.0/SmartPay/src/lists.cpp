#include "lists.h"
#include "ui_lists.h"

#include "departments.h"
#include "holidays.h"
#include "jobtitles.h"
#include "payrollmonths.h"
#include "shifts.h"
#include "saccos.h"

Lists::Lists(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Lists)
{
    ui->setupUi(this);
    db = database;


    ui->departmentsToolBar->setStyleSheet("QToolButton { border-image: url(:/images/panel_button.png) 2 2 2 19;"
                                          " border-width: 2px 2px 2px 19px; padding-left: -17; padding-right: 4 } "
                                          "QToolButton:checked { border-image: url(:/images/panel_button_checked.png) 2 2 2 19 } "
                                          "QToolButton::menu-indicator { width:0; height:0 }"
                );

    QActionGroup *ag = new QActionGroup(this);
    ag->addAction(ui->actionDepartments);
    ag->addAction(ui->actionHolidays);
    ag->addAction(ui->actionJob_Titles);
    ag->addAction(ui->actionShifts);
    ag->addAction(ui->actionSaccos);
    ag->addAction(ui->actionPayrollMonths);


    m_dept = new Departments(this, db);
    m_job_titles = new JobTitles(this, db);
    m_holidays = new Holidays(this);
    m_months = new PayrollMonths(this, db);
    m_shifts = new Shifts(this, db);
    m_saccos = new Saccos(this, db);

    ui->stackedWidget->addWidget(m_dept);
    ui->stackedWidget->addWidget(m_job_titles);
    ui->stackedWidget->addWidget(m_holidays);
    ui->stackedWidget->addWidget(m_months);
    ui->stackedWidget->addWidget(m_shifts);
    ui->stackedWidget->addWidget(m_saccos);

    ui->stackedWidget->setCurrentWidget(m_dept);
    ui->actionDepartments->setChecked(true);
}

Lists::~Lists()
{
    delete ui;
}

void Lists::on_actionDepartments_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_dept);
}

void Lists::on_actionJob_Titles_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_job_titles);
}

void Lists::on_actionShifts_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_shifts);
}

void Lists::on_actionSaccos_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_saccos);
}

void Lists::on_actionHolidays_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_holidays);
}

void Lists::on_actionPayrollMonths_triggered()
{
    ui->stackedWidget->setCurrentWidget(m_months);
}

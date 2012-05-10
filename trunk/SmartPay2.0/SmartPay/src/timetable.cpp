#include "timetable.h"
#include "ui_timetable.h"

#include "createtimetable.h"

#include "publics.h"

Timetable::Timetable(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);
    db = database;
    ui->StartDate->setDate(QDate::currentDate().addDays(-7));
    ui->EndDate->setDate(QDate::currentDate().addDays(7));
    reloadShifts();
    reloadTimeTable();
}

Timetable::~Timetable()
{
    delete ui;
}

void Timetable::reloadShifts()
{
   //Publics::loadDbToComboBox(db, "SELECT * FROM shifts", "ShiftName", ui->Shift);
}

void Timetable::reloadTimeTable()
{
    //QString shiftID = Publics::getDbValue(db, "SELECT * FROM shifts WHERE ShiftID = '" + ui->Shift->currentText() + "'", "ShiftID");

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_timetable WHERE Date BETWEEN '" + Publics::getDateString(ui->StartDate->date()) + "' AND '" + Publics::getDateString(ui->EndDate->date()) + "' ORDER BY `Date`");
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

void Timetable::on_CreateTimetable_clicked()
{
    CreateTimetable ct(this, db);
    if (ct.exec()) {

    }
}

void Timetable::on_ViewEmployees_clicked()
{
    reloadTimeTable();
}

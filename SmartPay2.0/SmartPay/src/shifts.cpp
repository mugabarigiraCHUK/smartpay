#include "shifts.h"
#include "ui_shifts.h"

Shifts::Shifts(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::Shifts)
{
    ui->setupUi(this);
    db = database;
    model = new QSqlQueryModel(this);
    ui->treeView->setModel(model);
    reload();
    clearTexts();
    isAdding = true;
    on_SaveAndNew_clicked();
}

Shifts::~Shifts()
{
    delete ui;
}

void Shifts::reload()
{
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_shifts", db);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

void Shifts::clearTexts()
{
    ui->ShiftName->setText("");
    ui->Description->setText("");
    ui->StartTime->setTime(QTime::fromString("08:00:00", "hh:mm:ss"));
    ui->EndTime->setTime(QTime::fromString("08:00:00", "hh:mm:ss"));
    ui->HasOvertime->setChecked(false);
    ui->OvertimeStart->setTime(QTime::fromString("08:00:00", "hh:mm:ss"));
    ui->MaximumOtMinutes->setValue(0);
    ui->LunchMinutes->setValue(0);
    ui->HasPenalties->setChecked(false);
    ui->Monday->setChecked(false);
    ui->Tuesday->setChecked(false);
    ui->Wednesday->setChecked(false);
    ui->Thursday->setChecked(false);
    ui->Friday->setChecked(false);
    ui->Saturday->setChecked(false);
    ui->Sunday->setChecked(false);
}

void Shifts::on_treeView_clicked(const QModelIndex &index)
{
    currentID = model->record(index.row()).value(0).toString();
    QSqlQuery qu = db.exec("SELECT * FROM shifts WHERE ShiftID = '" + currentID + "'");
    clearTexts();
    while (qu.next()) {
        QSqlRecord rec = qu.record();
        ui->ShiftName->setText(rec.value("ShiftName").toString());
        ui->Description->setText(rec.value("Description").toString());
        ui->StartTime->setTime(QTime::fromString(rec.value("StartTime").toString(), "hh:mm:ss"));
        ui->EndTime->setTime(QTime::fromString(rec.value("EndTime").toString(), "hh:mm:ss"));
        ui->OvertimeStart->setTime(QTime::fromString(rec.value("OvertimeStart").toString(), "hh:mm:ss"));

        if (rec.value("HasOvertime").toString() == "Yes")
            ui->HasOvertime->setChecked(true);

        if (rec.value("HasPenalties").toString() == "Yes")
            ui->HasPenalties->setChecked(true);

        if (rec.value("Monday").toString() == "Yes")
            ui->Monday->setChecked(true);

        if (rec.value("Tuesday").toString() == "Yes")
            ui->Tuesday->setChecked(true);

        if (rec.value("Wednesday").toString() == "Yes")
            ui->Wednesday->setChecked(true);

        if (rec.value("Thursday").toString() == "Yes")
            ui->Thursday->setChecked(true);

        if (rec.value("Friday").toString() == "Yes")
            ui->Friday->setChecked(true);

        if (rec.value("Saturday").toString() == "Yes")
            ui->Saturday->setChecked(true);

        if (rec.value("Sunday").toString() == "Yes")
            ui->Sunday->setChecked(true);

        ui->MaximumOtMinutes->setValue(rec.value("MaximumOvertimeMinutes").toInt());
        ui->LunchMinutes->setValue(rec.value("LunchMinutes").toInt());
        isAdding = false;
        ui->Delete->setEnabled(true);
        return;
    }
}

void Shifts::on_SaveAndNew_clicked()
{
    if (!isAdding)
        on_Save_clicked();
    isAdding = true;
    clearTexts();
    ui->Delete->setEnabled(false);
}

void Shifts::on_Save_clicked()
{
    if (ui->ShiftName->text().trimmed() == "") {
        QMessageBox::warning(this, "Fill all Details", "The shift name cannot be blank.");
        return;
    }

    if (isAdding) {
        QSqlQuery qu = db.exec("INSERT INTO shifts (ShiftName) VALUES('" + ui->ShiftName->text() + "')");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
        currentID = qu.lastInsertId().toString();
        isAdding = false;
        ui->Delete->setEnabled(true);
    }

    QString hasP = "No";
    QString hasO = "No";
    QString mon = "No";
    QString tue = "No";
    QString wed = "No";
    QString thu = "No";
    QString fri = "No";
    QString sat = "No";
    QString sun  = "No";

    if (ui->Monday->isChecked())
        mon = "Yes";

    if (ui->Tuesday->isChecked())
        tue = "Yes";

    if (ui->Wednesday->isChecked())
        wed = "Yes";

    if (ui->Thursday->isChecked())
        thu = "Yes";

    if (ui->Friday->isChecked())
        fri = "Yes";

    if (ui->Saturday->isChecked())
        sat = "Yes";

    if (ui->Sunday->isChecked())
        sun = "Yes";


    if (ui->HasOvertime->isChecked())
        hasO = "Yes";

    if (ui->HasPenalties->isChecked())
        hasP = "Yes";

    QSqlQuery saveQu = db.exec("UPDATE Shifts SET ShiftName = '"
                               + ui->ShiftName->text() + "', "
                               "Description = '" + ui->Description->text() + "', "
                               "StartTime = '" + ui->StartTime->time().toString("hh:mm:ss")  + "', "
                               "EndTime = '" + ui->EndTime->time().toString("hh:mm:ss") + "', "
                               "OvertimeStart = '" + ui->OvertimeStart->time().toString("hh:mm:ss")  + "', "
                               "MaximumOvertimeMinutes = '" + QString::number(ui->MaximumOtMinutes->value())  + "', "
                               "LunchMinutes = '" + QString::number(ui->LunchMinutes->value())  + "', "
                               "HasOvertime = '" + hasO  + "', "
                               "Monday = '" + mon + "', "
                               "Tuesday = '" + tue + "', "
                               "Wednesday = '" + wed + "', "
                               "Thursday = '" + thu + "', "
                               "Friday = '" + fri + "', "
                               "Saturday = '" + sat + "', "
                               "Sunday = '" + sun + "', "
                               "HasPenalties = '" + hasP  + "' WHERE ShiftID = '" + currentID + "'");
    if (saveQu.lastError().isValid()) {
        QMessageBox::critical(this, "Error", saveQu.lastError().text());
        return;
    }

    reload();
}

void Shifts::on_Delete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this shift?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QSqlQuery qu = db.exec("DELETE FROM shifts WHERE shiftID = '" + currentID + "'");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
        reload();
        clearTexts();
        isAdding = true;
        on_SaveAndNew_clicked();
    }
}

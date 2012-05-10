#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    db = database;
    loadUsers();
    on_SaveAndNew_clicked();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::loadUsers()
{
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_users", db);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

void Admin::clearTexts()
{
    for (int i = 0; i < ui->groupBox->children().count(); i++) {
        if ( qobject_cast<QLineEdit *>(ui->groupBox->children().at(i)) ) {
            QLineEdit *t = qobject_cast<QLineEdit *>(ui->groupBox->children().at(i));
            t->setText("");
        }
        if ( qobject_cast<QCheckBox *>(ui->groupBox->children().at(i)) ) {
            QCheckBox *c = qobject_cast<QCheckBox *>(ui->groupBox->children().at(i));
            c->setChecked(false);
        }
    }
    currentID = "";
}

void Admin::on_SaveAndNew_clicked()
{
    on_SaveChanges_clicked();
    clearTexts();
    isAdding = true;
    ui->Delete->setEnabled(false);
}

void Admin::on_SaveChanges_clicked()
{
    if (isAdding) {
        QSqlQuery ins = db.exec("INSERT INTO Users (LoginName) VALUES ('" + ui->LoginName->text() + "')");

        if (!ins.lastError().isValid()) {
            currentID = ins.lastInsertId().toString();
        } else {
            return;
        }
        isAdding = false;
    }

    QString HR = "No";
    QString Finance = "No";
    QString Leaves = "No";
    QString Payroll = "No";
    QString Attendance = "No";

    if (ui->EditHR->isChecked())
        HR = "Yes";

    if (ui->EditFinance->isChecked())
        Finance = "Yes";

    if (ui->EditLeaves->isChecked())
        Leaves = "Yes";

    if (ui->EditPayroll->isChecked())
        Payroll = "Yes";

    if (ui->EditAttendance->isChecked())
        Attendance = "Yes";

    QSqlQuery save = db.exec(
                "UPDATE users SET "
                "LoginName = '" + ui->LoginName->text() + "', "
                "PassWord = '" + ui->Password->text() + "', "
                "EditHR = '" + HR + "', "
                "EditLeaves = '" + Leaves + "', "
                "EditFinance = '" + Finance + "', "
                "EditAttendance = '" + Attendance + "', "
                "EditPayroll = '" + Payroll + "', "
                "FullName = '" + ui->FullName->text() + "' WHERE UserID = '" + currentID + "'");

    if (save.lastError().isValid()) {

    }
    ui->Delete->setEnabled(true);
    loadUsers();
}

void Admin::on_Delete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this user?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        db.exec("DELETE FROM users WHERE UserID = '" + currentID + "'");
        if (!db.lastError().isValid()) {
            clearTexts();
            loadUsers();
            ui->Delete->setEnabled(false);
            on_SaveAndNew_clicked();
        }
    }
}

void Admin::on_treeView_clicked(const QModelIndex &index)
{
    clearTexts();
    currentID = model->record(index.row()).value(0).toString();
    isAdding = false;
    ui->Delete->setEnabled(true);

    QString HR = "No";
    QString Finance = "No";
    QString Leaves = "No";
    QString Payroll = "No";
    QString Attendance = "No";

    QSqlQuery qu = db.exec("SELECT * FROM users WHERE UserID = '" + currentID   + "'");
    if (!qu.lastError().isValid()) {
        qu.next();
        QSqlRecord rec = qu.record();
        ui->LoginName->setText(rec.value("LoginName").toString());
        ui->Password->setText(rec.value("Password").toString());
        ui->FullName->setText(rec.value("FullName").toString());
        HR = rec.value("EditHR").toString();
        Finance = rec.value("EditFinance").toString();
        Leaves = rec.value("EditLeaves").toString();
        Attendance = rec.value("EditAttendance").toString();
        Payroll = rec.value("EditPayroll").toString();

        if (HR == "Yes")
            ui->EditHR->setChecked(true);

        if (Finance == "Yes")
            ui->EditFinance->setChecked(true);

        if (Leaves == "Yes")
            ui->EditLeaves->setChecked(true);

        if (Attendance == "Yes")
            ui->EditAttendance->setChecked(true);

        if (Payroll == "Yes")
            ui->EditPayroll->setChecked(true);
    }
}

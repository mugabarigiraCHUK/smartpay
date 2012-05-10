#include "saccos.h"
#include "ui_saccos.h"

Saccos::Saccos(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::Saccos)
{
    ui->setupUi(this);
    db = database;
    model = new QSqlQueryModel(this);
    ui->treeView->setModel(model);
    reload();
    isAdding = true;
    on_SaveAndNew_clicked();
}

Saccos::~Saccos()
{
    delete ui;
}

void Saccos::reload()
{
    model->setQuery("SELECT SaccoID, SaccoName FROM saccos");
    ui->treeView->setColumnHidden(0, true);
}

void Saccos::clearTexts()
{
    ui->SaccoName->setText("");
    ui->MinimumContribution->setValue(0);
    ui->Description->setPlainText("");
}

void Saccos::on_SaveAndNew_clicked()
{
    if (!isAdding)
        on_Save_clicked();
    isAdding = true;
    clearTexts();
    ui->Delete->setEnabled(false);
}

void Saccos::on_Save_clicked()
{
    if (isAdding) {
        QSqlQuery qu = db.exec("INSERT INTO saccos (SaccoName) VALUES ('" + ui->SaccoName->text() + "')");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
        currentID = qu.lastInsertId().toString();
        isAdding = false;
        ui->Delete->setEnabled(true);
    }

    QSqlQuery saveQu = db.exec("UPDATE saccos SET SaccoName = '" + ui->SaccoName->text() + "', "
            "Description = '" + ui->Description->toPlainText()  + "', "
            "MinimumContribution = '" + QString::number(ui->MinimumContribution->value()) + "'"
            " WHERE saccoID = '" + currentID + "'");
    if (saveQu.lastError().isValid()) {
        QMessageBox::critical(this, "Error", saveQu.lastError().text());
        return;
    }

    reload();
}

void Saccos::on_Delete_clicked()
{

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this sacco?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QSqlQuery qu = db.exec("DELETE FROM saccos WHERE SaccoID = '" + currentID + "'");
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

void Saccos::on_treeView_clicked(const QModelIndex &index)
{
    currentID = model->record(index.row()).value(0).toString();
    QSqlQuery qu = db.exec("SELECT * FROM saccos WHERE SaccoID = '" + currentID + "'");
    clearTexts();
    while (qu.next()) {
        QSqlRecord rec = qu.record();
        ui->SaccoName->setText(rec.value("SaccoName").toString());
        ui->Description->setPlainText(rec.value("Description").toString());
        ui->MinimumContribution->setValue(rec.value("MinimumContribution").toInt());
    }
    ui->Delete->setEnabled(true);
    isAdding = false;
}

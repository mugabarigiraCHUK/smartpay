#include "jobtitles.h"
#include "ui_jobtitles.h"

JobTitles::JobTitles(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::JobTitles)
{
    ui->setupUi(this);
    db = database;
    reload();
    on_cmdAddNew_clicked();
}

JobTitles::~JobTitles()
{
    delete ui;
}

void JobTitles::reload()
{
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM jobtitles", db);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

void JobTitles::clearTexts()
{
    ui->txtDescription->setText("");
    ui->txtJobTitle->setText("");
}

void JobTitles::on_cmdAddNew_clicked()
{
    clearTexts();
    isAdding = true;
    ui->cmdDelete->setEnabled(false);
}

void JobTitles::on_cmdSave_clicked()
{
    if (isAdding) {
        QSqlQuery insQu = db.exec("INSERT INTO jobtitles (JobTitle, Description) VALUES ('" + ui->txtJobTitle->text() + "', '" + ui->txtDescription->text() + "')");

        if (!insQu.lastError().isValid()) {
            currentID = insQu.lastInsertId().toString();
            isAdding = false;
            reload();
        } else {
            QMessageBox::critical(this, "Database Error", insQu.lastError().text());
            return;
        }
    } else {
        db.exec("UPDATE jobtitles SET JobTitle = '" + ui->txtJobTitle->text() + "', Description = '" + ui->txtDescription->text() + "' WHERE JobTitleID = '" + currentID + "'");

        if (db.lastError().isValid()) {
            QMessageBox::critical(this, "Database Error", db.lastError().text());
            return;
        } else {
            reload();
        }
    }
    ui->cmdDelete->setEnabled(true);
}

void JobTitles::on_treeView_clicked(const QModelIndex &index)
{
    ui->txtJobTitle->setText("");
    ui->txtDescription->setText("");
    currentID = model->record(index.row()).value(0).toString();
    ui->txtJobTitle->setText(model->record(index.row()).value(1).toString());
    ui->txtDescription->setText(model->record(index.row()).value(2).toString());
    isAdding = false;
     ui->cmdDelete->setEnabled(true);
}

void JobTitles::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete " + ui->txtJobTitle->text() + "?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        db.exec("DELETE FROM jobtitles WHERE JobTitleID = '" + currentID + "'");
        reload();
        on_cmdAddNew_clicked();
    }
}

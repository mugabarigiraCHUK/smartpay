#include "selectemployee.h"
#include "ui_selectemployee.h"

SelectEmployee::SelectEmployee(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::SelectEmployee)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_employeenames", database);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

SelectEmployee::~SelectEmployee()
{
    delete ui;
}

void SelectEmployee::on_treeView_doubleClicked(const QModelIndex &index)
{
    this->accept();
}


void SelectEmployee::on_treeView_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    selectedEmployeeName = ui->treeView->model()->index(ui->treeView->currentIndex().row(), 0).data().toString();
    selectedEmployeeName = ui->treeView->model()->index(ui->treeView->currentIndex().row(), 2).data().toString();
}

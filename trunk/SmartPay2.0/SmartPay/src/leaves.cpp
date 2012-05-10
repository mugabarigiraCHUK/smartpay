#include "leaves.h"
#include "ui_leaves.h"

Leaves::Leaves(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Leaves)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_employeenames", database);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
    ui->treeView->setColumnHidden(1, true);
}

Leaves::~Leaves()
{
    delete ui;
}

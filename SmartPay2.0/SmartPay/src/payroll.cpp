#include "payroll.h"
#include "ui_payroll.h"
#include "publics.h"

Payroll::Payroll(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Payroll)
{
    ui->setupUi(this);
    db = database;
    ui->widget->db = db;
    ui->widget_2->db = db;
    reloadMonths();
}

Payroll::~Payroll()
{
    delete ui;
}

void Payroll::reloadMonths()
{
    Publics::loadDbToComboBox(db, "SELECT * FROM vw_monthyear", "Month", ui->comboBox);
}

void Payroll::loadPayroll()
{
    model = new QSqlQueryModel(this);
    fModel = new QSortFilterProxyModel(model);
    model->setQuery("SELECT * FROM vw_payroll WHERE MonthID = '" + monthID + "'", db);
    fModel->setSourceModel(model);
    fModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    fModel->setFilterKeyColumn(-1);
    fModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->lstPayroll->setModel(fModel);
    ui->lstPayroll->setColumnHidden(0, true);


    ui->widget->loadReport("Payroll", monthID);
    ui->widget_2->loadReport("Payslips4x1", monthID);
}

void Payroll::on_comboBox_currentIndexChanged(const QString &arg1)
{
    monthID = Publics::getDbValue(db, "SELECT * FROM vw_monthyear WHERE Month = '" + arg1 + "'", "MonthID");
    loadPayroll();
}

void Payroll::on_Recalculate_clicked()
{
    db.exec("CALL RecalculatePayroll ('" + monthID + "')");
    if (db.lastError().isValid())
    {
        QMessageBox::critical(this, "Error", db.lastError().text());
        return ;
    }
    loadPayroll();
}

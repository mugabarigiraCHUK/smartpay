#include "employees.h"
#include "ui_employees.h"
#include "issueadvance.h"
#include "publics.h"
Employees::Employees(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Employees)
{
    ui->setupUi(this);
    isAclick  = false;
    ui->toolBar->setStyleSheet("QToolButton { border-image: url(:/images/panel_button.png) 2 2 2 19;"
                               " border-width: 2px 2px 2px 19px; padding-left: -17; padding-right: 4 } "
                               "QToolButton:checked { border-image: url(:/images/panel_button_checked.png) 2 2 2 19 } "
                               "QToolButton::menu-indicator { width:0; height:0 }"
                           #ifndef Q_WS_MAC // Mac UIs usually don't hover
                               "QToolButton:checked:hover { border-image: url(:/images/panel_button_checked_hover.png) 2 2 2 19 } "
                               "QToolButton:pressed:hover { border-image: url(:/images/panel_button_pressed.png) 2 2 2 19 } "
                               "QToolButton:hover { border-image: url(:/images/panel_button_hover.png) 2 2 2 19 } "
                           #endif
                               );

    db = database;

    model = new QSqlQueryModel(this);
    f_model = new QSortFilterProxyModel(model);
    f_model->setSourceModel(model);
    f_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    f_model->setSortCaseSensitivity(Qt::CaseInsensitive);
    f_model->setFilterKeyColumn(-1);
    ui->treeView->setModel(f_model);
    connect (ui->lineEdit, SIGNAL(textChanged(QString)), f_model, SLOT(setFilterWildcard(QString)));
    reload();

    clearTexts();
    loadCombos();

    on_actionAdd_New_triggered();
}

Employees::~Employees()
{
    delete ui;
}

void Employees::hideFinance()
{
    ui->BasicPay->setVisible(false);
    ui->label_5->setVisible(false);
    ui->HouseAllowance->setVisible(false);
    ui->label_6->setVisible(false);
}

void Employees::hideHR()
{
    ui->HrTab->setVisible(false);
}

void Employees::on_actionAdd_New_triggered()
{
    clearTexts();
    isAdding = true;
    ui->actionDeactivate->setEnabled(false);
    ui->actionIssue_Advance->setEnabled(false);
    ui->actionSave->setEnabled(true);
    ui->tab_3->setEnabled(false);
    ui->tab_4->setEnabled(false);
}

void Employees::reload()
{
    QString query = "SELECT * FROM vw_employeenames";
    if (ui->ShowInactive->checkState() == Qt::Checked)
        query = "SELECT * FROM vw_employeenames_all";
    model->setQuery(query,  db);
    ui->treeView->setModel(f_model);
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->setColumnHidden(0, true);
}

void Employees::reloadTrees()
{
    reloadAdvances();
    reloadSaccos();
}

void Employees::reloadAdvances()
{
    advancesModel = new QSqlQueryModel(this);
    advancesModel->setQuery("SELECT * FROM vw_advancesByEmployeeID WHERE EmployeeID = '" + currentID  + "'", db);
    ui->AdvancesTree->setModel(advancesModel);
    ui->AdvancesTree->setColumnHidden(0, true);
    ui->AdvancesTree->setColumnHidden(1, true);
}

void Employees::reloadSaccos()
{
    saccoModel = new QSqlQueryModel(this);
    saccoModel->setQuery("SELECT * FROM vw_employee_sacco_membership WHERE EmployeeID = '" + currentID + "'");
    ui->SaccoTree->setModel(saccoModel);
    ui->SaccoTree->setColumnHidden(0, true);
    ui->SaccoTree->setColumnHidden(1, true);
    ui->SaccoTree->setColumnHidden(2, true);
}

void Employees::loadSaccoList()
{
    ui->SaccoList->clear();
    QSqlQuery saccoQuery = db.exec("SELECT SaccoName FROM saccos");
    while (saccoQuery.next()) {
        ui->SaccoList->insertItem(ui->SaccoList->count(), saccoQuery.value(0).toString());
    }
}

void Employees::clearLineEdits(QObject *parent)
{
    for (int i = 0; i < parent->children().count(); i++) {
        if ( qobject_cast<QLineEdit *>(parent->children().at(i)) ) {
            QLineEdit *t = qobject_cast<QLineEdit *>(parent->children().at(i));
            t->setText("");
        } else if ( qobject_cast<QGroupBox *>(parent->children().at(i)) ) {
            QGroupBox *g = qobject_cast<QGroupBox *>(parent->children().at(i));
            clearLineEdits(g);
        }
    }
}

void Employees::clearTexts()
{
    clearLineEdits(ui->HrTab);
    clearLineEdits(ui->FinanceTab);
    clearLineEdits(ui->tab_3);
    clearLineEdits(ui->tab_4);
    ui->SaccoMonthlyContribution->setValue(0);
}

void Employees::loadCombos()
{
    QSqlQuery departmentsQuery = db.exec("SELECT DepartmentName FROM departments");
    QSqlQuery jobTitlesQuery = db.exec("SELECT JobTitle FROM JobTitles");
    QSqlQuery employeeQuery = db.exec("SELECT Name FROM vw_employeeNames");


    ui->Department->clear();
    ui->JobTitle->clear();
    ui->Supervisor->clear();

    while (departmentsQuery.next()) {
        ui->Department->insertItem(ui->Department->count(), departmentsQuery.value(0).toString());
    }

    while (jobTitlesQuery.next()) {
        ui->JobTitle->insertItem(ui->JobTitle->count(), jobTitlesQuery.value(0).toString());
    }

    while (employeeQuery.next()) {
        ui->Supervisor->insertItem(ui->Supervisor->count(), employeeQuery.value(0).toString());
    }

    loadSaccoList();
}

void Employees::edit(QString employeeID)
{
    currentID = employeeID;
    clearTexts();
    QSqlQuery hrQuery = db.exec("SELECT * FROM employees_hr WHERE EmployeeID = '" + employeeID + "'");
    QSqlQuery financeQuery = db.exec("SELECT * FROM employees_finance WHERE EmployeeID = '" + employeeID + "'");
    ui->actionDeactivate->setEnabled(true);
    ui->actionIssue_Advance->setEnabled(true);
    ui->tab_3->setEnabled(true);
    ui->tab_4->setEnabled(true);
    loadCombos();
    while (hrQuery.next()) {
        QSqlRecord rec = hrQuery.record();
        ui->EmployeeNo->setText(rec.value("EmployeeNo").toString());
        ui->FirstName->setText(rec.value("FirstName").toString());
        ui->OtherNames->setText(rec.value("OtherNames").toString());
        ui->IDNo->setText(rec.value("IDNo").toString());
        ui->PINNo->setText(rec.value("PINNo").toString());
        ui->NSSFNo->setText(rec.value("NSSFNo").toString());
        ui->NHIFNo->setText(rec.value("NHIFNo").toString());
        ui->Address->setText(rec.value("Address").toString());
        ui->Tel->setText(rec.value("Tel").toString());
        ui->Name->setText(rec.value("NextOfKin").toString());
        ui->Relationship->setText(rec.value("NextOfKinRelationship").toString());
        ui->Tel_2->setText(rec.value("NextOfKinTel").toString());
        QString employmentType = rec.value("EmploymentType").toString();

        for (int e = 0; e < ui->comboBox->count(); e++) {
            if (ui->comboBox->itemText(e) == employmentType)
                ui->comboBox->setCurrentIndex(e);
        }

        if (rec.value("IsActive").toString() == "No") {
            ui->actionDeactivate->setText("3   Activate");
        } else {
            ui->actionDeactivate->setText("3   Deactivate");
        }

        ui->DateOfBirth->setDate(QDate::fromString(rec.value("DateOfBirth").toString(), "yyyy-MM-dd"));
        ui->DateEmployed->setDate(QDate::fromString(rec.value("DateEmployed").toString(), "yyyy-MM-dd"));

        QString departmentID = rec.value("DepartmentID").toString();
        QString jobTitleID = rec.value("JobTitleID").toString();
        QString supervisorID =  rec.value("SupervisorID").toString();

        QString departmentName = Publics::getDbValue(db, "SELECT * FROM departments WHERE DepartmentID = '" + departmentID + "'", "DepartmentName");
        QString jobTitle = Publics::getDbValue(db, "SELECT * FROM JobTitles WHERE JobTitleID = '" + jobTitleID + "'", "JobTitle");
        QString supervisor = Publics::getDbValue(db, "SELECT * FROM vw_employeenames WHERE EmployeeID = '" + supervisorID + "'", "Name");

        for (int d = 0; d < ui->Department->count(); d++) {
            if (ui->Department->itemText(d) == departmentName)
                ui->Department->setCurrentIndex(d);
        }

        for (int j = 0; j < ui->Department->count(); j++) {
            if (ui->JobTitle->itemText(j) == jobTitle)
                ui->JobTitle->setCurrentIndex(j);
        }

        for (int s = 0; s < ui->Supervisor->count(); s++) {
            if (ui->Supervisor->itemText(s) == supervisor)
                ui->Supervisor->setCurrentIndex(s);
        }
    }

    while (financeQuery.next()) {
        QSqlRecord rec = financeQuery.record();
        ui->BasicPay->setText(rec.value("BasicPay").toString());
        ui->HouseAllowance->setText(rec.value("HouseAllowance").toString());
        ui->BankName->setText(rec.value("BankName").toString());
        ui->BankBranch->setText(rec.value("BankBranch").toString());
        ui->AccountName->setText(rec.value("AccountName").toString());
        ui->AccountNo->setText(rec.value("AccountNo").toString());
        ui->PaymentMethod->setEditText(rec.value("PaymentMethod").toString());
    }

    reloadTrees();
}

void Employees::addNew(QString employeeNo)
{
    QSqlQuery insertQuery = db.exec("INSERT INTO employees_hr (EmployeeNo) VALUES ('" + employeeNo + "')");
    if (!insertQuery.lastError().isValid()) {
        currentID = insertQuery.lastInsertId().toString();
        isAdding = false;
        reload();
        ui->actionDeactivate->setEnabled(true);
        ui->actionIssue_Advance->setEnabled(true);
        ui->tab_3->setEnabled(true);
        ui->tab_4->setEnabled(true);
        saveChanges();
    } else {
        //TODO: INSERT ERROR
    }
}

bool Employees::saveChanges(QString err)
{
    QString departmentID = Publics::getDbValue(db, "SELECT * FROM departments WHERE DepartmentName = '" + ui->Department->currentText() + "'", "DepartmentID");
    QString jobTitleID = Publics::getDbValue(db, "SELECT * FROM JobTitles WHERE JobTitle = '" + ui->JobTitle->currentText() + "'", "JobTitleID");
    QString supervisorID = Publics::getDbValue(db, "SELECT * FROM vw_employeenames WHERE name = '" + ui->Supervisor->currentText() + "'", "EmployeeID");

    if (isAdding) {
        if (ui->EmployeeNo->text().trimmed() == "") {
            if (!isAclick)
                QMessageBox::warning(this, "", "Please enter an employee number");
            err = "No Employee Number";
            return false;
        } else {
            addNew(ui->EmployeeNo->text());
        }
    } else {
        //Save
        db.exec("UPDATE employees_hr SET FirstName = '" + ui->FirstName->text() + "', "
                "OtherNames = '" + ui->OtherNames->text()  + "', "
                "IDNo = '" + ui->IDNo->text()  + "', "
                "PINNo = '" + ui->PINNo->text()  + "', "
                "NSSFNo = '" + ui->NSSFNo->text()  + "', "
                "EmployeeNo = '" + ui->EmployeeNo->text()  + "', "
                "NHIFNo = '" + ui->NHIFNo->text()  + "', "
                "Address = '" + ui->Address->text()  + "', "
                "Tel = '" + ui->Tel->text()  + "', "
                "DateOfBirth = '" + ui->DateOfBirth->date().toString("yyyy-MM-dd") + "', "
                "DateEmployed = '" + ui->DateEmployed->date().toString("yyyy-MM-dd") + "', "
                "NextOfKin = '" + ui->Name->text()  + "', "
                "NextOfKinRelationship = '"  + ui->Relationship->text()  + "', "
                "NextOfKinTel = '" + ui->Tel_2->text()  + "', "
                "EmploymentType = '" + ui->comboBox->currentText() + "', "
                "Status = 'Active'"
                " WHERE EmployeeID = '" + currentID + "'");

        if (db.lastError().isValid()) {
            err = db.lastError().text();
            return false;
        }

        db.exec("UPDATE employees_hr SET DepartmentID = '" + departmentID + "' "
                "WHERE EmployeeID = '" + currentID + "'");
        db.exec("UPDATE employees_hr SET SupervisorID = '" + supervisorID + "' "
                "WHERE EmployeeID = '" + currentID + "'");
        db.exec("UPDATE employees_hr SET JobTitleID = '" + jobTitleID + "' "
                "WHERE EmployeeID = '" + currentID + "'");

        db.exec("UPDATE employees_finance SET BasicPay = '" + ui->BasicPay->text() + "', "
                " HouseAllowance = '" + ui->HouseAllowance->text() + "', "
                " PaymentMethod = '" + ui->PaymentMethod->currentText() + "', "
                " BankName = '" + ui->BankName->text() + "', "
                " BankBranch = '" + ui->BankName->text() + "', "
                " AccountName = '" + ui->AccountName->text() + "', "
                " AccountNo = '" + ui->AccountNo->text() + "' WHERE EmployeeID = '" + currentID + "'");

        if (db.lastError().isValid()) {
            err = db.lastError().text();
            return false;
        }

        if (!isAclick)
            reload();
    }
    err = "";
    return true;

    if (!isAclick)
        reload();
}

void Employees::on_actionSave_triggered()
{
    QString err = QString();

    if (saveChanges(err))
        return;

    if (!isAclick)
        QMessageBox::critical(this, "Error", err);
}

void Employees::on_treeView_clicked(const QModelIndex &index)
{
    isAclick = true;
    on_actionSave_triggered();
    isAclick  = false;
    QModelIndex ind = f_model->index(index.row(), 0);
    QString editID = f_model->data(ind).toString();
    edit(editID);
    isAdding = false;
}

void Employees::on_actionIssue_Advance_triggered()
{
    IssueAdvance gad(this, db, currentID.toInt());
    if (gad.exec()) {
        reloadAdvances();
    }
}

void Employees::on_AddAdvance_clicked()
{
    on_actionIssue_Advance_triggered();
}

void Employees::on_DeleteAdvance_clicked()
{
    if (advancesModel->rowCount() < 1)
        return;
    QString advanceID = advancesModel->record(ui->AdvancesTree->currentIndex().row()).value("AdvanceID").toString();

    if (advanceID.trimmed().length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this advance?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM employee_advances WHERE advanceID = '" + advanceID + "'");
            reloadAdvances();
        }
    }
}

void Employees::on_NewSacco_clicked()
{
    if (!isSaccoAdding)
        on_SaveSacco_clicked();

    ui->SaccoList->setCurrentIndex(0);
    ui->SaccoMonthlyContribution->setValue(0);
    ui->SaccoDateJoined->setDate(QDate::currentDate());
    isSaccoAdding = true;
}

void Employees::on_SaveSacco_clicked()
{
    Publics p;
    QString saccoID = p.getDbValue(db, "SELECT * FROM saccos WHERE SaccoName = '" + ui->SaccoList->currentText() + "'", "SaccoID");

    if (ui->SaccoList->count() < 1)
    {
        QMessageBox::critical(this, "Error", "No saccos found,\nPlease add some saccos first.");
        return;
    }

    if (isSaccoAdding) {
        QSqlQuery qu = db.exec("INSERT INTO employees_saccos (EmployeeID) VALUES ('" + currentID + "')");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
        currentSaccoID = qu.lastInsertId().toString();
        isSaccoAdding = false;
        ui->RemoveSacco->setEnabled(true);
    }

    QSqlQuery saveQu = db.exec("UPDATE employees_saccos SET "
                               " SaccoID = '" + saccoID + "', "
                               " EmployeeID = '" + currentID + "', "
                               " DateJoined = '" + ui->SaccoDateJoined->date().toString("yyyy-MM-dd")  + "', "
                               " MonthlyContribution = '" + QString::number(ui->SaccoMonthlyContribution->value()) + "' "
                               " WHERE EntryID = '" + currentSaccoID + "'");
    if (saveQu.lastError().isValid()) {
        QMessageBox::critical(this, "Error", saveQu.lastError().text());
        return;
    }

    reloadSaccos();
}

void Employees::on_RemoveSacco_clicked()
{
    if (saccoModel->rowCount() < 1) {
        QMessageBox::critical(this, "Error", "Nothing to delete.");
        return;
    }

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::No) {
        return;
    }

    db.exec("DELETE FROM employees_saccos WHERE EntryID = '" + currentSaccoID + "'");

    reloadSaccos();
}

void Employees::on_SaccoTree_clicked(const QModelIndex &index)
{
    currentSaccoID = saccoModel->record(index.row()).value(0).toString();
    QSqlQuery saccoQu = db.exec("SELECT * FROM employees_saccos WHERE EntryID = '" + currentSaccoID + "'");
    if (!saccoQu.lastError().isValid()) {
        while (saccoQu.next()) {
            isSaccoAdding = false;
            QString saccoName = Publics::getDbValue(db, "SELECT * FROM saccos WHERE SaccoID = '" + saccoQu.record().value("SaccoID").toString() + "'", "SaccoName");
            double contrib = saccoQu.record().value("MonthlyContribution").toDouble();
            QDate dT = saccoQu.record().value("DateJoined").toDate();

            ui->SaccoMonthlyContribution->setValue(contrib);
            ui->SaccoDateJoined->setDate(dT);
            loadSaccoList();
            for (int i = 0; i < ui->SaccoList->count(); i++) {
                if (ui->SaccoList->itemText(i) == saccoName)
                    ui->SaccoList->setCurrentIndex(i);
            }
        }
    }
}

void Employees::on_actionDeactivate_triggered()
{
    QString query = "UPDATE employees_hr SET IsActive = 'Yes' WHERE EmployeeID = '" + currentID + "'";
    if (ui->actionDeactivate->text() == "3   Deactivate")
        query = "UPDATE employees_hr SET IsActive = 'No' WHERE EmployeeID = '" + currentID + "'";
    db.exec(query);
    reload();
}

void Employees::on_ShowInactive_toggled(bool checked)
{
    Q_UNUSED(checked);
    reload();
}

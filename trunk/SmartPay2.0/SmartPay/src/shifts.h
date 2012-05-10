#ifndef SHIFTS_H
#define SHIFTS_H

#include <QtGui>
#include <QtSql>

namespace Ui {
class Shifts;
}

class Shifts : public QWidget
{
    Q_OBJECT
    
public:
    explicit Shifts(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Shifts();
    QString currentID;
private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_SaveAndNew_clicked();

    void on_Save_clicked();

    void on_Delete_clicked();

private:
    Ui::Shifts *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    void reload();
    bool isAdding;
    void clearTexts();
};

#endif // SHIFTS_H

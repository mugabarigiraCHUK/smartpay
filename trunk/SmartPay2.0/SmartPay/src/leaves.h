#ifndef LEAVES_H
#define LEAVES_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Leaves;
}

class Leaves : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Leaves(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Leaves();
    
private:
    Ui::Leaves *ui;
};

#endif // LEAVES_H

#ifndef HOLIDAYS_H
#define HOLIDAYS_H

#include <QWidget>

namespace Ui {
class Holidays;
}

class Holidays : public QWidget
{
    Q_OBJECT
    
public:
    explicit Holidays(QWidget *parent = 0);
    ~Holidays();
    
private:
    Ui::Holidays *ui;
};

#endif // HOLIDAYS_H

#ifndef PUBLICS_H
#define PUBLICS_H

#include <QtGui>
#include <QtSql>

class Publics
{
public:
    Publics();
    static QString getDbValue(QSqlDatabase db, QString query, QString returnCol);
    static void loadDbToComboBox(QSqlDatabase db, QString Query, QString col, QComboBox *cbo);
    static QString getDateString(QDate dt);
};

#endif // PUBLICS_H

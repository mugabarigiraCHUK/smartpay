#include "publics.h"

Publics::Publics()
{
}

QString Publics::getDbValue(QSqlDatabase db, QString query, QString returnCol)
{
    QSqlQuery qu = db.exec(query);
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QSqlRecord rec = qu.record();
            return rec.value(returnCol).toString();
        }
    }
    return "";
}

void Publics::loadDbToComboBox(QSqlDatabase db, QString Query, QString col, QComboBox *cbo)
{
    QSqlQuery qu = db.exec(Query);
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QSqlRecord rec = qu.record();
            cbo->addItem(rec.value(col).toString());
        }
    }
}

QString Publics::getDateString(QDate dt)
{
    return dt.toString("yyyy-MM-dd");
}

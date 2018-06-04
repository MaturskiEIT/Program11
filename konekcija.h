#ifndef KONEKCIJA_H
#define KONEKCIJA_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>


class Konekcija
{
public:
    Konekcija();
    bool dbOpen();
    void dbClose();

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPutanja = "C:/Users/family/Documents/Prosveta/Matura EIT 2018/b11.db";  // Obavezno podesiti adresu baze!!!
};

#endif // KONEKCIJA_H

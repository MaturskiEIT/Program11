#include "konekcija.h"

Konekcija::Konekcija()
{

}

bool Konekcija::dbOpen()
{
    QFileInfo datoteka(Konekcija::dbPutanja);

    if(datoteka.exists() && datoteka.isFile())
    {
        db.setDatabaseName(dbPutanja);
        if(!db.open())
        {
            qDebug() << "Nismo ostvarili povezivanje na bazu podataka!";
            return false;
        }
        QSqlQuery upit;
        if(!upit.exec("PRAGMA foreign_key = ON;"))
        {
            qDebug() << "Ne radi foreign key!";
            return false;
        }
        else
        {
            qDebug() << "Uspesno ostvareno povezivanje na bazu podataka!";
            return true;
        }
    }
    else
    {
        qDebug() << "Ne postoji trazena baza podataka!";
        return false;
    }

}

void Konekcija::dbClose()
{
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

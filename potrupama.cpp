#include "potrupama.h"
#include "ui_potrupama.h"
#include "konekcija.h"
#include <QMessageBox>

PoTrupama::PoTrupama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoTrupama)
{
    ui->setupUi(this);

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT NazivTrupe FROM Pozorisna_Trupa ORDER BY NazivTrupe;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxTrupa->setModel(model);
        }
    }
    baza.dbClose();
}

PoTrupama::~PoTrupama()
{
    delete ui;
}

void PoTrupama::on_pushButtonIzadji_clicked()
{
    this->close();
}

void PoTrupama::on_pushButtonPrikazi_clicked()
{
    QString nazivTrupe = ui->comboBoxTrupa->currentText();

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT Glumac.GlumacID AS Sifra, Glumac.Ime, Glumac.Prezime FROM Glumac INNER JOIN Pozorisna_Trupa ON Glumac.TrupaID = Pozorisna_Trupa.TrupaID WHERE Pozorisna_Trupa.NazivTrupe = :nazivTrupe ORDER BY Glumac.GlumacID ASC;");
        upit.bindValue(":nazivTrupe", nazivTrupe);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->tableViewGlumci->setModel(model);
        }

        upit.prepare("SELECT Pozorisni_Komad.Naziv AS Komad, Pozorisni_Komad.Trajanje AS [Trajanje/min], COUNT (Predstava.KomadID) AS [Odigrano puta] FROM Predstava INNER JOIN Pozorisni_Komad ON Predstava.KomadID = Pozorisni_Komad.KomadID INNER JOIN Pozorisna_Trupa ON Predstava.TrupaID = Pozorisna_Trupa.TrupaID WHERE Pozorisna_Trupa.NazivTrupe = :nazivTrupe GROUP BY Predstava.KomadID;");
        upit.bindValue(":nazivTrupe", nazivTrupe);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->tableViewKomadi->setModel(model);
        }
    }
    baza.dbClose();
}

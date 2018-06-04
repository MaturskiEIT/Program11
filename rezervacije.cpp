#include "rezervacije.h"
#include "ui_rezervacije.h"
#include "konekcija.h"
#include <QMessageBox>

Rezervacije::Rezervacije(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rezervacije)
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

        upit.prepare("SELECT KomadID, Naziv FROM Pozorisni_Komad ORDER BY KomadID;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QStringList listaKomada;
            while(upit.next())
            {
                listaKomada.append(upit.value(0).toString() + " - " + upit.value(1).toString());
            }
            QStringListModel *model;
            model = new QStringListModel();
            model->setStringList(listaKomada);
            ui->comboBoxKomad->setModel(model);
        }
    }
    baza.dbClose();
}

Rezervacije::~Rezervacije()
{
    delete ui;
}

void Rezervacije::on_pushButtonIzadji_clicked()
{
    this->close();
}

void Rezervacije::on_pushButtonIzvrsi_clicked()
{
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QString sifraRezervacije = ui->lineEditSifraRezervacije->text();
        int redniBrojRezervacije;

        QSqlQuery upit;

        upit.prepare("SELECT MAX(RBR) FROM Stavke_Rezervacije WHERE RezervacijaId = :sifraRezervacije;");
        upit.bindValue(":sifraRezervacije", sifraRezervacije);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            redniBrojRezervacije = upit.value(0).isNull()?0:upit.value(0).toInt();
        }

        bool izborAkcijeUpisi = ui->radioButtonUpisi->isChecked();

        if(izborAkcijeUpisi)
        {
            QString komadID = ui->comboBoxKomad->currentText();
            komadID.truncate(komadID.indexOf(" - "));
            QString brojSedista = ui->lineEditBrojSedista->text();
            QString datum = ui->calendarWidgetDatum->selectedDate().toString(Qt::TextDate);
            redniBrojRezervacije++;
            QString rbr = QString::number(redniBrojRezervacije);

            upit.prepare("INSERT INTO Stavke_Rezervacije(RezervacijaID, RBR, KomadID, Datum, KolikoSedista) VALUES (:sifraRezervacije, :rbr, :komadID, :datum, :brojSedista);");
            upit.bindValue(":sifraRezervacije", sifraRezervacije);
            upit.bindValue(":rbr", rbr);
            upit.bindValue(":komadID", komadID);
            upit.bindValue(":datum", datum);
            upit.bindValue(":brojSedista", brojSedista);

            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QMessageBox::information(this, "Uspesno!!!", "Nova rezervacija je uspesno prijavljena!!!");
                ui->lineEditRedniBrojRezervacije->setText(QString::number(redniBrojRezervacije));
            }
        }
        else if(redniBrojRezervacije > 0)
        {
            QString rbr = QString::number(redniBrojRezervacije);

            upit.prepare("DELETE FROM Stavke_Rezervacije WHERE RezervacijaId = :sifraRezervacije AND RBR = :rbr;");
            upit.bindValue(":sifraRezervacije", sifraRezervacije);
            upit.bindValue(":rbr", rbr);

            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QMessageBox::information(this, "Uspesno!!!", "Rezervacija je uspesno obrisana!!!");
                ui->lineEditRedniBrojRezervacije->setText(QString::number(redniBrojRezervacije - 1));
            }
        }
    }
    baza.dbClose();
}

void Rezervacije::on_lineEditSifraRezervacije_editingFinished()
{
    QString sifraRezervacije = ui->lineEditSifraRezervacije->text();
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT Rezervacija.DatumRezervisanja, Pretplatnik.Ime, Pretplatnik.Prezime FROM Rezervacija INNER JOIN Pretplatnik ON Rezervacija.PretplatnikID = Pretplatnik.PretplatnikID WHERE Rezervacija.RezervacijaId = :sifraRezervacije;");
        upit.bindValue(":sifraRezervacije", sifraRezervacije);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            ui->labelDatumRezervacije->setText(upit.value(0).toString());
            ui->labelImeIPrezimeRezervacije->setText(upit.value(1).toString() + " " + upit.value(2).toString());
        }

        upit.prepare("SELECT MAX(RBR) FROM Stavke_Rezervacije WHERE RezervacijaId = :sifraRezervacije;");
        upit.bindValue(":sifraRezervacije", sifraRezervacije);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            ui->lineEditRedniBrojRezervacije->setText(QString::number(upit.value(0).isNull()?0:upit.value(0).toInt()));
        }
    }
    baza.dbClose();
}

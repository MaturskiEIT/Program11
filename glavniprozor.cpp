#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "konekcija.h"
#include "rezervacije.h"
#include "potrupama.h"

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this->close();
}

void GlavniProzor::on_actionRezervacije_triggered()
{
    Rezervacije *rez = new Rezervacije(this);
    rez->setModal(true);
    rez->show();
}

void GlavniProzor::on_actionPo_trupama_triggered()
{
    PoTrupama *pt = new PoTrupama(this);
    pt->setModal(true);
    pt->show();
}

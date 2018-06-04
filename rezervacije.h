#ifndef REZERVACIJE_H
#define REZERVACIJE_H

#include <QDialog>

namespace Ui {
class Rezervacije;
}

class Rezervacije : public QDialog
{
    Q_OBJECT

public:
    explicit Rezervacije(QWidget *parent = 0);
    ~Rezervacije();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonIzvrsi_clicked();

    void on_lineEditSifraRezervacije_editingFinished();

private:
    Ui::Rezervacije *ui;
};

#endif // REZERVACIJE_H

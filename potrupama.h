#ifndef POTRUPAMA_H
#define POTRUPAMA_H

#include <QDialog>

namespace Ui {
class PoTrupama;
}

class PoTrupama : public QDialog
{
    Q_OBJECT

public:
    explicit PoTrupama(QWidget *parent = 0);
    ~PoTrupama();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonPrikazi_clicked();

private:
    Ui::PoTrupama *ui;
};

#endif // POTRUPAMA_H

#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H

#include <QMainWindow>

namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

private slots:
    void on_actionIzlaz_triggered();

    void on_actionRezervacije_triggered();

    void on_actionPo_trupama_triggered();

private:
    Ui::GlavniProzor *ui;
};

#endif // GLAVNIPROZOR_H

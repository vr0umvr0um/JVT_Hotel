#ifndef LISTECHAMBRESDIALOG_H
#define LISTECHAMBRESDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

using namespace std;

namespace Ui {
class listeChambresDialog;
}

class listeChambresDialog : public QDialog
{
    Q_OBJECT

public:
    listeChambresDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    ~listeChambresDialog();
    void Afficherchambres();

private slots:
    void on_account_clicked();

    void on_pushButton_ValiderResa_clicked();

    void on_accueil_clicked();

private:
    Ui::listeChambresDialog *ui;
    QSqlDatabase db;
    QString ut, ma, md;
};

#endif // LISTECHAMBRESDIALOG_H

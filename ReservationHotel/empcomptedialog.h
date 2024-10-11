#ifndef EMPCOMPTEDIALOG_H
#define EMPCOMPTEDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDialog>

#include "employedao.h"

using namespace std;

namespace Ui {
class EmpCompteDialog;
}

class EmpCompteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmpCompteDialog(QWidget *parent = nullptr, QString userTyper="", QString mail="", QString mdp="");
    ~EmpCompteDialog();

private slots:
    void on_radioButtonAutorisePasModif_clicked();

    void on_radioButtonAutoriseModif_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_AfficherChambres_clicked();

    void on_pushButton_ValiderResa_clicked();

    void on_accueil_clicked();

    void on_account_clicked();

private:
    Ui::EmpCompteDialog *ui;
    Employe em;
    employeDAO emDAO;
    QSqlDatabase db;
    QString userType, mail, mdp;
};

#endif // EMPCOMPTEDIALOG_H

#ifndef EMPRESPCOMPTEDIALOG_H
#define EMPRESPCOMPTEDIALOG_H

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
class empRespCompteDialog;
}

class empRespCompteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit empRespCompteDialog(QWidget *parent = nullptr, QString userTyper="", QString mail="", QString mdp="");
    ~empRespCompteDialog();

private slots:
    void on_radioButtonAutorisePasModif_3_clicked();

    void on_radioButtonAutoriseModif_3_clicked();

    void on_pushButton_Modifier_3_clicked();

    void on_pushButtonListeEmployes_clicked();

    void on_pushButton_ListeClients_clicked();

    void on_pushButton_AfficherChambres_clicked();

    void on_account_clicked();

    void on_accueil_clicked();

    void on_pushButton_Stats_clicked();

private:
    Ui::empRespCompteDialog *ui;
    QString userType, mail, mdp;
    QSqlDatabase db;
    Employe em;
    employeDAO emDAO;
};

#endif // EMPRESPCOMPTEDIALOG_H

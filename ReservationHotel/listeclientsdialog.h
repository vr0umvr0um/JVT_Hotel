#ifndef LISTECLIENTSDIALOG_H
#define LISTECLIENTSDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

namespace Ui {
class listeClientsDialog;
}

class listeClientsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit listeClientsDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    ~listeClientsDialog();

private slots:

    void AfficheListeClients();

    void on_pushButton_ValiderAjoutCli_clicked();

    void on_pushButton_ValiderSuppCli_clicked();

    void on_accueil_clicked();

    void on_account_clicked();

    void on_pushButtonListeEmployes_clicked();

    void on_pushButton_AfficherChambres_clicked();

private:
    Ui::listeClientsDialog *ui;
    QSqlDatabase db;
    QString ut, ma, md;
};

#endif // LISTECLIENTSDIALOG_H

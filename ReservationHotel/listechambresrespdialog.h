#ifndef LISTECHAMBRESRESPDIALOG_H
#define LISTECHAMBRESRESPDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

using namespace std;

namespace Ui {
class listeChambresRespDialog;
}

class listeChambresRespDialog : public QDialog
{
    Q_OBJECT

public:
    explicit listeChambresRespDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    ~listeChambresRespDialog();

private slots:
    void on_account_clicked();

    void Afficherchambres();

    void on_pushButton_ListeEmployes_clicked();

    void on_pushButton_ListeClients_clicked();

    void on_pushButton_ConfimerSupp_clicked();

    void on_pushButton_ConfimerModifPrix_clicked();

    void on_pushButton_ConfimerNC_clicked();

    void on_accueil_clicked();

private:
    Ui::listeChambresRespDialog *ui;
    QSqlDatabase db;
    QString ut, ma, md;
};

#endif // LISTECHAMBRESRESPDIALOG_H

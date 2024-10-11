#ifndef LISTEEMPLOYESDIALOG_H
#define LISTEEMPLOYESDIALOG_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

namespace Ui {
class listeEmployesDialog;
}

class listeEmployesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit listeEmployesDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    ~listeEmployesDialog();

private slots:

    void AfficheListeEmployes();

    void on_pushButton_ValiderAjoutEmp_clicked();

    void on_pushButton_ValiderSuppEmp_clicked();

    void on_accueil_clicked();

    void on_account_clicked();

    void on_pushButton_ListeClients_clicked();

    void on_pushButton_AfficherChambres_clicked();

private:
    Ui::listeEmployesDialog *ui;
    QSqlDatabase db;
    QString ut, ma, md;
};

#endif // LISTEEMPLOYESDIALOG_H

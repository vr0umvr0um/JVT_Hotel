#ifndef RESERVATIONAVALIDERDIALOG_H
#define RESERVATIONAVALIDERDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

using namespace std;

namespace Ui {
class ReservationAvaliderDialog;
}

class ReservationAvaliderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReservationAvaliderDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    ~ReservationAvaliderDialog();
    void AfficherResa();


private slots:
    void on_pushButton_AfficherChambres_clicked();
    void on_account_clicked();
    void on_pushButton_ConfimerNT_clicked();
    void on_accueil_clicked();

private:
    Ui::ReservationAvaliderDialog *ui;
    QSqlDatabase db;
    QString ut, ma, md;
};

#endif // RESERVATIONAVALIDERDIALOG_H

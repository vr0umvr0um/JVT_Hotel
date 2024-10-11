#ifndef EMPRESPSTATSDIALOG_H
#define EMPRESPSTATSDIALOG_H

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
class empRespStatsDialog;
}

class empRespStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit empRespStatsDialog(QWidget *parent = nullptr, QString userTyper="", QString mail="", QString mdp="");
    ~empRespStatsDialog();

    /**
     * @brief afficheGrapheNbResaYM
     * Affiche dans la zone centrale le graphe du nombre de reservations par mois de l'hotel
     */
    void afficheGrapheNbResaYM();

    /**
     * @brief afficheGrapheNbClientsVille
     * Affiche dans la zone centrale le graphe du nombre de clients par ville de l'hotel
     */
    void afficheGrapheNbClientsVille();

    /**
     * @brief afficheGraphePrixMoyenChambre
     * Affiche le graphe du prix moyen d'une chambre
     */
    void afficheGraphePrixMoyenChambre();


private slots:
    /**
     * @brief on_pushButton_Stats_clicked
     * Passe sur l'affichage des statistiques de l'hotel
     */
    void on_pushButton_Stats_clicked();

    /**
     * @brief on_pushButtonListeEmployes_3_clicked
     * Affichage de la liste des employés
     */
    void on_pushButtonListeEmployes_3_clicked();

    /**
     * @brief on_pushButton_ListeClients_3_clicked
     * Affichage de la liste des clients
     */
    void on_pushButton_ListeClients_3_clicked();

    /**
     * @brief on_pushButton_AfficherChambres_3_clicked
     * Affichage de la liste des chambres
     */
    void on_pushButton_AfficherChambres_3_clicked();

    /**
     * @brief on_accueil_3_clicked
     * Retour à l'accueil
     */
    void on_accueil_3_clicked();

    /**
     * @brief on_account_3_clicked
     * Retour sur la page principal de compte
     */
    void on_account_3_clicked();

private:
    Ui::empRespStatsDialog *ui;
    QString userType, mail, mdp;
    QSqlDatabase db;
    Employe em;
    employeDAO emDAO;
};

#endif // EMPRESPSTATSDIALOG_H

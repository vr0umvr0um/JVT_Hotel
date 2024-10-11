#ifndef ADMINCOMPTEDIALOG_H
#define ADMINCOMPTEDIALOG_H

#include <QDialog>
#include <QDebug>
#include "administrateurdao.h"

namespace Ui {
class AdminCompteDialog;
}

class AdminCompteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminCompteDialog(QWidget *parent = nullptr, Administrateur admin = Administrateur());
    ~AdminCompteDialog();
    Administrateur admin;

    /**
     * @brief afficheGrapheNbClientsYM
     * Affiche le graphe du nombre de clients par mois dans l'espace central
     */
    void afficheGrapheNbClientsYM();

    /**
     * @brief afficheGrapheNbClientsDep
     * Affiche le graphe du nombre de clients par departement dans l'espace central
     */
    void afficheGrapheNbClientsDep();

    /**
     * @brief afficheGrapheNbReservationsYM
     * Affiche le graphe du nombre de réservations par mois dans l'espace central
     */
    void afficheGrapheNbReservationsYM();

    /**
     * @brief switchToCompte
     * Permet d'afficher la page de compte Admin
     */
    void switchToCompte();

    /**
     * @brief retourHomePage
     * Permet de retourner à la home page
     */
    void retourHomePage();

    /**
     * @brief consulterHotels
     * Permet d'afficher la liste des hotels de l'app
     */
    void consulterHotels();

    /**
     * @brief consulterClients
     * Permet d'afficher la liste des clients de l'app
     */
    void consulterClients();

    /**
     * @brief consulterAdmins
     * Affiche la liste des admins de l'app
     */
    void consulterAdmins();

    /**
     * @brief renommeHotel
     * Permet d'afficher un pop up pour renommer l'hotel en parametre
     * @param idhotel - id de l'hotel a renommer
     */
    void renommeHotel(int idhotel);

    /**
     * @brief supprimeHotel
     * Permet d'afficher un pop up pour demander la suppression d'un hotel
     * @param idhotel - id de l'hotel a supprimer
     */
    void supprimeHotel(int idhotel);

    /**
     * @brief supprimeClient
     * Permet d'afficher un pop up pour demander la suppression d'un client
     * @param idclient - id du client a supprimer
     */
    void supprimeClient(int idclient);

    /**
     * @brief supprimerAdmin
     * Permet d'afficher un pop up pour demander la suppression d'un hotel
     * @param idAdmin - id de l'admin a supprimer
     */
    void supprimerAdmin(int idAdmin);

    /**
     * @brief formulaireModifInfosAdmin
     * Permet d'afficher un formulaire pour modifier les informations d'un admin
     */
    void formulaireModifInfosAdmin();

    /**
     * @brief modifierInfosAdmin
     * Modifie les informations d'un admin en fonction des paramètres passés
     * @param newPseudo - string nouveau pseudo de l'admin
     * @param newMail - string nouveau mail de l'admin
     * @param newMdp - string nouveau mdp de l'admin
     */
    void modifierInfosAdmin(string newPseudo, string newMail, string newMdp);

    /**
     * @brief formulaireAjouterAdmin
     * Permet d'afficher un formulaire pour ajouter un nouvel admin
     */
    void formulaireAjouterAdmin();

    /**
     * @brief voirEmployes
     * Permet d'afficher les employés d'un hotel choisi
     * @param idhotel - id de l'hotel des employés
     */
    void voirEmployes(int idhotel);

private slots:
    void on_pushButton_Compte_clicked();

private:
    Ui::AdminCompteDialog *ui;
};

#endif // ADMINCOMPTEDIALOG_H

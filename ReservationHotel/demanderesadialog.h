#ifndef DEMANDERESADIALOG_H
#define DEMANDERESADIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>

using namespace std;

namespace Ui {
class DemandeResaDialog;
}

/**
 * Cette classe permet de gérer l'interface graphique 'DemandeResaDialog'
 *
 * @brief The DemandeResaDialog class
 * @author Vanessa Antivackis
 */
class DemandeResaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Cette méthode permet d'ouvrir une fenêtre de dialogue de demande de reservation.
     *
     * @brief DemandeResaDialog
     * @param parent
     * @param userType
     * @param mail
     */
    explicit DemandeResaDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    /**
     * Cette méthode permet de détruire une fenêtre de dialogue de demande de reservation.
     */
    ~DemandeResaDialog();
    /**
     * Cette méthode permet d'afficher une liste des hôtels dans une fenêtre de dialogue de demande de reservation.
     *
     * @brief afficherListeHotel
     */
    void afficherListeHotel();

private slots:
    /**
     * Ce 'slot' permet de rediriger vers la fenêtre de demande d'inscription lorsque l'utilisateur actuelle n'est pas un client.
     *
     * @brief on_pushButton_signupCli_clicked
     */
    void on_pushButton_signupCli_clicked();

    /**
     * Ce 'slot' permet de valider l'annulation de la réservation choisie.
     *
     * @brief on_pushButton_val_clicked
     */
    void on_pushButton_val_clicked();

    /**
     *
     * Ce 'slot' permet de se rendre sur la page d'accueil.
     *
     * @brief on_accueil_clicked
     */
    void on_accueil_clicked();

private:
    /**
     * Interface graphique d'une fenêtre de dialogue de demande de reservation.
     *
     * @brief ui
     */
    Ui::DemandeResaDialog *ui;

    /**
     *
     * Etablissement de la connexion à la base de données.
     *
     * @brief db
     */
    QSqlDatabase db;

    /**
     *
     * Permet de stocker userType, mail et mdp.
     *
     * @brief mail
     */
    QString mail, userType, mdp;
};

#endif // DEMANDERESADIALOG_H

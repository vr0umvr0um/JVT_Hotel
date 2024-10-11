#ifndef MODIFRESADIALOG_H
#define MODIFRESADIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QDialog>

#include "reservationdao.h"

using namespace std;

namespace Ui {
class ModifResaDialog;
}

/**
 *
 * Cette classe permet de gérer une interface graphique de modification de réservation.
 *
 * @author Vanessa Antivackis
 * @brief The ModifResaDialog class
 */
class ModifResaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     *
     * Cette méthode permet d'ouvrir une fenêtre de dialogue de modification de réservation.
     *
     * @brief ModifResaDialog
     * @param parent
     */
    explicit ModifResaDialog(QWidget *parent = nullptr, QString userType="", QString mail="", const Reservation& reservation= Reservation(), QString mdp="");

    /**
     *
     * Cette méthode permet de détruire une fenêtre de dialogue de modification de réservation.
     *
     */
    ~ModifResaDialog();

    /**
     *
     * Cette méthode permet d'afficher les informations concernant une reservation choisit selon plusieurs paramètres.
     *
     * @brief afficherInformationsResa
     * @param dateArrive
     * @param dateDepart
     * @param mailClient
     * @param numChambre
     */
    void afficherInformationsResa(QString dateArrive, QString dateDepart, QString mailClient, QString numChambre);

    /**
     *
     * Cette méthode permet d'afficher les informations concernant les hôtels.
     *
     * @brief afficherListeHotel
     */
    void afficherListeHotel();

private slots:
    /**
     * Ce 'slot' permet de modifier une reservation.
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
    Ui::ModifResaDialog *ui;

    /**
     *
     * Etablissement de la connexion à la base de données.
     *
     * @brief db
     */
    QSqlDatabase db;

    /**
     *
     * Gérer une instance ReservationDAO.
     *
     * @brief resaDAO
     */
    ReservationDAO resaDAO;

    /**
     *
     * Permet de stocker une instance reservation.
     *
     * @brief resa
     */
    Reservation resa;

    /**
     *
     * Permet de stocker userType, mail, mdp, dateArrive et dateDepart.
     *
     * @brief userType
     */
    QString userType, mail, dateArrive, dateDepart, mdp;
};

#endif // MODIFRESADIALOG_H

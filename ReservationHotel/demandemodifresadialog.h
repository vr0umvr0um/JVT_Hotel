#ifndef DEMANDEMODIFRESADIALOG_H
#define DEMANDEMODIFRESADIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QDialog>

using namespace std;

namespace Ui {
class DemandeModifResaDialog;
}

/**
 *
 * Cette classe permet de gérer l'interface graphique 'DemandeModifResaDialog'
 *
 * @author Vanessa Antivackis
 * @brief The DemandeModifResaDialog class
 */
class DemandeModifResaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     *
     * Cette méthode permet d'ouvrir une fenêtre de demande de modification de reservation.
     *
     * @brief DemandeModifResaDialog
     * @param parent
     * @param userType
     * @param mail
     * @param mdp
     */
    explicit DemandeModifResaDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    /**
     *
     * Cette méthode permet de détruire une fenêtre de demande de modification de reservation.
     *
     */
    ~DemandeModifResaDialog();
    /**
     * Cette méthode permet d'afficher une liste d'hôtel dans un QTableWidgetItem.
     *
     * @brief afficherHotel
     */
    void afficherHotel();
    /**
     * Cette méthode permet d'afficher une liste d'hôtel dans un QTableWidgetItem en fonction de son nom et de sa ville.
     *
     * @brief rechercherHotel
     * @param nom
     * @param ville
     */
    void rechercherHotel(const QString& nom, const QString& ville);

private slots:
    /**
     * Ce 'slot' permet de valider la rechercher selon des critères.
     *
     * @brief on_pushButton_search_clicked
     */
    void on_pushButton_search_clicked();

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

    /**
     *
     * Ce 'slot' permet de se rendre sur la page de compte.
     *
     * @brief on_account_clicked
     */
    void on_account_clicked();

private:
    /**
     *
     * Interface graphique
     *
     * @brief ui
     */
    Ui::DemandeModifResaDialog *ui;

    /**
     *
     * Etablissement de la connexion à la base de données.
     *
     * @brief db
     */
    QSqlDatabase db;

    /**
     *
     * Permet de stocker les attributs mail, userType, mdp et dateAjd.
     *
     * @brief mail
     */
    QString mail, userType, mdp, dateAjd;
};

#endif // DEMANDEMODIFRESADIALOG_H

#ifndef ANNULERESADIALOG_H
#define ANNULERESADIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QDialog>

using namespace  std;

namespace Ui {
class AnnuleResaDialog;
}

/**
 *
 * Cette classe permet de gérer l'interface graphique 'AnnuleResaDialog'
 *
 * @brief The AnnuleResaDialog class
 * @author Vanessa Antivackis
 */
class AnnuleResaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     *
     * Cette méthode permet d'ouvrir une fenêtre de dialogue de demande d'annuler de reservation.
     *
     * @brief AnnuleResaDialog
     * @param parent
     * @param userType
     * @param mail
     */
    explicit AnnuleResaDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");
    /**
     *
     * Cette méthode permet de détruire une fenêtre de dialogue de demande d'annuler de reservation.
     *
     */
    ~AnnuleResaDialog();
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
     * Interface graphique d'une fenêtre de dialogue de demande d'annuler de reservation.
     *
     * @brief ui
     */
    Ui::AnnuleResaDialog *ui;

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

#endif // ANNULERESADIALOG_H

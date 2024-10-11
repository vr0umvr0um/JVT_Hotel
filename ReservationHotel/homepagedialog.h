#ifndef HOMEPAGEDIALOG_H
#define HOMEPAGEDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDialog>

using namespace std;

namespace Ui {
class HomePageDialog;
}

/**
 * Cette classe est utilisée pour l'interface graphique HomePageDialog.ui.
 *
 * Elle permet d'afficher des hôtels ainsi que de rechercher des hôtels selon leur nom et ville.
 *
 * @brief The HomePageDialog class
 * @author Vanessa Antivackis
 */
class HomePageDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Cette méthode permet d'ouvrir une fenêtre de dialogue de la page d'acceuil.
     * Elle possède les paramètres userType, nom et prenom.
     *
     * @brief HomePageDialog
     * @param parent
     * @param userType
     * @param nom
     * @param prenom
     */
    explicit HomePageDialog(QWidget *parent = nullptr, QString userType="client", QString mail="", QString mdp="");

    /**
     * Cette méthode permet de détruire une fenêtre de dialogue de la page d'acceuil.
     */
    ~HomePageDialog();

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
     * Ce 'slot' permet de rediriger vers une fenêtre de dialogue de demande de reservation.
     *
     * @brief on_pushButton_dmdResa_clicked
     */
    void on_pushButton_dmdResa_clicked();

    /**
     *
     * Ce 'slot' permet de rediriger vers une fenêtre de dialogue de suppression d'une reservation choisi.
     *
     * @brief on_pushButton_delResa_clicked
     */
    void on_pushButton_delResa_clicked();

    /**
     *
     * Ce 'slot' permet de se rediriger sur la page compte.
     *
     * @brief on_account_clicked
     */
    void on_account_clicked();

    /**
     *
     * Ce 'slot' permet de rediriger vers une fenêtre de dialogue de modification d'une reservation choisie.
     *
     * @brief on_pushButton_modifResa_clicked
     */
    void on_pushButton_modifResa_clicked();

private:
    /**
     * Interface graphique d'une fenêtre de dialogue de la page d'acceuil.
     *
     * @brief ui
     */
    Ui::HomePageDialog *ui;

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
     * @brief userType
     */
    QString userType, mail, mdp;

};

#endif // HOMEPAGEDIALOG_H

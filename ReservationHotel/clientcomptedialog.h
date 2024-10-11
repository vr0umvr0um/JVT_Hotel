#ifndef CLIENTCOMPTEDIALOG_H
#define CLIENTCOMPTEDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QDialog>

#include "clientdao.h"

using namespace std;

namespace Ui {
class ClientCompteDialog;
}

/**
 * Cette classe permet de gérer l'interface graphique d'un compte client.
 *
 * @brief The ClientCompteDialog class
 * @author Vanessa Antivackis
 */
class ClientCompteDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     *
     * Cette méthode permet d'ouvrir une fenêtre de dialogue d'un compte client.
     *
     * @brief ClientCompteDialog
     * @param parent
     * @param userType
     * @param mail
     */
    explicit ClientCompteDialog(QWidget *parent = nullptr, QString userType="", QString mail="", QString mdp="");

    /**
     *
     * Cette méthode permet de détruire une fenêtre de dialogue d'un compte client.
     *
     */
    ~ClientCompteDialog();

    /**
     *
     * Cette méthode permet d'afficher les informations d'un client.
     *
     * @brief afficherInformationsw
     */
    void afficherInformations();

    /**
     *
     * Cette méthode permet d'afficher les reservations effectuées par un client.
     *
     * @brief afficherHistoriqueResa
     */
    void afficherHistoriqueResa();

private slots:
    /**
     *
     * Ce 'slot' permet de gérer la modificatoin des données d'un client.
     *
     * @brief on_pushButton_modifCli_clicked
     */
    void on_pushButton_modifCli_clicked();
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
     * Interface graphique d'une fenêtre de dialogue d'un compte client.
     *
     * @brief ui
     */
    Ui::ClientCompteDialog *ui;

    /**
     *
     * Gestion d'une instance ClientDAO.
     *
     * @brief clidao
     */
    ClientDAO clidao;

    /**
     *
     * Permet de stocker tous les informations relatives à un client.
     *
     * @brief cli
     */
    Client cli;

    /**
     *
     * Etablissmenent de la connexion à la base de données.
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

#endif // CLIENTCOMPTEDIALOG_H

#include "homepagedialog.h"
#include "ui_homepagedialog.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "EmpCompteDialog.h"
#include "emprespcomptedialog.h"
#include "demandemodifresadialog.h"
#include "demanderesadialog.h"
#include "annuleresadialog.h"

#include "singleconnection.h"

HomePageDialog::HomePageDialog(QWidget *parent, QString ut, QString m, QString pwd)
    : QDialog(parent)
    , ui(new Ui::HomePageDialog)
{
    // Gestion connexion à bdd
    db = SingleConnection::getInstance();

    // Affichage ui
    ui->setupUi(this);

    // Gestion des paramètres globaux
    this->mail = m;
    this->userType = ut;
    this->mdp = pwd;

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit.png");
    ui->logo->setPixmap(pixLogo);

    // Afficher tous les hotels et leurs informations
    afficherHotel();

    // Fermeture de la connexion a bdd
    db.close();
}

HomePageDialog::~HomePageDialog()
{
    delete ui;
}

void HomePageDialog::on_pushButton_search_clicked()
{
    // Recuperation du nom de l'hotel contenue dans QLineEdit
    QString nomHotel = ui->lineEdit_nh->text();

    // Recuperation de la ville de l'hotel contenue dans QLineEdit
    QString villeHotel = ui->lineEdit_vh->text();

    // Fonction pour rechercher en fonction de ces paramètres
    rechercherHotel(nomHotel, villeHotel);

}

void HomePageDialog::afficherHotel(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM hotel "
                            "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                            "JOIN chambre ON hotel.idHotel = chambre.idHotel; ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeHotel->setRowCount(query.size());
        int row_number = 0;

        // Iterer à travers les resultats de la requete
        while(query.next()){
            // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
            ui->tableWidget_ListeHotel->setItem(row_number,0, new QTableWidgetItem(query.value("hotel.nomHotel").toString()));
            ui->tableWidget_ListeHotel->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
            ui->tableWidget_ListeHotel->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
              ui->tableWidget_ListeHotel->setItem(row_number,3,new QTableWidgetItem(query.value("chambre.prix").toString() + " €"));
            ui->tableWidget_ListeHotel->setItem(row_number,4, new QTableWidgetItem( query.value("adresse.numero").toString()
                                                                                        + " " + query.value("adresse.rue").toString()
                                                                                        + " " + query.value("adresse.ville").toString()
                                                                                        + " " + query.value("adresse.codePostal").toString()
                                                                                        + " " + query.value("adresse.pays").toString()));
            // Incrementation du nombre de colonnes
            row_number = row_number + 1;
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeHotel->resizeRowsToContents();
    ui->tableWidget_ListeHotel->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}

void HomePageDialog::rechercherHotel(const QString& nom, const QString& ville) {
   // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Initialisation des lignes a 0
    ui->tableWidget_ListeHotel->setRowCount(0);

    // Si le nom et la ville sont vides
    if(nom.isEmpty() && ville.isEmpty()){
        afficherHotel();
    }
    // Si le nom est vide
    else if(nom.isEmpty() && !ville.isEmpty() ){
       // Preparation de la requete SQL
        QString preparedQuery = "SELECT * "
                               "FROM hotel "
                               "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                               "JOIN chambre ON hotel.idHotel = chambre.idHotel "
                               "WHERE adresse.ville LIKE '%" + ville + "%';";
        query.prepare(preparedQuery);

        // Execution de la requete et gestion de l'erreur
        if(!query.exec()){
            qDebug() << "Erreur requête SQL"<< query.lastError().text();
        }
        else {
             // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
            ui -> tableWidget_ListeHotel->setRowCount(query.size());
            int row_number = 0;

            // Iterer à travers les resultats de la requete & Ajout a l'instance tableWidget
            while(query.next()){
                ui->tableWidget_ListeHotel->setItem(row_number,0, new QTableWidgetItem(query.value("hotel.nomHotel").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,3,new QTableWidgetItem(query.value("chambre.prix").toString() + " €"));
                ui->tableWidget_ListeHotel->setItem(row_number,4, new QTableWidgetItem( query.value("adresse.numero").toString()
                                                                                        + " " + query.value("adresse.rue").toString()
                                                                                        + " " + query.value("adresse.ville").toString()
                                                                                        + " " + query.value("adresse.codePostal").toString()
                                                                                        + " " + query.value("adresse.pays").toString()));
                // Incrementation du nombre de colonnes
                row_number = row_number + 1;
            }
        }
    }
    // Si la ville est vide
    else if(!nom.isEmpty() && ville.isEmpty()){
        // Preparation de la requete SQL
        QString preparedQuery = "SELECT * "
                                "FROM hotel "
                                "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                "JOIN chambre ON hotel.idHotel = chambre.idHotel "
                                "WHERE hotel.nomHotel LIKE '%"+ nom + "%';";
        query.prepare(preparedQuery);

        // Execution de la requete et gestion de l'erreur
        if(!query.exec()){
            qDebug() << "Erreur requête SQL"<< query.lastError().text();
        }
        else {
             // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
            ui -> tableWidget_ListeHotel->setRowCount(query.size());
            int row_number = 0;

            // Iterer à travers les resultats de la requete & Ajout a l'instance tableWidget
            while(query.next()){
                ui->tableWidget_ListeHotel->setItem(row_number,0, new QTableWidgetItem(query.value("hotel.nomHotel").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,3,new QTableWidgetItem(query.value("chambre.prix").toString() + " €"));
                ui->tableWidget_ListeHotel->setItem(row_number,4, new QTableWidgetItem( query.value("adresse.numero").toString()
                                                                                        + " " + query.value("adresse.rue").toString()
                                                                                        + " " + query.value("adresse.ville").toString()
                                                                                        + " " + query.value("adresse.codePostal").toString()
                                                                                        + " " + query.value("adresse.pays").toString()));
                // Incrementation du nombre de colonnes
                row_number = row_number + 1;
            }
        }
    }
    // Si rien n'est vide
    else{
        // Preparation de la requete SQL
        QString preparedQuery = "SELECT * "
                                "FROM hotel "
                                "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                "JOIN chambre ON hotel.idHotel = chambre.idHotel "
                                "WHERE hotel.nomHotel LIKE '%"+ nom + "%' "
                                    "AND adresse.ville LIKE '%" + ville + "%'";
        query.prepare(preparedQuery);

        // Execution de la requete et gestion de l'erreur
        if(!query.exec()){
            qDebug() << "Erreur requête SQL"<< query.lastError().text();
        }
        else {
            // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
            ui -> tableWidget_ListeHotel->setRowCount(query.size());
            int row_number = 0;

            // Iterer à travers les resultats de la requete & Ajout a l'instance tableWidget
            while(query.next()){
                ui->tableWidget_ListeHotel->setItem(row_number,0, new QTableWidgetItem(query.value("hotel.nomHotel").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
                ui->tableWidget_ListeHotel->setItem(row_number,3,new QTableWidgetItem(query.value("chambre.prix").toString() + " €"));
                ui->tableWidget_ListeHotel->setItem(row_number,4, new QTableWidgetItem( query.value("adresse.numero").toString()
                                                                                        + " " + query.value("adresse.rue").toString()
                                                                                        + " " + query.value("adresse.ville").toString()
                                                                                        + " " + query.value("adresse.codePostal").toString()
                                                                                        + " " + query.value("adresse.pays").toString()));
                // Incrementation du nombre de colonnes
                row_number = row_number + 1;
            }
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeHotel->resizeRowsToContents();
    ui->tableWidget_ListeHotel->resizeColumnsToContents();

    // Supprimer les mots clefs de la rechercher
    ui->lineEdit_nh->clear();
    ui->lineEdit_vh->clear();

    // Fermeture de la connexion a bdd
    db.close();
}

void HomePageDialog::on_pushButton_dmdResa_clicked()
{
    // Creation instance DemandeResaDialog
    DemandeResaDialog* demandeResaDialog = new DemandeResaDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance DemandeResaDialog
    demandeResaDialog->showMaximized();

    // Fermer l'instance HomePageDialog
    this->close();
}

void HomePageDialog::on_pushButton_delResa_clicked()
{
    // Creation instance AnnuleResaDialog
    AnnuleResaDialog* annuleResaDialog = new AnnuleResaDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance AnnuleResaDialog
    annuleResaDialog->showMaximized();

    // Fermer l'instance HomePageDialog
    this->close();
}


void HomePageDialog::on_account_clicked()
{
    // Si utilisateur est un employe
    if(userType == "emp"){
        // Creation instance EmpCompteDialog
        EmpCompteDialog* empCompteDialog = new EmpCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance EmpCompteDialog
        empCompteDialog->showMaximized();

        // Fermer l'instance HomePageDialog
        this->close();
    }
    // Si utilisateur est un client
    else if(userType == "client"){
        // Creation instance ClientCompteDialog
        ClientCompteDialog* clientCompteDialog = new ClientCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance AnnuleResaDialog
        clientCompteDialog->showMaximized();

        // Fermer l'instance HomePageDialog
        this->close();
    }
    // Si utilisateur est un admin
    else if(userType == "admin"){
        // Creation instance Administrateur DAO
        AdministrateurDAO admindao;             //Pour ?
        // Affichage de l'instance AdminCompteDialog
        AdminCompteDialog* adminCompteDialog = new AdminCompteDialog(this, admindao.connexionAdmin(this->mail, this->mdp));
        adminCompteDialog->showMaximized();

        // Fermer l'instance HomePageDialog
        this->close();
    }
    // Si utilisateur est un employe responsable
    else if(userType == "empR"){
        // Creation instance empRespCompteDialog
        empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance empRespCompteDialog
        empRespCompteDialog->showMaximized();

        // Fermer l'instance HomePageDialog
        this->close();
    }
}

void HomePageDialog::on_pushButton_modifResa_clicked()
{   // Creation instance DemandeModifResaDialog
    DemandeModifResaDialog* demandeModifResaDialog = new DemandeModifResaDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance DemandeModifResaDialog
    demandeModifResaDialog->showMaximized();

    // Fermer l'instance HomePageDialog
    this->close();
}

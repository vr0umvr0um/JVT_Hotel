#include "annuleresadialog.h"
#include "ui_annuleresadialog.h"

#include "reservationdao.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "empcomptedialog.h"
#include "emprespcomptedialog.h"
#include "homepagedialog.h"

#include "singleconnection.h"

AnnuleResaDialog::AnnuleResaDialog(QWidget *parent, QString ut, QString m, QString pwd)
    : QDialog(parent)
    , ui(new Ui::AnnuleResaDialog)
{
    // Gestion connexion à bdd
    db = SingleConnection::getInstance();

    // Affichage ui
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);

    // Gestion des paramètres globaux
    this->userType=ut;
    this->mail=m;
    this->mdp=pwd;

    // Si l'utilisateur est un client
    if(userType=="client"){
        // Ajout de son mail au QLineEdit
        ui->lineEdit_mailCli->setText(this->mail);

        // Impossibilité pour lui de modifier son adresse mail
        ui->lineEdit_mailCli->setReadOnly(true);
    }
    else{
        ui->lineEdit_mailCli->setReadOnly(false);
    }

    // Date du jour
    this->dateAjd = QDate::currentDate().toString("yyyy-MM-dd");

    // Fonction pour afficher les hotels dans le QTableWidgetItem
    afficherHotel();

    // Fermeture de la connexion a bdd
    db.close();
}

AnnuleResaDialog::~AnnuleResaDialog()
{
    delete ui;
}

void AnnuleResaDialog::afficherHotel(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Initialisation de mailCli
    QString mailCli = ui->lineEdit_mailCli->text();

    // Si QLineEdit mail est vide
    if(mailCli.isEmpty()){
        // Preparation de la requete
        QString preparedQuery = "SELECT * FROM reservation "
                                "JOIN client ON reservation.idClient=client.idClient "
                                "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                "WHERE reservation.dateArrive >= '" + dateAjd + "' "
                                    "ORDER BY reservation.dateArrive;";
        query.prepare(preparedQuery);

        // Execution de la requete et gestion de l'erreur
        if(!query.exec()){
            qDebug() << "Erreur requête SQL"<< query.lastError().text();
        }
        else {
            // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
            ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
            int row_number = 0;

            // Effacer les informations déjà présente dans QComboBox
            ui->comboBox_listeHotelResa->clear();

            // Iterer à travers les resultats de la requete
            while(query.next()){
                // Extraire les données de la ligne actuelle
                QString nomHotel = query.value("hotel.nomHotel").toString();
                QString numChambre = query.value("chambre.numChambre").toString();
                QString nbCouchages = query.value("chambre.nbCouchages").toString();
                QString prixChambre = query.value("chambre.prix").toString();
                QString adresse = query.value("adresse.numero").toString()
                                  + " " + query.value("adresse.rue").toString()
                                  + " " + query.value("adresse.ville").toString()
                                  + " " + query.value("adresse.codePostal").toString()
                                  + " " + query.value("adresse.pays").toString();
                QString dateA = query.value("reservation.dateArrive").toString();
                QString dateD = query.value("reservation.dateDepart").toString();

                // Ajout a l'instance QTableWidget
                ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                // Gerer statut de la reservation
                if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                    ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                }
                else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                    ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                }
                else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                    ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                }

                // Incrementation du nombre de colonnes
                row_number = row_number + 1;

                // Creer un affichage pour l'element QComboBox
                QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                            .arg(nomHotel)
                                            .arg(numChambre)
                                            .arg(nbCouchages)
                                            .arg(prixChambre)
                                            .arg(adresse)
                                            .arg(dateA)
                                            .arg(dateD);

                // Ajouter l'element a la QComboBox
                ui->comboBox_listeHotelResa->addItem(displayString);
            }
        }
    }
    // Si QLineEDit mail n'est pas vide
    else{
        // Preparation de la requete
        QString preparedQuery = "SELECT * "
                                "FROM reservation "
                                "JOIN client ON reservation.idClient=client.idClient "
                                "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                "WHERE client.mailClient='" + mailCli +"' "
                                    "AND reservation.dateArrive >= '" + dateAjd + "' "
                                    "ORDER BY reservation.dateArrive;";
        query.prepare(preparedQuery);

        // Execution de la requete et gestion de l'erreur
        if(!query.exec()){
            qDebug() << "Erreur requête SQL"<< query.lastError().text();
        }
        else {
            // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
            ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
            int row_number = 0;

            // Effacer les informations déjà présente dans QComboBox
            ui->comboBox_listeHotelResa->clear();

            // Iterer à travers les resultats de la requete
            while(query.next()){
                // Extraire les données de la ligne actuelle
                QString nomHotel = query.value("hotel.nomHotel").toString();
                QString numChambre = query.value("chambre.numChambre").toString();
                QString nbCouchages = query.value("chambre.nbCouchages").toString();
                QString prixChambre = query.value("chambre.prix").toString();
                QString adresse = query.value("adresse.numero").toString()
                                  + " " + query.value("adresse.rue").toString()
                                  + " " + query.value("adresse.ville").toString()
                                  + " " + query.value("adresse.codePostal").toString()
                                  + " " + query.value("adresse.pays").toString();
                QString dateA = query.value("reservation.dateArrive").toString();
                QString dateD = query.value("reservation.dateDepart").toString();

                // Ajout a l'instance QTableWidget
                ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                // Gerer statut de la reservation
                if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                    ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                }
                else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                    ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                }
                else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                    ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                }

                // Incrementation de la colonne
                row_number = row_number + 1;

                // Creer un affichage pour l'element QComboBox
                QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                            .arg(nomHotel)
                                            .arg(numChambre)
                                            .arg(nbCouchages)
                                            .arg(prixChambre)
                                            .arg(adresse)
                                            .arg(dateA)
                                            .arg(dateD);

                // Ajouter l'element a la QComboBox
                ui->comboBox_listeHotelResa->addItem(displayString);
            }
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeHotelResa->resizeRowsToContents();
    ui->tableWidget_ListeHotelResa->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}

void AnnuleResaDialog::on_pushButton_search_clicked()
{
    // Recuperation du nom de l'hotel contenue dans QLineEdit
    QString nomHotel = ui->lineEdit_nh->text();

    // Recuperation de la ville de l'hotel contenue dans QLineEdit
    QString villeHotel = ui->lineEdit_vh->text();

    // Fonction pour rechercher en fonction de ces paramètres
    rechercherHotel(nomHotel, villeHotel);
}

void AnnuleResaDialog::rechercherHotel(const QString& nom, const QString& ville) {
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Initialisation des lignes a 0
    ui->tableWidget_ListeHotelResa->setRowCount(0);

    // Initialisation de mailCli
    QString mailCli = ui->lineEdit_mailCli->text();

    // Si mailCli est vide
    if(mailCli.isEmpty()){
        // Si le mail, nom et la ville sont vides
        if(nom.isEmpty() && ville.isEmpty()){
            afficherHotel();
        }
        // Si le mail et nom sont vides
        else if(nom.isEmpty() && !ville.isEmpty() ){
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM reservation "
                                    "JOIN client ON reservation.idClient=client.idClient "
                                    "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                    "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "WHERE adresse.ville LIKE '%" + ville +"%';"
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY reservation.dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();

                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonne
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
        // Si le mail et ville sont vides
        else if(!nom.isEmpty() && ville.isEmpty()){
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM hotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "JOIN chambre ON hotel.idHotel = chambre.idHotel "
                                    "WHERE hotel.nomHotel LIKE '%"+ nom + "%' "
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY reservation.dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();

                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonne
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
        // Si le mail est vide
        else{
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM hotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "JOIN chambre ON hotel.idHotel = chambre.idHotel "
                                    "WHERE hotel.nomHotel LIKE '%"+ nom + "%' "
                                        "AND adresse.ville LIKE '%" + ville + "%' "
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY reservation.dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();

                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonnes
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
    }
    // Si le QLabel mailCli n'est pas vide
    else{
        // Si le nom et la ville sont vides
        if(nom.isEmpty() && ville.isEmpty()){
            afficherHotel();
        }
        // Si le nom est vide
        else if(nom.isEmpty() && !ville.isEmpty() ){
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM reservation "
                                    "JOIN client ON reservation.idClient=client.idClient "
                                    "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                    "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "WHERE client.mailClient='" + mailCli +"' "
                                        "AND adresse.ville LIKE '%" + ville + "%' "
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY reservation.dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();


                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonne
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
        // Si la ville est vide
        else if(!nom.isEmpty() && ville.isEmpty()){
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM reservation "
                                    "JOIN client ON reservation.idClient=client.idClient "
                                    "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                    "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "WHERE client.mailClient='" + mailCli +"' "
                                        "AND hotel.nomHotel LIKE '%" + nom + "%' "
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY reservation.dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();

                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonnes
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
        // Si rien n'est vide
        else{
            // Preparation de la requete SQL
            QString preparedQuery = "SELECT * "
                                    "FROM reservation "
                                    "JOIN client ON reservation.idClient=client.idClient "
                                    "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                                    "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                                    "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                    "WHERE client.mailClient='" + mailCli +"' "
                                        "AND hotel.nomHotel LIKE '%" + nom + "%' "
                                        "AND adresse.ville LIKE '%" + ville + "%' "
                                        "AND reservation.dateArrive >= '" + dateAjd + "' "
                                        "ORDER BY dateArrive;";
            query.prepare(preparedQuery);

            // Execution de la requete et gestion de l'erreur
            if(!query.exec()){
                qDebug() << "Erreur requête SQL"<< query.lastError().text();
            }
            else {
                // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
                ui -> tableWidget_ListeHotelResa->setRowCount(query.size());
                int row_number = 0;

                // Effacer les informations déjà présente dans QComboBox
                ui->comboBox_listeHotelResa->clear();

                // Iterer à travers les resultats de la requete
                while(query.next()){
                    // Extraire les données de la ligne actuelle
                    QString nomHotel = query.value("hotel.nomHotel").toString();
                    QString numChambre = query.value("chambre.numChambre").toString();
                    QString nbCouchages = query.value("chambre.nbCouchages").toString();
                    QString prixChambre = query.value("chambre.prix").toString();
                    QString adresse = query.value("adresse.numero").toString()
                                      + " " + query.value("adresse.rue").toString()
                                      + " " + query.value("adresse.ville").toString()
                                      + " " + query.value("adresse.codePostal").toString()
                                      + " " + query.value("adresse.pays").toString();
                    QString dateA = query.value("reservation.dateArrive").toString();
                    QString dateD = query.value("reservation.dateDepart").toString();

                    // Ajout a l'instance QTableWidget
                    ui->tableWidget_ListeHotelResa->setItem(row_number,0, new QTableWidgetItem(nomHotel));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,1, new QTableWidgetItem(numChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,3, new QTableWidgetItem(prixChambre));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,4, new QTableWidgetItem(adresse));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,5, new QTableWidgetItem(dateA));
                    ui->tableWidget_ListeHotelResa->setItem(row_number,6, new QTableWidgetItem(dateD));

                    // Gerer statut de la reservation
                    if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                        ui->tableWidget_ListeHotelResa->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
                    }
                    else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                        ui->tableWidget_ListeHotelResa->setItem(row_number, 7, new QTableWidgetItem("Valide"));
                    }

                    // Incrementation du nombre de colonnes
                    row_number = row_number + 1;

                    // Creer un affichage pour l'element QComboBox
                    QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                                .arg(nomHotel)
                                                .arg(numChambre)
                                                .arg(nbCouchages)
                                                .arg(prixChambre)
                                                .arg(adresse)
                                                .arg(dateA)
                                                .arg(dateD);

                    // Ajouter l'element a la QComboBox
                    ui->comboBox_listeHotelResa->addItem(displayString);
                }
            }
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeHotelResa->resizeRowsToContents();
    ui->tableWidget_ListeHotelResa->resizeColumnsToContents();

    // Supprimer les mots clefs de la rechercher
    ui->lineEdit_nh->clear();
    ui->lineEdit_vh->clear();

    // Fermeture de la connexion a bdd
    db.close();
}


void AnnuleResaDialog::on_pushButton_val_clicked()
{
    // Recuperation des dates depuis QComboBox
    QString dateArr = ui->comboBox_listeHotelResa->currentText().split(" - ").at(5);;
    QString dateDep = ui->comboBox_listeHotelResa->currentText().split(" - ").at(6);;

    // Recuperation information Client
    QString mailCli = ui->lineEdit_mailCli->text();

    // Recuperation information Chambre
    QString numChambre = ui->comboBox_listeHotelResa->currentText().split(" - ").at(1);

    // Creation instances Reservation & ReservationDAO
    ReservationDAO resDAO;
    Reservation res = resDAO.lire(mailCli, dateArr, dateDep, numChambre);

    // Suppression de la reservation
    resDAO.supprimer(res);

    // Message de confirmation
    QMessageBox::information(this, "Valider", "Votre reservation a bien été annulé !");

    // Actualisation de la liste des hotels
    afficherHotel();
}


void AnnuleResaDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance AnnuleResaDialog
    this->close();
}


void AnnuleResaDialog::on_account_clicked()
{
    // Si utilisateur est un employe
    if(userType == "emp"){
        // Creation instance EmpCompteDialog
        EmpCompteDialog* empCompteDialog = new EmpCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance EmpCompteDialog
        empCompteDialog->showMaximized();

        // Fermer l'instance AnnuleResaDialog
        this->close();
    }
    // Si utilisateur est un client
    else if(userType == "client"){
        // Creation instance ClientCompteDialog
        ClientCompteDialog* clientCompteDialog = new ClientCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance ClientCompteDialog
        clientCompteDialog->showMaximized();

        // Fermer l'instance AnnuleResaDialog
        this->close();
    }
    // Si utilisateur est un admin
    else if(userType == "admin"){
        // Creation instance Administrateur DAO
        AdministrateurDAO admindao;             //Pour ?
        // Affichage de l'instance AdminCompteDialog
        AdminCompteDialog* adminCompteDialog = new AdminCompteDialog(this, admindao.connexionAdmin(this->mail, this->mdp));
        adminCompteDialog->showMaximized();

        // Fermer l'instance AnnuleResaDialog
        this->close();
    }
    // Si utilisateur est un employe responsable
    else if(userType == "empR"){
        // Creation instance empRespCompteDialog
        empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->userType, this->mail, this->mdp);

        // Affichage de l'instance empRespCompteDialog
        empRespCompteDialog->showMaximized();

        // Fermer l'instance AnnuleResaDialog
        this->close();
    }
}


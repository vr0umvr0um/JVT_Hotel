#include "clientcomptedialog.h"
#include "ui_clientcomptedialog.h"

#include "clientcomptedialog.h"
#include "homepagedialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

ClientCompteDialog::ClientCompteDialog(QWidget *parent, QString ut, QString m, QString pwd)
    : QDialog(parent)
    , ui(new Ui::ClientCompteDialog)
{
    // Gestion connexion à bdd
    db = SingleConnection::getInstance();

    // Affichage ui
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);

    // Gestion des paramètres globaux
    this->userType = ut;
    this->mail=m;
    this->mdp=pwd;

    // Initialisation mdpCli grâce aux paramètres globaux
    ui->lineEdit_mdpCli->setText(mdp);

    // Initialisation mailC grâce aux paramètres globaux
    ui->lineEdit_mailC->setText(mail);

    // Afficher les informations relatives au client
    afficherInformations();

    // Afficher toutes ses reservations
    afficherHistoriqueResa();

    // Initilisation cli
    this->cli = clidao.lire(mail);

    // Fermeture de la connexion a bdd
    db.close();
}

ClientCompteDialog::~ClientCompteDialog()
{
    delete ui;
}

void ClientCompteDialog::afficherInformations(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM client "
                            "JOIN adresse ON client.idAdresse=adresse.idAdresse "
                            "WHERE client.mailClient='" + mail + "'; ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Iterer à travers les resultats de la requete
        if(query.next()){
            // Extraire les données de la ligne actuelle
            QString nomClient = query.value("client.nomClient").toString();
            QString prenomClient = query.value("client.prenomClient").toString();
            QString telClient = query.value("client.telephone").toString();
            QString numeroAdr = query.value("adresse.numero").toString();
            QString rueAdr = query.value("adresse.rue").toString();
            QString villeAdr = query.value("adresse.ville").toString();
            QString cpAdr = query.value("adresse.codePostal").toString();
            QString pays = query.value("adresse.pays").toString();

            // Ajout de l'instance aux QLineEdit
            ui->lineEdit_nomC->setText(nomClient);
            ui->lineEdit_prenomC->setText(prenomClient);
            ui->lineEdit_numero->setText(numeroAdr);
            ui->lineEdit_telCli->setText(telClient);
            ui->lineEdit_rue->setText(rueAdr);
            ui->lineEdit_ville->setText(villeAdr);
            ui->lineEdit_cp->setText(cpAdr);
            ui->lineEdit_pays->setText(pays);
        }
        else{
            // Erreur lors de l'affichage des tuples
            qDebug() << "Requete next() incorrecte " << query.lastError().text();
        }
    }

    // Fermeture de la connexion a bdd
    db.close();
}

void ClientCompteDialog::on_pushButton_modifCli_clicked()
{
    // Recuperation des informations concernant un client
    string nomClient = ui->lineEdit_nomC->text().toStdString();
    string prenomClient = ui->lineEdit_prenomC->text().toStdString();
    string telClient = ui->lineEdit_telCli->text().toStdString();
    string mailClient = ui->lineEdit_mailC->text().toStdString();
    string mdpClient = ui->lineEdit_mdpCli->text().toStdString();

    // Recuperation des informations concernant l'adresse d'un client
    int numeroAdr = ui->lineEdit_numero->text().toInt();
    string rueAdr = ui->lineEdit_rue->text().toStdString();
    string villeAdr = ui->lineEdit_ville->text().toStdString();
    int cp = ui->lineEdit_cp->text().toInt();
    string pays = ui->lineEdit_pays->text().toStdString();

    // Creation des instances Adresse et Client
    Adresse adr(cli.getAdresse().getIdAdresse(),numeroAdr,rueAdr,villeAdr, cp, pays);
    Client cli2(cli.getIdClient(),nomClient,prenomClient,telClient,mailClient,mdpClient,adr);

    // Modification des informations
    if((clidao.updater(cli2)).getIdClient()!=-1){
        // Message de confirmation
        QMessageBox::information(this, "Valider", "Votre modification a bien été enregistrée !");

        // Actualisation des informations
        afficherInformations();
    }
    else {
        // Message d'erreur
        QMessageBox::information(this, "Erreur", "Quelque chose s'est produit... Veuillez réessayer !");
    }

}

void ClientCompteDialog::afficherHistoriqueResa(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT * "
                            "FROM reservation "
                            "JOIN client ON reservation.idClient=client.idClient "
                            "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                            "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                            "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                                "WHERE client.mailClient='" + mail +"'; "
                                "ORDER BY reservation.dateArrive;";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeResaHisto->setRowCount(query.size());
        int row_number = 0;

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
            ui->tableWidget_ListeResaHisto->setItem(row_number,0, new QTableWidgetItem(nomHotel));
            ui->tableWidget_ListeResaHisto->setItem(row_number,1, new QTableWidgetItem(numChambre));
            ui->tableWidget_ListeResaHisto->setItem(row_number,2, new QTableWidgetItem(nbCouchages));
            ui->tableWidget_ListeResaHisto->setItem(row_number,3, new QTableWidgetItem(prixChambre));
            ui->tableWidget_ListeResaHisto->setItem(row_number,4, new QTableWidgetItem(adresse));
            ui->tableWidget_ListeResaHisto->setItem(row_number,5, new QTableWidgetItem(dateA));
            ui->tableWidget_ListeResaHisto->setItem(row_number,6, new QTableWidgetItem(dateD));

            // Gerer statut de la reservation
            if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 0){
                ui->tableWidget_ListeResaHisto->setItem(row_number,7, new QTableWidgetItem("En attente de Validation"));
            }
            else if (query.value("reservation.estValide").toInt() == 0 && query.value("reservation.estTraite").toInt() == 1){
                ui->tableWidget_ListeResaHisto->setItem(row_number, 7, new QTableWidgetItem("Invalide"));
            }
            else if (query.value("reservation.estValide").toInt() == 1 && query.value("reservation.estTraite").toInt() == 1){
                ui->tableWidget_ListeResaHisto->setItem(row_number, 7, new QTableWidgetItem("Valide"));
            }

            // Incrementation du nombre de colonnes
            row_number = row_number + 1;
        }
    }

    // Fermeture de la connexion a bdd
    db.close();
}

void ClientCompteDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance ClientCompteDialog
    this->close();
}


void ClientCompteDialog::on_account_clicked()
{
    // Créer une boîte de message d'information
    QMessageBox msgBox;
    msgBox.setWindowTitle("Demande de redirection");
    msgBox.setText("Voulez-vous vous déconnecter ?");

    // Ajout de boutons
    QPushButton* btnOui = msgBox.addButton(tr("Oui"), QMessageBox::YesRole);
    QPushButton* btnNon = msgBox.addButton(tr("Non"), QMessageBox::NoRole);

    // Bouton par défaut
    msgBox.setDefaultButton(btnNon);

    // Afficher la boîte de message et récupérer la réponse de l'utilisateur
    msgBox.exec();
    QAbstractButton* clickedButton = msgBox.clickedButton();

    // Si un bouton a été cliqué
    if (clickedButton) {
        // Si l'utilisateur veut se déconnecter
        if (clickedButton == btnOui) {
            // Creation instance HomePageDialog
            MainWindow* mainWindow = new MainWindow(this);

            // Affichage de l'instance HomePageDialog
            mainWindow->showMaximized();

            // Fermeture de l'instance ClientCompteDialog
            this->close();
        }
    }
}


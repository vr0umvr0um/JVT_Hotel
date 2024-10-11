#include "listeclientsdialog.h"
#include "ui_listeclientsdialog.h"
#include "emprespcomptedialog.h"
#include "singleconnection.h"
#include "homepagedialog.h"
#include "listechambresrespdialog.h"
#include "listeemployesdialog.h"
#include "adresse.h"
#include "adressedao.h"
#include "clientdao.h"

listeClientsDialog::listeClientsDialog(QWidget *parent, QString userType, QString mail, QString mdp)
    : QDialog(parent)
    , ui(new Ui::listeClientsDialog)
{
    db = SingleConnection::getInstance();
    ui->setupUi(this);
    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);
    this->ut = userType;
    this->ma = mail;
    this->md = mdp;
    AfficheListeClients();
    db.close();
}

listeClientsDialog::~listeClientsDialog()
{
    delete ui;
}

void listeClientsDialog::AfficheListeClients(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM client "
                            "JOIN adresse ON client.idAdresse = adresse.idAdresse ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeClients->setRowCount(query.size());
        int row_number = 0;

        // Effacer les informations déjà présente dans QComboBox
        ui->comboBoxSuppCli->clear();

        // Iterer à travers les resultats de la requete
        while(query.next()){
            // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
            ui->tableWidget_ListeClients->setItem(row_number,0, new QTableWidgetItem(query.value("client.idClient").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,1, new QTableWidgetItem(query.value("client.nomClient").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,2, new QTableWidgetItem(query.value("client.prenomClient").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,3, new QTableWidgetItem(query.value("client.telephone").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,4, new QTableWidgetItem(query.value("client.mailClient").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,5, new QTableWidgetItem(query.value("client.mdpClient").toString()));
            ui->tableWidget_ListeClients->setItem(row_number,6, new QTableWidgetItem(query.value("client.idAdresse").toString()));
            row_number = row_number + 1;

            // Creer un affichage pour l'element QComboBox
            QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                        .arg(query.value("client.idClient").toString())
                                        .arg(query.value("client.nomClient").toString())
                                        .arg(query.value("client.prenomClient").toString())
                                        .arg(query.value("client.telephone").toString())
                                        .arg(query.value("client.mailClient").toString())
                                        .arg(query.value("client.mdpClient").toString())
                                        .arg(query.value("client.idAdresse").toString());

            // Ajouter l'element aux QComboBox
            ui->comboBoxSuppCli->addItem(displayString);
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeClients->resizeRowsToContents();
    ui->tableWidget_ListeClients->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}
void listeClientsDialog::on_pushButton_ValiderAjoutCli_clicked()
{
    //Infos du client
    QString nomClient = ui->lineEdit_CNom->text();
    QString prenomClient = ui->lineEdit_CPrenom->text();
    QString telephone = ui->lineEdit_CTel->text();
    QString mailClient = ui->lineEdit_CMail->text();
    QString mdpClient = ui->lineEdit_CMdp->text();

    //Infos de l'adresse du client
    QString numero = ui->lineEdit_CNumero->text();
    QString rue = ui->lineEdit_CRue->text();
    QString ville = ui->lineEdit_CVille->text();
    QString codePostal = ui->lineEdit_CCodePostal->text();
    QString pays = ui->lineEdit_CPays->text();

    if(nomClient!="" && prenomClient!="" && telephone!="" && mailClient!="" && mdpClient!=""){
        if(numero!="" && rue!="" && ville!="" && codePostal!="" && pays!=""){
            Adresse adr(-1, numero.toInt(), rue.toStdString(), ville.toStdString(), codePostal.toInt(), pays.toStdString());
            ClientDAO cli2DAO;
            Client cli(-1, nomClient.toStdString(), prenomClient.toStdString(), telephone.toStdString(), mailClient.toStdString(), mdpClient.toStdString(), adr);

            if((cli2DAO.creer(cli)).getIdClient() != -1){
                QMessageBox::information(this, "Valider", "La création du client a été effectué");

                // Créer une boîte de message d'information
                QMessageBox msgBox;
                msgBox.setWindowTitle("Demande de redirection");
                msgBox.setText("Voulez-vous vous modifier d'autres clients ?");

                // Ajout de boutons
                QPushButton* btnOui = msgBox.addButton(tr("Oui"), QMessageBox::YesRole);
                QPushButton* btnNon = msgBox.addButton(tr("Non"), QMessageBox::NoRole);

                // Bouton par défaut
                msgBox.setDefaultButton(btnNon);

                // Afficher la boîte de message et récupérer la réponse de l'utilisateur
                msgBox.exec();
                QAbstractButton* clickedButton = msgBox.clickedButton();

                // Si pas d'autres réservations à faire
                if (clickedButton) {
                    if (clickedButton == btnOui) {

                        //Actualiser la page
                        AfficheListeClients();
                        //Réinitialisation des infos du client
                        ui->lineEdit_CNom->setText("");
                        ui->lineEdit_CPrenom->setText("");
                        ui->lineEdit_CTel->setText("");
                        ui->lineEdit_CMail->setText("");
                        ui->lineEdit_CMdp->setText("");

                        //Réinitialisation des infos de l'adresse du client
                        ui->lineEdit_CNumero->setText("");
                        ui->lineEdit_CRue->setText("");
                        ui->lineEdit_CVille->setText("");
                        ui->lineEdit_CCodePostal->setText("");
                        ui->lineEdit_CPays->setText("");

                    } else if (clickedButton == btnNon){
                        // Creation instance HomePageDialog
                        HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

                        // Affichage de l'instance HomePageDialog
                        homePageDialog->showMaximized();

                        // Fermeture de l'instance DemandeResaDialog
                        this->close();
                    }
                }
            }else{
                QMessageBox::information(this, "Valider", "ERREUR : La création du client n'a pas été effectué");
                //---Actualiser la page---
                AfficheListeClients();

            }
        }else {
            QMessageBox::information(this, "Valider", "ERREUR : Veuillez remplir tous les champs concernant l'adresse avant de valider");
        }
    }else {
        QMessageBox::information(this, "Valider", "ERREUR : Veuillez remplir tous les champs concernant le client avant de valider");
    }
}


void listeClientsDialog::on_pushButton_ValiderSuppCli_clicked()
{
    QString idClient = ui->comboBoxSuppCli->currentText().split(" - ").at(0);
    QString nomClient = ui->comboBoxSuppCli->currentText().split(" - ").at(1);
    QString prenomClient = ui->comboBoxSuppCli->currentText().split(" - ").at(2);
    QString telephone = ui->comboBoxSuppCli->currentText().split(" - ").at(3);
    QString mailClient = ui->comboBoxSuppCli->currentText().split(" - ").at(4);
    QString mdpClient = ui->comboBoxSuppCli->currentText().split(" - ").at(5);
    QString idAdresse = ui->comboBoxSuppCli->currentText().split(" - ").at(6);

    AdresseDAO adrDAO;
    Adresse adr = adrDAO.lire(idAdresse.toInt());
    ClientDAO cliDAO;
    Client cli(idClient.toInt(), nomClient.toStdString(), prenomClient.toStdString(), telephone.toStdString(), mailClient.toStdString(), mdpClient.toStdString(), adr);
    cliDAO.supprimer(cli);


    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM client "
                            "JOIN adresse ON client.idAdresse = adresse.idAdresse "
                            "WHERE client.idClient='" + idClient + "' AND client.nomClient='" + nomClient +
                            "' AND client.prenomClient='" + prenomClient + "' AND client.telephone='" + telephone +
                            "' AND client.mailClient='" + mailClient + "' AND client.mdpClient='" + mdpClient +
                            "' AND client.idAdresse='" + idAdresse + "';";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        if(!query.next()){
            QMessageBox::information(this, "Valider", "La suppression du client a été effectué");

            // Créer une boîte de message d'information
            QMessageBox msgBox;
            msgBox.setWindowTitle("Demande de redirection");
            msgBox.setText("Voulez-vous vous modifier d'autres clients ?");

            // Ajout de boutons
            QPushButton* btnOui = msgBox.addButton(tr("Oui"), QMessageBox::YesRole);
            QPushButton* btnNon = msgBox.addButton(tr("Non"), QMessageBox::NoRole);

            // Bouton par défaut
            msgBox.setDefaultButton(btnNon);

            // Afficher la boîte de message et récupérer la réponse de l'utilisateur
            msgBox.exec();
            QAbstractButton* clickedButton = msgBox.clickedButton();

            // Si pas d'autres réservations à faire
            if (clickedButton) {
                if (clickedButton == btnOui) {

                    //Actualiser la page
                    AfficheListeClients();

                } else if (clickedButton == btnNon){
                    // Creation instance HomePageDialog
                    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

                    // Affichage de l'instance HomePageDialog
                    homePageDialog->showMaximized();

                    // Fermeture de l'instance DemandeResaDialog
                    this->close();
                }
            }
        }else{
            QMessageBox::information(this, "Valider", "ERREUR : La suppression du client n'a pas été effectué");
            //---Actualiser la page---
            AfficheListeClients();
        }
    }
    db.close();
}


void listeClientsDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance listeEmployesDialog
    this->close();
}


void listeClientsDialog::on_account_clicked()
{
        // Creation instance empRespCompteDialog
        empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->ut, this->ma, this->md);

        // Affichage de l'instance empRespCompteDialog
        empRespCompteDialog->showMaximized();

        // Fermer l'instance HomPageDialog
        this->close();
}


void listeClientsDialog::on_pushButtonListeEmployes_clicked()
{
    // Creation instance listeEmployesDialog
    listeEmployesDialog* listeEmployesDialog = new class listeEmployesDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance listeEmployesDialog
    listeEmployesDialog->showMaximized();

    // Fermeture de l'instance listeClientsDialog
    this->close();
}


void listeClientsDialog::on_pushButton_AfficherChambres_clicked()
{
    //Creation instance listeChambresRespDialog
    listeChambresRespDialog* listeChambresRespDialog = new class listeChambresRespDialog(this, this->ut, this->ma, this->md);

    //Affichage de l'instance listeChambresRespDialog
    listeChambresRespDialog->showMaximized();

    //Fermer l'instance listeClientsDialog
    this->close();
}


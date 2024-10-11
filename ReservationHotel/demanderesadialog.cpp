#include "demanderesadialog.h"
#include "ui_demanderesadialog.h"

#include "chambredao.h"
#include "clientdao.h"
#include "reservationdao.h"

#include "clientinscriptiondialog.h"
#include "homepagedialog.h"

#include "singleconnection.h"

DemandeResaDialog::DemandeResaDialog(QWidget *parent, QString ut, QString m, QString pwd)
    : QDialog(parent)
    , ui(new Ui::DemandeResaDialog)
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

    // Fonction pour afficher les hotels dans le QTableWidgetItem
    afficherListeHotel();

    // Pop up d'un calendrier quand modification de la date d'arrivee et de depart
    ui->dateEdit_dateArr->setCalendarPopup(true);
    ui->dateEdit_dateDep->setCalendarPopup(true);

    // Date du jour sur les QDateEdit
    QDate dateAjd = QDate::currentDate();
    ui->dateEdit_dateArr->setDate(dateAjd);
    ui->dateEdit_dateDep->setDate(dateAjd);

    // Fermeture de la connexion a bdd
    db.close();
}

DemandeResaDialog::~DemandeResaDialog()
{
    delete ui;
}


void DemandeResaDialog::afficherListeHotel() {
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT * "
                            "FROM hotel "
                            "JOIN adresse ON hotel.idAdresse = adresse.idAdresse "
                            "JOIN chambre ON hotel.idHotel = chambre.idHotel;";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Effacer les informations déjà présente dans QComboBox
        ui->comboBox_listeHotel->clear();

        // Iterer à travers les resultats de la requete
        while (query.next()) {
            // Extraire les données de la ligne actuelle
            QString nomHotel = query.value("hotel.nomHotel").toString();
            QString numChambre = query.value("chambre.numChambre").toString();
            QString nbCouchages = query.value("chambre.nbCouchages").toString();
            QString prix = query.value("chambre.prix").toString();
            QString numero = query.value("adresse.numero").toString();
            QString rue = query.value("adresse.rue").toString();
            QString ville = query.value("adresse.ville").toString();
            QString codePostal = query.value("adresse.codePostal").toString();
            QString pays = query.value("adresse.pays").toString();

            // Creer un affichage pour l'element QComboBox
            QString displayString = QString("%1 - %2 - %3 - %4 - %5")
                                        .arg(nomHotel)
                                        .arg(numChambre)
                                        .arg(nbCouchages)
                                        .arg(prix)
                                        .arg(QString("%1 %2 %3 %4 %5").arg(numero, rue, ville, codePostal, pays));

            // Ajouter l'element a la QComboBox
            ui->comboBox_listeHotel->addItem(displayString);
        }
    }

    // Fermeture de la connexion a bdd
    db.close();
}


void DemandeResaDialog::on_pushButton_signupCli_clicked()
{
    // Si type d'utilisateur est un client
    if(userType == "client"){
        // Information concernant ces droits
        QMessageBox::information(this, "PAS ENCORE CLIENT?", "Vous n'avez pas les droits !");
    }
    else {
        // Creation instance ClientInscriptionDialog
        ClientInscriptionDialog* clientInscriptionDialog = new ClientInscriptionDialog(this);

        // Affichage de l'instance ClientInscriptionDialog
        clientInscriptionDialog->showMaximized();
    }
}


void DemandeResaDialog::on_pushButton_val_clicked()
{
    // Recuperation des dates de l'interface graphique
    QDate dateArr = ui->dateEdit_dateArr->date();
    QDate dateDep = ui->dateEdit_dateDep->date();

    // Si la date de depart est strictement inferieur a la date d'arrivée
    if (dateArr > dateDep){
        // Message d'erreur
        QMessageBox::information(this, "Réservation interrompue", "Vous avez choisi une date de départ antérieure à celle d'arrivée...");
    } else {
        // Conversion QDate en std::string
        string dateArrS = dateArr.toString("yyyy-MM-dd").toStdString();
        string dateDepS = dateDep.toString("yyyy-MM-dd").toStdString();

        // Recuperation information Client
        QString mailCli = ui->lineEdit_mailCli->text();

        // Creation instances Client & ClientDAO
        ClientDAO cliDAO;
        Client cli = cliDAO.lire(mailCli);

        // Recuperation information Chambre
        QString numChambre = ui->comboBox_listeHotel->currentText().split(" - ").at(1);

        // Creation instances Chambre & ChambreDAO
        ChambreDAO chDAO;
        Chambre ch = chDAO.lire(numChambre);

        // Creation instances Reservation & ReservationDAO
        ReservationDAO resDAO;
        Reservation res(0,dateArrS,dateDepS,0, 0,ch,cli);

        // Creation de la demande de reservation
        if(resDAO.creer(res).getIdReservation()!= 0){
            QMessageBox::information(this, "Réservation validée", "Votre demande a bien été enregistrée !");

            // Créer une boîte de message d'information
            QMessageBox msgBox;
            msgBox.setWindowTitle("Demande de Réservation");
            msgBox.setText("Voulez-vous faire une autre réservation ?");

            // Ajout de boutons
            QPushButton* btnOui = msgBox.addButton(tr("Oui"), QMessageBox::YesRole);
            QPushButton* btnNon = msgBox.addButton(tr("Non"), QMessageBox::NoRole);

            // Bouton par défaut
            msgBox.setDefaultButton(btnOui);

            // Afficher la boîte de message et récupérer la réponse de l'utilisateur
            msgBox.exec();
            QAbstractButton* clickedButton = msgBox.clickedButton();

            // Si bouton cliqué
            if (clickedButton) {
                // Si pas d'autres réservations à faire
                if (clickedButton == btnNon) {
                    // Creation instance HomePageDialog
                    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

                    // Affichage de l'instance HomePageDialog
                    homePageDialog->showMaximized();

                    // Fermeture de l'instance DemandeResaDialog
                    this->close();
                } else {
                    // Creation instance DemandeResaDialog
                    DemandeResaDialog* demandeResaDialog = new DemandeResaDialog(this, this->userType, this->mail, this->mdp);

                    // Affichage de l'instance DemandeResaDialog
                    demandeResaDialog->showMaximized();

                    // Fermer l'instance DemandeResaDialog
                    this->close();
                }
            }
        }
        else {
            // Message d'erreur
            QMessageBox::information(this, "Réservation interrompue", "Quelque chose s'est produit... Veuillez réessayer !");
        }
    }
}

void DemandeResaDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}

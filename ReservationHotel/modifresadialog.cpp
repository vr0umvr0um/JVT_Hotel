#include "modifresadialog.h"
#include "ui_modifresadialog.h"

#include "clientdao.h"
#include "chambredao.h"

#include "demandemodifresadialog.h"
#include "homepagedialog.h"

#include "singleconnection.h"

ModifResaDialog::ModifResaDialog(QWidget *parent, QString ut, QString m, const Reservation &reservation, QString pwd)
    : QDialog(parent)
    , ui(new Ui::ModifResaDialog)
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
    this->resa=reservation;
    this->mdp=pwd;

    // Pop up d'un calendrier quand modification de la date d'arrivee et de depart
    ui->dateEdit_dateArr->setCalendarPopup(true);
    ui->dateEdit_dateDep->setCalendarPopup(true);

    // Si l'utilisateur est un client
    if(userType=="client"){
        // Ajout de son mail au QLineEdit
        ui->lineEdit_mailCli->setText(this->mail);

        // Impossibilité pour lui de modifier son adresse mail
        ui->lineEdit_mailCli->setReadOnly(true);
    }
    else {
        // Ajout du mail du client de la reservation
        ui->lineEdit_mailCli->setText(QString::fromStdString(resa.getClient().getMailClient()));
    }

    // Impossibilité de modifier adresse mail
    ui->lineEdit_mailCli->setReadOnly(true);

    // Initialisation des QDate && Conversion std::string en QDate
    string dateAS = (resa.getDateArrive());
    this->dateArrive = QString::fromUtf8(dateAS.data(), dateAS.size());
    QDate dateA = QDate::fromString(dateArrive, "yyyy-MM-dd");
    ui->dateEdit_dateArr->setDate(dateA);
    string dateDS = (resa.getDateDepart());
    this->dateDepart = QString::fromUtf8(dateDS.data(), dateDS.size());
    QDate dateD = QDate::fromString(dateDepart, "yyyy-MM-dd");
    ui->dateEdit_dateDep->setDate(dateD);

    // Initialisation numChambre && Conversion int en QString
    int ncS = resa.getChambre().getNumChambre();
    QString numChambre = QString::number(ncS);

    // Fonction qui affiche les informations de reservation selon des paramètres
    afficherInformationsResa(dateArrive, dateDepart, mail, numChambre);

    // Fonction pour afficher les hotels dans le QTableWidgetItem
    afficherListeHotel();

    // Fermeture de la connexion a bdd
    db.close();
}

ModifResaDialog::~ModifResaDialog()
{
    delete ui;
}

void ModifResaDialog::afficherInformationsResa(QString dateArrive, QString dateDepart, QString mailClient, QString numChambre){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT * "
                            "FROM reservation "
                            "JOIN client ON reservation.idClient=client.idClient "
                            "JOIN chambre ON reservation.numChambre=chambre.numChambre "
                            "JOIN hotel ON chambre.idHotel=hotel.idHotel "
                            "JOIN adresse ON hotel.idAdresse=adresse.idAdresse "
                            "WHERE reservation.dateArrive='" + dateArrive + "' "
                                "AND reservation.dateDepart='" + dateDepart + "' "
                                "AND client.mailClient='" + mailClient + "' "
                                "AND reservation.numChambre='" + numChambre + "';";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Effacer les informations déjà présente dans QComboBox
        ui->comboBox_listeHotel->clear();

        // Iterer à travers les resultats de la requete
        if(query.next()) {
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
            ui->comboBox_listeHotel->insertItem(0, displayString);
        }
        else{
            // Message d'erreur
            qDebug() << "Requete next() incorrecte" << query.lastError().text();
        }
    }

    // Fermeture de la connexion a bdd
    db.close();
}

void ModifResaDialog::afficherListeHotel(){
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

void ModifResaDialog::on_pushButton_val_clicked()
{
    // Recuperation des dates de l'interface graphique
    QDate dateArr = ui->dateEdit_dateArr->date();
    QDate dateDep = ui->dateEdit_dateDep->date();

    string dateArrS = dateArr.toString("yyyy-MM-dd").toStdString();
    string dateDepS = dateDep.toString("yyyy-MM-dd").toStdString();

    // Recuperation information Client
    QString mailCli = ui->lineEdit_mailCli->text();

    // Creation instances Client & ClientDAO
    ClientDAO cliDAO;
    Client cli = cliDAO.lire(mailCli);

    // Recuperation information Chambre
    QString nC = ui->comboBox_listeHotel->currentText().split(" - ").at(1);

    // Creation instances Chambre & ChambreDAO
    ChambreDAO chDAO;
    Chambre ch = chDAO.lire(nC);

    // Creation instances Reservation & ReservationDAO
    ReservationDAO resDAO;
    int idR = (resa.getIdReservation());
    int estValide = (resa.getEstValide());
    int estTraite = (resa.getEstTraite());
    Reservation res(idR,dateArrS,dateDepS,estValide,estTraite,ch,cli);

    // Modification de la reservation
    resDAO.updater(res);

    QMessageBox::information(this, "Valider", "Votre reservation a bien été modifié !");

    afficherInformationsResa(dateArr.toString("yyyy-MM-dd"), dateDep.toString("yyyy-MM-dd"), mailCli, nC);

    // Créer une boîte de message d'information
    QMessageBox msgBox;
    msgBox.setWindowTitle("Valider");
    msgBox.setText("Voulez-vous faire une autre modification de réservation ?");

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
        // Si pas d'autres modifications de réservations à faire
        if (clickedButton == btnNon) {
            // Fermeture de l'instance ModifResaDialog
            this->close();

            // Creation instance HomePageDialog
            HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

            // Affichage de l'instance HomePageDialog
            homePageDialog->showMaximized();
        // Si d'autres modifications de reservations a faire
        } else if(clickedButton == btnOui) {
            // Creation instance DemandeModifResaDialog
            DemandeModifResaDialog* demandeModifResaDialog = new DemandeModifResaDialog(this, this->userType, this->mail, this->mdp);

            // Affichage de l'instance DemandeModifResaDialog
            demandeModifResaDialog->showMaximized();

            // Fermer l'instance ModifResaDialog
            this->close();
        }
    }
}

void ModifResaDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


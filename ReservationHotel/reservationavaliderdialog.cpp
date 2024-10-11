#include "reservationavaliderdialog.h"
#include "ui_reservationavaliderdialog.h"

#include "chambre.h"
#include "client.h"
#include "reservation.h"

#include "administrateurdao.h"
#include "chambredao.h"
#include "clientdao.h"
#include "reservationdao.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "empcomptedialog.h"
#include "emprespcomptedialog.h"
#include "homepagedialog.h"
#include "listechambresdialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

ReservationAvaliderDialog::ReservationAvaliderDialog(QWidget *parent, QString userType, QString mail, QString mdp)
    : QDialog(parent)
    , ui(new Ui::ReservationAvaliderDialog)
{
    db = SingleConnection::getInstance();
    ui->setupUi(this);
    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);
    this->ut = userType;
    this->ma = mail;
    this->md = mdp;
    AfficherResa();
    db.close();
}

ReservationAvaliderDialog::~ReservationAvaliderDialog()
{
    delete ui;
}

void ReservationAvaliderDialog::AfficherResa(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM reservation "
                            "JOIN chambre ON reservation.numChambre = chambre.numChambre "
                            "JOIN client ON reservation.idClient = client.idClient ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeResaNT->setRowCount(query.size());
        ui -> tableWidget_ListeResaDV->setRowCount(query.size());
        int row_number1 = 0;
        int row_number3 = 0;

        // Iterer à travers les resultats de la requete
        while(query.next()){
            if(query.value("reservation.estValide").toInt() == 1){
                // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
                ui->tableWidget_ListeResaDV->setItem(row_number3,0, new QTableWidgetItem(query.value("reservation.idReservation").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,1, new QTableWidgetItem(query.value("reservation.dateArrive").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,2, new QTableWidgetItem(query.value("reservation.dateDepart").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,3, new QTableWidgetItem(query.value("reservation.estValide").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,4, new QTableWidgetItem(query.value("reservation.estTraite").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,5, new QTableWidgetItem(query.value("reservation.numChambre").toString()));
                ui->tableWidget_ListeResaDV->setItem(row_number3,6, new QTableWidgetItem(query.value("reservation.idClient").toString()));
                row_number3 = row_number3 + 1;

            } else if(query.value("reservation.estTraite").toInt() == 0){
                // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
                ui->tableWidget_ListeResaNT->setItem(row_number1,0, new QTableWidgetItem(query.value("reservation.idReservation").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,1, new QTableWidgetItem(query.value("reservation.dateArrive").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,2, new QTableWidgetItem(query.value("reservation.dateDepart").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,3, new QTableWidgetItem(query.value("reservation.estValide").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,4, new QTableWidgetItem(query.value("reservation.estTraite").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,5, new QTableWidgetItem(query.value("reservation.numChambre").toString()));
                ui->tableWidget_ListeResaNT->setItem(row_number1,6, new QTableWidgetItem(query.value("reservation.idClient").toString()));
                row_number1 = row_number1 + 1;

                // Creer un affichage pour l'element QComboBox
                QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7")
                                            .arg(query.value("reservation.idReservation").toString())
                                            .arg(query.value("reservation.dateArrive").toString())
                                            .arg(query.value("reservation.dateDepart").toString())
                                            .arg(query.value("reservation.estValide").toString())
                                            .arg(query.value("reservation.estTraite").toString())
                                            .arg(query.value("reservation.numChambre").toString())
                                            .arg(query.value("reservation.idClient").toString());

                // Ajouter l'element a la QComboBox
                ui->comboBox_listeResaNT->addItem(displayString);
            }
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeResaNT->resizeRowsToContents();
    ui->tableWidget_ListeResaNT->resizeColumnsToContents();
    ui->tableWidget_ListeResaDV->resizeRowsToContents();
    ui->tableWidget_ListeResaDV->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}

void ReservationAvaliderDialog::on_pushButton_AfficherChambres_clicked()
{
    {
        //Creation instance listeChambresDialog
        listeChambresDialog* listeChambresDialog = new class listeChambresDialog(this, ut, ma, md);

        //Affichage de l'instance listeChambresDialog
        listeChambresDialog->showMaximized();

        //Fermer l'instance EmpCompteDialog
        this->close();
    }
}

void ReservationAvaliderDialog::on_account_clicked()
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

    // Si pas d'autres réservations à faire
    if (clickedButton) {
        if (clickedButton == btnOui) {
            // Creation instance HomePageDialog
            MainWindow* mainWindow = new MainWindow(this);

            // Affichage de l'instance HomePageDialog
            mainWindow->showMaximized();

            // Fermeture de l'instance DemandeResaDialog
            this->close();
        } else {
            if(ut == "emp"){
                // Creation instance EmpCompteDialog
                EmpCompteDialog* empCompteDialog = new EmpCompteDialog(this, this->ut, this->ma, this->md);

                // Affichage de l'instance EmpCompteDialog
                empCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
            else if(ut == "client"){
                // Creation instance ClientCompteDialog
                ClientCompteDialog* clientCompteDialog = new ClientCompteDialog(this, this->ut, this->ma, this->md);

                // Affichage de l'instance AnnuleResaDialog
                clientCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
            else if(ut == "admin"){
                // Creation instance Administrateur DAO
                AdministrateurDAO admindao;             //Pour ?
                // Affichage de l'instance AdminCompteDialog
                AdminCompteDialog* adminCompteDialog = new AdminCompteDialog(this, admindao.connexionAdmin(this->ma, this->md));
                adminCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }else if(ut == "empR"){
                // Creation instance empRespCompteDialog
                empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->ut, this->ma, this->md);

                // Affichage de l'instance empRespCompteDialog
                empRespCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
        }
    }
}

void ReservationAvaliderDialog::on_pushButton_ConfimerNT_clicked()
{
    if(ui->checkBox_ValiderResaNT->isChecked()){
        int idResa = ui->comboBox_listeResaNT->currentText().split(" - ").at(0).toInt();
        string dateArr = ui->comboBox_listeResaNT->currentText().split(" - ").at(1).toStdString();
        string dateDep = ui->comboBox_listeResaNT->currentText().split(" - ").at(2).toStdString();
        int estTraite = ui->comboBox_listeResaNT->currentText().split(" - ").at(4).toInt();
        int numChambre = ui->comboBox_listeResaNT->currentText().split(" - ").at(5).toInt();
        int idClient = ui->comboBox_listeResaNT->currentText().split(" - ").at(6).toInt();
        qDebug() << "4 = " << idResa;
        qDebug() << "2024-05-11 = " << dateArr;
        qDebug() << "2024-05-14 = " << dateDep;
        qDebug() << "0 = " << estTraite;
        qDebug() << "4 = " << numChambre;
        qDebug() << "2 = " << idClient;
        ChambreDAO chaDAO;
        Chambre cha = chaDAO.lire(numChambre);
        ClientDAO cliDAO;
        Client cli = cliDAO.lire(idClient);
        ReservationDAO resaDAO;
        Reservation resa(idResa, dateArr, dateDep, 1, 1, cha, cli);
        qDebug() << "NT : idResa : " << resa.getIdReservation();
        qDebug() << "NT : dateArr : " << resa.getDateArrive();
        qDebug() << "NT : dateDep : " << resa.getDateDepart();
        qDebug() << "NT : estValide : " << resa.getEstValide();
        qDebug() << "NT : estTraite : " << resa.getEstTraite();
        Reservation resaUp = resaDAO.updater(resa);

        if(resaUp.getIdReservation()!=-1){
            qDebug() << "NT : idResa : " << resaUp.getIdReservation();
            qDebug() << "NT : estValide : " << resaUp.getEstValide();
            qDebug() << "NT : estTraite : " << resaUp.getEstTraite();
            QMessageBox::information(this, "Valider", "Validation de la réservation enregistrée");
            //---Actualiser la page---
            // Creation instance ReservationAvaliderDialog
            ReservationAvaliderDialog* ReservationAvaliderDialog = new class ReservationAvaliderDialog(this, this->ut, this->ma, this->md);

            // Affichage de l'instance ReservationAvaliderDialog
            ReservationAvaliderDialog->showMaximized();

            // Fermer l'instance HomPageDialog
            this->close();
        }else {
            QMessageBox::information(this, "Valider", "ERROR : Validation de la réservation");
        }

    }else {
        int idResa = ui->comboBox_listeResaNT->currentText().split(" - ").at(0).toInt();
        string dateArr = ui->comboBox_listeResaNT->currentText().split(" - ").at(1).toStdString();
        string dateDep = ui->comboBox_listeResaNT->currentText().split(" - ").at(2).toStdString();
        QString numChambre = ui->comboBox_listeResaNT->currentText().split(" - ").at(5);
        QString idClient = ui->comboBox_listeResaNT->currentText().split(" - ").at(6);

        ChambreDAO chaDAO;
        Chambre cha = chaDAO.lire(numChambre);
        ClientDAO cliDAO;
        Client cli = cliDAO.lire(idClient);
        ReservationDAO resaDAO;
        Reservation resa(idResa, dateArr, dateDep, 0, 1, cha, cli);


        if(resaDAO.updater(resa).getIdReservation()!=-1){
            Reservation re = resaDAO.lire(resa.getIdReservation());
            qDebug() << "estValide : " << re.getEstValide() << " , estTraite : " << re.getEstTraite();
            QMessageBox::information(this, "Valider", "Non validation de la réservation enregistrée");
            //---Actualiser la page---
            // Creation instance ReservationAvaliderDialog
            ReservationAvaliderDialog* ReservationAvaliderDialog = new class ReservationAvaliderDialog(this, this->ut, this->ma, this->md);

            // Affichage de l'instance ReservationAvaliderDialog
            ReservationAvaliderDialog->showMaximized();

            // Fermer l'instance HomPageDialog
            this->close();
        }else {
            QMessageBox::information(this, "Valider", "ERROR : Non validation de la réservation");
        }
    }
}

void ReservationAvaliderDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


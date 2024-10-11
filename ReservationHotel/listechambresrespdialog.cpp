#include "listechambresrespdialog.h"
#include "ui_listechambresrespdialog.h"

#include "administrateurdao.h"
#include "chambredao.h"
#include "hoteldao.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "empcomptedialog.h"
#include "homepagedialog.h"
#include "emprespcomptedialog.h"
#include "listeclientsdialog.h"
#include "listeemployesdialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

listeChambresRespDialog::listeChambresRespDialog(QWidget *parent, QString userType, QString mail, QString mdp)
    : QDialog(parent)
    , ui(new Ui::listeChambresRespDialog)
{
    db = SingleConnection::getInstance();
    ui->setupUi(this);
    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);
    this->ut = userType;
    this->ma = mail;
    this->md = mdp;
    Afficherchambres();
    db.close();
}

listeChambresRespDialog::~listeChambresRespDialog()
{
    delete ui;
}

void listeChambresRespDialog::Afficherchambres(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM chambre "
                            "JOIN hotel ON chambre.idHotel = hotel.idHotel ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeChambres->setRowCount(query.size());
        int row_number = 0;

        // Effacer les informations déjà présente dans QComboBox
        ui->comboBox_ChambreModifPrix->clear();
        ui->comboBox_ChambreSupp->clear();

        // Iterer à travers les resultats de la requete
        while(query.next()){
            // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
            ui->tableWidget_ListeChambres->setItem(row_number,0, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.prix").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,3, new QTableWidgetItem(query.value("chambre.idHotel").toString()));
            row_number = row_number + 1;

            // Creer un affichage pour l'element QComboBox
            QString displayString = QString("%1 - %2 - %3 - %4")
                                        .arg(query.value("chambre.numChambre").toString())
                                        .arg(query.value("chambre.prix").toString())
                                        .arg(query.value("chambre.nbCouchages").toString())
                                        .arg(query.value("chambre.idHotel").toString());

            // Ajouter l'element aux QComboBox
            ui->comboBox_ChambreSupp->addItem(displayString);
            ui->comboBox_ChambreModifPrix->addItem(displayString);
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeChambres->resizeRowsToContents();
    ui->tableWidget_ListeChambres->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}

void listeChambresRespDialog::on_pushButton_ConfimerSupp_clicked()
{
    QString numChambre = ui->comboBox_ChambreSupp->currentText().split(" - ").at(0);
    QString prix = ui->comboBox_ChambreSupp->currentText().split(" - ").at(1);
    QString nbCouchages = ui->comboBox_ChambreSupp->currentText().split(" - ").at(2);
    QString idH = ui->comboBox_ChambreSupp->currentText().split(" - ").at(3);

    HotelDAO hotDAO;
    Hotel hot = hotDAO.lire(idH.toInt());
    ChambreDAO chaDAO;
    Chambre cha(numChambre.toInt(), prix.toInt(), nbCouchages.toInt(), hot);
    chaDAO.supprimer(cha);

    QMessageBox::information(this, "Valider", "La suppression de la chambre a été effectué");
    //---Actualiser la page---
    Afficherchambres();
}


void listeChambresRespDialog::on_pushButton_ConfimerModifPrix_clicked()
{
    int numChambre = ui->comboBox_ChambreModifPrix->currentText().split(" - ").at(0).toInt();
    int nbCouchages = ui->comboBox_ChambreModifPrix->currentText().split(" - ").at(2).toInt();
    int idHotel = ui->comboBox_ChambreModifPrix->currentText().split(" - ").at(3).toInt();

    //Infos du nouveau prix de la chambre
    QString nouveauPrix = ui->lineEdit_PrixAC->text();

    HotelDAO hotDAO;
    Hotel hot = hotDAO.lire(idHotel);
    ChambreDAO chaDAO;
    Chambre cha(numChambre, nouveauPrix.toInt(), nbCouchages, hot);
    Chambre cha2 = chaDAO.updater(cha);
    if(cha2.getNumChambre() != -1){
        QMessageBox::information(this, "Valider", "La modification du prix de la chambre a été effectué");
        //---Actualiser la page---
        Afficherchambres();
    }else{
        QMessageBox::information(this, "Valider", "ERREUR : La modification du prix de la chambre n'a pas été effectué");
    }
}


void listeChambresRespDialog::on_pushButton_ConfimerNC_clicked()
{
    //Infos sur la chambre
    int prix = ui->lineEdit_PrixNC->text().toInt();
    int nbCouchage = ui->lineEdit_nbCouchNC->text().toInt();

    employeDAO emDAO;
    Employe em = emDAO.lireEmploye(ma);
    Hotel hot = em.getHotel();
    em.afficherDetails();
    qDebug() << prix << nbCouchage;
    ChambreDAO chaDAO;
    Chambre cha(-1, prix, nbCouchage, hot);

    if((chaDAO.creer(cha)).getNumChambre() != -1){
        QMessageBox::information(this, "Valider", "La création de la chambre a été effectuée");
        //---Actualiser la page---
        Afficherchambres();
    }else{
        QMessageBox::information(this, "Valider", "ERREUR : La création de la chambre n'a pas été effectuée");
    }
}


void listeChambresRespDialog::on_account_clicked()
{
    // Creation instance empRespCompteDialog
    empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance empRespCompteDialog
    empRespCompteDialog->showMaximized();

    // Fermer l'instance HomPageDialog
    this->close();
}

void listeChambresRespDialog::on_pushButton_ListeEmployes_clicked()
{
    // Creation instance listeEmployesDialog
    listeEmployesDialog* listeEmployesDialog = new class listeEmployesDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance listeEmployesDialog
    listeEmployesDialog->showMaximized();

    // Fermeture de l'instance listeChambresRespDialog
    this->close();
}


void listeChambresRespDialog::on_pushButton_ListeClients_clicked()
{
    // Creation instance listeClientsDialog
    listeClientsDialog* listeClientsDialog = new class listeClientsDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance listeClientsDialog
    listeClientsDialog->showMaximized();

    // Fermeture de l'instance listeChambresRespDialog
    this->close();
}



void listeChambresRespDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


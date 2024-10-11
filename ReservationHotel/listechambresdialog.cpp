#include "listechambresdialog.h"
#include "ui_listechambresdialog.h"

#include "empcomptedialog.h"
#include "homepagedialog.h"
#include "reservationavaliderdialog.h"


#include "singleconnection.h"

listeChambresDialog::listeChambresDialog(QWidget *parent, QString userType, QString mail, QString mdp)
    : QDialog(parent)
    , ui(new Ui::listeChambresDialog)
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

listeChambresDialog::~listeChambresDialog()
{
    delete ui;
}

void listeChambresDialog::Afficherchambres(){
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

        // Iterer à travers les resultats de la requete
        while(query.next()){
            // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
            ui->tableWidget_ListeChambres->setItem(row_number,0, new QTableWidgetItem(query.value("chambre.numChambre").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,1, new QTableWidgetItem(query.value("chambre.prix").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,2, new QTableWidgetItem(query.value("chambre.nbCouchages").toString()));
            ui->tableWidget_ListeChambres->setItem(row_number,3, new QTableWidgetItem(query.value("chambre.idHotel").toString()));
            row_number = row_number + 1;
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeChambres->resizeRowsToContents();
    ui->tableWidget_ListeChambres->resizeColumnsToContents();

    // Fermeture de la connexion a bdd
    db.close();
}

void listeChambresDialog::on_account_clicked()
{
    // Creation instance empRespCompteDialog
    EmpCompteDialog* empCompteDialog = new class EmpCompteDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance empRespCompteDialog
    empCompteDialog->showMaximized();

    // Fermer l'instance HomPageDialog
    this->close();

}

void listeChambresDialog::on_pushButton_ValiderResa_clicked()
{
    // Creation instance ReservationAvaliderDialog
    ReservationAvaliderDialog* ReservationAvaliderDialog = new class ReservationAvaliderDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance ReservationAvaliderDialog
    ReservationAvaliderDialog->showMaximized();

    // Fermer l'instance HomPageDialog
    this->close();
}

void listeChambresDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


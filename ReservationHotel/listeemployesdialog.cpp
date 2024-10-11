#include "listeemployesdialog.h"
#include "ui_listeemployesdialog.h"
#include "emprespcomptedialog.h"
#include "singleconnection.h"
#include "homepagedialog.h"
#include "listechambresrespdialog.h"
#include "listeclientsdialog.h"
#include "hotel.h"
#include "hoteldao.h"
#include "employe.h"
#include "employedao.h"

listeEmployesDialog::listeEmployesDialog(QWidget *parent, QString userType, QString mail, QString mdp)
    : QDialog(parent)
    , ui(new Ui::listeEmployesDialog)
{
    db = SingleConnection::getInstance();
    ui->setupUi(this);
    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);
    this->ut = userType;
    this->ma = mail;
    this->md = mdp;
    AfficheListeEmployes();
    db.close();
}

listeEmployesDialog::~listeEmployesDialog()
{
    delete ui;
}

void listeEmployesDialog::AfficheListeEmployes(){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM employe "
                            "JOIN hotel ON employe.idHotel = hotel.idHotel ";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        // Initialiser nombres de lignes dans la table avec taille de tuple rendus par requête
        ui -> tableWidget_ListeEmploye->setRowCount(query.size());
        int row_number = 0;

        // Effacer les informations déjà présente dans QComboBox
        ui->comboBoxSuppEmp->clear();
        ui->comboBox_CResp->clear();

        // Iterer à travers les resultats de la requete
        while(query.next()){
            // Extraire les données de la ligne actuelle & Ajout a l'instance tableWidget
            ui->tableWidget_ListeEmploye->setItem(row_number,0, new QTableWidgetItem(query.value("employe.numEmploye").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,1, new QTableWidgetItem(query.value("employe.poste").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,2, new QTableWidgetItem(query.value("employe.nomEmploye").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,3, new QTableWidgetItem(query.value("employe.prenomEmploye").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,4, new QTableWidgetItem(query.value("employe.mdpEmploye").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,5, new QTableWidgetItem(query.value("employe.estResponsable").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,6, new QTableWidgetItem(query.value("employe.mailEmploye").toString()));
            ui->tableWidget_ListeEmploye->setItem(row_number,7, new QTableWidgetItem(query.value("hotel.nomHotel").toString()));
            row_number = row_number + 1;

            // Creer un affichage pour l'element QComboBox
            QString displayString = QString("%1 - %2 - %3 - %4 - %5 - %6 - %7 - %8")
                                        .arg(query.value("employe.numEmploye").toString())
                                        .arg(query.value("employe.poste").toString())
                                        .arg(query.value("employe.nomEmploye").toString())
                                        .arg(query.value("employe.prenomEmploye").toString())
                                        .arg(query.value("employe.mdpEmploye").toString())
                                        .arg(query.value("employe.estResponsable").toString())
                                        .arg(query.value("employe.mailEmploye").toString())
                                        .arg(query.value("employe.idHotel").toString());

            // Ajouter l'element à la QComboBox
            ui->comboBoxSuppEmp->addItem(displayString);
        }
    }

    // Modification de la taille des lignes et colonnes en fonction des donnees affichees
    ui->tableWidget_ListeEmploye->resizeRowsToContents();
    ui->tableWidget_ListeEmploye->resizeColumnsToContents();

    //Ajout des possibilités de éponse pour savoir si l'employe créé est un responsable
    ui->comboBox_CResp->addItem("0");
    ui->comboBox_CResp->addItem("1");
    //Mettre la valeur à 0 par défaut
    ui->comboBox_CResp->setCurrentText("0");
    // Fermeture de la connexion a bdd
    db.close();
}
void listeEmployesDialog::on_pushButton_ValiderAjoutEmp_clicked()
{
    //Infos de l'employe
    QString poste = ui->lineEdit_CPoste->text();
    QString nomEmploye = ui->lineEdit_CNom->text();
    QString prenomEmploye = ui->lineEdit_CPrenom->text();
    QString mdpEmploye = ui->lineEdit_CMdp->text();
    QString estResponsable = ui->comboBox_CResp->currentText();
    QString mailEmploye = ui->lineEdit_CMail->text();

    if(poste!="" && nomEmploye!="" && prenomEmploye!="" && mdpEmploye!="" && estResponsable!="" && mailEmploye!=""){
        employeDAO emDAO;
        Employe em = emDAO.lireEmploye(ma);
        Hotel hot = em.getHotel();

        bool resp = false;
        if(estResponsable == "0"){
            resp = false;
        }else if(estResponsable == "1"){
            resp = true;
        }

        Employe em2(-1, poste.toStdString(), nomEmploye.toStdString(), prenomEmploye.toStdString(), mdpEmploye.toStdString(), resp, mailEmploye.toStdString(), hot);

        if((emDAO.creerEmploye(em2)).getNumEmploye() != -1){
            QMessageBox::information(this, "Valider", "La création d'un employe a été effectuée");
            //Actualiser la page
            AfficheListeEmployes();

            //Réinitialisation des infos de l'employe
            ui->lineEdit_CPoste->setText("");
            ui->lineEdit_CNom->setText("");
            ui->lineEdit_CPrenom->setText("");
            ui->lineEdit_CMdp->setText("");
            ui->comboBox_CResp->setCurrentText("0");
            ui->lineEdit_CMail->setText("");
        }else{
            QMessageBox::information(this, "Valider", "ERREUR : La création de la chambre n'a pas été effectuée");
            //---Actualiser la page---
            AfficheListeEmployes();

        }
    }else {
        QMessageBox::information(this, "Valider", "ERREUR : Veuillez remplir tous les champs concernant le client avant de valider");
    }
}


void listeEmployesDialog::on_pushButton_ValiderSuppEmp_clicked()
{
    QString numEmploye = ui->comboBoxSuppEmp->currentText().split(" - ").at(0);
    QString poste = ui->comboBoxSuppEmp->currentText().split(" - ").at(1);
    QString nomEmploye = ui->comboBoxSuppEmp->currentText().split(" - ").at(2);
    QString prenomEmploye = ui->comboBoxSuppEmp->currentText().split(" - ").at(3);
    QString mdpEmploye = ui->comboBoxSuppEmp->currentText().split(" - ").at(4);
    QString estResponsable = ui->comboBoxSuppEmp->currentText().split(" - ").at(5);
    QString mailEmploye = ui->comboBoxSuppEmp->currentText().split(" - ").at(6);
    QString idH = ui->comboBoxSuppEmp->currentText().split(" - ").at(7);

    bool resp = false;
    if(estResponsable == "0"){
        resp = false;
    }else if(estResponsable == "1"){
        resp = true;
    }
    HotelDAO hotDAO;
    Hotel hot = hotDAO.lire(idH.toInt());
    employeDAO emDAO;
    Employe em(numEmploye.toInt(), poste.toStdString(), nomEmploye.toStdString(), prenomEmploye.toStdString(), mdpEmploye.toStdString(), resp, mailEmploye.toStdString(), hot);
    emDAO.supprimerEmploye(em);


    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    db.open();
    QSqlQuery query(db);

    // Preparation de la requete
    QString preparedQuery = "SELECT * "
                            "FROM employe "
                            "JOIN hotel ON employe.idHotel = hotel.idHotel "
                            "WHERE employe.numEmploye='" + numEmploye + "' AND employe.poste='" + poste +
                            "' AND employe.nomEmploye='" + nomEmploye + "' AND employe.prenomEmploye='" + prenomEmploye +
                            "' AND employe.mdpEmploye='" + mdpEmploye + "' AND employe.estResponsable='" + estResponsable +
                            "' AND employe.mailEmploye='" + mailEmploye + "' AND employe.idHotel='" + idH + "';";
    query.prepare(preparedQuery);

    // Execution de la requete et gestion de l'erreur
    if(!query.exec()){
        qDebug() << "Erreur requête SQL"<< query.lastError().text();
    }
    else {
        if(!query.next()){
            QMessageBox::information(this, "Valider", "La suppression de l'employe a été effectué");
            //Actualiser la page
            AfficheListeEmployes();
        }else{
            QMessageBox::information(this, "Valider", "ERREUR : La suppression de l'employe n'a pas été effectué");
            //---Actualiser la page---
            AfficheListeEmployes();
        }
    }
    db.close();
}

void listeEmployesDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance listeEmployesDialog
    this->close();
}


void listeEmployesDialog::on_account_clicked()
{
    // Creation instance empRespCompteDialog
    empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance empRespCompteDialog
    empRespCompteDialog->showMaximized();

    // Fermer l'instance HomPageDialog
    this->close();
}


void listeEmployesDialog::on_pushButton_ListeClients_clicked()
{
    // Creation instance listeClientsDialog
    listeClientsDialog* listeClientsDialog = new class listeClientsDialog(this, this->ut, this->ma, this->md);

    // Affichage de l'instance listeClientsDialog
    listeClientsDialog->showMaximized();

    // Fermeture de l'instance listeEmployesDialog
    this->close();
}


void listeEmployesDialog::on_pushButton_AfficherChambres_clicked()
{
    //Creation instance listeChambresRespDialog
    listeChambresRespDialog* listeChambresRespDialog = new class listeChambresRespDialog(this, this->ut, this->ma, this->md);

    //Affichage de l'instance listeChambresRespDialog
    listeChambresRespDialog->showMaximized();

    //Fermer l'instance listeEmployesDialog
    this->close();
}


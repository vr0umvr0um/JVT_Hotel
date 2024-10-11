#include "emprespcomptedialog.h"
#include "ui_emprespcomptedialog.h"

#include "administrateurdao.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "empcomptedialog.h"
#include "emprespstatsdialog.h"
#include "homepagedialog.h"
#include "listechambresrespdialog.h"
#include "listeclientsdialog.h"
#include "listeemployesdialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

empRespCompteDialog::empRespCompteDialog(QWidget *parent, QString ut, QString ma, QString md)
    : QDialog(parent)
    , ui(new Ui::empRespCompteDialog)
{
    db = SingleConnection::getInstance();
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit.png");
    ui->logo->setPixmap(pixLogo);

    this->userType=ut;
    this->mail=ma;
    this->mdp=md;
    this->em = emDAO.lireEmploye(mail);
    ui->lineEditMail_3->setText(mail);
    ui->lineEditMail_3->setReadOnly(true);
    ui->lineEditMdp_3->setText(mdp);
    ui->lineEditMdp_3->setReadOnly(true);
    string nom = em.getNom();
    string prenom = em.getPrenom();
    ui->lineEditNom_3->setText(QString::fromStdString(nom));
    ui->lineEditNom_3->setReadOnly(true);
    ui->lineEditPrenom_3->setText(QString::fromStdString(prenom));
    ui->lineEditPrenom_3->setReadOnly(true);
    db.close();
}

empRespCompteDialog::~empRespCompteDialog()
{
    delete ui;
}

void empRespCompteDialog::on_radioButtonAutorisePasModif_3_clicked()
{
    ui->lineEditMail_3->setReadOnly(true);
    ui->lineEditMdp_3->setReadOnly(true);
    ui->lineEditNom_3->setReadOnly(true);
    ui->lineEditPrenom_3->setReadOnly(true);
}


void empRespCompteDialog::on_radioButtonAutoriseModif_3_clicked()
{
    ui->lineEditMail_3->setReadOnly(false);
    ui->lineEditMdp_3->setReadOnly(false);
    ui->lineEditNom_3->setReadOnly(false);
    ui->lineEditPrenom_3->setReadOnly(false);
}




void empRespCompteDialog::on_pushButton_Modifier_3_clicked()
{
    if(ui->radioButtonAutoriseModif_3->isChecked()){
        //Récupération des nouvelles informations de l'employé
        QString newNom = ui->lineEditNom_3->text();
        QString newPrenom= ui->lineEditPrenom_3->text();
        QString newMail = ui->lineEditMail_3->text();
        QString newMdp = ui->lineEditMdp_3->text();

        //Création des nouvelles instances d'Adresse, Hotel et Employé
        Adresse adr(em.getHotel().getAdresse().getIdAdresse(), em.getHotel().getAdresse().getNumero(), em.getHotel().getAdresse().getRue(), em.getHotel().getAdresse().getVille(), em.getHotel().getAdresse().getCodePostal(), em.getHotel().getAdresse().getPays());
        Hotel hot(em.getHotel().getIdHotel(), em.getHotel().getNomHotel(), em.getHotel().getNbChambres(), adr);
        Employe em2(em.getNumEmploye(), em.getPoste(), newNom.toStdString(), newPrenom.toStdString(), newMdp.toStdString(), em.getEstResponsable(), newMail.toStdString(), hot);

        //em.afficherDetails();
        //em2.afficherDetails();
        if(emDAO.updaterEmploye(em2).getNumEmploye()!=-1){
            QMessageBox::information(this, "Valider", "Votre modification a bien été enregistrée");
            //-----Tests------
            /*
            qDebug() << em2.getNom()+ " " + em2.getPrenom() + " " + em2.getMailEmploye() + " " + em2.getMdpEmploye();
            qDebug() << em.getNom()+ " " + em.getPrenom() + " " + em.getMailEmploye() + " " + em.getMdpEmploye();
            employeDAO eD;
            Employe e1 = eD.lireEmploye(QString::fromStdString(em2.getMailEmploye()));
            Employe e2 = eD.lireEmploye(QString::fromStdString(em.getMailEmploye()));
            qDebug() << e1.getNom()+ " " + e1.getPrenom() + " " + e1.getMailEmploye() + " " + e1.getMdpEmploye();
            qDebug() << e2.getNom()+ " " + e2.getPrenom() + " " + e2.getMailEmploye() + " " + e2.getMdpEmploye();
*/
        }else {
            QMessageBox::information(this, "Valider", "ERROR : Votre modification n'a pas été enregistrée");
        }
    }
}




void empRespCompteDialog::on_pushButtonListeEmployes_clicked()
{
    //Creation instance listeEmployesDialog
    listeEmployesDialog* listeEmployesDialog = new class listeEmployesDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeEmployesDialog
    listeEmployesDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}


void empRespCompteDialog::on_pushButton_ListeClients_clicked()
{
    //Creation instance listeClientsDialog
    listeClientsDialog* listeClientsDialog = new class listeClientsDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeClientsDialog
    listeClientsDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}


void empRespCompteDialog::on_pushButton_AfficherChambres_clicked()
{
    //Creation instance listeChambresRespDialog
    listeChambresRespDialog* listeChambresRespDialog = new class listeChambresRespDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeChambresRespDialog
    listeChambresRespDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}

void empRespCompteDialog::on_account_clicked()
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
            if(userType == "emp"){
                // Creation instance EmpCompteDialog
                EmpCompteDialog* empCompteDialog = new EmpCompteDialog(this, this->userType, this->mail, this->mdp);

                // Affichage de l'instance EmpCompteDialog
                empCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
            else if(userType == "client"){
                // Creation instance ClientCompteDialog
                ClientCompteDialog* clientCompteDialog = new ClientCompteDialog(this, this->userType, this->mail, this->mdp);

                // Affichage de l'instance AnnuleResaDialog
                clientCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
            else if(userType == "admin"){
                // Creation instance Administrateur DAO
                AdministrateurDAO admindao;             //Pour ?
                // Affichage de l'instance AdminCompteDialog
                AdminCompteDialog* adminCompteDialog = new AdminCompteDialog(this, admindao.connexionAdmin(this->mail, this->mdp));
                adminCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }else if(userType == "empR"){
                // Creation instance empRespCompteDialog
                empRespCompteDialog* empRespCompteDialog = new class empRespCompteDialog(this, this->userType, this->mail, this->mdp);

                // Affichage de l'instance empRespCompteDialog
                empRespCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
        }
    }
}


void empRespCompteDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


void empRespCompteDialog::on_pushButton_Stats_clicked()
{
    // Creation instance HomePageDialog
    empRespStatsDialog* empRespstatsDialog = new empRespStatsDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    empRespstatsDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


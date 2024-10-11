#include "empcomptedialog.h"
#include "ui_empcomptedialog.h"

#include "admincomptedialog.h"
#include "administrateurdao.h"
#include "emprespcomptedialog.h"
#include "clientcomptedialog.h"
#include "homepagedialog.h"
#include "listechambresdialog.h"
#include "reservationavaliderdialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

EmpCompteDialog::EmpCompteDialog(QWidget *parent,QString ut, QString ma, QString md)
    : QDialog(parent)
    , ui(new Ui::EmpCompteDialog)
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

    ui->lineEditMail->setText(mail);
    ui->lineEditMail->setReadOnly(true);
    ui->lineEditMdp->setText(mdp);
    ui->lineEditMdp->setReadOnly(true);
    string nom = em.getNom();
    string prenom = em.getPrenom();
    ui->lineEditNom->setText(QString::fromStdString(nom));
    ui->lineEditNom->setReadOnly(true);
    ui->lineEditPrenom->setText(QString::fromStdString(prenom));
    ui->lineEditPrenom->setReadOnly(true);
    db.close();
}

EmpCompteDialog::~EmpCompteDialog()
{
    delete ui;
}

void EmpCompteDialog::on_radioButtonAutorisePasModif_clicked()
{
    ui->lineEditMail->setReadOnly(true);
    ui->lineEditMdp->setReadOnly(true);
    ui->lineEditNom->setReadOnly(true);
    ui->lineEditPrenom->setReadOnly(true);
}


void EmpCompteDialog::on_radioButtonAutoriseModif_clicked()
{
    ui->lineEditMail->setReadOnly(false);
    ui->lineEditMdp->setReadOnly(false);
    ui->lineEditNom->setReadOnly(false);
    ui->lineEditPrenom->setReadOnly(false);
}


void EmpCompteDialog::on_pushButton_Modifier_clicked()
{
    if(ui->radioButtonAutoriseModif->isChecked()){
        //Récupération des nouvelles informations de l'employé
        string newNom = ui->lineEditNom->text().toStdString();
        string newPrenom= ui->lineEditPrenom->text().toStdString();
        string newMail = ui->lineEditMail->text().toStdString();
        string newMdp = ui->lineEditMdp->text().toStdString();

        //Création des nouvelles instances d'Adresse, Hotel et Employé
        Adresse adr(em.getHotel().getAdresse().getIdAdresse(), em.getHotel().getAdresse().getNumero(), em.getHotel().getAdresse().getRue(), em.getHotel().getAdresse().getVille(), em.getHotel().getAdresse().getCodePostal(), em.getHotel().getAdresse().getPays());
        Hotel hot(em.getHotel().getIdHotel(), em.getHotel().getNomHotel(), em.getHotel().getNbChambres(), adr);
        Employe em2(em.getNumEmploye(), em.getPoste(), newNom, newPrenom, newMdp, em.getEstResponsable(), newMail, hot);
        if(emDAO.updaterEmploye(em2).getNumEmploye()!=-1){
            QMessageBox::information(this, "Valider", "Votre modification a bien été enregistrée");
        }else {
            QMessageBox::information(this, "Valider", "ERROR : Votre modification n'a pas été enregistrée");
        }
    }
}


void EmpCompteDialog::on_pushButton_AfficherChambres_clicked()
{
    //Creation instance listeChambresDialog
    listeChambresDialog* listeChambresDialog = new class listeChambresDialog(this);

    //Affichage de l'instance listeChambresDialog
    listeChambresDialog->showMaximized();

    //Fermer l'instance EmpCompteDialog
    this->close();
}


void EmpCompteDialog::on_pushButton_ValiderResa_clicked()
{
    //Creation instance ReservationAvaliderDialog
    ReservationAvaliderDialog* ReservationAvaliderDialog = new class ReservationAvaliderDialog(this);

    //Affichage de l'instance ReservationAvaliderDialog
    ReservationAvaliderDialog->showMaximized();

    //Fermer l'instance EmpCompteDialog
    this->close();
}

void EmpCompteDialog::on_accueil_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


void EmpCompteDialog::on_account_clicked()
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
                // Creation instance EmpCompteDialog
                EmpCompteDialog* empCompteDialog = new EmpCompteDialog(this, this->userType, this->mail, this->mdp);

                // Affichage de l'instance EmpCompteDialog
                empCompteDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
        }
    }
}


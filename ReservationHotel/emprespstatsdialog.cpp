#include "emprespstatsdialog.h"
#include "ui_emprespstatsdialog.h"

#include "administrateurdao.h"

#include "admincomptedialog.h"
#include "clientcomptedialog.h"
#include "empcomptedialog.h"
#include "emprespcomptedialog.h"
#include "homepagedialog.h"
#include "listechambresrespdialog.h"
#include "listeclientsdialog.h"
#include "listeemployesdialog.h"

#include "mainwindow.h"

#include "singleconnection.h"

empRespStatsDialog::empRespStatsDialog(QWidget *parent, QString ut, QString ma, QString md)
    : QDialog(parent)
    , ui(new Ui::empRespStatsDialog)
{
    ui->setupUi(this);
    employeDAO employedao;
    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit.png");
    ui->logo_3->setPixmap(pixLogo);

    this->userType=ut;
    this->mail=ma;
    this->mdp=md;
    this->em = emDAO.lireEmploye(mail);

    // Connexion des boutons de graphes
    connect(ui->pushButton_NbResaYM,&QPushButton::clicked,this,&empRespStatsDialog::afficheGrapheNbResaYM);
    connect(ui->pushButton_NbClientsVille,&QPushButton::clicked,this,&empRespStatsDialog::afficheGrapheNbClientsVille);
    connect(ui->pushButton_PrixMoyenChambre,&QPushButton::clicked,this,&empRespStatsDialog::afficheGraphePrixMoyenChambre);

    // affichage d'un graphe de base
    ui->scrollArea_Graphe->setWidget(employedao.getGrapheNbReservationYM(this->em.getHotel().getIdHotel()));
}

empRespStatsDialog::~empRespStatsDialog()
{
    delete ui;
}


// --------------- Méthodes de graphe -------------
void empRespStatsDialog::afficheGrapheNbResaYM() {
    employeDAO employedao;
    ui->scrollArea_Graphe->setWidget(employedao.getGrapheNbReservationYM(this->em.getHotel().getIdHotel()));
}

void empRespStatsDialog::afficheGrapheNbClientsVille() {
    employeDAO employedao;
    ui->scrollArea_Graphe->setWidget(employedao.getGrapheNbClientVille(this->em.getHotel().getIdHotel()));
}

void empRespStatsDialog::afficheGraphePrixMoyenChambre() {
    employeDAO employedao;
    ui->scrollArea_Graphe->setWidget(employedao.getGraphePrixMoyenChambreYM(this->em.getHotel().getIdHotel()));
}

void empRespStatsDialog::on_pushButton_Stats_clicked()
{
    // Creation instance HomePageDialog
    empRespCompteDialog* empRespcompteDialog = new empRespCompteDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    empRespcompteDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


void empRespStatsDialog::on_pushButtonListeEmployes_3_clicked()
{
    //Creation instance listeEmployesDialog
    listeEmployesDialog* listeEmployesDialog = new class listeEmployesDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeEmployesDialog
    listeEmployesDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}


void empRespStatsDialog::on_pushButton_ListeClients_3_clicked()
{
    //Creation instance listeClientsDialog
    listeClientsDialog* listeClientsDialog = new class listeClientsDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeClientsDialog
    listeClientsDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}


void empRespStatsDialog::on_pushButton_AfficherChambres_3_clicked()
{
    //Creation instance listeChambresRespDialog
    listeChambresRespDialog* listeChambresRespDialog = new class listeChambresRespDialog(this, this->userType, this->mail, this->mdp);

    //Affichage de l'instance listeChambresRespDialog
    listeChambresRespDialog->showMaximized();

    //Fermer l'instance empRespCompteDialog
    this->close();
}


void empRespStatsDialog::on_accueil_3_clicked()
{
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, this->userType, this->mail, this->mdp);

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}


void empRespStatsDialog::on_account_3_clicked()
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
                empRespStatsDialog* empRespstatsDialog = new class empRespStatsDialog(this, this->userType, this->mail, this->mdp);

                // Affichage de l'instance empRespCompteDialog
                empRespstatsDialog->showMaximized();

                // Fermer l'instance HomPageDialog
                this->close();
            }
        }
    }
}


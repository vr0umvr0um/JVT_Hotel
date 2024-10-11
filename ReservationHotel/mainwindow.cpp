#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "administrateurDAO.h"
#include "clientDAO.h"
#include "employeDAO.h"

#include "clientinscriptiondialog.h"
#include "homepagedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit.png");
    ui->logo->setPixmap(pixLogo);

    ui->lineEdit_mdp->setEchoMode(QLineEdit::Password);     //Mettre des points pour la saisie du mot de passe

    // QPixmap pm("jvt_hotels.png"); // adresse de l'image
    // ui->imgLabel->setPixmap(pm);
    // ui->imgLabel->setScaledContents(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Méthode de connexion à l'application.
 *
 * @brief MainWindow::on_pushButton_val_clicked
 */
void MainWindow::on_pushButton_val_clicked()
{
    QString mail = ui->lineEdit_id->text();
    QString mdp = ui->lineEdit_mdp->text();
    QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(mdp.toUtf8(),QCryptographicHash::Sha256).toHex()));  //Hashage du mdp en sha256 (plus efficace que sha1)

    if(mail.isEmpty() || mdp.isEmpty()){
        QMessageBox::information(this, "Je comprends", "Merci de renseigner tous les champs");
    }
    else if(this->ui->radioAdmin->isChecked()){
       AdministrateurDAO adminDAO;

       if(adminDAO.connexionAdmin(mail, mdp).getIdAdmin() != -1){
           qDebug() << "Connexion à Administrateur reussie";
            QMessageBox::information(this, "Valider", "Cet utilisateur est un Administrateur");

           // Creation instance HomePageDialog
           HomePageDialog* homePageDialog = new HomePageDialog(this, "admin", mail, mdp);

           // Affichage de l'instance AnnuleResaDialog
           homePageDialog->showMaximized();

           // Cacher l'instance HomPageDialog
           this->hide();

        }else{
            qDebug() << "Connexion à Administrateur échouée";
            QMessageBox::information(this, "Valider", "Administrateur introuvé");
        }

    }else if(this->ui->radioClient->isChecked()){
        ClientDAO cliDAO;

        if(cliDAO.connexionClient(mail, mdpHash).getIdClient() != -1){
            qDebug() << "Connexion à Client reussie";
            QMessageBox::information(this, "Valider", "Cet utilisateur est un Client");

            // Creation instance HomePageDialog
            HomePageDialog* homePageDialog = new HomePageDialog(this, "client", mail, mdp);

            // Affichage de l'instance AnnuleResaDialog
            homePageDialog->showMaximized();

            // Cacher l'instance HomPageDialog
            this->hide();

        }else{
            qDebug() << "Connexion à Client échouée";
            QMessageBox::information(this, "Valider", "Client introuvé");
        }

    }else if(this->ui->radioEmploye->isChecked()){
        employeDAO empDAO;

        if(empDAO.connexionEmploye(mail,mdpHash).getEstResponsable() == 1 && empDAO.connexionEmploye(mail, mdpHash).getNumEmploye() != -1){

            qDebug() << "Connexion à Employe reussie";
            QMessageBox::information(this, "Valider", "Cet utilisateur est un Employé Responsable");

            // Creation instance HomePageDialog
            HomePageDialog* homePageDialog = new HomePageDialog(this, "empR", mail, mdp);

            // Affichage de l'instance AnnuleResaDialog
            homePageDialog->showMaximized();
        }
        else if(empDAO.connexionEmploye(mail,mdpHash).getEstResponsable() == 0 && empDAO.connexionEmploye(mail, mdpHash).getNumEmploye() != -1){

            qDebug() << "Connexion à Employe reussie";
            QMessageBox::information(this, "Valider", "Cet utilisateur est un Employé");

            // Creation instance HomePageDialog
            HomePageDialog* homePageDialog = new HomePageDialog(this, "emp", mail, mdp);

            // Affichage de l'instance AnnuleResaDialog
            homePageDialog->showMaximized();

            // Cacher l'instance HomPageDialog
            this->hide();

        }
        else{
        qDebug() << "Connexion à Employe échouée";
        QMessageBox::information(this, "Valider", "Employé introuvé");
        }
    }
}

void MainWindow::on_pushButton_signup_clicked()
{
    // Creation instance HomePageDialog
    ClientInscriptionDialog* clientInscriptionDialog = new ClientInscriptionDialog(this);

    // Affichage de l'instance AnnuleResaDialog
    clientInscriptionDialog->showMaximized();
}


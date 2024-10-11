/**
 * @author Forest Jules 22203517
 */
#include "admincomptedialog.h"
#include "ui_admincomptedialog.h"

#include "client.h"
#include "employe.h"
#include "hotel.h"

#include "clientdao.h"
#include "employedao.h"
#include "hoteldao.h"
#include <QtWidgets>

#include "mainwindow.h"
#include "homepagedialog.h"

AdminCompteDialog::AdminCompteDialog(QWidget *parent, Administrateur admin)
    : QDialog(parent)
    , admin(admin)
    , ui(new Ui::AdminCompteDialog)
{
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);

    AdministrateurDAO admindao;

    // Connexion des boutons de graphes
    connect(ui->pushButton_ClientYM,&QPushButton::clicked,this,&AdminCompteDialog::afficheGrapheNbClientsYM);
    connect(ui->pushButton_ClientDep,&QPushButton::clicked,this,&AdminCompteDialog::afficheGrapheNbClientsDep);
    connect(ui->pushButton_Resa,&QPushButton::clicked,this,&AdminCompteDialog::afficheGrapheNbReservationsYM);

    // Connexion des boutons d'action de l'admin
    connect(ui->pushButton_modifInfos,&QPushButton::clicked,this,&AdminCompteDialog::formulaireModifInfosAdmin);
    connect(ui->pushButton_consulterHotels,&QPushButton::clicked,this,&AdminCompteDialog::consulterHotels);
    connect(ui->pushButton_consulterClients,&QPushButton::clicked,this,&AdminCompteDialog::consulterClients);
    connect(ui->pushButton_consulterAdmins,&QPushButton::clicked,this,&AdminCompteDialog::consulterAdmins);
    connect(ui->pushButton_AjoutAdmin,&QPushButton::clicked,this,&AdminCompteDialog::formulaireAjouterAdmin);

    connect(ui->pushButton_Retour,&QPushButton::clicked,this,&AdminCompteDialog::retourHomePage);
    connect(ui->account,&QPushButton::clicked,this,&AdminCompteDialog::switchToCompte);

    // mise en place des infos de l'admin sur la page
    string mailadmin = "Mail : " + admin.getMailAdmin();
    ui->nomUser->setText(QString::fromStdString(admin.getPseudoAdmin()));
    ui->label_mailAdmin->setText(QString::fromStdString(mailadmin));

    // affichage d'un graphe de base
    ui->scrollArea_Graphe->setWidget(admindao.getGrapheNbClientsYM());
}

AdminCompteDialog::~AdminCompteDialog()
{
    delete ui;
}

// --------------- Méthodes de graphe -------------
void AdminCompteDialog::afficheGrapheNbClientsYM() {
    AdministrateurDAO admindao;
    ui->scrollArea_Graphe->setWidget(admindao.getGrapheNbClientsYM());
}

void AdminCompteDialog::afficheGrapheNbClientsDep() {
    AdministrateurDAO admindao;
    ui->scrollArea_Graphe->setWidget(admindao.getGrapheNbClientsDep());
}

void AdminCompteDialog::afficheGrapheNbReservationsYM() {
    AdministrateurDAO admindao;
    ui->scrollArea_Graphe->setWidget(admindao.getGrapheNbReservationsYM());
}

/**
 * @brief switchToCompte
 * Permet d'afficher la page de compte Admin
*/
void AdminCompteDialog::switchToCompte(){
    AdminCompteDialog* newAdminCompteDialog = new AdminCompteDialog(this, this->admin);
    this->close();
    newAdminCompteDialog->showMaximized();
}

void AdminCompteDialog::retourHomePage(){
    // Creation instance HomePageDialog
    HomePageDialog* homePageDialog = new HomePageDialog(this, QString::fromStdString("admin"), QString::fromStdString(this->admin.getMailAdmin()), QString::fromStdString(this->admin.getMdpAdmin()));

    // Affichage de l'instance HomePageDialog
    homePageDialog->showMaximized();

    // Fermeture de l'instance DemandeResaDialog
    this->close();
}

// -------------- Méthodes d'action de l'admin -------------
// ------------ hotels
void AdminCompteDialog::consulterHotels() {
    HotelDAO hoteldao;
    vector<Hotel> tabHotels = hoteldao.lireAllHotels();

    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(10);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez un widget pour chaque ligne d'hôtel
    for (Hotel hotel : tabHotels) {
        QWidget *rowHandlerwidget = new QWidget(scrollAreaWidgetContents);
        QHBoxLayout *hbox = new QHBoxLayout(rowHandlerwidget);

        // Créez l'encart pour chaque hôtel
        QPushButton *boutonRename = new QPushButton(rowHandlerwidget);
        boutonRename->setText("Renommer");
        QPushButton *boutonSupp = new QPushButton(rowHandlerwidget);
        boutonSupp->setText("Supprimer");
        QPushButton *boutonEmploye = new QPushButton(rowHandlerwidget);
        boutonEmploye->setText("Voir les employés");
        QLabel *nomHotel = new QLabel(rowHandlerwidget);
        nomHotel->setText(QString::fromStdString(hotel.getNomHotel()));
        nomHotel->setFrameShape(QFrame::Panel);

        hbox->addWidget(nomHotel);
        hbox->addWidget(boutonEmploye);
        hbox->addWidget(boutonRename);
        hbox->addWidget(boutonSupp);

        // Connectez le clic du boutonRename à une lambda fonction pour savoir quel hotel on renomme
        int idhotel = hotel.getIdHotel();  // Utilisez une référence pour l'hotel
        connect(boutonRename, &QPushButton::clicked, [idhotel, this] {
            this->renommeHotel(idhotel);
        });

        // Connectez le clic du boutonSupp à une lambda fonction pour savoir quel hotel on supprime
        connect(boutonSupp, &QPushButton::clicked, [idhotel, this] {
            this->supprimeHotel(idhotel);
        });

        // Connectez le clic du boutonEmploye à une lambda fonction pour savoir quels sont les employés
        connect(boutonEmploye, &QPushButton::clicked, [idhotel, this] {
            this->voirEmployes(idhotel);
        });

        // Ajoutez le widget de ligne au layout vertical
        verticalLayout->addWidget(rowHandlerwidget);
    }
    verticalLayout->setAlignment(Qt::AlignTop);
    // Définissez le widget pour la zone de défilement
    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);
}

void AdminCompteDialog::renommeHotel(int idhotel){
    bool ok;
    QString nouveauNom = QInputDialog::getText(this, "Nouveau nom d'hôtel", "Entrez le nom de l'hôtel :", QLineEdit::Normal, "", &ok);

    if (ok && !nouveauNom.isEmpty()) {
        // Traitez le nouveau nom d'hôtel
        HotelDAO hoteldao;
        hoteldao.renommer(idhotel, nouveauNom.toStdString());
        this->consulterHotels();
    } else {
        qDebug() << "Opération annulée.";
    }
}

void AdminCompteDialog::supprimeHotel(int idhotel){
    int reponse = QMessageBox::question(this, "Supprimer l'hôtel", "Voulez-vous vraiment supprimer l'hôtel ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes) {
        // Supprimez l'hôtel
        HotelDAO hoteldao;
        Hotel hotel = hoteldao.lire(idhotel);
        hoteldao.supprimer(hotel);
        this->consulterHotels();
    } else {
        qDebug() << "Suppression annulée.";
    }
}

// ------------- employés
void AdminCompteDialog::voirEmployes(int idhotel){
    employeDAO employedao;
    vector<Employe> tabEmployes= employedao.lireAllEmployeByIdHotel(idhotel);

    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(4);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez un widget pour chaque ligne d'hôtel
    for (Employe employe : tabEmployes) {
        QWidget *rowHandlerwidget = new QWidget(scrollAreaWidgetContents);
        QHBoxLayout *hbox = new QHBoxLayout(rowHandlerwidget);

        // Créez l'encart pour chaque employe
        QLabel *nomPrenomEmploye = new QLabel(rowHandlerwidget);
        nomPrenomEmploye->setFrameShape(QFrame::Panel);
        string nomPrenom = employe.getPrenom() + " " + employe.getNom();
        nomPrenomEmploye->setText(QString::fromStdString(nomPrenom));
        QLabel *posteEmploye = new QLabel(rowHandlerwidget);
        string poste = "Poste : " + employe.getPoste();
        posteEmploye->setText(QString::fromStdString(poste));
        QLabel *mailEmploye = new QLabel(rowHandlerwidget);
        string mail = "Mail : " + employe.getMailEmploye();
        mailEmploye->setText(QString::fromStdString(mail));

        hbox->addWidget(nomPrenomEmploye);
        hbox->addWidget(posteEmploye);
        hbox->addWidget(mailEmploye);

        // Ajoutez le widget de ligne au layout vertical
        verticalLayout->addWidget(rowHandlerwidget);
    }
    verticalLayout->setAlignment(Qt::AlignTop);
    // Définissez le widget pour la zone de défilement
    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);
}

// ---------- Clients
void AdminCompteDialog::consulterClients() {
    ClientDAO clientdao;
    vector<Client> tabClients = clientdao.lireAllClients();

    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(4);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez un widget pour chaque ligne d'hôtel
    for (Client client : tabClients) {
        QWidget *rowHandlerwidget = new QWidget(scrollAreaWidgetContents);
        QHBoxLayout *hbox = new QHBoxLayout(rowHandlerwidget);

        // Créez l'encart pour chaque client
        QLabel *nomPrenomClient = new QLabel(rowHandlerwidget);
        string nomPrenom = client.getPrenomClient() + " " + client.getNomClient();
        nomPrenomClient->setText(QString::fromStdString(nomPrenom));
        nomPrenomClient->setFrameShape(QFrame::Panel);
        QLabel *telephoneClient = new QLabel(rowHandlerwidget);
        string telephone = "Tel : " + client.getTelephoneClient();
        telephoneClient->setText(QString::fromStdString(telephone));
        QLabel *mailClient = new QLabel(rowHandlerwidget);
        string mail = "Mail : " + client.getMailClient();
        mailClient->setText(QString::fromStdString(mail));
        QPushButton *boutonSupp = new QPushButton(rowHandlerwidget);
        boutonSupp->setText("Supprimer");

        hbox->addWidget(nomPrenomClient);
        hbox->addWidget(telephoneClient);
        hbox->addWidget(mailClient);
        hbox->addWidget(boutonSupp);

        int idclient = client.getIdClient();
        // Connectez le clic du boutonSupp à une lambda fonction pour savoir quel client on supprime
        connect(boutonSupp, &QPushButton::clicked, [idclient, this] {
            this->supprimeClient(idclient);
        });
        // Ajoutez le widget de ligne au layout vertical
        verticalLayout->addWidget(rowHandlerwidget);
    }
    verticalLayout->setAlignment(Qt::AlignTop);
    // Définissez le widget pour la zone de défilement
    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);
}

void AdminCompteDialog::supprimeClient(int idclient){
    int reponse = QMessageBox::question(this, "Supprimer le client", "Voulez-vous vraiment supprimer le compte du client ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes) {
        // Supprimez le client
        ClientDAO clientdao;
        Client client = clientdao.lire(idclient);
        clientdao.supprimer(client);
        // refresh la page
        this->consulterClients();
    } else {
        qDebug() << "Suppression annulée.";
    }
}


// --------------- Admin
void AdminCompteDialog::consulterAdmins() {
    AdministrateurDAO admindao;
    vector<Administrateur> tabAdmins = admindao.lireAllAdminExceptMe(this->admin.getIdAdmin());

    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(2);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez un widget pour chaque ligne d'hôtel
    for (Administrateur administrateur : tabAdmins) {
        QWidget *rowHandlerwidget = new QWidget(scrollAreaWidgetContents);
        QHBoxLayout *hbox = new QHBoxLayout(rowHandlerwidget);

        // Créez l'encart pour chaque client
        QLabel *pseudoAdmin = new QLabel(rowHandlerwidget);
        string pseudo = administrateur.getPseudoAdmin();
        pseudoAdmin->setText(QString::fromStdString(pseudo));
        pseudoAdmin->setFrameShape(QFrame::Panel);
        QLabel *mailAdmin = new QLabel(rowHandlerwidget);
        string mail = "Mail : " + administrateur.getMailAdmin();
        mailAdmin->setText(QString::fromStdString(mail));
        QPushButton *boutonSupp = new QPushButton(rowHandlerwidget);
        boutonSupp->setText("Supprimer");

        hbox->addWidget(pseudoAdmin);
        hbox->addWidget(mailAdmin);
        hbox->addWidget(boutonSupp);

        int idadmin = administrateur.getIdAdmin();
        // Connectez le clic du boutonSupp à une lambda fonction pour savoir quel client on supprime
        connect(boutonSupp, &QPushButton::clicked, [idadmin, this] {
            this->supprimerAdmin(idadmin);
        });
        // Ajoutez le widget de ligne au layout vertical
        verticalLayout->addWidget(rowHandlerwidget);
    }
    verticalLayout->setAlignment(Qt::AlignTop);
    // Définissez le widget pour la zone de défilement
    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);
}

void AdminCompteDialog::supprimerAdmin(int idAdmin){
    int reponse = QMessageBox::question(this, "Supprimer l'administrateur", "Voulez-vous vraiment supprimer le compte de l'admin ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes) {
        // Supprimez le client
        AdministrateurDAO admindao;
        Administrateur admin = admindao.lire(idAdmin);
        admindao.supprimer(admin);
        // refresh la page
        this->consulterAdmins();
    } else {
        qDebug() << "Suppression annulée.";
    }
}


void AdminCompteDialog::formulaireModifInfosAdmin(){
    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez l'encart pour chaque client
    //QLabel *titre = new QLabel(scrollAreaWidgetContents);
    //titre->setText(QString::fromStdString("Modifier les informations de l'administrateur"));
    QLabel *pseudo = new QLabel(scrollAreaWidgetContents);
    pseudo->setText("Pseudo :");
    pseudo->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldPseudo = new QLineEdit(scrollAreaWidgetContents);
    fieldPseudo->setText(QString::fromStdString(this->admin.getPseudoAdmin()));

    QLabel *mail = new QLabel(scrollAreaWidgetContents);
    mail->setText("Mail :");
    mail->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldMail = new QLineEdit(scrollAreaWidgetContents);
    fieldMail->setText(QString::fromStdString(this->admin.getMailAdmin()));

    QLabel *mdp = new QLabel(scrollAreaWidgetContents);
    mdp->setText("Mot de passe :");
    mdp->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldMdp = new QLineEdit(scrollAreaWidgetContents);
    fieldMdp->setText(QString::fromStdString(this->admin.getMdpAdmin()));

    QLabel *spaceur = new QLabel(scrollAreaWidgetContents);
    spaceur->setText(" ");
    QPushButton *boutonModifier = new QPushButton(scrollAreaWidgetContents);
    boutonModifier->setText("Modifier");
    QPushButton *boutonAnnuler = new QPushButton(scrollAreaWidgetContents);
    boutonAnnuler->setText("Annuler");

    QLabel *test = new QLabel(scrollAreaWidgetContents);
    test->setText(QString::fromStdString(" "));

    //verticalLayout->addWidget(titre, 1);
    verticalLayout->addWidget(pseudo, 3);
    verticalLayout->addWidget(fieldPseudo, 3);
    verticalLayout->addWidget(mail, 3);
    verticalLayout->addWidget(fieldMail, 3);
    verticalLayout->addWidget(mdp, 3);
    verticalLayout->addWidget(fieldMdp, 3);
    verticalLayout->addWidget(spaceur, 3);
    verticalLayout->addWidget(boutonModifier, 3);
    verticalLayout->addWidget(boutonAnnuler, 3);
    verticalLayout->addWidget(test);


    // Connectez le clic du boutonModifier à une lambda fonctio
    connect(boutonModifier, &QPushButton::clicked, [fieldPseudo, fieldMail, fieldMdp, this] {
        this->modifierInfosAdmin(fieldPseudo->text().toStdString(),
                                 fieldMail->text().toStdString(),
                                 fieldMdp->text().toStdString()
                                 );
    });
    // Connectez le clic du boutonAnnuler à une lambda fonction
    connect(boutonAnnuler, &QPushButton::clicked, [this] {
        AdminCompteDialog* newAdminCompteDialog = new AdminCompteDialog(this, this->admin);
        this->close();
        newAdminCompteDialog->showMaximized();
    });
    // Définissez le widget pour la zone de défilement
    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);
}

void AdminCompteDialog::modifierInfosAdmin(string newPseudo, string newMail, string newMdp){
    AdministrateurDAO admindao;
    this->admin.setPseudoAdmin(newPseudo);
    this->admin.setMailAdmin(newMail);
    this->admin.setMdpAdmin(newMdp);

    admindao.updater(this->admin);
    AdminCompteDialog* newAdminCompteDialog = new AdminCompteDialog(this, this->admin);
    this->close();
    newAdminCompteDialog->showMaximized();
}

void AdminCompteDialog::on_pushButton_Compte_clicked()
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
            // Affichage de l'instance AdminCompteDialog
            AdminCompteDialog* adminCompteDialog = new AdminCompteDialog(this, admin);
            adminCompteDialog->showMaximized();

            // Fermer l'instance HomPageDialog
            this->close();
        }
    }
}

void AdminCompteDialog::formulaireAjouterAdmin(){
    // setup scroll area
    ui->scrollArea_zoneCentrale->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_zoneCentrale->setWidgetResizable(true);

    // Créez un widget pour le contenu de la zone de défilement
    auto scrollAreaWidgetContents = new QWidget();
    auto verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    // Créez l'encart pour chaque client
    //QLabel *titre = new QLabel(scrollAreaWidgetContents);
    //titre->setText(QString::fromStdString("Modifier les informations de l'administrateur"));
    QLabel *pseudo = new QLabel(scrollAreaWidgetContents);
    pseudo->setText("Pseudo :");
    pseudo->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldPseudo = new QLineEdit(scrollAreaWidgetContents);
    fieldPseudo->setPlaceholderText("Pseudo de l'admin");

    QLabel *mail = new QLabel(scrollAreaWidgetContents);
    mail->setText("Mail :");
    mail->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldMail = new QLineEdit(scrollAreaWidgetContents);
    fieldMail->setPlaceholderText("Mail de l'admin");

    QLabel *mdp = new QLabel(scrollAreaWidgetContents);
    mdp->setText("Mot de passe :");
    mdp->setStyleSheet("font-weight : bold; font-size : 20px");
    QLineEdit *fieldMdp = new QLineEdit(scrollAreaWidgetContents);
    fieldMdp->setPlaceholderText("Mot de passe de l'admin");

    QLabel *spaceur = new QLabel(scrollAreaWidgetContents);
    spaceur->setText(" ");
    QPushButton *boutonAjouter = new QPushButton(scrollAreaWidgetContents);
    boutonAjouter->setText("Ajouter");
    QPushButton *boutonAnnuler = new QPushButton(scrollAreaWidgetContents);
    boutonAnnuler->setText("Annuler");

    QLabel *test = new QLabel(scrollAreaWidgetContents);
    test->setText(QString::fromStdString(" "));

    //verticalLayout->addWidget(titre, 1);
    verticalLayout->addWidget(pseudo, 3);
    verticalLayout->addWidget(fieldPseudo, 3);
    verticalLayout->addWidget(mail, 3);
    verticalLayout->addWidget(fieldMail, 3);
    verticalLayout->addWidget(mdp, 3);
    verticalLayout->addWidget(fieldMdp, 3);
    verticalLayout->addWidget(spaceur, 3);
    verticalLayout->addWidget(boutonAjouter, 3);
    verticalLayout->addWidget(boutonAnnuler, 3);
    verticalLayout->addWidget(test);

    ui->scrollArea_zoneCentrale->setWidget(scrollAreaWidgetContents);

    // Connectez le clic du boutonAjouter à une lambda fonction
    connect(boutonAjouter, &QPushButton::clicked, [fieldPseudo, fieldMail, fieldMdp, this] {
        if(!fieldMail->text().isEmpty() && !fieldMdp->text().isEmpty() && !fieldPseudo->text().isEmpty()){
            AdministrateurDAO admindao;
            if(!admindao.isMailUsed(fieldMail->text().toStdString())){
                Administrateur newAdmin(-1, fieldMail->text().toStdString(),
                                        fieldMdp->text().toStdString(),
                                        fieldPseudo->text().toStdString());
                admindao.creer(newAdmin);
                this->consulterAdmins();
            } else {
                QMessageBox::information(this, "Erreur", "Ce mail est déja relié à un compte");
                fieldMail->clear();
            }
        } else {
            QMessageBox::information(this, "Erreur", "Merci de renseigner tous les champs");
        }
    });

    // Connectez le clic du boutonAnnuler à une lambda fonction
    connect(boutonAnnuler, &QPushButton::clicked, [this] {
        AdminCompteDialog* newAdminCompteDialog = new AdminCompteDialog(this, this->admin);
        this->close();
        newAdminCompteDialog->showMaximized();
    });
}


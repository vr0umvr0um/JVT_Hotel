#include "clientinscriptiondialog.h"
#include "ui_clientinscriptiondialog.h"

#include "clientDAO.h"
#include "adressedao.h"

/**
 * Initialisation des informations de l'interface graphique.
 *
 * @brief ClientInscriptionDialog::ClientInscriptionDialog
 * @param parent
 */
ClientInscriptionDialog::ClientInscriptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientInscriptionDialog)
{
    // Affichage ui
    ui->setupUi(this);

    // Ajout logo au QLabel
    QPixmap pixLogo(":/logoProjet_petit_petit.png");
    ui->logo->setPixmap(pixLogo);
}

ClientInscriptionDialog::~ClientInscriptionDialog()
{
    delete ui;
}

void ClientInscriptionDialog::on_pushButton_val_clicked()
{
    // Recuperation informations adresse
    QString num = this->ui->TextFieldNumero->text();
    QString rue = this->ui->TextFieldRue->text();
    QString ville = this->ui->TextFieldVille->text();
    QString codePostal = this->ui->TextFieldCodePostal->text();
    QString pays = this->ui->TextFieldPays->text();

    // Recuperation informations client
    QString nom = this->ui->TextFieldNom->text();
    QString prenom = this->ui->TextFieldPrenom->text();
    QString tel = this->ui->TextFieldTel->text();
    QString mail = this->ui->TextFieldMail->text();
    QString mdp = this->ui->TextFieldMDP->text();

    // Si les QTexTField sont vides
    if(num.isEmpty() || rue.isEmpty() || ville.isEmpty() || codePostal.isEmpty() || pays.isEmpty() || nom.isEmpty() || prenom.isEmpty() || tel.isEmpty() || mail.isEmpty() || mdp.isEmpty()){
        // Message d'erreur
        QMessageBox::information(this, "Erreur", "Merci de renseigner tous les champs");
    }
    else {
        // Creation instance adresse
        Adresse adr(-1, num.toInt(), rue.toStdString(), ville.toStdString(), codePostal.toInt(), pays.toStdString());

        // Creation instance adresseDAO
        AdresseDAO adrDAO;

        // Si l'adresse est créée en bdd
        if(adrDAO.creer(adr).getIdAdresse() != -1){
            // Message de confirmation dans la console
            qDebug() << "Création de l'adresse du nouveau Client reussie";

            // Creation instance client
            Client cli(-1, nom.toStdString(), prenom.toStdString(), tel.toStdString(), mail.toStdString(), mdp.toStdString(), adr);

            // Creation instance clientDAO
            ClientDAO cliDAO;
            if(cliDAO.creer(cli).getIdClient() != -1){
                // Message de confirmation dans la console
                qDebug() << "Inscription à Client reussie";

                // Message de confirmation
                QMessageBox::information(this, "Valider", "Inscription réussie");

                // Fermeture de l'instance ClientInscriptionDialog
                this->close();
            }else{
                // Message d'erreur dans la console
                qDebug() << "Inscription à Client échouée";
                // Message d'erreur
                QMessageBox::information(this, "Erreur", "Inscription échouée");
            }
        }else{
            // Message d'erreur dans la console
            qDebug() << "Création de l'adresse du nouveau Client échouée";
            // Message d'erreur
            QMessageBox::information(this, "Erreur", "Création de l'adresse du nouveau Client échouée");
        }

    }
}

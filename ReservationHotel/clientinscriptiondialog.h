#ifndef CLIENTINSCRIPTIONDIALOG_H
#define CLIENTINSCRIPTIONDIALOG_H

#include <QCryptographicHash>       //Hasher des QString
#include <QMessageBox>
#include <QDialog>

using namespace std;

namespace Ui {
class ClientInscriptionDialog;
}

/**
 * @brief The ClientInscriptionDialog class
 * @author Vanessa Antivackis
 */
class ClientInscriptionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Cette méthode permet d'ouvrir une fenêtre de dialogue d'inscription d'un client.
     *
     * @brief ClientInscriptionDialog
     * @param parent
     */
    explicit ClientInscriptionDialog(QWidget *parent = nullptr);

    /**
     * Cette méthode permet de détruire une fenêtre de dialogue d'inscription d'un client.
     */
    ~ClientInscriptionDialog();

private slots:
    /**
     * Ce 'slot' permet de valider les informations lors de la demande d'inscription.
     *
     * @brief on_pushButton_val_clicked
     */
    void on_pushButton_val_clicked();

private:
    /**
     * Interface graphique d'une fenêtre de dialogue d'inscription d'un client.
     *
     * @brief ui
     */
    Ui::ClientInscriptionDialog *ui;
};

#endif // CLIENTINSCRIPTIONDIALOG_H

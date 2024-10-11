#include "mainwindow.h"
#include "singleconnection.h"

#include "clientdao.h"
#include "hotel.h"
#include "hoteldao.h"
#include "adressedao.h"
#include "adresse.h"
#include "employedao.h"
#include "employe.h"
#include "client.h"
#include "chambre.h"
#include "chambredao.h"
#include "reservation.h"
#include "reservationdao.h"
#include "administrateur.h"
#include "administrateurdao.h"

#include <QFile>
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <vector>

#include <iostream>

using namespace std;

QSqlDatabase SingleConnection::db;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // récupréation du fichier css
    QString styleCSS;
    QFile file(":/FeuilleDeStyle.css");
    //lecture du fichier css
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        styleCSS = file.readAll();
        file.close();
    }

    // set du style de la fenetre via ce qu'on a lu dans le fichier css
    w.setStyleSheet(styleCSS); 

    // // --------- TESTS  -----------

    // ---------- test de hotel et hoteldao ---------------

    // HotelDAO hotelDAO;
    // Hotel hotel = hotelDAO.lire(2);
    // hotel.afficherDetails();

    //test de hoteldao.supprimer();
    // hotelDAO.supprimer(hotel);
    //HotelDAO hotelDAO;
    //map<vector<string>,int> dico = hotelDAO.getNbReservationYM(2);
    //for (pair<vector<string>, int> occurence : dico) {
    //     cout << occurence.first[0] <<", " << occurence.first[1] << " : " << occurence.second << endl;
    //}

    //map<vector<string>,float> dico2 = hotelDAO.getPrixMoyenChambreYM(2);
    //for (pair<vector<string>, float> occurence : dico2) {
    //    cout << occurence.first[0] <<", " << occurence.first[1] << " : " << occurence.second << endl;
    //}


    // ---------- test adressedao et adresse ----------------
    // AdresseDAO adressedao1;
    Adresse adresse1(1, 4, "rue du moulin", "Toulon", 42090, "France");
    // Adresse adresse2 = adressedao1.lire(2);
    // Adresse adresse3(22, 87, "rue des jolies fleurs", "Bourges", 18000, "France");
    // //adressedao1.creer(adresse3);
    // adresse1.afficheAdresse();
    // adresse2.afficheAdresse();
    // adresse3.afficheAdresse();

    // adressedao1.supprimer(adresse3);
    // cout << endl;

    // ---------------- test employe et employeDAO ----------------
    // employeDAO employeDAO;
    // Hotel htl(0, "Hotel du Grand Nom", 500, adresse1);
    // Employe e1(0, "receptionniste", "poulain", "matthieu", "mdp", false, "matthieu.poulain@entreprise.com",htl );
    // e1.afficherDetails();
    // employeDAO empDAO;
    // int idE = empDAO.creerEmploye(e1).getNumEmploye();
    // e1.setNumEmploye(idE);
    // qDebug()<<e1.getNumEmploye();

    // --------- Test classe client.cpp  -----------

    //Client c1(1, "Jarvis", "Michel", "+33624789845", "michel.jarvis@gmail.com", "JarvisMichel", adresse1);// Fonctionne
    // cout << c1.getIdClient() << endl;// Fonctionne
    // c1.setIdClient(99);// Fonctionne
    // cout << c1.getIdAdresse() << endl;// Fonctionne
    // c1.setIdAdresse(34);// Fonctionne
    // cout << c1.getNomClient() << endl;// Fonctionne
    // c1.setNomClient("Clerivard");// Fonctionne
    // cout << c1.getPrenomClient() << endl;// Fonctionne
    // c1.setPrenomClient("Michelle");// Fonctionne
    // cout << c1.getMailClient() << endl;// Fonctionne
    // c1.setMailClient("michelle.clerivard@gmail.com");// Fonctionne
    // cout << c1.getMdpClient() << endl;// Fonctionne
    // c1.setMdpClient("mdpJarJar");// Fonctionne
    // c1.afficherDetails();// Fonctionne


    // --------- Test classe clientDAO.cpp  -----------

    // clientDAO c;
    // c.creer(c1); // Fonctionne
    // c1.setPrenomClient("Merlin");
    // c.updater(c1); // Fonctionne
    // c.lire(c1.getIdClient()); // Fonctionne
    // c.supprimer(c1); // Fonctionne


    // -------------- test de chambre et chambredao -----------

    // ChambreDAO chambredao1;
    // Chambre chambre = chambredao1.lire(3);
    // chambre.afficheChambre();

    // Chambre chambre2(-1, 200, 4, hotel);
    // chambre2 = chambredao1.creer(chambre2);
    // chambre2.afficheChambre();

    // ------------- test reservation et reservationDAO ---------

    // clientDAO clientdao;
    // Client c1 = clientdao.lire(2);
    // Reservation reservation1(-1, "2022-08-25", "2022-08-29", chambre, c1);
    // reservation1.afficherReservation();

    // ReservationDAO reservationdao;
    // Reservation reservationLu = reservationdao.lire(3);
    // reservationLu.afficherReservation();



    // reservation1 = reservationdao.creer(reservation1);
    // reservation1.afficherReservation();
    //reservationdao.supprimer(reservation1);

    // reservation1.setDateArrive("2022-08-26");
    // reservation1 = reservationdao.updater(reservation1);
    // reservation1.afficherReservation();



    // vector<Reservation> reservations = reservationdao.lireAll("dateArrive");
    // cout << "AFFICHAGE DES RESERVATIONS" << endl;
    // for(Reservation reserv : reservations){
    //     reserv.afficherReservation();
    // }

    // ---------- test Administrateur et AdministrateurDAO ----------------
    // AdministrateurDAO admindao;
    // Administrateur admin1(-1, "forjules5@gmail.com", "caca", "Zorg");
    // admin1 = admindao.creer(admin1);
    // admin1.afficheAdministrateur();

    // Administrateur admin2 = admindao.lire(admin1.getIdAdmin());
    // admin2.afficheAdministrateur();

    // admin1.setPseudoAdmin("Jules le beau");
    // admin1 = admindao.updater(admin1);
    // //admindao.supprimer(admin1);
    // cout << endl;

    w.showMaximized();
    return a.exec();
}

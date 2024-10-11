/**
 * @author Forest Jules
 */
#include "reservationdao.h"
#include "chambredao.h"
#include "clientdao.h"

#include <iostream>




// -------------------- Constructeur ---------------

ReservationDAO::ReservationDAO() : DAO(){}


// ------------------- Fonctions usuelles --------------
Reservation ReservationDAO::creer(Reservation reservation){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Reservation(dateArrive, dateDepart, numChambre, idClient) VALUES (:un, :deux, :trois, :quatre)");
    query.bindValue(":un", QString::fromStdString(reservation.getDateArrive()));
    query.bindValue(":deux", QString::fromStdString(reservation.getDateDepart()));
    query.bindValue(":trois", reservation.getChambre().getNumChambre());
    query.bindValue(":quatre", reservation.getClient().getIdClient());


    if(query.exec()){
        reservation.setIdReservation(query.lastInsertId().toInt());
    }
    db.close();
    return reservation;
}

Reservation ReservationDAO::updater(Reservation reservation){
    QSqlQuery query(db);

    // Modification des informations concernant l'hotel dans sa table concernée.
    query.prepare("UPDATE reservation SET dateArrive=:dateA, dateDepart=:dateD, estValide=:val, estTraite=:traite, numChambre=:numC, idClient=:idC WHERE idReservation=:idR");
    query.bindValue(":dateA", QString::fromStdString(reservation.getDateArrive()));
    query.bindValue(":dateD", QString::fromStdString(reservation.getDateDepart()));
    query.bindValue(":val",reservation.getEstValide());
    query.bindValue(":traite",reservation.getEstTraite());
    query.bindValue(":numC", reservation.getChambre().getNumChambre());
    query.bindValue(":idC", reservation.getClient().getIdClient());
    query.bindValue(":idR", reservation.getIdReservation());

    query.exec();

    db.close();
    return reservation;
}

void ReservationDAO::supprimer(Reservation reservation){
    QSqlQuery query(db);
    // ecrire les requetes
    query.prepare("DELETE FROM reservation WHERE idReservation=:premierevaleur");
    query.bindValue(":premierevaleur", reservation.getIdReservation());
    query.exec();
    db.close();
}

Reservation ReservationDAO::lire(int idReservation){
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservation WHERE idReservation=:premierevaleur");
    query.bindValue(":premierevaleur", idReservation);

    if (query.exec()){
        if (query.next()){
            int id = query.value("idReservation").toInt();
            string dateArrive = query.value("dateArrive").toString().toStdString();
            string dateDepart = query.value("dateDepart").toString().toStdString();
            int idChambre = query.value("numChambre").toInt();
            int idClient = query.value("idClient").toInt();
            int estValide = query.value("estValide").toInt();
            int estTraite = query.value("estTraite").toInt();

            // création de le la chambre liée
            ChambreDAO chambredao;
            Chambre chambre = chambredao.lire(idChambre);

            // création du client lié
            ClientDAO clientdao;
            Client client = clientdao.lire(idClient);

            Reservation reservation(id, dateArrive, dateDepart, estValide, estTraite, chambre, client);
            return reservation;
        } else {
            qDebug() << "Pas de reservation correspondante";
        }
    }
    else
    {
        std::cout << "Impossible de lire dans la table Reservation" << std::endl;
    }
    db.close();
    Reservation reservation;
    return reservation;
}

Reservation ReservationDAO::lire(QString mailClient, QString dateA, QString dateD, QString numChambre){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT * FROM reservation "
                            "JOIN client ON reservation.idClient=client.idClient "
                            "WHERE client.mailClient='" + mailClient + "' AND reservation.dateArrive='" + dateA + "' AND reservation.dateDepart='" + dateD + "' AND reservation.numChambre='" + numChambre + "';";
    query.prepare(preparedQuery);

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Requete correcte";

        // Iterer à travers les resultats de la requete
        if (query.next()){
            int id = query.value("reservation.idReservation").toInt();
            string dateArrive = query.value("reservation.dateArrive").toString().toStdString();
            string dateDepart = query.value("reservation.dateDepart").toString().toStdString();
            int idChambre = query.value("reservation.numChambre").toInt();
            int idClient = query.value("reservation.idClient").toInt();
            int estValide = query.value("reservation.estValide").toInt();
            int estTraite = query.value("reservation.estTraite").toInt();

            // création de le la chambre liée
            ChambreDAO chambredao;
            Chambre chambre = chambredao.lire(idChambre);

            // création du client lié
            ClientDAO clientdao;
            Client client = clientdao.lire(idClient);

            Reservation reservation(id, dateArrive, dateDepart, estValide, estTraite, chambre, client);
            return reservation;
        } else {
            qDebug() << "Pas de reservation correspondante";
        }
    }
    else
    {
        std::cout << "Impossible de lire dans la table Reservation" << std::endl;
    }
    db.close();
    Reservation reservation;
    return reservation;
}

/**
 * @brief ReservationDAO::lireAll
 * Permet de lire toutes les réservations
 * @param ordonnancement - donne la posibilité de donner un ordre de retour des réservations
 *          Soit par "numChambre", "idClient", "dateArrive", "dateDepart"
 * @return
 */
vector<Reservation> ReservationDAO::lireAll(string ordonnancement){
    QSqlQuery query;
    vector<Reservation> tabReservations;
    map<string, int> dicoPossibiliteOrdre = {{"numChambre", 1}, {"idClient", 2}, {"dateArrive", 3}, {"dateDepart", 4}};

    if(dicoPossibiliteOrdre.find(ordonnancement) != dicoPossibiliteOrdre.end()){
        int choix = dicoPossibiliteOrdre.at(ordonnancement);
        switch(choix){
            case 1:
                query.prepare("SELECT idReservation FROM Reservation ORDER BY numChambre ASC");
                break;
            case 2:
                query.prepare("SELECT idReservation FROM Reservation ORDER BY idClient ASC");
                break;
            case 3:
                query.prepare("SELECT idReservation FROM Reservation ORDER BY dateArrive ASC");
                break;
            case 4:
                query.prepare("SELECT idReservation FROM Reservation ORDER BY dateDepart ASC");
                break;
            default:
                query.prepare("SELECT idReservation FROM Reservation");
                break;
        }
    } else {
        query.prepare("SELECT idReservation FROM Reservation");
    }

    if (query.exec()){
        vector<int> tabID;
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        while(query.next()){
            tabID.push_back(query.value("idReservation").toInt());
        }

        for(int id : tabID){
            tabReservations.push_back(this->lire(id));
        }
        return tabReservations;
    }
    else {
        cout << "Impossible de lire dans la table Reservation" << std::endl;
    }
    db.close();
    return tabReservations;
}

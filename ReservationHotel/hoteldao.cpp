/**
 * @author Forest Jules
 */
#include "HotelDAO.h"
#include "adressedao.h"

#include <iostream>

// ---------------- Constructeur ---------------
HotelDAO::HotelDAO() : DAO(){}


// -------------- Fonctions usuelles ----------------
Hotel HotelDAO::creer(Hotel hotel){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Hotel (nomHotel, nbChambres, idAdresse) VALUES (:un, :deux, :trois)");
    query.bindValue(":un", QString::fromStdString(hotel.getNomHotel()));
    query.bindValue(":deux", hotel.getNbChambres());
    query.bindValue(":trois", hotel.getAdresse().getIdAdresse());

    if(query.exec()){
        hotel.setIdHotel(query.lastInsertId().toInt());
    }
    db.close();
    return hotel;
}

Hotel HotelDAO::updater(Hotel hotel){
    QSqlQuery query(db);

    // Modification des informations concernant l'hotel dans sa table concernée.
    query.prepare("UPDATE hotel SET nomHotel=:nom, nbChambres=:nb, idAdresse=:idA WHERE idHotel=:idH");
    query.bindValue(":nom", QString::fromStdString(hotel.getNomHotel()));
    query.bindValue(":nb", hotel.getNbChambres());
    query.bindValue(":idA", hotel.getAdresse().getIdAdresse());
    query.bindValue(":idH", hotel.getIdHotel());

    query.exec();

    db.close();
    return hotel;
}

void HotelDAO::supprimer(Hotel hotel){
    QSqlQuery query(db);
    // ecrire les requetes
    query.prepare("DELETE FROM Employe WHERE idHotel=:premierevaleur");
    query.bindValue(":premierevaleur", hotel.getIdHotel());
    if(query.exec()){
        query.prepare("DELETE FROM Reservation WHERE numChambre IN \
                        (SELECT numChambre FROM Chambre WHERE idHotel =:premierevaleur)");
        query.bindValue(":premierevaleur", hotel.getIdHotel());
        if(query.exec()){
            query.prepare("DELETE FROM Chambre WHERE idHotel=:premierevaleur");
            query.bindValue(":premierevaleur", hotel.getIdHotel());
            if(query.exec()){
                query.prepare("DELETE FROM hotel WHERE idHotel=:premierevaleur");
                query.bindValue(":premierevaleur", hotel.getIdHotel());
                query.exec();
                cout << hotel.getNomHotel() << " supprimé avec succés.";
            }
        }
    }
    db.close();
}

Hotel HotelDAO::lire(int idHotel){
    QSqlQuery query;
    //Marqueurs "?"
    query.prepare("SELECT * FROM hotel WHERE idHotel=:premierevaleur");
    query.bindValue(":premierevaleur", idHotel);

    if (query.exec()){
        if (query.next()){
            string nom = query.value("nomHotel").toString().toStdString();
            int nbChambres = query.value("nbChambres").toInt();
            int id = query.value("idHotel").toInt();

            // on récupère l'adresse de l'hotel
            // il est important de d'abord récupérer idAdresse puis après de créer adresseDAO,
            // sinon on perd les informations de query et on ne pourra pas accéder à l'idAdresse
            int idA = query.value("idAdresse").toInt();
            AdresseDAO adressedao1;
            Adresse adresseHotel = adressedao1.lire(idA);
            Hotel hotel(id, nom, nbChambres, adresseHotel);
            return hotel;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        std::cout << "Impossible de lire dans la table Hotel l'hotel voulu" << std::endl;
    }
    db.close();
    Hotel hotel;
    return hotel;
}


vector<Hotel> HotelDAO::lireAllHotels(){
    QSqlQuery query;
    vector<Hotel> tabHotels;
    query.prepare("SELECT idHotel FROM hotel ORDER BY nomHotel ASC");

    if (query.exec()){
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        vector<int> tabID;
        while(query.next()){
            tabID.push_back(query.value("idHotel").toInt());
        }

        for(int id : tabID){
            tabHotels.push_back(this->lire(id));
        }
        db.close();
        return tabHotels;
    }
    else {
        cout << "Impossible de lire dans la table hotel" << std::endl;
    }
    db.close();
    return tabHotels;
}


void HotelDAO::renommer(int idHotel, string newName){
    QSqlQuery query(db);

    // Modification des informations concernant l'hotel dans sa table concernée.
    query.prepare("UPDATE hotel SET nomHotel=:nom WHERE idHotel=:idH");
    query.bindValue(":nom", QString::fromStdString(newName));
    query.bindValue(":idH", idHotel);

    query.exec();

    db.close();
}

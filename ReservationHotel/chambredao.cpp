/**
 * @author Forest Jules
 */
#include "chambredao.h"
#include "hotel.h"
#include "hoteldao.h"

#include <iostream>

// ----------------- Constructeur -------------------

ChambreDAO::ChambreDAO() : DAO(){}


// --------------- Fonctions usuelles ----------------

Chambre ChambreDAO::creer(Chambre chambre){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Chambre(prix, nbCouchages, idHotel) VALUES (:un, :deux, :trois)");
    query.bindValue(":un", chambre.getPrix());
    query.bindValue(":deux", chambre.getNbCouchages());
    query.bindValue(":trois", chambre.getHotel().getIdHotel());

    if(query.exec()){
        chambre.setNumChambre(query.lastInsertId().toInt());
        qDebug() << "Chambre créée";
    }else{
        qDebug() << "Chambre non créée"<< query.lastError().text();
    }

    db.close();
    return chambre;
}

Chambre ChambreDAO::updater(Chambre chambre){
    QSqlQuery query(db);

    // Modification des informations concernant la chambre dans sa table concernée.
    query.prepare("UPDATE chambre SET prix=:prix, nbCouchages=:nb, idHotel=:hotel WHERE numChambre=:idC");
    query.bindValue(":prix", chambre.getPrix());
    query.bindValue(":nb", chambre.getNbCouchages());
    query.bindValue(":hotel", chambre.getHotel().getIdHotel());
    query.bindValue(":idC", chambre.getNumChambre());

    if(query.exec()){
        qDebug() << "Chambre update";
    }else{
        qDebug() << "Chambre non update"<< query.lastError().text();
    }

    db.close();
    return chambre;
}

void ChambreDAO::supprimer(Chambre chambre){
    QSqlQuery query(db);

    // suppression des réservations par numchambre
    query.prepare("DELETE FROM reservation WHERE numChambre=:premierevaleur");
    query.bindValue(":premierevaleur", chambre.getNumChambre());
    if(query.exec()){
        // suppression de la chambre
        query.prepare("DELETE FROM Chambre WHERE numChambre=:premierevaleur");
        query.bindValue(":premierevaleur", chambre.getNumChambre());
        if(query.exec()){
            qDebug() << "Chambre supprimée";
        }else{
            qDebug() << "Chambre non supprimée : probleme suppression de chambre"<< query.lastError().text();
        }
    } else {
        qDebug() << "Probleme de suppression des reservations de la chambre"<< query.lastError().text();
    }

    db.close();
}

Chambre ChambreDAO::lire(int numChambre){
    QSqlQuery query;
    query.prepare("SELECT * FROM Chambre WHERE numChambre=:premierevaleur");
    query.bindValue(":premierevaleur", numChambre);

    if (query.exec()){
        if (query.next()){
            int id = query.value("numChambre").toInt();
            int prix = query.value("prix").toInt();
            int nbCouchages = query.value("nbCouchages").toInt();

            // création de l'hotel lié
            int idhotel = query.value("idHotel").toInt();
            HotelDAO hoteldao1;
            Hotel hotel = hoteldao1.lire(idhotel);
            Chambre chambre(id, prix, nbCouchages, hotel);
            return chambre;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        std::cout << "Problème de lecture d'une chambre !" << std::endl;
    }
    db.close();
    Chambre chambre;
    return chambre;
}


Chambre ChambreDAO::lire(QString numChambre){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT * FROM chambre WHERE numChambre='" + numChambre + "';";
    query.prepare(preparedQuery);

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Requete correcte";

        // Iterer à travers les resultats de la requete
        if (query.next()){

            // Extraire les données de la ligne actuelle
            int id = query.value("numChambre").toInt();
            int prix = query.value("prix").toInt();
            int nbCouchages = query.value("nbCouchages").toInt();

            // Creation de l'hotel d'une chambre
            int idhotel = query.value("idHotel").toInt();
            HotelDAO hoteldao1;
            Hotel hotel = hoteldao1.lire(idhotel);

            // Creation de la chambre
            Chambre chambre(id, prix, nbCouchages, hotel);
            return chambre;
        } else {
            // Erreur lors de l'affichage des tuples
            qDebug() << "Requete next() incorrecte " << query.lastError().text();
        }
    } else {
        // Erreur lors de la requete
        qDebug() << "Requete incorrecte "<< query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
    Chambre chambre;
    return chambre;
}

vector<Chambre> ChambreDAO::lireParIDHotel(){
    QSqlQuery query;
    vector<Chambre> tabChambres;
    query.prepare("SELECT numChambre FROM Chambre ORDER BY numChambre ASC");

    if (query.exec()){
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        vector<int> tabID;
        while(query.next()){
            tabID.push_back(query.value("numChambre").toInt());
        }

        for(int id : tabID){
            tabChambres.push_back(this->lire(id));
        }
        db.close();
        return tabChambres;
    }
    else {
        cout << "Impossible de lire dans la table Chambre" << std::endl;
    }
    db.close();
    return tabChambres;
}

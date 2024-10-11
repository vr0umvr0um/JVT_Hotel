/**
 * @author Forest Jules
 */
#include "adressedao.h"

#include <iostream>

// ---------------------- Constructeur ----------------

AdresseDAO::AdresseDAO() : DAO(){}


// -------------------- Fonctions usuelles -----------------------
Adresse AdresseDAO::creer(Adresse adresse){
    QSqlQuery query(db);
    query.prepare("INSERT INTO adresse (numero, rue, ville, codePostal, pays) VALUES (:un, :deux, :trois, :quatre, :cinq)");
    query.bindValue(":un", adresse.getNumero());
    query.bindValue(":deux", QString::fromStdString(adresse.getRue()));
    query.bindValue(":trois", QString::fromStdString(adresse.getVille()));
    query.bindValue(":quatre", adresse.getCodePostal());
    query.bindValue(":cinq", QString::fromStdString(adresse.getPays()));

    if(query.exec()){
        adresse.setId(query.lastInsertId().toInt());
    }

    db.close();
    return adresse;
}

Adresse AdresseDAO::updater(Adresse adresse){
    QSqlQuery query(db);

    // Modification des informations concernant l'adresse dans sa table concernée.
    query.prepare("UPDATE adresse SET numero=:num, rue=:rue, ville=:v, codePostal=:cp, pays=:p WHERE idAdresse=:idA");
    query.bindValue(":num", adresse.getNumero());
    query.bindValue(":rue", QString::fromStdString(adresse.getRue()));
    query.bindValue(":v", QString::fromStdString(adresse.getVille()));
    query.bindValue(":cp", adresse.getCodePostal());
    query.bindValue(":idA", QString::fromStdString(adresse.getPays()));

    query.exec();

    db.close();
    return adresse;

}

void AdresseDAO::supprimer(Adresse adresse){
    QSqlQuery query(db);
    // ecrire les requetes
    query.prepare("DELETE FROM Hotel WHERE idAdresse=:premierevaleur");
    query.bindValue(":premierevaleur", adresse.getIdAdresse());
    if(query.exec()){
        query.prepare("DELETE FROM Client WHERE idAdresse=:premierevaleur");
        query.bindValue(":premierevaleur", adresse.getIdAdresse());
        if(query.exec()){
            query.prepare("DELETE FROM Adresse WHERE idAdresse=:premierevaleur");
            query.bindValue(":premierevaleur", adresse.getIdAdresse());
            query.exec();
            cout << "adresse supprimée avec succés.";
        }
    }
    db.close();
}

Adresse AdresseDAO::lire(int idAdresse){
    QSqlQuery query;
    //Marqueurs "?"
    query.prepare("SELECT * FROM Adresse WHERE idAdresse=:premierevaleur");
    query.bindValue(":premierevaleur", idAdresse);

    if (query.exec()){
        if (query.next()){
            int id = query.value("idAdresse").toInt();
            int numero = query.value("numero").toInt();
            string rue = query.value("rue").toString().toStdString();
            string ville = query.value("ville").toString().toStdString();
            int codePostal = query.value("codePostal").toInt();
            string pays = query.value("pays").toString().toStdString();
            Adresse adresse(id, numero, rue, ville, codePostal, pays);
            return adresse;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        std::cout << "Impossible de lire dans la table Adresse l'adresse voulue" << std::endl;
    }

    db.close();
    Adresse adresse;
    return adresse;
}

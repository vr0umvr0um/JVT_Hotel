/**
 * @author Vanessa Antivackis
 */

#include "clientdao.h"

// --------- Fonctions CRUD -----------

ClientDAO::ClientDAO() : DAO(){}

Client ClientDAO::creer(Client client){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "INSERT INTO adresse (numero, rue, ville, codePostal, pays) VALUES (:un, :deux, :trois, :quatre, :cinq)";
    query.prepare(preparedQuery);

    // Ajout des valeurs
    query.bindValue(":un", client.getAdresse().getNumero());
    query.bindValue(":deux", QString::fromStdString(client.getAdresse().getRue()));
    query.bindValue(":trois", QString::fromStdString(client.getAdresse().getVille()));
    query.bindValue(":quatre", client.getAdresse().getCodePostal());
    query.bindValue(":cinq", QString::fromStdString(client.getAdresse().getPays()));

    // Execution de la requete
    if(query.exec()){
        qDebug() << "Creation de l'adresse d'un client dans la table 'adresse' reussi. On va maintenant creer un client.";

        // Initialiser idA avec le dernier Id entré de la bdd
        int idA = (query.lastInsertId()).toInt();

        // Hasher le mot de passe
        QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(QString::fromStdString(client.getMdpClient()).toUtf8(),QCryptographicHash::Sha256).toHex()));

        // Preparation de la requete SQL
        QString preparedQuery2 = "INSERT INTO client (nomClient, prenomClient, telephone, mailClient, mdpClient, idAdresse) VALUES(?, ?, ?, ?, ?, ?)";
        query.prepare(preparedQuery2);

        // Ajout des valeurs
        query.addBindValue(QString::fromStdString(client.getNomClient()));
        query.addBindValue(QString::fromStdString(client.getPrenomClient()));
        query.addBindValue(QString::fromStdString(client.getTelephoneClient()));
        query.addBindValue(QString::fromStdString(client.getMailClient()));
        // query.addBindValue(QString::fromStdString(client.getMdpClient()));
        query.addBindValue(mdpHash);
        query.addBindValue(idA);

        // Execution de la requete
        if(query.exec()){
            qDebug() << "Creation du client dans la table 'client' reussie.";

            // Initialiser idC avec le dernier Id entré de la bdd
            int idC = (query.lastInsertId().toInt());
            client.setIdClient(idC);

            // Renvoyer client avec nouveau id
            return client;

        } else {
            // Message d'erreur lors de la création d'un client
            qDebug() << "Erreur creation client:" << query.lastError().text();
        }
    }else{
        // Message d'erreur lors de la creation d'une adresse
        qDebug() << "Erreur creation adresse:" << query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
    return client;
}

Client ClientDAO::updater(Client client){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "UPDATE adresse SET numero=:num, rue=:rue, ville=:v, codePostal=:cp, pays=:p WHERE idAdresse=:idA";
    query.prepare(preparedQuery);

    // Ajout des valeurs
    query.bindValue(":num", client.getAdresse().getNumero());
    query.bindValue(":rue", QString::fromStdString(client.getAdresse().getRue()));
    query.bindValue(":v", QString::fromStdString(client.getAdresse().getVille()));
    query.bindValue(":cp", client.getAdresse().getCodePostal());
    query.bindValue(":p",  QString::fromStdString(client.getAdresse().getPays()));
    query.bindValue(":idA", client.getAdresse().getIdAdresse());

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Modification de l'adresse d'un client dans la table 'adresse' reussi. On va maintenant modifier un client.";

        // Preparation de la requete SQL
        QString preparedQuery2 = "UPDATE client SET nomClient=:nC, prenomClient=:pC, telephone=:t, mailClient=:mC, mdpClient=:mdpC WHERE idClient=:idC";
        query.prepare(preparedQuery2);

        // Ajout des valeurs
        query.bindValue(":nC", QString::fromStdString(client.getNomClient()));
        query.bindValue(":pC", QString::fromStdString(client.getPrenomClient()));
        query.bindValue(":t", QString::fromStdString(client.getTelephoneClient()));
        query.bindValue(":mC", QString::fromStdString(client.getMailClient()));
        //query.bindValue(":mdpC", QString::fromStdString(client.getMdpClient()));

        // Hasher le mot de passe
        QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(QString::fromStdString(client.getMdpClient()).toUtf8(),QCryptographicHash::Sha256).toHex()));
        query.bindValue(":mC", mdpHash);
        query.bindValue(":idA", client.getAdresse().getIdAdresse());
        query.bindValue(":idC", client.getIdClient());

        // Execution de la requete
        if(query.exec()){
            qDebug() << "Modification du client dans la table 'client' reussie.";
        } else {
            // Message d'erreur lors de la modification d'un client
            qDebug() << "Error modification client" << query.lastError().text();
        }
    } else {
        // Message d'erreur lors de la modification d'une adresse
        qDebug() << "Erreur modification adresse" << query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
    return client;
}

void ClientDAO::supprimer(Client client){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "DELETE FROM reservation WHERE idClient=:premierevaleur";
    query.prepare(preparedQuery);

    // Ajout des valeurs
    query.bindValue(":premierevaleur", client.getIdClient());

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Reservation du client supprime avec succes.";

        // Preparation de la requete SQL
        QString preparedQuery2 = "DELETE FROM client WHERE idClient=:premierevaleur";
        query.prepare(preparedQuery2);

        // Ajout des valeurs
        query.bindValue(":premierevaleur", client.getIdClient());

        // Execution de la requete
        if (query.exec()){
            qDebug() << "Client supprime avec succes.";

            // Preparation de la requete SQL
            QString preparedQuery3 = "DELETE FROM adresse WHERE idAdresse=:premierevaleur";
            query.prepare(preparedQuery3);

            // Ajout des valeurs
            query.bindValue(":premierevaleur", client.getAdresse().getIdAdresse());

            // Execution de la requete
            if(query.exec()){
                qDebug() << "Adresse du client supprime avec succes.";
            } else {
                // Message d'erreur lors de la suppresion d'une adresse d'un client
                qDebug() << "Erreur suppression adresse du client:" << query.lastError().text();
            }
        } else {
            // Message d'erreur lors de la suppression d'un client
            qDebug() << "Erreur suppression du client:" << query.lastError().text();
        }
    } else {
        // Message d'erreur lors de la suppression d'une reservation d'un client
        qDebug() << "Erreur suppression de la reservation du client:" << query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
}

Client ClientDAO::lire(int idClient){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT client.idAdresse, client.idClient, client.nomClient, client.prenomClient, client.telephone, client.mailClient, client.mdpClient, adresse.numero, adresse.rue, adresse.ville, adresse.pays, adresse.codePostal FROM client JOIN adresse ON client.idAdresse=adresse.idAdresse WHERE idClient=:idC";
    query.prepare(preparedQuery);

    // Ajout des valeurs
    query.bindValue(":idC", idClient);

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Requete correcte";

        // Iterer à travers les resultats de la requete
        if(query.next()){

            // Extraire les données de la ligne actuelle
            int idAdresse = query.value("client.idAdresse").toInt();
            int idC = query.value("client.idClient").toInt();
            string nomC = query.value("client.nomClient").toString().toStdString();
            string prenomC = query.value("client.prenomClient").toString().toStdString();
            string telephoneC = query.value("client.telephone").toString().toStdString();
            string mailC = query.value("client.mailClient").toString().toStdString();
            string mdpC = query.value("client.mdpClient").toString().toStdString();
            int numero = query.value("adresse.numero").toInt();
            string rue = query.value("adresse.rue").toString().toStdString();
            string ville = query.value("adresse.ville").toString().toStdString();
            string pays = query.value("adresse.pays").toString().toStdString();
            int codePostal = query.value("adresse.codePostal").toInt();

            // Creation de l'adresse d'un client
            Adresse adresse(idAdresse, numero, rue, ville, codePostal, pays);

            // Creation de l'adresse d'un client
            Client cli(idC, nomC, prenomC, telephoneC, mailC, mdpC, adresse);
            cli.afficherDetails();
            return cli;

        } else {
            // Erreur lors de l'affichage des tuples
            qDebug() << "Requete next() incorrecte " << query.lastError().text();
        }
    } else {
        // Erreur lors de la requete
        qDebug() << "Erreur lecture client par Id "<< query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
    Client client;
    return client;
}

Client ClientDAO::lire(QString mailClient){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT client.idAdresse, client.idClient, client.nomClient, client.prenomClient, client.telephone, client.mailClient, client.mdpClient, adresse.numero, adresse.rue, adresse.ville, adresse.pays, adresse.codePostal FROM client JOIN adresse ON client.idAdresse=adresse.idAdresse WHERE client.mailClient='" + mailClient + "';";
    query.prepare(preparedQuery);

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Requete correcte";

        // Iterer à travers les resultats de la requete
        if (query.next()){

            // Extraire les données de la ligne actuelle
            int idAdresse = query.value("client.idAdresse").toInt();
            int idC = query.value("client.idClient").toInt();
            string nomC = query.value("client.nomClient").toString().toStdString();
            string prenomC = query.value("client.prenomClient").toString().toStdString();
            string telephoneC = query.value("client.telephone").toString().toStdString();
            string mailC = query.value("client.mailClient").toString().toStdString();
            string mdpC = query.value("client.mdpClient").toString().toStdString();
            int numero = query.value("adresse.numero").toInt();
            string rue = query.value("adresse.rue").toString().toStdString();
            string ville = query.value("adresse.ville").toString().toStdString();
            string pays = query.value("adresse.pays").toString().toStdString();
            int codePostal = query.value("adresse.codePostal").toInt();

            // Creation de l'adresse d'un client
            Adresse adresse(idAdresse, numero, rue, ville, codePostal, pays);

            // Creation de l'adresse d'un client
            Client cli(idC, nomC, prenomC, telephoneC, mailC, mdpC, adresse);
            return cli;

        } else {
            // Erreur lors de l'affichage des tuples
            qDebug() << "Requete next() incorrecte " << query.lastError().text();
        }
    } else {
        // Erreur lors de la requete
        qDebug() << "Erreur lecture client par mail "<< query.lastError().text();
    }

    // Fermeture de la connexion a bdd
    db.close();
    Client client;
    return client;
}


vector<Client> ClientDAO::lireAllClients(){
    QSqlQuery query;
    vector<Client> tabClients;
    query.prepare("SELECT idClient FROM client ORDER BY nomClient, prenomClient ASC");

    if (query.exec()){
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        vector<int> tabID;
        while(query.next()){
            tabID.push_back(query.value("idClient").toInt());
        }

        for(int id : tabID){
            tabClients.push_back(this->lire(id));
        }
        db.close();
        return tabClients;
    }
    else {
        qDebug() << "Impossible de lire dans la table Client";
    }
    db.close();
    return tabClients;
}


Client ClientDAO::connexionClient(QString mailClient, QString mdpClient){
    // Ouverture de la connexion a bdd & Preparation de la requete SQL
    QSqlQuery query(db);

    // Preparation de la requete SQL
    QString preparedQuery = "SELECT client.idAdresse, client.idClient, client.nomClient, client.prenomClient, client.telephone, client.mailClient, client.mdpClient, adresse.numero, adresse.rue, adresse.ville, adresse.pays, adresse.codePostal FROM client JOIN adresse ON client.idAdresse=adresse.idAdresse WHERE client.mailClient='" + mailClient + "' AND client.mdpClient='" + mdpClient + "';";
    query.prepare(preparedQuery);

    // Execution de la requete
    if (query.exec()){
        qDebug() << "Requete correcte";

        // Iterer à travers les resultats de la requete
        if (query.next()){

            // Extraire les données de la ligne actuelle
            int idAdresse = query.value("client.idAdresse").toInt();
            int idC = query.value("client.idClient").toInt();
            string nomC = query.value("client.nomClient").toString().toStdString();
            string prenomC = query.value("client.prenomClient").toString().toStdString();
            string telephoneC = query.value("client.telephone").toString().toStdString();
            string mailC = query.value("client.mailClient").toString().toStdString();
            string mdpC = query.value("client.mdpClient").toString().toStdString();
            int numero = query.value("adresse.numero").toInt();
            string rue = query.value("adresse.rue").toString().toStdString();
            string ville = query.value("adresse.ville").toString().toStdString();
            string pays = query.value("adresse.pays").toString().toStdString();
            int codePostal = query.value("adresse.codePostal").toInt();

            // Creation de l'adresse d'un client
            Adresse adresse(idAdresse, numero, rue, ville, codePostal, pays);

            // Creation de l'adresse d'un client
            Client cli(idC, nomC, prenomC, telephoneC, mailC, mdpC, adresse);
            return cli;

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
    Client client;
    return client;
}

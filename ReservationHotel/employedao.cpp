/**
 * @author Haton Tom
 */
#include "employedao.h"

#include <iostream>

string mois[12] = {"Janv", "Fevr", "Mars", "Avri", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};

employeDAO::employeDAO() {}

Employe employeDAO::creerEmploye(Employe employe){
    QSqlQuery query(db);

    // Insertion des informations concernant l'adresse d'un employe dans sa table concernée.
    query.prepare("INSERT INTO adresse (numero, rue, ville, codePostal, pays) VALUES (:un, :deux, :trois, :quatre, :cinq)");
    query.bindValue(":un", employe.getHotel().getAdresse().getNumero());
    query.bindValue(":deux", QString::fromStdString(employe.getHotel().getAdresse().getRue()));
    query.bindValue(":trois", QString::fromStdString(employe.getHotel().getAdresse().getVille()));
    query.bindValue(":quatre", employe.getHotel().getAdresse().getCodePostal());
    query.bindValue(":cinq", QString::fromStdString(employe.getHotel().getAdresse().getPays()));

    if(query.exec()){
        qDebug() << "Creation de l'adresse d'un employe dans la table 'adresse' reussi. On va maintenant creer un hotel.";

        int idA = (query.lastInsertId()).toInt();
        employe.getHotel().getAdresse().setId(idA);

        // Insertion des informations concernant l'hotel d'un employe dans sa table concernée.
        query.prepare("INSERT INTO hotel (nomHotel, nbChambres, idAdresse) VALUES (:nom, :nbChambres, :idAdr)");
        query.bindValue(":nom", QString::fromStdString(employe.getHotel().getNomHotel()));
        query.bindValue(":nbChambres", employe.getHotel().getNbChambres());
        query.bindValue(":idAdr", idA);

        if(query.exec()){
            qDebug() << "Creation de l'hotel d'un employe dans la table 'hotel' reussi. On va maintenant creer un employe.";

            int idH = (query.lastInsertId()).toInt();
            employe.getHotel().setIdHotel(idH);

            query.prepare("INSERT INTO employe (poste, nomEmploye, prenomEmploye, mdpEmploye, estResponsable, mailEmploye, idHotel) VALUES (:Poste, :Nom, :Prenom, :mdpHash, :Resp, :Mail, :idHotel)");
            query.bindValue(":Poste", QString::fromStdString(employe.getPoste()));
            query.bindValue(":Nom", QString::fromStdString(employe.getNom()));
            query.bindValue(":Prenom", QString::fromStdString(employe.getPrenom()));

            QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(QString::fromStdString(employe.getMdpEmploye()).toUtf8(),QCryptographicHash::Sha256).toHex()));
            //query.bindValue(":mdpHash", QString::fromStdString(employe.getMdpEmploye()));
            query.bindValue(":mdpHash", mdpHash);

            query.bindValue(":Resp", employe.getEstResponsable());
            query.bindValue(":Mail", QString::fromStdString(employe.getMailEmploye()));
            query.bindValue(":idHotel", idH);

            if(query.exec()){
                qDebug() << "Creation employe reussi";
                employe.setNumEmploye(query.lastInsertId().toInt());
                return employe;
            } else {
                // Message d'erreur lors de la création d'un employe
                qDebug() << "Error creating employe:" << query.lastError().text();
            }
        } else {
            // Message d'erreur lors de la création d'un hotel
            qDebug() << "Error creating hotel:" << query.lastError().text();
        }
    } else {
        // Message d'erreur lors de la création d'une adresse d'un employe
        qDebug() << "Error creating employe's adress:" << query.lastError().text();
    }
    db.close();
    return employe;
}
Employe employeDAO::updaterEmploye(Employe employe){
    QSqlQuery query(db);

    // Modification des informations concernant l'adresse d'un employe dans sa table concernée.
    query.prepare("UPDATE adresse SET numero=:num, rue=:rue, ville=:v, codePostal=:cp, pays=:p WHERE idAdresse=:idA");
    query.bindValue(":num", employe.getHotel().getAdresse().getNumero());
    query.bindValue(":rue", QString::fromStdString(employe.getHotel().getAdresse().getRue()));
    query.bindValue(":v", QString::fromStdString(employe.getHotel().getAdresse().getVille()));
    query.bindValue(":cp", employe.getHotel().getAdresse().getCodePostal());
    query.bindValue(":idA", employe.getHotel().getAdresse().getIdAdresse());

    if (query.exec()){
        qDebug() << "Modification de l'adresse d'un employe dans la table 'adresse' reussi. On va maintenant modifier un hotel.";

        // Modification des informations concernant l'hotel d'un employe dans sa table concernée.
        query.prepare("UPDATE hotel SET nomHotel=:nH, nbChambres=:nbC, idAdresse=:idA WHERE idHotel=:idH");
        query.bindValue(":nH", QString::fromStdString(employe.getHotel().getNomHotel()));
        query.bindValue(":nbC", employe.getHotel().getNbChambres());
        query.bindValue(":idA", employe.getHotel().getAdresse().getIdAdresse());
        query.bindValue(":idH", employe.getHotel().getIdHotel());

        if(query.exec()){
            qDebug() << "Modification de l'hotel d'un employe dans la table 'hotel' reussi. On va maintenant modifier un employe.";

            // Modification des informations concernant un employe dans sa table concernée.
            query.prepare("UPDATE employe SET poste=:Poste, nomEmploye=:Nom, prenomEmploye=:Prenom, mdpEmploye=:mdpHash, estResponsable=:Resp, mailEmploye=:Mail, idHotel=:idH WHERE numEmploye=:numE");
            query.bindValue(":Poste", QString::fromStdString(employe.getPoste()));
            query.bindValue(":Nom", QString::fromStdString(employe.getNom()));
            query.bindValue(":Prenom", QString::fromStdString(employe.getPrenom()));

            QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(QString::fromStdString(employe.getMdpEmploye()).toUtf8(),QCryptographicHash::Sha256).toHex()));
            // query.bindValue(":mdpHash", QString::fromStdString(employe.getMdpEmploye()));
            query.bindValue(":mdpHash", mdpHash);

            query.bindValue(":Resp", employe.getEstResponsable());
            query.bindValue(":Mail", QString::fromStdString(employe.getMailEmploye()));
            query.bindValue(":idH", employe.getHotel().getIdHotel());
            query.bindValue(":numE", employe.getNumEmploye());

            if(query.exec()){
                qDebug() << "Modification du employe dans la table 'employe' reussie.";
                return employe;
            } else {
                qDebug() << "Error updating employe" << query.lastError().text();
            }
        }else{
            qDebug() << "Error updating hotel" << query.lastError().text();
        }
    } else {
        qDebug() << "Error updating adresse" << query.lastError().text();
    }

    db.close();
    return employe;
}
void employeDAO::supprimerEmploye(Employe employe){
    QSqlQuery query(db);
    query.prepare("DELETE FROM employe WHERE numEmploye=:premierevaleur");
    query.bindValue(":premierevaleur", employe.getNumEmploye());

    if(query.exec()){
        qDebug() << "Employe supprime avec succes.";

        query.prepare("DELETE FROM hotel WHERE idHotel=:premierevaleur");
        query.bindValue(":premierevaleur", employe.getHotel().getIdHotel());

        if(query.exec()){
            qDebug() << "Adresse du client supprime avec succes.";
        } else {
            qDebug() << "Erreur suppression hotel de l'employe:" << query.lastError().text();
        }
    } else {
        qDebug() << "Erreur suppression e l'employe:" << query.lastError().text();
    }
    db.close();
}

Employe employeDAO::lireEmploye(int numEmploye){
    QSqlQuery query;

    query.prepare("SELECT * FROM employe, hotel, adresse WHERE numEmploye=:premierevaleur");
    query.bindValue(":premierevaleur", numEmploye);

    if (query.exec()){
        qDebug() << "Requête de lecture d'un employe correcte";
        if (query.next()){
            //Infos table Employe
            int numEmploye = query.value("numEmploye").toInt();
            string poste = query.value("poste").toString().toStdString();
            string nom = query.value("nomEmploye").toString().toStdString();
            string prenom = query.value("prenomEmploye").toString().toStdString();
            string mdpEmploye = query.value("mdpEmploye").toString().toStdString();
            bool estResponsable = query.value("estResponsable").toBool();
            string mailEmploye = query.value("mailEmploye").toString().toStdString();

            //Infos table Hotel
            int idHotel = query.value("idHotel").toInt();
            string nomHotel = query.value("nomHotel").toString().toStdString();
            int nbChambres = query.value("nbChambres").toInt();

            //Infos table Adresse
            int idAdresse = query.value("idAdresse").toInt();
            int numero = query.value("numero").toInt();
            string rue = query.value("rue").toString().toStdString();
            string ville = query.value("ville").toString().toStdString();
            int codePostal = query.value("codePostal").toInt();
            string pays = query.value("pays").toString().toStdString();

            Adresse adr(idAdresse, numero, rue, ville, codePostal, pays);
            Hotel hot(idHotel, nomHotel, nbChambres, adr);
            Employe empl(numEmploye, poste, nom, prenom, mdpEmploye, estResponsable, mailEmploye, hot);
            return empl;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        cout << "Ça marche pas ! :(" << endl;
    }
    db.close();
    Employe empl;
    return empl;
}
Employe employeDAO::lireEmploye(QString mail){
    QSqlQuery query;

    query.prepare("SELECT * FROM employe "
                  "JOIN hotel ON employe.idHotel=hotel.idHotel "
                  "JOIN adresse ON hotel.idAdresse=adresse.idAdresse "
                  "WHERE employe.mailEmploye='" + mail +"'");

    if (query.exec()){
        qDebug() << "Requête de lecture d'un employe correcte";
        if (query.next()){
            //Infos table Employe
            int numEmploye = query.value("numEmploye").toInt();
            string poste = query.value("poste").toString().toStdString();
            string nom = query.value("nomEmploye").toString().toStdString();
            string prenom = query.value("prenomEmploye").toString().toStdString();
            string mdpEmploye = query.value("mdpEmploye").toString().toStdString();
            bool estResponsable = query.value("estResponsable").toBool();
            string mailEmploye = query.value("mailEmploye").toString().toStdString();

            //Infos table Hotel
            int idHotel = query.value("idHotel").toInt();
            string nomHotel = query.value("nomHotel").toString().toStdString();
            int nbChambres = query.value("nbChambres").toInt();

            //Infos table Adresse
            int idAdresse = query.value("idAdresse").toInt();
            int numero = query.value("numero").toInt();
            string rue = query.value("rue").toString().toStdString();
            string ville = query.value("ville").toString().toStdString();
            int codePostal = query.value("codePostal").toInt();
            string pays = query.value("pays").toString().toStdString();

            Adresse adr(idAdresse, numero, rue, ville, codePostal, pays);
            Hotel hot(idHotel, nomHotel, nbChambres, adr);
            Employe empl(numEmploye, poste, nom, prenom, mdpEmploye, estResponsable, mailEmploye, hot);
            return empl;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        cout << "Ça marche pas ! :(" << endl;
    }
    db.close();
    Employe empl;
    return empl;
}
Employe employeDAO::connexionEmploye(QString mailEmploye, QString mdpEmploye){
    QSqlQuery query;

    QString preparedQuery = "SELECT * FROM employe WHERE mailEmploye='" + mailEmploye + "' AND mdpEmploye='" + mdpEmploye + "';";
    query.prepare(preparedQuery);

    if (query.exec()){
        qDebug() << "Connexion d'un employe reussie)";
        if (query.next()){
            //Infos table Employe
            int numEmploye = query.value("numEmploye").toInt();
            string poste = query.value("poste").toString().toStdString();
            string nom = query.value("nomEmploye").toString().toStdString();
            string prenom = query.value("prenomEmploye").toString().toStdString();
            string mdpEmploye = query.value("mdpEmploye").toString().toStdString();
            bool estResponsable = query.value("estResponsable").toBool();
            string mailEmploye = query.value("mailEmploye").toString().toStdString();

            //Infos table Hotel
            int idHotel = query.value("idHotel").toInt();
            string nomHotel = query.value("nomHotel").toString().toStdString();
            int nbChambres = query.value("nbChambres").toInt();

            //Infos table Adresse
            int idAdresse = query.value("idAdresse").toInt();
            int numero = query.value("numero").toInt();
            string rue = query.value("rue").toString().toStdString();
            string ville = query.value("ville").toString().toStdString();
            int codePostal = query.value("codePostal").toInt();
            string pays = query.value("pays").toString().toStdString();

            Adresse adr(idAdresse, numero, rue, ville, codePostal, pays);
            Hotel hot(idHotel, nomHotel, nbChambres, adr);
            Employe empl(numEmploye, poste, nom, prenom, mdpEmploye, estResponsable, mailEmploye, hot);
            return empl;
        } else {
            qDebug() << "Rien de renvoyé";
        }
    }
    else
    {
        cout << "Ça marche pas ! :(" << endl;
    }
    db.close();
    Employe empl;
    return empl;
}


vector<Employe> employeDAO::lireAllEmployeByIdHotel(int idHotel){
    QSqlQuery query;
    vector<Employe> tabEmploye;
    query.prepare("SELECT numEmploye FROM Employe WHERE idHotel = :id ORDER BY numEmploye ASC");
    query.bindValue(":id", idHotel);

    if (query.exec()){
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        vector<int> tabID;
        while(query.next()){
            tabID.push_back(query.value("numEmploye").toInt());
        }

        for(int id : tabID){
            tabEmploye.push_back(this->lireEmploye(id));
        }
        db.close();
        return tabEmploye;
    }
    else {
        cout << "Impossible de lire dans la table Employe" << std::endl;
    }
    db.close();
    return tabEmploye;
}


// ---------------------- Fonctions de statistiques -----------------------

// ----------- Nombre réservations
/**
 * @brief employeDAO::getNbReservationYM
 * Permet de récupérer le nombre de réservations pour chaque mois
 * @param idHotel
 * @return
 */
map<vector<string>,int> employeDAO::getNbReservationYM(int idHotel){
    map<vector<string>,int> nbResa;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS nbReservations, YEAR(dateArrive) AS annee, MONTH(dateArrive) AS mois \
                FROM reservation \
                INNER JOIN chambre USING(numChambre) \
                INNER JOIN Hotel USING(idHotel) \
                WHERE idHotel = :id \
                GROUP BY YEAR(dateArrive), MONTH(dateArrive) \
                ORDER BY YEAR(dateArrive), MONTH(dateArrive) ASC");

    query.bindValue(":id", idHotel);
    if (query.exec()){
        while(query.next()){
            vector<string> cle = {query.value("mois").toString().toStdString(), query.value("annee").toString().toStdString()};
            nbResa.insert({cle, query.value("nbReservations").toInt()});
        }
        db.close();
        return nbResa;
    }
    else {
        cout << "Impossible de lire dans les stats de reservation" << std::endl;
    }
    db.close();
    return nbResa;
}


/**
 * @brief employeDAO::getMinNbReservationYM
 * Permet de récuperer le min du nombre de reservation d'un hotel par annee et par mois
 * @param map<vector<string>, int> dico
 * @return int, vecteur contenant le min du nombre de reservations sur 1 mois d'un hotel donné, si map vide alors renvoie -1
 */
/*
int employeDAO::getMinNbReservationYM(map<vector<string>, int> dico){
    if(!dico.empty()){
        int min = dico.begin()->second;
        for (pair<vector<string>, int> occurence : dico) {
            if(occurence.second < min){
                min = occurence.second;
            }
        }
        return min;
    }
    return -1;
}
*/

/**
 * @brief employeDAO::getMaxNbReservationYM
 * Permet de récuperer le max du nombre de reservation d'un hotel par annee et par mois
 * @param map<vector<string>, int> dico
 * @return int, vecteur contenant le max du nombre de reservations sur 1 mois d'un hotel donné, si map vide alors renvoie -1
 */
int employeDAO::getMaxNbReservationYM(map<vector<string>, int> dico){
    if(!dico.empty()){
        int max = dico.begin()->second;
        for (pair<vector<string>, int> occurence : dico) {
            if(occurence.second > max){
                max = occurence.second;
            }
        }
        return max;
    }
    return -1;
}

/**
 * @brief getGrapheNbReservationYM
 * Renvoie le graphe du nombre de réservation par mois et année d'un hôtel
 * @param idHotel
 * @return QChartView, graphe du nombre de réservation par mois et année d'un hôtel
 */
QChartView* employeDAO::getGrapheNbReservationYM(int idHotel){
    string mois[12] = {"Janv", "Fevr", "Mars", "Avri", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};
    QBarSet *set0 = new QBarSet("Nombre de reservations");
    map<vector<string>, int> dico = this->getNbReservationYM(idHotel);

    for(pair<vector<string>, int> occurence : dico){
        *set0 << occurence.second;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de reservations par mois");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList moisAnnee;
    for(pair<vector<string>, int> occurence2 : dico){
        string moisPlusAnnee = mois[stoi(occurence2.first.at(0))]+ " " +occurence2.first.at(1) + " : " + to_string(occurence2.second);
        moisAnnee << QString::fromStdString(moisPlusAnnee);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(moisAnnee);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int max = this->getMaxNbReservationYM(dico)+2;

    // amélioration l'affichage : soit de 1 en 1 soit division en 10
    if(max <= 10){
        axisY->setRange(0, max);
        axisY->setTickCount(max+1);
    }
    else {
        // recherche si on est en dizaine, centaine, milliers, etc...
        int coef = 10;
        while(max / coef >= 10){
            coef = coef*10;
        }
        // arrondi a la dizaine au dessus : Exemple 57 => 60, 23 => 30
        max = ((max + coef) / coef) * coef;
        axisY->setRange(0, max);
        // division en 10
        axisY->setTickCount(11);
    }

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

// ------------- Prix moyen chambre
/**
 * @brief employeDAO::getPrixMoyenChambreYM
 * récupérer le prix moyen d'une chambre d'un hotel par mois
 * @param idHotel
 * @return
 */
map<vector<string>,float> employeDAO::getPrixMoyenChambreYM(int idHotel){
    map<vector<string>,float> nbResa;
    QSqlQuery query;

    query.prepare("	SELECT AVG(prix) AS prixMoyen, YEAR(dateArrive) AS annee, MONTH(dateArrive) AS mois \
        FROM reservation \
        INNER JOIN chambre USING(numChambre) \
        INNER JOIN Hotel USING(idHotel) \
        WHERE idHotel = :id \
        GROUP BY YEAR(dateArrive), MONTH(dateArrive) \
        ORDER BY YEAR(dateArrive), MONTH(dateArrive) ASC");

    query.bindValue(":id", idHotel);
    if (query.exec()){
        while(query.next()){
            vector<string> cle = {query.value("mois").toString().toStdString(), query.value("annee").toString().toStdString()};
            nbResa.insert({cle, round(query.value("prixMoyen").toFloat() * 100) / 100});
        }
        db.close();
        return nbResa;
    }
    else {
        cout << "Impossible de lire dans les stats de reservation" << std::endl;
    }
    db.close();
    return nbResa;
}

/**
 * @brief employeDAO::getMinPrixMoyenChambreYM
 * Permet de récuperer le min du prix moyen d'une chambre d'un hotel
 * @param map<vector<string>, float> dico
 * @return float, vecteur contenant le min du prix moyen d'une chambre d'un hote donné, si map vide alors renvoie -1
 */
/*
float employeDAO::getMinPrixMoyenChambreYM(map<vector<string>, float> dico){
    if(!dico.empty()){
        float min = dico.begin()->second;
        for (pair<vector<string>, float> occurence : dico) {
            if(occurence.second < min){
                min = occurence.second;
            }
        }
        return min;
    }
    return -1;
}
*/

/**
 * @brief employeDAO::getMaxPrixMoyenChambreYM
 * Permet de récuperer le max du prix moyen d'une chambre d'un hotel
 * @param map<vector<string>, float> dico
 * @return float, vecteur contenant le max du prix moyen d'une chambre d'un hotel donné, si map vide alors renvoie -1
 */
float employeDAO::getMaxPrixMoyenChambreYM(map<vector<string>, float> dico){
    if(!dico.empty()){
        float max = dico.begin()->second;
        for (pair<vector<string>, float> occurence : dico) {
            if(occurence.second > max){
                max = occurence.second;
            }
        }
        return max;
    }
    return -1;
}

/**
 * @brief getGraphePrixMoyenChambreYM
 * Renvoie le graphe du prix moyen d'une chambre par mois et année d'un hôtel
 * @param idHotel
 * @return QChartView, graphe du prix moyen d'une chambre par mois et année d'un hôtel
 */
QChartView* employeDAO::getGraphePrixMoyenChambreYM(int idHotel){
    string mois[12] = {"Janv", "Fevr", "Mars", "Avri", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};
    QBarSet *set0 = new QBarSet("Prix moyen d'une chambre");
    map<vector<string>, float> dico = this->getPrixMoyenChambreYM(idHotel);

    for(pair<vector<string>, float> occurence : dico){
        *set0 << occurence.second;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Prix moyen d'une chambre par mois");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList moisAnnee;
    for(pair<vector<string>, float> occurence2 : dico){
        string moisPlusAnnee = mois[stoi(occurence2.first.at(0))]+ " " +occurence2.first.at(1) + " : " + to_string((int) occurence2.second) + " eur";
        moisAnnee << QString::fromStdString(moisPlusAnnee);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(moisAnnee);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int max = this->getMaxPrixMoyenChambreYM(dico)+2;

    // amélioration l'affichage : soit de 1 en 1 soit division en 10
    if(max <= 10){
        axisY->setRange(0, max);
        axisY->setTickCount(max+1);
    }
    else {
        // recherche si on est en dizaine, centaine, milliers, etc...
        int coef = 10;
        while(max / coef >= 10){
            coef = coef*10;
        }
        // arrondi a la dizaine au dessus : Exemple 57 => 60, 23 => 30
        max = ((max + coef) / coef) * coef;
        axisY->setRange(0, max);
        // division en 10
        axisY->setTickCount(11);
    }

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

// ----------- Nb clients par ville
/**
 * @brief getNbClientVille
 * Récupérer le nombre de clients par ville de l'hotel
 * @param idHotel
 * @return map<string,int>, map avec la ville comme clé et le nombre de client qui en vient en tant que valeur
 */
map<string,int> employeDAO::getNbClientVille(int idHotel){
    map<string,int> nbClients;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS NbClients, ville \
            FROM (SELECT DISTINCT idClient, Client.idAdresse \
            FROM Client \
            INNER JOIN reservation USING(idClient) \
            INNER JOIN chambre USING(numChambre) \
            INNER JOIN hotel USING(idHotel) \
            WHERE idHotel = :id \
        ) AS subquery \
        INNER JOIN adresse USING(idAdresse) \
        GROUP BY ville \
        ORDER BY ville ASC");

    query.bindValue(":id", idHotel);
    if (query.exec()){
        while(query.next()){
            nbClients.insert({query.value("ville").toString().toStdString(), query.value("NbClients").toInt()});
        }
        db.close();
        return nbClients;
    }
    else {
        cout << "Impossible de lire dans les stats de clients" << std::endl;
    }
    db.close();
    return nbClients;
}

/**
 * @brief getMaxNbClientVille
 * Récupérer le nombre de clients maximum d'une ville
 * @param dico
 * @return int, max de clients d'une ville
 */
int employeDAO::getMaxNbClientVille(map<string, int> dico){
    if(!dico.empty()){
        int max = dico.begin()->second;
        for (pair<string, int> occurence : dico) {
            if(occurence.second > max){
                max = occurence.second;
            }
        }
        return max;
    }
    return -1;
}

/**
 * @brief employeDAO::getGrapheNbClientVille
 * Crée le graphe du nombre de clients par ville
 * @param idHotel
 * @return QChartView, graphe du nombre de clients par ville
 */
QChartView* employeDAO::getGrapheNbClientVille(int idHotel){
    QBarSet *set0 = new QBarSet("Nombre de clients par ville");
    map<string,int> dico = this->getNbClientVille(idHotel);

    for(pair<string, int> occurence : dico){
        *set0 << occurence.second;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList villes;
    for(pair<string, int> occurence : dico){
        villes << QString::fromStdString(occurence.first);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(villes);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int max = this->getMaxNbClientVille(dico)+2;
    axisY->setRange(0, max);
    axisY->setTickCount(max+1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}


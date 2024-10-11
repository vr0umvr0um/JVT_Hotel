#include "administrateur.h"
#include "administrateurdao.h"

#include <iostream>

AdministrateurDAO::AdministrateurDAO() : DAO() {}

Administrateur AdministrateurDAO::connexionAdmin(QString mailAdmin, QString mdpAdmin){
    QSqlQuery query(db);

    query.prepare("SELECT * FROM administrateur WHERE mailAdmin LIKE :mail AND mdpAdmin LIKE :mdp");
    query.bindValue(":mail", mailAdmin);
    query.bindValue(":mdp", QString("%1").arg(QString(QCryptographicHash::hash(mdpAdmin.toUtf8(),QCryptographicHash::Sha256).toHex())));

    if (query.exec()){
        if (query.next()){
            //Administrateur(int idAdmin, string mailAmdin, string mdpAdmin, string pseudoAdmin);
            int idAdmin = query.value("idAdmin").toInt();
            string mailAmdin = query.value("mailAdmin").toString().toStdString();
            string mdpAdmin = query.value("mdpAdmin").toString().toStdString();
            string pseudoAdmin = query.value("pseudoAdmin").toString().toStdString();

            Administrateur admin1(idAdmin, mailAmdin, mdpAdmin, pseudoAdmin);
            return admin1;
        } else {
            qDebug() << "Requete next() incorrecte ";
            qDebug() << query.lastError().text();
        }
    } else {
        qDebug() << "Requete incorrecte "<< query.lastError().text();
    }

    db.close();
    Administrateur admin1;
    return admin1;

}

/**
    * @brief creer
    * Cette méthode permet de créer un admin en base
    * @param Administrateur
    * @return Administrateur - renvoie l'admin crée avec son id mis à jour
    *                   en corrélation avec celui en base
*/
Administrateur AdministrateurDAO::creer(Administrateur admin){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Administrateur (mailAdmin, mdpAdmin, pseudoAdmin) VALUES (:un, :deux, :trois)");
    query.bindValue(":un", QString::fromStdString(admin.getMailAdmin()));

    // hashage du mdp
    QString mdpHash = QString("%1").arg(QString(QCryptographicHash::hash(QString::fromStdString(admin.getMdpAdmin()).toUtf8(),QCryptographicHash::Sha256).toHex()));
    //query.bindValue(":deux", QString::fromStdString(admin.getMdpAdmin()));
    query.bindValue(":deux", mdpHash);
    query.bindValue(":trois", QString::fromStdString(admin.getPseudoAdmin()));

    if(query.exec()){
        admin.setIdAmin(query.lastInsertId().toInt());
    } else {
        qDebug() << "Problème création d'un admin";
    }

    db.close();
    return admin;

}

/**
         * @brief updater
         * Cette méthode permet d'update l'admin, qu'on donne en paramètre, dans la base de données
         * @param Administrateur
         * @return Administrateur
         */
Administrateur AdministrateurDAO::updater(Administrateur admin){
    QSqlQuery query(db);

    // Modification des informations concernant la chambre dans sa table concernée.
    query.prepare("UPDATE administrateur SET mailAdmin=:mail, mdpAdmin=:mdp, pseudoAdmin=:pseudo WHERE idAdmin=:idA");
    query.bindValue(":mail", QString::fromStdString(admin.getMailAdmin()));
    query.bindValue(":mdp", QString::fromStdString(admin.getMdpAdmin()));
    query.bindValue(":pseudo", QString::fromStdString(admin.getPseudoAdmin()));
    query.bindValue(":idA", admin.getIdAdmin());

    query.exec();

    db.close();
    return admin;

}

/**
         * @brief supprimer
         * Cette méthode supprime l'admin, en paramètre, de la base de données
         * @param Administrateur
         */
void AdministrateurDAO::supprimer(Administrateur admin){
    QSqlQuery query(db);

    // suppression des réservations par numchambre
    query.prepare("DELETE FROM Administrateur WHERE idAdmin=:premierevaleur");
    query.bindValue(":premierevaleur", admin.getIdAdmin());

    query.exec();

    db.close();
}

/**
         * @brief lire
         * Cette méthode renvoie l'admin en base dont l'id est celui passé en paramètre
         * @param idAdmin - int
         * @return Administrateur
         */
Administrateur AdministrateurDAO::lire(int idAdmin){
    QSqlQuery query;
    //Marqueurs = :quelquechose
    query.prepare("SELECT * FROM Administrateur WHERE idAdmin=:premierevaleur");
    query.bindValue(":premierevaleur", idAdmin);

    if (query.exec()){
        if (query.next()){
            int id = query.value("idAdmin").toInt();
            string mail = query.value("mailAdmin").toString().toStdString();
            string mdp = query.value("mdpAdmin").toString().toStdString();
            string pseudo = query.value("pseudoAdmin").toString().toStdString();

            Administrateur admin(id, mail, mdp, pseudo);
            return admin;
        } else {
            qDebug() << "Rien de renvoyé lecture d'un admin";
        }
    }
    else
    {
        std::cout << "Problème de lecture d'un admin !" << std::endl;
    }

    db.close();
    Administrateur admin;
    return admin;
}

/**
 * @brief lireAllAdminExceptMe
 * Renvoie tout les admins en base de données sauf celui dont l'id correspond à celui passé en paramètre
 * @param idAdminAPasRenvoyer
 * @return
 */
vector<Administrateur> AdministrateurDAO::lireAllAdminExceptMe(int idAdminAPasRenvoyer){
    QSqlQuery query;
    vector<Administrateur> tabAdmins;
    query.prepare("SELECT idAdmin FROM Administrateur WHERE idAdmin != :id ORDER BY idAdmin ASC");

    query.bindValue(":id", idAdminAPasRenvoyer);
    if (query.exec()){
        // il faut obligatoirement récupérer tout les id dans un tableau
        // avant de lancer les lectures, en effet sinon on réécris par dessus notre query
        // et on perds alors ses informations
        vector<int> tabID;
        while(query.next()){
            tabID.push_back(query.value("idAdmin").toInt());
        }

        for(int id : tabID){
            tabAdmins.push_back(this->lire(id));
        }
        db.close();
        return tabAdmins;
    }
    else {
        cout << "Impossible de lire dans la table Admin" << std::endl;
    }
    db.close();
    return tabAdmins;
}


bool AdministrateurDAO::isMailUsed(string mail){
    QSqlQuery query(db);

    // suppression des réservations par numchambre
    query.prepare("SELECT idAdmin FROM administrateur WHERE mailAdmin = :mail");
    query.bindValue(":mail", QString::fromStdString(mail));

    if (query.exec()){
        db.close();
        return query.next();
    }
    else {
        cout << "Impossible de lire dans la table Admin" << std::endl;
        db.close();
        return false;
    }
}


// ----------------- Méthodes de statistiques ---------------

// ------------- Nb clients en plus par mois
// récupérer le nombre de clients en plus par annee/mois
map<vector<string>,int> AdministrateurDAO::getNbClientsYM(){
    map<vector<string>,int> nbClients;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS nbClients, YEAR(date) AS annee, MONTH(date) AS mois \
            FROM ( \
            SELECT idClient, MIN(dateArrive) AS date \
            FROM reservation \
            GROUP BY idClient \
        ) AS sub \
        GROUP BY YEAR(date), MONTH(date) \
        ORDER BY YEAR(date), MONTH(date) ASC");

        if (query.exec()){
            while(query.next()){
                vector<string> cle = {query.value("mois").toString().toStdString(), query.value("annee").toString().toStdString()};
                nbClients.insert({cle, query.value("nbClients").toInt()});
            }
            db.close();
            return nbClients;
        }
        else {
            cout << "Impossible de lire dans les stats d'admin" << std::endl;
        }
        db.close();
        return nbClients;
}

// récuperer le max du nombre de clients en plus sur l'app par mois
int AdministrateurDAO::getMaxNbClientsYM(map<vector<string>, int> dico){
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

// Renvoie l'instance du graphe rempli
QChartView* AdministrateurDAO::getGrapheNbClientsYM(){
    string mois[12] = {"Janv", "Fevr", "Mars", "Avri", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};
    QBarSet *set0 = new QBarSet("Nombre de clients en plus");
    map<vector<string>, int> dico = this->getNbClientsYM();

    for(pair<vector<string>, int> occurence : dico){
        *set0 << occurence.second;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de clients en plus par mois");
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
    int max = this->getMaxNbClientsYM(dico)+2;

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

// --------------- Nb reservations par mois
// récupérer le nombre de réservations par annee/mois
map<vector<string>,int> AdministrateurDAO::getNbReservationsYM(){
    map<vector<string>,int> nbResa;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS nbResa, YEAR(dateArrive) AS annee, MONTH(dateArrive) AS mois \
            FROM reservation \
            GROUP BY YEAR(dateArrive), MONTH(dateArrive) \
            ORDER BY YEAR(dateArrive), MONTH(dateArrive) ASC");

        if (query.exec()){
            while(query.next()){
                vector<string> cle = {query.value("mois").toString().toStdString(), query.value("annee").toString().toStdString()};
                nbResa.insert({cle, query.value("nbResa").toInt()});
            }
            db.close();
            return nbResa;
        }
        else {
            cout << "Impossible de lire dans les stats d'admin" << std::endl;
        }
        db.close();
        return nbResa;
}

// récuperer le max du nombre de réservations sur l'app par mois
int AdministrateurDAO::getMaxNbReservationsYM(map<vector<string>, int> dico){
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

// Renvoie l'instance du graphe rempli
QChartView* AdministrateurDAO::getGrapheNbReservationsYM(){
    string mois[12] = {"Janv", "Fevr", "Mars", "Avri", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};
    QBarSet *set0 = new QBarSet("Nombre de reservations");
    map<vector<string>, int> dico = this->getNbReservationsYM();

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
    int max = this->getMaxNbReservationsYM(dico)+2;

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

// ---------------- Nb clients par departement
// récupérer le nombre de clients par departement
map<string,int> AdministrateurDAO::getNbClientsDep(){
    map<string,int> nbClients;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS nbClients, SUBSTRING(codePostal, 1, 2) AS dep \
            FROM client \
            INNER JOIN adresse USING(idAdresse) \
            GROUP BY SUBSTRING(codePostal, 1, 2) \
            ORDER BY dep ASC");

        if (query.exec()){
            while(query.next()){
                nbClients.insert({query.value("dep").toString().toStdString(), query.value("nbClients").toInt()});
            }
            db.close();
            return nbClients;
        }
        else {
            cout << "Impossible de lire dans les stats d'admin" << std::endl;
        }
        db.close();
        return nbClients;
}

// récuperer le max du nombre de clients par departement
int AdministrateurDAO::getMaxNbClientsDep(map<string,int> dico){
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

// Renvoie l'instance du graphe rempli
QChartView* AdministrateurDAO::getGrapheNbClientsDep(){
    QBarSet *set0 = new QBarSet("Nombre de clients");
    map<string,int> dico = this->getNbClientsDep();

    for(pair<string, int> occurence : dico){
        *set0 << occurence.second;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de clients par departement");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList depart;
    for(pair<string, int> occurence2 : dico){
        depart << QString::fromStdString(occurence2.first);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(depart);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int max = this->getMaxNbClientsDep(dico)+2;

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

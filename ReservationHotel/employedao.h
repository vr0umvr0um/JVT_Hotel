/**
 * @author Haton Tom
 */
#ifndef EMPLOYEDAO_H
#define EMPLOYEDAO_H

#include "employe.h"
#include "dao.h"

#include <QtWidgets>
#include <QtCharts>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QCryptographicHash>       //Hasher des QString
#include <map>
#include <vector>

using namespace std;

/**
 * @brief classe employeDAO
 * Cette classe va représenter la porte d'entrée dans la bdd pour les employes et donne différentes
 * fonctions qui permettront d'interagir avec
*/
class employeDAO : public DAO
{
public:
    employeDAO();

    Employe creerEmploye(Employe employe);
    Employe updaterEmploye(Employe employe);
    void supprimerEmploye(Employe employe);
    Employe lireEmploye(int numEmploye);
    Employe lireEmploye(QString mail);
    vector<Employe> lireAllEmployeByIdHotel(int idHotel);
    bool existeEmploye(string nomEmploye);
    Employe connexionEmploye(QString mailEmploye, QString mdpEmploye);

    // ------------- fonctions servant aux statistiques --------------
    // récupérer le nombre de réservations par annee/mois
    map<vector<string>,int> getNbReservationYM(int idHotel);
    // récuperer le min et le max du nombre de reservation d'un hotel par mois
    int getMinNbReservationYM(map<vector<string>, int> dico);
    int getMaxNbReservationYM(map<vector<string>, int> dico);
    // Renvoie l'instance du graphe rempli
    QChartView* getGrapheNbReservationYM(int idHotel);

    // récupérer le prix moyen d'une chambre dans l'hotel par mois
    map<vector<string>,float> getPrixMoyenChambreYM(int idHotel);
    // récupérer le prix moyen min et max d'une chambre dans l'hotel par mois
    float getMinPrixMoyenChambreYM(map<vector<string>, float> dico);
    float getMaxPrixMoyenChambreYM(map<vector<string>, float> dico);
    // Renvoie l'instance du graphe rempli
    QChartView* getGraphePrixMoyenChambreYM(int idHotel);

    // récupérer le nombre de clients par ville de l'hotel
    map<string,int> getNbClientVille(int idHotel);
    // Récupérer le nombre de clients maximum d'une ville
    int getMaxNbClientVille(map<string, int> dico);
    // Renvoie l'instance du graphe rempli
    QChartView* getGrapheNbClientVille(int idHotel);
};

#endif // EMPLOYEDAO_H

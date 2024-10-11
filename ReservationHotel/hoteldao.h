#ifndef HotelDAO_H
#define HotelDAO_H

#include "hotel.h"
#include "dao.h"

#include <QTableWidgetItem>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>

#include <map>
#include <vector>

using namespace std;

// -------------------------------
/**
 * @brief classe HotelDAO
 * Cette classe va représenter la porte d'entrée dans la bdd pour les hotels et donne différentes
 * fonctions qui permettront d'interagir avec
 * Auteur : Forest Jules
*/
class HotelDAO : public DAO{
public:
    //pas de constructeur, on prend celui de la classe mère DAO
    HotelDAO();

    Hotel creer(Hotel hotel);
    Hotel updater(Hotel hotel);
    void supprimer(Hotel hotel);
    Hotel lire(int idHotel);

    /**
     * @brief lireAllHotels
     * @return vector<Hotel> - liste des hotels de l'app
     */
    vector<Hotel> lireAllHotels();

    /**
     * @brief renommer
     * Permet de renommer un hotel
     * @param idHotel - id de l'hotel à renommer
     * @param newName - nouveau nom de l'hotel
     */
    void renommer(int idHotel, string newName);
};

#endif // HotelDAO_H

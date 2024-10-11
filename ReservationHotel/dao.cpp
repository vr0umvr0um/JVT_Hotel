#include "dao.h"
#include "SingleConnection.h"

// -------------------- Constructeurs et destructeur ---------------

DAO::DAO() {
    open();
}

DAO::~DAO(){}


// ------------------- fonctions usuelles ---------------
/**
* Cette méthode permet la connexion à la base de données au travers de la
* méthode SingleConnection.getInstance().
*/
void DAO::open() {
    db = SingleConnection::getInstance();
}

/**
* Cette méthode ferme l'accès à la base de données.
*/
void DAO::close() {
    SingleConnection::close();
}

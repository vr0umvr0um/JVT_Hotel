/**
 * @author : Forest Jules
 */
#ifndef DAO_H
#define DAO_H

#include <QSqlDatabase>

using namespace std;

/**
 * @brief la classe DAO
 * Cette classe va servir de classe mère aux
 */
class DAO {
    protected:
        QSqlDatabase db;

    public:
        DAO();
        ~DAO();

    private slots:
        /**
         * @brief open
         * Cette méthode permet la connexion à la base de données au travers de la
         * méthode SingleConnection.getInstance().
         */
        void open();

        /**
         * @brief close
         * Cette méthode ferme l'accès à la base de données.
         */
        void close();
};

#endif // DAO_H

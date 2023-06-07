/**
 * @author Guilherme Martinelli Taglietti
 * @file database.cpp (.cpp file) (implementation file)
 * 
 * Database class members/member functions implementation
 * 
*/

#include <iostream>
#include <sqlite3.h>
#include "database.h"

namespace database{

    /// @brief Database class overloaded constructor to start the database directly
    /// @param sm --> SocialMedia object
    database::Database::Database(socialmedia::SocialMedia &sm){
        if(dbinit(sm)) std::cout << std::endl << "Banco de dados iniciado e carregado com sucesso!" << std::endl;
        else std::cout << std::endl << "Problemas no banco de dados, favor verificar!" << std::endl;
    }

    /// @brief Default class constructor
    database::Database::Database(){};

    /// @brief Class destructor --> Close the database properly
    database::Database::~Database(){
        if(close_database()) 
            std::cout << "Banco de dados encerrado com sucesso!" << std::endl;
    }

    /**
     * @namespace database
     * @class Database
     * @name open_database()
     * @brief Open a database by a filename (if not exists, a new is created according to the name)
     * @attention This is a private member function, called by the class destructor,
     *            and by default, the filename of the database is: "graphsocial.db".
     * @param dbname --> const std::string: Database to be created/opened
     * @return bool --> true: Database successfully opened, false: Error opening database
    */
    bool database::Database::open_database(const std::string& dbname) {
        int rc = sqlite3_open(dbname.c_str(), &db);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name create_table()
     * @brief Create the necessary tables to the application work properly (if not exists)
     * @return bool --> true: Tables successfully created, false: Error during table creation
    */
    bool database::Database::create_table() {
        std::string query = "CREATE TABLE IF NOT EXISTS users ("
                            "email TEXT PRIMARY KEY NOT NULL, "
                            "name TEXT NOT NULL, "
                            "birthdate TEXT NOT NULL, "
                            "phone TEXT NOT NULL, "
                            "city TEXT NOT NULL);"
                            
                            "CREATE TABLE IF NOT EXISTS connections ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "user1 TEXT NOT NULL, "
                            "user2 TEXT NOT NULL);";
        char* err;
        int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao criar a tabela: " << err << std::endl;
            sqlite3_free(err);
            return false;
        }
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name save_user()
     * @brief Save a user in the database
     * @attention This member function is called in SocialMedia class everytime that a new user
     *            is created.
     * @param mail --> const std::string: User email (Unique) (PK) 
     * @param name --> const std::string: User name
     * @param brth --> const std::string: User birthdate
     * @param phne --> const std::string: User phone number 
     * @param cty --> const std::string: User city
     * @return bool --> true: User successfully saved, false: Error saving the user
    */
    bool database::Database::save_user(const std::string &mail, const std::string &nme,
                                       const std::string &brth, const std::string &phne,
                                       const std::string &cty)
    {
        std::string query = "INSERT INTO users (email, name, birthdate, phone, city) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        sqlite3_bind_text(stmt, 1, mail.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, nme.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, brth.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, phne.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, cty.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name load_users()
     * @brief Load all the users in the database to the network graph (nodes hashmap)
     * @attention This member function is called by the overloaded constructor or the dbinit
     *            member function in the database class.
     * @param sm --> SocialMedia object
     * @return bool --> true: Users successfully loaded, false: Error loading users
    */
    bool database::Database::load_users(socialmedia::SocialMedia& sm) {
        std::string query = "SELECT * FROM users;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
            if(
               sqlite3_column_type(stmt, 0) != SQLITE_NULL && 
               sqlite3_column_type(stmt, 1) != SQLITE_NULL &&
               sqlite3_column_type(stmt, 2) != SQLITE_NULL &&
               sqlite3_column_type(stmt, 3) != SQLITE_NULL &&
               sqlite3_column_type(stmt, 4) != SQLITE_NULL
            ){
                std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string birthdate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                std::string city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                sm.insert_node(email, name, birthdate, phone, city);
            }
        }
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name close_database()
     * @brief Properly closes the database
     * @return bool --> true: Database successfully closed, false: Error closing the database
    */
    bool database::Database::close_database(){
        int rc = sqlite3_close(db);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao fechar o banco de dados: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name dbinit()
     * @brief Properly start the database, opening the database, loading the users/links and
     *        creating the tables (if doesn't exists).
     * @param sm --> SocialMedia object
     * @return bool --> true: Database successfully started, false: Error starting the database
    */
    bool database::Database::dbinit(socialmedia::SocialMedia &sm){
        if(open_database("src/Database/graphsocial.db") && create_table() && load_users(sm) && load_links(sm))
            return true;
        return false;
    }

    /**
     * @namespace database
     * @class Database
     * @name save_link()
     * @brief Save a link between two users in the database
     * @attention This member function is called in SocialMedia class everytime that a user follow
     *            a user.
     * @param src --> const std::string: First user of the link
     * @param dest --> const std::string: Second user of the link
     * @return bool --> true: Link successfully saved, false: Error saving link
    */
    bool database::Database::save_link(const std::string &src, const std::string &dest){
        if(search_link(src, dest)) return false;
        std::string query = "INSERT INTO connections (user1, user2) VALUES (?, ?);";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        rc = sqlite3_bind_text(stmt, 1, src.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar parâmetro 'user1': " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_bind_text(stmt, 2, dest.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar parâmetro 'user2': " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name load_links()
     * @brief Load all the links between users in the database to each user that the link belongs
     * @attention This member function is called by the overloaded constructor or the dbinit
     *            member function in the database class.
     * @param sm --> SocialMedia object
     * @return bool --> true: Links successfully loaded, false: Error loading links
    */
    bool database::Database::load_links(socialmedia::SocialMedia& sm){
        std::string query = "SELECT user1, user2 FROM connections;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
            if(sqlite3_column_type(stmt, 0) != SQLITE_NULL && sqlite3_column_type(stmt, 1) != SQLITE_NULL){
                std::string email1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::string email2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                sm.follow(email1, email2);
            }
        }
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name drop_user()
     * @brief Delete a user and all user links in the database
     * @attention This member function is called everytime that a user is deleted
     *            in the SocialMedia class
     * @param s --> const std::string: User email
     * @return bool --> true: User successfully deleted, false: Error deleting user
    */
    bool database::Database::drop_user(const std::string &s){
        std::string query_users = "DELETE FROM users WHERE email = ?";
        std::string query_links = "DELETE FROM connections WHERE user1 = ? OR user2 = ?";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query_users.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        rc = sqlite3_bind_text(stmt, 1, s.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar o valor email na query_users: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query_users: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
        rc = sqlite3_prepare_v2(db, query_links.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        rc = sqlite3_bind_text(stmt, 1, s.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar o valor user1 na query_links: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_bind_text(stmt, 2, s.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar o valor user2 na query_links: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query_links: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
        return true;
    }

    /**
     * @namespace database
     * @class Database
     * @name search_link()
     * @brief Search in the database if a link between two users already exists
     * @param src --> const std::string: First user email
     * @param dest --> const std::string: Second user email
     * @return bool --> true: Link already exists, false: Link doesn't exists
    */
    bool database::Database::search_link(const std::string &src, const std::string &dest){
        std::string query = "SELECT user1 FROM connections WHERE user1 = ? AND user2 = ?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        rc = sqlite3_bind_text(stmt, 1, src.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar o valor user1: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_bind_text(stmt, 1, dest.c_str(), -1, SQLITE_STATIC);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao bindar o valor user2: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ROW){
            sqlite3_finalize(stmt);
            return true;
        } else if(rc == SQLITE_DONE){
            sqlite3_finalize(stmt);
            return false;
        } else{
            std::cout << "Erro ao executar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
    }

} // namespace database

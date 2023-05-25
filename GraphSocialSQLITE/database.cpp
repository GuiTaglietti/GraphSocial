#include <iostream>
#include <sqlite3.h>
#include "database.h"

namespace database {

    database::Database::Database(socialmedia::SocialMedia &sm){
        if(dbinit(sm)) std::cout << "Banco de dados iniciado e carregado com sucesso!" << std::endl;
        else std::cout << "Problemas no banco de dados, favor verificar!" << std::endl;
    }

    database::Database::Database(){};

    database::Database::~Database(){
        close_database();
    }

    bool database::Database::open_database(const std::string& dbname) {
        int rc = sqlite3_open(dbname.c_str(), &db);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    bool database::Database::create_table() {
        std::string query = "CREATE TABLE IF NOT EXISTS users ("
                            "email TEXT PRIMARY KEY NOT NULL, "
                            "name TEXT NOT NULL, "
                            "birthdate TEXT NOT NULL, "
                            "phone TEXT NOT NULL, "
                            "city TEXT NOT NULL);";
        char* err;
        int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao criar a tabela: " << err << std::endl;
            sqlite3_free(err);
            return false;
        }
        return true;
    }

    bool database::Database::save_users(socialmedia::SocialMedia& sm) {
        std::string query = "INSERT INTO users (email, name, birthdate, phone, city) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        //auto teste = sm.get_nodes();
        //std::cout << "Tam -> " << teste.size();
        for(auto& usr : sm.get_nodes()){
            //std::cout << "Entrou no for " << usr.second.user.email << std::endl;
            auto user = usr.second.user;
            sqlite3_bind_text(stmt, 1, user.email.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, user.name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, user.birthdate.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, user.phone.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, user.city.c_str(), -1, SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc != SQLITE_DONE){
                sqlite3_finalize(stmt);
                return false;
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
        std::cout << "Usuários salvos com sucesso no banco de dados!" << std::endl;
        return true;
    }

    bool database::Database::load_users(socialmedia::SocialMedia& sm) {
        std::string query = "SELECT * FROM users;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao preparar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
            std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string birthdate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sm.insert_node(email, name, birthdate, phone, city);
        }
        if(rc != SQLITE_DONE){
            std::cout << "Erro ao executar a query SQL: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
        std::cout << "Usuários carregados com sucesso do banco de dados!" << std::endl;
        return true;
    }

    bool database::Database::close_database() {
        int rc = sqlite3_close(db);
        if(rc != SQLITE_OK){
            std::cout << "Erro ao fechar o banco de dados: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    bool database::Database::dbinit(socialmedia::SocialMedia &sm) {
        if(open_database("graphsocial.db") && create_table() && load_users(sm)) return true;
        return false;
    }

    bool database::Database::dbshutdown(socialmedia::SocialMedia &sm) {
        if(save_users(sm)){
            std::cout << "Usuários salvos com sucesso com sucesso!" << std::endl;
            return true;
        }
        std::cout << "Erro ao salvar usuários no banco!" << std::endl;
        return false;
    }

} // namespace database

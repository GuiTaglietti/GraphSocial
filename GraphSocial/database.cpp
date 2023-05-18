/*
    Database simulation based on file stream

    .cpp file

    Guilherme M. Taglietti - 192370
    José Paulo R. Pereira - 192445
    Lucas Friedrich - 168238
*/

#include "database.h"

namespace database{

    void database::Database::save_users(const std::unordered_map<std::string, node>& users){
        std::ofstream file(filename);
        for(const auto& user : users){
            const node& nde = user.second;
            file << nde.user.email << ','
                 << nde.user.name << ','
                 << nde.user.birthdate << ','
                 << nde.user.phone << ','
                 << nde.user.city << std::endl;
        }
        file.close();
    }

    std::unordered_map<std::string, network::Network::node> database::Database::load_users(){
        std::unordered_map<std::string, node> users;
        std::ifstream file(filename);
        std::string userinfo;
        while(std::getline(file, userinfo)){
            std::stringstream ss(userinfo);
            std::string email, name, birthdate, phone, city;
            std::getline(ss, email, ',');
            std::getline(ss, name, ',');
            std::getline(ss, birthdate, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, city, ',');
            node user(email, name, birthdate, phone, city);
            users[email] = user;
        }
        file.close();
        return users;
    }

} // namespace network
/*
    Database simulation based on file stream

    Header file

    Guilherme M. Taglietti - 192370
    José Paulo R. Pereira - 192445
    Lucas Friedrich - 168238
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "network.h"

namespace database{

class Database : public network::Network{
private:
    const std::string filename = "users.txt";

public:
    void save_users(const std::unordered_map<std::string, node>& users);
    std::unordered_map<std::string, network::Network::node> load_users();
};

} // namespace network

#endif
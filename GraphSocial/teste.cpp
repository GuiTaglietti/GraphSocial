#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "network.h"

namespace network {

    class UserFileManager {
    private:
        const std::string filename = "users.txt";

    public:
        void saveUsers(const std::unordered_map<std::string, node>& users) {
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo para salvar os usuários." << std::endl;
                return;
            }

            for (const auto& pair : users) {
                const node& user = pair.second;
                file << user.user.email << ','
                     << user.user.name << ','
                     << user.user.birthdate << ','
                     << user.user.phone << ','
                     << user.user.city << '\n';
            }

            file.close();
            std::cout << "Usuários salvos com sucesso." << std::endl;
        }

        std::unordered_map<std::string, network::Network::node> loadUsers() {
            std::unordered_map<std::string, network::Network::node> users;
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo para carregar os usuários." << std::endl;
                return users;
            }

            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string email, name, birthdate, phone, city;
                std::getline(ss, email, ',');
                std::getline(ss, name, ',');
                std::getline(ss, birthdate, ',');
                std::getline(ss, phone, ',');
                std::getline(ss, city, ',');
                network::Network::node user(email, name, birthdate, phone, city);
                users[email] = user;
            }

            file.close();
            std::cout << "Usuários carregados com sucesso." << std::endl;
            return users;
        }
    };

    class ManagedNetwork : public Network {
    private:
        UserFileManager fileManager;

    public:
        ManagedNetwork() {
            nodes = fileManager.loadUsers();
        }

        ~ManagedNetwork() {
            fileManager.saveUsers(nodes);
        }
    };

}  // namespace network

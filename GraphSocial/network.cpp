/*

Network class member functions construction file

.cpp file

Guilherme M. Taglietti - 192370

*/

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "network.h"

namespace network{

    network::Network::Network(){}

    network::Network::Network(const node &n){
        node(n.user.email, n.user.name, n.user.birthdate,
             n.user.phone, n.user.city);
    }

    // Construtor de cópia
    network::Network::Network(const Network &other){
        nodes = other.nodes;
    }

    network::Network::~Network(){}

    network::Network::error_t network::Network::insert_node(const std::string &mail, const std::string &nm,
                                                            const std::string &brth, const std::string &phne,
                                                            const std::string &cty)
    {
        errors.reset();
        if(nodes.count(mail) > 0){
            errors.flag = true;
            errors.errmsg = "O email informado já está sendo usado por outro usuário!";
            return errors;
        }  
        node n(mail, nm, brth, phne, cty);                                                        
        nodes[mail] = n;                          
        return errors;
    }

    network::Network::node* network::Network::find(const std::string &s){
        auto it = nodes.find(s);
        return it == nodes.end() ? nullptr : &it->second;
    }

    network::Network::error_t network::Network::follow(const std::string &src, const std::string &dest){
        errors.reset();
        auto psrc = find(src);
        auto pdest = find(dest);
        if(!psrc || !pdest){
            errors.flag = true;
            errors.errmsg = "Um dos usuários informados não existe na rede!";
            return errors;
        }
        if(psrc->links.size() > 0){
            for(int i = 0; i < psrc->links.size(); i++){
                if(psrc->links[i]->user.email == pdest->user.email){
                    errors.flag = true;
                    errors.errmsg = "Estes usuários já se seguem mutuamente!";
                    return errors;
                }
            }
        }
        psrc->links.push_back(pdest);
        errors.errmsg = "Usuario: " + src + " começou a seguir: " + dest;
        return errors;
    }

    network::Network::error_t network::Network::unfollow(const std::string &src, const std::string &dest){
        errors.reset();
        auto psrc = find(src);
        auto pdest = find(dest);
        if(!psrc || !pdest){
            errors.flag = true;
            errors.errmsg = "Um/Ambos usuário(s) não existe(m) na rede!";
            return errors;
        }
        bool found = false;
        for(auto it = psrc->links.begin(); it != psrc->links.end(); ++it){
            if((*it)->user.email == dest){ // Faz o cast para ponteiro
                psrc->links.erase(it);
                found = true;
                break;
            }
        }
        if(!found){
            errors.flag = true;
            errors.errmsg = "O usuário informado não segue o outro usuário!";
            return errors;
        }
        return errors;
    }

    void network::Network::list_user(const std::string &s){
        auto user = find(s);
        if(!user){
            std::cout << "Usuário inexistente!" << std::endl;
            return;
        }
        std::cout << "Informações do usuário: " << s << std::endl;
        std::cout << user;
        std::cout << "Seguidores: " << indegree(s) << std::endl;
        std::cout << "Seguindo: " << outdegree(s) << std::endl;
        std::cout << std::endl;
    }

    void network::Network::list_network(){
        std::cout << "Informações da rede:" << std::endl;
        for(auto &it : nodes){
            std::cout << std::endl;
            std::cout << it.second;
            std::cout << "Seguidores: " << indegree(it.second.user.email) << std::endl;
            std::cout << "Seguindo: " << outdegree(it.second.user.email) << std::endl;
        }
        std::cout << std::endl;
    }

    void network::Network::debug(const std::string &filetype) const{
        export_to_file(filetype);
        std::system("dot -Tx11 network.dot");
    }

    void network::Network::export_to_file(const std::string &filetype) const{
        std::string filename = (filetype == "dot") ? "network.dot" : "network.dot." + filetype;
        std::ofstream dot(filename);
        dot << "Digraph{\n";
        for(auto n : nodes){
            dot << "\t\"" << n.first << '"';
            if(!n.second.links.empty()){
                dot << " -> { ";
                for(auto link : n.second.links){
                    dot << '"' << link->user.email << "\" ";
                }
                dot << "}";
            }
            dot << "\n";
        }
        dot << "}\n";
    }

    network::Network::error_t network::Network::remove(const std::string &s){
        errors.reset();
        auto temp = find(s);
        int op;
        if(!temp){
            errors.flag = true;
            errors.errmsg = "O usuário não existe!";
            return errors;
        }
        std::cout << std::endl;
        std::cout << "Informações do usuário:" << std::endl;
        std::cout << std::endl;
        std::cout << *temp;
        std::cout << "Deseja realmente excluir o usuário? (1 = SIM // 2 = NÃO): ";
        std::cin >> op;
        switch(op){
            case 1:
                for(auto n : nodes){
                    auto links = n.second.links;
                    for(auto it = links.begin(); it != links.end();){
                        if((*it)->user.email == s) it = links.erase(it); // Faz o cast para ponteiro
                        else ++it;
                    }
                }
                nodes.erase(s);
                return errors;
            
            case 2:
                errors.errmsg = "Operação cancelada!";
                return errors;

            default:
                errors.errmsg = "Opção inválida!";
                errors.flag = true;
                return errors;
        }
    }

    size_t network::Network::indegree(const std::string &s) const{
        size_t count = 0;
        for(auto n : nodes)
            for(auto link : n.second.links) 
                if(link->user.email == s) count++;
        return count;
    }

    size_t network::Network::outdegree(const std::string &s){
        auto pnode = find(s);
        if(!pnode) return 0;
        return pnode->links.size();
    }

    int network::Network::dijkstra(const std::string &src, const std::string &dest){
        const long long INF = 1e9;
        if(!find(src) || !find(dest)) return -1;
        std::unordered_map<std::string, int> distances;
        std::unordered_map<std::string, std::string> paths;
        std::unordered_map<std::string, bool> visited;
        for(const auto &n : nodes) 
            distances[n.first] = INF;
        distances[src] = 0;
        while(true){
            std::string min;
            int mindist = INF;
            for(const auto &n : nodes){
                if(!visited[n.first] && distances[n.first] < mindist){
                    min = n.first;
                    mindist = distances[n.first];
                }
            }
            if(min.empty() || mindist == INF) break;
            visited[min] = true;
            auto &node = nodes[min];
            for(auto &link : node.links){
                if(!visited[link->user.email]){
                    int newdist = distances[min] + 1; // Considerei peso como 1
                    if(newdist < distances[link->user.email]){
                        distances[link->user.email] = newdist;
                        paths[link->user.email] = min;
                    }
                }
            }
        }
        if(distances[dest] == INF) return 0;
        std::vector<std::string> path;
        std::string curr = dest;
        while(curr != src){
            path.push_back(curr);
            curr = paths[curr];
        }
        path.push_back(src);
        std::cout << "Menor caminho de " << src << " para " << dest << ": ";
        for(auto it = path.rbegin(); it != path.rend(); ++it){
            std::cout << *it;
            if(it + 1 != path.rend()) std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "Tamanho do caminho: " << distances[dest] << std::endl;
        std::cout << std::endl;
        return distances[dest];
    }

    network::Network::error_t network::Network::shortest_path(const std::string &src, const std::string &dest){
        errors.reset();
        int dist = dijkstra(src, dest);
        switch(dist){
            case -1:
                errors.flag = true;
                errors.errmsg = "Um/Ambos usuário(s) informado(s) não existe(m)!";
                return errors;

            case 0:
                errors.flag = true;
                errors.errmsg = "Não existe caminho possível!";
                return errors;

            default:
                return errors;
        }
    }

    std::ostream& operator<<(std::ostream &os, const network::Network::node &n){
        os << "Email: " << n.user.email << std::endl;
        os << "Nome: " << n.user.name << std::endl;
        os << "Data de nascimento: " << n.user.birthdate << std::endl;
        os << "Número de telefone: " << n.user.phone << std::endl;
        os << "Cidade: " << n.user.city << std::endl;
        return os;
    }

    network::Network& network::Network::operator=(const Network &rhs){
        if(this == &rhs) nodes = rhs.nodes;
        return *this;
    }

}
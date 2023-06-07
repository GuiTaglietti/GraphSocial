/**
 * @author Guilherme Martinelli Taglietti
 * @file network.cpp (.cpp file) (implementation file)
 * 
 * Network class members/member functions implementation
 * 
*/

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "network.h"

namespace network{

    /// @brief Default class constructor
    network::Network::Network(){}

    /// @brief Overloaded constructor to directly start a node
    /// @param n --> Node to be started
    network::Network::Network(const node &n){
        node(n.user.email, n.user.name, n.user.birthdate,
             n.user.phone, n.user.city);
    }

    /// @brief Class destructor
    network::Network::~Network(){}

    /**
     * @namespace network
     * @class Network
     * @name insert_node()
     * @brief Member function to insert a node in the graph (nodes hashmap)
     * @param mail --> const std::string: User email (Unique) 
     * @param name --> const std::string: User name
     * @param brth --> const std::string: User birthdate
     * @param phne --> const std::string: User phone number 
     * @param cty --> const std::string: User city
     * @return error_t --> Struct defined in network.h to handle errors  
    */
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

    /**
     * @namespace network
     * @class Network
     * @name find()
     * @brief Search for a user in the graph by email
     * @param s --> const std::string: Email to be searched
     * @return error_t --> Struct defined in network.h to handle errors  
    */
    network::Network::node* network::Network::find(const std::string &s){
        auto it = nodes.find(s);
        return it == nodes.end() ? nullptr : &it->second;
    }

    /**
     * @namespace network
     * @class Network
     * @name follow()
     * @brief Create a link between two users, where the first user start to follow the second user
     * @param src --> const std::string: First user for the link creation
     * @param dest --> const std::string: Second user for the link creation
     * @return error_t --> Struct defined in network.h to handle errors  
    */
    network::Network::error_t network::Network::follow(const std::string &src, const std::string &dest){
        errors.reset();
        auto psrc = find(src);
        auto pdest = find(dest);
        if(!psrc || !pdest){
            errors.flag = true;
            errors.errmsg = "Um dos usuários informados não existe na rede!";
            return errors;
        }
        if(psrc->links.size()){
            for(size_t i = 0; i < psrc->links.size(); i++){
                if(psrc->links[i]->user.email == pdest->user.email){
                    errors.flag = true;
                    errors.errmsg = "O usuário: " + src + " já segue: " + dest + "!";
                    return errors;
                }
            }
        }
        psrc->links.push_back(pdest);
        errors.errmsg = "Usuario: " + src + " começou a seguir: " + dest;
        return errors;
    }

    /**
     * @namespace network
     * @class Network
     * @name unfollow()
     * @brief Delete a link (if exists) between two users, 
     *        where the first user unfollow the second user
     * @param src --> const std::string: First user for the link erase
     * @param dest --> const std::string: Second user for the link erase
     * @return error_t --> Struct defined in network.h to handle errors  
    */
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
            if((*it)->user.email == dest){
                psrc->links.erase(it);
                found = true;
                break;
            }
        }
        if(!found){
            errors.flag = true;
            errors.errmsg = "O usuário: " + src + " não segue: " + dest + "!";
            return errors;
        }
        return errors;
    }

    /**
     * @namespace network
     * @class Network
     * @name list_user()
     * @brief Search for a user by email and show informations (if user exists)
     * @param s --> const std::string: Email to be searched
    */
    void network::Network::list_user(const std::string &s){
        auto user = find(s);
        if(!user){
            std::cout << "Usuário inexistente!" << std::endl;
            return;
        }
        std::cout << "Informações do usuário: " << s << std::endl;
        std::cout << *user;
        std::cout << "Seguidores: " << indegree(s) << std::endl;
        std::cout << "Seguindo: " << outdegree(s) << std::endl;
        std::cout << std::endl;
    }

    /**
     * @namespace network
     * @class Network
     * @name list_users()
     * @brief List informations about all users in the network graph
    */
    void network::Network::list_users(){
        std::cout << std::endl;
        std::cout << "Usuários da rede:" << std::endl;
        for(auto &it : nodes){
            std::cout << std::endl;
            std::cout << it.second;
            std::cout << "Seguidores: " << indegree(it.second.user.email) << std::endl;
            std::cout << "Seguindo: " << outdegree(it.second.user.email) << std::endl;
        }
        std::cout << std::endl;
    }

    /**
     * @namespace network
     * @class Network
     * @name network_indegree_rate()
     * @brief Get the medium indegree rate of the network graph
     * @attention Specially used for list_network() member function  
    */
    double network::Network::network_indegree_rate(){
        double ans = 0;
        for(const auto &usr : nodes)
            ans += indegree(usr.first);
        return ans/nodes.size();
    }

    /**
     * @namespace network
     * @class Network
     * @name network_outdegree_rate()
     * @brief Get the medium outdegree rate of the network graph
     * @attention Specially used for list_network() member function  
    */
    double network::Network::network_outdegree_rate(){
        double ans = 0;
        for(const auto &usr : nodes)
            ans += outdegree(usr.first);
        return ans/nodes.size();
    }

    /**
     * @namespace network
     * @class Network
     * @name most_followed_user()
     * @brief Get the most followed user of the network
     * @attention Specially used for list_network() member function  
    */
    std::string network::Network::most_followed_user(){
        std::string ans;
        unsigned int max = 0;
        for(const auto& node : nodes){
            unsigned int flwrs = indegree(node.first);
            if(flwrs > max){
                max = flwrs;
                ans = node.first;
            }
        }
        return ans;
    }

    /**
     * @namespace network
     * @class Network
     * @name network_graph_diameter()
     * @brief Get the graph diameter of network graph
     * @attention Specially used for list_network() member function  
    */
    int network::Network::network_graph_diameter(){
        int ans = 0;
        for(auto it1 = nodes.begin(); it1 != nodes.end(); ++it1){
            for(auto it2 = std::next(it1); it2 != nodes.end(); ++it2){
                int distance = dijkstra(it1->first, it2->first, true);
                if(distance > ans) ans = distance;
            }
        }
        return ans;
    }

    /**
     * @namespace network
     * @class Network
     * @name create_dot()
     * @brief Create the graph using dot language (graphviz dependence) to a file (.dot)
    */
    void network::Network::create_dot() const{
        std::string filename = "dot_exports/network.dot";
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

    /**
     * @namespace network
     * @class Network
     * @name remove()
     * @brief Remove a user from the network graph and all user connections (if exists)
     * @param s --> const std::string: User email to be searched
     * @return error_t --> Struct defined in network.h to handle errors  
    */
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
                for(auto &n : nodes){
                    auto &lnks = n.second.links;
                    auto it = std::find(lnks.begin(), lnks.end(), temp);
                    if(it != lnks.end()) lnks.erase(it);
                }
                nodes.erase(s);
                return errors;
            
            case 2:
                errors.errmsg = "Operação cancelada!";
                errors.flag = true;
                return errors;

            default:
                errors.errmsg = "Opção inválida!";
                errors.flag = true;
                return errors;
        }
    }

    /**
     * @namespace network
     * @class Network
     * @name indegree()
     * @brief Get the indegree of a user node
     * @param s --> const std::string: User email to be searched
     * @return unsigned int --> Indegree number of the user node  
    */
    unsigned int network::Network::indegree(const std::string &s) const{
        unsigned int count = 0;
        for(auto n : nodes)
            for(auto link : n.second.links) 
                if(link->user.email == s) count++;
        return count;
    }

    /**
     * @namespace network
     * @class Network
     * @name outdegree()
     * @brief Get the outdegree of a user node
     * @param s --> const std::string: User email to be searched
     * @return unsigned int --> Outdegree number of the user node  
    */
    unsigned int network::Network::outdegree(const std::string &s){
        auto pnode = find(s);
        if(!pnode) return 0;
        return pnode->links.size();
    }

    /**
     * @namespace network
     * @class Network
     * @name dijkstra()
     * @brief Get the shortest path between two users
     * @attention All the costs (weight) of the graph are considered: 1
     *            Also used to find the diameter of the graph
     * @param src --> const std::string: First user (Source)
     * @param dest --> const std::string: Second user (Destination)
     * @param flag --> bool: Used to show the path user by user (If false: Show) (False by default)
     * @return int --> Size of the path   
    */
    int network::Network::dijkstra(const std::string &src, const std::string &dest, bool flag = false){
        const long INF = (long)1e9;
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
        if(!flag){
            std::cout << "Menor caminho de " << src << " para " << dest << ": ";
            for(auto it = path.rbegin(); it != path.rend(); ++it){
                std::cout << *it;
                if(it + 1 != path.rend()) std::cout << " -> ";
            }
            std::cout << std::endl;
            std::cout << "Tamanho do caminho: " << distances[dest] << std::endl;
            std::cout << std::endl;
        }
        return distances[dest];
    }

    /**
     * @namespace network
     * @class Network
     * @name shortest_path()
     * @brief Get the shortest_path between two users (if exists)
     *        Also handle errors using the int return of the private
     *        dijkstra() member function and error_t struct
     * @param src --> const std::string: First user (Source)
     * @param dest --> const std::string: Second user (Destination) 
     * @return error_t --> Struct defined in network.h to handle errors  
    */
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

    /**
     * @namespace network
     * @overload --> "<<" operator
     * @brief Friend function (Not a member function of the class but have access to private members)
     *        Used to bind user information in a output stream (ostream)
     * @param os --> std::ostream: Output stream that store the node data 
     * @param n --> Network::node: Network class user node (user informations)
     * @return os --> Output stream with the user informations
    */
    std::ostream& operator<<(std::ostream &os, const network::Network::node &n){
        os << "Email: " << n.user.email << std::endl;
        os << "Nome: " << n.user.name << std::endl;
        os << "Data de nascimento: " << n.user.birthdate << std::endl;
        os << "Número de telefone: " << n.user.phone << std::endl;
        os << "Cidade: " << n.user.city << std::endl;
        return os;
    }

}
/*

Network graph implementation based on social media

Header file

Guilherme M. Taglietti

*/

#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <unordered_map>
#include <vector>

namespace network{

class Network{
protected:
    struct userdata{
        std::string email;
        std::string name;
        std::string birthdate;
        std::string phone;
        std::string city;
    };

    struct node{
        userdata user;
        std::vector<node*> links;
        node(){}
        node(const std::string &mail, const std::string &nm,
             const std::string &brth, const std::string &phne,
             const std::string &cty)
            {
                user.email = mail;
                user.name = nm;
                user.birthdate = brth;
                user.phone = phne;
                user.city = cty;
            }
    };

    struct error_t{
        bool flag = false;
        std::string errmsg;
        void reset(){
            flag = false;
            errmsg = "";
        }
    };
    
    std::unordered_map<std::string, node> nodes;
    error_t errors;

    int dijkstra(const std::string &src, const std::string &dest);

public:
    Network();
    Network(const node &n);
    Network(const Network &other); // Construtor de cópia
    virtual ~Network();
    error_t insert_node(const std::string &mail, const std::string &nm,
                        const std::string &brth, const std::string &phne,
                        const std::string &cty);
    size_t size() const { return nodes.size(); } // Inline
    node* find(const std::string &s);
    error_t follow(const std::string &src, const std::string &dest);
    error_t unfollow(const std::string &src, const std::string &dest);
    void export_to_file(const std::string &s) const;
    void list_user(const std::string &s);
    void list_network();
    unsigned int indegree(const std::string &s) const;
    unsigned int outdegree(const std::string &s);
    unsigned int degree(const std::string &s) { return indegree(s) + outdegree(s); } // Inline
    error_t remove(const std::string &s);
    error_t shortest_path(const std::string &src, const std::string &dest);
    std::unordered_map<std::string, node> get_nodes() const;
    friend std::ostream& operator<<(std::ostream &os, const node &n);
    network::Network& operator=(const Network &rhs);
    void debug(const std::string &filetype) const;

}; 

 }// namespace network

#endif
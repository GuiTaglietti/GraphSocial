/**
 * @author Guilherme Martinelli Taglietti
 * @file socialmedia.cpp (.cpp file) (implementation file)
 * 
 * SocialMedia class members/member functions implementation
 * @extends @class Network 
 * 
*/

#include <iostream>
#include <algorithm>
#include "socialmedia.h"
#include "network.cpp"
#include "database.cpp"

namespace socialmedia{

    /// @brief Default class constructor.
    socialmedia::SocialMedia::SocialMedia(){}

    /// @brief Class destructor.
    socialmedia::SocialMedia::~SocialMedia(){}

    /**
     * @namespace socialmedia
     * @class SocialMedia
     * @name show_menu()
     * @brief Display the menu in the terminal.
    */
    void socialmedia::SocialMedia::show_menu(){
        std::cout << std::endl;
        std::cout << "Bem vindo a GraphSocial, escolha as opções de funcionalidades:" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "1 - Cadastrar novo usuário" << std::endl;
        std::cout << "2 - Seguir usuário" << std::endl;
        std::cout << "3 - Deixar de seguir usuário" << std::endl;
        std::cout << "4 - Listar usuários" << std::endl;
        std::cout << "5 - Consultar dados de um usuário" << std::endl;
        std::cout << "6 - Excluir usuário" << std::endl;
        std::cout << "7 - Verificar caminho para um usuário" << std::endl;
        std::cout << "8 - Exportar rede" << std::endl;
        std::cout << "9 - Exibir informações da rede" << std::endl; 
    }

    /**
     * @namespace socialmedia
     * @class SocialMedia
     * @name is_number()
     * @brief Check if a string is number.
     * @attention It checks a "std::string" because if the user input was an "int" and the user
     *            insert a string, the program will die (Even with try/catch). 
     *            With strings, the user can input anything and the function 
     *            will handle the errors properly.
     * @param s --> const std::string: User input to be validated if is a number or not
     * @return bool --> true: Is a number // false: Isn't a number
    */
    bool socialmedia::SocialMedia::is_number(const std::string &s){
        auto it = s.begin();
        while(it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    /**
     * @namespace socialmedia
     * @class SocialMedia
     * @name get_instruction()
     * @brief Get a user input and check if is valid using is_number() member function.
     * @return int --> If input is a number: convert the string to a number and returns
     *                 Else: return -1 (Used to handle errors)
    */
    int socialmedia::SocialMedia::get_instruction(){
        std::string temp;
        std::cout << std::endl;
        std::cout << "Digite a opção (Digite o número referente a opção!): ";
        std::cin >> temp;
        if(is_number(temp) && std::stoi(temp) >= 0 && std::stoi(temp) < 10) return std::stoi(temp);
        return -1;
    }

    /**
     * @namespace socialmedia
     * @overload --> "<<" operator
     * @brief Friend function (Not a member function of the class but have access to private members).
     *        Used to bind network graph information in a output stream (ostream).
     * @param os --> std::ostream: Output stream that store the network graph data 
     * @param sm --> SocialMedia: Socialmedia class (network graph informations)
     * @return os --> Output stream with the network graph informations
    */
    std::ostream& operator<<(std::ostream &os, socialmedia::SocialMedia &sm){
        os << "Informações da rede:" << std::endl << std::endl;
        os << "Quantidade de usuários cadastrados: " << sm.nodes.size() << std::endl;
        os << "Grau médio de entrada: " << sm.network_indegree_rate() << std::endl;
        os << "Grau médio de saída: " << sm.network_outdegree_rate() << std::endl;
        os << "Diâmetro da rede (grafo da rede): " << sm.network_graph_diameter() << std::endl;
        os << "Usuário com maior número de seguidores: " << sm.most_followed_user() << std::endl;
        return os;
    }

    /**
     * @namespace socialmedia
     * @class SocialMedia
     * @name init()
     * @brief Start the database and the application, get user inputs and validate them
     *        using a switch statement to delegate what the application will do.
     *        Also control the database flow (insert/delete users and links).
     * @param sm --> SocialMedia object
    */
    void socialmedia::SocialMedia::init(socialmedia::SocialMedia &sm){
        database::Database db(sm);
        show_menu();
        int ins;
        while(true){
            ins = get_instruction();
            switch(ins){
                case 0:
                    std::cout << std::endl;
                    std::cout << "Até mais!" << std::endl;
                    return;

                case 1:
                {
                    std::string mail, nm, brth, phne, cty;
                    std::cout << std::endl;
                    std::cout << "Cadastro de usuário:" << std::endl;
                    std::cout << "Email: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    std::cout << "Nome: ";
                    std::cin >> nm;
                    std::cout << std::endl;
                    std::cout << "Data de nascimento: ";
                    std::cin >> brth;
                    std::cout << std::endl;
                    std::cout << "Número de telefone: ";
                    std::cin >> phne;
                    std::cout << std::endl;
                    std::cout << "Cidade: ";
                    std::cin >> cty;
                    std::cout << std::endl;
                    error_t insert = insert_node(mail, nm, brth, phne, cty);
                    if(insert.flag){
                        std::cout << insert.errmsg << std::endl;
                        break;
                    }
                    show_menu();
                    db.save_user(mail, nm, brth, phne, cty);
                    std::cout << std::endl;
                    std::cout << "Usuário cadastrado com sucesso!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 2:
                {
                    std::string mail, mail2;
                    std::cout << std::endl;
                    std::cout << "Informe o email do primeiro usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do segundo usuário: ";
                    std::cin >> mail2;
                    std::cout << std::endl;
                    error_t flw = follow(mail, mail2);
                    if(flw.flag){
                        std::cout << flw.errmsg << std::endl;
                        break;
                    }
                    show_menu();
                    db.save_link(mail, mail2);
                    std::cout << std::endl;
                    std::cout << flw.errmsg << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 3:
                {
                    std::string mail, mail2;
                    std::cout << std::endl;
                    std::cout << "Informe o email do primeiro usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do segundo usuário: ";
                    std::cin >> mail2;
                    std::cout << std::endl;
                    error_t unflw = unfollow(mail, mail2);
                    if(unflw.flag){
                        std::cout << unflw.errmsg << std::endl;
                        break;
                    }
                    show_menu();
                    std::cout << std::endl;
                    std::cout << "Operação realizada com sucesso!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 4:
                    show_menu();
                    list_users();
                    break;
                
                case 5:
                {
                    std::string mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    show_menu();
                    list_user(mail);
                    break;
                }

                case 6:
                {
                    std::string mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    error_t exclude = remove(mail);
                    if(exclude.flag){
                        std::cout << exclude.errmsg << std::endl;
                        break;
                    }
                    show_menu();
                    db.drop_user(mail);
                    std::cout << std::endl;
                    std::cout << "Usuário excluido com sucesso!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 7:
                {
                    std::string mail, mail2;
                    std::cout << std::endl;
                    std::cout << "Informe o email do primeiro usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do segundo usuário: ";
                    std::cin >> mail2;
                    std::cout << std::endl;
                    show_menu();
                    error_t path = shortest_path(mail, mail2);
                    if(path.flag){
                        std::cout << std::endl;
                        std::cout << path.errmsg << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    break;
                }

                case 8:
                {
                    show_menu();
                    std::string temp;
                    std::string format_buffer[4] = {"pdf", "png", "jpeg", "dot"};
                    std::cout << std::endl;
                    std::cout << "Digite o formato do arquivo que deseja exportar (pdf, png, jpeg, dot): ";
                    std::cin >> temp;
                    if(std::count(std::begin(format_buffer), std::end(format_buffer), temp)){
                        export_to_file(temp);
                        std::cout << "Arquivo network." << temp << " criado com sucesso!" << std::endl;
                        break;
                    }
                    std::cout << "Formato de arquivo inexistente/indisponível!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 9:
                    show_menu();
                    std::cout << std::endl;
                    std::cout << sm << std::endl;
                    break;

                default:
                    show_menu();
                    std::cout << std::endl;
                    std::cout << "Opção inválida, por favor insira novamente!" << std::endl;
                    break;
            }   
        }
    }

}
/*
    Social media control class member functions implementation

    .cpp file

    Guilherme Martinelli Taglietti - 192370
*/

#include "socialmedia.h"
#include <iostream>

namespace socialmedia{

    socialmedia::SocialMedia::SocialMedia(){}

    socialmedia::SocialMedia::~SocialMedia(){}

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

    bool socialmedia::SocialMedia::is_number(const std::string &s){
        auto it = s.begin();
        while(it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    std::string socialmedia::SocialMedia::get_instruction(){
        std::string temp;
        std::cout << std::endl;
        std::cout << "Digite a opção (Digite o número referente a opção!): ";
        std::cin >> temp;
        return temp;
    }

    int socialmedia::SocialMedia::load_instruction(const std::string &s){
        if(is_number(s) && std::stoi(s) >= 0 && std::stoi(s) < 10) return std::stoi(s);
        std::cout << "Opção inválida, por favor insira novamente!" << std::endl;
        load_instruction(get_instruction());
    }

    void socialmedia::SocialMedia::init(){
        datacontrol::DataControl dbinit;
        show_menu();
        std::string start = get_instruction();
        while(true){
            int ins = load_instruction(start);
            switch(ins){
                case 0:
                    std::cout << std::endl;
                    std::cout << "Até mais!" << std::endl;
                    break;

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
                    std::cout << "Operação realizada com sucesso!" << std::endl;
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
                    std::cout << "Operação realizada com sucesso!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 4:
                    list_network();
                    break;
                
                case 5:
                {
                    std::string mail;
                    std::cout << std::endl;
                    std::cout << "Informe o email do usuário: ";
                    std::cin >> mail;
                    std::cout << std::endl;
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
                    error_t path = shortest_path(mail, mail2);
                    if(path.flag){
                        std::cout << path.errmsg << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    break;
                }

                case 8:
                    std::cout << std::endl;
                    std::cout << "Em implementação...";
                    std::cout << std::endl;

                case 9:
                    std::cout << std::endl;
                    std::cout << "Em implementação...";
                    std::cout << std::endl;
            }   
        }
    }

}
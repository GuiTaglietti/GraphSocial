/*
    Social media control class member functions implementation

    .cpp file

    Guilherme Martinelli Taglietti - 192370
*/

#include <iostream>
#include <algorithm>
#include "socialmedia.h"
#include "network.cpp"
#include "database.cpp"

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

    int socialmedia::SocialMedia::get_instruction(){
        std::string temp;
        std::cout << std::endl;
        std::cout << "Digite a opção (Digite o número referente a opção!): ";
        std::cin >> temp;
        if(is_number(temp) && std::stoi(temp) >= 0 && std::stoi(temp) < 10) return std::stoi(temp);
        return -1;
    }

    void socialmedia::SocialMedia::init(socialmedia::SocialMedia &sm){
        database::Database db;
        db.dbinit(sm);
        show_menu();
        int ins;
        while(true){
            ins = get_instruction();
            switch(ins){
                case 0:
                    std::cout << std::endl;
                    std::cout << "Até mais!" << std::endl;
                    if(db.dbshutdown(sm)) return;
                    std::cout << "Erro ao salvar usuários/links no banco de dados, por favor tente novamente!" << std::endl;
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
                    show_menu();
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
                    std::cout << std::endl;
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
                    show_menu();
                    std::cout << std::endl;
                    std::cout << "Operação realizada com sucesso!" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                case 4:
                    show_menu();
                    list_network();
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
                    std::string format_buffer[5] = {"pdf", "png", "jpeg", "dot"};
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
                    std::cout << "Em implementação...";
                    std::cout << std::endl;
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
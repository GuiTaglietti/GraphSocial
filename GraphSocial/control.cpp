/*
    Social media control class member functions implementation

    .cpp file

    Guilherme Martinelli Taglietti - 192370
*/

#include "control.h"
#include <iostream>

namespace network{

    void network::SocialMedia::show_menu(){
        std::cout << std::endl;
        std::cout << "Bem vindo a GraphSocial, escolha as opções de funcionalidades:" << std::endl;
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

}
#include "control.cpp"
using namespace network;

int main(){
    SocialMedia teste;
    teste.insert_node("teste@upf.br", "Gui", "07/09/2003", "(54)984113901", "Sarandi");
    teste.insert_node("abc@upf.br", "Lucas", "07/09/2003", "(54)984113901", "Sarandi");
    teste.insert_node("dce@upf.br", "José", "07/09/2003", "(54)984113901", "Sarandi");
    teste.follow("teste@upf.br", "dce@upf.br");
    teste.follow("dce@upf.br", "abc@upf.br");
    //auto test = teste.shortest_path("teste@upf.br", "abc@upf.br");
    //if(test.flag) std::cout << test.errmsg << std::endl;
    //teste.list_network();
    //teste.remove("teste@upf.br");
    teste.show_menu();
    teste.debug("dot");
    return 0;
}
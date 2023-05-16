/*
    Social media control class implemented with inheritance to control
    the Network class flow like a "front-end" to use in a console based aplication

    Header file

    Guilherme Martinelli Taglietti - 192370
*/

#ifndef CONTROL_H
#define CONTROL_H

#include "network.h"
#include "network.cpp"
#include <string>

namespace network{

class SocialMedia : public Network{
public:
    void init();
    void show_menu();
    int get_instruction();
    void load_instructions(const std::string &s);
};

}

#endif
/*
    Social media control class implemented with inheritance to control
    the Network class flow like a "front-end" to use in a console based aplication

    Header file

    Guilherme Martinelli Taglietti - 192370
    José Paulo R. Pereira - 192445
    Lucas Friedrich - 168238
*/

#ifndef SOCIALMEDIA_H
#define SOCIALMEDIA_H

#include "network.h"
#include "network.cpp"
#include "datacontrol.h"
#include <string>

namespace socialmedia{

class SocialMedia : public datacontrol::DataControl{
private:
    bool is_number(const std::string& s);
    int load_instruction(const std::string &s);
    void show_menu();
    std::string get_instruction();

public:
    SocialMedia();
    virtual ~SocialMedia();
    void init();
};

}

#endif
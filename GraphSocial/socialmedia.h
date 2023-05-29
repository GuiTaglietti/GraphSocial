/**
 * @author Guilherme Martinelli Taglietti
 * @headerfile socialmedia.h (header file)
 * 
 * SocialMedia class interface/structure
 * @extends @class Network
 * Include guard
 * 
*/

#ifndef SOCIALMEDIA_H
#define SOCIALMEDIA_H

#include "network.h"
#include <string>

namespace socialmedia{

class SocialMedia : public network::Network{
public:
    SocialMedia();
    virtual ~SocialMedia();
    void init(socialmedia::SocialMedia &sm);

private:
    bool is_number(const std::string& s);
    void show_menu();
    int get_instruction();
    friend std::ostream& operator<<(std::ostream &os, SocialMedia &sm);
};

}

#endif
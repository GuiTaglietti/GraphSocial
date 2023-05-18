/*
    Database flow control using database class as member

    Header file

    Guilherme M. Taglietti - 192370
    José Paulo R. Pereira - 192445
    Lucas Friedrich - 168238
*/


#ifndef DATACONTROL_H
#define DATACONTROL_H

#include "database.h"

namespace datacontrol{

class DataControl : public network::Network{
private:
    database::Database data;

public:
    DataControl();
    virtual ~DataControl();
};

} // namespace network

#endif
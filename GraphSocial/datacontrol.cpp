/*
    Database flow control using database class as member

    .cpp file

    Guilherme M. Taglietti - 192370
    José Paulo R. Pereira - 192445
    Lucas Friedrich - 168238
*/

#include "datacontrol.h"

namespace datacontrol{

    datacontrol::DataControl::DataControl(){
        nodes = data.load_users();
    }

    datacontrol::DataControl::~DataControl(){
        data.save_users(nodes);
    }

} // namespace datacontrol
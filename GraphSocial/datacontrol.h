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
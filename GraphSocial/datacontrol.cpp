#include "datacontrol.h"

namespace datacontrol{

    datacontrol::DataControl::DataControl(){
        nodes = data.load_users();
    }

    datacontrol::DataControl::~DataControl(){
        data.save_users(nodes);
    }

} // namespace datacontrol
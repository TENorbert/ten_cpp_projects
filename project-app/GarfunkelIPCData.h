#ifndef AQUAGATOR_IPC_DATA_H
#define AQUAGATOR_IPC_DATA_H

#include <bitset>

#include "GarfunkelEnums.h"
#include "ecolab.h"

namespace Garfunkel
{
    class GarfunkelIPCData
    {
    public:
        GarfunkelIPCData(const GarfunkelIPCData &  objectToCopy);
        ~GarfunkelIPCData();
        
        static GarfunkelIPCData&    Instance();
        
    private:
        GarfunkelIPCData();
    };
};

#endif

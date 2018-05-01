#include "GarfunkelIPCData.h"

Garfunkel::GarfunkelIPCData::GarfunkelIPCData()
{
    //_cellRunState = eCellIdle;
}

Garfunkel::GarfunkelIPCData::GarfunkelIPCData(const GarfunkelIPCData &  objectToCopy)
{
}

Garfunkel::GarfunkelIPCData::~GarfunkelIPCData()
{
}

Garfunkel::GarfunkelIPCData&    Garfunkel::GarfunkelIPCData::Instance()
{
    static GarfunkelIPCData singleton;
    return singleton;
}

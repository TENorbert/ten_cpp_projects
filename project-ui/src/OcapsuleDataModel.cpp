
#include "OcapsuleDataModel.h"
//
//%% OcapsuleDataModel Instance
//
OcapsuleDataModel&
OcapsuleDataModel::Instance()
{
    static OcapsuleDataModel singleton;
    return singleton;
}
//
//%% GetPointer to Ocapsule Instance: getInstancePtr
//
QPointer<OcapsuleDataModel>
OcapsuleDataModel::getInstancePtr()
{
    OcapsuleDataModel& instance = Instance();
    return &instance;
}


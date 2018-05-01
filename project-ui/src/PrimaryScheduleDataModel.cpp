/*Define What and Install of the PrimaryScheduleDataModel is   */

#include "PrimaryScheduleDataModel.h"

//%====================================================================================
//%  Instance
//%====================================================================================
PrimaryScheduleDataModel&
PrimaryScheduleDataModel::Instance()
{
    static PrimaryScheduleDataModel singleton;
    return singleton;
}
//%====================================================================================
//%  Pointer to Instance: getInstancePtr
//%====================================================================================
QPointer<PrimaryScheduleDataModel>
PrimaryScheduleDataModel::getInstancePtr()
{
    PrimaryScheduleDataModel& instance = Instance();
    return &instance;
}


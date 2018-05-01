#include <QDebug> //% Qt Module for Debugging
#include "OcapsuleData.h"

//% Default Constructor of Ocapsule Object
OcapsuleData::OcapsuleData ()
{
    _ocapsuleId  = 0; 
    _isOcapsulePresent = true; // Ocapsule pressent
    _hasDetergent      = true; // Ocapsules non-empty
    _detergentName     = ""; 
    _valveSwitchState = 0; //Close = 0, Open = 1
    _lidState         = 0; //Close = 0, Open = 1
    _ledStatus        = 0; // Off = 0, On = 1

    _oType            = -1; // Undefined Type
    
    _conductivity     = 0.0; 
    _temp			  = 0.0; 
    _pressure		  = 0.0; 
    _detergentLevel   = 0.0;
    
    _valveOpenTime	  = 0;
}

//% Definition of Setters
//
void OcapsuleData::setOcapsuleId ( int &id )
{
   _ocapsuleId  = id;
}

void OcapsuleData::setIsOcapsulePresent ( bool b )
{
    _isCapsulePressent = b;
}

void OcapsuleData::setHasDetergent ( bool b)
{
    _hasDetergent = b;
}

void OcapsuleData::setDetergentName ( Qstring &name )
{
   _detergentName = name.toAscii();
}

void OcapsuleData::setOcapsuleValveSwitchState ( State &s )
{
    _valveSwitchState = s;
}

void OcapsuleData::setOcapsuleLidState ( State &s )
{
    _lidState = s;
}

void OcapsuleData::setOcapsuleLEDStatus ( LedStatus &ls )
{
    _ledStatus = ls;
}

void OcapsuleData::setOcapsuleType ( OcapsuleType &t )
{
    _oType = t;
}

void OcapsuleData::setConductivity ( double &c )
{
    _conductivity = c;
}

void OcapsuleData::setTemperature ( double &temp )
{
    _temp = temp;
}

void OcapsuleData::setPressure ( double &p )
{
    _pressure = p;
}

void OcapsuleData::setDetergentLevel ( double &l )
{
    _detergentLevel = l;
}

void OcapsuleData::setValveOpenTime ( int &t )
{
    _valveOpenTime = t;
}

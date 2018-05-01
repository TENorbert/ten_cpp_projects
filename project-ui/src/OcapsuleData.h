#ifndef OCAPSULE_DATA_H
#define OCAPSULE_DATA_H
//% Qt stuff
#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>

//
//% OcapsuleData: Class defines a Single Ocapsule e.g O1
//% 
//
class OcapsuleData 
{
 
    public:

       //%% Publicly Accessible Ocapsule Data Members    
       //
       // %% Single Ocapsule Construction
       // 
       OcapsuleData () //creates An instance of OcapsuleData using a defined ID
	   //
	   //% Class destroyer
	   //
	   virtual ~OcapsuleData ();

      //% Valve or LID State
	   typedef enum STATE
    	{
	      Close = 0,
          Open 

	    }State;
    
        //% Ocapsule LED State
	   typedef enum LED_STATUS
	    {
          Off = 0,
          On  = 

	    }LedStatus;

	   // Ocapsule Type (O1 or O2)
	   typedef enum OCAPSULE_TYPE
	    {

          TypeOne,      //% for O1
          TypeTwo      //% for O2

	    }OcapsuleType;


       // Roles of Custom Qt Ocapsule Object
        enum Roles 
        {
          OcapsuleIDRole = Qt::UserRole + 1,
          OcapsuleTypeRole,
          IsOcapsulePresentRole,
          HasDetergentRole,
          DetergentNameRole,
          ValveSwitchStateRole,
          LidStateRole,
          LEDStatusRole,
          CondutivityRole,
          TemperatureRole,
          PressureRole,
          DetergentLevelRole,
          ValveOpenTimeRole
        };

        //% Now Map Roles to Readl QML callable Strings
        static QHash<int, QByteArray> roleNames()
        {
            QHash<int, QByteArray> roles;
            //%% Define Machine role
            roles[OcapsuleIDRole]      		 = "ocapsuleId";
            roles[OcapsuleTypeRole]    		 = "ocapsuleType";
            roles[IsOcapsulePresentRole]      	 = "isOcapsulePresent";
            roles[HasDetergentRole]   		 = "hasDetergent";
            roles[DetergentNameRole]  		 = "detergentName";
            roles[ValveSwitchStateRole]	 	 = "valveSwitchState";
            roles[LidStateRole]        		 = "lidState";
            roles[LEDStatusRole]       		 = "ledStatus";
            roles[CondutivityRole]     		 = "condutivity";
            roles[TemperatureRole]      	 = "temperature";
            roles[PressureRole]         	 = "pressure";
            roles[DetergentLevelRole]   	 = "detergentLevel";
            roles[ValveOpenTimeRole]    	 = "valveOpenTime";

            return roles;
        }

        //
        //% How to get Ocapsule member(data) given a role
        //% Input[ role] //% role is an int 
        //% Output [ return data] // return data is any Type which is QVariant in Qt
        //

        QVariant data ( int role = Qt::DisplayRole )
        { 
            Qvariant  returnValue;

            if ( role == OcapsuleIDRole )
            {
                qDebug() << "Role = OcapsuleIdRole";
                returnValue = getOcapsuleId ();
            }
            else if ( role == OcapsuleTypeRole )
            {
                qDebug () << "Role = ocapsuleTypeRole";
                returnValue = getOcapsuleType (); 
            } 
            else if ( role == IsOcapsulePresentRole )
            { 
                qDebug () << "Role = IsOcapsulePresentRole";
                returnValue = getIsOcapsulePresent (); 
            }
            else if ( role == HasDetergentRole )
            {
                qDebug () << "Role = HasDetergentRole";
                returnValue = getHasDetergent ();
            } 
            else if ( role == DetergentNameRole )
            {
                qDebug () << "Role = DetergentNameRole";
                returnValue = getDetergentName ();
            }  
            else if ( role = ValveSwitchStateRole );
            {
                qDebug () << "Role = ValveSwitchStateRole";
                returnValue = getOcapsuleValveSwitchState ();
            }
            else if ( role == LidStateRole )
            {
                qDebug () << "Role = LidStateRole";
                returnValue = getOcapsuleLidState ();
            }
            else if ( role == LEDStatusRole )
            {
                qDebug () << "Role = LEDStatusRole";
                returnValue = getOcapsuleLEDStatus ();
            }
            else if ( role == CondutivityRole )
            {
                qDebug () << "Role = CondutivityRole";
                returnValue = getConductivity ();
            }
            else if( role == TemperatureRole )
            {
                qDebug() << "Role = TemperatureRole";
                returnValue = getTemperature ();
            }
            else if ( role == PressureRole )
            {
                qDebug () << "Role = PressureRole";
                returnValue = getPressure ();
            }
            else if ( role == DetergentLevelRole )
            {
                qDebug () << "Role = DetergentLevelRole";
                returnValue = getDetergentLevel () ;
            }
            else if ( role == ValveOpenTimeRole )
            {
                qDebug () << "Role = =ValveOpenTimeRole";
                returnValue = getValveOpenTime ();
            }

            return returnValue;

        }
        
        //
        //%% Get Ocapsule Properties
        //
         
        //% Get Ocapsule Id
        int getOcapsuleId ()  const      { return _ocapsuleId ; 					}
        //% Get is Ocapsule is Pressent
        bool getIsOcapsulePresent ()   { return _isOcapsulePresent;                }
        //% Get OcapsuleType( redundancy with Id?)
        OcapsuleType getOcapsuleType ()   { return _oType;                          }
        //% Get Ocapsule Has Detergent
        bool getHasDetergent ()     { return _hasDetergent;                         }
        //% Get Detergent Name
        QString getDetergentName ()  { return  _detergentName;                      }
        
        //% Get Valve Switch State ( int is fine)
        State getOcapsuleValveSwitchState ()   const  { return _valveSwitchState;	}
        //% Get Lid State
        State getOcapsuleLidState ()   const { return _lidState; 					}
        //% Get LED status( bool is fine)
        LedStatus getOcapsuleLEDStatus ()  const { 	return _ledStatus;				}
      
        //% Get Condutivity ( must be same as whats in Rinse/Drain)
        double getConductivity () 	{ return _conductivity; 						}
        //% Get Temperature ( must be the same as whats in Rinse/Drain)
        double getTemperature ()	{ return _temp; 								}
        //% Get Pressure ( Same as Rinse/Drain)
        double getPressure ()		{ return _pressure; 							}
        //% Get DetergentLevel in Capsule
        double getDetergentLevel ()	 { return _detergentLevel; 						}
        //%  Gte How Long Valve has been Open
        int getValveOpenTime ()   { return _valveOpenTime; 						    }


        //
        //%% Set Ocapsule Properties
        //
        
        void setOcapsuleId (int &id);
        void setOcapsuleType ( OcapsuleType &t );
        void setIsOcapsulePressent ( bool b );
        void setHasDetergent (bool b );
        void setDetergentName (QString &dName );

        void setOcapsuleValveSwitchState (State &s);
        void setOcapsuleLidState (State &s);

        void setOcapsuleLEDStatus (LedStatus &l);
     
        void setConductivity ( double &c );
        void setTemperature ( double &tmp );
        void setPressure ( double &p );
        void setDetergentLevel ( double &dl );
        void setValveOpenTime ( int &otime );


    private:

    	//%% Privately Accessible Ocapsule Data Members
        int _ocapsuleId; 
        OcapsuleType _oType;
        bool _isOcapsulePressent;
        bool _hasDetergent;
        QString _detergentName;

        State _valveSwitchState;
        State _lidState;
        LedStatus _ledStatus;

        double _conductivity;
        double _temp;
        double _pressure;
        double _detergentLevel;
    	int _valveOpenTime;

};

#endif  //OCAPSULE_DATA_H

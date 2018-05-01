#ifndef PASSWORD_CONTEXT_H
#define PASSWORD_CONTEXT_H

#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>

#include "GarfunkelDB.h"
#include "GarfunkelSystemContext.h" //use WHen we have flat file
#include "GarfunkelSystemData.h"

//#include "PasswordManager.h" // generates and validates passwords!!

//% System C/C++ classes
#include <stdio.h>
#include <string.h>
#include <math.h>


//%     PasswordContext 
//%
//%    The  PasswordContext class is a context interface class for exporting variables and
//%    methods to QML that are typically used for operations that require a Password Entry.
//%    
//%
class  PasswordContext : public QObject
{
    Q_OBJECT

    //% Determins if either TM or Customer want ot loggin in User Password Request Menu Items (true = TMpassword)
    Q_PROPERTY (bool tmOrCustomerPasswd    READ getTMOrCustomerPasswd    WRITE setTMOrCustomerPasswd    NOTIFY tmOrCustomerPasswdChanged )
    //%  Daily TM Password or Random Password?
    Q_PROPERTY (bool dTMorRandomTMpwd    READ getDTMorRandomTMpwd    WRITE setDTMorRandomTMpwd    NOTIFY dTMorRandomTMpwdChanged )
    //% daily TM password     
    Q_PROPERTY (QString dTMpasswd    READ  getDTMpasswd    WRITE setDTMpasswd    NOTIFY dTMpasswdChanged )
    //% random TM password  fixed and stored in Envision ( so this does not depend on the Serial Number & date ?! yes!!)
    Q_PROPERTY (QString randomTMpasswd    READ  getRandomTMpasswd    WRITE setRandomTMpasswd    NOTIFY randomTMpasswdChanged)
    //% Check that UI is loggnedIn
    //Q_PROPERTY(bool    uiLoggedIn    READ  getUILoggedIn     WRITE setUILoggedIn     NOTIFY  uiLoggedInChanged )
    //%Requests Password validation( triggers local password generation/Database password search)
    Q_PROPERTY (bool  pwdValidationRequest     READ  getPwdValidationRequest    WRITE  setPwdValidationRequest   NOTIFY pwdValidationRequestChanged )
    //% customer password!!
    Q_PROPERTY (QString customerPasswd    READ  getCustomerPasswd    WRITE setDBCustomerPasswd     NOTIFY customerPasswdChanged)
    //% validates user login
    //Q_PROPERTY(int     loginStatus       READ  getLoginStatus        WRITE checkLoginStatus(int)    NOTIFY loginStatusChanged )
    Q_PROPERTY (QString   customerInputPasswd    READ getCustomerInputPasswd    WRITE setCustomerInputPasswd    NOTIFY customerInputPasswdChanged )
    //% signal to indicate password is valid
    Q_PROPERTY (bool pwdValid    READ  getPwdValid    WRITE setPwdValid    NOTIFY  pwdValidChanged )
    //% login status once password is valid or not!!
    Q_PROPERTY (bool  loginStatus    READ  getLoginStatus    WRITE setLoginStatus    NOTIFY loginStatusChanged )

   
public:
    //%
    //%    Constructor
    //%
    PasswordContext (GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, QDeclarativeContext *context, QObject *parent = 0);

    //%
    //%    Destructor
    //% 
     virtual ~PasswordContext ();

    //
    //    Getters - Please note:  
    //%                           I am trying not to inline these to reduce bloat.
    //                            Also, getter methods are for getting data from this class,
    //                            **NOT**  for getting table data from the DB. Calling that operation
    //                            a "get" is obfuscation.  So its a slot called fetchPasswdTableCB() instead.
    //                            As such, its a callback, (the database trigger calls it back) and should have CB in its name.
    //



    //% 
    //%  PUBLIC GETTERS
    //%

    //% get TMorCustomer Password
    bool getTMOrCustomerPasswd ()  const        {  return        _tmOrCustomerPasswd;        }
    //% get daily or Radom TM password
    bool getDTMorRandomTMpwd ()  const            {  return          _dTMorRandomTMpwd;          }
    //% get daily TM Password
    QString getDTMpasswd ()    const            {  return          _dTMpasswd;               }
    //% get Random TM passwd 
    QString getRandomTMpasswd()  const          {  return          _randomTMpasswd;          }
    //% get TM password generation/validation request
    bool getPwdValidationRequest  ()  const     {  return         _pwdValidationRequest;     }
    //% get whether password was valid or not
    bool getPwdValid ()  const                  {  return         _pwdValid;                 }
    
    //% get Login status
    bool getLoginStatus()   const              {             return _loginStatus;            }
    //get customer password from this class
    QString getCustomerPasswd() const           {             return _customerPasswd;        }
    //% get Customer inoput password
    QString getCustomerInputPasswd ()  const    {    return  _customerInputPasswd;           }


    //%
    //%         PUBLIC SETTERS.  
    //%
    void setTMOrCustomerPasswd (const bool &tmOrCmerPwd);
    void setDTMorRandomTMpwd (const bool &dTMorRTMpwd);
    void setDTMpasswd ( const QString & dtmpwd);
    void setRandomTMpasswd ( const QString & rtmpwd);
    void setPwdValidationRequest ( const bool &pwdVrequest);
    void setPwdValid ( const bool & validPwd);
    void setLoginStatus ( const bool &lstatus);

    void setDBCustomerPasswd(const QString &customerdbPswd );
    void setCustomerInputPasswd ( const QString &customerInputPswd );



    //%
    //% Usefull Functions
    //%
    //bool getUILoggedIn();

    //% Read UI Input Password
 Q_INVOKABLE  void uiInputPassword (const QString &uiInputpasswd );

    //% use this functions to emit signals!!

    //% Check Login Status and Tell UI
    void checkLoginStatus ();

    //% Match Passwords return true if matched else false
    bool matchPasswords (const QString &readstring, const QString &givenstring);

    //void fetchCustomerPasswdFromDB();

    //% Daily TM Password Validation
    ///bool validateDTMPasswd (const QString &generatedDTMPwd, const QString &uiInputDTMPwd);

    //% Random TM Password Validation
    ///bool validateRTMPasswd (const QString &generatedRTMPwd, const QString &uiInputRTMPwd);

    //%Customer Password Validation
    bool validateCustomerPasswd(const QString &customerDBpasswd, const QString &customerUIpasswd);

    //% get Controller's Serial # from Database
    //QString   fetchControllerSerial (); // Get Controller Serial Number

    //% Get current Date of Today from Interned Updated date service
    //QString   fetchDateOftheDay ();  //% Get the current Month, Day, year ( synchronized with internet)


signals:
    //% Login Sinal emitted only after Password entered has been validated
    void loginStatusChanged (bool lgin);
    //% signal of Daily or Random TM pwd ( yes = daily TM password) 
    void dTMorRandomTMpwdChanged ();
    //% signal if password is valid
    void pwdValidChanged (); 
    //% signal for tm or customer password validation
    void tmOrCustomerPasswdChanged ();
    //%  signal for Daily TM password Changed
    void dTMpasswdChanged (); 
    //% signal fro Random TM passwd chnaged
    void randomTMpasswdChanged (); 
    //% signal that customer password changed
    void customerPasswdChanged ();
    //% customer input password change signal
    void customerInputPasswdChanged ();
    //%  Genral Password generation/validation Request signal
    void pwdValidationRequestChanged (); 
    //%

public slots:
   //% slots to Recived Signals from Password manager Class

   //%  Callback to fetch customer passord from DB
    void fetchPasswdTableCB();  
    //% Handles Daily TM Password Generation request  Signal
    void pwdValidationRequestChangedHandler ();
    
private:
    GarfunkelDB*        _gDB;               //% Pointer to the database instances //% for updating Login status
    GarfunkelSystemContext*  _gsystemContext; //% Pointer to GarfunkelSystemContext instances //% for updating system context

    QDeclarativeContext* _Context;          //%Pointer to the declarative context.
    //%
    //%     simple variables
    //% 
    bool _pwdValidationRequest;
    bool _dTMorRandomTMpwd;  
    bool _pwdValid; 
    bool _tmOrCustomerPasswd; 
    QString _dTMpasswd;
    QString _randomTMpasswd;
    //QString _contact;
    QString _customerPasswd;
    QString _customerInputPasswd; 
    bool _loginStatus;

    //% validate TM pasword by enVision
    bool _enVisionTMpwdValid;  //if Random TM password generated and sent to enVision can be validated or not!! if not use DTMpasswd
  
    //%
    //%      Private Setters.  
    //%
    void _setCustomerPasswd(const QString& customerPswd);

private slots:
    // Called during system setup
    //% Receives/creates Random TM Password and sent to envision
    ///void _generatedRandomTMPassword (QString & genDtmpwd); 
    //% Receives/creates Random Default Customer Password generated and stores encripted password in DB
    ////void _generatedRandomCustomerPassword (QString &genRtmpwd); 

};

#endif // PASSWORD_CONTEXT_H

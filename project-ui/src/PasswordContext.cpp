#include <QDebug>
#include <QString>  // to grap string to conversions!!
#include "PasswordContext.h"


//Construtor Implementation
 PasswordContext::PasswordContext(GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, QDeclarativeContext *context,  QObject *parent) :
     QObject(parent),
    _gDB(gdb),
    _gsystemContext(gsystemcontext),
    _Context(context)
  
{
     //Initialize  params!!
    _customerInputPasswd   = ""; // Customer Input Password set to empty String
    _pwdValidationRequest = false;
    _dTMorRandomTMpwd     = false;  
    _pwdValid             = false; 
    _tmOrCustomerPasswd   = false; 
    _dTMpasswd            = "";
    _randomTMpasswd       = "";
    _enVisionTMpwdValid   = false; 
    _loginStatus          = false; 

    //% make connection to get cusotmer password from database
    connect(_gDB, SIGNAL(passwordUpdated()), this, SLOT(fetchPasswdTableCB()));
    //% Make connections with Request for local DailyTM password Generation & validation
    //% would like to make this connection with PasswordManager in future!!!
    connect(this, SIGNAL(pwdValidationRequestChanged ()), this, SLOT(pwdValidationRequestChangedHandler ())); //,Qt::UniqueConnection
    //
    // Fetch database data the first time
    //
    fetchPasswdTableCB();
}


//% Desrtuctor Implementation 
 PasswordContext::~PasswordContext () 
{
    //Nothing to do
}

//%
//%  Usefull Functions
//%
Q_INVOKABLE void PasswordContext::uiInputPassword ( const QString &uiInputpasswd )
{
  // Can add the case to differentiate between Customer or TM Password here!!
   qDebug() << "UI Entered password = : \t" << uiInputpasswd; 

   setLoginStatus(false); // set user loginStatus to false temporarily!!
   qDebug () << "_LoginStatus: = \t" << _loginStatus;
   setCustomerInputPasswd (uiInputpasswd);

}
//%
//%   GETTING FUNCTIONS
//%
//%
/*
Q_INVOKABLE bool PasswordContext::getLoginStatus()
{
    return(true);
}
*/

//%
//%   SETTING FUNCTIONS
//%

//%
//%   setTMOrCustomerPasswd (const bool &tmOrCmerPwd)
//%
void PasswordContext::setTMOrCustomerPasswd (const bool &tmOrCmerPwd)
{
    if ( !(tmOrCmerPwd == _tmOrCustomerPasswd))
    {
        _tmOrCustomerPasswd = tmOrCmerPwd;
        qDebug () << "_tmOrCustomerPasswd = " << _tmOrCustomerPasswd; 
        emit tmOrCustomerPasswdChanged ();    
    }

}

//%
//% setDTMorRandomTMpwd (const bool &dTMorRTMpwd)
//%
void PasswordContext::setDTMorRandomTMpwd (const bool &dTMorRTMpwd)
{
   if (!(dTMorRTMpwd == _dTMorRandomTMpwd))
   {
      _dTMorRandomTMpwd = dTMorRTMpwd; 
      qDebug () << "_dTMorRandomTMpwd is = " << _dTMorRandomTMpwd; 
      emit dTMorRandomTMpwdChanged ();
   }

}

//%
//%   setDTMpasswd ( const QString & dtmpwd)
//%
void PasswordContext::setDTMpasswd ( const QString & dtmpwd)
{

   if (!(dtmpwd == _dTMpasswd ))
   {
      _dTMpasswd = dtmpwd; 
      qDebug () << "_dTMpasswd is = " << _dTMpasswd; 
      emit dTMpasswdChanged ();
   }

}


//%
//%   setRandomTMpasswd ( const QString & rtmpwd)
//%
void PasswordContext::setRandomTMpasswd ( const QString & rtmpwd)
{

   if (!(rtmpwd == _randomTMpasswd ))
   {
      _randomTMpasswd = rtmpwd; 
      qDebug () << "_randomTMpasswd is = " << _randomTMpasswd; 
      emit randomTMpasswdChanged ();
   }

}

//%
//%  setPwdValidationRequest ( const bool &pwdVrequest);
//%
//%  Once Request is set to True from UI, pwdValidationRequestChangedHandler()
//%                                       is called to Handle Password Gen and validation!!
//%
void PasswordContext::setPwdValidationRequest ( const bool &pwdVrequest)
{
   if (!(pwdVrequest == _pwdValidationRequest ))
   {
        _pwdValidationRequest = pwdVrequest; 
        qDebug () << "_pwdValidationRequest is = " << _pwdValidationRequest; 
        emit (pwdValidationRequestChanged () ); 
   }

}

//%
//%  setPwdValid ( const bool & validPwd)
//%  
//%  emits signal once validation is completed
//%
void PasswordContext::setPwdValid ( const bool & validPwd)
{
   if (!(validPwd == _pwdValid))
   {
      _pwdValid = validPwd; 
      qDebug() << "_pwdValid is = " << _pwdValid;
      emit pwdValidChanged ();   

   }

}

//%
//%  setLoginStatus ( const bool %lstatus)
//%  Sets the Login Status once password 
//%  validated
//%
void PasswordContext::setLoginStatus ( const bool &lstatus)
{
    if (!(lstatus == _loginStatus))
    {
        _loginStatus = lstatus; 
        qDebug () << "_loginStatus Changed to " << _loginStatus;
        emit(loginStatusChanged (_loginStatus));
    }
}

//%
//%  setCustomerInputPasswd ( const QString& customerInputPswd )
//%
//% Public Set Custormer Password From UI
void  PasswordContext::setCustomerInputPasswd ( const QString& customerInputPswd )
{
    if( !(customerInputPswd == _customerInputPasswd))
    {
        _customerInputPasswd = customerInputPswd;
        //qDebug() << "_customerInputPasswd ="<< _customerInputPasswd ;
        emit customerInputPasswdChanged ();
    }

}



//%
//%   Private Setter
//%  _setCustomerPasswd(const QString& customerPswd)
//%
//% Private Set Customer Password
void PasswordContext::_setCustomerPasswd(const QString& customerPswd)
{
    if( !(customerPswd == _customerPasswd))
    {
        _customerPasswd = customerPswd;
        //qDebug() << "_customerPasswd="<<_customerPasswd;
        emit customerPasswdChanged();
    }
}

//%
//% Public Setter 
//%  setDBCustomerPasswd(const QString& customerdbPswd)
//% 
//% Public Setting Customer Password in DB
void PasswordContext::setDBCustomerPasswd(const QString& customerdbPswd)
{
 //   qDebug() << "setting setDBCustomerPasswd = " << pcustomerdbPswd;
    _setCustomerPasswd(customerdbPswd);
     const QString executeString = "SetCustomerPassword(\'" + customerdbPswd + "\',\'ui\')";
    _gDB->executeStoredFunction(executeString);
}


//%
//%  SLOTS
//%

//%
//%
//%
//% Handles Daily TM Password Generation request  Signal
void PasswordContext::pwdValidationRequestChangedHandler ()
{
     // Call Validation of Password once request is made
     if (true == _pwdValidationRequest )
     {
        qDebug () <<"User Logging in ...\n"; 
        qDebug () << "_LoginStatus: = \t" << _loginStatus;

        checkLoginStatus();

    
     }else
     {
        //Do something if user has not asked for Password Validation
        qDebug () <<"User IS ALREADY LOGGED IN...\n"; 
        //setLoginStatus(false);
     }

}
    


//% Fetch DB for Customer Passwords Stored !!
void PasswordContext::fetchPasswdTableCB()
{
    if (!_gDB->isConnected())
    {
        qDebug() << "fetchPasswdTableCB NOT CONNECTED";
        _gDB->connect();
    }
    if(_gDB->isConnected())
    {
        qDebug() << "fetchPasswdTableCB CONNECTED";
        ecolab::DB::DataSet dataSet;
        dataSet = _gDB->executeStoredFunction(QString("GetPasswords()"));
        //if (dataSet.GetNumberOfRows() == 1) 
        if (dataSet.GetNumberOfRows() > 0) 
        {
            QString tmpString;
            ecolab::DB::DataRow rowData(dataSet.GetFirstRow());
            QVariant tmp;
            disconnect(_gDB, SIGNAL(passwordUpdated()), this, SLOT(fetchPasswdTableCB()));

            tmp = _gDB->value(rowData, "CustomerPassword", GarfunkelDB::String);
            tmpString  = tmp.toString();
            _setCustomerPasswd(tmpString);

            connect(_gDB, SIGNAL(passwordUpdated()), this, SLOT(fetchPasswdTableCB()));
        }
    }
     else //read from flat files
        {   /*
            QString tmPwd, secTMPwd, cusPwd;
            _gsystemContext->getPasswordProperties(tmPwd, secTMPwd, cusPwd);
            _setTMPasswd(tmPwd);
            _setSecretTMPasswd(secTMPwd);
            _setCustomerPasswd(secTMPwd);
            */
            printf("No Flat files reading ability yet!!");
        }


}


//%
//% UseFull Functions
//%


//%
//%     matchPasswords (const QString &readstring, const QString &givenstring)
//%     
//%     Matches user input password to database generated or stored in DB
//%
bool PasswordContext::matchPasswords (const QString &readstring, const QString &givenstring)
{
    bool matched = false; 
    ulong rpwd = 0; 
    ulong gpwd = 0;
    //check that strings aren't empty first
    if( !readstring.isEmpty ())
    {
         rpwd = readstring.toULong(); 

    }else
    {
        qDebug() << "Password read is Empty " << readstring ;  
    }

    if (!givenstring.isEmpty() )
    {
         gpwd = givenstring.toULong();
    }else
    {
        qDebug() << "Password Given is Empty " << givenstring ;  
    }
     
    
    // now check that the Unsigned Longs are equal!!
    if ( rpwd == gpwd )
    {
        qDebug () << "Valid Entered Password!";
        matched = true;
    }else
    {
        qDebug () <<"InValid Entered Password!!";
        matched = false; 
    }

   return (matched);
}



//% Check Password And Validate
bool  PasswordContext::validateCustomerPasswd(const QString &customerDBpasswd, const QString &customerUIpasswd)
{
    bool valid = false; 
    //% Need a better fuction to Match Character by Character
    //int mismatch = QString::compare(customerDBpasswd,customerUIpasswd);

    bool thesame = matchPasswords (customerDBpasswd, customerUIpasswd );
    if(thesame)
    {
        valid = true; 
    }
    else{

          valid = false;
    }

  return valid; 
}
//%
//% checkLoginStatus()
//%  Checks if user is still logged in and validates login!!
//%
void  PasswordContext::checkLoginStatus ()
{
       _loginStatus = false;
       _pwdValid  = false;
       _pwdValidationRequest = false; 

     //First check if password is user or DailyTM or TM using
     // parameters: _tmOrCustomerPasswd and _dTMorRandomTMpwd
     // and validate each case accordingly
     bool successful = validateCustomerPasswd (_customerPasswd, _customerInputPasswd);
     //const QString reset = ""; 

     if(successful)
     {
        setPwdValid(true);
        setLoginStatus(true);
        setPwdValidationRequest(false); // we've already validated ur entered password!!
        setCustomerInputPasswd (""); // Reset Password for next entry
     }
     else
     {
        
        _pwdValidationRequest = false;
        setPwdValid(false);
        setLoginStatus(false);
        // Set user Input password to empty strings
        setCustomerInputPasswd ("");
     }


}





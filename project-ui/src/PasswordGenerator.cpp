
/* Class PasswordGenerator Definition, copyright (c) ECOLAB 2016  */

#include <stdio.h>
#include <stdlib.h>     //for strtoul //
#include <math.h>
#include <assert.h>
#include <time.h>



#include <iomanip>
#include <iostream>
#include <string>     // std::string, std::to_string
#include <sstream>

#include "PasswordGenerator.h"



//Usefull Namespace functions


//% serialNumberType (const std::string &sStr)
//% Check type of Serial Number by classifying serial number by their type
//%
//int PWGenerator::serialNumberType (char* sStr)
int PWGenerator::serialNumberType ( const std::string &sStr)
{
    //printf("Serial Number Entered is = %s", sStr); //if use pointers!
    printf("Entered Serial Number = %s\n", sStr.c_str() );
    int type = -99; 

    //if (strlen(sStr) == SLENGTH_A) //if use pointers!
    if (sStr.length() == SLENGTH_A)
    {
      type = 0;
    }
    //else if(strlen(sStr) == SLENGTH_B) //if use pointers!
    else if(sStr.length() == SLENGTH_B)
    {
      type = 1;

    }else
    {
      printf( "WARNING!! INVALID SERIAL NUMBER!!\n");
    }

    return type;
}


//%  convertStringToCharPtr(std::string &sstr,)
//%  Takes a given serial number as string Character ARRAY or Pointer
//%
char* PWGenerator::convertStringToCharPtr(const std::string &iString )
{
  char *strPtr = new char[128]; //% long string

  // % safer because I know how many characters I am coppying! No Over flows!!
  strncpy(strPtr, iString.c_str(), 127 );

  printf("Pointer Is Holding %s\n", strPtr);
  return strPtr; 

}



//%  convertStringToCharPtr(std::string &sstr, int &type )
//%  Takes a given serial number as string and its type and choses the correct MAX of size of Character ARRAY or Pointer
//%
//char* PWGenerator::convertStringToCharPtr(char* sstr, int &type )
char* PWGenerator::convertStringToCharPtrForType(const std::string &sstr, int &type )
{
    //printf("Serial Number Entered is = %s\n", sstr); //if use pointers!
     printf("std::string is = %s\n", sstr.c_str());
     printf(" Serial Number is of Type: %i\n", type );
     char *strPtr = new char[130]; 
     // % make a Character Pointer Out of String
     const int  MA = 11;
     char snCharA[MA];

     const  int MB = 13; 
     char snCharB[MB]; 

     const int MAX = 128;
     char tchar [MAX]; //% dates
    switch (type) {

         case sNTypeA :
           {
             memset(snCharA, '\0', MA);
             //std::string(sstr).copy(snCharA, MAX_A-1); //if use pointers!
             sstr.copy(snCharA, MA);

            // % safer because I know how many characters I am coppying! No Over flows!!
             strncpy(strPtr, snCharA, MA );

           }
          break;
          case  sNTypeB :
           {
             memset(snCharB, '\0', MB);
             //std::string(sstr).copy(snCharB, MAX_B-1); //if use pointers!
             sstr.copy(snCharB, MB );

             // % safer because I know how many characters I am coppying! No Over flows!!
             strncpy(strPtr, snCharB, MB);
             //strPtr = snCharB;

           }
           break; 
          case  2 :
           {
            //do any for random string
            memset(tchar, '\0', MAX);
            sstr.copy(tchar, MAX-1);

              strncpy(strPtr, tchar, MAX );
              //strPtr = tchar; 
           }
           break;
           
    }

     printf(" Pointer Is Holding %s\n", strPtr);

     return strPtr; 

} 

//%
//%   convertCharPtrToULong (char* chrPtr )
//%   Converts CharPtr to unsigned long
//%   By replacing the D & E with 4 & 5 characters
//%
ulong PWGenerator::convertCharPtrToUlong (const char* chrPtr )
{
    int length =  strlen(chrPtr) + 1;  

    char snNew [length+2];

    std::string mystring = ""; 

    
    // Remove any letter characters and only live digits
    char d = 'D';
    char e = 'E';
    std::ostringstream ssm; 
    
    int m;  
    for( m = 0; chrPtr[m] != '\0'; m++ )
     {
        //if (isalpha(chrPtr[m]))
        //     {
        //      ssm << 1; //Change D = E = 1
        //    }
        if (chrPtr[m] == d)  
        {
          ssm << 4;  //% change D=4
        }
        else
        if (chrPtr[m] == e)
        {
          ssm << 5;  //% change E=5
        }
        else{

          ssm << chrPtr[m];
        }

     }
     
     mystring = ssm.str(); 

     // % safer because I know how many characters I am coppying! No Over flows!!
     strncpy(snNew, mystring.c_str(), length + 2);  

     printf("New Serial Number is = %s \n", snNew);

     ulong llnumber = (ulong)strtoul(snNew, NULL, 0); 
     printf("Converting %s string pointer to %lu  ulong \n", chrPtr, llnumber);
     //return ( (ulong)strtoul(std::string(chrPtr).c_str(), NULL, 0) ); or 
     printf("Unsigned long Number is =  %lu \n", llnumber);

     return llnumber; 

}

//%
//% convertUlongToCharPtr (ulong & lnumber)
//% Convert ulong(must only point to digit literals, return 0 if not) to Character Pointer
//%  or simply  do the reverse of previous function
//%
char* PWGenerator::convertUlongToCharPtr (ulong &number )
  {
    std::ostringstream ss;
    ss << number;
    return ( PWGenerator::convertStringToCharPtr (ss.str()) );
  }

/*
char* PWGenerator::convertUlongToCharPtr (ulong &lnumber)
{
  printf("Converting %lu ulong to string pointer\n", lnumber);

  std::string mstring = ""; 
  //first convert to std::string
  mstring = std::to_string(lnumber);
  //then convert std::string to ulong 
  return (PWGenerator::convertStringToCharPtr (mstring) );
}
*/

//%  rotate
//%
//% Rotates Characters in a string
void PWGenerator::rotate(char* str)
{

  int  end = strlen( str ) - 1;
  int x;
  char  t;

  t = str[ 0 ];
  for( x = 1; x <= end; x++ )
  {
    str[ x - 1 ] = str[ x ];
  }
  str[ end ] = t;

}



//Class Definition

//% Naked Constructor
PWGenerator::PasswordGenerator::PasswordGenerator ()
{
   //% NULL Everything
   std::cout <<"Naked Unsigned Contructor!!" << std::endl;
  _serialNumber  = _day = _month = _year = _ipasswd = 0;
  std::cout <<"Initialize params to 0!!" << std::endl;
  _serialN = _sDay = _sMonth = _sYear = _sPswd = 0;   

 
} 


//% Constructor with Character Pointer parameters
PWGenerator::PasswordGenerator::PasswordGenerator (char* serialN, char* day, char* month, char* year, char* password) : _serialN(serialN), _sDay(day), _sMonth(month), _sYear(year), _sPswd(password)
{
  std::cout <<"Initialize params to 0!!" << std::endl;
  _serialN = _sDay = _sMonth = _sYear = _sPswd = 0;   
  std::cout <<"Character Pointer Constructor!!" << std::endl;
  _serialNumber  = _day = _month = _year = _ipasswd = 0;
}


//% Constructor with unsigned long Input parameters
PWGenerator::PasswordGenerator::PasswordGenerator (ulong sNumber, ulong day, ulong month, ulong year, ulong pswd) : _serialNumber(sNumber), _day(day), _month(month), _year(year), _ipasswd(pswd)
{ 
  std::cout <<"Unsigned long Contructor!!" << std::endl;
  _serialN = _sDay = _sMonth = _sYear = _sPswd = 0;   
}

PWGenerator::PasswordGenerator::~PasswordGenerator ()
{
  std::cout << "Destroying Object" << std::endl;
}




void PWGenerator::PasswordGenerator::printInstanceIntInfo (PasswordGenerator &pwdG)
{
  printf("Condor Serial Number = %lu \n", pwdG._serialNumber);
  printf("Day = %lu \n", pwdG._day);
  printf("Month = %lu \n", pwdG._month);
  printf("Month = %lu \n", pwdG._year);
  printf("Password = %lu \n", pwdG._ipasswd);
  /*
  std::cout << "Condor Serial Number = " <<  pwdG._serialNumber << std::endl;
  std::cout << "Day = \t" <<  pwdG._day << std::endl;
  std::cout << "Month = \t" <<  pwdG._month << std::endl;
  std::cout << "Month = \t" <<  pwdG._year << std::endl;
  std::cout << "Password = \t" <<  pwdG._ipasswd << std::endl;
  */
}


void PWGenerator::PasswordGenerator::printInstanceCharInfo ()
{
  printf("Condor Serial Number = %s \n", _serialN);
  printf("Day = %s \n", _sDay);
  printf("Month = %s \n", _sMonth);
  printf("Month = %s \n", _sYear);
  printf("Password = %s \n", _sPswd);
  /*
  std::cout << "Condor Serial Number = " <<  pwdG._serialNumber << std::endl;
  std::cout << "Day = \t" <<  pwdG._day << std::endl;
  std::cout << "Month = \t" <<  pwdG._month << std::endl;
  std::cout << "Month = \t" <<  pwdG._year << std::endl;
  std::cout << "Password = \t" <<  pwdG._sPswd << std::endl;
  */
}



//% generatedPassword 
//% Produces the generated password
//% Return the generated password
char* PWGenerator::PasswordGenerator::generatedPassword (std::string &tmInputSerialNumber)
{
  char genPwd[128];
  char tmpassword[130]; 
    

  int sntype = PWGenerator::serialNumberType(tmInputSerialNumber);
  char* serial_number = PWGenerator::convertStringToCharPtrForType (tmInputSerialNumber, sntype);

  bool serialNumberIsValid = _isSerialNumberValid (serial_number);

  if(serialNumberIsValid)
  {
      
      if( _passwordOfTheDay ( serial_number, genPwd ) == FAILED )
      {
        printf("Failed to generate the password\n");
      }
      else
      {
        printf("Today's Password: %s\n", genPwd );
      }
      
      strncpy(tmpassword,  genPwd, 128);

  }else
  {
    printf("You Entered an Invalid Serial Number!!\n");
  }
  

  return tmpassword; 
}


//********************************/
// PRIVATE FUNCTIONS
//********************************/

//% 
//% _isSerialNumberValid(char* snStr)
//%
//% checks if serial Number is valid before you even create a password object
//%
 bool PWGenerator::PasswordGenerator::_isSerialNumberValid (char* snStr)
 {
     bool validLength = false;
     bool isValid = false;

     printf("Serial Number Entered is = %s \n", snStr);
     printf("Serial Number Length is = %i \n", strlen(snStr) );
     if(std::string(snStr).length() == SLENGTH_A || std::string(snStr).length() == SLENGTH_B )
     {
        validLength = true;

     }else
     {
            validLength = false;
            printf("Entered Serial Number has an Unusual Length!!" );
      }
  
     // Now validate Serial Number properly!!
     if( validLength )
     {
       //check that the first and fifth characters are Letters and Not digits
        if ( isalpha(snStr[0]) && isalpha(snStr[5]) )
        {
           isValid = true;

        }else
        {
           isValid = false;
        }

     }else
     {
       printf("INVALID SERIAL NUMBER!!\n");
     }


     return isValid; 
 }

//%
//% _pswStraight
//%
//% re-adjust digits 
//%
int PWGenerator::PasswordGenerator::_pswStraight ( char * str, char digit )
{
  int x;
  int max_zero_cnt, cur_zero_cnt;
  int state = 0;  // initial state: look for zero

  max_zero_cnt = cur_zero_cnt = 0;
  for( x = 0; str[ x ] != '\0'; x++ )
  {
    switch( state )
    {
    case 0: // look for the target digit
      if( str[ x ] == digit )
      {
        cur_zero_cnt++;
        state = 1;
      }
      break;
    case 1: // look for non-target digit
    default:
      if( str[ x ] == digit )
      {
        cur_zero_cnt++;
      }
      else
      {
        state = 0;
        if( cur_zero_cnt > max_zero_cnt )
        {
          max_zero_cnt = cur_zero_cnt;
        }
        cur_zero_cnt = 0;
      }
      break;
    }
  }
  if( cur_zero_cnt > max_zero_cnt )
  {
    max_zero_cnt = cur_zero_cnt;
  }
  return( max_zero_cnt );

}



//%
//% _pswRepeatDigit
//%  Count Number of repeated digits
//%
int PWGenerator::PasswordGenerator::_pswRepeatDigit (char * str, char c )
{
  int x;
  int same_cnt = 0;

  for( x = 0; str[ x ] != '\0'; x++ )
  {
    if( str[ x ] == c )
    {
      same_cnt++;
    }
  }
  return( same_cnt );
}

//%
//%   _pswDisperseMonth
//%   
//%   
//%
ulong PWGenerator::PasswordGenerator::_pswDisperseMonth (ulong month)
{
  ulong m = ( ( (month*7) ^ (month * month) ) + 3) & 0x1F;
  return( m );
}

//%
//%   _pswDisperseDay
//%      
//%
ulong PWGenerator::PasswordGenerator::_pswDisperseDay ( ulong day )
{
  ulong d;

#if 1
  d = ((day & 7) << 3) | ((day & 0x1C) >> 3) | (day & 0xFFC0);
#else
  d = (day*41) ^ ((day+3)*(day+7));
  if( day & 1 )
  {
    d = (d & 0xFE) >> 1; 
  }
  else
  {
    d = (d & 0x7F) >> 0; 
  }
#endif
  return( d ); 

}

//%
//% _pswDisperseTime
//%
//%
ulong PWGenerator::PasswordGenerator::_pswDisperseTime ( ulong year, ulong month, ulong day )
{
  ulong d, m, t;

  ulong d_m[ 13 ] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if( year >= 2015 )
  {
    year -= 2014;
  }
  year &= 0xF;
  if( month > 12 || month == 0 )
  {
    month = 1;
  }
  if( day > d_m[ month ] )
  {
    day = 1;
  }
  d = _pswDisperseDay( day );
  m = _pswDisperseMonth( month );
  t = (d << 9) | (m << 2) | ((year & 0xC) << 5) | (year & 0x3);
  t ^= 0x81A4;

  return( t );
}

//%
//% _pswDisperseSerial
//%
//%
ulong PWGenerator::PasswordGenerator::_pswDisperseSerial ( ulong serial, ulong day )
{
  ulong s;

  day = ((day & 7) << 3) | ((day & 0x1C) >> 3) | (day & 0xFFC0);
  s = (serial + day) * 3;
  s &= 0xFFFF;
  s ^= 0xA180;
  s = ((s & 0x0F00) >> 4) | ((s & 0x00F0) << 4) | ((s & 0xF) << 12) | ((s & 0xF000) >> 12);
  return( s );

}
//%
//%   _pswFusion
//%
//%  combine all!
//%
void PWGenerator::PasswordGenerator::_pswFusion( ulong serial, ulong month, ulong day, ulong year, char * passwd )
{
  ulong tm, sn, fn;
  char  p_str[ 32 ];

  tm = _pswDisperseTime( year, month, day );
  sn = _pswDisperseSerial( serial+1, day );
  
  fn = tm * sn; // combining is multiplying
  sprintf( p_str, "%09lu", fn ); // copy digits 0-9
  if( strlen( p_str ) > 9 )
  {
    strcpy( passwd, &p_str[1] ); //% not gud
  }
  else
  {
    strcpy( passwd, &p_str[0] ); //% not gud!!
  }
  
}

//%
//%
//% Check Pattern of Combined serial + date 
//%
//%
int PWGenerator::PasswordGenerator::_pswPatternCheck( char * str )
{
  //if( str[ 0 ] == '0' /* && str[ 1 ] == '0' */ )
  //{
  //  return( 0 );
  //}
  if( _pswStraight( str, '0' ) >= 4 ||
      _pswStraight( str, '1' ) >= 4 ||
      _pswStraight( str, '2' ) >= 4 ||
      _pswStraight( str, '3' ) >= 4 ||
      _pswStraight( str, '4' ) >= 4 ||
      _pswStraight( str, '5' ) >= 4 ||
      _pswStraight( str, '6' ) >= 4 ||
      _pswStraight( str, '7' ) >= 4 ||
      _pswStraight( str, '8' ) >= 4 ||
      _pswStraight( str, '9' ) >= 4 )
  {
    return( 0 );
  }
  if( _pswRepeatDigit( str, '0' ) >= 5 ||
      _pswRepeatDigit( str, '1' ) >= 6 ||
      _pswRepeatDigit( str, '2' ) >= 6 ||
      _pswRepeatDigit( str, '3' ) >= 6 ||
      _pswRepeatDigit( str, '4' ) >= 6 ||
      _pswRepeatDigit( str, '5' ) >= 6 ||
      _pswRepeatDigit( str, '6' ) >= 6 ||
      _pswRepeatDigit( str, '7' ) >= 6 ||
      _pswRepeatDigit( str, '8' ) >= 6 ||
      _pswRepeatDigit( str, '9' ) >= 6 )
  {
    return( 0 );
  }

  return( 1 );
}


//% 
//% _pswdAsciiGen
//%
//% Generates a password from input as strings or character pointers!!
//%
int PWGenerator::PasswordGenerator::_pswdFromAsciiGen ( char * serial_num, char * year, char * month, char * day, char * passwd )
{
  

  ulong bin_sn = convertCharPtrToUlong(serial_num);

  ulong y =  convertCharPtrToUlong(year);

  ulong m = convertCharPtrToUlong(month);

  ulong d = convertCharPtrToUlong(day); 

  //% Now Generate the password as if inputs were long long
  _pswdFromIntGen( bin_sn, y, m, d, passwd );

  return( GOOD );

}

//%    _pswdIntGen
//%
//%    Takes unsigned long intergers and calls the main password generating algorithm
//%    to generate the password of the day
//%   
//%    Description: Produce the password for the specified date.
//%    The user supply the serial number and the date all of which in binary format.
//%    passwd    must be at large enough to hold the serila number (16 characters)
//%    Password Today = ABS( serial_num - year + (20 * month) + (((-1)^day) * day *30))
//% 
void PWGenerator::PasswordGenerator::_pswdFromIntGen ( ulong serial_num, ulong year, ulong month, ulong day, char * passwd )
{

//One should be able to try different algorithms of Generating  the password!!
#if 1
       //% This is the main algorithm which generates the password!!!
      _pswAdvPassword(serial_num, year, month, day, passwd );
#else

 //% Generate the password another way!!
     or try another algorithm 
#endif
} 


//%
//%  _passwordOfTheDay
//%
//%   Description: Givs Today's password using the serial number supplied by the user
//%    passwd    must be at large enough to hold the serila number (10 to 12 characters)
//%
int PWGenerator::PasswordGenerator::_passwordOfTheDay( char * serial_num, char * passwd )
{

  struct  tm *tm_ptr;   // See target/h/time.h
  time_t  t = time( NULL );
  passwd[ 0 ] = '\0';
  tm_ptr = localtime( &t );
  ulong   bin_sn =  convertCharPtrToUlong (serial_num);


  // Now generate password using 
  _pswdFromIntGen ( bin_sn, tm_ptr->tm_year+1900, tm_ptr->tm_mon + 1,tm_ptr->tm_mday, passwd );

  return( GOOD );
}

//%
//%    _pswAdvPassword:
//%
//%    The main password Generation algorithm
//%  
//%
int PWGenerator::PasswordGenerator::_pswAdvPassword ( ulong serial, ulong year, ulong month, ulong day, char * passwd )
{
  ulong pswRegenSerial;

  #define SYS_PSW_REGEN_SN_SEG  20000
  #define SYS_PSW_REGEN_SN_START  20000
  #define SYS_PSW_REGEN_SN_END  65000
  int re_try;
  int regen_count;
  ulong new_sn;

  pswRegenSerial = serial;
  /* Normal segment */
  new_sn = serial;
  regen_count = 0;
  _pswFusion( year, month, day, new_sn, passwd );
    do
    {
      if( _pswPatternCheck( passwd ) == 1 )
      {
        break;
      }
      /* First extended segment */
      new_sn = (((new_sn) % SYS_PSW_REGEN_SN_SEG) + SYS_PSW_REGEN_SN_START);
      regen_count++;
      _pswFusion( year, month, day, new_sn, passwd );
      if( _pswPatternCheck( passwd ) == 1 )
      {
        break;
      }
      /* Seoond extended segment */
      new_sn += SYS_PSW_REGEN_SN_SEG;
      regen_count++;
      _pswFusion( year, month, day, new_sn, passwd );
              do
              {
                if( _pswPatternCheck( passwd ) == 1 )
                {
                  break;
                }
                /* Subsequent extended segment */
                new_sn = (((serial) % SYS_PSW_REGEN_SN_SEG) + SYS_PSW_REGEN_SN_START) + ((serial*37) & 0x1F);
                for( re_try = 0; re_try < 100; re_try++ )
                {
                  regen_count++;
          //{printf("%3d: %4d-%02d-%02d %5d: %5d %s %5s %5s\n", regen_count, year, month, day, serial, new_sn, passwd, WKstr_s, WKstr_t ); }
                  _pswFusion( year, month, day, new_sn, passwd );
                  if( _pswPatternCheck( passwd ) == 1 )
                  {
                    break;
                  }
                  new_sn += (serial % 10000 );
                  if( new_sn < ( SYS_PSW_REGEN_SN_START + SYS_PSW_REGEN_SN_SEG ) )
                  {
                    new_sn += SYS_PSW_REGEN_SN_SEG;
                  }
                  else
                  {
                    new_sn -= SYS_PSW_REGEN_SN_SEG;
                  } 
                  if( new_sn > SYS_PSW_REGEN_SN_END )
                  {
                    new_sn = SYS_PSW_REGEN_SN_START + (serial & 0xF);
                  }
                }
              } while( 0 );
    } while( 0 );

  if( regen_count > 0 )
  {
    pswRegenSerial = new_sn;
  }
  return( regen_count );

  #undef  SYS_PSW_REGEN_SN_SEG
  #undef  SYS_PSW_REGEN_SN_START
  #undef  SYS_PSW_REGEN_SN_END

}

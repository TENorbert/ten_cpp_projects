/**************************************************************************************
*											                                          *										  	
*		 Property of ECOLAB Copyright (c) 2016, All Rights Reserved                   *
*        Modified from Copyright (c) 2012 Nalco Company. All Rights Reserved.	      *	
*											                                          *
*		     Implemented by Tambe E. Norbert  March 09, 2016 			              *		
***************************************************************************************/
#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

#include <math.h>
#include <string.h>
#include <string>



//%
//%  Namespace PWGenerator has Class  PasswordGenerator is a Password Generator Class
//%  Can Generate Daily TM Password, Random TM password &
//%  Customer Password and encryped the Password
//%
//%
#define EXIT_SUCCESS 0 // naturally are in cstdlib
#define EXIT_FAILURE 1   
#define ERROR "Error!! Invalid Input"
#define FAILED -1  // for failure to generate password!!

//% Lengths of different type of serial number
#define  SLENGTH_A  10  //10 Character Long serial Number, static Allocation
#define  SLENGTH_B  12  //12 Character Long Serial Number, static Allocation

#define MAX_A 11 // for 10 character size serial numbers
#define MAX_B 13 // for 12 character size serial numbers

#define  PWDSIZE  9 // Generated Password is at most 9 characters long, static Allocation 


#define NOT_GOOD  0 //% if Error
#define GOOD      1  //% is all is good! 

//% If integer serial must be long enough
typedef unsigned long ulong;

//% serial number as a char string(strings as characters)
typedef char SN_A[SLENGTH_A];
typedef char SN_B[SLENGTH_B];

typedef char PWD[PWDSIZE]; //Password is a character array of at most 9 characters!!



//% Namesspace
namespace PWGenerator {

               // #define std::string pWDString;


                //% select the type of Serial Number
                enum STYPE {
                  sNTypeA = 0, //% 10 chracters long SN
                  sNTypeB      //% 12 character long SN
                };


                //General USEFULL FUNCTIONS
                //% Check type of Serial Number
                int serialNumberType (const std::string & );
                // Takes a given serial number as string and its type and choses the correct MAX of size of Character ARRAY or Pointer
                char* convertStringToCharPtrForType (const std::string &, int&);
                char* convertStringToCharPtr (const std::string&);  
                //% Convert CharPtr(must only point to digit literals) to unsigned long
                ulong convertCharPtrToUlong (const char *chrPtr);
                //% Convert ulong(must only point to digit literals) to Character Pointer
                char* convertUlongToCharPtr (ulong &);
                //% Rotate Characters in a string
                void rotate(char* str);

            
                     
                


                //% Create Instance of Password Generator Object with Valid Serial Number                

                //% Password Generating class: properties & Methods
                class PasswordGenerator 
                {

                public: 
                	      //Constructors 
                  	    //%
                        //%  Naked  constructor
                        PasswordGenerator ();
                        //Input Constructor 
                 	    PasswordGenerator (ulong, ulong, ulong, ulong, ulong);

                        //Constructor Using std::strings (serial Number, day, month, year, pswd
                        PasswordGenerator (char*, char*, char*, char*, char*);

                       
                        //% Destructor 
                 	    virtual ~PasswordGenerator ();
                  
                        //% Public Methods
                        //Set values for the passwordGenerator Object, Used template definition?
                        //template < class T > 
                        //For unsigned long types
                        void setParametersInt( ulong &sNumber, ulong &day, ulong &month, ulong &year, ulong &password ) { _serialNumber = sNumber; _day = day;  _month = month;  _year = year; _ipasswd = password; }
                        
                        //if class is created with Array of Characters or Pointers to Array of Characters
                        void setParametersChar(char *serialN, char* sDay, char* sMonth, char* sYear, char* pswd) { _serialN = serialN; _sDay = sDay; _sMonth = sMonth; _sYear = sYear ; _sPswd = pswd; }

                        //void setParametersB (SN_B &serialB, pString &sDay, pString &sMonth, pString &sYear) { _serialB = serialA; _sDay = sDay; _sMonth = sMonth; _sYear = sYear; }
                        // lets see what the object Integer instance is holding 
                        void printInstanceIntInfo (PasswordGenerator & );
                        // lets see what the object Character Pointer instance is holding 
                        void printInstanceCharInfo (); 
                        
                        //% return generated password
                        char* generatedPassword (std::string &); 

                         // if needed password of any given day!!
                        //char* passwordOfTheDay ( bool &request, char* day, );
                        





                private:
                   
                   	    //% private variables
                        //% Char Arrays
                        SN_A _serialA;
                        SN_B _serialB; 

                        char*_serialN;
                        char* _sDay;
                        char* _sMonth;
                        char* _sYear; 
                        char* _sPswd; 
                        //% single varilables
                  	    ulong _serialNumber;
                   	    ulong _day;
                   	    ulong _month;
                   	    ulong _year;
                        ulong _ipasswd;
                     
                        //% private methods : //Devide & conquer! best approach to accomodate future HEADACHES!!!
                        int _pswStraight( char * str, char digit );
                        //% count repeated digits
                        int _pswRepeatDigit( char * str, char c );
                        //% month disperse
                        ulong _pswDisperseMonth (ulong month);
                        //% Day disperse
                        ulong _pswDisperseDay ( ulong day );
                        //% time disperse
                        ulong _pswDisperseTime ( ulong year, ulong month, ulong day );
                        //% Disperse serial
                        ulong _pswDisperseSerial ( ulong serial, ulong day );
                        //% Combine all!!
                        void _pswFusion( ulong serial, ulong month, ulong day, ulong year, char * passwd );
                        //% Check repeated digits
                        int _pswPatternCheck( char * str );
                        
                        //% Generate Password using charactter Strings
                        int _pswdFromAsciiGen( char * serial_num, char * year, char * month, char * day, char * passwd );
                        //% Generate the password using inputs as unsigned long 
                        void _pswdFromIntGen(ulong serial_num, ulong year, ulong month, ulong day, char * passwd );
                        //% Main Password Generating algo
                        int _pswAdvPassword( ulong serial, ulong year, ulong month, ulong day, char * passwd );
                        //% Make sure SN is Valid
                        bool _isSerialNumberValid (char* ); 
                        //% Password of the day
                        int _passwordOfTheDay( char * serial_num, char * passwd );





                };

}

#endif //PASSWORD_GENERATOR_H



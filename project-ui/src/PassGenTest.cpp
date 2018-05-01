//% Testing Password Parameter Class

#include <stdio.h>
#include <iostream>
#include <stdlib.h>     //for strtoul //
#include <string>     // std::string, std::to_string

#include "PasswordGenerator.h"


using namespace std;

using namespace PWGenerator; 

//int main ( int argc, char** argv)
int main ( )
{

      //printf("Created a Password Object's Parameters\n");
      std::cout << "Created a Password Object's Parameters\n";
      //PasswordGenerator pwdGen; // = PasswordGenerator(0,0,0,0) ; 

      //char tmpwd [] = "D1137D0441";
      char tmpwd [] = "D1518E025897";  
      //char tmpwd [] = "1518025897";
      char* tptr = tmpwd; 
      PasswordGenerator pwdGen(0,0,0,0,tmpwd); // = PasswordGenerator(0,0,0,0) ; 
      //pwdGen.printInstanceIntInfo(pwdGen);
      pwdGen.printInstanceCharInfo();
      ulong ln = PWGenerator::convertCharPtrToUlong (tptr);
      printf("Converted %s Character Pointer to %lu Unsigned Long \n",tptr, ln );

      char* ptr = PWGenerator::convertUlongToCharPtr (ln);
      printf("Converted %lu Unsigned Long to %s Character Pointer \n", ln, ptr);
      /*
      ulong sn = 1009467812;
      ulong d  = 10;
      ulong m  = 04;
      ulong y  = 2016;
      ulong pwd = 0;
      */
     
      //std::string ss = "ABCDGET!T2354";
      std::string snt = "D1518E025897";
      
      //std::string strss = "EMpty String"; 
     // printf("mynew type string is %s \n", strss.c_str());

      //std::string snEnt = "D1137D0441"; //"D1518E025897";
      std::string snEnt = "D1518E025897";
      //std::string snEnt = "D1946D255689";
      std::string td = "11";
      std::string tM = "04";
      std::string tY = "2015";
      std::string tmpswd = "099999999";



      
      int t = PWGenerator::serialNumberType (snEnt);
      int it = 2; 
      
     
      char* serialNumber = PWGenerator::convertStringToCharPtrForType (snEnt, t);
      char* day = PWGenerator::convertStringToCharPtrForType (td, it);
      char* month = PWGenerator::convertStringToCharPtrForType (tM, it);
      char* year = PWGenerator::convertStringToCharPtrForType (tY, it);
      char*  pwd = PWGenerator::convertStringToCharPtrForType (tmpswd, it);
     
      pwdGen.setParametersChar(serialNumber, day, month, year, pwd);
      pwdGen.printInstanceCharInfo();

      ulong lber = PWGenerator::convertCharPtrToUlong (day);
      printf("Converted %s Character Pointer to %lu Unsigned Long \n",day, lber );
      /*
      //char serialNumber [] = "D1137D0441"; //"D1518E025897";
      char serialNumber [] = "D1518E025897";
      char day [] = "11";
      char month [] = "04";
      char year [] = "2015";
      char pwd []  = "099999999";
      */ 
       //PasswordGenerator pwdGen2(serialNumber,day,month,year,pwd); 
       //pwdGen2.printInstanceCharInfo();
     
      //pwdGen.setParametersInt(sn, d, m, y, pwd);
       std::cout << "Serial Number Type is = " << PWGenerator::serialNumberType(snEnt) << std::endl; 
      //pwdGen.printInstanceIntInfo(pwdGen);
      
       printf("S Number =  %s\n", serialNumber);
       std::cout << "Number of Characters in serial number Character Pointer is = " << strlen(serialNumber) << std::endl;
       printf("T Day =  %s\n", day);
       printf("T Month =  %s\n", month);
       printf("T Year  =  %s\n", year);
       printf("T Password = %s\n", pwd);
         
      pwdGen.generatedPassword(snEnt);

      return EXIT_SUCCESS;
}

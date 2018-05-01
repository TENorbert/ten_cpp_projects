#ifndef LOCALIZATION_H
#define LOCALIZATION_H

//  RANGES OF TYPES OF LOCALIZED STRINGS
#define STRINGS_START               1000  // Generalized strings start here

#define MACHINE_STRINGS_START       2000  // MACHINE strings start here
#define PUMP_STRINGS_START          2100  // MACHINE strings start here
#define ALARM_STRINGS_START         10000 // Alarm strings appear on the marquee
#define ALARM_STRING_MSGS_START     5000  // Alarm messages appear on a view's client area

//
//    This hopes to be a work around for not being able to export a Q_ENUM from a context property.
//
//class AquanomicsStringId: public QObject
//        Q_OBJECT
//        Q_ENUMS(StringID)
//public:

    enum stringID {

        // Machine strings

        #define WASHER1_STR                       (MACHINE_STRINGS_START + 1)
        #define WASHER2_STR                       (MACHINE_STRINGS_START + 2)
        #define WASHER3_STR                       (MACHINE_STRINGS_START + 3)
        #define WASHER4_STR                       (MACHINE_STRINGS_START + 4)

        // Pump  strings

        #define PUMP1_STR                         (PUMP_STRINGS_START + 1)   // pump name 1
        #define PUMP2_STR                         (PUMP_STRINGS_START + 2)   // pump name 2
        #define PUMP3_STR                         (PUMP_STRINGS_START + 3)   // pump name 3
        #define PUMP4_STR                         (PUMP_STRINGS_START + 4)   // pump name 4
        #define PUMP5_STR                         (PUMP_STRINGS_START + 5)   // pump name 5
        #define PUMP6_STR                         (PUMP_STRINGS_START + 6)   // pump name 6
        #define PUMP7_STR                         (PUMP_STRINGS_START + 7)   // pump name 7
        #define PUMP8_STR                         (PUMP_STRINGS_START + 8)   // pump name 8
        #define PUMP9_STR                         (PUMP_STRINGS_START + 9)   // pump name 9
        #define PUMP10_STR                        (PUMP_STRINGS_START + 10)  // pump name 10


        // General strings

        #define ENGLISH_STR                       (STRINGS_START + 1)
        #define GERMAN_STR                        (STRINGS_START + 2)
        #define ITALIAN_STR                       (STRINGS_START + 3)
        #define SPANISH_STR                       (STRINGS_START + 4)
        #define FRENCH_STR                        (STRINGS_START + 5)
        #define PORTUGUESE_STR                    (STRINGS_START + 6)
        #define FRENCH_CA_STR                     (STRINGS_START + 7)

        // This was used for the search routine in the internal english table
        #define ENDOFSTRINGLIST               -1

        // some constants used to pick intended language category or usage
        #define DEFAULTLANGUAGE   0
        #define PRIMARY   1
        #define SECONDARY 2
        #define TM        3
    };
//};




#endif

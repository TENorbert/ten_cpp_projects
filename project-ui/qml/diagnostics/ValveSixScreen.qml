/***********************************************************************
**
** ValveSixScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

Valve {

      id: v6Screen
      breadcrumb:  "Drain Valve"

      //Valve Diagnostics Data Strings
      temperatureString:        "Temperature"
      conductivityString:       "Conductivity"
      pWaterStatusString:       "P.Switch Status"
      vTimerString    :         "Timer"
      vTestString     :         "Valve Test"
      vStateString    :         "Valve State"

      valveTemp:                "0 F"
      valveCond:                "0 uS/cm"
      valvePStatus:             "CLOSE"
      valveDTimer:              "0 s"
      valveTest:                "NONE"
      valveState:               "CLOSE"


      //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]
      //property int mCount : valveDataModel.count

      //% Select valve to Run Diagnostics Test
      property int vId: 5  // % Asign Valve ID to perform Diagnostics here

      //property int timeCountDownValue: diagcontext.totalTime


      //% Funcation to Select Valve ID
      function getValveId (id)
      {
        diagcontext.valveId = id;
      }
      //% Update Data Model
      function dataUpdate (index, DataModel, item, data)
      {
        DataModel.insert(index, {"valveItem":item, "valveData": data})
      }



 /*     
      Timer {
        id: timer
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }
*/

/*
      //% Data Model
     // property variant valveDataModel: ListModel {}
      valveDataModel: ListModel
         {
             ListElement {  valveItem: "Temperature";   valveData: "" }
             ListElement {  valveItem: "Conductivity";  valveData: "" }
             ListElement {  valveItem: "P.Switch Status";  valveData: "" }
             ListElement {  valveItem: "Timer";  valveData: "" }
             ListElement {  valveItem: "Valve Test ";  valveData: "" }
             ListElement {  valveItem: "Valve State";  valveData: "" }
         }

*/




     //% Update to Delay Time & its value in model once Diagnostic is Activated
     function updateModel( mCount)   
    {
            //valveDataModel.clear();
            var index = 0 ;
            for (var i=0; i < mCount ;i++)
            {
               if ( valveDataModel.get(i).valveItem  == "Time" )
               {
                 index = i;
               }
            //	valveDataModel.append({"valveItem":"Tempeature", "valveData":" 5 F" })
            }
            valveDataModel.set(index, {"valveItem":"Delay Time", "valveData": timeCountDownValue + " s"})
           
    }


    Component.onCompleted: {
               //updateModel( mCount );
               //delay(10000, function() {
               //updateModel( mCount ); })
               //% Select Valve Id to Perform Diagnostics on
                getValveId( vId )
                }



}



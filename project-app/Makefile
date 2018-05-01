CXX=/usr/local/angstrom/arm/bin/arm-angstrom-linux-gnueabi-g++
CC=arm-angstrom-linux-gnueabi-gcc

LDFLAGS = -L../../Condor/Utilities  -L ../../Condor/ICU/Tools/armicu/lib -fpic
CXXFLAGS = -I../../Condor/Utilities -I../../Condor/Common  -I/usr/local/boost_1_44_0 -DECOLAB_THREADS_MANUAL_CLEANUP  -DTIXML_USE_STL  -fpic -g  
LIBS = -lutilities -lpthread -lrt -licudata -licui18n -licuuc
objects = main.o  IOBoardSyncManager.o GarfunkelData.o ProductData.o  IOBoardMessages.o  IPCMessages.o Alarm.o AlarmHandler.o IPCCommand.o DiagnosticsManager.o GarfunkelCommandProcessor.o BoardCommands.o  DatabaseCommands.o DatabaseCallbacks.o GarfunkelIPCData.o GarfunkelIPC.o ApplicationContext.o ElapsedTime.o  DatabaseManager.o DispenseAlgorithm.o SprayObject.o GarfunkelApp.o EventlogManager.o
# 
all : Garfunkel

Garfunkel : $(objects)
	$(CXX) $(LDFLAGS) $(LIBS) -o Garfunkel $(objects)

main.o : main.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c main.cpp
IPCCommand.o : IPCCommand.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c IPCCommand.cpp
GarfunkelCommandProcessor.o : GarfunkelCommandProcessor.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c GarfunkelCommandProcessor.cpp	
IPCMessages.o : IPCMessages.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c IPCMessages.cpp	
ApplicationContext.o : ApplicationContext.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c ApplicationContext.cpp
GarfunkelIPCData.o : GarfunkelIPCData.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c GarfunkelIPCData.cpp 
ElapsedTime.o : ElapsedTime.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c ElapsedTime.cpp
BoardCommands.o : BoardCommands.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c BoardCommands.cpp
GarfunkelIPC.o : GarfunkelIPC.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c GarfunkelIPC.cpp
IOBoardMessages.o : IOBoardMessages.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c IOBoardMessages.cpp
GarfunkelData.o : GarfunkelData.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c GarfunkelData.cpp
ProductData.o : ProductData.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c ProductData.cpp	
IOBoardSyncManager.o : IOBoardSyncManager.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c IOBoardSyncManager.cpp	
DispenseAlgorithm.o : DispenseAlgorithm.cpp 
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c DispenseAlgorithm.cpp		
AlarmHandler.o: AlarmHandler.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c AlarmHandler.cpp
Alarm.o: Alarm.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c Alarm.cpp
DatabaseManager.o: DatabaseManager.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c DatabaseManager.cpp
DatabaseCommands.o: DatabaseCommands.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c DatabaseCommands.cpp
DatabaseCallbacks.o: DatabaseCallbacks.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c DatabaseCallbacks.cpp	
DiagnosticsManager.o: DiagnosticsManager.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c DiagnosticsManager.cpp
SprayObject.o: SprayObject.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c SprayObject.cpp
GarfunkelApp.o: GarfunkelApp.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c GarfunkelApp.cpp
EventlogManager.o: EventlogManager.cpp
	$(CXX) $(CXXFLAGS) -D_REENTRANT -c EventlogManager.cpp
		
.PHONY : clean
clean :
	rm -f Garfunkel $(objects)
	
.PHONY : install
install : all	

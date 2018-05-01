#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "ecolab.h"
#include "DBAccess.h"

#include "GarfunkelData.h"

namespace Garfunkel
{
    class SystemDataCallback : public ecolab::DB::Callback
	{
	private:
    	BOOLEAN _firstUpdate;
		public:
    	SystemDataCallback(const std::string & name);
			virtual ~SystemDataCallback();
			virtual BOOLEAN Update();
	};

    class MachineDataCallback : public ecolab::DB::Callback
    	{
    		public:
    	MachineDataCallback(const std::string & name);
    			virtual ~MachineDataCallback();
    			virtual BOOLEAN Update();
    	};

    class FormulaDataCallback : public ecolab::DB::Callback
    	{
    		public:
    	FormulaDataCallback(const std::string & name);
    			virtual ~FormulaDataCallback();
    			virtual BOOLEAN Update();
    	};

    class MachineSpecificPumpDataCallback : public ecolab::DB::Callback
    {
    		public:
    	MachineSpecificPumpDataCallback(const std::string & name);
     			virtual ~MachineSpecificPumpDataCallback();
      			virtual BOOLEAN Update();
    };

    class ProductMapCallback : public ecolab::DB::Callback
    {
    		public:
    	ProductMapCallback(const std::string & name);
     			virtual ~ProductMapCallback();
      			virtual BOOLEAN Update();
    };

    class ProductDataCallback : public ecolab::DB::Callback
    {
    		public:
    	ProductDataCallback(const std::string & name);
     			virtual ~ProductDataCallback();
      			virtual BOOLEAN Update();
    };

    class ProductPulseCriteriaDataCallback : public ecolab::DB::Callback
    {
    		public:
    	ProductPulseCriteriaDataCallback(const std::string & name);
     			virtual ~ProductPulseCriteriaDataCallback();
      			virtual BOOLEAN Update();
    };

    class DispenserPocketInfoDataCallback : public ecolab::DB::Callback
    {
    		public:
    	DispenserPocketInfoDataCallback(const std::string & name);
     			virtual ~DispenserPocketInfoDataCallback();
      			virtual BOOLEAN Update();
    };

    class LocalizedStringsCallback : public ecolab::DB::Callback
    {
    		public:
    	LocalizedStringsCallback(const std::string & name);
     			virtual ~LocalizedStringsCallback();
      			virtual BOOLEAN Update();
    };

    class ThreadingCallback : public ecolab::DB::Callback
    {
        public:
            ThreadingCallback(const std::string & name);
            virtual ~ThreadingCallback();
            virtual BOOLEAN Update();
    };
};

#endif

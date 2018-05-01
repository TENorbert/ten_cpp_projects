#ifndef PRODUCT_DATA_H
#define PRODUCT_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "ecolab.h"
#include "GarfunkelData.h"


namespace Garfunkel
{
	class ProductInfo
	{
		public:
			ProductInfo(int id, GarfunkelProductType type, int nt);
			ProductInfo(const ProductInfo & objectToCopy) ;
			virtual ~ProductInfo();
			int GetProductID() {return ProductId;}
			GarfunkelProductType GetProductType(){return ProductType;}
			int GetNozzleTypeRefID() {return NozzleTypeRefID;}
			int GetProductSlotType() {return ProductSlotType;}
			timespec GetPredictedEmptyInHours();
			int GetResetDate();
			BOOLEAN GetTurnOffTitrationValues() {return TurnOffTitrationValues;}
			BOOLEAN SetPredictedEmptyInHours(int hrs);
			void ResetOOPDetectState();

		protected:
			int ProductId;
			GarfunkelProductType  ProductType;
			int NozzleTypeRefID;
			int ProductSlotType;
			int PredictedEmptyInHours;
			timespec ResetDate;
			BOOLEAN TurnOffTitrationValues;
			BOOLEAN isEmpty;
			ecolab::Shareable<GarfunkelProductState> OOP_State;
	};


	class SProduct: public ProductInfo
	{
		public:
			SProduct(int id, GarfunkelProductType type, int nt);
			virtual ~SProduct();
			ecolab::Shareable<BOOLEAN>  IsInUse;
			ecolab::Shareable<float>  PercentSO3InBlock;
		private:
	};

	class PProduct: public ProductInfo
	{
		public:
			PProduct(int id, GarfunkelProductType type, int nt);
			virtual ~PProduct();
			ecolab::Shareable<float> TotalAcidHardnessRatio;
			ecolab::Shareable<float> TotalMolePercentAmine;
			ecolab::Shareable<float> NaOHNeededToNeutralize;
			ecolab::Shareable<float> PercentCHA;
			ecolab::Shareable<float> PercentDEAE;
		private:

	};

	class OProduct: public ProductInfo
	{
		public:
			OProduct(int id, GarfunkelProductType type, int nt);
			virtual ~OProduct();
			ecolab::Shareable<float> PercentNaOHInProduct;
		private:

	};

	class ProductPulseCriteria
	{
		public:
			ProductPulseCriteria()
			{

			};
			ProductPulseCriteria(const ProductPulseCriteria & objectToCopy)
			{
			};
			~ProductPulseCriteria()
			{
			};

			ecolab::Shareable<float> FromTemp;
			ecolab::Shareable<float> ToTemp;
			ecolab::Shareable<float> PulseAmount;
			ecolab::Shareable<int> PulseOnTime;
			ecolab::Shareable<int> PulseOffTime;
			ecolab::Shareable<int> MaxNoOfPulses;
			ecolab::Shareable<float> PercentageTarget;
	};

	class ProductPulseInfo
	{
		public:
			ProductPulseInfo();
			ProductPulseInfo(const ProductPulseInfo & objectToCopy);
			~ProductPulseInfo();
			ecolab::Shareable<int> ProductId;
			std::vector<boost::shared_ptr<Garfunkel::ProductPulseCriteria> > _productPulseInfo;
			boost::shared_ptr<Garfunkel::ProductPulseCriteria> NeedtoPulse(float amount, float temp, int & onTime, int & offTime, float & perCent);
	};


	class ProductData
	{
		public:
			ProductData(const ProductData & objectToCopy);
			~ProductData();
			static ProductData&  Instance();	//single instance
			BOOLEAN Reset();
			boost::shared_ptr< Garfunkel::ProductInfo > GetContextForProduct(GarfunkelProductType productId);
		private:
			static BOOLEAN _initDone;
			BOOLEAN ReadProductDataFromDatabase();
			BOOLEAN ReadSProductPropertiesFromDatabase();
			BOOLEAN ReadPProductPropertiesFromDatabase();
			BOOLEAN ReadOProductPropertiesFromDatabase();
			BOOLEAN ReadProductDataFromFile();
			BOOLEAN WriteProductDataToFile();
			BOOLEAN ReadProductPulseDataFromDatabase();
			BOOLEAN ReadProductPulseDataFromFile();
			BOOLEAN WriteProductPulseDataToFile();

			ProductData();
			std::map<GarfunkelProductType, boost::shared_ptr< Garfunkel::ProductInfo > >  _product; //prodId->ProductInfo
			std::map<int, boost::shared_ptr< Garfunkel::ProductPulseInfo > >  _productPulseCriteria; //prodId->ProductPulseInfo
			ecolab::MutexLock                              _productLock;
	};


	class OOPState
	{
		public:
			OOPState();
			OOPState(const OOPState & objectToCopy);
			~OOPState();
			ecolab::Shareable<GarfunkelProductState> OOP_State;
			ecolab::Shareable<BOOLEAN> OOPAlarmAlreadyDetected;
			ecolab::Shareable<BOOLEAN> IsAlarmMuted;
			ecolab::Shareable<int>     AlarmMuteCount;
			void ResetOOPDetectState();
			timespec GetLastAlarmMuteTimeTime();
			void    UpdateLastAlarmMuteTime();
			timespec GetAlarmActivatedTimeTime();
			void    UpdateAlarmActivatedTime();

		private:
			timespec                 _lastMutedTime;
			ecolab::MutexLock        _lastMutedTimeDataLock;
			timespec                 _alarmActivatedTime;
			ecolab::MutexLock        _alarmActivatedTimeDataLock;

	};

	class PocketInfo : public OOPState
	{
		public:
			PocketInfo();
			PocketInfo(const PocketInfo & objectToCopy);
			~PocketInfo();
			ecolab::Shareable<GarfunkelProductPocket> PocketId;
			ecolab::Shareable<GarfunkelPumpState> IsOn;
	};


	class PocketInfoData
	{
		public:
			PocketInfoData(const PocketInfoData & objectToCopy);
			~PocketInfoData();
			static PocketInfoData&  Instance();	//single instance
			boost::shared_ptr< Garfunkel::PocketInfo> GetContextForPocket(int pocketid);
		private:
			static BOOLEAN _initDone;
			void Initailize();
			PocketInfoData();
			std::map<int, boost::shared_ptr< Garfunkel::PocketInfo> >  _pocket;		//Pocketid->PocketInfo
			ecolab::MutexLock                              _pocketLock;
	};


};


#endif //PRODUCT_DATA_H

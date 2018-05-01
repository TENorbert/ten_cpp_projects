#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ProductData.h"
/////////////////////////////////////////////////////////////////
/////
/////ProductInfo
//////////////////////////////////////////////////////////////////
Garfunkel::ProductInfo::ProductInfo(int id, GarfunkelProductType type, int nt)
{
	ProductId = id;
	ProductType = type;
	NozzleTypeRefID = nt;
	PredictedEmptyInHours = 2000;
	TurnOffTitrationValues = False;
	isEmpty = False;
	OOP_State.Set(eProductFull);

}

Garfunkel::ProductInfo::ProductInfo(const Garfunkel::ProductInfo & objectToCopy)
{
}

Garfunkel::ProductInfo::~ProductInfo()
{
	std::cout << " ProductInfo destructor called for id="<<ProductId<<std::endl;
}




Garfunkel::SProduct::SProduct(int id, GarfunkelProductType type, int nt): ProductInfo(id, type, nt)
{
	//TODO , update these to db defaults when you get them
	IsInUse = True;
	PercentSO3InBlock = 1.0;
}


Garfunkel::SProduct::~SProduct()
{
	std::cout << " S Product destructor called"<<std::endl;
}




Garfunkel::PProduct::PProduct(int id, GarfunkelProductType type, int nt): ProductInfo(id, type, nt)
{
	//TODO , update these to db defaults when you get them
	TotalAcidHardnessRatio = 1.0;
	TotalMolePercentAmine = 1.0;
	NaOHNeededToNeutralize = 1.0;
	PercentCHA = 1.0;
	PercentDEAE = 1.0;


}


Garfunkel::PProduct::~PProduct()
{
}


Garfunkel::OProduct::OProduct(int id, GarfunkelProductType type, int nt): ProductInfo(id, type, nt)
{
	//TODO , update these to db defaults when you get them
	PercentNaOHInProduct = 1.0;
}


Garfunkel::OProduct::~OProduct()
{
}


//////////////////////////////////////////////////////////////////
///
/// ProductData
//////////////////////////////////////////////////////


Garfunkel::ProductPulseInfo::ProductPulseInfo()
{

}

Garfunkel::ProductPulseInfo::ProductPulseInfo(const Garfunkel::ProductPulseInfo & objectToCopy)
{
}

Garfunkel::ProductPulseInfo::~ProductPulseInfo()
{

	if(_productPulseInfo.size() > 0)
	{
		_productPulseInfo.erase(_productPulseInfo.begin(), _productPulseInfo.end());
	}

}

boost::shared_ptr<Garfunkel::ProductPulseCriteria> Garfunkel::ProductPulseInfo::NeedtoPulse(float amount, float temp, int & onTime, int & offTime,  float & perCent)
{
	boost::shared_ptr<Garfunkel::ProductPulseCriteria> checkData, retData;

	std::vector<boost::shared_ptr<Garfunkel::ProductPulseCriteria> >::const_iterator iter;

	std::cout<<" req amount="<<amount<<std::endl;
	std::cout<<" cur temp="<<temp<<std::endl;

	for(iter=_productPulseInfo.begin(); iter!=_productPulseInfo.end(); iter++)
	{
		checkData = *iter;
		if(checkData)
		{
			//std::cout<<" Checking .. lowTempThresh ="<<checkData->FromTemp.Get()<<std::endl;
			//std::cout<<" Checking.. highTempThresh ="<<checkData->ToTemp.Get()<<std::endl;
			//std::cout<<" pulse amount ="<<checkData->PulseAmount.Get()<<std::endl;

			if(temp>=checkData->FromTemp.Get()&&temp<=checkData->ToTemp.Get()&&amount<=checkData->PulseAmount.Get())
			{
				std::cout<<" ********Pulse mode**************"<<std::endl;
				onTime= checkData->PulseOnTime.Get();
				offTime = checkData->PulseOffTime.Get();
				perCent = checkData->PercentageTarget.Get();
				std::cout<<" req amount="<<amount<<std::endl;
				std::cout<<" pulse amount ="<<checkData->PulseAmount.Get()<<std::endl;
				std::cout<<" cur temp="<<temp<<std::endl;
				std::cout<<" pulse lowTempThresh ="<<checkData->FromTemp.Get()<<std::endl;
				std::cout<<" pulse highTempThresh ="<<checkData->ToTemp.Get()<<std::endl;
				std::cout<<" PulseOnTime="<<onTime<<std::endl;
				std::cout<<" PulseOffTime="<<offTime<<std::endl;
				std::cout<<" PercentageTarget="<<perCent<<std::endl;
				retData = checkData;
				break;
			}
			else if(checkData->FromTemp.Get()==0&&checkData->ToTemp.Get()==0&&amount<=checkData->PulseAmount.Get())//check for always pulse critera
			{
				std::cout<<" ********Always Pulse mode for this amount**************"<<std::endl;
				onTime= checkData->PulseOnTime.Get();
				offTime = checkData->PulseOffTime.Get();
				perCent = checkData->PercentageTarget.Get();
				std::cout<<" req amount="<<amount<<std::endl;
				std::cout<<" pulse amount ="<<checkData->PulseAmount.Get()<<std::endl;
				retData = checkData;
				break;
			}

		}
	}

	return retData;

}

BOOLEAN Garfunkel::ProductData::_initDone = False;
Garfunkel::ProductData::ProductData()
{

}

Garfunkel::ProductData::ProductData(const Garfunkel::ProductData & objectToCopy)
{
}

Garfunkel::ProductData::~ProductData()
{
	ecolab::ScopeLock Lock(_productLock);

	if(_product.size() > 0)
	{
    	_product.erase(_product.begin(), _product.end());
	}

    if(_productPulseCriteria.size() > 0)
	{
    	boost::shared_ptr< Garfunkel::ProductPulseInfo > pulseinfo;
    	std::map<int, boost::shared_ptr<Garfunkel::ProductPulseInfo> > ::const_iterator iter;

    	for(iter = _productPulseCriteria.begin(); iter!= _productPulseCriteria.end(); iter++)
    	{
    		pulseinfo = iter->second;
    		if(pulseinfo)
    		{
    			pulseinfo->_productPulseInfo.erase(pulseinfo->_productPulseInfo.begin(), pulseinfo->_productPulseInfo.end());
    		}
    	}
    	_productPulseCriteria.erase(_productPulseCriteria.begin(), _productPulseCriteria.end());
	}

}

BOOLEAN Garfunkel::ProductData::Reset()
{
	ecolab::ScopeLock Lock(_productLock);
    if(_product.size() > 0)
	{
    	_product.erase(_product.begin(), _product.end());
	}

    if(_productPulseCriteria.size() > 0)
	{
    	boost::shared_ptr< Garfunkel::ProductPulseInfo > pulseinfo;
    	std::map<int, boost::shared_ptr<Garfunkel::ProductPulseInfo> > ::const_iterator iter;

    	for(iter = _productPulseCriteria.begin(); iter!= _productPulseCriteria.end(); iter++)
    	{
    		pulseinfo = iter->second;
    		if(pulseinfo)
    		{
    			pulseinfo->_productPulseInfo.erase(pulseinfo->_productPulseInfo.begin(), pulseinfo->_productPulseInfo.end());
    		}
    	}
    	_productPulseCriteria.erase(_productPulseCriteria.begin(), _productPulseCriteria.end());
	}

    _initDone = False;
    return True;
}

boost::shared_ptr< Garfunkel::ProductInfo > Garfunkel::ProductData::GetContextForProduct(GarfunkelProductType productId)
{

	ecolab::ScopeLock Lock(_productLock);
	boost::shared_ptr< Garfunkel::ProductInfo>  prodinfo;
	std::map<GarfunkelProductType, boost::shared_ptr<Garfunkel::ProductInfo> > ::const_iterator iter;
	prodinfo.reset();
	iter = _product.find((GarfunkelProductType) productId);
	if(iter!=_product.end())
	 return iter->second;
	else
	return prodinfo;

}


Garfunkel::ProductData&  Garfunkel::ProductData::Instance()
{
    static ProductData  singleton;
    BOOLEAN                 retValue = False;
	if(!_initDone)
	{
		std::cout<<"Initiating Product data Init..."<<std::endl;
		retValue = singleton.ReadProductDataFromDatabase();
		if(retValue==True)
		{
			singleton.ReadSProductPropertiesFromDatabase();
			singleton.ReadPProductPropertiesFromDatabase();
			singleton.ReadOProductPropertiesFromDatabase();
			retValue = singleton.ReadProductPulseDataFromDatabase();
			if(retValue==True)
			_initDone= True;
			std::cout<<"Product data Init Done!"<<std::endl;
		}

	}
    return singleton;
}

BOOLEAN Garfunkel::ProductData::ReadProductDataFromDatabase()
{
   //Do initalize _ProductInfo map, for all the  products from db
		ecolab::ScopeLock Lock(_productLock);

		ecolab::DB::DBAccess    myDBAccess;
	    std::string             connectString;
	    BOOLEAN                 retValue = False;

	    // Use of the connection string.
	    connectString = "dbname = 'Garfunkel' user = 'db_user_admin' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

	        ecolab::DB::DataSet        dataSet;
	        std::string                sql;
//	        sql = "SELECT * FROM \"ProductInfo\"";
	        std::stringstream strstream;
	        strstream<<"SELECT * FROM GetAllProgrammedProducts();"; //read all products for the given locale
	        sql = strstream.str();
	        std::cout << "Trying to execute " << sql << std::endl;
	        if(myDBAccess.DBExecuteStored(sql, dataSet))
	        {

	        	std::cout << "Execution of " << sql << std::endl;

	           if(dataSet.GetNumberOfRows() > 0)
	            {
					ecolab::DB::DataRow 						rowData;
	        	   	boost::shared_ptr<ecolab::DB::IColumnData>    colData;
					std::string									colDataAsString;
					int		numRows = 0;
					int		x = 0;
					typedef boost::bimap< int, int > bm_type;

					numRows = dataSet.GetNumberOfRows();
					std::cout << "GetProductInfo No Of rows : " << numRows << std::endl;


					/*Remove any previous data*/
				    if(_product.size() > 0)
					{
				    	_product.erase(_product.begin(), _product.end());
					}

					for( ; x < numRows; x++)
					{

						rowData = dataSet.GetRow(x);
						std::cout << "GetProductInfo GetRow : " << numRows << std::endl;
						if(rowData.GetNumberOfColumns() > 0)
						{

							INT32     productid, name  = -1;
		                    REAL64    RealValue = 0.0;

		                    colData = rowData.GetColumn("productid");
							if(colData.get() != NULL)
							{
								colData->AsInt(productid);
								std::cout << "ProductID: " <<productid<<std::endl;
							}
							colData = rowData.GetColumn("productname");
							if(colData.get() != NULL)
							{
								colData->AsInt(name);
								std::cout << "ProductName: " <<name<<std::endl;
							}


							switch((GarfunkelProductType) productid)
							{
								case eSProduct:
								{
									 boost::shared_ptr< Garfunkel::ProductInfo>  pinfo = boost::shared_ptr<Garfunkel::SProduct>  (new Garfunkel::SProduct(productid, eSProduct, -1));
									 if(pinfo)
									 {
										 // TODO : Get S Block properties here
										 _product[eSProduct]= pinfo;
									 }

								}
								break;

								case eP2Product:
								{
									boost::shared_ptr< Garfunkel::ProductInfo>  pinfo = boost::shared_ptr<Garfunkel::PProduct>  (new Garfunkel::PProduct(productid, eP2Product, -1));
									 if(pinfo)
									 {
										 // TODO : Get P Block properties here
										 _product[eP2Product]= pinfo;
									 }

								}
								break;

								case eO1Product:
								{
									//create 2 1 for each O capsule with same id
									boost::shared_ptr< Garfunkel::ProductInfo>  pinfo1 = boost::shared_ptr<Garfunkel::OProduct>  (new Garfunkel::OProduct(productid, eO1Product, -1));
									if(pinfo1)
									{
										// TODO : Get O capsule properties here
										 _product[eO1Product]= pinfo1;
									}

								}
								break;

								case eO2Product:
								{
									//create 2 1 for each O capsule with same id
									boost::shared_ptr< Garfunkel::ProductInfo>  pinfo2 = boost::shared_ptr<Garfunkel::OProduct>  (new Garfunkel::OProduct(productid, eO2Product, -1));
									if(pinfo2)
									{
										_product[eO2Product]= pinfo2;
									}

								}
								break;


							}


						}

						else
					    {
						    std::cout << "[DB] ERROR ProductInfo returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
					    }

				    }


					if(x == numRows)
					retValue = True;
	            }

				else
				{
					std::cout << "[DB] ERROR ProductInfo returned " << dataSet.GetNumberOfRows() << " rows. Expected More." << std::endl;
				}
			}
			else
			{
				std::cout << "[DB] ERROR: Execute the stored procedure GetProductInfo." << std::endl;
			}
	    }
	    else
	    {
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}


		if (retValue)
		{
	        /*
	            Write the machine data to a flat file.
	        */
			//now set flag
			_initDone = True;
			std::cout << "Init for productdata Done!" << std::endl;
		}
		else
	    {
		    /*
		        Database machine data are not available.
		        Read the machine data fom the flat file.
		    */
			std::cout << "Read product data values from a flat file" << std::endl;
			//ReadProductDataFromFile();
			_initDone = True;
	    }

	    myDBAccess.DBDisconnect();
	    return retValue;
}



BOOLEAN Garfunkel::ProductData::ReadSProductPropertiesFromDatabase()
{
   //Do initalize _ProductInfo map, for all the  products from db
		ecolab::ScopeLock Lock(_productLock);

		ecolab::DB::DBAccess    myDBAccess;
	    std::string             connectString;
	    BOOLEAN                 retValue = False;

	    // Use of the connection string.
	    connectString = "dbname = 'Garfunkel' user = 'db_user_admin' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

	        ecolab::DB::DataSet        dataSet;
	        std::string                sql;
//	        sql = "SELECT * FROM \"ProductInfo\"";
	        std::stringstream strstream;
	        strstream<<"SELECT * FROM GetSBlockProductProperties();"; //read all products for the given locale
	        sql = strstream.str();
	        std::cout << "Trying to execute " << sql << std::endl;
	        if(myDBAccess.DBExecuteStored(sql, dataSet))
	        {

	        	std::cout << "Execution of " << sql << std::endl;

	           if(dataSet.GetNumberOfRows()==1)
	            {
					ecolab::DB::DataRow 						rowData;
	        	   	boost::shared_ptr<ecolab::DB::IColumnData>    colData;
					std::string									colDataAsString;
					int		numRows = 0;
					int		x = 0;
					typedef boost::bimap< int, int > bm_type;

					numRows = dataSet.GetNumberOfRows();
					std::cout << "GetSProductInfo No Of rows : " << numRows << std::endl;

					rowData = dataSet.GetRow(0);
					if(rowData.GetNumberOfColumns() > 0)
					{

						INT32     productid, name  = -1;
		                REAL64    RealValue = 0.0;
		                BOOLEAN   IsInUse = False;

		                colData = rowData.GetColumn("ProductID");
		                if(colData.get() != NULL)
						{
		                	colData->AsInt(productid);
		                	std::cout << "ProductID: " << productid << std::endl;
						}
		                colData = rowData.GetColumn("IsInUse");
		                if (colData.get() != NULL)
		                {
		                	colData->AsBool(IsInUse);
		                	std::cout << "IsInUse: " << IsInUse << std::endl;
		                }
		                colData = rowData.GetColumn("PercentSO3InBlock");
		                if (colData.get() != NULL)
		                {
		                	colData->AsFloat(RealValue);
		                	std::cout << "PercentSO3InBlock: " << RealValue << std::endl;
		                }

		                if(_product.count(eSProduct) > 0)
		                {
		                	//TODO, check if you want to do downcasting (static/dynamic/shared_polymorphic_downcast ) http://stackoverflow.com/questions/1358143/downcasting-shared-ptrbase-to-shared-ptrderived
		                	boost::shared_ptr< Garfunkel::SProduct>  pinfo = boost::static_pointer_cast <Garfunkel::SProduct> (_product[eSProduct]);
		                	if(pinfo)
		                	{
		                		pinfo->IsInUse.Set(IsInUse);
		                		pinfo->PercentSO3InBlock.Set(RealValue);
		                		retValue = True;
		                	}
		                }
					}

					else
					{
						std::cout << "[DB] ERROR ProductInfo returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
					}

	            }
				else
				{
					std::cout << "[DB] ERROR ProductInfo returned " << dataSet.GetNumberOfRows() << " rows. Expected just One." << std::endl;
				}
			}
			else
			{
				std::cout << "[DB] ERROR: Execute the stored procedure GetProductInfo." << std::endl;
			}
	    }
	    else
	    {
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}


		if (retValue)
		{
			//TODO flat file for S Block properties

			std::cout << "Init for productdata Done!" << std::endl;
		}
		else
	    {
			std::cout << "Read product data values from a flat file" << std::endl;
			//TODO Read from flat file for S Block properties
			//ReadProductDataFromFile();
	    }

	    myDBAccess.DBDisconnect();
	    return retValue;
}


BOOLEAN Garfunkel::ProductData::ReadPProductPropertiesFromDatabase()
{
   //Do initalize _ProductInfo map, for all the  products from db
		ecolab::ScopeLock Lock(_productLock);

		ecolab::DB::DBAccess    myDBAccess;
	    std::string             connectString;
	    BOOLEAN                 retValue = False;

	    // Use of the connection string.
	    connectString = "dbname = 'Garfunkel' user = 'db_user_admin' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

	        ecolab::DB::DataSet        dataSet;
	        std::string                sql;
//	        sql = "SELECT * FROM \"ProductInfo\"";
	        std::stringstream strstream;
	        strstream<<"SELECT * FROM GetPBlockProductProperties();"; //read all products for the given locale
	        sql = strstream.str();
	        std::cout << "Trying to execute " << sql << std::endl;
	        if(myDBAccess.DBExecuteStored(sql, dataSet))
	        {

	        	std::cout << "Execution of " << sql << std::endl;

	           if(dataSet.GetNumberOfRows()==1)
	            {
					ecolab::DB::DataRow 						rowData;
	        	   	boost::shared_ptr<ecolab::DB::IColumnData>    colData;
					std::string									colDataAsString;
					int		numRows = 0;
					int		x = 0;
					typedef boost::bimap< int, int > bm_type;

					numRows = dataSet.GetNumberOfRows();
					std::cout << "GetPProductInfo No Of rows : " << numRows << std::endl;

					rowData = dataSet.GetRow(0);
					if(rowData.GetNumberOfColumns() > 0)
					{

						INT32     productid, name  = -1;
		                REAL64    RealValue = 0.0;
		                BOOLEAN   IsInUse = False;

		                colData = rowData.GetColumn("ProductID");
		                if(colData.get() != NULL)
						{
		                	colData->AsInt(productid);
		                	std::cout << "ProductID: " << productid << std::endl;
						}
		                /* TODO
		                 * colData = rowData.GetColumn("IsInUse");
		                if (colData.get() != NULL)
		                {
		                	colData->AsBool(IsInUse);
		                	std::cout << "IsInUse: " << IsInUse << std::endl;
		                }
		                colData = rowData.GetColumn("PercentSO3InBlock");
		                if (colData.get() != NULL)
		                {
		                	colData->AsFloat(RealValue);
		                	std::cout << "PercentSO3InBlock: " << RealValue << std::endl;
		                }*/

		                if(_product.count(eP2Product) > 0)
		                {
		                	boost::shared_ptr< Garfunkel::PProduct>  pinfo = boost::static_pointer_cast<Garfunkel::PProduct> (_product[eP2Product]);
		                	if(pinfo)
		                	{
		                		//TODO
		                		//pinfo->IsInUse.Set(IsInUse);

		                		retValue = True;
		                	}
		                }
					}

					else
					{
						std::cout << "[DB] ERROR ProductInfo returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
					}

	            }
				else
				{
					std::cout << "[DB] ERROR ProductInfo returned " << dataSet.GetNumberOfRows() << " rows. Expected just One." << std::endl;
				}
			}
			else
			{
				std::cout << "[DB] ERROR: Execute the stored procedure GetProductInfo." << std::endl;
			}
	    }
	    else
	    {
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}


		if (retValue)
		{
			//TODO flat file for S Block properties

			std::cout << "Init for productdata Done!" << std::endl;
		}
		else
	    {
			std::cout << "Read product data values from a flat file" << std::endl;
			//TODO Read from flat file for S Block properties
			//ReadProductDataFromFile();
	    }

	    myDBAccess.DBDisconnect();
	    return retValue;
}




BOOLEAN Garfunkel::ProductData::ReadOProductPropertiesFromDatabase()
{
   //Do initalize _ProductInfo map, for all the  products from db
		ecolab::ScopeLock Lock(_productLock);

		ecolab::DB::DBAccess    myDBAccess;
	    std::string             connectString;
	    BOOLEAN                 retValue = False;

	    // Use of the connection string.
	    connectString = "dbname = 'Garfunkel' user = 'db_user_admin' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

	        ecolab::DB::DataSet        dataSet;
	        std::string                sql;
	        std::stringstream strstream;
	        strstream<<"SELECT * FROM GetOCapsuleProductProperties();"; //read all products for the given locale
	        sql = strstream.str();
	        std::cout << "Trying to execute " << sql << std::endl;
	        if(myDBAccess.DBExecuteStored(sql, dataSet))
	        {

	        	std::cout << "Execution of " << sql << std::endl;

	           if(dataSet.GetNumberOfRows()==1)
	            {
					ecolab::DB::DataRow 						rowData;
	        	   	boost::shared_ptr<ecolab::DB::IColumnData>    colData;
					std::string									colDataAsString;
					int		numRows = 0;
					int		x = 0;
					typedef boost::bimap< int, int > bm_type;

					numRows = dataSet.GetNumberOfRows();
					std::cout << "GetPProductInfo No Of rows : " << numRows << std::endl;

					rowData = dataSet.GetRow(0);
					if(rowData.GetNumberOfColumns() > 0)
					{

						INT32     productid, name  = -1;
		                REAL64    RealValue = 0.0;
		                BOOLEAN   IsInUse = False;

		                colData = rowData.GetColumn("ProductID");
		                if(colData.get() != NULL)
						{
		                	colData->AsInt(productid);
		                	std::cout << "ProductID: " << productid << std::endl;
						}
		                colData = rowData.GetColumn("PercentNaOHInProduct");
		                if (colData.get() != NULL)
		                {
		                	colData->AsFloat(RealValue);
		                	std::cout << "PercentNaOHInProduct: " << RealValue << std::endl;
		                }

		                if(_product.count(eO1Product) > 0 && _product.count(eO2Product) > 0 )
		                {
		                	boost::shared_ptr< Garfunkel::OProduct>  o1 = boost::static_pointer_cast<Garfunkel::OProduct> (_product[eO1Product]);
		                	boost::shared_ptr< Garfunkel::OProduct>  o2 = boost::static_pointer_cast<Garfunkel::OProduct> (_product[eO2Product]);
		                	if(o1&&o2)
		                	{
		                		o1->PercentNaOHInProduct.Set(RealValue);
		                		o2->PercentNaOHInProduct.Set(RealValue);
		                		retValue = True;
		                	}
		                }
					}

					else
					{
						std::cout << "[DB] ERROR ProductInfo returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
					}

	            }
				else
				{
					std::cout << "[DB] ERROR ProductInfo returned " << dataSet.GetNumberOfRows() << " rows. Expected just One." << std::endl;
				}
			}
			else
			{
				std::cout << "[DB] ERROR: Execute the stored procedure GetProductInfo." << std::endl;
			}
	    }
	    else
	    {
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}


		if (retValue)
		{
			//TODO flat file for O properties

			std::cout << "Init for productdata Done!" << std::endl;
		}
		else
	    {
			std::cout << "Read product data values from a flat file" << std::endl;
			//TODO Read from flat file for O properties
			//ReadProductDataFromFile();
	    }

	    myDBAccess.DBDisconnect();
	    return retValue;
}


BOOLEAN Garfunkel::ProductData::ReadProductPulseDataFromDatabase()
{
		ecolab::ScopeLock Lock(_productLock);

		ecolab::DB::DBAccess    myDBAccess;
	    std::string             connectString;
	    BOOLEAN                 retValue = False;

	    // Use of the connection string.
	    connectString = "dbname = 'Garfunkel' user = 'db_user_admin' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

			/*Remove any previous data*/

	    	for(std::map<int, boost::shared_ptr< Garfunkel::ProductPulseInfo > >::iterator piter = _productPulseCriteria.begin(); piter!= _productPulseCriteria.end(); piter++)
	    	{
	    		boost::shared_ptr< Garfunkel::ProductPulseInfo > pulseCriteria = piter->second;

	    		if(pulseCriteria)
	    		{
	    			pulseCriteria->_productPulseInfo.erase(pulseCriteria->_productPulseInfo.begin(), pulseCriteria->_productPulseInfo.end());
	    		}

	    	}
	    	if(_productPulseCriteria.size() > 0)
			{
				_productPulseCriteria.erase(_productPulseCriteria.begin(), _productPulseCriteria.end());
			}

			for(std::map<GarfunkelProductType, boost::shared_ptr< Garfunkel::ProductInfo > >  ::const_iterator iter = _product.begin(); iter!= _product.end(); iter++)
			{
				int productId = iter->first;
	    		ecolab::DB::DataSet        dataSet;
	    		std::string                sql;
	    		std::stringstream strstream;
	    		strstream<<"SELECT * FROM GetProductPulseInfo('"<<productId<<"');";
	    		sql = strstream.str();
        		std::cout << "Trying to execute " << sql << std::endl;
	    		if(myDBAccess.DBExecuteStored(sql, dataSet))
	    		{

	    			std::cout << "Execution of " << sql << std::endl;

	    			if(dataSet.GetNumberOfRows() > 0)
	    			{
	    				ecolab::DB::DataRow 						rowData;
	    				boost::shared_ptr<ecolab::DB::IColumnData>    colData;
	    				std::string									colDataAsString;
	    				int		numRows = 0;
	    				int		x = 0;
	    				typedef boost::bimap< int, int > bm_type;

	    				numRows = dataSet.GetNumberOfRows();
	    				std::cout << "GetProductPulseInfo : No Of rows : " << numRows << std::endl;

						 boost::shared_ptr< Garfunkel::ProductPulseInfo > pinfo =  boost::shared_ptr< Garfunkel::ProductPulseInfo >  (new Garfunkel::ProductPulseInfo);

	    				for( ; x < numRows; x++)
	    				{

	    					rowData = dataSet.GetRow(x);

	    					if(rowData.GetNumberOfColumns() > 0)
	    					{

	    						INT32     IntValue  = -1;
	    						REAL64    RealValue = 0.0;
	    						BOOLEAN   BoolValue = False;
	    						std::string status;
	    						std::string StringValue;
	    						 boost::shared_ptr< Garfunkel::ProductPulseCriteria > pulseCriteria =  boost::shared_ptr< Garfunkel::ProductPulseCriteria >  (new Garfunkel::ProductPulseCriteria);

	    						if(pulseCriteria.get() != NULL)
	    						{
	    							colData = rowData.GetColumn("ProductID");

	    							if(colData.get() != NULL)
	    							{
	    								colData->AsInt(IntValue);
	    								//pulseinfo->ProductId.Set(IntValue);
	    								//std::cout << "ProductID: " <<IntValue<<std::endl;
	    							}
	    							colData = rowData.GetColumn("FromTempThreshold");
	    							if(colData.get() != NULL)
	    							{
	    								colData->AsFloat(RealValue);
	    								pulseCriteria->FromTemp.Set(RealValue);
	    							}

	    							colData = rowData.GetColumn("ToTempThreshold");
	    							if(colData.get() != NULL)
	    							{
	    								colData->AsFloat(RealValue);
	    								pulseCriteria->ToTemp.Set(RealValue);
	    							}

	    							colData = rowData.GetColumn("AmountInGrams");
	    							if(colData.get() != NULL)
	    							{
	    								colData->AsFloat(RealValue);
	    								pulseCriteria->PulseAmount.Set(RealValue);
	    							}

	    							colData = rowData.GetColumn("PulseOnTimeInSec");

	    							if(colData.get() != NULL)
	    							{
	    								colData->AsInt(IntValue);
	    								pulseCriteria->PulseOnTime.Set(IntValue);
	    							}

	    							colData = rowData.GetColumn("PulseOffTimeInSec");

	    							if(colData.get() != NULL)
	    							{
	    								colData->AsInt(IntValue);
	    								pulseCriteria->PulseOffTime.Set(IntValue);
	    							}

	    							colData = rowData.GetColumn("MaxNoOfPulses");

	    							if(colData.get() != NULL)
	    							{
	    								colData->AsInt(IntValue);
	    								pulseCriteria->MaxNoOfPulses.Set(IntValue);
	    							}

	    							colData = rowData.GetColumn("PercentageTarget");
	    							if(colData.get() != NULL)
	    							{
	    								colData->AsFloat(RealValue);
	    								pulseCriteria->PercentageTarget.Set(RealValue);
	    							}

	    							pinfo->_productPulseInfo.push_back(pulseCriteria);
	    						}
	    					}

	    					else
	    					{
	    						std::cout << "[DB] ERROR GetProductPulseInfo returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
	    					}

	    				}

	    				if(x>0&&x == numRows)
	    				{
	    					_productPulseCriteria.insert(std::map<int, boost::shared_ptr< Garfunkel::ProductPulseInfo > >::value_type(productId, pinfo));
	    					std::cout<<"Pulse info added for productId= "<<productId<<std::endl;
	    				}
	    			}

	    			else
	    			{
	    				std::cout << "[DB] ERROR GetProductPulseInfo returned " << dataSet.GetNumberOfRows() << " rows. Expected More." << std::endl;
	    			}
	    		}
	    		else
	    		{
	    			std::cout << "[DB] ERROR: Execute the stored procedure GetProductPulseInfo." << std::endl;
	    		}
	    	}

			retValue = True;


	    }
	    else
	    {
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}



	    if (retValue)
		{
	        /*
	            Write the machine data to a flat file.
	        */
			WriteProductPulseDataToFile();
			//now set flag
			std::cout << "Init Done!" << std::endl;
		}
		else
	    {
		    /*
		        Database machine data are not available.
		        Read the machine data fom the flat file.
		    */
			std::cout << "Read product pulse data values from a flat file" << std::endl;
			retValue = ReadProductPulseDataFromFile();
	    }

	    myDBAccess.DBDisconnect();
	    return retValue;

}


/////////////////////////////////////////////////////////////////
/////
/////OOPState
//////////////////////////////////////////////////////////////////
Garfunkel::OOPState::OOPState()
{
	OOP_State.Set(eProductFull);
	OOPAlarmAlreadyDetected.Set(False);
	IsAlarmMuted.Set(False);
	memset(&_lastMutedTime, 0, sizeof(timespec));
	memset(&_alarmActivatedTime, 0, sizeof(timespec));
	AlarmMuteCount.Set(0);

}

Garfunkel::OOPState::OOPState(const Garfunkel::OOPState & objectToCopy)
{
}

Garfunkel::OOPState::~OOPState()
{
}


void Garfunkel::OOPState::ResetOOPDetectState()
{
	OOPAlarmAlreadyDetected.Set(False); //raises product empty alarm
	IsAlarmMuted.Set(False); //unmute it
	AlarmMuteCount.Set(0);  //reset mute count
}

timespec Garfunkel::OOPState::GetLastAlarmMuteTimeTime()
{
	ecolab::ScopeLock Lock(_lastMutedTimeDataLock);
	return _lastMutedTime;
}

void Garfunkel::OOPState::UpdateLastAlarmMuteTime()
{
	ecolab::ScopeLock Lock(_lastMutedTimeDataLock);
	clock_gettime(CLOCK_MONOTONIC, &_lastMutedTime);
}

timespec Garfunkel::OOPState::GetAlarmActivatedTimeTime()
{
	ecolab::ScopeLock Lock(_alarmActivatedTimeDataLock);
	return _alarmActivatedTime;
}

void Garfunkel::OOPState::UpdateAlarmActivatedTime()
{
	ecolab::ScopeLock Lock(_alarmActivatedTimeDataLock);
	clock_gettime(CLOCK_MONOTONIC, &_alarmActivatedTime);
}






/////////////////////////////////////////////////////////////////
/////
/////PocketInfo
//////////////////////////////////////////////////////////////////
Garfunkel::PocketInfo::PocketInfo() : OOPState()
{
	PocketId.Set(eUndefinedPocket);

}

Garfunkel::PocketInfo::PocketInfo(const Garfunkel::PocketInfo & objectToCopy)
{
}

Garfunkel::PocketInfo::~PocketInfo()
{
}





//////////////////////////////////////////////////////////////////
///
/// PocketInfoData
//////////////////////////////////////////////////////

BOOLEAN Garfunkel::PocketInfoData::_initDone = False;
Garfunkel::PocketInfoData::PocketInfoData()
{

}

Garfunkel::PocketInfoData::PocketInfoData(const Garfunkel::PocketInfoData & objectToCopy)
{
}

Garfunkel::PocketInfoData::~PocketInfoData()
{
	ecolab::ScopeLock Lock(_pocketLock);

    if(_pocket.size() > 0)
	{
    	_pocket.erase(_pocket.begin(), _pocket.end());
	}
}


Garfunkel::PocketInfoData&  Garfunkel::PocketInfoData::Instance()
{
    static PocketInfoData  singleton;
	if(!_initDone)
	singleton.Initailize();
    return singleton;
}


boost::shared_ptr< Garfunkel::PocketInfo> Garfunkel::PocketInfoData::GetContextForPocket(int PocketId)
{
	ecolab::ScopeLock Lock(_pocketLock);
	boost::shared_ptr<Garfunkel::PocketInfo>  pdata;
	std::map<int, boost::shared_ptr<Garfunkel::PocketInfo> > ::const_iterator iter;
	pdata.reset();
	iter = _pocket.find(PocketId);
	if(iter!=_pocket.end())
	return iter->second;
	else
	{
		std::cout<<"ERROR: GetContextForPocket NOT found for PocketId="<<PocketId<<std::endl;
		return pdata;
	}

}



void Garfunkel::PocketInfoData::Initailize()
{
   //Do initalize _PumpInfo map, for all the availabe pumps from db
	ecolab::ScopeLock Lock(_pocketLock);
	if(_initDone==True)
	return;
#if 0
	TODO
	for(int i = (int)eDetergentPocket ; i < (int)eMaxSolidProducts ; i++)
	{
		boost::shared_ptr< Garfunkel::PocketInfo>  pinfo = boost::shared_ptr<Garfunkel::PocketInfo>  (new Garfunkel::PocketInfo);
		if(pinfo)
		{
			pinfo->PocketId.Set((GarfunkelProductPocket)i);
			_pocket[i]= pinfo;
		}
	}
#endif
   _initDone = True;

}

/*!
    \brief  Read the pump data from a flatfile
BOOLEAN Garfunkel::ProductData::ReadProductDataFromFile()
{
    BOOLEAN retValue = False;
    int NoOfProducts = 0;

    std::fstream    valuesRead("/usr/local/applications/Garfunkel-productdata.txt", std::ios_base::in );

    if(True == valuesRead.is_open())
    {
        int          IntValue;
        std::string  StringValue;
        float         RealValue;

        valuesRead >> IntValue;
        NoOfProducts = IntValue;

        if(NoOfProducts > 0)
        {


		    if(_product.size() > 0)
			{
		    	_product.erase(_product.begin(),_product.end());
			}

		    for(int i=0; i<NoOfProducts; i++)
		    {
				boost::shared_ptr< Garfunkel::ProductInfo>  pinfo = boost::shared_ptr<Garfunkel::ProductInfo>  (new Garfunkel::ProductInfo);
				if(pinfo.get() != NULL)
				{
		        	valuesRead >> IntValue; //ProductID
					pinfo->ProductId.Set(IntValue);

					valuesRead >> IntValue;
					pinfo->ProductType.Set((GarfunkelProductType)IntValue);

					valuesRead >> IntValue; //StatusCode
					pinfo->IsProductValid.Set((BOOLEAN)IntValue);

					valuesRead >> IntValue; //ProductState
					pinfo->ProductState.Set((GarfunkelProductPhysicalState)IntValue);

					valuesRead >> StringValue; //ProductState
					pinfo->ProductFactor.assign(StringValue);
					StringValue.assign("");

					valuesRead >> IntValue; //IsLockedProduct
					pinfo->IsLockedProduct.Set((BOOLEAN)IntValue);

					valuesRead >> RealValue; //AmountPerKg
					pinfo->AmountPerKg.Set(RealValue);

					valuesRead >> RealValue; //AmountPerKg
					pinfo->ProductDispenseRate.Set(RealValue);

					_product[pinfo->ProductId.Get()]= pinfo;  //this will overwrite if it already there or else will create new one
				}
		    }
        }

        valuesRead.close();
        retValue = True;
    }
    else
    {
        std::cout << "ERROR: Can't open Garfunkel-productdata.txt." << std::endl;
    }

    return retValue;
}

/*!
    \brief  Persist the product data to a flatfile

*/
BOOLEAN Garfunkel::ProductData::WriteProductDataToFile()
{

    BOOLEAN         retValue = False;
    std::map<GarfunkelProductType, boost::shared_ptr< Garfunkel::ProductInfo> >::const_iterator iter , iend ;
    boost::shared_ptr< Garfunkel::ProductInfo> pinfo;

    std::fstream    valuesWrite("/usr/local/applications/Garfunkel-productdata.txt", std::ios_base::trunc | std::ios_base::out);

    if(True == valuesWrite.is_open())
    {

        int          IntValue;
        REAL64       RealValue;
        BOOLEAN      BoolValue;
        std::string  StringValue;
    	IntValue = _product.size();                    //First write number of products
    	valuesWrite << IntValue << std::endl;

        for(iter = _product.begin(), iend =_product.end(); iter!=iend; iter++)
        {

        	pinfo =  (boost::shared_ptr< Garfunkel::ProductInfo>) (iter->second);
        	if(pinfo.get() != NULL)
        	{
        		IntValue = pinfo->GetProductID();
        		valuesWrite << IntValue << std::endl;

        		IntValue =   pinfo->GetProductType();
        		valuesWrite << IntValue << std::endl;

        		IntValue =   pinfo->GetNozzleTypeRefID();
        		valuesWrite << IntValue << std::endl;


        	}


        }

        valuesWrite.close();
        retValue = True;
    }


    return retValue;
}


/*!
    \brief  Read the product data from a flatfile

*/
BOOLEAN Garfunkel::ProductData::ReadProductPulseDataFromFile()
{
    BOOLEAN retValue = False;
    int NoOfProducts = 0;

    std::fstream    valuesRead("/usr/local/applications/Garfunkel-productpulsedata.txt", std::ios_base::in );

    if(True == valuesRead.is_open())
    {
        int          IntValue;
        std::string  StringValue;
        float         RealValue;
		int NoOfItems=0;

        valuesRead >> IntValue;
        NoOfProducts = IntValue;

        if(NoOfProducts > 0)
        {
			/*Delete any previous data*/
		    if(_productPulseCriteria.size() > 0)
			{
		    	_productPulseCriteria.erase(_productPulseCriteria.begin(),_productPulseCriteria.end());
			}

		    for(int i=0; i<NoOfProducts; i++)
		    {
				boost::shared_ptr< Garfunkel::ProductPulseInfo>  pinfo = boost::shared_ptr< Garfunkel::ProductPulseInfo>  (new Garfunkel::ProductPulseInfo);
				if(pinfo.get() != NULL)
				{
		        	valuesRead >> IntValue; //ProductID
					pinfo->ProductId.Set(IntValue);

					valuesRead >> IntValue;
					NoOfItems = IntValue;

					if(NoOfItems>0)
					{
						for(int j=0; j<NoOfItems; j++)
						{
							boost::shared_ptr< Garfunkel::ProductPulseCriteria > pulseinfo =  boost::shared_ptr< Garfunkel::ProductPulseCriteria >  (new Garfunkel::ProductPulseCriteria);
							if(pulseinfo)
							{
								valuesRead >> RealValue;
								pulseinfo->FromTemp.Set(RealValue);

								valuesRead >> RealValue;
								pulseinfo->ToTemp.Set(RealValue);

								valuesRead >> RealValue;
								pulseinfo->PulseAmount.Set(RealValue);

								valuesRead >> IntValue;
								pulseinfo->PulseOnTime.Set(IntValue);

								valuesRead >> IntValue;
								pulseinfo->PulseOffTime.Set(IntValue);

								valuesRead >> IntValue;
								pulseinfo->MaxNoOfPulses.Set(IntValue);

								valuesRead >> RealValue;
								pulseinfo->PercentageTarget.Set(RealValue);

								pinfo->_productPulseInfo.push_back(pulseinfo);
							}
						}

						_productPulseCriteria.insert(std::map<int, boost::shared_ptr< Garfunkel::ProductPulseInfo > >::value_type(pinfo->ProductId.Get(), pinfo));
					}
				}
		    }
        }

        valuesRead.close();
        retValue = True;
    }
    else
    {
        std::cout << "ERROR: Can't open Garfunkel-productdata.txt." << std::endl;
    }

    return retValue;
}


/*!
    \brief  Persist the product data to a flatfile

*/
BOOLEAN Garfunkel::ProductData::WriteProductPulseDataToFile()
{

    BOOLEAN         retValue = False;
    std::map<int, boost::shared_ptr< Garfunkel::ProductPulseInfo > >::const_iterator iter, iend ;
    boost::shared_ptr< Garfunkel::ProductPulseInfo> pinfo;
    boost::shared_ptr<Garfunkel::ProductPulseCriteria> pdata;
    std::fstream    valuesWrite("/usr/local/applications/Garfunkel-productpulsedata.txt", std::ios_base::trunc | std::ios_base::out);

    if(True == valuesWrite.is_open())
    {

        int          IntValue;
        REAL64       RealValue;
        BOOLEAN      BoolValue;
        std::string  StringValue;
    	IntValue = _productPulseCriteria.size();                    //First write number of products
    	valuesWrite << IntValue << std::endl;

        for(iter = _productPulseCriteria.begin(), iend =_productPulseCriteria.end(); iter!=iend; iter++)
        {

        	pinfo =  (boost::shared_ptr< Garfunkel::ProductPulseInfo>) (iter->second);
        	if(pinfo.get() != NULL)
        	{
        		IntValue = pinfo->ProductId.Get();
        		valuesWrite << IntValue << std::endl;

        		IntValue = pinfo->_productPulseInfo.size();
        		valuesWrite << IntValue << std::endl;

        		if(IntValue>0)
        		{
        			std::vector<boost::shared_ptr<Garfunkel::ProductPulseCriteria> >::const_iterator piter;

        			for(piter=pinfo->_productPulseInfo.begin(); piter!=pinfo->_productPulseInfo.end(); piter++)
        			{
        				pdata = *piter;
        				if(pdata)
        				{
        					RealValue = pdata->FromTemp.Get();
        					valuesWrite << RealValue << std::endl;

        					RealValue = pdata->ToTemp.Get();
        					valuesWrite << RealValue << std::endl;

        					RealValue = pdata->PulseAmount.Get();
        					valuesWrite << RealValue << std::endl;

        					IntValue = pdata->PulseOnTime.Get();
			        		valuesWrite << IntValue << std::endl;

        					IntValue = pdata->PulseOffTime.Get();
			        		valuesWrite << IntValue << std::endl;

        					IntValue = pdata->MaxNoOfPulses.Get();
			        		valuesWrite << IntValue << std::endl;

        					RealValue = pdata->PercentageTarget.Get();
        					valuesWrite << RealValue << std::endl;

        				}

        			}

        		}

        	}


        }

        valuesWrite.close();
        retValue = True;
    }


    return retValue;
}



-- stored procedures
--

DROP TYPE IF EXISTS MappedProducts CASCADE;
CREATE TYPE MappedProducts AS (ProductID integer, ProductName integer, ProductSlotID integer, ProductSlotType integer, NozzleTypeRefID integer, runTime integer, StatusCode character(1) );
ALTER TYPE MappedProducts OWNER TO db_user_admin;

DROP VIEW IF EXISTS "Products" CASCADE;
CREATE VIEW "Products"
AS
SELECT  "ProductID", "ProductSlotID"
FROM    "ProductMapping"
INNER JOIN 
		"SystemData" 
	ON "ProductMapping"."RegionID"="SystemData"."RegionID" 
WHERE   ("ProductSlotID" <> 4);
ALTER VIEW "Products" OWNER TO db_user_admin;

/*CREATE OR REPLACE FUNCTION GetProgrammedProducts(PrRefId integer) RETURNS SETOF MappedProducts AS $$
SELECT 	"ProductInfo"."ProductID", 
		"ProductInfo"."ProductName", 
		"ProductInfo"."StatusCode"
FROM 	"ProductInfo" 
	INNER JOIN 
		"SystemData" 
	ON "ProductInfo"."RegionID"="SystemData"."RegionID" 
	INNER JOIN 
		"Products" 
	ON "ProductInfo"."ProductID"="Products"."ProductID" 
	WHERE "Products"."ProductSlotID"=$1
ORDER BY "ProductInfo"."ProductID" ASC;
$$ LANGUAGE SQL;
ALTER FUNCTION GetProgrammedProducts(integer) OWNER TO db_user_admin;*/

CREATE OR REPLACE FUNCTION GetAllProgrammedProducts() RETURNS SETOF MappedProducts AS $$
SELECT 	"ProductInfo"."ProductID", 
		"ProductInfo"."ProductName", 
		"Products"."ProductSlotID", 
		"ProductSlot"."ProductSlotType",
		"ProductSlot"."NozzleTypeRefID",
		"ProductSlot"."RunTime",
		"ProductInfo"."StatusCode"
FROM 	"ProductInfo" 
	INNER JOIN 
		"SystemData" 
	ON "ProductInfo"."RegionID"="SystemData"."RegionID" 
	INNER JOIN 
		"Products" 
	ON "ProductInfo"."ProductID"="Products"."ProductID" 
	INNER JOIN 
		"ProductSlot"
	ON "ProductSlot"."ProductSlotID" = "Products"."ProductSlotID" 
ORDER BY "Products"."ProductSlotID" ASC;
$$ LANGUAGE SQL;
ALTER FUNCTION GetAllProgrammedProducts() OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetScheduleData() RETURNS SETOF "OperatingSchedule" AS $$
SELECT 	* FROM 	"OperatingSchedule" ORDER BY "OperatingScheduleRefID", "DayOfTheWeek", "StartHour";
$$ LANGUAGE SQL;
ALTER FUNCTION GetScheduleData() OWNER TO db_user_admin;
 
CREATE OR REPLACE FUNCTION GetScheduleSpecificPropertiesForSchedule(id integer) RETURNS SETOF "ScheduleSpecificProperties" AS $$
SELECT 	* FROM 	"ScheduleSpecificProperties" WHERE "OperatingScheduleRefID"=$1;
$$ LANGUAGE SQL;
ALTER FUNCTION GetScheduleSpecificPropertiesForSchedule(integer) OWNER TO db_user_admin;

DROP TYPE IF EXISTS ProductConProducts CASCADE;
CREATE TYPE ProductConProducts AS (OperatingScheduleRefId integer, ProductSlotID integer, ProductID integer, Conc real);
ALTER TYPE ProductConProducts OWNER TO db_user_admin;

/*CREATE OR REPLACE FUNCTION ProductConcentrationForSpray() RETURNS SETOF  ProductConProducts AS $$
SELECT 	"OperatingScheduleRefID", "Products"."ProductSlotID", "ProductConcentrationForSpray"."ProductID", "ProductConcentrationForSpray"."ProdConc"
FROM 	"ProductConcentrationForSpray"
	INNER JOIN 
		"SystemData" 
	ON "ProductConcentrationForSpray"."RegionID"="SystemData"."RegionID" 
	INNER JOIN 
		"Products" 
	ON "ProductConcentrationForSpray"."ProductID"="Products"."ProductID" 
	ORDER BY "Products"."ProductSlotID" ASC;
$$ LANGUAGE SQL;
ALTER FUNCTION ProductConcentrationForSpray() OWNER TO db_user_admin;*/


CREATE OR REPLACE FUNCTION GetSBlockProductProperties() RETURNS SETOF "SBlockProductProperties"  AS $$
DECLARE
	RegionID int;
	productId int;
	returnedData "SBlockProductProperties"%rowtype;
BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=0;
	IF ( FOUND = true ) THEN
	    FOR returnedData IN SELECT * FROM  "SBlockProductProperties"  SB
        WHERE SB."RegionID"=RegionID AND SB."ProductID"=productId
                LOOP
                        RETURN NEXT returnedData;
                END LOOP;
    RETURN;
	END IF;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetSBlockProductProperties() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetSBlockScheduleSpecificConcProperties() RETURNS SETOF "ProductConcentrationForSpray"  AS $$
DECLARE	
	RegionID int;
	productId int;
	returnedData "ProductConcentrationForSpray"%rowtype;
BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=0;
	IF ( FOUND = true ) THEN
	FOR returnedData IN SELECT * FROM  "ProductConcentrationForSpray"  SB
	WHERE SB."RegionID"=RegionID AND SB."ProductID"=productId
		LOOP                        
		RETURN NEXT returnedData;
		END LOOP;
		RETURN;
	END IF;
	END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetSBlockScheduleSpecificConcProperties() OWNER TO db_user_admin;
 
CREATE OR REPLACE FUNCTION GetPBlockProductProperties() RETURNS SETOF "PBlockProductProperties"  AS $$
DECLARE
	RegionID int;
	productId int;
	returnedData "PBlockProductProperties"%rowtype;
BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=1;
	IF ( FOUND = true ) THEN
	    FOR returnedData IN SELECT * FROM  "PBlockProductProperties"  HB
        WHERE HB."RegionID"=RegionID AND HB."ProductID"=productId
                LOOP
                        RETURN NEXT returnedData;
                END LOOP;
    RETURN;
	END IF;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetPBlockProductProperties() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetPBlockScheduleSpecificConcProperties() RETURNS SETOF "ProductConcentrationForSpray"  AS $$
DECLARE
	RegionID int;
	productId int;
	returnedData "ProductConcentrationForSpray"%rowtype;
	BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=1;
	IF ( FOUND = true ) THEN
	FOR returnedData IN SELECT * FROM  "ProductConcentrationForSpray"  SB
	WHERE SB."RegionID"=RegionID AND SB."ProductID"=productId
	LOOP
		RETURN NEXT returnedData;
		END LOOP;
		RETURN;
		END IF;
	END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetPBlockScheduleSpecificConcProperties() OWNER TO db_user_admin; 

CREATE OR REPLACE FUNCTION GetOCapsuleProductProperties() RETURNS SETOF "OCapsuleProductProperties"  AS $$
DECLARE
	RegionID int;
	productId int;
	returnedData "OCapsuleProductProperties"%rowtype;
BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=2; --or 3 for O2, both will give same product id
	IF ( FOUND = true ) THEN
	    FOR returnedData IN SELECT * FROM  "OCapsuleProductProperties"  HB
        WHERE HB."RegionID"=RegionID AND HB."ProductID"=productId
                LOOP
                        RETURN NEXT returnedData;
                END LOOP;
    RETURN;
	END IF;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetOCapsuleProductProperties() OWNER TO db_user_admin;

 
CREATE OR REPLACE FUNCTION GetOCapsuleScheduleSpecificConcProperties() RETURNS SETOF "ProductConcentrationForSpray"  AS $$
DECLARE
	RegionID int;
	productId int;
	returnedData "ProductConcentrationForSpray"%rowtype;
	BEGIN
	SELECT "RegionID" INTO RegionID FROM "SystemData";
	SELECT "Products"."ProductID" INTO productId FROM "Products" WHERE "Products"."ProductSlotID"=2;
	IF ( FOUND = true ) THEN
	FOR returnedData IN SELECT * FROM  "ProductConcentrationForSpray"  SB
	WHERE SB."RegionID"=RegionID AND SB."ProductID"=productId
	LOOP
		RETURN NEXT returnedData;
	END LOOP;
		RETURN;
	END IF;
	END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetOCapsuleScheduleSpecificConcProperties() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetBolierPropertiesForProducts() RETURNS SETOF "BolierPropertiesForProducts" AS $$
SELECT 	* FROM 	"BoilerPropertiesForProducts";
$$ LANGUAGE SQL;
ALTER FUNCTION GetBolierPropertiesForProducts() OWNER TO db_user_admin;

 
 
-- ControllerData table:
-- Return all rows in the  table
CREATE OR REPLACE FUNCTION GetControllerData() RETURNS SETOF "ControllerData" AS $$

	SELECT * FROM  "ControllerData";
$$ LANGUAGE SQL;
ALTER FUNCTION GetControllerData() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetControllerDataGarfunkel() RETURNS SETOF "ControllerData" AS $$

	SELECT * FROM  "ControllerData" WHERE "Description" = 'Garfunkel';
$$ LANGUAGE SQL;
ALTER FUNCTION GetControllerDataGarfunkel() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetControllerData(name character varying(25)) RETURNS SETOF "ControllerData" AS $$
	SELECT * FROM  "ControllerData" WHERE lower("Description") = lower($1);
$$ LANGUAGE SQL;
ALTER FUNCTION GetControllerData(character varying(25)) OWNER TO db_user_admin;



-- Default parameters
DROP TYPE IF EXISTS DefaultParameterType CASCADE;
CREATE TYPE DefaultParameterType AS (parameterName character varying(100), min real, max real, stepSize real, defaultValue real);
ALTER TYPE DefaultParameterType OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetParameters() RETURNS SETOF DefaultParameterType AS $$

	SELECT 	"ParameterName", 
		"Min", 
		"Max", 
		"StepSize", 
		"DefaultValue" 
	FROM 	"DefaultParameters"
			INNER JOIN
		"SystemData" 
			ON "DefaultParameters"."RegionID" = "SystemData"."RegionID";

$$ LANGUAGE SQL;
ALTER FUNCTION GetParameters() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetParameterByName(IN parameterName character varying(100)) RETURNS SETOF DefaultParameterType AS $$

	SELECT 	"ParameterName", 
		"Min", 
		"Max", 
		"StepSize", 
		"DefaultValue" 
	FROM 	"DefaultParameters" 
			INNER JOIN 
		"SystemData" 
			ON "DefaultParameters"."RegionID" = "SystemData"."RegionID" 
	WHERE "ParameterName" = $1;

$$ LANGUAGE SQL;
ALTER FUNCTION GetParameterByName(IN character varying(100)) OWNER TO db_user_admin;
-----
CREATE OR REPLACE FUNCTION GetDefaultParameters() RETURNS SETOF "DefaultParameters" AS $$

	SELECT 	d.* 
	FROM  	"DefaultParameters" d 
			INNER JOIN
		"SystemData" s
			ON d."RegionID" = s."RegionID";

$$ LANGUAGE SQL;
ALTER FUNCTION GetDefaultParameters() OWNER TO db_user_admin;



-- Get all of the System parameters
CREATE OR REPLACE FUNCTION GetSystemData() RETURNS SETOF "SystemData" AS $$

	SELECT * FROM "SystemData" where "StatusCode" = 'A';

$$ LANGUAGE SQL;
ALTER FUNCTION GetSystemData() OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetBusinessSpecificPorts(businessName character varying(50), OUT internalPort int, OUT externalPort int) as $$
DECLARE
BEGIN
	SELECT "InternalPort", "ExternalPort" INTO internalPort, externalPort
		FROM "CondorBusinessData"
		WHERE lower("BusinessType") = LOWER(businessName);

	EXCEPTION 
		WHEN NO_DATA_FOUND THEN
			RAISE EXCEPTION 'Business Type not found: %', businessName;
		WHEN TOO_MANY_ROWS THEN
			RAISE EXCEPTION 'Business Type not unique: %', businessName;

END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetBusinessSpecificPorts(character varying(50), OUT int, OUT int) OWNER TO db_user_admin;

-- Returns only the row where the description is equal to Aquanomics
CREATE OR REPLACE FUNCTION UpdateControllerData(description character varying(25), serialnumber character varying(25), buildDate character varying(25),
	softwareversion character varying(25), address character varying(5), instance character varying(5)) RETURNS BOOLEAN AS $$
DECLARE
	rowUpdated boolean;
BEGIN
	

	UPDATE "ControllerData" SET
		"SerialNumber" = $2,
		"BuildDate" = to_timestamp($3,'YYYY Month DD'),
		"SoftwareVersion" = $4,
		"Address" = $5,
		"Instance" = $6
		WHERE lower("Description") = lower($1);

	-- If the row is not updated, means that it is not in the table, add it.
	IF ( FOUND = false ) THEN
		INSERT INTO "ControllerData" ("Description", "SerialNumber", "BuildDate", "SoftwareVersion", "Address", "Instance") VALUES
			($1, $2, to_timestamp($3,'YYYY Month DD'), $4, $5, $6);
	END IF;

	rowUpdated = FOUND;

	return rowUpdated;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateControllerData(character varying(25), character varying(25), character varying(25), character varying(25), character varying(5), character varying(5)) OWNER TO db_user_admin;

-- Language stored procedures
CREATE OR REPLACE FUNCTION GetControllerLanguages() RETURNS SETOF "Language_Ref" AS $$

    SELECT * FROM "Language_Ref" WHERE "StatusCode" = 'A';

$$ LANGUAGE SQL;
ALTER FUNCTION GetControllerLanguages() OWNER TO db_user_admin;



-- Stored procs for getting and setting the values for a development,  
--  The stored procs may continue for 

CREATE OR REPLACE FUNCTION GetUnitOfMeasure(OUT uom integer, OUT returnValue integer) AS $$
DECLARE
BEGIN
	-- initialize the values to zero
	uom := 0;

	SELECT "UnitOfMeasure" INTO uom FROM "SystemData" WHERE "StatusCode" = 'A';
		
	returnValue := 0;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetUnitOfMeasure(OUT integer, OUT integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetUnitOfMeasure(uom integer, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
    retType integer;
	oldValue integer;
BEGIN

    retType := 8;
	
	SELECT "UnitOfMeasure" INTO oldValue FROM "SystemData" WHERE "StatusCode" = 'A';    
    
	IF( oldValue IS NULL ) THEN
            oldValue := -1;
    END IF;
	
	UPDATE "SystemData" SET 
	"UnitOfMeasure" = $1,
	"MOD_DT" = now(),
	"MOD_OPER" = $2
	WHERE "StatusCode" = 'A';
        
    IF FOUND THEN
        retType := 0;
		--PERFORM AddEventToLog(7, 2, $1, oldValue, -1, -1, -1, -1, $2);
    END IF;
    
    return retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetUnitOfMeasure(integer,  character varying(25)) OWNER TO db_user_admin;

--PrimaryLanguage
CREATE OR REPLACE FUNCTION GetPrimaryLanguage(OUT primaryLanguage integer, OUT returnValue integer) AS $$
DECLARE
BEGIN
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetPrimaryLanguage(OUT integer, OUT integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetDBSyncState(stateToChange boolean, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN

	UPDATE "DBSyncState" SET 
			"SyncStop" = $1,
			"MOD_DT" = now(),
			"MOD_OPER" = $2;
	retType := 0;        
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetDBSyncState(boolean,  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetPrimaryLanguage(primaryLanguage integer, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
	min	integer;
	max 	integer;
	oldValue integer;
BEGIN
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetPrimaryLanguage(integer,  character varying(25)) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetTMLanguage(OUT tmLanguage integer, OUT returnValue integer) AS $$
DECLARE
BEGIN
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetTMLanguage(OUT integer, OUT integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetTMLanguage(tmLanguage integer, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
	min		integer;
	max 	integer;
	oldValue integer;
BEGIN
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTMLanguage(integer, character(8)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetAccountName(name character varying(20), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"CustomerName" = name,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAccountName(character varying(20),  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetAccountNumber(num character varying(20), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"AccountNumber" = num,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAccountNumber(character varying(20),  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetAccountAddress(adr character varying(50), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"Address" = adr,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAccountAddress(character varying(50),  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetAccountPhoneNumber(num character varying(20), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"Contact" = num,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAccountPhoneNumber(character varying(20),  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetTMName(name character varying(20), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"TMName" = name,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTMName(character varying(20),  character varying(25)) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION SetTMNumber(num character varying(20), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"PhoneNumber" = num,
			"MOD_DT" = now(),
			"MOD_OPER" = $2
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTMNumber(character varying(20),  character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetAccountDateTime(Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
	retType := 0;
	UPDATE "CustomerInfo" SET 
			"DateInstalled" = now(),
			"MOD_DT" = now(),
			"MOD_OPER" = $1
			WHERE "StatusCode" = 'A';
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAccountDateTime( character varying(25)) OWNER TO db_user_admin;
-- EventDataLog table:

-- Language_Ref table:
CREATE OR REPLACE FUNCTION GetLanguageRef() RETURNS SETOF "Language_Ref" as $$

    SELECT * FROM "Language_Ref";
      
$$ LANGUAGE SQL;
ALTER FUNCTION GetLanguageRef() OWNER to db_user_admin;




DROP TYPE IF EXISTS CustomerInfoType CASCADE;
CREATE TYPE CustomerInfoType AS (customerid int, customername character varying(20), address character varying(50), contact character varying(20), tmname  character varying(20), phoneNumber  character varying(20), accountNumber character varying(20), dispenserId character varying(20), dateInstalled timestamp without time zone, lastresetdate timestamp without time zone);
ALTER TYPE CustomerInfoType OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetCustomerInfo() RETURNS SETOF CustomerInfoType AS $$
DECLARE
    startIndex integer;
    returnSet  CustomerInfoType%rowtype;
BEGIN

    SELECT count(*) INTO startIndex FROM "CustomerInfo";

-- The use of the start index will need to include the last index.
    FOR returnSet IN SELECT "CustomerID", "CustomerName", "Address", "Contact", "TMName", "PhoneNumber", "AccountNumber", "DispenserID", "DateInstalled", "LastResetDate" 
        FROM "CustomerInfo" WHERE "CustomerID" <= startIndex ORDER BY "CustomerID" ASC LOOP

-- Remove the milliseconds
    SELECT date_trunc('second', returnSet.dateinstalled) INTO returnSet.dateinstalled;
    RETURN NEXT returnSet;
END LOOP;

RETURN;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetCustomerInfo() OWNER TO db_user_admin;

-- Password table

CREATE OR REPLACE FUNCTION GetPasswords() RETURNS SETOF "Password" as $$

    SELECT * FROM "Password";
$$ LANGUAGE SQL;


CREATE OR REPLACE FUNCTION SetCustomerPassword( customerPassword character varying(8), Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN
    
    UPDATE "Password" SET
        "CustomerPassword" = $1,
        "MOD_DT" = now(),
        "MOD_OPER" = $2
        WHERE "StatusCode" = 'A';
        
    IF FOUND THEN
        retType := 0;
		--PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2);
    END IF;

    return retType;
END;

$$ LANGUAGE plpgsql;
ALTER FUNCTION SetCustomerPassword( customerPassword character varying(8), Operator  character varying(25) ) OWNER TO db_user_admin;


-- Stored procs for setting the local language through LocaleID,
-- Usage:   SELECT * FROM SetSystemLocaleID(" + QString::number(localId) + ", " + "\'ui\')";
-- Purpose: This SP would be useful  to set LocaleID( but what about the other columns of Language_Ref Table?)
-- Version: 29/04/2016 : Initial Version
CREATE OR REPLACE FUNCTION SetSystemLocaleID(localeID character varying(12), Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "Language_Ref" SET
        "LocaleID" = $1,
        "MOD_DT" = now(),
        "MOD_OPER" = $2
        WHERE "StatusCode" = 'A';

    IF FOUND THEN
        retType := 0;
		--PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2);
    END IF;

    return retType;
END;

$$ LANGUAGE plpgsql;
ALTER FUNCTION SetSystemLocaleID(character varying(12), character varying(25)) OWNER TO db_user_admin;

-- Stored procs for setting the local Language of local Class Object!,
-- Usage:   SELECT * FROM GetLocaleNames()
-- Purpose: This SP would be useful to get LocaleID and other stuff of given Language
-- Version: 29/04/2016 : Initial Version
CREATE OR REPLACE FUNCTION GetLocaleNames() RETURNS SETOF "Language_Ref" AS $$

        SELECT 	* 
	FROM  	"Language_Ref" 
	WHERE	"StatusCode" = 'A'
	ORDER BY "LanguageID" ASC;

$$ LANGUAGE SQL;
ALTER FUNCTION GetLocaleNames() OWNER TO db_user_admin;





CREATE OR REPLACE FUNCTION SetSystemRegionID( opmode integer, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "RegionID" = $1,
        "MOD_DT" = now(),
        "MOD_OPER" = $2
        WHERE "StatusCode" = 'A';

    IF FOUND THEN
        retType := 0;
		IF ($1!=0) THEN
	    UPDATE "SystemData" SET
        "UnitOfMeasure" = 1, --set it to metric for RegionID=1 and 2
        "MOD_DT" = now(),
        "MOD_OPER" = $2
        WHERE "StatusCode" = 'A';
		ELSE
	    UPDATE "SystemData" SET
        "UnitOfMeasure" = 0, --set it to standard for RegionID =0
        "MOD_DT" = now(),
        "MOD_OPER" = $2;
		END IF;
    END IF;

    return retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetSystemRegionID(integer, character varying(25)) OWNER TO db_user_admin;


-- Stored procs for setting the values for a development,
-- Usage:   SELECT * FROM GetRegionIDNames()
-- Purpose: This SP would be useful to get RegionID names
-- Version: 11/05/2013 : Initial Version
CREATE OR REPLACE FUNCTION GetRegionIDNames() RETURNS SETOF "SystemRegion_Ref" AS $$

        SELECT 	* 
	FROM  	"SystemRegion_Ref" 
	WHERE	"StatusCode" = 'A'
	ORDER BY "RegionID" ASC;

$$ LANGUAGE SQL;
ALTER FUNCTION GetRegionIDNames() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION ResetSystem() RETURNS INTEGER AS $$
DECLARE
    retType integer;
    returnedData "DefaultParameters"%rowtype;
    capacity                    	real;
    chartStop                   	boolean;
    flushWhiledosing            	boolean;
    additionalFlushTime         	integer;
    heavyBoostOn                	boolean;
    heavyBoostPercentage        	integer;
    signalFilterTime            	integer;
    machineOpMode               	integer;
    lockStatus                  	boolean;
    minPumpIDLockOut            	integer;
    maxPumpIDLockOut            	integer;
    optionalFlushInstalled      	boolean;
    optionalWEFlushTime         	integer;
    optionalFormSelect          	boolean;
    numberOfPumps			integer;
    numberOfWEs				integer;
    unitOfMeasure			integer;
    flushDelayTime			integer;
    flushDropTime			integer;
    additionalFlushDelayTime		integer;
    additionalFlushDropTime		integer;
    productPickupProbe			integer;
    addlProbeSensorEmptyAlarmDelay 	integer;
    alarmVolume				integer;
    alarmMuteTime			integer;
    calibrationValue			real;

	RegionIDValue             integer;
BEGIN


    IF FOUND THEN
        retType := 0;
		--PERFORM AddEventToLog(10, -1, -1, -1, -1, -1, -1, -1, 'ui');
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION ResetSystem() OWNER TO db_user_admin;

DROP TYPE IF EXISTS LocalizedStringType CASCADE;
CREATE TYPE LocalizedStringType AS (stringID integer, stringCommonName character varying(50), string character varying(250));
ALTER TYPE LocalizedStringType OWNER TO db_user_admin;
/*
-- PrimaryLanguage
CREATE OR REPLACE FUNCTION GetPrimaryLanguageStrings( ) RETURNS SETOF LocalizedStringType AS $$

    SELECT ls."StringID", ls."StringCommonName", ls."String" FROM "LocalizedStrings" AS ls
        JOIN "SystemData" as sd on ls."LanguageID" = sd."PrimaryLanguage"
        WHERE ls."SpecialString" = false;
        
$$ LANGUAGE SQL;
ALTER FUNCTION GetPrimaryLanguageStrings() OWNER TO db_user_admin;

-- TM Programming Language
CREATE OR REPLACE FUNCTION GetProgrammingLanguageStrings( ) RETURNS SETOF LocalizedStringType AS $$

    SELECT ls."StringID", ls."StringCommonName", ls."String" FROM "LocalizedStrings" AS ls
        JOIN "SystemData" as sd on ls."LanguageID" = sd."TMLanguage"
        WHERE ls."SpecialString" = false;
        
$$ LANGUAGE SQL;
ALTER FUNCTION GetProgrammingLanguageStrings() OWNER TO db_user_admin;

-- Get special system strings
CREATE OR REPLACE FUNCTION GetSpecialLanguageStrings( ) RETURNS SETOF LocalizedStringType AS $$

    SELECT ls."StringID", ls."StringCommonName", ls."String" FROM "LocalizedStrings" AS ls
        WHERE ls."SpecialString" = true;
        
$$ LANGUAGE SQL;
ALTER FUNCTION GetSpecialLanguageStrings() OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetProductName(IN productNo integer,  OUT name character varying(20), OUT returnValue integer) AS $$
DECLARE
	RegionIDValue integer;
	stringId  integer;
	productId integer;
BEGIN
	returnValue := 9;
	SELECT "RegionID" INTO RegionIDValue FROM "SystemData";
	SELECT "ProductID" INTO productId FROM "ProductInfo" WHERE "ProductNo"=$1 AND "RegionID"=RegionIDValue AND "StatusCode"='A';
	SELECT "ProductName" INTO stringId FROM "ProductInfo" WHERE "ProductID"=productId AND "RegionID"=RegionIDValue;
    
	IF FOUND THEN 
		SELECT 	"String" INTO name FROM "LocalizedStrings" WHERE "StringID"=stringId;
		returnValue := 0;
    END IF;
   	
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetProductName(IN  integer,  OUT  character varying(20), OUT  integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION SetProductName(prodno integer, name character varying(20), Operator character(20)) RETURNS INTEGER AS $$
DECLARE
    retType integer := 8;
	RegionIDValue integer;
	stringId  integer;
	testName character varying(20);
	uniqueName boolean;
BEGIN
	uniqueName := true;
	SELECT "RegionID" INTO RegionIDValue FROM "SystemData";
	
	FOR stringId IN SELECT "ProductName" FROM "ProductInfo" WHERE "RegionID"=RegionIDValue AND "StatusCode"='A'
		LOOP
		SELECT "String" INTO testName FROM "LocalizedStrings" WHERE "StringID"=stringId;
		IF (testName = name) THEN
			uniqueName := false;
			retType := 10;
			EXIT;
		END IF;
	END LOOP;
	
	IF (uniqueName = true) THEN 
		SELECT "ProductName" INTO stringId FROM "ProductInfo" WHERE "ProductNo"=$1 AND "RegionID"=RegionIDValue AND "StatusCode"='A';
		IF FOUND THEN 
			UPDATE "LocalizedStrings" SET "String" = $2, "MOD_DT" = now(),"MOD_OPER" = $3 WHERE "StringID"=stringId;
			IF FOUND THEN
			retType := 0;
			END IF;
		END IF;
	END IF;	
	return retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetProductName(integer, character varying(20), character(8)) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetProductNumber(IN name character varying(20), OUT productNumber integer, OUT returnValue integer) AS $$
DECLARE
	RegionIDValue integer;
	stringId  integer;
	testName character varying(20);
BEGIN
	returnValue := 8;
	productNumber := -1;
	
	SELECT "RegionID" INTO RegionIDValue FROM "SystemData";

	FOR stringId IN SELECT "ProductName" FROM "ProductInfo" WHERE "RegionID"=RegionIDValue  AND "StatusCode"='A' 
		LOOP
		SELECT "String" INTO testName FROM "LocalizedStrings" WHERE "StringID"=stringId;
		IF (testName = name) THEN
			SELECT "ProductNo" INTO productNumber FROM "ProductInfo" WHERE "ProductName"=stringId AND "RegionID"=RegionIDValue AND "StatusCode"='A';
			IF (FOUND = true) THEN
				returnValue := 0;
			ELSE
				productNumber := -1;
			EXIT;
			END IF;
		END IF;
		END LOOP;
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetProductNumber(IN  character varying(20),  OUT  integer, OUT  integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetTotalNoOfProductsForRegion(OUT totalProd integer, OUT returnValue integer) AS $$
DECLARE
	RegionIDValue integer;
BEGIN
	SELECT "RegionID" INTO RegionIDValue FROM "SystemData";
	SELECT MAX("ProductNo") INTO totalProd FROM "ProductInfo" WHERE "RegionID"=RegionIDValue AND "StatusCode"='A';
    returnValue := 0;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetTotalNoOfProductsForRegion(OUT integer, OUT integer) OWNER TO db_user_admin;




--if we delete a product from product list, we need to adjust all the existing products. But since we have their id being referenced in productMap and formulaSpeproductAttr and Alarm table, we could run into wrong ref and intgrity of data is lost

-- SU:7
CREATE OR REPLACE FUNCTION SetBoardBuildDate(buildDate character varying(25), description character varying(25)) RETURNS void AS $$

	UPDATE "ControllerData" SET 
		"BuildDate" = to_timestamp($1,'YYYY Mon DD');		
$$ LANGUAGE SQL;
ALTER FUNCTION SetBoardBuildDate(character varying(25), character varying(25)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetProductNumberForProductId(productId integer ) RETURNS INTEGER AS $$
DECLARE
	productno integer;
	RegionIDValue integer;
BEGIN
	productno := -1;
	SELECT "RegionID" INTO RegionIDValue FROM "SystemData";
	SELECT "ProductNo" INTO productno FROM "ProductInfo" WHERE "RegionID"=RegionIDValue AND "ProductID"=$1;
	return productno;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetProductNumberForProductId(integer) OWNER TO db_user_admin;





CREATE OR REPLACE FUNCTION GetLanguageDisplayRegionIDs(OUT primaryLang character varying(12), OUT secondaryLang character varying(12), OUT programmingLang character varying(12),OUT primaryLangFont character varying(20), OUT secondaryLangFont character varying(20), OUT programmingLangFont character varying(20), OUT primaryLangFontPointSize integer, OUT secondaryLangFontPointSize integer, OUT programmingLangFontPointSize integer, OUT primaryLangFontBold boolean, OUT secondaryLangFontBold boolean, OUT programmingLangFontBold boolean, OUT primaryLangFallbackFont character varying(20),OUT primaryLangFallbackFontPointSize integer, OUT primaryLangFallbackFontBold boolean) AS $$
DECLARE
BEGIN
    -- Get the primary language
    SELECT lr."RegionID", lr."Font",lr."PointSize", lr."BoldFont", lr."FallbackFont", lr."FallbackPointSize", lr."FallbackBoldFont"  INTO primaryLang, primaryLangFont, primaryLangFontPointSize, primaryLangFontBold, primaryLangFallbackFont, primaryLangFallbackFontPointSize, primaryLangFallbackFontBold FROM "Language_Ref" as lr
        JOIN "SystemData" as sd on lr."LanguageID" = sd."PrimaryLanguage";

    SELECT lr."RegionID", lr."Font",lr."PointSize", lr."BoldFont" INTO secondaryLang, secondaryLangFont, secondaryLangFontPointSize, secondaryLangFontBold FROM "Language_Ref" as lr
        JOIN "SystemData" as sd on lr."LanguageID" = sd."SecondaryLanguage";

    SELECT lr."RegionID", lr."Font",lr."PointSize", lr."BoldFont" INTO programmingLang, programmingLangFont, programmingLangFontPointSize, programmingLangFontBold FROM "Language_Ref" as lr
        JOIN "SystemData" as sd on lr."LanguageID" = sd."TMLanguage";

END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetLanguageDisplayRegionIDs(OUT character varying(12), OUT character varying(12), OUT  character varying(12), OUT  character varying(20), OUT  character varying(20), OUT  character varying(20),OUT  integer, OUT  integer, OUT  integer, OUT  boolean, OUT  boolean, OUT  boolean ) OWNER TO db_user_admin;

DROP TYPE IF EXISTS AlarmProperties CASCADE;
CREATE TYPE AlarmProperties AS (AlarmID integer, IsEnvisionConfigurable boolean, IsEnvisionEnabled boolean, StopSumpCreation boolean, StopDispenseOperation boolean, ActivationDelay integer, ActivationCondorDelay integer, ActivationEnvisionDelay integer, DeactivationDelay integer, DeactivationCondorDelay integer, DeactivationEnvisionDelay integer, IsActive BOOLEAN, ActiveCode BOOLEAN, ColorCode character varying(10));
ALTER TYPE AlarmProperties OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetAlarmSettings() RETURNS SETOF AlarmProperties AS $$
	SELECT "Alarms"."AlarmID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "StopSumpCreation", "StopDispenseOperation", "ActivationDelay", 
	"ActivationCondorDelay", "ActivationEnvisionDelay", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay",
	"Alarms"."IsActive", "RegionSpecificAlarmProperties"."IsActive", "ColorCode" FROM "Alarms" 
	INNER JOIN
	"RegionSpecificAlarmProperties"
	ON "Alarms"."AlarmID" = "RegionSpecificAlarmProperties"."AlarmID" 
	INNER JOIN
	"SystemData"
	ON "RegionSpecificAlarmProperties"."RegionID"= "SystemData"."RegionID"
	WHERE "RegionSpecificAlarmProperties"."IsActive"=true
	ORDER BY "AlarmID" ASC;
$$ LANGUAGE SQL;	
ALTER FUNCTION GetAlarmSettings() OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetAlarmSettings() RETURNS SETOF "Alarms" AS $$
SELECT 	* FROM 	"Alarms" ORDER BY "AlarmID" ASC;
$$ LANGUAGE SQL;
ALTER FUNCTION GetAlarmSettings() OWNER TO db_user_admin;
*/



CREATE OR REPLACE FUNCTION GetProductInfo() RETURNS SETOF "ProductInfo" AS $$
DECLARE
    returnedData "ProductInfo"%rowtype;
BEGIN

    FOR returnedData IN SELECT * FROM  "ProductInfo"  fi
	JOIN "SystemData" sd ON sd."RegionID"=fi."RegionID" 
	JOIN "ProductMapping" pm ON sd."RegionID"=pm."RegionID" AND fi."ProductID"= pm."ProductID" 
	ORDER BY fi."ProductID" ASC
		LOOP
			RETURN NEXT returnedData;
		END LOOP;
    RETURN;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetProductInfo() OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetSProductInfo() RETURNS SETOF "SBlockProductProperties" AS $$
DECLARE
    returnedData "SBlockProductProperties"%rowtype;
BEGIN

    FOR returnedData IN SELECT * FROM  "SBlockProductProperties"  fi
	JOIN "SystemData" sd ON sd."RegionID"=fi."RegionID" 
	ORDER BY "ProductID" ASC
		LOOP
			RETURN NEXT returnedData;
		END LOOP;
    RETURN;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetSProductInfo() OWNER TO db_user_admin;

DROP TYPE IF EXISTS LookupTableData CASCADE;
CREATE TYPE LookupTableData AS (ProductID integer, ProductSlotID integer, FromTempThreshold real, ToTempThreshold real, FromPressure real, ToPressure real, DispenseRate real, FlowRate real);
ALTER TYPE LookupTableData OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetLookupTableInfoForSlot(slotId integer) RETURNS SETOF LookupTableData AS $$
SELECT 	"SprayLookUpTable"."ProductID", "Products"."ProductSlotID", "SprayLookUpTable"."FromTemp", "SprayLookUpTable"."ToTemp", "SprayLookUpTable"."FromPressure", "SprayLookUpTable"."ToPressure", "SprayLookUpTable"."DispenseRate", "SprayLookUpTable"."FlowRate"
FROM 	"SprayLookUpTable"
	INNER JOIN 
		"SystemData" 
	ON "SprayLookUpTable"."RegionID"="SystemData"."RegionID" 
	INNER JOIN 
		"Products" 
	ON "SprayLookUpTable"."ProductID"="Products"."ProductID" 
	WHERE "Products"."ProductSlotID" = $1;
$$ LANGUAGE SQL;
ALTER FUNCTION GetLookupTableInfoForSlot(integer) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION SetAlarmActiveState(id integer, optflush boolean) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "Alarms" SET
        "IsActive" = $2,
        "MOD_DT" = now()
        WHERE "AlarmID" = $1;

    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetAlarmActiveState(integer, boolean) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION SetStandbyActiveState(optflush boolean) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "SystemData" SET
        "SystemStandby" = $1,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetStandbyActiveState( boolean) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION UpdateTreatmentPumpDutyCycle(id integer) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "ScheduleSpecificProperties" SET
        "ActiveTreatmentPumpDutyCycle" = "NewTreatmentPumpDutyCycle",
        "MOD_DT" = now()
        WHERE "OperatingScheduleRefID" = $1;

    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateTreatmentPumpDutyCycle(integer) OWNER TO db_user_admin;



CREATE OR REPLACE FUNCTION UpdateTimeDateofLastFillEvent() RETURNS INTEGER AS $$
DECLARE
    retType integer;
	prevFillTime timestamp without time zone;
	diffTime real = 0;
BEGIN

    retType := 8;

	SELECT "TimeDateOfStartOfLastFillEvent" INTO prevFillTime  FROM "SystemData";
    UPDATE "SystemData" SET
        "TimeDateOfStartOfLastFillEvent" = now(),
        "MOD_DT" = now();
	RAISE NOTICE 'here 1 =%', now() - prevFillTime;
	RAISE NOTICE 'here 2 =%', ((EXTRACT(EPOCH FROM current_timestamp) - EXTRACT(EPOCH FROM prevFillTime))/60)::Integer;
	diffTime := abs((EXTRACT(EPOCH FROM current_timestamp) - EXTRACT(EPOCH FROM prevFillTime))/60)::Integer;
	RAISE NOTICE 'difftime  in minutes=%', diffTime;
	UPDATE "SystemData" SET
        "TimeBetweenFillEvents" = diffTime,
        "MOD_DT" = now();	
		
    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateTimeDateofLastFillEvent() OWNER TO db_user_admin;



CREATE OR REPLACE FUNCTION UpdateLastTempAndSprayType(temp real, sptype integer) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "SystemData" SET
        "LastSumpCreateTempInDegreeC" = $1,
		"LastSprayType" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateLastTempAndSprayType(real, integer) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION UpdateLayupEnabled(optflush boolean) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "SystemData" SET
        "LayupEnabled" = $1,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateLayupEnabled( boolean) OWNER TO db_user_admin;
/*
DROP FUNCTION GetBFWPOnTime();
CREATE OR REPLACE FUNCTION GetBFWPOnTime() RETURNS character varying(30) AS $$
DECLARE
    cStartDate character varying(30);
BEGIN
	SELECT  TO_CHAR("TimeDateOfLastBFWPSignalReceived", 'MM-DD-YYYY HH24:MI:SS') INTO cStartDate FROM "SystemData";
	return cStartDate;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetBFWPOnTime( ) OWNER TO db_user_admin;
*/

CREATE OR REPLACE FUNCTION UpdateBFWPOnTime() RETURNS INTEGER AS $$
DECLARE
    retType integer;
	prevFillTime timestamp without time zone;
	diffTime real = 0;
BEGIN

    retType := 8;

	SELECT "TimeDateOfLastBFWPSignalReceived" INTO prevFillTime  FROM "SystemData";
    UPDATE "SystemData" SET
        "TimeDateOfLastBFWPSignalReceived" = now(),
        "MOD_DT" = now();
	--RAISE NOTICE 'here 1 =%', now() - prevFillTime;
	RAISE NOTICE 'here 2 =%', ((EXTRACT(EPOCH FROM current_timestamp) - EXTRACT(EPOCH FROM prevFillTime))/60);
	diffTime := abs((EXTRACT(EPOCH FROM current_timestamp) - EXTRACT(EPOCH FROM prevFillTime))/60);
	RAISE NOTICE 'difftime in minutes =%', diffTime;
	UPDATE "SystemData" SET
        "TimeBetweenBFWPEvents" = diffTime,
        "MOD_DT" = now();	
		
    IF FOUND THEN
        retType := 0;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateBFWPOnTime() OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION AddNewBFWPOnTime( OnTime character varying(30), duration real, secId integer ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
	lenOnTime real;
BEGIN

    retType := 0;

	INSERT INTO "BFWPOnTimes" ("OnTime", "DurationInMinutes", "OperatingScheduleRefID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
--			(to_timestamp($1, 'MM-DD:YYYY HH24:MI:SS'), $2, $3, clock_timestamp(), 'mca', clock_timestamp(), 'mca');	
			(to_timestamp($1, 'YYYY:MM:DD:HH24:MI:SS'), $2, $3, clock_timestamp(), 'mca', clock_timestamp(), 'mca');	
    IF FOUND THEN
        retType := 0;
		lenOnTime := 0;
		SELECT AVG("DurationInMinutes") INTO lenOnTime FROM "BFWPOnTimes" WHERE "OnTime">= CURRENT_DATE AND "OnTime"<= CURRENT_DATE+1;
		RAISE NOTICE 'length=%', lenOnTime;
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION AddNewBFWPOnTime( character varying(30),  real, integer ) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetBFWPOnTimeAverage( ) RETURNS real AS $$
DECLARE
	lenOnTime real;
BEGIN

	lenOnTime := 0;
	SELECT SUM("DurationInMinutes") INTO lenOnTime FROM "BFWPOnTimes" WHERE "OnTime">= (CURRENT_DATE-interval '7 day') AND "OnTime"<= CURRENT_DATE;
	RAISE NOTICE 'length=%', lenOnTime;
    return lenOnTime;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetBFWPOnTimeAverage(  ) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION UpdateTreatmentPumpRunTime(runTime real) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := 8;

    UPDATE "SystemData" SET
        "TimeTreatmentPumpRunSinceEmptyLevelSump" = $1,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateTreatmentPumpRunTime( real) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION UpdateRunTimeForProduct( slot integer, runTime integer) RETURNS INTEGER AS $$
DECLARE     
retType integer; 
BEGIN
	retType := 0;
	UPDATE "ProductSlot" SET "RunTime"=$2 WHERE "ProductSlotType"=$1; --use slot type to identify type of product (S, P, or O)
	return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION UpdateRunTimeForProduct( integer, integer) OWNER TO db_user_admin;	




--- SystemData Updating Functions ---
-----------------------------------------------------------------------------------------------------------
 /** SetDecimalOrComma **/
CREATE OR REPLACE FUNCTION SetDecimalOrComma( dOrC boolean, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "DecimalOrComma" = dOrC,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetDecimalOrComma( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

 /** SetDateFormatID **/
CREATE OR REPLACE FUNCTION SetDateFormatID( dateFormatID integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "DateFormatID" = dateFormatID,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetDateFormatID( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------


 /** SetIsTwelveHourFormat **/
CREATE OR REPLACE FUNCTION SetIsTweleveHourFormat( isTwelvehourformat boolean, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "IsTwelveHourFormat" = isTwelvehourformat,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetIsTwelveHourFormat( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetOperatingModeID **/
CREATE OR REPLACE FUNCTION SetOperatingModeID( opModeID integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "OperatingModeID" = opModeID,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetOperatingModeID( integer, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetIsDeareatorPresent **/ -- Same as DAorNoDA Setting?
CREATE OR REPLACE FUNCTION SetIsDeareatorPresent( isDtorPres boolean, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "IsDeareatorPresent" = isDtorPres,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetIsDeareatorPresent( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetBoilerPressure **/
CREATE OR REPLACE FUNCTION SetBoilerPressure( bpressure real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "BoilerPressure" = bpressure,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetBoilerPressure( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetFWTemperature **/
CREATE OR REPLACE FUNCTION SetFWTemperature( fwTemp real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "FWTemperature" = fwTemp,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetFWTemperature( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------


/** SetDAOperatingPressure **/
CREATE OR REPLACE FUNCTION SetDAOperatingPressure( dAOpPressure real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "DAOperatingPressure" = dAOpPressure,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetDAOperatingPressure( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetCyclesOfConcentrationTarget **/
CREATE OR REPLACE FUNCTION SetDCyclesOfConcentrationTarget( cConTarget real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "CyclesOfConcentrationTarget" = cConTarget,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetCyclesOfConcentrationTarget( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------


/** SetNominalSteamFlow **/
CREATE OR REPLACE FUNCTION SetNominalSteamFlow( nSteamFlow real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "NominalSteamFlow" = nSteamFlow,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetNominalSteamFlow( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------


/** SetTotalCondensateReturn **/
CREATE OR REPLACE FUNCTION SetTotalCondensateReturn( totCondRet real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "TotalCondensateReturn" = totCondRet,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTotalCondensateReturn( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------
 

 /** SetIsBFWPIntermittent **/
CREATE OR REPLACE FUNCTION SetIsBFWPIntermittent(intermittent boolean, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "IsBFWPIntermittent" = intermittent,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetIsBFWPIntermittent( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetOperatingHoursPerDay **/
CREATE OR REPLACE FUNCTION SetOperatingHoursPerDay( opHpD integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "OperatingHoursPerDay" = opHpD,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetOperatingHoursPerDay( integer, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetBFWPSignalFilterTime **/
CREATE OR REPLACE FUNCTION SetBFWPSignalFilterTime( bFWPSignalFilterTime integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "BFWPSignalFilterTime" = bFWPSignalFilterTime,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetBFWPSignalFilterTime( integer, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------

/** SetMaxTimeBetweenBFWPCallsInHours **/
CREATE OR REPLACE FUNCTION SetMaxTimeBetweenBFWPCallsInHours( maxTBetweenBFWPCallsInHours integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "MaxTimeBetweenBFWPCallsInHours" = maxTBetweenBFWPCallsInHours,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetMaxTimeBetweenBFWPCallsInHours( integer, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------


/** SetTimeBetweenFillEvents **/ -- Is this the same Length Of Time for Fill Events Before Alarms?
/*This is ONLY used by MCA and please use MaxTimeForFillEventsBeforeAlarm with correct OperatingScheduleRefID
to update Length Of Time for Fill events before Alarms!!!*/
CREATE OR REPLACE FUNCTION SetTimeBetweenFillEvents( timeBtweenFillEvents real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SystemData" SET
        "TimeBetweenFillEvents" = $1,
		"MOD_OPER" = $2,
        "MOD_DT" = now();

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTotalCondensateReturn( real, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------




--- S-Product Functions ---
----------------------------------------------------------------------------------------------------------- 



--- Setting Stored Procedures!!!-------
/** SetIsSBlockInUse **/
CREATE OR REPLACE FUNCTION SetIsSBlockInUse(sBlockInUse boolean, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "SBlockProductProperties" SET
        "IsInUse" = $1,
		"MOD_OPER" = $2,
        "MOD_DT" = now();
        --Add Condition for that Region?
    --WHERE "SBlockProductProperties"."RegionID" = "SystemData"."RegionID";

    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;
    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetIsSBlockInUse( boolean, Operator  character varying(25)) OWNER TO db_user_admin;
---------------------------------------------------------------------------------------------------




--- Boiler Properties for Product Functions ---

--- Getting Stored Procedures!!--------------
-----------------------------------------------------------------------------------------------------------
/** GetBoilerDataForProducts **/
CREATE OR REPLACE FUNCTION GetBoilerDataForProducts() RETURNS SETOF "BoilerPropertiesForProducts" AS $$

	SELECT 	d.* 
	FROM  	"BoilerPropertiesForProducts" d 
			INNER JOIN
		"SystemData" s
			ON d."SystemDataID" = s."SystemDataID";

$$ LANGUAGE SQL;
ALTER FUNCTION GetBoilerDataForProducts() OWNER TO db_user_admin;




--- Updating Stored Procedures!!--------------
-----------------------------------------------------------------------------------------------------------

/** SetUnitOfChoiceForDO **/
CREATE OR REPLACE FUNCTION SetUnitOfChoiceForDO(uNitOfChoiceForDO integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "UnitOfChoiceForDO" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetUnitOfChoiceForDO(integer,  Operator  character varying(25) ) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------





/** SetFWDissolvedOxygen **/
CREATE OR REPLACE FUNCTION SetFWDissolvedOxygen(fwOxygen real, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "FWDissolvedOxygen" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetFWDissolvedOxygen(real,  Operator  character varying(25) ) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------

/** SetTargertBWSO3Residual **/
CREATE OR REPLACE FUNCTION SetTargertBWSO3Residual(targertBWSO3Residual integer, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "TargertBWSO3Residual" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetTargertBWSO3Residual(integer,  Operator  character varying(25)) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------



/** SetFWTotalHardness **/
CREATE OR REPLACE FUNCTION SetFWTotalHardness(fWTotalHardness real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "FWTotalHardness" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();
      
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetFWTotalHardness(real,  Operator  character varying(25) ) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------


/** SetCaTOMgMoleRatio **/
CREATE OR REPLACE FUNCTION SetCaTOMgMoleRatio(cATOMgMoleRatio real, Operator  character varying(25)) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "CaTOMgMoleRatio" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();      
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetCaTOMgMoleRatio(real,  Operator  character varying(25) ) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------



/** SetBDPO4 **/
CREATE OR REPLACE FUNCTION SetBDPO4(bDPO4 real, Operator  character varying(25) ) RETURNS INTEGER AS $$
DECLARE
    retType integer;
BEGIN

    retType := -1;

    UPDATE "BoilerPropertiesForProducts" SET
        "BDPO4" = $1,
        "MOD_OPER" = $2,
        "MOD_DT" = now();       
    IF FOUND THEN
        retType := 0;
        --If needed Log Operation!!!
        --PERFORM AddEventToLog(6, 12, 0, 0, 0, 0, 0,0, $2); 
    END IF;

    return retType;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION SetBDPO4(real,  Operator  character varying(25)) OWNER TO db_user_admin;
-----------------------------------------------------------------------------------------------------------



--- Operating Schedule Updating Functions ---
-----------------------------------------------------------------------------------------------------------





--ADDITIONAL STORED PROCEDURES FOR SYSTEM DATA--



-- Stored procedures for BoilerPropertiesFor Product





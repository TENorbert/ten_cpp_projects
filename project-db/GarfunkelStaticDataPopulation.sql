-- This is the Condor table initial data population script

START TRANSACTION;
INSERT INTO "DBSyncState"("SyncStop","CRE_DT", "CRE_OPER", "MOD_DT", 
            "MOD_OPER")
    VALUES (false, clock_timestamp(), 'Initial',  clock_timestamp(), 'Initial');
END TRANSACTION;

START TRANSACTION;
-- Language Ref

INSERT INTO "Language_Ref"(
            "LanguageID", "Description", "LocaleID", "Font", "PointSize", "FallbackFont", "FallbackPointSize", "FallbackBoldFont", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", 
            "MOD_OPER")
    VALUES (0, 'None', 'en', 'helvetica', '26', 'Unifont', '24', true, 'A',  clock_timestamp(), 'Initial', NULL, NULL);

INSERT INTO "Language_Ref"(
            "LanguageID", "Description", "LocaleID",  "Font", "PointSize", "FallbackFont", "FallbackPointSize", "FallbackBoldFont", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", 
            "MOD_OPER")
    VALUES (1, 'English', 'en','helvetica', '26', 'Unifont', '24', true, 'A',  clock_timestamp(), 'Initial', NULL, NULL);

INSERT INTO "Language_Ref"(
            "LanguageID", "Description", "LocaleID",  "Font", "PointSize", "FallbackFont", "FallbackPointSize", "FallbackBoldFont", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", 
            "MOD_OPER")
    VALUES (2, 'Spanish', 'es', 'helvetica', '26','Unifont', '24', true, 'A', clock_timestamp(), 'Initial', NULL, NULL);

INSERT INTO "Language_Ref"(
            "LanguageID", "Description", "LocaleID",  "Font", "PointSize", "FallbackFont", "FallbackPointSize", "FallbackBoldFont", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", 
            "MOD_OPER")
    VALUES (3, 'French', 'fr', 'helvetica', '26','Unifont', '24', true, 'A', clock_timestamp(), 'Initial', NULL, NULL);

COMMIT TRANSACTION;	
-- SELECT * FROM "Language_Ref"

------------------------------------------------------------------------------------------
START TRANSACTION;
-- CondorBusinessData
INSERT INTO "CondorBusinessData"(
            "BusinessTypeID", "BusinessType", "InternalPort", "ExternalPort", 
            "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 'Condor', 1450, 1400, 
            clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
			
INSERT INTO "CondorBusinessData"(
            "BusinessTypeID", "BusinessType", "InternalPort", "ExternalPort", 
            "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (3, 'Garfunkel', 1200, 1201, 
            clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
			
COMMIT TRANSACTION;			
-- SELECT * FROM "CondorBusinessData"

START TRANSACTION;

-- Table: "SystemRegion_Ref"
--NA
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (0, 200108, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

--EU
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (1, 200109, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--AP
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (2, 200110, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
--LA
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (3, 200111, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--Middle East and Africa
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (4, 200112, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
--Graeter China
INSERT INTO "SystemRegion_Ref"(
            "RegionID", "RegionName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (5, 200113, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
	
COMMIT TRANSACTION;    



START TRANSACTION;

-- Table: "SystemOpMode_Ref"
--Basic Mode
INSERT INTO "SystemOpMode_Ref"(
            "SystemOpModeID", "SystemOpModeName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (0, 120038, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

--Advanced Mode
INSERT INTO "SystemOpMode_Ref"(
            "SystemOpModeID", "SystemOpModeName", "StatusCode", "CRE_DT", "CRE_OPER", 
            "MOD_DT", "MOD_OPER")
    VALUES (1,  120039, 'A', clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

COMMIT TRANSACTION;    
-- SELECT * FROM "SystemOpMode_Ref" 

-------------------------------------------------------------------------------------



START TRANSACTION;

INSERT INTO "DefaultParameters"(
            "RegionID", "ParameterName", "Min", "Max", "StepSize", "DefaultValue", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES ('0', 'SystemOpMode', 0, 0, 0, 0, now(), 'Initial', now(), 'Initial');

INSERT INTO "DefaultParameters"(
            "RegionID", "ParameterName", "Min", "Max", "StepSize", "DefaultValue", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES ('0', 'UnitOfMeasure', 0, 0, 0, 0, now(), 'Initial', now(), 'Initial');


COMMIT TRANSACTION;

-- Populate the Localized String table
START TRANSACTION;

COMMIT TRANSACTION;
-- Populate the Localized String table


START TRANSACTION;


--Specialized strings : washer names 
	
--Specialized strings:  product names
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 9001, 'S Product', '', true, now(), 'Initial', now(), 'Initial');
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 9002, 'H2 Product', '', true, now(), 'Initial', now(), 'Initial');
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 9003, 'Caustic Product', '', true, now(), 'Initial', now(), 'Initial');

COMMIT TRANSACTION;	


START TRANSACTION;
INSERT INTO "ControllerData" ("Description", "Address", "Instance", "SoftwareVersion","Identifier","LastReset") VALUES
	('Garfunkel', 'B', 'a', 'Garfunkel 0.0.1', '0', now() );
INSERT INTO "ControllerData" ("Description", "Address", "Instance", "SoftwareVersion","Identifier","LastReset") VALUES
	('GarfunkelCommServer', 'B', 'a', 'Garfunkel 0.0.4', '0', now() );	
INSERT INTO "ControllerData" ("Description", "Address", "Instance", "SoftwareVersion","Identifier","LastReset") VALUES
	('GarfunkelMCA', 'B', 'a', 'Garfunkel 0.0.1', '0', now() );
INSERT INTO "ControllerData" ("Description", "Address", "Instance", "SoftwareVersion","Identifier","LastReset") VALUES
	('SmartSimon IOBoard', 's', 'a', '0.0.1', '0', now() ); 
INSERT INTO "ControllerData" ("Description", "Address", "Instance", "SoftwareVersion","Identifier", "LastReset") VALUES
	('Garfunkel IOBoard', 'a', 'a', '0.0.1','0', now() );
COMMIT TRANSACTION;



START TRANSACTION;
--   S Block
INSERT INTO "NozzleType_Ref" ( "NozzleTypeRefID",  "NozzleTypeName",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 4001, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--H2	
INSERT INTO "NozzleType_Ref" ( "NozzleTypeRefID",  "NozzleTypeName",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(1, 4002, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--O
INSERT INTO "NozzleType_Ref" ( "NozzleTypeRefID",  "NozzleTypeName",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 4003, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	

COMMIT TRANSACTION;

START TRANSACTION;
--   S Block
INSERT INTO "ProductSlot" ( "ProductSlotID",  "ProductSlotType", "NozzleTypeRefID", "ResetDate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 0, clock_timestamp(), clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- H2 Block
INSERT INTO "ProductSlot" ( "ProductSlotID", "ProductSlotType", "NozzleTypeRefID", "ResetDate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(1, 1, 1, clock_timestamp(), clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
-- O1 Capsule	
INSERT INTO "ProductSlot" ( "ProductSlotID", "ProductSlotType", "NozzleTypeRefID", "ResetDate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 2, 2, clock_timestamp(), clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- O2 Capsule	
INSERT INTO "ProductSlot" ( "ProductSlotID", "ProductSlotType", "NozzleTypeRefID", "ResetDate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(3, 2, 2, clock_timestamp(), clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	

COMMIT TRANSACTION;



START TRANSACTION;
-- Aquanomics sump product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, -1, -1, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- S Block product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 1, 9001,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--  H2 Block product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 1, 2, 9002, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--O capsule product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 2, 3, 9003, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

	
COMMIT TRANSACTION;

START TRANSACTION;
--   S Block
INSERT INTO "SBlockProductProperties" ( "RegionID", "ProductID",  "IsInUse", "PercentSO3InBlock", "NaOHNeededToNeutralize", "PercentCHA", "PercentDEAE", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, true, 1.0, 0.5, 0.5, 0.5, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- P Block
INSERT INTO "PBlockProductProperties" ( "RegionID", "ProductID", "TotalAcidHardnessRatio", "TotalMolePercentAmine", "NaOHNeededToNeutralize", "PercentCHA", "PercentDEAE", "PercentPO4", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
-- O Capsule	
INSERT INTO "OCapsuleProductProperties" ( "RegionID", "ProductID", "PercentNaOHInProduct", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 2, 0.5, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');		

COMMIT TRANSACTION;



-- Create a default rows for the DispenserPocketInfo
START TRANSACTION;
		--S Block product slot
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0,  now(), 'Initial', now(), 'Initial'); 
		--H2
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(1, 1, 0,  now(), 'Initial', now(), 'Initial'); 
		--O	1	
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 2, 0,  now(), 'Initial', now(), 'Initial'); 
		--o 2		
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(3, 2, 0,  now(), 'Initial', now(), 'Initial');		
COMMIT TRANSACTION;


START TRANSACTION;
-- Primary Schedule Ref
INSERT INTO "OperatingSchedule_Ref" ( "OperatingScheduleRefID",  "ScheduleName",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 5001,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- Secondary Schedule Ref
INSERT INTO "OperatingSchedule_Ref" ( "OperatingScheduleRefID", "ScheduleName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(1, 5002,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	

COMMIT TRANSACTION;


START TRANSACTION;
-- Primary Schedule
--sunday
--add only primary schedule, rest will be secondary by default
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 10, 0, 12, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 14, 0, 16, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 20, 0, 22, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
--monday	
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 1, 8, 0, 12, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 1, 13, 0, 18, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--tuesday	
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 2, 8, 0, 11, 59,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 2, 14, 0, 17, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--wednesday
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 3, 8, 30, 11, 59,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 3, 13, 0, 16, 0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--thursday
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 4, 7, 30, 12, 00,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 4, 15, 10, 15, 55,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--friday
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 5, 8, 30, 11, 30,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 5, 14, 10, 17, 55,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
--saturday
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 6, 10, 30, 12, 00,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
INSERT INTO "OperatingSchedule" ( "OperatingScheduleRefID", "DayOfTheWeek", "StartHour", "StartMinute", "EndHour", "EndMinute", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 6, 18, 10, 23, 55,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	
COMMIT TRANSACTION;


START TRANSACTION;
-- Primary Schedule
INSERT INTO "ScheduleSpecificProperties" ( "OperatingScheduleRefID",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- Secondary Schedule
INSERT INTO "ScheduleSpecificProperties" ( "OperatingScheduleRefID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(1,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');	

COMMIT TRANSACTION;


START TRANSACTION;
		--product -1
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 3, 10, 3, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 3, 10, 110, 150, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 11, 20, 3, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 11, 20, 110, 150, now(), 'Initial', now(), 'Initial');
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 21, 30, 3, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, -1, 0, 21, 30, 110, 150, now(), 'Initial', now(), 'Initial');		
			
		--product 0 - S product
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, -10, 10, 10, 15, 0.5, 10, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, -10, 10, 16, 30, 1.2, 20, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 11, 20, 10, 15, 2.4, 30,  now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 11, 20, 16, 30, 3.5, 40, now(), 'Initial', now(), 'Initial');
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 21, 30, 10, 15, 4.6, 50, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 21, 30, 16, 30, 6.7, 60, now(), 'Initial', now(), 'Initial');			
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 31, 40, 10, 15, 0.77625, 35, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 31, 40, 16, 30, 9.5, 80, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 41, 50, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 41, 50, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');		
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 51, 1000, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 51, 1000, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');	
		--product 1 - P product
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, -10, 10, 10, 15, 0.8, 10, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, -10, 10, 16, 30, 1.7, 20, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 11, 20, 10, 15, 2.9, 30,  now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 11, 20, 16, 30, 3.3, 40, now(), 'Initial', now(), 'Initial');
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 21, 30, 10, 15, 4.2, 50, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 21, 30, 16, 30, 6.9, 60, now(), 'Initial', now(), 'Initial');			
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 31, 40, 10, 15, 0.621, 35, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 31, 40, 16, 30, 9.1, 80, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 41, 50, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 41, 50, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');				
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 51, 1000, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 51, 1000, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');	
		
		--product 2 - O product
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, -10, 10, 10, 15, 0.8, 10, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, -10, 10, 16, 30, 1.4, 20, now(),'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 11, 20, 10, 15, 2.3, 30,  now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 11, 20, 16, 30, 3.2, 40, now(), 'Initial', now(), 'Initial');
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 21, 30, 10, 15, 4.9, 50, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 21, 30, 16, 30, 6.7, 60, now(), 'Initial', now(), 'Initial');			
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 31, 40, 10, 15, 15.525, 35, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 31, 40, 16, 30, 9.1, 80, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 41, 50, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 41, 50, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');				
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 51, 1000, 10, 15, 9.73, 85, now(), 'Initial', now(), 'Initial');	
		INSERT INTO "SprayLookUpTable" ("RegionID", "ProductID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure", "DispenseRate", "FlowRate", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 51, 1000, 16, 30, 9.97, 90, now(), 'Initial', now(), 'Initial');				
			
COMMIT TRANSACTION;


START TRANSACTION;
		
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 3, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 1, 3, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 0, 1.29, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 1, 1, 1.29, now(), 'Initial', now(), 'Initial');
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 0, 1.44, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 2, 1, 1.44, now(), 'Initial', now(), 'Initial');			
COMMIT TRANSACTION;


START TRANSACTION;
		INSERT INTO "DateFormat_Ref" ("DateFormatID", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0,  'A', now(), 'Initial', now(), 'Initial'); 
COMMIT TRANSACTION;


-- Create a default row for the SystemData
START TRANSACTION;
		INSERT INTO "SystemData" ("SystemDataID",  "RegionID", "OperatingModeID", "DateFormatID", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 0, 0, 'A', now(), 'Initial', now(), 'Initial'); 
COMMIT TRANSACTION;

START TRANSACTION;
INSERT INTO "BolierPropertiesForProducts" ( "SystemDataID", "UnitOfChoiceForDO", "FWDissolvedOxygen", "TargertBWSO3Residual" , "FWTotalHardness",  "EstimatedBWpH" ,  "BDPO4",  "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(0, 0, 0.1, 45, 0, 0, 0.5, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

COMMIT TRANSACTION;



-- Create a default row for the Customertable
START TRANSACTION;

		INSERT INTO "CustomerInfo" ("CustomerID", "CustomerName","Address", "Contact", "TMName", "PhoneNumber", "AccountNumber",  "DateInstalled", "LastResetDate", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			( 0, 'Test Account', 'Eagan.', '415 433-4600', 'John Carl Warnecke', '415 433-4600', '10037',  now(), now(), 'A', now(), 'Initial', now(), 'Initial'); 

		INSERT INTO "Password" ("PasswordID", "CustomerPassword", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			( 0, '1234', 'A', now(), 'Initial', now(), 'Initial'); 
COMMIT TRANSACTION;








START TRANSACTION;
--IO Comm Error to Smart Simon Board
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 1, 6001, True, True, 30, 600, 600,  True, True, 7001, 0, 0, 0, 2, now(), 'Initial', now(), 'Initial');
--IO Comm Error to Garfunkel Board	
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(1, 2, 6002, True, True, 30, 600, 600,  True, True, 7002, 0, 0, 0, 2, now(), 'Initial', now(), 'Initial');
--Over High temp alarm
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 3, 6003, True, True, 10, 600, 600,  True, True, 7003, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');		
--Sump overflow alarm
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(3, 4, 6004, True, True, 10, 600, 600,  True, True, 7004, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');	
--No O remains 	in both capsule
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(4, 5, 6005, True, True, 10, 0, 0,  True, False, 7005, 10, 0, 0, 2, now(),'Initial', now(), 'Initial');	
--Empty Sump alarm
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
	"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(5, 6, 6006, True, True, 10, 600, 600,  False, True, 7006,  10, 300, 300, 2, now(), 'Initial', now(), 'Initial');		
--Low Pressure Makeup	
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(6, 7, 6007, True, True, 10, 600, 600,  True, False, 7007, 10, 300, 300, 2,  now(), 'Initial', now(), 'Initial');	
--High temp alarm
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(7, 8, 6008, True, True, 5, 600, 600,  True, False, 7008,  5, 300, 300, 2,  now(), 'Initial', now(), 'Initial');
--Low temp alarm
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", 
"DeactivationNameStringID", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(8, 9, 6009, True, True, 5, 600, 600,  True, False, 7009, 5, 300, 300, 2, now(), 'Initial', now(), 'Initial');	


--O1 capsule Lid Open
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(9, 10, 6010, True, True, 10, 600, 600,  True, False, 7010, 30, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');
--O2 capsule Lid Open	
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(10, 11, 6011, True, True, 10, 600, 600,  True, False, 7011, 30, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');	
--S Block Lid Open
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(11, 12, 6012, True, True, 10, 600, 600,  True, False, 7012, 30, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');
--H2 Block Lid Open
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(12, 13, 6013, True, True, 10, 600, 600,  True, False, 7013, 30, 10, 300, 300, 2, now(), 'Initial', now(), 'Initial');	
	
	
--O1 Product Empty
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(13, 14, 6014, True, True, 10, 600, 600, False, False, 7014, 30, 10, 300, 300, 1, now(), 'Initial', now(), 'Initial');
--O2 Product Empty
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "DeactivationNameStringID", "DeactivationDisplayTimeout", "DeactivationDelay", "DeactivationCondorDelay", "DeactivationEnvisionDelay", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(14, 15, 6015, True, True, 10, 600, 600, False, False, 7015, 30, 10, 300, 300, 1,  now(), 'Initial', now(), 'Initial');

--S Product Empty
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(15, 16, 6016, True, True, 10, 600, 600,  True, False, 2, now(), 'Initial', now(), 'Initial');
--H2 Product Empty
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(16, 17, 6017, True, True, 10, 600, 600,  True, False, 2, now(), 'Initial', now(), 'Initial');	
-- S Low Product 
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(17, 18, 6018, True, True, 10, 600, 900,  False, False, 1,  now(), 'Initial', now(), 'Initial');
-- H2 Low Product 
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(18, 19, 6018, True, True, 10, 600, 900,  False, False, 1, now(), 'Initial', now(), 'Initial');
	

--Excessive Time since sump fill
--delay comes from TM input dependign on the operating schedule
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(19, 20, 6022, True, True, 10, 10, 10,  False, False, 1, now(), 'Initial', now(), 'Initial');	
--Exceed max time between BFWP calls for water
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(20, 21, 6023, True, True, 10, 900, 900,  False, False, 1, now(), 'Initial', now(), 'Initial');

--Internet connectivity lost	
INSERT INTO "Alarms"( "AlarmID", "Priority", "ActivationNameStringID", "IsEnvisionConfigurable", "IsEnvisionEnabled", "ActivationDelay", "ActivationCondorDelay", "ActivationEnvisionDelay", "StopSumpCreation", "StopDispenseOperation", "StatusType", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(21, 22, 6024, True, True, 7200, 7200, 7200,  False, False, 1, now(), 'Initial', now(), 'Initial');	
COMMIT TRANSACTION;

--TODO, add color codes
START TRANSACTION;
--IO Comm Error Smart Simon
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 0, 'red', now(), 'Initial', now(), 'Initial');
--IO Comm Error Garfunkel
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 1, 'red', now(), 'Initial', now(), 'Initial');	
--Over High Temp Alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 2, 'red', now(), 'Initial', now(), 'Initial');
--Sump overflow alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 3, 'red', now(), 'Initial', now(), 'Initial');
--No O remains 	in both capsule
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 4, 'red', now(), 'Initial', now(), 'Initial');
--Empty Sump alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 5, 'red', now(), 'Initial', now(), 'Initial');	
--Low Pressure Makeup
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 6, 'red', now(), 'Initial', now(), 'Initial');		
--High temp alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 7, 'yellow', now(), 'Initial', now(), 'Initial');
--Low temp alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 8, 'yellow', now(), 'Initial', now(), 'Initial');	
--O1 capsule lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 9, 'red', now(), 'Initial', now(), 'Initial');
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 9, false, 'green', now(), 'Initial', now(), 'Initial');
--O2 capsule lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 10, 'red', now(), 'Initial', now(), 'Initial');
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 10, false, 'green', now(), 'Initial', now(), 'Initial');	
--S block lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 11, 'red', now(), 'Initial', now(), 'Initial');	
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 11, false, 'green', now(), 'Initial', now(), 'Initial');
--P2 block lid open/close
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 12, 'red', now(), 'Initial', now(), 'Initial');
--close
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 12, false,  'green', now(), 'Initial', now(), 'Initial');
--O1 product empty/full
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 13, 'yellow', now(), 'Initial', now(), 'Initial');
--O1 product full	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 13, false, 'green', now(), 'Initial', now(), 'Initial');	
--O2 product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 14, 'yellow', now(), 'Initial', now(), 'Initial');
--O2 product full	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 14, false, 'green', now(), 'Initial', now(), 'Initial');	
--S product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 15, 'red', now(), 'Initial', now(), 'Initial');	
--H2 product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 16, 'red', now(), 'Initial', now(), 'Initial');	
--S product low
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 17, 'yellow', now(), 'Initial', now(), 'Initial');	
--P2 product low
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 18, 'yellow', now(), 'Initial', now(), 'Initial');
--Excessive Time since sump fill
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 19, 'yellow', now(), 'Initial', now(), 'Initial');
--Exceed max time between BFWP calls for water
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 20, 'yellow', now(), 'Initial', now(), 'Initial');	
--Internet connectivity lost	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(0, 21, 'yellow', now(), 'Initial', now(), 'Initial');	
COMMIT TRANSACTION;



START TRANSACTION;
--ExposedFunction
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('truncateeventlog', 1, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('getsizeofeventLog', 0, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('getspecificdatalogentrybyindex', 1, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('getspecificdatalogentrybydate', 1, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('geteventlogdataafterindex', 1, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('geteventlogdataafterindexandevent', 2, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('geteventlogcountafterindex', 1, 'Initial');
INSERT INTO "ExposedFunction" ("FunctionName", "NumberParameters", "CRE_OPER")
    VALUES ('geteventlogcountafterindexandevent', 2, 'Initial');
COMMIT TRANSACTION; 


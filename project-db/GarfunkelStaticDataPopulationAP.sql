-- Condor portion of the static data for AP

START TRANSACTION;

INSERT INTO "DefaultParameters"(
            "RegionID", "ParameterName", "Min", "Max", "StepSize", "DefaultValue", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES ('2', 'SystemOpMode', 0, 0, 0, 0, now(), 'Initial', now(), 'Initial');

INSERT INTO "DefaultParameters"(
            "RegionID", "ParameterName", "Min", "Max", "StepSize", "DefaultValue", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES ('2', 'UnitOfMeasure', 0, 0, 0, 0, now(), 'Initial', now(), 'Initial');


COMMIT TRANSACTION;


START TRANSACTION;


--Specialized strings : washer names 
	
--Specialized strings:  product names
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 7001, 'S Product', '', true, now(), 'Initial', now(), 'Initial');
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 7002, 'H2 Product', '', true, now(), 'Initial', now(), 'Initial');
INSERT INTO "LocalizedStrings"( "LanguageID", "StringID", "String", "StringCommonName", "SpecialString", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES (1, 7003, 'Caustic Product', '', true, now(), 'Initial', now(), 'Initial');

COMMIT TRANSACTION;	





START TRANSACTION;
-- S Block product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 0, 1, 7001,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
--  H2 Block product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 1, 2, 7002, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
	
--O capsule product
INSERT INTO "ProductInfo" ("RegionID", "ProductID", "ProductNo", "ProductName", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 2, 3, 7003, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');

	
COMMIT TRANSACTION;

START TRANSACTION;
--   S Block
INSERT INTO "SBlockProductProperties" ( "RegionID", "ProductID",  "IsInUse", "PercentSO3InBlock", "NaOHNeededToNeutralize", "PercentCHA", "PercentDEAE", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 0, true, 1.0, 0.5, 0.5, 0.5, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- P Block
INSERT INTO "PBlockProductProperties" ( "RegionID", "ProductID", "TotalAcidHardnessRatio", "TotalMolePercentAmine", "NaOHNeededToNeutralize", "PercentCHA", "PercentDEAE", "PercentPO4", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,  clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');
-- O Capsule	
INSERT INTO "OCapsuleProductProperties" ( "RegionID", "ProductID", "PercentNaOHInProduct", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
	VALUES(2, 2, 0.5, clock_timestamp(), 'Initial', clock_timestamp(), 'Initial');		

COMMIT TRANSACTION;



-- Create a default rows for the DispenserPocketInfo
START TRANSACTION;
		--S Block product slot
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(0, 0, 2,  now(), 'Initial', now(), 'Initial'); 
		--H2
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(1, 1, 2,  now(), 'Initial', now(), 'Initial'); 
		--O		
		INSERT INTO "ProductMapping" ("ProductSlotID", "ProductID", "RegionID", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 2, 2,  now(), 'Initial', now(), 'Initial'); 
COMMIT TRANSACTION;




START TRANSACTION;
		
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 0, 0, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 0, 1, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 1, 0, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 1, 1, 109, now(), 'Initial', now(), 'Initial');
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 2, 0, 109, now(), 'Initial', now(), 'Initial'); 
		INSERT INTO "ProductConcentrationForSpray" ("RegionID", "ProductID", "OperatingScheduleRefID", "ProdConc","CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
			(2, 2, 1, 109, now(), 'Initial', now(), 'Initial');			
COMMIT TRANSACTION;


--TODO, add color codes
START TRANSACTION;
--IO Comm Error Smart Simon
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 0, 'red', now(), 'Initial', now(), 'Initial');
--IO Comm Error Garfunkel
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 1, 'red', now(), 'Initial', now(), 'Initial');	
--Over High Temp Alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 2, 'red', now(), 'Initial', now(), 'Initial');
--Sump overflow alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 3, 'red', now(), 'Initial', now(), 'Initial');
--No O remains 	in both capsule
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 4, 'red', now(), 'Initial', now(), 'Initial');
--Empty Sump alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 5, 'red', now(), 'Initial', now(), 'Initial');	
--Low Pressure Makeup
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 6, 'red', now(), 'Initial', now(), 'Initial');		
--High temp alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 7, 'yellow', now(), 'Initial', now(), 'Initial');
--Low temp alarm
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 8, 'yellow', now(), 'Initial', now(), 'Initial');	
--O1 capsule lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 9, 'red', now(), 'Initial', now(), 'Initial');
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 9, false, 'green', now(), 'Initial', now(), 'Initial');
--O2 capsule lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 10, 'red', now(), 'Initial', now(), 'Initial');
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID", "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 10, false, 'green', now(), 'Initial', now(), 'Initial');	
--S block lid open
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 11, 'red', now(), 'Initial', now(), 'Initial');	
--close	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 11, false, 'green', now(), 'Initial', now(), 'Initial');
--P2 block lid open/close
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 12, 'red', now(), 'Initial', now(), 'Initial');
--close
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 12, false,  'green', now(), 'Initial', now(), 'Initial');
--O1 product empty/full
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 13, 'yellow', now(), 'Initial', now(), 'Initial');
--O1 product full	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 13, false, 'green', now(), 'Initial', now(), 'Initial');	
--O2 product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 14, 'yellow', now(), 'Initial', now(), 'Initial');
--O2 product full	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "IsActive", "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 14, false, 'green', now(), 'Initial', now(), 'Initial');	
--S product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 15, 'red', now(), 'Initial', now(), 'Initial');	
--H2 product empty
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 16, 'red', now(), 'Initial', now(), 'Initial');	
--S product low
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 17, 'yellow', now(), 'Initial', now(), 'Initial');	
--P2 product low
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 18, 'yellow', now(), 'Initial', now(), 'Initial');
--Excessive Time since sump fill
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 19, 'yellow', now(), 'Initial', now(), 'Initial');
--Exceed max time between BFWP calls for water
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 20, 'yellow', now(), 'Initial', now(), 'Initial');	
--Internet connectivity lost	
INSERT INTO "RegionSpecificAlarmProperties"( "RegionID", "AlarmID",  "ColorCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER")
    VALUES(2, 21, 'yellow', now(), 'Initial', now(), 'Initial');
COMMIT TRANSACTION;

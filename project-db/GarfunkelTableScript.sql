--  Setting this causes psql to stop when an error occurs in non interactive mode.
\set ON_ERROR_STOP true
create or replace function update_the_db() returns void as $$ 
begin      

-- Core table
-- DROP TABLE "SystemRegionID_Ref";
	if not exists(select * from information_schema.tables where table_name = 'SystemRegionID_Ref') then 
	CREATE TABLE "SystemRegion_Ref"
	(
	"RegionID" integer NOT NULL,
	"RegionName" integer NOT NULL,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
	CONSTRAINT "RegionID" PRIMARY KEY ("RegionID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "SystemRegion_Ref" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'DefaultParameters') then 
	CREATE TABLE "DefaultParameters"
	(
        "ParameterID" serial NOT NULL,
        "ParameterName" character varying(100) NOT NULL,
        "Min" real NOT NULL,
        "Max" real NOT NULL,
        "StepSize" real,
        "DefaultValue" real,
        "RegionID" integer NOT NULL,
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
        CONSTRAINT "ParameterID" PRIMARY KEY ("ParameterID"),
		CONSTRAINT "RegionID" FOREIGN KEY("RegionID")
        REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
        ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "DefaultParameters" OWNER TO db_user_admin;
	end if;

-- Table: "Language_Ref"
-- DROP TABLE "Language_Ref";
	if not exists(select * from information_schema.tables where table_name = 'Language_Ref') then 
	CREATE TABLE "Language_Ref"
	(
		"LanguageID" integer NOT NULL,
		"Description" character varying(50) NOT NULL,
		"LocaleID" character varying(12) NOT NULL, --this one is for localization with icu
		"Font" character varying(20) NOT NULL,
		"PointSize" integer NOT NULL default 26,
		"BoldFont" boolean NOT NULL default false,
		"FallbackFont" character varying(20) NOT NULL,
		"FallbackPointSize" integer NOT NULL default 26,
		"FallbackBoldFont" boolean NOT NULL default false,
		"StatusCode" character(1) NOT NULL default 'A',
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25)  NOT NULL,
		"MOD_DT" timestamp(6) without time zone,
		"MOD_OPER" character varying(25) ,
		CONSTRAINT "LanguageID" PRIMARY KEY ("LanguageID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "Language_Ref" OWNER TO db_user_admin;
	end if;
		
-- change for localized string tables		
	if not exists(select * from information_schema.tables where table_name = 'LocalizedStrings') then 
	CREATE TABLE "LocalizedStrings"
	(
        "LocalizedID" serial NOT NULL,
        "LanguageID" integer NOT NULL,
        "StringID" integer NOT NULL,
        "String" character varying(250) NOT NULL,
        "StringCommonName" character varying(50),
        "SpecialString" boolean NOT NULL default false,
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25)  NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
		CONSTRAINT "LocalizedID" PRIMARY KEY ("LocalizedID"),
        CONSTRAINT "LanguageID" FOREIGN KEY ("LanguageID")
            REFERENCES "Language_Ref" ("LanguageID") MATCH SIMPLE
            ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "LocalizedStrings" OWNER TO db_user_admin;
	end if;    
	

	if not exists(select * from information_schema.tables where table_name = 'ControllerData') then 
	CREATE TABLE "ControllerData"
	(
		"Description" character varying(25),
		"SerialNumber" character varying(25) default '123456',
		"BuildDate" timestamp(6) without time zone default now(),
		"MACAddress" character varying(25) default '000000',
		"SoftwareVersion" character varying(25) default '0.0.0',
		"Address" character varying(5) default 'A',
		"Instance" character varying(5) default 'a',
		"Identifier" character varying(50),
		"LastReset" timestamp without time zone,
		"LastLogin" timestamp without time zone
	)
	WITH (OIDS=TRUE)
	TABLESPACE garfunkel;
	ALTER TABLE "ControllerData" OWNER TO db_user_admin;
	end if;
	

	
-- Table: "CondorBusinessData"
-- DROP TABLE "CondorBusinessData";	
	if not exists(select * from information_schema.tables where table_name = 'CondorBusinessData') then 
	CREATE TABLE "CondorBusinessData"
	(
		"BusinessTypeID" integer NOT NULL,
		"BusinessType" character varying(50) NOT NULL,
		"InternalPort" integer NOT NULL DEFAULT 2345,
		"ExternalPort" integer NOT NULL DEFAULT 2346,
		"CRE_DT" timestamp(6) without time zone NOT NULL,
		"CRE_OPER" character(20) NOT NULL,
		"MOD_DT" timestamp(6) without time zone,
		"MOD_OPER" character varying(25) ,
	CONSTRAINT "BusinessTypeID" PRIMARY KEY ("BusinessTypeID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "CondorBusinessData" OWNER TO db_user_admin;
	COMMENT ON TABLE "CondorBusinessData" IS 'Defines the internal and export port numbers by business type for the communications server.';
	end if;


-- Table: "SystemOpMode_Ref"

	-- Core table
-- DROP TABLE "SystemOpMode_Ref";
	if not exists(select * from information_schema.tables where table_name = 'SystemOpMode_Ref') then 
	CREATE TABLE "SystemOpMode_Ref"
	(
	"SystemOpModeID" integer NOT NULL,
	"SystemOpModeName" integer NOT NULL,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
	CONSTRAINT "SystemOpModeID" PRIMARY KEY ("SystemOpModeID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "SystemOpMode_Ref" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'OperatingSchedule_Ref') then 
	CREATE TABLE "OperatingSchedule_Ref"
	(
	"OperatingScheduleRefID" integer NOT NULL,
	"ScheduleName" integer,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
	CONSTRAINT "OperatingScheduleRefID" PRIMARY KEY ("OperatingScheduleRefID"),
	CHECK ("OperatingScheduleRefID" =0 OR  "OperatingScheduleRefID" =1)
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "OperatingSchedule_Ref" OWNER TO db_user_admin;
	end if;

	
	if not exists(select * from information_schema.tables where table_name = 'OperatingSchedule') then 
	CREATE TABLE "OperatingSchedule"
	(
	"OperatingScheduleRefID" integer NOT NULL CHECK ("OperatingScheduleRefID" = 0),
	"StartHour" integer default 0,
	"StartMinute" integer default 0,
	"EndHour" integer default 23,
	"EndMinute" integer default 59,
	"DayOfTheWeek" integer NOT NULL default 0,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
--	CONSTRAINT "OperatingScheduleID" PRIMARY KEY ("OperatingScheduleRefID"), -- "DayOfTheWeek"),
	CONSTRAINT "OperatingScheduleRefID" FOREIGN KEY ("OperatingScheduleRefID")
	REFERENCES "OperatingSchedule_Ref" ("OperatingScheduleRefID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "OperatingSchedule" OWNER TO db_user_admin;
	end if;
	
	if not exists(select * from information_schema.tables where table_name = 'ScheduleSpecificProperties') then 
	CREATE TABLE "ScheduleSpecificProperties"
	(
	"OperatingScheduleRefID" integer NOT NULL,
	"TMEnteredPercentTimeBFWPIsOn" real,
	"CalculatedPercentTimeBFWPIsOn" real,
	"MaxTimeForFillEventsBeforeAlarm" integer default 2*24, --in hours
	"ActiveTreatmentPumpDutyCycle" real default 0.5,
	"NewTreatmentPumpDutyCycle" real default 0.5,
	--"NoFillEventLengthOfTime" integer,
	"PrimaryLanguage" integer NOT NULL DEFAULT 1,
	"TMLanguage" integer NOT NULL DEFAULT 1,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
	PRIMARY KEY ("OperatingScheduleRefID"),
	CONSTRAINT "OperatingScheduleRefID" FOREIGN KEY ("OperatingScheduleRefID")
	REFERENCES "OperatingSchedule_Ref" ("OperatingScheduleRefID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "ScheduleSpecificProperties" OWNER TO db_user_admin;
	end if;
	
	
	if not exists(select * from information_schema.tables where table_name = 'NozzleType_Ref') then     
    CREATE TABLE "NozzleType_Ref"
    (
	  "NozzleTypeRefID" integer NOT NULL, 
	  "NozzleTypeName" integer NOT NULL, 
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying (20),
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("NozzleTypeRefID")
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "NozzleType_Ref" OWNER TO db_user_admin;    
    end if;


    if not exists(select * from information_schema.tables where table_name = 'ProductSlot') then     
    CREATE TABLE "ProductSlot"
    (
	  "ProductSlotID" integer NOT NULL, 
	  "NozzleTypeRefID" integer NOT NULL,
	  "ProductSlotType" integer NOT NULL, --S, P2 , O1 or O2 product
	  "PredictedEmptyInHours" integer NOT NULL DEFAULT 0,
	  "ResetDate" timestamp(6) without time zone NOT NULL,
	  "TurnOffTitrationValues" BOOLEAN NOT NULL DEFAULT TRUE,
	  "RunTime" integer NOT NULL default 0,
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character(20) NULL NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductSlotID"),
	  CHECK ("ProductSlotID" < 4),	  
	  CONSTRAINT "NozzleTypeRefID" FOREIGN KEY ("NozzleTypeRefID")
	  REFERENCES "NozzleType_Ref" ("NozzleTypeRefID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION

    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "ProductSlot" OWNER TO db_user_admin;    
    end if;
	
	    if not exists(select * from information_schema.tables where table_name = 'ProductInfo') then     
    CREATE TABLE "ProductInfo"
    (
      "ProductID" integer NOT NULL,
	  "RegionID" integer NOT NULL,
--	  "ProductRefID" integer NOT NULL,
	  "ProductNo" integer NOT NULL,
	  "ProductName" integer NOT NULL,
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductID", "RegionID"),
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION
--	  CONSTRAINT "ProductRefID" FOREIGN KEY ("ProductRefID")
--	  REFERENCES "Product_Ref" ("ProductRefID") MATCH SIMPLE
--	  ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "ProductInfo" OWNER TO db_user_admin;    
    end if;

	if not exists(select * from information_schema.tables where table_name = 'SBlockProductProperties') then     
    CREATE TABLE "SBlockProductProperties"
    (
	  "ProductID" integer NOT NULL, 
	  "RegionID" integer NOT NULL,
	  "IsInUse" BOOLEAN NOT NULL DEFAULT TRUE, 
	  "PercentSO3InBlock" real, 
	  "NaOHNeededToNeutralize" real, 
	  "PercentCHA" real, 
	  "PercentDEAE" real,
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductID", "RegionID"),
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID" )
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "SBlockProductProperties" OWNER TO db_user_admin;    
    end if;
	
	if not exists(select * from information_schema.tables where table_name = 'PBlockProductProperties') then     
    CREATE TABLE "PBlockProductProperties"
    (
	  "ProductID" integer NOT NULL, 
	  "RegionID" integer NOT NULL,
	  "TotalAcidHardnessRatio" real, 
	  "TotalMolePercentAmine" real, 
	  "NaOHNeededToNeutralize" real, 
	  "PercentCHA" real, 
	  "PercentDEAE" real, 
	  "PercentPO4" real, 
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductID", "RegionID"),
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID" )
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "PBlockProductProperties" OWNER TO db_user_admin;    
    end if;
	
	if not exists(select * from information_schema.tables where table_name = 'OCapsuleProductProperties') then     
    CREATE TABLE "OCapsuleProductProperties"
    (
	  "ProductID" integer NOT NULL, 
	  "RegionID" integer NOT NULL,
	  "PercentNaOHInProduct" real, 
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductID", "RegionID"),
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID" )
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "OCapsuleProductProperties" OWNER TO db_user_admin;    
    end if;
	
	
	
-- DROP TABLE "ProductInfo";
	
    if not exists(select * from information_schema.tables where table_name = 'ProductConcentrationForSpray') then     
    CREATE TABLE "ProductConcentrationForSpray"
    (
      "ProductID" integer NOT NULL,
	  "RegionID" integer NOT NULL,
	  "OperatingScheduleRefID" integer NOT NULL,
      "ProdConc" real NOT NULL default 1, 
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	  PRIMARY KEY ("ProductID", "RegionID", "OperatingScheduleRefID"),
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID" )
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "OperatingScheduleRefID" FOREIGN KEY ("OperatingScheduleRefID")
	  REFERENCES "OperatingSchedule_Ref" ("OperatingScheduleRefID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION

    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "ProductConcentrationForSpray" OWNER TO db_user_admin;    
    end if;

	if not exists(select * from information_schema.tables where table_name = 'ProductMapping') then     
    CREATE TABLE "ProductMapping"
    (
      "ProductSlotID" integer NOT NULL,
	  "ProductID" integer NOT NULL,
	  "RegionID" integer NOT NULL,
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A',
	  PRIMARY KEY ("ProductSlotID", "ProductID", "RegionID"),
	  CHECK ("ProductSlotID" < 4),	
  	  CONSTRAINT "ProductSlotID" FOREIGN KEY ("ProductSlotID")
	  REFERENCES "ProductSlot" ("ProductSlotID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,	 
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID") 
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "ProductMapping" OWNER TO db_user_admin;    
    end if;
	
	
	if not exists(select * from information_schema.tables where table_name = 'SprayLookUpTable') then     
    CREATE TABLE "SprayLookUpTable"
    (
      "ProductID" integer NOT NULL,
	  "RegionID" integer NOT NULL,
	  "NozzleTypeRefID" integer NOT NULL,
	  "FromTemp" real NOT NULL,
	  "ToTemp" real NOT NULL,
	  "FromPressure" real NOT NULL,
	  "ToPressure" real NOT NULL,
	  "DispenseRate" real NOT NULL default 1,
	  "FlowRate" real NOT NULL default 1, 
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A',
	  PRIMARY KEY ("ProductID", "RegionID", "NozzleTypeRefID", "FromTemp", "ToTemp", "FromPressure", "ToPressure" ),	  
	  CONSTRAINT "ProductID" FOREIGN KEY ("ProductID", "RegionID") 
	  REFERENCES "ProductInfo" ("ProductID", "RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	  REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION,
	  CONSTRAINT "NozzleTypeRefID" FOREIGN KEY ("NozzleTypeRefID")
	  REFERENCES "NozzleType_Ref" ("NozzleTypeRefID") MATCH SIMPLE
	  ON UPDATE NO ACTION ON DELETE NO ACTION

    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "SprayLookUpTable" OWNER TO db_user_admin;    
    end if;

	if not exists(select * from information_schema.tables where table_name = 'DateFormat_Ref') then 
	CREATE TABLE "DateFormat_Ref"
	(
	"DateFormatID" integer NOT NULL,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25) ,
	CONSTRAINT "DateFormatID" PRIMARY KEY ("DateFormatID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "DateFormat_Ref" OWNER TO db_user_admin;
	end if;

	
	-- Core table
-- Table: "SystemData"
	-- Core table
-- DROP TABLE "SystemData";
	if not exists(select * from information_schema.tables where table_name = 'SystemData') then 
	CREATE TABLE "SystemData"
	(
	"SystemDataID" serial NOT NULL,
	"RegionID" integer NOT NULL,
	"PrimaryLanguage" integer NOT NULL DEFAULT 1,
	"TMLanguage" integer NOT NULL DEFAULT 1,
	"UnitOfMeasure" integer NOT NULL DEFAULT 0,
	"DecimalOrComma" BOOLEAN NOT NULL  default true,
	"IsTwelveHourFormat" BOOLEAN NOT NULL  default true, 
	"OperatingModeID" integer NOT NULL,
--	"DualOpSchedule" BOOLEAN NOT NULL DEFAULT true,
	"BoilerPressure" real,
	"IsDeareatorPresent" BOOLEAN NOT NULL DEFAULT true,
	"FWTemperature" real,
	"DAOperatingPressure" real,
	"CyclesOfConcentrationTarget" real NOT NULL DEFAULT 30,
	"NominalSteamFlow" real,
	"TotalCondensateReturn" real,
	"IsBFWPIntermittent" BOOLEAN NOT NULL DEFAULT true,
	"OperatingHoursPerDay" integer NOT NULL DEFAULT 24,
	"ReferenceIntervalForTreatmentPump" integer NOT NULL DEFAULT 30,
	"TreatmentPumpCalibrationValue" real NOT NULL DEFAULT 1.88, --ml/sec 113.5624, --ml/min
	"BFWPSignalFilterTime" integer NOT NULL DEFAULT 4,
	"MaxTimeBetweenBFWPCallsInHours" integer NOT NULL DEFAULT 96,
	"MaxTimeForFillEventToComplete" integer NOT NULL DEFAULT 120, --TODO , add correct number, for leaks
	"VirtualCounterVolumeInMl" real NOT NULL DEFAULT 3000, --0.79 gallons  (3000ml)
	"SumpLowToFullVolumeInGallon" real NOT NULL DEFAULT 1.056688, --4000ml
	"SumpFullToOverFlowVolumeInGallon" real NOT NULL DEFAULT 1.849204, --7000ml
	"SumpOverFlowToAboveVolumeInGallon" real NOT NULL DEFAULT 0.5283441, --2000ml
	"TimeDateOfStartOfLastFillEvent" timestamp without time zone default now(),
	"TimeBetweenFillEvents" real default 0,
	"TimeDateOfLastBFWPSignalReceived" timestamp without time zone default now(),
	"TimeBetweenBFWPEvents" real default 0,
	"TimeDatePowerOn" timestamp without time zone,
	"CausticRinseStartTime" timestamp without time zone,
	"CausticRinseFinishTime" timestamp without time zone,
	"SystemStandby"  BOOLEAN NOT NULL DEFAULT false,
	"IsSystemInitialized" BOOLEAN NOT NULL DEFAULT false,
	"BaselineConductivity" real default 1000,
	"LastSumpCreateTempInDegreeC" real default 40, --TODO, add correct temp
	"LastSprayType" integer default 0,
	"LayupEnabled" BOOLEAN NOT NULL  default false,
	"TimeTreatmentPumpRunSinceEmptyLevelSump" real default 0, --to track virtual counter
	"DateFormatID" integer NOT NULL,	
	"SystemPressure" real NOT NULL default 15, --in psi, need to metric
	"StatusCode" character(1) NOT NULL default 'A', 
	"CRE_DT" timestamp without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp without time zone,
	"MOD_OPER" character varying(25),
	CONSTRAINT "SystemDataID" PRIMARY KEY ("SystemDataID"),
    CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
	REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT "OperatingModeID" FOREIGN KEY ("OperatingModeID")
	REFERENCES "SystemOpMode_Ref" ("SystemOpModeID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT "DateFormatID" FOREIGN KEY ("DateFormatID")
	REFERENCES "DateFormat_Ref" ("DateFormatID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "SystemData" OWNER TO db_user_admin;
	end if;

	
	if not exists(select * from information_schema.tables where table_name = 'BoilerPropertiesForProducts') then     
    CREATE TABLE "BoilerPropertiesForProducts"
    (
      "SystemDataID" integer NOT NULL,
	  "UnitOfChoiceForDO" integer NOT NULL,
	  "FWDissolvedOxygen" real,
      "TargertBWSO3Residual" integer NOT NULL default 0, 
	  "FWTotalHardness" real,
	  "EstimatedBWpH" real,
	  "CaTOMgMoleRatio" real default 2,
	  "BDPO4" real,
	  "MWTCa" real default 40.08,
	  "MWTMg" real default 24.305,
	  "MWTCaCO3" real default 100.0892,
	  "MWTPO4" real default 94.9714,
      "CRE_DT" timestamp(6) without time zone NOT NULL,
      "CRE_OPER" character varying(25) NOT NULL,
      "MOD_DT" timestamp(6) without time zone,
      "MOD_OPER" character varying(25) NOT NULL,
	  "StatusCode" character(1) NOT NULL default 'A', 
	   CONSTRAINT "SystemDataID" FOREIGN KEY ("SystemDataID")
	REFERENCES "SystemData" ("SystemDataID") MATCH SIMPLE
	ON UPDATE NO ACTION ON DELETE NO ACTION
    )
    WITH (
      OIDS=FALSE
    )
    TABLESPACE garfunkel;
    ALTER TABLE "BoilerPropertiesForProducts" OWNER TO db_user_admin;    
    end if;

	if not exists(select * from information_schema.tables where table_name = 'Alarms') then 
	CREATE TABLE "Alarms"
	(
        "AlarmID" integer NOT NULL,
		"Priority" integer NOT NULL,
		"IsEnvisionConfigurable" BOOLEAN NOT NULL DEFAULT TRUE,
		"IsEnvisionEnabled" BOOLEAN NOT NULL DEFAULT TRUE,
		"StopSumpCreation" BOOLEAN NOT NULL DEFAULT FALSE,
		"StopDispenseOperation" BOOLEAN NOT NULL DEFAULT FALSE,
        "ActivationNameStringID" integer NOT NULL,
		"ActivationDisplayTimeout" integer NOT NULL default -1,
		"ActivationDelay" integer NOT NULL,
		"ActivationCondorDelay" integer NOT NULL,
		"ActivationEnvisionDelay" integer NOT NULL,
        "DeactivationNameStringID" integer NOT NULL default -1,
		"DeactivationDisplayTimeout" integer NOT NULL default 30,
		"DeactivationDelay" integer NOT NULL default 10,
		"DeactivationCondorDelay" integer NOT NULL default 300,
		"DeactivationEnvisionDelay" integer NOT NULL default 300,
		"IsActive" BOOLEAN NOT NULL default false,
		"StatusType" integer default 2, --only for MCA
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
        CONSTRAINT "AlarmID" PRIMARY KEY ("AlarmID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "Alarms" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'RegionSpecificAlarmProperties') then 
	CREATE TABLE "RegionSpecificAlarmProperties"
	(
		"AlarmID" integer NOT NULL,
		"RegionID" integer NOT NULL,
		"IsActive" BOOLEAN NOT NULL default TRUE,
		"ColorCode" character varying(10),
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
		PRIMARY KEY ("AlarmID", "RegionID", "IsActive"),
		CONSTRAINT "AlarmID" FOREIGN KEY ("AlarmID")
		REFERENCES "Alarms" ("AlarmID") MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
		CONSTRAINT "RegionID" FOREIGN KEY ("RegionID")
		REFERENCES "SystemRegion_Ref" ("RegionID") MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "RegionSpecificAlarmProperties" OWNER TO db_user_admin;
	end if;
	
	if not exists(select * from information_schema.tables where table_name = 'InputType_Ref') then 
	CREATE TABLE "InputType_Ref"
	(
		"InputTypeRefID" integer NOT NULL,
		"Desc" integer,
		"StatusCode" character(1) NOT NULL default 'A',
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
		PRIMARY KEY ("InputTypeRefID")   
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "InputType_Ref" OWNER TO db_user_admin;
	end if;
	
	if not exists(select * from information_schema.tables where table_name = 'CustomerInputSignal') then 
	CREATE TABLE "CustomerInputSignal"
	(
        "ID" serial NOT NULL,
		"InputTypeRefID" integer NOT NULL,
		"InputName" integer,
		"IsEnabled" BOOLEAN NOT NULL DEFAULT FALSE,
		"Is4To20maType" BOOLEAN NOT NULL DEFAULT FALSE,
		"StatusCode" character(1) NOT NULL default 'A',
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
		PRIMARY KEY ("ID"),   
		CONSTRAINT "InputTypeRefID" FOREIGN KEY ("InputTypeRefID")
		REFERENCES "InputType_Ref" ("InputTypeRefID") MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION		
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "CustomerInputSignal" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'RegulatoryLimits') then 
	CREATE TABLE "RegulatoryLimits"
	(
        "ID" serial NOT NULL,
		"T3ActiveFDALimitInBW" real,
		"CHAActiveLimitInSteam" real,
		"HVACAirSpecificVolume " real,
		"STEAMInjectionRate" real,
		"PercentSteamInjection" real,
		"CHAOdorLimitSteam " real,
		"DEAEOdorLimitSteam " real,
		"StatusCode" character(1) NOT NULL default 'A',
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25) ,
		PRIMARY KEY ("ID")  
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "RegulatoryLimits" OWNER TO db_user_admin;
	end if;
	
	if not exists(select * from information_schema.tables where table_name = 'CustomerInfo') then 
	CREATE TABLE "CustomerInfo"
	(
        "CustomerID" integer NOT NULL,
		"CustomerName" character varying(20),
		"Address" character varying(50),
		"Contact" character varying(20),
		"TMName" character varying(20),
		"PhoneNumber" character varying(20),
		"AccountNumber" character varying(20),
		"DateInstalled" timestamp without time zone,
		"LastResetDate" timestamp without time zone,
		"StatusCode" character(1) NOT NULL default 'A',
		"CRE_DT" timestamp without time zone NOT NULL,
		"CRE_OPER" character varying(25) NOT NULL,
		"MOD_DT" timestamp without time zone,
		"MOD_OPER" character varying(25)        
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "CustomerInfo" OWNER TO db_user_admin;
	end if;

    if not exists(select * from information_schema.tables where table_name = 'Password') then
    CREATE TABLE "Password"
    (
        "PasswordID" integer NOT NULL,
--        "MasterPassword" character varying(6),
--        "EcolabMasterPassword" character varying(6),
        "CustomerPassword" character varying(6),
        "StatusCode" character(1) NOT NULL default 'A',
        "CRE_DT" timestamp without time zone NOT NULL,
        "CRE_OPER" character varying(25) NOT NULL,
        "MOD_DT" timestamp without time zone,
        "MOD_OPER" character varying(25)
    )
    WITH (OIDS=FALSE)
    TABLESPACE garfunkel;
    ALTER TABLE "Password" OWNER TO db_user_admin;
	end if;

	 if not exists(select * from information_schema.tables where table_name = 'DBSyncState') then
    CREATE TABLE "DBSyncState"
    (
		"SyncID" integer NOT NULL default 1,
        "SyncStop" boolean NOT NULL default false,
        "CRE_DT" timestamp without time zone NOT NULL,
        "CRE_OPER" character varying(25) NOT NULL,
        "MOD_DT" timestamp without time zone,
        "MOD_OPER" character varying(25) ,
		CHECK ("SyncID" = 1)
    )
    WITH (OIDS=FALSE)
    TABLESPACE garfunkel;
    ALTER TABLE "DBSyncState" OWNER TO db_user_admin;
	end if;
    
	if not exists(select * from information_schema.tables where table_name = 'ExposedFunction') then
	CREATE TABLE "ExposedFunction"
	(
	"ExposedFunctionID" SERIAL NOT NULL,
	"FunctionName" CHARACTER VARYING(100) NOT NULL,
	"NumberParameters" INTEGER NOT NULL,
	"StatusCode" CHARACTER(1) NOT NULL DEFAULT 'A',
	"CRE_DT" TIMESTAMP(6) WITHOUT TIME ZONE NOT NULL DEFAULT NOW(),
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" TIMESTAMP(6) WITHOUT TIME ZONE,
	"MOD_OPER" character varying(25) ,
	CONSTRAINT "ExposedFunctionID" PRIMARY KEY ("ExposedFunctionID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "ExposedFunction" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'BFWPOnTimes') then 
	CREATE TABLE "BFWPOnTimes"
	(
	"BFWPOnTimesID" SERIAL NOT NULL,
	"OperatingScheduleRefID" integer NOT NULL,
	"OnTime" timestamp without time zone default now(),
	"DurationInMinutes" real,
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25)
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "BFWPOnTimes" OWNER TO db_user_admin;
	end if;
	
	if not exists(select * from information_schema.tables where table_name = 'BFWPOnTimesWeekAverage') then 
	CREATE TABLE "BFWPOnTimesWeekAverage"
	(
	"BFWPOnTimesWeekAverageID" SERIAL NOT NULL,
	"OperatingScheduleRefID" integer NOT NULL,
	"OnTime" timestamp without time zone default now(),
	"DurationInMinutes" real,
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25)
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkel;
	ALTER TABLE "BFWPOnTimesWeekAverage" OWNER TO db_user_admin;
	end if;
	
	
	end;

$$ language 'plpgsql';  select update_the_db(); drop function update_the_db(); 

-- Set up the table permissions and securities

-- Revoke all table access from public
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ControllerData" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Alarms" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" FROM PUBLIC;

REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemData" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Password" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemOpMode_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" FROM PUBLIC;


-- Admin and controller have access to everything

-- revoke admin
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" FROM db_user_admin;
--REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemDefaults" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ControllerData" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Alarms" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemData" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Password" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemOpMode_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" FROM db_user_admin; 
-- revoke controller
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" FROM db_controller;
--REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemDefaults" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ControllerData" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Alarms" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemData" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Password" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemOpMode_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" FROM db_controller;  
-- revoke tablet user
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ControllerData" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Alarms" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SystemData" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "Password" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" FROM db_tablet_user;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" FROM db_tablet_user;

-- Grant for db_user_admin
-- Grant admin
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ControllerData" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Alarms" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemData" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Password" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemOpMode_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" TO db_user_admin;

-- Grant for db_controller
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemRegion_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "DefaultParameters" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Language_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "LocalizedStrings" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ControllerData" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Alarms" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "BFWPOnTimes" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CondorBusinessData" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemData" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductInfo" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductSlot" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "RegionSpecificAlarmProperties" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CustomerInfo" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "Password" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "DBSyncState" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ExposedFunction" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "BoilerPropertiesForProducts" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "CustomerInputSignal" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "InputType_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "NozzleType_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "PBlockProductProperties" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SBlockProductProperties" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OCapsuleProductProperties" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "OperatingSchedule_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductConcentrationForSpray" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ProductMapping" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "RegulatoryLimits" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "ScheduleSpecificProperties" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SystemOpMode_Ref" TO db_controller;
GRANT INSERT, DELETE, UPDATE, SELECT ON "SprayLookUpTable" TO db_controller;

-- Grant for the tablet user
GRANT SELECT ON "SystemRegion_Ref" TO db_tablet_user;
GRANT SELECT ON "DefaultParameters" TO db_tablet_user;
GRANT SELECT ON "Language_Ref" TO db_tablet_user;
GRANT SELECT ON "LocalizedStrings" TO db_tablet_user;
GRANT SELECT ON "ControllerData" TO db_tablet_user;
GRANT SELECT ON "Alarms" TO db_tablet_user;
GRANT SELECT ON "BFWPOnTimes" TO db_tablet_user;
GRANT SELECT ON "CondorBusinessData" TO db_tablet_user;
GRANT SELECT ON "SystemData" TO db_tablet_user;
GRANT SELECT ON "ProductInfo" TO db_tablet_user;
GRANT SELECT ON "RegionSpecificAlarmProperties" TO db_tablet_user;
GRANT SELECT ON "CustomerInfo" TO db_tablet_user;
GRANT SELECT ON "Password" TO db_tablet_user;
GRANT SELECT ON "ProductSlot" TO db_tablet_user;
GRANT SELECT ON "DBSyncState" TO db_tablet_user;
GRANT SELECT ON "ExposedFunction" TO db_tablet_user;
GRANT SELECT ON "BoilerPropertiesForProducts" TO db_tablet_user;
GRANT SELECT ON "CustomerInputSignal" TO db_tablet_user;
GRANT SELECT ON "InputType_Ref" TO db_tablet_user;
GRANT SELECT ON "NozzleType_Ref" TO db_tablet_user;
GRANT SELECT ON "PBlockProductProperties" TO db_tablet_user;
GRANT SELECT ON "SBlockProductProperties" TO db_tablet_user;
GRANT SELECT ON "OCapsuleProductProperties" TO db_tablet_user;
GRANT SELECT ON "OperatingSchedule" TO db_tablet_user;
GRANT SELECT ON "OperatingSchedule_Ref" TO db_tablet_user;
GRANT SELECT ON "ProductConcentrationForSpray" TO db_tablet_user;
GRANT SELECT ON "ProductMapping" TO db_tablet_user;
GRANT SELECT ON "RegulatoryLimits" TO db_tablet_user;
GRANT SELECT ON "ScheduleSpecificProperties" TO db_tablet_user;
GRANT SELECT ON "SystemOpMode_Ref" TO db_tablet_user;
GRANT SELECT ON "SprayLookUpTable" TO db_tablet_user;

GRANT CONNECT ON DATABASE "Garfunkel" TO db_tablet_user;
GRANT CONNECT ON DATABASE "Garfunkel" TO db_controller;
GRANT CONNECT ON DATABASE "Garfunkel" TO db_user_admin;

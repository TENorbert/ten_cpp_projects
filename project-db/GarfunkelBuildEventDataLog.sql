-- Build the external EventDataLog table
\set ON_ERROR_STOP true
-- create the table structure
create or replace function update_the_db() returns void as $$ 
begin      
	if not exists(select * from information_schema.tables where table_name = 'EventDataLog_Ref') then 
	CREATE TABLE "EventDataLog_Ref"
	(
	"EventDataLogID" integer NOT NULL,
	"EventDataLogName" character varying(50) NOT NULL,
	"StatusCode" character(1) NOT NULL default 'A',
	"CRE_DT" timestamp(6) without time zone NOT NULL,
	"CRE_OPER" character varying(25) NOT NULL,
	"MOD_DT" timestamp(6) without time zone,
	"MOD_OPER" character varying(25),
	CONSTRAINT "EventDataLogId" PRIMARY KEY ("EventDataLogID")
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkelext;
	ALTER TABLE "EventDataLog_Ref" OWNER TO db_user_admin;
	end if;

	if not exists(select * from information_schema.tables where table_name = 'EventDataLog') then 
	CREATE TABLE "EventDataLog"
	(
        "EventID" serial NOT NULL,
        "EventDataLogID" integer NOT NULL,
        "SubEventFlags" integer NOT NULL,
        "DataOne" real NOT NULL,
        "DataTwo" real NOT NULL,
        "DataThree" real NOT NULL,
        "DataFour" real NOT NULL,
		"DataFive" real NOT NULL,
        "DataSix" real NOT NULL,
        "EventDateTime" timestamp without time zone,
        "MOD_OPER" character varying(25),
        CONSTRAINT "EventID" PRIMARY KEY ("EventID"),
        CONSTRAINT "EventDataLogID" FOREIGN KEY ("EventDataLogID")
            REFERENCES "EventDataLog_Ref" ("EventDataLogID") MATCH SIMPLE
            ON UPDATE NO ACTION ON DELETE NO ACTION
	)
	WITH (OIDS=FALSE)
	TABLESPACE garfunkelext;
	ALTER TABLE "EventDataLog" OWNER TO db_user_admin;
	end if;
    


end;
$$ language 'plpgsql';  select update_the_db(); drop function update_the_db(); 


DROP INDEX IF EXISTS edl_datetime_eventid;
DROP TYPE IF EXISTS EventType CASCADE;


CREATE INDEX CONCURRENTLY edl_datetime_eventid ON "EventDataLog" ("EventDateTime" , "EventID") TABLESPACE garfunkelext; 
CREATE TYPE EventType AS (EventID int, EventDateTime timestamp without time zone, EventDataLogID int, SubEventFlags int, MOD_OPER character(8), DataOne real, DataTwo real, DataThree real, DataFour real);
ALTER TYPE EventType OWNER TO db_user_admin;

REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" FROM db_tablet_user;

GRANT INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "EventDataLog_Ref" TO db_controller;
GRANT SELECT ON "EventDataLog_Ref" TO db_tablet_user;

REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" FROM PUBLIC;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" FROM db_user_admin;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" FROM db_controller;
REVOKE INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" FROM db_tablet_user;



GRANT INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" TO db_user_admin;
GRANT INSERT, DELETE, UPDATE, SELECT ON "EventDataLog" TO db_controller;
GRANT SELECT ON "EventDataLog" TO db_tablet_user;


GRANT TRUNCATE ON "EventDataLog" TO db_controller;
GRANT UPDATE, SELECT ON "EventDataLog_EventID_seq" TO db_user_admin;
GRANT UPDATE, SELECT ON "EventDataLog_EventID_seq" TO db_controller;


CREATE OR REPLACE FUNCTION AddEventToLog(datalogid integer, subflags integer, dataone real, datatwo real, datathree real, datafour real,  userid character(8)) RETURNS void AS $$
BEGIN

	INSERT INTO "EventDataLog" ("EventDataLogID", "SubEventFlags", "DataOne", "DataTwo", "DataThree", "DataFour", "MOD_OPER", "EventDateTime")
		VALUES($1, $2, $3, $4, $5, $6, $7, now());
	RAISE NOTICE 'EventDataLogID= %', $1;	
	RAISE NOTICE 'SubEventFlags= %', $2;	
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION AddEventToLog(integer, integer, real, real, real, real, character(8)) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION TruncateEventLog(Operator character(8)) RETURNS INTEGER AS $$
DECLARE
	retType integer;
BEGIN
    -- Truncate the event log table and add a initialized line
    TRUNCATE TABLE "EventDataLog";
    -- Insert the initialize into the event log this occurs after the initialization.
    INSERT INTO "EventDataLog" ("EventDataLogID", "SubEventFlags", "DataOne", "DataTwo", "DataThree", "DataFour", "MOD_OPER", "EventDateTime")
        VALUES(1, -1, -1, -1, -1, -1, $1, clock_timestamp());
    
    IF( (SELECT COUNT(*) FROM "EventDataLog") = 1 ) THEN
        retType := 0;
    ELSE
        retType := 1;
    END IF;
            
	RETURN retType;		
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION TruncateEventLog(character(8)) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetSizeOfEventLog() RETURNS INTEGER AS $$
DECLARE
	numberOfRows  integer;
BEGIN
	
	SELECT COUNT(*) INTO numberOfRows FROM "EventDataLog";
	
	RETURN numberOfRows;
END		
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetSizeOfEventLog() OWNER TO db_user_admin;



CREATE OR REPLACE FUNCTION GetSpecificDataLogEntryByIndex(index integer) RETURNS EventType AS $$
DECLARE
	numberOfRecords integer;
	index 			integer;
	retValue		EventType;
BEGIN
	SELECT COUNT(*) INTO numberOfRecords FROM "EventDataLog";
	
	index := $1;
	
	-- If the number of records is exceeded 
	IF((numberOfRecords > 0) AND (index > (numberOfRecords - 1))) THEN
		index = numberOfRecords - 1;
	END IF;

	SELECT edl."EventID", edl."EventDateTime", edl."EventDataLogID", edl."SubEventFlags", edl."MOD_OPER", edl."DataOne", edl."DataTwo", 
		edl."DataThree", edl."DataFour"
		INTO retValue.EventID,  retValue.EventDateTime, retValue.EventDataLogID, retValue.SubEventFlags, retValue.MOD_OPER, 
			retValue.DataOne, retValue.DataTwo, retValue.DataThree, retValue.DataFour
		FROM "EventDataLog" AS edl
			JOIN "EventDataLog_Ref" AS edlr on edlr."EventDataLogID" = edl."EventDataLogID"
			ORDER BY edl."EventDateTime" ASC LIMIT 1 OFFSET index;
		
	return retValue;
END;		
$$ LANGUAGE plpgsql;
ALTER FUNCTION GetSpecificDataLogEntryByIndex(integer) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetSpecificDataLogEntryByDate(date character varying(25)) RETURNS SETOF EventType AS $$
	SELECT edl."EventID", edl."EventDateTime", edl."EventDataLogID", edl."SubEventFlags", edl."MOD_OPER", edl."DataOne", edl."DataTwo", 
		edl."DataThree", edl."DataFour" FROM "EventDataLog" AS edl
		JOIN "EventDataLog_Ref" AS edlr on edlr."EventDataLogID" = edl."EventDataLogID"	
			WHERE (edl."EventDateTime" >= to_timestamp($1, 'YYYY Month DD HH24:MI:SS')) 
			ORDER BY edl."EventDateTime" ASC LIMIT 1; 
$$ LANGUAGE SQL;
ALTER FUNCTION GetSpecificDataLogEntryByDate(character varying) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetEventLogDataAfterIndex(index integer) RETURNS SETOF EventType AS $$

	SELECT  edl."EventID", edl."EventDateTime", edl."EventDataLogID", edl."SubEventFlags", edl."MOD_OPER", edl."DataOne", edl."DataTwo", 
		edl."DataThree", edl."DataFour"
		FROM "EventDataLog" edl  WHERE "EventID" >= $1 LIMIT 10000;
	
$$ LANGUAGE SQL;
ALTER FUNCTION GetEventLogDataAfterIndex(integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetEventLogDataAfterIndexAndEvent(index integer, eventCode integer) RETURNS SETOF EventType AS $$

	SELECT edl."EventID", edl."EventDateTime", edl."EventDataLogID", edl."SubEventFlags", edl."MOD_OPER", edl."DataOne", edl."DataTwo", 
		edl."DataThree", edl."DataFour"
		FROM "EventDataLog" edl WHERE "EventID" >= $1 AND "EventDataLogID" = $2 LIMIT 10000;

$$ LANGUAGE SQL;
ALTER FUNCTION GetEventLogDataAfterIndexAndEvent(integer, integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetEventLogCountAfterIndex(index integer) RETURNS bigint AS $$
	SELECT COUNT(*) FROM "EventDataLog" WHERE "EventID" >= $1;
$$ LANGUAGE SQL;
ALTER FUNCTION GetEventLogCountAfterIndex(integer) OWNER TO db_user_admin;

CREATE OR REPLACE FUNCTION GetEventLogCountAfterIndexAndEvent(index integer, eventCode integer) RETURNS bigint AS $$
	SELECT COUNT(*) FROM "EventDataLog" WHERE "EventID" >= $1 AND "EventDataLogID" = $2;
$$ LANGUAGE SQL;
ALTER FUNCTION GetEventLogCountAfterIndexAndEvent(integer, integer) OWNER TO db_user_admin;


CREATE OR REPLACE FUNCTION GetEventDataLog() RETURNS SETOF "EventDataLog" as $$

    SELECT * FROM "EventDataLog";
      
$$ LANGUAGE SQL;
ALTER FUNCTION GetEventDataLog() OWNER to db_user_admin;

-- EventDataLog_Ref table:
CREATE OR REPLACE FUNCTION GetEventDataLogRef() RETURNS SETOF "EventDataLog_Ref" as $$

    SELECT * FROM "EventDataLog_Ref";
      
$$ LANGUAGE SQL;
ALTER FUNCTION GetEventDataLogRef() OWNER to db_user_admin;


-- Removal trigger, 
DROP TRIGGER IF EXISTS "EventDataLogInsertTrigger" ON "EventDataLog";

CREATE OR REPLACE FUNCTION "EDLInsertTrigger"()
  RETURNS trigger AS
$BODY$
DECLARE
    sizeOfTable  integer;
BEGIN
    
     select n_live_tup into sizeOfTable from pg_stat_user_tables where relname = 'EventDataLog';
    
    -- 2.75m rows of data for the internal EventDataLog table, this is ~750MB
    IF(sizeOfTable > 2750000) THEN
        
        DELETE FROM "EventDataLog" WHERE "EventDateTime" IN 
            (SELECT "EventDateTime" FROM "EventDataLog" 
                WHERE ("EventDateTime" < (now() - INTERVAL '6 month')) ORDER BY "EventID" ASC LIMIT 1000 );
        
        -- ZERO rows were deleted, now removal of oldest 10 rows is required.
        IF NOT FOUND THEN
            DELETE FROM "EventDataLog" WHERE "EventID" IN
                (SELECT "EventID" FROM "EventDataLog" ORDER BY "EventID" ASC LIMIT 10); 
        END IF;
    END IF;
    

return NULL;

END
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "EDLInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "EDLInsertTrigger"() IS 'This will be used to check the size of the table to remove old rows';

CREATE TRIGGER "EventDataLogInsertTrigger" AFTER INSERT ON "EventDataLog"
FOR EACH ROW EXECUTE PROCEDURE "EDLInsertTrigger"();


START TRANSACTION;

INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(1, 'Initialize', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(2, 'Application Startup', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(3, 'Alarm/Alerts', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(4, 'Date/Time Change', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(5, 'Operational Parameter Changed', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(6, 'Events', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(7, 'TM Menu Accessed', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(8, 'System Reset', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(9, 'Diagnostics', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(10, 'System Standby', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(11, 'Event 11', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(12, 'Event 12', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(13, 'Event 13', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(14, 'Event 14', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(15, 'Event 15', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(16, 'Event 16', 'A', now(), 'Initial', now(), 'Initial');
INSERT INTO "EventDataLog_Ref" ("EventDataLogID", "EventDataLogName", "StatusCode", "CRE_DT", "CRE_OPER", "MOD_DT", "MOD_OPER") VALUES
	(17, 'Event 17', 'A', now(), 'Initial', now(), 'Initial');
COMMIT TRANSACTION;

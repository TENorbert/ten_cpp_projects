-- Database triggers

-- SystemData table, this will contain triggers for INSERT, UPDATE, and DELETE

-- Drop the notification triggers
DROP TRIGGER IF EXISTS "SystemDataInsertTrigger" ON "SystemData";
DROP TRIGGER IF EXISTS "SystemDataUpdateTrigger" ON "SystemData";
DROP TRIGGER IF EXISTS "SystemDataDeleteTrigger" ON "SystemData";

-- Create the INSERT trigger for the SystemData table
CREATE OR REPLACE FUNCTION "SDInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SystemData', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SDInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SDInsertTrigger"() IS 'This is an insert notification trigger for System Data';

CREATE TRIGGER "SystemDataInsertTrigger" AFTER INSERT ON "SystemData"
FOR EACH ROW EXECUTE PROCEDURE "SDInsertTrigger"();

-- Create the UPDATE trigger for the SystemData table
CREATE OR REPLACE FUNCTION "SDUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SystemData', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SDUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SDUpdateTrigger"() IS 'This is an update notification trigger for System Data';

CREATE TRIGGER "SystemDataUpdateTrigger" AFTER UPDATE ON "SystemData"
FOR EACH ROW EXECUTE PROCEDURE "SDUpdateTrigger"();

-- Create the DELETE trigger for the SystemData table
CREATE OR REPLACE FUNCTION "SDDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SystemData', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SDDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SDDeleteTrigger"() IS 'This is an delete notification trigger for System Data';

CREATE TRIGGER "SystemDataDeleteTrigger" AFTER DELETE ON "SystemData"
FOR EACH ROW EXECUTE PROCEDURE "SDDeleteTrigger"();



-- Drop the notification triggers
DROP TRIGGER IF EXISTS "ProductInfoInsertTrigger" ON "ProductInfo";
DROP TRIGGER IF EXISTS "ProductInfoUpdateTrigger" ON "ProductInfo";
DROP TRIGGER IF EXISTS "ProductInfoDeleteTrigger" ON "ProductInfo";

-- Create the INSERT trigger for the ProductInfo table
CREATE OR REPLACE FUNCTION "PDIInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductInfo', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PDIInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PDIInsertTrigger"() IS 'This is an insert notification trigger for ProductInfo';

CREATE TRIGGER "ProductInfoInsertTrigger" AFTER INSERT ON "ProductInfo"
FOR EACH ROW EXECUTE PROCEDURE "PDIInsertTrigger"();

-- Create the UPDATE trigger for the ProductInfo table
CREATE OR REPLACE FUNCTION "PDIUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductInfo', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PDIUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PDIUpdateTrigger"() IS 'This is an update notification trigger for ProductInfo';

CREATE TRIGGER "ProductInfoUpdateTrigger" AFTER UPDATE ON "ProductInfo"
FOR EACH ROW EXECUTE PROCEDURE "PDIUpdateTrigger"();

-- Create the DELETE trigger for the ProductInfo table
CREATE OR REPLACE FUNCTION "PDIDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductInfo', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PDIDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PDIDeleteTrigger"() IS 'This is an delete notification trigger for ProductInfo';

CREATE TRIGGER "ProductInfoDeleteTrigger" AFTER DELETE ON "ProductInfo"
FOR EACH ROW EXECUTE PROCEDURE "PDIDeleteTrigger"();


------------------------------------------
-- Triggers for CustomerInfo
DROP TRIGGER IF EXISTS "CustomerInfoInsertTrigger" ON "CustomerInfo";
DROP TRIGGER IF EXISTS "CustomerInfoUpdateTrigger" ON "CustomerInfo";
DROP TRIGGER IF EXISTS "CustomerInfoDeleteTrigger" ON "CustomerInfo";

-- Create the INSERT trigger for the CustomerInfo table
CREATE OR REPLACE FUNCTION "CIInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInfo', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CIInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CIInsertTrigger"() IS 'This is an insert notification trigger for CustomerInfo';

CREATE TRIGGER "CustomerInfoInsertTrigger" AFTER INSERT ON "CustomerInfo"
FOR EACH ROW EXECUTE PROCEDURE "CIInsertTrigger"();

-- Create the UPDATE trigger for the CustomerInfo table
CREATE OR REPLACE FUNCTION "CIUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInfo', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CIUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CIUpdateTrigger"() IS 'This is an update notification trigger for CustomerInfo';

CREATE TRIGGER "CustomerInfoUpdateTrigger" AFTER UPDATE ON "CustomerInfo"
FOR EACH ROW EXECUTE PROCEDURE "CIUpdateTrigger"();

-- Create the DELETE trigger for the CustomerInfo table
CREATE OR REPLACE FUNCTION "CIDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInfo', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CIDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CIDeleteTrigger"() IS 'This is an delete notification trigger for CustomerInfo';

CREATE TRIGGER "CustomerInfoDeleteTrigger" AFTER DELETE ON "CustomerInfo"
FOR EACH ROW EXECUTE PROCEDURE "CIDeleteTrigger"();

-- Triggers for the password
DROP TRIGGER IF EXISTS "PasswordInsertTrigger" ON "Password";
DROP TRIGGER IF EXISTS "PasswordUpdateTrigger" ON "Password";
DROP TRIGGER IF EXISTS "PasswordDeleteTrigger" ON "Password";

-- Create the INSERT trigger for the Password table
CREATE OR REPLACE FUNCTION "PWInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Password', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PWInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PWInsertTrigger"() IS 'This is an insert notification trigger for Password';

CREATE TRIGGER "PasswordInsertTrigger" AFTER INSERT ON "Password"
FOR EACH ROW EXECUTE PROCEDURE "PWInsertTrigger"();

-- Create the UPDATE trigger for the Password table
CREATE OR REPLACE FUNCTION "PWUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Password', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PWUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PWUpdateTrigger"() IS 'This is an update notification trigger for Password';

CREATE TRIGGER "PasswordUpdateTrigger" AFTER UPDATE ON "Password"
FOR EACH ROW EXECUTE PROCEDURE "PWUpdateTrigger"();

-- Create the DELETE trigger for the Password table
CREATE OR REPLACE FUNCTION "PWDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Password', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PWDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PWDeleteTrigger"() IS 'This is an delete notification trigger for Password';

CREATE TRIGGER "PasswordDeleteTrigger" AFTER DELETE ON "Password"
FOR EACH ROW EXECUTE PROCEDURE "PWDeleteTrigger"();



-- Removal trigger, 
DROP TRIGGER IF EXISTS "BFWPOnTimesInsertTrigger" ON "BFWPOnTimes";

CREATE OR REPLACE FUNCTION "BFWPOnTimesInsertTrigger"()
  RETURNS trigger AS
$BODY$
DECLARE
    sizeOfTable  integer;
BEGIN
    
     select n_live_tup into sizeOfTable from pg_stat_user_tables where relname = 'BFWPOnTimes';
    
    -- 1000 rows of data for the internal 
    IF(sizeOfTable > 1000) THEN
        
        DELETE FROM "BFWPOnTimes" WHERE "CRE_DT" IN 
            (SELECT "CRE_DT" FROM "BFWPOnTimes" 
                WHERE ("CRE_DT" < (now() - INTERVAL '6 month')) ORDER BY "BFWPOnTimesID" ASC LIMIT 10 );
        
        -- ZERO rows were deleted, now removal of oldest 10 rows is required.
        IF NOT FOUND THEN
            DELETE FROM "BFWPOnTimes" WHERE "BFWPOnTimesID" IN
                (SELECT "BFWPOnTimesID" FROM "BFWPOnTimes" ORDER BY "BFWPOnTimesID" ASC LIMIT 10); 
        END IF;
    END IF;
    

return NULL;

END
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "BFWPOnTimesInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "BFWPOnTimesInsertTrigger"() IS 'This will be used to check the size of the table to remove old rows';

CREATE TRIGGER "BFWPOnTimesInsertTrigger" AFTER INSERT ON "BFWPOnTimes"
FOR EACH ROW EXECUTE PROCEDURE "BFWPOnTimesInsertTrigger"();


-- Drop the notification triggers
DROP TRIGGER IF EXISTS "AlarmsInsertTrigger" ON "Alarms";
DROP TRIGGER IF EXISTS "AlarmsUpdateTrigger" ON "Alarms";
DROP TRIGGER IF EXISTS "AlarmsDeleteTrigger" ON "Alarms";

-- Create the INSERT trigger for the Alarms table
CREATE OR REPLACE FUNCTION "ACInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Alarms', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "ACInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "ACInsertTrigger"() IS 'This is an insert notification trigger for Alarm count data';

CREATE TRIGGER "AlarmsInsertTrigger" AFTER INSERT ON "Alarms"
FOR EACH ROW EXECUTE PROCEDURE "ACInsertTrigger"();

-- Create the UPDATE trigger for the Alarms table
CREATE OR REPLACE FUNCTION "ACUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Alarms', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "ACUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "ACUpdateTrigger"() IS 'This is an update notification trigger for Alarm count data';

CREATE TRIGGER "AlarmsUpdateTrigger" AFTER UPDATE ON "Alarms"
FOR EACH ROW EXECUTE PROCEDURE "ACUpdateTrigger"();

-- Create the DELETE trigger for the Alarms table
CREATE OR REPLACE FUNCTION "ACDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('Alarms', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "ACDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "ACDeleteTrigger"() IS 'This is an delete notification trigger for Alarm Count Data';

CREATE TRIGGER "AlarmsDeleteTrigger" AFTER DELETE ON "Alarms"
FOR EACH ROW EXECUTE PROCEDURE "ACDeleteTrigger"();



-- Drop the notification triggers
DROP TRIGGER IF EXISTS "LocalizedStringsInsertTrigger" ON "LocalizedStrings";
DROP TRIGGER IF EXISTS "LocalizedStringsUpdateTrigger" ON "LocalizedStrings";
DROP TRIGGER IF EXISTS "LocalizedStringsDeleteTrigger" ON "LocalizedStrings";

-- Create the INSERT trigger for the LocalizedStrings table
CREATE OR REPLACE FUNCTION "LSInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('LocalizedStrings', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "LSInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "LSInsertTrigger"() IS 'This is an insert notification trigger for LocalizedStrings data';

CREATE TRIGGER "LocalizedStringsInsertTrigger" AFTER INSERT ON "LocalizedStrings"
FOR EACH ROW EXECUTE PROCEDURE "LSInsertTrigger"();

-- Create the UPDATE trigger for the LocalizedStrings table
CREATE OR REPLACE FUNCTION "LSUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('LocalizedStrings', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "LSUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "LSUpdateTrigger"() IS 'This is an update notification trigger for LocalizedStrings data';

CREATE TRIGGER "LocalizedStringsUpdateTrigger" AFTER UPDATE ON "LocalizedStrings"
FOR EACH ROW EXECUTE PROCEDURE "LSUpdateTrigger"();

-- Create the DELETE trigger for the LocalizedStrings table
CREATE OR REPLACE FUNCTION "LSDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('LocalizedStrings', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "LSDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "LSDeleteTrigger"() IS 'This is an delete notification trigger for LocalizedStrings Data';

CREATE TRIGGER "LocalizedStringsDeleteTrigger" AFTER DELETE ON "LocalizedStrings"
FOR EACH ROW EXECUTE PROCEDURE "LSDeleteTrigger"();
-----------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "OperatingScheduleInsertTrigger" ON "OperatingSchedule";
DROP TRIGGER IF EXISTS "OperatingScheduleUpdateTrigger" ON "OperatingSchedule";
DROP TRIGGER IF EXISTS "OperatingScheduleDeleteTrigger" ON "OperatingSchedule";

-- Create the INSERT trigger for the OperatingSchedule table
CREATE OR REPLACE FUNCTION "OSInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OperatingSchedule', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OSInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OSInsertTrigger"() IS 'This is an insert notification trigger for OperatingSchedule data';

CREATE TRIGGER "OperatingScheduleInsertTrigger" AFTER INSERT ON "OperatingSchedule"
FOR EACH ROW EXECUTE PROCEDURE "OSInsertTrigger"();

-- Create the UPDATE trigger for the OperatingSchedule table
CREATE OR REPLACE FUNCTION "OSUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OperatingSchedule', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OSUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OSUpdateTrigger"() IS 'This is an update notification trigger for OperatingSchedule data';

CREATE TRIGGER "OperatingScheduleUpdateTrigger" AFTER UPDATE ON "OperatingSchedule"
FOR EACH ROW EXECUTE PROCEDURE "OSUpdateTrigger"();

-- Create the DELETE trigger for the OperatingSchedule table
CREATE OR REPLACE FUNCTION "OSDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OperatingSchedule', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OSDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OSDeleteTrigger"() IS 'This is an delete notification trigger for OperatingSchedule Data';

CREATE TRIGGER "OperatingScheduleDeleteTrigger" AFTER DELETE ON "OperatingSchedule"
FOR EACH ROW EXECUTE PROCEDURE "OSDeleteTrigger"();
--------------------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "ScheduleSpecificPropertiesInsertTrigger" ON "ScheduleSpecificProperties";
DROP TRIGGER IF EXISTS "ScheduleSpecificPropertiesUpdateTrigger" ON "ScheduleSpecificProperties";
DROP TRIGGER IF EXISTS "ScheduleSpecificPropertiesDeleteTrigger" ON "ScheduleSpecificProperties";

-- Create the INSERT trigger for the ScheduleSpecificProperties table
CREATE OR REPLACE FUNCTION "SSInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ScheduleSpecificProperties', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SSInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SSInsertTrigger"() IS 'This is an insert notification trigger for ScheduleSpecificProperties data';

CREATE TRIGGER "ScheduleSpecificPropertiesInsertTrigger" AFTER INSERT ON "ScheduleSpecificProperties"
FOR EACH ROW EXECUTE PROCEDURE "SSInsertTrigger"();

-- Create the UPDATE trigger for the ScheduleSpecificProperties table
CREATE OR REPLACE FUNCTION "SSUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ScheduleSpecificProperties', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SSUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SSUpdateTrigger"() IS 'This is an update notification trigger for ScheduleSpecificProperties data';

CREATE TRIGGER "ScheduleSpecificPropertiesUpdateTrigger" AFTER UPDATE ON "ScheduleSpecificProperties"
FOR EACH ROW EXECUTE PROCEDURE "SSUpdateTrigger"();

-- Create the DELETE trigger for the ScheduleSpecificProperties table
CREATE OR REPLACE FUNCTION "SSDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ScheduleSpecificProperties', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SSDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SSDeleteTrigger"() IS 'This is an delete notification trigger for ScheduleSpecificProperties Data';

CREATE TRIGGER "ScheduleSpecificPropertiesDeleteTrigger" AFTER DELETE ON "ScheduleSpecificProperties"
FOR EACH ROW EXECUTE PROCEDURE "SSDeleteTrigger"();

-------------------------------------

-- Drop the notification triggers
DROP TRIGGER IF EXISTS "ProductSlotInsertTrigger" ON "ProductSlot";
DROP TRIGGER IF EXISTS "ProductSlotUpdateTrigger" ON "ProductSlot";
DROP TRIGGER IF EXISTS "ProductSlotDeleteTrigger" ON "ProductSlot";

-- Create the INSERT trigger for the ProductSlot table
CREATE OR REPLACE FUNCTION "PRInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductSlot', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PRInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PRInsertTrigger"() IS 'This is an insert notification trigger for ProductSlot data';

CREATE TRIGGER "ProductSlotInsertTrigger" AFTER INSERT ON "ProductSlot"
FOR EACH ROW EXECUTE PROCEDURE "PRInsertTrigger"();

-- Create the UPDATE trigger for the ProductSlot table
CREATE OR REPLACE FUNCTION "PRUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductSlot', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PRUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PRUpdateTrigger"() IS 'This is an update notification trigger for ProductSlot data';

CREATE TRIGGER "ProductSlotUpdateTrigger" AFTER UPDATE ON "ProductSlot"
FOR EACH ROW EXECUTE PROCEDURE "PRUpdateTrigger"();

-- Create the DELETE trigger for the ProductSlot table
CREATE OR REPLACE FUNCTION "PRDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductSlot', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PRDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PRDeleteTrigger"() IS 'This is an delete notification trigger for ProductSlot Data';

CREATE TRIGGER "ProductSlotDeleteTrigger" AFTER DELETE ON "ProductSlot"
FOR EACH ROW EXECUTE PROCEDURE "PRDeleteTrigger"();

------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "SBlockProductPropertiesInsertTrigger" ON "SBlockProductProperties";
DROP TRIGGER IF EXISTS "SBlockProductPropertiesUpdateTrigger" ON "SBlockProductProperties";
DROP TRIGGER IF EXISTS "SBlockProductPropertiesDeleteTrigger" ON "SBlockProductProperties";

-- Create the INSERT trigger for the SBlockProductProperties table
CREATE OR REPLACE FUNCTION "SBInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SBlockProductProperties', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SBInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SBInsertTrigger"() IS 'This is an insert notification trigger for SBlockProductProperties data';

CREATE TRIGGER "SBlockProductPropertiesInsertTrigger" AFTER INSERT ON "SBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "SBInsertTrigger"();

-- Create the UPDATE trigger for the SBlockProductProperties table
CREATE OR REPLACE FUNCTION "SBUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SBlockProductProperties', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SBUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SBUpdateTrigger"() IS 'This is an update notification trigger for SBlockProductProperties data';

CREATE TRIGGER "SBlockProductPropertiesUpdateTrigger" AFTER UPDATE ON "SBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "SBUpdateTrigger"();

-- Create the DELETE trigger for the SBlockProductProperties table
CREATE OR REPLACE FUNCTION "SBDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('SBlockProductProperties', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "SBDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "SBDeleteTrigger"() IS 'This is an delete notification trigger for SBlockProductProperties Data';

CREATE TRIGGER "SBlockProductPropertiesDeleteTrigger" AFTER DELETE ON "SBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "SBDeleteTrigger"();




----------------


------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "PBlockProductPropertiesInsertTrigger" ON "PBlockProductProperties";
DROP TRIGGER IF EXISTS "PBlockProductPropertiesUpdateTrigger" ON "PBlockProductProperties";
DROP TRIGGER IF EXISTS "PBlockProductPropertiesDeleteTrigger" ON "PBlockProductProperties";

-- Create the INSERT trigger for the PBlockProductProperties table
CREATE OR REPLACE FUNCTION "HBInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('PBlockProductProperties', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "HBInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "HBInsertTrigger"() IS 'This is an insert notification trigger for PBlockProductProperties data';

CREATE TRIGGER "PBlockProductPropertiesInsertTrigger" AFTER INSERT ON "PBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "HBInsertTrigger"();

-- Create the UPDATE trigger for the PBlockProductProperties table
CREATE OR REPLACE FUNCTION "HBUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('PBlockProductProperties', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "HBUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "HBUpdateTrigger"() IS 'This is an update notification trigger for PBlockProductProperties data';

CREATE TRIGGER "PBlockProductPropertiesUpdateTrigger" AFTER UPDATE ON "PBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "HBUpdateTrigger"();

-- Create the DELETE trigger for the PBlockProductProperties table
CREATE OR REPLACE FUNCTION "HBDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('PBlockProductProperties', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "HBDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "HBDeleteTrigger"() IS 'This is an delete notification trigger for PBlockProductProperties Data';

CREATE TRIGGER "PBlockProductPropertiesDeleteTrigger" AFTER DELETE ON "PBlockProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "HBDeleteTrigger"();




----------------







------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "OCapsuleProductPropertiesInsertTrigger" ON "OCapsuleProductProperties";
DROP TRIGGER IF EXISTS "OCapsuleProductPropertiesUpdateTrigger" ON "OCapsuleProductProperties";
DROP TRIGGER IF EXISTS "OCapsuleProductPropertiesDeleteTrigger" ON "OCapsuleProductProperties";

-- Create the INSERT trigger for the OCapsuleProductProperties table
CREATE OR REPLACE FUNCTION "OCInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OCapsuleProductProperties', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OCInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OCInsertTrigger"() IS 'This is an insert notification trigger for OCapsuleProductProperties data';

CREATE TRIGGER "OCapsuleProductPropertiesInsertTrigger" AFTER INSERT ON "OCapsuleProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "OCInsertTrigger"();

-- Create the UPDATE trigger for the OCapsuleProductProperties table
CREATE OR REPLACE FUNCTION "OCUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OCapsuleProductProperties', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OCUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OCUpdateTrigger"() IS 'This is an update notification trigger for OCapsuleProductProperties data';

CREATE TRIGGER "OCapsuleProductPropertiesUpdateTrigger" AFTER UPDATE ON "OCapsuleProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "OCUpdateTrigger"();

-- Create the DELETE trigger for the OCapsuleProductProperties table
CREATE OR REPLACE FUNCTION "OCDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('OCapsuleProductProperties', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "OCDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "OCDeleteTrigger"() IS 'This is an delete notification trigger for OCapsuleProductProperties Data';

CREATE TRIGGER "OCapsuleProductPropertiesDeleteTrigger" AFTER DELETE ON "OCapsuleProductProperties"
FOR EACH ROW EXECUTE PROCEDURE "OCDeleteTrigger"();




----------------


------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "ProductConcentrationForSprayInsertTrigger" ON "ProductConcentrationForSpray";
DROP TRIGGER IF EXISTS "ProductConcentrationForSprayUpdateTrigger" ON "ProductConcentrationForSpray";
DROP TRIGGER IF EXISTS "ProductConcentrationForSprayDeleteTrigger" ON "ProductConcentrationForSpray";

-- Create the INSERT trigger for the ProductConcentrationForSpray table
CREATE OR REPLACE FUNCTION "PCInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductConcentrationForSpray', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PCInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PCInsertTrigger"() IS 'This is an insert notification trigger for ProductConcentrationForSpray data';

CREATE TRIGGER "ProductConcentrationForSprayInsertTrigger" AFTER INSERT ON "ProductConcentrationForSpray"
FOR EACH ROW EXECUTE PROCEDURE "PCInsertTrigger"();

-- Create the UPDATE trigger for the ProductConcentrationForSpray table
CREATE OR REPLACE FUNCTION "PCUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductConcentrationForSpray', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PCUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PCUpdateTrigger"() IS 'This is an update notification trigger for ProductConcentrationForSpray data';

CREATE TRIGGER "ProductConcentrationForSprayUpdateTrigger" AFTER UPDATE ON "ProductConcentrationForSpray"
FOR EACH ROW EXECUTE PROCEDURE "PCUpdateTrigger"();

-- Create the DELETE trigger for the ProductConcentrationForSpray table
CREATE OR REPLACE FUNCTION "PCDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductConcentrationForSpray', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PCDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PCDeleteTrigger"() IS 'This is an delete notification trigger for ProductConcentrationForSpray Data';

CREATE TRIGGER "ProductConcentrationForSprayDeleteTrigger" AFTER DELETE ON "ProductConcentrationForSpray"
FOR EACH ROW EXECUTE PROCEDURE "PCDeleteTrigger"();




----------------
------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "ProductMappingInsertTrigger" ON "ProductMapping";
DROP TRIGGER IF EXISTS "ProductMappingUpdateTrigger" ON "ProductMapping";
DROP TRIGGER IF EXISTS "ProductMappingDeleteTrigger" ON "ProductMapping";

-- Create the INSERT trigger for the ProductMapping table
CREATE OR REPLACE FUNCTION "PMInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductMapping', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PMInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PMInsertTrigger"() IS 'This is an insert notification trigger for ProductMapping data';

CREATE TRIGGER "ProductMappingInsertTrigger" AFTER INSERT ON "ProductMapping"
FOR EACH ROW EXECUTE PROCEDURE "PMInsertTrigger"();

-- Create the UPDATE trigger for the ProductMapping table
CREATE OR REPLACE FUNCTION "PMUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductMapping', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PMUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PMUpdateTrigger"() IS 'This is an update notification trigger for ProductMapping data';

CREATE TRIGGER "ProductMappingUpdateTrigger" AFTER UPDATE ON "ProductMapping"
FOR EACH ROW EXECUTE PROCEDURE "PMUpdateTrigger"();

-- Create the DELETE trigger for the ProductMapping table
CREATE OR REPLACE FUNCTION "PMDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('ProductMapping', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "PMDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "PMDeleteTrigger"() IS 'This is an delete notification trigger for ProductMapping Data';

CREATE TRIGGER "ProductMappingDeleteTrigger" AFTER DELETE ON "ProductMapping"
FOR EACH ROW EXECUTE PROCEDURE "PMDeleteTrigger"();




----------------

------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "BoilerPropertiesForProductsInsertTrigger" ON "BoilerPropertiesForProducts";
DROP TRIGGER IF EXISTS "BoilerPropertiesForProductsUpdateTrigger" ON "BoilerPropertiesForProducts";
DROP TRIGGER IF EXISTS "BoilerPropertiesForProductsDeleteTrigger" ON "BoilerPropertiesForProducts";

-- Create the INSERT trigger for the BoilerPropertiesForProducts table
CREATE OR REPLACE FUNCTION "BPInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('BoilerPropertiesForProducts', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "BPInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "BPInsertTrigger"() IS 'This is an insert notification trigger for BoilerPropertiesForProducts data';

CREATE TRIGGER "BoilerPropertiesForProductsInsertTrigger" AFTER INSERT ON "BoilerPropertiesForProducts"
FOR EACH ROW EXECUTE PROCEDURE "BPInsertTrigger"();

-- Create the UPDATE trigger for the BoilerPropertiesForProducts table
CREATE OR REPLACE FUNCTION "BPUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('BoilerPropertiesForProducts', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "BPUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "BPUpdateTrigger"() IS 'This is an update notification trigger for BoilerPropertiesForProducts data';

CREATE TRIGGER "BoilerPropertiesForProductsUpdateTrigger" AFTER UPDATE ON "BoilerPropertiesForProducts"
FOR EACH ROW EXECUTE PROCEDURE "BPUpdateTrigger"();

-- Create the DELETE trigger for the BoilerPropertiesForProducts table
CREATE OR REPLACE FUNCTION "BPDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('BoilerPropertiesForProducts', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "BPDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "BPDeleteTrigger"() IS 'This is an delete notification trigger for BoilerPropertiesForProducts Data';

CREATE TRIGGER "BoilerPropertiesForProductsDeleteTrigger" AFTER DELETE ON "BoilerPropertiesForProducts"
FOR EACH ROW EXECUTE PROCEDURE "BPDeleteTrigger"();




----------------


------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "RegionSpecificAlarmPropertiesInsertTrigger" ON "RegionSpecificAlarmProperties";
DROP TRIGGER IF EXISTS "RegionSpecificAlarmPropertiesUpdateTrigger" ON "RegionSpecificAlarmProperties";
DROP TRIGGER IF EXISTS "RegionSpecificAlarmPropertiesDeleteTrigger" ON "RegionSpecificAlarmProperties";

-- Create the INSERT trigger for the RegionSpecificAlarmProperties table
CREATE OR REPLACE FUNCTION "RSInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('RegionSpecificAlarmProperties', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "RSInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "RSInsertTrigger"() IS 'This is an insert notification trigger for RegionSpecificAlarmProperties data';

CREATE TRIGGER "RegionSpecificAlarmPropertiesInsertTrigger" AFTER INSERT ON "RegionSpecificAlarmProperties"
FOR EACH ROW EXECUTE PROCEDURE "RSInsertTrigger"();

-- Create the UPDATE trigger for the RegionSpecificAlarmProperties table
CREATE OR REPLACE FUNCTION "RSUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('RegionSpecificAlarmProperties', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "RSUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "RSUpdateTrigger"() IS 'This is an update notification trigger for RegionSpecificAlarmProperties data';

CREATE TRIGGER "RegionSpecificAlarmPropertiesUpdateTrigger" AFTER UPDATE ON "RegionSpecificAlarmProperties"
FOR EACH ROW EXECUTE PROCEDURE "RSUpdateTrigger"();

-- Create the DELETE trigger for the RegionSpecificAlarmProperties table
CREATE OR REPLACE FUNCTION "RSDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('RegionSpecificAlarmProperties', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "RSDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "RSDeleteTrigger"() IS 'This is an delete notification trigger for RegionSpecificAlarmProperties Data';

CREATE TRIGGER "RegionSpecificAlarmPropertiesDeleteTrigger" AFTER DELETE ON "RegionSpecificAlarmProperties"
FOR EACH ROW EXECUTE PROCEDURE "RSDeleteTrigger"();




----------------

------------------------------------------------------------
-- Drop the notification triggers
DROP TRIGGER IF EXISTS "CustomerInputSignalInsertTrigger" ON "CustomerInputSignal";
DROP TRIGGER IF EXISTS "CustomerInputSignalUpdateTrigger" ON "CustomerInputSignal";
DROP TRIGGER IF EXISTS "CustomerInputSignalDeleteTrigger" ON "CustomerInputSignal";

-- Create the INSERT trigger for the CustomerInputSignal table
CREATE OR REPLACE FUNCTION "CSInsertTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInputSignal', 'Inserted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CSInsertTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CSInsertTrigger"() IS 'This is an insert notification trigger for CustomerInputSignal data';

CREATE TRIGGER "CustomerInputSignalInsertTrigger" AFTER INSERT ON "CustomerInputSignal"
FOR EACH ROW EXECUTE PROCEDURE "CSInsertTrigger"();

-- Create the UPDATE trigger for the CustomerInputSignal table
CREATE OR REPLACE FUNCTION "CSUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInputSignal', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CSUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CSUpdateTrigger"() IS 'This is an update notification trigger for CustomerInputSignal data';

CREATE TRIGGER "CustomerInputSignalUpdateTrigger" AFTER UPDATE ON "CustomerInputSignal"
FOR EACH ROW EXECUTE PROCEDURE "CSUpdateTrigger"();

-- Create the DELETE trigger for the CustomerInputSignal table
CREATE OR REPLACE FUNCTION "CSDeleteTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('CustomerInputSignal', 'Deleted');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "CSDeleteTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "CSDeleteTrigger"() IS 'This is an delete notification trigger for CustomerInputSignal Data';

CREATE TRIGGER "CustomerInputSignalDeleteTrigger" AFTER DELETE ON "CustomerInputSignal"
FOR EACH ROW EXECUTE PROCEDURE "CSDeleteTrigger"();




----------------

-- Create the UPDATE trigger for the "DBSyncState" table
CREATE OR REPLACE FUNCTION "DBSyncStateUpdateTrigger"()
  RETURNS trigger AS
$BODY$BEGIN

PERFORM pg_notify('DBSyncState', 'Updated');

return NULL;
END$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "DBSyncStateUpdateTrigger"() OWNER TO db_user_admin;
COMMENT ON FUNCTION "DBSyncStateUpdateTrigger"() IS 'This is an update notification trigger for DBSyncState data';

CREATE TRIGGER "DBSyncStateUpdateTrigger" AFTER UPDATE ON "DBSyncState"
FOR EACH ROW EXECUTE PROCEDURE "DBSyncStateUpdateTrigger"();

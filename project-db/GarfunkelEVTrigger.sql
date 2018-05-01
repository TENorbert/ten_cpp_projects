
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

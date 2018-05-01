-- Database: "Garfunkel"
--  Setting this causes psql to stop when an error occurs in non interactive mode.
\set ON_ERROR_STOP true
DROP DATABASE IF EXISTS "Garfunkel";
DROP DATABASE IF EXISTS "Garfunkelext";
DROP TABLESPACE IF EXISTS garfunkelext;
DROP TABLESPACE IF EXISTS garfunkel;

CREATE TABLESPACE garfunkel LOCATION '/usr/postgres/tablespace/garfunkel'; 

CREATE TABLESPACE garfunkelext LOCATION '/external_flash_a/db/garfunkelext';

CREATE DATABASE "Garfunkel"
  WITH OWNER = db_user_admin
       ENCODING = 'UTF8'
	   TEMPLATE=template0
	   TABLESPACE garfunkel
	   CONNECTION LIMIT=-1;
	   
CREATE DATABASE "Garfunkelext"
  WITH OWNER = db_user_admin
       ENCODING = 'UTF8'
	   TEMPLATE=template0
	   TABLESPACE garfunkelext
	   CONNECTION LIMIT=-1;

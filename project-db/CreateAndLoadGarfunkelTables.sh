#!/bin/sh

# Exit on error.
#set -e

# Create the internal tablespace directory, if it doesn't exist.
if [ ! -d "/usr/postgres/tablespace/garfunkel" ]; then
    mkdir -p /usr/postgres/tablespace/garfunkel
fi
chown -R postgres.nogroup /usr/postgres/tablespace/garfunkel

# Create the external tablespace directory, if it doesn't exist.
if [ ! -d "/external_flash_a/db/garfunkelext" ]; then
    mkdir -p /external_flash_a/db/garfunkelext
fi
chown -R postgres.nogroup /external_flash_a/db/garfunkelext


# Drop the tables, this will also drop the data
psql -U postgres -f GarfunkelCreateInstance.sql

# Reload the tables schema
psql -d Garfunkel  -U postgres  -f GarfunkelTableScript.sql
psql -d Garfunkelext  -U postgres  -f GarfunkelBuildEventDataLog.sql

# Reload the table static data
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulation.sql
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulationEU.sql
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulationAP.sql
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulationLA.sql
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulationME.sql
psql -d Garfunkel  -U postgres  -f GarfunkelStaticDataPopulationChina.sql
psql -d Garfunkel  -U postgres -f GarfunkelStoredFuncs.sql
psql -d Garfunkel -U postgres -f GarfunkelDBTriggers.sql
psql -d Garfunkelext -U postgres -f GarfunkelEVTrigger.sql

#psql -d Garfunkel -U postgres -f GarfunkelStaticLocalizationData.sql

/* $PostgreSQL: pgsql/contrib/spi/autoinc.sql.in,v 1.7 2007/11/13 04:24:28 momjian Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

CREATE OR REPLACE FUNCTION autoinc() 
RETURNS trigger 
AS '$libdir/autoinc'
LANGUAGE C;

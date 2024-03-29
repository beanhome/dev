/* $PostgreSQL: pgsql/contrib/spi/timetravel.sql.in,v 1.8 2007/11/13 04:24:28 momjian Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

CREATE OR REPLACE FUNCTION timetravel() 
RETURNS trigger 
AS '$libdir/timetravel'
LANGUAGE C;

CREATE OR REPLACE FUNCTION set_timetravel(name, int4) 
RETURNS int4 
AS '$libdir/timetravel'
LANGUAGE C RETURNS NULL ON NULL INPUT;

CREATE OR REPLACE FUNCTION get_timetravel(name) 
RETURNS int4 
AS '$libdir/timetravel'
LANGUAGE C RETURNS NULL ON NULL INPUT;

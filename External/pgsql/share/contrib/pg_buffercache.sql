/* $PostgreSQL: pgsql/contrib/pg_buffercache/pg_buffercache.sql.in,v 1.8 2008/08/14 12:56:41 heikki Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

-- Register the function.
CREATE OR REPLACE FUNCTION pg_buffercache_pages()
RETURNS SETOF RECORD
AS '$libdir/pg_buffercache', 'pg_buffercache_pages'
LANGUAGE C;

-- Create a view for convenient access.
CREATE VIEW pg_buffercache AS
	SELECT P.* FROM pg_buffercache_pages() AS P
 	(bufferid integer, relfilenode oid, reltablespace oid, reldatabase oid, 
	 relforknumber int2, relblocknumber int8, isdirty bool, usagecount int2);
 
-- Don't want these to be available at public.
REVOKE ALL ON FUNCTION pg_buffercache_pages() FROM PUBLIC;
REVOKE ALL ON pg_buffercache FROM PUBLIC;

/* $PostgreSQL: pgsql/contrib/fuzzystrmatch/fuzzystrmatch.sql.in,v 1.10 2008/04/03 21:13:07 tgl Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

CREATE OR REPLACE FUNCTION levenshtein (text,text) RETURNS int
AS '$libdir/fuzzystrmatch','levenshtein'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION levenshtein (text,text,int,int,int) RETURNS int
AS '$libdir/fuzzystrmatch','levenshtein_with_costs'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION metaphone (text,int) RETURNS text
AS '$libdir/fuzzystrmatch','metaphone'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION soundex(text) RETURNS text
AS '$libdir/fuzzystrmatch', 'soundex'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION text_soundex(text) RETURNS text
AS '$libdir/fuzzystrmatch', 'soundex'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION difference(text,text) RETURNS int
AS '$libdir/fuzzystrmatch', 'difference'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION dmetaphone (text) RETURNS text 
AS '$libdir/fuzzystrmatch', 'dmetaphone'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION dmetaphone_alt (text) RETURNS text 
AS '$libdir/fuzzystrmatch', 'dmetaphone_alt'
LANGUAGE C IMMUTABLE STRICT;

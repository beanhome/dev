/* $PostgreSQL: pgsql/contrib/test_parser/test_parser.sql.in,v 1.3 2007/11/13 04:24:29 momjian Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

CREATE OR REPLACE FUNCTION testprs_start(internal, int4)
RETURNS internal
AS '$libdir/test_parser'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION testprs_getlexeme(internal, internal, internal)
RETURNS internal
AS '$libdir/test_parser'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION testprs_end(internal)
RETURNS void
AS '$libdir/test_parser'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION testprs_lextype(internal)
RETURNS internal
AS '$libdir/test_parser'
LANGUAGE C STRICT;

CREATE TEXT SEARCH PARSER testparser (
    START    = testprs_start,
    GETTOKEN = testprs_getlexeme,
    END      = testprs_end,
    HEADLINE = pg_catalog.prsd_headline,
    LEXTYPES = testprs_lextype
);

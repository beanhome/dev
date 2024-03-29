/* $PostgreSQL: pgsql/contrib/dict_int/dict_int.sql.in,v 1.3 2007/11/13 04:24:27 momjian Exp $ */

-- Adjust this setting to control where the objects get created.
SET search_path = public;

CREATE OR REPLACE FUNCTION dintdict_init(internal)
        RETURNS internal
        AS '$libdir/dict_int'
        LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION dintdict_lexize(internal, internal, internal, internal)
        RETURNS internal
        AS '$libdir/dict_int'
        LANGUAGE C STRICT;

CREATE TEXT SEARCH TEMPLATE intdict_template (
        LEXIZE = dintdict_lexize,
	INIT   = dintdict_init
);

CREATE TEXT SEARCH DICTIONARY intdict (
	TEMPLATE = intdict_template
);

COMMENT ON TEXT SEARCH DICTIONARY intdict IS 'dictionary for integers';

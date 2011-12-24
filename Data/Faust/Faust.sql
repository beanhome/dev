--
-- PostgreSQL database cluster dump
--

-- Started on 2011-12-15 18:00:01

\connect postgres

SET client_encoding = 'LATIN1';
SET standard_conforming_strings = off;
SET escape_string_warning = off;

--
-- Roles
--

CREATE ROLE "Alex";
ALTER ROLE "Alex" WITH NOSUPERUSER INHERIT CREATEROLE NOCREATEDB LOGIN PASSWORD 'md593eb0af529881d0be163816054436e22';
CREATE ROLE "ArnaudD";
ALTER ROLE "ArnaudD" WITH NOSUPERUSER INHERIT CREATEROLE NOCREATEDB LOGIN PASSWORD 'md5669b175d7264910c800553b9c143a527';
CREATE ROLE "Calixte";
ALTER ROLE "Calixte" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN;
CREATE ROLE "Daemon";
ALTER ROLE "Daemon" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN VALID UNTIL 'infinity';
CREATE ROLE "Faust";
ALTER ROLE "Faust" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN VALID UNTIL 'infinity';
CREATE ROLE "FaustHighPlayer";
ALTER ROLE "FaustHighPlayer" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN PASSWORD 'md5f92fb9172d552afa2aa7d4864b15a448';
CREATE ROLE "FaustLowPlayer";
ALTER ROLE "FaustLowPlayer" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN PASSWORD 'md5baf40924acad45d5286ea9d328656a14';
CREATE ROLE "FaustMedFaust";
ALTER ROLE "FaustMedFaust" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN PASSWORD 'md5e6f2e911243758a493d03c9ffc67a9d7';
CREATE ROLE "FaustPlayer";
ALTER ROLE "FaustPlayer" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN PASSWORD 'md5ee81bd3878ddca058f8593a85440fa74' VALID UNTIL 'infinity';
CREATE ROLE "Faust_High";
ALTER ROLE "Faust_High" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN;
CREATE ROLE "Faust_Low";
ALTER ROLE "Faust_Low" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN;
CREATE ROLE "Faust_Medium";
ALTER ROLE "Faust_Medium" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN;
CREATE ROLE "LambdaPlayer";
ALTER ROLE "LambdaPlayer" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN VALID UNTIL 'infinity';
CREATE ROLE "Lilian";
ALTER ROLE "Lilian" WITH NOSUPERUSER INHERIT CREATEROLE NOCREATEDB LOGIN PASSWORD 'md5ca35e63b940875834b1dfd11e616bf57';
CREATE ROLE "Prout";
ALTER ROLE "Prout" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN;
CREATE ROLE "Romain";
ALTER ROLE "Romain" WITH NOSUPERUSER INHERIT CREATEROLE NOCREATEDB LOGIN PASSWORD 'md58345a77daa7fd9eea9b59263b27716dc';
CREATE ROLE "Scenario";
ALTER ROLE "Scenario" WITH NOSUPERUSER INHERIT CREATEROLE CREATEDB NOLOGIN VALID UNTIL 'infinity';
CREATE ROLE "Scenariste";
ALTER ROLE "Scenariste" WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN PASSWORD 'md5a245f7c96cb5caf9c5f9f817a8abdff8' VALID UNTIL 'infinity';
CREATE ROLE "Sly";
ALTER ROLE "Sly" WITH NOSUPERUSER INHERIT CREATEROLE NOCREATEDB LOGIN PASSWORD 'md53594d3e8853763f62e94b30ac1d4c812';
CREATE ROLE everybody;
ALTER ROLE everybody WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB NOLOGIN VALID UNTIL 'infinity';
CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN PASSWORD 'md5c5ac6c40775a5fe00fa67d0d9efad78a';


--
-- Role memberships
--

GRANT "Daemon" TO "Scenario" GRANTED BY postgres;
GRANT "Faust" TO "FaustPlayer" GRANTED BY postgres;
GRANT "Faust" TO "Scenario" GRANTED BY postgres;
GRANT "Faust_High" TO "FaustHighPlayer" GRANTED BY postgres;
GRANT "Faust_High" TO "Scenario" GRANTED BY "Alex";
GRANT "Faust_Low" TO "FaustLowPlayer" GRANTED BY postgres;
GRANT "Faust_Low" TO "Faust_Medium" GRANTED BY postgres;
GRANT "Faust_Medium" TO "FaustMedFaust" GRANTED BY postgres;
GRANT "Faust_Medium" TO "Faust_High" GRANTED BY postgres;
GRANT "Scenario" TO "Alex" GRANTED BY "Sly";
GRANT "Scenario" TO "ArnaudD" GRANTED BY postgres;
GRANT "Scenario" TO "Lilian" GRANTED BY postgres;
GRANT "Scenario" TO "Romain" GRANTED BY postgres;
GRANT "Scenario" TO "Scenariste" GRANTED BY postgres;
GRANT "Scenario" TO "Sly" GRANTED BY postgres;




--
-- Database creation
--

CREATE DATABASE "Faust" WITH TEMPLATE = template0 OWNER = postgres;
REVOKE ALL ON DATABASE template1 FROM PUBLIC;
REVOKE ALL ON DATABASE template1 FROM postgres;
GRANT ALL ON DATABASE template1 TO postgres;
GRANT CONNECT ON DATABASE template1 TO PUBLIC;


\connect "Faust"

--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.9
-- Dumped by pg_dump version 9.0.4
-- Started on 2011-12-15 18:00:02

SET statement_timeout = 0;
SET client_encoding = 'LATIN1';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 332 (class 2612 OID 16532)
-- Name: plpgsql; Type: PROCEDURAL LANGUAGE; Schema: -; Owner: postgres
--

CREATE OR REPLACE PROCEDURAL LANGUAGE plpgsql;


ALTER PROCEDURAL LANGUAGE plpgsql OWNER TO postgres;

SET search_path = public, pg_catalog;

--
-- TOC entry 303 (class 1247 OID 16387)
-- Dependencies: 3 1519
-- Name: Datation; Type: TYPE; Schema: public; Owner: postgres
--

CREATE TYPE "Datation" AS (
	start date,
	"end" date
);


ALTER TYPE public."Datation" OWNER TO postgres;

--
-- TOC entry 19 (class 1255 OID 16533)
-- Dependencies: 3 332
-- Name: updatedate(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION updatedate() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
    BEGIN
        NEW.update_date := 'now';
        RETURN NEW;
    END;
$$;


ALTER FUNCTION public.updatedate() OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 1527 (class 1259 OID 16420)
-- Dependencies: 1819 1820 1821 303 3
-- Name: Event; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Event" (
    id integer NOT NULL,
    name character varying(32) NOT NULL,
    description text,
    datation "Datation",
    belief numeric(3,2) DEFAULT 1.0 NOT NULL,
    creation_date timestamp without time zone DEFAULT now() NOT NULL,
    update_date timestamp without time zone DEFAULT now() NOT NULL,
    parent integer
);


ALTER TABLE public."Event" OWNER TO postgres;

--
-- TOC entry 1530 (class 1259 OID 16449)
-- Dependencies: 3
-- Name: Event_Location; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Event_Location" (
    id integer NOT NULL,
    event_id integer NOT NULL,
    location_id integer NOT NULL
);


ALTER TABLE public."Event_Location" OWNER TO postgres;

--
-- TOC entry 1529 (class 1259 OID 16447)
-- Dependencies: 1530 3
-- Name: Event_Location_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Event_Location_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Event_Location_id_seq" OWNER TO postgres;

--
-- TOC entry 1876 (class 0 OID 0)
-- Dependencies: 1529
-- Name: Event_Location_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Event_Location_id_seq" OWNED BY "Event_Location".id;


--
-- TOC entry 1877 (class 0 OID 0)
-- Dependencies: 1529
-- Name: Event_Location_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Event_Location_id_seq"', 84, true);


--
-- TOC entry 1532 (class 1259 OID 16475)
-- Dependencies: 3
-- Name: Event_Role; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Event_Role" (
    id integer NOT NULL,
    event_id integer NOT NULL,
    role name NOT NULL
);


ALTER TABLE public."Event_Role" OWNER TO postgres;

--
-- TOC entry 1531 (class 1259 OID 16473)
-- Dependencies: 1532 3
-- Name: Event_Role_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Event_Role_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Event_Role_id_seq" OWNER TO postgres;

--
-- TOC entry 1880 (class 0 OID 0)
-- Dependencies: 1531
-- Name: Event_Role_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Event_Role_id_seq" OWNED BY "Event_Role".id;


--
-- TOC entry 1881 (class 0 OID 0)
-- Dependencies: 1531
-- Name: Event_Role_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Event_Role_id_seq"', 77, true);


--
-- TOC entry 1534 (class 1259 OID 16490)
-- Dependencies: 3
-- Name: Event_Tags; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Event_Tags" (
    id integer NOT NULL,
    event_id integer NOT NULL,
    tag_id integer NOT NULL
);


ALTER TABLE public."Event_Tags" OWNER TO postgres;

--
-- TOC entry 1533 (class 1259 OID 16488)
-- Dependencies: 1534 3
-- Name: Event_Tags_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Event_Tags_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Event_Tags_id_seq" OWNER TO postgres;

--
-- TOC entry 1884 (class 0 OID 0)
-- Dependencies: 1533
-- Name: Event_Tags_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Event_Tags_id_seq" OWNED BY "Event_Tags".id;


--
-- TOC entry 1885 (class 0 OID 0)
-- Dependencies: 1533
-- Name: Event_Tags_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Event_Tags_id_seq"', 64, true);


--
-- TOC entry 1526 (class 1259 OID 16418)
-- Dependencies: 1527 3
-- Name: Event_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Event_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Event_id_seq" OWNER TO postgres;

--
-- TOC entry 1887 (class 0 OID 0)
-- Dependencies: 1526
-- Name: Event_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Event_id_seq" OWNED BY "Event".id;


--
-- TOC entry 1888 (class 0 OID 0)
-- Dependencies: 1526
-- Name: Event_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Event_id_seq"', 48, true);


--
-- TOC entry 1525 (class 1259 OID 16412)
-- Dependencies: 3
-- Name: Location; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Location" (
    id integer NOT NULL,
    country character varying(32) NOT NULL,
    city character varying(32),
    district character varying(32),
    street character varying(32),
    address character varying(32)
);


ALTER TABLE public."Location" OWNER TO postgres;

--
-- TOC entry 1524 (class 1259 OID 16410)
-- Dependencies: 3 1525
-- Name: Location_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Location_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Location_id_seq" OWNER TO postgres;

--
-- TOC entry 1891 (class 0 OID 0)
-- Dependencies: 1524
-- Name: Location_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Location_id_seq" OWNED BY "Location".id;


--
-- TOC entry 1892 (class 0 OID 0)
-- Dependencies: 1524
-- Name: Location_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Location_id_seq"', 39, true);


--
-- TOC entry 1523 (class 1259 OID 16396)
-- Dependencies: 3
-- Name: Perso; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Perso" (
    id integer NOT NULL,
    name character varying(64) NOT NULL,
    player integer,
    current_name character varying(64)
);


ALTER TABLE public."Perso" OWNER TO postgres;

--
-- TOC entry 1522 (class 1259 OID 16394)
-- Dependencies: 1523 3
-- Name: Perso_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Perso_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Perso_id_seq" OWNER TO postgres;

--
-- TOC entry 1895 (class 0 OID 0)
-- Dependencies: 1522
-- Name: Perso_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Perso_id_seq" OWNED BY "Perso".id;


--
-- TOC entry 1896 (class 0 OID 0)
-- Dependencies: 1522
-- Name: Perso_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Perso_id_seq"', 17, true);


--
-- TOC entry 1521 (class 1259 OID 16390)
-- Dependencies: 3
-- Name: Player; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Player" (
    id integer NOT NULL,
    first_name character varying(32) NOT NULL,
    last_name character varying(32)
);


ALTER TABLE public."Player" OWNER TO postgres;

--
-- TOC entry 1528 (class 1259 OID 16432)
-- Dependencies: 1623 3
-- Name: Player_Perso; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW "Player_Perso" AS
    SELECT "Player".first_name, "Player".last_name, "Perso".name FROM ("Player" FULL JOIN "Perso" ON (("Player".id = "Perso".player))) ORDER BY "Player".first_name;


ALTER TABLE public."Player_Perso" OWNER TO postgres;

--
-- TOC entry 1520 (class 1259 OID 16388)
-- Dependencies: 3 1521
-- Name: Player_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Player_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Player_id_seq" OWNER TO postgres;

--
-- TOC entry 1899 (class 0 OID 0)
-- Dependencies: 1520
-- Name: Player_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Player_id_seq" OWNED BY "Player".id;


--
-- TOC entry 1900 (class 0 OID 0)
-- Dependencies: 1520
-- Name: Player_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Player_id_seq"', 16, true);


--
-- TOC entry 1536 (class 1259 OID 16538)
-- Dependencies: 3
-- Name: Tags; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "Tags" (
    id integer NOT NULL,
    tag character varying(32) NOT NULL
);


ALTER TABLE public."Tags" OWNER TO postgres;

--
-- TOC entry 1535 (class 1259 OID 16536)
-- Dependencies: 3 1536
-- Name: Tags_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Tags_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Tags_id_seq" OWNER TO postgres;

--
-- TOC entry 1902 (class 0 OID 0)
-- Dependencies: 1535
-- Name: Tags_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE "Tags_id_seq" OWNED BY "Tags".id;


--
-- TOC entry 1903 (class 0 OID 0)
-- Dependencies: 1535
-- Name: Tags_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Tags_id_seq"', 11, true);


--
-- TOC entry 1818 (class 2604 OID 16423)
-- Dependencies: 1526 1527 1527
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Event" ALTER COLUMN id SET DEFAULT nextval('"Event_id_seq"'::regclass);


--
-- TOC entry 1822 (class 2604 OID 16452)
-- Dependencies: 1530 1529 1530
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Event_Location" ALTER COLUMN id SET DEFAULT nextval('"Event_Location_id_seq"'::regclass);


--
-- TOC entry 1823 (class 2604 OID 16478)
-- Dependencies: 1532 1531 1532
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Event_Role" ALTER COLUMN id SET DEFAULT nextval('"Event_Role_id_seq"'::regclass);


--
-- TOC entry 1824 (class 2604 OID 16493)
-- Dependencies: 1533 1534 1534
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Event_Tags" ALTER COLUMN id SET DEFAULT nextval('"Event_Tags_id_seq"'::regclass);


--
-- TOC entry 1817 (class 2604 OID 16415)
-- Dependencies: 1525 1524 1525
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Location" ALTER COLUMN id SET DEFAULT nextval('"Location_id_seq"'::regclass);


--
-- TOC entry 1816 (class 2604 OID 16399)
-- Dependencies: 1523 1522 1523
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Perso" ALTER COLUMN id SET DEFAULT nextval('"Perso_id_seq"'::regclass);


--
-- TOC entry 1815 (class 2604 OID 16393)
-- Dependencies: 1520 1521 1521
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Player" ALTER COLUMN id SET DEFAULT nextval('"Player_id_seq"'::regclass);


--
-- TOC entry 1825 (class 2604 OID 16541)
-- Dependencies: 1536 1535 1536
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE "Tags" ALTER COLUMN id SET DEFAULT nextval('"Tags_id_seq"'::regclass);


--
-- TOC entry 1864 (class 0 OID 16420)
-- Dependencies: 1527
-- Data for Name: Event; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Event" (id, name, description, datation, belief, creation_date, update_date, parent) FROM stdin;
1	Test 1	Test 1 Test 1 Test 1\nPopolop\nUpdated	\N	1.00	2011-08-02 16:15:47.908456	2011-08-02 16:15:47.908456	\N
7	test 2 update	test 2 update	\N	1.00	2011-08-13 16:33:31.811344	2011-08-13 16:33:31.811344	\N
9	Test Create	Create Create	(1979-12-01,1981-12-16)	1.00	2011-08-15 16:56:34.692653	2011-08-15 16:56:34.692653	\N
4	Test 4	Test 4 Test 4 Test 4 Test 4	(1981-12-16,1981-12-16)	1.00	2011-08-02 16:18:33.41135	2011-08-02 16:18:33.41135	\N
5	Test Update 2	Update Update Update Update Update 	\N	1.00	2011-08-13 07:58:46.198829	2011-08-31 23:35:19.060625	\N
34	bla test romain	et bla et bla et bla! faust deamon et bg test	(2011-09-01,2011-09-01)	1.00	2011-09-01 09:38:09.418651	2011-09-01 09:38:15.255744	\N
47	BG File Test	Test Dest Test Desc Test Dest Test Desc 	(1978-10-15,1999-05-06)	1.00	2011-09-27 17:38:52.869692	2011-09-27 18:13:57.356564	\N
36	Adoubement	 gdghdsfdsjhgrjfjh	(1981-02-27,1981-02-27)	1.00	2011-09-02 20:26:49.151494	2011-09-02 20:28:29.814986	\N
48	BG File Test 2	Test Dest Test Desc Test Dest Test Desc 	(1998-03-05,1999-11-16)	1.00	2011-09-27 17:38:53.55018	2011-09-27 18:19:47.459397	\N
3	Test 3	Test 3 Test 3 Test 3 Test 3 Updated	\N	1.00	2011-08-02 16:17:57.723601	2011-08-02 16:17:57.723601	\N
35	Première partie		(2011-11-25,2011-11-27)	1.00	2011-09-01 16:04:12.530695	2011-09-17 23:43:38.256718	\N
2	Test 2	Test 2 Test 2 Test 2 Test 2	\N	1.00	2011-08-02 16:16:43.619462	2011-09-19 11:22:11.331247	\N
17	Faust Role Low Secret	Info de secret bas au sein de l'organisation Faust.	\N	1.00	2011-08-31 02:38:47.903044	2011-08-31 02:38:47.903044	\N
18	Faust Role Middle Secret	Info de secret intermediaire au sein de l'organisation Faust.	\N	1.00	2011-08-31 02:58:56.275925	2011-08-31 02:58:56.275925	\N
19	Faust Role High Secret	Info de secret sensible au sein de l'organisation Faust.	\N	1.00	2011-08-31 02:59:47.61182	2011-08-31 02:59:47.61182	\N
10	Hop Test 2	Test test test accent : éèàùçêï	(1776-04-18,1824-04-06)	1.00	2011-08-15 21:33:48.760505	2011-09-20 14:06:07.436926	\N
25	Essai 01	Ajout desc	(1982-03-28,1982-03-28)	1.00	2011-08-31 15:32:58.155316	2011-10-03 01:38:32.437575	\N
26	Essai 02	Creation event Creation lieu	(1982-03-28,1982-03-28)	1.00	2011-08-31 15:33:53.157476	2011-09-22 15:00:04.978895	25
27	Essai 03	Creation event Creation lieu	(1982-03-28,1982-03-28)	1.00	2011-08-31 15:33:53.966371	2011-09-22 15:00:06.157497	25
28	Essai 04	Creation event Creation lieu	(1982-03-28,1982-03-28)	1.00	2011-08-31 15:34:02.766092	2011-09-22 15:00:07.538306	25
29	Essai 05	Creation event Creation lieu	(1982-03-28,1982-03-28)	1.00	2011-08-31 15:34:03.543178	2011-09-22 15:00:08.527573	25
\.


--
-- TOC entry 1865 (class 0 OID 16449)
-- Dependencies: 1530
-- Data for Name: Event_Location; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Event_Location" (id, event_id, location_id) FROM stdin;
1	1	21
3	4	3
4	4	4
5	4	5
6	5	24
7	7	26
8	9	27
42	34	26
18	3	1
48	36	36
49	35	20
50	2	20
51	10	28
24	17	1
25	18	1
26	19	1
57	26	34
58	27	34
59	28	34
60	29	34
79	47	27
80	47	39
82	48	20
84	25	34
\.


--
-- TOC entry 1866 (class 0 OID 16475)
-- Dependencies: 1532
-- Data for Name: Event_Role; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Event_Role" (id, event_id, role) FROM stdin;
4	5	Scenario
5	9	Faust
6	5	Faust
70	47	Faust
71	47	Scenario
11	4	everybody
12	1	everybody
13	7	everybody
20	3	Daemon
21	3	Faust
27	17	Faust_Low
28	18	Faust_Medium
29	19	Faust_High
37	34	Scenario
42	36	Calixte
43	35	everybody
44	2	Faust
45	10	Daemon
46	10	Faust
52	26	Faust
53	27	Faust
54	28	Faust
55	29	Faust
74	48	Faust
75	48	Scenario
77	25	Faust
\.


--
-- TOC entry 1867 (class 0 OID 16490)
-- Dependencies: 1534
-- Data for Name: Event_Tags; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Event_Tags" (id, event_id, tag_id) FROM stdin;
1	5	8
4	7	7
5	1	5
7	9	4
11	7	5
12	1	3
13	4	8
14	3	1
15	3	4
16	17	6
17	18	6
18	19	6
26	34	4
28	36	2
31	2	3
32	2	8
33	10	8
39	26	5
40	27	5
41	28	5
42	29	5
57	47	1
58	47	4
61	48	1
62	48	4
64	25	4
\.


--
-- TOC entry 1863 (class 0 OID 16412)
-- Dependencies: 1525
-- Data for Name: Location; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Location" (id, country, city, district, street, address) FROM stdin;
2	Angleterre	\N	\N	\N	\N
3	France	\N	\N	\N	\N
4	Belgique	\N	\N	\N	\N
5	Pays-bas	\N	\N	\N	\N
6	Suisse	\N	\N	\N	\N
7	Italie	\N	\N	\N	\N
8	Espagne	\N	\N	\N	\N
20	France	Paris	\N	\N	\N
21	Angleterre	Londres	\N	\N	\N
22	Italie	Rome	\N	\N	\N
23	Espagne	Madrid	\N	\N	\N
24	USA	Paris	\N	\N	\N
25	France	Paris	Montmartre	\N	\N
26	France	Paris	Marais	\N	\N
27	France	Paris	Jussieu	\N	\N
28	France	Paris	Jussieu	Rue des Ecoles	6
29	Chine	\N	\N	\N	\N
30	Japon	\N	\N	\N	\N
31	Belgique	Bruxelle	\N	\N	\N
1	none	\N	\N	\N	\N
33	USA	\N	\N	\N	\N
32	France	Paris	Jussieu	Rue des Ecoles	\N
34	France	Paris	Cite	\N	\N
35	France	Paris	La Défense	\N	\N
36	France	Paris	La Défense	Tour Calixte	\N
37	France	Limoge	\N	\N	\N
39	Angleterre	Londres	Whitechapel	\N	\N
\.


--
-- TOC entry 1862 (class 0 OID 16396)
-- Dependencies: 1523
-- Data for Name: Perso; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Perso" (id, name, player, current_name) FROM stdin;
1	Ernest Laforêt	\N	\N
5	Simon Martin	\N	\N
9	Norbert Loche	\N	\N
12	Paul Julian	\N	\N
17	Nicolas Fabre	\N	\N
3	Gaspard Lelievre	7	\N
4	Henry duprés	13	\N
6	René Deschamps	11	\N
7	Claire Monet	4	\N
8	Isabelle Dumarais	16	\N
11	Michel Dapres	3	\N
13	Monique Glabre	6	\N
15	Julia Monceau	12	\N
16	Sarah Fauchard	16	\N
14	Marguerite Noebet	\N	\N
2	Denise Marechal	10	\N
10	Raymond Roncier	\N	\N
\.


--
-- TOC entry 1861 (class 0 OID 16390)
-- Dependencies: 1521
-- Data for Name: Player; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Player" (id, first_name, last_name) FROM stdin;
3	Nicolas	Martin
4	Nathalie	Bernard
5	Stephane	Dubois
6	Stephanie	Thomas
7	Olivier	Robert
10	Sandrine	Richard
11	David	Petit
12	Sophie	Durand
13	Christophe	Leroy
16	Celine	Moreau
\.


--
-- TOC entry 1868 (class 0 OID 16538)
-- Dependencies: 1536
-- Data for Name: Tags; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Tags" (id, tag) FROM stdin;
1	Daemon
2	Pacte
3	Plop
4	Moulin
5	Faust
6	TestFaust
7	BG
8	toto
\.


--
-- TOC entry 1839 (class 2606 OID 16454)
-- Dependencies: 1530 1530
-- Name: Event_Location_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Event_Location"
    ADD CONSTRAINT "Event_Location_id" PRIMARY KEY (id);


--
-- TOC entry 1846 (class 2606 OID 16495)
-- Dependencies: 1534 1534
-- Name: Event_Tags_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Event_Tags"
    ADD CONSTRAINT "Event_Tags_id" PRIMARY KEY (id);


--
-- TOC entry 1834 (class 2606 OID 16431)
-- Dependencies: 1527 1527
-- Name: Event_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Event"
    ADD CONSTRAINT "Event_id" PRIMARY KEY (id);


--
-- TOC entry 1836 (class 2606 OID 16554)
-- Dependencies: 1527 1527
-- Name: Event_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Event"
    ADD CONSTRAINT "Event_name_key" UNIQUE (name);


--
-- TOC entry 1843 (class 2606 OID 16480)
-- Dependencies: 1532 1532
-- Name: Evnet_Role_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Event_Role"
    ADD CONSTRAINT "Evnet_Role_id" PRIMARY KEY (id);


--
-- TOC entry 1832 (class 2606 OID 16417)
-- Dependencies: 1525 1525
-- Name: Location_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Location"
    ADD CONSTRAINT "Location_id" PRIMARY KEY (id);


--
-- TOC entry 1829 (class 2606 OID 16401)
-- Dependencies: 1523 1523
-- Name: Perso_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Perso"
    ADD CONSTRAINT "Perso_id" PRIMARY KEY (id);


--
-- TOC entry 1827 (class 2606 OID 16403)
-- Dependencies: 1521 1521
-- Name: Player_id; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Player"
    ADD CONSTRAINT "Player_id" PRIMARY KEY (id);


--
-- TOC entry 1850 (class 2606 OID 16551)
-- Dependencies: 1536 1536
-- Name: Tags_Tag_Unique; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Tags"
    ADD CONSTRAINT "Tags_Tag_Unique" UNIQUE (tag);


--
-- TOC entry 1852 (class 2606 OID 16543)
-- Dependencies: 1536 1536
-- Name: Tags_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY "Tags"
    ADD CONSTRAINT "Tags_pkey" PRIMARY KEY (id);


--
-- TOC entry 1840 (class 1259 OID 16460)
-- Dependencies: 1530
-- Name: fki_Event_Location_Event_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_Location_Event_id" ON "Event_Location" USING btree (event_id);


--
-- TOC entry 1841 (class 1259 OID 16466)
-- Dependencies: 1530
-- Name: fki_Event_Location_Location_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_Location_Location_id" ON "Event_Location" USING btree (location_id);


--
-- TOC entry 1844 (class 1259 OID 16486)
-- Dependencies: 1532
-- Name: fki_Event_Role_Event; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_Role_Event" ON "Event_Role" USING btree (event_id);


--
-- TOC entry 1847 (class 1259 OID 16502)
-- Dependencies: 1534
-- Name: fki_Event_Tags_Event_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_Tags_Event_id" ON "Event_Tags" USING btree (event_id);


--
-- TOC entry 1848 (class 1259 OID 16549)
-- Dependencies: 1534
-- Name: fki_Event_Tags_Tags_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_Tags_Tags_id" ON "Event_Tags" USING btree (tag_id);


--
-- TOC entry 1837 (class 1259 OID 16560)
-- Dependencies: 1527
-- Name: fki_Event_event_ref_Event_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Event_event_ref_Event_id" ON "Event" USING btree (parent);


--
-- TOC entry 1830 (class 1259 OID 16409)
-- Dependencies: 1523
-- Name: fki_Perso_Player_id; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX "fki_Perso_Player_id" ON "Perso" USING btree (player);


--
-- TOC entry 1860 (class 2620 OID 16534)
-- Dependencies: 19 1527
-- Name: Event_UpdateDate; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER "Event_UpdateDate"
    BEFORE UPDATE ON "Event"
    FOR EACH ROW
    EXECUTE PROCEDURE updatedate();


--
-- TOC entry 1855 (class 2606 OID 16455)
-- Dependencies: 1833 1527 1530
-- Name: Event_Location_Event_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event_Location"
    ADD CONSTRAINT "Event_Location_Event_id" FOREIGN KEY (event_id) REFERENCES "Event"(id);


--
-- TOC entry 1856 (class 2606 OID 16461)
-- Dependencies: 1831 1525 1530
-- Name: Event_Location_Location_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event_Location"
    ADD CONSTRAINT "Event_Location_Location_id" FOREIGN KEY (location_id) REFERENCES "Location"(id);


--
-- TOC entry 1857 (class 2606 OID 16481)
-- Dependencies: 1527 1532 1833
-- Name: Event_Role_Event; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event_Role"
    ADD CONSTRAINT "Event_Role_Event" FOREIGN KEY (event_id) REFERENCES "Event"(id);


--
-- TOC entry 1858 (class 2606 OID 16497)
-- Dependencies: 1833 1534 1527
-- Name: Event_Tags_Event_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event_Tags"
    ADD CONSTRAINT "Event_Tags_Event_id" FOREIGN KEY (event_id) REFERENCES "Event"(id);


--
-- TOC entry 1859 (class 2606 OID 16544)
-- Dependencies: 1536 1534 1851
-- Name: Event_Tags_Tags_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event_Tags"
    ADD CONSTRAINT "Event_Tags_Tags_id" FOREIGN KEY (tag_id) REFERENCES "Tags"(id);


--
-- TOC entry 1854 (class 2606 OID 16561)
-- Dependencies: 1527 1527 1833
-- Name: Event_parent_event_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Event"
    ADD CONSTRAINT "Event_parent_event_id" FOREIGN KEY (parent) REFERENCES "Event"(id);


--
-- TOC entry 1853 (class 2606 OID 16404)
-- Dependencies: 1523 1521 1826
-- Name: Perso_Player_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Perso"
    ADD CONSTRAINT "Perso_Player_id" FOREIGN KEY (player) REFERENCES "Player"(id);


--
-- TOC entry 1873 (class 0 OID 0)
-- Dependencies: 3
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 1874 (class 0 OID 0)
-- Dependencies: 1527
-- Name: Event; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Event" FROM PUBLIC;
REVOKE ALL ON TABLE "Event" FROM postgres;
GRANT ALL ON TABLE "Event" TO postgres;
GRANT SELECT ON TABLE "Event" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Event" TO "Scenario";


--
-- TOC entry 1875 (class 0 OID 0)
-- Dependencies: 1530
-- Name: Event_Location; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Event_Location" FROM PUBLIC;
REVOKE ALL ON TABLE "Event_Location" FROM postgres;
GRANT ALL ON TABLE "Event_Location" TO postgres;
GRANT SELECT ON TABLE "Event_Location" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Event_Location" TO "Scenario";


--
-- TOC entry 1878 (class 0 OID 0)
-- Dependencies: 1529
-- Name: Event_Location_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Event_Location_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Event_Location_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Event_Location_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Event_Location_id_seq" TO "Scenario";


--
-- TOC entry 1879 (class 0 OID 0)
-- Dependencies: 1532
-- Name: Event_Role; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Event_Role" FROM PUBLIC;
REVOKE ALL ON TABLE "Event_Role" FROM postgres;
GRANT ALL ON TABLE "Event_Role" TO postgres;
GRANT SELECT ON TABLE "Event_Role" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Event_Role" TO "Scenario";


--
-- TOC entry 1882 (class 0 OID 0)
-- Dependencies: 1531
-- Name: Event_Role_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Event_Role_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Event_Role_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Event_Role_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Event_Role_id_seq" TO "Scenario";


--
-- TOC entry 1883 (class 0 OID 0)
-- Dependencies: 1534
-- Name: Event_Tags; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Event_Tags" FROM PUBLIC;
REVOKE ALL ON TABLE "Event_Tags" FROM postgres;
GRANT ALL ON TABLE "Event_Tags" TO postgres;
GRANT SELECT ON TABLE "Event_Tags" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Event_Tags" TO "Scenario";


--
-- TOC entry 1886 (class 0 OID 0)
-- Dependencies: 1533
-- Name: Event_Tags_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Event_Tags_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Event_Tags_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Event_Tags_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Event_Tags_id_seq" TO "Scenario";


--
-- TOC entry 1889 (class 0 OID 0)
-- Dependencies: 1526
-- Name: Event_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Event_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Event_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Event_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Event_id_seq" TO "Scenario";


--
-- TOC entry 1890 (class 0 OID 0)
-- Dependencies: 1525
-- Name: Location; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Location" FROM PUBLIC;
REVOKE ALL ON TABLE "Location" FROM postgres;
GRANT ALL ON TABLE "Location" TO postgres;
GRANT SELECT ON TABLE "Location" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Location" TO "Scenario";


--
-- TOC entry 1893 (class 0 OID 0)
-- Dependencies: 1524
-- Name: Location_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Location_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Location_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Location_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Location_id_seq" TO "Scenario";


--
-- TOC entry 1894 (class 0 OID 0)
-- Dependencies: 1523
-- Name: Perso; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Perso" FROM PUBLIC;
REVOKE ALL ON TABLE "Perso" FROM postgres;
GRANT ALL ON TABLE "Perso" TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Perso" TO "Scenario";


--
-- TOC entry 1897 (class 0 OID 0)
-- Dependencies: 1522
-- Name: Perso_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Perso_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Perso_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Perso_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Perso_id_seq" TO "Scenario";


--
-- TOC entry 1898 (class 0 OID 0)
-- Dependencies: 1521
-- Name: Player; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "Player" FROM PUBLIC;
REVOKE ALL ON TABLE "Player" FROM postgres;
GRANT ALL ON TABLE "Player" TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "Player" TO "Scenario";


--
-- TOC entry 1901 (class 0 OID 0)
-- Dependencies: 1520
-- Name: Player_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE "Player_id_seq" FROM PUBLIC;
REVOKE ALL ON SEQUENCE "Player_id_seq" FROM postgres;
GRANT ALL ON SEQUENCE "Player_id_seq" TO postgres;
GRANT USAGE ON SEQUENCE "Player_id_seq" TO "Scenario";


-- Completed on 2011-12-15 18:00:02

--
-- PostgreSQL database dump complete
--

\connect postgres

--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.9
-- Dumped by pg_dump version 9.0.4
-- Started on 2011-12-15 18:00:02

SET statement_timeout = 0;
SET client_encoding = 'LATIN1';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 1769 (class 0 OID 0)
-- Dependencies: 3
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2011-12-15 18:00:02

--
-- PostgreSQL database dump complete
--

\connect template1

--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.9
-- Dumped by pg_dump version 9.0.4
-- Started on 2011-12-15 18:00:02

SET statement_timeout = 0;
SET client_encoding = 'LATIN1';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 1768 (class 1262 OID 1)
-- Dependencies: 1767
-- Name: template1; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE template1 IS 'default template database';


--
-- TOC entry 1770 (class 0 OID 0)
-- Dependencies: 3
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2011-12-15 18:00:04

--
-- PostgreSQL database dump complete
--

-- Completed on 2011-12-15 18:00:04

--
-- PostgreSQL database cluster dump complete
--


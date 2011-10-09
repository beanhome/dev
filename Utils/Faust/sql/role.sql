--SELECT pg_has_role('FaustPlayer', 'Faust', 'MEMBER');
--SELECT pg_has_role('Scenariste', 'Faust', 'MEMBER');
--SELECT A.rolname, B.rolname, pg_has_role(A.rolname, B.rolname, 'MEMBER') FROM pg_authid AS A JOIN pg_authid AS B ON A.rolname != B.rolname AND A.rolcanlogin = true AND B.rolcanlogin = false;

--SELECT * FROM "Event" INNER JOIN FROM "Event_Role" WHERE pg_has_role('Scenariste', role, 'MEMBER');

--SELECT role FROM "Event_Role" WHERE event_id = 3;

--INSERT INTO "Event_Role" (event_id, role) VALUES (5, 'Faust');

--SELECT * FROM "Event_Role";


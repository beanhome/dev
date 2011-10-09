--SELECT '{3,5,7}';
--SELECT ARRAY[3,5,7];
--SELECT (3,5,7);
--SELECT ROW(3,5,7);

--SELECT 1 IN (1,2,3);
--SELECT country FROM "Location" WHERE "id" IN (3,5,7);

--SELECT * from "Event" WHERE 1 =ANY ("Event"."location");

--SELECT 1 =ANY (ARRAY[1,2,3]);
--SELECT 1 =ANY (('{1,2,3}')::int[]);

--SELECT 'aa' =ANY (ARRAY['aa','bb','cc']);

--(SELECT knowers FROM "Event" WHERE id = 1);

SELECT 'aa' =ANY ((SELECT knowers FROM "Event" WHERE id = 1)::name[]);

--SELECT 1 =ANY ((SELECT location FROM "Event" WHERE id = 1)::int[]);

-- location du event id = 1
--SELECT country FROM "Location" WHERE "id" =ANY ((SELECT location FROM "Event" WHERE id = 1)::int[]);

--SELECT (SELECT country FROM "Location" WHERE "id" =ANY ((SELECT location FROM "Event" WHERE id = 1)::int[]))::varchar[];

--SELECT ROW(3,4,5);


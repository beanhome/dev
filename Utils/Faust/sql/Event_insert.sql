--INSERT INTO "Event" (name, description, datation, location, knowers, belief, tags) VALUES ('Test insert', 'Insert Insert Insert Insert Insert Insert ', ('01-02-0304', '05-06-0708'), '{2,3,4}', ARRAY['aa','bb'], 1.0, ARRAY['a','b','c']);
UPDATE "Event" SET name = 'Test update', description = 'Update Update Update Update Update ', datation = ('01-02-0304', '05-06-0708'), location = ARRAY[2,3,4], knowers = ARRAY['aa','bb'], belief = 0.5, tags = ARRAY['a'] WHERE id = 5;



--SELECT currval('"Event_id_seq"'::regclass);
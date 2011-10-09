--INSERT INTO "Tags" (tag) SELECT DISTINCT tag FROM "Event_Tags";

--COPY (SELECT DISTINCT tag FROM "Event_Tags") TO '/tmp/save.tmp';

--SELECT * FROM "Event_Tags";

--UPDATE "Event_Tags" SET tag_id = (SELECT id FROM "Tags" WHERE "Event_Tags".tag = "Tags".tag);

--SELECT "Event_Tags".event_id, "Tags".tag FROM "Event_Tags" JOIN "Tags" ON "Event_Tags".tag_id = "Tags".id;

INSERT INTO "Event_Tags" (event_id, tag_id) VALUES (2, (SELECT id FROM "Tags" WHERE tag = 'toto'));

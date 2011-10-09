--SELECT DISTINCT tag FROM "Event_Tags" ORDER BY tag;

SELECT * FROM "Event" INNER JOIN "Event_Tags" ON "Event".id = "Event_Tags".event_id WHERE "Event_Tags".tag = 'toto';
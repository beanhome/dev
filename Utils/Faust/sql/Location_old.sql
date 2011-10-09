--INSERT INTO "City" (country, city) VALUES ('France', 'Bordeaux');
--INSERT INTO "District" (country, city, district) VALUES ('France', 'Paris', 'Montmartre');

--SELECT * FROM "Location";
--SELECT * FROM "City";
--SELECT * FROM "District";

--SELECT "Location".id, "Location".country, "City".city FROM "Location" FULL OUTER JOIN "City" ON "Location".id = "City".id;
--SELECT "Location".id, "Location".country, "City".city FROM "Location" LEFT JOIN "City" ON "Location".id = "City".id;

SELECT "Location".id, "Location".country, "City".city, "District".district FROM ("Location" FULL OUTER JOIN "City" ON "Location".id = "City".id) FULL OUTER JOIN "District" ON "Location".id = "District".id;

--SELECT DISTINCT(country)  FROM "Location" ;

--SELECT country, city FROM "City";
--SELECT DISTINCT(country, city) FROM "City";

--SELECT DISTINCT(city) FROM "City" WHERE country = 'France';

--SELECT id FROM ONLY "Location" WHERE country = 'France' ;


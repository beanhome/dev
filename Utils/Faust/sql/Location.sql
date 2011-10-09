-- tout
--SELECT (country, city, district, street, address) FROM "Location";

-- tout les pays
--SELECT DISTINCT country FROM "Location";

-- toutes les villes de pays différent
--SELECT DISTINCT country, city FROM "Location" WHERE city IS NOT NULL;

-- toutes les district de ville et pays différent
--SELECT DISTINCT country, city, district FROM "Location" WHERE city IS NOT NULL AND district IS NOT NULL;

SELECT * FROM ONLY "Location" WHERE country = 'France' AND city = 'Paris'
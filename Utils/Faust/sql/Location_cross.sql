-- ** SELECT les location d'un event precis **
SELECT "Location".id, "Location".country, "Location".city, "Location".district, "Location".street, "Location".address
  FROM "Event_Location" LEFT JOIN "Location"
  ON "Event_Location".location_id = "Location".id
  WHERE "Event_Location".event_id = 10
  ;

-- ** SELECT les id des event se passant à une location precise **
--SELECT  "Event_Location"."Event_id"
--  FROM "Event_Location" LEFT JOIN "Location"
--  ON "Event_Location"."Location_id" = "Location".id
--  WHERE "Location".country = 'France'
--  ;

-- ** SELECT les event se passant à une location precise **
--SELECT "Event".*
--  FROM "Event"
--  RIGHT JOIN
--  ( SELECT "Event_Location".event_id AS loc_id
--    FROM "Event_Location" LEFT JOIN "Location"
--    ON "Event_Location".location_id = "Location".id
--    WHERE "Location".country = 'France'
--  ) AS loc
--  ON "Event".id = loc.loc_id
--  --WHERE ("Event".datation).start < '2020-10-10'
--  ;
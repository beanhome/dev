SELECT DISTINCT 
  "Event".id, 
  "Event".name,
  "Event".description,
  "Event".datation,
  ("Event".datation).start as start
FROM "Event"

INNER JOIN
( SELECT
    "Event_Location".event_id AS loc_id
  FROM "Event_Location"
  LEFT JOIN "Location"
  ON "Event_Location".location_id = "Location".id
  WHERE "Location".country = 'France'
  AND "Location".city = 'Paris'
) AS loc
ON "Event".id = loc.loc_id

INNER JOIN
( SELECT 
    "Event_Role".event_id AS role_id
  FROM "Event_Role"
  WHERE pg_has_role('Scenariste', "Event_Role".role, 'MEMBER')
  OR "Event_Role".role = 'everybody'
) AS role
ON "Event".id = role.role_id

INNER JOIN
( SELECT
    "Event_Tags".event_id AS tag_id
  FROM "Event_Tags"
  LEFT JOIN "Tags"
  ON "Event_Tags".tag_id = "Tags".id
  WHERE "Tags".tag = 'Daemon'
  OR "Tags".tag = 'Faust'
) AS tag
ON "Event".id = tag.tag_id

WHERE ("Event".datation).start > '13-08-1754'
AND ("Event".datation).end < '16-07-2001'
AND update_date > '17-08-2011'
AND update_date < '12-09-2011'

ORDER BY start ASC;

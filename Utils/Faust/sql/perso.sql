SELECT "Player".first_name, "Player".last_name, "Perso".usual_name
  FROM "Player" FULL OUTER JOIN "Perso"
  ON "Player".id = "Perso".player
  ORDER BY "Player".first_name;
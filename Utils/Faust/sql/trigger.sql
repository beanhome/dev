CREATE OR REPLACE FUNCTION UpdateDate() RETURNS trigger AS $$
    BEGIN
        NEW.update_date := 'now';
        RETURN NEW;
    END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER "Event_UpdateDate"
  BEFORE UPDATE
  ON "Event"
  FOR EACH ROW
  EXECUTE PROCEDURE updatedate();
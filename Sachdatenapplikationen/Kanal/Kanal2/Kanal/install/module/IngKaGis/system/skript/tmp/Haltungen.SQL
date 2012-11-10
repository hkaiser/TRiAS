


/* Wenn eine neue Haltung angelegt wurde */
CREATE TRIGGER TRIG_HALTUNG_BEFORE_INSERT
FOR HALTUNG BEFORE INSERT AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dtOld      DATE;
  DECLARE VARIABLE dAblHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);
BEGIN
 /* Datum der letzten Spülung in Haltungen anpassen */

  dLange = 0.0;

END !!

/* Wenn eine Haltung geändert wurde wurde */
CREATE TRIGGER TRIG_HALTUNG_BEFORE_UPDATE
FOR HALTUNG AFTER UPDATE AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dGKRZul  DECIMAL (15, 3);
  DECLARE VARIABLE dGKHZul  DECIMAL (15, 3);
  DECLARE VARIABLE dGKRAbl  DECIMAL (15, 3);
  DECLARE VARIABLE dGKHAbl  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);
BEGIN
 /* Wenn Zu oder Ablauf geändert wurde, dann Länge neu berechnen */

   IF (OLD.IDZUL <> NEW.IDZUL) THEN BEGIN

    /* Länge der Haltung zwische Zu und Ablauf bestimmen */
    SELECT GKR     FROM ABLAUF   WHERE IDHALTUNG = NEW.ID INTO dGKRAbl;
    SELECT GKH     FROM ABLAUF   WHERE IDHALTUNG = NEW.ID INTO dGKHAbl;
    SELECT GKR     FROM ZULAUF   WHERE IDHALTUNG = NEW.ID INTO dGKRZul;
    SELECT GKH     FROM ZULAUF   WHERE IDHALTUNG = NEW.ID INTO dGKHZul;
/*    EXECUTE PROCEDURE PROC_CALC_HALTLANGE :dGKRZul, :dGKHZul, :dGKRAbl, :dGKHAbl, NEW.ID, 1;  */ /* Länge Haltung */
    UPDATE HALTUNG SET HALTUNG.MARKIERUNG = "Geändert" WHERE HALTUNG.ID = NEW.ID; 

  end

END !!



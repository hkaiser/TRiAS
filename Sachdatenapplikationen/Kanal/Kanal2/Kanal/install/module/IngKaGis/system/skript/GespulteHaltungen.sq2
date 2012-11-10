


/* Wenn eine neue gespülte Haltung angelegt wurde */
CREATE TRIGGER TRIG_SPLHALTUNGEN_BEFORE_INSERT
FOR SPLHALTUNGEN BEFORE INSERT AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dtOld      DATE;
  DECLARE VARIABLE dAblHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);
BEGIN
 /* Datum der letzten Spülung in Haltungen anpassen */

   nIDHaltung = NEW.IDHALTUNG;
   SELECT LETZTESPULUNG   FROM HALTUNG  WHERE ID = :nIDHaltung INTO dtOld;
   IF ((dtOld IS NULL) OR (dtOld < NEW.DATUM)) then begin
     UPDATE HALTUNG SET HALTUNG.LETZTESPULUNG = NEW.DATUM WHERE HALTUNG.ID = :nIDHaltung;
   end 

END !!


/* Wenn eine neue gespülte Haltung gelöscht wurde */
CREATE TRIGGER TRIG_SPLHALTUNGEN_AFTER_DELETE
FOR SPLHALTUNGEN AFTER DELETE AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dtOld      DATE;
  DECLARE VARIABLE dtTemp      DATE;
BEGIN
 /* Datum der letzten Spülung in Haltungen anpassen */
 /* Wenn die Spülung gelöscht wird, die als aktuelle in Haltungen eingetragen ist, */
 /* Dann die nächst Neueste suchen und in Haltungen eintragen */

   nIDHaltung = OLD.IDHALTUNG;
   SELECT HALTUNG.LETZTESPULUNG FROM HALTUNG WHERE ID = :nIDHaltung INTO dtOld;
   /* Wenn die gelöschte Spülung die in Haltungen als aktuelle Spülung vermerkte ist */
   IF (dtOld = OLD.DATUM) then begin
     /* Diejenige Spülung raussuchen, die am neuesten ist */
     dtOld = cast(NULL as DATE);
     FOR SELECT DATUM FROM SPLHALTUNGEN WHERE (IDHALTUNG = :nIDHaltung) AND (DATUM IS NOT NULL) INTO dtTemp
     DO BEGIN
       if ((dtTemp > dtOld) or (dtOld IS NULL)) then begin
         dtOld = dtTemp;
       end
     END
     /* neue aktuelle Spülung in Haltungen eintragen */
     UPDATE HALTUNG SET HALTUNG.LETZTESPULUNG = :dtOld WHERE HALTUNG.ID = :nIDHaltung;
   end 

END !!
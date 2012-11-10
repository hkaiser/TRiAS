/* Wenn am Deckel was geändert wurde */
CREATE TRIGGER TRIG_DECKEL_BEFORE_UPDATE
FOR DECKEL BEFORE UPDATE AS
  DECLARE VARIABLE lLangeDeckel SmallInt;
  DECLARE VARIABLE lOk SmallInt;

  DECLARE VARIABLE nIDSchachtO  Integer;
  DECLARE VARIABLE nIDSchachtU  Integer;
  DECLARE VARIABLE nIDHaltung   Integer;
  DECLARE VARIABLE nIDDeckel    Integer;
  DECLARE VARIABLE dDeckelGKR   FLOAT;
  DECLARE VARIABLE dDeckelGKH   FLOAT;

BEGIN

  lLangeDeckel = 0;
  lOk = 1;
  /* Wenn Deckelkoordinaten geändert wurden, Länge neu berechnen */
  IF (NEW.GKR <> OLD.GKR) THEN BEGIN
    lLangeDeckel = 1;
  END
  IF (NEW.GKH <> OLD.GKH) THEN BEGIN
    lLangeDeckel = 1;
  END
  
  /* Länge der Haltung zwischen Deckelkoordinaten bestimmen */
  IF (lLangeDeckel = 1) THEN BEGIN
    lOk = 1;
    /* Schacht bestimmen, dessen Deckel verschoben wurde */
    IF (lOk = 1) THEN BEGIN
      SELECT ID     FROM SCHACHT   WHERE ID = NEW.IDSCHACHT INTO nIDSchachtO;
      IF (nIDSchachtO = 0) THEN lOk = 0;
    END
    IF (lOk = 1) THEN BEGIN
      /* Alle Haltungen bestimmen, die mit diesem Schacht als SchachtOben verknüpft sind */
      FOR SELECT ID FROM HALTUNG WHERE (IDSCHO = :nIDSchachtO) INTO nIDHaltung
        DO BEGIN
UPDATE HALTUNG SET HALTUNG.BEZEICH2 = "Deckelkoordinate" WHERE HALTUNG.ID = :nIDHaltung;
          /* den unteren Schacht suchen
          SELECT IDSCHU     FROM HALTUNG  WHERE (ID = :nIDHALTUNG)  INTO nIDSchachtU;
          /* Den Deckel des unteren Schacht suchen */
          SELECT ID         FROM DECKEL    WHERE ((IDSCHACHT = :nIDSchachtU) AND (DECKEL.NR = 0)) INTO nIDDeckel;
          IF (nIDDeckel = 0) THEN lOk = 0;
          /* Die Koordinaten des Unteren Deckels holen */  
          IF (lOk = 1) THEN BEGIN
UPDATE HALTUNG SET HALTUNG.BEZEICH2 = "Deckelkoordinate 2" WHERE HALTUNG.ID = :nIDHaltung;
            SELECT GKR        FROM DECKEL    WHERE ID = :nIDDeckel INTO dDeckelGKR;
            SELECT GKH        FROM DECKEL    WHERE ID = :nIDDeckel INTO dDeckelGKH;
            EXECUTE PROCEDURE PROC_CALC_HALTLANGE NEW.GKR, NEW.GKH, :dDeckelGKR, :dDeckelGKH, :nIDHaltung, 0; /* Länge zwischen Deckel */              
          END
      END
      /* Alle Haltungen bestimmen, die mit diesem Schacht als SchachtUnten verknüpft sind */
      FOR SELECT ID FROM HALTUNG WHERE (IDSCHU = :nIDSchachtO) INTO nIDHaltung
        DO BEGIN
UPDATE HALTUNG SET HALTUNG.BEZEICH2 = "Deckelkoordinate 3" WHERE HALTUNG.ID = :nIDHaltung;
          /* den oberen Schacht suchen
          SELECT IDSCHO     FROM HALTUNG  WHERE (ID = :nIDHALTUNG)  INTO nIDSchachtO;
          /* Den Deckel des oberen Schacht suchen */
          SELECT ID         FROM DECKEL    WHERE ((IDSCHACHT = :nIDSchachtO) AND (DECKEL.NR = 0)) INTO nIDDeckel;
          IF (nIDDeckel = 0) THEN lOk = 0;
          /* Die Koordinaten des Unteren Deckels holen */  
          IF (lOk = 1) THEN BEGIN
UPDATE HALTUNG SET HALTUNG.BEZEICH2 = "Deckelkoordinate 4" WHERE HALTUNG.ID = :nIDHaltung;
            SELECT GKR        FROM DECKEL    WHERE ID = :nIDDeckel INTO dDeckelGKR;
            SELECT GKH        FROM DECKEL    WHERE ID = :nIDDeckel INTO dDeckelGKH;
            EXECUTE PROCEDURE PROC_CALC_HALTLANGE NEW.GKR, NEW.GKH, :dDeckelGKR, :dDeckelGKH, :nIDHaltung, 0; /* Länge zwischen Deckel */              
          END
      END
    END
  END
END !!

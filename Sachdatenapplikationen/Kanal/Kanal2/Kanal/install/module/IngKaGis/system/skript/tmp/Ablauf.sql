/* Wenn am Ablauf was ge�ndert wurde */
CREATE TRIGGER TRIG_ABLAUF_BEFORE_UPDATE
FOR ABLAUF BEFORE UPDATE AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dZulHoehe  FLOAT;
  DECLARE VARIABLE dAblHoehe  FLOAT;
  DECLARE VARIABLE dLange     FLOAT;

  DECLARE VARIABLE nIDSCHO INTEGER;
  DECLARE VARIABLE nIDSCHU INTEGER;
  DECLARE VARIABLE nIDDeckelO INTEGER;
  DECLARE VARIABLE nIDDeckelU INTEGER;
  DECLARE VARIABLE dDeckelOGKR    FLOAT;
  DECLARE VARIABLE dDeckelOGKH    FLOAT;
  DECLARE VARIABLE dDeckelUGKR    FLOAT;
  DECLARE VARIABLE dDeckelUGKH    FLOAT;

  DECLARE VARIABLE dZulGKR    FLOAT;
  DECLARE VARIABLE dZulGKH    FLOAT;

  DECLARE VARIABLE lLangeHaltung SmallInt;
  DECLARE VARIABLE lLangeDeckel SmallInt;
  DECLARE VARIABLE lGefalle SmallInt;
  DECLARE VARIABLE lOk SmallInt;
  
BEGIN
  lLangeHaltung   = 0;
  lLangeDeckel    = 0;
  lGefalle = 0;
  /* Wenn Haltungsverkn�pfung ge�ndert wurde, dann Haltungsl�nge neu berechnen */
  IF ((NEW.IDHALTUNG <> OLD.IDHALTUNG) ) THEN BEGIN 
    lLangeHaltung = 1;
    lLangeDeckel = 1;
    lGefalle = 1;
  END

  /* Wenn Ablaufh�he ge�ndert wurde, gef�lle neu berechnen */
  IF (NEW.GKHOEHE <> OLD.GKHOEHE) THEN BEGIN
    lGefalle = 1;
  END

  /* Wenn AblaufKoordinaten ge�ndert wurden, L�nge und Gef�lle neu berechnen */
  IF (NEW.GKR <> OLD.GKR) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
  /* Wenn AblaufKoordinaten ge�ndert wurden, L�nge und Gef�lle neu berechnen */
  IF (NEW.GKH <> OLD.GKH) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
  lLangeHaltung   = 0;
  lLangeDeckel    = 0;
  lGefalle = 0;

 IF (lLangeDeckel = 1) THEN BEGIN
    /* L�nge der Haltung zwischen Deckelkoordinaten bestimmen */
    lOk = 1;
    IF (lOk = 1) THEN BEGIN
      SELECT IDSCHO     FROM HALTUNG   WHERE ID = NEW.IDHaltung INTO nIDSCHO;
      IF (nIDSCHO = 0) THEN lOk = 0;
    END
    IF (lOk = 1) THEN BEGIN
      SELECT IDSCHU     FROM HALTUNG   WHERE ID = NEW.IDHaltung INTO nIDSCHU;
      IF (nIDSCHU = 0) THEN lOk = 0;
    END
    IF (lOk = 1) THEN BEGIN
      SELECT ID         FROM DECKEL    WHERE ((IDSCHACHT = :nIDSCHO) AND (DECKEL.NR = 0)) INTO nIDDeckelO;
      IF (nIDDeckelO = 0) THEN lOk = 0;
    END
    IF (lOk = 1) THEN BEGIN
      SELECT ID         FROM DECKEL    WHERE ((IDSCHACHT = :nIDSCHU) AND (DECKEL.NR = 0)) INTO nIDDeckelU;
      IF (nIDDeckelU = 0) THEN lOk = 0;
    END
    IF (lOk = 1) THEN BEGIN
      SELECT GKR        FROM DECKEL    WHERE ID = :nIDDeckelO INTO dDeckelOGKR;
      SELECT GKH        FROM DECKEL    WHERE ID = :nIDDeckelO INTO dDeckelOGKH;
      SELECT GKR        FROM DECKEL    WHERE ID = :nIDDeckelU INTO dDeckelUGKR;
      SELECT GKH        FROM DECKEL    WHERE ID = :nIDDeckelU INTO dDeckelUGKH;      
    END
    IF (lOk = 1) THEN BEGIN
      EXECUTE PROCEDURE PROC_CALC_HALTLANGE :dDeckelOGKR, :dDeckelOGKH, :dDeckelUGKR, :dDeckelUGKH, NEW.IDHALTUNG, 0; /* L�nge zwischen Deckel */
    END
  END

  IF (lLangeHaltung = 1) THEN BEGIN
    /* L�nge der Haltung zwische Zu und Ablauf bestimmen */
    SELECT GKR     FROM ZULAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dZulGKR;
    SELECT GKH     FROM ZULAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dZulGKH;
    EXECUTE PROCEDURE PROC_CALC_HALTLANGE NEW.GKR, NEW.GKH, :dZulGKR, dZulGKH, NEW.IDHALTUNG, 1; /* L�nge Haltung */
  END

  IF (lGefalle = 1) THEN BEGIN
    dAblHoehe  = NEW.GKHOEHE;
    nIDHaltung = NEW.IDHALTUNG;
    SELECT GKHOEHE     FROM ZULAUF   WHERE IDHALTUNG = :nIDHaltung INTO dZulHoehe;
    SELECT LANGEHALTUNG FROM HALTUNG  WHERE ID =        :nIDHaltung INTO dLange;
    EXECUTE PROCEDURE PROC_CALC_HALTGEFALLE :dAblHoehe , :dZulHoehe, :dLange, :nIDHaltung;
/*    UPDATE HALTUNG SET HALTUNG.MARKIERUNG = cast(:dLange as VARCHAR(25)) WHERE HALTUNG.ID = NEW.IDHALTUNG; */
  END
END !!




/* Wenn ein neuer Ablauf angelegt wurde */
CREATE TRIGGER TRIG_ABLAUF_BEFORE_INSERT
FOR ABLAUF BEFORE INSERT AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dZulHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dAblHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);
BEGIN
 /* Haltungsgef�lle neu berechnen */

   dAblHoehe  = NEW.GKHOEHE;
   nIDHaltung = NEW.IDHALTUNG;
   IF (nIDHaltung > 0) then begin
     SELECT GKHOEHE     FROM ZULAUF   WHERE IDHALTUNG = :nIDHaltung INTO dZulHoehe;
     SELECT LANGEDECKEL FROM HALTUNG  WHERE ID =        :nIDHaltung INTO dLange;
     EXECUTE PROCEDURE PROC_CALC_HALTGEFALLE :dAblHoehe , :dZulHoehe, :dLange, :nIDHaltung;
   end
END !!

/* SQL Skript zur Automatisierung von Berechnungen in der KI- Datenbank */
/* LETZTE ÄNDERUNG 31.3.1999 */
/* DURCHGEFÜHRT VON NIKO */

/* Folgende Zeile schaltet Fehlermeldungen aus, da DROP einen Fehler liefert, wenn das Objekt erst garnicht existiert */
SET ECHO OFF

/* Befehlstermiatorzeichen auf Semikolon schalten */
SET TERM !! ;

DROP TRIGGER TRIG_DECKEL_BEFORE_UPDATE ;


DROP TRIGGER TRIG_ZULAUF_BEFORE_UPDATE ;


DROP TRIGGER TRIG_ZULAUF_BEFORE_INSERT ;


DROP TRIGGER TRIG_ABLAUF_BEFORE_UPDATE ;


DROP TRIGGER TRIG_ABLAUF_BEFORE_INSERT ;


DROP TRIGGER TRIG_HALTUNG_BEFORE_UPDATE ;


DROP TRIGGER TRIG_HALTUNG_BEFORE_INSERT ;


DROP TRIGGER TRIG_SPLHALTUNGEN_BEFORE_INSERT ;


DROP TRIGGER TRIG_SPLHALTUNGEN_AFTER_DELETE ;


DROP PROCEDURE PROC_CALC_HALTGEFALLE;


DROP PROCEDURE PROC_CALC_HALTLANGE;


DROP PROCEDURE PROC_CALC_SQRT;


DROP PROCEDURE PROC_CALC_FABS;

/* Fehlermeldungen wieder einschalten */
SET ECHO ON

/* Befehlstermiatorzeichen auf Semikolon schalten */
SET TERM ; !!

CREATE PROCEDURE PROC_CALC_HALTGEFALLE( dx DECIMAL(15, 3),dy DECIMAL(15, 3),dLange DECIMAL(15, 3), nIDHaltung INTEGER) 
AS
  DECLARE VARIABLE dGefaelle  FLOAT;
BEGIN
/*  UPDATE HALTUNG SET HALTUNG.MARKIERUNG = "GEFAELLE_1" WHERE HALTUNG.ID = :nIDHaltung;
*/
  IF (dLange > 0.0 ) THEN BEGIN
    dGefaelle = (((dx - dy) / dLange ) * 1000.0);
    UPDATE HALTUNG SET HALTUNG.GEFAELLE = :dGefaelle WHERE HALTUNG.ID = :nIDHaltung;
/*    UPDATE HALTUNG SET HALTUNG.MARKIERUNG = "GEFAELLE" WHERE HALTUNG.ID = :nIDHaltung; */
  END
END !!


CREATE PROCEDURE PROC_CALC_FABS(d FLOAT) RETURNS (res FLOAT)
AS
BEGIN
  res = d;
  IF (d < 0.0) THEN BEGIN
   res = - d;
  END
END !!


CREATE PROCEDURE PROC_CALC_SQRT( d FLOAT ) RETURNS (dRes FLOAT)
AS
  DECLARE VARIABLE dLastRes  FLOAT;
  DECLARE VARIABLE dStep     FLOAT;
  DECLARE VARIABLE dBuf      FLOAT;
  DECLARE VARIABLE dBuf2     FLOAT;
  DECLARE VARIABLE i         Integer;
  DECLARE VARIABLE lDir      SmallInt;
  DECLARE VARIABLE lLoop     SmallInt;
BEGIN
  if (d > 1.0) then begin
    dStep = 4.0;
  end else begin
    dStep = 1.0;
  end
  dRes = 5.0;
  dLastRes = 0.0;
  lDir = 0;
  i=0;
  lLoop = 1;
  while (lLoop = 1) do begin
    dLastRes = dRes;
    if ((dRes * dRes) > d) then begin
      dRes = dRes - dStep;
      if (lDir = 1) then dStep = dStep / 2.0;
      lDir = 0;
    end else if ((dRes * dRes) < d) then begin
      dRes = dRes + dStep;
      if (lDir= 0) then dStep = dStep / 2.0;
      lDir = 1;
    end
    i = i + 1;
    dBuf = dRes - dLastRes;
    EXECUTE PROCEDURE PROC_CALC_FABS :dBuf RETURNING_VALUES :dBuf2;
    IF ((dBuf2 < 0.001) OR (i > 100)) THEN BEGIN
      lLoop = 0;
    END
    IF (i > 100) THEN BEGIN
      dRes = -1;
    END
  end
end  !!


/* nTyp = 0 -> Lange Deckel */
/* nTyp = 1 -> Lange Haltung */
/* nTyp = 2 -> Lange Schacht */
CREATE PROCEDURE PROC_CALC_HALTLANGE( dx1 DECIMAL(15, 3),dy1 DECIMAL(15, 3),dx2 DECIMAL(15, 3),dy2 DECIMAL(15, 3), nIDHaltung INTEGER, nTyp INTEGER) 
AS
  DECLARE VARIABLE dxDiff  FLOAT;
  DECLARE VARIABLE dyDiff  FLOAT;
  DECLARE VARIABLE dLange  FLOAT;
  DECLARE VARIABLE dBuf    FLOAT;
  DECLARE VARIABLE lOk     SmallInt;

BEGIN
  lOk = 1;
  IF ((dx1 = 0.0) or (dy1 = 0.0) or (dx2 = 0.0) or (dy2 = 0.0)) THEN BEGIN
    lOk = 0;
  END
  IF ((dx1 IS NULL) or (dy1 IS NULL) or (dx2 IS NULL) or (dy2 IS NULL)) THEN BEGIN
    lOk = 0;
  END
  if (lOk = 1) then begin
    dxDiff = dx1 - dx2;
    EXECUTE PROCEDURE PROC_CALC_FABS :dxDiff RETURNING_VALUES :dxDiff;
    dyDiff = dy1 - dy2;
    EXECUTE PROCEDURE PROC_CALC_FABS :dyDiff RETURNING_VALUES :dyDiff;
    UPDATE HALTUNG SET HALTUNG.BEZEICH2 = cast(:dxDiff as VARCHAR(25)) WHERE HALTUNG.ID = :nIDHaltung;
    UPDATE HALTUNG SET HALTUNG.BEZEICH3 = cast(:dyDiff as VARCHAR(25)) WHERE HALTUNG.ID = :nIDHaltung;
  

    dBuf = (dxDiff * dxDiff) + (dyDiff * dyDiff);
    EXECUTE PROCEDURE PROC_CALC_SQRT :dBuf RETURNING_VALUES :dLange;
    IF (nTyp =0 ) THEN BEGIN
      UPDATE HALTUNG SET HALTUNG.LANGEDECKEL  = :dLange WHERE HALTUNG.ID = :nIDHaltung; 
    END ELSE IF (nTyp=1) THEN BEGIN
      UPDATE HALTUNG SET HALTUNG.LANGEHALTUNG = :dLange WHERE HALTUNG.ID = :nIDHaltung; 
    END ELSE IF (nTyp=2) THEN BEGIN
      UPDATE HALTUNG SET HALTUNG.LANGESCHACHT = :dLange WHERE HALTUNG.ID = :nIDHaltung; 
    END
  END
END !!


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




/* Wenn am Zulauf was geändert wurde */
CREATE TRIGGER TRIG_ZULAUF_BEFORE_UPDATE
FOR ZULAUF BEFORE UPDATE AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dZulHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dAblHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);

  DECLARE VARIABLE dAblGKR    FLOAT;
  DECLARE VARIABLE dAblGKH    FLOAT;

  DECLARE VARIABLE nIDSCHO INTEGER;
  DECLARE VARIABLE nIDSCHU INTEGER;
  DECLARE VARIABLE nIDDeckelO INTEGER;
  DECLARE VARIABLE nIDDeckelU INTEGER;
  DECLARE VARIABLE dDeckelOGKR    FLOAT;
  DECLARE VARIABLE dDeckelOGKH    FLOAT;
  DECLARE VARIABLE dDeckelUGKR    FLOAT;
  DECLARE VARIABLE dDeckelUGKH    FLOAT;

  DECLARE VARIABLE lLangeHaltung SmallInt;
  DECLARE VARIABLE lLangeDeckel SmallInt;
  DECLARE VARIABLE lGefalle SmallInt;
  DECLARE VARIABLE lOk SmallInt;
  
BEGIN
  lLangeHaltung   = 0;
  lLangeDeckel    = 0;
  lGefalle        = 0;
  /* Wenn Haltungsverknüpfung geändert wurde, dann Haltungslänge neu berechnen */
  IF ((NEW.IDHALTUNG <> OLD.IDHALTUNG) ) THEN BEGIN 
    lLangeHaltung = 1;
    lLangeDeckel = 1;
    lGefalle = 1;
  END

  /* Wenn Zulaufhöhe geändert wurde, gefälle neu berechnen */
  IF (NEW.GKHOEHE <> OLD.GKHOEHE) THEN BEGIN
    lGefalle = 1;
  END
 
  /* Wenn ZulaufKoordinaten geändert wurden, Länge und Gefälle neu berechnen */
  IF (NEW.GKR <> OLD.GKR) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
  /* Wenn ZulaufKoordinaten geändert wurden, Länge und Gefälle neu berechnen */
  IF (NEW.GKH <> OLD.GKH) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
 IF (lLangeDeckel = 1) THEN BEGIN
    /* Länge der Haltung zwischen Deckelkoordinaten bestimmen */
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
      EXECUTE PROCEDURE PROC_CALC_HALTLANGE :dDeckelOGKR, :dDeckelOGKH, :dDeckelUGKR, :dDeckelUGKH, NEW.IDHALTUNG, 0; /* Länge zwischen Deckel */
    END
  END

 IF (lLangeHaltung = 1) THEN BEGIN
    /* Länge der Haltung zwische Zu und Ablauf bestimmen */
    SELECT GKR     FROM ABLAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dAblGKR;
    SELECT GKH     FROM ABLAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dAblGKH;
    EXECUTE PROCEDURE PROC_CALC_HALTLANGE NEW.GKR, NEW.GKH, :dAblGKR, :dAblGKH, NEW.IDHALTUNG, 1; /* Länge Haltung */
  END

  IF (lGefalle = 1) THEN BEGIN
    dZulHoehe  = NEW.GKHOEHE;
    nIDHaltung = NEW.IDHALTUNG;
    SELECT GKHOEHE     FROM ABLAUF   WHERE IDHALTUNG = :nIDHaltung INTO dAblHoehe;
    SELECT LANGEDECKEL FROM HALTUNG  WHERE ID =        :nIDHaltung INTO dLange;
    EXECUTE PROCEDURE PROC_CALC_HALTGEFALLE :dAblHoehe , :dZulHoehe, :dLange, :nIDHaltung;
  END
END !!


/* Wenn ein neuer Zulauf angelegt wurde */
CREATE TRIGGER TRIG_ZULAUF_BEFORE_INSERT
FOR ZULAUF BEFORE INSERT AS
  DECLARE VARIABLE nIDHaltung INTEGER;
  DECLARE VARIABLE dZulHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dAblHoehe  DECIMAL (15, 3);
  DECLARE VARIABLE dLange     DECIMAL (15, 3);
BEGIN
 /* Haltungsgefälle neu berechnen */

   dZulHoehe  = NEW.GKHOEHE;
   nIDHaltung = NEW.IDHALTUNG;
   IF (nIDHaltung > 0) then begin
     SELECT GKHOEHE     FROM ABLAUF   WHERE IDHALTUNG = :nIDHaltung INTO dAblHoehe;
     SELECT LANGEDECKEL FROM HALTUNG  WHERE ID =        :nIDHaltung INTO dLange;
     EXECUTE PROCEDURE PROC_CALC_HALTGEFALLE :dAblHoehe , :dZulHoehe, :dLange, :nIDHaltung;
   end
END !!


/* Wenn am Ablauf was geändert wurde */
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
  /* Wenn Haltungsverknüpfung geändert wurde, dann Haltungslänge neu berechnen */
  IF ((NEW.IDHALTUNG <> OLD.IDHALTUNG) ) THEN BEGIN 
    lLangeHaltung = 1;
    lLangeDeckel = 1;
    lGefalle = 1;
  END

  /* Wenn Ablaufhöhe geändert wurde, gefälle neu berechnen */
  IF (NEW.GKHOEHE <> OLD.GKHOEHE) THEN BEGIN
    lGefalle = 1;
  END

  /* Wenn AblaufKoordinaten geändert wurden, Länge und Gefälle neu berechnen */
  IF (NEW.GKR <> OLD.GKR) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
  /* Wenn AblaufKoordinaten geändert wurden, Länge und Gefälle neu berechnen */
  IF (NEW.GKH <> OLD.GKH) THEN BEGIN
    lLangeHaltung = 1;
    lGefalle = 1;
  END
 
 
 IF (lLangeDeckel = 1) THEN BEGIN
    /* Länge der Haltung zwischen Deckelkoordinaten bestimmen */
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
      EXECUTE PROCEDURE PROC_CALC_HALTLANGE :dDeckelOGKR, :dDeckelOGKH, :dDeckelUGKR, :dDeckelUGKH, NEW.IDHALTUNG, 0; /* Länge zwischen Deckel */
    END
  END

  IF (lLangeHaltung = 1) THEN BEGIN
    /* Länge der Haltung zwische Zu und Ablauf bestimmen */
    SELECT GKR     FROM ZULAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dZulGKR;
    SELECT GKH     FROM ZULAUF   WHERE IDHALTUNG = NEW.IDHaltung INTO dZulGKH;
    EXECUTE PROCEDURE PROC_CALC_HALTLANGE NEW.GKR, NEW.GKH, :dZulGKR, dZulGKH, NEW.IDHALTUNG, 1; /* Länge Haltung */
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
 /* Haltungsgefälle neu berechnen */

   dAblHoehe  = NEW.GKHOEHE;
   nIDHaltung = NEW.IDHALTUNG;
   IF (nIDHaltung > 0) then begin
     SELECT GKHOEHE     FROM ZULAUF   WHERE IDHALTUNG = :nIDHaltung INTO dZulHoehe;
     SELECT LANGEDECKEL FROM HALTUNG  WHERE ID =        :nIDHaltung INTO dLange;
     EXECUTE PROCEDURE PROC_CALC_HALTGEFALLE :dAblHoehe , :dZulHoehe, :dLange, :nIDHaltung;
   end
END !!


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


/* SQL Skript zur Automatisierung von Berechnungen in der KI- Datenbank */
/* LETZTE ÄNDERUNG 31.3.1999 */
/* DURCHGEFÜHRT VON NIKO */

/* Folgende Zeile schaltet Fehlermeldungen aus, da DROP einen Fehler liefert, wenn das Objekt erst garnicht existiert */
SET ECHO OFF

/* Befehlstermiatorzeichen auf Semikolon schalten */
/* SET TERM !! ; */

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




/* SQL Skript zur Automatisierung von Berechnungen in der KI- Datenbank */
/* LETZTE ÄNDERUNG 13.6.1999 */
/* DURCHGEFÜHRT VON NIKO */

/* erst mal alle vorhandenen Trigger löschen */
SET INCLUDE DelTrigger.SQ2

/* Utils */
SET INCLUDE Util.SQ2

/* Neue geänderte Haltungen */
SET INCLUDE Haltungen.SQ2

/* Gespülte Haltungen */
SET INCLUDE GespulteHaltungen.SQ2


/* Zuläufe */
SET INCLUDE Zulauf.SQ2

/* Abläufe */
SET INCLUDE Ablauf.SQ2

/* Deckel */
SET INCLUDE Deckel.SQ2

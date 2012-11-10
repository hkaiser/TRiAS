/* SQL Skript zur Automatisierung von Berechnungen in der KI- Datenbank */
/* LETZTE ÄNDERUNG 13.6.1999 */
/* DURCHGEFÜHRT VON NIKO */

/* erst mal alle vorhandenen Trigger löschen */
SET INCLUDE DelTrigger.SQL

/* Utils */
SET INCLUDE Util.SQL

/* Neue geänderte Haltungen */
SET INCLUDE Haltungen.SQL

/* Gespülte Haltungen */
SET INCLUDE GespulteHaltungen.SQL


/* Zuläufe */
SET INCLUDE Zulauf.SQL

/* Abläufe */
SET INCLUDE Ablauf.SQL

/* Deckel */
SET INCLUDE Deckel.SQL

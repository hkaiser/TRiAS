;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASOleDB
;// SourceFile: OleDBMSG.MC
;
;#if !defined(_OLEDBMSG_HMC)
;#define _OLEDBMSG_HMC
;
;#if _MSC_VER >= 1000
;#pragma once
;#endif // _MSC_VER >= 1000
;

;#define MAX_MSG_LENGTH				1024
;#define SEVERITY_MASK					0xC0000000
;#define APPLICATION_MASK				0x20000000
;#define SEVERITY_SUCCESS_MASK			0x00000000
;#define SEVERITY_INFORMATIONAL_MASK	0x40000000
;#define SEVERITY_WARNING_MASK			0xB0000000
;#define SEVERITY_ERROR_MASK			0xC0000000

;#define FACILITY_MASK					0x0FFF0000
;#define FACILITY_FACILITY_DATASOURCE	0x0F200000
;#define FACILITY_FACILITY_SESSION		0x0F210000
;#define FACILITY_FACILITY_ROWSET		0x0F220000
;#define FACILITY_FACILITY_COMMAND		0x0F230000
;#define FACILITY_FACILITY_GEN_PURPOSE	0x0F2F0000

SeverityNames = (
	Success = 0x0:STATUS_SEVERITY_SUCCESS
	Informational = 0x1:STATUS_SEVERITY_INFORMATIONAL
	Warning = 0x2:STATUS_SEVERITY_WARNING
	Error = 0x3:STATUS_SEVERITY_ERROR
)

FacilityNames = (
	System = 0x0FF
	DataSource = 0xF20:FACILITY_DATASOURCE	; Fehler der Datenquelle
	Session = 0xF21:FACILITY_SESSION		; Fehler einer Session
	RowSet = 0xF22:FACILITY_ROWSET			; Fehler eines RowSets
	Command = 0xF23:FACILITY_COMMAND		; Fehler eines Commands
	GenPurpose = 0xF2F:FACILITY_GENPURPOSE	; Allgemeiner Fehler 
)

LanguageNames = (
	Deutsch=0x407:MSG00407
	English=0x409:MSG00409
)

MessageIdTypedef=HRESULT

;
MessageId=0x1001
Severity=Error
Facility=RowSet
SymbolicName=TRIASOLEDB_E_NOSELECTSTMT
Language=Deutsch
Es ist keine 'SELECT' Klausel im SQL-Kommando gegeben.
.

Language=English
'SELECT' clause is missing from SQL command.
.

;
MessageId=0x1002
Severity=Error
Facility=RowSet
SymbolicName=TRIASOLEDB_E_NOSELECTEXPRESSION
Language=Deutsch
Es ist keine Auswahlausdruck in der 'SELECT' Klausel des SQL-Kommandos gegeben.
.

Language=English
Expression missing from 'SELECT' clause in SQL command.
.

;
MessageId=0x1003
Severity=Error
Facility=RowSet
SymbolicName=TRIASOLEDB_E_SELECTEXPECTED
Language=Deutsch
Es wurde ein 'SELECT' Befehl erwartet.
.

Language=English
'SELECT' statement expected.
.

;
MessageId=0x1004
Severity=Error
Facility=RowSet
SymbolicName=TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE
Language=Deutsch
Eine im 'SELECT' Befehl referenzierte Tabelle fehlt in der 'FROM' Klausel.
.

Language=English
Table referenced in 'SELECT' not given in 'FROM' clause.
.

;
MessageId=0x1005
Severity=Error
Facility=RowSet
SymbolicName=TRIASOLEDB_E_SQL_TYPEMISMATCH
Language=Deutsch
Der SQL Befehl enthält Typ-Inkompatibilitäten.
.

Language=English
There is a type mismatch in the SQL statement.
.

;#endif // _OLEDBMSG_HMC

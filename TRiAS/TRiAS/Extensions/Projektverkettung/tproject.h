// Datei enthält die RessourceID - Definitionen für Projektverwaltung
// File: TPROJECT.H


#if !defined(_TPROJECT_H)
#define _TPROJECT_H

#include "tproj32\resource.h"

// MenuID's
// hat keine eigenen Menu's, nur einen MenuPunkt

#define CPROJECTEXTENSIONMENU	100

// MenuUnterPunkt-IDs: müssen im Bereich von 1 bis 99 liegen

#define IDM_DEFPROJECT		1
#define IDM_SEARCHPROJECT	2
#define IDM_SETCONT		3
#define IDM_OPENPREVIOUSPROJECT	4
#define IDM_OPENPREVIOUSLEVEL	5

#define IDM_ABOUT		9

#define IDM_SHOWPROJECT		10
#define IDM_DEFWNDPROJECT	12

#define IDM_TPROJECT		20

//	Def-Fenster
#define TPROJECTDEFINITION	500

//	MK-Fenster
#define TPROJECTMCODE		600

//	Korrektur-Fenster
#define TPROJECTKORREKTUR	700

//
#define IDLB_TPROJECTS		1500
#define IDS_TPROJECTSDIR	1501
#define IDS_TPROJECTKEY		1502
#define IDB_TPROJECTSEARCH	1503
#define IDB_TPROJECTDELETE	1504
#define IDB_TPROJECTSTORE	1505
#define IDB_TPROJECTSEARCHMOD	1506
//
#define IDLB_TPMKLIST		1510
#define IDS_TPMCODE		1511

//
#define IDT_TPCAPTION		1550
#define IDT_HEADTPMCODEIDENT	1551
#define IDT_HEADTPMCODETEXT	1552

//
#define IDC_TPPROJECTINI        1560
#define IDC_TPROJECTPFAD        1561
#define IDC_DELBUTTON           1570

// StringRessourcen
#define IDS_PROJECTMENUITEM	2000
#define IDS_PREVPROJECT		2001
#define IDS_PROJECTDEF		2002
#define IDS_PROJECTS		2003
#define IDS_PROJECTSUBDIR	2004
#define IDS_PROFILEEXT		2005
#define IDS_DATABASEEXT		2006
#define IDS_TPNOPROJECTKEY	2007
#define IDS_TPSEARCHCAPTION	2008
#define IDS_TPOPENPOPUP		2009
#define IDS_TPORWINDOWCAPTION	2010
#define IDS_TPORWINDOWFALSE	2011
#define IDS_TPNORELATION	2012
//-------------------------------------
#define IDS_GLOBALDELETE                2020
#define IDS_LOCALDELETE                 2021

//-------------------------------------
//neu
#define IDS_LONGCLASSNAME	2100
#define IDS_ININOWRITABLE	2101
#endif 	// _TPROJECT_H

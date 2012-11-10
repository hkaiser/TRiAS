/*
Datei: ABFARMAP.H

Das Modul relisert die Verwaltung einer Abfallartenmap.

Erarbeitet: J. Benkenstein		Stand vom: 7.1.1997
*/

#ifndef _ABFARMAP_H
#define _ABFARMAP_H

class CAbfallArt : public CObject
{
public:
//	Attribute
	double m_dDichte;
	BOOL m_bSonderAbfall;

//	Konstruktor/Destruktor
	CAbfallArt (double dDichte, BOOL bSonderAbfall)
	{ m_dDichte = dDichte; m_bSonderAbfall = bSonderAbfall; }
};

class CAbfallArtenMap : public CMapStringToOb
{
public:
//	Konstruktor/Destruktor
	CAbfallArtenMap (void) {}
	~CAbfallArtenMap (void);		//	Löschen aller Einträge

//	Abfallart in Map einfügen
	BOOL AddAbfallArt (const CString &strAbfallArt, double dDichte, BOOL bSonderAbfall);
};

#endif		//	_ABFARMAP_H

#ifndef _LINIE_H_
#define _LINIE_H_

//	Datei:	Linie.h
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "koorpaar.h"
#include "geoobj.hpp"

class CFunktion;
class CEDBSObjekt;

class CLinie : public CObject
{	
BOOL		m_bGueltig;
	CKoordPaar	m_EndPunkt;
	char		m_Art[3];
	CObArray	m_Funktionen;
	CObArray	m_Punkte;

public:
	char SplineKennung();
				CLinie();
				~CLinie();

	short		Lesen( const char* );
	short		LesenALK( const char* );
	BOOL		&Gueltig()			{ return m_bGueltig; }
	const char	*ArtGeometrie()		{ return m_Art; }
	short		PunkteZahl()		{ return m_Punkte.GetSize(); }
	short		FktZahl()			{ return m_Funktionen.GetSize(); }
	double		EndPunktHoch()		{ return m_EndPunkt.Hoch(); }
	double		EndPunktRechts()	{ return m_EndPunkt.Rechts(); }
	CFunktion	*Funktion( short f )
						{ return (CFunktion*)m_Funktionen[f]; }
	double		PunktHoch( short );
	double		PunktRechts( short );
protected:
	char m_cSplineKennung;
};

class CFunktion : public CObject
{	BOOL		m_bGueltig;
	char		m_Folie[4];
	char		m_ObjArt[5];
	char		m_ObjNr1[8];
	char		m_ObjNr2[8];
	char		m_ObjTeilNr1[4];
	char		m_ObjTeilNr2[4];
	char		m_LinienTeilung1[2];
	char		m_LinienTeilung2[2];
	CString		m_FachParam;

public:
				CFunktion();
				~CFunktion();
	short		Lesen( const char* );
	short		LesenALK( const char* );
	BOOL		Gueltig()		{ return m_bGueltig; }
	const char	*Folie()		{ return m_Folie; }
	const char	*ObjArt()		{ return m_ObjArt; }
	const char	*ObjNr1()		{ return m_ObjNr1; }
	const char	*ObjNr2()		{ return m_ObjNr2; }
	const char	*ObjTeilNr1()	{ return m_ObjTeilNr1; }
	const char	*ObjTeilNr2()	{ return m_ObjTeilNr2; }
	const char	*LinienTeilung1()	{ return m_LinienTeilung1; }
	const char	*LinienTeilung2()	{ return m_LinienTeilung2; }
	const char	*FachParam()	{ return m_FachParam; }
};

class CEDBSObjekt : public CObject
{
	BOOL		m_bGueltig;
	char		m_Folie[4];
	char		m_ObjArt[5];
	char		m_Aktuali[3];
	char		m_ObjTyp[2];
	char		m_ObjNr[8];
	char		m_ModellTyp[3];
	char		m_EDatum[7];
	char		m_ModKenn[2];

public:
				CEDBSObjekt();
				~CEDBSObjekt();
	short		Lesen( const char* );
	short		LesenALK( const char* );
	BOOL		Gueltig()		{ return m_bGueltig; }
	const char	*Folie()		{ return m_Folie; }
	const char	*ObjArt()		{ return m_ObjArt; }
	const char	*Aktuali()		{ return m_Aktuali; }
	const char	*ObjTyp()		{ return m_ObjTyp; }
	const char	*ObjNr()		{ return m_ObjNr; }
	const char	*ModellTyp()	{ return m_ModellTyp; }
	const char	*EDatum()		{ return m_EDatum; }
	const char	*ModKenn()		{ return m_ModKenn; }
};

class CInfo : public CObject
{
	BOOL		m_bGueltig;
	char		m_ArtInfo[3];
	char		m_KartenTyp[3];
	char		m_ObjArt[7];
	char		m_Text[34];
	char		m_ArtGeo[3];
	char		m_ObjTeilNr[4];
	BOOL		m_bGeoAngaben;
	CPunktFolge* m_pPoints;
//	CKoordPaar	m_Pkt1;
//	CKoordPaar	m_Pkt2;
//	CKoordPaar	m_Pkt3;

public:
//	BOOL PktGueltig( short );
				CInfo();
				~CInfo();
	short		Lesen( const char* );
	short		LesenALK( const char* );
	BOOL		Gueltig()		{ return m_bGueltig; }
	const char	*ArtInfo()		{ return m_ArtInfo; }
	const char	*KartenTyp()	{ return m_KartenTyp; }
	const char	*ObjArt()		{ return m_ObjArt; }
	CPunktFolge	*Points()		{ return m_pPoints; }
	const char	*Text()			{ return m_Text; }
	const char	*ArtGeo()		{ return m_ArtGeo; }
	const char	*ObjTeilNr()	{ return m_ObjTeilNr; }
	BOOL		GeoAngaben()	{ return m_bGeoAngaben; }
/*
	double		Pkt1Hoch()		{ return m_Pkt1.Hoch(); }
	double		Pkt1Rechts()	{ return m_Pkt1.Rechts(); }
	double		Pkt2Hoch()		{ return m_Pkt2.Hoch(); }
	double		Pkt2Rechts()	{ return m_Pkt2.Rechts(); }
	double		Pkt3Hoch()		{ return m_Pkt3.Hoch(); }
	double		Pkt3Rechts()	{ return m_Pkt3.Rechts(); }
*/
};

  
#endif _LINIE_H_
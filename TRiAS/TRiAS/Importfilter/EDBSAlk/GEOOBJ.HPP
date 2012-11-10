///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			geoobj.hpp
//
//	Stand:			15.11.1994
//	Beschreibung:	Klassendeklarationen für Geoobjekte
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef	_GEOOBJ_HPP
#define _GEOOBJ_HPP

class CObjectClassTRiAS;


class CAttribute : public CObject
{
public:	
					CAttribute( const char* key ) { strKey = key; strValue.Empty(); }
					CAttribute( const char* key, const char* val ) { strKey = key; strValue = val; }
//					~CAttribute();
	CString			strKey;
	CString			strValue;
};

class CPunkt : public CObject
{
private:
	double	m_lHoch;
	double	m_lRechts;
	short	m_sDreh;
public:
			CPunkt()	{ m_lHoch = 0L; m_lRechts = 0L; m_sDreh = 0; }
			CPunkt( double h, double r ) { m_lHoch = h; m_lRechts = r; m_sDreh = 0; }
			CPunkt( double h, double r, short i ) { m_lHoch = h; m_lRechts = r; m_sDreh = i; }
			CPunkt( CPunkt& );
			~CPunkt()	{}
	double	&Hoch()		{ return m_lHoch; }
	double	&Rechts()	{ return m_lRechts; }
	short	&Dreh()		{ return m_sDreh; }
	BOOL	operator == ( CPunkt& );
};


class CPunktPaar : public CObject
{
private:
	CPunkt	m_Punkt1;
	CPunkt	m_Punkt2;

public:
			CPunktPaar()	{}
			CPunktPaar( double h1, double r1, double h2, double r2 );
			CPunktPaar( CPunkt &p1, CPunkt &p2 );
			~CPunktPaar()	{}
	CPunkt	&Punkt1()		{ return m_Punkt1; }
	CPunkt	&Punkt2()		{ return m_Punkt2; }
};


class CPunktFolge : public CObArray
{
public:
			CPunktFolge()	{}
			CPunktFolge( int );
			CPunktFolge( CPunktFolge&, BOOL bReverse = FALSE );
			~CPunktFolge();

	BOOL	AddFolge( CPunktFolge* );
	BOOL	Leer()			{ return ( GetSize() == 0 ); }
	CPunkt	&First()		{ return *(CPunkt*)GetAt(0); }
	CPunkt	&GetPoint(int i){ return *(CPunkt*)GetAt(i); }
	CPunkt	&Last()			{ return *(CPunkt*)GetAt(GetUpperBound()); }
	BOOL	Geschlossen()	{ return (( GetSize() > 2 ) && ( First() == Last())); }
};

class CGeometry : public CObject
{
public:
	short m_iGeometryType;
	short m_iObjectClassEDBS;
};

class CGeometries : public CObArray
{};

class CGeoObj : public CObject
{
	CObjectClassTRiAS	*m_pObjectClassTRiAS;
	CString				m_strUniqueIdent;
	CString				m_strFolie;
	CString				m_strObjektArt;
	CString				m_strFunktionenDerLinien;
	CString				m_strAktualitaet;
	CString				m_strClassX;
	CString				m_strLabel;
	CGeometries			m_Geometries;
	CObArray			m_oaPunktFolgen;
	long				m_lObjNr;
	char				m_cObjTyp;

	// Als vorläufige Lösung zur Fehlerbehebung "Selbstinzidenz" werden in
	// dieser Variablen alle Verknüfungspunkte zur Kontrolle gespeichert.
	CPunktFolge			m_VPunkte;

	int				Zusammenfassen( int idx );

public:
					CGeoObj( const char* UID );
//					CGeoObj( const char* UID,const char* folie,const char* objart );
					~CGeoObj();
	CMapStringToOb		m_Attributes;
	bool			tBI;
	long&			ObjNr()					{ return m_lObjNr; }
	char&			ObjTyp()				{ return m_cObjTyp; }
	CString	&		ObjLabel()				{ return m_strLabel; }
	CString	&		UniqueIdent()			{ return m_strUniqueIdent; }
	CString	&		Folie()					{ return m_strFolie; }
	CString	&		Aktualitaet()			{ return m_strAktualitaet; }
	CString	&		Objektart()				{ return m_strObjektArt; }
	CObjectClassTRiAS*	&ObjectClassTRiAS()	{ return m_pObjectClassTRiAS; }
	CGeoObj			*AddFolge( CPunktFolge* /*, const char*, const char* */);
	CGeometries&	Geometries()			{ return m_Geometries; }
	void			DelFolge( int i )		{ delete (CPunktFolge*)m_oaPunktFolgen[i];
											  m_oaPunktFolgen.SetAt( i, NULL );
											}
	void			ReDefType( const char* );
	void			Pack();

	void			AddAttribute( CString &strKey, CString &strValue );
	CAttribute*		GetAttribute( const char* key );
	int				numAttributes()		{ return m_Attributes.GetCount(); }
	bool			hasAttributes()		{ return !m_Attributes.IsEmpty(); }

	void			SetzPunkt( double, double );
	int				AnzahlLinien()	{ return m_oaPunktFolgen.GetSize(); }
	int				AnzahlPunkte( int i )
						{ return ((CPunktFolge*)m_oaPunktFolgen[i]) -> GetSize(); }
	CPunktFolge		*Punkte( int i )
						{ return (CPunktFolge*)m_oaPunktFolgen[i]; }

//	CMapStringToString	*Merkmale() { return &m_TextMerkmale; }
//	POSITION		GetMMStartPos()
//						{ return m_TextMerkmale.GetStartPosition(); }
//	void			GetMMNext( POSITION &p, CString &k, CString &t )
//						{ m_TextMerkmale.GetNextAssoc( p, k, t ); }
	void			SetClassX( const CString &t ) { m_strClassX = t; }
	CString&		GetClassX( ) { return m_strClassX; }
protected:
	void KonturAufspalten( int idx, int k1, int k2 );
	void TestSelbstinzidenz( int idx );
};


#endif	// _GEOOBJ_HPP

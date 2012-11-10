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

class CPunkt : public CObject
{
private:
	double	m_lHoch;
	double	m_lRechts;

public:
			CPunkt()	{ m_lHoch = 0L; m_lRechts = 0L; }
			CPunkt( double h, double r ) { m_lHoch = h; m_lRechts = r; }
			CPunkt( CPunkt& );
			~CPunkt()	{}
	double	&Hoch()		{ return m_lHoch; }
	double	&Rechts()	{ return m_lRechts; }
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
	CPunkt	&Last()			{ return *(CPunkt*)GetAt(GetUpperBound()); }
	BOOL	Geschlossen()	{ return (( GetSize() > 2 ) && ( First() == Last())); }
};


class CGeoObj : public CObject
{
	CString				m_strUniqueIdent;
	CString				m_strFolie;
	CString				m_strObjektArt;
	CObArray			m_oaPunktFolgen;
	long				m_lObjNr;
	char				m_cObjTyp;
	CMapStringToString	m_TextMerkmale;
	// Als vorläufige Lösung zur Fehlerbehebung "Selbstinzidenz" werden in
	// dieser Variablen alle Verknüfungspunkte zur Kontrolle gespeichert.
	CPunktFolge			m_VPunkte;
	BOOL m_fIsFloeDelta;

	int				Zusammenfassen( int idx );

public:
	CGeoObj()
	{ 
		m_cObjTyp = 'U';
		m_lObjNr = 0L; 
		m_fIsFloeDelta = FALSE;
	}
	CGeoObj (const char* UID, BOOL fIsFloeDelta = FALSE)
	{ 
		m_cObjTyp = 'U';
		m_lObjNr = 0L;
		m_strUniqueIdent = UID; 
		m_fIsFloeDelta = fIsFloeDelta;
	}
	~CGeoObj();
	
	long			&ObjNr()				{ return m_lObjNr; }
	char			&ObjTyp()				{ return m_cObjTyp; }
	CString			&UniqueIdent()			{ return m_strUniqueIdent; }
	CString			&Folie()				{ return m_strFolie; }
	CString			&ObjektArt()			{ return m_strObjektArt; }
	CGeoObj			*AddFolge( CPunktFolge*, const char*, const char* );
	void			DelFolge( int i )		{ delete (CPunktFolge*)m_oaPunktFolgen[i];
											  m_oaPunktFolgen.SetAt( i, NULL );
											}
	void			ReDefType( const char* );
	void			Pack();

	void			AddTextMerkmal( const char*, const char* );
	void			SetzPunkt( double, double );
	BOOL RemoveMerkmal (LPCSTR pcKey) { return m_TextMerkmale.RemoveKey(pcKey); }
	BOOL TextMerkmal (LPCSTR pcKey, CString &rstrWert) { return m_TextMerkmale.Lookup(pcKey, rstrWert); }
	
	int				AnzahlLinien()	{ return m_oaPunktFolgen.GetSize(); }
	int				AnzahlPunkte( int i )
						{ return ((CPunktFolge*)m_oaPunktFolgen[i]) -> GetSize(); }
	CPunktFolge		*Punkte( int i )
						{ return (CPunktFolge*)m_oaPunktFolgen[i]; }

	CMapStringToString	*Merkmale() { return &m_TextMerkmale; }
	POSITION		GetMMStartPos()
						{ return m_TextMerkmale.GetStartPosition(); }
	void			GetMMNext( POSITION &p, CString &k, CString &t )
						{ m_TextMerkmale.GetNextAssoc( p, k, t ); }

	BOOL IsFloeDelta() { return m_fIsFloeDelta; }

protected:
	void KonturAufspalten( int idx, int k1, int k2 );
	void TestSelbstinzidenz( int idx );
};


#endif	// _GEOOBJ_HPP

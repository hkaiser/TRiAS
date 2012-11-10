///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			Regeln.h
//
//	Stand:			24.02.1995
//	Beschreibung:	Verwaltung der Regeln
//	Entwicklung:	24.02.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////


#ifndef _REGELN_H_
#define _REGELN_H_


class CRegel
{
	CStringList			m_listMerkmale;
	CMapStringToString	m_mapWerte;

	void				And( CString&, const char* );
	void				LiesRegel( const char*, char&, const char* );

public:
						CRegel( const char* );
	BOOL				GetIdent( CMapStringToString*, CString& );
	CMapStringToString	*MapWerte()		{ return &m_mapWerte; }
};

class CMapRegeln : public CMapStringToPtr
{
public:
					CMapRegeln()		{}
					~CMapRegeln();
	void			AddEintrag( const char* );

	void Tidy();
};

#endif

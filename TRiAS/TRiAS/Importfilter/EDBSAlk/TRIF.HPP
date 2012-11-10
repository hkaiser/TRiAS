///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trif.h
//
//	Stand:			02.12.1994
//	Beschreibung:	TRIAS-Interface-Objekt
//					- Header-Update
//					- IdentsDB-Update
//					- GeoObjekt-Zugriff
//	Entwicklung:	02.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////


#ifndef _TRIF_H_
#define _TRIF_H_

#include "CXSTRING.H"
#include "GeoObj.HPP"
#include "MetaData.H"

#define KURZTEXT_LEN		 32
#define MAX_LANGTEXT_LEN	128

HRESULT IdFromClassX( const char*, unsigned long*, BOOL );


class CMerkmalsKode : public CObject
{
	unsigned long	m_ulObjectClassTRiAS;
	long			m_MMK;
	CString			m_Kurz;
	CString			m_Lang;
	char			m_Typ;
	bool			m_Gueltig;

public:
					CMerkmalsKode( unsigned long ulObjectClassTRiAS, char, long, const char* = NULL, const char* = NULL );
	char			Typ()		{ return m_Typ; }
	long			Kode()		{ return m_MMK; }
	CString			&KurzText()	{ return m_Kurz; }
	CString			&LangText()	{ return m_Lang; }
	bool			Gueltig()	{ return m_Gueltig; }
	void			WriteBack();
	bool			Read();
};


class CTriasObjekt : public CObject
{
	CGeoObj*			m_pGO;
	long				m_lONr;
	long				m_lIdent;
	short				m_iObjTyp;
	long				m_lCnt;
	short				m_iKCnt;
	void				*m_pdblX;
	void				*m_pdblY;
	long				*m_plCnt;
	CxString				m_strUniqueIdent;
//	CString				m_strTextMerkmal;
//	CMapStringToString	m_Merkmale;
//	CAttributes			m_Attributes;
	bool				m_bNeu;

public:
					CTriasObjekt( CGeoObj* pGO);
					~CTriasObjekt();
	long			&ONr()				{ return m_lONr; }
	long			&Ident()			{ return m_lIdent; }
	short			&ObjTyp()			{ return m_iObjTyp; }
	long			&AnzahlPunkte()		{ return m_lCnt; }
	short			&AnzahlKonturen()	{ return m_iKCnt; }
	void			*XKoord()			{ return m_pdblX; }
	void			XKoord( void* p )	{ m_pdblX = p; }
	void			*YKoord()			{ return m_pdblY; }
	void			YKoord( void* p )	{ m_pdblY = p; }
	long			*KonturPunkte()		{ return m_plCnt; }
	void			KonturPunkte( long* p )
										{ m_plCnt = p; }
	CxString			&UniqueIdent()		{ return m_strUniqueIdent; }

/*	void			AddAttribute( const char* key, const char* text, bool add = true );
	CAttribute*		GetAttribute( const char* key )
										{ return m_Attributes.GetAttribute( key ); }
	int				numAttributes()		{ return m_Attributes.GetCount(); }
	bool			hasAttributes()		{ return !m_Attributes.IsEmpty(); }
*/	
	bool &			Neu()				{ return m_bNeu; }
	bool			ReadyForRead();
	bool			ReadyForWrite();

	bool			Read();
	bool			WriteUniqueIdent();
	void			WriteAttribute( CString strAttribute, CString strValue );
	bool			WriteAttributes();
	bool			WriteErrorLog();
	bool			WriteBack();
};

class CTriasInterface
{	// Header - Daten
	long				m_lUniqueIdent;

	// Identsdb
//	CStringList			m_slIdents;
	CStringList			m_slMerkmale;
//	CStringList			m_slEDBS_ID;
//	CStringList			m_slBedingungen;

public:
	bool				m_tUpdateHeader;
	long				m_lOffsetX;
	long				m_lOffsetY;
	double				m_dKoeff11;
	double				m_dKoeff12;
	double				m_dKoeff21;
	double				m_dKoeff22;
	void EnableCrtMemDbgFlag( BOOL );
					CTriasInterface();
					~CTriasInterface();
	void			UpdateHeaders( void );
	void			ConfigCoord( HPROJECT hPr  );
	bool			ProjectOpen();
	long			&OffsetX()				{ return m_lOffsetX; }
	long			&OffsetY()				{ return m_lOffsetY; }
	long			&UniqueIdent()			{ return m_lUniqueIdent; }
//	long			TextMMK( const char* );
	double			&Koeff11()				{ return m_dKoeff11; }
	double			&Koeff12()				{ return m_dKoeff12; }
	double			&Koeff21()				{ return m_dKoeff21; }
	double			&Koeff22()				{ return m_dKoeff22; }
	CStringList		&MerkmalList()			{ return m_slMerkmale; }
//	CStringList		&BedingungList()		{ return m_slBedingungen; }
//	bool			Get_A_Rule( const char *k, CString &s );
	bool			NeuesMerkmal( const char* );
	void			Flush();
	void			DeleteObjekt( long );
	CString			strImportFullFileName;
	CString			strImportFileName;
	CString			strImportFullLogFileName;
	CString			strImportFullErrorLogFileName;

private:
	DWORD m_dwDbgFlag;
	CString			GetHeaderEntry( const char* );
	void			SetHeaderEntry( const char*, const char* );
	unsigned long	BildeIdent( const char*, CMapStringToString* );
};

extern CTriasInterface*	g_pTriasInterface;

#endif // _TRIF_H_

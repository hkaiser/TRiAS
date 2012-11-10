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

#define KURZTEXT_LEN		 32
#define MAX_LANGTEXT_LEN	128

HRESULT IdFromClassX( const char*, unsigned long*, BOOL );

class CMerkmalsKode : public CObject
{
	INT_PTR m_MMK;
	INT_PTR m_lMappedMCode;
	CString			m_Kurz;
	CString			m_Lang;
	CString m_strOKS;
	char			m_Typ;
	bool			m_Gueltig;
	bool m_fWritten;

public:
	CMerkmalsKode(char typ, long lCode, const char * pcKText = NULL, const char *pcLText = NULL, LPCSTR pcOKS = NULL);

	char			Typ()		{ return m_Typ; }
	long			Kode()		{ _ASSERTE('i' == m_Typ || 0 != m_lMappedMCode); return ('i' == m_Typ) ? m_MMK : m_lMappedMCode; }
	CString			&KurzText()	{ return m_Kurz; }
	CString			&LangText()	{ return m_Lang; }
	CString &OKS() { return m_strOKS; }

	bool			Gueltig()	{ return m_Gueltig; }
	bool Written() { return m_fWritten; }
	
	void			WriteBack();
	BOOL			Read();
};

class CKodeTabelle : public CObArray
{
	char			m_Typ;

public:
					CKodeTabelle()		{ m_Typ = '\0'; }
					~CKodeTabelle();
	void			SetTyp( char t )	{ if ( m_Typ == '\0' ) m_Typ = t; }
	long			FindeKode( const char* );
	BOOL			Add( long, const char*, const char* = NULL );
	BOOL			AddMMK( const char*, BOOL hexBase, LPCSTR pcOKS = NULL);
	BOOL			Mod( long, const char*, const char* = NULL );
	BOOL			KodeExist( long );

	void Tidy();
};

class CEDBSidList : public CObArray
{
public:
	CEDBSidList() {}
	~CEDBSidList();

	void AddID(const char *, BOOL);
	long GetKode(const char *);

// aus Punkten Text erzeugen
	bool MakeText (LPCSTR def);
	CString GetTextAttr(LPCSTR def);

	void Tidy();
};

class CMapAliase : 
	public CMapStringToString
{
public:
	CMapAliase() {}
	~CMapAliase();

	void AddEintrag(const char *);
	void AddRegelnA (CString strKey);
	void AddRegelnC (CString strKey);

	void Tidy();
};

// Beschreibung einer Objektklasse
class CTriasIdent : public CObject
{
	unsigned long	m_lKode;		// Ident
	CString			m_strSchl;		// OKS
	CString			m_strKurz;		// Kurztext
	CString			m_strLang;		// Langtext

public:
	CTriasIdent(const char *, BOOL);

	unsigned long &Kode()			
	{ 
		if (0 == m_lKode) 
			m_lKode = EnsureIdent(m_strSchl); 
		return m_lKode; 
	}
	CString			&Kurz()			{ return m_strKurz; }
	CString			&Lang()			{ return m_strLang; }
	CString			&OKS()			{ return m_strSchl; }

	static unsigned long EnsureIdent (CString &rstrOKS, bool fCreate = false, bool fHexBase = true);
	static CString CTriasIdent::GetOKS (unsigned long lIdent);
};

class CEDBSIdent : public CObject
{
private:
	unsigned long	m_lTKode;		// TRIAS - Kode
	long			m_lEKode;		// EDBS - Kode
	CString			m_strEKode;		// EDBS - Kode (Maske)
	CString			m_strEBed;		// EDBS - Kode (Bedingung)
	bool m_fMakeText;			// aus Punkten Text machen
	CString m_strTextAttr;		// diesen Wert im Text anzeigen

	bool m_fEindeutig;
	CString m_strOKS;

public:
	CEDBSIdent(const char *, BOOL hexbase, BOOL fMakeText, LPCSTR pcTextAttr);
	~CEDBSIdent() {}
					
	long TRIAS_Kode()
	{
		if (0 == m_lTKode && m_fEindeutig) {
			_ASSERTE(!m_strOKS.IsEmpty());
			m_lTKode = CTriasIdent::EnsureIdent(m_strOKS, true, (16 == DEX_GetIdBase()) ? true : false);
		}
		return m_lTKode; 
	}
	long EDBS_Kode() { return m_lEKode; }

	bool MakeText() { return m_fMakeText; }
	CString GetTextAttr() { _ASSERTE(m_fMakeText); return m_strTextAttr; }
};

// Liste aller Objektklassen
class CTriasIdList : public CObArray
{
public:
	CTriasIdList()	{}
	~CTriasIdList();

	void AddID(const char*, BOOL hexbase);

	CTriasIdent *GetId(unsigned long ulIdent);
	CTriasIdent	*GetId(CString &rstrKurz);

	void Tidy();
};

class CTriasObjekt : public CObject
{
private:
	long				m_lONr;
	long				m_lIdent;
	short				m_iObjTyp;
	long				m_lCnt;
	short				m_iKCnt;
	void				*m_pdblX;
	void				*m_pdblY;
	long				*m_plCnt;
	CString				m_strUniqueIdent;
//	CString				m_strTextMerkmal;
	CMapStringToString	m_Merkmale;
	CString				m_strTextObjekt;
	BOOL				m_bNeu;

public:
					CTriasObjekt();
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
	void			KonturPunkte( long* p ) { m_plCnt = p; }
	CString			&UniqueIdent()		{ return m_strUniqueIdent; }
	CString GetOKS();
	
	void			AddTextMerkmal( const char*, const char*, BOOL = TRUE );
	BOOL			TextMerkmal( const char* k, CString& t ) { return m_Merkmale.Lookup( k, t ); }
	int				TextMerkmalAnzahl()	{ return m_Merkmale.GetCount(); }
	BOOL			TextMerkmalExist()	{ return !m_Merkmale.IsEmpty(); }
	POSITION		FirstTextMerkmal()	{ return m_Merkmale.GetStartPosition(); }
	void			NextTextMerkmal( POSITION& p, CString& k, CString& t ) { m_Merkmale.GetNextAssoc( p, k, t ); }
	BOOL RemoveMerkmal (LPCSTR pcKey);
	
	CString			&TextObjekt()		{ return m_strTextObjekt; }
	BOOL			&Neu()				{ return m_bNeu; }
	BOOL			ReadyForRead();
	BOOL			ReadyForWrite();

	BOOL			Read();
	BOOL			WriteBack();
};

#if defined(_USE_B_REGELN)
#include "regeln.hpp"
#endif // defined(_USE_B_REGELN)

class CTriasInterface		// Header - Daten
{	
private:
	long				m_lOffsetX;
	long				m_lOffsetY;
	double				m_dKoeff11;
	double				m_dKoeff12;
	double				m_dKoeff21;
	double				m_dKoeff22;
	long				m_lUniqueIdent;
	BOOL				m_bUndefinedObj;
	BOOL				m_bHexIdents;
	BOOL				m_bHexMKodes;
	CString m_strIniFileName;
	CString m_strActFileName;

// Identsdb
	CKodeTabelle		m_tabIdent;
	CKodeTabelle		m_tabMMK;
	CStringList			m_slMerkmale;
	CEDBSidList			m_listEdbsId;
	CTriasIdList		m_listTriasId;		// sämtliche Objektklasse aus EDBS.INI
	CMapAliase			m_Aliase;
#if defined(_USE_B_REGELN)
	CMapRegeln			m_Regeln;
#endif // defined(_USE_B_REGELN)
	
	HPROJECT m_hPr;							// Datenquelle, wo alles rein importiert wird

public:
	void EnableCrtMemDbgFlag( BOOL );

		CTriasInterface();
		~CTriasInterface();
	
	BOOL FInit();
	void Tidy();

	HPROJECT hPr() { _ASSERTE(NULL != m_hPr); return m_hPr; }

	BOOL			ProjectOpen();
	long			&OffsetX()				{ return m_lOffsetX; }
	long			&OffsetY()				{ return m_lOffsetY; }
	long			&UniqueIdent()			{ return m_lUniqueIdent; }

	long			TextMMK( const char* );
	BOOL AddMMK(const char* kurz, LPCSTR pcOKS = NULL);

	double			&Koeff11()				{ return m_dKoeff11; }
	double			&Koeff12()				{ return m_dKoeff12; }
	double			&Koeff21()				{ return m_dKoeff21; }
	double			&Koeff22()				{ return m_dKoeff22; }
	void			UpdateHeader();
//	CStringList		&IdentList()			{ return m_slIdents; }
	CStringList		&MerkmalList()			{ return m_slMerkmale; }
//	CStringList		&EDBSidList()			{ return m_slEDBS_ID; }
//	CStringList		&BedingungList()		{ return m_slBedingungen; }
	unsigned long	GetIdent(const char *pcFolie, const char *pcObjArt, CMapStringToString *pAttribs);

	BOOL GetImportUnknownData() { return m_bUndefinedObj; }
	BOOL GetAlias(const char *k, const char *p2ndKey, CString &s) 
	{
	CString strKey (k);

		strKey += p2ndKey;
		if (!m_Aliase.Lookup(strKey, s)) {
		// nochmal in der allgemeinen Tabelle versuchen
			strKey = "*";
			strKey += p2ndKey;
			return m_Aliase.Lookup(strKey, s);
		}
		return TRUE;
	}
	BOOL DeleteAlias (LPCSTR pcKey) { return m_Aliase.RemoveKey(pcKey); }
	
	BOOL			NeuesMerkmal( const char* );
	void			Flush();
	void			DeleteObjekt( long );

	bool MakeText (LPCSTR def) { return m_listEdbsId.MakeText(def); }
	CString GetTextAttr(LPCSTR def) { return m_listEdbsId.GetTextAttr(def); }

	CString GetActFileName() { return m_strActFileName; }
	void SetActFileName(LPCSTR pcFileName) { _ASSERTE(NULL != pcFileName); m_strActFileName = GetFileName(pcFileName); }

	LPCSTR GetIniFileName() { return m_strIniFileName; }

	HOBJECT FindObject (const char *pObjNr);
		
protected:
	static CString GetFileName(LPCSTR pcFullpath);

private:
	DWORD m_dwDbgFlag;
	unsigned long	BildeIdent( const char*, CMapStringToString* );
};

#endif // _TRIF_H_

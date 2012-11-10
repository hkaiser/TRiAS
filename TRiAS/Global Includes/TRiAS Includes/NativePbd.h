///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CNativePbd.h | Klassendeklaration für Pbd-Zugriff

#if !defined(_CNATIVEPBD_H__7A24AC73_96F4_11D1_BA0E_080036D63803__INCLUDED_)
#define _CNATIVEPBD_H__7A24AC73_96F4_11D1_BA0E_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <idtdb.h>			// Für Dateinummern

namespace trias_nativepbd {

const int TEXTLEN_001 = 16;	// KurzTextlänge
const int TEXTLEN = 32;	

enum PBDTyp {
	PBD_IDENT = 'i',		// PBD-Satztypen
	PBD_MERKMAL = 'm',
	PBD_MWERT = 'w',
	PBD_RELATION = 'r',
	PBD_SYMBOL = 's',
	PBD_VISUAL = 'u',
};

class _TRIAS01_ENTRY CNativePbd
{
public:
// StatusWerte
	enum PBDStatus { 
		PBD_Unmodified, 
		PBD_Modified, 
		PBD_Deleted, 
		PBD_Invalid, 
	};

protected:
	long m_lCode;			// Identifikator
	os_string m_strKurzText;	// KurzText
	os_string m_strLangText;	// LangText
	long m_dbaSatz;			// SatzNr
	PBDTyp m_rgTyp;			// DatenTyp
	PBDStatus m_rgStatus;	// Status
	HPROJECT m_hPr;			// zugehörige PBD-DatenBasis 
	bool m_fTemp;

protected:
	static HRESULT CALLBACK FindEntryCallback (INT_PTR lCode, UINT_PTR dwData);
	static HRESULT CALLBACK FindEqualEntriesCallback (INT_PTR lCode, UINT_PTR dwData);
	static HRESULT CALLBACK IsUniqueNameCallback (INT_PTR lCode, UINT_PTR dwData);

	HRESULT PutKurzText();
	HRESULT PutLangText(int iTyp);

	virtual HRESULT mdelete (long lSatz = 0) = 0; //{ return E_NOTIMPL; }
	virtual HRESULT mfind (long lCode, long *pSatz) = 0; //{ return E_NOTIMPL; }
	virtual HRESULT mgetkt (char *pText) = 0; //{ return E_NOTIMPL; }
	virtual HRESULT mgetl (long *plLen) = 0; // { return E_NOTIMPL; }
	virtual HRESULT mgettx (char *pText) = 0; // { return E_NOTIMPL; }
	virtual HRESULT mputkt (const char *pcText) = 0; // { return E_NOTIMPL; }
	virtual HRESULT mputtx (const char *pcText) = 0; // { return E_NOTIMPL; }

	HRESULT mgetktall (char *pText, int iFileNo);
	HRESULT mputktall (const char *pcText, int iFileNo);
	HRESULT mgetlall (long *pLen, int iFileNo, int iFileNoNext);
	HRESULT mgettxall (char *pText, int iFileNo, int iFileNoNext);
	HRESULT mputtxall (const char *pcText, int iFileNo, int iFileNoNext);

	HRESULT FreeText (int FileNo, long lRecNo);

	HRESULT EnsureUniqueName (LPCSTR pcName);
	BOOL IsUniqueName (LPCSTR pcName);

public:
// Konstruktoren
		CNativePbd (HPROJECT hPr, PBDTyp Typ);
		CNativePbd (HPROJECT hPr, PBDTyp Typ, long lCode);

	HRESULT FInit (LPCSTR pcKText = NULL, BOOL fIssueError = TRUE, BOOL fCorrectName = FALSE);

// Memberfunktionen
	LPCSTR GetLangText (LPSTR pBuffer = NULL, int iLen = 0);

	long GetCode (void) { return m_lCode; }
	LPCSTR GetKurzText (void) { return m_strKurzText.c_str(); }
	LPCSTR MakeDefaultName (UINT uiResID, LPSTR pBuffer, int iLen);
	PBDTyp GetDataType (void) { return m_rgTyp; }
	PBDStatus & Status (void) { return m_rgStatus; }
	BOOL isTemp (void) { return m_fTemp ? TRUE : FALSE; }
	long Addr (void) { return m_dbaSatz; }

	HRESULT SetKurzText (LPCSTR);
	HRESULT SetLangText (LPCSTR);

	HPROJECT PBDHandle (void) { return m_hPr; }

	BOOL operator!() { return (m_rgStatus == PBD_Invalid) ? TRUE : FALSE; }

	static HRESULT EnumPBDData (HPROJECT hPr, long pbdTyp, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData);
	static HRESULT FindEntry (HPROJECT hPr, long pbdTyp, LPCSTR pcName, long *plCode);
	static HRESULT EnumEqualEntries (HPROJECT hPr, long pbdTyp, LPCSTR pcName, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData);

public:
// Destruktor
	virtual ~CNativePbd (void);
	virtual HRESULT SaveInPBD (void);
	virtual HRESULT DeleteInPBD (void);
};


///////////////////////////////////////////////////////////////////////////////
// Identifikatorinformation in Pbd
class _TRIAS01_ENTRY CNativePbdIdent : 
	public CNativePbd 
{
private:
	bool m_fSystem;			// SystemIdent
	bool m_fReadOnly;		// ReadOnly-Ident

protected:
	HRESULT mdelete (long lSatz = 0);
	HRESULT mfind (long lCode, long *pSatz);
	HRESULT mgetkt (char *pText) { return mgetktall (pText, MID); }
	HRESULT mgetl (long *plLen) { return mgetlall (plLen, MID, MIF); }
	HRESULT mgettx (char *pText) { return mgettxall (pText, MID, MIF); }
	HRESULT mputkt (const char *pcText) { return mputktall (pcText, MID); }
	HRESULT mputtx (const char *pcText) { return mputtxall (pcText, MID, MIF); }

	HRESULT mputki (long iTyp, long *plRecNo);
	HRESULT mgetki (long *plIdent, long *piTyp = NULL);

public:
// Konstruktor
	CNativePbdIdent (HPROJECT hPr, BOOL fIssueError = TRUE, BOOL fCorrectName = FALSE);
	CNativePbdIdent (HPROJECT hPr, long lCode, LPCSTR pcKText = NULL, BOOL fIssueError = TRUE, BOOL fCorrectName = FALSE);

// Destruktor
	~CNativePbdIdent (void);

// MerkmalsTypen
	enum PBDIDENTTYPE {
		PBDIDENTTYPE_System = 0x10000,		// IPSystemFeatures
		PBDIDENTTYPE_ReadOnly = 0x40000,	// IPReadOnlyFeatures
		PBDIDENTTYPE_PbdOnly = 0x100000,	// IPPbdOnly
		PBDIDENTTYPE_Mask = 0xFFFF0000,		// IPPbdMask
	};

	BOOL isSystem (void) { return m_fSystem; }
	void SetSystem (BOOL fSystem) { m_fSystem = fSystem ? true : false; m_rgStatus = PBD_Modified; }

	BOOL isReadOnly (void) { return m_fReadOnly ? true : false; }
	void SetReadOnly (BOOL fReadOnly) { m_fReadOnly = fReadOnly ? true : false; m_rgStatus = PBD_Modified; }

	DWORD GetFullType();

	LPCSTR MakeDefaultName (LPSTR pBuffer = NULL, int iLen = 0);

	HRESULT SaveInPBD (void);
	HRESULT DeleteInPBD (void);

	static HRESULT EnumPBDData (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumPBDData(hPr, PBD_IDENT, pFcn, dwData); }
	static HRESULT FindIdent (HPROJECT hPr, LPCSTR pcName, long *plIdent)
		{ return CNativePbd::FindEntry (hPr, PBD_IDENT, pcName, plIdent); }
	static HRESULT EnumEqualEntries (HPROJECT hPr, LPCSTR pcName, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumEqualEntries (hPr, PBD_IDENT, pcName, pFcn, dwData); }
};

///////////////////////////////////////////////////////////////////////////////
// Merkmalsklassen 

#if !defined(PBDMERKMAL_SYSTEMFLAG)
#define PBDMERKMAL_SYSTEMFLAG	0x80		// Merkmal ist SystemMerkmal
#endif

class _TRIAS01_ENTRY CNativePbdMerkmal 
	: public CNativePbd 
{
private:
	int m_iMTyp;			// MerkmalsTyp
	bool m_fSystem;			// SystemMerkmal
	bool m_fReadOnly;		// ReadOnly-Merkmal
	INT_PTR m_lIdent;		// gehört zu dieser Objektklasse

protected:
	HRESULT mdelete (long lSatz = 0);
	HRESULT mfind (long lCode, long *pSatz);
	HRESULT mgetkt (char *pText) { return mgetktall (pText, MMK); }
	HRESULT mgetl (long *plLen) { return mgetlall (plLen, MMK, MKF); }
	HRESULT mgettx (char *pText) { return mgettxall (pText, MMK, MKF); }
	HRESULT mputkt (const char *pcText) { return mputktall (pcText, MMK); }
	HRESULT mputtx (const char *pcText) { return mputtxall (pcText, MMK, MKF); }

	HRESULT mputkm (short MTyp, long WF, long *von, long *bis, long *plRecNo);
	HRESULT mgetkm (long *pMCode = NULL, short *pMTyp = NULL, INT_PTR *plIdent = NULL, long *pWF = NULL, 
					long *pVon = NULL, long *pBis = NULL, long *pNext = NULL);

public:
// Konstruktor
	CNativePbdMerkmal (HPROJECT hPr, BOOL fIssueError = TRUE, BOOL fCorrectName = FALSE);
	CNativePbdMerkmal (HPROJECT hPr, long lCode, LPCSTR = NULL, BOOL fIssueError = TRUE, BOOL fCorrectName = FALSE);

// MerkmalsTypen
	enum PBDFEATURETYPE {
		PBDFEATURETYPE_Object = 'a',		// MPObjectFeature (s. xtension.h)
		PBDFEATURETYPE_View = 'b',			// MPViewFeature
		PBDFEATURETYPE_Ident = 'c',			// MPIdentFeature
		PBDFEATURETYPE_Unknown = 'u',		// MPUnknownFeature
		PBDFEATURETYPE_TypeMask = 0xff,
		PBDFEATURETYPE_System = 0x100,		// MPSystemFeatures
		PBDFEATURETYPE_ReadOnly = 0x400,	// MPReadOnlyFeatures
		PBDFEATURETYPE_TextFeature = 0x800,	// MPTextFeature
		PBDFEATURETYPE_PbdOnly = 0x1000,	// MPPbdOnly
	};

// Memberfunktionen
	int GetMLen (void);

	int isA (void) { return m_iMTyp; }
	void SetTyp (int newTyp) { m_iMTyp = newTyp; m_rgStatus = PBD_Modified; }

	BOOL isSystem (void) { return m_fSystem; }
	void SetSystem (BOOL fSystem) { m_fSystem = fSystem ? true : false; m_rgStatus = PBD_Modified; }

	BOOL isReadOnly (void) { return m_fReadOnly ? true : false; }
	void SetReadOnly (BOOL fReadOnly) { m_fReadOnly = fReadOnly ? true : false; m_rgStatus = PBD_Modified; }

	DWORD GetFullType();
	LPCSTR MakeDefaultName (LPSTR pBuffer = NULL, int iLen = 0);

	INT_PTR GetIdent() { return m_lIdent; }
	void SetIdent (INT_PTR lIdent) { m_lIdent = lIdent; m_rgStatus = PBD_Modified; }

	virtual int MTyp (void) { return toupper(PBDFEATURETYPE_Unknown); }		// liefert Merkmalstyp
	virtual LPCSTR GetMerkmalsText (void) { return NULL; }

// DatenBankArbeit
	HRESULT SaveInPBD (void);
	HRESULT DeleteInPBD (void);

	static HRESULT EnumPBDData (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumPBDData(hPr, PBD_MERKMAL, pFcn, dwData); }
	static HRESULT FindMerkmal (HPROJECT hPr, LPCSTR pcName, long *plMCode)
		{ return CNativePbd::FindEntry (hPr, PBD_MERKMAL, pcName, plMCode); }
	static HRESULT EnumEqualEntries (HPROJECT hPr, LPCSTR pcName, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumEqualEntries (hPr, PBD_MERKMAL, pcName, pFcn, dwData); }

// Destruktor
	~CNativePbdMerkmal (void) {}
};

///////////////////////////////////////////////////////////////////////////////
// Ein GeoDB-Objekt kann mehrere verschiedene Einzel-Merkmale besitzen 
class _TRIAS01_ENTRY CNativePbdTextMerkmal : 
	CNativePbdMerkmal 
{
private:
	os_string m_strText;		// Merkmalstext

public:
// Konstruktor
	CNativePbdTextMerkmal (HPROJECT hPr, long lCode, LPCSTR pcMText = NULL);
	CNativePbdTextMerkmal (CNativePbdTextMerkmal &);
		
// Memberfunktionen
	LPCSTR GetMerkmalsText (void);
	BOOL hasTextMerkmal (void);
	
	int MTyp (void) { return isA(); }		// MerkmalsTyp

// Destruktor
	~CNativePbdTextMerkmal (void);
};

///////////////////////////////////////////////////////////////////////////////
// Relationsbeschreibungen in Pbd
class CNativePbdRelation : 
	public CNativePbd 
{
private:
	short m_iRelTyp;

protected:
	HRESULT mdelete (long lSatz = 0);
	HRESULT mfind (long lCode, long *pSatz);
	HRESULT mgetkt (char *pText) { return mgetktall (pText, MRL); }
	HRESULT mgetl (long *plLen) { return mgetlall (plLen, MRL, MRF); }
	HRESULT mgettx (char *pText) { return mgettxall (pText, MRL, MRF); }
	HRESULT mputkt (const char *pcText) { return mputktall (pcText, MRL); }
	HRESULT mputtx (const char *pcText) { return mputtxall (pcText, MRL, MRF); }

	HRESULT mgetkr (long *pRCode = NULL, short *pRTyp = NULL);
	HRESULT mputkr (short reltyp, long *plRecNo);

public:
// Konstruktor
	CNativePbdRelation (HPROJECT hPr, BOOL fIssueError = TRUE, BOOL fCorrectName = TRUE);
	CNativePbdRelation (HPROJECT hPr, long lCode, LPCSTR = NULL, BOOL fIssueError = TRUE, BOOL fCorrectName = TRUE);

// Member
	LPCSTR MakeDefaultName (LPSTR pBuffer = NULL, int iLen = 0);

	HRESULT SaveInPBD (void);
	HRESULT DeleteInPBD (void);

	static HRESULT EnumPBDData (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumPBDData(hPr, PBD_RELATION, pFcn, dwData); }
	static HRESULT FindRelation (HPROJECT hPr, LPCSTR pcName, long *plRCode)
		{ return CNativePbd::FindEntry (hPr, PBD_RELATION, pcName, plRCode); }
	static HRESULT EnumEqualEntries (HPROJECT hPr, LPCSTR pcName, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
		{ return CNativePbd::EnumEqualEntries (hPr, PBD_RELATION, pcName, pFcn, dwData); }

	int FRTyp (void) { return m_iRelTyp; }
	void SetTyp (int newT) { m_iRelTyp = newT; }

// Destruktor
		~CNativePbdRelation (void) {}
};

} // namespace trias_nativepbd

#endif // !defined(_CNATIVEPBD_H__7A24AC73_96F4_11D1_BA0E_080036D63803__INCLUDED_)

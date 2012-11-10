// @doc
// @module DBUTIL.H | Allgemeine Makrodefinitionen et.al.

#if !defined(_DBUTIL_H__978C1EC3_2F3C_11d1_969F_00A024D6F582__INCLUDED_)
#define _DBUTIL_H__978C1EC3_2F3C_11d1_969F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <TRiASDBDispIds.h>
#include <Com/BstrHelpers.h>

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTable in ein CString
void __cdecl FormatMessage (CString &rStr, UINT uiError, ...);

// MessageBox anzeigen, Text ist formatierbar 
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...);
int __cdecl VMessageBox (LPCSTR pcCaption, UINT uiType, UINT uiText, ...);
os_string __cdecl FakeTRiASName (UINT resID, ...);
os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
// Größe eines Arrays
#define _countof(x) (sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// Zerlegen eines Objektes/Arrays
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!x) {} else { delete(x); x = NULL; }		//lint --e774
#endif // DELETE_OBJ

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(!x) {} else { delete[](x); x = NULL; }	//lint --e774
#endif // DELETE_VEC

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) "): " desc)

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Bytes für ein BSTR in einem Stream
inline 
ULONG LenForStream (const CComBSTR &bstr)
{
	return (bstr.m_str ? ::SysStringByteLen(bstr.m_str)+sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

///////////////////////////////////////////////////////////////////////////////
// Daten in einen Stream Schreiben/von dort lesen
template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
	return pIStm -> Read (&riVal, sizeof(T), NULL);
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

// backwards compatibility functions
inline HRESULT LoadLong (IStream *pIStm, long &riVal) { return LoadData (pIStm, riVal); }
inline HRESULT SaveLong (IStream *pIStm, long iVal) { return SaveData (pIStm, iVal); }

///////////////////////////////////////////////////////////////////////////////
// sonstige globale Funktionsdeklarationen
HRESULT GetSubStorage (IStorage *pIRootStg, LPCOLESTR pcoleName, REFCLSID rClsId, IStorage **ppIStg, bool fCreate = false);
HRESULT GetSubStream (IStorage *pIRootStg, LPCOLESTR pcoleName, IStream **ppIStm, bool fCreate = false);

// WindowsVersion
bool WINAPI IsWin31 (void);
bool WINAPI IsWin40 (void);
bool WINAPI IsWin41 (void);
bool WINAPI IsWin50 (void);
bool WINAPI IsWin32s (void);
bool WINAPI IsWinNT (void);

///////////////////////////////////////////////////////////////////////////////
// Finden eines besonderen Parents in der Objekthierarchie über einem gegebenen
// Objekt
template<class T>
inline HRESULT FindSpecificParent (T ParentIn, REFIID riid, void **ppIObj)
{
__Interface<IDispatch> Parent(ParentIn);

	while (Parent.IsValid()) {
		if (SUCCEEDED(Parent -> QueryInterface(riid, ppIObj)))
			return S_OK;			// gesuchtes Objekt gefunden

	// eine Etage weiter hoch
	__Interface<ITRiASBase> ParT;

		if (FAILED(Parent -> QueryInterface (ParT.ppi())))
			return E_UNEXPECTED;	// snh

		RETURN_FAILED_HRESULT(ParT -> get_Parent (Parent.ppi()));
	}
	return E_UNEXPECTED;
}

template<class T1, class T2>
inline HRESULT FindSpecificParent (T1 ParentIn, T2 **ppIObj)
{
	return FindSpecificParent (ParentIn, __uuidof(T2), reinterpret_cast<void **>(ppIObj));
}

HRESULT RetrieveDBHandle (IUnknown *pIObj, HPROJECT *phPr);

// Radix-Konvertierung
long Hex2Dec (long lHex);
long Dec2Hex (long lDec);

// OBJECTTYPE zu TRiAS-Objektbits konvertieren
typedef enum _tagOBJECTTYPE OBJECTTYPE;		/* !e761 */ // forward decl only 
DWORD OBJECTTYPEToBits (OBJECTTYPE rgType);
OBJECTTYPE BitsToOBJECTTYPE (DWORD dwTypes);

// FileHandling
bool TestFileRO (LPCSTR pcName, BOOL &rRO);

// stellt fest, ob das angegebene Verzeichnis die Besonderheiten eines Novell-Verzeichnisses 
// besitzt (sharingcontrol nicht selbst machen)
// vorerst wird dieser Test an Hand der Existenz einer Datei 'TRiAS.Dir' erledigt
bool IsNovellDrive (BSTR bstrName);

///////////////////////////////////////////////////////////////////////////////
// nützliche Datendefinitionen
typedef enum tagSTGMODE {
	STGMODE_Normal = 0x01,
	STGMODE_NoScribble = 0x02,

	STGMODE_HandsOff = 0x10,
	STGMODE_HandsOffAfterNormal = 0x14,
	STGMODE_HandsOffAfterSave = 0x18,

	STGMODE_Unknown = 0,
} STGMODE;

/////////////////////////////////////////////////////////////////////////////
// Feststellen, ob String ein OKS ist und wenn ja selbigen liefern
bool StringIsOKS (BSTR bstrToStrip, BSTR *pStripped = NULL, BSTR *pbstrAppendix = NULL);

///////////////////////////////////////////////////////////////////////////////
// Supportfunktionen für RechercheFunktionalität
int MainModeFromSearchCommand (BSTR bstrCommand);
int ModeFromSearchCommand (BSTR bstrCommand);
HRESULT RetrieveSearchParams (BSTR bstrCommand, SAFEARRAY *pParams, BSTR *pbstrPattern, int *piMode = NULL);

///////////////////////////////////////////////////////////////////////////////
// eine beliebige Resource laden
BYTE *ReadResource (int iResID, DWORD &dwResSize, HINSTANCE hInstance = NULL);

///////////////////////////////////////////////////////////////////////////////
// Bits in einem Objekttype (OBJECTTYPE) zählen
extern const int __declspec(selectany) g_iBitCount[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, };
inline int BitCount(int iBits) 
{
	_ASSERTE(0 <= iBits && iBits < 16);
	return g_iBitCount[iBits & 0xF];
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen für die Verwaltung von bitweisen enum's
template<class T>
inline 
T GetType (T rVal, DWORD rgToGet) 
{ 
	return (T)(rVal & rgToGet);
}

template<class T>
inline 
void SetType (T &rVal, DWORD rgToSet) 
{ 
	rVal = (T)(rVal | rgToSet);
}

template<class T>
inline 
void ClearType (T &rVal, DWORD rgToClear) 
{ 
	rVal = (T)(rVal & ~rgToClear); 
}

template<class T>
inline 
bool HasType (T rgVal, DWORD rgToTest) 
{ 
	return (rgVal & rgToTest) ? true : false; 
}

///////////////////////////////////////////////////////////////////////////////
// helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != *pbstr) {
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT *CLEARED (CComVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();			//lint !e534, !e613
	return pv;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob ein bestimmtes Interface unterstützt wird
template<class T>
BOOL SupportsInterface (IUnknown *pIUnk, T *)
{
__Interface<T> Obj;

	return SUCCEEDED(pIUnk -> QueryInterface (Obj.ppi()));
}

///////////////////////////////////////////////////////////////////////////////
// ItemMoniker für aktuelle process erzeugen
inline HRESULT CreatePIDMoniker (IMoniker **ppIMk)
{
__Interface<IMoniker> mkPID;
wchar_t cbPID[32];

	_ultow (GetCurrentProcessId(), cbPID, 16);
	RETURN_FAILED_HRESULT(CreateItemMoniker (L"!", cbPID, ppIMk));
	return S_OK;
}

#endif // !defined(_DBUTIL_H__978C1EC3_2F3C_11d1_969F_00A024D6F582__INCLUDED_)

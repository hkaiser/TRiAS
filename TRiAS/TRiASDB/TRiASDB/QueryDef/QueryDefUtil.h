// @doc 
// @module QueryDefUtil.h | Nützliche Makros etc...

#if !defined(_QUERYDEFUTIL_H__1BF01AF6_33CF_11D3_94FA_0080C786297B__INCLUDED_)
#define _QUERYDEFUTIL_H__1BF01AF6_33CF_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTable in ein CString
void __cdecl FormatMessage (CString &rStr, UINT uiError, ...);

// MessageBox anzeigen, Text ist formatierbar 
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...);
int __cdecl VMessageBox (LPCSTR pcCaption, UINT uiType, UINT uiText, ...);
os_string __cdecl FakeTRiASName (UINT resID, ...);
os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)			#x
#define STR2(x)			STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) ") : " #desc)
#define TODO(desc)		message(__FILE__ "(" STR2(__LINE__) ") : TODO: " #desc)

///////////////////////////////////////////////////////////////////////////////
// sonstige nützliche Makros
#define _countof(array) (sizeof(array)/sizeof(array[0]))

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

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
// Helperfunktionen für die Verwaltung von bitweisen enum's
template<class T>
inline void SetType (T &rVal, DWORD rgToSet) 
{ 
	rVal = (T)(rVal | rgToSet);
}

template<class T>
inline void ClearType (T &rVal, DWORD rgToClear) 
{ 
	rVal = (T)(rVal & ~rgToClear); 
}

template<class T>
inline bool HasType (T rgVal, DWORD rgToTest) 
{ 
	return (rgVal & rgToTest) ? true : false; 
}

///////////////////////////////////////////////////////////////////////////////
//
DWORD OBJECTTYPEToBits (OBJECTTYPE rgType);		// OBJECTTYPE zu TRiAS-Objektbits konvertieren
OBJECTTYPE BitsToOBJECTTYPE (DWORD dwTypes);	// Objektbits zu OBJECTTYPE konvertieren

///////////////////////////////////////////////////////////////////////////////
// Helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr) {
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
// Sammeln aller selektierten Objektes eines oder aller Recherchefenster
typedef list<INT_PTR> CSelectedObjects;
bool CollectSelectedObjects (HWND hWnd, insert_iterator<CSelectedObjects> it);

///////////////////////////////////////////////////////////////////////////////
// der neue midl generiert sowas
#if _MSC_VER < 1100			
#define DECLSPEC_UUID(x)
#define DECLSPEC_SELECTANY
#else
#define DECLSPEC_SELECTANY __declspec(selectany)
#endif // _MSC_VER < 1100

#endif // !defined(_QUERYDEFUTIL_H__1BF01AF6_33CF_11D3_94FA_0080C786297B__INCLUDED_)

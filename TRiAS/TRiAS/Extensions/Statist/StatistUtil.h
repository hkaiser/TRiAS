// @doc 
// @module StatistUtil.h | Nützliche Makros etc...

#if !defined(_STATISTUTIL_H__CF461D87_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
#define _STATISTUTIL_H__CF461D87_EE47_11D2_9BE4_BAF620524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

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

#if _MSC_VER < 1100			// der neue midl generiert sowas
#define DECLSPEC_UUID(x)
#define DECLSPEC_SELECTANY
#else
#define DECLSPEC_SELECTANY __declspec(selectany)
#endif // _MSC_VER < 1100

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
// Strings laden/schreiben
HRESULT LoadString (IStream *pIStm, os_string &rStr);
HRESULT SaveString (IStream *pIStm, os_string str);
DWORD GetSizeMax (os_string &rStr);

#endif // !defined(_STATISTUTIL_H__CF461D87_EE47_11D2_9BE4_BAF620524153__INCLUDED_)

#include "TRiASMDS.h"

#include "resource.h"       // main symbols

#include "ospace/com/iterenum.h"
#include "McKinney/OleType.h"
#include "com/VariantHelpers.h"

using namespace MC;

#include "TRiASMDS.hmc"

#define	TLB_TRiASMDS_SIGNAT	&LIBID_TRiASMDS, TYPELIB_TRIASMDS_VERSION_MAJOR, TYPELIB_TRIASMDS_VERSION_MINOR

DefineSmartInterface( TRiASMDSStringColl )

#include "com/StreamHelpers.h"

///////////////////////////////////////////////////////////////////////////
// @doc 
// @module MakeEnumVariant.h | Konvertieren eines WEnumWBla in einen IEnumVARIANT

#if !defined(_MAKEENUMVARIANT_H__B6F85384_9A35_11D1_BA15_080036D63803__INCLUDED_)
#define _MAKEENUMVARIANT_H__B6F85384_9A35_11D1_BA15_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Typdefinitionen etc.
typedef CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > CEnumVARIANT;

///////////////////////////////////////////////////////////////////////////////
// Template overloading für unterschiedliche Count-Prototypen in IEnum<T> 
// und IEnumEx<K,T>
template <class T>
inline long GetCount (T &rEnum, IEnum<T::target_t::enum_t> *) {
	return rEnum -> Count();
}

template <class T>
inline long GetCount (T &rEnum, IEnum2<T::target_t::enum_t> *) {
long lCount = 0;
	rEnum -> Count((ULONG *)&lCount);
	return lCount;
}

template <class T>
inline long GetCount (T &rEnum, IEnumEx<T::target_t::enumkey_t, T::target_t::enum_t> *)
{
long lCount = 0;

	rEnum -> Count((ULONG *)&lCount);
	return lCount;
}

///////////////////////////////////////////////////////////////////////////////
// Die eigentliche Konvertierung findet hier statt
// <class T> muß ein Enumerator vom Typ 'WEnumW[Interface]' sein (z.B. WEnumWTRiASView)

template <class T>
inline HRESULT MakeEnumVARIANT (T rEnum, IUnknown *pIUnk, IUnknown **ppIEnum)
{
// Kopie des Enumerator anfordern (ThreadSicherheit)
T Enum;

	RETURN_FAILED_HRESULT(rEnum -> Clone(Enum.ppi()));

// Anzahl der Elemente besorgen
long lCount = GetCount<T>(Enum, (T::target_t *)NULL);

//	if (0 == lCount) return S_FALSE;

// Speicher für neue Variants anfordern (gibt sich selbst frei!)
VARIANT *pVars = (VARIANT *)alloca(sizeof(VARIANT) * lCount);
T::target_t::enum_t t;		// 't' ist ein enumeriertes Element
long i = 0;

	memset (pVars, '\0', sizeof(VARIANT) * lCount);	// Speicher (VARIANT's) initialisieren
	for (Enum -> Reset(); S_OK == Enum -> Next (1, &t, NULL); ++i)
	{
		CComVariant v( (LPCWSTR) t );		// alle Elemente umkopieren

//		::VariantInit (&pVars[i]);
		RETURN_FAILED_HRESULT(v.Detach(&pVars[i]));
	}
	_ASSERTE(i == lCount);

// neuen Enumerator erzeugen
CComObject<CEnumVARIANT> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumVARIANT>());
	if (NULL == pIEnum) return E_OUTOFMEMORY;

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init (&pVars[0], &pVars[lCount], pIUnk, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumVARIANT, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

// Variants wieder freigeben (Init kopiert sauber)
	for (i = 0; i < lCount; ++i)
		::VariantClear (&pVars[i]);

	return hr;
}

#endif // !defined(_MAKEENUMVARIANT_H__B6F85384_9A35_11D1_BA15_080036D63803__INCLUDED_)

///////////////////////////////////////////////////////////////////////////
// Enumeratoren

// {04D103F2-592A-11d2-8FCA-0060085FC1CE}
extern "C" const IID __declspec(selectany) IID_IEnumBSTR = 
{ 0x4d103f2, 0x592a, 0x11d2, { 0x8f, 0xca, 0x0, 0x60, 0x8, 0x5f, 0xc1, 0xce } };

DefineEnumerator2( BSTR, IID_IEnumBSTR )
DefineSmartEnumerator2( BSTR, IID_IEnumBSTR )


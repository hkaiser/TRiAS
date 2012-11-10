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
template<typename T>
inline long GetCount (T &rEnum, IEnum<T::target_t::enum_t> *)
{
	return rEnum -> Count();
}

template<typename T>
inline long GetCount (T &rEnum, IEnum2<T::target_t::enum_t> *)
{
long lCount = 0;

	rEnum -> Count((ULONG *)&lCount);
	return lCount;
}

template<typename T>
inline long GetCount (T &rEnum, IEnumEx<T::target_t::enumkey_t, T::target_t::enum_t> *)
{
long lCount = 0;

	rEnum -> Count((ULONG *)&lCount);
	return lCount;
}

///////////////////////////////////////////////////////////////////////////////
// Unterscheidung nach verarbeiteten Interface's (abgeleitet von IDispatch bzw.
// abgeleitet von IUnknown
template<typename T>
inline HRESULT CopyEnum (T Enum, VARIANT *pVars, long lCount, IDispatch *)
{
T::target_t::enum_t t;		// 't' ist ein enumeriertes Element
long i = 0;

	for (Enum -> Reset(); S_OK == Enum -> Next (1, &t, NULL); ++i)
	{
	// Ältere Tools (late binding) gehen davon aus, daß IDispatch * geliefert werden (#HK981111)
	CComQIPtr<IDispatch, &IID_IDispatch> disp(t);
	CComVariant v (disp);	// alle Elemente umkopieren

		_ASSERTE(NULL != V_DISPATCH(&v));							// QI darf nicht fehlschlagen
		RETURN_FAILED_HRESULT(v.Detach(&pVars[i]));
	}
	_ASSERTE(i == lCount);
	return S_OK;
}

template<typename T>
inline HRESULT CopyEnum (T Enum, VARIANT *pVars, long lCount, IUnknown *)
{
T::target_t::enum_t t;		// 't' ist ein enumeriertes Element
long i = 0;

	for (Enum -> Reset(); S_OK == Enum -> Next (1, &t, NULL); ++i)
	{
	CComVariant v (t);	// alle Elemente umkopieren

		_ASSERTE(NULL != V_UNKNOWN(&v));
		RETURN_FAILED_HRESULT(v.Detach(&pVars[i]));
	}
	_ASSERTE(i == lCount);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Die eigentliche Konvertierung findet hier statt
// <typename T> muß ein Enumerator vom Typ 'WEnumW[Interface]' sein (z.B. WEnumWTRiASView)

template<typename T>
inline HRESULT MakeEnumVARIANT (T rEnum, IUnknown *pIUnk, IUnknown **ppIEnum)
{
// Kopie des Enumerator anfordern (ThreadSicherheit)
T Enum;

	RETURN_FAILED_HRESULT(rEnum -> Clone(Enum.ppi()));

// Anzahl der Elemente besorgen
long lCount = GetCount<T>(Enum, (T::target_t *)NULL);
HRESULT hr = E_FAIL;

// Speicher für neue Variants anfordern (gibt sich selbst frei!)
	COM_TRY {
	VARIANT *pVars = new VARIANT [lCount];
	
		memset (pVars, '\0', sizeof(VARIANT) * lCount);		// Speicher (VARIANT's) initialisieren
		CopyEnum (Enum, pVars, lCount, (T::target_t::enum_t::target_t *)NULL);

	// neuen Enumerator erzeugen
	CComObject<CEnumVARIANT> *pIEnum = new CComObject<CEnumVARIANT>();

		if (NULL == pIEnum) 
			return E_OUTOFMEMORY;

	// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
	// letzten+1 Elementes eines Vektors
		hr = pIEnum -> Init (&pVars[0], &pVars[lCount], pIUnk, AtlFlagTakeOwnership);
		if (SUCCEEDED(hr))
			hr = pIEnum -> QueryInterface(IID_IEnumVARIANT, (LPVOID *)ppIEnum);

		if (FAILED(hr)) {		// bei Fehler alles freigeben
			*ppIEnum = NULL;
			delete pIEnum;
		}
		
	} COM_CATCH;
	return hr;
}

#endif // !defined(_MAKEENUMVARIANT_H__B6F85384_9A35_11D1_BA15_080036D63803__INCLUDED_)

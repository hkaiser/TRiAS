///////////////////////////////////////////////////////////////////////////
// @doc
// @module PropertySupportImpl.cpp | Verwaltung diverser Properties für ein Objekt

#ifndef _PROPERTYSUPPORT_H__97993C74_5FE6_11D1_B9E6_080036D63803__INCLUDED_
	#error PropertySupportImpl.cpp requires PropertySupport.h to be included first
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ClassFactory);

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen von _PROPERTYSUPPORT_ENTRY

#pragma optimize ("", off)
HRESULT _PROPERTYSUPPORT_ENTRY::GetSupportObject (ITRiASPropertyCallback **ppOut, IUnknown *punk)
{
	_ASSERTE(!(dwFlags & PROPERTYSUPPORT_DEFAULT));

HRESULT hr = E_FAIL;

	if (NULL == pobj) {
		if (dwFlags & PROPERTYSUPPORT_USECREATORFUNC)
			hr = ((_ATL_CREATORFUNC *)dw)(NULL, IID_IUnknown, (LPVOID *)&pobj);
		else
			hr = TxCreatePropertySupportObject((const CLSID *)dw, NULL, (LPVOID *)&pobj);
 		if (FAILED(hr))	return hr;
	}
	_ASSERTE(NULL != pobj);

// zusätzliche Initialisierungen durchführen
	TxInitPropertySupportObject(this, pobj, punk);		// evtl. Fehler ignorieren

	hr = pobj -> QueryInterface (ppOut);
	if (FAILED(hr)) 
		ReleaseSupportObjects();
	return hr;
}
#pragma optimize ("", on)

HRESULT _PROPERTYSUPPORT_ENTRY::GetDefaultSupportObject (
	LPCOLESTR pcName, ITRiASPropertyCallback **ppOut, IUnknown *punk)
{
	_ASSERTE(dwFlags & PROPERTYSUPPORT_DEFAULT);

WUnknown Unk;
HRESULT hr = E_FAIL;

	if (dwFlags & PROPERTYSUPPORT_USECREATORFUNC)
		hr = ((_ATL_CREATORFUNC *)dw)((dwFlags & PROPERTYSUPPORT_AGGREGATE) ? punk : NULL, IID_IUnknown, Unk.ppv());
	else
		hr = TxCreatePropertySupportObject((const CLSID *)dw, (dwFlags & PROPERTYSUPPORT_AGGREGATE) ? punk : NULL, Unk.ppv());
	
	if (FAILED(hr)) return hr;

	hr = Unk -> QueryInterface (ppOut);
	if (FAILED(hr)) 
		ReleaseSupportObjects();
	else {
	// zusätzliche Initialisierungen durchführen
		RETURN_FAILED_HRESULT(TxInitPropertySupportObject(this, *ppOut, punk));
		RETURN_FAILED_HRESULT(AddDefaultEntry (pcName, Unk));
	}
	return hr;
}

inline
HRESULT _PROPERTYSUPPORT_ENTRY::SetSupportObject (ITRiASPropertyCallback *pISupp, IUnknown *pIUnk)
{
	_ASSERTE(NULL == pobj);		// darf noch nicht gesetzt sein
	_ASSERTE(!(dwFlags & PROPERTYSUPPORT_DEFAULT));

// zusätzliche Initialisierungen durchführen
	AtlComPtrAssign((IUnknown **)&pobj, pISupp);
	return TxInitPropertySupportObject(this, pobj, pIUnk);
}

inline
HRESULT _PROPERTYSUPPORT_ENTRY::SetDefaultSupportObject (
	LPCOLESTR pcName, ITRiASPropertyCallback *pISupp, IUnknown *pIUnk)
{
	_ASSERTE(dwFlags & PROPERTYSUPPORT_DEFAULT);

// zusätzliche Initialisierungen durchführen
	RETURN_FAILED_HRESULT(TxInitPropertySupportObject(this, pISupp, pIUnk));
	return AddDefaultEntry (pcName, pISupp);
}

inline
HRESULT _PROPERTYSUPPORT_ENTRY::AddDefaultEntry (LPCOLESTR pcName, IUnknown *pIUnk)
{
	_ASSERTE(dwFlags & PROPERTYSUPPORT_DEFAULT);

// in unserer Liste eintragen
	if (NULL == pobjs) {
		ATLTRY(pobjs = new CDefEntries);
		if (NULL == pobjs) {
			ReleaseSupportObjects();
			return E_OUTOFMEMORY;
		}
	}
	pobjs -> push_back (CDefEntry(CComBSTR(pcName), pIUnk));
	return S_OK;
}

HRESULT _PROPERTYSUPPORT_ENTRY::ReleaseSupportObjects (LPCOLESTR pcName)
{
__Interface<IObjectWithSite> Site;
HRESULT hr = S_FALSE;

	if (dwFlags & PROPERTYSUPPORT_DEFAULT) {
		if (NULL != pobjs) {
			if (NULL == pcName) {
			// alles freigeben
				for (CDefEntries::iterator it = pobjs -> begin(); it != pobjs -> end(); ++it)
				{
					if ((*it).second.IsValid() && SUCCEEDED((*it).second -> QueryInterface(Site.ppi()))) 
						Site -> SetSite(NULL);
				}
				pobjs -> clear();			// alle Einträge freigeben
				hr = S_OK;
			} else {
				for (CDefEntries::iterator it = pobjs -> begin(); it != pobjs -> end(); ++it)
				{
					if (wcscmp ((*it).first, pcName))
						continue;			// noch nicht gefunden

					if ((*it).second.IsValid() && SUCCEEDED((*it).second -> QueryInterface(Site.ppi()))) 
						Site -> SetSite(NULL);
					pobjs -> erase (it);	// diesen Eintrag freigeben
					hr = S_OK;
					break;
				}
			}

		// evtl. Containerobjekt freigeben
			if (0 == pobjs -> size()) {
				delete pobjs;
				pobjs = NULL;
			}
		} 
	} else {
		if (NULL != pobj) { 
			if (SUCCEEDED(pobj->QueryInterface(Site.ppi())))
			{
				Site->SetSite(NULL);
			}
			pobj -> Release(); 
			pobj = NULL; 

			hr = S_OK;
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen, die _einmal_ gerneriert werden sollten
HRESULT TxCreatePropertySupportObject (const CLSID *pclsid, IUnknown *punk, LPVOID *ppobj)
{
// erst versuchen, lokal zu erzeugen
WUnknown Unk;
HRESULT hr = Unk.LocalCreateInstance (*pclsid, CLSCTX_INPROC_SERVER, punk);

	if (FAILED(hr)) return hr;
	*ppobj = Unk.detach();
	return S_OK;
}

HRESULT TxGetPropertySupportSite (
	_PROPERTYSUPPORT_ENTRY* pEntries, LPCOLESTR pcKey, ITRiASPropertyCallback *pdefault, 
	IUnknown *punk, ITRiASPropertyCallback **ppISite)
{
// versuchen diesen Eintrag zu finden
_PROPERTYSUPPORT_ENTRY* pDefEntry = NULL;

	while (NULL != pEntries->dw) {
		if (pEntries->dwFlags & PROPERTYSUPPORT_DEFAULT)
			pDefEntry = pEntries;		// DefaultEntry merken
		else if (NULL != pEntries->szKey && !wcscmp (pcKey, pEntries->szKey)) {
			if (SUCCEEDED(pEntries -> GetSupportObject (ppISite, punk))) 		// gefunden und erzeugt
				return S_OK;
		}
		pEntries++;
	}

// nichts gefunden, Standard liefern
	if (NULL == pdefault && NULL == pDefEntry) 
		return E_POINTER;

// evtl. ist Default-CLSID gegeben
	if (NULL != pDefEntry && SUCCEEDED(pDefEntry -> GetDefaultSupportObject (pcKey, ppISite, punk))) 
		return S_OK;

// ansonsten gegebenes defaultobjekt verwenden
	_ASSERTE(NULL != pdefault);
	*ppISite = pdefault;
	LPUNKNOWN(*ppISite) -> AddRef();

	return S_FALSE;		// Standard geliefert
}

// Enumerieren aller 'festen' Properties dieses Objektes
HRESULT TxEnumPropertyEntries (
	_PROPERTYSUPPORT_ENTRY* pEntry, HRESULT (CALLBACK *pFcn)(LPCOLESTR, UINT_PTR), 
	UINT_PTR dwData)
{
HRESULT hr = S_OK;

	while (NULL != pEntry->dw) {
		if (NULL != pEntry->szKey) {
			hr = pFcn (pEntry->szKey, dwData);
			if (S_OK != hr) 
				break;
		}
		pEntry++;
	}
	return hr;
}

// Feststellen, ob eine property zu den 'festen' eines Objektes gehört
HRESULT TxPropertyIsPredefined (_PROPERTYSUPPORT_ENTRY* pEntry, LPCOLESTR pcKey)
{
	while (NULL != pEntry->dw) {
		if (NULL != pEntry->szKey && !wcscmp (pEntry->szKey, pcKey)) 
			return S_OK;	// festen Property
		pEntry++;
	}
	return S_FALSE;		// dynamisch erzeugte Property
}

// Initialisieren des PropertySupportObjektes
HRESULT TxSetPropertySupportSite (
	_PROPERTYSUPPORT_ENTRY* pEntries, LPCOLESTR pcKey, ITRiASPropertyCallback *pISupp, IUnknown *pIUnk)
{
// versuchen diesen Eintrag zu finden
_PROPERTYSUPPORT_ENTRY* pDefEntry = NULL;

	while (NULL != pEntries->dw) {
		if (pEntries->dwFlags & PROPERTYSUPPORT_DEFAULT)
			pDefEntry = pEntries;		// DefaultEntry merken
		else if (NULL != pEntries->szKey && !wcscmp (pcKey, pEntries->szKey)) {
			if (SUCCEEDED(pEntries -> SetSupportObject (pISupp, pIUnk))) 		// gefunden und erzeugt
				return S_OK;
		}
		pEntries++;
	}

// evtl. ist Default-CLSID gegeben
	if (NULL != pDefEntry && SUCCEEDED(pDefEntry -> SetDefaultSupportObject (pcKey, pISupp, pIUnk))) 
		return S_OK;

	return S_FALSE;
}

// Freigeben eines Property-Bezugsobjektes
HRESULT TxReleasePropertySupportObject (_PROPERTYSUPPORT_ENTRY* pEntries, LPCOLESTR pcKey)
{
// versuchen diesen Eintrag zu finden
_PROPERTYSUPPORT_ENTRY* pDefEntry = NULL;

	while (NULL != pEntries->dw) {
		if (pEntries->dwFlags & PROPERTYSUPPORT_DEFAULT)
			pDefEntry = pEntries;		// DefaultEntry merken
		else if (NULL != pEntries->szKey && !wcscmp (pcKey, pEntries->szKey)) {
		HRESULT hr = E_FAIL;

			if (SUCCEEDED(hr = pEntries -> ReleaseSupportObjects())) {		// gefunden und freigegeben
				if (pEntries -> dwFlags & PROPERTYSUPPORT_DYNAMICSTRING) 
				{
					delete const_cast<unsigned short *>(pEntries -> szKey);
					pEntries -> szKey = NULL;
				}
				VariantClear(&pEntries -> vInitData);
				pEntries -> vInitData = vtMissing;
				return hr;
			}
		}
		pEntries++;
	}

// evtl. ist Default-CLSID gegeben
	if (NULL != pDefEntry) 
		return pDefEntry -> ReleaseSupportObjects (pcKey); 

	return S_FALSE;
}

// Freigeben aller Property-Bezugsobjekte
void TxReleasePropertySupportObjects (_PROPERTYSUPPORT_ENTRY* pEntry)
{
	while (NULL != pEntry->dw) {
		pEntry -> ReleaseSupportObjects();
		if (pEntry -> dwFlags & PROPERTYSUPPORT_DYNAMICSTRING) 
		{
			delete const_cast<unsigned short *>(pEntry -> szKey);
			pEntry -> szKey = NULL;
		}
		VariantClear(&pEntry -> vInitData);
		pEntry -> vInitData = vtMissing;
		pEntry -> pDefValProc = NULL;
		pEntry++;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Verändern eines Eintrages
HRESULT TxChangeMapEntry (
	_PROPERTYSUPPORT_ENTRY* pEntry, LPCOLESTR pcKey, INT_PTR NewData, DWORD NewFlags, 
	VARIANT vInitData, GETDEFAULTVALUEPROC pFcn)
{
	while (NULL != pEntry->dw) {
		if (NULL != pEntry->szKey && !wcscmp (pEntry->szKey, pcKey)) {
			pEntry -> dw = NewData;
			pEntry -> dwFlags = NewFlags;

			if (VT_ERROR != V_VT(&vInitData))
			{
				RETURN_FAILED_HRESULT(VariantCopy (&pEntry -> vInitData, &vInitData));
			}
			if (NULL != pFcn)
				pEntry -> pDefValProc = pFcn;
			return S_OK;
		}
		pEntry++;
	}
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen eines Eintrages
HRESULT TxAddMapEntry (
	_PROPERTYSUPPORT_ENTRY* pEntry, LPCOLESTR pcKey, INT_PTR NewData, DWORD NewFlags, 
	VARIANT vInitData, GETDEFAULTVALUEPROC pFcn)
{
	while (NULL != pEntry->dw) {
		if (pEntry -> dwFlags & PROPERTYSUPPORT_DYNAMICSTRING && NULL == pEntry -> szKey) {
            if (NULL != pcKey) {
			    ATLTRY(pEntry -> szKey = new wchar_t[wcslen(pcKey)+1]);
			    if (NULL == pEntry -> szKey) return E_OUTOFMEMORY;
			    wcscpy (const_cast<unsigned short *>(pEntry -> szKey), pcKey);
            }

			pEntry -> dw = NewData;
			pEntry -> dwFlags |= NewFlags;
			if (VT_ERROR != V_VT(&vInitData))
			{
				RETURN_FAILED_HRESULT(VariantCopy (&pEntry -> vInitData, &vInitData));
			}
			pEntry -> pDefValProc = pFcn;
			return S_OK;
		}
		pEntry++;
	}
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Initialisierungen durchführen

HRESULT TxInitPropertySupportObject (
	_PROPERTYSUPPORT_ENTRY* pEntry, ITRiASPropertyCallback *pobj, IUnknown *punk)
{
// Objekte, die den Parent brauchen, kriegen selbigen über das IObjectWithSite zugeschoben
CComPtr<IObjectWithSite> pSite;

	if (NULL != punk && SUCCEEDED(pobj -> QueryInterface(&pSite.p)))
	{
		RETURN_FAILED_HRESULT(pSite -> SetSite(punk));
	}

// Objekte, die Ihren Namen brauchen, kriegen selbigen
CComPtr<IObjectWithName> pName;
CComBSTR bstrName (pEntry->szKey);

	if (SUCCEEDED(pobj -> QueryInterface(&pName.p)))
	{
		RETURN_FAILED_HRESULT(pName -> put_Name(bstrName));
	}

// Objekte, die initialisiert werden sollen, werden es hier
	if (pEntry->dwFlags & PROPERTYSUPPORT_HASINITDATA)
	{
		if (NULL != pEntry -> pDefValProc) {
		// Initialisierung erfolgt über gegebene Funktion
		PROPERTY_TYPE rgType = PROPERTY_TYPE_Normal;

			RETURN_FAILED_HRESULT((pEntry -> pDefValProc)(bstrName, &pEntry -> vInitData, &rgType));
			RETURN_FAILED_HRESULT(pobj -> PutValueAndType (bstrName, pEntry -> vInitData, rgType));
		} else {
			RETURN_FAILED_HRESULT(pobj -> PutValue (bstrName, pEntry -> vInitData));
		}
	}
	return S_OK;
}



// Implementation diverser ObjEnumerator - Interfaces -------------------------
// File: IENUMSTR.CXX

#include "triaspre.hxx"

#include <tchar.h>
#include "ienumstr.hxx"

// ArrayContainer, der alle ObjektNummern enthält -----------------------------
CStringArray :: CStringArray (void)
	      : CArrayContainer (5)
{
	// nothing else
}

CStringArray :: ~CStringArray (void)
{
	EveryDelete ();
}

void EXPORTTRIAS CStringArray :: UserDelete (void *pObj)
{
	((CStringItem *)pObj) -> ~CStringItem();
}


// StringEnumeratoren ---------------------------------------------------------
// Funktionen der Basisklasse -------------------------------------------------
CImpIEnumStrings :: CImpIEnumStrings (void)		// Konstruktor
{
	m_pacStrings = NULL;	// ObjectContainer
	m_cRef = 0;		// ReferenceCount initialisieren
}

CImpIEnumStrings :: ~CImpIEnumStrings (void)		// Destruktor
{
	DELETE_OBJ (m_pacStrings);	// StringContainer freigeben
}

CImpIEnumStrings *CImpIEnumStrings :: CreateInstance (void)
{
CImpIEnumStrings *pEnum = new CImpIEnumStrings();

	if (pEnum == NULL || !pEnum -> Init()) {
		DELETE_OBJ(pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// Initialisieren der BasisKlasse. Diese Funktion sollte aus der 
// InitialisierungsFunktion des konkreten Enumerators heraus gerufen werden.
bool CImpIEnumStrings :: Init (void)
{
	m_pacStrings = new CStringArray;
	Reset();
	
return m_pacStrings != NULL;
}


// String zu Array hinzufügen -------------------------------------------------
bool CImpIEnumStrings :: AddString (LPCSTR pStr)
{
	if (pStr == NULL || m_pacStrings == NULL)
		return false;
		
CStringItemCreator CSCr (*m_pacStrings);

	return ContCreate (CSCr, CStringItem)(pStr) != NULL;
}

#if !defined(WIN16)
bool CImpIEnumStrings :: AddString (LPCWSTR pStr)
{
	if (pStr == NULL || m_pacStrings == NULL)
		return false;
		
CStringItemCreator CSCr (*m_pacStrings);

	return ContCreate (CSCr, CStringItem)(pStr) != NULL;
}
#endif // WIN16

// AddRef/Release - Kontrolle der LebensDauer des Enumerators -----------------
STDMETHODIMP_(ULONG) CImpIEnumStrings :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpIEnumStrings :: Release (void)
{
DWORD cRefT;

	cRefT = --m_cRef;
	if (m_cRef == 0) delete this;	// freigeben

return cRefT;
}

STDMETHODIMP CImpIEnumStrings :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumString)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

// Die nächsten celt ObjektNummern liefern ------------------------------------
STDMETHODIMP CImpIEnumStrings :: Next (DWORD celt, LPWSTR *rgelt, LPDWORD ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (rgelt == NULL) return ResultFromScode(S_FALSE);
	if (m_pacStrings == NULL  || m_ulCur >= m_pacStrings -> Count())
        	return ResultFromScode(S_FALSE);
        	
CRing r (*m_pacStrings);

	while (m_ulCur < m_pacStrings -> Count() && celt > 0) {

		r.Goto (m_ulCur);	// Navigator positionieren
		
	CStringItemLock l(r);
	
		if (!l)	return ResultFromScode(S_FALSE);
		*rgelt++ = StrDupW (l -> FString(), 0);

	// weiterzählen
		m_ulCur++;
		celt--;
		cONrReturn++;
	}
	if (ppeltFetched) 
		*ppeltFetched = (cONrReturn - celt);	// gelieferte Werte

return NOERROR;
}


// Enumerator um dwSkip weitersetzen ------------------------------------------
STDMETHODIMP CImpIEnumStrings :: Skip (DWORD dwSkip)
{
	if (m_ulCur + dwSkip < m_pacStrings -> Count()) {
		m_ulCur += dwSkip;
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

// Zurücksetzen des Enumerators -----------------------------------------------
STDMETHODIMP CImpIEnumStrings :: Reset (void)
{
	m_ulCur = 0L;

return NOERROR;
}

STDMETHODIMP CImpIEnumStrings :: Clone (IEnumString **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

CImpIEnumStrings *pEnum = CImpIEnumStrings :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// String kopieren
CRing r (*m_pacStrings);

	for (r.First(); r.Valid(); r.Next()) {
	CStringItemLock l(r);
	
		if (!l)	continue;
		if (!pEnum -> AddString (l -> FString())) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}
	}
	pEnum -> m_ulCur = m_ulCur;
	*ppenum = pEnum;

return NOERROR;
}



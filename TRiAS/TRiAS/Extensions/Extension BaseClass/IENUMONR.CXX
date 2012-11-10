// Implementation des IEnumObjectsByNumber - Interfaces -----------------------
// File: IENUMONR.CXX

#include "xtensnp.hxx"

#include "ienumonr.hxx"
#include <eonrguid.h>

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ArrayContainer, der alle ObjektNummern enthält -----------------------------
CObjectArray :: CObjectArray (int iCnt)
	      : CArrayContainer (iCnt > 0 ? iCnt : DEFAULTONRCNT)
{
	// nothing else
}

CObjectArray :: ~CObjectArray (void)
{
	EveryDelete ();
}

void _XTENSN_EXPORT CObjectArray :: UserDelete (void *pObj)
{
	((CONrItem *)pObj) -> ~CONrItem();
}

bool CObjectArray :: AddObject (LONG lONr)
{
CONrItemCreator ONrCr (*this);

#if defined(__MFC__) 
CONrItem *pItem = new CONrItem (lONr);

	if (NULL == pItem) return false;

	return ONrCr.InsertPtr(pItem) ? true : false;
#elif defined(__ATL_USED__)
	return NULL != ContCreate (ONrCr, CONrItem)(lONr) ? true : false;
#else
	return NULL != Create (ONrCr, CONrItem)(lONr) ? true : false;
#endif
}

// StringEnumeratoren ---------------------------------------------------------
// Funktionen der Basisklasse -------------------------------------------------
CEnumObjectsByNumber :: CEnumObjectsByNumber (int iCnt)		// Konstruktor
	              : m_iCnt(iCnt), m_Objs(iCnt)
{
	m_ulCur = 0L;
	m_dwRefCnt = 0;		// ReferenceCount initialisieren

	Reset();
}

CEnumObjectsByNumber :: ~CEnumObjectsByNumber (void)		// Destruktor
{
}

CEnumObjectsByNumber *CEnumObjectsByNumber :: CreateInstance (int iCnt)
{
CEnumObjectsByNumber *pEnum = new CEnumObjectsByNumber (iCnt);

	if (pEnum == NULL || !pEnum -> FInit()) {
		DELETE_OBJ(pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// Initialisieren der BasisKlasse. Diese Funktion sollte aus der 
// InitialisierungsFunktion des konkreten Enumerators heraus gerufen werden.
bool CEnumObjectsByNumber :: FInit (void) { return true; }


// Objekt zu Array hinzufügen -------------------------------------------------
bool CEnumObjectsByNumber :: AddObject (LONG lONr)
{
	return m_Objs.AddObject (lONr);
}

// AddRef/Release - Kontrolle der LebensDauer des Enumerators -----------------
STDMETHODIMP_(ULONG) CEnumObjectsByNumber :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumObjectsByNumber :: Release (void)
{
DWORD dwRefT = --m_dwRefCnt;

	if (m_dwRefCnt == 0) delete this;	// freigeben

return dwRefT;
}

STDMETHODIMP CEnumObjectsByNumber :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumLONG)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

// Die nächsten celt Objekte liefern ------------------------------------------
STDMETHODIMP CEnumObjectsByNumber :: Next (DWORD celt, LONG *rgelt, LPDWORD ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (NULL == rgelt || m_Objs.Count() == m_ulCur) 
		return ResultFromScode (S_FALSE);
        	
CRing r (m_Objs);

	while (m_Objs.Count() >= m_ulCur && 0 < celt) {

		r.Goto (m_ulCur);	// Navigator positionieren
		
	CONrItemLock l(r);
	
		TX_ASSERT (NULL != (CONrItem *)l);

		*rgelt = l -> FONr();
		rgelt++;

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
STDMETHODIMP CEnumObjectsByNumber :: Skip (DWORD dwSkip)
{
	if (m_Objs.Count() >= m_ulCur + dwSkip) {
		m_ulCur += dwSkip;
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

// Zurücksetzen des Enumerators -----------------------------------------------
STDMETHODIMP CEnumObjectsByNumber :: Reset (void)
{
	m_ulCur = 0L;

return NOERROR;
}

STDMETHODIMP CEnumObjectsByNumber :: Clone (IEnumLONG **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden (standalone)
CEnumObjectsByNumber *pEnum = CEnumObjectsByNumber :: CreateInstance (m_iCnt);

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Objects kopieren
CRing r (m_Objs);

	for (r.First(); r.Valid(); r.Next()) {
	CONrItemLock l(r);
	
		TX_ASSERT(NULL != (CONrItem *)l);
		
		if (!pEnum -> AddObject (l -> FONr())) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}
	}
	pEnum -> m_ulCur = m_ulCur;
	*ppenum = pEnum;

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumObjectsByNumber :: Count (void)
{
	return m_Objs.Count();
}


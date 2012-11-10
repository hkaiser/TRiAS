// Implementation des IEnumUnknown - Interfaces -------------------------------
// File: ENUMUNDO.CXX

#include "trias03p.hxx"

#include <containr.hxx>
#include "enumundo.hxx"

// ArrayContainer, der alle ObjektNummern enthält -----------------------------
CUnknownArray :: CUnknownArray (int iCnt)
	       : CArrayContainer (iCnt > 0 ? iCnt : DEFAULTUNDOCNT, 
	       			  CONTFLAG(CFSyncThreads|CFAutoDelete))
{
	// nothing else
}

CUnknownArray :: ~CUnknownArray (void)
{
	EveryDelete ();
}

void EXPORT03 CUnknownArray :: UserDelete (void *pObj)
{
	((CUnknownItem *)pObj) -> ~CUnknownItem();
}

bool CUnknownArray :: DeleteFirst (void)
{
CRing r (*this);

	if (r.Goto (0))
		return r.Delete();

return false;
}

bool CUnknownArray :: DeleteLast (void)
{
CRing r (*this);

	if (r.Goto (Count()-1))
		return r.Delete();

return false;
}

// StringEnumeratoren ---------------------------------------------------------
// Funktionen der Basisklasse -------------------------------------------------
CEnumUndoRedo :: CEnumUndoRedo (LPUNKNOWN pUnk, int iCnt)		// Konstruktor
	       : m_iUndoCnt (iCnt), m_Unks (iCnt)
{
	m_pIUnk = pUnk;		// controlling unknown

	m_ulCur = 0L;
	m_cRef = 0;		// ReferenceCount initialisieren

	Reset();
}

CEnumUndoRedo :: ~CEnumUndoRedo (void)		// Destruktor
{
}

CEnumUndoRedo *CEnumUndoRedo :: CreateInstance (LPUNKNOWN pUnk, int iCnt)
{
CEnumUndoRedo *pEnum = new CEnumUndoRedo (pUnk, iCnt);

	if (pEnum == NULL || !pEnum -> FInit()) {
		DELETE_OBJ(pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// Initialisieren der BasisKlasse. Diese Funktion sollte aus der 
// InitialisierungsFunktion des konkreten Enumerators heraus gerufen werden.
bool CEnumUndoRedo :: FInit (void) { return true; }


// String zu Array hinzufügen -------------------------------------------------
bool CEnumUndoRedo :: AddUnknown (LPUNKNOWN pUnk)
{
	if (pUnk == NULL) return false;

bool fRet = false;

	{		
	CUnknownItemCreator CSCr (m_Unks);
	
		fRet = ContCreate (CSCr, CUnknownItem)(pUnk) != NULL;
	}	// wegspeichern

// Liste wird länger als gewünscht
	if (fRet && m_iUndoCnt > 0 && Count() > (ULONG)m_iUndoCnt)
		m_Unks.DeleteFirst();

return fRet;
}

// AddRef/Release - Kontrolle der LebensDauer des Enumerators -----------------
STDMETHODIMP_(ULONG) CEnumUndoRedo :: AddRef (void)
{
	++m_cRef;
	if (m_pIUnk)	// if exists controlling unknown, simply delegate
		return m_pIUnk -> AddRef();

return m_cRef;		// if standalone
}

STDMETHODIMP_(ULONG) CEnumUndoRedo :: Release (void)
{
DWORD cRefT = --m_cRef;

	if (m_pIUnk)	// if exists controlling unknown, simply delegate
		return m_pIUnk -> Release();

// if standalone
	if (m_cRef == 0) delete this;	// freigeben

return cRefT;
}

STDMETHODIMP CEnumUndoRedo :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (m_pIUnk)	// if exists controlling unknown, simply delegate
		return m_pIUnk -> QueryInterface (riid, ppvObj);

// if standalone
	if (riid == IID_IUnknown || riid == IID_IEnumUnknown)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

// Die nächsten celt Undo's liefern -------------------------------------------
// ACHTUNG: arbeitet rückwärts
STDMETHODIMP CEnumUndoRedo :: Next (DWORD celt, LPUNKNOWN *rgelt, LPDWORD ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (rgelt == NULL || m_ulCur == 0) return ResultFromScode(S_FALSE);
        	
CRing r (m_Unks);

	while (m_ulCur > 0 && celt > 0) {

		r.Goto (m_ulCur -1);	// Navigator positionieren
		
	CUnknownItemLock l(r);
	
		if (!l)	return ResultFromScode(S_FALSE);

		*rgelt = l -> FUnknown();
		LPUNKNOWN(*rgelt) -> AddRef();
		rgelt++;

	// weiterzählen
		m_ulCur--;
		celt--;
		cONrReturn++;
	}
	if (ppeltFetched) 
		*ppeltFetched = (cONrReturn - celt);	// gelieferte Werte

return NOERROR;
}


// Enumerator um dwSkip weitersetzen ------------------------------------------
STDMETHODIMP CEnumUndoRedo :: Skip (DWORD dwSkip)
{
	if (m_ulCur - dwSkip >= 0) {
		m_ulCur -= dwSkip;
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

// Zurücksetzen des Enumerators -----------------------------------------------
STDMETHODIMP CEnumUndoRedo :: Reset (void)
{
	m_ulCur = m_Unks.Count();

return NOERROR;
}

STDMETHODIMP CEnumUndoRedo :: Clone (IEnumUnknown **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden (standalone)
CEnumUndoRedo *pEnum = CEnumUndoRedo :: CreateInstance (NULL, m_iUndoCnt);

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Unknown kopieren
CRing r (m_Unks);

	for (r.First(); r.Valid(); r.Next()) {
	CUnknownItemLock l(r);
	
		if (!l)	continue;
		if (!pEnum -> AddUnknown (l -> FUnknown())) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}
	}
	pEnum -> m_ulCur = m_ulCur;
	*ppenum = pEnum;

return NOERROR;
}



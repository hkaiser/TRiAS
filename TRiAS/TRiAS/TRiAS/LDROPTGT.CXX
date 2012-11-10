// DropTarget für Legendenfenster ---------------------------------------------
// File: LDROPTGT.CXX

#include "triaspre.hxx"

#include "legdinfo.hxx"
#include "legwind.hxx"
#include "ldroptgt.hxx"

// #define _DUMP

/*
 * CLegWindDropTarget::CLegWindDropTarget
 * CLegWindDropTarget::~CLegWindDropTarget
 *
 * Constructor Parameters:
 *  pBack           LPVOID back pointer to whatever we're related to.
 */

CLegWindDropTarget :: CLegWindDropTarget (CLegendeClientWindow *pBack)
{
	m_cRef = 0;
	m_pBack = pBack;
	m_pIDataObject = NULL;
}


CLegWindDropTarget :: ~CLegWindDropTarget (void)
{
	// nothing to do
}

/*
 * CLegWindDropTarget::QueryInterface
 * CLegWindDropTarget::AddRef
 * CLegWindDropTarget::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CLegWindDropTarget.
 */

STDMETHODIMP CLegWindDropTarget :: QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
	*ppv=NULL;

//Any interface on this object is the object pointer.
	if (IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_IDropTarget))
		*ppv = LPVOID(this);

/*
 * If we actually assign an interface to ppv we need to AddRef
 * it since we're returning a new pointer.
 */
	if (*ppv != NULL) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CLegWindDropTarget :: AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CLegWindDropTarget :: Release(void)
{
ULONG cRefT = --m_cRef;

	if (m_cRef == 0L)
		delete this;

return cRefT;
}


/*
 * CLegWindDropTarget::DragEnter
 *
 * Purpose:
 *  Indicates that data in a drag operation has been dragged over
 *  our window that's a potential target.  We are to decide if it's
 *  something in which we're interested.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT providing the source data.
 *  grfKeyState     DWORD flags: states of keys and mouse buttons.
 *  pt              POINTL coordinates in the client space of
 *                  the document.
 *  pdwEffect       LPDWORD into which we'll place the appropriate
 *                  effect flag for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CLegWindDropTarget :: DragEnter (LPDATAOBJECT pIDataSource,
					      DWORD grfKeyState, 
					      POINTL pt, LPDWORD pdwEffect)
{
	m_pIDataObject = NULL;		// für alle Fälle
	
// Testen, wir diese Daten verstehen
	if (!m_pBack -> FQueryPasteFromData (pIDataSource)) {
	// diese Daten sind nicht für uns
		*pdwEffect = DROPEFFECT_NONE;
		return NOERROR;
	}

// Check if this is a valid drop point.
UINT uRet = m_pBack -> UTestDroppablePoint(&pt);
	
	m_pBack -> m_uiLastTest = uRet;
	if (uRet == UDROP_NONE)
		*pdwEffect=DROPEFFECT_NONE;
	else {
	// wir können unser eigenes Zeug nur verschieben, da kopieren der 
	// LegendenEinträge sinnlos ist	
		if (m_pBack -> IsDropSource())
			*pdwEffect = DROPEFFECT_MOVE;
		else {
			*pdwEffect = DROPEFFECT_MOVE;
			if (grfKeyState & MK_CONTROL)
				*pdwEffect |= DROPEFFECT_COPY;
		}
	}
			
// Datenfesthalten
	m_pIDataObject = pIDataSource;
	m_pIDataObject  -> AddRef();	

// vollständiges Anzeigen der Legende
	m_pBack -> ToTop();
	m_pBack -> Update();
	
// Scrollen initialisieren
	m_pBack -> m_uiHorzScrollCode = USHRT_MAX;
	m_pBack -> m_uiVertScrollCode = USHRT_MAX;
	
// Einfügepunkt anzeigen
	m_pBack -> DropSelectTargetWindow (&pt);

return NOERROR;
}


/*
 * CLegWindDropTarget::DragOver
 *
 * Purpose:
 *  Indicates that the mouse was moved inside the window represented
 *  by this drop target.  This happens on every WM_MOUSEMOVE, so
 *  this function should be very efficient.
 *
 * Parameters:
 *  grfKeyState     DWORD providing the current keyboard and
 *                  mouse states
 *  pt              POINTL where the mouse currently is.
 *  pdwEffect       LPDWORD in which to store the effect flag
 *                  for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CLegWindDropTarget :: DragOver (DWORD grfKeyState, POINTL pt, 
					     LPDWORD pdwEffect)
{
// wenn das nicht für uns ist, dann weiter
	if (m_pIDataObject == NULL) {
		*pdwEffect = DROPEFFECT_NONE;
		return NOERROR;
	}

// Check if this is still a valid point.  uRet used below as well
UINT uRet = m_pBack -> UTestDroppablePoint (&pt);

	if (uRet == UDROP_NONE)
		*pdwEffect = DROPEFFECT_NONE;
	else {
	// wir können unser eigenes Zeug nur verschieben, da kopieren der 
	// LegendenEinträge sinnlos ist	
		if (m_pBack -> IsDropSource())
			*pdwEffect = DROPEFFECT_MOVE;
		else {
			*pdwEffect = DROPEFFECT_MOVE;
			if (grfKeyState & MK_CONTROL)
				*pdwEffect |= DROPEFFECT_COPY;
		}
	}
		
	if (m_pBack -> m_fFitFont) {
		m_pBack -> m_uiVertScrollCode = USHRT_MAX;
		m_pBack -> m_uiHorzScrollCode = USHRT_MAX;

	// Einfügepunkt korrigieren
		m_pBack -> DropSelectTargetWindow (&pt);
		return NOERROR; 	// no scrolling at all
	}
	
UINT uLast = m_pBack -> m_uiLastTest;

	m_pBack -> m_uiLastTest = uRet;		// alten Wert speichern
	if (uRet == UDROP_NONE) {
		m_pBack -> m_uiVertScrollCode = USHRT_MAX;
		m_pBack -> m_uiHorzScrollCode = USHRT_MAX;

	// Einfügepunkt korrigieren
		m_pBack -> DropSelectTargetWindow (&pt);

		return NOERROR;
	}

/*
 * Scrolling is a little tricky:  We get a DragOver pulse even
 * if we didn't move.  First we have to delay scrolling for
 * m_pBack->m_uiScrollDelay clock ticks which we can determine using
 * GetTickCount.  Timers do not work here since we may not be
 * yielding to our message loop.
 *
 * Once we know we are scrolling then we determine if we
 * scroll again or if we reset the scrolling state.
 */
	if ((uRet & UDROP_INSET) || (uLast & UDROP_INSET)) {
		if ((uLast & UDROP_INSETHORZ) && !(uRet & UDROP_INSETHORZ))
			m_pBack -> m_uiHorzScrollCode = USHRT_MAX;
	
		if (!(uLast & UDROP_INSETHORZ) && (uRet & UDROP_INSETHORZ)) {
			m_pBack -> m_dwTimeLast = GetTickCount();
			m_pBack -> m_uiHorzScrollCode = ((uRet & UDROP_INSETLEFT) != 0) ?
				SB_LINELEFT : SB_LINERIGHT;	//Same as UP & DOWN codes.
		}
	
		if ((uLast & UDROP_INSETVERT) && !(uRet & UDROP_INSETVERT))
			m_pBack -> m_uiVertScrollCode = USHRT_MAX;
	
		if (!(uLast & UDROP_INSETVERT) && (uRet & UDROP_INSETVERT)) {
			m_pBack -> m_dwTimeLast = GetTickCount();
			m_pBack -> m_uiVertScrollCode = ((UDROP_INSETTOP & uRet) != 0) ?
				SB_LINEUP : SB_LINEDOWN;
		}
	} 
	
// Only change the last time if ALL scrolling stops.
	if (m_pBack -> m_uiHorzScrollCode == USHRT_MAX && 
	    m_pBack -> m_uiVertScrollCode == USHRT_MAX)
		m_pBack -> m_dwTimeLast = 0L;

// Set the scroll effect on any inset hit.
	if (uRet & UDROP_INSET)
		*pdwEffect |= DROPEFFECT_SCROLL;

// Has the delay elapsed?  We can scroll if so
	if (m_pBack -> m_dwTimeLast != 0 && 
            (GetTickCount() - m_pBack -> m_dwTimeLast) > (DWORD)m_pBack -> m_uiScrollDelay)
        {
#if defined(_DUMP)
	OutputDebugString ("Drop: Ausblenden\r\n");
#endif // _DUMP

	// alten Einfügepunkt ausblenden
		m_pBack -> DropSelectTargetWindow (NULL, true);

		if (m_pBack -> m_uiHorzScrollCode != USHRT_MAX)
			SendMessage (m_pBack -> m_hWnd, WM_HSCROLL, m_pBack->m_uiHorzScrollCode, 0L);

		if (m_pBack -> m_uiVertScrollCode != USHRT_MAX) 
			SendMessage (m_pBack -> m_hWnd, WM_VSCROLL, m_pBack->m_uiVertScrollCode, 0L);

	// Einblenden übernimmt Expose
		m_pBack -> DropSelectTargetWindow (&pt, false, false);
	} else {
	// Einfügepunkt korrigieren
#if defined(_DUMP)
	OutputDebugString ("Drop: Einblenden\r\n");
#endif // _DUMP
		m_pBack -> DropSelectTargetWindow (&pt);
	}
	
return NOERROR;
}


/*
 * CLegWindDropTarget::DragLeave
 *
 * Purpose:
 *  Informs the drop target that the operation has left its window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR
 */
STDMETHODIMP CLegWindDropTarget :: DragLeave (void)
{
// wenn das nicht für uns ist, dann weiter
	if (m_pIDataObject == NULL) 
		return S_OK;

// Stop scrolling
	m_pBack -> m_uiHorzScrollCode = USHRT_MAX;
	m_pBack -> m_uiVertScrollCode = USHRT_MAX;

// Einfügepunkt ausblenden
	m_pBack -> DropSelectTargetWindow (NULL, true);
	m_pIDataObject -> Release();	// Daten werden nicht mehr benötigt
	return S_OK;
}


/*
 * CLegWindDropTarget::Drop
 *
 * Purpose:
 *  Instructs the drop target to paste the data that was just now
 *  dropped on it.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT from which we'll paste.
 *  grfKeyState     DWORD providing current keyboard/mouse state.
 *  pt              POINTL at which the drop occurred.
 *  pdwEffect       LPDWORD in which to store what you did.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CLegWindDropTarget :: Drop (LPDATAOBJECT pIDataSource, 
					 DWORD grfKeyState, 
					 POINTL pt, LPDWORD pdwEffect)
{
// wenn das nicht für uns ist, dann weiter
	if (m_pIDataObject == NULL) 
		return ResultFromScode (E_FAIL);

	*pdwEffect = DROPEFFECT_NONE;	// richtig initialisieren

// Daten einfügen
HRESULT hr = E_FAIL;

	if (m_pBack -> FPasteFromData (pIDataSource)) {	// erfolgreich eingefügt
	// wir können unser eigenes Zeug nur verschieben, da kopieren der 
	// LegendenEinträge sinnlos ist	
		if (m_pBack -> IsDropSource())
			*pdwEffect = DROPEFFECT_MOVE;
		else {
			*pdwEffect = DROPEFFECT_MOVE;
			if (grfKeyState & MK_CONTROL)
				*pdwEffect |= DROPEFFECT_COPY;
		}
		hr = S_OK;
	}
		
// Stop scrolling
	m_pBack -> m_uiHorzScrollCode = USHRT_MAX;
	m_pBack -> m_uiVertScrollCode = USHRT_MAX;

// Einfügepunkt ausblenden
	m_pBack -> DropSelectTargetWindow (NULL, true);
	m_pIDataObject -> Release();	// Daten werden nicht mehr benötigt
	return hr;
}

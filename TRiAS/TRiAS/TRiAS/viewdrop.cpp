// DropTarget für View-Fenster
// File: VIEWDROP.CPP

#include "triaspre.hxx"

#if !defined(_OLD_DRAGNDROP)

#include <dirisole.h>
#include "viewdrop.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CViewDropTarget::CViewDropTarget (void)
{
	m_pBack = NULL;
	m_pWnd = NULL;
}

CViewDropTarget::~CViewDropTarget (void)
{
}

bool CViewDropTarget::FInit (CDragDropCallback *pBack, Window *pWnd)
{
	m_pBack = pBack;
	m_pWnd = pWnd;		// BezugsFenster merken
	return true;
}

// *** IDropTarget interface members
STDMETHODIMP CViewDropTarget::DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, 
										 POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);
	m_DataSource.Assign(NULL);		// alten DataSource löschen

// erstmal alle Erweiterungen befragen
	*pdwEffect = DROPEFFECT_NONE;

	if (S_OK == m_pBack -> DragEnter (pIDataSource, grfKeyState, pt, pdwEffect))
		return NOERROR;		// abgearbeitet

// ab hier ist TRiAS selbst verantwortlich
	if (!m_pBack -> IsDropSourceInst())		// aus anderer TRiAS-Instanz
		return S_FALSE;

// Testen, ob wird diese Daten verstehen
	if (!m_pBack -> FQueryPasteFromData (pIDataSource)) 
		return S_FALSE;

// Testen, ob das hier ein gültiger Abwurfpunkt ist
UINT uiRet = m_pBack -> TestDroppablePoint (&pt);

	SetLastTest (uiRet);
	if (UDROP_NONE != uiRet) {
		*pdwEffect |= DROPEFFECT_MOVE;		// mindestens verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren
	}

// DataSource festhalten, wird noch gebraucht
	m_DataSource = pIDataSource;

// Fenster hochbringen
	m_pWnd -> ToTop();
	m_pWnd -> Update();

// Scrollen initialisieren
	SetHorzScrollCode (UINT_MAX);
	SetVertScrollCode (UINT_MAX);

// UI feedback anzeigen
	m_pBack -> GiveFeedBack (&pt);
	return S_OK;
}

STDMETHODIMP CViewDropTarget::DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);

// erstmal alle Erweiterungen befragen
	*pdwEffect = DROPEFFECT_NONE;
	if (S_OK == m_pBack -> DragOver (grfKeyState, pt, pdwEffect))
		return NOERROR;		// abgearbeitet

// ab hier ist wieder TRiAS selbst verantwortlich
	if (!m_DataSource.IsValid()) 			// war nichts für uns
		return S_FALSE;

	if (!m_pBack -> IsDropSourceInst())		// aus anderer TRiAS-Instanz
		return S_FALSE;

// noch mal DropPoint testen
UINT uiRet = m_pBack -> TestDroppablePoint (&pt);

	if (UDROP_NONE != uiRet) {
		*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren
	}

UINT uiLast = GetLastTest();

	SetLastTest (uiRet);		// alten Wert speichern
	if (uiRet == UDROP_NONE) {
		SetVertScrollCode (UINT_MAX);
		SetHorzScrollCode (UINT_MAX);

	// Einfügepunkt korrigieren
		m_pBack -> GiveFeedBack (&pt);
		return S_FALSE;
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
	if ((uiRet & UDROP_INSET) || (uiLast & UDROP_INSET)) {
		if ((uiLast & UDROP_INSETHORZ) && !(uiRet & UDROP_INSETHORZ))
			SetHorzScrollCode (UINT_MAX);
	
		if (!(uiLast & UDROP_INSETHORZ) && (uiRet & UDROP_INSETHORZ)) {
			SetLastTime (GetTickCount());
			SetHorzScrollCode ((uiRet & UDROP_INSETLEFT) ? SB_LINELEFT : SB_LINERIGHT);	// Same as UP & DOWN codes.
		}
	
		if ((uiLast & UDROP_INSETVERT) && !(uiRet & UDROP_INSETVERT))
			SetVertScrollCode (UINT_MAX);
	
		if (!(uiLast & UDROP_INSETVERT) && (uiRet & UDROP_INSETVERT)) {
			SetLastTime (GetTickCount());
			SetVertScrollCode ((UDROP_INSETTOP & uiRet) ? SB_LINEUP : SB_LINEDOWN);
		}
	} 
	
// Only change the last time if ALL scrolling stops.
	if (GetHorzScrollCode() == UINT_MAX && GetVertScrollCode() == UINT_MAX)
		ResetLastTime();

// Set the scroll effect on any inset hit.
	if (uiRet & UDROP_INSET)
		*pdwEffect |= DROPEFFECT_SCROLL;

// Has the delay elapsed?  We can scroll if so
	if (0 != GetLastTime() && (GetTickCount() - GetLastTime()) > g_dwScrollDelay) {
#if defined(_DUMP)
		OutputDebugString ("Drop: Ausblenden\r\n");
#endif // _DUMP

	// alten Einfügepunkt ausblenden
		m_pBack -> GiveFeedBack (NULL, true);

		if (UINT_MAX != GetHorzScrollCode())
			m_pWnd -> ForwardEvent(WM_HSCROLL, GetHorzScrollCode());

		if (UINT_MAX != GetVertScrollCode()) 
			m_pWnd -> ForwardEvent(WM_VSCROLL, GetVertScrollCode());

	// Einblenden übernimmt Expose
		m_pBack -> GiveFeedBack (&pt, false, false);
	} else {
	// Einfügepunkt korrigieren
#if defined(_DUMP)
		OutputDebugString ("Drop: Einblenden\r\n");
#endif // _DUMP
		m_pBack -> GiveFeedBack (&pt);
	}
	return S_OK;
}

STDMETHODIMP CViewDropTarget::DragLeave (void)
{
	TX_ASSERT(NULL != m_pBack);
	if (S_OK == m_pBack -> DragLeave())
		return NOERROR;			// Extensions befragen

// wenn das nicht für uns ist, dann weiter
	if (!m_DataSource.IsValid()) 
		return S_FALSE;

	if (!m_pBack -> IsDropSourceInst())		// aus anderer TRiAS-Instanz
		return S_FALSE;

// Stop scrolling
	SetHorzScrollCode (UINT_MAX);
	SetVertScrollCode (UINT_MAX);

// Einfügepunkt ausblenden
	m_pBack -> GiveFeedBack (NULL, true);
	m_DataSource.Assign(NULL);
	return S_OK;
}

STDMETHODIMP CViewDropTarget::Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);

	*pdwEffect = DROPEFFECT_NONE;	// richtig initialisieren
	if (S_OK == m_pBack -> Drop (pIDataSource, grfKeyState, pt, pdwEffect))
		return NOERROR;

// wenn das nicht für uns ist, dann weiter
	if (!m_DataSource.IsValid()) 
		return E_FAIL;

	if (!m_pBack -> IsDropSourceInst())		// aus anderer TRiAS-Instanz
		return S_FALSE;

// Daten einfügen
HRESULT hr = E_FAIL;

	if (m_pBack -> FPasteFromData (pIDataSource)) {	// erfolgreich eingefügt
		*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren

		hr = S_OK;
	}
		
// Stop scrolling
	SetHorzScrollCode (UINT_MAX);
	SetVertScrollCode (UINT_MAX);

// Einfügepunkt ausblenden
	m_pBack -> GiveFeedBack (NULL, true);
	m_DataSource.Assign (NULL);				// Daten werden nicht mehr benötigt
	return hr;	
}

#endif // !_OLD_DRAGNDROP

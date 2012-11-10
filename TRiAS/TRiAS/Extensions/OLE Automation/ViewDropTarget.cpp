// DropTarget für View-Fenster
// File: VIEWDROPTARGET.CPP

#include "precomp.hxx"

#include <dirisole.h>
#include "ViewDropTarget.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// *** IDropTarget interface members
STDMETHODIMP CViewDropTarget::DragEnter (
	IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pDoc);
	m_DataSource.Assign(NULL);		// alten DataSource löschen

// Testen, ob wird diese Daten verstehen
	if (!m_pDoc -> FQueryPasteFromData (pIDataSource)) 
		return S_FALSE;

// Testen, ob das hier ein gültiger Abwurfpunkt ist
UINT uiRet = m_pDoc -> TestDroppablePoint (&pt);

	if (IsSourceInstance()) 	// wir selbst brauchen keine unserer Objekte
		return S_FALSE;

	if (UDROP_NONE != uiRet) {
		if (grfKeyState & MK_RBUTTON) {	// Drag mit rechter Maus
			*pdwEffect |= DROPEFFECT_MOVE;	// kein besonderer Cursor
			*pdwEffect &= ~DROPEFFECT_COPY;
			m_uiButton = MK_RBUTTON;
		} else {
		// Kopieren ist default
			if (grfKeyState & MK_SHIFT) 
				*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
			else
				*pdwEffect |= DROPEFFECT_COPY;		// kopieren
			m_uiButton = MK_LBUTTON;
		}
	}

// DataSource festhalten, wird noch gebraucht
	m_DataSource = pIDataSource;
	return NOERROR;
}

STDMETHODIMP CViewDropTarget::DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pDoc);

	if (!m_DataSource.IsValid()) 			// war nichts für uns
		return S_FALSE;

	if (IsSourceInstance()) 	// wir selbst brauchen keine unserer Objekte
		return S_FALSE;

// noch mal DropPoint testen
UINT uiRet = m_pDoc -> TestDroppablePoint (&pt);

	if (UDROP_NONE != uiRet) {
		if (grfKeyState & MK_RBUTTON) {	// Drag mit rechter Maus
			*pdwEffect |= DROPEFFECT_MOVE;	// kein besonderer Cursor
			*pdwEffect &= ~DROPEFFECT_COPY;
		} else {	// wir selbst brauchen keine unserer Objekte
		// Kopieren ist default
			if (grfKeyState & MK_SHIFT) 
				*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
			else
				*pdwEffect |= DROPEFFECT_COPY;		// kopieren
		}
	}
	return NOERROR;
}

STDMETHODIMP CViewDropTarget::DragLeave (void)
{
	TX_ASSERT(NULL != m_pDoc);

	m_uiButton = 0;

// wenn das nicht für uns ist, dann weiter
	if (!m_DataSource.IsValid()) 
		return S_FALSE;

	m_DataSource.Assign(NULL);
	return NOERROR;
}

STDMETHODIMP CViewDropTarget::Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pDoc);

// wenn das nicht für uns ist, dann weiter
	if (!m_DataSource.IsValid()) 
		return E_FAIL;

// Daten einfügen
HRESULT hr = E_FAIL;

	if (IsSourceInstance())			// wir selbst brauchen keine unserer Objekte
		return S_FALSE;

HPROJECT hPr = HACTCONNECTION;
BOOL fShowORWnd = FALSE;

	*pdwEffect = DROPEFFECT_NONE;
	if (m_uiButton & MK_RBUTTON) {	// Drag mit rechter Maus
		hr = m_pExt -> TrackDragPopupMenuRight(&pt, pdwEffect, &hPr, &fShowORWnd);
		if (FAILED(hr)) {
			MessageBeep (-1);
			return hr;
		}
		if (*pdwEffect != DROPEFFECT_NONE &&
			m_pDoc -> FPasteFromData (pIDataSource, hPr, fShowORWnd)) 	// erfolgreich eingefügt
		{
			hr = S_OK;
		} 
		else
			hr = E_FAIL;

	} else if (m_uiButton & MK_LBUTTON) {
	BOOL fCopy = (grfKeyState & MK_SHIFT) ? FALSE : TRUE;

		hr = m_pExt -> TrackDragPopupMenuLeft (&pt, pdwEffect, &hPr, &fShowORWnd, fCopy);
		if (FAILED(hr)) {
			MessageBeep (-1);
			return hr;
		}
		if (*pdwEffect != DROPEFFECT_NONE &&
			m_pDoc -> FPasteFromData (pIDataSource, hPr)) 
		{	// erfolgreich eingefügt
		// Kopieren ist default
			if (fCopy) 
				*pdwEffect |= DROPEFFECT_COPY;		// kopieren
			else
				*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
			hr = S_OK;
		}
		else 
			hr = E_FAIL;
	}

	*pdwEffect &= ~DROPEFFECT_SHOWORWINDOW;		// internes Flag löschen
	m_DataSource.Assign (NULL);					// Daten werden nicht mehr benötigt
	return hr;	
}


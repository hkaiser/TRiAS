// Drag'n Drop für Objektrecherchefenster
// File: DDORWND.CPP

#include "triaspre.hxx"

#include "triasres.h"

#include <ospace/com/iterenum.h>
#include <ospace/std/algorithm>

#include <dirisole.h>
#include <eonrguid.h>
#include <funcs03.h>

#include "tenums.h"
#include "Strings.h"
#include "extmain3.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(DataObject);
DefineSmartInterface(DropSource);
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);		// WEnumLONG etc.

#include "DdORWnd.h"
#include "objowndr.hxx"

///////////////////////////////////////////////////////////////////////////////
// erstmal nicht immer Drag'n Drop erlauben
#if defined(_DEBUG)
static bool IsEnabledDragDrop (void) { return true; }
#else
static bool IsEnabledDragDrop (void)
{
//	if (DEX_QueryMode() & QMSysAdmin)
//		return true;

CRegKey regDD;		// testen, ob Drag'n Drop unterdrückt sein soll

	if (ERROR_SUCCESS != regDD.Open (HKEY_CURRENT_USER, g_cbRegConfig)) 
		return false;

DWORD dwDragDrop = 1L;

	if (ERROR_SUCCESS == regDD.QueryValue (dwDragDrop, g_cbEnableDragDrop) &&
		0 == dwDragDrop)
	{
		return false;
	}
	return true;
}
#endif //!_DEBUG

///////////////////////////////////////////////////////////////////////////////
// Funktionalität für ORFenster
HRESULT ObjektInfo::InitDragDrop (void)
{
// anlegen und registrieren des DropTargets
	m_pDropTgt = NULL;
	if (!IsEnabledDragDrop()) return S_OK;

	try {
	CComObject<CORWndDropTarget> *pTarget = NULL;
	HRESULT hr = CComObject<CORWndDropTarget>::CreateInstance(&pTarget);
	
		if (FAILED(hr)) _com_issue_error(hr);
		
		hr = pTarget -> QueryInterface (IID_IDropTarget, (LPVOID *)&m_pDropTgt);
		if (FAILED(hr)) _com_issue_error(hr);
		
		pTarget -> FInit (this);
		CoLockObjectExternal (m_pDropTgt, true, false);
		RegisterDragDrop (m_hWnd, m_pDropTgt);

	} catch (...) {
		TX_TRACE("TRiAS:Could not initialize DropTarget for ORWnd\n");
		// no target, no Drag'n Drop
	}
	return S_OK;
}

// DropTarget abmelden, wenn's noch nicht passiert ist
HRESULT ObjektInfo::RevokeDragDrop (void)
{
	if (NULL != m_pDropTgt) {
		::RevokeDragDrop (m_hWnd);
		CoLockObjectExternal (m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
		return S_OK;
	};
	return S_FALSE;
}

// Letzte Möglichkeit für die DatenQuelle den Drop doch noch zu verhindern
bool ObjektInfo::FQueryDrop (void)
{
	return true;
}

// Testen, ob Daten dabei sind, die wir gebrauchen können
bool ObjektInfo::FQueryPasteFromData (IDataObject *pIDataSource)
{
// nach EnumLONG mit Objektnummern fragen
HRESULT hr = GetEnumLONGData (pIDataSource);

	return SUCCEEDED(hr);
}

// Daten bei uns einfügen
bool ObjektInfo::FPasteFromData (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt)
{
// EnumLONG mit ObjektNummern aus DataSource holen
WEnumLONG EnumObj;
HRESULT hr = GetEnumLONGData (pIDataSource, EnumObj.ppi());

	if (FAILED(hr)) return false;

	if (grfKeyState & MK_LBUTTON)	// diese Objekte zu unserem Fenster hinzufügen
		return AddObjectsToWindow (EnumObj, m_iDropIndex);

	if (grfKeyState & MK_RBUTTON && IsDropSourceORWnd()) {
	Menu DDORWnd (IDR_DDORWND);
	HMENU hMenu = GetSubMenu(DDORWnd.Handle(), 0);

		SetMenuDefaultItem(hMenu, ID_DDORWND_UNION, FALSE);

	UINT uiCmd = TrackPopupMenu(hMenu, TPM_RETURNCMD|TPM_NONOTIFY, pt.x, pt.y, 0, m_hWnd, NULL);

		switch (uiCmd) {
		case ID_DDORWND_UNION_NEWWIN:
			return AddObjectsToNewWindow (EnumObj);

		case ID_DDORWND_INTERSECTION_NEWWIN:
			return BuildIntersectionInNewWindow (EnumObj);

		case ID_DDORWND_XOR_NEWWIN:
			return BuildXorInNewWindow (EnumObj);

		case ID_DDORWND_DIFFERENCE_NEWWIN:
			return BuildDifferenceInNewWindow (EnumObj);

		case ID_DDORWND_DIFFERENCE_INV_NEWWIN:
			return BuildInvDifferenceInNewWindow (EnumObj);

		default:
			break;		// abgebrochen
		}
	}
	return false;
}

// selektierte Objekte aus Fenster und evtl. aus GeoDB entfernen
bool ObjektInfo::ClipSelEntries (bool fDelete)
{
ResString resUndo (IDS_UNDOCLIPSELENTRIES, 128);

	DEX_BeginUndoLevel (resUndo.Addr());

int maxIndex = GetCount()-1;

	for (int i = maxIndex; i >= 0; i--) {		// von hinten, da gelöscht wird
		if (m_pKurzInfo->GetSelection (i)) {	// nur selektierte Objekte behandeln
		long lONr = (long)m_pKurzInfo -> GetItem (i);	// Eintrag holen

			TX_ASSERT(lONr > 0);
			HandleDeleteObject (lONr, false, true);			// aus Liste entfernen
		}
	}

	m_ulActCount = UpdateActivation();
	UpdateCaption();		// Caption richten
	DEX_EndUndoLevel();
	return true;
}

bool ObjektInfo::AddObjectsToWindow (IEnum<LONG> *pIEnumObj, int iIndex)
{
ResString resUndo (IDS_UNDOADDOBJECTS, 128);

	DEX_BeginUndoLevel (resUndo.Addr());

LONG lONr = 0;
int iFirst = iIndex;
int iNewIndex = iIndex;

	for (pIEnumObj->Reset(); S_OK == pIEnumObj->Next(1, &lONr, NULL); /**/)
	{
		TX_ASSERT(lONr != 0);

	// liefert S_FALSE, wenn Objekt schon drin ist
		if (S_OK == RetrieveObjInfo (lONr, iIndex, &iNewIndex, true))
			iIndex = iNewIndex+1;
	}

// alle neuen selektieren
	m_pKurzInfo -> ChangeSelected (Range (iFirst, iNewIndex));
	m_ulActCount = UpdateActivation();
	UpdateCaption();		// Caption richten

	DEX_EndUndoLevel();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein gültiger Abwurfpunkt vorliegt, bzw. ob gescrollt werden soll
UINT ObjektInfo::TestDroppablePoint (POINTL *pptl)
{
POINT pt;
RECT rcC;
UINT uiRet = UDROP_NONE;
HWND hCtrl = m_pKurzInfo->Handle(API_WINDOW_HWND);

	POINTFROMPOINTL (pt, *pptl);
	ScreenToClient (hCtrl, &pt);
	GetClientRect (hCtrl, &rcC);

// Check for at least a client area hit.
	if (PtInRect (&rcC, pt)) {
		uiRet = UDROP_CLIENT;

		pt.y = rcC.bottom-rcC.top-pt.y;

	BOOL fPastLast = false;
	int iIndex = m_pKurzInfo->IndexFromPoint ((Point &)pt, &fPastLast);

		if (0 == iIndex || iIndex == int(GetCount()-1) || fPastLast)
			return uiRet;	// nur scrollen wenn notwendig

	// Check vertical inset
		if (pt.y <= rcC.top + (int)g_dwScrollInset) {
			uiRet |= UDROP_INSETBOTTOM;
			TX_TRACE("TRiAS:InsetBottom\r\n");
		} else if (pt.y >= rcC.bottom - (int)g_dwScrollInset) {
			uiRet |= UDROP_INSETTOP;
			TX_TRACE("TRiAS:InsetTop\r\n");
		}
	}
	return uiRet;
}

// Einfügepunkt in Listbox kennzeichnen
bool ObjektInfo::GiveFeedBack (POINTL *pptl, bool fRemove, bool fPaint)
{
Rectangle rc = m_pKurzInfo -> CanvasRect();

// nur vorherige Einfügemarke entfernen
	if (fRemove) {
		DrawDropSelection (rc);
		m_iDropPos = -1;
		m_iDropIndex = -1;
		return true;
	}

// neue Einfügemarke erzeugen
Point pt (CoOrd(pptl -> x), CoOrd(pptl -> y));
CoOrd dY = rc.Top()-rc.Bottom();

	ScreenToClient (m_pKurzInfo->Handle(API_WINDOW_HWND), (POINT *)&pt);
	pt.Y() = dY - pt.Y();

	TX_TRACE1("TRiAS:Y-Koordinate: %ld\r\n", pt.Y());

Range r;
int iOrder = FindEntrySize (dY, pt, r);

	if (0 <= iOrder) {
	// Position der Einfügemarke bestimmen
		TX_TRACE1("TRiAS:DropIndex: %d\r\n", iOrder);
		TX_TRACE2("TRiAS:Range min: %ld, max: %ld\r\n", r.Min(), r.Max());

		if (pt.Y() > (r.Max()+r.Min())/2)
			pt.Y() = r.Max();
		else 
			pt.Y() = r.Min();

		TX_TRACE1("TRiAS:Korrigierte Y-Koordinate: %ld\r\n", pt.Y());

		if (pt.Y() != m_iDropPos) {
		// vorherige Einfügemarke entfernen
			if (fPaint && (-1 != m_iDropPos))
				DrawDropSelection (rc);
			
		// Einfügemarke zeichnen
			m_iDropIndex = iOrder;
			m_iDropPos = pt.Y();
			if (fPaint) 
				DrawDropSelection (rc);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Zeichnen des Einfügepunktes
const int DD = 2;	// Dicke der SelektionsLinie [Pixel]
HBRUSH WINAPI CreateInvBrush (void);

bool ObjektInfo::DrawDropSelection (Rectangle &rRc)
{
	if (m_iDropPos < 0) return false;
	
	if (NULL == m_hBr) {
	// Brush nur erzeugen, wenn er benötigt wird
		m_hBr = CreateInvBrush();
		if (m_hBr == NULL) {
			m_hBr = (HBRUSH)GetStockObject (GRAY_BRUSH);
			m_fBrushToDelete = false;
		} else
			m_fBrushToDelete = true;
	}
	if (m_fBrushToDelete)		// nur für geladenen Brush
		UnrealizeObject (m_hBr);

int iPos = rRc.Top()-rRc.Bottom()-m_iDropPos;
HWND hCtrl = m_pKurzInfo->Handle(API_WINDOW_HWND);
HDC hDC = GetDC (hCtrl);
HBRUSH hBrush = (HBRUSH)SelectObject (hDC, m_hBr);

	PatBlt (hDC, rRc.Left()+DD, iPos-DD/2, 
			rRc.Right()-rRc.Left()-2*DD, DD, PATINVERT);

	PatBlt (hDC, rRc.Left()+DD, iPos-3*DD,
				 DD, 6*DD, PATINVERT);
	PatBlt (hDC, rRc.Right()-2*DD, iPos-3*DD,
				 DD, 6*DD, PATINVERT);

	SelectObject (hDC, hBrush);
	ReleaseDC (hCtrl, hDC);
	return true;
}

int ObjektInfo::FindEntrySize (CoOrd dY, Point pt, Range &rR)
{
BOOL fPastLast = false;
int iDropIndex = m_pKurzInfo->IndexFromPoint (pt, &fPastLast);

	if (0 >= iDropIndex && fPastLast) 
		iDropIndex = GetCount();

	if (0 <= iDropIndex) {
	RECT rc;

		ListBox_GetItemRect (m_pKurzInfo->Handle(API_WINDOW_HWND), iDropIndex, &rc);
		rR.Min() = dY-rc.bottom;
		rR.Max() = dY-rc.top;
	} else {
		rR.Min() = rR.Max() = dY;
		iDropIndex = 0;
	}
	return iDropIndex;
}

///////////////////////////////////////////////////////////////////////////////
// Messages von der ListBox
LRESULT ObjektInfo::OnNotify (WPARAM, LPARAM lParam)
{
NM_LISTBOX *pNMData = (NM_LISTBOX *)lParam;

	if (IDL_OBJEKTE != pNMData->hdr.idFrom)
		return false;		// nicht von unserer ListBox

	if (!IsEnabledDragDrop()) return false;

	switch (pNMData -> hdr.code) {
	case LBN_BEGINDRAG:		// DragDrop mit linker Maustaste
		return DoDragDropAction (MK_LBUTTON);

	case LBN_BEGINRDRAG:	// DragDrop mit rechter Maustaste
		return DoDragDropAction (MK_RBUTTON);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// DragDrop initialisieren und auslösen
HRESULT ObjektInfo::DoDragDropAction (DWORD dwFlags)
{
// Erzeugen und Füllen des DataObjektes
WDataObject DataObj;
WDropSource DropSrc;
WEnumLONG EnumObj;

	try {
		DataObj = WDataObject(CLSID_DataTransferObject);	// Erzeugen des DataObjektes
		if (!CreateObjEnumerator (EnumObj.ppi(), ENUMOBJECTTYPE_ACTIVATED, (DWORD)(void *)hWnd()))
		{
			_com_issue_error(E_OUTOFMEMORY);
		}
		THROW_FAILED_HRESULT(SetEnumLONGData (EnumObj, DataObj));

	CComObject<CORWndDropSource> *pSource = NULL;	// Erzeugen der DropSource

		THROW_FAILED_HRESULT(CComObject<CORWndDropSource>::CreateInstance(&pSource));
		THROW_FAILED_HRESULT(pSource -> QueryInterface (IID_IDropSource, DropSrc.ppv()));
		
		pSource -> FInit (this, dwFlags);

	} catch (_com_error& hr) {	
		return _COM_ERROR(hr);
	} catch (...) {
		return E_FAIL;
	}

// Eigentliches DragDrop
ResString resUndo (IDS_UNDODRAGDROPOBJECTS, 128);
DWORD dwEffect = 0L;

// Erweiterungen eine Chance geben, ihren Senf dazuzugeben
HRESULT hr = EL().BeginDragDrop (DRAGDROPTYPE_ORWINDOW, hWnd(), dwFlags, DataObj);

	if (FAILED(hr)) return hr;

	DEX_BeginUndoLevel (resUndo.Addr());

	m_fIsDropTarget = false;
	m_fIsDropSource = true;
	hr = ::DoDragDrop (DataObj, DropSrc, DROPEFFECT_MOVE|DROPEFFECT_COPY, &dwEffect);
	m_fIsDropSource = false;	

	if (SUCCEEDED(hr) && DRAGDROP_S_DROP == GetScode(hr)) 	{
	// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
	bool fIsDropSourceInst = IsDropSourceInst();

		EL().EndDragDrop (DRAGDROPTYPE_ORWINDOW, hWnd(), dwEffect);

		if (DROPEFFECT_MOVE == dwEffect && !m_fIsDropTarget) {
			ClipSelEntries();				// selektierte Objekte rausnehmen
			if (!fIsDropSourceInst)
				DeleteDroppedObjects(EnumObj);		// Objekte wirklich löschen (Verschieben)
		}

		m_fIsDropTarget = false;
		DEX_EndUndoLevel();
		return S_OK;
	}

// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
	EL().EndDragDrop (DRAGDROPTYPE_ORWINDOW, hWnd(), DROPEFFECT_NONE);

	m_fIsDropTarget = false;
	DEX_CancelUndoLevel(true);		// abgebrochen oder Fehler
	return hr;
}

// sämtliche in einer anderen TRiAS-Instanz fallengelassenen Objekte hier löschen
bool ObjektInfo::DeleteDroppedObjects(IEnum<LONG> *pIEnum)
{
INT_PTR lONr = NULL;

	for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) 
		DEX_DeleteObjectEx(lONr);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionalität für Erweiterungen
HRESULT ObjektInfo::DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return EL().DragEnter (DRAGDROPTYPE_ORWINDOW, hWnd(), pIDataSource, grfKeyState, pt, pdwEffect); 
}

HRESULT ObjektInfo::DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return EL().DragOver (DRAGDROPTYPE_ORWINDOW, hWnd(), grfKeyState, pt, pdwEffect); 
}

HRESULT ObjektInfo::DragLeave (void)
{ 
	return EL().DragLeave(DRAGDROPTYPE_ORWINDOW, hWnd()); 
}

HRESULT ObjektInfo::Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return EL().Drop (DRAGDROPTYPE_ORWINDOW, hWnd(), pIDataSource, grfKeyState, pt, pdwEffect); 
}

///////////////////////////////////////////////////////////////////////////////
// DropSourceObject für ObjektRechercheFenster
bool CORWndDropSource::FInit (ObjektInfo *pBack, DWORD grfMouse)
{
	TX_ASSERT(NULL != pBack);
	
	m_pBack = pBack;
	m_dwFlags = grfMouse;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// *** IDropSource interface members
STDMETHODIMP CORWndDropSource::QueryContinueDrag (BOOL fEsc, DWORD grfKeyState)
{
	TX_ASSERT(NULL != m_pBack);
	TX_ASSERT(0L != m_dwFlags);

	if (fEsc) return DRAGDROP_S_CANCEL;

	if (!(grfKeyState & m_dwFlags)) {
		if (m_pBack -> FQueryDrop()) 
			return DRAGDROP_S_DROP;
		else
			return DRAGDROP_S_CANCEL;
	}
	return S_OK;
}

STDMETHODIMP CORWndDropSource::GiveFeedback (DWORD dwEffect)
{
	return DRAGDROP_S_USEDEFAULTCURSORS;
}

///////////////////////////////////////////////////////////////////////////////
// DropTargetObject für ObjektRechercheFenster
bool CORWndDropTarget::FInit (ObjektInfo *pBack)
{
	TX_ASSERT(NULL != pBack);
	
	m_pBack = pBack;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// *** IDropTarget interface members
STDMETHODIMP CORWndDropTarget::DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);
	m_DataObject.Assign(NULL);		// für alle Fälle
	
// erstmal alle Erweiterungen befragen
	*pdwEffect = DROPEFFECT_NONE;

	if (S_OK == m_pBack -> DragEnter (pIDataSource, grfKeyState, pt, pdwEffect))
		return S_OK;		// abgearbeitet

// Testen, wir diese Daten verstehen bzw.
// wenns aus einer anderen TRiAS Instanz kommt erstmal ablehnen
	if (!m_pBack->IsDropSourceInst() || !m_pBack -> FQueryPasteFromData (pIDataSource)) 
	{
	// diese Daten sind nicht für uns
		*pdwEffect = DROPEFFECT_NONE;
		return S_OK;
	}

// Check if this is a valid drop point.
UINT uiRet = m_pBack -> TestDroppablePoint(&pt);
	
	SetLastTest (uiRet);
	if (uiRet != UDROP_NONE) {
		if (m_pBack -> IsDropSource()) {	// wir selbst brauchen keine unserer Objekte
			*pdwEffect |= DROPEFFECT_MOVE;	// aber Cursor soll normal aussehen
		} else {
		// Verschieben nur zulassen, wenn aus anderem ORFenster
			if (m_pBack -> IsDropSourceORWnd()) {
				*pdwEffect |= DROPEFFECT_MOVE;
				if (grfKeyState & MK_CONTROL)
					*pdwEffect |= DROPEFFECT_COPY;
			} else {
			// ansonsten immer kopieren
				*pdwEffect |= DROPEFFECT_COPY;
			}
		}
	}
			
// Daten festhalten
	m_DataObject = pIDataSource;

// vollständiges Anzeigen des ORWnd's
	m_pBack -> ToTop();
	m_pBack -> Update();
	
	if (!m_pBack -> IsDropSource()) {
	// Scrollen initialisieren
		SetVertScrollCode (UINT_MAX);
		
	// Einfügepunkt anzeigen
		m_pBack -> GiveFeedBack (&pt);
	}
	return S_OK;
}

STDMETHODIMP CORWndDropTarget::DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);

// erstmal alle Erweiterungen befragen
	*pdwEffect = DROPEFFECT_NONE;
	if (S_OK == m_pBack -> DragOver (grfKeyState, pt, pdwEffect))
		return S_OK;		// abgearbeitet

// ab hier ist wieder TRiAS selbst verantwortlich
	if (!m_pBack->IsDropSourceInst() || NULL == (IDataObject *)m_DataObject) 
	{			// war nichts für uns
		*pdwEffect = DROPEFFECT_NONE;
		return S_OK;
	}

// noch mal DropPoint testen
UINT uiRet = m_pBack -> TestDroppablePoint (&pt);

	if (UDROP_NONE == uiRet)
		*pdwEffect = DROPEFFECT_NONE;
	else {
		*pdwEffect = DROPEFFECT_NONE;

		if (m_pBack -> IsDropSource()) {	// wir selbst brauchen keine unserer Objekte
			*pdwEffect |= DROPEFFECT_MOVE;	// aber Cursor soll normal aussehen
		} else {
		// Verschieben nur zulassen, wenn aus anderem ORFenster
			if (m_pBack -> IsDropSourceORWnd()) {
				*pdwEffect |= DROPEFFECT_MOVE;
				if (grfKeyState & MK_CONTROL)
					*pdwEffect |= DROPEFFECT_COPY;
			} else {
			// ansonsten immer kopieren
				*pdwEffect |= DROPEFFECT_COPY;
			}
		}
	}

UINT uiLast = GetLastTest();

	SetLastTest (uiRet);				// alten Wert speichern

	if (m_pBack -> IsDropSource()) 
		return S_OK;					// nicht im eigenen Fenster

	m_dwLastKeyState = grfKeyState;
	if (uiRet == UDROP_NONE) {
		SetVertScrollCode (UINT_MAX);
		m_pBack -> GiveFeedBack (&pt);	// Einfügepunkt korrigieren
		return S_OK;
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
		if ((uiLast & UDROP_INSETVERT) && !(uiRet & UDROP_INSETVERT))
			SetVertScrollCode (UINT_MAX);
	
		if (!(uiLast & UDROP_INSETVERT) && (uiRet & UDROP_INSETVERT)) {
			SetLastTime (GetTickCount());
			SetVertScrollCode ((UDROP_INSETTOP & uiRet) ? SB_LINEUP : SB_LINEDOWN);
		}
	} 
	
// Only change the last time if ALL scrolling stops.
	if (GetVertScrollCode() == UINT_MAX)
		ResetLastTime();

// Set the scroll effect on any inset hit.
	if (uiRet & UDROP_INSET)
		*pdwEffect |= DROPEFFECT_SCROLL;

// Has the delay elapsed?  We can scroll if so
	if (0 != GetLastTime() && (GetTickCount() - GetLastTime()) > GetScrollDelay())
	{
	// alten Einfügepunkt ausblenden
		m_pBack -> GiveFeedBack (NULL, true);

		if (UINT_MAX != GetVertScrollCode()) 
			SendMessage (m_pBack -> Handle(API_WINDOW_HWND), WM_VSCROLL, GetVertScrollCode(), 0L);
	}

// Einfügepunkt korrigieren/wieder anzeigen
	m_pBack -> GiveFeedBack (&pt);
	return S_OK;
}

STDMETHODIMP CORWndDropTarget::DragLeave (void)
{
	TX_ASSERT(NULL != m_pBack);
	if (S_OK == m_pBack -> DragLeave())
		return S_OK;			// Extensions befragen

// wenn das nicht für uns ist, dann weiter
	if (!m_pBack->IsDropSourceInst() || !m_DataObject.IsValid()) 
		return S_OK;

	SetVertScrollCode (UINT_MAX);			// Stop scrolling
	m_pBack -> GiveFeedBack (NULL, true);	// Einfügepunkt ausblenden
	m_DataObject.Assign(NULL);
	m_dwLastKeyState = 0;
	return S_OK;
}

STDMETHODIMP CORWndDropTarget::Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	TX_ASSERT(NULL != m_pBack);

	*pdwEffect = DROPEFFECT_NONE;	// richtig initialisieren
	if (S_OK == m_pBack -> Drop (pIDataSource, grfKeyState, pt, pdwEffect))
		return S_OK;

// wenn das nicht für uns ist, dann weiter
	if (!m_pBack->IsDropSourceInst() || NULL == (IDataObject *)m_DataObject) 
		return E_FAIL;

// Daten einfügen
	if (!m_pBack -> IsDropSource())	{		// wir selbst brauchen keine unserer Objekte
		if (m_pBack -> FPasteFromData (pIDataSource, m_dwLastKeyState, pt)) {	// erfolgreich eingefügt
		// Verschieben nur zulassen, wenn aus anderem ORFenster
			if (m_pBack -> IsDropSourceORWnd()) {
				*pdwEffect |= DROPEFFECT_MOVE;
				if (grfKeyState & MK_CONTROL)
					*pdwEffect |= DROPEFFECT_COPY;

			// D&D mit rechter Maus aus anderem ORWnd läßt source immer unberührt ('copy')
				if (m_dwLastKeyState & MK_RBUTTON)
					*pdwEffect |= DROPEFFECT_COPY;
			} else {
			// ansonsten immer kopieren
				*pdwEffect |= DROPEFFECT_COPY;
			}
		}
		m_pBack -> IsDropTarget(true);			// dieses Fenster ist DropTarget
	}
			
	SetVertScrollCode  (UINT_MAX);				// Stop scrolling
	if (!m_pBack -> IsDropSource()) 
		m_pBack -> GiveFeedBack (NULL, true);	// Einfügepunkt ausblenden
	m_DataObject.Assign (NULL);					// Daten werden nicht mehr benötigt

	return S_OK;	
}


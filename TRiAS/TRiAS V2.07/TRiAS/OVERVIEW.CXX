// Uebersichtsanzeige der aktuellen Datenbank ---------------------------------
// File: OVERVIEW.CXX

#include "triaspre.hxx"
#include "triasres.h"

#include "overview.h"

#include "Strings.h"
#include "shiftovw.hxx"
#include "overview.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// #define ENUMENHMETAFILE
// #define CREATEPALETTE
#if defined(_DEBUG)
#define COPYTOCLIPBOARD
#endif //_DEBUG

extern HINSTANCE hInstance;
extern Bool OverViewCFlag;

// Anlegen und Anzeigen des Fensters ------------------------------------------
COverView *COverView::CreateOverView (
	pWindow pW, ObjContainer &ocDB, bool fInitNew, Point ptAspect, double dRatio)
{
COverView *pOV = new COverView (pW, ptAspect, dRatio);

	if (pOV == NULL || !pOV -> FInit (ocDB, fInitNew)) {
		DELETE (pOV);
		return NULL;
	}

	pOV -> Show();
	pW -> SetFocus();
	pOV -> FInitCursor();
	return pOV;
}
		
		
// Konstruktor/Destruktor/Initialisierung -------------------------------------
COverView :: COverView (pWindow pW, Point ptAspect, double dRatio)
	   : DialogWindow (pW, OVERVIEWDIALOG, false),	// ModeLess
	     m_ptAspect(ptAspect), m_dRatio(dRatio)
{
// alles initialisieren
	m_hMF = 0;
#if defined(WIN32)
	m_hPal = NULL;
#endif // WIN32

	memset (&m_ocDB, '\0', sizeof(RECTL));
	m_dimWnd = Dimension (0, 0);
	m_dY = 0;

	m_dAspect = 1.0;
	m_ixExt = 0;
	m_iyExt = 0;

	m_fBrushChanged = false;
	m_pBr = NULL;
	
	m_prcActVP = NULL;
	m_prcSel = NULL;
	
	m_fLeftBttnSem = false;

	m_fPointerChanged = false;
	m_pOldPointer = NULL;
	m_pLupe = NULL;
	m_pMove = NULL;

	m_fToDelete = false;
	m_fIsDirty = false;

	m_hSubMenu = NULL;

// Menupunkte eines Fensters mit SysMenu entfernen
HMENU hSysMenu = ::GetSystemMenu (Handle(API_WINDOW_HWND), false);

	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}


COverView :: ~COverView (void)
{
	if (m_hMF) {
#if defined(WIN32)
		if (m_fIsDirty)
			SaveEnhMetaFile (g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);	// jetzt freigeben
#else
		DeleteMetaFile (m_hMF);
#endif // WIN32
		m_hMF = 0;
	}
#if defined(WIN32)
	if (NULL != m_hPal) {
		DeleteObject (m_hPal);
		m_hPal = NULL;
	}
#endif // WIN32

	if (m_fBrushChanged) {
		m_pBr = ChangeBackground (m_pBr);
		DELETE (m_pBr);
	}
	if (m_fPointerChanged)
		ChangePointer (m_pOldPointer);

	DELETE (m_pMove);
	DELETE (m_pLupe);
		
	DELETE (m_prcActVP);
	DELETE (m_prcSel);
}

bool COverView::SaveOverview (LPCSTR pcName)
{
	if (m_hMF) {
#if defined(WIN32)
		if (m_fIsDirty)
			SaveEnhMetaFile (NULL != pcName ? pcName : g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);	// jetzt freigeben
#else
		DeleteMetaFile (m_hMF);
#endif // WIN32
		m_hMF = 0;
		return true;
	}

	return false;
}

void COverView :: FInitCursor (void)		// nur Cursor wechseln
{
	if (m_pLupe) {
		m_fPointerChanged = TRUE;
		m_pOldPointer = ChangePointer (m_pLupe);
	}
}

BOOL COverView::FInit (ObjContainer &ocGeoDB, bool fInitNew)
{
CEierUhr Wait (GetParent());	// SandUhr anzeigen

// grauen Hintergrund einstellen
	m_pBr = new Brush (Color ((ColorVal)192, (ColorVal)192, (ColorVal)192));
	if (m_pBr) {
		m_pBr = ChangeBackground (m_pBr);
		m_fBrushChanged = TRUE;
	}
	
// Pointer anlegen
	m_pLupe = new Pointer (ResID(LUPECURSOR));
	m_pMove = new Pointer (ResID(MOVECURSOR));

// DatenbankContainer speichern, Aspekt berechnen
	m_ocDB.left = ocGeoDB.XMin();
	m_ocDB.right = ocGeoDB.XMax();
	m_ocDB.bottom = ocGeoDB.YMin();
	m_ocDB.top = ocGeoDB.YMax();
	
long dX = m_ocDB.right - m_ocDB.left;
long dY = m_ocDB.top - m_ocDB.bottom;

	m_dAspect = (double(dY) / double(dX)) * (double(m_ptAspect.Y()) / double(m_ptAspect.X()));
	m_dAspect /= m_dRatio;

// ringsherum je 5% zugeben
	dX /= 20;
	dY /= 20;
	m_ocDB.left -= dX;
	m_ocDB.right += dX;
	m_ocDB.bottom -= dY;
	m_ocDB.top += dY;

// Fenster positionieren und Größe einstellen
Rectangle rcC = GetParent() -> CanvasRect();

	m_dimWnd.Width() = (rcC.Right()-rcC.Left()) / 4;
	m_dimWnd.Height() = short(m_dimWnd.Width() * m_dAspect);
	ChangeSize (m_dimWnd);
	
// links oben positionieren
Rectangle rcW = WindowRect();

	ChangePosition (Point (0, rcC.Top()-rcC.Bottom() -
				  (rcW.Top() - rcW.Bottom())));	

// MetaFile besorgen
	rcC = CanvasRect();

#if defined(WIN32)
	if (!fInitNew)		// versuchen neu zu laden
		LoadEnhMetaFile(g_cbDefaultPict);

	if (NULL == m_hMF && !RetrieveActViewMetaFile (rcC))
		return false;
#else
HGLOBAL hMFP = (HGLOBAL)RetrieveMetaFile (Handle(), rcC, m_ocDB, MM_ISOTROPIC);

	if (!hMFP) return FALSE;
	
METAFILEPICT *lpMFP = (METAFILEPICT *)GlobalLock (hMFP);

	if (lpMFP != NULL) {
		m_ixExt = lpMFP -> xExt;
		m_iyExt = lpMFP -> yExt;
		m_hMF = lpMFP -> hMF;
		
	// die METAFILEPICT-Struktur wird nicht mehr gebraucht, 
	// das Metafile gehört uns
		GlobalUnlock (hMFP);
		GlobalFree (hMFP);
	} else {
		GlobalFree (hMFP);
		return FALSE;
	}
#endif // WIN32
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// MetaFile für aktuelle Ansicht besorgen
bool COverView::RetrieveActViewMetaFile (Rectangle &rcC)
{
	if (NULL != m_hMF) {
		if (m_fIsDirty)
			SaveEnhMetaFile (g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);	// jetzt freigeben
		m_hMF = NULL;
	}

	m_hMF = RetrieveMetaFile (Handle(), rcC, m_ocDB, MM_ISOTROPIC);
	if (NULL == m_hMF) return false;

	m_fIsDirty = true;		// neues MetaFile

ENHMETAHEADER EMH;

	EMH.iType = EMR_HEADER;
	EMH.nSize = sizeof(ENHMETAHEADER);
	GetEnhMetaFileHeader (m_hMF, sizeof(ENHMETAHEADER), &EMH);

	m_ixExt = EMH.szlMillimeters.cx;
	m_iyExt = EMH.szlMillimeters.cy;

#if defined(CREATEPALETTE)
UINT uiPalEntries = GetEnhMetaFilePaletteEntries (m_hMF, 0, NULL);

	if (uiPalEntries) {
	LPLOGPALETTE pPal = NULL;
	
		ATLTRY(pPal = (LPLOGPALETTE) new char[sizeof(LOGPALETTE) + (sizeof (PALETTEENTRY) * uiPalEntries)]);
		if (NULL == pPal) return FALSE;
		pPal->palVersion = 0x300;
		pPal->palNumEntries = uiPalEntries;
		GetEnhMetaFilePaletteEntries (m_hMF, uiPalEntries, pPal->palPalEntry);
		m_hPal = CreatePalette (pPal);

		delete pPal;
		if (NULL == m_hPal) return FALSE;

	} else
		m_hPal = NULL;		// keine Palette
#endif // CREATEPALETTE

#if defined(COPYTOCLIPBOARD)
	OpenClipboard(Handle(API_WINDOW_HWND));
	EmptyClipboard();
	SetClipboardData (CF_ENHMETAFILE, (HANDLE)CopyEnhMetaFile (m_hMF, NULL));
	CloseClipboard();
#endif // COPYTOCLIPBOARD
	return true;
}

// Aktuellen Bildausschnitt anzeigen ------------------------------------------
void COverView :: SetActVP (ObjContainer &ocNewVP)
{
HWND hWnd = Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
int iOldRop = SetROP2 (hDC, R2_XORPEN);
HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));

	hP = (HPEN)SelectObject (hDC, hP);
	if (m_prcActVP) {
	// altes Rechteck löschen
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);
	} else 
		m_prcActVP = new RECT;

	if (m_prcActVP) {
	// neues Rechteck zeichnen
		SetRect (m_prcActVP, xDBtoCV (ocNewVP.XMin()),
				     yDBtoCV (ocNewVP.YMin()),
				     xDBtoCV (ocNewVP.XMax()),
				     yDBtoCV (ocNewVP.YMax()));
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);
				
	// neue DBAusschnitts-Ausdehnungen merken
		m_dDBx = ocNewVP.XMax() - ocNewVP.XMin();
		m_dDBy = ocNewVP.YMax() - ocNewVP.YMin();
	}

	DeleteObject (SelectObject (hDC, hP));
	SetROP2 (hDC, iOldRop);
	ReleaseDC (hWnd, hDC);
}

void COverView :: ResetActVP (BOOL fFreeSel)
{
	if (m_prcActVP) {
	// altes Rechteck löschen
	HWND hWnd = Handle (API_WINDOW_HWND);
	HDC hDC = ::GetDC (hWnd);
	int iOldRop = SetROP2 (hDC, R2_XORPEN);
	HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	
		hP = (HPEN)SelectObject (hDC, hP);
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);

		if (fFreeSel) {
			delete m_prcActVP;
			m_prcActVP = NULL;
		}
		DeleteObject (SelectObject (hDC, hP));
		SetROP2 (hDC, iOldRop);
		ReleaseDC (hWnd, hDC);
	}
}

#if defined(WIN32)
#if defined(ENUMENHMETAFILE)
int CALLBACK DrawEnhMetaRecord (HDC hDC, HANDLETABLE *pHT, ENHMETARECORD *pMR, int cObj, LPARAM eData)
{
	PlayEnhMetaFileRecord (hDC, pHT, pMR, cObj);

/*	if (pMR -> iType == EMR_SETWINDOWEXTEX) {
	//
	// Die Funktion SetViewportExtEx soll erst nach SetWindowExtEx gerufen 
	// werden, um eine bestmögliche Platzaufteilung im Fenster zu 
	// ermöglichen. SetWindowExt wird aber erst im Metafile selbst gerufen. 
	// Folglich dieser hack gleich an der Stelle.
	//
	Rectangle *prcC = (Rectangle *)eData;

		SetViewportOrgEx (hDC, (prcC -> Right() - prcC -> Left())/2, (prcC -> Top() - prcC -> Bottom())/2, NULL);
		SetViewportExtEx (hDC, prcC -> Right() - prcC -> Left(), 
							   prcC -> Top() - prcC -> Bottom(),
						  NULL);
	} 
*/	
	App :: Exec (ExecWhileEvent);			// be a good windows app
	return TRUE;	// immer weiter machen
}
#endif // ENUMENHMETAFILE

#else

extern "C" 
int WINAPI EXPORTTRIAS DrawMetaRecord (HDC hDC, HANDLETABLE *pHT, 
				    METARECORD *pMR, int cObj, LPARAM eData)
{
static BOOL m_fwasCreateRegion = FALSE;

	if (pMR -> rdFunction == META_CREATEREGION) {
		m_fwasCreateRegion = TRUE;
	} else if (pMR -> rdFunction == META_SELECTOBJECT && m_fwasCreateRegion) {
	Rectangle *prcC = (Rectangle *)eData;
	
		m_fwasCreateRegion = FALSE;
	//
	// Die Funktion SetViewportExt soll erst nach SetWindowExt gerufen 
	// werden, um eine bestmögliche Platzaufteilung im Fenster zu 
	// ermöglichen. SetWindowExt wird aber erst im Metafile selbst gerufen. 
	// Folglich dieser hack gleich mit an der Stelle, wo die ClippingRegion 
	// ausgeblendet wird.
	//
		SetViewportExtEx (hDC, prcC -> Right() - prcC -> Left(), 
				     -(prcC -> Bottom() - prcC -> Top()), NULL);
		return TRUE;
	}
		
	PlayMetaFileRecord (hDC, pHT, pMR, cObj);
	App :: Exec (ExecWhileEvent);			// be a good windows app

return TRUE;	// immer weiter machen
}
#endif // !WIN32

///////////////////////////////////////////////////////////////////////////////
// EventHandler 
void COverView :: Expose (ExposeEvt e)	// neu zeichnen
{
	if (!m_hMF) return;	// no picture, no fun

CEierUhr Wait (GetParent());
HWND hWnd = Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);

	SendMessage (hWnd, WM_ERASEBKGND, (WPARAM)hDC, 0L);	// Hintergrund löschen
	
	SaveDC (hDC);
	SetMapMode (hDC, MM_TEXT);

#if defined(WIN32)
HPALETTE hOldPal = NULL;

	if (NULL != m_hPal) {
		hOldPal = SelectPalette (hDC, m_hPal, FALSE);
		RealizePalette(hDC);
	}

RECT rcC, rcOrg;

	GetClientRect (hWnd, &rcC);
	rcOrg = rcC;

// ringsherum je 5% zugeben
	InflateRect (&rcC, -(rcC.right - rcC.left)/20, -(rcC.bottom - rcC.top)/20);

// evtl. Koordinatensystem kippen
	SetMapMode (hDC, MM_ISOTROPIC);
	SetWindowExtEx (hDC, rcC.right-rcC.left, rcC.bottom-rcC.top, NULL);

	if (IsWin40() && !IsWinNT()) {
	// Win95 stellt aus unbekannten Gründen das Metafile auf den Kopf
	long dX = (rcC.right - rcC.left) - (rcOrg.right - rcOrg.left);
	long dY = (rcC.bottom - rcC.top) - (rcOrg.bottom - rcOrg.top);

		SetViewportExtEx (hDC, rcC.right-rcC.left, -(rcC.bottom-rcC.top), NULL);
		SetViewportOrgEx (hDC, 0, (rcC.bottom-rcC.top)-dY, NULL);
	} else {
		SetViewportExtEx (hDC, rcC.right-rcC.left, rcC.bottom-rcC.top, NULL);
		SetViewportOrgEx (hDC, 0, 0, NULL);
	}

#if defined(ENUMENHMETAFILE)
	EnumEnhMetaFile (hDC, m_hMF, (ENHMFENUMPROC)DrawEnhMetaRecord, NULL, &rcC);
#else
	PlayEnhMetaFile (hDC, m_hMF, &rcC);
#endif // ENUMENHMETAFILE

	if (NULL != m_hPal) SelectPalette (hDC, hOldPal, FALSE);

#else
MFENUMPROC pDrawMetaRecord = (MFENUMPROC)MakeProcInstance ((FARPROC)DrawMetaRecord, hInstance);
Rectangle rcC = CanvasRect();

	EnumMetaFile (hDC, m_hMF, pDrawMetaRecord, (LPARAM)&rcC);
	FreeProcInstance ((FARPROC)pDrawMetaRecord);	
#endif // WIN32
	
	RestoreDC (hDC, -1);

	if (m_prcActVP) {	// aktuellen Ausschnitt Kennzeichnen (DeviceCoords)
	int iOldRop = SetROP2 (hDC, R2_XORPEN);
	
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);
		SetROP2 (hDC, iOldRop);
	}

	ReleaseDC (hWnd, hDC);
	DialogWindow :: Expose (e);		// StandardHandler rufen
}

BOOL HitTest (RECT *prc, Point &pt)
{
	if (pt.X() < prc -> left || pt.X() >= prc -> right) return FALSE;
	if (pt.Y() < prc -> bottom || pt.Y() >= prc -> top) return FALSE;
	
return TRUE;
}

void COverView :: MouseButtonDn (MouseEvt e)
{
	if (!e.isLeftButton() || m_fLeftBttnSem) 
		return;		// nur linke Taste
	m_fLeftBttnSem = TRUE;
	MouseTrap (On);
	
// in Abhängigkeit, ob Selektion getroffen wurde, verschiedene Wege gehen
Point ptM (e.Where().X(), m_dY - e.Where().Y());

	DELETE (m_prcSel);	 	// für alle Fälle
	if (m_prcActVP && HitTest (m_prcActVP, ptM)) {
	// aktuelle Selektion verschieben
		m_prcSel = new SelectionRectangle (ptM, *m_prcActVP);
	} else {
	// neuen Bereich aufziehen
		m_prcSel = new DragRectangle (ptM);
	}
	ResetActVP ();				// evtl. alte Selektion löschen
	
	if (m_prcSel) Draw (m_prcSel);		// erstmalig zeichnen
}

void COverView :: MouseButtonUp (MouseEvt e)
{
	if (e.isRightButton() && !m_fLeftBttnSem) {
		TrackOverviewMenu (e.Where());
		return;
	}

	if (!e.isLeftButton() || !m_fLeftBttnSem || m_prcSel == NULL) 
		return;		// nur linke Taste

	if (m_prcSel) Draw (m_prcSel);		// letztmalig zeichnen
	
// neuen DBAusschnitt einstellen
Rectangle rcR = m_prcSel -> newRect();
ObjContainer OC;

	if (m_prcSel -> isA() == SELRECT_NEWRECT) {
		OC.XMin() = xCVtoDB(rcR.Left());
		OC.XMax() = xCVtoDB(rcR.Right());
		OC.YMin() = yCVtoDB(rcR.Top());
		OC.YMax() = yCVtoDB(rcR.Bottom());
	} else {
		OC.XMin() = xCVtoDB(rcR.Left());
		OC.XMax() = OC.XMin() + m_dDBx;
		OC.YMin() = yCVtoDB(rcR.Top());
		OC.YMax() = OC.YMin() + m_dDBy;
	}
		 
	DELETE (m_prcSel);	// Selektionsrechteck freigeben
	DEX_SetActiveSightContainer (OC);
	DEX_RePaint();

	MouseTrap (Off);
	m_fLeftBttnSem = FALSE;
}


void COverView :: MouseDrag (MouseEvt e)
{
	if (!m_fLeftBttnSem || m_prcSel == NULL) 
		return;	// nur wenn linke Taste gedrückt ist

// DragRechteck neu dimensionieren und neu zeichen
Point ptM (e.Where().X(), m_dY - e.Where().Y());

	Draw (m_prcSel);
	m_prcSel -> Process (ptM);
	Draw (m_prcSel);
}

void COverView :: MouseMove (MouseEvt e)
{
// nur Pointer umschalten
Point ptM (e.Where().X(), m_dY - e.Where().Y());

	if (m_prcActVP && HitTest (m_prcActVP, ptM)) {
		if (m_pMove) 
			ChangePointer (m_pMove);
	} else {
		if (m_pLupe) 
			ChangePointer (m_pLupe);
	}
}

// Skalieren des Selektionsrechteckes -----------------------------------------
inline short Rescale (CoOrd c, CoOrd dNew, CoOrd dOld)
{
	return MulDiv (c, dNew, dOld);
}

void COverView :: ReSize (ReSizeEvt)
{
// evtl. alte Selektion löschen
HWND hWnd = Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
int iOldRop = SetROP2 (hDC, R2_XORPEN);
HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	
	hP = (HPEN)SelectObject (hDC, hP);
	if (m_prcActVP) {
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);
	}

Rectangle rc = CanvasRect();
CoOrd dXC = rc.Right() - rc.Left();	// neuer CanvasBereich
CoOrd dYC = rc.Top() - rc.Bottom();

// neues Selektionsrechteck berechnen und anzeigen
	if (m_prcActVP) {
		m_prcActVP -> left = Rescale (m_prcActVP -> left, dXC, m_dX);
		m_prcActVP -> right = Rescale (m_prcActVP -> right, dXC, m_dX);
		m_prcActVP -> bottom = Rescale (m_prcActVP -> bottom, dYC, m_dY);
		m_prcActVP -> top = Rescale (m_prcActVP -> top, dYC, m_dY);

		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, 
				m_prcActVP -> right, m_prcActVP -> bottom);
	}
	
// neue FensterAbmessungen merken
	m_dX = dXC;
	m_dY = dYC;
	rc = WindowRect();
	m_dimWnd = Dimension (rc.Right()-rc.Left(), rc.Top()-rc.Bottom());

	DeleteObject (SelectObject (hDC, hP));
	SetROP2 (hDC, iOldRop);
	ReleaseDC (hWnd, hDC);

	RePaint();	// auf jeden Fall neuzeichnen
}

Bool COverView :: QueryClose (Event)
{
	OverViewCFlag = FALSE;
	m_fToDelete = TRUE;		// kann gelöscht werden
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Eigener Eventhandler und eigener Dispatcher 
long COverView :: Dispatch (Event e) 
{
// wenn WM_WINDOWPOSCHANGING --> umlenken
	switch (e.Msg()) {
	case WM_WINDOWPOSCHANGING:
		WindowPosChanging ((WindowPosEvt &)e);
		break;		// auf jeden Fall weitersenden

	case WM_DLGSUBCLASS:
		*(int *)e.LParam() = CTL3D_NOSUBCLASS;
		break;
	}

// ansonsten normaler Dispatcher
	return Window :: Dispatch (e);
}

///////////////////////////////////////////////////////////////////////////////
// MetaFile speichern/einlesen
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);

HRESULT COverView::LoadEnhMetaFile (LPCSTR pcName)
{
	TX_ASSERT(NULL == m_hMF);

// SubStorage öffnen bzw. anlegen, wenn es noch nicht existiert
WStorage IStg;
HRESULT hr = E_FAIL;

	USES_CONVERSION;
	{
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> OpenStorage (A2OLE(g_cbOverviews), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
		
		if (FAILED(hr)) return hr;
	} // IRootStg freigeben

BYTE *pBytes = NULL;

	try {
	// Stream erzeugen
	WStream IStm;

		hr = IStg -> OpenStream (A2OLE(pcName), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// MetaFile wegschreiben
	UINT uiBytes = 0L;

		THROW_FAILED_HRESULT(IStm -> Read (&uiBytes, sizeof(ULONG), NULL));	

		ATLTRY(pBytes = new BYTE[uiBytes]);
		if (NULL == pBytes) _com_issue_error(E_OUTOFMEMORY);

		THROW_FAILED_HRESULT(IStm -> Read (pBytes, uiBytes, NULL));

		m_hMF = SetEnhMetaFileBits (uiBytes, pBytes);
		if (NULL == m_hMF) _com_issue_error(E_OUTOFMEMORY);

	} catch (_com_error& hr) {
		delete pBytes;
		return _COM_ERROR(hr);
	}

	delete pBytes;
	return S_OK;
}

HRESULT COverView::SaveEnhMetaFile (LPCSTR pcName)
{
	if (NULL == m_hMF) return E_HANDLE;

// SubStorage öffnen bzw. anlegen, wenn es noch nicht existiert
WStorage IStg;
HRESULT hr = E_FAIL;

	USES_CONVERSION;
	{
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> OpenStorage (A2OLE(g_cbOverviews), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
		
		if (FAILED(hr)) {
			hr = IRootStg -> CreateStorage (A2OLE(g_cbOverviews),  
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						0L, 0L, IStg.ppi());
		}
		if (FAILED(hr)) return hr;
	} // IRootStg freigeben

BYTE *pBytes = NULL;

	try {
	// Stream erzeugen
	WStream IStm;

		hr = IStg -> CreateStream (A2OLE(pcName), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// MetaFile wegschreiben
	UINT uiBytes = GetEnhMetaFileBits (m_hMF, (UINT)-1, NULL);
	
		ATLTRY(pBytes = new BYTE[uiBytes]);
		if (NULL == pBytes) _com_issue_error(E_OUTOFMEMORY);
		GetEnhMetaFileBits (m_hMF, uiBytes, pBytes);

		THROW_FAILED_HRESULT(IStm -> Write (&uiBytes, sizeof(ULONG), NULL));
		THROW_FAILED_HRESULT(IStm -> Write (pBytes, uiBytes, NULL));

	// Änderungen speichern
		hr = IStm -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		delete pBytes;
		return _COM_ERROR(hr);
	}

	delete pBytes;
	hr = IStg -> Commit (STGC_DEFAULT);
	if (SUCCEEDED(hr)) {
		DEX_SetDirtyGeoDB(true);
		m_fIsDirty = false;
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RightButtonMenu
void COverView::MenuCommand (MenuCommandEvt e)
{
	BEGIN_COMMANDS(e) 
		ON_COMMAND_ID(ID_OVERVIEW_RESETRECT, OnResetRect);	// Ausschnitt rücksetzen
		ON_COMMAND_ID(ID_OVERVIEW_ACTVIEW, OnActView);		// Aktuelle Ansicht übernehmen
		ON_COMMAND_ID(ID_OVERVIEW_HIDE, OnHideWindow);		// Fenster ausblenden
	END_COMMANDS;
}

// MenuBefehle
bool COverView::OnResetRect (void) 
{
	GetParent() -> PostEvent (Event(WM_COMMAND, IDM_RESTOREVIEWCONTAINER));
	return true;
}

bool COverView::OnActView (void) 
{
Rectangle rcC = CanvasRect();

	if (RetrieveActViewMetaFile (rcC)) {
		RePaint();
		return true;
	}
	return false;
}

bool COverView::OnHideWindow (void) 
{
	TX_ASSERT(OverViewCFlag);		// Fenster muß angezeigt sein
	GetParent() -> PostEvent (Event(WM_COMMAND, IDM_OVERVIEW));
	return true;
}

// Menu initialisieren
void COverView::MenuInit (MenuInitEvt e)
{
	TX_ASSERT(NULL != m_hSubMenu);
	if (NULL != m_prcActVP)
		EnableMenuItem (m_hSubMenu, ID_OVERVIEW_RESETRECT, MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (m_hSubMenu, ID_OVERVIEW_RESETRECT, MF_BYCOMMAND|MF_GRAYED);

	SetMenuDefaultItem (m_hSubMenu, ID_OVERVIEW_ACTVIEW, false);
}

// StatusZeilenText anzeigen
void COverView::MenuSelect (MenuSelectEvt e)
{
	TX_ASSERT(NULL != m_hSubMenu);

UINT uiRes = 0L;

	switch (e.GetItemID()) {
	case ID_OVERVIEW_RESETRECT: uiRes = IDS_OVERVIEW_RESETRECT; break;
	case ID_OVERVIEW_ACTVIEW: uiRes = IDS_OVERVIEW_ACTVIEW; break;
	case ID_OVERVIEW_HIDE: uiRes = IDS_OVERVIEW_HIDE; break;
	}
	if (0 == uiRes) {
	// Separator getroffen
		DEX_SetMessageString(g_cbNil);
		return;
	}

ResString resStatus (uiRes, _MAX_PATH);

	DEX_SetMessageString (resStatus.Addr());
}

bool COverView::TrackOverviewMenu (Point pt)
{
HMENU hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (IDR_OVERVIEW_DROPDOWN));

	if (hMenu == NULL) return false;	// irgend was stimmt nicht

// Menu generieren
	m_hSubMenu = GetSubMenu (hMenu, 0);		// SubMenu holen
	if (NULL == m_hSubMenu) {
		DestroyMenu (hMenu);
		return false;
	}

Rectangle Rc = CanvasRect();
HWND hWnd = Handle (API_CLIENT_HWND);

	pt.Y() = Rc.Top() - Rc.Bottom() - pt.Y();	// in WindowsKoord umrechnen
	ClientToScreen (hWnd, (LPPOINT)&pt);

BOOL fResult = TrackPopupMenu (m_hSubMenu, 0, pt.X(), pt.Y(), 0, hWnd, NULL);

// wieder aufräumen
	m_hSubMenu = NULL;
	DestroyMenu (hMenu);

	return fResult ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler für MinMaxEvent etc. 
void COverView :: WindowPosChanging (WindowPosEvt e)
{
	if (!e.SizeIsChanging()) return;
	
Dimension dimNew;

	e.GetWindowSize (dimNew);
	if (dimNew.Width() != m_dimWnd.Width()) {
		dimNew.Height() = int(dimNew.Width() * m_dAspect);
		e.SetWindowSize (dimNew);
		return;
	}
	
	if (dimNew.Height() != m_dimWnd.Height()) {
		dimNew.Width() = int(dimNew.Height() / m_dAspect);
		e.SetWindowSize (dimNew);
		return;
	}
}

void WindowPosEvt :: GetWindowSize (Dimension &dim)
{
	dim.Width() = ((WINDOWPOS *)lParam) -> cx;
	dim.Height() = ((WINDOWPOS *)lParam) -> cy;
}

void WindowPosEvt :: SetWindowSize (Dimension dim)
{
	((WINDOWPOS *)lParam) -> cx = dim.Width();
	((WINDOWPOS *)lParam) -> cy = dim.Height();
}

BOOL WindowPosEvt :: SizeIsChanging (void)
{
	return (((WINDOWPOS *)lParam) -> flags & SWP_NOSIZE) ? FALSE : TRUE;
}

///////////////////////////////////////////////////////////////////////////////


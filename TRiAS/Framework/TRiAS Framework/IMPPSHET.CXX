// Implementor für CPropertySheet ---------------------------------------------
// File: IMPPSHET.CXX

#include "tfrmpre.hxX"
#include <_Link.hxx>

#include <commctrl.h>
#include <limits.h>

/////////////////////////////////////////////////////////////////////////////
// Window creation hooks
typedef struct tagHOOKCREATEWINDOWDATA {
	HHOOK m_hHookOldCbtFilter;	// Hook weiterreichen an
	DWind_Imp *m_pWndInit;		// neues Fensterobjekt
	WNDPROC m_WndProc;			// neue WindowProc
} HOOKCREATEWINDOWDATA;

HOOKCREATEWINDOWDATA g_CreateWndHookData = { NULL, NULL, NULL };

LRESULT CALLBACK _CbtFilterHook (int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HCBT_CREATEWND)		// wait for HCBT_CREATEWND just pass others on...
		return CallNextHookEx (g_CreateWndHookData.m_hHookOldCbtFilter, code, wParam, lParam);

	_ASSERTE(lParam != NULL);

LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;

	_ASSERTE(lpcs != NULL);

// this hook exists to set the SendMessage hook on window creations
//  (but this is only done for MFC windows or non-child windows)
// the subclassing cannot be done at this point because on Win32s
//  the window does not have the WNDPROC set yet
DWind_Imp *pWndInit = g_CreateWndHookData.m_pWndInit;

	if (pWndInit != NULL || !(lpcs->style & WS_CHILD)) {
		_ASSERTE(wParam != NULL); // should be non-NULL HWND
	
	HWND hWnd = (HWND)wParam;
	WNDPROC oldWndProc;
	
		if (pWndInit != NULL) {
		// connect the HWND to pWndInit...
			pWndInit -> Attach(hWnd);

		WNDPROC *pOldWndProc = pWndInit -> GetSuperClassProc();

			_ASSERTE(NULL != pOldWndProc);

		// subclass the window with given WindowProc
		WNDPROC WndProc = g_CreateWndHookData.m_WndProc;

			oldWndProc = (WNDPROC)SetWindowLong (hWnd, GWL_WNDPROC, (DWORD)WndProc);
			_ASSERTE(oldWndProc != NULL);
			if (oldWndProc != WndProc)
				*pOldWndProc = oldWndProc;
		}
		g_CreateWndHookData.m_pWndInit = NULL;
	}

	return CallNextHookEx (g_CreateWndHookData.m_hHookOldCbtFilter, code, wParam, lParam);
}

BOOL WINAPI HookWindowCreate (DWind_Imp *pWnd, WNDPROC WndProc)
{
	if (g_CreateWndHookData.m_pWndInit == pWnd)
		return true;

	if (NULL == g_CreateWndHookData.m_hHookOldCbtFilter) {
		g_CreateWndHookData.m_hHookOldCbtFilter = ::SetWindowsHookEx (WH_CBT,
			_CbtFilterHook, NULL, ::GetCurrentThreadId());
		if (g_CreateWndHookData.m_hHookOldCbtFilter == NULL)
			return false;
	}
	_ASSERTE(NULL != g_CreateWndHookData.m_hHookOldCbtFilter);
	_ASSERTE(NULL != pWnd);
	_ASSERTE(NULL == CV_RunTime::Window_Handle(pWnd));   // only do once

	_ASSERTE(NULL == g_CreateWndHookData.m_pWndInit);   // hook not already in progress
	g_CreateWndHookData.m_pWndInit = pWnd;
	g_CreateWndHookData.m_WndProc = WndProc;

return true;
}

BOOL WINAPI UnhookWindowCreate (void)
{
	if (g_CreateWndHookData.m_hHookOldCbtFilter != NULL) 
	{
		::UnhookWindowsHookEx (g_CreateWndHookData.m_hHookOldCbtFilter);
		g_CreateWndHookData.m_hHookOldCbtFilter = NULL;
	}

	g_CreateWndHookData.m_WndProc = NULL;
	if (NULL != g_CreateWndHookData.m_pWndInit)
	{
		g_CreateWndHookData.m_pWndInit = NULL;
		return false;   // was not successfully hooked
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// CallbackProcedure for Creation of PropSheets
int CALLBACK PropSheetCallback (HWND, UINT message, LPARAM lParam)
{
	switch (message) {
	case PSCB_PRECREATE:
		{
		LPDLGTEMPLATE lpTemplate = (LPDLGTEMPLATE)lParam;
		
			if (lpTemplate->style & WS_VISIBLE) {
			// Mark the dialog template as read-write.
			DWORD dwOldProtect;

				VirtualProtect (lpTemplate, sizeof(DLGTEMPLATE), PAGE_READWRITE, &dwOldProtect);
				lpTemplate->style &= ~WS_VISIBLE;
				return TRUE;
			}
			return FALSE;
		}
	}

	return 0;
}

// Konstruktor/Destruktor/Initialisierung -------------------------------------
PSheetWind_Imp::PSheetWind_Imp (CPropertySheet *pSheet, LPCSTR pszCaption, 
				  Wind_Imp *parent, DWORD dwFlags, int iSelPage)
		: DWind_Imp(pSheet), m_iSelPage(iSelPage)
{
	WndParent = parent;
	m_pPages = new PPageWind_Imp *[MAXPROPPAGES];

	if (NULL != pszCaption) 
		WndCapt = CV_strdup (pszCaption);	// Take a copy

pApp_Imp pAppImpInst = _AppImpFind();

	memset(&m_psh, '\0', sizeof(m_psh));
	m_psh.dwSize = sizeof(PROPSHEETHEADER);
	m_psh.dwFlags = dwFlags|PSH_USECALLBACK;
	m_psh.hwndParent = CV_RunTime::Window_Handle(parent);
	m_psh.hInstance = CV_RunTime::App_hApp(pAppImpInst);
	m_psh.pszIcon = NULL;
	m_psh.pszCaption = WndCapt;
	m_psh.nPages = 0;
	m_psh.nStartPage = 0;
	m_psh.phpage = new HPROPSHEETPAGE [MAXPROPPAGES];
	m_psh.pfnCallback = PropSheetCallback;

	WindMgt.isModal = (dwFlags & PSH_MODELESS) ? false : true;
	DlgFlags.IsShown = 0;
	DlgFlags.fParentsDisabled = false;

	if (NULL == m_pPages || NULL == m_psh.phpage)
		return;

	for (UINT uiCnt = 0; uiCnt < MAXPROPPAGES; uiCnt++) {
		m_psh.phpage[uiCnt] = NULL;
		m_pPages[uiCnt] = NULL;
	}

	m_st = Normal;
}

PSheetWind_Imp::~PSheetWind_Imp (void)
{
	if (NULL == hEContext) {
	// PropSheet wurde nicht angezeigt
		for (int i = 0; i < MAXPROPPAGES; i++) {
			if (NULL != m_psh.phpage[i])
				DestroyPropertySheetPage (m_psh.phpage[i]);
		}
	}
	if (m_pPages) {
		delete [] m_pPages;
		m_pPages = NULL;
	}
	if (m_psh.phpage) {
		delete [] m_psh.phpage;
		m_psh.phpage = NULL;
	}
}

void PSheetWind_Imp::SetStyle (ulong style, BOOL setflag)
{
	if (NULL != hEContext) return;		// bereits initialisiert
	if (setflag)
		m_psh.dwFlags |= style;
	else
		m_psh.dwFlags &= (~style);
}

void CentreWindow (HWND hWndP, HWND hWnd);

BOOL PSheetWind_Imp::FInit (HWND hWnd)
{
	if (NULL == hWnd) return false;

	if (!WindMgt.Initialised) {
		hModeless = hWnd;
		_ASSERTE(hEContext == hModeless);
		Initialise();

	// FensterGröße initialisieren
		InitSize();

	Rectangle r ;

		GetClientRect (hEContext, (RECT *)&r);

	long lDBUnits = GetDialogBaseUnits();

		Xbase = LOWORD(lDBUnits) ;
		Ybase = HIWORD(lDBUnits) ;

		Xchars = r.Right()/Xbase;
		Ychars = r.Bottom()/Ybase;
	}

// wenn gefordert, Sheet im Parent zentrieren
	if (Centre == (ShowState)(m_st & SHOWSTATE_STATE)) {
	HWND hWndP = ::GetParent (hModeless);

		CentreWindow ((hWndP && IsWindow(hWndP)) ? hWndP : GetDesktopWindow(), hModeless);
	}

// Caption merken
char cbBuffer[129];

	if (GetWindowText (hEContext, cbBuffer, 128)) {
		cbBuffer[128] = '\0';
		SetCaption (cbBuffer);
	}

return true;
}

// InterfaceFunktionen --------------------------------------------------------
int PSheetWind_Imp::GetPageCount (void)
{
	return m_psh.nPages;	// Anzahl der Seiten
}

PPageWind_Imp* PSheetWind_Imp::GetPage (UINT nPage) const
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);
	
	if (nPage >= 0 && nPage < m_psh.nPages)
		return m_pPages[nPage];

return NULL;
}

BOOL ContinueModal (DWORD dwDataCM)
{
PSheetWind_Imp *pSheet = (PSheetWind_Imp *)dwDataCM;

	_ASSERTE(NULL != pSheet);
	_ASSERTE(::IsWindow(pSheet->hEContext));

BOOL bResult = (NULL != ::SendMessage (pSheet->hEContext, PSM_GETCURRENTPAGEHWND, 0L, 0L)) ? true : false;

	if (!bResult) 
		pSheet->EndDlg(pSheet->result);

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
//
void PSheetWind_Imp::Show (ShowState s)
{
	result = 0;		// Re-initialise result before each showing;

	m_st = s;		// ShowState merken

pApp_Imp pAppImpInst = _AppImpFind();

	if (!DlgFlags.IsShown) {

		if (CV_RunTime::Window_Capt(this)) 
			m_psh.pszCaption = CV_RunTime::Window_Capt(this);

		m_psh.dwFlags |= PSH_MODELESS;		// Modal selbst simulieren

	// Dialog als modeless erzeugen
	int iStartPage = m_psh.nStartPage;

		m_psh.nStartPage = 0;
		{
		// %%TODO: threadsafe machen
			HookWindowCreate (this, PropSheetDispatcher);
			hModeless = (HWND)::PropertySheet (&m_psh);
			UnhookWindowCreate();
		}

		if (!IsWindow(hModeless) || !FInit (hModeless)) {
			_ASSERTE(IsWindow(hModeless));
			return;		// Fehler;
		}

		if (CV_RunTime::Window_Capt(this))	// * 1.26 *
	   		SetWindowText (hEContext, CV_RunTime::Window_Capt(this));

	// künstlich modal machen
		if (WindMgt.isModal) {
		HWND h = GetFocus();

			if (!h || !((h == hModeless) || IsChild (hModeless, h)))
				::SetFocus(hModeless);

		HWND hp = hEContext;

			DlgFlags.IsShown = true;
			while (hp = ::GetParent(hp))
				EnableWindow(hp, 0);
			DlgFlags.fParentsDisabled = true;

		// jetzt wirklich anzeigen
			if (0 != iStartPage)	// evtl. andere Seite aktivieren
				SetCurSel (iStartPage);

		// jetzt anzeigen
			if (s & NoActivate)
				ShowWindow (hModeless, SW_SHOWNOACTIVATE);
			else
				ShowWindow (hModeless, SW_SHOW);
			pAppImpInst -> SetActiveDialog(hModeless);
			
		ExecType et = ExecNormal;

			if (NoQuitOnHide & s)
				et = ExecNormalNoQuitOnHide;
			CV_RunTime::App_Exec (pAppImpInst, et, &pActiveContext, ContinueModal, (DWORD)this);

		// aktiven Dialog wieder rücksetzen
			EndDlg (result);
			if (hModeless == pAppImpInst -> GetActiveDialog())
				pAppImpInst -> SetActiveDialog(0);
		} else {
		// jetzt wirklich anzeigen
			if (0 != iStartPage)	// evtl. andere Seite aktivieren
				SetCurSel (iStartPage);

		// lediglich anzeigen
			if (s & NoActivate)
				ShowWindow (hModeless, SW_SHOWNOACTIVATE);
			else
				ShowWindow (hModeless, SW_SHOW);
			pAppImpInst -> SetActiveDialog(hModeless);
		}
	}
}

UINT PSheetWind_Imp::AddPage (PPageWind_Imp *pPage)
{
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);
	CV_ASSERT_VALID(NULL != pPage);

	if (m_psh.nPages >= MAXPROPPAGES) 
		return UINT_MAX; // kein Platz mehr

// Page generieren
	m_psh.phpage[m_psh.nPages] = pPage -> CreatePage (this);
	m_pPages[m_psh.nPages] = pPage;

return m_psh.nPages++;
}

UINT PSheetWind_Imp::AddPage (HPROPSHEETPAGE hPage)
{
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	if (m_psh.nPages >= MAXPROPPAGES) 
		return UINT_MAX; // kein Platz mehr

// Page generieren
	m_psh.phpage[m_psh.nPages] = hPage;
	m_pPages[m_psh.nPages] = NULL;

return m_psh.nPages++;
}

BOOL PSheetWind_Imp::RemovePage (PPageWind_Imp *pPage)
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	if (NULL == pPage) return false;

	for (UINT iCnt = 0; iCnt < m_psh.nPages; iCnt++) {
		if (pPage == m_pPages[iCnt]) {	// found: Remove Page
			PropSheet_RemovePage (hEContext, iCnt, m_psh.phpage[iCnt]);

			for (UINT ui = iCnt; ui < m_psh.nPages-1; ui++) {
				m_psh.phpage[ui] = m_psh.phpage[ui+1];
				m_pPages[ui] = m_pPages[ui+1];
			}
			m_psh.phpage[--m_psh.nPages] = NULL;
			m_pPages[m_psh.nPages] = NULL;

			return true;		// fertig
		}
	}

return false;
}

BOOL PSheetWind_Imp::RemovePage (HPROPSHEETPAGE hPage)
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	for (UINT iCnt = 0; iCnt < m_psh.nPages; iCnt++) {
		if (hPage == m_psh.phpage[iCnt]) {	// found: Remove Page
			PropSheet_RemovePage (hEContext, iCnt, hPage);

			for (UINT ui = iCnt; ui < m_psh.nPages-1; ui++) {
				m_psh.phpage[ui] = m_psh.phpage[ui+1];
				m_pPages[ui] = m_pPages[ui+1];
			}
			m_psh.phpage[--m_psh.nPages] = NULL;
			m_pPages[m_psh.nPages] = NULL;

			return true;		// fertig
		}
	}

return false;
}

BOOL PSheetWind_Imp::RemovePage (UINT nPage)
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	if (nPage >= 0 && nPage < m_psh.nPages) {
		PropSheet_RemovePage (hEContext, nPage, m_psh.phpage[nPage]);

		for (UINT uiCnt = nPage; uiCnt < m_psh.nPages-1; uiCnt++) {
			m_psh.phpage[uiCnt] = m_psh.phpage[uiCnt+1];
			m_pPages[uiCnt] = m_pPages[uiCnt+1];
		}
		m_psh.phpage[--m_psh.nPages] = NULL;
		m_pPages[m_psh.nPages] = NULL;
		return true;
	}

return false;
}

void PSheetWind_Imp::EndDlg (int nEndID)
{
	DWind_Imp::EndDlg (nEndID);
}

BOOL PSheetWind_Imp::SetCurSel (PPageWind_Imp *pPage)
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	if (NULL == pPage) return false;
	for (UINT iCnt = 0; iCnt < m_psh.nPages; iCnt++) {
		if (pPage == m_pPages[iCnt]) {	// found: SetSelection
			PropSheet_SetCurSel (hEContext, m_psh.phpage[iCnt], iCnt);
			return true;
		}
	}

return false;
}

BOOL PSheetWind_Imp::SetCurSel (HPROPSHEETPAGE hPage)
{
	CV_ASSERT_VALID(hEContext);
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	for (UINT iCnt = 0; iCnt < m_psh.nPages; iCnt++) {
		if (hPage == m_psh.phpage[iCnt]) {	// found: SetSelection
			PropSheet_SetCurSel (hEContext, hPage, iCnt);
			return true;
		}
	}

return false;
}

BOOL PSheetWind_Imp::SetCurSel (UINT nPage)
{
	CV_ASSERT_VALID(NULL != m_pPages);
	CV_ASSERT_VALID(NULL != m_psh.phpage);

	if (nPage >= 0 && nPage < m_psh.nPages) {
		if (NULL == hEContext)
			m_psh.nStartPage = nPage;
		else
			PropSheet_SetCurSel (hEContext, m_psh.phpage[nPage], nPage);
		return true;
	}

return false;
}

void PSheetWind_Imp::PressButton (DWORD rgBT)
{
	CV_ASSERT_VALID(hEContext);

	PropSheet_PressButton (hEContext, rgBT);
}

void PSheetWind_Imp::SetWizButtons (DWORD rgBT)
{
	CV_ASSERT_VALID(hEContext);

	PropSheet_SetWizButtons (hEContext, rgBT);
}

// Icon für Caption setzen ----------------------------------------------------
void PSheetWind_Imp::SetIcon (ResID resID)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

pApp_Imp pAppImpInst = _AppImpFind();

	m_psh.hIcon = LoadIcon (CV_RunTime::ResID_handle (resID, pAppImpInst, RT_ICON),
				(char *)((ulong)((uint)resID)));
	if (NULL != m_psh.hIcon) 
		m_psh.dwFlags |= PSH_USEHICON;
}

void PSheetWind_Imp::SetIcon (Icon_Imp *pIcon)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

	m_psh.hIcon = CV_RunTime::IconImp_hIcon(pIcon);
	if (NULL != m_psh.hIcon) 
		m_psh.dwFlags |= PSH_USEHICON;
}

// #HK030116: Wizard97: Headerbitmap und Watermark setzen
void PSheetWind_Imp::SetHeaderBitmap (ResID resID)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

pApp_Imp pAppImpInst = _AppImpFind();

	m_psh.hbmHeader = LoadBitmap (CV_RunTime::ResID_handle (resID, pAppImpInst, RT_BITMAP),
				(char *)((ulong)((uint)resID)));
	if (NULL != m_psh.hbmHeader) 
		m_psh.dwFlags |= (PSH_USEHBMHEADER|PSH_HEADER);
}

void PSheetWind_Imp::SetHeaderBitmap (Bitmap_Imp *pBitmap)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

	m_psh.hbmHeader = CV_RunTime::BitmapImp_hBitmap(pBitmap);
	if (NULL != m_psh.hbmHeader) 
		m_psh.dwFlags |= (PSH_USEHBMHEADER|PSH_HEADER);
}

void PSheetWind_Imp::SetWatermark (ResID resID)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

pApp_Imp pAppImpInst = _AppImpFind();

	m_psh.hbmWatermark = LoadBitmap (CV_RunTime::ResID_handle (resID, pAppImpInst, RT_BITMAP),
				(char *)((ulong)((uint)resID)));
	if (NULL != m_psh.hbmWatermark) 
		m_psh.dwFlags |= (PSH_USEHBMWATERMARK|PSH_WATERMARK);
}

void PSheetWind_Imp::SetWatermark (Bitmap_Imp *pBitmap)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

	m_psh.hbmWatermark = CV_RunTime::BitmapImp_hBitmap(pBitmap);
	if (NULL != m_psh.hbmWatermark) 
		m_psh.dwFlags |= (PSH_USEHBMWATERMARK|PSH_WATERMARK);
}

///////////////////////////////////////////////////////////////////////////////
// FensterProzedur für PropertySheets
LRESULT WINAPI _DISPATCH_ENTRY
PropSheetDispatcher (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
pApp_Imp AppImpInst = _AppImpFind();
pWind_Imp pWI;
 	
	if (!((AppImpInst -> ContextList() -> First()) &&
		 (pWI = (pWind_Imp)(AppImpInst -> ContextList() -> Find ((HANDLE)hWnd)))))
	{
	// fehler !!
		_ASSERTE(false);
		return false;
	}

	switch (uiMsg) {
	case WM_INITDIALOG:
		{
			CV_RunTime::App_LastDlgHandle(AppImpInst) = hWnd;
		
		// evtl. TabControl darf nicht multiline sein
			_ASSERTE(hWnd == CV_RunTime::EventContext_hEContext(pWI));

		DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE); 
		HWND hTabCtrl = (HWND)::GetDlgItem(hWnd, 0x3020);	// Property Sheet control id's (determined with Spy++)

			if (NULL != hTabCtrl)
				SetWindowLong(hTabCtrl, GWL_STYLE, GetWindowLong(hTabCtrl, GWL_STYLE) & ~TCS_MULTILINE);

		LRESULT lResult = EventDispatcher (hWnd, uiMsg, wParam, lParam);

			((PSheetWind_Imp *)pWI) -> FInit (hWnd);
			return lResult;
		}
		break;

	case WM_SYSCOMMAND:
		{
			if (SC_CLOSE == (wParam & 0xfff0)) {
				CV_RunTime::PropertySheet_SetResult (pWI, IDCANCEL);
				SendMessage (hWnd, WM_CLOSE, 0, 0);
				return TRUE;
			}
		}
		break;

	case WM_COMMAND:
		{
		// crack message parameters
		UINT nID = LOWORD(wParam);
		HWND hWndCtrl = (HWND)lParam;
		int nCode = HIWORD(wParam);

		// set result to ID of button, whenever button is clicked
			if (hWndCtrl != NULL && nCode == BN_CLICKED) {
				if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0) & (DLGC_BUTTON|DLGC_DEFPUSHBUTTON))
				{
				LONG lStyle = ::GetWindowLong(hWndCtrl, GWL_STYLE) & 0x0F;
					
					if (lStyle == BS_PUSHBUTTON || lStyle == BS_DEFPUSHBUTTON ||
						lStyle == BS_USERBUTTON || lStyle == BS_OWNERDRAW)
					{
						CV_RunTime::PropertySheet_SetResult (pWI, nID);
					}
				}
			}
		}
		break;
	}

// return CV_RunTime::PropertySheet_CallWindowProc (pWI, uiMsg, wParam, lParam);
	return EventDispatcher (hWnd, uiMsg, wParam, lParam);
}


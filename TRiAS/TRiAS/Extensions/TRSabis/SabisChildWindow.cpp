// SabisChildWindow.cpp : Implementation of CSabisChildWindow

#include "stdafx.h"
#include "TRSABIS.h"

#include "SabisChildWindow.h"

#include "macros.h"

// Macro zum ermitteln eines sicheren Pointers auf das Childwindow
// die Funktion wird mit entsprechendem Fehlercode verlassen, wenn 
// das Fenster nicht existiert und auch nicht angelegt werden kann
#define GETPWND() \
	CTRiASChild* pWnd = GetWindow(); \
	CHECKPOINTER(pWnd, E_OUTOFMEMORY);

/////////////////////////////////////////////////////////////////////////////
// CSabisChildWindow
STDMETHODIMP CSabisChildWindow::put_BackColor (/* [in] */ long __MIDL_0015)
{
	GETPWND();
	pWnd -> SetBackgroundColor(__MIDL_0015);
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_BackColor (/* [retval][out] */ long *__MIDL_0016)
{
	CHECKPOINTERHR(__MIDL_0016);
	GETPWND();

	*__MIDL_0016 = pWnd -> GetBackgroundColor();

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Caption ( 
        /* [in] */ BSTR __MIDL_0017)
{
	GETPWND();

	CString strCaption(__MIDL_0017);
	pWnd -> SetWindowText(strCaption);
	
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_Caption ( 
        /* [retval][out] */ BSTR *__MIDL_0018)
{
	CHECKPOINTERHR(__MIDL_0018);
	GETPWND();

	CString strCaption;
	pWnd -> GetWindowText(strCaption);

	*__MIDL_0018 = CComBSTR(strCaption);
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Enabled ( 
        /* [in] */ VARIANT_BOOL fEnabled)
{
	GETPWND();

	if (VARIANT_FALSE != fEnabled)
		pWnd -> EnableWindow();
	else
		pWnd -> EnableWindow(FALSE);

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_Enabled ( 
        /* [retval][out] */ VARIANT_BOOL *pfEnabled)
{
	CHECKPOINTERHR(pfEnabled);
	GETPWND();

	if (pWnd -> IsWindowEnabled())
		*pfEnabled = TRUE;
	else
		*pfEnabled = FALSE;

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_Height ( 
        /* [retval][out] */ long *plHeight)
{
	CHECKPOINTERHR(plHeight);
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	*plHeight = rect.Height();
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Height ( 
        /* [in] */ long lHeight)
{
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	rect.bottom = rect.top + lHeight;
	pWnd -> MoveWindow(rect);
	
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_hWnd ( 
        /* [retval][out] */ long *phWnd)
{
	GETPWND();
	CHECKPOINTERHR(phWnd)

	*phWnd = reinterpret_cast<long> (pWnd->GetSafeHwnd());
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Icon ( 
        /* [in] */ VARIANT rhs)
{
	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_Left ( 
        /* [retval][out] */ long *plLeft)
{
	CHECKPOINTERHR(plLeft);
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	*plLeft = rect.left;
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::put_Left ( 
        /* [in] */ long lLeft) 
{ 
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

long w = rect.Width();

	rect.left = lLeft;
	rect.right = rect.left + w;

	pWnd -> MoveWindow(rect);

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::Move ( 
        /* [in] */ long X,
        /* [in] */ long Y) 
{ 
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	long w = rect.Width();
	rect.left = X;
	rect.right = rect.left + w;

	long h = rect.Height();
	rect.top = Y;
	rect.bottom = rect.top + h;

	pWnd -> MoveWindow(rect);

	return S_OK; 
}
// was'n das 
STDMETHODIMP CSabisChildWindow::OnKeyDown ( 
        /* [out][in] */ short *KeyCode,
        /* [out][in] */ short *Shift) 
{
	CHECKPOINTERHR(KeyCode);
	CHECKPOINTERHR(Shift);

	CWnd* pParent = AfxGetMainWnd();
	CHECKPOINTERHR(pParent);
	
	pParent->SendMessage(WM_KEYDOWN, static_cast<WPARAM>(*KeyCode), static_cast<LPARAM>(*Shift));

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Tag ( 
        /* [in] */ BSTR bstrTag) 
{ 
	m_Tag = bstrTag;
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::get_Tag ( 
        /* [retval][out] */ BSTR *pbstrTag) 
{ 
	CHECKPOINTERHR(pbstrTag);

CComBSTR bstr(m_Tag);

	*pbstrTag = bstr.Detach();
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::get_Top ( 
        /* [retval][out] */ long *plTop) 
{ 
	CHECKPOINTERHR(plTop);
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	*plTop = rect.top;

	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::put_Top ( 
        /* [in] */ long lTop) 
{ 
	GETPWND();

	CRect rect;
	RETURN_FAILED_HRESULT(GetWindowRect(rect));

	long h = rect.Height();
	rect.top = lTop;
	rect.bottom = rect.top + h;

	pWnd -> MoveWindow(rect);

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::put_Visible ( 
        /* [in] */ VARIANT_BOOL fVisible) 
{ 
	GETPWND();

	if (fVisible) {
		pWnd -> ShowWindow(SW_SHOW);
		pWnd -> BringWindowToTop();
	}
	else 
		pWnd -> ShowWindow(SW_HIDE);

	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::get_Visible ( 
        /* [retval][out] */ VARIANT_BOOL *pfVisible) 
{ 
	CHECKPOINTERHR(pfVisible);
	GETPWND();

	WINDOWPLACEMENT wndPlace;
	INITWP(wndPlace);
	pWnd -> GetWindowPlacement(&wndPlace);

	// entsprechend dem akuellem Status das Fenster schalten
	if (	(wndPlace.showCmd == SW_HIDE) 
		||	(wndPlace.showCmd == SW_MINIMIZE))
	{
		*pfVisible = FALSE;
	}
	else {
		*pfVisible = TRUE;
	}

	return S_OK;
}

STDMETHODIMP CSabisChildWindow::get_Width ( 
        /* [retval][out] */ long *plWidth) 
{ 
	CHECKPOINTERHR(plWidth);
	GETPWND();

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	*plWidth = rect.Width();
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::put_Width ( 
        /* [in] */ long lWidth) 
{ 
	GETPWND();

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	rect.right = rect.left + lWidth;
	pWnd -> MoveWindow(rect);
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::get_WindowState ( 
        /* [retval][out] */ long *plState) 
{ 
//	helpstring("O:Normal, 1:Minimiert, 2:Maximiert")]
	CHECKPOINTERHR(plState);
	GETPWND();
	
	WINDOWPLACEMENT wp;
	INITWP(wp);
	pWnd->GetWindowPlacement(&wp);

	switch (wp.showCmd) {
	case SW_MAXIMIZE:
		*plState = 2;
		break;

	case SW_HIDE:
	case SW_SHOWMINIMIZED:
	case SW_MINIMIZE:
	case SW_SHOWNOACTIVATE: 
		*plState = 1;
		break;

	case SW_SHOW:
	case SW_NORMAL: 
	case SW_SHOWDEFAULT:
	default:
		*plState = 0;
		break;
	}
	return S_OK; 
}

STDMETHODIMP CSabisChildWindow::put_WindowState ( 
        /* [in] */ long lState) 
{ 
//	helpstring("O:Normal, 1:Minimiert, 2:Maximiert")]
	GETPWND();
	
WINDOWPLACEMENT wp;

	INITWP(wp);

// erstmal sinnvoll füllen lassen
	pWnd->GetWindowPlacement(&wp);	
	switch (lState) {
	case 0:	
		wp.showCmd = SW_SHOWNORMAL;
		break;

	case 1:
		wp.showCmd = SW_SHOWMINIMIZED;
		break;

	case 2:
		wp.showCmd = SW_SHOWMAXIMIZED;
		break;
	}

	pWnd->SetWindowPlacement(&wp);
	return S_OK; 
}

// Private Helper functions

///////////////////////////////////////////////////////////////////////////////
// Zugriffsfunktion auf das Fenster (wird bei Bedarf erzeugt)
CTRiASChild* CSabisChildWindow::GetWindow()
{
	if (NULL == m_pWnd)	{
		TRY	{
			AFX_MANAGE_STATE(AfxGetAppModuleState());
			m_pWnd = new CTRiASChild(AfxGetMainWnd());
		}
		CATCH(CMemoryException, e) {
			;
		} END_CATCH
	}
	CHECKPOINTER(m_pWnd, NULL);	// endgültiger Check des Pointers 
								// keine weiteren Tests im Quellcode notwendig, 
								// solange dieser Accessor benutzt wird
	return m_pWnd;
}

HRESULT CSabisChildWindow::GetWindowRect(CRect& rect)
{
	GETPWND();

// get the screen coords of the wnd
	pWnd -> GetWindowRect(rect);

// change to client coordinates of the Parent
CWnd* pParent = AfxGetMainWnd(); /*pWnd -> GetParent();*/

	CHECKPOINTERHR(pParent);
	pParent -> ScreenToClient(rect);
	return S_OK;
}


// CToolBarCtrl - Interface ---------------------------------------------------
// File: TOOLBAR.CXX

#include "tfrmpre.hxx"

CToolBarCtrl :: CToolBarCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CToolBarCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CToolBarCtrl :: CToolBarCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CToolBarCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CToolBarCtrl :: ~CToolBarCtrl (void)
{
}

CToolBarCtrl_Imp :: CToolBarCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_ToolBarCtrl, dwInitStyle)
{
}

CToolBarCtrl_Imp :: CToolBarCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_ToolBarCtrl)
{
}

CToolBarCtrl_Imp :: ~CToolBarCtrl_Imp (void)
{
}

int CToolBarCtrl::AddBitmap(int nNumButtons, pBitmap pBitmap)
{ 
	CV_ASSERT(::IsWindow(Handle()));

TBADDBITMAP tbab;

	tbab.hInst = NULL;
	tbab.nID = (UINT)pBitmap->Handle();

return (int) ::SendMessage(Handle(), TB_ADDBITMAP, (WPARAM)nNumButtons, (LPARAM)&tbab);
}

int CToolBarCtrl::AddBitmap(int nNumButtons, ResID nBitmapID)
{ 
	CV_ASSERT(::IsWindow(Handle()));

TBADDBITMAP tbab;

	tbab.hInst = CV_RunTime::ResID_handle (nBitmapID, _AppImpFind(), RT_BITMAP);
	CV_ASSERT(tbab.hInst != NULL);
	
	if (tbab.hInst == NULL)	return false;
	tbab.nID = (UINT)nBitmapID;

return (int) ::SendMessage(Handle(), TB_ADDBITMAP, (WPARAM)nNumButtons, (LPARAM)&tbab);
}

void CToolBarCtrl::SaveState(HKEY hKeyRoot, LPCSTR lpszSubKey, LPCSTR lpszValueName)
{
	CV_ASSERT(::IsWindow(Handle()));

TBSAVEPARAMS tbs;

	tbs.hkr = hKeyRoot;
	tbs.pszSubKey = lpszSubKey;
	tbs.pszValueName = lpszValueName;
	::SendMessage(Handle(), TB_SAVERESTORE, (WPARAM)true, (LPARAM)&tbs);
}

void CToolBarCtrl::RestoreState(HKEY hKeyRoot, LPCSTR lpszSubKey, LPCSTR lpszValueName)
{
	CV_ASSERT(::IsWindow(Handle()));

TBSAVEPARAMS tbs;

	tbs.hkr = hKeyRoot;
	tbs.pszSubKey = lpszSubKey;
	tbs.pszValueName = lpszValueName;
	::SendMessage(Handle(), TB_SAVERESTORE, (WPARAM)false, (LPARAM)&tbs);
}

int CToolBarCtrl::AddString(ResID nStringID)
{
	CV_ASSERT(::IsWindow(Handle()));

HINSTANCE hInst = CV_RunTime::ResID_handle (nStringID, _AppImpFind(), RT_STRING);

	CV_ASSERT(hInst != NULL);
	if (hInst == NULL) return false;

return (int) ::SendMessage(Handle(), TB_ADDSTRING, (WPARAM)hInst, (LPARAM)(UINT)nStringID);
}

void CToolBarCtrl_Imp :: Create (void)
{
	Control_Imp :: Create();
	((CToolBarCtrl *)pRequestor) -> SetButtonStructSize(sizeof(TBBUTTON));
}


// CStatusBarCtrl - Interface -------------------------------------------------
// File: STATBAR.CXX

#include "tfrmpre.hxx"
#if _MSC_VER >= 1100
#include <ospace/except/stdex.h>
#endif // _MSC_VER

CStatusBarCtrl :: CStatusBarCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CStatusBarCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CStatusBarCtrl :: CStatusBarCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CStatusBarCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CStatusBarCtrl :: ~CStatusBarCtrl (void)
{
}

CStatusBarCtrl_Imp :: CStatusBarCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_StatusBarCtrl, dwInitStyle)
{
}

CStatusBarCtrl_Imp :: CStatusBarCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_StatusBarCtrl)
{
}

CStatusBarCtrl_Imp :: ~CStatusBarCtrl_Imp (void)
{
}

int CStatusBarCtrl::GetText(LPCSTR lpszText, int nPane, int* pType)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(nPane < 256);

DWORD dw = ::SendMessage(Handle(), SB_GETTEXT, (WPARAM)nPane, (LPARAM)lpszText);
	
	if (pType != NULL) *pType = HIWORD(dw);

return LOWORD(dw);
}

string CStatusBarCtrl::GetText(int nPane, int* pType)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(nPane < 256);

int nLength = LOWORD(::SendMessage(Handle(), SB_GETTEXTLENGTH, (WPARAM)nPane, 0L));
string str;

	try {
	char *pText = new char [nLength+1];
	DWORD dw = ::SendMessage(Handle(), SB_GETTEXT, (WPARAM)nPane, (LPARAM)pText);

		if (pType != NULL) *pType = HIWORD(dw);

		str = pText;
		delete pText;
	
#if _MSC_VER >= 1100
	} catch (os_length_error) {
#else
	} catch (...) {
#endif // _MSC_VER
		return str;
	}

	return str;
}

int CStatusBarCtrl::GetTextLength(int nPane, int* pType)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(nPane < 256);

DWORD dw = ::SendMessage(Handle(), SB_GETTEXTLENGTH, (WPARAM)nPane, 0L);

	if (pType != NULL) *pType = HIWORD(dw);

return LOWORD(dw);
}

BOOL CStatusBarCtrl::SetBorders(int nHorz, int nVert, int nSpacing)
{ 
	CV_ASSERT(::IsWindow(Handle())); 

int borders[3];

	borders[0] = nHorz;
	borders[1] = nVert;
	borders[2] = nSpacing;

return (BOOL)::SendMessage(Handle(), SB_SETPARTS, 0, (LPARAM)&borders);
}

BOOL CStatusBarCtrl::GetBorders(int& nHorz, int& nVert, int& nSpacing)
{
	CV_ASSERT(::IsWindow(Handle()));

int borders[3];
BOOL bResult = (BOOL)::SendMessage(Handle(), SB_GETBORDERS, 0, (LPARAM)&borders);
	
	if (bResult) {
		nHorz = borders[0];
		nVert = borders[1];
		nSpacing = borders[2];
	}

return bResult;
}


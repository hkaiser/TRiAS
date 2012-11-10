// CSpinButtonCtrl - Interface ------------------------------------------------
// File: UPDOWN.CXX

#include "tfrmpre.hxx"

CSpinButtonCtrl :: CSpinButtonCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CSpinButtonCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CSpinButtonCtrl :: CSpinButtonCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CSpinButtonCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CSpinButtonCtrl :: ~CSpinButtonCtrl (void)
{
}

CSpinButtonCtrl_Imp :: CSpinButtonCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_SpinButtonCtrl, dwInitStyle)
{
}

CSpinButtonCtrl_Imp :: CSpinButtonCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_SpinButtonCtrl)
{
}

CSpinButtonCtrl_Imp :: ~CSpinButtonCtrl_Imp (void)
{
}

void CSpinButtonCtrl::GetRange(int &lower, int& upper)
{
	CV_ASSERT(::IsWindow(Handle()));

DWORD dw = ::SendMessage(Handle(), UDM_GETRANGE, 0, 0l);

	lower = (int)(short)HIWORD(dw);
 	upper = (int)(short)LOWORD(dw);
}

pControl CSpinButtonCtrl::GetBuddy()
{
	return (pControl)(_AppImpFind()->ControlList()->Find((HANDLE)::SendMessage(Handle(), UDM_GETBUDDY, 0, 0l))); 
}

pControl CSpinButtonCtrl::SetBuddy(pControl pWndBuddy)
{ 
	return (pControl)(_AppImpFind()->ControlList()->Find((HWND)::SendMessage(Handle(), UDM_SETBUDDY, (WPARAM)pWndBuddy->Handle(), 0L))); 
}



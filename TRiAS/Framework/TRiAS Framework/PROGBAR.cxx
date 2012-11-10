// CProgressCtrl - Interface --------------------------------------------------
// File: PROGBAR.CXX

#include "tfrmpre.hxx"

CProgressCtrl :: CProgressCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CProgressCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CProgressCtrl :: CProgressCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CProgressCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CProgressCtrl :: ~CProgressCtrl (void)
{
}

CProgressCtrl_Imp :: CProgressCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_ProgressBarCtrl, dwInitStyle)
{
}

CProgressCtrl_Imp :: CProgressCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_ProgressBarCtrl)
{
}

CProgressCtrl_Imp :: ~CProgressCtrl_Imp (void)
{
}


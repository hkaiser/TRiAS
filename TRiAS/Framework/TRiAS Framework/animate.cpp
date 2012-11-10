// CAnimateCtrl - Interface --------------------------------------------------
// File: ANIMATE.CPP

#include "tfrmpre.hxx"

CAnimateCtrl :: CAnimateCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CAnimateCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CAnimateCtrl :: CAnimateCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CAnimateCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CAnimateCtrl :: ~CAnimateCtrl (void)
{
}

CAnimateCtrl_Imp :: CAnimateCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_AnimateCtrl, dwInitStyle)
{
}

CAnimateCtrl_Imp :: CAnimateCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_AnimateCtrl)
{
}

CAnimateCtrl_Imp :: ~CAnimateCtrl_Imp (void)
{
}


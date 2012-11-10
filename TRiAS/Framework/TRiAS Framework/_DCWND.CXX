/*
 *
 *	_ d c w n d . c x x
 *
 *	Copyright (c) Glockenspiel Ltd 1991.
 *
 *	Mods Log:
 *	1.0	sm		Original version
 *
 */
#include "tfrmpre.hxx"

_DLLENTRY CDCWindow :: CDCWindow (HDC hDC, Rectangle &Rc, HDC hTargetDC)
{
CDCWind_Imp *pImp = new CDCWind_Imp (this, Rc);

	if (pImp != NULL) {
	// DC setzen, auf dem gezeichnet werden soll 	
		pImp -> SetDrawDC (hDC);
		pImp -> SetDrawTarget (hTargetDC);
		
		ec_Imp = (EC_Imp *)pImp;	// zugehöriger Implementor
	}
}


_DLLENTRY CDCWindow :: ~CDCWindow (void)
{
}


// Liefert diverse hDC's (ZeichenGrundlage und SkalierungsGrundlage) ----------
HWND _DLLENTRY CDCWindow :: Handle (Service s)
{
	switch (s) {
	case API_WINDOW_TARGETHDC:		// #HK940119
		return Window :: Handle (API_WINDOW_TARGETHDC);

	default:
	case API_WINDOW_HDC:
		break;
	}

return Window :: Handle (API_WINDOW_HDC);
}


// Rendering ------------------------------------------------------------------
BOOL _DLLENTRY CDCWindow :: Render (Rectangle &r)
{
CDCExposeEvt e;

	CV_RunTime :: Event_SetExtra (e, (void *)&r);
	{
	DS_fixup AppFixUp;
	
		return DCExpose (e);
	}
}

 

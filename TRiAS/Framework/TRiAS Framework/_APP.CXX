/* $Header:   G:/cv.win/pvcs/commonvu/src/_app.cxv   3.0.1.0   14 Jul 1992 11:48:10   RONAN  $
 *
 *	_ a p p . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	created 1-9-89 by ferg
 *
 */

#include "tfrmpre.hxx"

_DLLENTRY App::  App()
{
	app_Imp = 0;
}

#ifdef MSCC8
_TF_ENTRY32 int _DLLENTRY CallAppExec(ExecType et)
{
	return _AppImpFind()->Exec ((BOOL**)0, et);
}
/*static*/
_TF_ENTRY32 int	App::Exec (ExecType et, BOOL **ppac)
{
	return _AppImpFind()->Exec(ppac, et);
}
#else
int	  _DLLENTRY App:: Exec	(ExecType et)
{
	return _AppImpFind()->Exec ((BOOL**)0, et);
}
#endif

void   _DLLENTRY App:: Quit	()
{
	App_Imp :: Quit();
}


long   _DLLENTRY App:: Run	(const char *cmd)
{
	int retval = WinExec (cmd, SW_SHOWNORMAL);
	return ((retval > 32) ? TRUE : FALSE); 
}


_DLLENTRY App :: ~App (void)
{
	_AppDelete();
	if ( app_Imp )
	{
		delete	app_Imp;
		app_Imp = NULL ;
	}
}

HINSTANCE _DLLENTRY App :: Handle ( Service s_ID )
{
	return _AppImpFind() -> Handle(s_ID);
}

_DLLENTRY SystemApp :: SystemApp  (  uint seg, HINSTANCE hInst, HINSTANCE hPrev, const char* CmdL, int scmd) 
{
	app_Imp =  new App_Imp ( this, seg, hInst, hPrev, CmdL, scmd );
}

#if defined(WIN32)
PRETRANSLATEPROC App::AttachPreTranslateProc (PRETRANSLATEPROC pF)
{
	return app_Imp -> AttachPreTranslateMsgProc (pF);
}

PRETRANSLATEPROC App::DetachPreTranslateProc (void)
{
	return app_Imp -> DetachPreTranslateMsgProc();
}
IDLEPROC App::AttachIdleProc (IDLEPROC pF)
{
	return app_Imp -> AttachIdleProc (pF);
}

IDLEPROC App::DetachIdleProc (void)
{
	return app_Imp -> DetachIdleProc();
}

// #HK960821
BOOL App::QuitOnLast (void)
{
	return app_Imp->QuitOnLast();
}

void App::SetQuitOnLast (BOOL fFlag)
{
	app_Imp->SetQuitOnLast (fFlag);
}

#endif // WIN32


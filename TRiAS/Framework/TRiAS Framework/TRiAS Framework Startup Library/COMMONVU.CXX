/* $Header:   G:/cv.win/pvcs/commonvu/src/commonvu.cxv   3.0.1.0   14 Jul 1992 11:57:26   RONAN  $
 *
 *	C O M M O N V U . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	------ Milestone	2.. Beta 2 ship --------
 *	0.1	ferg	11oct88	Presentation Manager integration. Delimited
 *						by PM and MSWIND #ifdef's.
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.3 jk		02dec88	Fast Compile defines added
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 */
#include "tfrmlib.hxx"

#if !defined(WIN32)
#include <FreeStor.hxx>
#endif

#ifdef MSCC8
extern int _DLLENTRY CallAppExec(ExecType et);
#endif

pApp 	AppInst = 0;

void		CV_Out_of_Memory (  )
{
	FatalAppExit(0, "TRiAS® Framework: Out of memory");
	FatalExit (0x280);
}	// End of FUNCTION "CV_Out_of_Memory"


#if !defined(WIN32)
int	  _pascal WinMain	(HINSTANCE hInst, HINSTANCE hPrevInst, pchar CmdL, int cmdShow )
#else
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, pchar CmdL, int cmdShow )
#endif
{
#if !defined(WIN32)
#if defined(_DEBUG)
	CWindowsFS parfs;
	CFindBugFS fs (&parfs);
#else
	CWindowsFS fs;
#endif

	fs.Select();

// Set up the out of memory handler
	fs.SetNewHandler((pNewHandler)CV_Out_of_Memory);
#endif	// WIN32

// Create an Application Instance
	CV_RunTime :: App_new (hInst, hPrevInst, CmdL, cmdShow);

// call application specific initialization
#if !defined(WIN32)
CFreeStore *pFS = AppInst -> InitApp (&fs);

	if (pFS == NULL) {	// Initialisierungsfehler
		delete AppInst;
		return 0;
	}
	
	if (pFS != &fs)	pFS -> SetNewHandler((pNewHandler)CV_Out_of_Memory);
#else
	AppInst -> InitApp (NULL);
#endif // WIN32

// Now start the application.
	AppInst->Start (CV_RunTime :: pApp_to_pImp(AppInst) -> ArgC(), 
		(const char**)(CV_RunTime :: pApp_to_pImp(AppInst) -> ArgV()));

// call application specific deinitialization
	AppInst -> DeInitApp();

// delete the application
	delete AppInst;

return 0;
}	// End of Application Mainline


pApp CV_RunTime:: 	App_new (HINSTANCE current, HINSTANCE prev, pchar c, int d)
{	
#ifdef __BCPLUSPLUS__
	AppInst = (pApp) new SystemApp(_DS, current, prev, c, d );
#else
#if !defined(WIN32)
	AppInst = (pApp) new SystemApp (_getDS(), current, prev, c, d );
#else
	AppInst = (pApp) new SystemApp (0, current, prev, c, d);
#endif // WIN32
#endif
	pApp_to_pImp(AppInst) -> IdleFunc = &App::Idle;
	_AppInsert( AppInst );
	return AppInst;
}

#ifdef MSCC8
int	App :: Exec	(ExecType et)
{
	return CallAppExec (et);
}
#endif

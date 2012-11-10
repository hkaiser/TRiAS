/* $Header:   G:/cv.win/pvcs/commonvu/src/_main.cxv   3.0.1.0   14 Jul 1992 11:55:44   RONAN  $
 *
 *	_ M A I N . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0 jk		29nov88 ------ Milestone 2A. Beta 2A ship date. ------
 *	0.1 jk		02dec88 Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2	rs		23aug89	Debugging info
 *
 *  ????		????????-------Release for Windows3.0----------------
 *      ????	hl	27sep89		WEP function                                      
 *
 *
 *
 *
 */

#include "tfrmpre.hxx"
#include	<_Link.hxx>

CVLinked_List 	Task_List; 				// * 0.2 *
pApp_Imp    	LastAppUsed = 0;
#if !defined(WIN32)
HTASK		LastHandleUsed = 0;
#else
LPVOID		LastHandleUsed = NULL;
#endif

#if !defined(WIN32)
extern "C" int PASCAL_FUNC _DLLENTRY LibMain(HINSTANCE hLib, WORD , WORD , char *)
{
	StaticDataInit(hLib);		// * 1.2 *
	return 1;
}	

// Provided for windows 3.0 support
extern "C" int	  PASCAL_FUNC WEP( int )
{
	StaticDataCleanup();
	return 1;
}
#else

bool __stdcall DllMain (HINSTANCE hLib, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		StaticDataInit (hLib);		// * 1.2 *
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		StaticDataCleanup();
		break;
	}

return true;
}

#endif

extern "C" _TF_ENTRY32 pApp_Imp PASCAL_FUNC _AppImpFind (void)
{
#if !defined(WIN32)
HTASK hTask = GetCurrentTask();
#else
LPVOID hTask = GetCurrentProcess();
#endif

	if (hTask == LastHandleUsed)
		return LastAppUsed;
	else {
		LastHandleUsed = hTask;
		return LastAppUsed = (pApp_Imp) Task_List.TaskFind((HANDLE)hTask );
	}
}


extern "C" _TF_ENTRY32 void   PASCAL_FUNC _DLLENTRY _AppInsert( pApp AppInst )
{
#if !defined(WIN32)
HTASK hTask = GetCurrentTask();
#else
LPVOID hTask = GetCurrentProcess();
#endif

	Task_List.Insert((HANDLE)hTask , (void *) CV_RunTime :: pApp_to_pImp(AppInst) );
}

extern "C" _TF_ENTRY32 void  PASCAL_FUNC _DLLENTRY _AppDelete()
{
#if !defined(WIN32)
HTASK hTask = GetCurrentTask();
#else
LPVOID hTask = GetCurrentProcess();
#endif

	if (hTask == LastHandleUsed)
	{
		LastHandleUsed = 0;
		LastAppUsed = 0;
	}
	Task_List.Delete((HANDLE)hTask);
}														// * 0.2 End *



	

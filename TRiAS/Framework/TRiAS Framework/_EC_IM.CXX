/* $Header:   G:/cv.win/pvcs/commonvu/src/_ec_im.cxv   1.2   22 Aug 1991 15:17:10   RONAN  $
 *
 *	_ c o n t e x t . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	ferg	05oct88	------ Milestone 2.. Beta 2 shipped ----------
 *	0.1	ferg	02nov88	EventContext::~EventContext() and EventContext::Create()
 *						moved here from Context.cxx. Also now get AppInst
 *						from DLL. Context.cxx is now defunct.
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.3	jk		02dec88	Fast Compile defines added.
 *	0.4 ferg	06dec88	virtual Cleanup function executes after Event handler.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		24Nov89	Support for void return values to event handlers
 *	1.3 rs		24Nov89	Added EventContext constructor
 *	1.4 rs		20Feb90	Only remove window from list if handle is still valid
 */

#include "tfrmpre.hxX"
#include	<_Link.hxx>  			// * 0.1  Begin *

EC_Imp::  ~EC_Imp	()
{
	if (hEContext)				// * 1.4 *
		_AppImpFind() -> ContextList() -> Delete ((HANDLE)hEContext );
}	// End of "EC_Imp" DESTRUCTOR


EC_Imp ::  EC_Imp (EventContext *req)							// * 1.3 *
{
	pRetval = 0;
	hEContext = 0;
	pRequestor = req;
}



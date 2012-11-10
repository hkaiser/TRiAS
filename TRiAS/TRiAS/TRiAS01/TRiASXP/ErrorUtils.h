// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 14.08.2001 23:36:10 
//
// @doc
// @module ErrorUtils.h | Definition of error related stuff

#if !defined(_ERRORUTILS_H__3FFB3640_9391_41C6_8039_C478F9354E74__INCLUDED_)
#define _ERRORUTILS_H__3FFB3640_9391_41C6_8039_C478F9354E74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Error codes
#define XP_NOERROR				0
#define XP_ERROR				1

#define MAX_SERVER_ERROR		20000
#define XP_ASTEXT_ERROR			MAX_SERVER_ERROR+1

///////////////////////////////////////////////////////////////////////////////
// send szErrorMsg to client
inline
RETCODE printError (SRV_PROC *pSrvProc, DBINT iError, DBUSMALLINT iLine, CHAR *szErrorMsg)
{
	srv_sendmsg(pSrvProc, SRV_MSG_ERROR, iError, SRV_INFO, 1, NULL, 0, iLine, szErrorMsg, SRV_NULLTERM);
	srv_senddone(pSrvProc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return XP_ERROR;
}

#endif // !defined(_ERRORUTILS_H__3FFB3640_9391_41C6_8039_C478F9354E74__INCLUDED_)

/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: SHAlloc.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 6:45p
 * Updated in $/Products/SmallParser
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/


#include "stdafx.h"

#ifdef _DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "shalloc.h"
#include <windows.h>

#define new DEBUG_NEW

CAllocationGuarder::CAllocationGuarder( const char *szFile, int nLine )
{
ResetState( szFile, nLine );
}

CAllocationGuarder::~CAllocationGuarder()
{
	Report();
}

void CAllocationGuarder::Report()
{
#if defined(_REPORT_MEMORY_ALLOC)
	OutputDebugString( "Reporting memory allocations from file ");
	OutputDebugString( m_strFile.c_str() );
	OutputDebugString( " line ");
	OutputDebugString( m_strLine.c_str() );
	OutputDebugString( " \n");

	_CrtMemDumpAllObjectsSince( &m_MemState );
#endif // defined(_REPORT_MEMORY_ALLOC)
}

void CAllocationGuarder::ResetState( const char *szFile, int nLine )
{
#if defined(_REPORT_MEMORY_ALLOC)
	m_strFile = szFile;
	char szBuf[20];
	sprintf( szBuf, "%d", nLine );
	m_strLine = szBuf;
	_CrtMemCheckpoint( &m_MemState );
#endif // defined(_REPORT_MEMORY_ALLOC)
}
void *DebugMalloc( size_t nSize, char *szFile, int nLine )
{
	return _malloc_dbg(nSize, _NORMAL_BLOCK, szFile, nLine);
}



#undef new
void* __cdecl operator new(size_t nSize, char *lpszFileName, int nLine)
{
	void* pResult;
//	if ( nSize == 12 )
//		{
//		int j;
//		j = 0;
//		}
	pResult = _malloc_dbg(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
	return pResult;
}

void __cdecl operator delete(void* p, char *lpszFileName, int nLine)
{
		_free_dbg(p, _NORMAL_BLOCK);
}

#endif
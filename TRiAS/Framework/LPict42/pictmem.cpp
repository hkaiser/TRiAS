#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_WINC_SEG
#pragma code_seg(LAFX_WINC_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: pictmem.cpp 1.1 1996/07/12 10:35:52 andy Exp $";
/* $Log: pictmem.cpp $
// Revision 1.1  1996/07/12  10:35:52  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CMemBlock, CObject, 1 );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////

CMemBlock::CMemBlock( long lSize, UINT Flags ) {
	Initialize( );
	Alloc( lSize, Flags );
}

CMemBlock::~CMemBlock( ) {
	if( NULL == m_hMem )
		return;
	if( TRUE == m_bIsLocked )
		::GlobalUnlock( m_hMem );
	::GlobalFree( m_hMem );
}

void CMemBlock::Initialize( ) {
	m_bIsLocked = FALSE;
	m_hMem = NULL;
	m_lBlockSize = 0L;
	m_pData = NULL;
}

void CMemBlock::ReInitialize( ) {
	if( NULL == m_hMem )
		return;
	if( TRUE == m_bIsLocked )
		::GlobalUnlock( m_hMem );
	m_bIsLocked = FALSE;
	::GlobalFree( m_hMem );
	m_lBlockSize = 0L;
	m_hMem = NULL;
}

BOOL CMemBlock::_Alloc( long dwSize, UINT uFlags ) {
	if( NULL == ( m_hMem = ::GlobalAlloc( uFlags, dwSize ) ) ) {
		m_lBlockSize = 0L;
		return FALSE;
	}
	m_lBlockSize = dwSize;
	return TRUE;
}

BOOL CMemBlock::Alloc( long dwSize, UINT uFlags ) {
	if( dwSize == m_lBlockSize )
		return TRUE;
	UnLock( );

	if( 0L == dwSize ) {
		ReInitialize( );
		return TRUE;
	}
	if( 0L == m_lBlockSize ) {
		return _Alloc( dwSize, uFlags );
	}
	ReInitialize( );
	return _Alloc( dwSize, uFlags );
}

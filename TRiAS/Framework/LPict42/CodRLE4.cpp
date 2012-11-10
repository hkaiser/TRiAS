#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCodecRLE4, CPictCodec );

#define	new	DEBUG_NEW

void CCodecRLE4::Reset( ) {
}

BOOL CCodecRLE4::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	ASSERT( NULL != m_pPicture );
	return FALSE;
}

long CCodecRLE4::DecodeLine( long nBytes ) {
	return nBytes;
}

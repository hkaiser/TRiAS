#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	new	DEBUG_NEW

IMPLEMENT_DYNAMIC( CPictCodec, CObject );

BOOL CPictCodec::Decode( const CRect& rcPict ) {
	long	line = m_pPicture->AlignTop( rcPict.top );
	long	decodedBytes = 0;
	long	restBytes = 0;
	long	rowsPerStrip = m_pPicture->GetStripRect().Height();
	long	rowInStrip = 0;

	m_lineLength = m_pPicture->GetImageRect().Width();
	m_srcPos = m_dstPos = 0;

	while( restBytes = m_pPicture->FillBuffer( line, m_srcPos, restBytes ) ) {
		if( 0 == restBytes || !Init() )
			return FALSE;

		m_srcEnd = restBytes;
		m_dstPos = 0;

		for( ; line < rcPict.top && rowInStrip < rowsPerStrip; ) {
			decodedBytes = DecodeLine( restBytes );
			m_srcStart += decodedBytes;
			restBytes -= decodedBytes;
			m_dstPos = 0;
			line++;
			rowInStrip++;
			if( 0 == restBytes )
				break;
		}
		for( ; line < rcPict.bottom && rowInStrip < rowsPerStrip; ) {
			decodedBytes = DecodeLine( restBytes );
			restBytes -= decodedBytes;
			m_pPicture->StoreScanLine( m_pDst, line, rcPict );
			m_dstPos = 0;
			line++;
			rowInStrip++;
			if( 0 == restBytes )
				break;
		}
		if( line >= rcPict.bottom )
			break;
		if( rowInStrip == rowsPerStrip ) {
			restBytes = 0;
			rowInStrip = 0;
		}
		if( 0 == restBytes )
			m_srcPos = 0;
	}
	return TRUE;
}

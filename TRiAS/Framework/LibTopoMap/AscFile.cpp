#include "stdafx.h"
#include "libTopoMap/AscFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

ASC_HEADER& ASC_HEADER::operator=( const ASC_HEADER& hdr )
{
	m_strCoordTrans = hdr.m_strCoordTrans;
	m_dwOffsetX = hdr.m_dwOffsetX;
	m_dwOffsetY = hdr.m_dwOffsetY;
	m_dwScale11 = hdr.m_dwScale11;
	m_dwScale12 = hdr.m_dwScale12;
	m_dwScale21 = hdr.m_dwScale21;
	m_dwScale22 = hdr.m_dwScale22;
	return *this;
}

void ASC_HEADER::Init()
{
	m_strCoordTrans.Empty();
	m_dwOffsetX = 0.0;
	m_dwOffsetY = 0.0;
	m_dwScale11 = 1.0;
	m_dwScale12 = 0.0;
	m_dwScale21 = 0.0;
	m_dwScale22 = 1.0;
}

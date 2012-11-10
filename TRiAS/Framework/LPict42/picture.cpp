// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:54:55 
//
// @doc
// @module picture.cpp | Definition of the <c CPictureBase> class

#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CPicture, CObject);
IMPLEMENT_DYNAMIC(CPictureBase, CPicture);
IMPLEMENT_DYNAMIC(CPictException, CException);

#define	new	DEBUG_NEW

///////////////////////////////////////////////////////////////////////////////
// allgemeine Basisklasse
CPicture::CPicture()
{
	m_pTagMap			= (void*) new CTagMap;
	m_pFile				= NULL;
}

CPicture::~CPicture()
{
	if (NULL != m_pFile) Detach();
	delete (CTagMap *) m_pTagMap;
}

void CPicture::Init()
{
	m_strPictName.Empty();
	m_rcPicture.SetRectEmpty();
	m_rcPictInCore.SetRectEmpty();
	m_rcImage.SetRectEmpty();
	m_rcImageInCore.SetRectEmpty();
	m_rcStrip.SetRectEmpty();
	m_szStrips = CSize(1, 1);

	m_samplesPerPixel	= 0;
	m_bitsPerSample		= 0;
	m_colorspace		= PICT_UNKNOWN_COLOR;
	m_compression		= PICT_UNKNOWN_COMPR;
//	m_orientation		= PICT_UNKNOWN_ORIENT;
	m_nFillOrder			= PICT_FILLORD_SEVENISZERO;
	m_nPlanarConfiguration	= PICT_UNKNOWN_PLANARCFG;
	m_orientation			= PICT_ORIENT_UPPERLEFT;
//	m_XResolution		= 1.0;
//	m_YResolution		= 1.0;

	TAGMAP.erase(TAGMAP.begin(), TAGMAP.end());
	TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG( PICT_PROP_SAMPLESPERPIXEL, (WORD) m_samplesPerPixel );
	TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG( PICT_PROP_BITSPERSAMPLE, (WORD) m_bitsPerSample );
	TAGMAP[PICT_PROP_COLORSPACE] = TAG( PICT_PROP_COLORSPACE, (WORD) m_colorspace );
	TAGMAP[PICT_PROP_COMPRESSION] = TAG( PICT_PROP_COMPRESSION, (WORD) m_compression );
	TAGMAP[PICT_PROP_ORIENTATION] = TAG( PICT_PROP_ORIENTATION, (WORD) m_orientation );
	TAGMAP[PICT_PROP_RESOLUTIONUNIT] = TAG( PICT_PROP_RESOLUTIONUNIT, (WORD) PICT_UNIT_NOUNIT );
	TAGMAP[PICT_PROP_XRESOLUTION] = TAG( PICT_PROP_XRESOLUTION, (ULONG) 1, (ULONG) 1 );
	TAGMAP[PICT_PROP_YRESOLUTION] = TAG( PICT_PROP_YRESOLUTION, (ULONG) 1, (ULONG) 1 );
}

///////////////////////////////////////////////////////////////////
// es werden nur diejenigen Bildeigenschaften übertragen, die
// unabhängig vom Bildformat sind...

BOOL CPicture::Clone(CPicture *pI, CPictException *pE /*= NULL*/ ) 
{
	ASSERT(pI->IsKindOf(RUNTIME_CLASS(CPicture)));
	ASSERT_VALID(pI);
	Init();

	CTagMap::const_iterator i;
	CTagMap* pMap = (CTagMap*) pI->m_pTagMap;

	for( i = pMap->begin(); i != pMap->end(); ++i )
		TAGMAP[(*i).first] = (*i).second;

//	SetXResolution( pI->GetXResolution() );
//	SetYResolution( pI->GetYResolution() );

BOOL bRet = TRUE;

	m_samplesPerPixel = pI->GetSamplesPerPixel();
	m_bitsPerSample = pI->GetBitsPerSample();

	SetPictRect( pI->GetPictRect() );
	return bRet;
}

BOOL CPicture::GetTag( const PICT_PROPERTY tagNum, TAG& rTag ) const 
{
	CTagMap::const_iterator i = TAGMAP.find( tagNum );
	if( i == TAGMAP.end() )
		return FALSE;
	rTag = (*i).second;
	return TRUE;
}

BOOL CPicture::SetTag( const PICT_PROPERTY tagNum, const TAG& rTag ) 
{
	CTagMap::const_iterator i = tagMasterMap.find( tagNum );
	if( -1 == (*i).first )
		return FALSE;
	if( rTag.Type() != (*i).second.Type() )
		return FALSE;
	TAGMAP[tagNum] = rTag;
	return TRUE;
}

BOOL CPicture::MergeTag( const PICT_PROPERTY tagNum, LPCTSTR lpszString ) 
{
	CTagMap::const_iterator i = tagMasterMap.find( tagNum );
	if( -1 == (*i).first )
		return FALSE;
	if( PICT_DATA_ASCII != (*i).second.Type() )
		return FALSE;
	CString S = TAGMAP[tagNum].strVal();
	if( NULL != strstr( S, lpszString ) )
		return TRUE;
	if( !S.IsEmpty() )
		S += _T("|");
	S += lpszString;
	TAGMAP[tagNum] = TAG( tagNum, S, S.GetLength() + 1 );
	return TRUE;
}

BOOL CPicture::Attach(CFile* pFile) 
{
	ASSERT(NULL == m_pFile);
	ASSERT_VALID(pFile);

	Init( );
	return NULL != (m_pFile = pFile);
}

void CPicture::Detach() 
{
	m_pFile = NULL;
}

void CPicture::SetXResolution( double res ) 
{
	m_XResolution = res;
//	long	num, denom;
//	dbl2ratio( res, num, denom );
//	TAGMAP[TAGXRESOLUTION] = TAG( TAGXRESOLUTION, (ULONG) num, (ULONG) denom );
}
void CPicture::SetYResolution( double res ) 
{
	m_YResolution = res;
//	long	num, denom;
//	dbl2ratio( res, num, denom );
//	TAGMAP[TAGYRESOLUTION] = TAG( TAGYRESOLUTION, (ULONG) num, (ULONG) denom );
}

BOOL CPicture::SetCoreRect(const CRect& rcNewCore) 
{
CRect	rcCore = rcNewCore.IsRectNull() ? m_rcPicture : rcNewCore;
long	bytesPerSample = (m_bitsPerSample + 7) / 8;

	m_rcImageInCore.left = rcCore.left * m_bitsPerSample;
	m_rcImageInCore.left /= 8;						// Byteposition
	m_rcImageInCore.left /= (4 * bytesPerSample);	// am DWORD ausrichten
	m_rcImageInCore.left *= (4 * bytesPerSample);

	m_rcImageInCore.right = Align(rcCore.right, m_bitsPerSample, sizeof(DWORD));
	m_rcPictInCore.left = (m_rcImageInCore.left * 8) / m_bitsPerSample;
	m_rcPictInCore.right = (m_rcImageInCore.right * 8) / m_bitsPerSample;
	m_rcPictInCore.right = min(m_rcPictInCore.right, m_rcPicture.right);

	m_rcPictInCore.top = m_rcImageInCore.top = max(rcCore.top, 0);
	m_rcPictInCore.bottom = m_rcPictInCore.top + rcCore.Height();
	m_rcPictInCore.bottom = min(m_rcPictInCore.bottom, m_rcPicture.bottom);
	m_rcImageInCore.bottom = m_rcPictInCore.bottom;

	return TRUE;
}

BOOL CPicture::Read(const CRect& rcSrc) 
{
BOOL	bRet = TRUE;
CRect	rcPict;

	if (rcSrc.left >= m_rcPictInCore.left &&
		rcSrc.top >= m_rcPictInCore.top &&
		rcSrc.right <= m_rcPictInCore.right &&
		rcSrc.bottom <= m_rcPictInCore.bottom)
	{
		return TRUE;
	}

CString	S = this->GetBlockName();
CString	S1;

#ifdef _DEBUG
	goto ReadNew;
#endif

	::AfxExtractSubString( S1, S, 0, '\t' );
	if( S1.IsEmpty() || 0 != strcmp( m_strPictName, S1 ) )
		goto ReadNew;
	::AfxExtractSubString( S1, S, 1, '\t' );
	rcPict.left = atol( S1 );
	if( rcSrc.left < rcPict.left )
		goto ReadNew;
	::AfxExtractSubString( S1, S, 2, '\t' );
	rcPict.top = atol( S1 );
	if( rcSrc.top < rcPict.top )
		goto ReadNew;
	::AfxExtractSubString( S1, S, 3, '\t' );
	rcPict.right = atol( S1 );
	if( rcSrc.right > rcPict.right )
		goto ReadNew;
	::AfxExtractSubString( S1, S, 4, '\t' );
	rcPict.bottom = atol( S1 );
	if( rcSrc.bottom > rcPict.bottom )
		goto ReadNew;
	this->CacheHit();

	return SetCoreRect( rcPict );

ReadNew:

	this->CacheHit(FALSE);

	if( !SetCoreRect( rcSrc ) ) {
		SetCoreRect( CRect( 0, 0, 0, 0 ) );
		return FALSE;
	}

	if( PICT_COMPR_NOCOMPR == m_compression )
		bRet = this->ReadRaw(rcSrc);
	else 
		bRet = this->Decode(rcSrc);
	
	if (bRet) {
		S.Format( _T("%s\t%ld\t%ld\t%ld\t%ld}"),
			m_strPictName,
			m_rcPictInCore.left, m_rcPictInCore.top, m_rcPictInCore.right, m_rcPictInCore.bottom );
		this->SetBlockName(S);
	}
	return bRet;
}

void CPicture::Serialize(CArchive& ar) 
{
	CObject::Serialize(ar);
}

BOOL CPicture::GetGeoPoints (GCPList *pGcpList, CPictException *e)
{
	return FALSE;		// normalerweise keine GCP's
}

BOOL CPicture::GetGeoPointCS (IUnknown **ppICS, GCPList &rGcpList, CPictException *e)
{
	return FALSE;		// normalerweise keine GCP's, also kein CS
}

BOOL CPicture::WantsToCorrectGeoPoints()
{
	return FALSE;		// normalerweise keine Korrekturen notwendig
}

BOOL CPicture::CorrectGeoPoints (CSize &rSize, GCPList &GCPList, int iSubFile, CPictException *e)
{
	return FALSE;		// normalerweise keine Korrekturen notwendig
}

//////////////////////////////////////////////////////////////////////////
// BasisKlasse für Bilder mit interner Behandlung
const int maxClutEntries = 256;
#define	Size32K		( 32 * Size1K )

#ifdef _WIN32
const int tmpBufSize = Size512K;
#else
const UINT tmpBufSize = Size64K - 1;
#endif

CPictureBase::CPictureBase( ) 
{
	m_pMemBlock			= new CMemBlock( Size512K );
	m_pMemBlock->SetBlockName( _T("MAIN internal") );
	m_bHaveOwnMemory	= TRUE;
	m_pTmpBlock			= new CMemBlock( tmpBufSize );
	m_pTmpBlock->SetBlockName( _T("TEMP internal") );
	m_nColors			= 0;
	m_pClut				= (LPRGBQUAD) new char[ maxClutEntries * sizeof( RGBQUAD ) ];
	m_pFilters			= NULL;
	m_pCodec			= NULL;
	m_rgbTranspColor.rgbRed	
		= m_rgbTranspColor.rgbGreen
		= m_rgbTranspColor.rgbBlue
		= m_rgbTranspColor.rgbReserved
		= 0
		;
}

CPictureBase::CPictureBase( CMemBlock *pMemBlock ) 
{
	m_pMemBlock			= pMemBlock;
	m_bHaveOwnMemory	= FALSE;
	m_pTmpBlock			= new CMemBlock( tmpBufSize );
	m_pTmpBlock->SetBlockName( _T("TEMP internal") );
	m_nColors			= 0;
	m_pClut				= (LPRGBQUAD) new char[ maxClutEntries * sizeof( RGBQUAD ) ];
	m_pFilters			= NULL;
	m_pCodec			= NULL;
}

CPictureBase::~CPictureBase( ) 
{
	if( TRUE == m_bHaveOwnMemory ) delete m_pMemBlock;
	if( NULL != m_pClut ) delete m_pClut;
	if( NULL != m_pFilters ) delete m_pFilters;
	if( NULL != m_pCodec ) delete m_pCodec;
	delete m_pTmpBlock;
}

void CPictureBase::Init( ) 
{
	CPicture::Init();

	m_nUsedColors		= 0;
	memset( (void FAR*) m_pClut, 0x00, maxClutEntries * sizeof( RGBQUAD ) );
	if( NULL != m_pCodec ) {
		ASSERT_KINDOF( CPictCodec, m_pCodec );
		delete m_pCodec;
	}
	m_pCodec = NULL;
}

///////////////////////////////////////////////////////////////////
// es werden nur diejenigen Bildeigenschaften übertragen, die
// unabhängig vom Bildformat sind...

BOOL CPictureBase::Clone( CPicture *pI, CPictException *pE /*= NULL*/ ) 
{
	if(!CPicture::Clone(pI, pE))
		return FALSE;

	ASSERT(pI->IsKindOf(RUNTIME_CLASS(CPictureBase)));

CPictureBase *pPB = (CPictureBase *)pI;
BOOL bRet = TRUE;

	bRet = bRet && SetColorspace( pPB->GetColorspace(), pE );
	bRet = bRet && SetOrientation( pPB->GetOrientation(), pE );

	memcpy( (void FAR*) m_pClut, (void FAR*) pPB->m_pClut, m_nColors * sizeof(RGBQUAD));
	m_rcStrip = pPB->m_rcStrip;
	m_szStrips = pPB->m_szStrips;
	return bRet;
}

///////////////////////////////////////////////////////////////////
// -1 markiert reales Feldende, NULL genutztes Feldende
// nach den Zeigern auf die Filter muß immer ein NULL-Zeiger stehen
// ansonsten sind beim Durchlaufen des Arrays zwei Testbedingungen
// notwendig: while( *pFilter && -1 != *(pFilter+1) )
// Mit dem garantierten NULL-Zeiger: while( *pFilter )

void CPictureBase::AddColorFilter( CColorFilter *pNewFilter ) 
{
	if( NULL == m_pFilters ) {
		m_pFilters = new CColorFilter*[10];
		memset( m_pFilters, 0x00, 10 * sizeof( CColorFilter* ) );
		m_pFilters[9] = (CColorFilter*) (-1);
	}
	CColorFilter	**pFilter = m_pFilters;
	for( int i = 0; *pFilter; ++i )
		pFilter++;
	*pFilter = pNewFilter;
	if( (CColorFilter*)(-1) == *(pFilter+1) ) {
		i += 2;
		ASSERT( 0 == i % 10 );
		CColorFilter** pArray = new CColorFilter*[i+10];
		memset( pArray, 0x00, (i+10) * sizeof( CColorFilter* ) );
		pArray[i + 10 - 1] = (CColorFilter*) (-1);
		memcpy( (void*) pArray, (void*) m_pFilters, ( i - 1 ) * sizeof( CColorFilter* ) );
		delete m_pFilters;
	}
}

void CPictureBase::RemoveColorFilters() 
{
	if( NULL != m_pFilters ) {
		CColorFilter*	*pFilter = m_pFilters;
		for( ; *pFilter; ++pFilter ) {
			ASSERT_KINDOF( CColorFilter, *pFilter );
			*pFilter = NULL;
		}
	}
}

BOOL CPictureBase::GetClut( LPRGBQUAD pClut, long items ) 
{
	if (m_bitsPerSample == 1 && items > 1) return FALSE;
	if (m_bitsPerSample == 4 && items > 16) return FALSE;
	if (m_bitsPerSample == 8 && items > 256) return FALSE;

	memcpy(pClut, m_pClut, items * sizeof(RGBQUAD));
//	m_nColors = m_nUsedColors = items;
	return TRUE;
}

BOOL CPictureBase::SetClut( LPRGBQUAD pClut, long items ) 
{ 
	if (m_bitsPerSample == 1 && items > 1) return FALSE;
	if (m_bitsPerSample == 4 && items > 16) return FALSE;
	if (m_bitsPerSample == 8 && items > 256) return FALSE;
	
	memcpy(m_pClut, pClut, items * sizeof(RGBQUAD));
	m_nColors = m_nUsedColors = items;

	return TRUE;
}

BOOL CPictureBase::SetCoreRect(const CRect& rcNewCore) 
{
	if (!CPicture::SetCoreRect(rcNewCore))
		return FALSE;

	while (m_rcImageInCore.Width() * m_rcImageInCore.Height() > m_pMemBlock->Size()) {
		if (!m_pMemBlock->Alloc(m_pMemBlock->Size() + Size512K))
			return FALSE;
	}
	return TRUE;
}

CString CPictureBase::GetBlockName()
{
	return m_pMemBlock->GetBlockName();
}

void CPictureBase::SetBlockName(LPCTSTR pcBlockName)
{
	m_pMemBlock->SetBlockName(pcBlockName);
}

void CPictureBase::CacheHit(BOOL bHit)
{
	m_pMemBlock->CacheHit(bHit);
}

BOOL CPictureBase::Decode(const CRect& rcRect)
{
	if (NULL == m_pCodec)
		return FALSE;
	return m_pCodec->Decode(rcRect);
}

void CPictureBase::Serialize( CArchive& ar ) 
{
	CPicture::Serialize( ar );
}

static CRuntimeClass* rtPicturesOld[] = {
	RUNTIME_CLASS(CBmpPicture),
	RUNTIME_CLASS(CTifPicture),
	RUNTIME_CLASS(CPolyGISPicture),
	NULL
} ;

static CRuntimeClass* rtPictures[] = {
    RUNTIME_CLASS( CLeadToolsPicture ),
	RUNTIME_CLASS( CPolyGISPicture ),
	NULL
} ;

static CRuntimeClass* rtPicturesWritable[] = {
	RUNTIME_CLASS( CBmpPicture ),
	RUNTIME_CLASS( CTifPicture ),
	RUNTIME_CLASS( CPolyGISPicture ),
	NULL
} ;

AFX_EXT_API CRuntimeClass* GetPictureType( CFile* pFile, CPictException	*e /*=NULL*/ ) 
{
CRegKey key;
BOOL bUseOld = FALSE;
DWORD dwUseOldPictures = 0;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software"), KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, TEXT("Config"), KEY_READ) &&
        ERROR_SUCCESS == key.QueryValue(dwUseOldPictures, "UseOldPictures"))
	{
        bUseOld = dwUseOldPictures ? TRUE : FALSE;
    }

	CRuntimeClass	**pRTCurr = bUseOld ? rtPicturesOld : rtPictures;
	CRuntimeClass	*pRT = NULL;
	CPicture		*pPict = NULL;
		
	for(/**/; *pRTCurr; pRTCurr++ ) {
		pPict = (CPicture*) (*pRTCurr)->CreateObject();
		VERIFY(pPict->Attach(pFile));
		if( pPict->ReadHeader(e) )
			pRT = *pRTCurr;

		pPict->Detach();
		delete pPict;
		if(NULL != pRT)
			return pRT;
	}
	return NULL;
}

AFX_EXT_API CRuntimeClass* GetWritablePictureType( CFile* pFile, CPictException	*e /*=NULL*/ ) 
{
CRegKey key;
BOOL bUseOld = FALSE;
DWORD dwUseOldPictures = 0;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software"), KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, TEXT("Config"), KEY_READ) &&
        ERROR_SUCCESS == key.QueryValue(dwUseOldPictures, "UseOldPictures"))
	{
        bUseOld = dwUseOldPictures ? TRUE : FALSE;
    }

	CRuntimeClass	**pRTCurr = bUseOld ? rtPicturesOld : rtPicturesWritable;
	CRuntimeClass	*pRT = NULL;
	CPicture		*pPict = NULL;
		
	for(/**/; *pRTCurr; pRTCurr++ ) {
		pPict = (CPicture*) (*pRTCurr)->CreateObject();
		VERIFY(pPict->Attach(pFile));
		if( pPict->ReadHeader(e) )
			pRT = *pRTCurr;

		pPict->Detach();
		delete pPict;
		if(NULL != pRT)
			return pRT;
	}
	return NULL;
}

void CPictureBase::SetTransparency( int nChannel, COLORREF rgb ) 
{
	if (1 == m_bitsPerSample || 8 == m_bitsPerSample) {
		m_rgbTranspColor.rgbRed	= GetRValue( rgb );
		m_rgbTranspColor.rgbGreen = GetGValue( rgb );
		m_rgbTranspColor.rgbBlue = GetBValue( rgb );
		m_rgbTranspColor.rgbReserved = nChannel;
	}
    else {
		CString	S;
		S.Format(_T("Picture has %d BPS"), m_bitsPerSample );
		::LAfxThrowPictException( CPictException::errTransparency, GetRuntimeClass()->m_lpszClassName, S );
    }
}


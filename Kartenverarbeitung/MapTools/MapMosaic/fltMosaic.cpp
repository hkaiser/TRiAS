#include "stdafx.h"

#include "fltMosaic.h"
#include "MapMosaic.h"

IMPLEMENT_SERIAL(CPictMosaic,CPictFilter,0x0001);

tagPICTMOSAICPARAM::tagPICTMOSAICPARAM() {
	memset( m_Ref, 0x00, sizeof(m_Ref));
	memset( m_Clip, 0x00, sizeof(m_Clip));
	m_rcDst.SetRectEmpty();
}

tagPICTMOSAICPARAM& tagPICTMOSAICPARAM::operator=( tagPICTMOSAICPARAM& p ) {
	memcpy( (void*) m_Ref, (void*) p.m_Ref, sizeof(m_Ref));
	memcpy( (void*) m_Clip, (void*) p.m_Clip, sizeof(m_Clip));
	m_rcDst = p.m_rcDst;
	return *this;
}

tagPICTMOSAICPARAM& tagPICTMOSAICPARAM::operator=( tagPICTMOSAICPARAM *p ) {
	memcpy( (void*) m_Ref, (void*) p->m_Ref, sizeof(m_Ref));
	memcpy( (void*) m_Clip, (void*) p->m_Clip, sizeof(m_Clip));
	m_rcDst = p->m_rcDst;
	return *this;
}

CPictMosaic::CPictMosaic() {
}

CPictMosaic::~CPictMosaic() {
}

BOOL CPictMosaic::SetFilterData( LPFILTERPARAM pData ) {
	LPPICTMOSAICPARAM p = (LPPICTMOSAICPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	m_param = (PICTMOSAICPARAM*) p;
	return TRUE;
}

void CPictMosaic::Serialize( CArchive& ar ) {
}

static const long dstBandHeight = 200;

BOOL CPictMosaic::Filter( CPicture *pI, CPicture *pO, ostream* pstr ) {
	SIZED	szRef, szPic;
	SIZED	dl, dr;		// Koordinatendifferenzen (l)inks und (r)echts
	POINTD	pl, pr;		// Punkt auf (l)inker und (r)echter Kante
	double off;

	POINTD	ptClip[4];
	POINTD	ptBand[4];

	GetPictureInfo( pI, pO );

	//////////////////////////////////////////////////////////
	// Schrittweiten in x bzw. y

	szRef.cx = m_param.m_Ref[1].x - m_param.m_Ref[0].x;
	szRef.cy = m_param.m_Ref[3].y - m_param.m_Ref[0].y;
	szPic.cx = m_rcSrcPict.right - m_rcSrcPict.left;
	szPic.cy = m_rcSrcPict.bottom - m_rcSrcPict.top;

	dr.cx = szPic.cx / szRef.cx;
	dr.cy = szPic.cy / szRef.cy;

	//////////////////////////////////////////////////////////
	// Koordinaten der Clippunkte in Bildkoordinaten umrechnen

	ptClip[0].x = ( m_param.m_Clip[0].x - m_param.m_Ref[0].x ) * dr.cx;
	ptClip[1].x = ( m_param.m_Clip[1].x - m_param.m_Ref[0].x ) * dr.cx;
	ptClip[2].x = ( m_param.m_Clip[2].x - m_param.m_Ref[0].x ) * dr.cx;
	ptClip[3].x = ( m_param.m_Clip[3].x - m_param.m_Ref[0].x ) * dr.cx;

	ptClip[0].y = ( m_param.m_Clip[0].y - m_param.m_Ref[0].y ) * dr.cy;
	ptClip[1].y = ( m_param.m_Clip[1].y - m_param.m_Ref[0].y ) * dr.cy;
	ptClip[2].y = ( m_param.m_Clip[2].y - m_param.m_Ref[0].y ) * dr.cy;
	ptClip[3].y = ( m_param.m_Clip[3].y - m_param.m_Ref[0].y ) * dr.cy;

	//////////////////////////////////////////////////////////
	// Schrittweiten auf der linken / rechten Seite

	dl.cx = ( ptClip[3].x - ptClip[0].x ) / m_param.m_rcDst.Height();
	dl.cy = ( ptClip[3].y - ptClip[0].y ) / m_param.m_rcDst.Height();
	dr.cx = ( ptClip[2].x - ptClip[1].x ) / m_param.m_rcDst.Height();
	dr.cy = ( ptClip[2].y - ptClip[1].y ) / m_param.m_rcDst.Height();

	//////////////////////////////////////////////////////////
	// Punkte auf der linken / rechten Geraden

	pl.x = ptClip[0].x; pl.y = ptClip[0].y;
	pr.x = ptClip[1].x; pr.y = ptClip[1].y;

	m_rcDstBand = m_param.m_rcDst;
	m_rcDstBand.bottom = m_rcDstBand.top + dstBandHeight;

	while( m_rcDstBand.top < m_param.m_rcDst.bottom ) {
		pO->Read( m_rcDstBand );
		m_rcDstCore = pO->GetCoreImageRect();
		m_pDstPictData = pO->GetDataPointer();

		ptBand[0].x = pl.x; ptBand[0].y = pl.y;
		ptBand[1].x = pr.x; ptBand[1].y = pr.y;
		ptBand[2].x = pr.x + m_rcDstBand.Height() * dr.cx; ptBand[2].y = pr.y + m_rcDstBand.Height() * dr.cy;
		ptBand[3].x = pl.x + m_rcDstBand.Height() * dl.cx; ptBand[3].y = pl.y + m_rcDstBand.Height() * dl.cy;

//		m_rcSrcBand.left   = pI->GetPictRect().left;
//		m_rcSrcBand.right  = pI->GetPictRect().right;
		m_rcSrcBand.left   = min( froundl( ptBand[0].x ), froundl( ptBand[3].x ) );
		m_rcSrcBand.right  = max( froundl( ptBand[1].x ), froundl( ptBand[2].x ) );
		m_rcSrcBand.top    = min( froundl( ptBand[0].y ), froundl( ptBand[1].y ) );
		m_rcSrcBand.bottom = max( froundl( ptBand[2].y ), froundl( ptBand[3].y ) );

		if( pstr ) {
			CString	S;
			S.Format( _T("%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld")
				, m_rcDstBand.left
				, m_rcDstBand.top
				, m_rcDstBand.right
				, m_rcDstBand.bottom
				, m_rcSrcBand.left
				, m_rcSrcBand.top
				, m_rcSrcBand.right
				, m_rcSrcBand.bottom
				);
			*pstr << (LPCTSTR) S << endl;
		}

		pI->Read( m_rcSrcBand );
		m_rcSrcCore = pI->GetCoreImageRect();
		m_pSrcPictData = pI->GetDataPointer();

		off = froundl( pl.y ) - m_rcSrcCore.top;
		off *= m_rcSrcCore.Width();
		off += froundl( pl.x ) - m_rcSrcCore.left;

//		TRACE( "%06ld\t%06.8lf\t%06.8lf\t%06.8lf\t%06.8lf\t%06.8lf\n", m_rcDstBand.top, off, pl.x, pl.y, pr.x, pr.y );

		switch( pI->GetColorspace() ) {
		case PICT_COLOR_PAL8 :
		case PICT_COLOR_PALETTE :
			samplePal8( pl, dl, pr, dr );
			break;
		}

		if( PICT_COLOR_MONOBIZ == pI->GetColorspace() && 8 == pI->GetBitsPerSample() ) {
			samplePal8( pl, dl, pr, dr );
		}

//		if( pstr )
//			*pstr << " w " << m_rcDstBand.left << "," << m_rcDstBand.top << endl;

		pO->Write( m_rcDstBand );

		m_rcDstBand.OffsetRect( 0, m_rcDstBand.Height() );
		m_rcDstBand.bottom = min( m_rcDstBand.bottom, m_param.m_rcDst.bottom );
	}
	return TRUE;
}

BOOL CPictMosaic::samplePal8( POINTD& pl, SIZED& dl, POINTD& pr, SIZED& dr ) {
	HPBYTE	pSrcPixel;
	HPBYTE	pDstPixel, pDstRow;
	POINTD	p;
	SIZED	d;
	long	off, row, col;
	double	dstWidth = m_param.m_rcDst.Width();

	pDstRow = m_pDstPictData;

	for( row = m_rcDstBand.top; row < m_rcDstBand.bottom; row++ ) {
		d.cx = ( pr.x - pl.x ) / dstWidth;
		d.cy = ( pr.y - pl.y ) / dstWidth;
		p.x = pl.x; p.y = pl.y;
		pDstPixel = pDstRow;
		for( col = m_rcDstBand.left; col < m_rcDstBand.right; col++ ) {
			off = froundl( p.y ) - m_rcSrcCore.top;
			off *= m_rcSrcCore.Width();
			off += froundl( p.x ) - m_rcSrcCore.left;
			pSrcPixel = m_pSrcPictData + off;
#ifdef	_DEBUG
//			ASSERT( TRUE == m_pI->CheckDataPointer( pSrcPixel ) );
//			ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
			*pDstPixel = *pSrcPixel;
			p.x += d.cx;
			p.y += d.cy;
			pDstPixel++;
		}
		pr += dr;
		pl += dl;
		pDstRow += m_rcDstCore.Width();
	}
#ifdef _DEBUG
	pDstRow = m_pDstPictData;
	pDstPixel = pDstRow;
	for( col = m_rcDstBand.left; col < m_rcDstBand.right; col++ ) {
		*pDstPixel++ = 0xff;
	}
	for( row = m_rcDstBand.top; row < m_rcDstBand.bottom; row += 10 ) {
		pDstPixel = pDstRow;
		for( col = m_rcDstBand.left; col < 20; col++ ) {
			*pDstPixel++ = 0xff;
		}
		pDstRow += 10 * m_rcDstCore.Width();
	}
#endif
	return TRUE;
}

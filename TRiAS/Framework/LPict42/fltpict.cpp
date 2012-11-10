#include "stdafx.h"
#include "LPictImpl.h"

#ifdef	PICTFLT_RELEASED

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CPictFilter, CObject );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

CPictFilter::CPictFilter( ) {
	m_pSrcPictData = m_pDstPictData = NULL;
	m_rcSrcImage.SetRectEmpty();
	m_rcDstImage.SetRectEmpty();
	m_rcSrcPict.SetRectEmpty();
	m_rcDstPict.SetRectEmpty();
	m_rcSrcBand.SetRectEmpty();
	m_rcDstBand.SetRectEmpty();
}

void CPictFilter::Serialize( CArchive& ar ) {
	CObject::Serialize( ar );
}

void CPictFilter::GetPictureInfo( CPicture *pI, CPicture *pO ) {
	m_rcSrcImage	= pI->GetImageRect();
	m_rcSrcPict		= pI->GetPictRect();
	m_pSrcPictData	= NULL; // pI->GetDataPointer();

	if( NULL != pO ) {
		m_rcDstImage	= pO->GetImageRect();
		m_rcDstPict		= pO->GetPictRect();
		m_pDstPictData	= NULL; // pO->GetDataPointer( );
	} else {
		m_rcDstImage.SetRectEmpty();
		m_rcDstPict.SetRectEmpty();
		m_pDstPictData = NULL;
	}
#ifdef	_DEBUG
	m_pI = pI;
	m_pO = pO;
#endif
}

BOOL CPictFilter::DoFilter( ) {
	return TRUE;
}

void CPictFilter::MergeTags( CPicture* pO ) {
	if( m_strTagsToMerge.IsEmpty() )
		return;
	ASSERT_KINDOF( CPicture, pO );
	CString	S, SR, SL, FL, FR;
	S = m_strTagsToMerge;
	int	idx;
	for( ; -1 != ( idx = S.Find( '|' ) ) || S.GetLength( ) > 0; S = SR ) {
		if( -1 != idx ) {
			SL = S.Left( idx );
			SR = S.Right( S.GetLength() - idx - 1 );
		} else {
			SL = S;
			SR = "";
		}
		idx = SL.Find( ',' );
		if( -1 == idx )
			continue;
		FL = SL.Left( idx );
		FR = SL.Right( SL.GetLength() - idx - 1 );
		if( 0 == FL.GetLength() || 0 == FR.GetLength() )
			continue;
		pO->MergeTag( (PICT_PROPERTY) atol( FL ), FR );
	}
}

#endif	// PICTFLT_RELEASED

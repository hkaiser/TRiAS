#include "stdafx.h"
#include "LPictImpl.h"

#ifdef	PICTFLT_FLIP_RELEASED

#ifdef	PICTFLT_FLIP_RELEASED

class AFX_EXT_CLASS CPictFlip : public CPictFilter {
protected:
	DECLARE_SERIAL( CPictFlip );
public:
	CPictFlip( );
	~CPictFlip( );
public:
	BOOL	Filter( CPicture *pIPic, CPicture *pOPic, ostream* prot = NULL );
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_FLIP_RELEASED

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CPictFlip, CPictFilter, 1 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

CPictFlip::~CPictFlip( ) {
}

BOOL CPictFlip::Filter( CPicture *pI, CPicture *pO, ostream* pstr ) {
	DWORD	startSrcLine = 0;
	DWORD	startDstLine = 0;
	CRect	rcSrc = pI->GetPictDimension();
	
	pO->Clone( pI );
	pO->SetPictDimension( CRect( 0, 0, rcSrc.Height(), rcSrc.Width( ) ) );

	pO->WriteHeader( );

	GetPictureInfo( pI, pO );
	
	return TRUE;
}

void CPictFlip::Serialize( CArchive& ar ) {
	CPictFilter::Serialize( ar );
}

#endif	// PICTFLT_FLIP_RELEASED

#include "stdafx.h"
#if defined(TRILAY)
#include "../TRILay/TRILayImpl.h"
#else
#include "LPictImpl.h"
#endif
#include "lpict/pictdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagePictprop property page

IMPLEMENT_DYNCREATE(CPagePictprop, CPropertyPage)

CPagePictprop::CPagePictprop() : CPropertyPage(IDD_PG_PICTPROP) {
	//{{AFX_DATA_INIT(CPagePictprop)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pPicture = NULL;
}

CPagePictprop::~CPagePictprop() {
}

void CPagePictprop::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagePictprop)
	DDX_Control(pDX, IDC_TREE_PICTPROP, m_treeProp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPagePictprop, CPropertyPage)
	//{{AFX_MSG_MAP(CPagePictprop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagePictprop message handlers

////////////////////////////////////////////////////////////////
// 0 == m_nProp => Node
// 0 != m_nProp => Leaf

typedef struct tagPROPCRACK {
	PICT_PROPERTY	m_nProp;
	LPCTSTR			m_pDescr;
} PROPCRACK;
typedef const PROPCRACK FAR* LPCPROPCRACK;

static TCHAR *szSS = _T("%s: %s");

static PROPCRACK	props[] = {
	{ (PICT_PROPERTY) 0, _T("Image") }
	, { (PICT_PROPERTY) 0, _T("Geomtry") }
	,	{ PICT_PROP_IMAGEWIDTH, szSS }
	,	{ PICT_PROP_IMAGELENGTH, szSS }
	,	{ PICT_PROP_FILLORDER, szSS }
	,	{ PICT_PROP_ORIENTATION, szSS }
	,	{ PICT_PROP_COMPRESSION, szSS }
	, { (PICT_PROPERTY) 0, _T("Resolution") }
	,	{ PICT_PROP_RESOLUTIONUNIT, szSS }
	,	{ PICT_PROP_XRESOLUTION, szSS }
	,	{ PICT_PROP_YRESOLUTION, szSS }
	, { (PICT_PROPERTY) 0, _T("Color") }
	,	{ PICT_PROP_BITSPERSAMPLE, szSS }
	,	{ PICT_PROP_COLORSPACE, szSS }
	,	{ PICT_PROP_SAMPLESPERPIXEL, szSS }
	,	{ PICT_PROP_PLANARCONFIGURATION, szSS }
	, { (PICT_PROPERTY) 0, _T("Document") }
	,	{ PICT_PROP_DOCUMENTNAME, szSS }
	,	{ PICT_PROP_IMAGEDESCRIPTION, szSS }
	,	{ PICT_PROP_PAGENAME, szSS }
	, { (PICT_PROPERTY) 0, _T("Manufacturer") }
	,	{ PICT_PROP_SCANNERMANUFACTURER, szSS }
	,	{ PICT_PROP_SCANNERMODEL, szSS }
	,	{ PICT_PROP_SOFTWARE, szSS }
	,	{ PICT_PROP_DATETIME, szSS }
	,	{ PICT_PROP_ARTIST, szSS }
	,	{ PICT_PROP_HOSTCOMPUTER, szSS }
	, { (PICT_PROPERTY) 0, NULL }
};

static LPCPROPCRACK filltree ( CTreeCtrlEx& rTree, CTreeCursor& parent, LPCPROPCRACK pProp, const CPicture* pPicture ) {
	CTreeCursor	child;
	CString		S;
	CPictCrack	C;
	for( ; 0 == pProp->m_nProp && NULL != pProp->m_pDescr; ) {
		child = rTree.InsertItem( pProp->m_pDescr, parent );
		pProp = filltree( rTree, child, ++pProp, pPicture );
	}
	for( ; 0 != pProp->m_nProp && NULL != pProp->m_pDescr; ++pProp ) {
		S.Format( pProp->m_pDescr, C.Crack( pProp->m_nProp ), C.Crack( pProp->m_nProp, pPicture ) );
		parent.AddTail( S );
	}
	return pProp;
}

BOOL CPagePictprop::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	CString	S, S1;

	// TODO: Add extra initialization here
	if( NULL != m_pPicture ) {
		CTreeCursor	root, file;
		S = _T("Dateiformat "); S += m_pPicture->GetPictType( );
		root = m_treeProp.InsertItem( S );
		file = m_treeProp.InsertItem( _T("Datei"), root );
			S1 = m_pPicture->GetFileName( );
			S.Format( _T("Name: %s"), (LPCTSTR) S1 );
			file.AddTail( S );
			S.Format( _T("Größe: %ld Bytes"), m_pPicture->GetFileSize( ) );
			file.AddTail( S );
		filltree( m_treeProp, root, props, m_pPicture );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CPicture* CPagePictprop::Attach( CPicture* pPicture ) {
	CPicture	*pOld = m_pPicture;
#ifdef _DEBUG
	if( NULL != pPicture )
		ASSERT_KINDOF( CPicture, pPicture );
#endif
	m_pPicture = pPicture;
	return pOld;
}

#ifndef _AFX_ENABLE_INLINES			// _DEBUG is defined

#ifdef AFX_DBG1_SEG
#pragma code_seg(AFX_DBG1_SEG)
#endif

static char BASED_CODE _szAfxWinInl[] = "LafxCtrl.inl";
#undef THIS_FILE
#define THIS_FILE _szAfxWinInl
#define _AFXWIN_INLINE
#include "lmfcx/LafxCtrl.inl"

#endif //!_AFX_ENABLE_INLINES

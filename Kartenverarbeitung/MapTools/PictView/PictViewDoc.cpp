#include "stdafx.h"
#include "PictView.h"

#include "PictViewDoc.h"
#include "SrvrItem.h"
#include "BasePpg.h"
#include "PgOptDraw.h"
#include "PgBWPictures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc

IMPLEMENT_DYNCREATE(CPictViewDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CPictViewDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CPictViewDoc)
	ON_COMMAND(ID_OPTIONS, OnOptions)
	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTIES, OnUpdateFileProperties)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_COPY_AS, OnUpdateFileSaveCopyAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPictViewDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CPictViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IPictVi to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3ECD6803-A060-11D0-9886-006097556705}
static const IID IID_IPictVi =
{ 0x3ecd6803, 0xa060, 0x11d0, { 0x98, 0x86, 0x0, 0x60, 0x97, 0x55, 0x67, 0x5 } };

BEGIN_INTERFACE_MAP(CPictViewDoc, COleServerDoc)
	INTERFACE_PART(CPictViewDoc, IID_IPictVi, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc construction/destruction

CPictViewDoc::CPictViewDoc() {
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	m_pPicture = NULL;
	m_bBanding = FALSE;
	m_nTranspChannel = 0;
	m_dwTranspColor = RGB( 192, 255, 192 );
	m_nOptDlgIndex = -1;

	EnableAutomation();

	AfxOleLockApp();
}

CPictViewDoc::~CPictViewDoc() {
	AfxOleUnlockApp();
}

BOOL CPictViewDoc::OnNewDocument() {
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc server implementation

COleServerItem* CPictViewDoc::OnGetEmbeddedItem() {
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CPictViewSrvrItem* pItem = new CPictViewSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc serialization

void CPictViewDoc::Serialize(CArchive& ar) {
	if( IsEmbedded() ) {
		if (ar.IsStoring()) {
			ar << m_strPictName;
		} else {
			ar >> m_strPictName;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc diagnostics

#ifdef _DEBUG
void CPictViewDoc::AssertValid() const {
	COleServerDoc::AssertValid();
}

void CPictViewDoc::Dump(CDumpContext& dc) const {
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc commands

BOOL CPictViewDoc::OnOpenDocument(LPCTSTR lpszPathName)  {
	if( IsEmbedded() ) {
		if( !COleServerDoc::OnOpenDocument(lpszPathName) )
			return FALSE;
		return CreatePicture( m_strPictName );
	}
	else
		return CreatePicture( lpszPathName );
}

void CPictViewDoc::OnCloseDocument()  {
	// TODO: Add your specialized code here and/or call the base class
	if( NULL != m_pPicture ) {
		ASSERT_VALID( m_pPicture );
		m_pPicture->Detach();
		delete m_pPicture;
		m_pPicture = NULL;
		m_fileOfPicture.Abort();
	}
	m_strPictName.Empty();
	COleServerDoc::OnCloseDocument();
}

BOOL CPictViewDoc::CreatePicture( LPCTSTR lpszFileName ) {
	ASSERT( NULL == m_pPicture );
	m_strPictName.Empty();
	CFileException	fe;

	if( !m_fileOfPicture.Open( lpszFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyRead, &fe ) )
		return FALSE;
	CRuntimeClass	*pRT = GetPictureType( &m_fileOfPicture );
	if( NULL == pRT )
		return FALSE;
	VERIFY( m_pPicture = (CPicture*) pRT->CreateObject() );
	VERIFY( m_pPicture->Attach( &m_fileOfPicture ) );
	VERIFY( m_pPicture->ReadHeader() );
	m_strPictName = lpszFileName;
	SetTitle( lpszFileName );
	UpdateAllViews( NULL, PICT_OPENED );

	return TRUE;
}

void CPictViewDoc::OnOptions()  {
	PICT_COLOR	cs;
	CPropertySheet	dlg;
	CPgOptDraw	pgOptDraw;
	CPgBWPictures	pgBWPict;
	dlg.AddPage( &pgOptDraw );

	if( m_pPicture ) {
		ASSERT_VALID( m_pPicture );
		cs = m_pPicture->GetColorspace();
		if( PICT_COLOR_MONOWIZ == cs || PICT_COLOR_MONOBIZ == cs ) {
			dlg.AddPage( &pgBWPict );
			dlg.SetActivePage( &pgBWPict );
			pgBWPict.m_bTransparent = m_nTranspChannel ? TRUE : FALSE;
			pgBWPict.m_rgbRed = GetRValue(m_dwTranspColor);
			pgBWPict.m_rgbGreen = GetGValue(m_dwTranspColor);
			pgBWPict.m_rgbBlue = GetBValue(m_dwTranspColor);
			pgBWPict.m_nChannel = m_nTranspChannel ? m_nTranspChannel - 1:
				PICT_COLOR_MONOWIZ == cs ? 0 : 1;
		}
	}
	pgOptDraw.m_bBanding = m_bBanding;

	if( IDOK == dlg.DoModal() ) {
		m_bBanding = pgOptDraw.m_bBanding;
		if( PICT_COLOR_MONOWIZ == cs || PICT_COLOR_MONOBIZ == cs ) {
			m_nTranspChannel = pgBWPict.m_bTransparent ? pgBWPict.m_nChannel + 1 : 0;
			m_dwTranspColor = RGB(pgBWPict.m_rgbRed,pgBWPict.m_rgbGreen,pgBWPict.m_rgbBlue );
			m_pPicture->SetTransparency( m_nTranspChannel, m_dwTranspColor );
		}
		UpdateAllViews( NULL, PICT_PROPCHANGED );
	}
}

BOOL CPictViewDoc::IsBanding() {
	return m_bBanding;
}

void CPictViewDoc::OnFileProperties()  {
	// TODO: Add your command handler code here

	CPropertySheet	sheet( IDS_FILE_PROPERTIES );
	CPagePictprop	pgPict;

	ASSERT_VALID( m_pPicture );
	pgPict.Attach( m_pPicture );

	sheet.AddPage( &pgPict );

	if( IDOK == sheet.DoModal() ) {
	}
}

void CPictViewDoc::OnUpdateFileProperties(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture );
}

void CPictViewDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

void CPictViewDoc::OnUpdateFileSaveCopyAs(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

void CPictViewDoc::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

void CPictViewDoc::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

void CPictViewDoc::OnUpdateFilePrint(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

void CPictViewDoc::OnUpdateFileSave(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture ); 
}

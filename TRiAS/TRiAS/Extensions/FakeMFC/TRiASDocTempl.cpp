// Special document template for subclassed View/Document
// File: TRiASDocTempl.cpp

#include "fakemfcp.hxx"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Strings.h"
#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"		// die Erweiterung selbst
#include "MainFrm.h"

#include "TRiASDocTempl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTRiASDocTemplate, CSingleDocTemplate)

/////////////////////////////////////////////////////////////////////////////

CTRiASDocTemplate::CTRiASDocTemplate(UINT nIDResource,
	CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass,
	CRuntimeClass* pViewClass)
		: CSingleDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
// Zeichenketten korrigieren
	if (m_strDocStrings.IsEmpty())
		m_strDocStrings.LoadString(nIDResource);
	
	ATLTRY(m_strDocStrings = FakeTRiASName (
					m_strDocStrings, g_cbTRiAS, g_cbTRiAS, g_cbTRiAS,
					g_cbRiw, g_cbRiw, g_cbTRiAS).c_str());
}

CTRiASDocTemplate::~CTRiASDocTemplate()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASDocTemplate commands
CTRiASView* CTRiASDocTemplate::SubclassView (CFrameWnd *pMainFrm, HWND hWndView)
{
	TRACE( "FakeMFC: CTRiASDocTemplate::SubclassView\r\n");

// Document erzeugen
CDocument* pDocument = CreateNewDocument();

	if (pDocument == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT(pDocument == m_pOnlyDoc);

// Frame mitteilen, daß View erzeugt/Subclassed werden muß
BOOL bAutoDelete = pDocument->m_bAutoDelete;
CTRiASView *pViewWnd = NULL;

	pDocument->m_bAutoDelete = FALSE;	// don't destroy if something goes wrong
	pViewWnd = CreateSubclassedView (pDocument, hWndView);
	pDocument->m_bAutoDelete = bAutoDelete;

	if (NULL == pViewWnd) {
		AfxMessageBox (AFX_IDP_FAILED_TO_CREATE_DOC);
		delete pDocument;       // explicit delete on error
		return NULL;
	}

// Die neue View als aktive im Frame setzen
	pMainFrm -> SetActiveView (pViewWnd);

	AfxGetApp()->m_nCmdShow = DEXI_isAppWindowVisible() ? SW_SHOW : SW_HIDE; // set to default after first time
	InitialUpdateFrame(pMainFrm, pDocument, TRUE);
	return pViewWnd;
}

CTRiASView* CTRiASDocTemplate::CreateSubclassedView (CDocument* pDoc, HWND hWndView)
{
	TRACE( "FakeMFC: CTRiASDocTemplate::CreateSubclassedView\r\n");

	if (pDoc != NULL)
		ASSERT_VALID(pDoc);

// create a View wired to the specified document
CCreateContext context;

	context.m_pCurrentFrame = NULL;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = m_pViewClass;
	context.m_pNewDocTemplate = this;

CMainFrame* pFrame = (CMainFrame *)g_pTE -> MWind();

	if (pFrame == NULL) {
		TRACE0("Warning: Frame does not exist.\n");
		return NULL;
	}
	ASSERT_KINDOF(CFrameWnd, pFrame);

	if (context.m_pNewViewClass == NULL)
		TRACE0("Warning: creating frame with no default view.\n");

// create new from resource
CTRiASView *pViewWnd = pFrame->CreateSubclassedView (&context, hWndView);

	if (NULL == pViewWnd) {
		TRACE0("Warning: CDocTemplate couldn't create a subclassed view.\n");
		return NULL;
	}

	// it worked !
	return pViewWnd;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASDocTemplate diagnostics

#ifdef _DEBUG
void CTRiASDocTemplate::Dump(CDumpContext& dc) const
{
	CSingleDocTemplate::Dump(dc);
}

void CTRiASDocTemplate::AssertValid() const
{
	CSingleDocTemplate::AssertValid();
}
#endif //_DEBUG



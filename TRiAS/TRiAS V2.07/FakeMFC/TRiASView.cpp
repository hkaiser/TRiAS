// TRiASView.cpp : implementation of the CTRiASView class
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <toolguid.h>
#include <itoolbar.h>

#include <vinfomfc.h>
#include <igeometr.hxx>
#include <objgguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "InlineFuncs.h"
#include "Strings.h"

#include "TRiASDoc.h"
#include "CntrItem.h"
#include "TRiASView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LINE_EPSILON_DC	3

/////////////////////////////////////////////////////////////////////////////
// CTRiASView

DefineSmartInterface(ObjectProperty);
DefineSmartInterface(TriasXtensionSite);

IMPLEMENT_DYNCREATE(CTRiASView, CView)

BEGIN_MESSAGE_MAP(CTRiASView, CView)
	//{{AFX_MSG_MAP(CTRiASView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP

// ToolTipHandling
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
	ON_NOTIFY_EX(TTN_SHOW, 0, OnToolTipShow)
	ON_NOTIFY_EX(TTN_POP, 0, OnToolTipPop)

// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTRiASView construction/destruction

CTRiASView::CTRiASView()
{
	m_pSelection = NULL;
	m_pCTF = NULL;
}

CTRiASView::~CTRiASView()
{
	if (NULL != m_pCTF) {
		m_pCTF -> Release();
		m_pCTF = NULL;
	}
}

BOOL CTRiASView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASView drawing

void CTRiASView::OnDraw(CDC* pDC)
{
	CTRiASDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document
}

void CTRiASView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

// Enable tooltips for this view.
// MFC's message filter will now do most of the work for us.
	EnableToolTips(TRUE);			

// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CTRiASView printing
/*
BOOL CTRiASView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTRiASView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void CTRiASView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}
*/
/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CTRiASView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CTRiASCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CTRiASView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CTRiASCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CTRiASCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CTRiASDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CTRiASCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

	// As an arbitrary user interface design, this sets the selection
	//  to the last item inserted.

	// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CTRiASView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CTRiASView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CTRiASView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CTRiASView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASView diagnostics

#ifdef _DEBUG
void CTRiASView::AssertValid() const
{
	CView::AssertValid();
}

void CTRiASView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTRiASDoc* CTRiASView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTRiASDoc)));
	return (CTRiASDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASView message handlers

void CTRiASView::PreSubclassWindow() 
{
	CView::PreSubclassWindow();

WTriasXtensionSite Site;

	if (SUCCEEDED(g_pTE -> GetXtensionSite (Site.ppi()))) {
	HRESULT hr = CComObject<CConnectedCtf>::CreateInstance (&m_pCTF);

		if (SUCCEEDED(hr)) {
			m_pCTF -> AddRef();
			m_pCTF -> SetXtsnSite (Site);
		}
	}
}

BOOL CTRiASView::WireDocument (CCreateContext* pContext)
{
	// wire in the current document
	ASSERT(m_pDocument == NULL);

	// A view should be created in a given context!
	if (pContext != NULL && pContext->m_pCurrentDoc != NULL)
	{
		pContext->m_pCurrentDoc->AddView(this);
		ASSERT(m_pDocument != NULL);
		
		ASSERT(NULL != m_pCTF);
		if (!m_pCTF -> LoadCTF()) {	// erste Initialisierung
			TRACE0("Warning: Initialisation of CoordTransform for view failed.\n");
			return FALSE;
		}
	}
	else
	{
		TRACE0("Warning: Creating a pane with no CDocument.\n");
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// ToolTipHandling

CPoint CTRiASView::m_ptToolHit;				// static info to provide hit text
CRect CTRiASView::m_rcToolTipObject;
LONG CTRiASView::m_lToolTipObject;
Punkt CTRiASView::m_ptToolTest;

/////////////////////////////////////////////////////////////////////////////
// Map der Objekte unter dem MouseTip (nach Prioritäten/ObjTypen geordnet)
class CObjRectMaxPriority
{
private:
	LONG m_lONr;
	CRect m_rc;
	int m_iPriority;
	int m_iVType;

public:
		CObjRectMaxPriority (void)
			: m_lONr(0L), m_iPriority(0), m_iVType(0) {}
		CObjRectMaxPriority (LONG lONr, int iVTyp, int iPrio, CRect rc)
			: m_lONr(lONr), m_iPriority(iPrio), m_iVType(iVTyp), m_rc(rc) {}

	LONG ObjNr() const { return m_lONr; }
	CRect ObjRect() const { return m_rc; }
	int Priority() const { return m_iPriority; }
	int VisType() const { return m_iVType; }

	bool should_insert (int iVTyp, int iPrio) const
		{
		// 1. höher Priorität sticht
			if (Priority() != iPrio)	
				return Priority() < iPrio;
		
		// 2. ansonsten VT_Text(4) > VT_Flaeche(2) > VT_Linie(1) > VT_Punkt(0)
			return VisType() < iVTyp;	
		}

	bool operator< (const CObjRectMaxPriority &rhs) const
		{ 
			return should_insert(rhs.VisType(), rhs.Priority());
		}

	CObjRectMaxPriority &operator= (const CObjRectMaxPriority &rhs)
		{
			m_lONr = rhs.ObjNr();
			m_iPriority = rhs.Priority();
			m_rc = rhs.ObjRect();
			m_iVType = rhs.VisType();
			return *this;
		}

	CObjRectMaxPriority &insert (LONG lONr, int iVTyp, int iPrio, CRect rc)
		{
			*this = CObjRectMaxPriority (lONr, iVTyp, iPrio, rc);
			return *this;
		}

	bool IsValid() { return m_lONr != 0 ? true : false; }
};

// Test, ob Objekt von Punkt getroffen wird
DefineSmartInterface(ObjektGeometrie);
DefineSmartInterface(InitObjektGeometrie);

inline void DCtoOCEx (const CPoint &rPt, Punkt *pPt)
{
COORDCONVERT CT;

	CT.lpPt = (POINT *)&rPt;
	CT.lpPkt = (long *)pPt;
	DEX_DCtoOCEx(CT);
}

void RetrievePointDims (LONG lONr, CRect &rrc, LONG &rlEpsX, LONG &rlEpsY)
{
	DCtoOCEx (rrc.TopLeft(), (Punkt *)&rrc.TopLeft());
	DCtoOCEx (rrc.BottomRight(), (Punkt *)&rrc.BottomRight());
	rlEpsX = abs(rrc.right - rrc.left);
	rlEpsY = abs(rrc.top - rrc.bottom);
}

void RetrieveLineDim (LONG lONr, CRect &rrc, LONG &rlEps)
{
	rrc.BottomRight() = rrc.TopLeft();
	rrc.bottom += LINE_EPSILON_DC;
	rrc.right += LINE_EPSILON_DC;

	DCtoOCEx (rrc.TopLeft(), (Punkt *)&rrc.TopLeft());
	DCtoOCEx (rrc.BottomRight(), (Punkt *)&rrc.BottomRight());

	rlEps = (abs(rrc.right - rrc.left) + abs(rrc.top - rrc.bottom))/2;
}

HRESULT HitTest (LONG lONr, int iVisType, CRect &rrc, Punkt &rpt, CursPos *prgCP)
{
	TEST_E_POINTER("HitTest", prgCP);

// Epsilons berechnen
LONG lEpsX = 0L;
LONG lEpsY = 0L;
LONG lEpsLine = 0L;

	switch (iVisType) {
	case VT_Punkt:
		RetrievePointDims (lONr, rrc, lEpsX, lEpsY);
		break;

	case VT_Linie:
		RetrieveLineDim (lONr, rrc, lEpsLine);
		break;

	case VT_Flaeche:
		break;				// alle Eps sind 0

	case VT_Text:
		*prgCP = CURSPOS_OBJECT;
		return S_OK;		// Texte sind rechtwinklig

	default:
		return E_INVALIDARG;
	}

// jetzt Geoemtrie genau testen
	try {
	WObjektGeometrie Obj (CLSID_ObjektGeometrie);	// throws hr
	WInitObjektGeometrie Init (Obj);				// throws hr

		THROW_FAILED_HRESULT(Init -> InitObjGeometry (lONr));
		THROW_FAILED_HRESULT(Obj -> CursorInObject (rpt.X(), rpt.Y(), lEpsX, lEpsY, lEpsLine, true, prgCP));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

// CallBack für gefundene Objekte
extern "C"
BOOL CALLBACK FindObjectsForToolTip (long Key, RECT Rc, void *pData)
{
CObjRectMaxPriority *pMax = (CObjRectMaxPriority *)pData;
IDENTPRIORITY IP;

	INITSTRUCT(IP, IDENTPRIORITY);
	IP.lONr = Key;

	if (FAILED(DEX_GetIdentPriority(IP))) 
		return TRUE;	// weiter
	if (!pMax -> should_insert(IP.iVisType, IP.iPriority)) 
		return TRUE;	// weiter

CursPos rgCP = CURSPOS_OUTSIDE;

	if (FAILED(HitTest (Key, IP.iVisType, CRect(Rc), CTRiASView::m_ptToolTest, &rgCP)))
		return TRUE;	// weiter
	if (CURSPOS_OBJECT == rgCP) 
		pMax -> insert (Key, IP.iVisType, IP.iPriority, CRect(Rc));

	return TRUE;
}

int CTRiASView::OnToolHitTest (CPoint point, TOOLINFO* pTI) const
{
	VERIFY(CView::OnToolHitTest(point, pTI) == -1);

	if (DEXI_isDrawing() || DEXI_isPrinting()) 
		return -1;		// während des Zeichnens nichts machen

LONG lPrevObject = m_lToolTipObject;

	m_lToolTipObject = 0L;		// aktives Objekt rücksetzen

CRect rc;
	
	GetClientRect(rc);			// Y-Koordinate kippen

// Koordinaten in DB-Koordinaten umsetzen
CPoint pt;

	pt.x = point.x;
	pt.y = rc.bottom - rc.top - point.y;
	DCtoOCEx (pt, &m_ptToolTest);       // Device --> Objekt
	
FINDOBJECT FO;
CObjRectMaxPriority obj;

	INITSTRUCT(FO, FINDOBJECT);
	FO.Pt = pt;
	FO.iFOMode = FOPunkt|FOKante|FOFlaeche|FOText;
	FO.eFcn = (FINDOBJECTPROC)FindObjectsForToolTip;
	FO.pData = (void *)&obj;
	if (!DEX_FindObjectsFromPoint(FO) || 0L == obj.IsValid())
		return -1;		// irgend ein Fehler oder nichts gefunden

// das Objekt mit der höchsten ZeichenPriorität verwenden
	m_lToolTipObject = obj.ObjNr();
	m_rcToolTipObject = obj.ObjRect();

// wenn ein neues Objekt geliefert wurde, alten Tooltip ausblenden
	if (lPrevObject != m_lToolTipObject)
		CancelToolTips(TRUE);

// if there were any area's that are not hits, then we could return -1
// immiediately, but in this example, every grid square fires.
	pTI->rect.left = m_rcToolTipObject.left;
	pTI->rect.right = m_rcToolTipObject.right;
	pTI->rect.bottom = rc.bottom - rc.top - m_rcToolTipObject.bottom;
	pTI->rect.top = rc.bottom - rc.top - m_rcToolTipObject.top;

// if using callbacks - store enough info in a static variable so
// we can produce the text later on a TTN_NEEDTEXT notification.
	pTI->lpszText = LPSTR_TEXTCALLBACK;
	m_ptToolHit = point;
	
// set up the rest of the flags. Not all of these are required, but it seems
// safer to supply them.
	pTI->hwnd = m_hWnd;				// window where TTN_NEEDTEXT will be sent.
	
	pTI->uFlags = 0; //TTF_ALWAYSTIP ;
	pTI->cbSize = sizeof TOOLINFO;
	pTI->uId = (UINT)(m_lToolTipObject | ~0x7fffffffL);		// dummy id, so we can tell it's not a standard command
								// if you want standard tooltip processing, you should
								// put the command id here
	// need a return value that is different for every grid square. 
	return int(m_lToolTipObject);
}

// Handle TTN_NEEDTEXT notification.
BOOL CTRiASView::OnToolTipNeedText (UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
// We may have been called for any notification here. First check, we're
// looking at a request from CTRiASView, by checking the ID requested is the
// same dummy one we supplied in OnToolHitTest
TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    
	if (pNMHDR->idFrom & ~0x7fffffffL) {	// ältestes Bit gesetzt ?
	LONG lONr = pNMHDR->idFrom & 0x7fffffffL;

		pTTT -> szText[0] = '\0';
		return GenerateTipTextHelper (pTTT->szText, m_ptToolHit, lONr);	// call the helper function to supply the text
	} else 
		return FALSE;		// so message processing continues
}

BOOL CTRiASView::GenerateTipTextHelper (LPSTR pText, CPoint pt, LONG lONr) 
{
WObjectProperty ObjProp;
HRESULT hr = DEX_GetActObjProp (ObjProp.ppv());

	if (FAILED(hr) || !ObjProp) return FALSE;

	hr = ObjProp -> Eval (lONr, pText, 79, NULL);
	if (FAILED(hr)) return FALSE;

	m_strTipText = pText;
	return SUCCEEDED(hr);
}

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)
// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375		

// Handle TTN_SHOW notification.
BOOL CTRiASView::OnToolTipShow (UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!(pNMHDR->idFrom & ~0x7fffffffL))	// ältestes Bit gesetzt ?
		return FALSE;

	TRY {
	LONG lONr = pNMHDR->idFrom & 0x7fffffffL;
	char cbBuffer[_MAX_PATH];

		if (!DEX_GetActObjPropName (cbBuffer)) 
			return FALSE;

	// Objekt selektieren
	ACTIVATEOBJECT AO;

		INITSTRUCT(AO, ACTIVATEOBJECT);
		AO.lONr = lONr;
		AO.crAct = RGB(255, 0, 255);
		DEX_SelectObject(AO);

	// StatusZeilenText erzeugen und anzeigen
	CWnd *pFrame = g_pTE -> MWind();
	CString strStatusText;
	
		strStatusText.Format(IDS_STATUSTIPTEXT, (LPCSTR)cbBuffer, (LPCSTR)m_strTipText);

		ASSERT(NULL != pFrame && pFrame -> IsKindOf(RUNTIME_CLASS(CWnd)));
		pFrame -> SendMessage (WM_SETMESSAGESTRING, 0, (LPARAM)(LPCSTR)strStatusText);

	} CATCH (CMemoryException, e) {
		return FALSE;
	} END_CATCH;

	return TRUE;
}

// Handle TTN_POP notification.
BOOL CTRiASView::OnToolTipPop (UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!(pNMHDR->idFrom & ~0x7fffffffL))	// ältestes Bit gesetzt ?
		return FALSE;

	m_strTipText = g_cbNil;

// Objekt deselektieren
LONG lONr = pNMHDR->idFrom & 0x7fffffffL;

	DEX_UnselectObject (lONr);

// StatusZeile rücksetzen
CWnd *pFrame = g_pTE -> MWind();

	ASSERT(NULL != pFrame && pFrame -> IsKindOf(RUNTIME_CLASS(CWnd)));
	pFrame -> SendMessage (WM_POPMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Messages, die direkt an TRiAS weiterzuleiten sind

void CTRiASView::OnPaint() 
{
	ForwardMsgToTRiAS (m_hWnd, WM_PAINT, 0L, 0L);
}

void CTRiASView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
// TRiAS rufen
	CView::OnHScroll(nSBCode, nPos, pScrollBar);

// Tooltip wieder einblenden
long cont[4];	// XMin, XMax, YMin, YMax

	DEX_GetActiveSightContainer(cont);

// Koordinaten umrechnen
double XOut, YOut;

	m_pCTF -> UnScale (cont[0], cont[2], &XOut, &YOut);
	m_pCTF -> Transform (&XOut, &YOut);

// Koordinaten ausgeben
char cbBuffer[64];

	m_pCTF -> CoordTransToStringEx (XOut, YOut, true, cbBuffer, sizeof(cbBuffer));

	TRY {
	CString strText, strTempl;

		strTempl.LoadString (IDS_RECHTSWERT);
		strTempl += TEXT(": %s");
		strText.Format(strTempl, cbBuffer);
		m_ScrollTip.HandleScrollMessage(this, nSBCode, SB_HORZ, strText, pScrollBar); 	

	} CATCH(CMemoryException, e) {
		;
	} END_CATCH;
}

void CTRiASView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
// TRiAS rufen
	CView::OnVScroll(nSBCode, nPos, pScrollBar);

// Tooltip wieder einblenden
long cont[4];	// XMin, XMax, YMin, YMax

	DEX_GetActiveSightContainer(cont);

// Koordinaten umrechnen
double XOut, YOut;

	m_pCTF -> UnScale (cont[0], cont[2], &XOut, &YOut);
	m_pCTF -> Transform (&XOut, &YOut);

// Koordinaten ausgeben
char cbBuffer[64];

	m_pCTF -> CoordTransToStringEx (XOut, YOut, false, cbBuffer, sizeof(cbBuffer));

	TRY {
	CString strText, strTempl;

		strTempl.LoadString (IDS_HOCHWERT);
		strTempl += TEXT(": %s");
		strText.Format(strTempl, cbBuffer);
		m_ScrollTip.HandleScrollMessage(this, nSBCode, SB_VERT, strText, pScrollBar);

	} CATCH(CMemoryException, e) {
		;
	} END_CATCH;
}

void CTRiASView::OnEnable(BOOL bEnable) 
{
	CView::OnEnable(bEnable);
}

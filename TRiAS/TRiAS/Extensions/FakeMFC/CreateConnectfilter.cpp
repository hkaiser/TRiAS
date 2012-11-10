// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 18.12.2002 11:38:15 
//
// @doc
// @module CreateConnectfilter.cpp | Definition of the <c CCreateConnectfilter> class

#include "fakemfcp.hxx"

#include <ospace/utility/autoptr.h>

#include <Com/Thunk.h>
#include <CSRectGeom.h>
#include <xtensnn.h>

#include "fakemfc.h"
#include "fakemfc.hxx"

#include "MainFrm.h"
#include "CreateConnectfilter.h"
#include "ConnectedCtf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(_DGMGeometry, IID__DGMGeometry);
DefineSmartInterface2(_DGMPoints, IID__DGMPoints);
DefineSmartInterface2(_DGMPolylineGeometry, IID__DGMPolylineGeometry);

///////////////////////////////////////////////////////////////////////////////
//	Bildchen in der ImageList
#define IMG_CONNECTFILTER	0

///////////////////////////////////////////////////////////////////////////////
// diesen Dialog anzeiegn
void CMainFrame::OnCreateConnectFilter(HWND hWnd)
{
CTRiASView *pView = (CTRiASView *)GetActiveView();

	ASSERT_KINDOF(CTRiASView, pView);

CREATECONNECTIONFILTER CCF;
char cbBuffer[_MAX_PATH];

	cbBuffer[0] = '\0';

	INITSTRUCT(CCF, CREATECONNECTIONFILTER);
	CCF.hWndParent = (NULL != hWnd) ? hWnd : pView->GetSafeHwnd();
	CCF.iMode = (NULL != hWnd) ? CF_Polygon_OverlappedContainers : CF_Rectangle_OverlappedContainers;
	CCF.pName = cbBuffer;
	CCF.iLen = sizeof(cbBuffer);
	CCF.fApplySettings = true;
	CCF.fShowApplyAllConnections = true;
	CCF.fApplyAllConnections = true;
	if (NULL != hWnd) 
		CCF.hTargetONr = DEX_GetActiveObject(hWnd);

	DEX_ShowCreateConnectionFilterDlg(CCF);
}

/////////////////////////////////////////////////////////////////////////////
// CCreateConnectfilter dialog

CCreateConnectfilter::CCreateConnectfilter(UINT uiResId, CWnd* pParent /*=NULL*/)
	: CDialog(uiResId, pParent)
{
	//{{AFX_DATA_INIT(CCreateConnectfilter)
	m_iOperator = -1;
	m_strOperatorDesc = _T("");
	//}}AFX_DATA_INIT

	m_fApplyToAll = FALSE;
	m_fNameIsNew = FALSE;
	m_strFilterName = _T("");
	m_fHasApplyToAll = (uiResId == IDD) ? TRUE : FALSE;
	m_fShowPropertiesOnly = FALSE;
	m_fIsPolygon = FALSE;
	m_hTargetONr = INVALID_HOBJECT;
}


void CCreateConnectfilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateConnectfilter)
	DDX_Control(pDX, IDC_ATTACH_FILTER, m_cbApplyToAll);
	DDX_Control(pDX, IDC_CONNECTIONFILTERS, m_cbFilters);
	DDX_Radio(pDX, IDC_OVERLAPPED, m_iOperator);
	DDX_Text(pDX, IDC_OPERATOR_DESC, m_strOperatorDesc);
	//}}AFX_DATA_MAP
}

bool CCreateConnectfilter::PrepareResults()
{
	UpdateData(TRUE);
	m_cbFilters.GetWindowText(m_strFilterName);
	m_fApplyToAll = m_cbApplyToAll.GetCheck();
	m_fNameIsNew = (CB_ERR == m_cbFilters.FindStringExact(-1, m_strFilterName)) ? TRUE : FALSE;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Einstellungen wirklich durchsetzen
BOOL CCreateConnectfilter::EnumConnectionsNewName(long hPr, BOOL, void *pData)
{
char cbDataSourceName[_MAX_PATH];

	if (!DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbDataSourceName))
		return FALSE;

GETATTACHEDCONNECTIONFILTER GACF;

	INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
	GACF.pcConnName = cbDataSourceName;

ATTACHCONNECTIONFILTER ACF;

	INITSTRUCT(ACF, ATTACHCONNECTIONFILTER);
	ACF.pcConnName = cbDataSourceName;

	if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF))) 
		DEX_DetachConnectionFilter(ACF);	// bestehenden Filter herauslösen

	ACF.pcName = m_strFilterName;
	return SUCCEEDED(DEX_AttachConnectionFilter(ACF));
}

BOOL CCreateConnectfilter::EnumConnectionsOldName(long hPr, BOOL, void *pData)
{
char cbDataSourceName[_MAX_PATH];

	if (!DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbDataSourceName))
		return FALSE;

GETATTACHEDCONNECTIONFILTER GACF;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
	GACF.pcConnName = cbDataSourceName;
	GACF.pName = cbBuffer;
	GACF.iLen = sizeof(cbBuffer);

ATTACHCONNECTIONFILTER ACF;

	INITSTRUCT(ACF, ATTACHCONNECTIONFILTER);
	ACF.pcConnName = cbDataSourceName;
	ACF.pcName = m_strFilterName;

	if (!m_fApplyToAll) {
	// nur die neu setzen, die das Filter bereits haben
		if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF)) && 
			m_strFilterName == GACF.pName) 
		{
			DEX_DetachConnectionFilter(ACF);	// bestehenden Filter herauslösen
			return SUCCEEDED(DEX_AttachConnectionFilter(ACF));	// und neu setzen
		}
	}

// allen das Filter setzen
	if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF)))
		DEX_DetachConnectionFilter(ACF);	// bestehenden Filter herauslösen

	return SUCCEEDED(DEX_AttachConnectionFilter(ACF));	// und neu setzen
}

HRESULT CCreateConnectfilter::InitGeometry(IDispatch *pICS, 
	_DGMGeometry *pPolygon)
{
	_ASSERTE(INVALID_HOBJECT != m_hTargetONr);
	_ASSERTE(OGFlaeche == DEX_GetObjectType(m_hTargetONr));

	COM_TRY {
	OBJGEOMETRIE og;

		INITSTRUCT(og, OBJGEOMETRIE);
		og.dwSize = sizeof(OBJSTATISTIK);
		og.lONr = m_hTargetONr;
		if (!DEX_GetObjStatistik(og))
			return E_FAIL;

	auto_ptr<double> pX (new double[og.lCnt]);
	auto_ptr<double> pY (new double[og.lCnt]);
	auto_ptr<long> pCnt (new long[og.iKCnt]);

		og.dwSize = sizeof(OBJGEOMETRIE);
		og.iFlags = OGConverted;
		og.pdblX = pX.get();
		og.pdblY = pY.get();
		og.plCnt = pCnt.get();

	GEOMETRIEWITHCS ogcs;

		INITSTRUCT(ogcs, GEOMETRIEWITHCS);
		ogcs.pOG = &og;
		ogcs.pICS = pICS;
		if (!DEX_GetObjGeometrie(ogcs))
			return E_FAIL;

	W_DGMPoints pts;

		RETURN_FAILED_HRESULT(W_DGMPolylineGeometry(pPolygon) -> get_Points (pts.ppi()));
		for (long i = 0; i < og.lCnt; ++i) {
			RETURN_FAILED_HRESULT(pts -> Add (CCSPoint(pX.get()[i], pY.get()[i]), vtMissing));
		}

	} COM_CATCH;
	return S_OK; 
}

BOOL CCreateConnectfilter::ApplySettings(BOOL fFullApply)
{
CConnectedCtf *pCTF = ((CFakeMFCExtension *)g_pTE) -> GetViewWnd() -> m_pCTF;
__Interface<IDispatch> OutCS;

	if (FAILED(pCTF -> GetOutputCS(OutCS.ppi())))
		return FALSE;

// Connectionfilter erzeugen/modifizieren
W_DGMGeometry geom;
CONNECTIONFILTER CF;

	INITSTRUCT(CF, CONNECTIONFILTER);
	CF.pcName = m_strFilterName;
	CF.pICS = OutCS;
	if (m_fShowPropertiesOnly) {
	// ggf. alte Geometrie besorgen
		DEX_GetConnectionFilter(CF);
		if (NULL != CF.pIGeometry) {
			geom = CF.pIGeometry;
			CF.pIGeometry -> Release();
			CF.pIGeometry = NULL;
		}
	}

	if (!geom) {
		if (!m_fIsPolygon) {
		// neue Geometrie aus Bildausschnitt verwenden
			_ASSERTE(OGFlaeche == DEX_GetObjectType(m_hTargetONr)); 

		CCSRectangleGeometry rect;
		GENERICCONTAINER GC;

			INITSTRUCT(GC, GENERICCONTAINER);
			GC.pICS = OutCS;
			if (!DEX_GetActiveSelectionEx(GC))	// Selektion oder
				DEX_GetWindowAsContainer(GC);	// Fensterecken

			rect.SetRect(GC.dXMin, GC.dYMin, GC.dXMax, GC.dYMax);
			geom = rect;
		}
		else {
		// neue Geometrie aus Fläche verwenden
		W_DGMGeometry polygon; 

			if (FAILED(polygon.CreateInstance(CLSID_TRiASCSPolygonGeometry)))
				return FALSE;

		CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (polygon);
		
			_ASSERTE(NULL != (IPersistStreamInit *)p);
			p -> InitNew();

			if (FAILED(InitGeometry(OutCS, polygon)))
				return FALSE;
			geom = polygon;
		}
	}

	CF.pIGeometry = geom;
	CF.iMode = GetFilterTyp();
	if (FAILED(DEX_CreateConnectionFilter(CF)))
		return FALSE;

// wenns nicht verlang wird oder, wenn nur Eigenschaften geändert werden und 
// nicht an alle Verbindungen zurückgeschrieben werden soll
	if (!fFullApply || (m_fShowPropertiesOnly && m_fHasApplyToAll && !m_fApplyToAll))
		return TRUE;

// ausgewählte Aktionen ausführen
CWaitCursor wait;
BOOL fResult = TRUE;

	if (m_fNameIsNew) {
	// Name wurde neu vergeben
		if (m_fApplyToAll) {
		ENUMNOKEYLONG ENK;
		CStdThunkImpl<CCreateConnectfilter, ENUMNOKEYLONGPROC> 
			Thunk(this, &CCreateConnectfilter::EnumConnectionsNewName);

			ENK.eFcn = Thunk.GetThunk();
			ENK.ePtr = NULL;
			fResult = DEX_EnumDataSourceHandles(ENK);
		}
	}
	else {
	// der Filtername wurde wiederverwendet
	ENUMNOKEYLONG ENK;
	CStdThunkImpl<CCreateConnectfilter, ENUMNOKEYLONGPROC> 
		Thunk(this, &CCreateConnectfilter::EnumConnectionsOldName);

		ENK.eFcn = Thunk.GetThunk();
		ENK.ePtr = NULL;
		fResult = DEX_EnumDataSourceHandles(ENK);
	}

	if (fResult) {
	// alles neu einlesen
		DEX_RemoveAllORWnds();
		DEXN_ReReadIdents();
		DEXN_ReReadContainer();
		DEXN_ReScale();
		if (!DEX_RebuildSight())
			DEX_PostRebuildSight();
	}
	return fResult;
}

BEGIN_MESSAGE_MAP(CCreateConnectfilter, CDialog)
	//{{AFX_MSG_MAP(CCreateConnectfilter)
	ON_BN_CLICKED(IDC_OVERLAPPED, OnOverlapped)
	ON_BN_CLICKED(IDC_CONTAINED, OnContained)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateConnectfilter message handlers

BOOL CCreateConnectfilter::EnumConnectionFilters(char *pName, BOOL, void *pData)
{
COMBOBOXEXITEM cbItem;

	memset(&cbItem, '\0', sizeof(COMBOBOXEXITEM));
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	cbItem.pszText = pName;
	cbItem.iImage = cbItem.iSelectedImage = IMG_CONNECTFILTER;
	m_cbFilters.InsertItem(&cbItem);
	return TRUE;
}

BOOL CCreateConnectfilter::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_cbFilters.SetExtendedStyle(CBES_EX_CASESENSITIVE, CBES_EX_CASESENSITIVE);

CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_CONNECTFILTER_DLG) || 
		!bmpMask.LoadBitmap(IDB_CONNECTFILTER_DLG_MASK)) 
	{
		TRACE0("Could not load bitmaps for CManageConnectionFilters\r\n");
		return FALSE;
	} 
	else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 1, 1) ||
			-1 == m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CManageConnectionFilters\r\n");
			return FALSE;
		} 
		else 
			m_cbFilters.SetImageList(&m_ilImages);
	}

// Typ des Filters setzen
CString strFilterDesc;

	VERIFY(strFilterDesc.LoadString(!m_fIsPolygon ? 
		IDS_FILTER_RECTANGLE : IDS_FILTER_POLYGON));
	GetDlgItem(IDC_FILTER_DESCRIPTION) -> SetWindowText(strFilterDesc);

// existierende Filternamen in Combobox füllen	
CStdThunkImpl<CCreateConnectfilter, ENUMNOKEYPROC> 
	Thunk(this, &CCreateConnectfilter::EnumConnectionFilters);
ENUMNOKEY ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = NULL;
	DEX_EnumConnectionFilters(ENK);

	VERIFY(m_strOperatorDesc.LoadString((0 == m_iOperator) ? 
		IDS_FILTER_OVERLAP_DESC : IDS_FILTER_CONTAINS_DESC));

// wenn Name nicht editiert werden darf, dann muß er gegeben sein
	_ASSERTE(!(m_fShowPropertiesOnly && m_strFilterName.IsEmpty()));

	if (m_fShowPropertiesOnly) {
	int iIndex = m_cbFilters.FindStringExact(-1, m_strFilterName);

		_ASSERTE(CB_ERR != iIndex);
		m_cbFilters.SetCurSel(iIndex);		// Namen auswählen und pasivieren
		m_cbFilters.EnableWindow(FALSE);

	// noch das Caption und den Prompt ändern
	CString str;

		VERIFY(str.LoadString(IDS_CONNECTFILTERPROPS_CAP));
		SetWindowText(str);
		VERIFY(str.LoadString(IDS_FILTERNAME_PROPS));
		GetDlgItem(IDC_FILTERNAME_PROMPT) -> SetWindowText(str);
	}
	else {
	// ggf. einen neuen Namen ausdenken
		if (m_strFilterName.IsEmpty()) {
		int i = 0;

			do {
				m_strFilterName.Format(IDS_NEWCONNFILTERNAME, ++i);
			} while (CB_ERR != m_cbFilters.FindStringExact(-1, m_strFilterName));
		}
		m_cbFilters.SetCurSel(CB_ERR);		// nichts vorselektieren
		m_cbFilters.SetWindowText(m_strFilterName);
	}

	m_cbApplyToAll.SetCheck(m_fApplyToAll);

	UpdateData(FALSE);

// überm Parent zentrieren
	CenterWindow(GetParent());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateConnectfilter::OnOverlapped() 
{
	VERIFY(m_strOperatorDesc.LoadString(IDS_FILTER_OVERLAP_DESC));
	UpdateData(FALSE);
	((CButton *)GetDlgItem(IDC_OVERLAPPED)) -> SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CONTAINED)) -> SetCheck(FALSE);
}

void CCreateConnectfilter::OnContained() 
{
	VERIFY(m_strOperatorDesc.LoadString(IDS_FILTER_CONTAINS_DESC));
	UpdateData(FALSE);
	((CButton *)GetDlgItem(IDC_OVERLAPPED)) -> SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CONTAINED)) -> SetCheck(TRUE);
}

void CCreateConnectfilter::OnOK() 
{
	if (PrepareResults())
		CDialog::OnOK();
}

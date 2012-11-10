// $Header: $
// Copyright© 1999-2000 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 13.09.2000 15:48:18
//
// @doc
// @module MeshGenerationDlg.cpp | Implementation of the <c CMeshGenerationDlg> class

#include "stdafx.h"

#include "resource.h"
#include "MeshGenerationDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeshGenerationDlg

CMeshGenerationDlg* CMeshGenerationDlg::CreateInstance (LPCSTR pcCaption)
{
CMeshGenerationDlg *pCfgDlg = NULL;

// Dialog erzeugen
	ATLTRY(pCfgDlg = new CMeshGenerationDlg(pcCaption));
	return pCfgDlg; 
}

CMeshGenerationDlg::CMeshGenerationDlg(LPCSTR pcTitle) 
	: CPropertyPageImpl<CMeshGenerationDlg>(pcTitle)
{
	m_rgOperation = MESH_CONVEXHULL;
	m_dwFlags = 0;
}

CMeshGenerationDlg::~CMeshGenerationDlg()
{
}

void CMeshGenerationDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	GetPropertySheet().SetWizardButtons(dwBttns);
}

BOOL CMeshGenerationDlg::GetDisableNextPage()
{
	return FALSE;		// immer enabled
}

/////////////////////////////////////////////////////////////////////////////
// CMeshGenerationDlg message handlers

BOOL CMeshGenerationDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return CPropertyPageImpl<CMeshGenerationDlg>::OnSetActive();
}

void CMeshGenerationDlg::OnConvexhull(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	m_rgOperation = MESH_CONVEXHULL;
	m_Operation.SetBitmap(m_bmpConvexHull);
	AdjustOperation();
}

void CMeshGenerationDlg::OnDelaunay(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	m_rgOperation = MESH_DELAUNAY;
	m_Operation.SetBitmap(m_bmpDelaunay);
	AdjustOperation();
}

void CMeshGenerationDlg::OnVoronoi(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	m_rgOperation = MESH_VORONOI;
	m_Operation.SetBitmap(m_bmpVoronoi);
	AdjustOperation();
}

LRESULT CMeshGenerationDlg::OnInitDialog(HWND hWnd, LPARAM lParam) 
{
	m_Operation.Attach (GetDlgItem(IDC_OPERATION));
	m_Desc.SubclassWindow(GetDlgItem(IDC_STATIC_DESC));

	m_bmpConvexHull.LoadBitmap(IDB_CONEXHULL);
	m_bmpVoronoi.LoadBitmap(IDB_VORONOI);
	m_bmpDelaunay.LoadBitmap(IDB_DELAUNAY);

	_ASSERTE(!m_bmpConvexHull.IsNull());
	_ASSERTE(!m_bmpVoronoi.IsNull());
	_ASSERTE(!m_bmpDelaunay.IsNull());

	switch (m_rgOperation) {
	case MESH_CONVEXHULL:
		m_Operation.SetBitmap(m_bmpConvexHull);
		break;
	
	case MESH_VORONOI:
		m_Operation.SetBitmap(m_bmpVoronoi);
		break;
	
	case MESH_DELAUNAY:
		m_Operation.SetBitmap(m_bmpDelaunay);
		break;
	
	default:
		_ASSERTE(FALSE);
		break;
	}
	AdjustOperation();

// erstmal nur ConvexHull aktivieren
//	::EnableWindow(GetDlgItem(IDC_VORONOI), FALSE);
//	::EnableWindow(GetDlgItem(IDC_DELAUNAY), FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////////////
// RadioButons richten
void CMeshGenerationDlg::AdjustOperation()
{
CButton bttnConvexHull (GetDlgItem(IDC_CONVEXHULL));
CButton bttnVoronoi (GetDlgItem(IDC_VORONOI));
CButton bttnDelaunay (GetDlgItem(IDC_DELAUNAY));
CStatic ftDesc (GetDlgItem(IDC_DESC_OPERATION));

	bttnConvexHull.SetCheck(0);
	bttnVoronoi.SetCheck(0);
	bttnDelaunay.SetCheck(0);

UINT uiId = 0;

	switch (m_rgOperation) {
	case MESH_UNKNOWN:
		_ASSERTE(MESH_UNKNOWN != m_rgOperation);
		break;

	case MESH_CONVEXHULL:
		bttnConvexHull.SetCheck(1);
		uiId = IDS_DESC_CONVEXHULL;
		break;

	case MESH_VORONOI:
		bttnVoronoi.SetCheck(1);
		uiId = IDS_DESC_VORONOI;
		break;

	case MESH_DELAUNAY:
		bttnDelaunay.SetCheck(1);
		uiId = IDS_DESC_DELAUNAY;
		break;
	}

CString strDesc;

	_ASSERTE(0 != uiId);
	strDesc.LoadString(uiId);
	_ASSERTE(strDesc.GetLength() > 0);
	ftDesc.SetWindowText(strDesc);
}

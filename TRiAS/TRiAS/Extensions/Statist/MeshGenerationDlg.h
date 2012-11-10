// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.09.2000 15:48:18
//
// @doc
// @module MeshGenerationDlg.h | Declaration of the <c CMeshGenerationDlg> class

#if !defined(_MESHGENERATIONDLG_H__AC4E355E_C666_41D7_9492_43C262E1809C__INCLUDED_)
#define _MESHGENERATIONDLG_H__AC4E355E_C666_41D7_9492_43C262E1809C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "Separator.h"

/////////////////////////////////////////////////////////////////////////////
// CMeshGenerationDlg dialog

class CMeshGenerationDlg : 
	public CPropertyPageImpl<CMeshGenerationDlg>
{
// Construction
public:
	CMeshGenerationDlg(LPCSTR pcTitle);
	~CMeshGenerationDlg();

	enum MESH_OPERATION {
		MESH_UNKNOWN = -1,
		MESH_CONVEXHULL = 0,
		MESH_VORONOI = 1,
		MESH_DELAUNAY = 2,
	};
	
// Dialog Data
	enum { IDD = IDD_MESHGENERATION_OPTIONS };

	CStatic	m_Operation;
	CSeparator m_Desc;
	MESH_OPERATION m_rgOperation;

// Overrides
public:
	BOOL OnSetActive();

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CMeshGenerationDlg *CreateInstance (LPCSTR pcCaption);
	void InitWithData (MESH_OPERATION rgOperation)
	{
		m_rgOperation = rgOperation;
	}
	MESH_OPERATION GetOperation() { return m_rgOperation; }

	BEGIN_MSG_MAP_EX(CMeshGenerationDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDC_CONVEXHULL, BN_CLICKED, OnConvexhull)
		COMMAND_HANDLER_EX(IDC_DELAUNAY, BN_CLICKED, OnDelaunay)
		COMMAND_HANDLER_EX(IDC_VORONOI, BN_CLICKED, OnVoronoi)

		CHAIN_MSG_MAP(CPropertyPageImpl<CMeshGenerationDlg>)
	END_MSG_MAP()

// Implementation
protected:
	void OnConvexhull(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDelaunay(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnVoronoi(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	void AdjustOperation();

private:
	DWORD m_dwFlags;
	CBitmap m_bmpConvexHull;
	CBitmap m_bmpVoronoi;
	CBitmap m_bmpDelaunay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MESHGENERATIONDLG_H__AC4E355E_C666_41D7_9492_43C262E1809C__INCLUDED_)

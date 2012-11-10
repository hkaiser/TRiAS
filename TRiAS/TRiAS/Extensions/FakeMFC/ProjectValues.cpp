// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 10:14:37 
//
// @doc
// @module ProjectValues.cpp | Definition of the <c CProjectValues> class

#include "stdafx.h"

#if defined(_USE_PROJECTVALUES)

#include "fakemfc.h"
#include "ProjectValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectValues dialog

CProjectValues::CProjectValues(CWnd *pParent)
	: CResizableDialog(CProjectValues::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectValues)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProjectValues::~CProjectValues()
{
	if (NULL != m_hWnd)
		DestroyWindow();
	_ASSERTE(NULL == m_hWnd);
}

void CProjectValues::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectValues)
	DDX_Control(pDX, IDC_VALUES, m_ValueStore);
	DDX_Control(pDX, IDC_CATEGORIES, m_Categories);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProjectValues, CResizableDialog)
	//{{AFX_MSG_MAP(CProjectValues)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectValues message handlers

BOOL CProjectValues::OnInitDialog() 
{
	CResizableDialog::OnInitDialog();

	ShowSizeGrip(false);

	AddAnchor(IDC_STATIC_CATEGORIES, TOP_LEFT);
	AddAnchor(IDC_CATEGORIES, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_VALUES, TOP_LEFT, BOTTOM_RIGHT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectValues::OnCancel()
{
// einfach abfangen
}

#endif // defined(_USE_PROJECTVALUES)

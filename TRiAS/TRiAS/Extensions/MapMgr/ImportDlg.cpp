// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 12:01:47 
//
// @doc
// @module ImportDlg.cpp | Definition of the <c CImportDlg> class

#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMapImportDlg, CPropertySheet)

/////////////////////////////////////////////////////////////////////////////
// CMapImportDlg dialog

CMapImportDlg::CMapImportDlg(CWnd* pParent /*=NULL*/) :
	CPropertySheet(CMapImportDlg::IDD, pParent),
	m_sizeOfPicture(0,0)
{
	//{{AFX_DATA_INIT(CMapImportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	AddPage(&m_ppgSelMapType);
	AddPage(&m_ppgFiles);
	AddPage(&m_ppgSelCoordSys);
	AddPage(&m_ppgDataSource);

// KK010307
//	AddPage(&m_ppgSelDocFile);

	AddPage(&m_ppgSelAddFile);
	AddPage(&m_ppgNomenclatur);
	AddPage(&m_ppgMapInfo);
	AddPage(&m_ppgImportFile);
	AddPage(&m_ppgRefPoints);
	AddPage(&m_ppgIntergraph);

	SetWizardMode();

	ReadEngines();

// KK001120
	m_bMulti = false;		// Einzelverarbeitung
	m_lMultiCount = 0;

// KK010315
	m_bNoReduce = false;
//	m_bDstDir = FALSE;

	m_hPr = HACTCONNECTION;
}

CMapImportDlg::~CMapImportDlg() 
{
	m_treeOfEngines.clear();
	::CoFreeUnusedLibraries();
}

void CMapImportDlg::DoDataExchange(CDataExchange* pDX) 
{
	CPropertySheet::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapImportDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapImportDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CMapImportDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapImportDlg message handlers

BOOL CMapImportDlg::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();

	try {
	CComObject<CPictHolder> *pNew = NULL;

		CComObject<CPictHolder>::CreateInstance(&pNew);
		m_pTopoPict = pNew;
	} 
	catch(...) {
		;
	}

	if (!m_pTopoPict) {
	CString sText;
	
		sText.LoadString(IDS_NOMAPINIT);
		::AfxMessageBox(sText);
		return FALSE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

const TCHAR szReg[] = _T("Software\\") REG_COMPANY_KEY _T("\\")
	REG_PRODUCT_KEY _T("\\Extensions\\TRiAS.MapMgr.Import.1\\ImportEngines");

HRESULT CMapImportDlg::ReadEngines() 
{
HKEY	hk = NULL;
TCHAR	strName[_MAX_PATH];
CLSID	clsid;
DWORD	dwSize = _countof(strName);
CComBSTR	strPictFilter;
CComBSTR	strDisplayName;

	USES_CONVERSION;
	if (ERROR_SUCCESS == ::RegOpenKeyEx (HKEY_CURRENT_USER, szReg, 0, KEY_ALL_ACCESS, &hk)) {
		for (DWORD dwIndex = 0; 
			ERROR_SUCCESS == ::RegEnumKeyEx(hk, dwIndex, strName, &dwSize, 0, NULL, NULL, NULL); 
			++dwIndex) 
		{
			dwSize = _countof(strName);
			::CLSIDFromString(A2W(strName), &clsid);

		MAPPOINTER p;
		HRESULT	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_ITopoMap, (void **)&p);

			if (S_OK != hr)
				continue;

		CComBSTR strDisplay;

			if (S_OK != p->GetDisplayName(&strDisplay) || 0 == strDisplay.Length())
				continue;

		CComBSTR strMapTyp;

			p->GetAltFileTyp(&strMapTyp);
			m_strMapExt = W2A(strMapTyp);

		TCHAR fmtBuf[_MAX_PATH];
		CString S;

			S.LoadString (IDS_IMPORTNAME);
			wsprintf(fmtBuf, _T("%s%s"), (LPCTSTR)S, W2A(strDisplay));
			m_treeOfEngines.Add(fmtBuf, CComPtr<IUnknown>(p));
		}
		::RegCloseKey( hk );
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgewählten Importmodul auffordern das Verzeichnis zu korrigieren (ggf.)
void CMapImportDlg::CorrectDirectory()
{
CComBSTR bstrToWrite;

	USES_CONVERSION;
	if (SUCCEEDED(m_pTopoMap->CorrectDirectory(CComBSTR(m_strDstDir), &bstrToWrite)))
		m_strDstDir = OLE2A(bstrToWrite);
}

///////////////////////////////////////////////////////////////////////////////
// Der Koordinatenseite mitteilen, ob sie die letzte Seite ist
void CMapImportDlg::SetCoordSystemIsLast(bool fFlag)
{
	m_ppgSelCoordSys.SetIsLast(fFlag);	
}

///////////////////////////////////////////////////////////////////////////////
// 
TREENODE::TREENODE(CComPtr<IUnknown>& data) :
	m_data(data)
{
}

TREENODE::~TREENODE() 
{
	m_childs.erase( m_childs.begin(), m_childs.end() );
}

PUNKTREE::~PUNKTREE() 
{
	erase( begin(), end() );
}

HRESULT PUNKTREE::Add(LPCTSTR lpszDisplay, CComPtr<IUnknown>& p) 
{
	if( !lpszDisplay || _T('\0') == *lpszDisplay )
		return S_FALSE;
	TCHAR	strTmp[_MAX_PATH];
	LPCTSTR	lpszEnd = lpszDisplay;
	LPTSTR	lpszStart = strTmp;
	memset( strTmp, 0x00, sizeof( strTmp ) );
	for( lpszEnd = lpszDisplay; *lpszEnd && _T('\\') != *lpszEnd; lpszEnd++, lpszStart++ ) {
		*lpszStart = *lpszEnd;
	}
	if( _T('\\') == *lpszEnd ) {
		insert( strTmp, TREENODE( CComPtr<IUnknown>( NULL ) ) );
		if( _T('\0') == ++lpszEnd )
			return S_OK;
		PUNKTREE::iterator i = find( strTmp );
		_ASSERTE( end() != i );
		return (*i).second.m_childs.Add( lpszEnd, p );
	} else if( _T('\0') == *lpszEnd ) {
		insert( strTmp, TREENODE( CComPtr<IUnknown>( p ) ) );
	}
	return S_OK;
}

int PUNKTREE::Traverse( PUNKINSPECTOR& inspector ) 
{
	for( PUNKTREE::iterator i = begin(); end() != i; i++ ) {
		inspector.OnNode( (*i).first, (*i).second );
	}
	return 0;
}


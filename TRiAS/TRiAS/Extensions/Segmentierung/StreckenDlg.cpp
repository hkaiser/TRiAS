// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 19.07.2002 09:47:45
//
// @doc
// @module StreckenDlg.cpp | Implementation of the <c CStreckenDlg> class

#include "stdafx.h"

#include "Segment.h"
#include "StreckenDlg.h"

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#import	"tlb/TRiASDB.tlb"	\
	raw_interfaces_only		\
	, raw_dispinterfaces	\
	, no_namespace			\
	, named_guids exclude("IObjectWithSite")



// SmartIF's
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);

#include "DatasourceIcon.h"


/////////////////////////////////////////////////////////////////////////////
// CStreckenDlg

CStreckenDlg* CStreckenDlg::CreateInstance (LPCSTR pcCaption)
{
CStreckenDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CStreckenDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);


	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CStreckenDlg, CPropertyPage)

CStreckenDlg::CStreckenDlg() 
	: CPropertyPage(CStreckenDlg::IDD)
{
	//{{AFX_DATA_INIT(CStreckenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;

	m_bKnoten = 1;		// Knoten bilden
	m_bKanten = 0;		// keine Kanten bilden

	CString sK;
//	CString sA;

	sK.LoadString(IDS_KNOTENTEXT);
//	sA.LoadString(IDS_KANTENTEXT);

	m_nDescription = sK;

//	m_hPr = HACTCONNECTION;
	m_hPr = DEX_GetDataSourceHandle();

}

CStreckenDlg::~CStreckenDlg()
{
}

void CStreckenDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStreckenDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Control(pDX, IDC_CHECKKNOTEN, m_btnKnoten);
//		DDX_Control(pDX, IDC_CHECKKANTEN, m_btnKanten);
		DDX_Control(pDX, IDC_COMBODATASOURCE, m_cbDataSources);
		DDX_Control(pDX, IDC_BESCHREIBUNG, m_nText);
		DDX_Check(pDX, IDC_CHECKKNOTEN, m_bKnoten);
//		DDX_Check(pDX, IDC_CHECKKANTEN, m_bKanten);
		DDX_Text(pDX, IDC_BESCHREIBUNG, m_nDescription);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStreckenDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CStreckenDlg)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(IDC_CHECKKNOTEN, OnKnoten)
//		ON_BN_CLICKED(IDC_CHECKKANTEN, OnKanten)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CStreckenDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = (CPropertySheet *) GetParent();

	ASSERT(NULL != pSheet);	

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


	dwBttns |= (CB_ERR == m_cbDataSources.GetCurSel()) ? PSWIZB_DISABLEDFINISH : PSWIZB_FINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CStreckenDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  message handlers

BOOL CStreckenDlg::OnInitDialog() 
{


	CPropertyPage::OnInitDialog();
	
CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_PROJECTTYPES) || !bmpMask.LoadBitmap(IDB_PROJECTTYPES_MASK)) 
		TRACE0("Could not load bitmaps for CDataServerList\r\n");
	else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 20, 0) ||
			-1 ==  m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CDataServerList\r\n");
		} else 
			m_cbDataSources.SetImageList(&m_ilImages);
	}

// Combobox füllen
	FillDataSources();

	m_nText.SetWindowText (m_nDescription);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
BOOL CStreckenDlg::OnWizardFinish() 
{
int iSelItem = m_cbDataSources.GetCurSel();

	if (CB_ERR != iSelItem) {
	COMBOBOXEXITEM item;

		item.mask = CBEIF_LPARAM;
		item.iItem = iSelItem;
		VERIFY(m_cbDataSources.GetItem(&item));
		m_hPr = (HPROJECT)item.lParam;
	}
	return CPropertyPage::OnWizardFinish();
}

/////////////////////////////////////////////////////////////////////////////
// CStreckenDlg message handlers

BOOL CStreckenDlg::OnSetActive() 
{

	m_btnKnoten.SetCheck(m_bKnoten);
//	m_btnKanten.SetCheck(m_bKanten);

	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Datenquellen füllen
struct CCompareNoCase :
	binary_function<CString, CString, bool>
{
	bool operator()(const CString& _X, const CString& _Y) const
	{
		return _X.CompareNoCase(_Y) < 0;
	}
};

typedef map<CString, pair<DWORD, HPROJECT>, CCompareNoCase> CComboEntryMap; 

BOOL CStreckenDlg::FillDataSources()
{
LONG lCntOpen = 0;
int iSelItem = CB_ERR;

	USES_CONVERSION;
	COM_TRY {
	// alle Connections durchgehen und feststellen:
	// aktuelle Connection, ob beschreibbare Connection existiert
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

	WTRiASConnections Conns;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

	CComboEntryMap Entries;

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			// geöffnet
			CComBSTR bstrName;

			THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(bstrName)));

			// wenns die aktuelle ist, dann den Index speichern
			WTRiASDatabase DBase;
			HPROJECT lHandle = 0; 

				THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)&lHandle));

				Entries.insert(CComboEntryMap::value_type(OLE2A(bstrName), 
					pair<DWORD, HPROJECT>(datasource_icon::GetBitmapIndex(lHandle), lHandle)));
			}
		}

	// jetzt in ComboBox einfügen (in alphabetischer Reihenfolge)
	CComboEntryMap::iterator end = Entries.end();

		for (CComboEntryMap::iterator it = Entries.begin(); it !=end; ++it) {
		COMBOBOXEXITEM item;

			item.mask = CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_LPARAM|CBEIF_TEXT;
			item.iItem = -1;
			item.pszText = (LPTSTR)(LPCTSTR)(*it).first;
			item.iImage = item.iSelectedImage = (*it).second.first;
			item.lParam = (LPARAM)(*it).second.second;			// ProjectHandle zuordnen
			int i = m_cbDataSources.InsertItem(&item);
			lCntOpen++;

			if ((*it).second.second == m_hPr)
				iSelItem = item.iItem;
		}

	} COM_CATCH_RETURN(FALSE);

	_ASSERTE(0 != lCntOpen);
	if (0 == lCntOpen) 		// keine Datenquellen vorhanden
		return FALSE;

	if (CB_ERR != iSelItem)
		m_cbDataSources.SetCurSel(iSelItem);
	else
		m_cbDataSources.SetCurSel(0);


	UpdateData();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
///
void CStreckenDlg::OnKnoten()  
{

	CString sK;
//	CString sA;
	CString sN;

	sK.LoadString(IDS_KNOTENTEXT);
//	sA.LoadString(IDS_KANTENTEXT);
	sN.LoadString(IDS_NODATEN);

	m_nDescription = "" ;

	if ( m_btnKnoten.GetCheck()) 
		m_nDescription += sK ;
//	if ( m_btnKanten.GetCheck()) 
//		m_nDescription += sA ;

	if ( m_nDescription.IsEmpty())
		m_nDescription += sN ;

	m_nText.SetWindowText (m_nDescription);

	UpdateData();
}


/////////////////////////////////////////////////////////////////////////////
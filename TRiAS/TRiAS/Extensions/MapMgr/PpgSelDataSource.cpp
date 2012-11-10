// PpgSelDataSource.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#import "tlb/TRiASDB.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids exclude("IObjectWithSite")

#include "DatasourceIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDataSource property page

IMPLEMENT_DYNCREATE(CPpgSelDataSource, CPropertyPage)

CPpgSelDataSource::CPpgSelDataSource() : CPropertyPage(CPpgSelDataSource::IDD)
{
	//{{AFX_DATA_INIT(CPpgSelDataSource)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgSelDataSource::~CPpgSelDataSource()
{
}

void CPpgSelDataSource::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgSelDataSource)
	DDX_Control(pDX, IDC_SELECTDATASOURCE, m_cbDataSources);
	//}}AFX_DATA_MAP
}

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

BOOL CPpgSelDataSource::FillDataSources()
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
			CONNECTMODE rgRW = CONNECTMODE_OpenReadOnly;

				THROW_FAILED_HRESULT(Conn -> get_Mode (&rgRW));
				if (CONNECTMODE_OpenReadWrite == 
					CONNECTMODE(rgRW & ~CONNECTMODE_ResolutionFlags)) 
				{
				// R/W geöffnet
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
			m_cbDataSources.InsertItem(&item);
			lCntOpen++;

			if ((*it).second.second == m_pParent->m_hPr)
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
	return TRUE;
}
	

void CPpgSelDataSource::UpdateControls()
{
	m_pParent->m_hPr = HACTCONNECTION;
	AdjustButtons();
}

void CPpgSelDataSource::AdjustButtons()
{
DWORD dwButtons = PSWIZB_BACK;

	dwButtons |= (CB_ERR == m_cbDataSources.GetCurSel()) ? PSWIZB_DISABLEDFINISH : PSWIZB_FINISH;
	m_pParent->SetWizardButtons(dwButtons);
}

BEGIN_MESSAGE_MAP(CPpgSelDataSource, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgSelDataSource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDataSource message handlers

BOOL CPpgSelDataSource::OnInitDialog() 
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CPpgSelDataSource::OnWizardFinish() 
{
int iSelItem = m_cbDataSources.GetCurSel();

	if (CB_ERR != iSelItem) {
	COMBOBOXEXITEM item;

		item.mask = CBEIF_LPARAM;
		item.iItem = iSelItem;
		VERIFY(m_cbDataSources.GetItem(&item));
		m_pParent->m_hPr = (HPROJECT)item.lParam;
	}
	return CPropertyPage::OnWizardFinish();
}

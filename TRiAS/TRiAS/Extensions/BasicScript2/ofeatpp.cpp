// ofeatdlg.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>
#include <iobjman.h>

#include "macrguid.h"
#include "iscrprop.h"

#include "macro.h"
#include "objfeat.h"
#include "ofeatpp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OS_NO_STREAM_SUPPORT

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

DefineSmartInterface(AddScriptProperty);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(ObjectManagement);

////////////////////////////////////////////////////////////////////////////
// Deklaration externer globaler Funktionen
BOOL	LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// CObjFeatInstallDlg dialog

IMPLEMENT_DYNCREATE(CObjFeatInstallDlg, CPropertyPage)

CObjFeatInstallDlg::CObjFeatInstallDlg()
	: CPropertyPage(CObjFeatInstallDlg::IDD)
{
	//{{AFX_DATA_INIT(CObjFeatInstallDlg)
	//}}AFX_DATA_INIT
	m_fLock = false;
	m_fMustBeGray = false;
}

CObjFeatInstallDlg::~CObjFeatInstallDlg()
{
}

void CObjFeatInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjFeatInstallDlg)
	DDX_Control(pDX, IDC_STATICML, m_staticAvailableItems);
	DDX_Control(pDX, IDC_MACROLIST, m_clbxMacroList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CObjFeatInstallDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CObjFeatInstallDlg)
	ON_LBN_SELCHANGE(IDC_MACROLIST, OnSelchangeMacrolist)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjFeatInstallDlg message handlers

BOOL CObjFeatInstallDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
 
	FillListBox(); 
	InitDialogControls();

	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CObjFeatInstallDlg::OnOK() 
{
	HRESULT hr = Install();
	if (E_UNEXPECTED == hr) return;
	SetApplyButton(hr);
	CPropertyPage::OnOK();
}

BOOL CObjFeatInstallDlg::OnApply() 
{
	//Install();, hier wird auch OnOk() gerufen 
	return CPropertyPage::OnApply();
}

BOOL CObjFeatInstallDlg::OnSetActive() 
{
	InitDialogControls();
	return CPropertyPage::OnSetActive();
}

void CObjFeatInstallDlg::InitDialogControls()
{
	CString str;
	if (NULL == DEX_GetActiveProjectHandle() || 0 == m_clbxMacroList.GetCount())
	{
	// Disable der Page, wenn leer		
		m_fMustBeGray = true;
		m_clbxMacroList.EnableWindow(false);
		::LoadString(str, IDS_NOAVAILABLEITEMS);
		m_staticAvailableItems.SetWindowText(str);
	}
	else {
		m_fMustBeGray = false;
		m_clbxMacroList.EnableWindow(true);
		::LoadString(str, IDS_AVAILABLEITEMS);
		m_staticAvailableItems.SetWindowText(str);
		m_clbxMacroList.SetFocus();	
	}
}

HBRUSH CObjFeatInstallDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
// TODO: Return a different brush if the default is not desired
HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);	

	if (pWnd->GetDlgCtrlID() == IDC_MACROLIST && m_fMustBeGray)
		return (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);	
	return hbr;
}

void CObjFeatInstallDlg::OnSelchangeMacrolist() 
{
	SetApplyButton();
}

HRESULT CObjFeatInstallDlg::FillListBox()
{
HRESULT hr = NOERROR;

	if (NULL == DEX_GetActiveProjectHandle())
		return hr;
		
	USES_CONVERSION;
	try {
	WUnknown IU;

		THROW_FAILED_HRESULT(g_pBSE -> GetObjectFeatureScripts() -> EnumStrings(IU.ppi()));

	CString str, strOld;

		if (!LoadString (str, IDS_NEWSTREAMINFO)) _com_issue_error(E_OUTOFMEMORY);
		if (!LoadString (strOld, IDS_NEWSTREAMINFO)) _com_issue_error(E_OUTOFMEMORY);

	WEnumos_wstring IE(IU);
	os_wstring oswstr;

		for (IE -> Reset(); S_OK == IE -> Next(1, &oswstr, NULL); /**/) 
		{			
		LPSTR lpstr = OLE2A(oswstr.c_str());	
		
			if (0 == _stricmp(str, lpstr) || 0 == _stricmp(strOld, lpstr)) 
				continue;

		DWORD dwInfo = 0;
		
			THROW_FAILED_HRESULT(g_pBSE -> GetInfoObjFeatureScripts() -> Get(A2OLE(lpstr), &dwInfo));

			if (!(dwInfo & SUPERITEM)) 
				continue;

		int i = m_clbxMacroList.AddString(lpstr);
		
			if (LB_ERR == i || LB_ERRSPACE == i) 
				_com_issue_error(E_FAIL);
						
			if (dwInfo & OBJFEAT_INSTALLED)
				m_clbxMacroList.SetCheck(i, 1);
			else // Wenn Installiert Checken
				m_clbxMacroList.SetCheck(i, 0);
		}
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CObjFeatInstallDlg::SetApplyButton(HRESULT hr)
{
int i = m_clbxMacroList.GetCurSel();

	if (LB_ERR == i) return S_FALSE; 

	try 
	{// von dieser Erweiterung Objektmanagement geben lassen
	WObjectManagement IOM = g_pBSE -> GetObjectFeatureScripts(); 
	
	// Selektierten geben lassen
	CString str;

		m_clbxMacroList.GetText(i, str);
		if (str.IsEmpty()) _com_issue_error(E_FAIL);
	
	// Cooky holen
	DWORD dwID = 0;
	
		THROW_FAILED_HRESULT(GetCooky(IOM, str, dwID));

	//	ist inst., 	soll uninst.
	BOOL fCheck = m_clbxMacroList.GetCheck(i);

		if ((0 != dwID && 0 == fCheck || 0 == dwID && 1 == fCheck) && SUCCEEDED(hr)) // ApplyButton schwarz
			SetModified(true);
		else
			SetModified(false);
	} 
	catch (_com_error &e)
	{
		return _COM_ERROR(e); 
	}

	return NOERROR;
}

HRESULT CObjFeatInstallDlg::Install()
{
	CWaitCursor wait;	
	HRESULT hr = NOERROR;

	if (true == m_fLock) return E_UNEXPECTED;
	m_fLock = true;

	USES_CONVERSION;
	try {	
	// von dieser Erweiterung Objektmanagement geben lassen
	WObjectManagement IOM = g_pBSE -> GetObjectFeatureScripts(); 
	WStreamInfo	ISI = g_pBSE -> GetInfoObjFeatureScripts(); 

	// Liste der Objekteigenschaften durchlaufen
		for (int i = 0; i < m_clbxMacroList.GetCount(); i++) {	// Namen geben lassen
		CString str;

			m_clbxMacroList.GetText(i, str);
			if (str.IsEmpty()) continue;
		
		// Cooky merken
		DWORD dwID = 0;
		
			THROW_FAILED_HRESULT(GetCooky(IOM, str, dwID));

		// Ursprüngliche Streamifo zum Namen geben lassen
		DWORD dwInfo = 0;

			THROW_FAILED_HRESULT(ISI -> Get(A2OLE(str), &dwInfo));

		//	ist inst., 	soll uninst.
			if (0 != dwID && 0 == m_clbxMacroList.GetCheck(i))
			{// Uninstall....
			// EndProperty rufen, egal was passiert, immer Remove !!!
				Uninstall(IOM, str);

			// Objekt wieder schlessen, um neu zu laden
			// Wenn neues Objekt, muß in GetObject() Objekt -> Load() 
			// für Refresh des Namens gesorgt werden
			WUnknown IU;

				THROW_FAILED_HRESULT(RefreshObject(IOM, str, IU.ppi()));

			////////////////////////////////////
			// eigentliche DEINSTALLIERUNG
				if (!g_pBSE -> RemovePropertyFunction (dwID)) 
					_com_issue_error(E_FAIL);
				
				dwID = 0;
			
			// Neue Info wegeschreiben
				dwInfo &= OBJFEAT_UNINSTALLED;
				THROW_FAILED_HRESULT(SaveInfo(IOM, ISI, dwInfo, str));
				SetModified();
			}
			// nicht inst.,		soll installiert werden
			else if (0 == dwID && 1 == m_clbxMacroList.GetCheck(i))
			{	
			// Query... Install....
			// Objekt wieder schlessen, um neu zu laden
			// Wenn neues Objekt, muß in GetObject() Objekt -> Load() 
			// für Refresh des Namens gesorgt werden
			WUnknown IU;

				THROW_FAILED_HRESULT(RefreshObject(IOM, str, IU.ppi()));

			// BeginProperty rufen
			HRESULT hr = Install(IOM, str);
			
			// wenn nicht implementiert, trotzdem installieren
				if (FAILED(hr) && E_NOTIMPL != hr) 
				{// Check zurücksetzen, auch bei Laufzeitfehler (E_ABORT)
					m_clbxMacroList.SetCheck(i, 0); 
					continue;
				}

			////////////////////////////////////
			// eigentliche INSTALLIERUNG
			WObjectProperty IOP = IU;

				dwID = g_pBSE -> AddPropertyFunction (IOP);
				if (0 == dwID) _com_issue_error(E_UNEXPECTED);

			// Neue Info wegeschreiben
				dwInfo |= OBJFEAT_INSTALLED;
				THROW_FAILED_HRESULT(SaveInfo(IOM, ISI, dwInfo, str));
				SetModified();
			}
		// Cookie im Objekt RÜCKSETZEN
			THROW_FAILED_HRESULT(SetCooky(IOM, str, dwID));
		}
		// Smarts -> Release()
	} 
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e); 
		TRACE("Installierung bzw. Deinstallierung der Objekteigenschaft schlug fehl.'\n'");
	}

	m_fLock = false;
	return hr;
}


HRESULT CObjFeatInstallDlg::SaveInfo(
									IObjectManagement *pIOM,
									IStreamInfo *pISI, 
									DWORD dwInfo,
									CString str)
{
	ASSERT(pIOM);
	ASSERT(pISI); 

	USES_CONVERSION;
	
	HRESULT hr = pISI -> Set(A2OLE(str), dwInfo);				
	if (FAILED(hr)) return hr;
	
//	CString strInfo;
//	if (!LoadString(strInfo, IDS_NEWSTREAMINFO)) return E_OUTOFMEMORY;	
// neue Streaminfo speichern
//	hr = pIOM -> SaveObject(A2OLE(strInfo)); ???
//	if (FAILED(hr)) return hr;
	// Speichern notwendig
	DEX_SetDirtyGeoDB(true);

	return hr;
}

HRESULT CObjFeatInstallDlg::GetCooky(IObjectManagement *pIOM, LPCSTR lpcstr, DWORD & dwID)
{
	ASSERT(pIOM);
	ASSERT(lpcstr);

// Altes Objekt für GetCooky() geben lassen
	USES_CONVERSION;
	dwID = 0;
	try {
	WUnknown IU;

		THROW_FAILED_HRESULT(pIOM -> GetObject(A2OLE(lpcstr), IU.ppi()));

	// Ursprüngliche Coocky (Install_List_Id) vom Objekt geben lassen
	WAddScriptProperty IASP = IU;

		// muß vor ReleaseObject für RÜCKSETZEN geschehen,
		THROW_FAILED_HRESULT(IASP -> GetCooky(&dwID));
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
	
	return NOERROR;
}

HRESULT CObjFeatInstallDlg::Install(IObjectManagement *pIOM, LPCSTR lpcstr)
{
	ASSERT(pIOM);
	ASSERT(lpcstr);

	USES_CONVERSION;

	try
	{
	WUnknown IU;

		THROW_FAILED_HRESULT(pIOM -> GetObject(A2OLE(lpcstr), IU.ppi()));
		THROW_FAILED_HRESULT(WAddScriptProperty(IU) -> Install());
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CObjFeatInstallDlg::Uninstall(IObjectManagement *pIOM, LPCSTR lpcstr)
{
	ASSERT(pIOM);
	ASSERT(lpcstr);

	USES_CONVERSION;

	try
	{
	WUnknown IU;

		THROW_FAILED_HRESULT(pIOM -> GetObject(A2OLE(lpcstr), IU.ppi()));
		THROW_FAILED_HRESULT(WAddScriptProperty(IU) -> Uninstall());
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CObjFeatInstallDlg::SetCooky(IObjectManagement *pIOM, LPCSTR lpcstr, DWORD dwID)
{
	ASSERT(lpcstr);
	ASSERT(pIOM);

	USES_CONVERSION;

	try
	{
	WUnknown IU;

		THROW_FAILED_HRESULT(pIOM -> GetObject(A2OLE(lpcstr), IU.ppi()));
		THROW_FAILED_HRESULT(WAddScriptProperty(IU) -> SetCooky (dwID));
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return NOERROR;
}

HRESULT CObjFeatInstallDlg::RefreshObject(IObjectManagement *pIOM, LPCSTR lpcstr, LPUNKNOWN *ppUnk)
{
	ASSERT(pIOM);
	ASSERT(lpcstr);

	USES_CONVERSION;

	try {
	// Objekt wieder schlessen, um neu zu laden
	LPOLESTR poleName = A2OLE(lpcstr);

		THROW_FAILED_HRESULT(pIOM -> ReleaseObject(poleName));

	// Wenn neues Objekt, muß in GetObject() Objekt -> Load() 
	// für Refresh des Namens durchgeführt werden
		return pIOM -> GetObject(poleName, ppUnk);

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
}




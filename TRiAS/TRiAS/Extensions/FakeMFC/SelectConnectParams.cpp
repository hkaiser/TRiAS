// SelectConnectParams.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <shlobj.h>
#include <ospace/file/path.h>
#include <ospace/string/regexp.h>

#include <ciid.h>
#include <Registrx.hxx>
#include <ixtnext.hxx>
#include <Helper.h>
//#include <Helper_i.c>
#include <itoolbar.h>

const CLSID CLSID_ParseStringPairs = {0xC21AAF96,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

#include "FakeMFC.hxx"
#include "Strings.h"
#include "OpenNewPropertySheet.h"
#include "CreateNewWiz.h"
#include "SelectConnectParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SETFOCUSTOCONNECTIONNAME	(WM_USER+2345)
#define WM_SWITCHTONEXTPAGE			(WM_USER+2346)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TriasPropSheetExt);		// WTriasPropSheetExt
DefineSmartInterface(ParseStringPairs);			// WParseStringPairs
DefineSmartInterface(ParseStringPairs2);		// WParseStringPairs2

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectParams property page

IMPLEMENT_DYNCREATE(CSelectConnectParams, CPropertyPage)

CSelectConnectParams::CSelectConnectParams(UINT uiResID, BOOL fAsDbmsPage, UINT uiCapID) 
	: CPropertyPage(uiResID),
	  m_pParams(NULL), m_fAsDbmsPage(fAsDbmsPage)
{
	//{{AFX_DATA_INIT(CSelectConnectParams)
	m_strConnectDesc = _T("");
	m_strConnectName = _T("");
	m_strFileName = _T("");
	//}}AFX_DATA_INIT

	m_fIsTempName = FALSE;
	m_fHasExtPages = FALSE;
	m_fHasCoordSystem = FALSE;
	m_fWasNext = FALSE;

	m_pCoordSysWiz = NULL;
	m_uiCaption = CCreateNewWiz::IDD_CAPTION_NEW;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (uiCapID));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CSelectConnectionPage\r\n");
	} END_CATCH;
}

CSelectConnectParams::~CSelectConnectParams()
{
	if (m_fHasCoordSystem) {
		_ASSERTE(NULL != m_pCoordSysWiz);
		m_pCoordSysWiz -> HandleConnectString();
		m_pCoordSysWiz -> SetPairs(NULL, NULL);
		if (::IsWindow(m_pCoordSysWiz->m_hWnd)) 
			GetPropSheet()->RemovePage(m_pCoordSysWiz);
		DELETE_OBJ(m_pCoordSysWiz);
		m_fHasCoordSystem = FALSE;
	}
}

void CSelectConnectParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectConnectParams)
	DDX_Control(pDX, IDC_DESCTEXT, m_ftDescText);
	DDX_Text(pDX, IDC_CONNECT_DESCRIPTION, m_strConnectDesc);
	DDX_Text(pDX, IDC_CONNECTION_NAME, m_strConnectName);
	//}}AFX_DATA_MAP

	if (!m_fAsDbmsPage) {
		DDX_Control(pDX, IDC_SELECTFILEORDIR_PROMPT, m_ftSelectPrompt);
		DDX_Text(pDX, IDC_SELECTFILEORDIR, m_strFileName);

		if (m_fNameIsFile) {
			ASSERT(!m_pParams -> m_fNameIsDir && !m_pParams -> m_fNameIsSubStorage);

		// Dateinamen auswählen
		DWORD dwFlags = 0;

			if (!IsWin40())
				dwFlags |= GF_OLD_STYLE_DIALOG;

			if (!m_pParams -> m_fIsReadWrite)
				dwFlags |= GF_HIDEREADONLY;
			if (m_pParams -> m_fMultipleFiles)
				dwFlags |= GF_MULTIPLESELECTION;
			
		UINT uiResID = 0;

			if (DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode()) {
				uiResID = IDS_FILECREATECAPTION;
				dwFlags |= GF_SAVEASDIALOG|GF_HIDEREADONLY|GF_OVERWRITEPROMPT;
			} else {
				uiResID = IDS_DATASOURCEOPENCAPTION;
				dwFlags |= GF_FILEMUSTEXIST;
			}

		CString strCaption;

			strCaption.Format (uiResID, m_strFileDesc);
			DDX_GetFilenameControl(pDX, IDC_SELECTFILEORDIR, 
					m_sleGetFileName, dwFlags, 
					strCaption, m_pParams -> m_strFilter,
					m_pParams -> m_strDefExt,
					m_pParams -> m_strLastDirUsed);

		} 
		else if (m_pParams -> m_fNameIsDir) {
			ASSERT(!m_pParams -> m_fNameIsFile && !m_pParams -> m_fNameIsSubStorage);
//			ASSERT(!m_pParams -> m_fIsReadWrite);	// zur Zeit nur dateibezogen möglich

		// Verzeichnis auswählen
		DWORD dwFlags = 0;

			if (!IsWin40())
				dwFlags |= GFLDR_OLD_STYLE_DIALOG;
			if (IsWin50() && m_pParams -> m_fIsReadWrite)
				dwFlags |= GFLDR_SAVEASDIALOG;

		CString strCaption;
		os_path fileordir = os_string(m_pParams -> m_strLastDirUsed);

			fileordir.no_extension();
			fileordir.filename(g_cbNil);

			strCaption.Format (IDS_FOLDERCAPTION, m_strFileDesc);
			DDX_GetFolderControl(pDX, IDC_SELECTFILEORDIR, 
				m_sleGetFolder, dwFlags, strCaption,
				(LPCSTR)fileordir);
		} 
		else {
		// Oracle etc.
			ASSERT(m_pParams -> m_fNameIsFile || m_pParams -> m_fNameIsDir || m_pParams -> m_fNameIsSubStorage);
		}
	} 
}

BEGIN_MESSAGE_MAP(CSelectConnectParams, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectConnectParams)
	ON_EN_CHANGE(IDC_CONNECTION_NAME, OnChangeConnectionName)
	ON_EN_KILLFOCUS(IDC_CONNECTION_NAME, OnKillfocusConnectionName)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FILESELECTED, OnFileOrDirSelected)
	ON_MESSAGE(WM_DIRSELECTED, OnFileOrDirSelected)
	ON_MESSAGE(WM_SETFOCUSTOCONNECTIONNAME, OnSetFocusToConnectionName)
	ON_MESSAGE(WM_SWITCHTONEXTPAGE, OnSwitchToNextPage)
END_MESSAGE_MAP()

void CSelectConnectParams::AdjustButtons (bool fForceDisableNext)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = PSWIZB_BACK;
DATASOURCEMODE rgMode = GetPropSheet() -> GetDatasourceMode();

	UpdateData(TRUE);
	if (fForceDisableNext) {
		if (!m_fHasExtPages && !m_fHasCoordSystem) 
			dwBttns |= PSWIZB_DISABLEDFINISH;
	} 
	else {
		if (!m_fHasExtPages && !m_fHasCoordSystem) {
			if ((!m_fAsDbmsPage && m_strFileName.IsEmpty()) || m_strConnectName.IsEmpty())
				dwBttns |= PSWIZB_DISABLEDFINISH;
			else
				dwBttns |= PSWIZB_FINISH;
		} else {
			ASSERT(rgMode == DATASOURCEMODE_CreateNew || 
				   rgMode == DATASOURCEMODE_OpenExistend);

			if ((m_fAsDbmsPage || !m_strFileName.IsEmpty()) && !m_strConnectName.IsEmpty())
				dwBttns |= PSWIZB_NEXT;
		}
	}
	pSheet -> SetWizardButtons (dwBttns);
}

BOOL CSelectConnectParams::SaveSelectedDirectory (
	LPCTSTR pcProgID, LPCTSTR pcFileName)
{
	if (m_fIsTempName)	// temporärer Name
		return TRUE;

// Verzeichnis übrig lassen
//os_path fileordir = os_string(pcFileName);
//
//	fileordir.no_extension();
//	fileordir.filename(g_cbNil);

#if _TRiAS_VER <= 0x0420
#pragma TODO("LastDirUsed muß unter HKCU gespeichert werden!")

// RegistryKey zusammenbauen
os_string str (pcProgID);

	str += os_string(g_cbDel) + g_cbTRiASDB + g_cbDel + g_cbDescription;

CClassesRoot reg (str.c_str(), true);	// HKCR\\DataServerProgID\\TRiASDB\\Description

#else
os_string str ("Software");

	str += os_string(g_cbDel) + REG_COMPANY_KEY + g_cbDel + REG_PRODUCT_KEY;
	str += os_string(g_cbDel) + g_cbTRiASDB + g_cbDel + pcProgID;

CCurrentUser reg (str.c_str(), true);	// HKCU\\TRiAS\\TRiAS\\TRiASDB\\ProgId

#endif // _TRiAS_VER <= 0x0430

// jetzt letztes Verzeichnis hier mit speichern
	if (reg.isValid())
		return reg.SetSubSZ (g_cbLastDirUsed, pcFileName);	//(LPCSTR)fileordir);
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectParams message handlers

BOOL CSelectConnectParams::OnInitDialog() 
{
	m_pParams = GetPropSheet() -> GetConnectParams();
	m_fNameIsFile = m_pParams -> m_fNameIsFile;
	m_fNameIsDir = m_pParams -> m_fNameIsDir;
	m_fNameIsSubStg = m_pParams -> m_fNameIsSubStorage;
	m_strFileDesc = m_pParams -> m_strFileDesc;
	m_rgDataSrcMode = DATASOURCEMODE_Unknown;

	CPropertyPage::OnInitDialog();

// Strings richten
CString str, strTempl;

	m_ftDescText.GetWindowText (strTempl);
	str.Format (strTempl, m_pParams -> m_strShortName);
	m_ftDescText.SetWindowText (str);

	if (!m_fAsDbmsPage) {
		if (DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode()) 
			str.Format (IDS_SELECTNEWDATASOURCE_PROMPT, m_strFileDesc);		// Neu anlegen
		else {
			m_ftSelectPrompt.GetWindowText (strTempl);
			str.Format (strTempl, m_strFileDesc);
		}
		m_ftSelectPrompt.SetWindowText (str);
	}

// wenn neu erzeugen und TempName erlaubt, dann diesen setzen
	if (DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode() &&
		!m_pParams -> m_strTempName.IsEmpty())
	{
		m_strFileName = m_pParams -> m_strTempName;
		m_fIsTempName = TRUE;
	}

	AdjustButtons();
	UpdateData (FALSE);

	return FALSE;  // return TRUE unless you set the focus to a control
}

LRESULT CSelectConnectParams::OnWizardBack() 
{
	ASSERT(NULL != m_pParams);
	if (!m_fAsDbmsPage) {
		if (m_fNameIsFile) 
			m_sleGetFileName.Reset();
		else
			m_sleGetFolder.Reset();
	}

	CPropertyPage::OnWizardBack();
	m_fWasNext = FALSE;

	if (!(TRIASMODE_GDO & g_dwHookFlags) ||		// TRiAS läuft auf GDO
		1 == GetPropSheet()->CountAvailableDataServers())
	{
	// die vorherige Seite (IDD_SELECT_CONNECTION) muß übersprungen werden
		SetWindowLong (m_hWnd, DWL_MSGRESULT, IDD_CONNECTION_OPENNEW);
		return IDD_CONNECTION_OPENNEW;
	} 

	SetWindowLong (m_hWnd, DWL_MSGRESULT, IDD_SELECT_CONNECTION);
	return IDD_SELECT_CONNECTION;
}

// Eingaben auswerten und speichern
void CSelectConnectParams::PrepareResults(bool fPrepareAfterClose)
{
	ASSERT(NULL != m_pParams);

	if (!fPrepareAfterClose)
		UpdateData (TRUE);		// Daten übernehmen

	if (!m_fAsDbmsPage) {
		if (m_fNameIsFile) 
			m_sleGetFileName.Reset();
		else
			m_sleGetFolder.Reset();

		SaveSelectedDirectory(m_pParams -> m_strProgID, m_strFileName);
	}
	else if (m_fHasExtPages) {
	// ggf. Connectinfo auswerten
		_ASSERTE(m_Pairs.IsValid());

		USES_CONVERSION;
		COM_TRY {
		WParseStringPairs Pairs(m_Pairs);
		WParseStringPairs2 Pairs2(Pairs);
		CComBSTR bstr;

			if (SUCCEEDED(Pairs->get_Value(CComBSTR(L"Location"), CLEARED(&bstr))))
			{
				m_strFileName = OLE2A(bstr);
				m_Files.clear();
				m_Files.insert (os_string(m_strFileName));
				Pairs2->DeletePair(CComBSTR(L"Location"));
			}
			if (SUCCEEDED(Pairs->get_Value(CComBSTR(L"ConnName"), CLEARED(&bstr))))
			{
			BOOL fCorrected = FALSE;

				m_strConnectName = ((CFakeMFCExtension *)g_pTE) -> EnsureUniqueConnectionName (
								this, OLE2A(bstr), m_strFileName, &fCorrected);

				Pairs2->DeletePair(CComBSTR(L"ConnName"));
			}
			if (SUCCEEDED(Pairs->get_Value(CComBSTR(L"ConnDesc"), CLEARED(&bstr))))
			{
				m_strConnectDesc = OLE2A(bstr);
				Pairs2->DeletePair(CComBSTR(L"ConnDesc"));
			}

			if (SUCCEEDED(Pairs->get_Value(CComBSTR(L"Server"), CLEARED(&bstr))))
			{
			CString strServer (OLE2A(bstr));

				SaveSelectedDirectory(m_pParams -> m_strProgID, strServer);
			}

		} COM_CATCH_NORETURN;
	}

	if (m_fHasCoordSystem) {
	CComBSTR bstrSelectCS;

		if (m_pParams->GetNeedsCoordSysExisting()) {
		WTRiASAccessDatabase DB;
		
			if (SUCCEEDED(DB.CreateInstance(m_pParams->m_ClsId))) {
				USES_CONVERSION;
				if (SUCCEEDED(DB -> get_AttachedCS(A2OLE(m_strFileName), &bstrSelectCS)))
					m_pCoordSysWiz -> SetPairs(m_Pairs, bstrSelectCS);
			}
		}

		if (!bstrSelectCS || 0 == bstrSelectCS.Length()) {
			bstrSelectCS = m_pParams -> m_strTcfName;
			m_pCoordSysWiz -> SetPairs(m_Pairs, bstrSelectCS);
		}
	}
}

LRESULT CSelectConnectParams::OnWizardNext() 
{
//	ASSERT(DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode());
	PrepareResults();
	m_fWasNext = TRUE;
	return CPropertyPage::OnWizardNext();
}

BOOL CSelectConnectParams::OnWizardFinish() 
{
	PrepareResults();
	m_fWasNext = TRUE;
	return CPropertyPage::OnWizardFinish();
}

void CSelectConnectParams::OnChangeConnectionName() 
{
	AdjustButtons();
}

void CSelectConnectParams::OnKillfocusConnectionName() 
{
	if (DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode()) 
		return;		// nothing to do, name should be unique

BOOL fCorrected = FALSE;
CString strName;

	strName = ((CFakeMFCExtension *)g_pTE) -> EnsureUniqueConnectionName (
					this, m_strConnectName, m_strFileName, &fCorrected);

// Fokus evtl. wieder aufs Editcontrol setzen
	if (fCorrected) {
		m_strConnectName = strName;
		UpdateData (FALSE);
		AdjustButtons (true);
		PostMessage (WM_SETFOCUSTOCONNECTIONNAME);
	}
}

// WM_SETFOCUSTOCONNECTIONNAME
LRESULT CSelectConnectParams::OnSetFocusToConnectionName (WPARAM wParam, LPARAM lParam)
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_CONNECTION_NAME);

	pEdit -> SetFocus ();
	pEdit -> SetSel (0, -1);
	return TRUE;
}

// WM_SWITCHTONEXTPAGE
LRESULT CSelectConnectParams::OnSwitchToNextPage (WPARAM wParam, LPARAM lParam)
{
	m_fWasNext = !wParam;
	GetPropSheet()->PressButton(wParam ? PSBTN_BACK : PSBTN_NEXT);
	return TRUE;
}

LRESULT CSelectConnectParams::OnFileOrDirSelected (WPARAM, LPARAM)
{
	if (m_fAsDbmsPage)
		return TRUE;		// nothing to do

	UpdateData (TRUE);		// Daten übernehmen

os_path fileordir = os_string(m_strFileName);
os_string basepart (fileordir.base());

	if (basepart.size() > 0) {
		m_strConnectName = basepart.c_str();
		m_strConnectDesc.Format (IDS_CONNECTDESCRIPTION, basepart.c_str(), m_pParams -> m_strFileDesc);
	} 
	else {
		basepart = fileordir[fileordir.levels()-1];
		m_strConnectName = basepart.c_str();
		m_strConnectDesc.Format (IDS_CONNECTDESCRIPTION, basepart.c_str(), m_pParams -> m_strFileDesc);
	}

BOOL fCorrected = FALSE;
CString strName;

	strName = ((CFakeMFCExtension *)g_pTE) -> EnsureUniqueConnectionName (
					this, m_strConnectName, m_strFileName, &fCorrected);

// ggf. korrigierten Wert ins Feld schreiben
	if (fCorrected) 
		m_strConnectName = strName;

	UpdateData (FALSE);		// Daten zurückschreiben

// Focus auf neuen Text setzen und vollständig markieren
CEdit *pEdit = (CEdit *)GetDlgItem(IDC_CONNECTION_NAME);

	ASSERT_VALID(pEdit);
	pEdit -> SetFocus();
	pEdit -> SetSel(0, -1);

	m_fIsTempName = FALSE;

	if (m_fNameIsFile && m_pParams -> m_fIsReadWrite) 
		m_pParams -> m_fIsReadWrite = !m_sleGetFileName.GetReadOnly();
	AdjustButtons();
	return TRUE;
}

BOOL CSelectConnectParams::OnSetActive() 
{
	if (m_fNameIsFile != m_pParams -> m_fNameIsFile ||
		m_fNameIsDir != m_pParams -> m_fNameIsDir ||
		m_fNameIsSubStg != m_pParams -> m_fNameIsSubStorage ||
		m_strFileDesc != m_pParams -> m_strFileDesc ||
		m_strProgID != m_pParams -> m_strProgID || 
		m_rgDataSrcMode != GetPropSheet() -> GetDatasourceMode())
	{
	// Parameter wurden geändert, neu initialisieren
		m_fNameIsFile = m_pParams -> m_fNameIsFile;
		m_fNameIsDir = m_pParams -> m_fNameIsDir;
		m_fNameIsSubStg = m_pParams -> m_fNameIsSubStorage;
		m_strFileDesc = m_pParams -> m_strFileDesc;
		m_rgDataSrcMode = GetPropSheet() -> GetDatasourceMode();
		m_strProgID = m_pParams -> m_strProgID;

	// Strings richten
	CString str;

		if (!m_fAsDbmsPage) {
			str.Format (IDS_GDODESCTEXT, m_pParams -> m_strShortName);
			m_ftSelectPrompt.SetWindowText (str);

			str.Format (IDS_GDOSELECTPROMPT, m_strFileDesc);
			m_ftDescText.SetWindowText (str);

			m_strConnectDesc = g_cbNil;
			m_strConnectName = g_cbNil;

			m_strFileName = g_cbNil;
		} 
		else {
			str.Format (IDS_GDOSELECTPROMPT_DBMS, m_strFileDesc);
			m_ftDescText.SetWindowText (str);

		int iCnt = DEX_GetOpenConnectionCount(QDCAllOpen);

			if (iCnt == 0) {
				m_strConnectName = m_pParams -> m_strShortName;
				m_strConnectDesc.Format (IDS_CONNECTDESCRIPTION, m_pParams -> m_strShortName, m_pParams -> m_strFileDesc);
			} else {
				m_strConnectName.Format (IDS_CONNECTNAME_DBMS, m_pParams -> m_strShortName, iCnt);
				m_strConnectDesc.Format (IDS_CONNECTDESCRIPTION_DBMS, m_pParams -> m_strShortName, iCnt, m_pParams -> m_strFileDesc);
			}

		CString str;

			str.LoadString (IDS_FILENAMETEMPLATE_DBMS);
			m_Files.insert (os_string(str));
		}

		m_fIsTempName = FALSE;

		UpdateData (FALSE);

	// evtl. zusätzliche DialogSeiten laden
		m_fHasExtPages = LoadExtPages (m_pParams -> m_strExtProgID);
//		ASSERT(!m_fAsDbmsPage || m_fHasExtPages || m_pParams -> m_fNameIsSubStorage);	// irgend jemand _muß_ mind. eine eigene Seite haben
	}

// DBMS Seite nur anzeigen, wenn keine zusätzlichen Dialoge registriert sind
	if (m_fAsDbmsPage) {
		if (m_fHasExtPages) {
		// zuerst sicherstellen, daß alle Controls ausgeblendet sind (flackert weniger)
			GetDlgItem(IDC_DESCTEXT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CONNECTION_NAME_PROMPT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CONNECTION_NAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CONNECT_DESCRIPTION_PROMPT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CONNECT_DESCRIPTION)->ShowWindow(SW_HIDE);

		// jetzt zur nächsten bzw. vorhergehenden Seite schalten
			PostMessage (WM_SWITCHTONEXTPAGE, m_fWasNext);
			m_fWasNext = !m_fWasNext;
		}
		else {
		// sicherstellen, daß alle Controls wieder eingeblendet sind
			GetDlgItem(IDC_DESCTEXT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CONNECTION_NAME_PROMPT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CONNECTION_NAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CONNECT_DESCRIPTION_PROMPT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CONNECT_DESCRIPTION)->ShowWindow(SW_SHOW);
		}
	}

	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

HRESULT CSelectConnectParams::ResetExtPages()
{
// evtl. alte Pages freigeben
COpenNewPropertySheet *pSheet = GetPropSheet();

	if (m_fHasCoordSystem) {
		_ASSERTE(NULL != m_pCoordSysWiz);
		m_pCoordSysWiz -> SetPairs(NULL, NULL);
//		pSheet->RemovePage(m_pCoordSysWiz);		// macht bereits dtor s.n.Zeile
		DELETE_OBJ(m_pCoordSysWiz);
		m_fHasCoordSystem = FALSE;
	}

int iToDelete = pSheet -> GetPageCount() - pSheet -> GetPageIndex (this) - 1;

	while (iToDelete > 0) {
		pSheet -> SendMessage (PSM_REMOVEPAGE, pSheet -> GetPageCount() -1);
		iToDelete--;
	}

// evtl. altes Objekt freigeben
	pSheet -> m_ExtPages.Assign(NULL);
	pSheet -> m_Pairs.Assign(NULL);
	m_Pairs.Assign(NULL);
	return S_OK;
}

BOOL CSelectConnectParams::LoadExtPages (CString strProgID)
{
BOOL fHasPages = FALSE;

	USES_CONVERSION;
	try {
		ResetExtPages();

	WComposeStringPairs Pairs (CLSID_ParseStringPairs);
	COpenNewPropertySheet *pSheet = GetPropSheet();

	// wenn CoordSystem ausgwählt werden soll
		m_fHasCoordSystem = FALSE;
		DELETE_OBJ(m_pCoordSysWiz);
		if (pSheet->GetConnectParams()->GetNeedsCoordSys(pSheet->GetDatasourceMode())) 
		{
			ATLTRY(m_pCoordSysWiz = new CCreateNewWiz(FALSE, m_uiCaption));
			if (NULL != m_pCoordSysWiz) {
				pSheet->AddPage(m_pCoordSysWiz);
				m_fHasCoordSystem = TRUE;
				fHasPages = TRUE;
				m_pCoordSysWiz -> SetIsLast(true);
			}
		}

	// wenn kein Objekt für diesen DataServer existiert, dann weiter
		if (!strProgID.IsEmpty()) {
		// neues Objekt erzeugen
		CIID ClsId (strProgID, CIID::INITCIID_InitFromProgId);

			if (!ClsId) return FALSE;

		// Objekt für zusätzliche Pages erzeugen und initialisieren
		WTRiASOpenWizardPropExt ExtPages (ClsId);	// throws hr
		VARIANT_BOOL fCreate = (DATASOURCEMODE_CreateNew == pSheet -> GetDatasourceMode()) ? VARIANT_TRUE : VARIANT_FALSE;

			if (SUCCEEDED(ExtPages -> InitForOpenDialog (
				A2OLE(m_pParams -> m_strProgID), A2OLE(m_strCaption), fCreate, Pairs)))
			{
			// Pages einhängen
			WTriasPropSheetExt SheetExt (ExtPages);

				THROW_FAILED_HRESULT(SheetExt -> AddPages (AddPropSheetPageProc, reinterpret_cast<LPARAM>(pSheet)));
				fHasPages = TRUE;
				if (NULL != m_pCoordSysWiz)
					m_pCoordSysWiz -> SetIsLast(false);		// CoordSys ist doch nicht letztes Fenster
			}

			if (fHasPages) 
				pSheet -> m_ExtPages = ExtPages;
		}

		if (fHasPages) {
			pSheet -> m_Pairs = Pairs;
			m_Pairs = Pairs;
		}

	} catch (_com_error &) {
		ResetExtPages();
		return FALSE;
	}
	return fHasPages;	// mindestens ein Objekt erfolgreich geladen
}

BOOL CSelectConnectParams::AddPropSheetPageProc (HPROPSHEETPAGE hPSP, LPARAM lParam)
{
	return reinterpret_cast<COpenNewPropertySheet *>(lParam) -> SendMessage(PSM_ADDPAGE, 0, (LPARAM)hPSP);
}



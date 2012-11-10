// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module ManageConnections.cpp | Implementation of the <c CManageConnections> class

#include "fakemfcp.hxx"

#include "fakemfc.h"
#include "Strings.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>
#include <ScopeVar.h>

#include "Wrapper.h"		// SmartInterfaces

#include "fakemfc.hxx"
#include "MainFrm.h"
#include "ManageConnections.h"
#include "AttachNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SHOWINPLACEEDIT	(WM_USER+1234)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C2-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASProject = 
	{0x422fb8c2,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};
// {422FB8C0-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASConnection = 
	{0x422fb8c0,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};


DefineSmartInterface(TRiASMainDBEngine);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASProjects);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASDatabase);

DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(Dispatch);
DefineSmartInterface(PersistStream);

DefineEnumerator2(WTRiASProject, IID_IEnumTRiASProject);
DefineSmartEnumerator2(WTRiASProject, IID_IEnumTRiASProject);		// WEnumWTRiASProject

DefineEnumerator2(WTRiASConnection, IID_IEnumTRiASConnection);
DefineSmartEnumerator2(WTRiASConnection, IID_IEnumTRiASConnection);	// WEnumWTRiASConnection

///////////////////////////////////////////////////////////////////////////////
// 
#define SHORT_COLUMN			0
#define TYP_COLUMN				1
#define STATUS_COLUMN			2
#define CONNECTFILTER_COLUMN	3
#define LONG_COLUMN				4
#define PATH_COLUMN				5

#define CONNECTION_UNKNOWNSTATUS	(-1)
#define CONNECTION_CLOSED			0
#define CONNECTION_READONLY			1
#define CONNECTION_WRITEABLE		2

///////////////////////////////////////////////////////////////////////////////
// dafür sorgen daß räumliche Filter erst ab V6.0 verfügbar sind
#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
inline 
int CorrectColNum(int iCol)
{
	_ASSERTE(iCol > CONNECTFILTER_COLUMN);
	return /*(g_dwVer51 != 0) ? iCol : */iCol - 1;
}
#else
#define CorrectColNum(i)	(i)
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// 
namespace {
// stellt sicher, daß die derzeit aktive Ansicht wieder neu eingestellt wird
	class CReInitView 
	{
	public:
		CReInitView() 
		{
		char cbBuffer[_MAX_PATH];

			cbBuffer[0] = '\0';
			if (DEX_GetActiveSight(cbBuffer))
				m_strView = cbBuffer;
			m_fPreventRePaint = DEX_IsPreventRepaintActive();
			DEX_SetPreventRepaint(TRUE);
		}
		~CReInitView()
		{
			DEX_SetPreventRepaint(m_fPreventRePaint);
			if (m_strView.size() > 0) {
				DEX_SelectNewSight(m_strView.c_str());
				DEX_RePaint();
			}
		}
		
	private:
		os_string m_strView;
		BOOL m_fPreventRePaint;
	};

// alle Buttons passivieren
	class CDisableButtons
	{
	public:
		CDisableButtons (CManageConnections *pDlg) : m_pDlg(pDlg)
		{
			m_pDlg -> m_pbActions.EnableWindow(FALSE);
			m_pDlg -> m_pbCancel.EnableWindow(FALSE);
			m_pDlg -> m_pbOK.EnableWindow(FALSE);
		}
		~CDisableButtons ()
		{
			m_pDlg -> m_pbActions.EnableWindow(TRUE);
			m_pDlg -> m_pbCancel.EnableWindow(TRUE);
			m_pDlg -> m_pbOK.EnableWindow(TRUE);
		}

	private:
		CManageConnections *m_pDlg;
	};
}

///////////////////////////////////////////////////////////////////////////////
// 
void CMainFrame::OnManageConnections (void)
{
CManageConnections Dlg (this);
CScopeVar<CManageConnections *> Scope1 (m_pManageConnections, &Dlg);
CScopeVar<CManageConnections *> Scope2 (((CFakeMFCExtension *)g_pTE)->m_pManageConnections, &Dlg);

	Dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CManageConnections dialog

CManageConnections::CManageConnections(CWnd* pParent /*=NULL*/)
	: CDialog(CManageConnections::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageConnections)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_fIsValid = FALSE;
	m_uiDefault = (UINT)-1;
	m_pPopup = NULL;
}


void CManageConnections::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_FUNCTIONMENU, m_FunctionMenu);
	//{{AFX_DATA_MAP(CManageConnections)
	DDX_Control(pDX, IDOK, m_pbOK);
	DDX_Control(pDX, IDCANCEL, m_pbCancel);
	DDX_Control(pDX, IDC_CONNECTIONS, m_lvConnections);
	//}}AFX_DATA_MAP
}

static UINT WM_PREPAREPOPUPMENU = RegisterWindowMessage(PrepareMenuString);
static UINT WM_DESTROYPOPUPMENU = RegisterWindowMessage(DestroyMenuString);
static UINT WM_MENUBUTTONPUSHED = RegisterWindowMessage(MenuButtonPushed);

BEGIN_MESSAGE_MAP(CManageConnections, CDialog)
	//{{AFX_MSG_MAP(CManageConnections)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CONNECTIONS, OnItemChangedConnections)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_CONNECTIONS, OnEndLabelEditConnections)
	ON_REGISTERED_MESSAGE(WM_PREPAREPOPUPMENU, OnPreparePopupMenu)
	ON_REGISTERED_MESSAGE(WM_DESTROYPOPUPMENU, OnDestroyPopupMenu)
	ON_BN_CLICKED(IDC_ACTIONS, OnActions)
	ON_WM_DELETEITEM()
	ON_NOTIFY(NM_RCLICK, IDC_CONNECTIONS, OnRclickConnections)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWINPLACEEDIT, OnShowInPlaceEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageConnections message handlers

BOOL CManageConnections::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();

// Actions-Button einbinden
	m_pbActions.SubclassDlgItem(IDC_ACTIONS, this);

// Liste initialiseren
	if (!m_lvConnections.InitListCrtl()) {
		TRACE("Couldn't initialize list control in CManageConnections\r\n");
		return FALSE;
	}

// Liste füllen
	if (!InitConnectionList (0))
		return FALSE;

	m_fIsValid = TRUE;
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CManageConnections::InitConnectionList (int iItem)
{
// Liste füllen
	if (!FillListWithActualConnections()) {
		TRACE("Couldn't fill list control in CManageConnections\r\n");
		return FALSE;
	}

// Spaltenbreite richten
	if (-1 == iItem)
		iItem = m_lvConnections.GetItemCount()-1;

	m_lvConnections.SelectItem(iItem, TRUE);
	m_lvConnections.FitColumn();	// Fit all Columns
	m_lvConnections.SetFocus();

	AdjustButtons(iItem);
	return TRUE;
}

BOOL CManageConnections::IsConnectionDeleted (ITRiASConnection *pIConn)
{
	CConnectionList::iterator end = m_Deleted.end();
	for (CConnectionList::iterator it = m_Deleted.begin(); it != end; ++it) {
		if ((*it) == WTRiASConnection(pIConn))
			return TRUE;
	}
	return FALSE;		// nicht in der Liste der gelöschten Datenquellen
}

BOOL CManageConnections::IsConnectionDeleted (BSTR bstrName)
{
	CConnectionList::iterator end = m_Deleted.end();
	for (CConnectionList::iterator it = m_Deleted.begin(); it != end; ++it) {
	CComBSTR bstr;

		if (SUCCEEDED((*it) -> get_Name(&bstr)) && bstr == bstrName)
			return TRUE;
	}
	return FALSE;		// nicht in der Liste der gelöschten Datenquellen
}

BOOL CManageConnections::FillListWithActualConnections()
{
char cbBuffer[_MAX_PATH];
CManageDataServerItem *pNewItem = NULL;

	VERIFY(NULL != DEX_GetActiveProject(cbBuffer));

	USES_CONVERSION;
	try {
	WTRiASMainDBEngine Main;
	WTRiASProjects Prjs;

		THROW_FAILED_HRESULT(((CFakeMFCExtension *)g_pTE) -> GetMainDBEngine (Main.ppi()));
		THROW_FAILED_HRESULT(Main -> get_Projects (Prjs.ppi()));

	// aktuelles Projekt wiederfinden
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(Prjs -> Item(CComVariant(cbBuffer), Prj.ppi()));

	// alle Connections des Projektes durchgehen
	WTRiASConnections Conns;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	
		THROW_FAILED_HRESULT(Conns -> _NewEnum (Enum.ppu()));
		m_lvConnections.DeleteAllItems();		// erstmal alles rauslöschen

		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) 
		{
			THROW_FAILED_HRESULT(v.ChangeType(VT_UNKNOWN));

		// statische Infos über TRiASDB-TargetDatenbank besorgen
		WTRiASConnection Conn (V_UNKNOWN(&v));

		// Testen, ob diese Datenquelle vielleicht gerade gelöscht werden sollte
			if (IsConnectionDeleted (Conn)) 
				continue;

		// Item erzeugn, welches an dem Listeintrag dranhängt
			ATLTRY(pNewItem = new CManageDataServerItem);
			if (NULL == pNewItem) _com_issue_error(E_OUTOFMEMORY);

			THROW_FAILED_HRESULT(LoadConnectParams (Conn, pNewItem));
			
		// dynamische Informationen hinzufügen
		CComBSTR bstrPath;

			THROW_FAILED_HRESULT(Conn -> get_Location(CLEARED(&bstrPath)));
			pNewItem -> SetPath (OLE2A(bstrPath));

		CComBSTR bstrDesc;

			THROW_FAILED_HRESULT(Conn -> get_Name(CLEARED(&bstrDesc)));
			pNewItem -> SetDesc (OLE2A(bstrDesc));

		CComBSTR bstrConnDesc;

			THROW_FAILED_HRESULT(Conn -> get_Description(CLEARED(&bstrConnDesc)));
			pNewItem -> SetConnDesc (OLE2A(bstrConnDesc));

		CONNECTSTATUS rgOpened = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgOpened));
			pNewItem -> SetIsOpened ((CONNECTSTATUS_Opened == rgOpened) ? TRUE : FALSE);

			if (CONNECTSTATUS_Opened == rgOpened) {
			CONNECTMODE rgRW = CONNECTMODE_OpenReadOnly;

				THROW_FAILED_HRESULT(Conn -> get_Mode (&rgRW));
				pNewItem -> SetConnIsReadWrite ((CONNECTMODE_OpenReadWrite & rgRW) ? TRUE : FALSE);
				pNewItem -> SetSourceIsReadWrite ((CONNECTMODE_IsReadOnly & rgRW) ? FALSE : TRUE);
			}

		// Connection merken
			pNewItem -> SetConnection (Conn);

		// jetzt zum Control hinzufügen
			THROW_FAILED_HRESULT(m_lvConnections.AddItemToTree (pNewItem));
			pNewItem = NULL;
		}

	} catch (_com_error &e) {
		DELETE_OBJ(pNewItem);

		VMessageBox (this, FakeTRiASName(IDS_BADREGISTRATION_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONSTOP, IDS_BADREGISTRATION, g_cbTRiAS);
		return SUCCEEDED(_COM_ERROR(e));
	}
	return TRUE;
}

HRESULT CManageConnections::LoadConnectParams (ITRiASConnection *pIConn, CManageDataServerItem *pItem)
{
WTRiASDatabase DBase;

	if (SUCCEEDED(pIConn -> get_Database (DBase.ppi()))) {
		USES_CONVERSION;

	CComBSTR bstrProgID;		// ProgID des TRiAS-DataBase-TargetObjektes
	
		RETURN_FAILED_HRESULT(DBase -> get_Type (CLEARED(&bstrProgID)));

	// jetzt alle zugehörigen Infos aus registry lesen
	DWORD dwPos = IMG_GENERAL;

		RETURN_FAILED_HRESULT(TxGetExtension() -> ReadDataServerParams (dwPos, pItem, OLE2A(bstrProgID)));
		pItem -> SetPosBmp (dwPos);
		pItem -> AddDirty (DIRTYFLAG_ConnectParamsInitialized);
		return S_OK;
	}
	return S_FALSE;
}

class CDeleteConnection
{
private:
	CWnd *m_pWnd;
	CONNECTMODE m_rgMode;
	bool &m_rfFirst;

public:
	CDeleteConnection (CWnd *pWnd, bool &rfFirst, CONNECTMODE rgMode = CONNECTMODE_CloseUserResolves) : 
		m_pWnd(pWnd), m_rfFirst(rfFirst), m_rgMode(rgMode) 
	{
	}

	void operator() (WTRiASConnection Conn)
	{
		if (!Conn) return;	// nichts machen, wenn keine Connection gegeben ist

	CComBSTR bstr (g_cbUnknownName);
	CComBSTR bstrDesc (g_cbUnknownName);

		Conn -> get_Name (CLEARED(&bstr));
		Conn -> get_Description (CLEARED(&bstrDesc));
		try {
		// erst sicher schließen
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Opened;
		HRESULT hr = S_OK;		// geschlossene Datenquellen einfach entfernen

			Conn -> get_Status (&rgStatus);
			if (CONNECTSTATUS_Opened == rgStatus)
			{
				if (m_rfFirst) {
				CONNECTMODE rgMode = m_rgMode;

					Conn -> get_Mode(&rgMode);
					rgMode = CONNECTMODE((rgMode & ~CONNECTMODE_CloseResolutionFlags)|m_rgMode|CONNECTMODE_ResetDisconnectAskMode);
					hr = Conn -> Disconnect(rgMode);
					m_rfFirst = false;
				}
				else {
					hr = Conn -> Disconnect(m_rgMode);
				}
			}

		// Fehlerauswertung
			if (FAILED(hr))	{
				THROW_FAILED_HRESULT(hr);
			} else if (S_FALSE == hr)
				return;		// skip this datasource

		// wenn storagebasierte Datenquelle entfernt werden soll, dann vorher
		// warnen
		CONNECTPARAM rgParam = CONNECTPARAM_Unknown;

			THROW_FAILED_HRESULT(Conn -> get_Param (&rgParam));
			if (CONNECTPARAM_Storage == rgParam) {
			int iResult = VMessageBox (m_pWnd, FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
							MB_YESNOCANCEL|MB_ICONQUESTION, IDS_EMBEDDED_DATASOURCE, bstr.m_str);

				switch (iResult) {
				case IDYES:
//					SaveAsFileBasedDataSource (Conn);
					break;		// save as external datasource

				case IDNO:
					break;		// do not save datasource, discard information

				case IDCANCEL:
					return;		// skip this datasource
				}
			}

		// danach aus Projekt entfernen
		WDispatch Parent;

			THROW_FAILED_HRESULT(Conn -> get_Parent (Parent.ppi()));

		WTRiASConnections Conns;

			THROW_FAILED_HRESULT(WTRiASProject(Parent) -> get_Connections (Conns.ppi()));
			THROW_FAILED_HRESULT(Conns -> Remove (CComVariant(bstr.m_str)));

		} catch (_com_error &e) {
			VMessageBox (m_pWnd, FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONSTOP, IDS_DISCONNECTERROR, bstrDesc.m_str, bstr.m_str, _COM_ERROR(e));
		}
	}
};

void CManageConnections::OnOK() 
{
	CDialog::OnOK();

CWaitCursor Wait;
CReInitView View;

	DEX_RemoveAllORWnds();		// alle ORFenster schließen (sicherheitshalber)

// alle entfernten Connections sicher Schließen und rauswerfen
bool fFirstD = true;
bool fFirstC = true;

	for_each (m_Deleted.begin(), m_Deleted.end(), CDeleteConnection(this, fFirstD));

// alle geänderten Parameter abarbeiten
bool fMustReload = false;

	for (int iItem = m_lvConnections.GetNextItem (-1, LVNI_ALL);
		 -1 != iItem;
		 iItem = m_lvConnections.GetNextItem (iItem, LVNI_ALL))
	{
	// alle Einträge durchgehen, und überprüfen, was sich geändert hat
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (iItem));
	DIRTYFLAG rgDirty = pData -> IsDirty();

		if (DIRTYFLAG_NoChange == DIRTYFLAG(rgDirty & DIRTYFLAG_Mask)) 
			continue;

	// versuchen herauszufinden, was sich geändert hat
	WTRiASConnection Conn (pData -> GetConnection());

		if (DIRTYFLAG_NameChanged & rgDirty) {
		CString str = m_lvConnections.GetItemText(iItem, SHORT_COLUMN);
		CComBSTR bstr (str);

			Conn -> put_Name(bstr);
		}

		if (DIRTYFLAG_DescriptionChanged & rgDirty) {
		CString str = m_lvConnections.GetItemText(iItem, CorrectColNum(LONG_COLUMN));
		CComBSTR bstr (str);

			Conn -> put_Description(bstr);
		}

	// Connectfilter has changed
		if (DIRTYFLAG_ConnectionFilterChanged & rgDirty) {
		CString strConnName = m_lvConnections.GetItemText(iItem, SHORT_COLUMN);
		CString str = m_lvConnections.GetItemText(iItem, CONNECTFILTER_COLUMN);
		ATTACHCONNECTIONFILTER ACF;

			INITSTRUCT(ACF, ATTACHCONNECTIONFILTER);
			ACF.pcConnName = strConnName;
			if (str.GetLength() > 0) {
			GETATTACHEDCONNECTIONFILTER GACF;

				INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
				GACF.pcConnName = strConnName;
				if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF)))
					DEX_DetachConnectionFilter(ACF);

				ACF.pcName = str;
				DEX_AttachConnectionFilter(ACF);
			}
			else {
				DEX_DetachConnectionFilter(ACF);
			}

			fMustReload = true;
		}

	// Status has changed 
	CString str = m_lvConnections.GetItemText(iItem, STATUS_COLUMN);
	int iIndex = m_lvConnections.DecodeStatus (str, pData -> IsDriverReadWrite() && pData -> IsSourceReadWrite());

		if (DIRTYFLAG_StatusChanged & rgDirty) {
			if (CONNECTION_CLOSED == iIndex) {
			// speichern ???
			// ...
				if (fFirstD) {
				CONNECTMODE rgMode = CONNECTMODE(0);

					Conn -> get_Mode(&rgMode);
					rgMode = CONNECTMODE((rgMode & ~CONNECTMODE_CloseResolutionFlags)|CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetDisconnectAskMode);
					THROW_FAILED_HRESULT(Conn -> Disconnect(rgMode));
					fFirstD = false;
				}
				else {
					THROW_FAILED_HRESULT(Conn -> Disconnect(CONNECTMODE_CloseUserResolves));
				}
			} 
			else {
				if (CONNECTION_READONLY == iIndex) {
				CONNECTMODE rgMode = CONNECTMODE_OpenReadOnly;

					if (SUCCEEDED(Conn -> get_Mode (&rgMode))) {	// R/O öffnen
						rgMode = CONNECTMODE(rgMode & ~CONNECTMODE_OpenReadWrite);
						Conn -> put_Mode (rgMode);
					}
					Conn -> Connect (fFirstC ? 
						CONNECTMODE(CONNECTMODE_ResetConnectAskMode|CONNECTMODE_OpenReadOnly) : 
						CONNECTMODE_OpenReadOnly);
				} 
				else {
					Conn -> Connect (fFirstC ? 
						CONNECTMODE(CONNECTMODE_ResetConnectAskMode|CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves) : 
						CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves));
				}
				fFirstC = false;
			}
		}
		else if (DIRTYFLAG_ModeChanged & rgDirty) {
		CONNECTMODE rgMode = CONNECTMODE_OpenReadOnly;

			if (SUCCEEDED(Conn -> get_Mode (&rgMode))) {
				if (CONNECTION_READONLY == iIndex) 
					rgMode = CONNECTMODE(rgMode & ~CONNECTMODE_OpenReadWrite);
				else
					rgMode = CONNECTMODE(rgMode | (CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves));
				Conn -> put_Mode (rgMode);
			}
		}
	}
	if (fMustReload) {
	// alles neu einlesen
		DEX_RemoveAllORWnds();
		DEXN_ReReadIdents();
		DEXN_ReReadContainer();
		DEXN_ReScale();
	}
}

void CManageConnections::OnCancel() 
{
// alle hinzugefügten Connections sicher Schließen und rauswerfen
CWaitCursor Wait;
bool fFirst = true;

	for_each (m_Added.begin(), m_Added.end(), CDeleteConnection(this, fFirst, CONNECTMODE_CloseNoResolution));
	CDialog::OnCancel();
}

void CManageConnections::OnRemoveConnection(int nItem) 
{
	if (-1 == nItem)
		nItem = m_lvConnections.GetNextItem(-1, LVNI_SELECTED);
	ASSERT(-1 != nItem);

	if (-1 != nItem) {
	// gelöschte Connection fürs OK zwischenspeichern
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

		_ASSERTE(NULL != pData);
		COM_TRY {
		// ggf. Schließen und Nutzer bei Bedarf fragen, ob gespeichert werden soll
		WTRiASConnection Conn (pData -> GetConnection());
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			Conn -> get_Status(&rgStatus);
			if (CONNECTSTATUS_Opened == rgStatus) {		
			HRESULT hr = Conn -> SaveConnectedDatabase(CONNECTMODE_CloseUserResolves);

				if (S_OK != hr) return;		// entweder Fehler oder abgebrochen
			}

//		COM_TRY {
//		WTRiASConnection Conn (pData -> GetConnection());
//		WPersistStream Persist;
//		CONNECTMODE rgRW = CONNECTMODE_OpenReadOnly;
//
//			THROW_FAILED_HRESULT(Conn -> get_Mode (&rgRW));
//			if (pData -> IsOpened() &&								// muß geöffnet sein
//				(CONNECTMODE_OpenReadWrite & rgRW) &&				// nur beschreibbare DQ's speichern
//				SUCCEEDED(Conn -> QueryInterface(Persist.ppi())) && 
//				S_OK == Persist -> IsDirty()) 
//			{
//			CComBSTR bstr;
//
//				Conn -> get_Name (&bstr);
//				
//			int iResult = VMessageBox (this, FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
//							MB_YESNOCANCEL|MB_ICONQUESTION, IDS_SAVEPROMPT, bstr.m_str);
//
//				switch (iResult) {
//				case IDNO:			// entfernen, aber nicht speichern
//					break;
//
//				case IDYES:			// entfernen, aber vorher speichern
//					{
//					WTRiASDatabase DBase;
//
//						THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
//						THROW_FAILED_HRESULT(DBase -> Save());
//					}
//					break;
//
//				case IDCANCEL:
//					return;			// doch nicht entfernen
//				}
//			}

//		CString strClose;
//
//			VERIFY(strClose.LoadString(IDS_CLOSE));
//			m_pbOK.SetWindowText(strClose);
//			m_pbCancel.EnableWindow(FALSE);

		// als zu entfernen vormerken
			m_Deleted.push_back (Conn);
			m_lvConnections.DeleteItem (nItem);

		} COM_CATCH_NORETURN;
	}
	AdjustButtons (nItem);
}

void CManageConnections::OnAddConnection(int nItem) 
{
CReInitView View;
CDisableButtons tmp (this);
HRESULT hr = ((CFakeMFCExtension *)g_pTE) -> ShowAddConnectionCommand(this, TRUE);		// evtl. Fehler nicht anzeigen

	if (S_OK == hr) {
	
		InitConnectionList();
//		if (-1 == nItem)
			nItem = m_lvConnections.GetNextItem(-1, LVNI_SELECTED);
		ASSERT(-1 != nItem);
		if (-1 != nItem) {
		// hinzugefügte Connection fürs Cancel zwischenspeichern
		CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

			ASSERT(NULL != pData);

		WTRiASConnection Conn (pData -> GetConnection());

			ATLTRY(m_Added.push_back (Conn));
		}
		AdjustButtons (nItem);

	} else {
	// irgend etwas ist schiefgegangen

	}
}

void CManageConnections::RefreshAfterDragAndDrop()
{
int nCount = m_lvConnections.GetItemCount();	// Anzahl vorher

	InitConnectionList();		// neu einlesen

// hinzugefügte Connections fürs Cancel zwischenspeichern
	for (int i = nCount; i < m_lvConnections.GetItemCount(); ++i) {
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (i));

		ASSERT(NULL != pData);

	WTRiASConnection Conn (pData -> GetConnection());

		ATLTRY(m_Added.push_back (Conn));
	}
}

void CManageConnections::OnItemChangedConnections(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
int iItem = pNMListView -> iItem;

	ASSERT(0 <= iItem);

	if (pNMListView -> uNewState & LVIS_SELECTED) 
		AdjustButtons (iItem);
	*pResult = 0;
}

void CManageConnections::OnEndLabelEditConnections(NMHDR* pNMHDR, LRESULT* pResult) 
{
// hier LV_DISPINFO und nicht wie normalerweise NM_LISTVIEW, da diese Message
// außschließlich von den InplaceControls verschickt wird. Das ListCtrl selbst
// editiert keine Labels.
LV_DISPINFO* pNMDisp = (LV_DISPINFO*)pNMHDR;
int iItem = pNMDisp -> item.iItem;

	ASSERT(0 <= iItem);

// nachsehen, ob und was sich geändert hat
CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (iItem));

	switch (pNMHDR -> idFrom) {
	case IDC_INPLACECOMBO:		// Mode wurde evtl. geändert
		{
		int iIndex = m_lvConnections.DecodeStatus (CString(pNMDisp -> item.pszText), 
			pData -> IsDriverReadWrite() && pData -> IsSourceReadWrite());

			if (-1 == iIndex)
				break;

			if ((CONNECTION_CLOSED == iIndex && pData -> IsOpened()) ||
				(CONNECTION_CLOSED != iIndex && !pData -> IsOpened()))
			{
				pData -> AddDirty (DIRTYFLAG_StatusChanged);
			}
			else if ((CONNECTION_READONLY == iIndex && pData -> IsConnReadWrite()) ||
					 (CONNECTION_WRITEABLE == iIndex && !pData -> IsConnReadWrite()))
			{
				pData -> SetConnIsReadWrite(pData -> IsConnReadWrite() ? FALSE : TRUE);
				pData -> AddDirty (DIRTYFLAG_ModeChanged);
			} 
			else
				pData -> RemoveDirty (DIRTYFLAG_ModeChanged);
		}
		break;

	case IDC_INPLACECOMBO_FILTER:	// Connectfilter geändert
		{
		CString strNewFilter(pNMDisp -> item.pszText);
		int iIndex = m_lvConnections.DecodeConnectFilter(strNewFilter);

			if (-1 == iIndex)
				break;

			if (0 == iIndex) {
			// neuen Verbindungsfilter definieren
				m_lvConnections.SetConnectFilter(iItem, "");

			CREATECONNECTIONFILTER CCF;
			char cbBuffer[_MAX_PATH];

				cbBuffer[0] = '\0';

				INITSTRUCT(CCF, CREATECONNECTIONFILTER);
				CCF.hWndParent = GetSafeHwnd();
				CCF.iMode = CF_Rectangle_OverlappedContainers;
				CCF.pName = cbBuffer;
				CCF.iLen = sizeof(cbBuffer);
				DEX_ShowCreateConnectionFilterDlg(CCF);

				if (IDOK == CCF.iRetVal) {
					pData -> AddDirty(DIRTYFLAG_ConnectionFilterChanged);
					m_lvConnections.SetConnectFilter(iItem, CCF.pName);
				}
				else {
					m_lvConnections.SetConnectFilter(iItem, "");
				}
			}
			else if (1 == iIndex) {
			// keinen Verbindungsfilter verwenden
			GETATTACHEDCONNECTIONFILTER GACF;

				INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
				GACF.pcConnName = pData -> GetDesc();
				DEX_GetAttachedConnectionFilter(GACF);

			// hatte einen Filter und soll jetzt keinen mehr haben
				if (0 != GACF.iLen) 
					pData -> AddDirty(DIRTYFLAG_ConnectionFilterChanged);

				m_lvConnections.SetConnectFilter(iItem, "");
			}
			else {
			GETATTACHEDCONNECTIONFILTER GACF;
			char cbBuffer[_MAX_PATH+1];

				INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
				GACF.pcConnName = pData -> GetDesc();
				GACF.iLen = sizeof(cbBuffer);
				GACF.pName = cbBuffer;
				DEX_GetAttachedConnectionFilter(GACF);

			// hatte keinen Filter und soll nun einen haben
				if (0 == GACF.iLen || strNewFilter != cbBuffer) 
					pData -> AddDirty(DIRTYFLAG_ConnectionFilterChanged);
			}
		}
		break;

	case IDC_INPLACEEDIT:
		{
			if (CString(pNMDisp -> item.pszText) != pData -> GetConnDesc()) 
				pData -> AddDirty (DIRTYFLAG_DescriptionChanged);
			else
				pData -> RemoveDirty (DIRTYFLAG_DescriptionChanged);
		}
		break;

	case IDC_INPLACEEDIT_SHORT:
		if (NULL != pNMDisp -> item.pszText) {
		BOOL fCorrected = FALSE;
		CString strName, strFileName (m_lvConnections.GetFileName (iItem));

			strName = EnsureUniqueConnectionName (iItem, pNMDisp -> item.pszText, strFileName, &fCorrected);
			if (fCorrected) {
				m_lvConnections.SetShortName (iItem, strName);
				PostMessage (WM_SHOWINPLACEEDIT, iItem, IDC_INPLACEEDIT_SHORT);
			}

			if (CString(pNMDisp -> item.pszText) != pData -> GetDesc())
				pData -> AddDirty (DIRTYFLAG_NameChanged);
			else
				pData -> RemoveDirty (DIRTYFLAG_NameChanged);
		} 
		else {
		// abgebrochen, alten Namen wieder setzen
			m_lvConnections.SetShortName (iItem, pData -> GetDesc());
		}
		break;

	default:
		ASSERT(IDC_INPLACEEDIT != pNMHDR -> idFrom && IDC_INPLACECOMBO == pNMHDR -> idFrom);
		break;
	}
	AdjustButtons(iItem);
	*pResult = 0;
}

LRESULT CManageConnections::OnShowInPlaceEdit (WPARAM wParam, LPARAM lParam)
{
	if (IDC_INPLACEEDIT_SHORT == lParam)
		m_lvConnections.EditSubLabel (wParam, SHORT_COLUMN, IDC_INPLACEEDIT_SHORT);
	else {
		_ASSERTE(IDC_INPLACEEDIT == lParam);
		m_lvConnections.EditSubLabel (wParam, CorrectColNum(LONG_COLUMN), IDC_INPLACEEDIT);
	}
	return TRUE;
}

void CManageConnections::AdjustButtons (int iItem)
{
//	InitCoolButton(true);
}

CString CManageConnections::EnsureUniqueConnectionName (
	int iActItem, LPCSTR pcOrigName, LPCSTR pcFileName, BOOL *pfCorrected)
{
	_ASSERTE(NULL != pcOrigName);
	_ASSERTE(NULL != pfCorrected);

CString strName (pcOrigName);

	*pfCorrected = FALSE;
	while (S_OK == FindConnection (iActItem, strName)) {
	// eine Connection mit diesem Namen gibt es schon
		if (!*pfCorrected) {
		// Meldung nur einmal anzeigen
			VMessageBox (this, FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONSTOP, IDS_CONNECTNAMEISNOTUNIQUE, pcOrigName, pcFileName);
		}

	CAttachNumber AN;

		if (AN.HasNumbering (strName)) 
			strName = AN.CorrectNumbering (strName);
		else 
			strName += " (1)";

		*pfCorrected = TRUE;
	}
	return strName;
}

///////////////////////////////////////////////////////////////////////////////
// Überprüfen, ob eine gegebene Connection bereits existiert
HRESULT CManageConnections::FindConnection (int iActItem, LPCSTR pcToSearch)
{
int iCnt = m_lvConnections.GetItemCount();
CString strToSearch (pcToSearch);

	for (int iIndex = 0; iIndex < iCnt; ++iIndex) {
		if (-1 != iActItem && iActItem == iIndex)
			continue;		// aktuelles Item nicht auswerten

	CString strAct = m_lvConnections.GetItemText (iIndex, SHORT_COLUMN);

		if (strAct == strToSearch)
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// PopupMenu behandeln
LRESULT CManageConnections::OnPreparePopupMenu(WPARAM wParam, LPARAM lParam)
{
CMenu *pMenu = (CMenu *)wParam;

	ASSERT(pMenu -> IsKindOf(RUNTIME_CLASS(CMenu)));

	ASSERT(NULL == m_pPopup);
	ATLTRY(m_pPopup = new CPopUpMenu(this, pMenu));
	if (NULL == m_pPopup) return FALSE;

	return InitPopupMenu (m_pPopup, TRUE);
}

// Menu ist wieder weg
LRESULT CManageConnections::OnDestroyPopupMenu (WPARAM wParam, LPARAM lParam)
{
LRESULT lResult = ExecuteCommand ((UINT)lParam);

	if (NULL != m_pPopup) {
		delete m_pPopup;
		m_pPopup = NULL;
	}
	return lResult;
}

void CManageConnections::InitCoolButton(BOOL fMenuBtn)
{
// Text des DefaultItems des Menus in CoolBtn übernehmen
//	if (fMenuBtn) {
//	CPopUpMenu menu(this, IDR_MANAGE_CONNECTIONS);
//
//		if (InitPopupMenu (&menu)) {
//			m_uiDefault = menu.GetSubMenu() -> GetDefaultItem(0, FALSE);
//			if ((UINT)-1 == m_uiDefault)
//				m_uiDefault = ID_ADD_CONNECTION;
//		}
//		delete m_pPopup;
//		m_pPopup = NULL;
//	}
}

BOOL CManageConnections::InitPopupMenu (CPopUpMenu *pPopup, BOOL fMenuBtn)
{
// rausfinden, welches Item aktiv ist
int nItem = m_lvConnections.GetNextItem(-1, LVNI_SELECTED);
bool fSave = false;		// Speichern
bool fOpened = false;	// Speichern unter, Kopie speichern als
bool fIsRO = true;
bool fDriverIsRO = false;
bool fDSIsRO = false;

	if ((UINT)-1 == m_uiDefault)
		m_uiDefault = ID_ADD_CONNECTION;

	if (-1 != nItem) {
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

		_ASSERTE(NULL != pData);
		fOpened = pData -> IsOpened();	// derzeit (zumindest logisch) geöffnet

		if (fOpened) {
			fIsRO = !pData -> IsConnReadWrite();
			fDriverIsRO = !pData -> IsDriverReadWrite();
			fDSIsRO = !pData -> IsDriverReadWrite() || !pData -> IsSourceReadWrite();

			COM_TRY {
			WTRiASConnection Conn (pData -> GetConnection());
			WPersistStream Persist;
			CONNECTMODE rgRW = CONNECTMODE_OpenReadOnly;
			CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

				THROW_FAILED_HRESULT(Conn -> get_Status(&rgStatus));
				if (CONNECTSTATUS_Opened == rgStatus) {
					THROW_FAILED_HRESULT(Conn -> get_Mode (&rgRW));
					if (CONNECTMODE_OpenReadWrite & rgRW && !(CONNECTMODE_IsReadOnly & rgRW)) {
					// nur beschreibbare DQ's speichern
						if (SUCCEEDED(Conn -> QueryInterface(Persist.ppi())) && S_OK == Persist -> IsDirty()) 
							fSave = true;		// Speichern bringt Sinn
					}
				}

			} COM_CATCH_RETURN(FALSE);
		}
	}

// Menu reinkopieren, da Menu aus Button leer ist
	if (fMenuBtn) {
	CMenu menu;

		VERIFY(menu.LoadMenu(IDR_MANAGE_CONNECTIONS));

	CMenu *pSubMenu = menu.GetSubMenu(fOpened ? 1 : 0);

		_ASSERTE(NULL != pSubMenu);
		for (int iCnt = 0; iCnt < pSubMenu -> GetMenuItemCount(); ++iCnt) {
		UINT uiID = GetMenuItemID (pSubMenu -> GetSafeHmenu(), iCnt);

			if (ID_COPYSAVEAS_CONNECTION == uiID && !(QMSysAdmin & DEX_QueryMode()))
				continue;	// Kopie speichern als nur im AdminMode verfügbar

		char cbBuffer[_MAX_PATH];
		UINT uiState = GetMenuState(pSubMenu -> GetSafeHmenu(), iCnt, MF_BYPOSITION);

			if (MF_SEPARATOR & uiState) {
				InsertMenu(pPopup -> GetSubMenu() -> GetSafeHmenu(), -1, MF_BYPOSITION|MF_SEPARATOR, uiID, NULL);
			} 
			else {
				GetMenuString(pSubMenu -> GetSafeHmenu(), iCnt, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);
				InsertMenu(pPopup -> GetSubMenu() -> GetSafeHmenu(), -1, MF_BYPOSITION|MF_STRING, uiID, cbBuffer);
			}
		}
	}

	if (fOpened) {
		pPopup -> EnableItem(ID_SAVE_CONNECTION, fSave);
		pPopup -> EnableItem(ID_SAVEAS_CONNECTION, !fDriverIsRO);
		pPopup -> EnableItem(ID_COPYSAVEAS_CONNECTION, !fDriverIsRO);
		pPopup -> CheckItem(ID_TOGGLE_MODE, fIsRO);
		pPopup -> EnableItem(ID_TOGGLE_MODE, !fDSIsRO);
	}

// Kopie sepichern als nur im Adminmode verfügbar
	if (!(QMSysAdmin & DEX_QueryMode())) 
		pPopup -> RemoveItem (ID_COPYSAVEAS_CONNECTION, MF_BYCOMMAND);

	pPopup -> GetSubMenu() -> SetDefaultItem(m_uiDefault);
	return TRUE;
}

void CManageConnections::OnActions() 
{
//	if ((UINT)-1 != m_uiDefault) {
//		ExecuteCommand (m_uiDefault);
//		PostMessage(WM_INITCOOLBUTTON, TRUE);
//	}
//	m_pbActions.PostMessage (WM_MENUBUTTONPUSHED);		// Menu anzeigen
}

LRESULT CManageConnections::ExecuteCommand (UINT uiCmd) 
{
	UpdateWindow();

// rausfinden, welches Item aktiv ist
int nItem = m_lvConnections.GetNextItem(-1, LVNI_SELECTED);
CManageDataServerItem *pData = NULL;

	if (-1 != nItem) {
		pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));
		_ASSERTE(NULL != pData);
	}

LRESULT lResult = TRUE;
	
	switch (uiCmd) {
	case ID_EDIT_NAME:
		OnEditName(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_TOGGLE_MODE:
		OnToggleMode(nItem);
		break;

	case ID_EDIT_DESCRIPTION:
		OnEditDescription(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_CLOSE_CONNECTION:
		OnCloseDataSource(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_OPEN_CONNECTION:
		OnOpenDataSource(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_SAVE_CONNECTION:
		OnSaveConnection(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_SAVEAS_CONNECTION:
		OnSaveAsConnection(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_COPYSAVEAS_CONNECTION:
		OnSaveCopyAsConnection(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_ADD_CONNECTION:
		OnAddConnection(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_REMOVE_CONNECTION:
		OnRemoveConnection(nItem);
		m_uiDefault = uiCmd;
		break;

	case ID_CANCELMENU:
	case IDCANCEL:
	case 0:			// do nothing
		lResult = FALSE;
		break;
	}
	return lResult;
}

void CManageConnections::OnEditName(int nItem)
{
	if (-1 != nItem)
		PostMessage (WM_SHOWINPLACEEDIT, nItem, IDC_INPLACEEDIT_SHORT);
}

void CManageConnections::OnEditDescription(int nItem)
{
	if (-1 != nItem)
		PostMessage (WM_SHOWINPLACEEDIT, nItem, IDC_INPLACEEDIT);
}

void CManageConnections::OnOpenDataSource(int nItem)
{
	if (-1 == nItem) 
		return;

CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));
int iIndex = CONNECTION_UNKNOWNSTATUS;

	_ASSERTE(!pData -> IsOpened());
	pData -> SetIsOpened(TRUE);

	if (pData -> IsDriverReadWrite() && pData -> IsSourceReadWrite()) {
		iIndex = CONNECTION_WRITEABLE;
		pData -> SetConnIsReadWrite(TRUE);
	} 
	else {
		iIndex = CONNECTION_READONLY;
		pData -> SetConnIsReadWrite(FALSE);
	}

// Modi richten
	pData -> AddDirty (DIRTYFLAG_StatusChanged);

// ComboBox nachführen
CString strStatus (pData -> GetStatusText());

	m_lvConnections.SetItemText(nItem, STATUS_COLUMN, strStatus);
}

void CManageConnections::OnCloseDataSource(int nItem)
{
	if (-1 == nItem) 
		return;

CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

	_ASSERTE(pData -> IsOpened());

// Modi richten
	pData -> SetIsOpened(FALSE);
	pData -> AddDirty (DIRTYFLAG_StatusChanged);

// ComboBox nachführen
CString strStatus (pData -> GetStatusText());

	m_lvConnections.SetItemText(nItem, STATUS_COLUMN, strStatus);
}

void CManageConnections::OnToggleMode(int nItem)
{
	if (-1 == nItem) 
		return;

CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));
int iIndex = CONNECTION_UNKNOWNSTATUS;

	_ASSERTE(pData -> IsOpened());
	_ASSERTE(pData -> IsDriverReadWrite());

// Modi richten
	pData -> SetConnIsReadWrite(pData -> IsConnReadWrite() ? FALSE : TRUE);
	pData -> AddDirty (DIRTYFLAG_ModeChanged);

// ComboBox nachführen
CString strStatus (pData -> GetStatusText());

	m_lvConnections.SetItemText(nItem, STATUS_COLUMN, strStatus);
}

void CManageConnections::OnSaveConnection(int nItem)
{
	COM_TRY {
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

		_ASSERTE(NULL != pData);
		_ASSERTE(pData -> IsOpened());

	WTRiASConnection Conn (pData -> GetConnection());
	WPersistStream Persist;
	CONNECTMODE rgRW = CONNECTMODE_OpenReadOnly;

		THROW_FAILED_HRESULT(Conn -> get_Mode (&rgRW));
		if ((CONNECTMODE_OpenReadWrite & rgRW) &&				// nur beschreibbare DQ's speichern
			SUCCEEDED(Conn -> QueryInterface(Persist.ppi())) && 
			S_OK == Persist -> IsDirty()) 
		{
		CWaitCursor wait;	// warten, warten, warten ...
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
			THROW_FAILED_HRESULT(DBase -> Save());
		}

	} COM_CATCH_NORETURN;
}

void CManageConnections::OnSaveAsConnection(int nItem)
{
	USES_CONVERSION;
	COM_TRY {
	CReInitView View;
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

		_ASSERTE(NULL != pData);
		_ASSERTE(pData -> IsOpened());

	CWaitCursor wait;	// warten, warten, warten ...
	WTRiASConnection Conn (pData -> GetConnection());
	HRESULT hr = Conn -> SaveAsConnectedDatabase(CONNECTMODE_UseDefaultMode);

		if (FAILED(hr)) {
			if (E_ABORT != hr)
				_com_issue_error(hr);
		}

	// neuen Namen in Dialog anzeigen
	CComBSTR bstrNewName;

		THROW_FAILED_HRESULT(Conn -> get_Location(&bstrNewName));
		m_lvConnections.SetFileName(nItem, OLE2A(bstrNewName));

	} COM_CATCH_NORETURN;
}

void CManageConnections::OnSaveCopyAsConnection(int nItem)
{
	AfxMessageBox(IDS_NOTIMPLEMENTED_YET);
}

///////////////////////////////////////////////////////////////////////////////
// rechte Maus im ListControl
void CManageConnections::OnRclickConnections(NMHDR* pNMHDR, LRESULT* pResult) 
{
NMITEMACTIVATE *pNmData = (NMITEMACTIVATE *)pNMHDR;
int nItem = pNmData -> iItem;

	if (-1 != nItem) {
	// ein Item angeklickt: Popupmenu anzeigen
	CPopUpMenu menu (this, IDR_MANAGE_CONNECTIONS);
	CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(m_lvConnections.GetItemData (nItem));

		_ASSERTE(NULL != pData);
		if (pData -> IsOpened())
			menu.DeletePopup(0);		// 'ClosedMenu' rausnehmen

		if (!InitPopupMenu (&menu))
			return;

		ExecuteCommand(menu.Track(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD));
	}
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CManageDataServerList

CManageDataServerList::CManageDataServerList()
{
	m_lCnt = 0L;		// Zähler der Einträge
}

CManageDataServerList::~CManageDataServerList()
{
}

BEGIN_MESSAGE_MAP(CManageDataServerList, CListCtrlEx)
	//{{AFX_MSG_MAP(CManageDataServerList)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageDataServerList message handlers

void CManageDataServerList::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
CManageDataServerItem *pOldItem = (CManageDataServerItem *)pNMListView -> lParam;

	if (NULL != pOldItem)
		delete pOldItem;
	
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
BOOL CManageDataServerList::InitListCrtl (void)
{

HWND hWnd = GetSafeHwnd();

	ASSERT(NULL != hWnd && ::IsWindow(hWnd));

DWORD dwStyleEx = ListView_GetExtendedListViewStyle(hWnd);

	ModifyStyle (0L, LVS_SHOWSELALWAYS, 0);
	ListView_SetExtendedListViewStyle(hWnd, dwStyleEx | LVS_EX_FULLROWSELECT);

CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_DATASERVER) || !bmpMask.LoadBitmap(IDB_DATASERVERMASK)) {
		TRACE0("Could not load bitmaps for CManageDataServerList\r\n");
		return FALSE;
	} else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 20, 0) ||
			-1 == m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CManageDataServerList\r\n");
			return FALSE;
		} else 
			SetImageList(&m_ilImages, LVSIL_SMALL);
	}

//	if (!m_ilImages.Create (IDB_DATASERVER, 16, 16, RGB(255,0,255))) {
//		TRACE0("Could not create imagelist for CManageDataServerList\r\n");
//		return FALSE;
//	} else 
//		SetImageList(&m_ilImages, LVSIL_SMALL);

// Spalten einfügen
	VERIFY(-1 != InsertColumn (SHORT_COLUMN, IDS_SHORTNAMECOLUMN, LVCFMT_LEFT, -1, SHORT_COLUMN));
	VERIFY(-1 != InsertColumn (TYP_COLUMN, IDS_TYPCOLUMN, LVCFMT_LEFT, -1, TYP_COLUMN));
	VERIFY(-1 != InsertColumn (STATUS_COLUMN, IDS_STATUSCOLUMN, LVCFMT_LEFT, -1, STATUS_COLUMN));
//#if _TRiAS_VER < 0x0510
//	if (g_dwVer51 != 0) 
//#endif // _TRiAS_VER < 0x0510
//	{
//		VERIFY(-1 != InsertColumn (CONNECTFILTER_COLUMN, IDS_CONNECTFILTERCOLUMN, LVCFMT_LEFT, -1, CONNECTFILTER_COLUMN));
//	}
	VERIFY(-1 != InsertColumn (CorrectColNum(LONG_COLUMN), IDS_LONGNAMECOLUMN, LVCFMT_LEFT, -1, CorrectColNum(LONG_COLUMN)));
	VERIFY(-1 != InsertColumn (CorrectColNum(PATH_COLUMN), IDS_PATHCOLUMN, LVCFMT_LEFT, -1, CorrectColNum(PATH_COLUMN)));

	m_lCnt = 0L;		// Zähler der Einträge
	return TRUE;
}

HRESULT CManageDataServerList::AddItemToTree (CManageDataServerItem *pItem)
{
// neues Item erzeugen (erste Spalte ist Bildchen plus KurzBezeichner)
LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lvi.iItem = m_lCnt++;
	lvi.iSubItem = SHORT_COLUMN;
	lvi.pszText = (LPTSTR)(LPCTSTR)pItem -> GetDesc();
	lvi.iImage = pItem -> GetPosBmp();
	lvi.lParam = reinterpret_cast<DWORD>(pItem);
	lvi.stateMask = LVIS_OVERLAYMASK;
	lvi.state = INDEXTOOVERLAYMASK(0);

int iItem = InsertItem (&lvi);

	if (-1 == iItem) return E_OUTOFMEMORY;

// zweite Spalte enthält die LangBeschreibung
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (LPTSTR)(LPCTSTR)pItem -> GetConnDesc();
	lvi.iItem = iItem;
	lvi.iSubItem = CorrectColNum(LONG_COLUMN);
	SetItem (&lvi);

// dritte Spalte enthält den ConnectionTyp (KurzBezeichner)
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (LPTSTR)(LPCTSTR)pItem -> GetName();
	lvi.iItem = iItem;
	lvi.iSubItem = TYP_COLUMN;
	SetItem (&lvi);

// die vierte Spalte enthält ggf. den Verbindungsfilter
//#if _TRiAS_VER < 0x0510
//	if (g_dwVer51 != 0) 
//#endif // _TRiAS_VER < 0x0510
//	{
//	GETATTACHEDCONNECTIONFILTER GACF;
//	char cbBuffer[_MAX_PATH+1];
//
//		INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
//		GACF.iLen = sizeof(cbBuffer);
//		GACF.pName = cbBuffer;
//		GACF.pcConnName = pItem -> GetDesc();
//		if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF))) {
//			memset (&lvi, 0, sizeof(LV_ITEM));
//			lvi.mask = LVIF_TEXT;
//			lvi.pszText = cbBuffer;
//			lvi.iItem = iItem;
//			lvi.iSubItem = CONNECTFILTER_COLUMN;
//			SetItem (&lvi);
//		}
//	}

// fünfte Spalte enthält den Status
CString Status (pItem -> GetStatusText());

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (LPTSTR)(LPCTSTR)Status;
	lvi.iItem = iItem;
	lvi.iSubItem = STATUS_COLUMN;
	SetItem (&lvi);

// sechte Spalte enthält den Dateipfad
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (LPTSTR)(LPCTSTR)pItem -> GetPath();
	lvi.iItem = iItem;
	lvi.iSubItem = CorrectColNum(PATH_COLUMN);
	SetItem (&lvi);

	return S_OK;
}

BOOL CManageDataServerList::SetShortName (int iIndex, LPCSTR pcName)
{
	return SetItemText (iIndex, SHORT_COLUMN, pcName);
}

CString CManageDataServerList::GetFileName (int iIndex)
{
	return GetItemText (iIndex, CorrectColNum(PATH_COLUMN));
}

BOOL CManageDataServerList::SetFileName (int iIndex, LPCSTR pcName)
{
	return SetItemText (iIndex, CorrectColNum(PATH_COLUMN), pcName);
}

BOOL CManageDataServerList::SetConnectFilter (int iIndex, LPCSTR pcName)
{
	return SetItemText (iIndex, CONNECTFILTER_COLUMN, pcName);
}

BOOL CManageDataServerList::FillStringList (CStringList &rLst, CString &rStr, BOOL fIsReadWrite)
{
CString str;
int iIndex = CONNECTION_UNKNOWNSTATUS;

	TRY {
		if (!str.LoadString(IDS_CLOSED))
			return CONNECTION_UNKNOWNSTATUS;
		rLst.AddTail (str);
		if (str == rStr)
			iIndex = CONNECTION_CLOSED;

		if (!str.LoadString(IDS_READONLY))
			return CONNECTION_UNKNOWNSTATUS;
		rLst.AddTail (str);
		if (str == rStr)
			iIndex = CONNECTION_READONLY;

		if (fIsReadWrite) {
			if (!str.LoadString(IDS_READWRITE))
				return CONNECTION_UNKNOWNSTATUS;
			rLst.AddTail (str);
			if (str == rStr)
				iIndex = CONNECTION_WRITEABLE;
		} 
		else if (str == rStr)
			iIndex = CONNECTION_READONLY;

	} CATCH (CMemoryException, e) {
		rLst.RemoveAll();
		return CONNECTION_UNKNOWNSTATUS;
	} END_CATCH;
	return iIndex;
}

namespace {
	struct ENUMFILTERDATA {
		ENUMFILTERDATA(CStringList &rLst_, CString &rStr_) :
			rLst(rLst_), rStr(rStr_), iIndex (CB_ERR) {}

		CStringList &rLst;
		CString &rStr;
		int iIndex;
	};

	BOOL CALLBACK EnumConnectionFilters(char *pName, BOOL, void *pData)
	{
		TRY {
		ENUMFILTERDATA *pEFD = reinterpret_cast<ENUMFILTERDATA *>(pData);

			pEFD -> rLst.AddTail(pName);
			if (pEFD -> rStr == pName)
				pEFD -> iIndex = pEFD -> rLst.GetCount()-1;

		} CATCH (CMemoryException, e) {
			reinterpret_cast<ENUMFILTERDATA *>(pData) -> rLst.RemoveAll();
			return FALSE;
		} END_CATCH;
		return TRUE;
	}
}

BOOL CManageDataServerList::FillConnectFilterList (CStringList &rLst, CString &rStr)
{
CString str;

	TRY {
	ENUMNOKEY ENK;
	ENUMFILTERDATA EFD(rLst, rStr);

		if (!str.LoadString(IDS_CREATENEWCONNECTFILTER_CMD))
			return CB_ERR;
		rLst.AddTail (str);
		if (str == rStr)
			EFD.iIndex = 0;

		if (!str.LoadString(IDS_DESELECTCONNECTFILTER_CMD))
			return CB_ERR;
		rLst.AddTail (str);
		if (str == rStr)
			EFD.iIndex = 1;

		ENK.eFcn = reinterpret_cast<ENUMNOKEYPROC>(EnumConnectionFilters);
		ENK.ePtr = &EFD;
		if (!DEX_EnumConnectionFilters(ENK))
			return CB_ERR;

		return EFD.iIndex;

	} CATCH (CMemoryException, e) {
		rLst.RemoveAll();
		return CB_ERR;
	} END_CATCH;
	return CB_ERR;
}

int CManageDataServerList::DecodeConnectFilter(CString &rStr)
{
CStringList lstItems;

	return FillConnectFilterList (lstItems, rStr);
}

int CManageDataServerList::DecodeStatus (CString &rStr, BOOL fIsReadWrite)
{
CStringList lstItems;

	return FillStringList (lstItems, rStr, fIsReadWrite);
}

void CManageDataServerList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrlEx::OnLButtonDown(nFlags, point);

int index;
int colnum;

	if ((index = HitTestEx (point, &colnum)) != -1) 
	{
	UINT flag = LVIS_FOCUSED;
	
		if ((GetItemState (index, flag) & flag) == flag) 
		{
		// evtl Status über ComboBox ändern
			switch (colnum) {
			case STATUS_COLUMN:
				{
					TRY {
					CString strAct;
					LV_ITEM item;

						item.mask = LVIF_TEXT|LVIF_PARAM;	
						item.iItem = index;
						item.iSubItem = STATUS_COLUMN;
						item.pszText = strAct.GetBufferSetLength(_MAX_PATH);
						item.cchTextMax = _MAX_PATH;
						
						GetItem (&item);
						strAct.ReleaseBuffer();
					
					CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(item.lParam);
					CStringList lstItems;
					int iIndex = FillStringList (lstItems, strAct, pData -> IsDriverReadWrite() && pData -> IsSourceReadWrite());

						ShowInPlaceList (index, STATUS_COLUMN, lstItems, iIndex);

					} CATCH (CMemoryException, e) {
						AfxMessageBox (g_cbNoMemory);
					} END_CATCH;
				}
				break;

			case SHORT_COLUMN:
				EditSubLabel (index, SHORT_COLUMN, IDC_INPLACEEDIT_SHORT);
				break;

			default:
			// evtl. BeschreibungsString modifizieren
				if (colnum == CorrectColNum(LONG_COLUMN))
					EditSubLabel (index, CorrectColNum(LONG_COLUMN), IDC_INPLACEEDIT);
				else if (colnum == CorrectColNum(PATH_COLUMN))
					break;	// nothing to do
//				else if (colnum == CONNECTFILTER_COLUMN) {
//				// räumliche Filter behandeln
//#if _TRiAS_VER < 0x0510
//					if (0 == g_dwVer51)
//						break;
//#endif // _TRiAS_VER < 0x0510
//					TRY {
//					CString strAct;
//					LV_ITEM item;
//
//						item.mask = LVIF_TEXT|LVIF_PARAM;	
//						item.iItem = index;
//						item.iSubItem = CONNECTFILTER_COLUMN;
//						item.pszText = strAct.GetBufferSetLength(_MAX_PATH);
//						item.cchTextMax = _MAX_PATH;
//						
//						GetItem (&item);
//						strAct.ReleaseBuffer();
//					
//					CManageDataServerItem *pData = reinterpret_cast<CManageDataServerItem *>(item.lParam);
//					CStringList lstItems;
//					int iIndex = FillConnectFilterList (lstItems, strAct); 
//
//						ShowInPlaceList (index, CONNECTFILTER_COLUMN, lstItems, 
//							iIndex, IDC_INPLACECOMBO_FILTER);
//
//					} CATCH (CMemoryException, e) {
//						AfxMessageBox (g_cbNoMemory);
//					} END_CATCH;
//				}
				break;
			}
		} 
		else {
			SetItemState (index, LVIS_SELECTED | LVIS_FOCUSED, 
					LVIS_SELECTED | LVIS_FOCUSED);
		}
	}
}


// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module SelectExportObjectsDlg.cpp | Implementation of the <c CSelectExportObjectsDlg> class

#include "trias03p.hxx"

#include "trias03.h"
#include "SelectExportObjectsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
StdMessBoxReply VMessageBox (Window *pW, UINT uiCaption, StdMessBox rgType, UINT uiText, ...);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);

/////////////////////////////////////////////////////////////////////////////
// CSelectExportObjectsDlg

CSelectExportObjectsDlg* CSelectExportObjectsDlg::CreateInstance (ResID uiDlg, LPCSTR pcCaption)
{
CSelectExportObjectsDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CSelectExportObjectsDlg(uiDlg, pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CSelectExportObjectsDlg::CSelectExportObjectsDlg(ResID uiDlg, LPCSTR pcCaption) 
	: CPropertyPage(uiDlg, pcCaption),
	  m_lbDataSources (this, IDC_SELECT_DATASOURCES),
	  m_pbSelectAll (this, IDB_SELALLDATASOURCES)
{
	m_dwFlags = 0;
	m_lCntOpen = 0;
}

CSelectExportObjectsDlg::~CSelectExportObjectsDlg()
{
}

void CSelectExportObjectsDlg::AdjustSheetButtons()
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

	SetSheetWizardButtons (dwBttns);
}

BOOL CSelectExportObjectsDlg::GetDisableNextPage()
{
	return ((m_lCntOpen > 0) && (m_lbDataSources.GetNoSelected() > 0)) ? FALSE : TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Datenquellen füllen
BOOL CSelectExportObjectsDlg::FillDataSources()
{
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

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			// geöffnet
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));

			int iNew = m_lbDataSources.AddString (OLE2A(bstrName));

			// wenns die aktuelle ist, dann den Index speichern
			WTRiASDatabase DBase;
			LONG lHandle = 0; 

				THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)&lHandle));
				if (-1 != iNew) {
					m_lbDataSources.SetItemData (iNew, lHandle);		// ProjectHandle zuordnen
					m_lCntOpen++;
				}
			}
		}

	// SpaltenBreite einrichten
		m_lbDataSources.FitColumn();

	} COM_CATCH_RETURN(false);

	if (0 == m_lCntOpen) {		// keine Datenquellen vorhanden
		VMessageBox (this, IDS_EXPORTFMTDLGCAP, 
			ExclamationIcon|OkayButton, IDS_NOOPENCONNECTIONS);
		return false;
	}
	return true;
}
	
// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
HRESULT CSelectExportObjectsDlg::PrepareResult (void)
{
	m_DS.clear();
	if (0 == m_lbDataSources.GetNoSelected()) 
		return false;

int iIndex = m_lbDataSources.GetFirstSelected();
bool fFound = false;

	while (-1 != iIndex) {
		m_DS.insert (reinterpret_cast<HPROJECT>(m_lbDataSources.GetItemData(iIndex)));
		iIndex = m_lbDataSources.GetNextSelected();
		fFound = TRUE;
	}
	return fFound ? S_OK : E_UNEXPECTED;
}

HRESULT CSelectExportObjectsDlg::GetDataSources (CDataSources &rDS)
{
	rDS = m_DS;
	return rDS.size() > 0 ? S_OK : E_UNEXPECTED;
}

/////////////////////////////////////////////////////////////////////////////
// CSelectExportObjectsDlg message handlers

void CSelectExportObjectsDlg::WindowInit (Event e)
{
	m_lbDataSources.FInit();
	m_pbSelectAll.FInit();

	if (!FillDataSources()) 
		m_pbSelectAll.Disable();

	AdjustSheetButtons();
}

void CSelectExportObjectsDlg::ButtonClick (ControlEvt e)
{
	TX_ASSERT(IDB_SELALLDATASOURCES == (uint)e.GetControlID());
	m_lbDataSources.ChangeSelected(Range (0, m_lbDataSources.GetCount()-1));		// alle selektieren
	AdjustSheetButtons();
}

void CSelectExportObjectsDlg::OnItemChanged (NotifyEvt e) 
{
	TX_ASSERT(IDC_SELECT_DATASOURCES == (uint)e.GetControlID());
	AdjustSheetButtons();
}

int CSelectExportObjectsDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CSelectExportObjectsDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CSelectExportObjectsDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Listcontrol, welches annähernd wie eine MultiSelListbox aussieht
CSelectExportObjectsDlg::COpenProjects::COpenProjects(DialogWindow *pParent, ResID id) :
	CListViewCtrl(pParent, id),	m_iLast(-1)
{
}

// dtor
CSelectExportObjectsDlg::COpenProjects::~COpenProjects()
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier doppeltes Freigeben verhindern
CImageList *pIL = SetImageList (NULL, LVSIL_SMALL);

	if (pIL) delete pIL;
}

BOOL CSelectExportObjectsDlg::COpenProjects::FInit()
{
	if (!CListViewCtrl::FInit())
		return FALSE;

#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) 
		SetExtendedStyle (GetExtendedStyle() | LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
#endif 

// eine Spalte hinzufügen
ResourceFile RF (g_pDLLName);
ResString resDataSource (ResID (IDS_DATASOURCE, &RF), 128);

	_ASSERTE(resDataSource.Len() > 0);
	InsertColumn (0, resDataSource);

// ImageList initialisieren
Bitmap bmp (ResID (IDB_PROJECTTYPES, &RF));
Bitmap bmpMask (ResID (IDB_PROJECTTYPES_MASK, &RF));

	_ASSERTE(NULL != bmp.Handle() && NULL != bmpMask.Handle());
	m_ilProjects.CreateList(16, 16, ILC_COLOR|ILC_MASK, 20, 0);

int iCount = m_ilProjects.Add(&bmp, &bmpMask);

	_ASSERTE(iCount != -1);

// Imagelist im ListCtrl setzen
CImageList *pIL = SetImageList (&m_ilProjects, LVSIL_SMALL);

	if (pIL) delete pIL;
	return true;
}

void CSelectExportObjectsDlg::COpenProjects::FitColumn (int iCol)
{
// Call this after your list control is filled     
	SetRedraw(false);

int mincol = iCol < 0 ? 0 : iCol;
int maxcol = iCol < 0 ? GetColumnCount()-1 : iCol;

	for (int col = mincol; col <= maxcol; col++) {
		SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = GetColumnWidth (col);

		SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

	int wc2 = GetColumnWidth (col);
	int wc = max (10, max(wc1, wc2));

		SetColumnWidth (col, wc);     
	}

//	RecalcHeaderTips(); 
	SetRedraw (true);
	InvalidateRect (Handle(), NULL, true); 
}

void CSelectExportObjectsDlg::COpenProjects::SetRedraw (BOOL fRedraw)
{
	ForwardEvent(WM_SETREDRAW, fRedraw);
}

int CSelectExportObjectsDlg::COpenProjects::GetColumnCount(void)
{
HWND hCtrl = GetDlgItem (Handle(), 0);

	TX_ASSERT(::IsWindow(hCtrl));
	return Header_GetItemCount (hCtrl);
}


// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.10.2001 17:11:30
//
// @doc
// @module CopyObjectsDlg.cpp | Implementation of the <c CCopyObjectsDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/Thunk.h>

#include <ipropseq.hxx>
#include <funcs03.h>
#include <xtsnguid.h>

#include "ObjekteDoppelnGuid.h"
#include "ObjekteDoppeln.h"

#include "CopyObjectsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineSmartInterface(ObjectWithSite);

///////////////////////////////////////////////////////////////////////////////
// 
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CCopyObjectsDlg

CCopyObjectsDlg* CCopyObjectsDlg::CreateInstance (CCopyObjects *pParent, ResID uiDlg, LPCSTR pcCaption)
{
CCopyObjectsDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CCopyObjectsDlg(pParent, uiDlg, pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CCopyObjectsDlg::CCopyObjectsDlg(CCopyObjects *pParent, ResID uiDlg, LPCSTR pcCaption) :
	CPropertyPage(uiDlg, pcCaption),
	m_pParent(pParent),
	m_lvDatasources(this, IDC_SELECT_DATASOURCE)
{
	m_dwFlags = 0;
}

CCopyObjectsDlg::~CCopyObjectsDlg()
{
CImageList *pIL = m_lvDatasources.SetImageList (NULL, LVSIL_SMALL);

	if (pIL) delete pIL;
}

void CCopyObjectsDlg::AdjustSheetButtons()
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

	SetSheetWizardButtons(dwBttns);
}

BOOL CCopyObjectsDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Ergebnisdaten aus Controls lesen und zwischenspeichern 
HRESULT CCopyObjectsDlg::PrepareResult (void)
{
	COM_TRY {
	// ausgewählte Datenquelle im globalen Kontext ablegen
	int iIndex = m_lvDatasources.GetNextItem(-1, LVNI_ALL|LVNI_SELECTED);

		if (-1 != iIndex) {
		WDataObject DO;
		WPropertyActionSequence Seq;
		HPROJECT hPr = reinterpret_cast<HPROJECT>(m_lvDatasources.GetItemData(iIndex));

			_ASSERTE(NULL != hPr);
			_ASSERTE(NULL != m_pParent);

			THROW_FAILED_HRESULT(WObjectWithSite(m_pParent) -> GetSite (IID_IPropertyActionSequence, Seq.ppv()));
			THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

		CComVariant vData (reinterpret_cast<LONG>(hPr), VT_I4);

			THROW_FAILED_HRESULT(PropActBase::SetVariantData (vData, DO, &c_feDataSourceHandle));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Datenquellen füllen
BOOL CCopyObjectsDlg::EnumDataSources (HPROJECT hPr, BOOL, UINT_PTR *pData)
{
// in Liste einfügen, nur, wenn nicht schreibgeschützt
	if (DEX_GetROModeEx(hPr))
		return TRUE;

// Namen der Datenquelle besorgen
char cbBuffer[_MAX_PATH];

	if (DEX_GetDataSourceShortName(hPr, cbBuffer)) {
	int iIndex = m_lvDatasources.InsertItem(m_lvDatasources.GetItemCount(), cbBuffer);

		if (-1 != iIndex) {
		DWORD dwBmp = datasource_icon::GetBitmapIndex(hPr);

			m_lvDatasources.SetItem (iIndex, 0, LVIF_IMAGE|LVIF_PARAM, NULL, 
				dwBmp, 0, 0, reinterpret_cast<DWORD>(hPr));
		}
	}
	return TRUE;
}

void CCopyObjectsDlg::FitColumn (int iCol)
{
// Call this after your list control is filled     
	m_lvDatasources.ForwardEvent(WM_SETREDRAW, false);

int mincol = iCol < 0 ? 0 : iCol;
int maxcol = iCol < 0 ? Header_GetItemCount (m_lvDatasources.Handle())-1 : iCol;

	for (int col = mincol; col <= maxcol; col++) {
		m_lvDatasources.SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = m_lvDatasources.GetColumnWidth (col);

		m_lvDatasources.SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

	int wc2 = m_lvDatasources.GetColumnWidth (col);
	int wc = max (10, max(wc1, wc2));

		m_lvDatasources.SetColumnWidth (col, wc);     
	}

//	RecalcHeaderTips(); 
	m_lvDatasources.ForwardEvent(WM_SETREDRAW, true);
	InvalidateRect (m_lvDatasources.Handle(), NULL, true); 
}

HRESULT CCopyObjectsDlg::FillDatasources()
{
CStdThunkImpl<CCopyObjectsDlg, ENUMNOKEYLONGPROC> Thunk(this, &CCopyObjectsDlg::EnumDataSources);
ENUMNOKEYLONG ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = NULL;
	if (!DEX_EnumDataSourceHandles(ENK))
		return E_FAIL;

// SpaltenBreite einrichten
	FitColumn();

// ggf. Fehlermeldung, wenn keine beschreibbaren Datenquellen geöffnet sind
ResourceFile RF (g_pDLLName);

	if (0 == m_lvDatasources.GetItemCount()) {
		VMessageBox (this, ResID(IDS_COPYOBJECTSFMTDLGCAP, &RF),
			ExclamationIcon|OkayButton, ResID(IDS_NOOPENWRITABLECONNECTIONS, &RF));
		return E_FAIL;
	}

	return S_OK;
}

bool CCopyObjectsDlg::InitDatasourceCtrl()
{
	m_lvDatasources.FInit();

#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) 
		m_lvDatasources.SetExtendedStyle (m_lvDatasources.GetExtendedStyle() | LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
#endif 

// eine Spalte hinzufügen
ResourceFile RF (g_pDLLName);
ResString resDataSource (ResID (IDS_DATASOURCE_NOTRO, &RF), 128);

	_ASSERTE(resDataSource.Len() > 0);
	m_lvDatasources.InsertColumn (0, resDataSource);

// ImageList initialisieren
Bitmap bmp (ResID (IDB_PROJECTTYPES, &RF));
Bitmap bmpMask (ResID (IDB_PROJECTTYPES_MASK, &RF));

	_ASSERTE(NULL != bmp.Handle() && NULL != bmpMask.Handle());
	if (!m_ilProjects.CreateList(16, 16, ILC_COLOR|ILC_MASK, 20, 0))
		return false;

int iCount = m_ilProjects.Add(&bmp, &bmpMask);

	_ASSERTE(iCount != -1);

// Imagelist im ListCtrl setzen
CImageList *pIL = m_lvDatasources.SetImageList (&m_ilProjects, LVSIL_SMALL);

	if (pIL) delete pIL;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CCopyObjectsDlg message handlers
void CCopyObjectsDlg::WindowInit (Event e)
{
	if (InitDatasourceCtrl())
		FillDatasources();
}

int CCopyObjectsDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CCopyObjectsDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CCopyObjectsDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}


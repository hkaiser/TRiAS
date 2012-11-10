// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 11.03.2002 18:40:51 
//
// @doc
// @module PpgSelMapType.cpp | Definition of the <c CPpgSelMapType> class

#include "stdafx.h"

#include "resource.h"
#include "MapCtrl/MapCtrlTree.h"

#include "ImportDlg.h"
#include "PpgSelMapType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgSelMapType property page

IMPLEMENT_DYNCREATE(CPpgSelMapType, CPropertyPage)

CPpgSelMapType::CPpgSelMapType() : CPropertyPage(CPpgSelMapType::IDD) 
{
	//{{AFX_DATA_INIT(CPpgSelMapType)
	m_strDesc = _T("");
	//}}AFX_DATA_INIT
}

CPpgSelMapType::~CPpgSelMapType() 
{
}

void CPpgSelMapType::DoDataExchange(CDataExchange* pDX) 
{
	CPropertyPage::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CPpgSelMapType)
	DDX_Control(pDX, IDC_TREEOFENGINES, m_treeOfEngines);
	DDX_Text(pDX, IDC_DESCRIPTION, m_strDesc);
	//}}AFX_DATA_MAP
}

///////////////////////////////////////////////////////////////////////////////
// wird von der Basisklase gerufen
void CPpgSelMapType::UpdateControls() 
{
	m_treeOfEngines.SetFocus();

	m_pParent->m_nNextStep = -1;
	m_pParent->m_strMapExt.Empty();
	m_pParent->m_strMapType.Empty();
	m_pParent->m_pTopoMap.Release();

	if (AdjustDataForSelectedItem (m_treeOfEngines.GetSelectedItem())) 
		UpdateData(FALSE);

	AdjustNextPage();
	AdjustButtons();
}

void CPpgSelMapType::AdjustNextPage()
{
	if (NULL != HTREEITEM(m_treeOfEngines.GetSelectedItem()) && 
		m_pParent->m_pTopoMap != NULL) 
	{
	CComBSTR S;
	long bValid;

		if (S_OK == m_pParent->m_pTopoMap->GetAltFileFilter(&S) && S.Length() > 0) 
		// Kartentyp hat beschreibende, georeferenzierende Dateien zugeordnet
			m_pParent->m_nNextStep = CPpgSelFilesOrDirs::IDD;
		else if(S_OK == m_pParent->m_pTopoMap->HaveNomenclatur(&bValid) && bValid) 
		// Kartentyp hat eine Nomenklatur
			m_pParent->m_nNextStep = CPpgNomenclatur::IDD;
		else if(S_OK == m_pParent->m_pTopoMap->NeedFixPoints(&bValid) && bValid) 
		// Kartentyp braucht Referenzpunkte
			m_pParent->m_nNextStep = CPpgRefPoints::IDD;
		else if(S_OK == m_pParent->m_pTopoMap->PrepareFinalData(&bValid) && bValid) 
			m_pParent->m_nNextStep = CPpgMapInfo::IDD;
	}
}

void CPpgSelMapType::AdjustButtons()
{
	if (-1 == m_pParent->m_nNextStep || m_pParent->m_strMapType.IsEmpty()) 
		m_pParent->SetWizardButtons(0);	// noch unklar, welche Seite folgen soll
	else
		m_pParent->SetWizardButtons(PSWIZB_NEXT);
}

BOOL CPpgSelMapType::AdjustDataForSelectedItem(HTREEITEM hItem)
{
	if (NULL == hItem)
		return FALSE;

MapDWToIUnk::iterator i = m_mapOfEngines.find(hItem);

	if (m_mapOfEngines.end() == i) 
		return FALSE;
		
MAPPOINTER p ((*i).second);

	_ASSERTE(p);
	try {
		m_pParent->m_pTopoMap = p;
	
	// ggf. Beschreibungsinfo abfragen
	CComBSTR bstrFilter;
	
		if (S_OK == p->GetImageFileFilter(&bstrFilter)) 
			m_pParent->m_strPictFileFilter = bstrFilter;

	CComBSTR bstrDescription;

		if (S_OK == p->GetDescription(&bstrDescription)) 
			m_strDesc = bstrDescription;
		else
			m_strDesc.Empty();

	// Kurznamen speichern
	CTreeCursor	c (hItem, &m_treeOfEngines);

		m_pParent->m_strMapType = c.GetText();

	// Default Dateierweiterung
	CComBSTR strDefTyp;
	
		if (S_OK == p->GetDefaultFileTyp(&strDefTyp))
			m_pParent->m_strDefExt = strDefTyp;

	// Dateierweiterung der Beschreibungsdateien
	CComBSTR strMapTyp;
	
		if (S_OK == p->GetAltFileTyp(&strMapTyp))
			m_pParent->m_strMapExt = strMapTyp;

	// Modul kann mehrere Dateien verarbeiten
	long lMultiFlag = 0;

		p->HaveMultiMap(&lMultiFlag);
		m_pParent->m_bMulti = lMultiFlag ? TRUE : FALSE;
	} 
	catch(...) {
		return FALSE;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CPpgSelMapType, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgSelMapType)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEOFENGINES, OnSelchangedTreeofengines)
	ON_NOTIFY(TVN_GETDISPINFO, IDC_TREEOFENGINES, OnGetdispinfoTreeofengines)
	ON_NOTIFY(NM_DBLCLK, IDC_TREEOFENGINES, OnDblclkTreeofengines)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// initialiseren von map<HTREEITEM,CComPtr<IUnknown>>

class PINSPECT : 
	public PUNKINSPECTOR 
{
private:
	CTreeCursor	m_bmk;
	MapDWToIUnk&	m_m;

public:
	PINSPECT(MapDWToIUnk& m, const CTreeCursor& bmk) : m_m(m) { m_bmk = bmk; }
	virtual void OnNode (const CComBSTR& strName, TREENODE& node);
};

void PINSPECT::OnNode(const CComBSTR& strName, TREENODE& node) 
{
	USES_CONVERSION;

MAPPOINTER p (node.m_data);
CTreeCursor	bmk;

	if (!p)
		bmk = m_bmk.AddTail(W2A(strName), I_IMAGECALLBACK);
	else {
	// den Importmodul nach dem Bitmapindex fragen
	long lIndex = 0;

		p->BitmapIndex(&lIndex);
		bmk = m_bmk.AddTail(W2A(strName), lIndex);
	}

	if (node.m_data) {
		_ASSERTE(m_m.end() == m_m.find(bmk));
		m_m.insert(bmk, node.m_data);
	}

PINSPECT pi(m_m, bmk);

	node.m_childs.Traverse(pi);
}

/////////////////////////////////////////////////////////////////////////////
// CPpgSelMapType message handlers

BOOL CPpgSelMapType::OnInitDialog()  
{
	CPropertyPage::OnInitDialog();

	if (!m_ilImages.Create (IDB_MAPTYPES, 16, 16, RGB(255,0,255))) {
		TRACE0("Could not create imagelist for Maptypes\r\n");
	} else 
		m_treeOfEngines.SetImageList(&m_ilImages, TVSIL_NORMAL);

PUNKTREE& t = m_pParent->m_treeOfEngines;
PINSPECT pi(m_mapOfEngines, CTreeCursor(NULL, &m_treeOfEngines));

	t.Traverse(pi);

HTREEITEM hRoot = m_treeOfEngines.GetRootItem();

	m_treeOfEngines.Expand(hRoot, TVE_EXPAND);
	m_treeOfEngines.Expand(m_treeOfEngines.GetNextItem(hRoot, TVGN_CHILD), TVE_EXPAND);

	m_pParent->m_strPictFileFilter.Empty();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//void CPpgSelMapType::OnButtonsrcmap()  
//{
//long lMultiFlag = 0;
//
//	m_pParent->m_pTopoMap->HaveMultiMap(&lMultiFlag);
//
//DWORD dwFlag = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
//
//	if (lMultiFlag)
//		dwFlag |= OFN_ALLOWMULTISELECT;
//
//#if defined(OFN_ENABLESIZING)
//	if (g_Version.IsWin41() || (g_Version.IsWinNT() && g_Version.IsWin50())) {		// Win98 oder WinNT50
//		dwFlag |= OFN_ENABLESIZING;
//#if defined(OFN_DONTADDTORECENT)
//		dwFlag |= OFN_DONTADDTORECENT;
//#endif // defined(OFN_DONTADDTORECENT)
//	}
//#endif // OFN_ENABLESIZING
//
//CMultiFileDialog dlg(TRUE, NULL, _T(""), dwFlag, m_strPictFileFilter, this);
//CString strTitle;
//
//	VERIFY(strTitle.LoadString(IDS_OPENFILETITLE));
//	dlg.m_ofn.lpstrTitle = strTitle;
//	if (IDOK == dlg.DoModal()) {
//
//		if (!lMultiFlag) {
//		CString	strPath = dlg.GetPathName();
//		CComQIPtr<IPictHolder, &IID_IPictHolder> p;
//
//			_ASSERTE(m_pParent->m_pTopoPict);
//			p = m_pParent->m_pTopoPict;
//			if (S_OK == p->OpenPictureFile(CComBSTR(strPath))) {
//			long bValid;
//			
//				m_pParent->m_pTopoMap->CheckPictureFile(m_pParent->m_pTopoPict, &bValid);
//				m_pParent->m_strSrcMap = strPath;
//			} 
//			else {
//			CString	S;
//
//				S.Format(IDS_NOMAP, (LPCTSTR)strPath);
//				::AfxMessageBox(S);
//				m_pParent->m_strSrcMap.Empty();
//			}
//		} 
//		else {
//		POSITION po = dlg.GetStartPosition();
//		
//			if (!po) {
//				CString	S;
//				S.LoadString(IDS_NOMAPNAME);
//				::AfxMessageBox (S);
//				m_pParent->m_strSrcMap.Empty();
//			} 
//			else {
//				while (NULL != po) {
//				CString strPath = dlg.GetNextPathName(po);
//				CComQIPtr<IPictHolder, &IID_IPictHolder> p;
//				
//					_ASSERTE(m_pParent->m_pTopoPict);
//					p = m_pParent->m_pTopoPict;
//					if (S_OK == p->OpenPictureFile(CComBSTR(strPath))) {
//					long bValid;
//
//						m_pParent->m_pTopoMap->CheckPictureFile(m_pParent->m_pTopoPict, &bValid);
//						m_pParent->m_strSrcMap = strPath;
//						m_pParent->m_lMultiCount++;
//					} 
//					else {
//					CString	S;
//
//						S.Format(IDS_NOMAP, (LPCTSTR) strPath);
//						::AfxMessageBox(S);
//						m_pParent->m_strSrcMap.Empty();
//					}
//
//				// Aufsammeln der Karten
//					if (lMultiFlag)
//						OnStoreMaps((LPCTSTR) strPath);
//				}
//			}
//		}
//		m_pParent -> m_bMulti = lMultiFlag ? TRUE : FALSE;
//	}
//	UpdateData(FALSE);
//}

/////////////////////////////////////////////////////////////////////////////////////
//
//void CPpgSelMapType::OnStoreMaps(const char *sPath)  
//{
//TCHAR strDrive[_MAX_DRIVE];
//TCHAR strDir[_MAX_DIR];
//TCHAR strName[_MAX_FNAME];
//TCHAR strExt[_MAX_EXT];
//
//	::_splitpath(sPath, strDrive, strDir, strName, strExt);
//	m_pParent->m_TopKart.push_back((const char *) strName);
//}


////////////////////////////////////////////////////////////////////////////////////

LRESULT CPpgSelMapType::OnWizardNext()  
{
	AdjustDataForSelectedItem(m_treeOfEngines.GetSelectedItem());
	return CPropertyPage::OnWizardNext(m_pParent->m_nNextStep);
}

//	_ASSERTE(m_pParent->m_pTopoMap);
//
//long bValid = 0;
//	
//	if (S_OK == m_pParent->m_pTopoMap->CheckPictureFile(m_pParent->m_pTopoPict, &bValid) && bValid) 
//	{
//	CComVariant	v;
//	HRESULT	hr = m_pParent->m_pTopoPict->GetTagValue(256, &v);
//	
//		_ASSERTE(S_OK == hr);
//		if (S_OK != hr)
//			goto labelWrongPicture;
//		m_pParent->m_sizeOfPicture.cx = v.lVal;
//
//		hr = m_pParent->m_pTopoPict->GetTagValue(257, &v);
//		_ASSERTE(S_OK == hr);
//		if (S_OK != hr)
//			goto labelWrongPicture;
//		m_pParent->m_sizeOfPicture.cy = v.lVal;
//		return CPropertyPage::OnWizardNext(m_pParent->m_nNextStep);
//	}
//
//labelWrongPicture:
//
//CString S;
//
//	S.Format(IDS_NOMAPTYPE, m_pParent->m_strSrcMap, m_pParent->m_strMapType );
//	::AfxMessageBox(S);
//	return -1;

void CPpgSelMapType::OnSelchangedTreeofengines(NMHDR* pNMHDR, LRESULT* pResult)  
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_pParent->m_nNextStep = -1;
	m_pParent->m_strMapType.Empty();
	m_pParent->m_strMapExt.Empty();
	m_pParent->m_pTopoMap.Release();

	if (AdjustDataForSelectedItem (pNMTreeView->itemNew.hItem)) 
		UpdateData(FALSE);

	AdjustNextPage();
	AdjustButtons();
	*pResult = 0;
}

void CPpgSelMapType::OnGetdispinfoTreeofengines(NMHDR* pNMHDR, LRESULT* pResult) 
{
TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	if (TVIF_IMAGE & pTVDispInfo->item.mask || 
		TVIF_SELECTEDIMAGE & pTVDispInfo->item.iSelectedImage) 
	{
		if (!m_treeOfEngines.ItemHasChildren(pTVDispInfo->item.hItem)) {
			pTVDispInfo->item.iImage = IMG_MAPPICT;
			pTVDispInfo->item.iSelectedImage = IMG_MAPPICT;
		}
		else {
			if (m_treeOfEngines.GetItemState (pTVDispInfo->item.hItem, TVIS_EXPANDED) & TVIS_EXPANDED) {
				pTVDispInfo->item.iImage = IMG_FOLDER_OPENED;
				pTVDispInfo->item.iSelectedImage = IMG_FOLDER_OPENED;
			} 
			else {
				pTVDispInfo->item.iImage = IMG_FOLDER_CLOSED;
				pTVDispInfo->item.iSelectedImage = IMG_FOLDER_CLOSED;
			}
		}
	}
	*pResult = 0;
}

void CPpgSelMapType::OnDblclkTreeofengines(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

HTREEITEM hItem = m_treeOfEngines.GetSelectedItem();

	if (NULL != hItem) {
	MapDWToIUnk::iterator i = m_mapOfEngines.find(hItem);

		if (m_mapOfEngines.end() != i) 
		// nur, wenn leaf selektiert wurde
			m_pParent -> PressButton (PSBTN_NEXT);
	}
}


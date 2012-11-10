// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 26.11.2002 13:19:43
//
// @doc
// @module FilesToCopyTree.cpp | Implementation of the <c CFilesToCopyTree> class

#include "stdafx.h"
#include "CopyDLK2.h"

#include "DestList.h"
#include "FilesToCopyTree.h"

// CFilesToCopyTree
IMPLEMENT_DYNAMIC(CFilesToCopyTree, SECTreeCtrl)

CFilesToCopyTree::CFilesToCopyTree() :
    m_hItemNotFound(NULL)
{
}

CFilesToCopyTree::~CFilesToCopyTree()
{
}

///////////////////////////////////////////////////////////////////////////////
//  
void CFilesToCopyTree::AdjustColumns()
{
	SetRedraw(false);
	
CRect rcClient;

    GetClientRect(&rcClient);
    SetColumnWidth(NAME_COLUMN, rcClient.Width()/3);
    SetColumnWidth(COPIED_COLUMN, rcClient.Width()/10);
    
    if (WS_VSCROLL & GetStyle())
        SetColumnWidth(ERROR_COLUMN, (rcClient.Width()*6)/10-GetSystemMetrics(SM_CXVSCROLL));
    else
        SetColumnWidth(ERROR_COLUMN, (rcClient.Width()*6)/10);

	SetRedraw(true);
	InvalidateRect(NULL, true); 
}

int CFilesToCopyTree::GetItemIndex (HTREEITEM hItem)
{
	for (int i = 0; i < GetItemCount(); i++) 
	{
		if (hItem == GetItemAt(i))
			return i;
	}
	return -1;
}

int CFilesToCopyTree::InsertColumn(
	int nCol, UINT uiColHead, int nFormat, int nWidth, int nSubItem)
{
	TRY {
	CString strColHead;

		strColHead.LoadString (uiColHead);
		return SECTreeCtrl::InsertColumn (nCol, strColHead, nFormat, nWidth, nSubItem);

	} CATCH_ALL(e) {
		TRACE0("Could not load resources for column headings\r\n");
		return -1;
	} END_CATCH_ALL;
}

BOOL CFilesToCopyTree::Init(CWnd *pParent)
{
    SubclassTreeCtrlId(IDC_FILESTOCOPY, pParent);
	EnableHeaderCtrl (TRUE);
	ModifyListCtrlStyles (0, LVS_NOSORTHEADER, 0, LVXS_HILIGHTSUBITEMS|
	    LVXS_FITCOLUMNSONSIZE|LVXS_WORDWRAP);
	StoreSubItemText(TRUE);
	
CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_FILETREE) || !bmpMask.LoadBitmap(IDB_FILETREEMASK)) {
		TRACE0("Could not load bitmaps for CDataServerList\r\n");
	    return FALSE;
	}
	else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 20, 0) ||
			-1 == m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CDataServerList\r\n");
			return FALSE;
		} else 
			SetImageList(&m_ilImages, TVSIL_NORMAL);
	}

    m_ilImages.SetOverlayImage(IMG_OVL_OK, IMG_OVL_OK);
    m_ilImages.SetOverlayImage(IMG_OVL_ERROR, IMG_OVL_ERROR);
    
CString str;

	VERIFY(str.LoadString(IDS_SHORTNAMECOLUMN));
	SetColumnHeading (NAME_COLUMN, str);
	
	VERIFY(-1 != InsertColumn (COPIED_COLUMN, IDS_COPIED, LVCFMT_LEFT, -1, COPIED_COLUMN));
	VERIFY(-1 != InsertColumn (ERROR_COLUMN, IDS_ERRORTEXT, LVCFMT_LEFT, -1, ERROR_COLUMN));

    return TRUE;
}

HTREEITEM CFilesToCopyTree::AddCdNode(long lCdName)
{
HTREEITEM hItem = NULL;

    COM_TRY {
    CCdNodes::iterator it = m_mapCds.find(lCdName);

        if (it == m_mapCds.end()) {
        char cbBuffer[_MAX_PATH];
        
            hItem = InsertItem (ltoa (lCdName, cbBuffer, 10), IMG_CD_LOGO, 
                IMG_CD_LOGO, TVI_ROOT, TVI_LAST);

            if (NULL == hItem)
                return NULL;
                
        std::pair<CCdNodes::iterator, bool> p = 
                m_mapCds.insert(CCdNodes::value_type(lCdName, hItem));
            
            if (p.second) 
                return hItem;
            return NULL;
        }
        else {
            hItem = (*it).second;
        }
        
    } COM_CATCH_RETURN(NULL);
    return hItem;
}

namespace {
    CString GetCopiedString(long lFileTypesCopied)
    {
        if (FILETYPE_UNKNOWN == lFileTypesCopied) {
        CString strNo;
        
            VERIFY(strNo.LoadString(IDS_NO));
            return strNo;
        }
        
    CString strCopied ("");
    bool fNeedsComma = false;
    
        if (FILETYPE_TIF & lFileTypesCopied) {
            strCopied += ".tif";
            fNeedsComma = true;
        }
        if (FILETYPE_TFW & lFileTypesCopied) {
            if (fNeedsComma)
                strCopied += ", ";
            strCopied += ".tfw";
            fNeedsComma = true;
        }
        if (FILETYPE_X & lFileTypesCopied) {
            if (fNeedsComma)
                strCopied += ", ";
            strCopied += ".x";
        }
        return strCopied;
    }
}

HTREEITEM CFilesToCopyTree::AddDlkNode(HTREEITEM hParent, long lDlkNode,
    long lFileTypesCopied)
{
HTREEITEM hItem = NULL;

    COM_TRY {
    char cbBuffer[_MAX_PATH];
    CDlkNodes::iterator it = m_mapDlks.find(lDlkNode);

        if (it != m_mapDlks.end()) 
            return (*it).second;
            
        hItem = InsertItem(ltoa(lDlkNode, cbBuffer, 10), IMG_DLK_LOGO, 
                IMG_DLK_LOGO, hParent, TVI_LAST);

    std::pair<CDlkNodes::iterator, bool> p =
        m_mapDlks.insert(CDlkNodes::value_type(lDlkNode, hItem));

        if (!p.second)
            return NULL;

        if (FILETYPE_UNKNOWN == lFileTypesCopied) {
        CString strNo;

            VERIFY(strNo.LoadString(IDS_NO));
            SetItemText(hItem, COPIED_COLUMN, strNo);
            SetItemText(hItem, ERROR_COLUMN, "");
        }
        else {
            SetItemData(hItem, FILETYPE_UNKNOWN);
            SetCopied(lDlkNode, lFileTypesCopied);
        }
        SetItemData(hItem, lFileTypesCopied);
        
    } COM_CATCH_RETURN(NULL);
    return hItem;
}

HTREEITEM CFilesToCopyTree::AddDlkNodeNotFound(long lDlkNode)
{
    if (NULL == m_hItemNotFound) {
    CString strNotExistent;
    
        VERIFY(strNotExistent.LoadString(IDS_NOTEXISTANT_NODE));
        m_hItemNotFound = InsertItem(TVIF_STATE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT, 
                strNotExistent, IMG_CD_LOGO, IMG_CD_LOGO, INDEXTOOVERLAYMASK(IMG_OVL_ERROR), 
                TVIS_OVERLAYMASK, NULL, TVI_ROOT, TVI_FIRST);
        if (NULL == m_hItemNotFound)
            return NULL;
    }
    
char cbBuffer[_MAX_PATH];
HTREEITEM hItem = InsertItem(ltoa(lDlkNode, cbBuffer, 10), IMG_DLK_LOGO, 
            IMG_DLK_LOGO, m_hItemNotFound, TVI_LAST);
CString strNotFound;
CString strNo;

    VERIFY(strNotFound.LoadString(IDS_NOTFOUND_NODE));
    VERIFY(strNo.LoadString(IDS_NO));
    
    SetItemText(hItem, COPIED_COLUMN, strNo);
    SetItemText(hItem, ERROR_COLUMN, strNotFound);
    return hItem;
}

void CFilesToCopyTree::PickTextColors(LvPaintContext* pPC)
{
    ASSERT(NULL != pPC);
    SECTreeCtrl::PickTextColors(pPC);

    if(pPC->lvi.iSubItem == 0) {    // subitem (column) number 0
    // Inside tree column, get a convenient context.
    TvPaintContext* pTvPC = (TvPaintContext *)pPC;
    CString strCopied, strError;
    
        GetItemString(pTvPC->tvi.hItem, COPIED_COLUMN, strCopied);
        GetItemString(pTvPC->tvi.hItem, ERROR_COLUMN, strError);

        if (GetFocus() != this || !(pTvPC->lvi.state & LVIS_SELECTED)) {
        CString strYes;
        
            VERIFY(strYes.LoadString(IDS_YES));
            if (strCopied == strYes)
                pTvPC->rgbText = RGB(0, 128, 0);
            else if (!strError.IsEmpty())
                pTvPC->rgbText = RGB(128, 0, 0);
        }
    }
}

BOOL CFilesToCopyTree::ChildsHaveErrors(HTREEITEM hItem)
{
HTREEITEM hChild = GetNextItem(hItem, TVGN_CHILD);
CString strNo;

    VERIFY(strNo.LoadString(IDS_NO));
    while (NULL != hChild) {
    CString strCopied;
    CString strError;
    
        GetItemString(hChild, COPIED_COLUMN, strCopied);
        GetItemString(hChild, ERROR_COLUMN, strError);
        if (strCopied == strNo && !strError.IsEmpty())
            return TRUE;        // beim ersten Fehler raus
        hChild = GetNextItem(hChild, TVGN_NEXT);
    }
    return FALSE;
}

BOOL CFilesToCopyTree::ChildsAllOk(HTREEITEM hItem)
{
HTREEITEM hChild = GetNextItem(hItem, TVGN_CHILD);
CString strNo;

    VERIFY(strNo.LoadString(IDS_NO));
    while (NULL != hChild) {
    CString strCopied;
    
        GetItemString(hChild, COPIED_COLUMN, strCopied);
        if (strCopied == strNo)
            return FALSE;        // beim ersten Fehler raus
        hChild = GetNextItem(hChild, TVGN_NEXT);
    }
    return TRUE;
}

void CFilesToCopyTree::SetItemOverlayImage(HTREEITEM hItem, int iImage)
{
    _ASSERTE(NULL != hItem);
    if (NULL == hItem)
        return;
        
TV_ITEM tvi;

	memset(&tvi, '\0', sizeof(TV_ITEM));
	tvi.hItem = hItem;
	tvi.mask = TVIF_HANDLE | TVIF_STATE;
	tvi.stateMask = TVIS_OVERLAYMASK;
	tvi.state = INDEXTOOVERLAYMASK(iImage);
	SetItem(&tvi);
}

BOOL CFilesToCopyTree::SetCopied(long lCopiedDlk, long lAddFileTypesCopied)
{
    _ASSERTE(FILETYPE_UNKNOWN != lAddFileTypesCopied);
    
CDlkNodes::iterator it = m_mapDlks.find(lCopiedDlk);

    if (it == m_mapDlks.end())
        return FALSE;

long lFileTypesCopied = GetItemData((*it).second);
CString strYes;
CString strCopied (GetCopiedString(lFileTypesCopied|lAddFileTypesCopied));

    VERIFY(strYes.LoadString(IDS_YES));
    SetItemText((*it).second, COPIED_COLUMN, strYes);
    SetItemText((*it).second, ERROR_COLUMN, strCopied);
    SetItemData((*it).second, lFileTypesCopied|lAddFileTypesCopied);
    
HTREEITEM hParent = GetParentItem((*it).second);

    if (ChildsHaveErrors(hParent))
        SetItemOverlayImage(hParent, IMG_OVL_ERROR);
    else if (ChildsAllOk(hParent))
        SetItemOverlayImage(hParent, IMG_OVL_OK);
    else
        SetItemOverlayImage(hParent, IMG_OVL_NONE);
    
    return TRUE;
}

BOOL CFilesToCopyTree::SetError(long lDlkWithError, char const *pcErrorText)
{
CDlkNodes::iterator it = m_mapDlks.find(lDlkWithError);

    if (it == m_mapDlks.end())
        return FALSE;

    SetItemText((*it).second, ERROR_COLUMN, pcErrorText);
    SetItemOverlayImage(GetParentItem((*it).second), IMG_OVL_ERROR);
    return TRUE;
}
   
///////////////////////////////////////////////////////////////////////////////
//  tab delimited Liste der Resultate liefern
std::string CFilesToCopyTree::GetCdsAndDlks()
{
CString strCaption;

    VERIFY(strCaption.LoadString(IDS_FIELDNAMES));
    
std::string strResult(strCaption);
HTREEITEM hItem = GetNextItem(NULL, TVGN_CHILD);

    
    while (NULL != hItem) {
    CString strName;
    
        GetItemString(hItem, NAME_COLUMN, strName);
        strResult += GetDlksForCd (strName, hItem);
        hItem = GetNextItem (hItem, TVGN_NEXT);
    }
    return strResult;
}

std::string CFilesToCopyTree::GetDlksForCd (
    char const *pcName, HTREEITEM hItem)
{
std::string strResult;
HTREEITEM hChild = GetNextItem (hItem, TVGN_CHILD);

    while (NULL != hChild) {
    CString strName, strComment;
    
        GetItemString(hChild, NAME_COLUMN, strName);
        GetItemString(hChild, ERROR_COLUMN, strComment);
        strResult += std::string(pcName);
        strResult += ';';
        strResult += strName;
        strResult += ';';
        strResult += strComment;
        strResult += '\n';
        hChild = GetNextItem (hChild, TVGN_NEXT);
    }
    return strResult;
}

///////////////////////////////////////////////////////////////////////////////
//  
BEGIN_MESSAGE_MAP(CFilesToCopyTree, SECTreeCtrl)
END_MESSAGE_MAP()


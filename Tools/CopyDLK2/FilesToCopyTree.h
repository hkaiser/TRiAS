// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 26.11.2002 13:18:33
//
// @doc
// @module FilesToCopyTree.h | Declaration of the <c CFilesToCopyTree> class

#if !defined(_FILESTOCOPYTREE_H__DE202811_4668_4E12_9DAE_1669507860D8__INCLUDED_)
#define _FILESTOCOPYTREE_H__DE202811_4668_4E12_9DAE_1669507860D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ot_treectrl.h>		// Objective Toolkit tree/listcontrols
#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
//  ColumnNummern
#define NAME_COLUMN         0
#define COPIED_COLUMN       1
#define ERROR_COLUMN        2

#if !defined(MINCOLWIDTH)
#define MINCOLWIDTH		   10
#endif // MINCOLWIDTH

#define IMG_OVL_NONE        0
#define IMG_OVL_OK          1
#define IMG_OVL_ERROR       2

#define IMG_FOLDER_CLOSED   8
#define IMG_FOLDER_OPENED   9 
#define IMG_DLK_LOGO       10
#define IMG_CD_LOGO        13

#define IMG_CHECKED        11
#define IMG_UNCHECKED      12

///////////////////////////////////////////////////////////////////////////////
//  
class CFilesToCopyTree : public SECTreeCtrl
{
    typedef std::map<long, HTREEITEM> CCdNodes;
    typedef std::map<long, HTREEITEM> CDlkNodes;
    
private:
	DECLARE_DYNAMIC(CFilesToCopyTree)

public:
	CFilesToCopyTree();
	virtual ~CFilesToCopyTree();

	int GetItemIndex (HTREEITEM hItem);

    BOOL Init(CWnd *pParent);
    void AdjustColumns();
        
    void ResetCds() 
    { 
        m_mapCds.clear(); 
        m_mapDlks.clear(); 
        DeleteAllItems(); 
        m_hItemNotFound = NULL;
    }
    HTREEITEM AddCdNode(long lCdName);
    HTREEITEM AddDlkNode (HTREEITEM hParent, long lDlkName, long lFileTypesCopied);
    HTREEITEM AddDlkNodeNotFound (long lDlkName);

    BOOL SetCopied(long lCopiedDlk, long lFileTypesCopied);
    BOOL SetError(long lDlkWithError, char const *pcErrorText);

    std::string GetCdsAndDlks();
    
protected:
	DECLARE_MESSAGE_MAP()

	int InsertColumn(int nCol, UINT uiColHead,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);

    void PickTextColors(LvPaintContext* pPC);
    void SetItemOverlayImage(HTREEITEM hItem, int iImage);

    BOOL ChildsHaveErrors(HTREEITEM hItem);
    BOOL ChildsAllOk(HTREEITEM hItem);

    std::string GetDlksForCd (char const *pcName, HTREEITEM hItem);

private:
   	CImageList m_ilImages;
    CCdNodes m_mapCds;
    CDlkNodes m_mapDlks;
    HTREEITEM m_hItemNotFound;
};

#endif // !defined(_FILESTOCOPYTREE_H__DE202811_4668_4E12_9DAE_1669507860D8__INCLUDED_)

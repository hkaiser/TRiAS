// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.10.2002 21:05:57 
//
// @doc
// @module CoordSystemTree.h | Declaration of the <c CCoordSystemTree> class

#if !defined(_COORDSYSTEMTREE_H__F4AA92FE_5D3D_4660_844E_BF8B9AE61D93__INCLUDED_)
#define _COORDSYSTEMTREE_H__F4AA92FE_5D3D_4660_844E_BF8B9AE61D93__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <registry.hxx>

#pragma warning (disable: 4192)
#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids 

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

class CCoordSystemItem 
{
private:
	os_string m_strFullDesc;
	os_string m_strRegKey;
	os_string m_strTcfName;

public:
		CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey);
		~CCoordSystemItem (void) {}

	os_string &GetDesc (void) { return m_strFullDesc; }
	os_string &GetRegKey (void) { return m_strRegKey; }
	os_string &GetTcfName (void) { return m_strTcfName; }

	HRESULT GetTRiASCS (ITRiASCS **ppICS);
};

///////////////////////////////////////////////////////////////////////////////
// 
#define IMG_COORDFOLDER		3
#define IMG_COORDOPENFOLDER	4

class CCoordSystemTree : public CTreeViewCtrl
{
private:
	class CSelectCoordSysActionDlg *m_pPage;
	CImageList m_ilImages;

// Construction
public:
	CCoordSystemTree(pDialogWindow parent, ResID id);
	~CCoordSystemTree();

// Operations
public:
	HRESULT InitTreeCrtl (CSelectCoordSysActionDlg *pPage);
	void AdjustImage (HTREEITEM hItem);

	bool InitCoordSystemsFromRegistry (void);

	void OnDeleteCoordSystemItem(NMHDR* pNMHDR);
	void OnSelchanged(NMHDR* pNMHDR);
	void OnItemExpanded(NMHDR* pNMHDR);

protected:
	bool InitCoordSystemEntry (CRegistry &rCurr, HTREEITEM hParent, 
		LPCSTR pcFullKey, LPCSTR pcSubkey, DWORD dwPos);
	bool InitCoordSystem (CRegistry &rCurr, HTREEITEM hParent, 
		LPCSTR pcFullKey, LPCSTR pcKey);

private:
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_ProjCS;
	HTREEITEM m_hSelItem;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_COORDSYSTEMTREE_H__F4AA92FE_5D3D_4660_844E_BF8B9AE61D93__INCLUDED_)

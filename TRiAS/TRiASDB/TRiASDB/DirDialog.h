// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.02.2000 15:18:29 
//
// @doc
// @module DirDialog.h | Declaration of the <c CDirDialog> class

#if !defined(_DIRDIALOG_H__D1599594_548D_4900_90F9_A647980F67D1__INCLUDED_)
#define _DIRDIALOG_H__D1599594_548D_4900_90F9_A647980F67D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CDirDialog
{
protected:
	HWND m_hWndParent;

public:
	CDirDialog(CWnd *pParentWnd = NULL);
	virtual ~CDirDialog();
	
	bool DoBrowse();

	CString m_strPath;		// Resultat
	CString m_strInitDir;	// angezeigtes RootVerzeichnis
	CString m_strSelDir;	// Anfangs selektiertes Verzeichnis
	CString m_strTitle;		// Caption
	int  m_iImageIndex;
	UINT m_ulFlags;

	friend int __stdcall BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

#endif // !defined(_DIRDIALOG_H__D1599594_548D_4900_90F9_A647980F67D1__INCLUDED_)

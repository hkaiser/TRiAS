// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.02.2000 15:19:21
//
// @doc
// @module DirDialog.cpp | Implementation of the <c CDirDialog> class

#include "stdafx.h"

#include "DirDialog.h"
#include "shlobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

DefineSmartInterface(Malloc);

// Callback function called by SHBrowseForFolder's browse control
// after initialization and when selection changes
int __stdcall BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
CDirDialog* pDirDialogObj = (CDirDialog*)lpData;

	if (uMsg == BFFM_INITIALIZED && !pDirDialogObj->m_strSelDir.IsEmpty())
	{
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)(LPCTSTR)(pDirDialogObj->m_strSelDir));
	}
//	else // uMsg == BFFM_SELCHANGED
//	{
//	}
	return false;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CDirDialog::CDirDialog(CWnd *pParentWnd)
	: m_hWndParent(NULL), m_ulFlags(BIF_RETURNONLYFSDIRS)
{
	m_hWndParent = pParentWnd -> GetSafeHwnd();
}

CDirDialog::~CDirDialog()
{
}

bool CDirDialog::DoBrowse()
{
WMalloc pMalloc;

	if (S_OK != SHGetMalloc (pMalloc.ppi()))
		return false;

BROWSEINFO bInfo;
LPITEMIDLIST pidl;

	ZeroMemory ((PVOID)&bInfo, sizeof(BROWSEINFO));

	if (!m_strInitDir.IsEmpty ()) {
	OLECHAR olePath[MAX_PATH];
	ULONG chEaten;
	ULONG dwAttributes;
	HRESULT hr;
	LPSHELLFOLDER pDesktopFolder;

	// Get a pointer to the Desktop's IShellFolder interface. 
		if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))	{
		// IShellFolder::ParseDisplayName requires the file name be in Unicode.
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_strInitDir.GetBuffer(MAX_PATH), -1, olePath, MAX_PATH);
			m_strInitDir.ReleaseBuffer (-1);

		// Convert the path to an ITEMIDLIST.
			hr = pDesktopFolder -> ParseDisplayName(NULL, NULL, olePath, &chEaten, &pidl, &dwAttributes);
			if (FAILED(hr))	{
				pMalloc -> Free (pidl);
				return false;
			}
			bInfo.pidlRoot = pidl;
		}
	}

	bInfo.hwndOwner = m_hWndParent;
	bInfo.pszDisplayName = m_strPath.GetBuffer (MAX_PATH);
	_ASSERTE(!m_strTitle.IsEmpty());
	bInfo.lpszTitle = m_strTitle;
	bInfo.ulFlags = m_ulFlags;
	bInfo.lpfn = BrowseCtrlCallback;	// address of callback function
	bInfo.lParam = (LPARAM)this;		// pass address of object to callback function
	if (NULL == (pidl = ::SHBrowseForFolder(&bInfo)))
		return false;

	m_strPath.ReleaseBuffer();
	m_iImageIndex = bInfo.iImage;

	if (!::SHGetPathFromIDList(pidl, m_strPath.GetBuffer(MAX_PATH))) {
		pMalloc ->Free(pidl);
		return false;
	}

	m_strPath.ReleaseBuffer();
	pMalloc ->Free(pidl);
	return true;
}

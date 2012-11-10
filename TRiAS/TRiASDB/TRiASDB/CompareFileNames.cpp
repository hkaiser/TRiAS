// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 09/08/1998 11:53:41 PM
//
// @doc
// @module CompareFileNames.cpp | This function compares the PIDLs of two file names.
// NOTE that you cannot compare the names directly (strcmp() for instance), because one 
// of the names might appear in long file name format and the other in short file name format.
// The function returns TRUE, if 'pszPath1' and 'pszPath2' name the same file in the 
// filesystem, otherwise FALSE. 'pszPath1' and 'pszPath2' shall be absolute pathnames ...

#include "fakemfcp.hxx"
#include <shlobj.h>

BOOL CompareFileNames (BSTR bstrPath1, BSTR bstrPath2) 
{
	VERIFY(bstrPath1 != 0);
	VERIFY(bstrPath2 != 0);

BOOL bRet = FALSE;
LPSHELLFOLDER pDesktopFolder;

	if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder))) {
	// retrieve PIDLs
	LPITEMIDLIST pidl1, pidl2;
	DWORD dwAttr;
	DWORD dummy;

		if (SUCCEEDED(pDesktopFolder->ParseDisplayName(0, 0, bstrPath1, &dummy, &pidl1, &dwAttr)) &&
			SUCCEEDED(pDesktopFolder->ParseDisplayName(0, 0, bstrPath2, &dummy, &pidl2, &dwAttr))) 
		{
		// now we can compare the PIDLs
		HRESULT hRes = pDesktopFolder->CompareIDs(0, pidl1, pidl2);

			if (HRESULT_CODE(hRes) == 0)
				bRet = TRUE;
		
		// free the PIDLs (do not forget this !) ...
		LPMALLOC pMalloc;
		
			SHGetMalloc(&pMalloc);
			pMalloc->Free((void *)pidl1);
			pMalloc->Free((void *)pidl2);
			pMalloc->Release();		
		}
		pDesktopFolder->Release();	
	}	
	return bRet;
}

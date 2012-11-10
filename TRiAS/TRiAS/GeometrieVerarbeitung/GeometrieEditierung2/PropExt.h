// PropertySheet, welcher zusätzliche Pages über die Registry lädt ------------
// File: PropExt.h
// H. Kaiser

#ifndef _PROPEXT_H
#define _PROPEXT_H


#include <shlobj.h>
#include <xtsnguid.h>		// IID_ITriasExtInit, IID_ITriasExtInit2
#include <ixtnext.hxx>		// ITriasExtInit, ITriasExtInit2


//////////////////////////////////////////////////////////////////////////////
// SmartInterfaceKlassen für benötigte Interfaces
DefineSmartInterface(TriasExtInit);
DefineSmartInterface(TriasExtInit2);
DefineSmartInterface(TriasPropSheetExt);

class CEditObjectSheet : 
	public CPropertySheet 
{
private:
	typedef list<WTriasPropSheetExt> CPageList;		// Liste der PageObjekte
	CPageList *m_pPages;		// Liste der nachgeladenen Pages

protected:
	HRESULT LoadExtPageFromRegistry (HKEY hKey, LPCSTR pcKey, LPCSTR pcSubKey, ULONG ulCount, IUnknown **pIUnk, LPDATAOBJECT pIDO);
	HRESULT LoadExtPagesFromRegistry (HKEY hKey, LPCSTR pcKey, LPCSTR pcSubKey, ULONG ulCount, IUnknown **pIUnk, LPDATAOBJECT pIDO);

public:
		CEditObjectSheet (LPCSTR pszCaption, Window *pParentWnd = NULL, 
						  DWORD dwStyle = PSH_DEFAULT, UINT iSelectPage = 0);
		~CEditObjectSheet (void);

// zusätzliche Pages über Registry laden
	HRESULT LoadExtPagesFromRegistry (LPCSTR pcSubKey, ULONG ulCount, IUnknown **ppIUnk, LPDATAOBJECT pIDO = NULL)
		{ return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, g_cbGeoEdit, pcSubKey, ulCount, ppIUnk, pIDO); }
};

///////////////////////////////////////////////////////////////////////////////
// CallBack Funktion, über die die neuen Pages eingehängt werden
BOOL CALLBACK AddPropSheetPageProc (HPROPSHEETPAGE hpage, LPARAM lParam);

#endif // _PROPEXT_H

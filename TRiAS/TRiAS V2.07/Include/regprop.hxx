// PropertySheet, welcher zusätzliche Pages über die Registry lädt ------------
// File: REGPROP.HXX

#if !defined(_REGPROP_HXX)
#define _REGPROP_HXX

#include <ixtnext.hxx>

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaceKlassen für benötigte Interfaces
DefineSmartInterface(TriasExtInit);
DefineSmartInterface(TriasPropSheetExt);

typedef list<WTriasPropSheetExt> CPageList;		// Liste der PageObjekte

class _TRIAS03_ENTRY CPropertySheetExt : public CPropertySheet {
private:
	CPageList *m_pPages;

protected:
	HRESULT LoadExtPageFromRegistry (
				HKEY hKey, LPCSTR pcKey, LPCSTR pcSubKey, 
				LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl);

public:
		CPropertySheetExt (LPCSTR pszCaption, Window *pParentWnd = NULL, 
				DWORD dwStyle = PSH_DEFAULT, UINT iSelectPage = 0);
		~CPropertySheetExt (void);

// zusätzliche Pages über Registry laden
	HRESULT LoadExtPagesFromRegistry (HKEY hKey, LPCSTR pcKey, 
				LPCSTR pcSubKey, LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl);
};

bool CALLBACK AddPropSheetPageProc (HPROPSHEETPAGE hpage, LPARAM lParam);

#endif // _REGPROP_HXX

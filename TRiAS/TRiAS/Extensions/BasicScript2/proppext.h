// proppext.h : header file
//
#ifndef _PROPPEXT_H
#define _PROPPEXT_H

#include <new>		// bad_alloc

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

///////////////////////////////////////////////////////////////////////////
// Template zum Einhängen von PropertyPages
template <class T>
class CPPExt2 : 
		public ITriasPropSheetExt,
		public ITriasExtInit
{
		
protected:
	T	* m_pDlg;
	void DestroyDlg(void) 
		{
			/*if (m_pDlg && IsWindow(m_pDlg -> GetSafeHwnd())) {
				m_pDlg -> DestroyWindow(); 
			}*/
			if (m_pDlg) delete m_pDlg;	m_pDlg = NULL; 
		}
public:
	// Konstruktor
	CPPExt2() {	m_pDlg = NULL; }
	~CPPExt2() { DestroyDlg(); }        
	////////////////////////////////////////////////////////////////////////////
	// ITriasPropSheetExt
	STDMETHOD (AddPages)	(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
		{// Setzt den Modulstatus der MFC.dll auf diese DLL
			AFX_MANAGE_STATE(AfxGetModuleState()); 		
			HPROPSHEETPAGE  hPSP = NULL;
			try {
				if (NULL == m_pDlg) 
					_com_issue_error(E_UNEXPECTED);
			
			// Page kreieren
				hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pDlg->m_psp); 
				if (NULL == hPSP) _com_issue_error(E_HANDLE);	
			
			// Page hinzufügen
				if (!(*lpfnAddPage) (hPSP, lParam)) 
					_com_issue_error(E_FAIL);
			
			} catch (_com_error &e) {
				DestroyDlg(); 
				if (hPSP) DestroyPropertySheetPage(hPSP);
				return _COM_ERROR(e);
			}
			return S_OK;
		}
	STDMETHOD (ReplacePage)	(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
		{// Setzt den Modulstatus der MFC.dll auf diese DLL
			AFX_MANAGE_STATE(AfxGetModuleState()); return E_NOTIMPL;
		}
	////////////////////////////////////////////////////////////////////////////
	// ITriasExtInit
	STDMETHOD (Initialize)	(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
		{// Setzt den Modulstatus der MFC.dll auf diese DLL
			AFX_MANAGE_STATE(AfxGetModuleState()); 
			if (!g_pTE -> isLoaded()) return E_FAIL;
			if (m_pDlg) delete m_pDlg; m_pDlg = NULL; 
			try {   // Page neu anlegen		
				m_pDlg = new T;
			} catch (bad_alloc) {
				return E_OUTOFMEMORY;
			}
			return S_OK;
		}
};
/////////////////////////////////////////////////////////////////////////////

#endif // _PROPPEXT_H
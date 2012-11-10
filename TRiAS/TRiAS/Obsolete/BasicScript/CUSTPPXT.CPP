// CustPPxt.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include "xtsnguid.h"                  

#include <ixtnext.hxx>
#include <dirisole.h>

#include "macrguid.h"
#include "imacorg.h"
#include "imacro.h"

#include "custdlg.h"
#include "CustPPxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeMenuPPExt

IMPLEMENT_DYNCREATE(CCustomizeMenuPPExt, CCmdTarget)

CCustomizeMenuPPExt * CCustomizeMenuPPExt::CreateInstance(IUnknown *pIUnk, 
														  DESTROYNOTIFYPROCPTR pProc)
{
	CCustomizeMenuPPExt * pCustMenuPPExt = new CCustomizeMenuPPExt(); 
	if (NULL == pCustMenuPPExt || !pCustMenuPPExt -> FInit()) {
		if (pCustMenuPPExt) delete pCustMenuPPExt;
		return NULL;
	}

//	((CCmdTarget *)pCustMenuPPExt) -> ExternalAddRef();
	
return pCustMenuPPExt;
}

bool CCustomizeMenuPPExt::FInit()
{
return true;
}

CCustomizeMenuPPExt::CCustomizeMenuPPExt()
{
//	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	m_pCustomizePageDlg = NULL;
	AfxOleLockApp();
}

CCustomizeMenuPPExt::~CCustomizeMenuPPExt()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	if (m_pCustomizePageDlg) delete m_pCustomizePageDlg;
	AfxOleUnlockApp();
}


void CCustomizeMenuPPExt::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CCustomizeMenuPPExt, CCmdTarget)
	//{{AFX_MSG_MAP(CCustomizeMenuPPExt)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Note: we add support for IID_ITRiASPropSheetExt to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

BEGIN_INTERFACE_MAP(CCustomizeMenuPPExt, CCmdTarget)
	INTERFACE_PART(CCustomizeMenuPPExt, IID_ITriasPropSheetExt, CustomizeMenuPSheetExt)
	INTERFACE_PART(CCustomizeMenuPPExt, IID_ITriasExtInit, CustomizeMenuExtInit)
END_INTERFACE_MAP()

#ifdef _DEBUG
// {07963847-3123-101C-BB62-00AA0018497C}						
IMPLEMENT_OLECREATE(CCustomizeMenuPPExt, "TRiASEx.CustomizeMenu.1", 0x07963847L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C)
#endif // _DEBUG
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuExtInit members
/////////////////////////////////////////////////////////////////////////////

CCustomizeMenuPPExt::
XCustomizeMenuExtInit::~XCustomizeMenuExtInit()
{
}

/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuExtInit ITriasExtInit methods

STDMETHODIMP CCustomizeMenuPPExt::
XCustomizeMenuExtInit::Initialize(	LPCITEMIDLIST pidlFolder,	
									LPDATAOBJECT lpdobj,	
									HKEY hkeyProgID)
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuExtInit);
	return pThis -> Initialize(pidlFolder, lpdobj, hkeyProgID);
}

/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuExtInit IUnknown methods

STDMETHODIMP_(ULONG) CCustomizeMenuPPExt::
XCustomizeMenuExtInit::AddRef()
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuExtInit);
	return pThis -> ExternalAddRef();
}

STDMETHODIMP_(ULONG) CCustomizeMenuPPExt::
XCustomizeMenuExtInit::Release()
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuExtInit);
	return pThis -> ExternalRelease();	
}

STDMETHODIMP CCustomizeMenuPPExt::
XCustomizeMenuExtInit::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuExtInit);
	return (HRESULT)pThis -> ExternalQueryInterface(&iid, ppvObj);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuPSheetExt members
/////////////////////////////////////////////////////////////////////////////

CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::~XCustomizeMenuPSheetExt()
{
}

/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuPSheetExt ITriasPropSheetExt methods

STDMETHODIMP CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::AddPages(	LPFNADDPROPSHEETPAGE lpfnAddPage,	
									LPARAM lParam)						
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuPSheetExt);

HPROPSHEETPAGE hPSP = NULL;

    if (NULL != pThis -> m_pCustomizePageDlg) {
		hPSP = CreatePropertySheetPage (&pThis->m_pCustomizePageDlg->m_psp);
		if (NULL == hPSP) return ResultFromScode (E_OUTOFMEMORY);

		if (!(*lpfnAddPage) (hPSP, lParam))             // Page hinzufügen
			return ResultFromScode (E_FAIL);
    } 
	else return ResultFromScode (E_UNEXPECTED);

return NOERROR;
}

STDMETHODIMP CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::ReplacePage(	UINT uPageID,	
										LPFNADDPROPSHEETPAGE lpfnReplacePage,
										LPARAM lParam)
{
	return ResultFromScode(E_NOTIMPL);
}
/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuPSheetExt non-Interface members

HRESULT CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::Initialize(LPCITEMIDLIST pidlFolder,	
									LPDATAOBJECT lpdobj,	
									HKEY hkeyProgID)
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuPSheetExt);

	if (!((CMacroScriptExtension *)g_pTE) -> isLoaded()) {
            ASSERT(0); return ResultFromScode (E_FAIL);
	}

HRESULT hr = ((CMacroScriptExtension *)g_pTE) -> GetMenuStructure();
	if (FAILED(hr)) {
		ASSERT(0); return hr;	
	}

	if (pThis -> m_pCustomizePageDlg) delete (pThis -> m_pCustomizePageDlg);

    TRY {   // Page neu anlegen		
            pThis -> m_pCustomizePageDlg = new CCustDlg;
    } CATCH (CMemoryException, e) {
            return ResultFromScode (E_OUTOFMEMORY);
    } END_CATCH;
	
return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// XCustomizeMenuPSheetExt IUnknown methods

STDMETHODIMP_(ULONG) CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::AddRef()
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuPSheetExt);
	return pThis -> ExternalAddRef();
}

STDMETHODIMP_(ULONG) CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::Release()
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuPSheetExt);
	return pThis -> ExternalRelease();	
}

STDMETHODIMP CCustomizeMenuPPExt::
XCustomizeMenuPSheetExt::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CCustomizeMenuPPExt, CustomizeMenuPSheetExt);
	return (HRESULT)pThis -> ExternalQueryInterface(&iid, ppvObj);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeMenuPPExt message handlers


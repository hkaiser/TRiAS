// Implementation eines PropertySheetHandlers für TRiAS.Document.2 ------------
// File: CTFPROP.CXX

#include "besslgkp.hxx"

#include <shlobj.h>
#include <limits.h>
#include <ixtnext.hxx>
#include <dirisole.h>

#include "besslres.h"

#include "ctfprpcf.hxx"
#include "ctfprop.hxx"

#include "coordpar.hxx"

#include <xtsnguid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// aktuelle Einstellungen füe diese CTF
extern "C" COORDTRANSFORMMODE g_CTFMode = CTFMODE_AutoMeridian;	// wenn GK, dann Meridian automatisch auswählen
extern "C" int g_iMeridian;					// Meridian für GK
extern "C" int g_iStrBreite;				// Streifenbreite für GK
extern "C" int g_iPrec;						// Darstellungsgenauigkeit
extern "C" bool g_fInitialized;				// CTF wurde ordnungsgemäß geladen
extern "C" double g_dScale;					// zusätzlicher Skalierungskoeffizient

extern "C" char g_pDLLName[260];			// Name dieses Modules

#if defined(ELLIPSE_BESSEL)
static const TCHAR szOldName[] = TEXT("BESSELGK");
#elif defined(ELLIPSE_KRASSOVSKY)
static const TCHAR szOldName[] = TEXT("KRASSGK");
#else
#error "No Ellipse defined, Bessel assumed"
#endif


///////////////////////////////////////////////////////////////////////////////
// Controlling Unknown --------------------------------------------------------
#pragma warning(disable: 4355)

CCTFPropExt::CCTFPropExt (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc)
		    : m_Init (pIUnk ? pIUnk : this, this),
			  m_Handler (pIUnk ? pIUnk : this, this)
{
	m_dwRefCnt = 0;
	m_pProc = pProc;
}

#pragma warning(default: 4355)

CCTFPropExt::~CCTFPropExt (void)
{
	if (m_pProc) (*m_pProc)();		// Objekt wieder abmelden
}

bool CCTFPropExt::FInit (void)
{
	return true;
}

CCTFPropExt *CCTFPropExt::CreateInstance (
		IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc)
{
CCTFPropExt *pInfo = new CCTFPropExt(pIUnk, pProc);

	if (NULL == pInfo || !pInfo -> FInit()) {
		DELETE(pInfo);
		return NULL;
	}
	pInfo -> AddRef();

return pInfo; 
}

// *** IUnknown members -------------------------------------------------------
STDMETHODIMP CCTFPropExt::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;

	if (riid == IID_IUnknown)
		*ppvObj = this;
	else if (riid == IID_ITriasExtInit)
		*ppvObj = &m_Init;
	else if (riid == IID_ITriasPropSheetExt)
		*ppvObj = &m_Handler;

	if (NULL != *ppvObj) {
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CCTFPropExt::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CCTFPropExt::Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// InitialisierungInterface dieser PropSheetExt
CCTFPropExt::
CTRiASExtInit::CTRiASExtInit (IUnknown *pIUnk, CCTFPropExt *pInfo)
{
	m_pIUnk = pIUnk;
	m_pInfo = pInfo;

#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
}

CCTFPropExt::
CTRiASExtInit::~CTRiASExtInit (void)
{
	// nothing to do
}

// *** IUnknown members (delegating)
STDMETHODIMP CCTFPropExt::
CTRiASExtInit::QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pIUnk -> QueryInterface (riid, ppv);
}

STDMETHODIMP_(ULONG) CCTFPropExt::
CTRiASExtInit::AddRef (void)
{
#if defined(_DEBUG)
	m_dwRefCnt++;
#endif // _DEBUG

	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CCTFPropExt::
CTRiASExtInit::Release (void)
{
#if defined(_DEBUG)
	m_dwRefCnt--;
#endif // _DEBUG

	return m_pIUnk -> Release();
}

// *** ITriasExtInit methods --------------------------------------------------
STDMETHODIMP CCTFPropExt::
CTRiASExtInit::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
{
	TX_ASSERT (NULL != m_pInfo);
	
	return m_pInfo -> Initialize (pidl, pIDO, hKey);
}


///////////////////////////////////////////////////////////////////////////////
// eigentliches Interface zum Installieren der PropPages
CCTFPropExt::
CTRiASPropSheetExt::CTRiASPropSheetExt (IUnknown *pIUnk, CCTFPropExt *pInfo)
{
	m_pIUnk = pIUnk;
	m_pInfo = pInfo;

	m_pCTFPropPage = NULL;

#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
}

CCTFPropExt::
CTRiASPropSheetExt::~CTRiASPropSheetExt (void)
{
	DELETE(m_pCTFPropPage);
}

// *** IUnknown members (delegating) ------------------------------------------
STDMETHODIMP CCTFPropExt::
CTRiASPropSheetExt::QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pIUnk -> QueryInterface (riid, ppv);
}

STDMETHODIMP_(ULONG) CCTFPropExt::
CTRiASPropSheetExt::AddRef (void)
{
#if defined(_DEBUG)
	m_dwRefCnt++;
#endif // _DEBUG

	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CCTFPropExt::
CTRiASPropSheetExt::Release (void)
{
#if defined(_DEBUG)
	m_dwRefCnt--;
#endif // _DEBUG

	return m_pIUnk -> Release();
}

// *** ITriasPropSheetExt -----------------------------------------------------
STDMETHODIMP CCTFPropExt::
CTRiASPropSheetExt::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
UINT uiPage = ((CPropertySheet *)lParam) -> AddPage (m_pCTFPropPage);

	if (UINT_MAX == uiPage)
		return ResultFromScode (E_FAIL);

return NOERROR;
}

STDMETHODIMP CCTFPropExt::
CTRiASPropSheetExt::ReplacePage (UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return ResultFromScode (E_NOTIMPL);
}

static bool IsActiveCTF (LPCTSTR pcOldName)
{
ResourceFile RF (g_pDLLName);
HeaderEntryX HE (ResString (ResID (IDS_COORDTRANSFORM, &RF), 30));

	if (HE_UNMODIFIED != HE.Status())
		return g_fInitialized;		// nicht vorgegeben, also ist's für uns

	if (!strcmp (HE.EntryText(), pcOldName))
		return true;				// der alte Name stimmt

return false;
}

HRESULT CCTFPropExt::
CTRiASPropSheetExt::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
{
	DELETE(m_pCTFPropPage);

// Testen, ob diese CTF im aktuellen Projekt eingestellt ist
	if (!IsActiveCTF (szOldName))
		return ResultFromScode (E_FAIL);	// nicht für uns

// alles ok, Page(s) anlegen
	try {			// Page neu anlegen
	ResourceFile RF (g_pDLLName);

		m_pCTFPropPage = new CCTFParams (
					ResID (IDD_COORDPARAM, &RF), ResID (IDS_CTFPROPPAGECAP, &RF),
					g_CTFMode, g_iMeridian, g_iStrBreite, g_iPrec, g_dScale);
	} catch (...) {
		return ResultFromScode (E_OUTOFMEMORY);
	}

return NOERROR;
}


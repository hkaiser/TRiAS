// Implementation eines PropertySheetHandlers für TRiAS.Document.2 ------------
// File: SUMMARY.CXX

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <xtsnguid.h>

#include "fakemfc.hxx"		// die Erweiterung selbst
#include "summary.hxx"
#include "summcf.hxx"

#include "summpage.h"
#include "statpage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Controlling Unknown --------------------------------------------------------
#pragma warning(disable: 4355)

CSummaryInfo::CSummaryInfo (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc)
			 : m_Init (pIUnk ? pIUnk : this, this),
			   m_Handler (pIUnk ? pIUnk : this, this)
{
	m_dwRefCnt = 0;
	m_pProc = pProc;
}

#pragma warning(default: 4355)

CSummaryInfo::~CSummaryInfo (void)
{
	if (m_pProc) (*m_pProc)();		// Objekt wieder abmelden
}

bool CSummaryInfo::FInit (void)
{
	return true;
}

CSummaryInfo *CSummaryInfo::CreateInstance (
		IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc)
{
CSummaryInfo *pInfo = new CSummaryInfo(pIUnk, pProc);

	if (NULL == pInfo || !pInfo -> FInit()) {
		DELETE(pInfo);
		return NULL;
	}
	pInfo -> AddRef();

return pInfo; 
}

// *** IUnknown members -------------------------------------------------------
STDMETHODIMP CSummaryInfo::QueryInterface (REFIID riid, LPVOID *ppvObj)
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

STDMETHODIMP_(ULONG) CSummaryInfo::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CSummaryInfo::Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// InitialisierungInterface dieser PropSheetExt
CSummaryInfo::
CTRiASExtInit::CTRiASExtInit (IUnknown *pIUnk, CSummaryInfo *pInfo)
{
	m_pIUnk = pIUnk;
	m_pInfo = pInfo;

#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
}

CSummaryInfo::
CTRiASExtInit::~CTRiASExtInit (void)
{
	// nothing to do
}

// *** IUnknown members (delegating)
STDMETHODIMP CSummaryInfo::
CTRiASExtInit::QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pIUnk -> QueryInterface (riid, ppv);
}

STDMETHODIMP_(ULONG) CSummaryInfo::
CTRiASExtInit::AddRef (void)
{
#if defined(_DEBUG)
	m_dwRefCnt++;
#endif // _DEBUG

	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CSummaryInfo::
CTRiASExtInit::Release (void)
{
#if defined(_DEBUG)
	m_dwRefCnt--;
#endif // _DEBUG

	return m_pIUnk -> Release();
}

// *** ITriasExtInit methods --------------------------------------------------
STDMETHODIMP CSummaryInfo::
CTRiASExtInit::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
{
	ASSERT (NULL != m_pInfo);
	
	return m_pInfo -> Initialize (pidl, pIDO, hKey);
}


///////////////////////////////////////////////////////////////////////////////
// eigentliches Interface zum Installieren der PropPages
CSummaryInfo::
CTRiASPropSheetExt::CTRiASPropSheetExt (IUnknown *pIUnk, CSummaryInfo *pInfo)
{
	m_pIUnk = pIUnk;
	m_pInfo = pInfo;

	m_pSummPage = NULL;
	m_pStatPage = NULL;

	m_uiCF = RegisterClipboardFormat (TEXT("TRiAS.Document.2"));

#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
}

CSummaryInfo::
CTRiASPropSheetExt::~CTRiASPropSheetExt (void)
{
	DELETE(m_pSummPage);
	DELETE(m_pStatPage);
}

// *** IUnknown members (delegating) ------------------------------------------
STDMETHODIMP CSummaryInfo::
CTRiASPropSheetExt::QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pIUnk -> QueryInterface (riid, ppv);
}

STDMETHODIMP_(ULONG) CSummaryInfo::
CTRiASPropSheetExt::AddRef (void)
{
#if defined(_DEBUG)
	m_dwRefCnt++;
#endif // _DEBUG

	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CSummaryInfo::
CTRiASPropSheetExt::Release (void)
{
#if defined(_DEBUG)
	m_dwRefCnt--;
#endif // _DEBUG

	return m_pIUnk -> Release();
}

// *** ITriasPropSheetExt -----------------------------------------------------
STDMETHODIMP CSummaryInfo::
CTRiASPropSheetExt::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
HPROPSHEETPAGE hPSP = NULL;

	if (NULL != m_pSummPage) {		// SummaryPage einhängen
		hPSP = CreatePropertySheetPage (&m_pSummPage->m_psp);
		if (NULL == hPSP) return ResultFromScode (E_OUTOFMEMORY);

		if (!(*lpfnAddPage) (hPSP, lParam))		// Page hinzufügen
			return ResultFromScode (E_FAIL);
	} else
		return ResultFromScode (E_UNEXPECTED);

	if (NULL != m_pStatPage) {		// StatistikPage einhängen
		hPSP = CreatePropertySheetPage (&m_pStatPage->m_psp);
		if (NULL == hPSP) return ResultFromScode (E_OUTOFMEMORY);

		if (!(*lpfnAddPage) (hPSP, lParam))		// Page hinzufügen
			return ResultFromScode (E_FAIL);
	} else
		return ResultFromScode (E_UNEXPECTED);

return NOERROR;
}

STDMETHODIMP CSummaryInfo::
CTRiASPropSheetExt::ReplacePage (UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return ResultFromScode (E_NOTIMPL);
}


HRESULT CSummaryInfo::
CTRiASPropSheetExt::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
{
	DELETE(m_pSummPage);
	DELETE(m_pStatPage);

// Testen, ob dieses Projekt ein Storage ist
	if (NULL == pIDO) return (E_FAIL);

// Storage aus DataObject extrahieren
	{
	FORMATETC fe;
//	STGMEDIUM stm;

	// Testen, ob das gewünschte Format überhaupt da ist
		SETDefFormatEtc (fe, m_uiCF, TYMED_ISTORAGE);

	HRESULT hr = pIDO -> QueryGetData (&fe);

		if (NOERROR != hr) return hr;	// Format nicht vorhanden
/*
	// Daten vom DataObject geben lassen
		memset (&stm, 0, sizeof(STGMEDIUM));
		hr = pIDO -> GetData (&fe, &stm);
		if (FAILED(hr)) return hr;

		if (NULL != stm.pstg)	// ProjectStorage speichern
			m_Stg = stm.pstg;

	// StorageMedium wieder freigeben
		if (TYMED_NULL != stm.tymed)
			ReleaseStgMedium (&stm);
*/	}

// alles ok, Page(s) anlegen
	TRY {	// Page neu anlegen
	CSummInfo *pSI = ((CFakeMFCExtension *)g_pTE) -> GetSummInfo();

		m_pSummPage = new CSummPage;
		m_pSummPage -> SetSummInfo (pSI);

		m_pStatPage = new CStatPage;
		m_pStatPage -> SetSummInfo (pSI);
	} CATCH (CMemoryException, e) {
		return ResultFromScode (E_OUTOFMEMORY);
	} END_CATCH;

return NOERROR;
}

// Basisklasse für GeoDataImport-Interface in einer Erweiterung ---------------
// File: XTSNIMP.CXX

#include "xtensnp.hxx"

#include <xtsnguid.h>
#include <registrx.hxx>

#include "xtsnimp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor -----------------------------------------------------
CImportGeoData :: CImportGeoData (LPUNKNOWN pIUnk)
{
	m_dwRefCnt = 0;
	m_pUnk = pIUnk;
//	ADDREF (m_pUnk);	// nicht nötig, da vollständig von pExt kontrolliert
}

CImportGeoData :: ~CImportGeoData()
{
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP_(HRESULT) CImportGeoData :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pUnk -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CImportGeoData :: AddRef (void)
{
	++m_dwRefCnt;		// debug purposes only
	return m_pUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CImportGeoData :: Release (void)
{
	--m_dwRefCnt;		// debug purposes only
	return m_pUnk -> Release();
}

// ** IImportGeoData methods --------------------------------------------------
STDMETHODIMP_(DWORD) CImportGeoData :: Capabilities (void)
{
	return IMPORTCAPS_NOTIMPLEMENTED;	// can do nothing
}

STDMETHODIMP CImportGeoData :: Configure (HWND hWnd)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CImportGeoData :: ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImportGeoData :: GetConfigInfo (IEnumString **pIEnumStr, DWORD dwReserved)
{
	return ResultFromScode(E_NOTIMPL);
}

// *** IImportGeoDataWithResultCS methods
STDMETHODIMP CImportGeoData::put_CS (IUnknown *pICS)
{
	return ResultFromScode(E_NOTIMPL);
}


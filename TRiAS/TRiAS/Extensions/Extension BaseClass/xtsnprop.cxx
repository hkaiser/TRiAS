// Basisklasse für ObjektPropertyExtensions -----------------------------------
// File: XTSNPROP.CXX

#include "xtensnp.hxx"

#include <xtsnguid.h>

#include "enumprop.hxx"
#include "enmcprop.hxx"
#include "xtsnprop.hxx"
#include "objpropf.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER >= 0x0300
#include <TRiASHelper.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);			// WTRiASLockFeature
DefineSmartInterface(InitInnerObject);			// WInitInnerObject
DefineSmartInterface(TRiASLockFeature);			// WTRiASLockFeature

///////////////////////////////////////////////////////////////////////////////
// Guids etc.
EXTERN_C const CLSID __declspec(selectany) CLSID_FakeTRiASLockFeature = {0x26A3BD85,0x6D09,0x11D2,{0x9E,0xE7,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID __declspec(selectany) IID_IInitInnerObject = {0x58DAD7D6,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
//EXTERN_C const IID __declspec(selectany) IID_ITRiASLockFeature = {0xAF0CE5D5,0x57D8,0x11D2,{0x9E,0xD0,0x00,0x60,0x08,0x44,0x78,0x00}};
#endif // _TRiAS_VER >= 0x0300

// Konstruktor/Destruktor -----------------------------------------------------
CObjectProperties::CObjectProperties (LPUNKNOWN pIUnk, LPCSTR pcGroup, DWORD dwFlags)
{
	m_dwRefCnt = 0;
	m_pIUnk = pIUnk;
	m_pObjEnum = NULL;
	m_pClsEnum = NULL;

	m_dwFlags = dwFlags;
	if (pcGroup) m_strGroup = pcGroup;

//	ADDREF (m_pUnk);	// nicht nötig, da vollständig von pExt kontrolliert
}

CObjectProperties::~CObjectProperties (void)
{
	if (m_pObjEnum) m_pObjEnum -> Release();
	if (m_pClsEnum) m_pClsEnum -> Release();
}

CObjectProperties *CObjectProperties::CreateInstance (
			LPUNKNOWN pUnk, LPCSTR pcGroup, DWORD dwFlags)
{
CObjectProperties *pProps = new CObjectProperties (pUnk, pcGroup, dwFlags);

	if (NULL == pProps || !pProps -> FInit()) {
		DELETE_OBJ(pProps);
		return NULL;
	}
// kein AddRef !!

return pProps;
}

bool CObjectProperties::FInit (void)
{
	m_pObjEnum = CEnumObjectProperties::CreateInstance();
	if (NULL == m_pObjEnum) return false;

	m_pClsEnum = CEnumClassProperties::CreateInstance();
	if (NULL == m_pClsEnum) return false;

return true;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP_(HRESULT) CObjectProperties::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CObjectProperties::AddRef (void)
{
	++m_dwRefCnt;		// debug purposes only
	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CObjectProperties::Release (void)
{
	--m_dwRefCnt;		// debug purposes only
	return m_pIUnk -> Release();
}

// *** IObjectProps specific functions *** ------------------------------------
STDMETHODIMP CObjectProperties::EnumObjectProps (IEnumObjProps **ppEnumProp)
{
#if !defined(__CV__)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // !defined(__CV__)

	if (NULL == ppEnumProp || NULL == m_pObjEnum) 
		return ResultFromScode (E_FAIL);

return m_pObjEnum -> QueryInterface (IID_IEnumObjProps, (LPVOID *)ppEnumProp);
}

STDMETHODIMP CObjectProperties::EnumClassProps (IEnumClassProps **ppEnumProp)
{
#if !defined(__CV__)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // !defined(__CV__)

	if (NULL == ppEnumProp || NULL == m_pClsEnum) 
		return ResultFromScode (E_FAIL);

return m_pClsEnum -> QueryInterface (IID_IEnumClassProps, (LPVOID *)ppEnumProp);
}

STDMETHODIMP CObjectProperties::OnNewReferenceObject (INT_PTR lRefONr)
{
	return ResultFromScode (E_NOTIMPL);	// placeholder only 
}

STDMETHODIMP CObjectProperties::OnNewReferenceClass (IEnumLONG *pEnumObjs)
{
	return ResultFromScode (E_NOTIMPL);	// placeholder only 
}

// Funktion, über welche besondere Informationen abgefragt werden -------------
STDMETHODIMP CObjectProperties::GetGroupInfo (
		LPSTR pGroupName, WORD wLen, DWORD *pdwFlags)
{
#if !defined(__CV__)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // !defined(__CV__)

// GruppenNamen kopieren, wenn gewünscht
	if (pGroupName && wLen > 0) {
		if (m_strGroup.length() > 0) {
		size_t ulT = min ((size_t)(wLen-1), m_strGroup.length());

			strncpy (pGroupName, m_strGroup.c_str(), size_t(ulT));
			pGroupName[ulT] = '\0';
		} else {
			pGroupName[0] = '\0';
			return ResultFromScode (E_FAIL);
		}
	}

// sonstige Flags kopieren, wenn gewünscht
	if (pdwFlags) *pdwFlags = m_dwFlags;

return NOERROR;
}

#if _MSC_VER >= 1100
STDMETHODIMP CObjectProperties::OnNewReferenceObjects(INT_PTR lRefObjs, INT_PTR lRefObj)
{
#if !defined(__CV__)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // !defined(__CV__)
	return E_NOTIMPL;
}
#endif // _MSC_VER >= 1100

// Helperfunktionen, die uns das Leben leichter machen ------------------------
// Definieren einer ObjProperty 
ULONG CObjectProperties::AddPropertyFunction (
		LPCSTR pFName, OBJPROPCALLBACK pFunc, DWORD dwFlags)
{
// spezielles ObjPropertyObjekt erzeugen, das die gegebene Funktion kapselt
CFuncObjectProperty *pFProp = CFuncObjectProperty::CreateInstance (pFName, pFunc, dwFlags);

	if (NULL == pFProp) return 0L;		// E_OUTOFMEMORY or error

LPOBJECTPROPERTY pIObjProp = NULL;
HRESULT hr = pFProp -> QueryInterface (IID_IObjectProperty, (LPVOID *)&pIObjProp);
DWORD dwCookie = 0L;

	pFProp -> Release();

WObjectProperty ObjProp (pIObjProp);

#if _TRiAS_VER >= 0x300
// Aggregation mit dem unbekannten
	COM_TRY {
	WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

		FakeLock -> SetInnerObject (pIObjProp, IID_IObjectProperty, ObjProp.ppu());
		if (!ObjProp.IsValid())
			ObjProp = pIObjProp;

	} COM_CATCH;
#endif // _TRiAS_VER >= 0x300

	if (SUCCEEDED(hr)) {
		dwCookie = m_pObjEnum -> AddProp (ObjProp);
		pIObjProp -> Release();
	}
	return dwCookie;
}

ULONG CObjectProperties::AddPropertyFunctionEx (
		LPCSTR pFName, OBJPROPEXCALLBACK pFunc, DWORD dwData, 
		OBJPROPDELCALLBACK pDelF, DWORD dwFlags)
{
// spezielles ObjPropertyObjekt erzeugen, das die gegebene Funktion kapselt
CFuncObjectProperty *pFProp = CFuncObjectProperty::CreateInstance (
						pFName, pFunc, dwData, pDelF, dwFlags);
	if (NULL == pFProp) return 0L;		// E_OUTOFMEMORY or error

LPOBJECTPROPERTY pIObjProp = NULL;
HRESULT hr = pFProp -> QueryInterface (IID_IObjectProperty, (LPVOID *)&pIObjProp);
DWORD dwCookie = 0L;

	pFProp -> Release();

WObjectProperty ObjProp (pIObjProp);

#if _TRiAS_VER >= 0x300
// Aggregation mit dem unbekannten
	COM_TRY {
	WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

		FakeLock -> SetInnerObject (pIObjProp, IID_IObjectProperty, ObjProp.ppu());
		if (!ObjProp.IsValid())
			ObjProp = pIObjProp;

	} COM_CATCH;
#endif // _TRiAS_VER >= 0x300

	if (SUCCEEDED(hr)) {
		dwCookie = m_pObjEnum -> AddProp (ObjProp);
		pIObjProp -> Release();
	}
	return dwCookie;
}

ULONG CObjectProperties::AddPropertyFunction (LPOBJECTPROPERTY pIObjProp)
{
//WObjectProperty ObjProp (pIObjProp);
//
//#if _TRiAS_VER >= 0x300
//// Aggregation mit dem unbekannten
//	COM_TRY {
//	WTRiASLockFeature Lock;
//
//		if (FAILED(pIObjProp -> QueryInterface (IID_ITRiASLockFeature, Lock.ppv()))) {
//		WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);
//
//			FakeLock -> SetInnerObject (pIObjProp, IID_IObjectProperty, ObjProp.ppu());
//			if (!ObjProp.IsValid())
//				ObjProp = pIObjProp;
//		}
//
//	} COM_CATCH;
//#endif // _TRiAS_VER >= 0x300

DWORD dwCookie = m_pObjEnum -> AddProp (pIObjProp);

	return dwCookie;
}

// Freigeben einer/aller OPFs -------------------------------------------------
bool CObjectProperties::RemovePropertyFunction (ULONG ulFuncID)
{
	return m_pObjEnum -> DeleteProp (ulFuncID);
}

bool CObjectProperties::RemoveAllPropertyFunctions (void)
{
	return m_pObjEnum -> EveryDelete();
}

// Registrieren einer OCPF ----------------------------------------------------
ULONG CObjectProperties::AddPropertyFunction (LPCLASSPROPERTY pIClsProp)
{
DWORD dwCookie = m_pClsEnum -> AddProp (pIClsProp);

//	if (0 != dwCookie) pIClsProp -> AddRef();	// Objekt festhalten

return dwCookie;
}

// Freigeben einer/aller OCPFs ------------------------------------------------
bool CObjectProperties::RemoveClassPropertyFunction (ULONG ulFuncID)
{
	return m_pClsEnum -> DeleteProp (ulFuncID);
}

bool CObjectProperties::RemoveAllClassPropertyFunctions (void)
{
	return m_pClsEnum -> EveryDelete();
}

///////////////////////////////////////////////////////////////////////////////
// Finden einer OPF
HRESULT CObjectProperties::FindObjProp (char const *pName, IObjectProperty **ppIObjProp)
{
	return m_pObjEnum ->FindByName (pName, ppIObjProp);
}


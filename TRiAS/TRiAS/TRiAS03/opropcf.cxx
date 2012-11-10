// ClassFactory für ObjektEigenschaften ---------------------------------------
// File: OPROPCF.CX

#include "trias03p.hxx"

#include "trias03.h"
#include <funcs03.h>

#include <containr.hxx>

#include <undoguid.h>
#include <oprpguid.h>

#include <ixtensn.hxx>		// Interface's
#include <iunredo.hxx>
#include <ioprpini.hxx>
#include <xtsnguid.h>
#include <oprpguid.h>

#include <enumundo.hxx>		// Klassendeklaration
#include <undoredo.hxx>

#include "intoprop.hxx"

extern LONG g_cObj;

///////////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ClassFactory);
DefineSmartInterface(ObjectProperty);

///////////////////////////////////////////////////////////////////////////////
// Lokale Liste der Objekteigenschaften
BEGIN_OBJECT_MAP(ObjPropObjectMap)		
// Objekteigenschaften
	OBJECT_ENTRY(CLSID_ObjPropONr, CObjPropONr)
	OBJECT_ENTRY(CLSID_ObjPropIdent, CObjPropIdent)
	OBJECT_ENTRY(CLSID_ObjPropObjClassCode, CObjPropObjClassCode)
	OBJECT_ENTRY(CLSID_ObjPropObjTypLong, CObjPropObjTypLong)
	OBJECT_ENTRY(CLSID_ObjPropQueryField, CObjPropQueryField)
	OBJECT_ENTRY(CLSID_ObjPropFeature, CObjPropMerkmal)
	OBJECT_ENTRY(CLSID_ObjPropGUID, CObjPropGUID)
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	OBJECT_ENTRY(CLSID_ObjPropDataSource, CObjPropDataSource)
	OBJECT_ENTRY(CLSID_ObjPropDataSourceDesc, CObjPropDataSourceDesc)
#endif // !_FORCE_LEGACY_CODE && _TRiAS_VER >= 0x0300
#if defined(_FORCE_LEGACY_CODE)
	OBJECT_ENTRY(CLSID_ObjPropObjTypShort, CObjPropObjTypShort)
#endif // defined(_FORCE_LEGACY_CODE)
END_OBJECT_MAP()

void TermObjProps (void)
{
_ATL_OBJMAP_ENTRY* pEntry = ObjPropObjectMap;

	while (pEntry->pclsid != NULL)
	{
		if (pEntry->pCF != NULL)
			pEntry->pCF->Release();
		pEntry->pCF = NULL;
		pEntry++;
	}
}

inline
HRESULT GetClassObject(_ATL_OBJMAP_ENTRY* pEntry, REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
HRESULT hRes = S_OK;

	if (ppv == NULL) return E_POINTER;
	while (pEntry->pclsid != NULL) {
		if (InlineIsEqualGUID(rclsid, *pEntry->pclsid)) {
			if (pEntry->pCF == NULL) {
#if defined(__ATL_20_USED__)
				EnterCriticalSection(&_Module.m_csObjMap);
				if (pEntry->pCF == NULL)
					hRes = pEntry->pfnGetClassObject(pEntry->pfnCreateInstance, IID_IUnknown, (LPVOID*)&pEntry->pCF);
				LeaveCriticalSection(&_Module.m_csObjMap);
#else
				_Module.m_csObjMap.Lock();
				if (pEntry->pCF == NULL)
					hRes = pEntry->pfnGetClassObject(pEntry->pfnCreateInstance, IID_IUnknown, (LPVOID*)&pEntry->pCF);
				_Module.m_csObjMap.Unlock();
#endif // __ATL_20_USED__
			}
			if (pEntry->pCF != NULL)
				hRes = pEntry->pCF->QueryInterface(riid, ppv);
			break;
		}
		pEntry++;
	}
	if (*ppv == NULL && hRes == S_OK)
		hRes = CLASS_E_CLASSNOTAVAILABLE;
	return hRes;
}

// Externe Funktion, über welche eine Instanz erzeugt werden kann -------------
_TRIAS03_ENTRY 
HRESULT ObjPropCreateInstance (IUnknown *pIUnk, REFCLSID rClsID, REFIID riid, LPVOID *ppvObj)
{
	if (NULL != pIUnk && !InlineIsEqualGUID(riid, IID_IUnknown))
		return ResultFromScode (CLASS_E_NOAGGREGATION);

// konkrete Objekteigenschaft generieren
WClassFactory cf;
HRESULT hr = GetClassObject (ObjPropObjectMap, rClsID, IID_IClassFactory, cf.ppv());

	if (FAILED(hr)) return hr;

	{
	WObjectProperty op;

		hr = cf -> CreateInstance (pIUnk, riid, op.ppv());
		if (SUCCEEDED(hr)) {
			piInterlockedIncrement (&g_cObj);
			*ppvObj = op.detach();
		}
	}

// Kill the object if initial creation failed. (Release())
	return hr;
}


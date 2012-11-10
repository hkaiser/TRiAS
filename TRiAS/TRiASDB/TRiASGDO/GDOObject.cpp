#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDOObject.h"
#include "GDOFeatures.h"


/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CGDOObject);

/////////////////////////////////////////////////////////////////////////////
// IGDOObject

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDOObject, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ DWORD, dwType
		, /*[in]*/ BSTR, strObjectname
)
{
	COM_TRY {
	CComSemaphore < _ThreadModel> Sem(m_lInitData);	// doppeltes Initialisieren verhindern
//	MC::ArrayUnknown arr;
//	
//		arr.Attach(pObjects);
//		m_pDGMConnection = arr[0];
//
//	WDispatch pDisp;
//		
//		EXT_ERROR_FAILED_HRESULT(m_pDGMConnection -> get_Database (pDisp.ppi()), E_FAIL);
//		m_pGDatabase = pDisp;

		m_bWritable = bWritable;

	WTRiASObject Obj (m_BaseUnk);

		RETURN_FAILED_HRESULT(Obj -> put_Type((OBJECTTYPE)dwType));
		RETURN_FAILED_HRESULT(Obj -> put_Name(strObjectname));
	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectCallback

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObject, get_DefaultType, BSTR*, pbstrType) 
{
	CHECKINPOINTER(pbstrType);
	COM_TRY 
	{
		CComBSTR bstrType(GetObjectCLSID());
		*pbstrType = bstrType.Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObject, SetupObject, SETUPOBJECTMODE, SetupMode) 
{
	return S_OK;
}

HRESULT CGDOObject::EnsureFeatures(bool bForceSetup) 
{
	if (m_bHaveFeatures && !bForceSetup)
		return S_OK;

// alle Objekte einer Objektklasse besitzen einen identischen Satz von Attributen
#if defined(_GDOOBJECT_HAS_OWN_ATTRIBUTES)
WGDOObjects pGDOObjects;
WTRiASFeatures pTRiASFeatures;
WGDOFeatures pGDOFeatures;

	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDOObjects.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pGDOObjects -> CreateFeatures(this, pGDOFeatures.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pGDOFeatures -> QueryInterface(pTRiASFeatures.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECT -> put_Features(pTRiASFeatures), E_FAIL);
#else
WTRiASObjects pTRiASObjects;
WTRiASFeatures pTRiASFeatures;

	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pTRiASObjects.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features (pTRiASFeatures.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECT -> put_Features(pTRiASFeatures), E_FAIL);
#endif // defined(_GDOOBJECT_HAS_OWN_ATTRIBUTES)

	m_bHaveFeatures = true;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObject, SetupFeatures, SETUPFEATURESMODE, SetupMode) 
{
	return EnsureFeatures((SETUPFEATURESMODE_Force & SetupMode) ? true : false);
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObject, OnDelete) 
{
	return E_NOTIMPL;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOObject, OnChanging,/*[in]*/ CHANGEDOBJECT, rgWhat, 
	VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow) 
{
	CHECKINPOINTER(pbDisallow);
	if (IsSemaphoreSignaled(m_lInitData, *this)) 
		return S_OK;

	COM_TRY {
		switch (rgWhat)	{
		case CHANGEDOBJECT_Name: 
			return OnChangingName(vNewValue, pbDisallow);
		
		case CHANGEDOBJECT_Handle:
		case CHANGEDOBJECT_Type:
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObject, OnChanged,/*[in]*/ CHANGEDOBJECT, rgWhat, 
	VARIANT, vOldValue) 
{
	if (IsSemaphoreSignaled(m_lInitData, *this)) 
		return S_OK;

	COM_TRY {
		switch (rgWhat) {
		case CHANGEDOBJECT_Name: 
			return OnChangedName(vOldValue);
		
		case CHANGEDOBJECT_Handle:
		case CHANGEDOBJECT_Type:
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObject, OnFinalRelease) 
{
	return S_OK;
}

HRESULT	CGDOObject::OnChangingName(VARIANT& vNew, VARIANT_BOOL* pbDisallow) 
{
	*pbDisallow = VARIANT_TRUE;
	if (VARIANT_FALSE == m_bWritable)
		return S_FALSE;
	if (V_ISNULL(&vNew) || V_ISEMPTY(&vNew) || V_ISERROR(&vNew))
	{
		return S_FALSE;
	}
	CComVariant	vNewName(vNew);
	WIN_ERROR_NOTSUCCESS(vNewName.ChangeType(VT_BSTR), GDO_E_COERCE);
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT	CGDOObject::OnChangedName(VARIANT& vOld) 
{
	ERROR_EXPR_FALSE(V_ISBSTR(&vOld), E_FAIL);
	WDispatch		pParent;
	WGDOObjects		pGDOObjects;
	
	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECT -> get_Parent(pParent.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pParent -> QueryInterface(pGDOObjects.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pGDOObjects -> RenameObject(this, V_BSTR(&vOld)), E_FAIL);
/*
	CComBSTR		strPrimaryKey;
	CComBSTR		strName;
	WGDODatabase	pGDODatabase;
	WGDOObjects		pGDOObjects;
	WTRiASObjects	pTRiASObjects;
	WTRiASFeatures	pTRiASFeatures;
	WTRiASFeature	pTRiASFeature;
	WGDOFeature		pGDOFeature;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDODatabase.GetIID(), pGDODatabase.ppv()), GDO_E_NOPARENT);
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pTRiASObjects.GetIID(), pTRiASObjects.ppv()), GDO_E_NOPARENT);
	ERROR_FAILED_HRESULT(pTRiASObjects -> QueryInterface(pGDOObjects.GetIID(), pGDOObjects.ppv()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_PrimaryKey(CLEARED(strPrimaryKey)), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strPrimaryKey), pTRiASFeature.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.GetIID(), pGDOFeature.ppv()), E_FAIL);

	{
		AC_GRecordset	rs;
		DBTransaction	dbTrans(m_pGDatabase);
		ERROR_FAILED_HRESULT(LocateRecord(pGDODatabase, pGDOObjects, pGDOFeature, V_BSTR(&vOldName), rs), E_FAIL);
		EXT_ERROR_FAILED_HRESULT(rs -> Edit(), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(SetFieldValue(rs, strPrimaryKey, CComVariant(strName)), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
		dbTrans.Succeeded();
	} // rs schließt automatisch
*/
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IOleClientSite

STDMETHODIMP CGDOObject::GetMoniker(DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk) 
{
	COM_TRY {
		switch (dwWhich) {
		case OLEWHICHMK_CONTAINER: 
			ERROR_FAILED_HRESULT(GetContainerMoniker(ppIMk), E_FAIL);
			break;

		case OLEWHICHMK_OBJREL:
		case OLEWHICHMK_OBJFULL: 
			{
			WMoniker mkCont;
			CComBSTR strName;
			
				ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECT -> get_Name(CLEARED(strName)), E_FAIL);
				ERROR_FAILED_HRESULT(GetContainerMoniker(mkCont.ppi()), E_FAIL);
				ERROR_FAILED_HRESULT(GetObjectMoniker(strName, mkCont, dwWhich, ppIMk), E_FAIL);
			}
			break;

		default:
			MAKE_ERROR(E_INVALIDARG);
			break;
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOObject::GetContainerMoniker(IMoniker **ppIMk) 
{
	COM_TRY {
	WDispatch Parent;
	WMoniker mk;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECT -> get_Parent(Parent.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(WOleClientSite(Parent) -> GetMoniker(OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mk.ppi()), E_FAIL);
		*ppIMk = mk.detach();
	} COM_CATCH;
	return S_OK;
}

/*static*/ 
HRESULT CGDOObject::GetObjectMoniker(LPCOLESTR lpszName, IMoniker *pIContMk, 
	DWORD dwWhich, IMoniker **ppIMk) 
{
CComBSTR strItem(g_cbMkObjectDefW);	// "!MkObjectDef:<Object Name>"

	strItem.Append(g_cbColonW);
	strItem.Append(lpszName);
	if (!strItem)
		return E_OUTOFMEMORY;

WMoniker mkThis, mkItem;

	switch (dwWhich) {
	case OLEWHICHMK_OBJREL:
		RETURN_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDelW, strItem, mkThis.ppi()));
		*ppIMk = mkItem.detach();
		break;

	case OLEWHICHMK_OBJFULL:
		if (NULL == pIContMk)
			return E_POINTER;
		RETURN_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDelW, strItem, mkThis.ppi()));
		RETURN_FAILED_HRESULT(pIContMk -> ComposeWith(mkThis, false, mkItem.ppi()));
		*ppIMk = mkItem.detach();
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}


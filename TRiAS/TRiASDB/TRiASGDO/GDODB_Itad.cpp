#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODatabase.h"
//#include "GDOObjects.h"

/////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
// nach einer bestimmten Objektklasse fragen

/////////////////////////////////////////////////////////////////////////////
// CGDODatabase
// (I)(T)RiAS(A)ccess(D)atabase

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase,get_Views,/*[out, retval]*/ ITRiASViews**, pVal) {
	HRESULT	hr = E_NOTIMPL;
	return hr;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase,get_StartViewName,/*[out, retval]*/ BSTR*, pVal) {
	HRESULT	hr = E_NOTIMPL;
	return hr;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase,get_ObjectsDefs,/*[out, retval]*/ ITRiASObjectsCollection**, ppVal) {
	CHECKOUTPOINTER(ppVal);
	COM_TRY {
		ERROR_EXPR_FALSE( S_OK == IsInitialized(), DBE_E_DATABASE_NOT_OPENED );
		RETURN_FAILED_HRESULT( EnsureObjectsColl() );
		WTRiASObjectsCollection	pTRiASObjectsCollection(m_pGDOObjectsCollection);
		*ppVal = pTRiASObjectsCollection.Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDODatabase,get_ObjectsDef,VARIANT, vIndex, VARIANT_BOOL, fCreate, BSTR, Type, ITRiASObjects**, ppIObjectsDef) 
{
	CHECKOUTPOINTER(ppIObjectsDef);
	COM_TRY {
		CHECK_INITIALIZED();

	WTRiASObjects	pTRiASObjects;
	CComVariant	vItem;

		RETURN_FAILED_HRESULT(EnsureObjectsColl());
	
	HRESULT hr = m_pGDOObjectsCollection -> Item (vIndex, CLEARED(vItem));

		if (SUCCEEDED(hr)) 
			pTRiASObjects = V_DISPATCH(&vItem);
		else if (TRIASDB_E_UNKNOWN_OBJECTS == hr && fCreate) {
		WTRiASObjectsCollection	pTRiASObjectsCollection;
		
			ERROR_FAILED_HRESULT(m_pGDOObjectsCollection -> QueryInterface (pTRiASObjectsCollection.ppi()), E_FAIL);
			ERROR_FAILED_HRESULT(pTRiASObjectsCollection -> Add (V_BSTR(&vIndex), Type, pTRiASObjects.ppi()), E_FAIL);
		} else 
			return hr;

		*ppIObjectsDef = pTRiASObjects.detach();
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// hier gleich noch das gleiche für OleItemContainerSupport
HRESULT CGDODatabase::GetObjectsDef( LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly) {
	COM_TRY	{
		if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)
			return MK_E_EXCEEDEDDEADLINE;
		WTRiASObjects Objs;
		RETURN_FAILED_HRESULT( get_ObjectsDef( CComVariant(pcItem), VARIANT_FALSE, NULL, Objs.ppi() ) );
		if( !fTestRunningOnly && NULL != ppvObj ) {
			THROW_FAILED_HRESULT( Objs->QueryInterface( riid, ppvObj ) );
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDODatabase::GetObjectDef ( LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly) {
	_ASSERTE(SUCCEEDED(MK_E_EXCEEDEDDEADLINE));
	return S_FALSE;
}

HRESULT CGDODatabase::ParseObjectsDef ( LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut) {
	CComBSTR bstrItem(pcItem);
	RETURN_FAILED_HRESULT(CreateItemMoniker (g_cbMkDelW, bstrItem, ppmkOut));
	*pulEaten += bstrItem.Length();
	return S_OK;
}

HRESULT CGDODatabase::ParseObjectDef ( LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut) {
	CComBSTR bstrItem(pcItem);
	RETURN_FAILED_HRESULT(CreateItemMoniker (g_cbMkDelW, bstrItem, ppmkOut));
	*pulEaten += bstrItem.Length();
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,get_Envelope,ENVELOPETYPE,rgType,IDispatch**, pVal) {
	CHECKOUTPOINTER( pVal );
	COM_TRY {
		_ASSERTE(!!m_rcContainer);
		*pVal = m_rcContainer;
		(*pVal)->AddRef();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase,get_ObjectCount,long*, pVal) 
{
	CHECKINPOINTER( pVal );
	*pVal = 1;
	return S_OK;
}

// Implementation of get_AttachedCS
IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase, get_AttachedCS, BSTR, bstrDbName, BSTR *, pbstrAssocCS)
{
	return E_NOTIMPL;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_ConnectionFilter, ITRiASConnectionFilter **, ppIGeom)
{
	return E_NOTIMPL;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, put_ConnectionFilter,ITRiASConnectionFilter *, pIGeom)
{
	return E_NOTIMPL;
}

////////////////////////////////////////////////////////////////////
// Objektklassen anlegen

HRESULT CGDODatabase::EnsureObjectsColl( ) {
	if( !!m_pGDOObjectsCollection )
		return S_OK;
	// Objektklassendefinitionen erstellen
	WGDOObjectsCollection	pGDOObjectsCollection(CLSID_GDOObjectsCollection);
	WTRiASObjectsCollection	pTRiASObjectsCollection(pGDOObjectsCollection);
//	_ASSERTE( m_pApplication );
	ERROR_FAILED_HRESULT( pTRiASObjectsCollection->put_Application( m_pApplication ), E_FAIL  );
	ERROR_FAILED_HRESULT( pTRiASObjectsCollection->put_Parent( static_cast<ITRiASDatabase *>(this) ), E_FAIL );
	MC::ArrayUnknown	arr(3);
	arr[0] = WUnknown(m_pDBConnection).Detach();
	arr[1] = WUnknown(m_pGDatabase).Detach();
	arr[2] = WUnknown(m_pDGMCoordSystemsMgr).Detach();
	ERROR_FAILED_HRESULT( pGDOObjectsCollection->InitTarget( &arr, m_bWritable ), E_FAIL );
	m_pGDOObjectsCollection = pGDOObjectsCollection;
	ERROR_FAILED_HRESULT( m_pGDOObjectsCollection->SetupCollection(), E_FAIL );
	return S_OK;
}

HRESULT CGDODatabase::ReloadObjectsColl() {
	ERROR_EXPR_TRUE( !m_pGDOObjectsCollection, E_FAIL );
	ERROR_FAILED_HRESULT( m_pGDOObjectsCollection->SetupCollection(), E_FAIL );
	return S_OK;
}


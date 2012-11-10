// @doc
// @module TRiASCSPolygon.cpp | Implementation of the <c CTRiASCSPolygonGeometry>
// class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPolygon.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPolygonGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPolygonGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPolygonGeometry

STDMETHODIMP CTRiASCSPolygonGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID *arr[] =
	{
		&IID__DGMPolygonGeometry,
		&IID__DGMPolylineGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASCSPolygonGeometry::get_Type (BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

CComBSTR bstr (g_cbPolygonGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSPolygonGeometry::get_Type (GEOMETRYTYPE * pVal)
{
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pVal = GEOMETRYTYPE_Area;
	return S_OK;
}

STDMETHODIMP CTRiASCSPolygonGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSPolygonGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CTRiASCSPolygonGeometry::Clone (IDispatch * * ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

ObjectLock l(this);
CComObject<CTRiASCSPolygonGeometry> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPolygonGeometry>::CreateInstance (&pNew));
		pNew -> AddRef();			//  pending AddRef

	WDispatch disp;

		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_ptPoints) -> Clone(disp.ppi()));
		pNew -> m_ptPoints = disp;		// throws hr

	// sonstige Werte kopieren
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMGeometry *>(pNew);

	} COM_CATCH_OP (
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSPolygonGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);

ObjectLock l(this);
ULONG ulSize = 0;

	COM_TRY {
		WPersistMemoryWks(m_ptPoints) -> GetSizeMaxWkb (&ulSize);
	} COM_CATCH;

	*pulSize = sizeof(BYTE)+sizeof(UINT)+ulSize;
	return S_OK;
}

HRESULT CTRiASCSPolygonGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPolygonGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	COM_TRY	{
		SaveAndAdvance(pvMem, (BYTE)wkbNDR);
		SaveAndAdvance(pvMem, (UINT)wkbPolygon);
		SaveAndAdvance(pvMem, (UINT)1);
		THROW_FAILED_HRESULT(WPersistMemoryWks(m_ptPoints) -> SaveWkb (pvMem, fClearDirty, cbSize));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSPolygonGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPolygonGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);

	COM_TRY	{
	CComBSTR bstrWKT(L"POLYGON((");
	CComBSTR bstrWKTPts;

		THROW_FAILED_HRESULT(WPersistMemoryWks(m_ptPoints) -> SaveWkt (&bstrWKTPts, fClearDirty));
		bstrWKT.AppendBSTR(bstrWKTPts);
		bstrWKT.Append(L"))");
		*pbstrWKT = bstrWKT;
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


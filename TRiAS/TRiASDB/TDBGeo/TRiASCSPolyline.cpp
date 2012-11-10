// @doc
// @module TRiASCSPolyline.cpp | Implementation of the <c CTRiASCSPolylineGeometry>
// class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPoints.h"
#include "TRiASCSPolyline.h"
#include "TRiASCSPolygon.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPolylineGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPolylineGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSPolylineBase::IsDirty (void)
{
ObjectLock l(this);

	if (m_fIsDirty)
		return S_OK;

// Origin testen
HRESULT	hRes = S_FALSE;

	COM_TRY	{
		hRes = WPersistStream(m_ptPoints) -> IsDirty();
	} COM_CATCH;
	return hRes;
}

HRESULT CTRiASCSPolylineBase::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMPoints, m_ptPoints.ppv()));
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPolylineBase::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);
bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_ptPoints), pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;

	return S_OK;
}

HRESULT CTRiASCSPolylineBase::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);
	pcbSize -> QuadPart = 0;

	COM_TRY	{
	ObjectLock l(this);

		WPersistStream(m_ptPoints) -> GetSizeMax (pcbSize);
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSPolylineBase::InitNew (void)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	COM_TRY	{
	ObjectLock l(this);
	CComObject<CTRiASCSPoints> *pPts = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoints>::CreateInstance (&pPts));
		m_ptPoints = pPts;		// throws hr

		THROW_FAILED_HRESULT(WPersistStreamInit(pPts->GetUnknown()) -> InitNew());

		m_fIsDirty = false;
		m_fIsInitialized = true;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSPolylineBase::Load (void * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	COM_TRY	{
	ObjectLock l(this);
	CComObject<CTRiASCSPoints> *pPts = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoints>::CreateInstance (&pPts));
		m_ptPoints = pPts;	// throws hr

		THROW_FAILED_HRESULT(WPersistMemory(pPts->GetUnknown()) -> Load (pvMem, cbSize));

		m_fIsDirty = false;
		m_fIsInitialized = true;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPolylineBase::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	COM_TRY	{
	ObjectLock l(this);

		THROW_FAILED_HRESULT(WPersistMemory(m_ptPoints) -> Save (pvMem, fClearDirty, cbSize));

		if (fClearDirty)
			m_fIsDirty = false;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPolylineBase::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 0;
	COM_TRY	{
	ObjectLock l(this);

		WPersistMemory(m_ptPoints) -> GetSizeMax (pcbSize);
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPolylineGeometry

STDMETHODIMP CTRiASCSPolylineGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID * arr[] =
	{
		&IID__DGMPolylineGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0;i < sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(* arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASCSPolylineBase::get_Points (_DGMPoints **ppVal)
{
	CHECKOUTPOINTER(ppVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*ppVal = m_ptPoints;
	if (*ppVal)
		(*ppVal) -> AddRef();
	return S_OK;
}

//	ITRiASGeometry
//
STDMETHODIMP CTRiASCSPolylineBase::get_Type (GEOMETRYTYPE * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pVal = GEOMETRYTYPE_Line;
	return S_OK;
}

STDMETHODIMP CTRiASCSPolylineBase::get_Envelope(ITRiASSimpleRectangle * * Rect)
{
	CHECKOUTPOINTER(Rect);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY	{
		return WTRiASCSMBRAccess(m_ptPoints) -> get_Envelope(Rect);
	} COM_CATCH;
	return S_OK;
}

//ITRiASTransformGeometry
HRESULT CTRiASCSPolylineBase::Transform(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	COM_TRY	{
		return WTRiASTransformGeometry(m_ptPoints) -> Transform(csGUID, pCSTransform);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPolylineBase::TransformInverse(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	COM_TRY	{
		return WTRiASTransformGeometry(m_ptPoints) -> TransformInverse(csGUID, pCSTransform);
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASCSPolylineGeometry::get_Type (BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

CComBSTR bstr (g_cbPolylineGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSPolylineGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSPolylineGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSPolylineGeometry::Clone (IDispatch **ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

CComObject<CTRiASCSPolylineGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPolylineGeometry>::CreateInstance (&pNew));
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
HRESULT CTRiASCSPolylineGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);

ULONG ulSize = 0;

	COM_TRY {
	ObjectLock l(this);

		WPersistMemoryWks(m_ptPoints) -> GetSizeMaxWkb (&ulSize);
	} COM_CATCH;

	*pulSize = sizeof(BYTE)+sizeof(UINT)+ulSize;
	return S_OK;
}

HRESULT CTRiASCSPolylineGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPolylineGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	COM_TRY	{
		SaveAndAdvance(pvMem, (BYTE)wkbNDR);
		SaveAndAdvance(pvMem, (UINT)wkbLineString);
		THROW_FAILED_HRESULT(WPersistMemoryWks(m_ptPoints) -> SaveWkb (pvMem, fClearDirty, cbSize));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSPolylineGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPolylineGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);

	COM_TRY	{
	CComBSTR bstrWKT(L"LINESTRING(");
	CComBSTR bstrWKTPts;

		THROW_FAILED_HRESULT(WPersistMemoryWks(m_ptPoints) -> SaveWkt (&bstrWKTPts, fClearDirty));
		bstrWKT.AppendBSTR(bstrWKTPts);
		bstrWKT.Append(L")");
		*pbstrWKT = bstrWKT;
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


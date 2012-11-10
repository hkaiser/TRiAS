// @doc
// @module TRiASCSPointGeometry.cpp | Implementation of the <c CTRiASCSPointGeometry>
// class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPointGeometry.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPointGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPointGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointGeometry

STDMETHODIMP CTRiASCSPointGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID*arr[] =
	{
		&IID__DGMPointGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0; i<sizeof(arr) / sizeof(arr[0]); i ++)
	{
		if (InlineIsEqualGUID(* arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASCSPointGeometry::get_Origin (_DGMPoint **pVal)
{
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

ObjectLock l(this);
CComObject<CTRiASCSPointInCsCoordTarget> *pPt = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPointInCsCoordTarget>::CreateInstance(&pPt));
		pPt -> AddRef();		// pending AddRef

		THROW_FAILED_HRESULT(pPt -> SetCollectionMember (static_cast<_DGMGeometry *>(this), &m_ptOrig));
		*pVal = pPt;

	} COM_CATCH_OP(
		RELEASE(pPt);
	);
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::putref_Origin (_DGMPoint *newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	COM_TRY {
		THROW_FAILED_HRESULT(newVal -> get_X (&m_ptOrig.X));
		THROW_FAILED_HRESULT(newVal -> get_Y (&m_ptOrig.Y));
		THROW_FAILED_HRESULT(newVal -> get_Z (&m_ptOrig.Z));
	} COM_CATCH;

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

// ITRiASSimplePoint
STDMETHODIMP CTRiASCSPointGeometry::GetPoint(double *pVals)
{
	CHECKOUTPOINTER(pVals);
	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

ObjectLock l(this);

	pVals[0] = m_ptOrig.X;
	pVals[1] = m_ptOrig.Y;
	pVals[2] = m_ptOrig.Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::SetPoint(double *pVals)
{
	CHECKINPOINTER(pVals);

ObjectLock l(this);

	m_ptOrig.X = pVals[0];
	m_ptOrig.Y = pVals[1];
	m_ptOrig.Z = pVals[2];
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::get_Type (BSTR*pVal)
{
	CHECKOUTPOINTER(pVal);

CComBSTR bstr (g_cbPointGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::get_Type (GEOMETRYTYPE*pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = GEOMETRYTYPE_Point;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::get_Envelope(ITRiASSimpleRectangle **ppRect)
{
	CHECKOUTPOINTER(ppRect);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY	{
	CCSRectangleGeometry envelSum (m_ptOrig.X, m_ptOrig.Y, m_ptOrig.X, m_ptOrig.Y, 1);

		*ppRect = envelSum.detach();	// Rect ist jetzt Owner des Rechteckes
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASCSPointGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSPointGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSPointGeometry::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

HRESULT CTRiASCSPointGeometry::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

// Bezugspunkt initialisieren
ObjectLock l(this);

	COM_TRY {
	W_DGMPoint newVal;

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMPoint, newVal.ppv()));
		THROW_FAILED_HRESULT(newVal -> get_X (&m_ptOrig.X));
		THROW_FAILED_HRESULT(newVal -> get_Y (&m_ptOrig.Y));
		THROW_FAILED_HRESULT(newVal -> get_Z (&m_ptOrig.Z));
	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPointGeometry::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);
bool fWasDirty = false;

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
	W_DGMPoint ptOrig;

		THROW_FAILED_HRESULT(get_Origin (ptOrig.ppi()));
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(ptOrig), pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;

	return S_OK;
}

HRESULT CTRiASCSPointGeometry::GetSizeMax (ULARGE_INTEGER*pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	pcbSize -> QuadPart = sizeof(CSCOORD);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSPointGeometry::InitNew (void)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	memset (&m_ptOrig, 0, sizeof(CSCOORD));

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSPointGeometry::Load (void *pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	::LoadAndAdvance (m_ptOrig, pvMem);
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPointGeometry::Save (void*pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	::SaveAndAdvance (pvMem, m_ptOrig);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPointGeometry::GetSizeMax (ULONG *pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = sizeof(CSCOORD);
	return S_OK;
}


// ITRiASTransformGeometry
HRESULT CTRiASCSPointGeometry::Transform(struct CSID csGUID, ITRiASCSTransform*pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> Transform (csGUID, 1, &m_ptOrig, &m_ptOrig));
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPointGeometry::TransformInverse(struct CSID csGUID, ITRiASCSTransform*pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> TransformInverse (csGUID, 1, &m_ptOrig, &m_ptOrig));
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSPointGeometry::Clone (IDispatch **ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSPointGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPointGeometry>::CreateInstance(&pNew));
		pNew -> AddRef();	// pending AddRef (stabilize)

		pNew -> m_ptOrig = m_ptOrig;

	// sonstige Werte kopieren
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMGeometry *>(pNew);

	} COM_CATCH_OP(
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSPointGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);
	*pulSize = 2*sizeof(double) + sizeof(UINT) + sizeof(BYTE);
	return S_OK;
}

HRESULT CTRiASCSPointGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPointGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(cbSize < 2*sizeof(double) + sizeof(UINT) + sizeof(BYTE), STREAM_E_INVALIDSIZE);

ObjectLock l(this);

	::SaveAndAdvance (pvMem, (BYTE)wkbNDR);	
	::SaveAndAdvance (pvMem, (UINT)wkbPoint);
	::SaveAndAdvance (pvMem, m_ptOrig.X);
	::SaveAndAdvance (pvMem, m_ptOrig.Y);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSPointGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPointGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);
CComBSTR bstrWKT (L"POINT(");

	ERROR_FAILED_HRESULT(AppendPoint (bstrWKT, m_ptOrig.X, m_ptOrig.Y, false), E_OUTOFMEMORY);
	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


// Implementation of get_X
STDMETHODIMP CTRiASCSPointGeometry::get_X(double *pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_ptOrig.X;
	return S_OK;
}

// Implementation of put_X
STDMETHODIMP CTRiASCSPointGeometry::put_X(double newVal)
{
	m_ptOrig.X = newVal;
	return S_OK;
}

// Implementation of get_Y
STDMETHODIMP CTRiASCSPointGeometry::get_Y(double *pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_ptOrig.Y;
	return S_OK;
}

// Implementation of put_Y
STDMETHODIMP CTRiASCSPointGeometry::put_Y(double newVal)
{
	m_ptOrig.Y = newVal;
	return S_OK;
}

// Implementation of get_Z
STDMETHODIMP CTRiASCSPointGeometry::get_Z(double *pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_ptOrig.Z;
	return S_OK;
}

// Implementation of put_Z
STDMETHODIMP CTRiASCSPointGeometry::put_Z(double newVal)
{
	m_ptOrig.Z = newVal;
	return S_OK;
}


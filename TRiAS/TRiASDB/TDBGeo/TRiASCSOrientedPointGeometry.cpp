// @doc
// @module TRiASCSOrientedPointGeometry.cpp | Implementation of the <c CTRiASCSOrientedPointGeometry> class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPoint.h"
#include "TRiASCSVector.h"
#include "TRiASCSOrientedPointGeometry.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSOrientedPointGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSOrientedPointGeometry

STDMETHODIMP CTRiASCSOrientedPointGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID*arr[] =
	{
		&IID__DGMOrientedPointGeometry,
		&IID__DGMPointGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0; i<sizeof(arr) / sizeof(arr[0]); i ++)
	{
		if (InlineIsEqualGUID(* arr[i] , riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASCSOrientedPointGeometry::get_Origin(_DGMPoint** pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptOrigin;
	if (*pVal)
		(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::putref_Origin(_DGMPoint*newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutOrigin(newVal , false);		// Achtung! Ohne AddRef()!!

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::get_Orientation(_DGMVector** pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_vecOrientation;
	if (* pVal)
		(* pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::putref_Orientation(_DGMVector*newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutOrientation(newVal , false);		// Achtung! Ohne AddRef()!!

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::get_Type(BSTR*pVal)
{
	CHECKOUTPOINTER(pVal);

CComBSTR bstr(g_cbOrientedPointGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::get_Type(GEOMETRYTYPE*pVal)
{
	CHECKINPOINTER(pVal);
	*pVal = GEOMETRYTYPE_OrientedPoint;
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::get_Envelope(/*[out, retval]*/ITRiASSimpleRectangle** Rect)
{
	CHECKOUTPOINTER(Rect);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	if (NULL == m_ptOrigin)
		return E_UNEXPECTED;

	COM_TRY {
	// Punkt bestimmen
	CSCOORD pt;
	
		m_ptOrigin->GetPoint(& pt.X);

	CCSRectangleGeometry mbr(pt.X , pt.Y , 0 , 0);

		*Rect = mbr.detach();	// Rect ist jetzt Owner des Rechteckes
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::get_InitString(BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSOrientedPointGeometry::put_InitString(BSTR bstrMkName)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSOrientedPointGeometry::IsDirty(void)
{
	if (m_fIsDirty)
		return S_OK;

// Origin und Normal testen
ObjectLock l(this);
WPersistStream PS;

	if (SUCCEEDED(m_ptOrigin->QueryInterface(IID_IPersistStream , PS.ppv())) &&
		S_OK == PS->IsDirty())
	{
		return S_OK;
	}
	if (SUCCEEDED(m_vecOrientation->QueryInterface(IID_IPersistStream , PS.ppv())) &&
		S_OK == PS->IsDirty())
	{
		return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASCSOrientedPointGeometry::Load(LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);

	ASSERT(m_fIsOwnerOrig || NULL == m_ptOrigin);
	ASSERT(m_fIsOwnerOrientation || NULL == m_vecOrientation);

	COM_TRY	{
	W_DGMPoint ptOri;
	W_DGMVector vecNormal;

		THROW_FAILED_HRESULT(::OleLoadFromStream(pStm , IID__DGMPoint , ptOri.ppv()));
		THROW_FAILED_HRESULT(::OleLoadFromStream(pStm , IID__DGMVector , vecNormal.ppv()));

		PutOrigin(ptOri , true);
		PutOrientation(vecNormal , true);
	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::Save(LPSTREAM pStm , BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	ASSERT(NULL != m_ptOrigin);
	ASSERT(NULL != m_vecOrientation);

bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
		THROW_FAILED_HRESULT(::OleSaveToStream(WPersistStream(m_ptOrigin) , pStm));
		THROW_FAILED_HRESULT(::OleSaveToStream(WPersistStream(m_vecOrientation) , pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;

	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::GetSizeMax(ULARGE_INTEGER*pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	ASSERT(NULL != m_ptOrigin);
	ASSERT(NULL != m_vecOrientation);

	pcbSize->QuadPart = 0;
	COM_TRY	{
	ULARGE_INTEGER li;

		THROW_FAILED_HRESULT(WPersistStream(m_ptOrigin)->GetSizeMax(pcbSize));
		THROW_FAILED_HRESULT(WPersistStream(m_vecOrientation)->GetSizeMax(& li));
		pcbSize->QuadPart += li.QuadPart;
	
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSOrientedPointGeometry::InitNew(void)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);

	ASSERT(m_fIsOwnerOrig || NULL == m_ptOrigin);
	ASSERT(m_fIsOwnerOrientation || NULL == m_vecOrientation);

CComObject<CTRiASCSPoint> *ptOri = NULL;
CComObject<CTRiASCSVector> *vecNormal = NULL;

	COM_TRY	{
	// Bezugspunkt erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoint>::CreateInstance(& ptOri));
		ptOri->AddRef();		// pending AddRef (stabilize)
		THROW_FAILED_HRESULT(WPersistStreamInit(ptOri->GetUnknown())->InitNew());

	// Vector (Normale) erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSVector>::CreateInstance(& vecNormal));
		vecNormal->AddRef();	// pending AddRef (stabilize)
		THROW_FAILED_HRESULT(WPersistStreamInit(vecNormal->GetUnknown())->InitNew());

		PutOrigin(ptOri, true);
		RELEASE(ptOri);

		PutOrientation(vecNormal, true);
		RELEASE(vecNormal);
	} COM_CATCH_OP(
		RELEASE(ptOri);
		RELEASE(vecNormal);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSOrientedPointGeometry::Load(void*pvMem , ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

CComObject<CTRiASCSPoint> *ptOri = NULL;
CComObject<CTRiASCSVector> *vecNormal = NULL;

	COM_TRY	{
	// Bezugspunkt erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoint>::CreateInstance(& ptOri));
		ptOri->AddRef();		// pending AddRef (stabilize)
		THROW_FAILED_HRESULT(WPersistMemory(ptOri->GetUnknown())->Load(pvMem , SIZEOF_POINT));
		pvMem = (BYTE *)pvMem + SIZEOF_POINT;

	// vector (Normale) erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSVector>::CreateInstance(& vecNormal));
		vecNormal->AddRef();	// pending AddRef (stabilize)
		THROW_FAILED_HRESULT(WPersistMemory(vecNormal->GetUnknown())->Load(pvMem , SIZEOF_POINT));
		pvMem = (BYTE *)pvMem + SIZEOF_POINT;

		PutOrigin(ptOri, true);
		RELEASE(ptOri);

		PutOrientation(vecNormal, true);
		RELEASE(vecNormal);
	}
	COM_CATCH_OP(
		RELEASE(ptOri);
		RELEASE(vecNormal);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::Save(void*pvMem , BOOL fClearDirty , ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	COM_TRY	{
		THROW_FAILED_HRESULT(WPersistMemory(m_ptOrigin)->Save(pvMem , fClearDirty , SIZEOF_POINT));
		pvMem = (BYTE *)pvMem + SIZEOF_POINT;

		THROW_FAILED_HRESULT(WPersistMemory(m_vecOrientation)->Save(pvMem , fClearDirty , SIZEOF_POINT));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::GetSizeMax(ULONG*pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	*pcbSize = 2*SIZEOF_POINT;
	return S_OK;
}

// ITRiASTransformGeometry
HRESULT CTRiASCSOrientedPointGeometry::Transform(/*[in]*/ struct CSID csGUID , /*[in]*/ ITRiASCSTransform*pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);

		return WTRiASTransformGeometry(m_ptOrigin)->Transform(csGUID , pCSTransform);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::TransformInverse(/*[in]*/ struct CSID csGUID , /*[in]*/ ITRiASCSTransform*pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);

		return WTRiASTransformGeometry(m_ptOrigin)->TransformInverse(csGUID , pCSTransform);
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSOrientedPointGeometry::Clone(IDispatch** ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSOrientedPointGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSOrientedPointGeometry>::CreateInstance(& pNew));
		pNew->AddRef();

	// Bezugspunkt und Vector (Normale) erzeugen und initialisieren
	WDispatch disp;

		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_ptOrigin)->Clone(disp.ppi()));
		pNew->PutOrigin(W_DGMPoint(disp) , true);
		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_vecOrientation)->Clone(disp.ppi()));
		pNew->PutOrientation(W_DGMVector(disp) , true);

	// sonstige Werte kopieren
		pNew->m_fIsDirty = false;
		pNew->m_fIsInitialized = true;

		*ppIClonedObj = static_cast<_DGMGeometry *>(pNew);		// übernimmt RefCnt
	} COM_CATCH_OP(
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSOrientedPointGeometry::GetSizeMaxWkb(ULONG *pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	*pcbSize = sizeof(BYTE)+sizeof(UINT)+2*sizeof(double);
	return S_OK;
}

HRESULT CTRiASCSOrientedPointGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSOrientedPointGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	SaveAndAdvance(pvMem, (BYTE)wkbNDR);
	SaveAndAdvance(pvMem, (UINT)wkbPoint);

double dCoord[3];

	RETURN_FAILED_HRESULT(m_ptOrigin -> GetPoint(dCoord));
	SaveAndAdvance(pvMem, dCoord[0]);
	SaveAndAdvance(pvMem, dCoord[1]);

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSOrientedPointGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSOrientedPointGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);

CComBSTR bstrWKT(L"POINT(");
double dCoord[3];

	RETURN_FAILED_HRESULT(m_ptOrigin -> GetPoint(dCoord));
	AppendPoint(bstrWKT, dCoord[0], dCoord[1], false);

	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT.Detach();

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


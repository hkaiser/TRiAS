// @doc
// @module TRiASCSPoint.cpp | Implementation of CTRiASCSPoint.

#include "StdAfx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPoint.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this classes
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPoint);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPointInCol);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPointInCsCoordTarget);


#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPoint, g_cbCounts)
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPointInCol, g_cbCounts)
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPointInCsCoordTarget, g_cbCounts)

//template CTRiASCSPointInTarget<CTRiASCSPointInCol, &CLSID_TRiASCSPointInCol>;

/////////////////////////////////////////////////////////////////////////////
// ITRiASCSPoint

/////////////////////////////////////////////////////////////////////////////
// properties

STDMETHODIMP CTRiASCSPoint::get_X(double * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_p.X;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::put_X(double newVal)
{
	m_p.X = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::get_Y(double * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_p.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::put_Y(double newVal)
{
	m_p.Y = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::get_Z(double * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_p.Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::put_Z(double newVal)
{
	m_p.Z = newVal;
	m_fIsDirty = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// methods

STDMETHODIMP CTRiASCSPoint::GetPoint (double * Coords)
{
	CHECKOUTPOINTER(Coords);
	*(CSCOORD *)Coords = m_p;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoint::SetPoint (double * Coords)
{
	CHECKINPOINTER(Coords);
	m_p = *(CSCOORD *)Coords;
	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSPoint
HRESULT CTRiASCSPoint::SetPoint(double X, double Y, double Z)
{
	m_p.X = X;
	m_p.Y = Y;
	m_p.Z = Z;
	m_fIsDirty = true;
	return S_OK;
}

HRESULT CTRiASCSPoint::GetPoint(double * pX, double * pY, double * pZ)
{
	CHECKOUTPOINTER(pX);
	CHECKOUTPOINTER(pY);
	CHECKOUTPOINTER(pZ);

	*pX = m_p.X;
	*pY = m_p.Y;
	*pZ = m_p.Z;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSPoint::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

HRESULT CTRiASCSPoint::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)

	ERROR_FAILED_HRESULT(LoadItem (pStm, m_p.X), STREAM_E_CANNOTLOADITEM);
	ERROR_FAILED_HRESULT(LoadItem (pStm, m_p.Y), STREAM_E_CANNOTLOADITEM);
	ERROR_FAILED_HRESULT(LoadItem (pStm, m_p.Z), STREAM_E_CANNOTLOADITEM);
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPoint::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED)

	ERROR_FAILED_HRESULT(SaveItem (pStm, m_p.X), STREAM_E_CANNOTSAVEITEM);
	ERROR_FAILED_HRESULT(SaveItem (pStm, m_p.Y), STREAM_E_CANNOTSAVEITEM);
	ERROR_FAILED_HRESULT(SaveItem (pStm, m_p.Z), STREAM_E_CANNOTSAVEITEM);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPoint::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);
	pcbSize -> QuadPart = sizeof(CSCOORD);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

HRESULT CTRiASCSPoint::InitNew (void)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSPoint::Load (void *pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)
	ERROR_EXPR_TRUE(cbSize < sizeof(CSCOORD), STREAM_E_INVALIDSIZE);

	::LoadAndAdvance (m_p, pvMem);
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPoint::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	ERROR_EXPR_TRUE(cbSize < sizeof(CSCOORD), STREAM_E_INVALIDSIZE);

	::SaveAndAdvance (pvMem, m_p);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPoint::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = sizeof(CSCOORD);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSPoint::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);
	*pulSize = 2*sizeof(double) + sizeof(UINT) + sizeof(BYTE);
	return S_OK;
}

HRESULT CTRiASCSPoint::LoadWkb(LPVOID pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPoint::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(cbSize < 2*sizeof(double) + sizeof(UINT) + sizeof(BYTE), STREAM_E_INVALIDSIZE);

	::SaveAndAdvance (pvMem, (BYTE)wkbNDR);	
	::SaveAndAdvance (pvMem, (UINT)wkbPoint);
	::SaveAndAdvance (pvMem, m_p.X);
	::SaveAndAdvance (pvMem, m_p.Y);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSPoint::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPoint::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

CComBSTR bstrWKT (L"POINT(");

	ERROR_FAILED_HRESULT(AppendPoint (bstrWKT, m_p.X, m_p.Y, false), E_OUTOFMEMORY);
	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//ITRiASTransformGeometry
HRESULT CTRiASCSPoint::Transform(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
{
	COM_TRY	{
	WTRiASRawCoordTransform	cst(pCSTransform);
	
		ERROR_FAILED_HRESULT(cst -> Transform(csGUID, 1, &m_p, &m_p), POINT_E_CANNOTTRANSFORMGEOMETRY);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPoint::TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
{
	COM_TRY {
	WTRiASRawCoordTransform	cst(pCSTransform);
		
		ERROR_FAILED_HRESULT(cst -> TransformInverse(csGUID, 1, &m_p, &m_p), POINT_E_CANNOTTRANSFORMGEOMETRY);
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSPoint::Clone (IDispatch * * ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

CComObject<CTRiASCSPoint> *pNew = NULL;

	COM_TRY
	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoint >::CreateInstance(&pNew));
		pNew -> AddRef();	// pending AddRef (stabilize)

	double dX, dY, dZ;

		THROW_FAILED_HRESULT(GetPoint (&dX, &dY, &dZ));
		THROW_FAILED_HRESULT(pNew -> SetPoint (dX, dY, dZ));

		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMPoint *>(pNew);

	} COM_CATCH_OP(
		RELEASE(pNew);
	);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASCSPointInCol(lection)

/////////////////////////////////////////////////////////////////////////////
// properties

STDMETHODIMP CTRiASCSPointInTarget::get_X(double * pVal)
{
	CHECKOUTPOINTER(pVal);

CSCOORD	c;									// Puffer

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	*pVal = c.X;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::put_X(double newVal)
{
CSCOORD	c;

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	c.X = newVal;
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::get_Y(double * pVal)
{
	CHECKOUTPOINTER(pVal);

CSCOORD	c;									// Puffer

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	*pVal = c.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::put_Y(double newVal)
{
CSCOORD	c;									// Puffer

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	c.Y = newVal;								// nur y Verändern
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::get_Z(double * pVal)
{
	CHECKOUTPOINTER(pVal);

CSCOORD	c;

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	*pVal = c.Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::put_Z(double newVal)
{
CSCOORD	c;

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	c.Z = newVal;
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);
	m_fIsDirty = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// methods

STDMETHODIMP CTRiASCSPointInTarget::GetPoint (double * Coords)
{
	CHECKOUTPOINTER(Coords);
	ERROR_FAILED_HRESULT(GetData(Coords), POINT_E_CANNOTRETRIEVECOORDINATE);
	return S_OK;
}

STDMETHODIMP CTRiASCSPointInTarget::SetPoint (double * Coords)
{
	CHECKINPOINTER(Coords);
	ERROR_FAILED_HRESULT(SetData(Coords), POINT_E_CANNOTSETCOORDINATE);
	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSPoint
HRESULT CTRiASCSPointInTarget::SetPoint(double X, double Y, double Z)
{
CSCOORD	c;

	c.X = X;
	c.Y = Y;
	c.Z = Z;								// nur x Verändern
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::GetPoint(double * pX, double * pY, double * pZ)
{
	CHECKOUTPOINTER(pX);
	CHECKOUTPOINTER(pY);
	CHECKOUTPOINTER(pZ);

CSCOORD	c;							// Puffer

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	*pX = c.X;
	*pY = c.Y;
	*pZ = c.Z;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSPointInTarget::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

HRESULT CTRiASCSPointInTarget::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)

CSCOORD	c;							// Puffer

	ERROR_FAILED_HRESULT(LoadItem (pStm, c.X), STREAM_E_CANNOTLOADITEM);
	ERROR_FAILED_HRESULT(LoadItem (pStm, c.Y), STREAM_E_CANNOTLOADITEM);
	ERROR_FAILED_HRESULT(LoadItem (pStm, c.Z), STREAM_E_CANNOTLOADITEM);
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

CSCOORD	c;							// Puffer

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	ERROR_FAILED_HRESULT(SaveItem (pStm, c.X), STREAM_E_CANNOTSAVEITEM);
	ERROR_FAILED_HRESULT(SaveItem (pStm, c.Y), STREAM_E_CANNOTSAVEITEM);
	ERROR_FAILED_HRESULT(SaveItem (pStm, c.Z), STREAM_E_CANNOTSAVEITEM);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);
	pcbSize -> QuadPart = sizeof(CSCOORD);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSPointInTarget::InitNew (void)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSPointInTarget::Load (void * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)
	ERROR_EXPR_TRUE(cbSize<sizeof(CSCOORD), STREAM_E_INVALIDSIZE);

CSCOORD	c;

	::LoadAndAdvance (c, pvMem);
	ERROR_FAILED_HRESULT(SetData(&c.X), POINT_E_CANNOTSETCOORDINATE);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(cbSize<sizeof(CSCOORD), STREAM_E_INVALIDSIZE);

CSCOORD	c;

	ERROR_FAILED_HRESULT(GetData(&c.X), POINT_E_CANNOTRETRIEVECOORDINATE);
	::SaveAndAdvance (pvMem, c);

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED)
	*pcbSize = sizeof(CSCOORD);
	return S_OK;
}

//ITRiASTransformGeometry
// ... hier wird nichts gemacht, da CTRiASCSPointInTarget nur auf Daten seines Papa (oder der Mama)
// zugreift. Die oder der ist für die Transformation zuständig
HRESULT CTRiASCSPointInTarget::Transform(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
{
	return S_OK;
}

HRESULT CTRiASCSPointInTarget::TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointInCol

HRESULT CTRiASCSPointInCol::SetCollectionMember (_DGMPoints *pIPoints, long nIndex)
{
	if (m_wParent.IsValid())	// kann nur zu einer Collection gehören
		return E_UNEXPECTED;

// ich hole jetzt meine Daten von dort
	m_wParent = pIPoints;
	m_nIndex = nIndex;

	return S_OK;
}

HRESULT CTRiASCSPointInCol::GetData(double * val)
{
	if (m_wParent.IsValid())	// hier jetzt die richtigen Daten abholen
		return m_wParent -> GetPoint (m_nIndex, val);

// geht nicht, Initialisierung fehlt
	return E_FAIL;
}

HRESULT CTRiASCSPointInCol::SetData(double * val)
{
	if (m_wParent.IsValid())
		return m_wParent -> SetPoint (m_nIndex, val);

// geht nicht, Initialisierung fehlt
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointInCsCoordTarget
HRESULT CTRiASCSPointInCsCoordTarget::SetCollectionMember (_DGMGeometry *pIRect, CSCOORD *pPt)
{
	if (m_wParent.IsValid())	// kann nur zu einer Collection gehören
		return E_UNEXPECTED;

// ich hole jetzt meine Daten von dort
	m_wParent = pIRect;
	m_pPt = pPt;

	return S_OK;
}

HRESULT CTRiASCSPointInCsCoordTarget::GetData(double *val)
{
	if (m_wParent.IsValid() && NULL != m_pPt) {	// hier jetzt die richtigen Daten abholen
		*reinterpret_cast<CSCOORD *>(val) = *m_pPt;
		return S_OK;
	}

// geht nicht, Initialisierung fehlt
	return E_FAIL;
}

HRESULT CTRiASCSPointInCsCoordTarget::SetData(double *val)
{
	if (m_wParent.IsValid() && NULL != m_pPt) {
		*m_pPt = *reinterpret_cast<CSCOORD *>(val);
		return S_OK;
	}

// geht nicht, Initialisierung fehlt
	return E_FAIL;
}


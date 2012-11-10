// @doc
// @module TRiASCSLine.cpp | Implementation of the <c CTRiASCSLineGeometry>
// class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSLine.h"
#include "TRiASCSVector.h"
#include "TRiASCSRectangle.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
//IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSLineGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSLineGeometry , g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSLineGeometry

STDMETHODIMP CTRiASCSLineGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID*arr[] =
	{
		&IID__DGMLineGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0;i < sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(* arr[i] , riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASCSLineGeometry::get_Start (_DGMPoint** pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptStart;
	if (* pVal)
		(* pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::putref_Start (_DGMPoint*newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutStart(newVal , false);		// Achtung! Ohne AddRef()!!

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::get_End (_DGMPoint** pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptEnd;
	if (* pVal)
		(* pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::putref_End (_DGMPoint*newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutEnd(newVal , false);		// Achtung! Ohne AddRef()!!

	m_fIsDirty = true;
	m_fIsInitialized = true;	// das einzige, was InitNew machen soll, wird hier erledigt
	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::get_Type (BSTR*pVal)
{
	CHECKOUTPOINTER(pVal);

CComBSTR bstr (g_cbLineGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSLineGeometry::IsDirty (void)
{
ObjectLock l(this);

	if (m_fIsDirty)
		return S_OK;

	// Origin testen
	HRESULT	hRes = S_FALSE;

	COM_TRY {
	WPersistStream	str1(m_ptStart);		// throws hr
	WPersistStream	str2(m_ptEnd);		// throws hr

		hRes = str1 -> IsDirty();
		if (S_FALSE == hRes)
			hRes = str2 -> IsDirty();

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);
	COM_TRY {
	W_DGMPoint newVal;

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm , IID__DGMPoint , newVal.ppv()));
		PutStart (newVal , true);

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm , IID__DGMPoint , newVal.ppv()));
		PutEnd (newVal , true);

	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::Save (LPSTREAM pStm , BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);

bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty());

	COM_TRY {
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_ptStart) , pStm));
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_ptEnd) , pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::GetSizeMax (ULARGE_INTEGER*pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(! m_fIsInitialized , STREAM_E_OBJECTNOTINITIALIZED);

	pcbSize -> QuadPart = 0;
	COM_TRY {
	WPersistStream PStrm1 (m_ptStart);		// throws hr
	WPersistStream PStrm2 (m_ptEnd);		// throws hr
	ULARGE_INTEGER temp;

		PStrm1 -> GetSizeMax (pcbSize);
		temp.QuadPart = pcbSize -> QuadPart;
		PStrm2 -> GetSizeMax (pcbSize);
		pcbSize -> QuadPart += temp.QuadPart;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSLineGeometry::InitNew (void)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);
	COM_TRY	{
	W_DGMPoint ptStart(CLSID_TRiASCSPoint);	// throws hr
	W_DGMPoint ptEnd(CLSID_TRiASCSPoint);	// throws hr

		THROW_FAILED_HRESULT(WPersistStreamInit(ptStart) -> InitNew());
		PutStart(ptStart , true);

		THROW_FAILED_HRESULT(WPersistStreamInit(ptEnd) -> InitNew());
		PutEnd(ptEnd , true);
	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSLineGeometry::Load (void*pvMem , ULONG cbSize)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);
	COM_TRY	{
	W_DGMPoint ptStart(CLSID_TRiASCSPoint);	// throws hr
	W_DGMPoint ptEnd(CLSID_TRiASCSPoint);	// throws hr

		ULONG ulSize = 0;
		WPersistMemory psStart (ptStart);

		THROW_FAILED_HRESULT(psStart -> Load (pvMem , cbSize));
		THROW_FAILED_HRESULT(psStart -> GetSizeMax (& ulSize));
		pvMem = (BYTE *)pvMem + ulSize;

		WPersistMemory psEnd (ptEnd);

		THROW_FAILED_HRESULT(psEnd -> Load (pvMem , cbSize));

		PutStart(ptStart , true);
		PutEnd(ptEnd , true);

		m_fIsDirty = false;
		m_fIsInitialized = true;
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::Save (void*pvMem , BOOL fClearDirty , ULONG cbSize)
{
ObjectLock l(this);

	COM_TRY	{
	ULONG ulSize = 0;
	WPersistMemory psStart (m_ptStart);

		THROW_FAILED_HRESULT(psStart -> Save (pvMem , fClearDirty , cbSize));
		THROW_FAILED_HRESULT(psStart -> GetSizeMax (&ulSize));
		pvMem = (BYTE *)pvMem + ulSize;
		THROW_FAILED_HRESULT(WPersistMemory(m_ptEnd) -> Save (pvMem, fClearDirty, cbSize));
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::GetSizeMax (ULONG*pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 0;
	COM_TRY	{
	ULONG ulSize = 0;

		THROW_FAILED_HRESULT(WPersistMemory(m_ptStart) -> GetSizeMax (&ulSize));
		*pcbSize = ulSize;
		THROW_FAILED_HRESULT(WPersistMemory(m_ptEnd) -> GetSizeMax (&ulSize));
		*pcbSize += ulSize;
	} COM_CATCH;
	return S_OK;
}

// ITRiASCSGeometrieProperties
STDMETHODIMP CTRiASCSLineGeometry::get_Type(/*[out, retval]*/ GEOMETRYTYPE*pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = GEOMETRYTYPE_Line;
	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::get_Envelope(/*[out, retval]*/ITRiASSimpleRectangle** Rect)
{
	CHECKOUTPOINTER(Rect);

ObjectLock l(this);

	ERROR_EXPR_TRUE(! m_fIsInitialized , STREAM_E_OBJECTNOTINITIALIZED);

	if (NULL == m_ptEnd)
		return E_UNEXPECTED;

	if (NULL == m_ptStart)
		return E_UNEXPECTED;

	// Zeigerarbeit

	*Rect = NULL;

	COM_TRY	{
	CSCOORD minPt , maxPt , currPoint;
	
		minPt.X = minPt.Y = minPt.Z = DBL_MAX;
		maxPt.X = maxPt.Y = maxPt.Z = - DBL_MAX;

		m_ptEnd -> GetPoint(& currPoint.X);
		minPt.X = min(currPoint.X , minPt.X);
		minPt.Y = min(currPoint.Y , minPt.Y);
		minPt.Z = min(currPoint.Z , minPt.Z);
		maxPt.X = max(currPoint.X , maxPt.X);
		maxPt.Y = max(currPoint.Y , maxPt.Y);
		maxPt.Z = max(currPoint.Z , maxPt.Z);

		m_ptStart -> GetPoint(& currPoint.X);
		minPt.X = min(currPoint.X , minPt.X);
		minPt.Y = min(currPoint.Y , minPt.Y);
		minPt.Z = min(currPoint.Z , minPt.Z);
		maxPt.X = max(currPoint.X , maxPt.X);
		maxPt.Y = max(currPoint.Y , maxPt.Y);
		maxPt.Z = max(currPoint.Z , maxPt.Z);

	CCSRectangleGeometry mbr(minPt.X , minPt.Y , maxPt.X - minPt.X , maxPt.Y - minPt.Y);

		// endlich fertig
		*Rect = mbr.detach();	// Rect ist jetzt Owner des Rechteckes
	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASCSLineGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSLineGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASTransformGeometry

//inline void SetGreater (double &rx, double &ry) { if (ry > rx) rx = ry; }	// x = max (x,y)
//inline void SetSmaller (double &rx, double &ry) { if (ry < rx) rx = ry; }	// x = min (x,y)

HRESULT CTRiASCSLineGeometry::Transform (struct CSID csGUID , ITRiASCSTransform*pCSTransform)
{
	CHECKINPOINTER(pCSTransform);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY	{
		ERROR_FAILED_HRESULT(WTRiASTransformGeometry(m_ptStart) -> Transform(csGUID, pCSTransform) , LINE_E_CANNOTTRANSFORMGEOMETRY);
		ERROR_FAILED_HRESULT(WTRiASTransformGeometry(m_ptEnd) -> Transform(csGUID, pCSTransform) , LINE_E_CANNOTTRANSFORMGEOMETRY);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::TransformInverse (struct CSID csGUID , ITRiASCSTransform*pCSTransform)
{
	CHECKINPOINTER(pCSTransform);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY	{
		ERROR_FAILED_HRESULT(WTRiASTransformGeometry(m_ptStart) -> TransformInverse(csGUID, pCSTransform) , LINE_E_CANNOTTRANSFORMGEOMETRY);
		ERROR_FAILED_HRESULT(WTRiASTransformGeometry(m_ptEnd) -> TransformInverse(csGUID, pCSTransform) , LINE_E_CANNOTTRANSFORMGEOMETRY);
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSLineGeometry::Clone (IDispatch** ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSLineGeometry>*pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject < CTRiASCSLineGeometry > ::CreateInstance (& pNew));
		pNew -> AddRef();		// pending AddRef

	// Anfangs- und Endpunkt erzeugen und initialisieren
	WDispatch disp;

		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_ptStart) -> Clone(disp.ppi()));
		pNew -> PutStart(W_DGMPoint(disp) , true);
		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_ptEnd) -> Clone(disp.ppi()));
		pNew -> PutEnd(W_DGMPoint(disp) , true);

	// sonstige Werte kopieren
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast < _DGMGeometry*> (pNew);

	} COM_CATCH_OP (
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSLineGeometry::GetSizeMaxWkb(ULONG *pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = sizeof(BYTE)+sizeof(UINT)+sizeof(UINT)+4*sizeof(double);
	return S_OK;
}

HRESULT CTRiASCSLineGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSLineGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	SaveAndAdvance(pvMem, (BYTE)wkbNDR);
	SaveAndAdvance(pvMem, (UINT)wkbLineString);
	SaveAndAdvance(pvMem, (UINT)2);

	COM_TRY {
	double dCoord[3];

		THROW_FAILED_HRESULT(W_DGMPoint(m_ptStart) -> GetPoint(dCoord));
		SaveAndAdvance(pvMem, dCoord[0]);
		SaveAndAdvance(pvMem, dCoord[1]);

		THROW_FAILED_HRESULT(W_DGMPoint(m_ptEnd) -> GetPoint(dCoord));
		SaveAndAdvance(pvMem, dCoord[0]);
		SaveAndAdvance(pvMem, dCoord[1]);

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSLineGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSLineGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);

	COM_TRY {
	CComBSTR bstrWKT(L"LINESTRING(");
	double dCoord[3];

		THROW_FAILED_HRESULT(W_DGMPoint(m_ptStart) -> GetPoint(dCoord));
		AppendPoint(bstrWKT, dCoord[0], dCoord[1]);

		THROW_FAILED_HRESULT(W_DGMPoint(m_ptEnd) -> GetPoint(dCoord));
		AppendPoint(bstrWKT, dCoord[0], dCoord[1], false);

		bstrWKT.Append(L")");
		*pbstrWKT = bstrWKT.Detach();

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


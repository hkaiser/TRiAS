// @doc
// @module TRiASCSBoundaryGeometry.cpp | Implementation of the <c CTRiASCSBoundaryGeometry>
// class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSBoundaryGeometry.h"
#include "TRiASCSPolygon.h"
#include "TRiASCSStorageService.h"
#include "TDBGEO.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSBoundaryGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSBoundaryGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSBoundaryGeometry

STDMETHODIMP CTRiASCSBoundaryGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID * arr[] =
	{
		&IID__DGMBoundaryGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(* arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Exterior(IDispatch * * returnValue)
{
	CHECKOUTPOINTER(returnValue);

ObjectLock l(this);

	*returnValue = m_pExterior;
	if (*returnValue)
		(*returnValue) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::putref_Exterior(IDispatch * newValue)
{
	CHECKINPOINTER(newValue);

ObjectLock l(this);

	PutExterior (newValue, false);		// Achtung! Ohne AddRef()!!

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Holes (_DGMGeometryCollection * * returnValue)
{
	CHECKOUTPOINTER(returnValue);

ObjectLock l(this);

	*returnValue = m_pHoles;
	if (*returnValue)
		(*returnValue) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Type (BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);

CComBSTR bstr (g_cbBoundaryGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Type (GEOMETRYTYPE * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = GEOMETRYTYPE_Boundary;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSBoundaryGeometry::IsDirty (void)
{
ObjectLock l(this);

	if (m_fIsDirty)
		return S_OK;

// Exterior und Holes testen
HRESULT	hRes = S_FALSE;

	COM_TRY	{

		hRes = WPersistStream(m_pExterior) -> IsDirty();
		if (S_FALSE == hRes)
		{
			hRes = WPersistStream(m_pHoles) -> IsDirty();
		}

	} COM_CATCH;
	return hRes;
}

HRESULT CTRiASCSBoundaryGeometry::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	_ASSERTE(m_fIsOwner || NULL == m_pExterior);

WDispatch newExt;

	RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IDispatch, newExt.ppv()));
	PutExterior(newExt, true);

	RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMGeometryCollection, m_pHoles.ppv()));

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);
bool fWasDirty = false;

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	_ASSERTE(NULL != m_pExterior);

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_pExterior), pStm));
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_pHoles), pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);
ULARGE_INTEGER temp;

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	_ASSERTE(NULL != m_pExterior);

	pcbSize -> QuadPart = 0;
	COM_TRY	{
		THROW_FAILED_HRESULT(WPersistStream(m_pExterior) -> GetSizeMax (pcbSize));
		THROW_FAILED_HRESULT(WPersistStream(m_pHoles) -> GetSizeMax (&temp));
		pcbSize -> QuadPart += temp.QuadPart;
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSBoundaryGeometry::InitNew (void)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);
	_ASSERTE(m_fIsOwner || NULL == m_pExterior);

CComObject<CTRiASCSPolygonGeometry> *newExt = NULL;
CComObject<CTRiASCSGeometryCollection> *pHoles = NULL;

	COM_TRY	{
		// Auﬂenkontur erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPolygonGeometry>::CreateInstance(& newExt));
		newExt -> AddRef();		// pending AddRef (stabilize)
		THROW_FAILED_HRESULT(WPersistStreamInit(newExt->GetUnknown()) -> InitNew());

		// Innenkonturen erzeugen und initialisieren
		THROW_FAILED_HRESULT(CComObject<CTRiASCSGeometryCollection>::CreateInstance(& pHoles));
		pHoles -> AddRef();		// pending AddRef
		THROW_FAILED_HRESULT(WPersistStreamInit(pHoles->GetUnknown()) -> InitNew());

		PutExterior (static_cast<_DGMGeometry *>(newExt), true);
		RELEASE(newExt);
		m_pHoles = pHoles;
		RELEASE(pHoles);

	} COM_CATCH_OP (
		RELEASE(newExt);
		RELEASE(pHoles);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSBoundaryGeometry::Load (void * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);
CComObject<CTRiASCSGeometryCollection> * pHoles = NULL;

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);
	COM_TRY	{
	// Auﬂenkontur laden
	GUID guid;
	ULONG ulSize = 0;

		LoadAndAdvance(ulSize, pvMem);
		ulSize -= sizeof(GUID);
		LoadAndAdvance(guid, pvMem);

	// Auﬂenkontur
#if defined(_USE_CLASSFACTORY_CACHE)
	W_DGMPolygonGeometry newExt;	// throws hr

		THROW_FAILED_HRESULT(CClassFactoryMap::CreateInstance (guid, newExt));	// Geometrieobjekt erzeugen
#else
	W_DGMPolygonGeometry newExt(guid);	// throws hr
#endif // 	defined(_USE_CLASSFACTORY_CACHE)

		THROW_FAILED_HRESULT(WPersistMemory(newExt) -> Load (pvMem, ulSize));
		pvMem = (BYTE *)pvMem + ulSize;

	// Innenkonturen laden
		LoadAndAdvance(ulSize, pvMem);
		ulSize -= sizeof(GUID);
		LoadAndAdvance(guid, pvMem);

		THROW_FAILED_HRESULT(CComObject<CTRiASCSGeometryCollection>::CreateInstance(& pHoles));
		pHoles -> AddRef();		// pending AddRef (stibilze)
		THROW_FAILED_HRESULT(WPersistMemory(pHoles->GetUnknown()) -> Load (pvMem, ulSize));

		PutExterior (newExt, true);
		m_pHoles = pHoles;
		RELEASE(pHoles);

	} COM_CATCH_OP (
		RELEASE(pHoles);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	COM_TRY	{
	// Auﬂenkontur speichern
	GUID guid;
	ULONG ulSize = 0;
	WPersistMemory ext(m_pExterior);

		THROW_FAILED_HRESULT(ext -> GetSizeMax (& ulSize));
		SaveAndAdvance(pvMem, ulSize + sizeof(GUID));

		THROW_FAILED_HRESULT(ext -> GetClassID(& guid));
		SaveAndAdvance(pvMem, guid);

		THROW_FAILED_HRESULT(ext -> Save (pvMem, fClearDirty, ulSize));
		pvMem = (BYTE *)pvMem + ulSize;

	// Innenkonturen speichern
	WPersistMemory holes(m_pHoles);

		THROW_FAILED_HRESULT(holes -> GetSizeMax (& ulSize));
		SaveAndAdvance(pvMem, ulSize + sizeof(GUID));

		THROW_FAILED_HRESULT(holes -> GetClassID(& guid));
		SaveAndAdvance(pvMem, guid);

		THROW_FAILED_HRESULT(holes -> Save (pvMem, fClearDirty, ulSize));

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemoryGDO

HRESULT CTRiASCSBoundaryGeometry::LoadGDO(VOID * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);
CComObject<CTRiASCSGeometryCollection> *pHoles = NULL;

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);
	COM_TRY {
	// Auﬂenkontur laden
	GUID guid;
	ULONG ulSize = 0;

		LoadAndAdvance(ulSize, pvMem);
		ulSize -= sizeof(GUID);
		LoadAndAdvance(guid, pvMem);

	/////////////////////////////////////////////////////////////////////////////
	// Geomedia - GUID ummappen
		MapOfGUIDS::iterator i = g_mapGDO2TRiAS.find(guid);
		ERROR_EXPR_TRUE(g_mapGDO2TRiAS.end() == i, TGEO_E_UNKNOWN_OBJECTTYPE);
		guid = (* i).second;

	/////////////////////////////////////////////////////////////////////////////
	// Auﬂenkontur laden
	W_DGMPolygonGeometry newExt;

		COM_TRY { newExt = W_DGMPolygonGeometry(guid); } COM_CATCH;
		ERROR_EXPR_FALSE(newExt.IsValid(), TGEO_E_UNKNOWN_OBJECTTYPE);

		ERROR_FAILED_HRESULT(WPersistMemoryGDO(newExt) -> LoadGDO(pvMem, ulSize), STREAM_E_CANNOTLOADITEM);
		ERROR_FAILED_HRESULT(PutExterior(newExt, true), E_FAIL);
		pvMem = (BYTE *)pvMem + ulSize;

	/////////////////////////////////////////////////////////////////////////////
	// Innenkonturen laden
		LoadAndAdvance(ulSize, pvMem);
		ulSize -= sizeof(GUID);
		LoadAndAdvance(guid, pvMem);

	/////////////////////////////////////////////////////////////////////////////
	// Geomedia - GUID ummappen
		i = g_mapGDO2TRiAS.find(guid);
		ERROR_EXPR_TRUE(g_mapGDO2TRiAS.end() == i, TGEO_E_UNKNOWN_OBJECTTYPE);
		guid = (* i).second;

		ERROR_FAILED_HRESULT(CComObject<CTRiASCSGeometryCollection>::CreateInstance(& pHoles), STREAM_E_CANNOTLOADITEM);
		pHoles -> AddRef();			// pending AddRef
		ERROR_FAILED_HRESULT(WPersistMemoryGDO(pHoles->GetUnknown()) -> LoadGDO(pvMem, ulSize), STREAM_E_CANNOTLOADITEM);

		m_pHoles = pHoles;
		RELEASE(pHoles);

	} COM_CATCH_OP (
		RELEASE(pHoles);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::SaveGDO(VOID * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	COM_TRY {
	/////////////////////////////////////////////////////////////////////////////
	// Auﬂenkontur speichern
	GUID guid;
	ULONG ulSize = 0;
	WPersistMemoryGDO ext(m_pExterior);

		ERROR_FAILED_HRESULT(ext -> GetSizeMax(& ulSize), TGEO_E_INVALID_OBJECTSTATE);
		ERROR_FAILED_HRESULT(ext -> GetClassID(& guid), TGEO_E_INVALID_OBJECTSTATE);

	/////////////////////////////////////////////////////////////////////////////
	// Geomedia - GUID ummappen
	MapOfGUIDS::iterator i = g_mapTRiAS2GDO.find(guid);

		ERROR_EXPR_TRUE(g_mapTRiAS2GDO.end() == i, TGEO_E_UNKNOWN_OBJECTTYPE);
		guid = (*i).second;

		SaveAndAdvance(pvMem, ulSize + sizeof(GUID));
		SaveAndAdvance(pvMem, guid);
		ERROR_FAILED_HRESULT(ext -> SaveGDO(pvMem, fClearDirty, ulSize), STREAM_E_CANNOTSAVEITEM);
		pvMem = (BYTE *)pvMem + ulSize;

	/////////////////////////////////////////////////////////////////////////////
	// Innenkonturen speichern
	WPersistMemoryGDO holes(m_pHoles);

		ERROR_FAILED_HRESULT(holes -> GetSizeMax (& ulSize), TGEO_E_INVALID_OBJECTSTATE);
		ERROR_FAILED_HRESULT(holes -> GetClassID(& guid), TGEO_E_INVALID_OBJECTSTATE);

	/////////////////////////////////////////////////////////////////////////////
	// Geomedia - GUID ummappen
		i = g_mapTRiAS2GDO.find(guid);
		ERROR_EXPR_TRUE(g_mapTRiAS2GDO.end() == i, TGEO_E_UNKNOWN_OBJECTTYPE);
		guid = (* i).second;

		SaveAndAdvance(pvMem, ulSize + sizeof(GUID));
		SaveAndAdvance(pvMem, guid);
		ERROR_FAILED_HRESULT(holes -> SaveGDO (pvMem, fClearDirty, ulSize), STREAM_E_CANNOTSAVEITEM);
		if (fClearDirty)
			m_fIsDirty = false;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 0;
	COM_TRY	{
	ULONG temp = 0;

		THROW_FAILED_HRESULT(WPersistMemory(m_pExterior) -> GetSizeMax (pcbSize));
		THROW_FAILED_HRESULT(WPersistMemory(m_pHoles) -> GetSizeMax (& temp));
		*pcbSize += temp + 3 * sizeof(long) + 2 * sizeof(GUID);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Type(LONG * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = GEOMETRYTYPE_Boundary;
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_Envelope (ITRiASSimpleRectangle * * ppIRect)
{
	CHECKOUTPOINTER(ppIRect);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	if (NULL == m_pExterior)
		return E_UNEXPECTED;

	COM_TRY	{
		THROW_FAILED_HRESULT(WTRiASCSGeometryProperties(m_pExterior) -> get_Envelope(ppIRect));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSBoundaryGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

// ITRiASTransformGeometry
HRESULT CTRiASCSBoundaryGeometry::Transform(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
	COM_TRY	{
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(m_pExterior) -> Transform (csGUID, pCSTransform));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(m_pHoles) -> Transform (csGUID, pCSTransform));
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSBoundaryGeometry::TransformInverse(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
	COM_TRY	{
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(m_pExterior) -> TransformInverse (csGUID, pCSTransform));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(m_pHoles) -> TransformInverse (csGUID, pCSTransform));
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSBoundaryGeometry::Clone (IDispatch **ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

CComObject<CTRiASCSBoundaryGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSBoundaryGeometry>::CreateInstance(& pNew));
		pNew -> AddRef();	// pending AddRef (stabilize)

	// Auﬂenkontur und Innenkonturfeld kopieren
	WDispatch disp;

		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_pExterior) -> Clone(disp.ppi()));
		pNew -> PutExterior (disp, true);
		THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_pHoles) -> Clone(disp.ppi()));
		pNew -> m_pHoles = disp;

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
HRESULT CTRiASCSBoundaryGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSBoundaryGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSBoundaryGeometry::SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSBoundaryGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSBoundaryGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);
	return E_NOTIMPL;
}


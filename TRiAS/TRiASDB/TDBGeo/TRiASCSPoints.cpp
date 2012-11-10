// @doc
// @module TRiASCSPoints.cpp | Implementation of CTRiASCSPoints.

#include "StdAfx.h"
#include "TDBGeoImpl.h"

#include "MakeEnumVariant.h"
#include "TRiASCSPoints.h"
#include "TRiASCSPointEnum.h"
#include "TRiASCSRectangle.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPoints);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPoints, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASCSPoints::get_Count (long*pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = (long)clCoords.GetCount();
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::Remove (VARIANT Which)
{
	COM_TRY {
	ObjectLock l(this);
	CComVariant vWhich(Which);

		WIN_ERROR_NOTSUCCESS(vWhich.ChangeType(VT_UI4), TGEO_E_COERCE);

	ULONG nIndex = V_UI4(& vWhich);

		ERROR_EXPR_TRUE(0 == nIndex, TGEO_E_INDEXISZERO);
		nIndex -= 1;		// in C wird von 0 aus gezählt...

	HRESULT	hr;

		ERROR_FAILED_HRESULT(hr = clCoords.Remove(nIndex), hr);
		m_fIsDirty = true;
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::Add (_DGMPoint*pIPoint, VARIANT Which)
{
	CHECKINPOINTER(pIPoint);
	COM_TRY {
	ObjectLock l(this);
	ULONG nIndex = 0;

		ERROR_EXPR_FALSE(V_ISINTEGER(& Which) || V_ISEMPTY(& Which) || V_ISERROR(& Which), TGEO_E_COERCE);
		if(V_ISINTEGER(& Which)) {
		// vorgegebener Index
		CComVariant vWhich(Which);

			WIN_ERROR_NOTSUCCESS(vWhich.ChangeType(VT_UI4), TGEO_E_COERCE);
			nIndex = V_UI4(& vWhich);
			ERROR_EXPR_TRUE(0 == nIndex, TGEO_E_INDEXISZERO);
		} 
		else if(V_ISEMPTY(& Which) || V_ISERROR(& Which)) {
			// einfach anhängen
			nIndex = 0;						// wird zu CCoordField::Add( -1...) ==>
		} 
		else {
			MAKE_ERROR(TGEO_E_INTERNAL);	// das sollte eigentlich nicht passieren
		}
		nIndex -= 1;		// in C wird von 0 aus gezählt...

	CSCOORD c;
	HRESULT	hr;
	
		ERROR_FAILED_HRESULT(W_DGMPoint(pIPoint) -> GetPoint((double *) & c.X), TGEO_E_ACCESSELEMENT);	// Rohdaten abholen
		ERROR_FAILED_HRESULT(hr = clCoords.Add(nIndex, &c), hr);
		m_fIsDirty = true;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::get_NewEnum (IUnknown** ppIEnum)
{
	CHECKOUTPOINTER(ppIEnum);

// Erzeugen
ObjectLock l(this);
CComObject<CTRiASCSPointEnum >*pPE  = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASCSPointEnum>::CreateInstance(&pPE));	// der wird weitergereicht

// Initialisieren
	pPE -> Init(this);
	pPE -> AddRef();

// Ergebnisse
	*ppIEnum = pPE;	// der geht immer
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::Item (VARIANT Which, _DGMPoint** ppIPoint)
{
	CHECKOUTPOINTER(ppIPoint);
	COM_TRY	{
	ObjectLock l(this);
	ULONG nIndex = 0;
		
		ERROR_EXPR_FALSE(V_ISINTEGER(&Which), TGEO_E_COERCE);
		if(V_ISINTEGER(& Which)) {
		// vorgegebener Index
		CComVariant vWhich(Which);
		
			WIN_ERROR_NOTSUCCESS(vWhich.ChangeType(VT_UI4), TGEO_E_COERCE);
			nIndex = V_UI4(& vWhich);
			ERROR_EXPR_TRUE(0 == nIndex, TGEO_E_INDEXISZERO);
		} 
		else {
			MAKE_ERROR(TGEO_E_INTERNAL);	// das sollte eigentlich nicht passieren
		}
		nIndex -= 1;

	CSCOORD *pc;
	HRESULT	hr;

		ERROR_FAILED_HRESULT(hr = clCoords.Get(nIndex, &pc), hr);						// alle anderen Fehler so rausschmeißen

	// einen Punkt mit Zugriffsinformationen erzeugen
	CComObject<CTRiASCSPointInCol> *pPt;
	
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPointInCol>::CreateInstance(& pPt));

	W_DGMPoint wPoint(pPt);

		pPt -> SetCollectionMember (static_cast<_DGMPoints *>(this), nIndex);
		wPoint -> AddRef();		// Adding new referenz
		*ppIPoint = wPoint;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// offensichtlich interne Zugriffsmethoden, um Effizienz zu erhöhen
// Aus diesen Gründen wird auch der Enumerator m_Enum direkt verwendet.
STDMETHODIMP CTRiASCSPoints::GetPoint (long lIndex, double *pCoords)
{
	CHECKINPOINTER(pCoords);
	ERROR_EXPR_TRUE(0 == lIndex, TGEO_E_INDEXISZERO);

ObjectLock l(this);
CSCOORD	*c;
HRESULT	hr;

	ERROR_FAILED_HRESULT(hr = clCoords.Get ((ULONG)(lIndex-1), &c), hr);
	*reinterpret_cast<CSCOORD *>(pCoords) = *c;
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::GetPoints (ULONG lIndex, ULONG lCnt, double *pCoords)
{
	CHECKINPOINTER(pCoords);
	ERROR_EXPR_TRUE(0 == lIndex, TGEO_E_INDEXISZERO);
	ERROR_EXPR_TRUE(lIndex + lCnt -1 > clCoords.GetCount(), POINTS_E_INDEXTOLARGE_R);

ObjectLock l(this);
CSCOORD	*c;
HRESULT	hr;

	ERROR_FAILED_HRESULT(hr = clCoords.Get ((ULONG)(lIndex-1), &c), hr);
	memcpy (pCoords, c, lCnt*sizeof(CSCOORD));
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::SetPoint (long lIndex, double *pCoords)
{
	CHECKINPOINTER(pCoords);
	COM_TRY	{
		ERROR_EXPR_TRUE(0 == lIndex, TGEO_E_INDEXISZERO);

	ObjectLock l(this);
	CSCOORD	*c;
	HRESULT hr = clCoords.Get ((ULONG)(lIndex -1), &c);

		if (FAILED(hr))	{
			if (lIndex -1 == clCoords.Count())	{
			// einen Punkt hinzufügen
				ERROR_FAILED_HRESULT(hr = clCoords.Add ((ULONG)-1L, reinterpret_cast<CSCOORD *>(pCoords)), hr);
				m_fIsDirty = true;	// externer Datenzugriff -> Daten sind jetzt dirty
				return S_OK;
			} else
				ERROR_FAILED_HRESULT(hr, hr);
		}

	// Koordinaten eines exitierenden Punktes austauschen
		*c = *reinterpret_cast<CSCOORD *>(pCoords);	// gibts hier Exceptions ???
		m_fIsDirty = true;							// externer Datenzugriff -> Daten sind jetzt dirty
	
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSPoints::IsDirty()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

HRESULT CTRiASCSPoints::Load(LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

ObjectLock l(this);

	RETURN_FAILED_HRESULT(clCoords.Load(pStm));
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPoints::Save(LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

bool fWasDirty = false;

	if (! fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

ObjectLock l(this);

	RETURN_FAILED_HRESULT(clCoords.Save(pStm));
	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;
	return S_OK;
}

HRESULT CTRiASCSPoints::GetSizeMax(ULARGE_INTEGER*pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	pcbSize -> QuadPart = clCoords.GetCount()*sizeof(CSCOORD) + sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSPoints::InitNew()
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSPoints::Load (void*pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

ObjectLock l(this);

	RETURN_FAILED_HRESULT(clCoords.Load(pvMem));
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSPoints::Save (void*pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	RETURN_FAILED_HRESULT(clCoords.Save(pvMem));
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSPoints::GetSizeMax (ULONG*pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	*pcbSize = clCoords.GetCount()*sizeof(CSCOORD) + sizeof(long);
	return S_OK;
}

STDMETHODIMP CTRiASCSPoints::get_Envelope(/*[out, retval]*/ ITRiASSimpleRectangle** Rect)
{
ObjectLock l(this);
CSCOORD min, max;	// Puffer

	RETURN_FAILED_HRESULT(clCoords.GetEnvelope(min, max));
	RETURN_FAILED_HRESULT(CreateRect(min, max, Rect));

	return S_OK;
}

HRESULT CTRiASCSPoints::CreateRect(CSCOORD & org, CSCOORD & sec, ITRiASSimpleRectangle** pRect)
{
	CHECKOUTPOINTER(pRect);
	COM_TRY	{
	CCSRectangleGeometry mbr(org.X, org.Y, sec.X, sec.Y, 1);
	
		*pRect = mbr.detach();	// Rect ist jetzt Owner des Rechteckes
	} COM_CATCH;
	return S_OK;
}

//ITRiASTransformGeometry
HRESULT CTRiASCSPoints::Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform*pCSTransform)
{
	CHECKINPOINTER(pCSTransform);
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst(pCSTransform);
	CSCOORD	*pCoords = NULL;
	
		clCoords.Get(0, & pCoords);
		ERROR_EXPR_TRUE(NULL == pCoords, E_POINTER);
		return cst -> Transform(csGUID, clCoords.GetCount(), pCoords, pCoords);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSPoints::TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform*pCSTransform)
{
	CHECKINPOINTER(pCSTransform);
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst(pCSTransform);
	CSCOORD	*pCoords = NULL;
	
		clCoords.Get(0, &pCoords);
		ERROR_EXPR_TRUE(NULL == pCoords, E_POINTER);
		return cst -> TransformInverse(csGUID, clCoords.GetCount(), pCoords, pCoords);
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSPoints::Clone (IDispatch** ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

CComObject<CTRiASCSPoints> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPoints>::CreateInstance(& pNew));
		pNew -> AddRef();	// pending AddRef (stabilize)

	// Koordinaten kopieren
	ObjectLock l(this);
	CSCOORD *pSrc = NULL;

		THROW_FAILED_HRESULT(clCoords.Get (0, &pSrc));
		THROW_FAILED_HRESULT(pNew -> clCoords.Add (0, pSrc, clCoords.Count()));	// Koordinaten kopieren

	// jetzt alles fertig initialisiert
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMPoints*> (pNew);

	} COM_CATCH_OP(
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSPoints::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);

ObjectLock l(this);

	*pulSize = clCoords.GetCount()*2*sizeof(double);
	return S_OK;
}

HRESULT CTRiASCSPoints::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPoints::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);
bool fWasDirty = false;

	if (! fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;


	RETURN_FAILED_HRESULT(clCoords.SaveWkb(pvMem));
	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSPoints::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSPoints::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);
bool fWasDirty = false;

	if (! fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	RETURN_FAILED_HRESULT(clCoords.SaveWkt(pbstrWKT));
	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;
	return S_OK;
}


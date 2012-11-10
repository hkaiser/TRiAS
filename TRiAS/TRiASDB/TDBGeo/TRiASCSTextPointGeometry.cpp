// TRiASCSTextPointGeometry.cpp : Implementation of CTRiASTextPointGeometry

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPoint.h"
#include "TRiASCSVector.h"
#include "TRiASCSTextPointGeometry.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSTextPointGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSTextPointGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSTextPointGeometry

STDMETHODIMP CTRiASCSTextPointGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID * arr[] =
	{
		&IID__DGMTextPointGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i ++)
	{
		if (InlineIsEqualGUID(* arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

// IPersistStream
HRESULT CTRiASCSTextPointGeometry::IsDirty()
{
ObjectLock l(this);

	if (m_fIsDirty)
		return S_OK;

// Origin und Normal testen
WPersistStream PS;

	if (SUCCEEDED(m_vecNormal -> QueryInterface (PS.ppi())) && S_OK == PS -> IsDirty())
		return S_OK;

	return S_FALSE;
}

HRESULT CTRiASCSTextPointGeometry::Load(LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	COM_TRY	{
	W_DGMPoint newVal;

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMPoint, newVal.ppv()));
		THROW_FAILED_HRESULT(newVal -> get_X (&m_ptOrig.X));
		THROW_FAILED_HRESULT(newVal -> get_Y (&m_ptOrig.Y));
		THROW_FAILED_HRESULT(newVal -> get_Z (&m_ptOrig.Z));

	W_DGMVector newVec;

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMVector, newVec.ppv()));
		PutNormal(newVec, true);

		THROW_FAILED_HRESULT(LoadItem (pStm, m_dRotation));
		THROW_FAILED_HRESULT(LoadItem (pStm, m_iFormat));
		THROW_FAILED_HRESULT(LoadItem (pStm, m_lAlignment));
		THROW_FAILED_HRESULT(m_bstrText.ReadFromStream (pStm));

	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::Save(LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

ObjectLock l(this);
bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty());

	COM_TRY	{
	W_DGMPoint ptOrig;

		THROW_FAILED_HRESULT(get_Origin (ptOrig.ppi()));
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(ptOrig), pStm));

		if (NULL == m_vecNormal) {
		W_DGMVector vec;

			THROW_FAILED_HRESULT(get_Normal (vec.ppi()));
			_ASSERTE(NULL != m_vecNormal);
		}
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_vecNormal), pStm));

		THROW_FAILED_HRESULT(SaveItem (pStm, m_dRotation));
		THROW_FAILED_HRESULT(SaveItem (pStm, m_iFormat));
		THROW_FAILED_HRESULT(SaveItem (pStm, m_lAlignment));
		THROW_FAILED_HRESULT(m_bstrText.WriteToStream (pStm));
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;		// !fClearDirty ==> Kapsel erbt Dirty-Flag ggf. von Member

	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::GetSizeMax(ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	pcbSize -> QuadPart = 2 * SIZEOF_POINT + sizeof(double) + 2 * sizeof(long) + LenForStream(m_bstrText);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSTextPointGeometry::InitNew()
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	m_dRotation = 0.0;
	m_lAlignment = 0;
	m_iFormat = 0;

	m_vecNormal = NULL;
	m_fIsOwnerNormal = false;

	memset (&m_ptOrig, 0, sizeof(CSCOORD));

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// _DGMGeometry
STDMETHODIMP CTRiASCSTextPointGeometry::get_Type (BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);
	
CComBSTR bstr (g_cbTextPointGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_Type (GEOMETRYTYPE * pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = GEOMETRYTYPE_Text;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_Envelope (ITRiASSimpleRectangle **Rect)
{
	CHECKOUTPOINTER(Rect);
	ERROR_EXPR_TRUE(! m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	*Rect = NULL;
	COM_TRY	{
	ObjectLock l(this);
	CCSRectangleGeometry mbr (m_ptOrig.X, m_ptOrig.Y, 0, 0);

		*Rect = mbr.detach();	// Rect ist jetzt Owner des Rechteckes
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSTextPointGeometry::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// _DGMPointGeometry
STDMETHODIMP CTRiASCSTextPointGeometry::get_Origin(_DGMPoint **pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

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

STDMETHODIMP CTRiASCSTextPointGeometry::putref_Origin(_DGMPoint * newVal)
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

/////////////////////////////////////////////////////////////////////////////
// _DGMTextPointGeometry
STDMETHODIMP CTRiASCSTextPointGeometry::get_Rotation(double * returnValue)
{
	CHECKOUTPOINTER(returnValue);

ObjectLock l(this);

	*returnValue = m_dRotation;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::put_Rotation(double newValue)
{
ObjectLock l(this);

	m_dRotation = newValue;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_Alignment(long * returnValue)
{
	CHECKOUTPOINTER(returnValue);

ObjectLock l(this);

	*returnValue = m_lAlignment;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::put_Alignment(long newValue)
{
// Alignment-Konstanten:
//	gmaCenterCenter	0	Der Ursprungspunkt befindet sich in der Mitte
//						des Rich-Texts.
//	gmaCenterLeft	1	Der Rich-Text ist vertikal und links vom
//						Ursprungspunkt zentriert.
//	gmaCenterRight	2	Der Rich-Text ist vertikal und rechts vom
//						Ursprungspunkt zentriert.
//	gmaTopCenter	4	Der Rich-Text ist horizontal und oberhalb des
//						Ursprungspunkts zentriert.
//	gmaTopLeft		5	Der Rich-Text befindet sich links oberhalb des
//						Ursprungspunkts.
//	gmaTopRight		6	Der Rich-Text befindet sich rechts oberhalb des
//						Ursprungspunkts.
//	gmaBottomCenter	8	Der Rich-Text ist horizontal und unterhalb des
//						Ursprungspunkts zentriert.
//	gmaBottomLeft	9	Der Rich-Text befindet sich links unterhalb des
//						Ursprungspunkts.
//	gmaBottomRight	10	Der Rich-Text befindet sich rechts unterhalb des
//						Ursprungspunkts.
	if (newValue < 0L || newValue > 10L)
		return E_INVALIDARG;
	if (newValue == 3L || newValue == 7L)
		return E_INVALIDARG;

ObjectLock l(this);

	m_lAlignment = newValue;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_RichText(BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	if (0 != m_iFormat)
		return E_UNEXPECTED;

CComBSTR bstr (m_bstrText);

	if (!bstr)
		return E_OUTOFMEMORY;

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::put_RichText(BSTR text)
{
ObjectLock l(this);

	if (NULL == text)
		m_bstrText = g_cbNil;
	else
		m_bstrText = text;

	m_iFormat = 0;		// gmfRichText
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_text(BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	if (1 != m_iFormat)
		return E_UNEXPECTED;

CComBSTR bstr (m_bstrText);

	if (!bstr)
		return E_OUTOFMEMORY;

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::put_text(BSTR text)
{
ObjectLock l(this);

	if (NULL == text)
		m_bstrText = g_cbNil;
	else
		m_bstrText = text;

	m_iFormat = 1;		// gmfUnformatted
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_Format(short * returnValue)
{
	CHECKOUTPOINTER(returnValue);

ObjectLock l(this);

	*returnValue = m_iFormat;
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::get_Normal (_DGMVector **pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	if (NULL == m_vecNormal) {
	CComObject<CTRiASCSVector> *pVec = NULL;

		COM_TRY {
			THROW_FAILED_HRESULT(CComObject<CTRiASCSVector>::CreateInstance(&pVec));
			pVec -> AddRef();			// pending AddRef
			PutNormal (pVec, true);
			RELEASE(pVec);
		} COM_CATCH_OP(
			RELEASE(pVec);
		);
	}

	*pVal = m_vecNormal;
	if (*pVal)
		(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCSTextPointGeometry::putref_Normal (_DGMVector * newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutNormal(newVal, false);
	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSTextPointGeometry::Load (void * pvMem, ULONG cbSize)
{
	return DoLoad(pvMem, cbSize, false);
}

HRESULT CTRiASCSTextPointGeometry::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	return DoSave(pvMem, fClearDirty, cbSize, false);
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemoryGDO
HRESULT CTRiASCSTextPointGeometry::LoadGDO (void * pvMem, ULONG cbSize)
{
	return DoLoad(pvMem, cbSize, true);
}

HRESULT CTRiASCSTextPointGeometry::SaveGDO (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	return DoSave(pvMem, fClearDirty, cbSize, true);
}

/////////////////////////////////////////////////////////////////////////////
// das eigentliche Laden
HRESULT CTRiASCSTextPointGeometry::DoLoad (void * pvMem, ULONG cbSize, bool bLoadGDO)
{
ObjectLock l(this);

	CHECKINPOINTER(pvMem);
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

CComObject<CTRiASCSVector> *pVec = NULL;

	COM_TRY	{
	// Bezugspunkt initialisieren
		::LoadAndAdvance (m_ptOrig, pvMem);
		::LoadAndAdvance (m_dRotation, pvMem);

	// Normalenvektor
	CSCOORD c;

		::LoadAndAdvance (c, pvMem);

		if (c.X != 0.0 || c.Y != 0.0 || c.Z != 1.0) {
			THROW_FAILED_HRESULT(CComObject<CTRiASCSVector>::CreateInstance(&pVec));
			pVec -> AddRef();	// pending AddRef
			PutNormal (pVec, true);
			RELEASE(pVec);

			THROW_FAILED_HRESULT(pVec -> put_I (c.X));
			THROW_FAILED_HRESULT(pVec -> put_J (c.Y));
			THROW_FAILED_HRESULT(pVec -> put_K (c.Z));
		}

	// sonstige Attribute einlesen
	unsigned char PropertiesBytes[4] = {0, 0, 0, 0};

		_ASSERTE(sizeof(long) == sizeof(PropertiesBytes));
		LoadAndAdvance (*(long *)&PropertiesBytes, pvMem);
		m_lAlignment = PropertiesBytes[3];		// Alignment
		m_iFormat = PropertiesBytes[2];			// Format

	long iLen = 0L;

		LoadAndAdvance (iLen, pvMem);
		m_bstrText = CComBSTR (iLen / sizeof(OLECHAR) + 1, (LPCOLESTR)NULL);
		LoadAndAdvance (m_bstrText.m_str, pvMem, iLen);

	} COM_CATCH_OP (
		RELEASE(pVec);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::DoSave (void * pvMem, BOOL fClearDirty, ULONG cbSize, bool bSaveGDO)
{
ObjectLock l(this);

	CHECKINPOINTER(pvMem);

	COM_TRY	{
	// Origin
		::SaveAndAdvance (pvMem, m_ptOrig);
		::SaveAndAdvance (pvMem, m_dRotation);

	// Normale
		if (NULL != m_vecNormal) {
			THROW_FAILED_HRESULT(WPersistMemory(m_vecNormal) -> Save (pvMem, fClearDirty, SIZEOF_POINT));
			pvMem = (BYTE *)pvMem + SIZEOF_POINT;
		}
		else {
			::SaveAndAdvance (pvMem, 0.0);
			::SaveAndAdvance (pvMem, 0.0);
			::SaveAndAdvance (pvMem, 1.0);
		}

	// sonstiges
	unsigned char PropertiesBytes[4] = {0, 0, 0, 0};

		PropertiesBytes[3] = (unsigned char)m_lAlignment;		// Alignment
		PropertiesBytes[2] = (unsigned char)m_iFormat;			// Format

		_ASSERTE(sizeof(long) == sizeof(PropertiesBytes));
		::SaveAndAdvance (pvMem, *(long *)&PropertiesBytes);

	int iLen = (m_bstrText.Length() + 1) * sizeof(OLECHAR);

		::SaveAndAdvance (pvMem, iLen);
		::SaveAndAdvance (pvMem, m_bstrText.m_str, iLen);

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 2*SIZEOF_POINT + sizeof(double) + 2 * sizeof(long) + LenForStream(m_bstrText);
	return S_OK;
}

// ITRiASTransformGeometry
HRESULT CTRiASCSTextPointGeometry::Transform(struct CSID csGUID, ITRiASCSTransform *pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> Transform (csGUID, 1, &m_ptOrig, &m_ptOrig));
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::TransformInverse(struct CSID csGUID, ITRiASCSTransform *pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> TransformInverse (csGUID, 1, &m_ptOrig, &m_ptOrig));
	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSTextPointGeometry::Clone (IDispatch **ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSTextPointGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSTextPointGeometry>::CreateInstance (&pNew));
		pNew -> AddRef();	// pending AddRef

	// Bezugspunkt und Vector (Normale) erzeugen und initialisieren
		if (NULL != m_vecNormal) {
		WDispatch disp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_vecNormal) -> Clone (disp.ppi()));
			pNew -> PutNormal (W_DGMVector(disp), true);
		}
		pNew -> m_ptOrig = m_ptOrig;

	// sonstige Werte kopieren
		pNew -> m_dRotation = m_dRotation;
		pNew -> m_lAlignment = m_lAlignment;
		pNew -> m_bstrText = m_bstrText;
		pNew -> m_iFormat = m_iFormat;

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
HRESULT CTRiASCSTextPointGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);
	*pulSize = 2*sizeof(double) + sizeof(UINT) + sizeof(BYTE);
	return S_OK;
}

HRESULT CTRiASCSTextPointGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSTextPointGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
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
HRESULT CTRiASCSTextPointGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSTextPointGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
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


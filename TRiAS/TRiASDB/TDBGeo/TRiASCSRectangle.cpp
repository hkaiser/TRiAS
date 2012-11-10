// @doc
// @module TRiASCSRectangle.cpp | Implementation of the <c CTRiASCSRectangleGeometry>
// class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Atl/atlbasex.h>
#include <Com/VariantHelpers.h>		// V_ISDISPATCH etc. 

#include "TDBGeoImpl.h"

#include "TRiASCSPoint.h"
#include "TRiASCSVector.h"
#include "TRiASCSRectangle.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSRectangleGeometry);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// LocaleID für English
#define LOCALE_ENGLISH (MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT))

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSRectangleGeometry, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSRectangle

STDMETHODIMP CTRiASCSRectangleGeometry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID*arr[] =
	{
		&IID_ITRiASSimpleRectangle,
		&IID__DGMRectangleGeometry,
		&IID__DGMGeometry,
		&IID_ITRiASCloneGeometry,
	};
	for (int i = 0;i<sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASCSRectangleGeometry::get_Width (double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	*pVal = m_pt2nd.X - m_ptOrig.X;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_Width (double newVal)
{
ObjectLock l(this);

	m_pt2nd.X = m_ptOrig.X + newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Height (double*pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	*pVal = m_pt2nd.Y - m_ptOrig.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_Height (double newVal)
{
ObjectLock l(this);

	m_pt2nd.Y = m_ptOrig.Y + newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Rotation (double*pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	*pVal = m_dRotation;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_Rotation (double newVal)
{
ObjectLock l(this);

	m_dRotation = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Origin (_DGMPoint **pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

CComObject<CTRiASCSPointInCsCoordTarget> *pPt = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASCSPointInCsCoordTarget>::CreateInstance(&pPt));
		pPt -> AddRef();		// pending AddRef

		THROW_FAILED_HRESULT(pPt -> SetCollectionMember (static_cast<_DGMRectangleGeometry *>(this), &m_ptOrig));
		*pVal = pPt;

	} COM_CATCH_OP(
		RELEASE(pPt);
	);
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::putref_Origin (_DGMPoint *newVal)
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

STDMETHODIMP CTRiASCSRectangleGeometry::get_Normal (_DGMVector **pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

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

STDMETHODIMP CTRiASCSRectangleGeometry::putref_Normal (_DGMVector *newVal)
{
	CHECKINPOINTER(newVal);

ObjectLock l(this);

	PutNormal(newVal, false);

	m_fIsDirty = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Type (BSTR*pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

CComBSTR bstr (g_cbRectangleGeometry);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Type (GEOMETRYTYPE*pVal)
{
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	*pVal = GEOMETRYTYPE_Area;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_Envelope(ITRiASSimpleRectangle **ppIRect)
{
	CHECKOUTPOINTER(ppIRect);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	COM_TRY	{
	// explizite Berechnung eines Hüllrechteckes anstatt this-Pointer
	// 1. da Hüllrechteck achsenparallel liegt
	// 2. wenn einfach Referenz auf sich selbst übergeben würde,
	//		würde dies ein anderes Verhalten als sonst üblich darstellen
	// (Änderungen an this würde den Hüllcontainer verändern und umgedreht)
	CCSRectangleGeometry mbr (m_ptOrig.X, m_ptOrig.Y, m_pt2nd.X, m_pt2nd.Y, 1);

		*ppIRect = mbr.detach();	// Rect ist jetzt Owner des Rechteckes

	} COM_CATCH;
	return S_OK;
}

namespace {
	HRESULT AppendToBSTR (CComBSTR &rbstr, double dValue, bool fAppendSpace = true)
	{
	CComVariantEx vVal (dValue, LOCALE_ENGLISH);

		RETURN_FAILED_HRESULT(vVal.ChangeTypeEx (VT_BSTR));
		RETURN_FAILED_HRESULT(rbstr.Append (V_BSTR(&vVal)));
		if (fAppendSpace) 
		{
			RETURN_FAILED_HRESULT(rbstr.Append (g_cbSpace));
		}
		return S_OK;
	}

	bool TestAndAdvance (LPOLESTR &rpoleCurr, OLECHAR coleToTest)
	{
		_ASSERTE(coleToTest == *rpoleCurr);
		if (coleToTest == *rpoleCurr) {
			++rpoleCurr;
			return true;
		}
		return false;
	}

	double GetNextDouble (LPOLESTR poleCurr, LPOLESTR *poleNext, OLECHAR cEndChar)
	{
	// das Ende der Doublezahl finden
		for (LPOLESTR pT = poleCurr; L'\0' != *pT; pT++) {
			if (cEndChar == *pT)
				break;
		}

	CComBSTR bstr (pT - poleCurr, poleCurr);
	CComVariantEx vCoord(bstr.Detach(), LOCALE_ENGLISH);

		*poleNext = pT;
		if (FAILED(vCoord.ChangeTypeEx (VT_R8)))
			return 0.0;
		return V_R8(&vCoord);
	}
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_InitString (BSTR *pbstrMkName)
{
	CHECKOUTPOINTER(pbstrMkName);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	COM_TRY {
	// "TRiAS.Geometry.1:{...}:XMin XMax YMin YMax"	- erstmal minimal
	CComBSTR bstrMkName (g_cbMkGeom);

		THROW_FAILED_HRESULT(bstrMkName.Append (g_cbColon));

	CIID Guid (CLSID_TRiASCSRectangleGeometry);

		THROW_FAILED_HRESULT(bstrMkName.Append(Guid));
		THROW_FAILED_HRESULT(bstrMkName.Append(g_cbColon));

		THROW_FAILED_HRESULT(AppendToBSTR (bstrMkName, m_ptOrig.X));
		THROW_FAILED_HRESULT(AppendToBSTR (bstrMkName, m_pt2nd.X));
		THROW_FAILED_HRESULT(AppendToBSTR (bstrMkName, m_ptOrig.Y));
		THROW_FAILED_HRESULT(AppendToBSTR (bstrMkName, m_pt2nd.Y, false));

		*pbstrMkName = bstrMkName.Detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_InitString (BSTR bstrInit)
{
	CHECKINPOINTER(bstrInit);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, TGEO_E_INVALID_OBJECTSTATE);

	COM_TRY {
	LPOLESTR poleCurr = bstrInit;

		m_ptOrig.X = GetNextDouble (poleCurr, &poleCurr, L' ');
		TestAndAdvance (poleCurr, L' ');
		m_pt2nd.X = GetNextDouble (poleCurr, &poleCurr, L' ');
		TestAndAdvance (poleCurr, L' ');
		m_ptOrig.Y = GetNextDouble (poleCurr, &poleCurr, L' ');
		TestAndAdvance (poleCurr, L' ');
		m_pt2nd.Y = GetNextDouble (poleCurr, &poleCurr, L' ');

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSRectangleGeometry::IsDirty (void)
{
ObjectLock l(this);

	if (m_fIsDirty)
		return S_OK;

// Origin und Normal testen
WPersistStream PS;

	if (NULL != m_vecNormal && 
		SUCCEEDED(m_vecNormal -> QueryInterface (IID_IPersistStream, PS.ppv())) &&
		S_OK == PS -> IsDirty())
	{
		return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASCSRectangleGeometry::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	COM_TRY	{
	W_DGMPoint newVal;
	W_DGMVector newVec;
	double dWidth = 0.0;
	double dHeight = 0.0;

		THROW_FAILED_HRESULT(LoadItem (pStm, dWidth));
		THROW_FAILED_HRESULT(LoadItem (pStm, dHeight));
		THROW_FAILED_HRESULT(LoadItem (pStm, m_dRotation));

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMPoint, newVal.ppv()));
		THROW_FAILED_HRESULT(newVal -> get_X (&m_ptOrig.X));
		THROW_FAILED_HRESULT(newVal -> get_Y (&m_ptOrig.Y));
		THROW_FAILED_HRESULT(newVal -> get_Z (&m_ptOrig.Z));

		THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID__DGMVector, newVec.ppv()));
		PutNormal(newVec, true);

	// zweiten Punkt initialisieren
		m_pt2nd.X = m_ptOrig.X + dWidth;
		m_pt2nd.Y = m_ptOrig.Y + dHeight;
		m_pt2nd.Z = m_ptOrig.Y;

	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
	double dWidth = m_pt2nd.X - m_ptOrig.X;
	double dHeight = m_pt2nd.Y - m_ptOrig.Y;

		THROW_FAILED_HRESULT(SaveItem (pStm, dWidth));
		THROW_FAILED_HRESULT(SaveItem (pStm, dHeight));
		THROW_FAILED_HRESULT(SaveItem (pStm, m_dRotation));

	W_DGMPoint ptOrig;

		THROW_FAILED_HRESULT(get_Origin (ptOrig.ppi()));
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(ptOrig), pStm));

		if (NULL == m_vecNormal) {
		W_DGMVector vec;

			THROW_FAILED_HRESULT(get_Normal (vec.ppi()));
			_ASSERTE(NULL != m_vecNormal);
		}
		THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_vecNormal), pStm));

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;

	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	CHECKINPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	pcbSize -> QuadPart = 2*sizeof(CSCOORD) + sizeof(double) + 3*sizeof(double);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSRectangleGeometry::InitNew (void)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	m_dRotation = 0.0;

	m_vecNormal = NULL;
	m_fIsOwnerNormal = false;

	memset (&m_ptOrig, 0, sizeof(CSCOORD));
	memset (&m_pt2nd, 0, sizeof(CSCOORD));

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSRectangleGeometry::Load (void *pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

CComObject<CTRiASCSVector> *pVec = NULL;

	COM_TRY	{
	// Origin
		::LoadAndAdvance (m_ptOrig, pvMem);

	// Breite, Höhe, Rotation
	double h, w;

		::LoadAndAdvance(w, pvMem);
		::LoadAndAdvance(h, pvMem);
		::LoadAndAdvance(m_dRotation, pvMem);

	// zweiten Punkt aus Origin, Breite und Höhe konstruieren
		m_pt2nd.X = m_ptOrig.X + w;
		m_pt2nd.Y = m_ptOrig.Y + h;
		m_pt2nd.Z = m_ptOrig.Z;

	// Normalenvektor
	CSCOORD c;

		::LoadAndAdvance (c, pvMem);

		if (c.X != 0.0 || c.Y != 0.0 || c.Z != 1.0) {
		// Vector muß wirklich erzeugt werden
			THROW_FAILED_HRESULT(CComObject<CTRiASCSVector>::CreateInstance(&pVec));
			pVec -> AddRef();	// pending AddRef
			PutNormal (pVec, true);
			RELEASE(pVec);
			THROW_FAILED_HRESULT(pVec -> put_I (c.X));
			THROW_FAILED_HRESULT(pVec -> put_J (c.Y));
			THROW_FAILED_HRESULT(pVec -> put_K (c.Z));
		}

	} COM_CATCH_OP (
		RELEASE(pVec);
	);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::Save (void*pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	COM_TRY	{
		::SaveAndAdvance (pvMem, m_ptOrig.X);
		::SaveAndAdvance (pvMem, m_ptOrig.Y);
		::SaveAndAdvance (pvMem, m_ptOrig.Z);

		::SaveAndAdvance (pvMem, m_pt2nd.X-m_ptOrig.X);
		::SaveAndAdvance (pvMem, m_pt2nd.Y-m_ptOrig.Y);
		::SaveAndAdvance (pvMem, m_dRotation);

		if (NULL != m_vecNormal) {
			THROW_FAILED_HRESULT(WPersistMemory(m_vecNormal) -> Save (pvMem, fClearDirty, SIZEOF_POINT));
			pvMem = (BYTE *)pvMem + SIZEOF_POINT;
		}
		else {
			::SaveAndAdvance (pvMem, 0.0);
			::SaveAndAdvance (pvMem, 0.0);
			::SaveAndAdvance (pvMem, 1.0);
		}

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::GetSizeMax (ULONG*pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);
	*pcbSize = 9*sizeof(double);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASTransformGeometry
HRESULT CTRiASCSRectangleGeometry::Transform (struct CSID csGUID, ITRiASCSTransform *pCSTransform)
{
	CHECKINPOINTER(pCSTransform);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY	{
	// Rechteck wird über seine 4 Einzelkoordinaten umgerechnet
	CSCOORD	dKoords[4];

		memset (dKoords, '\0', sizeof(dKoords));
		dKoords[0] = m_ptOrig;
		dKoords[3] = m_pt2nd;

	// links oben
		dKoords[2].X = dKoords[0].X;	// XMin
		dKoords[2].Y = dKoords[3].Y;	// YMax

	// rechts unten
		dKoords[1].X = dKoords[3].X;	// XMax
		dKoords[1].Y = dKoords[0].Y;	// YMin

	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> Transform (csGUID, _countof(dKoords), dKoords, dKoords));

	// neuen Container berechnen
	CSCOORD minPt, maxPt;

	// Initialisieren
		minPt = dKoords[0];
		maxPt = dKoords[0];

		for (ULONG i = 1; i < _countof(dKoords); i++) {
			minPt.X = min(minPt.X, dKoords[i].X);
			minPt.Y = min(minPt.Y, dKoords[i].Y);
			minPt.Z = min(minPt.Z, dKoords[i].Z);

			maxPt.X = max(maxPt.X, dKoords[i].X);
			maxPt.Y = max(maxPt.Y, dKoords[i].Y);
			maxPt.Z = max(maxPt.Z, dKoords[i].Z);
		}

	// Ergebnis setzen
		m_ptOrig = minPt;
		m_pt2nd = maxPt;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::TransformInverse (struct CSID csGUID, ITRiASCSTransform*pCSTransform)
{
	CHECKINPOINTER(pCSTransform);

ObjectLock l(this);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	COM_TRY {
	// rechteck wird über seine 4 Einzelkoordinaten umgerechnet
	CSCOORD	dKoords[4];

		memset (dKoords, '\0', sizeof(dKoords));
		dKoords[0] = m_ptOrig;
		dKoords[3] = m_pt2nd;

	// links oben
		dKoords[2].X = dKoords[0].X;	// XMin
		dKoords[2].Y = dKoords[3].Y;	// YMax

	// rechts unten
		dKoords[1].X = dKoords[3].X;	// XMax
		dKoords[1].Y = dKoords[0].Y;	// YMin

	WTRiASRawCoordTransform	cst (pCSTransform);

		THROW_FAILED_HRESULT(cst -> TransformInverse (csGUID, _countof(dKoords), dKoords, dKoords));

	// neuen Container berechnen
	CSCOORD minPt, maxPt;

	// Initialisieren
		minPt = dKoords[0];
		maxPt = dKoords[0];

		for (ULONG i = 1; i < _countof(dKoords); i++)
		{
			minPt.X = min(minPt.X, dKoords[i].X);
			minPt.Y = min(minPt.Y, dKoords[i].Y);
			minPt.Z = min(minPt.Z, dKoords[i].Z);

			maxPt.X = max(maxPt.X, dKoords[i].X);
			maxPt.Y = max(maxPt.Y, dKoords[i].Y);
			maxPt.Z = max(maxPt.Z, dKoords[i].Z);
		}

	// Ergebnis setzen
		m_ptOrig = minPt;
		m_pt2nd = maxPt;

	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSRectangleGeometry::Clone (IDispatch **ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSRectangleGeometry> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject<CTRiASCSRectangleGeometry>::CreateInstance (&pNew));
		pNew -> AddRef();		// pending AddRef

		if (NULL != m_vecNormal) {
		WDispatch disp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(m_vecNormal) -> Clone (disp.ppi()));
			pNew -> PutNormal (W_DGMVector(disp), true);
		}

	// Werte kopieren
		pNew -> m_ptOrig = m_ptOrig;
		pNew -> m_pt2nd = m_pt2nd;
		pNew -> m_dRotation = m_dRotation;
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMGeometry *>(pNew);

	} COM_CATCH_OP (
		RELEASE(pNew);
	);
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_XMin(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptOrig.X;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_XMin(double newVal)
{
ObjectLock l(this);

	m_ptOrig.X = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_YMin(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptOrig.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_YMin(double newVal)
{
ObjectLock l(this);

	m_ptOrig.Y = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_ZMin(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_ptOrig.Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_ZMin(double newVal)
{
ObjectLock l(this);

	m_ptOrig.Z = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_XMax(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_pt2nd.X;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_XMax(double newVal)
{
ObjectLock l(this);

	m_pt2nd.X = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_YMax(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_pt2nd.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_YMax(double newVal)
{
ObjectLock l(this);

	m_pt2nd.Y = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::get_ZMax(double *pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_pt2nd.Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::put_ZMax(double newVal)
{
ObjectLock l(this);

	m_pt2nd.Z = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::GetRect (
	double *pValXMin, double *pValYMin, double *pValXMax, double *pValYMax)
{
	BEGIN_OUT_PARAMS()
		OUT_PARAM(pValXMin)
		OUT_PARAM(pValYMin)
		OUT_PARAM(pValXMax)
		OUT_PARAM(pValYMax)
	END_OUT_PARAMS()

ObjectLock l(this);

	*pValXMin = m_ptOrig.X;
	*pValYMin = m_ptOrig.Y;
	*pValXMax = m_pt2nd.X;
	*pValYMax = m_pt2nd.Y;
	return S_OK;
}

STDMETHODIMP CTRiASCSRectangleGeometry::SetRect (
	double newValXMin, double newValYMin, double newValXMax, double newValYMax)
{
ObjectLock l(this);

	m_ptOrig.X = newValXMin;
	m_ptOrig.Y = newValYMin;
	m_pt2nd.X = newValXMax;
	m_pt2nd.Y = newValYMax;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSRectangleGeometry::GetSizeMaxWkb(ULONG *pulSize)
{
	CHECKINPOINTER(pulSize);

	*pulSize = sizeof(BYTE)+2*sizeof(UINT)+10*sizeof(double);
	return S_OK;
}

HRESULT CTRiASCSRectangleGeometry::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSRectangleGeometry::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	SaveAndAdvance(pvMem, (BYTE)wkbNDR);
	SaveAndAdvance(pvMem, (UINT)wkbPolygon);
	SaveAndAdvance(pvMem, (UINT)5);

	SaveAndAdvance(pvMem, m_ptOrig.X);
	SaveAndAdvance(pvMem, m_ptOrig.Y);
	SaveAndAdvance(pvMem, m_ptOrig.X);
	SaveAndAdvance(pvMem, m_pt2nd.Y);
	SaveAndAdvance(pvMem, m_pt2nd.X);
	SaveAndAdvance(pvMem, m_pt2nd.Y);
	SaveAndAdvance(pvMem, m_pt2nd.X);
	SaveAndAdvance(pvMem, m_ptOrig.Y);
	SaveAndAdvance(pvMem, m_ptOrig.X);
	SaveAndAdvance(pvMem, m_ptOrig.Y);

	if (fClearDirty)
		m_fIsDirty = false;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSRectangleGeometry::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSRectangleGeometry::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);

ObjectLock l(this);
CComBSTR bstrWKT (L"POLYGON(");

	AppendPoint(bstrWKT, m_ptOrig.X, m_ptOrig.Y);
	AppendPoint(bstrWKT, m_ptOrig.X, m_pt2nd.Y);
	AppendPoint(bstrWKT, m_pt2nd.X, m_pt2nd.Y);
	AppendPoint(bstrWKT, m_pt2nd.X, m_ptOrig.Y);
	AppendPoint(bstrWKT, m_ptOrig.X, m_ptOrig.Y, false);

	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT.Detach();

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}


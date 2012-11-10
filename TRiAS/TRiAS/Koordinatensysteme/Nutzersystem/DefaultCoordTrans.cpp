// @doc
// @module DefaultCoordTrans.cpp | Implementation of CDefaultCoordTrans

#include "Defaultp.hxx"

#include <Com/PropertyHelper.h>
//#include <TDBGeo.h>

#include "Default.h"
#include "Strings.h"

#include "DefaultCoordTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_USE_LEGACY_CODE)
HWND __hWndM = NULL;				// eigentlich nicht benötigt
UINT __DexCmd = 0;
#endif // _USE_LEGACY_CODE

/////////////////////////////////////////////////////////////////////////////
// externe Funktionen
extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, int iPrec, double);

///////////////////////////////////////////////////////////////////////////////
// Quadrat
inline double Sqr(double x) { return x * x; }

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(Dispatch);

/////////////////////////////////////////////////////////////////////////////
// CDefaultCoordTrans

STDMETHODIMP CDefaultCoordTrans::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICoordTransform,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransformInit
STDMETHODIMP CDefaultCoordTrans::InitCoordTransform(IUnknown *pIUnk)
{
	COM_TRY {
	// SkalierungsKoeffizienten aus Header holen
	WTRiASProperties Props;

		m_PropBase = pIUnk;
		THROW_FAILED_HRESULT(m_PropBase -> get_Properties (Props.ppi()));

		m_dKoeff = GetProperty (Props, g_cbCoordScaling, 1.0, LOCALE_ENGLISH);
		m_iPrecision = GetProperty (Props, g_cbCoordPrecision, 0, LOCALE_ENGLISH);

		if (0.0 == m_dKoeff) {
			TX_ASSERT(0.0 != m_dKoeff);
			m_dKoeff = 1.0;		// sicherheitshalber
		}

		m_dFalseX = GetProperty (Props, g_cbCoordFalseX, 4500000.0, LOCALE_ENGLISH);
		m_dFalseY = GetProperty (Props, g_cbCoordFalseY, 0.0, LOCALE_ENGLISH);
		m_dLongOrig = GetProperty (Props, g_cbCoordMeridian, 12.0, LOCALE_ENGLISH);
		m_dLongOrig *= 3600.0;		// Sekunden
		m_dLatOrig = GetProperty (Props, g_cbCoordLatitude, 0.0, LOCALE_ENGLISH);
		m_dLatOrig *= 3600.0;		// Sekunden
		m_dScaleAtOrig = GetProperty (Props, g_cbCoordScaleAtOrig, 1.0, LOCALE_ENGLISH);

	// Initialisierung der Transformationspipe
		if (m_CTF.IsValid()) {
//			m_CSMap.clear();
			SetProperty (Props, g_cbExternPipe, NULL);
			WTRiASCSTransform(m_CTF) -> ShutDown();
			m_CTF.Assign(NULL);
		}
		THROW_FAILED_HRESULT(m_CTF.CreateInstance(CLSID_TRiASCSTransform));
		THROW_FAILED_HRESULT(AddOutputAndInputCS());

	// diese Pipe am Projekt speichern
	PROPERTY_TYPE rgPropType = PROPERTY_TYPE(PROPERTY_TYPE_Hidden|PROPERTY_TYPE_System);

		SetPropertyAndType (Props, g_cbExternPipe, m_CTF, rgPropType, true);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::ReInitCoordTransform(IUnknown *Props)
{
	return InitCoordTransform(Props);
}

STDMETHODIMP CDefaultCoordTrans::TermCoordTransform()
{
	if (m_CTF.IsValid()) {
//	WTRiASProperties Props;
//
//		_ASSERTE(m_PropBase.IsValid());
//		if (SUCCEEDED(m_PropBase -> get_Properties (Props.ppi())))
//			SetProperty (Props, g_cbExternPipe, NULL);

		WTRiASCSTransform(m_CTF) -> ShutDown();
//		m_CSMap.clear();
		m_CTF.Assign(NULL);
	}
	m_PropBase.Assign(NULL);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Properties

STDMETHODIMP CDefaultCoordTrans::get_Description(BSTR * pVal)
{
	if (NULL == pVal) return E_POINTER;

ResourceFile RF (g_pDLLName);
CComBSTR bstrDesc (ResString (ResID (IDS_DESCRIPTION, &RF), 120));

	*pVal = bstrDesc.Detach();
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::get_AspectRatio(_DGMPoint *pPt1, _DGMPoint *pPt2, double *pVal)
{
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = 1.0;		// immer isotrop
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::get_IsMetric(VARIANT_BOOL * pVal)
{
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::get_CanConfig(VARIANT_BOOL * pVal)
{
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = VARIANT_FALSE;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Methods

STDMETHODIMP CDefaultCoordTrans::Transform(_DGMPoint *pPt, TRANSDIRECTION Dir)
{
	if (1.0 == m_dKoeff) 
		return S_OK;	// nothing to do

	try {
	double dX, dY, dZ;

		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			THROW_FAILED_HRESULT(pPt -> get_X (&dX));
			THROW_FAILED_HRESULT(pPt -> put_X (dX / m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Y (&dY));
			THROW_FAILED_HRESULT(pPt -> put_Y (dY / m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Z (&dZ));
			THROW_FAILED_HRESULT(pPt -> put_Z (dZ / m_dKoeff));
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			THROW_FAILED_HRESULT(pPt -> get_X (&dX));
			THROW_FAILED_HRESULT(pPt -> put_X (dX * m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Y (&dY));
			THROW_FAILED_HRESULT(pPt -> put_Y (dY * m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Z (&dZ));
			THROW_FAILED_HRESULT(pPt -> put_Z (dZ * m_dKoeff));
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			TX_ASSERT(Dir != TRANSDIRECTION_IGNORED);
			_com_issue_error(E_UNEXPECTED);
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::TransformColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
// alle Punkte der Collection Transformieren
	try {
	W_DGMPoint Point;
	WUnknown EnumUnk;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(EnumUnk.ppi()));

	WEnumW_DGMPoint Enum (EnumUnk);

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &Point, NULL); /**/)
		{
			THROW_FAILED_HRESULT(Transform (Point, Dir));
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::TransformEx(_DGMPoint *Point, 
	TRANSDIRECTION Dir, IDispatch *pIParams)
{
	return Transform (Point, Dir);
}

STDMETHODIMP CDefaultCoordTrans::TransformEx2(_DGMPoint *Point, 
	TRANSDIRECTION Dir, IUnknown *pICS)
{
	return Transform (Point, Dir);
}

STDMETHODIMP CDefaultCoordTrans::TransformCollEx(_DGMPoints *Points, 
	TRANSDIRECTION Dir, IDispatch *pIParams)
{
	return TransformColl (Points, Dir);
}

STDMETHODIMP CDefaultCoordTrans::TransformCollEx2(_DGMPoints *Points, 
	TRANSDIRECTION Dir, IUnknown *pICS)
{
	return TransformColl (Points, Dir);
}

STDMETHODIMP CDefaultCoordTrans::Native(_DGMPoint * pPt, TRANSDIRECTION Dir)
{
	if (1.0 == m_dKoeff) 
		return S_OK;	// nothing to do

	try {
	double dX, dY, dZ;

		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Metric
			THROW_FAILED_HRESULT(pPt -> get_X (&dX));
			THROW_FAILED_HRESULT(pPt -> put_X (dX / m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Y (&dY));
			THROW_FAILED_HRESULT(pPt -> put_Y (dY / m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Z (&dZ));
			THROW_FAILED_HRESULT(pPt -> put_Z (dZ / m_dKoeff));
			break;

		case TRANSDIRECTION_INVERSE:	// Native
			THROW_FAILED_HRESULT(pPt -> get_X (&dX));
			THROW_FAILED_HRESULT(pPt -> put_X (dX * m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Y (&dY));
			THROW_FAILED_HRESULT(pPt -> put_Y (dY * m_dKoeff));
			THROW_FAILED_HRESULT(pPt -> get_Z (&dZ));
			THROW_FAILED_HRESULT(pPt -> put_Z (dZ * m_dKoeff));
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			TX_ASSERT(Dir != TRANSDIRECTION_IGNORED);
			_com_issue_error(E_UNEXPECTED);
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::NativeColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
// alle Punkte der Collection Transformieren
	try {
	W_DGMPoint Point;
	WUnknown EnumUnk;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(EnumUnk.ppi()));

	WEnumW_DGMPoint Enum (EnumUnk);

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &Point, NULL); /**/)
		{
			THROW_FAILED_HRESULT(Native (Point, Dir));
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::NativeEx(_DGMPoint * Point, TRANSDIRECTION Dir, IDispatch *pIParam)
{
	return Native (Point, Dir);
}

STDMETHODIMP CDefaultCoordTrans::NativeCollEx(_DGMPoints * Points, TRANSDIRECTION Dir, IDispatch *pIParam)
{
	return NativeColl (Points, Dir);
}

STDMETHODIMP CDefaultCoordTrans::TransformParameter(_DGMPoint * Point, TRANSDIRECTION Dir, IDispatch * * pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDefaultCoordTrans::FreeTransformParameter(TRANSDIRECTION Dir, IDispatch * pDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDefaultCoordTrans::NativeParameter(_DGMPoint * Point, TRANSDIRECTION Dir, IDispatch * * pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDefaultCoordTrans::FreeNativeParameter(TRANSDIRECTION Dir, IDispatch * pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDefaultCoordTrans::Distance(_DGMPoint * Point1, _DGMPoint * Point2, _DGMPoint ** pDist)
{
	if (NULL == pDist) 
		return E_POINTER;

	TX_ASSERT(0.0 != m_dKoeff);
	try {
	W_DGMPoint outPt (CLSID_TRiASCSPoint);
	double d1, d2;

		THROW_FAILED_HRESULT(Point1 -> get_X(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_X(&d2));
		THROW_FAILED_HRESULT(outPt -> put_X(fabs(d2 - d1) / m_dKoeff));

		THROW_FAILED_HRESULT(Point1 -> get_Y(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_Y(&d2));
		THROW_FAILED_HRESULT(outPt -> put_Y(fabs(d2 - d1) / m_dKoeff));

		THROW_FAILED_HRESULT(Point1 -> get_Z(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_Z(&d2));
		THROW_FAILED_HRESULT(outPt -> put_Z(fabs(d2 - d1) / m_dKoeff));

	// Resultat liefern
		*pDist = outPt.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::DistanceEx(
	_DGMPoint *Point1, _DGMPoint *Point2, _DGMPoint **ppDist, double *pdDist)
{
	if (NULL == ppDist) 
		return E_POINTER;
	*ppDist = NULL;
	if (NULL == pdDist)
		return E_POINTER;
	*pdDist = 0.0;

	TX_ASSERT(0.0 != m_dKoeff);
	try {
	W_DGMPoint outPt (CLSID_TRiASCSPoint);
	double dDeltaX, dDeltaY, dDeltaZ;
	double d1, d2;

		THROW_FAILED_HRESULT(Point1 -> get_X(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_X(&d2));
		dDeltaX = fabs(d2 - d1) / m_dKoeff;
		THROW_FAILED_HRESULT(outPt -> put_X(dDeltaX));

		THROW_FAILED_HRESULT(Point1 -> get_Y(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_Y(&d2));
		dDeltaY = fabs(d2 - d1) / m_dKoeff;
		THROW_FAILED_HRESULT(outPt -> put_Y(dDeltaY));

		THROW_FAILED_HRESULT(Point1 -> get_Z(&d1));
		THROW_FAILED_HRESULT(Point2 -> get_Z(&d2));
		dDeltaZ = fabs(d2 - d1) / m_dKoeff;
		THROW_FAILED_HRESULT(outPt -> put_Z(dDeltaZ));

	// Resultate liefern
		*ppDist = outPt.detach();
		*pdDist = sqrt(Sqr(dDeltaX) + Sqr(dDeltaY) + Sqr(dDeltaZ));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

// Liefert den Punkt, der einen vorgegebenen Abstand zum ersten Punkt besitzt
STDMETHODIMP CDefaultCoordTrans::DistancePoint(_DGMPoint * Point, _DGMPoint * Delta, _DGMPoint * * pVal)
{
	if (NULL == pVal) 
		return E_POINTER;

	try {
	W_DGMPoint outPt (CLSID_TRiASCSPoint);
	double d1, d2;

		THROW_FAILED_HRESULT(Point -> get_X(&d1));
		THROW_FAILED_HRESULT(Delta -> get_X(&d2));
		THROW_FAILED_HRESULT(outPt -> put_X(d1 + (d2 * m_dKoeff)));

		THROW_FAILED_HRESULT(Point -> get_Y(&d1));
		THROW_FAILED_HRESULT(Delta -> get_Y(&d2));
		THROW_FAILED_HRESULT(outPt -> put_Y(d1 + (d2 * m_dKoeff)));

		THROW_FAILED_HRESULT(Point -> get_Z(&d1));
		THROW_FAILED_HRESULT(Delta -> get_Z(&d2));
		THROW_FAILED_HRESULT(outPt -> put_Z(d1 + (d2 * m_dKoeff)));

	// Resultat liefern
		*pVal = outPt.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}


STDMETHODIMP CDefaultCoordTrans::ToStrings(_DGMPoint * Point, BSTR * XStr, BSTR * YStr, BSTR * ZStr)
{
char cbFormat[20];
char cbBuffer[256];

	if (0 == m_iPrecision)
		strcpy (cbFormat, "%ld");
	else
		wsprintf (cbFormat, "%%ld.%%0%dlu" /*"%%%d.%df"*/, m_iPrecision);

	try {
	CComBSTR bstr;
	double d;

	// X-Koordinate
		if (NULL != XStr) {
			THROW_FAILED_HRESULT(Point -> get_X(&d));
			DtoACTF (cbBuffer, cbFormat, m_iPrecision, d/* /m_dKoeff */);
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*XStr = bstr.Detach();
		}

	// Y-Koordinate
		if (NULL != YStr) {
			THROW_FAILED_HRESULT(Point -> get_Y(&d));
			DtoACTF (cbBuffer, cbFormat, m_iPrecision, d/* /m_dKoeff */);
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*YStr = bstr.Detach();
		}

	// Z-Koordinate
		if (NULL != ZStr) {
			THROW_FAILED_HRESULT(Point -> get_Z(&d));
			DtoACTF (cbBuffer, cbFormat, m_iPrecision, d/* /m_dKoeff */);
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*ZStr = bstr.Detach();
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::ToPoint(BSTR XStr, BSTR YStr, BSTR ZStr, _DGMPoint **ppIPoint)
{
	if (NULL == ppIPoint)
		return E_POINTER;

	USES_CONVERSION;
	try {
	W_DGMPoint Point (CLSID_TRiASCSPoint);
	double Coords[3] = 
		{ 
			atof (OLE2A(XStr))/* *m_dKoeff */, 
			atof (OLE2A(YStr))/* *m_dKoeff */,
			0.0,
		};
	
		if (SysStringLen (ZStr) > 0)
			Coords[2] = atof (OLE2A(ZStr))/* *m_dKoeff */;

		THROW_FAILED_HRESULT(Point -> SetPoint (Coords));
		*ppIPoint = Point.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::get_Envelope(IDispatch **ppIDisp)
{
	if (NULL == ppIDisp)
		return E_POINTER;

	try {
	CCSRectangleGeometry Rect (0.0, 0.0, 1.0e6, 1.0e6);
	WDispatch disp (Rect);		// AddRef/QI

		*ppIDisp = disp.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für Koordinatentransformations-Pipe
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSPCS);
DefineSmartInterface(TRiASCSDatumTransformation);

HRESULT CDefaultCoordTrans::AddOutputAndInputCS()
{
	_ASSERTE(m_CTF.IsValid());

	COM_TRY {
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CS -> put_CoordSystemType(tcsCS_Projected));

	// Geodätische Grundlage initialisieren
	TRIASCSGEODETICDATUM rgDatum = tcsGD_DeutscheHauptdreiecksnetz;

		{
		WTRiASCSGCS GCS;

			THROW_FAILED_HRESULT(CS -> get_GeographicCS(GCS.ppi()));
			THROW_FAILED_HRESULT(GCS -> put_GeodeticDatum(rgDatum));
			THROW_FAILED_HRESULT(GCS -> put_PrimeMeridian(tcsPM_Greenwich));
			THROW_FAILED_HRESULT(GCS -> put_UnitOfAngle(tcsUOA_Second));
		}

	// Datumsparameter einstellen
		{
		WTRiASCSDatumTransformation DTrans;

			THROW_FAILED_HRESULT(CS -> get_DatumTransformation(DTrans.ppi()));
			THROW_FAILED_HRESULT(DTrans -> put_GeodeticDatum(rgDatum));
			THROW_FAILED_HRESULT(DTrans -> put_TransformationAlgorithm(
				tcsDTA_PositionVector7ParamTransformation));
		}
	
	// Projektionsparameter setzen
		{
		WTRiASCSPCS PCS;

			THROW_FAILED_HRESULT(CS -> get_ProjectedCS (PCS.ppi()));
		
		// Projektionsparameter festlegen
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(
				tcsPA_CylindricEquirectangular));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, m_dScaleAtOrig));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin, m_dLongOrig));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_CylindricEquirectangular_FalseEasting, m_dFalseX));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin, m_dLatOrig));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_CylindricEquirectangular_FalseNorthing, m_dFalseY));
			THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(tcsUOL_Metre));
		}

	// CS ist jetzt fertig initialisiert
		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> putref_OutputCS(CS));
		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> AddInputCS(CS));

		THROW_FAILED_HRESULT(CS -> Recompute());

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CDefaultCoordTrans::get_CoordTransformPipe (IDispatch **ppIPipe)
{
	if (NULL == ppIPipe)
		return E_POINTER;
	*ppIPipe = NULL;

	COM_TRY {
	WDispatch dispCtf (m_CTF);

		*ppIPipe = dispCtf.detach();

	} COM_CATCH;
	return S_OK;
}


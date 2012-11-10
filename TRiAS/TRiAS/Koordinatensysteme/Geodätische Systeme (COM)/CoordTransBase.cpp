// @doc
// @module CoordTransBase.cpp | Implementation of CCoordTrans

#include "stdafx.h"

#include <Com/PropertyHelper.h>
#include <Atl/Ciid.h>

#include "GeodCtf_COM.h"
#include "CoordTransBase.h"
#include "Strings.h"

//#include "CtfGeoGK.h"
#include "CTFExContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumVARIANT);			// WEnumVARIANT
DefineSmartInterface2(_DGMPoint, IID__DGMPoint);
DefineSmartInterface(CTFExContext)			// WCTFExContext
DefineSmartInterface(PersistStreamInit);	// WPersistStreamInit
DefineSmartInterface(Dispatch);

DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSPCS);
DefineSmartInterface(TRiASCSDatumTransformation);

/////////////////////////////////////////////////////////////////////////////
// externe Funktionen
extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, int iPrec, double);

///////////////////////////////////////////////////////////////////////////////
// Quadrat
inline double Sqr(double x) { return x * x; }

///////////////////////////////////////////////////////////////////////////////
// Das folgende nur eingeschränktem Kundenkreis zugänglich machen
// Der Ellipsoidübergang wird mit RegEntry
//		HKCU\Software\uve\TRiAS\Config\AllowExtendedCoords:REG_DWORD:ALLOW_COOKIE
// bzw. SysAdminMode erlaubt.
//
#define ALLOW_COOKIE	DWORD(0x0023484b)

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

STDMETHODIMP CCoordTrans::InterfaceSupportsErrorInfo(REFIID riid)
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

const double PI = 3.141592653589793238;

double GetUnitOfScale (BSTR bstrUnitOfAngle, TRIASCSUNITOFANGLE &rrgUOA)
{
double dScale = 1.0;

	rrgUOA = tcsUOA_Second;
	if (!_wcsicmp (bstrUnitOfAngle, g_cbSecond)) {
		dScale = 1.0;
		rrgUOA = tcsUOA_Second;
	}
	else if (!_wcsicmp (bstrUnitOfAngle, g_cbRadian)) {
		dScale = 180.0*3600/PI;
		rrgUOA = tcsUOA_Radian;
	}
	else if (!_wcsicmp (bstrUnitOfAngle, g_cbDegree)) {	// Grad
		dScale = 3600;
		rrgUOA = tcsUOA_Degree;
	}
	else if (!_wcsicmp (bstrUnitOfAngle, g_cbGrad))	{	// Neugrad
		dScale = 180*3600/200;
		rrgUOA = tcsUOA_Grad;
	}
	else if (!_wcsicmp (bstrUnitOfAngle, g_cbGon)) {
		dScale = 180*3600/200;
		rrgUOA = tcsUOA_Gon;
	}
	else if (!_wcsicmp (bstrUnitOfAngle, g_cbMicroradian)) {
		dScale = 180*3600*1e6/PI;
		rrgUOA = tcsUOA_Microradian;
	}
//	else if (!_wcsicmp (bstrUnitOfAngle, g_cbArcMinute))
//		dScale = 10800.0/PI;
//	else if (!_wcsicmp (bstrUnitOfAngle, g_cbArcSecond))
//		dScale = 648000.0/PI;
	return dScale;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransformInit

STDMETHODIMP CCoordTrans::InitCoordTransform(IUnknown *pIUnk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

#if _TRiAS_VER < 0x0400
// Testen, ob Ellipsoidübergang erlaubt werden kann
	m_fAllowChangeEllipse = false;
	{
	CRegKey regAllow;

		if (ERROR_SUCCESS == regAllow.Open(HKEY_CURRENT_USER, TEXT("Software")) && 
			ERROR_SUCCESS == regAllow.Open(regAllow, REG_COMPANY_KEY) &&
			ERROR_SUCCESS == regAllow.Open(regAllow, REG_PRODUCT_KEY) &&
			ERROR_SUCCESS == regAllow.Open(regAllow, TEXT("Config")))
		{
		DWORD dwData = 0L;

			if (ERROR_SUCCESS == regAllow.QueryValue (dwData, TEXT("AllowExtendedCoords")))
				m_fAllowChangeEllipse = (ALLOW_COOKIE == dwData) ? true : false;
		}
	}
#else
	m_fAllowChangeEllipse = true;
#endif // _TRiAS_VER < 0x0400

// Parameter lesen
	COM_TRY {
		THROW_FAILED_HRESULT(pIUnk -> QueryInterface(IID_ITRiASPropertyBase, m_PropBase.ppv()));

		_ASSERTE(m_PropBase.IsValid());

	// aktueller AnzeigeMode: ShowGKCoords
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(m_PropBase -> get_Properties (Props.ppi()));

		if (!m_fAllowChangeEllipse)		// muß zuerst initialisiert werden
			m_fAllowChangeEllipse =	(0 == GetProperty (Props, g_cbSysAdminMode, 0, LOCALE_ENGLISH) ? false : true);

		InitVars (Props);

	// CoordStrBreite
		m_iStrBreite = GetProperty (Props, g_cbCoordStrBreite, 3, LOCALE_ENGLISH);
		if (m_iStrBreite != 3 && m_iStrBreite != 6) 
			m_iStrBreite = 3;

	// CoordMeridian
		if (m_CTFMode != CTFMODE_AutoMeridian)	// JG990128 CoordMeriadian nur auslesen, wenn notwendig
		{
			m_iMeridian = GetProperty (Props, g_cbCoordMeridian, 12, LOCALE_ENGLISH);
			if (3 == m_iStrBreite && (m_iMeridian / 3) * 3 != m_iMeridian)
			{
				m_iMeridian = 12;	// fehlerhafter Mittelmeridian
			}
			else if (6 == m_iStrBreite && ((m_iMeridian -3) / 6) * 6 != m_iMeridian -3)
			{
				m_iMeridian = 15;	// fehlerhafter Mittelmeridian
			}
		}

	// CoordPrecision
		m_iPrec = GetProperty (Props, g_cbCoordPrecision, 3, LOCALE_ENGLISH);

	// Maßeinheit aus Header holen
	CComBSTR bstrUnitOfAngle (GetProperty (Props, g_cbUnitOfAngle, CComBSTR(g_cbSecond)));

		m_dUnitScale = GetUnitOfScale (bstrUnitOfAngle, m_rgUOA);
		if (m_dUnitScale == 0.0)		
			m_dUnitScale = 1.0;

	// Initialisierung der Transformationspipe
		if (m_CTF.IsValid()) {
			m_CSMap.clear();
			SetProperty (Props, g_cbExternPipe, NULL);
			WTRiASCSTransform(m_CTF) -> ShutDown();
			m_CTF.Assign(NULL);
		}
		THROW_FAILED_HRESULT(m_CTF.CreateInstance(CLSID_TRiASCSTransform));
		THROW_FAILED_HRESULT(AddOutputCS());

	// diese Pipe am Projekt speichern
	PROPERTY_TYPE rgPropType = PROPERTY_TYPE(PROPERTY_TYPE_Hidden|PROPERTY_TYPE_System);

		SetPropertyAndType (Props, g_cbExternPipe, m_CTF, rgPropType, true);

	} COM_CATCH;

	m_fInitialized = true;
	return S_OK;
}

STDMETHODIMP CCoordTrans::ReInitCoordTransform(IUnknown *pIUnk)
{
	return InitCoordTransform (pIUnk);
}

STDMETHODIMP CCoordTrans::TermCoordTransform()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_CTF.IsValid()) {
//	WTRiASProperties Props;
//
//		_ASSERTE(m_PropBase.IsValid());
//		if (SUCCEEDED(m_PropBase -> get_Properties (Props.ppi())))
//			SetProperty (Props, g_cbExternPipe, NULL);

		WTRiASCSTransform(m_CTF) -> ShutDown();
		m_CSMap.clear();
		m_CTF.Assign(NULL);
	}
	m_PropBase.Assign(NULL);
	m_fInitialized = false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Properties

///////////////////////////////////////////////////////////////////////////////
// Berechnen des bildausschnittsabhängigen Isotropie-Koeffizienten 
// HilfsFunktionen 
inline long double Q (long double x) 
{
	return x * x; 
}

inline long double D (long double dX, long double dY) 
{ 
	return sqrtl (Q(dX) + Q(dY)); 
}

STDMETHODIMP CCoordTrans::get_AspectRatio(_DGMPoint *pPt1, _DGMPoint *pPt2, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

	COM_TRY {
#if !defined(_USE_OLD_ASPECT_RATIO)
	// nach neueren Erkenntnissen (für mich) ist der AnIsotropiekoeffizient gleich
	// dem cosinus der geodätischen Höhe :-)
	double dY1, dY2;

		THROW_FAILED_HRESULT(pPt1 -> get_Y(&dY1));
		THROW_FAILED_HRESULT(pPt2 -> get_Y(&dY2));

	// nicht alle Koordinaten sind in Sekunden :-) - #HK040608
		*pVal = cos(((dY2 + dY1) * m_dUnitScale/2) * (PI/(180.0*3600)));
#else
	double dX1, dX2, dY1, dY2;

	// 1. Berechnen der mittleren Ausdehnungen des Rechteckes in geodätischen
	//    Koordinaten
		THROW_FAILED_HRESULT(pPt1 -> get_X(&dX1));
		THROW_FAILED_HRESULT(pPt2 -> get_X(&dX2));
		THROW_FAILED_HRESULT(pPt1 -> get_Y(&dY1));
		THROW_FAILED_HRESULT(pPt2 -> get_Y(&dY2));

	long double DeltaXGeod = dX2 - dX1;
	long double DeltaYGeod = dY1 - dY2;

	// 2. Berechnen der mittleren Ausdehnungen des Rechteckes in Gauß/Krüger
	//    Koordinaten
	// ACHTUNG: Es wird eine Konvertierung in Bessel: Gauß/Krüger 6(12) 
	//          Koordinaten durchgeführt, da davon ausgegangen wird, daß die 
	//          Koordinaten in unseren Breiten liegen.
	// Gauß/Krüger Koordinaten
	long double X1, Y1;	// links oben
	long double X2, Y2;	// rechts unten
	long double X3, Y3;	// links unten
	long double X4, Y4;	// rechts oben

		geogau (HA, HB, m_iStrBreite, m_iMeridian, dY1, dX1, KS, &Y1, &X1);
		geogau (HA, HB, m_iStrBreite, m_iMeridian, dY2, dX2, KS, &Y2, &X2);
		geogau (HA, HB, m_iStrBreite, m_iMeridian, dY2, dX1, KS, &Y3, &X3);
		geogau (HA, HB, m_iStrBreite, m_iMeridian, dY1, dX2, KS, &Y4, &X4);

	// mittlere Längen der Rechteck-Seiten in Gauß/Krüger Koordinaten
	// links oben - rechts oben ./. links unten - rechts unten
	long double DeltaXGK = (D(X1-X4, Y1-Y4) + D(X2-X3, Y2-Y3))/2;

	// links oben - links unten ./.  rechts oben - rechts unten
	long double DeltaYGK = (D(X1-X3, Y1-Y3) + D(X4-X2, Y4-Y2))/2;

		if (0 == DeltaYGK || 0 == DeltaXGeod) {
			ASSERT(0 != DeltaYGK && 0 != DeltaXGeod);
			*pVal = 1.0;
			return S_OK;		// Fehler ! Division durch null
		}

	// 3. Berechnen des Isotropiekoefizienten
		*pVal = fabs((double)((DeltaXGK * DeltaYGeod) / (DeltaXGeod * DeltaYGK)));
#endif // !defined(_USE_OLD_ASPECT_RATIO)

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::get_IsMetric(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

	*pVal =  (m_CTFType == CTF_Native) ? VARIANT_FALSE : VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CCoordTrans::get_CanConfig(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = VARIANT_TRUE;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Methods

STDMETHODIMP CCoordTrans::Transform(_DGMPoint *pPt, TRANSDIRECTION Dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// JG990126
	_ASSERTE(pPt);
	if (NULL == pPt)
		return E_POINTER;

//long double dXOut, dYOut, dZOut;
//double dX, dY, dZ;

CSCOORD Coords;

	RETURN_FAILED_HRESULT(pPt -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> get_Z (&Coords.Z));

	if (CTF_TransMercator == m_CTFType)	{	// aus GKCoords konvertieren
	int iMeridian = 0;

		if (CTFMODE_AutoMeridian != m_CTFMode)
			iMeridian = m_iMeridian;

	CSID Guid;

		RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, m_iStrBreite, iMeridian, &Guid))
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
//				dZOut = dZ;	// oder wie?
//				if (!GetMeridianGeod (dX, iMeridian)) 
//					_com_issue_error(E_UNEXPECTED);
//				ConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
//				if (!GetMeridianGK (dX, iMeridian))	
//					_com_issue_error(E_UNEXPECTED);
//				InvConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//				dZOut = dZ;
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	} 
	else if (m_rgChangeEllipse != m_rgEllipseNative) {
	CSID Guid;

		RETURN_FAILED_HRESULT(EnsureGeodCS(m_rgChangeEllipse, &Guid))
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	}
	else {
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
//			Coords.X /= m_dUnitScale;
//			Coords.Y /= m_dUnitScale;
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
//			Coords.X *= m_dUnitScale;
//			Coords.Y *= m_dUnitScale;
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	}

	RETURN_FAILED_HRESULT(pPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(pPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> put_Z (Coords.Z));

	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
// alle Punkte der Collection transformieren
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(Enum.ppu()));

	CComVariant var;

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
			{
				THROW_FAILED_HRESULT(Transform (W_DGMPoint(V_UNKNOWN(&var)), Dir));
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformParameter(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

double dX;
int iMeridian = m_iMeridian;

	COM_TRY {
		THROW_FAILED_HRESULT(pPt -> get_X (&dX));
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:		// Transform
			dX /= m_dUnitScale;
			if (!GetMeridianGeod (dX, iMeridian)) 
				_com_issue_error(E_UNEXPECTED);
			break;

		case TRANSDIRECTION_INVERSE:		// InvTransform
			if (!GetMeridianGK (dX, iMeridian))	
				_com_issue_error(E_UNEXPECTED);
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			ASSERT(Dir != TRANSDIRECTION_IGNORED);
			_com_issue_error(E_UNEXPECTED);
		}

	WCTFExContext context (CLSID_CTFExContext);
	
		THROW_FAILED_HRESULT(context -> put_Meridian (iMeridian));
		*pVal = context.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::FreeTransformParameter(TRANSDIRECTION Dir, IDispatch *pIDisp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pIDisp)
		pIDisp -> Release();

	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeParameter(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

double dX;
int iMeridian = m_iMeridian;

	COM_TRY {
		THROW_FAILED_HRESULT(pPt -> get_X (&dX));

		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			dX /= m_dUnitScale;
			if (!GetMeridianGeod (dX, iMeridian))
				_com_issue_error(E_UNEXPECTED);
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			if (!GetMeridianGK (dX, iMeridian))	
				_com_issue_error(E_UNEXPECTED);
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			ASSERT(Dir != TRANSDIRECTION_IGNORED);
			_com_issue_error(E_UNEXPECTED);
		}

	WCTFExContext context(CLSID_CTFExContext);
	
		THROW_FAILED_HRESULT(context -> put_Meridian (iMeridian));
		*pVal = context.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::FreeNativeParameter(TRANSDIRECTION Dir, IDispatch *pIDisp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pIDisp)
		pIDisp -> Release();

	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformEx(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch *pIParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//long double dXOut, dYOut, dZOut;
//double dX, dY, dZ;
int iMeridian = 0;

	if (NULL != pIParams) {
	WCTFExContext param;
	
		RETURN_FAILED_HRESULT(pIParams->QueryInterface(param.ppi()));
		RETURN_FAILED_HRESULT(param -> get_Meridian (&iMeridian));
	} 
	else if (CTFMODE_AutoMeridian != m_CTFMode)
		iMeridian = m_iMeridian;	// keine speziellen Parameter gegeben

CSCOORD Coords;

	RETURN_FAILED_HRESULT(pPt -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> get_Z (&Coords.Z));

	if (CTF_TransMercator == m_CTFType)	{	// aus GKCoords konvertieren
	CSID Guid;

		RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, m_iStrBreite, iMeridian, &Guid))
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
//				dZOut = dZ;
//				ConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
//				InvConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//				dZOut = dZ;
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	} 
	else if (m_rgChangeEllipse != m_rgEllipseNative) {
	CSID Guid;

		RETURN_FAILED_HRESULT(EnsureGeodCS(m_rgChangeEllipse, &Guid))
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	}
	else {
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
//			Coords.X /= m_dUnitScale;
//			Coords.Y /= m_dUnitScale;
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
//			Coords.X *= m_dUnitScale;
//			Coords.Y *= m_dUnitScale;
			break;

		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	}

	RETURN_FAILED_HRESULT(pPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(pPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> put_Z (Coords.Z));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// in/aus bestimmten Koordinatensystem konvertieren
STDMETHODIMP CCoordTrans::TransformEx2(_DGMPoint *pPt, TRANSDIRECTION Dir, IUnknown *pICS)
{
	if (NULL == pICS)		// ggf. CSOut nicht berücksichtigen
		return Transform (pPt, Dir);

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// gewünschtes Ausgabesystem zum Transformator hinzufügen
WTRiASCS CSOut;
CComBSTR bstrGuid;
CComVariant v;

	RETURN_FAILED_HRESULT(pICS -> QueryInterface(CSOut.ppi()));
	RETURN_FAILED_HRESULT(CSOut -> get_GUID(&bstrGuid));

WTRiASCSTransform CSS;

	RETURN_FAILED_HRESULT(m_CTF -> QueryInterface(CSS.ppi()));
	if (FAILED(CSS -> get_Item (CComVariant(bstrGuid), &v))) {
	// Koordinatensystem als Eingangssystem zum Transformationsobjekt hinzufügen
		THROW_FAILED_HRESULT(CSS -> AddInputCS(CSOut));
		THROW_FAILED_HRESULT(CSOut -> Recompute());
	}

CSCOORD Coords;

	RETURN_FAILED_HRESULT(pPt -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> get_Z (&Coords.Z));

CIID Guid (bstrGuid, CIID::INITCIID_InitFromGuid);

	switch (Dir) {
	case TRANSDIRECTION_FORWARD:	// Transform
		RETURN_FAILED_HRESULT(m_CTF -> TransformInverse ((CSID &)Guid, 1, &Coords, &Coords));
		break;

	case TRANSDIRECTION_INVERSE:	// InvTransform
		RETURN_FAILED_HRESULT(m_CTF -> Transform ((CSID &)Guid, 1, &Coords, &Coords));
		break;

	default:
	case TRANSDIRECTION_IGNORED:
		_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
		return E_UNEXPECTED;
	}

	RETURN_FAILED_HRESULT(pPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(pPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> put_Z (Coords.Z));

	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformCollEx(_DGMPoints *Points, TRANSDIRECTION Dir, IDispatch *pIParam)
{
// alle Punkte der Collection Transformieren
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pIParam)	// keine speziellen Parameter gegeben
		return TransformColl (Points, Dir);

	COM_TRY {
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(Enum.ppu()));

	CComVariant var;

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
			{
				THROW_FAILED_HRESULT(TransformEx (W_DGMPoint(V_UNKNOWN(&var)), Dir, pIParam));
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformCollEx2(_DGMPoints *Points, TRANSDIRECTION Dir, IUnknown *pICS)
{
// alle Punkte der Collection Transformieren
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pICS)	// keine speziellen Parameter gegeben
		return TransformColl (Points, Dir);

	COM_TRY {
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(Enum.ppu()));

	CComVariant var;

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
			{
				THROW_FAILED_HRESULT(TransformEx2(W_DGMPoint(V_UNKNOWN(&var)), Dir, pICS));
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::Native(_DGMPoint * pPt, TRANSDIRECTION Dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//long double dXOut, dYOut, dZOut;
//double dX, dY, dZ;
//int iMeridian = m_iMeridian;

CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, m_iStrBreite, 0, &Guid))

CSCOORD Coords;

	RETURN_FAILED_HRESULT(pPt -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> get_Z (&Coords.Z));

	switch (Dir) {
	case TRANSDIRECTION_FORWARD:	// Metric
//		Coords.X /= m_dUnitScale;
//		Coords.Y /= m_dUnitScale;
		RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
//			if (!GetMeridianGeod (dX, iMeridian))
//				_com_issue_error(E_UNEXPECTED);
//			ConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//			dZOut = dZ;
		break;

	case TRANSDIRECTION_INVERSE:	// Native
		RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
//			if (!GetMeridianGK (dX, iMeridian))	
//				_com_issue_error(E_UNEXPECTED);
//			InvConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//		Coords.X *= m_dUnitScale;
//		Coords.Y *= m_dUnitScale;
		break;

	default:
	case TRANSDIRECTION_IGNORED:
		_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
		return E_UNEXPECTED;
	}

	RETURN_FAILED_HRESULT(pPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(pPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> put_Z (Coords.Z));

	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
// alle Punkte der Collection Transformieren
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(Enum.ppu()));

	CComVariant var;

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
			{
				THROW_FAILED_HRESULT(Native (W_DGMPoint(V_UNKNOWN(&var)), Dir));
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeEx(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch *pIParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pIParam)	// keine speziellen Parameter gegeben
		return Native (pPt, Dir);

//long double dXOut, dYOut, dZOut;
//double dX, dY, dZ;
int iMeridian;

	if (NULL != pIParam) {
	WCTFExContext param (pIParam);		// throws hr

		param -> get_Meridian (&iMeridian);
	} else
		iMeridian = 0;

CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, m_iStrBreite, iMeridian, &Guid))

CSCOORD Coords;

	RETURN_FAILED_HRESULT(pPt -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> get_Z (&Coords.Z));

	switch (Dir) {
	case TRANSDIRECTION_FORWARD:	// Transform
		RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, &Coords, &Coords));
//		dX /= m_dUnitScale;
//		dY /= m_dUnitScale;
//		ConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//		dZOut = dZ;
		break;

	case TRANSDIRECTION_INVERSE:	// InvTransform
		RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, &Coords, &Coords));
//		InvConvertEllipse (m_iStrBreite, iMeridian, dY, dX, &dYOut, &dXOut);
//		dXOut *= m_dUnitScale;
//		dYOut *= m_dUnitScale;
//		dZOut = dZ;
		break;

	default:
	case TRANSDIRECTION_IGNORED:
		_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
		return E_UNEXPECTED;
	}

	RETURN_FAILED_HRESULT(pPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(pPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(pPt -> put_Z (Coords.Z));

	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeCollEx(_DGMPoints *Points, TRANSDIRECTION Dir, IDispatch *pIParam)
{
// alle Punkte der Collection Transformieren
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pIParam)	// keine speziellen Parameter gegeben
		return NativeColl (Points, Dir);

	COM_TRY {
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(Points -> get_NewEnum(Enum.ppu()));

	CComVariant var;

		for (Enum -> Reset(); S_OK == Enum -> Next(1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
			{
				THROW_FAILED_HRESULT(NativeEx (W_DGMPoint(V_UNKNOWN(&var)), Dir, pIParam));
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnung des (karthesischen) Abstandes zweier gegebener Punkte
// Punkte sind in Normalkoordinaten gegeben

STDMETHODIMP CCoordTrans::Distance(_DGMPoint * pPt1, _DGMPoint * pPt2, _DGMPoint ** pDist)
{
// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//double dX1, dX2, dY1, dY2, dZ1, dZ2;
//long double XMin, XMax, YMin, YMax;		// Gauß/Krüger Koordinaten
//int iMeridian = m_iMeridian;

	if (NULL == pDist) 
		return E_POINTER;
	*pDist = NULL;

CSCOORD Coords[2];
CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgEllipseNative, m_iStrBreite, m_iMeridian, &Guid))

	RETURN_FAILED_HRESULT(pPt1 -> get_X (&Coords[0].X));
	RETURN_FAILED_HRESULT(pPt1 -> get_Y (&Coords[0].Y));
	RETURN_FAILED_HRESULT(pPt1 -> get_Z (&Coords[0].Z));
	RETURN_FAILED_HRESULT(pPt2 -> get_X (&Coords[1].X));
	RETURN_FAILED_HRESULT(pPt2 -> get_Y (&Coords[1].Y));
	RETURN_FAILED_HRESULT(pPt2 -> get_Z (&Coords[1].Z));

//		if (!GetMeridianGeod (dX1, iMeridian))
//			_com_issue_error(E_UNEXPECTED);
//	
//		geogau (HA, HB, m_iStrBreite, iMeridian, dY1, dX1, KS, &YMin, &XMin);
//		geogau (HA, HB, m_iStrBreite, iMeridian, dY2, dX2, KS, &YMax, &XMax);
	RETURN_FAILED_HRESULT(m_CTF -> TransformInverse(Guid, 2, Coords, Coords));

W_DGMPoint outPt;

	RETURN_FAILED_HRESULT(outPt.CreateInstance(CLSID_TRiASCSPoint));
	RETURN_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());
	RETURN_FAILED_HRESULT(outPt -> put_X (Coords[1].X - Coords[0].X));
	RETURN_FAILED_HRESULT(outPt -> put_Y (Coords[1].Y - Coords[0].Y));
	RETURN_FAILED_HRESULT(outPt -> put_Z (Coords[1].Z - Coords[0].Z));

// Resultat liefern
	*pDist = outPt.detach();

	return S_OK;
}

STDMETHODIMP CCoordTrans::DistanceEx(
	_DGMPoint *pPt1, _DGMPoint *pPt2, _DGMPoint **ppDist, double *pdDist)
{
// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//double dX1, dX2, dY1, dY2, dZ1, dZ2;
//long double XMin, XMax, YMin, YMax;		// Gauß/Krüger Koordinaten
//int iMeridian = m_iMeridian;

	if (NULL == ppDist) 
		return E_POINTER;
	*ppDist = NULL;
	if (NULL == pdDist)
		return E_POINTER;
	*pdDist = 0.0;

CSCOORD Coords[2];
CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgEllipseNative, m_iStrBreite, m_iMeridian, &Guid))

	RETURN_FAILED_HRESULT(pPt1 -> get_X (&Coords[0].X));
	RETURN_FAILED_HRESULT(pPt1 -> get_Y (&Coords[0].Y));
	RETURN_FAILED_HRESULT(pPt1 -> get_Z (&Coords[0].Z));
	RETURN_FAILED_HRESULT(pPt2 -> get_X (&Coords[1].X));
	RETURN_FAILED_HRESULT(pPt2 -> get_Y (&Coords[1].Y));
	RETURN_FAILED_HRESULT(pPt2 -> get_Z (&Coords[1].Z));

//		if (!GetMeridianGeod (dX1, iMeridian))
//			_com_issue_error(E_UNEXPECTED);
//	
//		geogau (HA, HB, m_iStrBreite, iMeridian, dY1, dX1, KS, &YMin, &XMin);
//		geogau (HA, HB, m_iStrBreite, iMeridian, dY2, dX2, KS, &YMax, &XMax);
	RETURN_FAILED_HRESULT(m_CTF -> TransformInverse(Guid, 2, Coords, Coords));

W_DGMPoint outPt;

	RETURN_FAILED_HRESULT(outPt.CreateInstance(CLSID_TRiASCSPoint));
	RETURN_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());
	RETURN_FAILED_HRESULT(outPt -> put_X (Coords[1].X - Coords[0].X));
	RETURN_FAILED_HRESULT(outPt -> put_Y (Coords[1].Y - Coords[0].Y));
	RETURN_FAILED_HRESULT(outPt -> put_Z (Coords[1].Z - Coords[0].Z));

// Resultate liefern
	*ppDist = outPt.detach();
	*pdDist = sqrt(Sqr(Coords[1].X - Coords[0].X) + 
		Sqr(Coords[1].Y - Coords[0].Y) + Sqr(Coords[1].Z - Coords[0].Z));

	return S_OK;
}

// Liefert den Punkt, der einen vorgegebenen Abstand zum ersten Punkt besitzt
// Läuft auf stetigen Koordinaten
STDMETHODIMP CCoordTrans::DistancePoint(_DGMPoint * pPt1, _DGMPoint * Delta, _DGMPoint * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

//	double dX, dY, dZ;
//	long double XIn, YIn, ZIn;		// Gauß/Krüger Koordinaten
//	long double XOut, YOut, ZOut;
//	int iMeridian = m_iMeridian;

CSCOORD Coords;
CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgEllipseNative, m_iStrBreite, 0, &Guid))

	RETURN_FAILED_HRESULT(pPt1 -> get_X (&Coords.X));
	RETURN_FAILED_HRESULT(pPt1 -> get_Y (&Coords.Y));
	RETURN_FAILED_HRESULT(pPt1 -> get_Z (&Coords.Z));

//	if (!GetMeridianGeod (dX, iMeridian))
//		_com_issue_error(E_UNEXPECTED);

//	1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
//	geogau (HA, HB, m_iStrBreite, iMeridian, dY, dX, KS, &YIn, &XIn);
//	ZIn = dZ;
	RETURN_FAILED_HRESULT(m_CTF -> TransformInverse(Guid, 1, &Coords, &Coords));

// 2. neuen Punkt berechnen
double dX, dY, dZ;

	RETURN_FAILED_HRESULT(Delta -> get_X(&dX));
	RETURN_FAILED_HRESULT(Delta -> get_Y(&dY));
	RETURN_FAILED_HRESULT(Delta -> get_Z(&dZ));
	Coords.X += dX;
	Coords.Y += dY;
	Coords.Z += dZ;

// 3. Koordinaten zurückkonvertieren
//	gaugeo (HA, HB, m_iStrBreite, iMeridian, double(YIn), double(XIn), KS, &YOut, &XOut);
//	ZOut = ZIn;
	RETURN_FAILED_HRESULT(m_CTF -> Transform(Guid, 1, &Coords, &Coords));

W_DGMPoint outPt;

	RETURN_FAILED_HRESULT(outPt.CreateInstance(CLSID_TRiASCSPoint));
	RETURN_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());
	RETURN_FAILED_HRESULT(outPt -> put_X (Coords.X));
	RETURN_FAILED_HRESULT(outPt -> put_Y (Coords.Y));
	RETURN_FAILED_HRESULT(outPt -> put_Z (Coords.Z));

// Resultat liefern
	*pVal = outPt.detach();

	return S_OK;
}

STDMETHODIMP CCoordTrans::ToStrings(_DGMPoint * Point, BSTR * XStr, BSTR * YStr, BSTR * ZStr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

char cbFormat[20];
char cbBuffer[256];
char cbSek[32];
double Value;
short sign;
short lGrad;
short lMin;
double dSek;

	if (0 == m_iPrec || CTF_TransMercator != m_CTFType)
		strcpy (cbFormat, "%02ld");
	else
		wsprintf (cbFormat, "%%02ld.%%0%dlu" /*"%%%02d.%df"*/, m_iPrec);

	COM_TRY {
	CComBSTR bstr;

	// X-Koordinate
		if (NULL != XStr) {
			THROW_FAILED_HRESULT(Point -> get_X(&Value));

			if (CTF_Geodetical == m_CTFType)	{
				Value *= m_dUnitScale;

				sign = Value < 0;
				Value = fabs(Value);

				lGrad = (short)(Value/3600.0);
				lMin = (short)(Value/60.0 - (double)lGrad * 60.0);
				dSek = Value - (double)lGrad * 3600.0 - (double)lMin * 60.0;

				if (dSek >= 60.0) { dSek -= 60.0; lMin++; }
				if (lMin >= 60) { lMin -= 60; lGrad++; }

				DtoACTF (cbSek, cbFormat, m_iPrec, dSek);
				wsprintf (cbBuffer, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, sign ? g_cbWL : g_cbOL);
			} 
			else {		
			// !CTF_TransMercator
				DtoACTF (cbBuffer, cbFormat, m_iPrec, Value);
			}

			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*XStr = bstr.Detach();
		}

	// Y-Koordinate
		if (NULL != YStr) {
			THROW_FAILED_HRESULT(Point -> get_Y(&Value));

			if (CTF_Geodetical == m_CTFType)	{
				Value *= m_dUnitScale;

				sign = Value < 0;
				Value = fabs(Value);

				lGrad = (short)(Value/3600.0);
				lMin = (short)(Value/60.0 - (double)lGrad * 60.0);
				dSek = Value - (double)lGrad * 3600.0 - (double)lMin * 60.0;

				if (dSek >= 60.0) { dSek -= 60.0; lMin++; }
				if (lMin >= 60) { lMin -= 60; lGrad++; }

				DtoACTF (cbSek, cbFormat, m_iPrec, dSek);
				wsprintf (cbBuffer, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, sign ? g_cbSB : g_cbNB);
			} else {
			// !CTF_TransMercator
				DtoACTF (cbBuffer, cbFormat, m_iPrec, Value);
			}
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*YStr = bstr.Detach();
		}

	// Z-Koordinate (wie gehabt dezimal oder ?!)
		if (NULL != ZStr) {
			THROW_FAILED_HRESULT(Point -> get_Z(&Value));
			DtoACTF (cbBuffer, cbFormat, m_iPrec, Value);
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*ZStr = bstr.Detach();
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren eines in der Darstellungsform gegeben Koordinatenwertes
static bool SkipWhites (char *& pS) 
{
	while (*pS) {
		if (isascii(*pS) && isdigit(*pS)) 
			break;
		pS++;
	}
	return *pS != '\0';
}

static bool AtoI (char *& pS, short *iR)
{
	*iR = 0;
	while (*pS && isascii(*pS) && isdigit(*pS))
		*iR = (*iR*10) + *pS++ - '0';
	return *pS != '\0';
}

static double GtoValue (char *pBuffer)
{
char *cptr = pBuffer;
short lGrad = 0;
short lMin = 0;

	SkipWhites (cptr);
	if (!AtoI (cptr, &lGrad) || !SkipWhites (cptr))
		return lGrad * 3600.0;
	if (!AtoI (cptr, &lMin) || !SkipWhites (cptr))
		return lGrad * 3600.0 + lMin * 60.0;

double dSek = atof (cptr);	//	AtoI (cptr, &lSek);

	return lGrad * 3600.0 + lMin * 60.0 + dSek;
}

STDMETHODIMP CCoordTrans::ToPoint(BSTR XStr, BSTR YStr, BSTR ZStr, _DGMPoint **ppIPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// JG990121 Parametercheck 
	ASSERT(ppIPoint);
	if (NULL == ppIPoint)
		return E_POINTER;

	USES_CONVERSION;
	COM_TRY {
	W_DGMPoint Point (CLSID_TRiASCSPoint);
	CSCOORD Coords;

		THROW_FAILED_HRESULT(WPersistStreamInit(Point) -> InitNew());
		if (CTF_TransMercator == m_CTFType) {
			Coords.X = atof (OLE2A(XStr));
			Coords.Y = atof (OLE2A(YStr));
		} 
		else {
		// Strings sind bereits geodätische Koordinaten
			Coords.X = GtoValue (OLE2A(XStr)) / m_dUnitScale;
			Coords.Y = GtoValue (OLE2A(YStr)) / m_dUnitScale;
		}
	
		if (SysStringLen (ZStr) > 0)
			Coords.Z = atof (OLE2A(ZStr));
		else
			Coords.Z = 0.0;

		THROW_FAILED_HRESULT(Point -> SetPoint ((double *)&Coords));
		*ppIPoint = Point.detach();

	} COM_CATCH;
	return S_OK;
}

// Funktionen, die MittelMeridian berechnen -----------------------------------
// Berechnet aus geod. Koordinate den ZielMeridian
BOOL CCoordTrans::GetMeridianGeod (double dX, int &riMeridian) 
{
	if (CTFMODE_AutoMeridian == m_CTFMode)
	{
		if  (3 == m_iStrBreite)
			riMeridian = (int)((dX/3600.0 + 1.5)/3) * 3;
		else
			riMeridian = (int)((dX/3600.0)/6) * 6 + 3;
	} else 
		riMeridian = m_iMeridian;		// vorgegebenen verwenden

	return TRUE;
}

BOOL CCoordTrans::GetMeridianGK (double dX, int &riMeridian) 
{
	if (CTFMODE_AutoMeridian == m_CTFMode)
	{
		if (dX < 0 || dX > 7000000.0) 
			return FALSE;

		if (3 == m_iStrBreite)
			riMeridian = (int)(dX/1000000.0) * 3;
		else
			riMeridian = (int)(dX/1000000.0) * 6 - 3;
	} else 
		riMeridian = m_iMeridian;		// vorgegebenen verwenden

	return TRUE;
}

STDMETHODIMP CCoordTrans::get_Envelope(LPDISPATCH * pVal)	// JG990120
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Veränderungen zurückschreiben und sich selbst neu initialisieren
HRESULT CCoordTrans::UpdateNewSettings (bool fNative, bool fAutoMeridian)
{
// erstmal Rundspruch schicken
VARIANT_BOOL fChange = VARIANT_FALSE;

	RETURN_FAILED_HRESULT(Fire_CoordParamsToChange (this, &fChange));
	if (fChange != VARIANT_FALSE)
		return S_FALSE;		// abgebrochen oder Fehler
	RETURN_FAILED_HRESULT(Fire_ChangingCoordParams (this));

// ShowGKCoords
int iShow = 0;

	if (fNative)
		iShow = 0;
	else if (fAutoMeridian)
		iShow = 2;
	else
		iShow = 1;
	
// 0: geodätische Koordinaten anzeigen
// 1: GK mit vorgegebenem Meridian anzeigen
// 2: GK mit automatisch ausgewähltem Meridian anzeigen
// 0x04 bzw. 0x08: mit Übergang in den jeweils anderen Ellipsoid
	if (GetChangedEllipse() > 0) {
		ASSERT(GetAllowChangeEllipse());
		iShow |= 0x01 << (GetChangedEllipse()+1);
	} 

	ASSERT(m_PropBase.IsValid());

WTRiASProperties Props;

	RETURN_FAILED_HRESULT(m_PropBase -> get_Properties (Props.ppi()));

	SetPropertyAndType (Props, g_cbShowGKCoords, iShow, PROPERTY_TYPE_System, true);

// CoordMeridian, CoordStrBreite
	if (!fNative) {
		if (!fAutoMeridian)
			SetPropertyAndType (Props, g_cbCoordMeridian, m_iMeridian, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);
		else
			SetPropertyAndType (Props, g_cbCoordMeridian, g_cbAutoSelect, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);

		SetPropertyAndType (Props, g_cbCoordStrBreite, m_iStrBreite, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);
	}

// CoordPrecision
	SetPropertyAndType (Props, g_cbCoordPrecision, m_iPrec, PROPERTY_TYPE_System, true); 

// alle informieren
	RETURN_FAILED_HRESULT(Fire_ChangedCoordParams (this));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für Koordinatentransformations-Pipe
HRESULT CCoordTrans::AddOutputCS()
{
	_ASSERTE(m_CTF.IsValid());

	COM_TRY {
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CS -> put_CoordSystemType(tcsCS_Geographic));

	// Geodätische Grundlage initialisieren
	TRIASCSGEODETICDATUM rgDatum = GetGeodDatum(m_rgEllipseNative, true);

		{
		WTRiASCSGCS GCS;

			THROW_FAILED_HRESULT(CS -> get_GeographicCS(GCS.ppi()));
			THROW_FAILED_HRESULT(GCS -> put_GeodeticDatum(rgDatum));
			THROW_FAILED_HRESULT(GCS -> put_PrimeMeridian(tcsPM_Greenwich));
			THROW_FAILED_HRESULT(GCS -> put_UnitOfAngle(m_rgUOA));
		}

	// Datumsparameter einstellen
		{
		WTRiASCSDatumTransformation DTrans;

			THROW_FAILED_HRESULT(CS -> get_DatumTransformation(DTrans.ppi()));
			THROW_FAILED_HRESULT(DTrans -> put_GeodeticDatum(rgDatum));
			THROW_FAILED_HRESULT(DTrans -> put_TransformationAlgorithm(
				tcsDTA_PositionVector7ParamTransformation));
		}
	
	// CS ist jetzt fertig initialisiert
		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> putref_OutputCS(CS));
		THROW_FAILED_HRESULT(CS -> Recompute());

	} COM_CATCH;
	return S_OK;
}

namespace {
	inline
	ULONG MakeCSKey (TRIASCSGEODETICDATUM rgEllipse, int iStrBreite, 
		int iMeridian)
	{
		return MAKELONG(rgEllipse, MAKEWORD(iStrBreite, iMeridian));
	}
}

HRESULT CCoordTrans::EnsureGeodCS (COORDTRANSELLIPSE rgEllipse, CSID *pCsId)
{
	_ASSERTE(NULL != pCsId);
	*pCsId = (CSID &)GUID_NULL;

	COM_TRY {
	// zuerst nachsehen, ob dieses CS schon bekannt ist
	TRIASCSGEODETICDATUM rgDatum = GetGeodDatum(rgEllipse);
	ULONG ulCSKey = MakeCSKey (rgDatum, 0, 0);
	CCSMap::iterator it = m_CSMap.find(ulCSKey);

		if (it != m_CSMap.end()) {
			*pCsId = (*it).second;
			return S_OK;
		}

	// jetzt neu erzeugen und fürs nächste Mal speichern
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CS -> put_CoordSystemType(tcsCS_Geographic));

	// Geodätische Grundlage initialisieren
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

	CComBSTR bstrGuid;

		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> AddInputCS(CS));
		THROW_FAILED_HRESULT(CS -> Recompute());
		THROW_FAILED_HRESULT(CS -> get_GUID(&bstrGuid));

	CIID Guid(bstrGuid, CIID::INITCIID_InitFromGuid);

		m_CSMap.insert(CCSMap::value_type(ulCSKey, *(CSID *)&Guid));
		*pCsId = *(CSID *)&Guid;

	} COM_CATCH;
	return S_OK;
}

namespace {
	inline
	double GetLongitude (int iMeridian)
	{
		return iMeridian * 3600.0;
	}
	inline
	double GetFalseX (int iMeridian, int iZoneWidth)
	{
		if (3 == iZoneWidth)
			return (iMeridian / iZoneWidth) * 1000000.0 + 500000.0;

		_ASSERTE(6 == iZoneWidth);
		return ((iMeridian + 3) / iZoneWidth) * 1000000.0 + 500000.0;
	}
}

HRESULT CCoordTrans::EnsureGKCS (COORDTRANSELLIPSE rgEllipse, int iZoneWidth, 
	int iMeridian, CSID *pCsId)
{
	_ASSERTE(NULL != pCsId);
	*pCsId = (CSID &)GUID_NULL;

	COM_TRY {
	// zuerst nachsehen, ob dieses CS schon bekannt ist
	TRIASCSGEODETICDATUM rgDatum = GetGeodDatum(rgEllipse);
	ULONG ulCSKey = MakeCSKey (rgDatum, iZoneWidth, iMeridian);
	CCSMap::iterator it = m_CSMap.find(ulCSKey);

		if (it != m_CSMap.end()) {
			*pCsId = (*it).second;
			return S_OK;
		}

	// jetzt neu erzeugen und fürs nächste Mal speichern
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CS -> put_CoordSystemType(tcsCS_Projected));
	// Geodätische Grundlage initialisieren

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
				tcsPA_TransverseMercator));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, GetScaleFactor(rgEllipse)));

			if (0 != iMeridian) {
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, GetLongitude(iMeridian)));
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_FalseEasting, GetFalseX(iMeridian, iZoneWidth)));
			}
			else {
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_ZoneWidth, iZoneWidth));
			}

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, 0.0));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_FalseNorthing, 0.0));
			THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(tcsUOL_Metre));
		}

	CComBSTR bstrGuid;

		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> AddInputCS(CS));
		THROW_FAILED_HRESULT(CS -> Recompute());
		THROW_FAILED_HRESULT(CS -> get_GUID(&bstrGuid));

	CIID Guid(bstrGuid, CIID::INITCIID_InitFromGuid);

		m_CSMap.insert(CCSMap::value_type(ulCSKey, *(CSID *)&Guid));
		*pCsId = *(CSID *)&Guid;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::get_CoordTransformPipe (IDispatch **ppIPipe)
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


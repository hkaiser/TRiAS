// @doc
// @module GKCoordTransBase.cpp | Implementation of CGKCoordTransBase

#include "stdafx.h"

#include <Com/PropertyHelper.h>

#include "GKCtf_COM.h"
#include "CoordTransBase.h"
#include "Strings.h"
#include "Wrapper.h"

//#include "CtfGeoGK.h"
#include "CTFExContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(Dispatch);

DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSPCS);
DefineSmartInterface(TRiASCSDatumTransformation);

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

///////////////////////////////////////////////////////////////////////////////
// JG990127 for each inherited class the same
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

STDMETHODIMP CCoordTrans::InitCoordTransform(IUnknown *pIUnk)	// checked
{
// Testen, ob Ellipsoidübergang erlaubt werden kann
#if _TRiAS_VER < 0x0400
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
#endif _TRiAS_VER < 0x0400

// new from GeodObj	JG990120
	COM_TRY {
		THROW_FAILED_HRESULT(pIUnk -> QueryInterface(IID_ITRiASPropertyBase, m_PropBase.ppv()));
		ASSERT(m_PropBase.IsValid());

	// aktueller AnzeigeMode: ShowGKCoords
	WTRiASProperties Props;
		
		THROW_FAILED_HRESULT(m_PropBase -> get_Properties (Props.ppi()));

		if (!m_fAllowChangeEllipse)		// muß zuerst initialisiert werden
			m_fAllowChangeEllipse =	(0 == GetProperty (Props, g_cbSysAdminMode, 0, LOCALE_ENGLISH) ? false : true);

	// Mittelmeridian und Streifenbreite der GeoDB aus Header holen
		m_iStreifenDB = GetProperty (Props, g_cbCoordStrBreite, 3, LOCALE_ENGLISH);
	
	// PlausibilitätsTests
		if (m_iStreifenDB != 3 && m_iStreifenDB != 6)	
			m_iStreifenDB = 3;

	// abgeleitete Klasse fertig initialisieren
		InitVars (Props);	// default: CTF_TransMercator/CTFMODE_SelectMeridian

		m_iMeridianDB = GetProperty (Props, g_cbCoordMeridian, 12, LOCALE_ENGLISH);
		if (0 != GetProperty (Props, g_cbCoordAutoMeridian, 12, LOCALE_ENGLISH) && 0 == m_iMeridianDB) {
		// automode GK System
			m_iMeridianDB = 0;
			m_iMeridian = 0;
		}
		else {
			if (3 == m_iStreifenDB && (m_iMeridianDB / 3) * 3 != m_iMeridianDB)
				m_iMeridianDB = 12;	// fehlerhafter Mittelmeridian
			else if (6 == m_iStreifenDB && 
				 ((m_iMeridianDB -3) / 6) * 6 != m_iMeridianDB -3)
				m_iMeridianDB = 15;	// fehlerhafter Mittelmeridian
		}

	// Mittelmeridian und Streifenbreite der _Anzeige_ aus Header holen
		m_iStrBreite = GetProperty (Props, g_cbCTFStreifenView, m_iStreifenDB, LOCALE_ENGLISH);

	// PlausibilitätsTest
		if (m_iStrBreite != 3 && m_iStrBreite != 6)		
			m_iStrBreite = m_iStreifenDB;

		if (m_CTFMode != CTFMODE_AutoMeridian) {	// JG990128 CoordMeriadian nur auslesen, wenn notwendig
			m_iMeridian = GetProperty (Props, g_cbCTFMeridianView, m_iMeridianDB, LOCALE_ENGLISH);
			
		// PlausibilitätsTest
			if (m_iStrBreite == 3 && (m_iMeridian / 3) * 3 != m_iMeridian)
				m_iMeridian = m_iMeridianDB;		// fehlerhafter Mittelmeridian
			else if (m_iStrBreite == 6 && ((m_iMeridian -3) / 6) * 6 != m_iMeridian -3)
				m_iMeridian = m_iMeridianDB;		// fehlerhafter Mittelmeridian
		}

	// DarstellungsGenauigkeit aus Header holen
		m_iPrec = GetProperty (Props, g_cbCoordPrecision, 3, LOCALE_ENGLISH);

	// SkalierungsKoeffizienten aus Header holen
		m_dScale = GetProperty (Props, g_cbCoordScaling, 1.0, LOCALE_ENGLISH);
		if (m_dScale == 0.0)		
			m_dScale = 1.0;

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

STDMETHODIMP CCoordTrans::ReInitCoordTransform(IUnknown *pIUnk)	// checked
{
	return InitCoordTransform(pIUnk);
}

STDMETHODIMP CCoordTrans::TermCoordTransform() // checked
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_PropBase.Assign(NULL);	// JG990120

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
	m_fInitialized = false;		// JG990126 from geod.
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
// Berechnnen des bildausschnittsabhängigen Isotropie-Koeffizienten 
// HilfsFunktionen ------------------------------------------------------------
inline long double Q (long double x)
{
	return x * x; 
}

inline long double D (long double dX, long double dY)
{ 
	return sqrtl (Q(dX) + Q(dY)); 
}

STDMETHODIMP CCoordTrans::get_AspectRatio(_DGMPoint *pPt1, _DGMPoint *pPt2, double *pVal) // checked
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pVal);

// 3. Berechnen des Isotropiekoefizienten
	*pVal = 1.0;

	return S_OK;
}

STDMETHODIMP CCoordTrans::get_IsMetric(VARIANT_BOOL * pVal)
{
	CHECKPOINTER(pVal);

	// change if geod. Output is possible
	*pVal = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CCoordTrans::get_CanConfig(VARIANT_BOOL * pVal)// checked 
{
	CHECKPOINTER(pVal);

	*pVal = VARIANT_TRUE;	// JG990125	// config
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Methods
STDMETHODIMP CCoordTrans::Transform(_DGMPoint *pPt, TRANSDIRECTION Dir)	// checked
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

double inCoords[3];	// dx,dy,dz

	CHECKPOINTER(pPt);
	COM_TRY {
		THROW_FAILED_HRESULT(pPt -> GetPoint(inCoords));
		THROW_FAILED_HRESULT(InnerTransform(inCoords, Dir));
		THROW_FAILED_HRESULT(pPt -> SetPoint(inCoords));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::TransformColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(Points);

// alle Punkte der Collection transformieren
	COM_TRY {
		double coords[3];
		long iCount;

		THROW_FAILED_HRESULT(Points->get_Count(&iCount));
		for (long i = 0; i<iCount; i++)
		{
			THROW_FAILED_HRESULT(Points->GetPoint(i, coords));
			THROW_FAILED_HRESULT(InnerTransform(coords, Dir));
			THROW_FAILED_HRESULT(Points->SetPoint(i, coords));
		}
	} COM_CATCH;
	return S_OK;
}

// JG990126 neu implementiert, angepaßt an GK
STDMETHODIMP CCoordTrans::TransformParameter(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pVal);

double dX;
int iMeridian = m_iMeridian;

	COM_TRY {
		THROW_FAILED_HRESULT(pPt -> get_X (&dX));

		if (CTF_Geodetical == m_CTFType) {		// aus geod. Coords konvertieren
			switch (Dir) {
			case TRANSDIRECTION_FORWARD:	// Transform
				// JG990126 fcall angepaßt Geod->GK
				if (!GetMeridianGK (dX, iMeridian))	
					_com_issue_error(E_UNEXPECTED);
				break;

			case TRANSDIRECTION_INVERSE:	// InvTransform
				// JG990126 fcall angepaßt GK->Geod
				if (!GetMeridianGeod (dX, iMeridian))	
					_com_issue_error(E_UNEXPECTED);
				break;

			default:
			case TRANSDIRECTION_IGNORED:
				ASSERT(Dir != TRANSDIRECTION_IGNORED);
				_com_issue_error(E_UNEXPECTED);
			}
		} else {
			_ASSERTE(CTF_Native == m_CTFType);
			switch (Dir) {
			case TRANSDIRECTION_FORWARD:	// Transform
			case TRANSDIRECTION_INVERSE:	// InvTransform
				if (!GetMeridianGK (dX, iMeridian))	
					_com_issue_error(E_UNEXPECTED);
				break;

			default:
			case TRANSDIRECTION_IGNORED:
				ASSERT(Dir != TRANSDIRECTION_IGNORED);
				_com_issue_error(E_UNEXPECTED);
			}
		}
	
	WCTFExContext context(CLSID_CTFExContext);

		THROW_FAILED_HRESULT(context -> put_Meridian (iMeridian));
		*pVal = context.detach();	// JG990126

	} COM_CATCH;
	return S_OK;
}

// JG990126	checked and reworked
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
	CHECKPOINTER(pVal);

double dX;
int iMeridian = m_iMeridian;

	COM_TRY {
		THROW_FAILED_HRESULT(pPt -> get_X (&dX));

		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			// JG990126 fcall angepaßt Geod->GK
			if (!GetMeridianGK (dX, iMeridian))
				_com_issue_error(E_UNEXPECTED);
			break;

		case TRANSDIRECTION_INVERSE:	// InvTransform
			// JG990126 fcall angepaßt GK->Geod
			if (!GetMeridianGeod (dX, iMeridian))	
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
// JG990121 added from Geod-Project, this will be called without pIParams
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// keine Parameter -> normale Transformation
//	if (NULL == pIParams)
//		return Transform(pPt, Dir);

// JG990120
	CHECKPOINTER(pPt);
	
	COM_TRY {
	int iMeridian = 0;
	WCTFExContext param (pIParams);

		if (param.IsValid())
		{
			THROW_FAILED_HRESULT(param -> get_Meridian (&iMeridian));
		}

	double inCoords[3];	// dx,dy,dz

		THROW_FAILED_HRESULT(pPt -> GetPoint(inCoords));
		THROW_FAILED_HRESULT(InnerTransform(inCoords, Dir, iMeridian));
		THROW_FAILED_HRESULT(pPt -> SetPoint(inCoords));
	} COM_CATCH;
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

STDMETHODIMP CCoordTrans::TransformCollEx(_DGMPoints * Points, TRANSDIRECTION Dir, IDispatch *pIParams)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// keine Parameter -> normale Transformation
	if (NULL == pIParams)
		return TransformColl(Points, Dir);

// alle Punkte der Collection transformieren
	COM_TRY {
	long iCount = 0;
		
		THROW_FAILED_HRESULT(Points->get_Count(&iCount));

	int	iMeridian = 0;
	WCTFExContext param( pIParams );
	
		THROW_FAILED_HRESULT(param -> get_Meridian (&iMeridian));
		for (long i = 0; i<iCount; i++) {
		double coords[3];

			THROW_FAILED_HRESULT(Points->GetPoint (i, coords));
			THROW_FAILED_HRESULT(InnerTransform (coords, Dir, iMeridian));
			THROW_FAILED_HRESULT(Points->SetPoint (i, coords));
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
	CHECKPOINTER(pPt);

// alle Punkte der Collection transformieren
	COM_TRY {
	// den Meridian anhand des ersten Punktes bestimmen
	double coords[3];
	int iMeridian = 0;
		
		THROW_FAILED_HRESULT(pPt -> GetPoint(coords));
		if (!GetMeridianGK(coords[0], iMeridian))
			_com_issue_error(E_UNEXPECTED);

		THROW_FAILED_HRESULT(InnerNative(coords, Dir, iMeridian));
		THROW_FAILED_HRESULT(pPt -> SetPoint(coords));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeColl(_DGMPoints * Points, TRANSDIRECTION Dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(Points);

// alle Punkte der Collection transformieren
	COM_TRY {
	// den Meridian anhand des ersten Punktes bestimmen
	double coords[3];
	long iCount = 0;
	int iMeridian;

		THROW_FAILED_HRESULT(Points -> GetPoint(0, coords));
		if (!GetMeridianGK(coords[0], iMeridian))
			_com_issue_error(E_UNEXPECTED);

		THROW_FAILED_HRESULT(Points -> get_Count(&iCount));
		for (long i = 0; i < iCount; i++)
		{
			THROW_FAILED_HRESULT(Points->GetPoint(i, coords));
			THROW_FAILED_HRESULT(InnerNative(coords, Dir, iMeridian));
			THROW_FAILED_HRESULT(Points->SetPoint(i, coords));
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeEx(_DGMPoint * pPt, TRANSDIRECTION Dir, IDispatch *pIParam)
{
	if (NULL == pIParam)	// keine speziellen Parameter gegeben
		return Native(pPt, Dir);

	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pPt);

// alle Punkte der Collection transformieren
	COM_TRY {
	// den Meridian bestimmen
	double coords[3];
	int iMeridian = m_iMeridian;

//		if (CTFMODE_AutoMeridian == m_CTFMode)
		{
			THROW_FAILED_HRESULT(WCTFExContext(pIParam) -> get_Meridian (&iMeridian));
		}

		THROW_FAILED_HRESULT(pPt->GetPoint(coords));
		THROW_FAILED_HRESULT(InnerNative(coords, Dir, iMeridian));
		THROW_FAILED_HRESULT(pPt->SetPoint(coords));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::NativeCollEx(_DGMPoints * Points, TRANSDIRECTION Dir, IDispatch *pIParam)
{
	if (NULL == pIParam)	// keine speziellen Parameter gegeben
		return NativeColl (Points, Dir);

	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(Points);

// alle Punkte der Collection transformieren
	COM_TRY {
	// den Meridian bestimmen
	double coords[3];
	long iCount;
	int iMeridian = m_iMeridian;

		if (CTFMODE_AutoMeridian == m_CTFMode)
		{
			THROW_FAILED_HRESULT(WCTFExContext(pIParam) -> get_Meridian (&iMeridian));
		}

		THROW_FAILED_HRESULT(Points->get_Count(&iCount));
		for (long i = 0; i < iCount; i++)
		{
			THROW_FAILED_HRESULT(Points->GetPoint(i, coords));
			THROW_FAILED_HRESULT(InnerNative(coords, Dir, iMeridian));
			THROW_FAILED_HRESULT(Points->SetPoint(i, coords));
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnung des (karthesischen) Abstandes zweier gegebener Punkte
// Punkte sind in Normalkoordinaten gegeben
// Edited by JG990121	Ausgangspunkte in GK stetig
STDMETHODIMP CCoordTrans::Distance(_DGMPoint * pPt1, _DGMPoint * pPt2, _DGMPoint ** pDist)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12) JG entfällt, haben wir schn
double dX1, dX2, dY1, dY2, dZ1, dZ2;

	CHECKPOINTER(pDist);

	COM_TRY {
	W_DGMPoint outPt (CLSID_TRiASCSPoint);

		THROW_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());

		THROW_FAILED_HRESULT(pPt1 -> get_X (&dX1));
		THROW_FAILED_HRESULT(pPt1 -> get_Y (&dY1));
		THROW_FAILED_HRESULT(pPt1 -> get_Z (&dZ1));
		THROW_FAILED_HRESULT(pPt2 -> get_X (&dX2));
		THROW_FAILED_HRESULT(pPt2 -> get_Y (&dY2));
		THROW_FAILED_HRESULT(pPt2 -> get_Z (&dZ2));

// #pragma MSG("JG990127 Muß hier die Skalierung reinberechnet werden?"): ja s.u.
		THROW_FAILED_HRESULT(outPt -> put_X( (dX2 - dX1) / m_dScale ));
		THROW_FAILED_HRESULT(outPt -> put_Y( (dY2 - dY1) / m_dScale ));
		THROW_FAILED_HRESULT(outPt -> put_Z( (dZ2 - dZ1) / m_dScale ));

	// Resultat liefern
		*pDist = outPt.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCoordTrans::DistanceEx(
	_DGMPoint * pPt1, _DGMPoint * pPt2, _DGMPoint **ppDist, double *pdDist)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12) JG entfällt, haben wir schn
double dX1, dX2, dY1, dY2, dZ1, dZ2;

	CHECKPOINTER(ppDist);
	CHECKPOINTER(pdDist);

	COM_TRY {
	W_DGMPoint outPt (CLSID_TRiASCSPoint);

		THROW_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());

		THROW_FAILED_HRESULT(pPt1 -> get_X (&dX1));
		THROW_FAILED_HRESULT(pPt1 -> get_Y (&dY1));
		THROW_FAILED_HRESULT(pPt1 -> get_Z (&dZ1));
		THROW_FAILED_HRESULT(pPt2 -> get_X (&dX2));
		THROW_FAILED_HRESULT(pPt2 -> get_Y (&dY2));
		THROW_FAILED_HRESULT(pPt2 -> get_Z (&dZ2));

	double dDeltaX = (dX2 - dX1) / m_dScale;
	double dDeltaY = (dY2 - dY1) / m_dScale;
	double dDeltaZ = (dZ2 - dZ1) / m_dScale;

		THROW_FAILED_HRESULT(outPt -> put_X(dDeltaX));
		THROW_FAILED_HRESULT(outPt -> put_Y(dDeltaY));
		THROW_FAILED_HRESULT(outPt -> put_Z(dDeltaZ));

	// Resultate liefern
		*ppDist = outPt.detach();
		*pdDist = sqrt(Sqr(dDeltaX) + Sqr(dDeltaY) + Sqr(dDeltaZ));

	} COM_CATCH;
	return S_OK;
}

// Liefert den Punkt, der einen vorgegebenen Abstand zum ersten Punkt besitzt
// Berechnung über stetigen Koordinaten
//  Edited by JG990121
//		Die Konvertierung fallen weg
STDMETHODIMP CCoordTrans::DistancePoint(_DGMPoint * Point, _DGMPoint * Delta, _DGMPoint * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pVal);

	COM_TRY {
	double dX, dY, dZ;
	double dXIn, dYIn, dZIn;		// Gauß/Krüger Koordinaten
	W_DGMPoint outPt (CLSID_TRiASCSPoint);

		THROW_FAILED_HRESULT(WPersistStreamInit(outPt) -> InitNew());

		THROW_FAILED_HRESULT(Point -> get_X(&dXIn));
		THROW_FAILED_HRESULT(Point -> get_Y(&dYIn));
		THROW_FAILED_HRESULT(Point -> get_Z(&dZIn));

	// 2. neuen Punkt berechnen
		THROW_FAILED_HRESULT(Delta -> get_X(&dX));
		THROW_FAILED_HRESULT(Delta -> get_Y(&dY));
		THROW_FAILED_HRESULT(Delta -> get_Z(&dZ));

	// 3. Koordinaten zurückkonvertieren
		THROW_FAILED_HRESULT(outPt -> put_X(dXIn + (dX * m_dScale)));
		THROW_FAILED_HRESULT(outPt -> put_Y(dYIn + (dY * m_dScale)));
		THROW_FAILED_HRESULT(outPt -> put_Z(dZIn + (dZ * m_dScale)));

	// Resultat liefern
		*pVal = outPt.detach();

	} COM_CATCH;
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

	if (0 == m_iPrec)
		strcpy (cbFormat, "%02ld");
	else
		wsprintf (cbFormat, "%%02ld.%%0%dlu" /*"%%%02d.%df"*/, m_iPrec);

	COM_TRY {
	CComBSTR bstr;

		// X-Koordinate
		if (NULL != XStr)
		{
			THROW_FAILED_HRESULT(Point -> get_X(&Value));
	
			if (CTF_Geodetical == m_CTFType)	// JG990126
			{
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
			else	// !CTF_TransMercator
			{
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

			if (CTF_Geodetical == m_CTFType)	// JG990126
			{
				sign = Value < 0;
				Value = fabs(Value);

				lGrad = (short)(Value/3600.0);
				lMin = (short)(Value/60.0 - (double)lGrad * 60.0);
				dSek = Value - (double)lGrad * 3600.0 - (double)lMin * 60.0;

				if (dSek >= 60.0) { dSek -= 60.0; lMin++; }
				if (lMin >= 60) { lMin -= 60; lGrad++; }

				DtoACTF (cbSek, cbFormat, m_iPrec, dSek);
				wsprintf (cbBuffer, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, sign ? g_cbSB : g_cbNB);
			}
			else	// !CTF_TransMercator
			{
				DtoACTF (cbBuffer, cbFormat, m_iPrec, Value);
			}
			bstr = cbBuffer;
			if (!bstr) 
				_com_issue_error(E_OUTOFMEMORY);
			*YStr = bstr.Detach();
		}

	// Z-Koordinate (wie gehabt dezimal oder ?!)
		if (NULL != ZStr)
		{
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

// JG990121 renamed Param Point to ppIPoint 
STDMETHODIMP CCoordTrans::ToPoint(BSTR XStr, BSTR YStr, BSTR ZStr, _DGMPoint **ppIPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// JG990121 Parametercheck 
	CHECKPOINTER(ppIPoint);
	USES_CONVERSION;

	COM_TRY {
	double Coords[3];
	W_DGMPoint Point (CLSID_TRiASCSPoint);

		THROW_FAILED_HRESULT(WPersistStreamInit(Point) -> InitNew());
		if (CTF_TransMercator == m_CTFType)
		{
			Coords[0] = atof (OLE2A(XStr));
			Coords[1] = atof (OLE2A(YStr));
		} else {
			Coords[0] = GtoValue (OLE2A(XStr));
			Coords[1] = GtoValue (OLE2A(YStr));
		}
	
		if (SysStringLen (ZStr) > 0)
			Coords[2] = atof (OLE2A(ZStr));
		else
			Coords[2] = 0.0;

		THROW_FAILED_HRESULT(Point -> SetPoint (Coords));
		*ppIPoint = Point.detach();

	} COM_CATCH;
	return S_OK;
}

// Funktionen, die MittelMeridian berechnen -----------------------------------
// Berechnet aus geod. Koordinate den ZielMeridian
BOOL CCoordTrans::GetMeridianGeod (double dX, int &riMeridian)
{
	if (CTFMODE_AutoMeridian == m_CTFMode) {
		if ( 3 == m_iStrBreite)
			riMeridian = (int)((dX/3600.0 + 1.5)/3) * 3;
		else
			riMeridian = (int)((dX/3600.0)/6) * 6 + 3;
	} else 
		riMeridian = m_iMeridian;		// vorgegebenen verwenden

	return TRUE;
}

BOOL CCoordTrans::GetMeridianGK (double dX, int &riMeridian)
{
	if (CTFMODE_AutoMeridian == m_CTFMode) {
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

STDMETHODIMP CCoordTrans::get_Envelope(LPDISPATCH * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CCoordTrans::get_Container(LPDISPATCH * pVal)
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
			SetPropertyAndType (Props, g_cbCTFMeridianView, m_iMeridian, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);
		else
			SetPropertyAndType (Props, g_cbCTFMeridianView, g_cbAutoSelect, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);

		SetPropertyAndType (Props, g_cbCTFStreifenView, m_iStrBreite, (PROPERTY_TYPE)(PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_System), true);
	}

// CoordPrecision
	SetPropertyAndType (Props, g_cbCoordPrecision, m_iPrec, PROPERTY_TYPE_System, true); 

// alle informieren
	RETURN_FAILED_HRESULT(Fire_ChangedCoordParams (this));
	return S_OK;
}

HRESULT CCoordTrans::InnerTransform(double *pCoords, TRANSDIRECTION Dir, int iMeridian)
{
	CHECKPOINTER(pCoords);

//long double b, l;
//int Lm = iMeridian;
//long double dXOut, dYOut, dZOut;
	  
//	dZOut = pCoords[2];

// Umwandlung GK->Geod
	if (CTF_Geodetical == m_CTFType) {
	CSID Guid;

		RETURN_FAILED_HRESULT(EnsureGeodCS (m_rgChangeEllipse, &Guid))
		switch (Dir) {
		case TRANSDIRECTION_FORWARD:	// Transform
			RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
//			gaugeo (HA, HB, m_iStreifenDB, m_iMeridianDB, pCoords[1], pCoords[0], KS, &dYOut, &dXOut);
			break;
		
		case TRANSDIRECTION_INVERSE:	// InvTransform
			RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
//			geogau (HA, HB, m_iStreifenDB, m_iMeridianDB, pCoords[1], pCoords[0], KS, &dYOut, &dXOut);
			break;
		
		default:
		case TRANSDIRECTION_IGNORED:
			_ASSERTE(Dir != TRANSDIRECTION_IGNORED);
			return E_UNEXPECTED;
		}
	} 
	else {
	// wenn von außen kein Meridian vorgegeben ist, dann den internen benutzen
		if (m_iStreifenDB != m_iStrBreite ||		// andere Streifenbreite
			CTFMODE_AutoMeridian == m_CTFMode ||	// automatische Berechnung des Meridians
			0 != m_iMeridianDB || 
			m_iMeridianDB != m_iMeridian)			// oder anderer Meridian
		{
		CSID Guid;

			if (CTFMODE_AutoMeridian != m_CTFMode)
				iMeridian = m_iMeridian;

			switch (Dir) {
			case TRANSDIRECTION_FORWARD:	// Transform
				{
					if (m_iStrBreite != m_iStreifenDB || 0 != m_iMeridianDB || iMeridian != m_iMeridianDB) {
						RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, 
							m_iStrBreite, iMeridian, &Guid));
						RETURN_FAILED_HRESULT(m_CTF -> TransformInverse(Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
					}
					pCoords[0] /= m_dScale;
					pCoords[1] /= m_dScale;

//				 // Meridian Lm bestimmen
//					if (0 == iMeridian || iMeridian != m_iMeridianDB) {
//						gaugeo (HA, HB, m_iStreifenDB, m_iMeridianDB, pCoords[1], pCoords[0], KS, &b, &l);
//						if (0 == iMeridian && !GetMeridianGeod(l, iMeridian))
//							return E_FAIL;
//					}
//
//					if (iMeridian != m_iMeridianDB) {
//						geogau (HA, HB, m_iStrBreite, iMeridian, double(b), double(l), KS, &dYOut, &dXOut);
//
//						dXOut = double(dXOut)/m_dScale;
//						dYOut = double(dYOut)/m_dScale;
//					} else {
//						dXOut = pCoords[0] / m_dScale;
//						dYOut = pCoords[1] / m_dScale;
//					}
				}
				break;

			case TRANSDIRECTION_INVERSE:	// InvTransform	//new Code unchecked
				{
				// eigentliche Konvertierung
					pCoords[0] *= m_dScale;
					pCoords[1] *= m_dScale;

					if (m_iStrBreite != m_iStreifenDB || iMeridian != m_iMeridianDB || 0 != m_iMeridianDB) {
						RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, 
							m_iStrBreite, iMeridian, &Guid));
						RETURN_FAILED_HRESULT(m_CTF -> Transform(Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
					}

//				// PlausibilitätsTest
//					if (pCoords[1] < -8000000.0 || pCoords[1] > 8000000.0) 
//						return E_FAIL;
//					if (pCoords[0] < 0 || pCoords[0] > 7000000.0) 
//						return E_FAIL;
//
//				// Meridian Lm bestimmen
//					if (0 == Lm && !GetMeridianGK(pCoords[0], Lm))
//						return E_FAIL;
//
//					if (m_iStrBreite != m_iStreifenDB || Lm != m_iMeridianDB) {
//						gaugeo (HA, HB, m_iStrBreite, Lm, pCoords[1], pCoords[0], KS, &b, &l);
//						geogau (HA, HB, m_iStreifenDB, m_iMeridianDB, double(b), double(l), KS, &dYOut, &dXOut);
//					} else {
//						dXOut = pCoords[0];
//						dYOut = pCoords[1];
//					}
				}
				break;

			default:
			case TRANSDIRECTION_IGNORED:
				ASSERT(Dir != TRANSDIRECTION_IGNORED);
				return E_UNEXPECTED;
			}
		} 
		else {
			switch (Dir) {
			case TRANSDIRECTION_FORWARD:	// Transform
				pCoords[0] /= m_dScale;
				pCoords[1] /= m_dScale;
				break;

			case TRANSDIRECTION_INVERSE:	// InvTransform	
				pCoords[0] *= m_dScale;
				pCoords[1] *= m_dScale;
				break;

			default:
			case TRANSDIRECTION_IGNORED:
				ASSERT(Dir != TRANSDIRECTION_IGNORED);
				return E_UNEXPECTED;
			}
		}
	}
	return S_OK;
}

HRESULT CCoordTrans::InnerNative(double *pCoords, TRANSDIRECTION Dir, int iMeridianExt)
{
//long double b, l;
//long double XOut, YOut;

// der vorgegebene iMeridianExt wird außerhalb bestimmt
// hier passiert nur noch die eigentliche Umwandlung des vorgegebenen Punktes
CSID Guid;

	RETURN_FAILED_HRESULT(EnsureGKCS (m_rgChangeEllipse, m_iStrBreite, iMeridianExt, &Guid))
	switch (Dir) {
	case TRANSDIRECTION_FORWARD:	// Transform
		{
		// eigentliche Konvertierung
			pCoords[0]	/= m_dScale;
			pCoords[1]	/= m_dScale;

		// kann weitere Transformation gespart werden ?
			if (0 != 0 != m_iMeridianDB || iMeridianExt != m_iMeridianDB || m_iStrBreite != m_iStreifenDB) {
				RETURN_FAILED_HRESULT(m_CTF -> TransformInverse (Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
//				gaugeo (HA, HB, m_iStreifenDB, m_iMeridianDB, pCoords[1], pCoords[0], KS, &b, &l);
//				geogau (HA, HB, m_iStrBreite, iMeridianExt, double(b), double(l), KS, &YOut, &XOut);
//				pCoords[0] = double(XOut);
//				pCoords[1] = double(YOut);
			}
		}
		break;

	case TRANSDIRECTION_INVERSE:	// InvTransform
		{
		// eigentliche Konvertierung
			pCoords[0] *= m_dScale;
			pCoords[1] *= m_dScale;

			if (pCoords[1] < -8000000.0 || pCoords[1] > 8000000.0) 
				return E_FAIL;
			if (pCoords[0] < 0 || pCoords[0] > 7000000.0) 
				return E_FAIL;

		// kann weitere Transformation gespart werden ?
			if (0 != m_iMeridianDB || iMeridianExt != m_iMeridianDB || m_iStrBreite != m_iStreifenDB) {
				RETURN_FAILED_HRESULT(m_CTF -> Transform (Guid, 1, (CSCOORD *)pCoords, (CSCOORD *)pCoords));
//				gaugeo (HA, HB, m_iStrBreite, iMeridianExt, pCoords[1], pCoords[0], KS, &b, &l);
//				geogau (HA, HB, m_iStreifenDB, m_iMeridianDB, double(b), double(l), KS, &YOut, &XOut);
//				pCoords[0] = double(XOut);
//				pCoords[1] = double(YOut);
			}
		}
		break;

	default:
	case TRANSDIRECTION_IGNORED:
		ASSERT(Dir != TRANSDIRECTION_IGNORED);
		return E_UNEXPECTED;
	}	// of switch

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für Koordinatentransformations-Pipe

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

HRESULT CCoordTrans::AddOutputCS()
{
	_ASSERTE(m_CTF.IsValid());

	COM_TRY {
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CS -> put_CoordSystemType(tcsCS_Projected));

	// Geodätische Grundlage initialisieren
	TRIASCSGEODETICDATUM rgDatum = GetGeodDatum(m_rgEllipseNative, true);

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

	// projektives Koordinatensystem beachten
		{
		WTRiASCSPCS PCS;

			THROW_FAILED_HRESULT(CS -> get_ProjectedCS (PCS.ppi()));
		
		// Projektionsparameter festlegen
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(
				tcsPA_TransverseMercator));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, KS));

			if (0 != m_iMeridianDB) {
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, GetLongitude(m_iMeridianDB)));
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_FalseEasting, GetFalseX(m_iMeridianDB, m_iStreifenDB)));
			}
			else {
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
					tcsPP_GaussKrueger_ZoneWidth, m_iStreifenDB));
			}

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, 0.0));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(
				tcsPP_GaussKrueger_FalseNorthing, 0.0));
			THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(tcsUOL_Metre));
		}
	
	// CS ist jetzt fertig initialisiert
		THROW_FAILED_HRESULT(WTRiASCSTransform(m_CTF) -> putref_OutputCS(CS));
		THROW_FAILED_HRESULT(CS -> Recompute());

	} COM_CATCH;
	return S_OK;
}

namespace {
	inline
	ULONG MakeCSKey (TRIASCSGEODETICDATUM rgDatum, int iStrBreite, 
		int iMeridian)
	{
		return MAKELONG(rgDatum, MAKEWORD(iStrBreite, iMeridian));
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


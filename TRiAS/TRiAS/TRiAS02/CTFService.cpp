// Memberfunktionen für die Schnittstelle zu den KoordinatenTransformations-Objekten
// File: CTFService.cpp

#include "trias02p.hxx"

#include <math.h>
#include <comcat.h>
//#include <tdbgeo.h>

#include <Com/PropertyHelper.h>
#include <CSPoint.h>
//#include <registry.hxx>

//#include <tdbgeo_i.c>
//#include <ictf_i.c>		// in einem Module

const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformEvents = {0x764CA444,0xDFF6,0x11D1,{0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A}};
const IID LIBID_CoordTransLib = {0x0BDC3C09,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_DefaultCoordTrans = {0x0BDC3C19,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_ManageCoordParam = {0x95F58F37,0xDF2C,0x11D1,{0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A}};

#include "trias02.h"
#include "trias02.hmc"

#include "Strings.h"
#include "Utils.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumGUID);
DefineSmartInterface(CatInformation);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(CoordTransformInit);

///////////////////////////////////////////////////////////////////////////////
//
_TRIAS02_ENTRY ErrCode EvalKoeffs (double *, double *, double *, double *);

///////////////////////////////////////////////////////////////////////////////
// Lokale Stringkonstanten
static const char g_cbCoordTransAspectRatio[] = TEXT("CoordTransAspectRatio");
static const char g_cbCoordTransDistance[] = TEXT("CoordTransDistance");
static const char g_cbCoordTransDistanceEx[] = TEXT("CoordTransDistanceEx");
static const char g_cbTransform[] = TEXT("Transform");
static const char g_cbInvTransform[] = TEXT("InvTransform");
static const char g_cbTransformEx[] = TEXT("TransformEx");
static const char g_cbInvTransformEx[] = TEXT("InvTransformEx");
static const char g_cbCoordTransDescription[] = TEXT("CoordTransDescription");
static const char g_cbCoordTransMode[] = TEXT("CoordTransMode");
static const char g_cbCoordTransToString[] = TEXT("CoordTransToString");
static const char g_cbCoordTransToValue[] = TEXT("CoordTransToValue");
static const char g_cbCoordTransToStringEx[] = TEXT("CoordTransToStringEx");
static const char g_cbCoordTransToValueEx[] = TEXT("CoordTransToValueEx");
static const char g_cbCoordTransRectangle[] = TEXT("CoordTransRectangle");
static const char g_cbIsMetric[] = TEXT("IsMetric");
static const char g_cbNative[] = TEXT("Native");
static const char g_cbMetric[] = TEXT("Metric");
static const char g_cbMetricParam[] = TEXT("MetricParam");
static const char g_cbNativeParam[] = TEXT("NativeParam");
static const char g_cbNativeEx[] = TEXT("NativeEx");
static const char g_cbMetricEx[] = TEXT("MetricEx");
static const char g_cbTransformParam[] = TEXT("TransformParam");
static const char g_cbInvTransformParam[] = TEXT("InvTransformParam");

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
const CATID CATID_TRiASCoordsystem = {0x079639C3L,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor 
CCoordTransService::CCoordTransService (void)
{
	m_fIsDefault = false;
	m_fIsInitialized = false;
	m_fCanConfig = false;
	m_dwCookie = 0L;
}

HRESULT CCoordTransService::InitCTFService (ITRiASPropertyBase *pIPropBase)
{
	if (NULL == pIPropBase) return E_POINTER;

	m_PropBase = pIPropBase;
	if (!Refresh (true))			// jetzt fertig initialiseren
		return E_FAIL;

	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// diese Funktionalität wird nicht hier benötigt
//HRESULT CCoordTransService::FindCTF (void)
//{
//	USES_CONVERSION;
//
//char cbCTFName[_MAX_PATH];
//CComBSTR bstr (GetProperty (m_Props, g_cbCoordTransform, A2OLE(g_cbDefault)));
//
//	strcpy (cbCTFName, OLE2A(bstr));
//	if (!stricmp (cbCTFName, g_cbDefault)) 
//		m_fIsDefault = true;
//
//// CTFService's über CATID enumerieren, CTFService wiederfinden
//	COM_TRY {
//	WEnumGUID EnumGuids;		// Enumerator der CTFService-Objekte
//	WCatInformation CatInfo (CLSID_StdComponentCategoriesMgr);	// throws hr
//	GUID guidImpl[1]; 
//
//		guidImpl[0] = CATID_TRiASCoordsystem;
//		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));
//
//	GUID guid;
//	LPOLESTR lpGuid = NULL;
//	bool fFoundGuid = false;
//
//		for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
//		{
//			THROW_FAILED_HRESULT(StringFromCLSID (guid, &lpGuid));
//
//		CClassesRoot regClsID (OLE2A(lpGuid), KEY_READ);
//		char cbBuffer[_MAX_PATH];
//		LONG lSize = sizeof(cbBuffer);
//
//			if (NULL != lpGuid) {
//				CoTaskMemFree (lpGuid);
//				lpGuid = NULL;
//			}
//			if (regClsID.isValid() && regClsID.GetSZ (g_cbOldName, cbBuffer, lSize))
//			{
//				if (!stricmp (cbBuffer, cbCTFName)) {
//					fFoundGuid = true;
//					m_strCTF = cbBuffer;
//					break;
//				}
//			}
//		}
//		if (!fFoundGuid) {
//			TX_ASSERT(fFoundGuid);
//			return E_FAIL;					// snh!
//		}
//
//	} COM_CATCH_EX(e) {
//		TX_ASSERT(S_OK == _COM_ERROR(e));
//		return _COM_ERROR(e);
//	}
//	return S_OK;
//}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die CTF neu geladen werden muß

bool CCoordTransService::Reload (bool fRefresh)
{
	USES_CONVERSION;

WTRiASProperties Props;

	if (FAILED(m_PropBase -> get_Properties (Props.ppi())))
		return false;

CComBSTR bstr (GetProperty (Props, g_cbCoordTransform, CComBSTR(g_cbDefault)));
LPCSTR pcName = OLE2A(bstr);

	if (stricmp(pcName, m_strCTF.c_str())) {
		return true;		// muß neu _geladen_ werden
	} else if (!stricmp(pcName, g_cbDefault) && !m_fIsDefault) {
		m_fIsDefault = true;
		TX_TRY(m_strCTF = g_cbDefault);
		return true;		// war nicht DEFAULT und ist jetzt nichts mehr
	}
	if (fRefresh)			// neu initialisieren der _selben_ CTF
		Refresh();

	return false;	// muß nicht neu geladen werden
}

bool CCoordTransService::Refresh (bool fForce)
{
WTRiASProperties Props;

	if (FAILED(m_PropBase -> get_Properties (Props.ppi())))
		return false;

// SkalierungsKoeffizienten lesen
double dK11 = GetProperty (Props, g_cbKoeff11, 1.0, LOCALE_ENGLISH);
double dK12 = GetProperty (Props, g_cbKoeff12, 0.0, LOCALE_ENGLISH);
double dK21 = GetProperty (Props, g_cbKoeff21, 0.0, LOCALE_ENGLISH);
double dK22 = GetProperty (Props, g_cbKoeff22, 1.0, LOCALE_ENGLISH);
double dOX = GetProperty (Props, g_cbOffsetX, 0.0, LOCALE_ENGLISH);
double dOY = GetProperty (Props, g_cbOffsetY, 0.0, LOCALE_ENGLISH);

	if (fForce ||
		dK11 != m_dK11 || dK12 != m_dK12 || dK21 != m_dK21 || dK22 != m_dK22 ||
		dOX != m_dOX || dOY != m_dOY) 
	{
		m_dInvK11 = m_dK11 = dK11;
		m_dInvK12 = m_dK12 = dK12;
		m_dInvK21 = m_dK21 = dK21;
		m_dInvK22 = m_dK22 = dK22;
		m_dOX = dOX;
		m_dOY = dOY;

	} else {
		if (m_CTF.IsValid()) {	// lediglich CTF neu initialisieren
		WCoordTransformInit Init;

			if (SUCCEEDED(m_CTF -> QueryInterface (IID_ICoordTransformInit, Init.ppv())))
				Init -> ReInitCoordTransform(m_PropBase);
		}
		return true;
	}

// Koeffizienten Matrix invertieren
	if (EvalKoeffs (&m_dInvK11, &m_dInvK12, &m_dInvK21, &m_dInvK22) != EC_OKAY)
		return false;	// entartete TMatrix

// Objekt erzeugen und initialisieren
	USES_CONVERSION;
	COM_TRY {
	// GetProperty liefert mit AddRef ab !
		m_CTF = GetProperty (Props, g_cbCTFService, (IDispatch *)NULL);
		m_CTF -> Release();

	// Eigenschaften einlesen
	VARIANT_BOOL fFlag;			// überprüfen, ob CTF Config-Mode besitzt

		THROW_FAILED_HRESULT(m_CTF -> get_CanConfig (&fFlag));
		m_fCanConfig = fFlag ? true : false;

	// OldName speichern 
	CComBSTR bstr (GetProperty (Props, g_cbCoordTransform, CComBSTR(g_cbDefault)));

		m_strCTF = OLE2A(bstr);

	} catch (_com_error &) {
		m_CTF.Assign (NULL);		// auf jeden Fall freigeben
		return false;
	}
	return true;
}

CCoordTransService::~CCoordTransService (void)
{
	TX_ASSERT(0 == m_dwCookie);
	m_PropBase.Assign(NULL);
	m_CTF.Assign (NULL);		// Objekt freigeben
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die nicht auf die CTF-Objekt durchgreifen 

bool CCoordTransService::Scale (const double &rdX, const double &rdY, Punkt &outPt)
{
	outPt.SetX(ScaleX (rdX, rdY));
	outPt.SetY(ScaleY (rdX, rdY));
	return true;
}

bool CCoordTransService::Scale (const double &rdX, const double &rdY, KoOrd *pX, KoOrd *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = ScaleX (rdX, rdY);
	*pY = ScaleY (rdX, rdY);
	return true;
}

bool CCoordTransService::UnScale (const Punkt &Pt, double *pX, double *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = UnScaleX (Pt.GetX(), Pt.GetY());
	*pY = UnScaleY (Pt.GetX(), Pt.GetY());;
	return true;
}

bool CCoordTransService::UnScale (const KoOrd &inX, const KoOrd &inY, double *pX, double *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = UnScaleX (inX, inY);
	*pY = UnScaleY (inX, inY);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die auf die CTF-Objekt durchgreifen 
double CCoordTransService::CoordTransAspectRatio (ObjContainer &OC)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
		// Koordinaten transformieren
		CCSPoint LO (OC.XMin(), OC.YMax());
		CCSPoint RU (OC.XMax(), OC.YMin());
#else
		CCSPoint LO (UnScaleX(OC.XMin(), OC.YMax()), UnScaleY(OC.XMin(), OC.YMax()));
		CCSPoint RU (UnScaleX(OC.XMax(), OC.YMin()), UnScaleY(OC.XMax(), OC.YMin()));
#endif // _KOORD_ISDOUBLE
		double dAspect = 1.0;
		
			THROW_FAILED_HRESULT(m_CTF -> get_AspectRatio (&LO, &RU, &dAspect));
			return dAspect;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransAspectRatio);
			return 1.0;
		}
	}
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransAspectRatio);
	return 1.0;
}

inline double Sqr (double d) { return d*d; }

double CCoordTransService::CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2)
{
	if (m_fIsInitialized) {
	double dDist = 0.0;

		COM_TRY {
		CCSPoint pt1 (pP1 -> Width(), pP1 -> Height());
		CCSPoint pt2 (pP2 -> Width(), pP2 -> Height());
		W_DGMPoint ptDist;

			THROW_FAILED_HRESULT(m_CTF -> DistanceEx (&pt1, &pt2, ptDist.ppi(), &dDist));
			TX_ASSERT(dDist >= 0.0);

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDistance);
		}
		return dDist;
	}
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDistance);
	return 0.0;
}

bool CCoordTransService::CoordTransDistanceEx (
	const DoublePair *pP1, const DoublePair *pP2, double &dX, double &dY)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CCSPoint pt1 (pP1 -> Width(), pP1 -> Height());
		CCSPoint pt2 (pP2 -> Width(), pP2 -> Height());
		W_DGMPoint outPt;

			THROW_FAILED_HRESULT(m_CTF -> Distance(&pt1, &pt2, outPt.ppi()));
			THROW_FAILED_HRESULT(outPt -> get_X (&dX));
			THROW_FAILED_HRESULT(outPt -> get_Y (&dY));
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDistanceEx);
			return false;
		}
	}
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDistanceEx);
	return false;
}

bool CCoordTransService::Transform (double *pX, double *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (*pX, *pY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			THROW_FAILED_HRESULT(m_CTF -> Transform (&m_pt, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(m_pt -> get_X (pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransform);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransform);
	return false;
}

bool CCoordTransService::Transform (DoublePair *pPoints, int iNum)
{
	if (m_fIsInitialized) {
		COM_TRY {
			for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
				THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> Transform (&m_pt, TRANSDIRECTION_FORWARD));
				THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransform);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransform);
	return false;
}

bool CCoordTransService::InvTransform (double *pX, double *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (*pX, *pY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			THROW_FAILED_HRESULT(m_CTF -> Transform (&m_pt, TRANSDIRECTION_INVERSE));
			THROW_FAILED_HRESULT(m_pt -> get_X (pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransform);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransform);
	return false;
}

bool CCoordTransService::InvTransform (DoublePair *pPoints, int iNum)
{
	if (m_fIsInitialized) {
		COM_TRY {
			for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
				THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> Transform (&m_pt, TRANSDIRECTION_INVERSE));
				THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransform);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransform);
	return false;
}

char * CCoordTransService::CoordTransDescription (char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CComBSTR bstr;

			THROW_FAILED_HRESULT(m_CTF -> get_Description (CLEARED(&bstr)));
		
			USES_CONVERSION;
			iLen = min(bstr.Length(), (size_t)(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDescription);
			return NULL;
		}
	
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDescription);
	return NULL;
}

bool CCoordTransService::CoordTransMode (pWindow pW)
{
	ShowError (E_NOTIMPL, IDS_CSSERRORCAPTION, g_cbCoordTransMode);
	return false;
}

char * CCoordTransService::CoordTransToString (
	double Value, bool isX, char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CComBSTR bstr;

			if (isX) {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (Value, 0.0);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (Value));
				THROW_FAILED_HRESULT(m_pt -> put_Y (0.0));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&m_pt, CLEARED(&bstr), NULL, NULL));
			} else {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (0.0, Value);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (0.0));
				THROW_FAILED_HRESULT(m_pt -> put_Y (Value));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&m_pt, NULL, CLEARED(&bstr), NULL));
			}

			USES_CONVERSION;
			iLen = min(bstr.Length(), (size_t)(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToString);
			return NULL;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToString);
	return NULL;
}

double CCoordTransService::CoordTransToValue (char *pBuffer)
{
	ShowError (E_NOTIMPL, IDS_CSSERRORCAPTION, g_cbCoordTransToValue);
	return 0.0;
}

char * CCoordTransService::CoordTransToStringEx (
	double dX, double dY, bool isX, char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CComBSTR bstr;
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			if (isX) {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&m_pt, CLEARED(&bstr), NULL, NULL));
			} else {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&m_pt, NULL, CLEARED(&bstr), NULL));
			}

			USES_CONVERSION;
			iLen = min(bstr.Length(), (size_t)(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
			return NULL;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
	return NULL;
}

bool CCoordTransService::CoordTransToValueEx (
	const char *pBuffX, const char *pBuffY, double &dX, double &dY)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CComBSTR bstrX (pBuffX);
		CComBSTR bstrY (pBuffY);
		W_DGMPoint pt;

			THROW_FAILED_HRESULT(m_CTF -> ToPoint (bstrX, bstrY, NULL, pt.ppi()));
			THROW_FAILED_HRESULT(pt -> get_X(&dX));
			THROW_FAILED_HRESULT(pt -> get_Y(&dY));
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToValueEx);
			return false;
		}
	
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToValueEx);
	return false;
}

bool CCoordTransService::CoordTransRectangle (
	const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut)
{
	if (m_fIsInitialized) {
		COM_TRY {
		CCSPoint ptIn (pIn -> Width(), pIn -> Height());
		CCSPoint ptDelta (pDelta -> Width(), pDelta -> Height());
		W_DGMPoint ptOut;

			THROW_FAILED_HRESULT(m_CTF -> DistancePoint (&ptIn, &ptDelta, ptOut.ppi()));
			THROW_FAILED_HRESULT(ptOut -> get_X(&pOut -> X()));
			THROW_FAILED_HRESULT(ptOut -> get_Y(&pOut -> Y()));
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransRectangle);
			return false;
		}
	}
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransRectangle);
	return false;
}

// Funktionen, die Koordinaten in metrische Einheiten konvertieren ------------
bool CCoordTransService::isMetric (void)
{
	if (m_fIsInitialized) {
		COM_TRY {
		VARIANT_BOOL fVal = VARIANT_TRUE;

			THROW_FAILED_HRESULT(m_CTF -> get_IsMetric (&fVal));
			return fVal ? true : false;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbIsMetric);
			return true;	// metrisch annehmen
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbIsMetric);
	return true;	// metrisch annehmen
}

#if _TRiAS_VER < 0x0400
bool CCoordTransService::Native (
	const double &rdX, const double &rdY, Punkt &outPt)
{
KoOrd dX = outPt.GetX();
KoOrd dY = outPt.GetY();

	if (Native (rdX, rdY, &dX, &dY)) {
		outPt.SetX(dX);
		outPt.SetY(dY);
		return true;
	}
	return false;
}

bool CCoordTransService::Native (
	const double &rdX, const double &rdY, KoOrd *pX, KoOrd *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (rdX, rdY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (rdX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (rdY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			THROW_FAILED_HRESULT(m_CTF -> Native (&m_pt, TRANSDIRECTION_INVERSE));

#if defined(_KOORD_ISDOUBLE)
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return S_OK;
#else
		double dX, dY;

			return Scale (dX, dY, pX, pY);
#endif // _KOORD_ISDOUBLE
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNative);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNative);
	return false;	// Fehler
}
#else
bool CCoordTransService::Native (
	const double &rdX, const double &rdY, DoublePair &outPt)
{
KoOrd dX = outPt.X();
KoOrd dY = outPt.Y();

	if (Native (rdX, rdY, &dX, &dY)) {
		outPt.X() = dX;
		outPt.Y() = dY;
		return true;
	}
	return false;
}

bool CCoordTransService::Native (
	const double &rdX, const double &rdY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (rdX, rdY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (rdX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (rdY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			THROW_FAILED_HRESULT(m_CTF -> Native (&m_pt, TRANSDIRECTION_INVERSE));

#if defined(_KOORD_ISDOUBLE)
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return S_OK;
#else
		double dX, dY;

			return Scale (dX, dY, pX, pY);
#endif // _KOORD_ISDOUBLE
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNative);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNative);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0400
bool CCoordTransService::Metric (const Punkt &Pt, double *pX, double *pY)
{
	return Metric (Pt.GetX(), Pt.GetY(), pX, pY);
}

bool CCoordTransService::Metric (
	const KoOrd &inX, const KoOrd &inY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (inX, inY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (inX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (inY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#else
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#endif // _KOORD_ISDOUBLE

			THROW_FAILED_HRESULT(m_CTF -> Native (&m_pt, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return true;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetric);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetric);
	return false;	// Fehler
}
#else
bool CCoordTransService::Metric (const DoublePair &Pt, double *pX, double *pY)
{
	return Metric (Pt.Width(), Pt.Height(), pX, pY);
}

bool CCoordTransService::Metric (
	const double &inX, const double &inY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (inX, inY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (inX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (inY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#else
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#endif // _KOORD_ISDOUBLE

			THROW_FAILED_HRESULT(m_CTF -> Native (&m_pt, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return true;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetric);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetric);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Funktionen für parametrisierbare Transformationen
bool CCoordTransService::GetMetricParam (const Punkt &rPt, LPVOID *ppData)
{
	return GetMetricParam (rPt.GetX(), rPt.GetY(), ppData);
}

bool CCoordTransService::GetMetricParam (KoOrd iX, KoOrd iY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (iX, iY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (iX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (iY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#else
		double dX, dY;

			if (!UnScale (iX, iY, &dX, &dY)) return false;

#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#endif // _KOORD_ISDOUBLE

			if (SUCCEEDED(m_CTF -> NativeParameter (&m_pt, TRANSDIRECTION_FORWARD, (IDispatch **)ppData)))
				return true;
			return false;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricParam);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricParam);
	return false;	// Fehler
}

#if _TRiAS_VER < 0x0400
bool CCoordTransService::MetricEx (
	const Punkt &rPt, double *pX, double *pY, LPVOID pData)
{
	return MetricEx (rPt.GetX(), rPt.GetY(), pX, pY, pData);
}

bool CCoordTransService::MetricEx (
	KoOrd inX, KoOrd inY, double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (inX, inY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (inX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (inY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#else
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#endif // _KOORD_ISDOUBLE

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&m_pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return true;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	return false;	// Fehler
}
#else
bool CCoordTransService::MetricEx (
	const DoublePair &rPt, double *pX, double *pY, LPVOID pData)
{
	return MetricEx (rPt.Width(), rPt.Height(), pX, pY, pData);
}

bool CCoordTransService::MetricEx (
	double inX, double inY, double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if defined(_KOORD_ISDOUBLE)
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (inX, inY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (inX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (inY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#else
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
#endif // _KOORD_ISDOUBLE

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&m_pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			THROW_FAILED_HRESULT(m_pt -> get_X(pX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(pY));
			return true;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

bool CCoordTransService::GetNativeParam (const double &rdX, const double &rdY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (rdX, rdY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (rdX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (rdY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			if (SUCCEEDED(m_CTF -> NativeParameter (&m_pt, TRANSDIRECTION_INVERSE, (IDispatch **)ppData)))
				return true;
			return false;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNativeParam);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNativeParam);
	return false;	// Fehler
}

#if _TRiAS_VER < 0x0400
bool CCoordTransService::NativeEx (
	const double &rdX, const double &rdY, DoublePair &outPt, LPVOID pData)
{
KoOrd dX = outPt.X();
KoOrd dY = outPt.Y();

	if (NativeEx (rdX, rdY, &dX, &dY, pData)) {
		outPt.X() = dX;
		outPt.Y() = dY;
		return true;
	}
	return false;
}

bool CCoordTransService::NativeEx (
	const double &rdX, const double &rdY, double *piX, double *piY, LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (rdX, rdY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (rdX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (rdY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&m_pt, TRANSDIRECTION_INVERSE, (IDispatch *)pData));

#if defined(_KOORD_ISDOUBLE)
			THROW_FAILED_HRESULT(m_pt -> get_X(piX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(piY));
			return S_OK;
#else
		double dX, dY;

			THROW_FAILED_HRESULT(m_pt -> get_X(&dX));
			THROW_FAILED_HRESULT(m_pt -> get_Y(&dY));
			return Scale (dX, dY, piX, piY);
#endif // _KOORD_ISDOUBLE
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

bool CCoordTransService::GetTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

			if (SUCCEEDED(m_CTF -> TransformParameter (&m_pt, TRANSDIRECTION_FORWARD, (IDispatch **)ppData)))
				return true;
			return false;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformParam);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformParam);
	return false;	// Fehler
}

bool CCoordTransService::GetInvTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		COM_TRY {
#if !defined(_CTF_USE_POINTMEMBER)
		CCSPoint m_pt (dX, dY);
#else
			THROW_FAILED_HRESULT(m_pt -> put_X (dX));
			THROW_FAILED_HRESULT(m_pt -> put_Y (dY));
			THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)
		CCSPoint pt (dX, dY);

			if (SUCCEEDED(m_CTF -> TransformParameter (&m_pt, TRANSDIRECTION_INVERSE, (IDispatch **)ppData)))
				return true;
			return false;
						
		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformParam);
			return false;	// Fehler
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformParam);
	return false;	// Fehler
}

bool CCoordTransService::TransformEx (double *pX, double *pY, LPVOID pData, 
	IUnknown *pICS)
{
	if (m_fIsInitialized) {
		COM_TRY {
			if (NULL == pICS) {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (*pX, *pY);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
				THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> TransformEx(&m_pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
				THROW_FAILED_HRESULT(m_pt -> get_X (pX));
				THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			}
			else {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (*pX, *pY);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
				THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> TransformEx2(&m_pt, TRANSDIRECTION_FORWARD, pICS));
				THROW_FAILED_HRESULT(m_pt -> get_X (pX));
				THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformEx);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformEx);
	return false;
}

bool CCoordTransService::TransformEx (DoublePair *pPoints, int iNum, 
	LPVOID pData, IUnknown *pICS)
{
	if (m_fIsInitialized) {
		COM_TRY {
			if (NULL == pICS) {
				for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
				CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
					THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
					THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

					THROW_FAILED_HRESULT(m_CTF -> TransformEx(&m_pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
					THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
				}
			}
			else {
				for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
				CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
					THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
					THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

					THROW_FAILED_HRESULT(m_CTF -> TransformEx2(&m_pt, TRANSDIRECTION_FORWARD, pICS));
					THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
				}
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformEx);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformEx);
	return false;
}

bool CCoordTransService::InvTransformEx (double *pX, double *pY, LPVOID pData,
	IUnknown *pICS)
{
	if (m_fIsInitialized) {
		COM_TRY {
			if (NULL == pICS) {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (*pX, *pY);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
				THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> TransformEx (&m_pt, TRANSDIRECTION_INVERSE, (IDispatch *)pData));
				THROW_FAILED_HRESULT(m_pt -> get_X (pX));
				THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			}
			else {
#if !defined(_CTF_USE_POINTMEMBER)
			CCSPoint m_pt (*pX, *pY);
#else
				THROW_FAILED_HRESULT(m_pt -> put_X (*pX));
				THROW_FAILED_HRESULT(m_pt -> put_Y (*pY));
				THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

				THROW_FAILED_HRESULT(m_CTF -> TransformEx2 (&m_pt, TRANSDIRECTION_INVERSE, pICS));
				THROW_FAILED_HRESULT(m_pt -> get_X (pX));
				THROW_FAILED_HRESULT(m_pt -> get_Y (pY));
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformEx);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformEx);
	return false;
}

bool CCoordTransService::InvTransformEx (DoublePair *pPoints, int iNum, 
	LPVOID pData, IUnknown *pICS)
{
	if (m_fIsInitialized) {
		COM_TRY {
			if (NULL == pICS) {
				for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
				CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
					THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
					THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

					THROW_FAILED_HRESULT(m_CTF -> TransformEx (&m_pt, TRANSDIRECTION_INVERSE, (IDispatch *)pData));
					THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
				}
			}
			else {
				for (int i = 0; i < iNum; i++) {
#if !defined(_CTF_USE_POINTMEMBER)
				CCSPoint m_pt (pPoints[i].X(), pPoints[i].Y());
#else
					THROW_FAILED_HRESULT(m_pt -> put_X (pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> put_Y (pPoints[i].Y()));
					THROW_FAILED_HRESULT(m_pt -> put_Z (0.0));
#endif // !defined(_CTF_USE_POINTMEMBER)

					THROW_FAILED_HRESULT(m_CTF -> TransformEx2 (&m_pt, TRANSDIRECTION_INVERSE, pICS));
					THROW_FAILED_HRESULT(m_pt -> get_X (&pPoints[i].X()));
					THROW_FAILED_HRESULT(m_pt -> get_Y (&pPoints[i].Y()));
				}
			}
			return true;

		} COM_CATCH_EX(e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformEx);
			return false;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformEx);
	return false;
}

void CCoordTransService::FreeMetricParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
			THROW_FAILED_HRESULT(m_CTF -> FreeNativeParameter (TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			return;

		} catch (_com_error &) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricParam);
			return;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricParam);
}

void CCoordTransService::FreeNativeParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
			THROW_FAILED_HRESULT(m_CTF -> FreeNativeParameter (TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			return;

		} catch (_com_error &) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNativeParam);
			return;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNativeParam);
}

void CCoordTransService::FreeTransformParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
			THROW_FAILED_HRESULT(m_CTF -> FreeTransformParameter (TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			return;

		} catch (_com_error &) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformParam);
			return;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformParam);
}

void CCoordTransService::FreeInvTransformParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		COM_TRY {
			THROW_FAILED_HRESULT(m_CTF -> FreeNativeParameter (TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			return;

		} catch (_com_error &) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformParam);
			return;
		}
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformParam);
}

/////////////////////////////////////////////////////////////////////////////
// Connectionpoint anmelden/abmelden
HRESULT CCoordTransService::Advise (ICoordTransformEvents *pEventSink)
{
	TX_ASSERT(0 == m_dwCookie);
	return AtlAdvise (m_CTF, pEventSink, IID_ICoordTransformEvents, &m_dwCookie);
}

HRESULT CCoordTransService::UnAdvise()
{
	if (0 != m_dwCookie) {
	DWORD dwCookie = m_dwCookie;

		m_dwCookie = 0L;
		return AtlUnadvise (m_CTF, IID_ICoordTransformEvents, dwCookie);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OutputCS abfragen
HRESULT CCoordTransService::GetCoordTransformPipe(IDispatch **ppICS)
{
	if (NULL == ppICS)
		return E_POINTER;
	*ppICS = NULL;

	COM_TRY {
	__Interface<IDispatch> Pipe;

		THROW_FAILED_HRESULT(m_CTF -> get_CoordTransformPipe(Pipe.ppi()));
		*ppICS = Pipe.detach();

	} COM_CATCH;
	return S_OK;
}


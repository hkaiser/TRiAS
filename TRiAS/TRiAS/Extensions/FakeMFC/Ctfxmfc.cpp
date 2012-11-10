// Memberfunktionen fuer die Schnittstelle zu den Koordinaten-
// Transformations-DLL's (Extension)
// File: CTFXMFC.CPP

#include "StdAfx.h"		// StdAfx.h

#if _MSC_VER < 1100
#include "CtfxMfc.nocom.cpp"		// 'alte' Variante laden
#else

#ifdef _DEBUG
#if !defined(__CV__)				// MFC-Version
#define new DEBUG_NEW
#endif	// !__CV__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include <comcat.h>
#include <math.h>

//#include <ictf.h>
//#include <tdbgeo.h>
//#include <CSPoint.h>
#include <TRiASDB.h>
#include <TrCatIds.h>
#include <xtensnn.h>

#include <Com/PropertyHelper.h>
#include <objcontx.hxx>
#include <dblpair.hxx>
#include <ctfxmfc.h>

#import "tlb/TRiASCS.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

#if !defined(TX_TRY)
#define TX_TRY(x)	ATLTRY(x)
#endif // TX_TRY

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten Koordinatentransformation
namespace {
	const TCHAR g_cbCoordTransform[] = TEXT("CoordTransform  ");
	const TCHAR g_cbKoeff11[] = TEXT("Koeff11         ");
	const TCHAR g_cbKoeff12[] = TEXT("Koeff12         ");
	const TCHAR g_cbKoeff21[] = TEXT("Koeff21         ");
	const TCHAR g_cbKoeff22[] = TEXT("Koeff22         ");
	const TCHAR g_cbOffsetX[] = TEXT("OffsetX         ");
	const TCHAR g_cbOffsetY[] = TEXT("OffsetY         ");
	const TCHAR g_cbDefault[] = TEXT("DEFAULT");
	const TCHAR g_cbCTFService[] = TEXT("CTFService");
}
//const TCHAR g_cbTransform[] = TEXT("TRANSFORM");
//const TCHAR g_cbInvTransform[] = TEXT("INVTRANSFORM");
//const TCHAR g_cbCoordTransMode[] = TEXT("COORDTRANSMODE");
//const TCHAR g_cbCoordTransAspectRatio[] = TEXT("COORDTRANSASPECTRATIO");
//const TCHAR g_cbCoordTransDistance[] = TEXT("COORDTRANSDISTANCE");
//const TCHAR g_cbCoordTransDistanceEx[] = TEXT("COORDTRANSDISTANCEEX");
//const TCHAR g_cbCoordTransLoad[] = TEXT("COORDTRANSLOAD");
//const TCHAR g_cbCoordTransUnLoad[] = TEXT("COORDTRANSUNLOAD");
//const TCHAR g_cbCoordTransToString[] = TEXT("COORDTRANSTOSTRING");
//const TCHAR g_cbCoordTransToValue[] = TEXT("COORDTRANSTOVALUE");
//const TCHAR g_cbCoordTransToStringEx[] = TEXT("COORDTRANSTOSTRINGEX");
//const TCHAR g_cbCoordTransToValueEx[] = TEXT("COORDTRANSTOVALUEEX");
//const TCHAR g_cbCoordTransRectangle[] = TEXT("COORDTRANSRECTANGLE");
//const TCHAR g_cbCoordTransIsMetric[] = TEXT("COORDTRANSISMETRIC");
//const TCHAR g_cbCoordTransNative[] = TEXT("COORDTRANSNATIVE");
//const TCHAR g_cbCoordTransMetric[] = TEXT("COORDTRANSMETRIC");
//const TCHAR g_cbCoordTransDescription[] = TEXT("COORDTRANSDESCRIPTION");
//
//#if defined(WIN32)
//const char g_cbCoordTransNativeParam[] = TEXT("COORDTRANSNATIVEPARAM");
//const char g_cbCoordTransMetricParam[] = TEXT("COORDTRANSMETRICPARAM");
//const char g_cbCoordTransNativeEx[] = TEXT("COORDTRANSNATIVEEX");
//const char g_cbCoordTransMetricEx[] = TEXT("COORDTRANSMETRICEX");
//const char g_cbTransformEx[] = TEXT("TRANSFORMEX");
//const char g_cbInvTransformEx[] = TEXT("INVTRANSFORMEX");
//#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
//EXTERN_C const IID __declspec(selectany) IID_ITRiASProject = {0x1CB3AB62,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
//EXTERN_C const CLSID __declspec(selectany) CLSID_TRiASCSPoint = {0x0BDC3C1E,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumGUID);
DefineSmartInterface(CatInformation);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(CoordTransformInit);

///////////////////////////////////////////////////////////////////////////////
// sonstige Prototypen
namespace {
// lokale Fehlerbehandlungsroutine 
	static inline ErrCode loc_db_error (int EC, int RC)
	{
	ErrCode locRC;

		DEXN_ErrorMessage (locRC, EC, RC, NULL);
		return locRC;
	}

// Inverse Matrix für Koordinatentransformation berechnen ---------------------
	ErrCode EvalKoeffs (double *k11, double *k12, double *k21, double *k22) 
	{
	double DetA = *k11 * *k22 - *k12 * *k21;

		if (DetA != 0.0) {
		double temp = *k11;

			*k11 = *k22/DetA;
			*k22 = temp/DetA;
			*k12 = -(*k12/DetA);
			*k21 = -(*k21/DetA);
			return EC_OKAY;
		} else {
			return (ErrCode)loc_db_error (EC_BadKoeffs, RC_MatrixEvalKoeffs);
		}
	}
}

// Konstruktor/Destruktor -----------------------------------------------------
CCoordTransServiceX::CCoordTransServiceX (void)
{
	m_fIsDefault = false;
	m_fIsInitialized = false;
	m_fCanConfig = false;

// Initialisierung dieser CoordTransX
	try {
	WTRiASProject Prj;

		if (DEX_GetActiveProjectPtr(*Prj.ppi())) 
			InitCTFService (WTRiASPropertyBase(Prj));		// setzt m_fIsInitialized

	} catch (_com_error &e) {
		e;
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return;
	}
}

HRESULT CCoordTransServiceX::InitCTFService (ITRiASPropertyBase *pIPropBase)
{
	if (NULL == pIPropBase) 
		return E_POINTER;

	m_PropBase = pIPropBase;
	if (!Refresh (true))			// jetzt fertig initialiseren
		return E_FAIL;

	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die CTF neu geladen werden muß
bool CCoordTransServiceX::Reload (bool fRefresh)
{
	USES_CONVERSION;
	ASSERT(m_PropBase.IsValid());

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

bool CCoordTransServiceX::Refresh (bool fForce)
{
	ASSERT(m_PropBase.IsValid());

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

			if (SUCCEEDED(m_CTF -> QueryInterface (__uuidof(ICoordTransformInit), Init.ppv())))
				Init -> ReInitCoordTransform(m_PropBase);
		}
		return true;
	}

// Koeffizienten Matrix invertieren
	if (EvalKoeffs (&m_dInvK11, &m_dInvK12, &m_dInvK21, &m_dInvK22) != EC_OKAY)
		return false;	// entartete TMatrix

// Objekt erzeugen und initialisieren
	USES_CONVERSION;
	try {
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

CCoordTransServiceX::~CCoordTransServiceX (void)
{
	m_CTF.Assign (NULL);		// Objekt freigeben
}

// Funktionen, die nicht auf die CTF-DLL durchgreifen -------------------------
bool CCoordTransServiceX::Scale (const double &rdX, const double &rdY, Punkt &outPt)
{
	outPt.SetX(ScaleX (rdX, rdY));
	outPt.SetY(ScaleY (rdX, rdY));
	return true;
}

bool CCoordTransServiceX::Scale (const double &rdX, const double &rdY, KoOrd *pX, KoOrd *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = ScaleX (rdX, rdY);
	*pY = ScaleY (rdX, rdY);

	return true;
}

bool CCoordTransServiceX::UnScale (const Punkt &Pt, double *pX, double *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = UnScaleX (Pt.GetX(), Pt.GetY());
	*pY = UnScaleY (Pt.GetX(), Pt.GetY());;

	return true;
}

bool CCoordTransServiceX::UnScale (const KoOrd &inX, const KoOrd &inY, double *pX, double *pY)
{
	if (NULL == pX || NULL == pY) 
		return false;

	*pX = UnScaleX (inX, inY);
	*pY = UnScaleY (inX, inY);

	return true;
}

// Funktionen, die auf die CTF-DLL durchgreifen -------------------------------
double CCoordTransServiceX::CoordTransAspectRatio (ObjContainer &OC)
{
	if (m_fIsInitialized) {
		try {
		// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
		CCSPoint LO (UnScaleX(OC.XMin(), OC.YMax()), UnScaleY(OC.XMin(), OC.YMax()));
		CCSPoint RU (UnScaleX(OC.XMax(), OC.YMin()), UnScaleY(OC.XMax(), OC.YMin()));
		double dAspect = 1.0;
		
			THROW_FAILED_HRESULT(m_CTF -> get_AspectRatio (&LO, &RU, &dAspect));
			return dAspect;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransAspectRatio);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFAspect);
			return 1.0;
		}
	}
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransAspectRatio);
	loc_db_error (EC_UNEXPECTED, RC_CTFAspect);
	return 1.0;
}

inline double Sqr (double d) { return d*d; }

double CCoordTransServiceX::CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2)
{
	if (m_fIsInitialized) {
	double dDist = 0.0;

		try {
		CCSPoint pt1 (pP1 -> Width(), pP1 -> Height());
		CCSPoint pt2 (pP2 -> Width(), pP2 -> Height());
		W_DGMPoint ptDist;
		double dSum = 0.0;

			THROW_FAILED_HRESULT(m_CTF -> DistanceEx (&pt1, &pt2, ptDist.ppi(), &dDist));
			_ASSERTE(dDist >= 0.0);

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDistance);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);
		}
		return dDist;
	}
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDistance);
	loc_db_error (EC_UNEXPECTED, RC_CTFDistance);
	return 0.0;
}

bool CCoordTransServiceX::CoordTransDistanceEx (
	const DoublePair *pP1, const DoublePair *pP2, double &dX, double &dY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt1 (pP1 -> Width(), pP1 -> Height());
		CCSPoint pt2 (pP2 -> Width(), pP2 -> Height());
		W_DGMPoint outPt;

			THROW_FAILED_HRESULT(m_CTF -> Distance (&pt1, &pt2, outPt.ppi()));
			THROW_FAILED_HRESULT(outPt -> get_X (&dX));
			THROW_FAILED_HRESULT(outPt -> get_Y (&dY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDistanceEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);
			return false;
		}
	}
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDistanceEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFDistance);
	return false;
}

bool CCoordTransServiceX::Transform (double *pX, double *pY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt1 (*pX, *pY);

			THROW_FAILED_HRESULT(m_CTF -> Transform (&pt1, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(pt1 -> get_X (pX));
			THROW_FAILED_HRESULT(pt1 -> get_Y (pY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransform);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransform);
	loc_db_error (EC_UNEXPECTED, RC_CTFTrans);
	return false;
}

bool CCoordTransServiceX::Transform (DoublePair *pPoints, int iNum)
{
	if (m_fIsInitialized) {
		try {
			for (int i = 0; i < iNum; i++) {
			CCSPoint pt1 (pPoints[i].X(), pPoints[i].Y());

				THROW_FAILED_HRESULT(m_CTF -> Transform (&pt1, TRANSDIRECTION_FORWARD));
				THROW_FAILED_HRESULT(pt1 -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(pt1 -> get_Y (&pPoints[i].Y()));
			}
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransform);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
			return false;
		}
	
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransform);
	loc_db_error (EC_UNEXPECTED, RC_CTFTrans);
	return false;
}

bool CCoordTransServiceX::InvTransform (double *pX, double *pY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt1 (*pX, *pY);

			THROW_FAILED_HRESULT(m_CTF -> Transform (&pt1, TRANSDIRECTION_INVERSE));
			THROW_FAILED_HRESULT(pt1 -> get_X (pX));
			THROW_FAILED_HRESULT(pt1 -> get_Y (pY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransform);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransform);
	loc_db_error (EC_UNEXPECTED, RC_CTFInvTrans);
	return false;
}

bool CCoordTransServiceX::InvTransform (DoublePair *pPoints, int iNum)
{
	if (m_fIsInitialized) {
		try {
			for (int i = 0; i < iNum; i++) {
			CCSPoint pt1 (pPoints[i].X(), pPoints[i].Y());

				THROW_FAILED_HRESULT(m_CTF -> Transform (&pt1, TRANSDIRECTION_INVERSE));
				THROW_FAILED_HRESULT(pt1 -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(pt1 -> get_Y (&pPoints[i].Y()));
			}
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransform);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransform);
	loc_db_error (EC_UNEXPECTED, RC_CTFInvTrans);
	return false;
}

char * CCoordTransServiceX::CoordTransDescription (char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		try {
		CComBSTR bstr;

			THROW_FAILED_HRESULT(m_CTF -> get_Description (CLEARED(&bstr)));
		
			USES_CONVERSION;
			iLen = min(bstr.Length(), (size_t)(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransDescription);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFLoad);
			return NULL;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransDescription);
	loc_db_error (EC_UNEXPECTED, RC_CTFLoad);
	return NULL;
}

#if defined(__CV__)
bool CCoordTransServiceX::CoordTransMode ( pWindow )
#else
bool CCoordTransServiceX::CoordTransMode ( HWND )
#endif
{
	loc_db_error (E_NOTIMPL, RC_CTFLoad);
	return false;
}

char * CCoordTransServiceX::CoordTransToString (
	double Value, bool isX, char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		try {
		CComBSTR bstr;

			if (isX) {
			CCSPoint pt (Value, 0.0);

				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, CLEARED(&bstr), NULL, NULL));
			} else {
			CCSPoint pt (0.0, Value);

				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, NULL, CLEARED(&bstr), NULL));
			}

			USES_CONVERSION;
			iLen = min(bstr.Length(), size_t(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToString);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFToString);
			return NULL;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToString);
	loc_db_error (EC_UNEXPECTED, RC_CTFToString);
	return NULL;
}

double CCoordTransServiceX::CoordTransToValue (char *pBuffer)
{
	loc_db_error (EC_UNEXPECTED, RC_CTFToString);
//	ShowError (E_NOTIMPL, IDS_CSSERRORCAPTION, g_cbCoordTransToValue);
	return 0.0;
}

char * CCoordTransServiceX::CoordTransToStringEx (
	double dX, double dY, bool isX, char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		try {
		CComBSTR bstr;
		CCSPoint pt (dX, dY);

			if (isX) {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, CLEARED(&bstr), NULL, NULL));
			} else {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, NULL, CLEARED(&bstr), NULL));
			}

			USES_CONVERSION;
			iLen = min(bstr.Length(), size_t(iLen-1));
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFToString);
			return NULL;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFToString);
	return NULL;
}

bool CCoordTransServiceX::CoordTransToValueEx (
	const char *pBuffX, const char *pBuffY, double &dX, double &dY)
{
	if (m_fIsInitialized) {
		try {
		CComBSTR bstrX (pBuffX);
		CComBSTR bstrY (pBuffY);
		W_DGMPoint pt;

			THROW_FAILED_HRESULT(m_CTF -> ToPoint (bstrX, bstrY, NULL, pt.ppi()));
			THROW_FAILED_HRESULT(pt -> get_X(&dX));
			THROW_FAILED_HRESULT(pt -> get_Y(&dY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToValueEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFToValue);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToValueEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFToValue);
	return false;
}

bool CCoordTransServiceX::CoordTransRectangle (
	const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint ptIn (pIn -> Width(), pIn -> Height());
		CCSPoint ptDelta (pDelta -> Width(), pDelta -> Height());
		W_DGMPoint ptOut;

			THROW_FAILED_HRESULT(m_CTF -> DistancePoint (&ptIn, &ptDelta, ptOut.ppi()));
			THROW_FAILED_HRESULT(ptOut -> get_X(&pOut -> X()));
			THROW_FAILED_HRESULT(ptOut -> get_Y(&pOut -> Y()));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransRectangle);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFRectangle);
			return false;
		}
	}
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransRectangle);
	loc_db_error (EC_UNEXPECTED, RC_CTFRectangle);
	return false;
}

// Funktionen, die Koordinaten in metrische Einheiten konvertieren ------------
bool CCoordTransServiceX::isMetric (void)
{
	if (m_fIsInitialized) {
		try {
		VARIANT_BOOL fVal = VARIANT_TRUE;

			THROW_FAILED_HRESULT(m_CTF -> get_IsMetric (&fVal));
			return fVal ? true : false;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbIsMetric);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFisMetric);
			return true;	// metrisch annehmen
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbIsMetric);
	loc_db_error (EC_UNEXPECTED, RC_CTFisMetric);
	return true;	// metrisch annehmen
}

#if _TRiAS_VER < 0x0400
bool CCoordTransServiceX::Native (const double &rdX, const double &rdY, Punkt &outPt)
{
KoOrd dX = 0;
KoOrd dY = 0;

	if (Native (rdX, rdY, &dX, &dY)) {
		outPt.SetX(dX);
		outPt.SetY(dY);
		return true;
	}
	return false;
}

bool CCoordTransServiceX::Native (const double &rdX, const double &rdY, KoOrd *pX, KoOrd *pY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (rdX, rdY);

			THROW_FAILED_HRESULT(m_CTF -> Native (&pt, TRANSDIRECTION_INVERSE));

		double dX, dY;

			THROW_FAILED_HRESULT(pt -> get_X(&dX));
			THROW_FAILED_HRESULT(pt -> get_Y(&dY));
			return Scale (dX, dY, pX, pY);
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNative);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNative);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}

bool CCoordTransServiceX::Metric (const Punkt &Pt, double *pX, double *pY)
{
	return Metric (Pt.GetX(), Pt.GetY(), pX, pY);
}

bool CCoordTransServiceX::Metric (const KoOrd &inX, const KoOrd &inY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		try {
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

		CCSPoint pt (dX, dY);

			THROW_FAILED_HRESULT(m_CTF -> Native (&pt, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(pt -> get_X(pX));
			THROW_FAILED_HRESULT(pt -> get_Y(pY));
			return true;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetric);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetric);
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}
#else
bool CCoordTransServiceX::Native (const double &rdX, const double &rdY, DoublePair &outPt)
{
double dX = 0;
double dY = 0;

	if (Native (rdX, rdY, &dX, &dY)) {
		outPt.X() = dX;
		outPt.Y() = dY;
		return true;
	}
	return false;
}

bool CCoordTransServiceX::Native (const double &rdX, const double &rdY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (rdX, rdY);

			THROW_FAILED_HRESULT(m_CTF -> Native (&pt, TRANSDIRECTION_INVERSE));
			THROW_FAILED_HRESULT(pt -> get_X(pX));
			THROW_FAILED_HRESULT(pt -> get_Y(pY));
			return true;
						
		} catch (...) {
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}

bool CCoordTransServiceX::Metric (const DoublePair &Pt, double *pX, double *pY)
{
	return Metric (Pt.Width(), Pt.Height(), pX, pY);
}

bool CCoordTransServiceX::Metric (const double &dX, const double &dY, double *pX, double *pY)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (dX, dY);

			THROW_FAILED_HRESULT(m_CTF -> Native (&pt, TRANSDIRECTION_FORWARD));
			THROW_FAILED_HRESULT(pt -> get_X(pX));
			THROW_FAILED_HRESULT(pt -> get_Y(pY));
			return true;
						
		} catch (...) {
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Funktionen für parametrisierbare Transformationen
bool CCoordTransServiceX::GetMetricParam (const Punkt &rPt, LPVOID *ppData)
{
	return GetMetricParam (rPt.GetX(), rPt.GetY(), ppData);
}

bool CCoordTransServiceX::GetMetricParam (KoOrd iX, KoOrd iY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		try {
		double dX, dY;

			if (!UnScale (iX, iY, &dX, &dY)) return false;

		CCSPoint pt (dX, dY);

			if (SUCCEEDED(m_CTF -> NativeParameter (&pt, TRANSDIRECTION_FORWARD, (IDispatch **)ppData)))
				return true;
			return false;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}

#if _TRiAS_VER < 0x0400
bool CCoordTransServiceX::MetricEx (const Punkt &rPt, double *pX, double *pY, LPVOID pData)
{
	return MetricEx (rPt.GetX(), rPt.GetY(), pX, pY, pData);
}

bool CCoordTransServiceX::MetricEx (KoOrd inX, KoOrd inY, double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		double dX, dY;

			if (!UnScale (inX, inY, &dX, &dY)) return false;

		CCSPoint pt (dX, dY);

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			THROW_FAILED_HRESULT(pt -> get_X(pX));
			THROW_FAILED_HRESULT(pt -> get_Y(pY));
			return true;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}
#else
bool CCoordTransServiceX::MetricEx (const DoublePair &rPt, double *pX, double *pY, LPVOID pData)
{
	return MetricEx (rPt.Width(), rPt.Height(), pX, pY, pData);
}

bool CCoordTransServiceX::MetricEx (double dX, double dY, double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (dX, dY);

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&pt, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			THROW_FAILED_HRESULT(pt -> get_X(pX));
			THROW_FAILED_HRESULT(pt -> get_Y(pY));
			return true;
						
		} catch (...) {
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

bool CCoordTransServiceX::GetNativeParam (const double &rdX, const double &rdY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (rdX, rdY);

			if (SUCCEEDED(m_CTF -> NativeParameter (&pt, TRANSDIRECTION_INVERSE, (IDispatch **)ppData)))
				return true;
			return false;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNativeParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNativeParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}

#if _TRiAS_VER < 0x0400
bool CCoordTransServiceX::NativeEx (const double &rdX, const double &rdY, Punkt &outPt, LPVOID pData)
{
KoOrd dX = 0;
KoOrd dY = 0;

	if (NativeEx (rdX, rdY, &dX, &dY, pData)) {
		outPt.SetX(dX);
		outPt.SetY(dY);
		return true;
	}
	return false;
}

bool CCoordTransServiceX::NativeEx (const double &rdX, const double &rdY, KoOrd *piX, KoOrd *piY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (rdX, rdY);

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&pt, TRANSDIRECTION_INVERSE, (IDispatch *)pData));

		double dX, dY;

			THROW_FAILED_HRESULT(pt -> get_X(&dX));
			THROW_FAILED_HRESULT(pt -> get_Y(&dY));
			return Scale (dX, dY, piX, piY);
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}
#else
bool CCoordTransServiceX::NativeEx (const double &rdX, const double &rdY, DoublePair &outPt, LPVOID pData)
{
double dX = 0;
double dY = 0;

	if (NativeEx (rdX, rdY, &dX, &dY, pData)) {
		outPt.X() = dX;
		outPt.Y() = dY;
		return true;
	}
	return false;
}

bool CCoordTransServiceX::NativeEx (const double &rdX, const double &rdY, double *piX, double *piY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (rdX, rdY);

			THROW_FAILED_HRESULT(m_CTF -> NativeEx (&pt, TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			THROW_FAILED_HRESULT(pt -> get_X(piX));
			THROW_FAILED_HRESULT(pt -> get_Y(piY));
			return true;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}
#endif // _TRiAS_VER < 0x0400

bool CCoordTransServiceX::GetTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (dX, dY);

			if (SUCCEEDED(m_CTF -> TransformParameter (&pt, TRANSDIRECTION_FORWARD, (IDispatch **)ppData)))
				return true;
			return false;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
	return false;	// Fehler
}

bool CCoordTransServiceX::GetInvTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt (dX, dY);

			if (SUCCEEDED(m_CTF -> TransformParameter (&pt, TRANSDIRECTION_INVERSE, (IDispatch **)ppData)))
				return true;
			return false;
						
//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;	// Fehler
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;	// Fehler
}

bool CCoordTransServiceX::TransformEx (double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt1 (*pX, *pY);

			THROW_FAILED_HRESULT(m_CTF -> TransformEx (&pt1, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			THROW_FAILED_HRESULT(pt1 -> get_X (pX));
			THROW_FAILED_HRESULT(pt1 -> get_Y (pY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;
}

bool CCoordTransServiceX::TransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			for (int i = 0; i < iNum; i++) {
			CCSPoint pt1 (pPoints[i].X(), pPoints[i].Y());

				THROW_FAILED_HRESULT(m_CTF -> TransformEx (&pt1, TRANSDIRECTION_FORWARD, (IDispatch *)pData));
				THROW_FAILED_HRESULT(pt1 -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(pt1 -> get_Y (&pPoints[i].Y()));
			}
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
	return false;
}

bool CCoordTransServiceX::InvTransformEx (double *pX, double *pY, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
		CCSPoint pt1 (*pX, *pY);

			THROW_FAILED_HRESULT(m_CTF -> TransformEx (&pt1, TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			THROW_FAILED_HRESULT(pt1 -> get_X (pX));
			THROW_FAILED_HRESULT(pt1 -> get_Y (pY));
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFInvTrans);
	return false;
}

bool CCoordTransServiceX::InvTransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			for (int i = 0; i < iNum; i++) {
			CCSPoint pt1 (pPoints[i].X(), pPoints[i].Y());

				THROW_FAILED_HRESULT(m_CTF -> TransformEx (&pt1, TRANSDIRECTION_INVERSE, (IDispatch *)pData));
				THROW_FAILED_HRESULT(pt1 -> get_X (&pPoints[i].X()));
				THROW_FAILED_HRESULT(pt1 -> get_Y (&pPoints[i].Y()));
			}
			return true;

//		} catch (_com_error &e) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformEx);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
			return false;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformEx);
	loc_db_error (EC_UNEXPECTED, RC_CTFInvTrans);
	return false;
}

void CCoordTransServiceX::FreeMetricParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			THROW_FAILED_HRESULT(m_CTF -> FreeNativeParameter (TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			return;

//		} catch (_com_error &) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbMetricParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);
			return;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbMetricParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFMetric);
}

void CCoordTransServiceX::FreeNativeParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			THROW_FAILED_HRESULT(m_CTF -> FreeNativeParameter (TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			return;

//		} catch (_com_error &) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbNativeParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);
			return;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbNativeParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFNative);
}

void CCoordTransServiceX::FreeTransformParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			THROW_FAILED_HRESULT(m_CTF -> FreeTransformParameter (TRANSDIRECTION_FORWARD, (IDispatch *)pData));
			return;

//		} catch (_com_error &) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbTransformParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
			return;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbTransformParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFTrans);
}

void CCoordTransServiceX::FreeInvTransformParam (LPVOID pData)
{
	if (m_fIsInitialized) {
		try {
			THROW_FAILED_HRESULT(m_CTF -> FreeTransformParameter (TRANSDIRECTION_INVERSE, (IDispatch *)pData));
			return;

//		} catch (_com_error &) {
		} catch (...) {
//			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbInvTransformParam);
			loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
			return;
		}
	} 
//	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbInvTransformParam);
	loc_db_error (EC_UNEXPECTED, RC_CTFTrans);
}

///////////////////////////////////////////////////////////////////////////////
// OutputCS abfragen
HRESULT CCoordTransServiceX::GetOutputCS(IDispatch **ppICS)
{
	if (NULL == ppICS)
		return E_POINTER;
	*ppICS = NULL;

	COM_TRY {
	__Interface<IDispatch> Pipe;
	__Interface<ITRiASCS> OutCS;

		THROW_FAILED_HRESULT(m_CTF -> get_CoordTransformPipe(Pipe.ppi()));
		THROW_FAILED_HRESULT(__Interface<ITRiASCSTransform>(Pipe) -> get_OutputCS(OutCS.ppi()));
		THROW_FAILED_HRESULT(OutCS -> QueryInterface(ppICS));

	} COM_CATCH;
	return S_OK;
}

#endif // WIN32

#endif // _MSC_VER < 1100

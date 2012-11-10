// Memberfunktionen fuer die Schnittstelle zu den Koordinaten-
// Transformations-DLL's (Extension)
// File: CTFX.CXX
// H. Kaiser (mit meiner Exportierung: _GEOMETR_EXPORT,
//            meinem EPunkt, meinem ObjRechteck sowie
//            Information, daß meine DLL aktiviert ist)

#include "GeometrP.hxx"

//#include "xtensnp.hxx"

//#include <resstrg.h>
//#include <dllbindx.hxx>
//#include <objcontx.hxx>
//#include <dblpair.hxx>
#include "ctfx.hxx"
#include <hdrentrx.hxx>

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten Koordinatentransformation
const char g_cbCoordTransform[] = TEXT("CoordTransform  ");
const char g_cbCTFExt[] = TEXT(".CTF");
const char g_cbDefaultCTF[] = TEXT("DEFAULT.CTF");
const char g_cbKoeff11[] = TEXT("Koeff11         ");
const char g_cbKoeff12[] = TEXT("Koeff12         ");
const char g_cbKoeff21[] = TEXT("Koeff21         ");
const char g_cbKoeff22[] = TEXT("Koeff22         ");
const char g_cbOffsetX[] = TEXT("OffsetX         ");
const char g_cbOffsetY[] = TEXT("OffsetY         ");

const char g_cbTransform[] = TEXT("TRANSFORM");
const char g_cbInvTransform[] = TEXT("INVTRANSFORM");
const char g_cbCoordTransMode[] = TEXT("COORDTRANSMODE");
const char g_cbCoordTransAspectRatio[] = TEXT("COORDTRANSASPECTRATIO");
const char g_cbCoordTransDistance[] = TEXT("COORDTRANSDISTANCE");
const char g_cbCoordTransDistanceEx[] = TEXT("COORDTRANSDISTANCEEX");
const char g_cbCoordTransLoad[] = TEXT("COORDTRANSLOAD");
const char g_cbCoordTransUnLoad[] = TEXT("COORDTRANSUNLOAD");
const char g_cbCoordTransToString[] = TEXT("COORDTRANSTOSTRING");
const char g_cbCoordTransToValue[] = TEXT("COORDTRANSTOVALUE");
const char g_cbCoordTransToStringEx[] = TEXT("COORDTRANSTOSTRINGEX");
const char g_cbCoordTransToValueEx[] = TEXT("COORDTRANSTOVALUEEX");
const char g_cbCoordTransRectangle[] = TEXT("COORDTRANSRECTANGLE");
const char g_cbCoordTransIsMetric[] = TEXT("COORDTRANSISMETRIC");
const char g_cbCoordTransNative[] = TEXT("COORDTRANSNATIVE");
const char g_cbCoordTransMetric[] = TEXT("COORDTRANSMETRIC");

#if defined(WIN32)
const char g_cbCoordTransNativeParam[] = TEXT("COORDTRANSNATIVEPARAM");
const char g_cbCoordTransMetricParam[] = TEXT("COORDTRANSMETRICPARAM");
const char g_cbCoordTransNativeEx[] = TEXT("COORDTRANSNATIVEEX");
const char g_cbCoordTransMetricEx[] = TEXT("COORDTRANSMETRICEX");
const char g_cbTransformEx[] = TEXT("TRANSFORMEX");
const char g_cbInvTransformEx[] = TEXT("INVTRANSFORMEX");
#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
//
ErrCode EvalKoeffs (double *, double *, double *, double *);

// lokale Fehlerbehandlungsroutine --------------------------------------------
static inline ErrCode loc_db_error (int EC, int RC)
{
ErrCode locRC;

	DEXN_ErrorMessage (locRC, EC, RC, NULL);

return locRC;
}

// Konstruktor/Destruktor -----------------------------------------------------
_GEOMETR_EXPORT CoordTransX :: CoordTransX (void)
{
HeaderEntryX HE (g_cbCoordTransform);

	_pDLL = NULL;	// für alle Fälle NULL setzen
	m_fIsDefault = false;

	if (HE.Status() != HE_INVALID) {
	char CTName[_MAX_FNAME];

		strcpy (CTName, HE.EntryText());
		strcat (CTName, g_cbCTFExt);
		_pDLL = new CDllBindX (CTName);
		if (_pDLL == NULL) {
			loc_db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
	} 
	if (_pDLL == NULL || _pDLL -> hLib() == 0) {	// Objekt ungültig
		DELETE_OBJ (_pDLL);
		_pDLL = new CDllBindX (g_cbDefaultCTF);
		if (_pDLL == NULL) {
			loc_db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
	}

	Refresh (true);
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die CTF neu geladen werden muß
bool CoordTransX::Reload (bool fRefresh)
{
HeaderEntryX HE (g_cbCoordTransform);

	if (HE.Status() != HE_INVALID) {
		if (strcmp (_pDLL -> GetName(), HE.EntryText()))
			return true;	// neue CTF laden
	} else if (!m_fIsDefault) {
		m_fIsDefault = true;
		return true;		// war nicht DEFAULT und ist jetzt nichts mehr
	}

	if (fRefresh) Refresh();

return false;	// muß nicht neu geladen werden
}

bool CoordTransX::Refresh (bool fForce)
{
// SkalierungsKoeffizienten lesen
double dK11, dK12, dK21, dK22, dOX, dOY;

	{
	// Koeffizienten aus DB-Header lesen
		dK11 = HeaderEntryX (g_cbKoeff11).EntryDouble(1.0);
		dK12 = HeaderEntryX (g_cbKoeff12).EntryDouble(0.0);
		dK21 = HeaderEntryX (g_cbKoeff21).EntryDouble(0.0);
		dK22 = HeaderEntryX (g_cbKoeff22).EntryDouble(1.0);
		dOX = HeaderEntryX (g_cbOffsetX).EntryDouble(0.0);
		dOY = HeaderEntryX (g_cbOffsetY).EntryDouble(0.0);
	}

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
	} else
		return true;

// Koeffizienten Matrix invertieren
	if (EvalKoeffs (&m_dInvK11, &m_dInvK12, &m_dInvK21, &m_dInvK22) != EC_OKAY)
		return false;	// entartete TMatrix

// für Hin- und Rücktransformation Funktionen binden
	CTFTransFunc = (CTFTRANSPROC)GetProcAddress (g_cbTransform);
	CTFInvTransFunc = (CTFTRANSPROC)GetProcAddress (g_cbInvTransform);
	CTFAspectFunc = (CTFASPECTPROC)GetProcAddress (g_cbCoordTransAspectRatio);
	CTFDistanceFunc = (CTFDISTANCEPROC)GetProcAddress (g_cbCoordTransDistance);
	CTFDistExFunc = (CTFDISTEXPROC)GetProcAddress (g_cbCoordTransDistanceEx);
	CTFStringFunc = (CTFTOSTRINGPROC)GetProcAddress (g_cbCoordTransToString);
	CTFValueFunc = (CTFTOVALUEPROC)GetProcAddress (g_cbCoordTransToValue);
	CTFStringExFunc = (CTFTOSTRINGEXPROC)GetProcAddress (g_cbCoordTransToStringEx);
	CTFValueExFunc = (CTFTOVALUEEXPROC)GetProcAddress (g_cbCoordTransToValueEx);
	CTFRectFunc = (CTFRECTPROC)GetProcAddress (g_cbCoordTransRectangle);
	CTFIsMetricFunc = (CTFISMETRICPROC)GetProcAddress (g_cbCoordTransIsMetric);
	CTFNativeFunc = (CTFTRANSPROC)GetProcAddress (g_cbCoordTransNative);
	CTFMetricFunc = (CTFTRANSPROC)GetProcAddress (g_cbCoordTransMetric);
#if defined(WIN32)
	CTFMetricParamFunc = (CTFTRANSPARAMPROC)GetProcAddress (g_cbCoordTransMetricParam);
	CTFMetricExFunc = (CTFTRANSPROCEX)GetProcAddress(g_cbCoordTransMetricEx);
	CTFNativeParamFunc = (CTFTRANSPARAMPROC)GetProcAddress (g_cbCoordTransNativeParam);
	CTFNativeExFunc = (CTFTRANSPROCEX)GetProcAddress(g_cbCoordTransNativeEx);
	CTFTransExFunc = (CTFTRANSPROCEX)GetProcAddress (g_cbTransformEx);
	CTFInvTransExFunc = (CTFTRANSPROCEX)GetProcAddress (g_cbInvTransformEx);
#endif // WIN32


// ÄNDERUNG: DLL informieren, daß sie aktiviert ist, FensterHandle mitteilen
#if defined(__GEOMETRDLL__) || defined(GEOMETR_DLL)
	CoordTransLoad (__hWndM);
#else
	CoordTransLoad (g_pTE -> hWnd());
#endif


// überprüfen, ob CTF Config-Mode besitzt
	m_fConfig = (NULL != GetProcAddress (g_cbCoordTransMode));

// überprüfen, ob CTF DistanceExFunktion besitzt
	m_fDistEx = (NULL != GetProcAddress (g_cbCoordTransDistanceEx));

return true;
}

_GEOMETR_EXPORT CoordTransX :: ~CoordTransX (void)
{
// DLL informieren, das jetzt alles vorbei ist
	CoordTransUnLoad();

// DLL freigeben
	DELETE_OBJ (_pDLL);
}

// Funktionen, die nicht auf die CTF-DLL durchgreifen -------------------------
BOOL _GEOMETR_EXPORT CoordTransX :: Scale (const double &pX, const double &pY, EPunkt &outPt)
{
double tX = pX - m_dOX;
double tY = pY - m_dOY;

	outPt.X() = (KoOrd)(m_dInvK11 * tX + m_dInvK12 * tY);
	outPt.Y() = (KoOrd)(m_dInvK21 * tX + m_dInvK22 * tY);
	
return TRUE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: Scale (const double &X, const double &Y, 
			   KoOrd *pX, KoOrd *pY)
{
double tX = X - m_dOX;
double tY = Y - m_dOY;

	*pX = (KoOrd)(m_dInvK11 * tX + m_dInvK12 * tY);
	*pY = (KoOrd)(m_dInvK21 * tX + m_dInvK22 * tY);
	
return TRUE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: UnScale (const EPunkt &Pt, double *pX, double *pY)
{
	*pX = m_dK11 * (double)((EPunkt &)Pt).X() + m_dK12 * (double)((EPunkt &)Pt).Y() + m_dOX;
	*pY = m_dK21 * (double)((EPunkt &)Pt).X() + m_dK22 * (double)((EPunkt &)Pt).Y() + m_dOY;
	
return TRUE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: UnScale (const KoOrd &inX, const KoOrd &inY, 
			     double *pX, double *pY)
{
	*pX = m_dK11 * (double)inX + m_dK12 * (double)inY + m_dOX;
	*pY = m_dK21 * (double)inX + m_dK22 * (double)inY + m_dOY;
	
return TRUE;
}


// Funktionen, die auf die CTF-DLL durchgreifen -------------------------------
double _GEOMETR_EXPORT CoordTransX :: CoordTransAspectRatio (ObjRechteck &OC)
{
	if (CTFAspectFunc) {
	// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	double XOut = (long)(m_dK11 * (double)OC.XMin() + m_dK12 * (double)OC.YMax() + m_dOX);
	double YOut = (long)(m_dK21 * (double)OC.XMin() + m_dK22 * (double)OC.YMax() + m_dOY);
	DoublePair LO (XOut, YOut);

		XOut = (long)(m_dK11 * (double)OC.XMax() + m_dK12 * (double)OC.YMin() + m_dOX);
		YOut = (long)(m_dK21 * (double)OC.XMax() + m_dK22 * (double)OC.YMin() + m_dOY);

	DoublePair RU (XOut, YOut);

	// DLL-Funktion rufen
		return (*CTFAspectFunc)(&LO, &RU);
	}
	loc_db_error (EC_NODLLFUNCTION, RC_CTFAspect);

return 1.0;
}

double _GEOMETR_EXPORT CoordTransX :: CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2)
{
	if (CTFDistanceFunc) {
	// DLL-Funktion rufen

		return (*CTFDistanceFunc)(pP1, pP2);
	}
	loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);

return 0.0;
}

bool _GEOMETR_EXPORT CoordTransX :: CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, 
			   double &dX, double &dY)
{
	if (m_fDistEx) {		// DistanceEx wird unterstützt
		if (!CTFDistExFunc) {
			loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);
			return false;
		}

	// DLL-Funktion rufen
	DoublePair D;

		if ((*CTFDistExFunc)(pP1, pP2, &D)) {
			dX = D.X();
			dY = D.Y();
			return true;
		}
	} else {
	DoublePair P1 (pP1->Width(), pP1->Height());
	DoublePair P2 (pP2->Width(), pP1->Height());
	DoublePair P3 (pP2->Width(), pP2->Height());

		dX = CoordTransDistance (&P1, &P2);
		dY = CoordTransDistance (&P2, &P3);
		return true;
	}

	loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);

return false;
}

BOOL _GEOMETR_EXPORT CoordTransX :: Transform (double *pX, double *pY)
{
	if (CTFTransFunc) {
	DoublePair DP (*pX, *pY);

		if ((*CTFTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		}
	} else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
	
return FALSE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: Transform (DoublePair *pPoints, short iNum)
{
	if (CTFTransFunc) // DLL-Funktion rufen
		return (*CTFTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
		
return FALSE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: InvTransform (double *pX, double *pY)
{
	if (CTFInvTransFunc) {
	// DLL-Funktion rufen
	DoublePair DP (*pX, *pY);

		if ((*CTFInvTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		}
	} else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
		
return FALSE;
}

BOOL _GEOMETR_EXPORT CoordTransX :: InvTransform (DoublePair *pPoints, short iNum)
{
	if (CTFInvTransFunc) // DLL-Funktion rufen
		return (*CTFInvTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
		
return FALSE;
}

char* _GEOMETR_EXPORT CoordTransX :: CoordTransDescription (char *, short)
{
	return NULL;
}

Bool _GEOMETR_EXPORT CoordTransX :: CoordTransMode (pWindow pW)
{
CTFMODEPROC CTFHandlingFunc = (CTFMODEPROC)GetProcAddress (g_cbCoordTransMode);

	if (CTFHandlingFunc) {	// DLL Funktion rufen
	COORDTRANSMODE CTM;

		CTM.dwSize = sizeof(COORDTRANSMODE);
		CTM.hWnd = pW -> Handle (API_WINDOW_HWND);

		return (*CTFHandlingFunc)(&CTM);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return false;
}

Bool _GEOMETR_EXPORT CoordTransX :: CoordTransLoad (HWND hWnd)
{
CTFLOADPROC CTFHandlingFunc = (CTFLOADPROC)GetProcAddress (g_cbCoordTransLoad);

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)(hWnd);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return FALSE;
}

Bool _GEOMETR_EXPORT CoordTransX :: CoordTransUnLoad (void)
{
CTFUNLOADPROC CTFHandlingFunc = (CTFUNLOADPROC)GetProcAddress (g_cbCoordTransUnLoad);

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)();
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFUnLoad);

return FALSE;
}

char* _GEOMETR_EXPORT CoordTransX :: CoordTransToString (double Value, 
					 BOOL isX,
					 char *pBuffer, 
					 short iLen)
{
	if (CTFStringFunc) {
	// DLL Funktion rufen

		return (*CTFStringFunc)(Value, isX, pBuffer, iLen);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFToString);

return NULL;
}

double _GEOMETR_EXPORT CoordTransX :: CoordTransToValue (char *pBuffer)
{
	if (CTFValueFunc) {
	// DLL Funktion rufen

		return (*CTFValueFunc)(pBuffer);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFToValue);

return NULL;
}

char* _GEOMETR_EXPORT CoordTransX :: CoordTransToStringEx (double dX, double dY,
						    bool isX, char *pBuffer, 
						    short iLen)
{
	if (CTFStringExFunc) {
	// DLL Funktion rufen
	DoublePair DP(dX, dY);

		if ((*CTFStringExFunc)(pBuffer, iLen, isX, &DP))
			return pBuffer;
		else
			return NULL;
	} else {
		if (isX) 
			return CoordTransToString (dX, true, pBuffer, iLen);
		else
			return CoordTransToString (dY, false, pBuffer, iLen);
	}			
}

bool _GEOMETR_EXPORT CoordTransX :: CoordTransToValueEx (const char *pBuffX, const char *pBuffY,
						 double &dX, double &dY)
{
	if (CTFValueExFunc) {
	// DLL Funktion rufen
	DoublePair DP;
	
		if ((*CTFValueExFunc)(&DP, pBuffX, pBuffY)) {
			dX = DP.Width();
			dY = DP.Height();
			return true;
		} else
			return false;
	} else {
		dX = CoordTransToValue ((char *)pBuffX);
		dY = CoordTransToValue ((char *)pBuffY);
		return true;
	}
}

BOOL _GEOMETR_EXPORT CoordTransX :: CoordTransRectangle (const DoublePair *pIn, 
					 const DoublePair *pDelta, 
					 DoublePair *pOut)
{
	if (CTFRectFunc) {
	// DLL Funktion rufen

		return (*CTFRectFunc)(pIn, pDelta, pOut);
	} else
		loc_db_error (EC_NODLLFUNCTION, RC_CTFRectangle);
		
return FALSE;
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


// Funktionen, die Koordinaten in metrische Einheiten konvertieren ------------
BOOL _GEOMETR_EXPORT CoordTransX :: isMetric (void)
{
	if (CTFIsMetricFunc) {
	// DLL Funktion rufen

		return (*CTFIsMetricFunc)();
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFisMetric);

return TRUE;	// metrisch annehmen
}

BOOL _GEOMETR_EXPORT CoordTransX :: Native (const double &pX, const double &pY, EPunkt &outPt)
{
	if (CTFNativeFunc) {
	// DLL Funktion rufen
	DoublePair DP (pX, pY);

		if ((*CTFNativeFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), outPt);
		else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return FALSE;	// Fehler
}

BOOL _GEOMETR_EXPORT CoordTransX :: Native (const double &X, const double &Y, 
			   KoOrd *pX, KoOrd *pY)
{
	if (CTFNativeFunc) {
	// DLL Funktion rufen
	DoublePair DP (X, Y);

		if ((*CTFNativeFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), pX, pY);
		else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return FALSE;	// Fehler
}

BOOL _GEOMETR_EXPORT CoordTransX :: Metric (const EPunkt &Pt, double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (Pt, &DP.X(), &DP.Y())) return FALSE;

	if (CTFMetricFunc) {
	// DLL Funktion rufen

		if ((*CTFMetricFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		} else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return FALSE;	// Fehler
}

BOOL _GEOMETR_EXPORT CoordTransX :: Metric (const KoOrd &inX, const KoOrd &inY, 
			   double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (inX, inY, &DP.X(), &DP.Y())) return FALSE;

	if (CTFMetricFunc) {
	// DLL Funktion rufen

		if ((*CTFMetricFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		} else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return FALSE;	// Fehler
}

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Funktionen für parametrisierbare Transformationen
bool CoordTransX::GetMetricParam (const EPunkt &rPt, LPVOID *ppData)
{
DoublePair DP;

	if (!UnScale (rPt, &DP.X(), &DP.Y())) return false;

	if (CTFMetricParamFunc)	// DLL Funktion rufen
		return (*CTFMetricParamFunc)(&DP, ppData);

	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTransX::GetMetricParam (KoOrd iX, KoOrd iY, LPVOID *ppData)
{
DoublePair DP;

	if (!UnScale (iX, iY, &DP.X(), &DP.Y())) return false;

	if (CTFMetricParamFunc)	// DLL Funktion rufen
		return (*CTFMetricParamFunc)(&DP, ppData);

	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTransX::MetricEx (const EPunkt &rPt, double *pX, double *pY, LPVOID pData)
{
DoublePair DP;

	if (!UnScale (rPt, &DP.X(), &DP.Y())) return false;

	if (CTFMetricExFunc) {
	// DLL Funktion rufen
		if ((*CTFMetricExFunc)(&DP, 1, pData)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		} else
			return false;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

bool CoordTransX::MetricEx (KoOrd inX, KoOrd inY, double *pX, double *pY, LPVOID pData)
{
DoublePair DP;

	if (!UnScale (inX, inY, &DP.X(), &DP.Y())) return false;

	if (CTFMetricExFunc) {
	// DLL Funktion rufen

		if ((*CTFMetricExFunc)(&DP, 1, pData)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		} else
			return false;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

bool CoordTransX::GetNativeParam (const double &rdX, const double &rdY, LPVOID *ppData)
{
	if (CTFNativeParamFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		return (*CTFNativeParamFunc)(&DP, ppData);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;
}

bool CoordTransX::NativeEx (const double &rdX, const double &rdY, EPunkt &outPt, LPVOID pData)
{
	if (CTFNativeExFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		if ((*CTFNativeExFunc)(&DP, 1, pData)) 
			return Scale (DP.X(), DP.Y(), outPt);
		else
			return false;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool CoordTransX::NativeEx (const double &rdX, const double &rdY, KoOrd *piX, KoOrd *piY, LPVOID pData)
{
	if (CTFNativeExFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		if ((*CTFNativeExFunc)(&DP, 1, pData)) 
			return Scale (DP.X(), DP.Y(), piX, piY);
		else
			return false;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool CoordTransX::GetTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (CTFMetricParamFunc)	{
	// DLL Funktion rufen
	DoublePair DP (dX, dY);

		return (*CTFMetricParamFunc)(&DP, ppData);
	}
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTransX::GetInvTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (CTFNativeParamFunc) {
	// DLL Funktion rufen
	DoublePair DP (dX, dY);

		return (*CTFNativeParamFunc)(&DP, ppData);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;
}

bool CoordTransX::TransformEx (double *pX, double *pY, LPVOID pData)
{
	if (CTFTransExFunc) {
	DoublePair DP (*pX, *pY);

		if ((*CTFTransExFunc)(&DP, 1, pData)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		}
	} 

return Transform (pX, pY);
}

bool CoordTransX::TransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (CTFTransExFunc)		// erweiterte Funktion rufen
		return (*CTFTransExFunc)(pPoints, iNum, pData);

return Transform (pPoints, iNum);
}

bool CoordTransX::InvTransformEx (double *pX, double *pY, LPVOID pData)
{
	if (CTFInvTransExFunc) {
	// DLL-Funktion rufen
	DoublePair DP (*pX, *pY);

		if ((*CTFInvTransExFunc)(&DP, 1, pData)) {
			*pX = DP.X();
			*pY = DP.Y();	
			return true;
		}
	}

return InvTransform (pX, pY);
}

bool CoordTransX::InvTransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (CTFInvTransExFunc)	// DLL-Funktion rufen
		return (*CTFInvTransExFunc)(pPoints, iNum, pData);

return InvTransform (pPoints, iNum);
}

#endif // WIN32

// Memberfunktionen fuer die Schnittstelle zu den Koordinaten-
// Transformations-DLL's
// File: CTF.CXX

#include "trias02p.hxx"

#include "hdrentry.hxx"
#include "trias02.h"

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

_TRIAS02_ENTRY ErrCode EvalKoeffs (double *, double *, double *, double *);

// Konstruktor/Destruktor -----------------------------------------------------
EXPORT02 CoordTrans :: CoordTrans (pWindow pW, GeoDB &DB)
	    : _DB (DB)
{
	_pDLL = NULL;	// für alle Fälle NULL setzen
	m_fIsDefault = false;

HeaderEntry HE (_DB, g_cbCoordTransform);

	if (HE.Status() != HE_INVALID) {
	char CTName[_MAX_FNAME];

		strcpy (CTName, HE.EntryText());
		strcat (CTName, g_cbCTFExt);
		_pDLL = new DLLBind (CTName);
		if (_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
	} 
	if (_pDLL == NULL || _pDLL -> hLib() == 0) {	// Objekt ungültig
		DELETE (_pDLL);
		_pDLL = new DLLBind (g_cbDefaultCTF);
		if (_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
		m_fIsDefault = true;
	}

	Refresh (true);
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die CTF neu geladen werden muß

bool CoordTrans::Reload (bool fRefresh)
{
HeaderEntry HE (_DB, g_cbCoordTransform);

	if (HE.Status() != HE_INVALID) {
		if (strcmp (_pDLL -> GetName(), HE.EntryText()))
			return true;	// neue CTF laden
	} else if (!m_fIsDefault) {
		m_fIsDefault = true;
		return true;		// war nicht DEFAULT und ist jetzt nichts mehr
	}

	if (fRefresh) Refresh();

return false;	// muß nicht meu geladen werden
}

bool CoordTrans::Refresh (bool fForce)
{
// SkalierungsKoeffizienten lesen
double dK11, dK12, dK21, dK22, dOX, dOY;

	{
	// Koeffizienten aus DB-Header lesen
		dK11 = HeaderEntry (_DB, g_cbKoeff11).EntryDouble(1.0);
		dK12 = HeaderEntry (_DB, g_cbKoeff12).EntryDouble(0.0);
		dK21 = HeaderEntry (_DB, g_cbKoeff21).EntryDouble(0.0);
		dK22 = HeaderEntry (_DB, g_cbKoeff22).EntryDouble(1.0);
		dOX = HeaderEntry (_DB, g_cbOffsetX).EntryDouble(0.0);
		dOY = HeaderEntry (_DB, g_cbOffsetY).EntryDouble(0.0);
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

// Funktionen dieser DLL binden
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

// DLL informieren, daß sie aktiviert ist, FensterHandle mitteilen
	CoordTransLoad (__hWndM);

// überprüfen, ob CTF Config-Mode besitzt
	m_fConfig = (NULL != GetProcAddress (g_cbCoordTransMode));

// überprüfen, ob CTF DistanceExFunktion besitzt
	m_fDistEx = (NULL != GetProcAddress (g_cbCoordTransDistanceEx));

return true;
}

EXPORT02 CoordTrans :: ~CoordTrans (void)
{
// DLL informieren, das jetzt alles vorbei ist
	CoordTransUnLoad();

// DLL freigeben
	DELETE (_pDLL);
}

// Funktionen, die nicht auf die CTF-DLL durchgreifen -------------------------
bool EXPORT02 CoordTrans :: Scale (const double &pX, const double &pY, Punkt &outPt)
{
double tX = pX - m_dOX;
double tY = pY - m_dOY;

	outPt.X() = (KoOrd)(m_dInvK11 * tX + m_dInvK12 * tY);
	outPt.Y() = (KoOrd)(m_dInvK21 * tX + m_dInvK22 * tY);

return true;
}

bool EXPORT02 CoordTrans :: Scale (const double &X, const double &Y, 
			  KoOrd *pX, KoOrd *pY)
{
double tX = X - m_dOX;
double tY = Y - m_dOY;

	*pX = (KoOrd)(m_dInvK11 * tX + m_dInvK12 * tY);
	*pY = (KoOrd)(m_dInvK21 * tX + m_dInvK22 * tY);

return true;
}

bool EXPORT02 CoordTrans :: UnScale (const Punkt &Pt, double *pX, double *pY)
{
	*pX = m_dK11 * (double)((Punkt &)Pt).X() + m_dK12 * (double)((Punkt &)Pt).Y() + m_dOX;
	*pY = m_dK21 * (double)((Punkt &)Pt).X() + m_dK22 * (double)((Punkt &)Pt).Y() + m_dOY;

return true;
}

bool EXPORT02 CoordTrans :: UnScale (const KoOrd &inX, const KoOrd &inY, 
			    double *pX, double *pY)
{
	*pX = m_dK11 * (double)inX + m_dK12 * (double)inY + m_dOX;
	*pY = m_dK21 * (double)inX + m_dK22 * (double)inY + m_dOY;

return true;
}


// Funktionen, die auf die CTF-DLL durchgreifen -------------------------------
double EXPORT02 CoordTrans :: CoordTransAspectRatio (ObjContainer &OC)
{
	if (CTFAspectFunc) {
	// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	double XOut = (m_dK11 * (double)OC.XMin() + m_dK12 * (double)OC.YMax());
	double YOut = (m_dK21 * (double)OC.XMin() + m_dK22 * (double)OC.YMax());
	DoublePair LO (XOut + m_dOX, YOut + m_dOY);

		XOut = (m_dK11 * (double)OC.XMax() + m_dK12 * (double)OC.YMin());
		YOut = (m_dK21 * (double)OC.XMax() + m_dK22 * (double)OC.YMin());

	DoublePair RU (XOut + m_dOX, YOut + m_dOY);

	// DLL-Funktion rufen
		return (*CTFAspectFunc)(&LO, &RU);
	}
	db_error (EC_NODLLFUNCTION, RC_CTFAspect);

return 1.0;
}

double EXPORT02 CoordTrans :: CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2)
{
	if (CTFDistanceFunc) {
	// DLL-Funktion rufen

		return (*CTFDistanceFunc)(pP1, pP2);
	}
	db_error (EC_NODLLFUNCTION, RC_CTFDistance);

return 0.0;
}

bool EXPORT02 CoordTrans :: CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, 
			   double &dX, double &dY)
{
	if (CTFDistExFunc) {
	// DLL-Funktion rufen
	DoublePair D;

		if ((*CTFDistExFunc)(pP1, pP2, &D)) {
			dX = D.X();
			dY = D.Y();
			return true;
		}
	}
	db_error (EC_NODLLFUNCTION, RC_CTFDistance);

return false;
}



bool EXPORT02 CoordTrans :: Transform (double *pX, double *pY)
{
	if (CTFTransFunc) {
	DoublePair DP (*pX, *pY);

		if ((*CTFTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		}
	} else 		  // Fehlermeldung
		db_error (EC_NODLLFUNCTION, RC_CTFTrans);

return false;
}

bool EXPORT02 CoordTrans :: Transform (DoublePair *pPoints, short iNum)
{
	if (CTFTransFunc) // DLL-Funktion rufen
		return (*CTFTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		db_error (EC_NODLLFUNCTION, RC_CTFTrans);

return false;
}

bool EXPORT02 CoordTrans :: InvTransform (double *pX, double *pY)
{
	if (CTFInvTransFunc) {
	// DLL-Funktion rufen
	DoublePair DP (*pX, *pY);

		if ((*CTFInvTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();	
			return true;
		}
	} else 		  // Fehlermeldung
		db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);

return false;
}

bool EXPORT02 CoordTrans :: InvTransform (DoublePair *pPoints, short iNum)
{
	if (CTFInvTransFunc) // DLL-Funktion rufen
		return (*CTFInvTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);

return false;
}

char * EXPORT02 CoordTrans :: CoordTransDescription (char *, short)
{
	return NULL;
}

bool EXPORT02 CoordTrans :: CoordTransMode (pWindow pW)
{
CTFMODEPROC CTFHandlingFunc = (CTFMODEPROC)GetProcAddress (g_cbCoordTransMode);

	if (CTFHandlingFunc) {	// DLL Funktion rufen
	COORDTRANSMODE CTM;

		CTM.dwSize = sizeof(COORDTRANSMODE);
		CTM.hWnd = pW -> Handle (API_WINDOW_HWND);

		return (*CTFHandlingFunc)(&CTM);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return false;
}

bool EXPORT02 CoordTrans :: CoordTransLoad (HWND hWnd)
{
CTFLOADPROC CTFHandlingFunc = (CTFLOADPROC)GetProcAddress (g_cbCoordTransLoad);

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)(hWnd);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return false;
}

bool EXPORT02 CoordTrans :: CoordTransUnLoad (void)
{
CTFUNLOADPROC CTFHandlingFunc = (CTFUNLOADPROC)GetProcAddress (g_cbCoordTransUnLoad);

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)();
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFUnLoad);

return false;
}

char * EXPORT02 CoordTrans :: CoordTransToString (double Value, 
					bool isX,
					char *pBuffer, 
					short iLen)
{
	if (CTFStringFunc) {
	// DLL Funktion rufen

		return (*CTFStringFunc)(Value, isX, pBuffer, iLen);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFToString);

return NULL;
}

double EXPORT02 CoordTrans :: CoordTransToValue (char *pBuffer)
{
	if (CTFValueFunc) {
	// DLL Funktion rufen

		return (*CTFValueFunc)(pBuffer);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFToValue);

return NULL;
}

char * EXPORT02 CoordTrans :: CoordTransToStringEx (double dX, double dY,
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

bool EXPORT02 CoordTrans :: CoordTransToValueEx (const char *pBuffX, const char *pBuffY,
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

bool EXPORT02 CoordTrans :: CoordTransRectangle (const DoublePair *pIn, 
					const DoublePair *pDelta, 
					DoublePair *pOut)
{
	if (CTFRectFunc) {
	// DLL Funktion rufen

		return (*CTFRectFunc)(pIn, pDelta, pOut);
	} else
		db_error (EC_NODLLFUNCTION, RC_CTFRectangle);

return false;
}


// Funktionen, die Koordinaten in metrische Einheiten konvertieren ------------
bool EXPORT02 CoordTrans :: isMetric (void)
{
	if (CTFIsMetricFunc) {
	// DLL Funktion rufen

		return (*CTFIsMetricFunc)();
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFisMetric);

return true;	// metrisch annehmen
}

bool EXPORT02 CoordTrans :: Native (const double &pX, const double &pY, Punkt &outPt)
{
	if (CTFNativeFunc) {
	// DLL Funktion rufen
	DoublePair DP (pX, pY);

		if ((*CTFNativeFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), outPt);
		else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool EXPORT02 CoordTrans :: Native (const double &X, const double &Y, 
			   KoOrd *pX, KoOrd *pY)
{
	if (CTFNativeFunc) {
	// DLL Funktion rufen
	DoublePair DP (X, Y);

		if ((*CTFNativeFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), pX, pY);
		else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool EXPORT02 CoordTrans :: Metric (const Punkt &Pt, double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (Pt, &DP.X(), &DP.Y())) return false;

	if (CTFMetricFunc) {
	// DLL Funktion rufen

		if ((*CTFMetricFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		} else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

bool EXPORT02 CoordTrans :: Metric (const KoOrd &inX, const KoOrd &inY, 
			   double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (inX, inY, &DP.X(), &DP.Y())) return false;

	if (CTFMetricFunc) {
	// DLL Funktion rufen

		if ((*CTFMetricFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return true;
		} else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Funktionen für parametrisierbare Transformationen
bool CoordTrans::GetMetricParam (const Punkt &rPt, LPVOID *ppData)
{
DoublePair DP;

	if (!UnScale (rPt, &DP.X(), &DP.Y())) return false;

	if (CTFMetricParamFunc)	// DLL Funktion rufen
		return (*CTFMetricParamFunc)(&DP, ppData);

	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTrans::GetMetricParam (KoOrd iX, KoOrd iY, LPVOID *ppData)
{
DoublePair DP;

	if (!UnScale (iX, iY, &DP.X(), &DP.Y())) return false;

	if (CTFMetricParamFunc)	// DLL Funktion rufen
		return (*CTFMetricParamFunc)(&DP, ppData);

	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTrans::MetricEx (const Punkt &rPt, double *pX, double *pY, LPVOID pData)
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
	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

bool CoordTrans::MetricEx (KoOrd inX, KoOrd inY, double *pX, double *pY, LPVOID pData)
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
	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;	// Fehler
}

bool CoordTrans::GetNativeParam (const double &rdX, const double &rdY, LPVOID *ppData)
{
	if (CTFNativeParamFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		return (*CTFNativeParamFunc)(&DP, ppData);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;
}

bool CoordTrans::NativeEx (const double &rdX, const double &rdY, Punkt &outPt, LPVOID pData)
{
	if (CTFNativeExFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		if ((*CTFNativeExFunc)(&DP, 1, pData)) 
			return Scale (DP.X(), DP.Y(), outPt);
		else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool CoordTrans::NativeEx (const double &rdX, const double &rdY, KoOrd *piX, KoOrd *piY, LPVOID pData)
{
	if (CTFNativeExFunc) {
	// DLL Funktion rufen
	DoublePair DP (rdX, rdY);

		if ((*CTFNativeExFunc)(&DP, 1, pData)) 
			return Scale (DP.X(), DP.Y(), piX, piY);
		else
			return false;
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;	// Fehler
}

bool CoordTrans::GetTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (CTFMetricParamFunc)	{
	// DLL Funktion rufen
	DoublePair DP (dX, dY);

		return (*CTFMetricParamFunc)(&DP, ppData);
	}
	db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return false;
}

bool CoordTrans::GetInvTransformParam (double dX, double dY, LPVOID *ppData)
{
	if (CTFNativeParamFunc) {
	// DLL Funktion rufen
	DoublePair DP (dX, dY);

		return (*CTFNativeParamFunc)(&DP, ppData);
	} 
	db_error (EC_NODLLFUNCTION, RC_CTFNative);

return false;
}

bool CoordTrans::TransformEx (double *pX, double *pY, LPVOID pData)
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

bool CoordTrans::TransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (CTFTransExFunc)		// erweiterte Funktion rufen
		return (*CTFTransExFunc)(pPoints, iNum, pData);

return Transform (pPoints, iNum);
}

bool CoordTrans::InvTransformEx (double *pX, double *pY, LPVOID pData)
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

bool CoordTrans::InvTransformEx (DoublePair *pPoints, int iNum, LPVOID pData)
{
	if (CTFInvTransExFunc)	// DLL-Funktion rufen
		return (*CTFInvTransExFunc)(pPoints, iNum, pData);

return InvTransform (pPoints, iNum);
}

#endif // WIN32

// Klasse, welche KoordinatenTransformations-DLL repraesentiert (Extension)
// File: CTFX.HXX

#if !defined(_CTFX_HXX)
#define _CTFX_HXX

#include <ctf.h>

class CoordTransX {
private:
// gebundene Funktionen aus der aktuellen CTF
	CTFTRANSPROC CTFTransFunc;
	CTFTRANSPROC CTFInvTransFunc;
	CTFASPECTPROC CTFAspectFunc;
	CTFDISTANCEPROC CTFDistanceFunc;
	CTFDISTEXPROC CTFDistExFunc;
	CTFTOSTRINGPROC CTFStringFunc;
	CTFTOVALUEPROC CTFValueFunc;
	CTFTOSTRINGEXPROC CTFStringExFunc;
	CTFTOVALUEEXPROC CTFValueExFunc;
	CTFRECTPROC CTFRectFunc;
	CTFISMETRICPROC CTFIsMetricFunc;
	CTFTRANSPROC CTFNativeFunc;
	CTFTRANSPROC CTFMetricFunc;
#if !defined(WIN16)
	CTFTRANSPARAMPROC CTFMetricParamFunc;
	CTFTRANSPARAMPROC CTFNativeParamFunc;
	CTFTRANSPROCEX CTFMetricExFunc;
	CTFTRANSPROCEX CTFNativeExFunc;
	CTFTRANSPROCEX CTFTransExFunc;
	CTFTRANSPROCEX CTFInvTransExFunc;
#endif // WIN16

	CDllBindX *_pDLL;

	double m_dK11, m_dK12, m_dK21, m_dK22, m_dOX, m_dOY;
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;

	bool m_fConfig;
	bool m_fDistEx;
	bool m_fIsDefault;

protected:
	Bool CoordTransLoad (HWND);
	Bool CoordTransUnLoad (void);

public:
		CoordTransX (void);
		~CoordTransX (void);

	BOOL Transform (double *, double *);
	BOOL InvTransform (double *, double *);
	BOOL Transform (DoublePair *, short);
	BOOL InvTransform (DoublePair *, short);
	double CoordTransAspectRatio (ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	BOOL CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, short);
#if defined(__CV__)
	Bool CoordTransMode (pWindow);
#else
	bool CoordTransMode (HWND);
#endif

	BOOL Scale (const double &, const double &, Punkt &);
	BOOL Scale (const double &, const double &, KoOrd *, KoOrd *);
	BOOL UnScale (const Punkt &, double *, double *);
	BOOL UnScale (const KoOrd &, const KoOrd &, double *, double *);

	BOOL isMetric (void);		// ist Koordinatensystem metrisch ?

	BOOL Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	BOOL Metric (const KoOrd &, const KoOrd &, double *, double *);
	BOOL Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	BOOL Native (const double &, const double &, KoOrd *, KoOrd *);

	char *CoordTransToString (double Value, BOOL isX, char *pBuff, short iLen);
	double CoordTransToValue (char *pBuffer);

	FARPROC GetProcAddress (const char *pName) 
		{ return _pDLL ? _pDLL -> GetProcAddress (pName) : 0; }

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dValueX, double dValueY, bool isX, char *pBuff, short iLen);
	bool CoordTransToValueEx (const char *pBuffer, const char *pBuffY, double &dX, double &dY);
	bool CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, double &dX, double &dY);

#if !defined(WIN16)
// Funktionen für parametrisierbare Transformationen (#HK960824)
// der durch die folgenden Funktionen gelieferte Wert pData muß nach
// Gebrauch mit CoTaskMemFree(pData) wieder freigegeben werden !
	bool GetMetricParam (const Punkt &, LPVOID *);
	bool GetMetricParam (KoOrd, KoOrd, LPVOID *);
	bool GetNativeParam (const double &, const double &, LPVOID *);
	bool GetTransformParam (double, double, LPVOID *);
	bool GetInvTransformParam (double, double, LPVOID *);

	bool MetricEx (const Punkt &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, Punkt &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID);

	bool TransformEx (double *, double *, LPVOID);
	bool TransformEx (DoublePair *, int, LPVOID);
	bool InvTransformEx (double *, double *, LPVOID);
	bool InvTransformEx (DoublePair *, int, LPVOID);
#endif // WIN16

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fConfig; }
};

#if !defined(IDS_CTFTOSTRINGEX)		// neue ResourceKonstanten
#define IDS_CTFTOSTRINGEX       1408
#define IDS_CTFTOVALUEEX        1409
#endif

#endif	// _CTFX_HXX

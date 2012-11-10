// Klasse, welche KoordinatenTransformations-DLL repraesentiert (Extension)
// File: CTFXMFC.NOCOM.H

#if !defined(_CTFXMFC_NOCOM_H)
#define _CTFXMFC_NOCOM_H

#include <ctf.h>
#include <dllbindx.hxx>
#include <objcontx.hxx>

#if defined(__CV__)
#define CCoordTransX CoordTransX
#endif // __CV__

class CCoordTransX {
private:
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
#if defined(WIN32)
	CTFTRANSPARAMPROC CTFMetricParamFunc;
	CTFTRANSPARAMPROC CTFNativeParamFunc;
	CTFTRANSPROCEX CTFMetricExFunc;
	CTFTRANSPROCEX CTFNativeExFunc;
	CTFTRANSPROCEX CTFTransExFunc;
	CTFTRANSPROCEX CTFInvTransExFunc;
#endif // WIN32

	CDllBindX *_pDLL;

	double m_dK11, m_dK12, m_dK21, m_dK22, m_dOX, m_dOY;
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;

	bool m_fConfig;
	bool m_fDistEx;
	bool m_fIsDefault;

protected:
	bool CoordTransLoad (HWND);
	bool CoordTransUnLoad (void);

public:
		CCoordTransX (void);
		~CCoordTransX (void);

	bool Transform (double *, double *);
	bool InvTransform (double *, double *);
	bool Transform (DoublePair *, short);
	bool InvTransform (DoublePair *, short);
	double CoordTransAspectRatio (ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, short);
#if defined(__CV__)
        Bool CoordTransMode (pWindow);
#else
        bool CoordTransMode (HWND);
#endif

	bool Scale (const double &, const double &, Punkt &);
	bool Scale (const double &, const double &, KoOrd *, KoOrd *);
	bool UnScale (const Punkt &, double *, double *);
	bool UnScale (const KoOrd &, const KoOrd &, double *, double *);

	bool isMetric (void);		// ist Koordinatensystem metrisch ?

	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);

	char *CoordTransToString (double Value, bool isX, char *pBuff, short iLen);
	double CoordTransToValue (char *pBuffer);

	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, short iLen);
	bool CoordTransToValueEx (const char *pBuffX, const char *pBuffY, double &dX, double &dY);
	bool CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, double &dX, double &dY);

#if defined(WIN32)
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
#endif // WIN32

	FARPROC GetProcAddress (const char *pName) 
		{ return _pDLL ? _pDLL -> GetProcAddress (pName) : 0; }

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fConfig ? true : false; }
};

#endif	// _CTFXMFC_NOCOM_H

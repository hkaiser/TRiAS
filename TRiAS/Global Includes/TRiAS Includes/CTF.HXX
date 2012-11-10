// Klasse, welche KoordinatenTransformations-DLL repraesentiert
// File: CTF.HXX

#if !defined(_CTF_HXX)
#define _CTF_HXX

#include <CSPoint.h>

#include <ctf.h>
#include <ictf.h>

class GeoDB;

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// gemeinsame Basisklasse für Koordinatentransformationen
class _TRIAS02_ENTRY CoordTrans
{
public:
	virtual bool Reload (bool fRefresh = false) = 0;
	virtual bool CanConfig (void) = 0;
	virtual bool hasDistEx (void) = 0;
	virtual bool isMetric (void) = 0;

	virtual char *CoordTransDescription (char *, int) = 0;
	virtual bool CoordTransMode (pWindow) = 0;

	virtual bool Transform (double *, double *) = 0;
	virtual bool Transform (DoublePair *, int) = 0;

	virtual bool InvTransform (double *, double *) = 0;
	virtual bool InvTransform (DoublePair *, int) = 0;

	virtual double CoordTransAspectRatio (class ObjContainer &) = 0;
	virtual double CoordTransDistance (const DoublePair *, const DoublePair *) = 0;
	virtual bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut) = 0;

	virtual bool Scale (const double &, const double &, class Punkt &) = 0;
	virtual bool Scale (const double &, const double &, KoOrd *, KoOrd *) = 0;
	virtual bool UnScale (const Punkt &, double *, double *) = 0;
	virtual bool UnScale (const KoOrd &, const KoOrd &, double *, double *) = 0;

	virtual bool Metric (const Punkt &, double *, double *) = 0;
	virtual bool Metric (const KoOrd &, const KoOrd &, double *, double *) = 0;
	virtual bool Native (const double &, const double &, Punkt &) = 0;
	virtual bool Native (const double &, const double &, KoOrd *, KoOrd *) = 0;

	virtual char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen) = 0;
	virtual double CoordTransToValue (char *pBuffer) = 0;
	virtual char *CoordTransToStringEx (double dValueX, double dValueY, bool isX, char *pBuff, int iLen) = 0;
	virtual bool CoordTransToValueEx (const char *pBuffer, const char *pBuffY, double &dX, double &dY) = 0;
	virtual bool CoordTransDistanceEx (const DoublePair *, const DoublePair *, double &dX, double &dY) = 0;

	virtual bool GetMetricParam (const Punkt &, LPVOID *) = 0;
	virtual bool GetMetricParam (KoOrd, KoOrd, LPVOID *) = 0;
	virtual bool GetNativeParam (const double &, const double &, LPVOID *) = 0;
	virtual bool GetTransformParam (double, double, LPVOID *) = 0;
	virtual bool GetInvTransformParam (double, double, LPVOID *) = 0;
	virtual void FreeMetricParam (LPVOID) = 0;
	virtual void FreeNativeParam (LPVOID) = 0;
	virtual void FreeTransformParam (LPVOID) = 0;
	virtual void FreeInvTransformParam (LPVOID) = 0;

	virtual bool MetricEx (const Punkt &, double *, double *, LPVOID) = 0;
	virtual bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID) = 0;
	virtual bool NativeEx (const double &, const double &, Punkt &, LPVOID) = 0;
	virtual bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID) = 0;
	virtual bool TransformEx (double *, double *, LPVOID) = 0;
	virtual bool TransformEx (DoublePair *, int, LPVOID) = 0;
	virtual bool InvTransformEx (double *, double *, LPVOID) = 0;
	virtual bool InvTransformEx (DoublePair *, int, LPVOID) = 0;

	virtual ~CoordTrans() {}

	virtual HRESULT Advise (ICoordTransformEvents *pEventSink) = 0;
	virtual HRESULT UnAdvise (void) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// dynamisch ladbare Koordinatentransformation
class _TRIAS02_ENTRY CCoordTransServiceObsolete :
	public CoordTrans
{
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
	CTFTRANSPARAMPROC CTFMetricParamFunc;
	CTFTRANSPARAMPROC CTFNativeParamFunc;
	CTFTRANSPROCEX CTFMetricExFunc;
	CTFTRANSPROCEX CTFNativeExFunc;
	CTFTRANSPROCEX CTFTransExFunc;
	CTFTRANSPROCEX CTFInvTransExFunc;

	class DLLBind *_pDLL;

	double m_dK11, m_dK12, m_dK21, m_dK22, m_dOX, m_dOY;
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;

	GeoDB &_DB;

	bool m_fConfig;
	bool m_fDistEx;
	bool m_fIsDefault;

protected:
	bool CoordTransLoad (HWND);
	bool CoordTransUnLoad (void);

public:
		CCoordTransServiceObsolete (pWindow, GeoDB &);
		~CCoordTransServiceObsolete (void);

	bool Transform (double *, double *);
	bool InvTransform (double *, double *);
	bool Transform (DoublePair *, int);
	bool InvTransform (DoublePair *, int);
	double CoordTransAspectRatio (class ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, int);
	bool CoordTransMode (pWindow);

	bool Scale (const double &, const double &, class Punkt &);
	bool Scale (const double &, const double &, KoOrd *, KoOrd *);
	bool UnScale (const Punkt &, double *, double *);
	bool UnScale (const KoOrd &, const KoOrd &, double *, double *);

	bool isMetric (void);		// ist Koordinatensystem metrisch ?

	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dValueX, double dValueY, bool isX, char *pBuff, int iLen);
	bool CoordTransToValueEx (const char *pBuffer, const char *pBuffY, double &dX, double &dY);

	bool CoordTransDistanceEx (const DoublePair *, const DoublePair *, double &dX, double &dY);

// Funktionen für parametrisierbare Transformationen (#HK960824)
// der durch die folgenden Funktionen gelieferte Wert pData muß nach
// Gebrauch mit CoTaskMemFree(pData) wieder freigegeben werden !
	bool GetMetricParam (const Punkt &, LPVOID *);
	bool GetMetricParam (KoOrd, KoOrd, LPVOID *);
	bool GetNativeParam (const double &, const double &, LPVOID *);
	bool GetTransformParam (double, double, LPVOID *);
	bool GetInvTransformParam (double, double, LPVOID *);
	void FreeMetricParam (LPVOID);
	void FreeNativeParam (LPVOID);
	void FreeTransformParam (LPVOID);
	void FreeInvTransformParam (LPVOID);

	bool MetricEx (const Punkt &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, Punkt &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID);

	bool TransformEx (double *, double *, LPVOID);
	bool TransformEx (DoublePair *, int, LPVOID);
	bool InvTransformEx (double *, double *, LPVOID);
	bool InvTransformEx (DoublePair *, int, LPVOID);

	FARPROC GetProcAddress (const char *pName) 
		{ return _pDLL ? _pDLL -> GetProcAddress (pName) : 0; }

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fConfig; }
	bool hasDistEx (void) { return m_fDistEx; }

	HRESULT Advise (ICoordTransformEvents *pEventSink);
	HRESULT UnAdvise (void);
};
#endif // _FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation, ladbar über CLSID ...

DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(CoordTransform);

class _TRIAS02_ENTRY CCoordTransService 
#if defined(_FORCE_LEGACY_CODE)
	: public CoordTrans
#endif // _FORCE_LEGACY_CODE
{
private:
	WCoordTransform m_CTF;
	WTRiASPropertyBase m_PropBase;
	string m_strCTF;			// OldName der aktuellen CTF

	double m_dK11, m_dK12, m_dK21, m_dK22, m_dOX, m_dOY;
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;

	bool m_fIsDefault;
	bool m_fIsInitialized;
	bool m_fCanConfig;

	DWORD m_dwCookie;

#if defined(_CTF_USE_POINTMEMBER)
	CCSPoint m_pt;	
#endif // defined(_CTF_USE_POINTMEMBER)

protected:
	HRESULT FindCTF (void);
	bool Refresh (bool fForce = false);

public:
		CCoordTransService (void);
		~CCoordTransService (void);

	HRESULT InitCTFService (ITRiASPropertyBase *pIPropBase);

	bool Reload (bool fRefresh = false);
	bool CanConfig (void) { return m_fCanConfig; }
	bool hasDistEx (void) { return true; }
	bool isMetric (void);

	char *CoordTransDescription (char *, int);
	bool CoordTransMode (pWindow);

	bool Transform (double *, double *);
	bool Transform (DoublePair *, int);

	bool InvTransform (double *, double *);
	bool InvTransform (DoublePair *, int);

	double CoordTransAspectRatio (class ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);

	bool Scale (const double &, const double &, class Punkt &);
	bool Scale (const double &, const double &, KoOrd *, KoOrd *);
	bool UnScale (const Punkt &, double *, double *);
	bool UnScale (const KoOrd &, const KoOrd &, double *, double *);

#if _TRiAS_VER < 0x0400
	bool Metric (const Punkt &, double *, double *);
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);
	bool Native (const double &, const double &, KoOrd *, KoOrd *);
#else
	bool Metric (const DoublePair &, double *, double *);
	bool Metric (const double &, const double &, double *, double *);
	bool Native (const double &, const double &, DoublePair &);
	bool Native (const double &, const double &, double *, double *);
#endif // _TRiAS_VER < 0x0400

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);
	char *CoordTransToStringEx (double dValueX, double dValueY, bool isX, char *pBuff, int iLen);
	bool CoordTransToValueEx (const char *pBuffer, const char *pBuffY, double &dX, double &dY);
	bool CoordTransDistanceEx (const DoublePair *, const DoublePair *, double &dX, double &dY);

	bool GetMetricParam (const Punkt &, LPVOID *);
	bool GetMetricParam (KoOrd, KoOrd, LPVOID *);
	bool GetNativeParam (const double &, const double &, LPVOID *);
	bool GetTransformParam (double, double, LPVOID *);
	bool GetInvTransformParam (double, double, LPVOID *);
	void FreeMetricParam (LPVOID);
	void FreeNativeParam (LPVOID);
	void FreeTransformParam (LPVOID);
	void FreeInvTransformParam (LPVOID);

#if _TRiAS_VER < 0x0400
	bool MetricEx (const Punkt &, double *, double *, LPVOID);
	bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, Punkt &, LPVOID);
	bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID);
#else
	bool MetricEx (const DoublePair &, double *, double *, LPVOID);
	bool MetricEx (double, double, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, DoublePair &, LPVOID);
	bool NativeEx (const double &, const double &, double *, double *, LPVOID);
#endif // _TRiAS_VER < 0x0400

	bool TransformEx (double *, double *, LPVOID pParam, IUnknown *pICS = NULL);
	bool TransformEx (DoublePair *, int, LPVOID pParam, IUnknown *pICS = NULL);
	bool InvTransformEx (double *, double *, LPVOID pParam, IUnknown *pICS = NULL);
	bool InvTransformEx (DoublePair *, int, LPVOID pParam, IUnknown *pICS = NULL);

// inlines
	inline KoOrd ScaleX (const double dX, const double dY) const 
	{
		return (KoOrd)(m_dInvK11 * (dX - m_dOX) + m_dInvK12 * (dY - m_dOY));
	}
	inline KoOrd ScaleY (const double dX, const double dY) const 
	{
		return (KoOrd)(m_dInvK21 * (dX - m_dOX) + m_dInvK22 * (dY - m_dOY));
	}
	inline double UnScaleX (const KoOrd lX, const KoOrd lY) const 
	{
		return m_dK11 * (double)lX + m_dK12 * (double)lY + m_dOX;
	}
	inline double UnScaleY (const KoOrd lX, const KoOrd lY) const 
	{
		return m_dK21 * (double)lX + m_dK22 * (double)lY + m_dOY;
	}

	HRESULT Advise (ICoordTransformEvents *pEventSink);
	HRESULT UnAdvise (void);

	HRESULT GetCoordTransformPipe(IDispatch **ppICS);
};

#if !defined(_FORCE_LEGACY_CODE)
typedef CCoordTransService CoordTrans;
#endif // !defined(_FORCE_LEGACY_CODE)

#endif	// _CTF_HXX

// Klasse, welche KoordinatenTransformations-DLL repraesentiert (Extension)
// File: CTFXMFC.H

#if !defined(_CTFXMFC_H)
#define _CTFXMFC_H

#if _TRiAS_VER < 0x0300
#include <ctfmfc.nocom.h>
#else

#include <objcontx.hxx>
#include <ctf.h>

#include <dllbindx.hxx>
#include <DblPair.hxx>

#if defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// gemeinsame Basisklasse für Koordinatentransformationen
class CoordTransXBase 
{
public:
		CoordTransXBase (void) {}

	virtual bool Reload (bool fRefresh = false) = 0;
	virtual bool CanConfig (void) = 0;
	virtual bool hasDistEx (void) = 0;
	virtual bool isMetric (void) = 0;		// ist Koordinatensystem metrisch ?

	virtual char *CoordTransDescription (char *, int) = 0;
#if defined(__CV__)
	virtual bool CoordTransMode (pWindow) = 0;
#else
	virtual bool CoordTransMode (HWND) = 0;
#endif

	virtual bool Transform (double *, double *) = 0;
	virtual bool Transform (DoublePair *, int) = 0;
	virtual bool InvTransform (double *, double *) = 0;
	virtual bool InvTransform (DoublePair *, int) = 0;

	virtual double CoordTransAspectRatio (ObjContainer &) = 0;
	virtual double CoordTransDistance (const DoublePair *, const DoublePair *) = 0;
	virtual bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut) = 0;

	virtual bool Scale (const double &, const double &, Punkt &) = 0;
	virtual bool Scale (const double &, const double &, KoOrd *, KoOrd *) = 0;
	virtual bool UnScale (const Punkt &, double *, double *) = 0;
	virtual bool UnScale (const KoOrd &, const KoOrd &, double *, double *) = 0;

	virtual bool Metric (const Punkt &, double *, double *) = 0;	// metrische Koordinaten erzeugen
	virtual bool Metric (const KoOrd &, const KoOrd &, double *, double *) = 0;
	virtual bool Native (const double &, const double &, Punkt &) = 0;	// aus metrischen Koordinaten konvertieren
	virtual bool Native (const double &, const double &, KoOrd *, KoOrd *) = 0;

	virtual char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen) = 0;
	virtual double CoordTransToValue (char *pBuffer) = 0;

// neue Konvertierungen (#HK950822)
	virtual char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, int iLen) = 0;
	virtual bool CoordTransToValueEx (const char *pBuffX, const char *pBuffY, double &dX, double &dY) = 0;
	virtual bool CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, double &dX, double &dY) = 0;

#if !defined(WIN16)
// Funktionen für parametrisierbare Transformationen (#HK960824)
// der durch die folgenden Funktionen gelieferte Wert pData muß nach
// Gebrauch mit CoTaskMemFree(pData) wieder freigegeben werden !
	virtual bool GetMetricParam (const Punkt &, LPVOID *) = 0;
	virtual bool GetMetricParam (KoOrd, KoOrd, LPVOID *) = 0;
	virtual bool GetNativeParam (const double &, const double &, LPVOID *) = 0;
	virtual bool GetTransformParam (double, double, LPVOID *) = 0;
	virtual bool GetInvTransformParam (double, double, LPVOID *) = 0;

// jetzt den erhaltenen Pointer nicht mehr mit CoTaskMemFree freigeben, 
// sondern an die folgenden Funktionen übergeben (#HK980305)
	virtual void FreeMetricParam (LPVOID) = 0;
	virtual void FreeNativeParam (LPVOID) = 0;
	virtual void FreeTransformParam (LPVOID) = 0;
	virtual void FreeInvTransformParam (LPVOID) = 0;

	virtual bool MetricEx (const Punkt &, double *, double *, LPVOID) = 0;		// metrische Koordinaten erzeugen
	virtual bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID) = 0;
	virtual bool NativeEx (const double &, const double &, Punkt &, LPVOID) = 0;	// aus metrischen Koordinaten konvertieren
	virtual bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID) = 0;

	virtual bool TransformEx (double *, double *, LPVOID) = 0;
	virtual bool TransformEx (DoublePair *, int, LPVOID) = 0;
	virtual bool InvTransformEx (double *, double *, LPVOID) = 0;
	virtual bool InvTransformEx (DoublePair *, int, LPVOID) = 0;
#endif // !WIN16

	virtual ~CoordTransXBase (void) {}
	virtual bool Refresh (bool fForce = false) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// dynamisch ladbare Koordinatentransformation
class CCoordTransServiceObsoleteX :
	public CoordTransXBase
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
#if !defined(WIN16)
	CTFTRANSPARAMPROC CTFMetricParamFunc;
	CTFTRANSPARAMPROC CTFNativeParamFunc;
	CTFTRANSPROCEX CTFMetricExFunc;
	CTFTRANSPROCEX CTFNativeExFunc;
	CTFTRANSPROCEX CTFTransExFunc;
	CTFTRANSPROCEX CTFInvTransExFunc;
#endif // !WIN16

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
		CCoordTransServiceObsoleteX (void);
		~CCoordTransServiceObsoleteX (void);

	FARPROC GetProcAddress (const char *pName) 
		{ return _pDLL ? _pDLL -> GetProcAddress (pName) : 0; }

	bool Transform (double *, double *);
	bool InvTransform (double *, double *);
	bool Transform (DoublePair *, int);
	bool InvTransform (DoublePair *, int);
	double CoordTransAspectRatio (ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, int);
#if defined(__CV__)
	bool CoordTransMode (pWindow);
#else
	bool CoordTransMode (HWND);
#endif

	bool Scale (const double &, const double &, Punkt &);
	bool Scale (const double &, const double &, KoOrd *, KoOrd *);
	bool UnScale (const Punkt &, double *, double *);
	bool UnScale (const KoOrd &, const KoOrd &, double *, double *);

	bool isMetric (void);		// ist Koordinatensystem metrisch ?

#if _TRiAS_VER < 0x0400
	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);
#else
	bool Metric (const Punkt &pt, double *pdX, double *pdY)
	{
		return Metric (DoublePair(pt.X(), pt.Y()), pdX, pdY);
	}
	bool Metric (const DoublePair &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const double &, const double &, double *, double *);
	bool Native (const double &, const double &, DoublePair &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, double *, double *);
#endif // _TRiAS_VER < 0x0400

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, int iLen);
	bool CoordTransToValueEx (const char *pBuffX, const char *pBuffY, double &dX, double &dY);
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
	void FreeMetricParam (LPVOID);
	void FreeNativeParam (LPVOID);
	void FreeTransformParam (LPVOID);
	void FreeInvTransformParam (LPVOID);

#if _TRiAS_VER < 0x0400
	bool MetricEx (const Punkt &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, Punkt &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID);
#else
	bool MetricEx (const Punkt &pt, double *pdX, double *pdY, LPVOID pData)
	{
		return MetricEx (DoublePair(pt.X(), pt.Y()), pdX, pdY, pData);
	}
	bool MetricEx (const DoublePair &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (double, double, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, DoublePair &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, double *, double *, LPVOID);
#endif // _TRiAS_VER < 0x0400

	bool TransformEx (double *, double *, LPVOID);
	bool TransformEx (DoublePair *, int, LPVOID);
	bool InvTransformEx (double *, double *, LPVOID);
	bool InvTransformEx (DoublePair *, int, LPVOID);
#endif // !WIN16

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fConfig ? true : false; }
	bool hasDistEx (void) { return m_fDistEx ? true : false; }
};

#endif // _FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation, ladbar über CLSID ...
#include <ictf.h>
#include <TRiASDB.h>
#include <geo_inl.hxx>

DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(CoordTransform);

class Punkt;
class ObjContainer;

// ABC0C9B2-C71D-4EF6-B8EC-2BB2B29A2B34
EXTERN_C const GUID __declspec(selectany) CLSID_ConnectedCTF = 
	{ 0xABC0C9B2, 0xC71D, 0x4EF6, 0xB8, 0xEC, 0x2B, 0xB2, 0xB2, 0x9A, 0x2B, 0x34 };

class CCoordTransServiceX 
#if defined(_FORCE_LEGACY_CODE)
	: public CoordTransXBase 
#endif // _USE_LEGACY_CODE
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

protected:
	HRESULT InitCTFService (ITRiASPropertyBase *pIProps);

public:
		CCoordTransServiceX (void);
		~CCoordTransServiceX (void);

	bool Transform (double *, double *);
	bool InvTransform (double *, double *);
	bool Transform (DoublePair *, int);
	bool InvTransform (DoublePair *, int);
	double CoordTransAspectRatio (ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	bool CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, int);
#if defined(__CV__)
	bool CoordTransMode (pWindow);
#else
	bool CoordTransMode (HWND);
#endif

	bool Scale (const double &, const double &, Punkt &);
	bool Scale (const double &, const double &, KoOrd *, KoOrd *);
	bool UnScale (const Punkt &, double *, double *);
	bool UnScale (const KoOrd &, const KoOrd &, double *, double *);

	bool isMetric (void);		// ist Koordinatensystem metrisch ?

#if _TRiAS_VER < 0x0400
	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);
#else
	bool Metric (const Punkt &pt, double *pdX, double *pdY)
	{
		return Metric (DoublePair(pt.GetX(), pt.GetY()), pdX, pdY);
	}
	bool Metric (const DoublePair &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const double &, const double &, double *, double *);
	bool Native (const double &rdX, const double &rdY, Punkt &rpt)
	{
	DoublePair dp;
	bool fResult = Native (rdX, rdY, dp);

		if (fResult) {
			rpt.SetX((KoOrd)dp.X());
			rpt.SetY((KoOrd)dp.Y());
		}
		return fResult;
	}
	bool Native (const double &, const double &, DoublePair &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, double *, double *);
#endif // _TRiAS_VER < 0x0400

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, int iLen);
	bool CoordTransToValueEx (const char *pBuffX, const char *pBuffY, double &dX, double &dY);
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
	void FreeMetricParam (LPVOID);
	void FreeNativeParam (LPVOID);
	void FreeTransformParam (LPVOID);
	void FreeInvTransformParam (LPVOID);

#if _TRiAS_VER < 0x0400
	bool MetricEx (const Punkt &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (KoOrd, KoOrd, double *, double *, LPVOID);
	bool NativeEx (const double &, const double &, Punkt &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, KoOrd *, KoOrd *, LPVOID);
#else
	bool MetricEx (const Punkt &pt, double *pdX, double *pdY, LPVOID pData)
	{
		return MetricEx (DoublePair(pt.GetX(), pt.GetY()), pdX, pdY, pData);
	}
	bool MetricEx (const DoublePair &, double *, double *, LPVOID);		// metrische Koordinaten erzeugen
	bool MetricEx (double, double, double *, double *, LPVOID);
	bool NativeEx (const double &rdX, const double &rdY, Punkt &rpt, LPVOID pData)
	{
	DoublePair dp;
	bool fResult = NativeEx (rdX, rdY, dp, pData);

		if (fResult) {
			rpt.SetX((KoOrd)dp.X());
			rpt.SetY((KoOrd)dp.Y());
		}
		return fResult;
	}
	bool NativeEx (const double &, const double &, DoublePair &, LPVOID);	// aus metrischen Koordinaten konvertieren
	bool NativeEx (const double &, const double &, double *, double *, LPVOID);
#endif // _TRiAS_VER < 0x0400

	bool TransformEx (double *, double *, LPVOID);
	bool TransformEx (DoublePair *, int, LPVOID);
	bool InvTransformEx (double *, double *, LPVOID);
	bool InvTransformEx (DoublePair *, int, LPVOID);
#endif // !WIN16

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fCanConfig ? true : false; }
	bool hasDistEx (void) { return true; }

	bool operator!() { return !m_fIsInitialized; }		// InitStatus abfragen

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

// OutputCS abfragen
	HRESULT GetOutputCS(IDispatch **ppICS);
};

///////////////////////////////////////////////////////////////////////////////
// dafür sorgen das der alte Code mit der neuen Klasse arbeitet
#if !defined(__CV__)
//typedef CCoordTransServiceX CCoordTransX;
#define CCoordTransX CCoordTransServiceX 
#else
#define CoordTransX CCoordTransServiceX 
#endif // !__CV__

#endif // _TRiAS_VER < 0x0300

#endif	// _CTFXMFC_H

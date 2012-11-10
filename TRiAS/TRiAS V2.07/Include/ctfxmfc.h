// Klasse, welche KoordinatenTransformations-DLL repraesentiert (Extension)
// File: CTFXMFC.H

#if !defined(_CTFXMFC_H)
#define _CTFXMFC_H

#if _MSC_VER < 1100
#include <ctfxmfc.nocom.h>
#else

#include <ctf.h>

#include <dllbindx.hxx>
#if !defined(__CV__)
#include <objcontx.hxx>
#endif // !__CV__

#if defined(_USE_LEGACY_CODE)

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

#if defined(WIN32)
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
#endif // WIN32

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

	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, int iLen);
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
#endif // WIN32

	bool Reload (bool fRefresh = false);
	bool Refresh (bool fForce = false);

	bool CanConfig (void) { return m_fConfig ? true : false; }
	bool hasDistEx (void) { return m_fDistEx ? true : false; }
};

#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation, ladbar über CLSID ...
#include <ictf.h>
#include <TRiASDB.h>

DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(CoordTransform);

class CCoordTransServiceX 
#if defined(_USE_LEGACY_CODE)
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

	bool Metric (const Punkt &, double *, double *);	// metrische Koordinaten erzeugen
	bool Metric (const KoOrd &, const KoOrd &, double *, double *);
	bool Native (const double &, const double &, Punkt &);	// aus metrischen Koordinaten konvertieren
	bool Native (const double &, const double &, KoOrd *, KoOrd *);

	char *CoordTransToString (double Value, bool isX, char *pBuff, int iLen);
	double CoordTransToValue (char *pBuffer);

// neue Konvertierungen (#HK950822)
	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, int iLen);
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
#endif // WIN32

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
};

///////////////////////////////////////////////////////////////////////////////
// dafür sorgen das der alte Code mit der neuen Klasse arbeitet
#if !defined(__CV__)
typedef CCoordTransServiceX CCoordTransX;
#else
typedef CCoordTransServiceX CoordTransX;
#endif // !__CV__

#endif // _MSC_VER < 1100

#endif	// _CTFXMFC_H

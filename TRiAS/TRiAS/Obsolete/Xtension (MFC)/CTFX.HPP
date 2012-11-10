// Klasse, welche KoordinatenTransformations-DLL repraesentiert (Extension)
// File: CTFX.HXX

#if !defined(_CTFX_HXX)
#define _CTFX_HXX

#include <ctf.h>

class CoordTransX {
private:
	CTFTRANSPROC CTFTransFunc;
	CTFTRANSPROC CTFInvTransFunc;
	DLLBind *_pDLL;

	double K11, K12, K21, K22, OX, OY;
	double iK11, iK12, iK21, iK22;

protected:
	Bool CoordTransLoad (HWND);
	Bool CoordTransUnLoad (void);

public:
		CoordTransX (void);
		~CoordTransX (void);

	void Transform (double *, double *);
	void InvTransform (double *, double *);
	void Transform (DoublePair *, short);
	void InvTransform (DoublePair *, short);
	double CoordTransAspectRatio (ObjContainer &);
	double CoordTransDistance (const DoublePair *, const DoublePair *);
	void CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
	char *CoordTransDescription (char *, short);
	Bool CoordTransMode (pWindow);

	void Scale (const double &, const double &, Punkt &);
	void Scale (const double &, const double &, KoOrd *, KoOrd *);
	void UnScale (const Punkt &, double *, double *);
	void UnScale (const KoOrd &, const KoOrd &, double *, double *);

	char *CoordTransToString (double Value, BOOL isX, char *pBuff, short iLen);
	double CoordTransToValue (char *pBuffer);

	FARPROC GetProcAddress (const char *pName) 
		{ return _pDLL ? _pDLL -> GetProcAddress (pName) : 0; }
};

#endif	// _CTFX_HXX

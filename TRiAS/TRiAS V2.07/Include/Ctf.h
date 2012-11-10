// Deklarationen von Datenstrukturen und Funktionen fuer 
// KoordinatenTransformationen
// File CTF.H

#if !defined(_CTF_H)
#define _CTF_H

#include <pshpack1.h>
#include <ctfm.hxx>		// ManifestKonstanten

// DatentypDeklarationen ------------------------------------------------------
typedef struct tagCOORDTRANSDESC {
	DWORD dwSize;		// Größe der Datenstruktur
	short iLen;		// max. Größe des Puffers
	char *pDesc;		// Puffer
} COORDTRANSDESC;

typedef struct tagCOORDTRANSMODE {
	DWORD dwSize;		// Größe der DatenStruktur
	HWND hWnd;		// Handle des TRIAS(R)-Hauptfensters
} COORDTRANSMODE;

typedef struct tagPUNKT {
	long lpktX;		// X-Wert
	long lpktY;		// y-Wert
} PUNKT;

#include <poppack.h>

// Funktionsdeklarationen -----------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

class DoublePair;

_CTF_ENTRY bool WINAPI CoordTransLoad (HWND);
_CTF_ENTRY bool WINAPI CoordTransUnLoad (void);
_CTF_ENTRY bool WINAPI CoordTransDescription (COORDTRANSDESC *pCTD);
_CTF_ENTRY bool WINAPI CoordTransMode (COORDTRANSMODE *pCTM);
_CTF_ENTRY double WINAPI CoordTransAspectRatio (const DoublePair *pLO, const DoublePair *pRU);
_CTF_ENTRY double WINAPI CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2);
_CTF_ENTRY bool WINAPI CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
_CTF_ENTRY bool WINAPI Transform (DoublePair *pPoints, short iNum);
_CTF_ENTRY bool WINAPI InvTransform (DoublePair *pPoints, short iNum);
_CTF_ENTRY char * WINAPI CoordTransToString (double, bool, char *, short);
_CTF_ENTRY double WINAPI CoordTransToValue (char *);
_CTF_ENTRY bool WINAPI CoordTransIsMetric (void);
_CTF_ENTRY bool WINAPI CoordTransMetric (DoublePair *pIn, short iNum);
_CTF_ENTRY bool WINAPI CoordTransNative (DoublePair *pIn, short iNum);
_CTF_ENTRY bool WINAPI CoordTransToValueEx (DoublePair *pDP, const char *pBuffX, const char *pBuffY);
_CTF_ENTRY char *WINAPI CoordTransToStringEx (char *pBuffer, short iLen, bool isX, const DoublePair *pDP);
_CTF_ENTRY bool WINAPI CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, DoublePair *pDP);

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die Behandlung einer Koordinate nach externen Kriterien ermöglichen
_CTF_ENTRY bool WINAPI CoordTransMetricParam (DoublePair *pIn, LPVOID *ppData);
_CTF_ENTRY bool WINAPI CoordTransMetricEx (DoublePair *pIn, short iNum, LPVOID pData);
_CTF_ENTRY bool WINAPI CoordTransNativeParam (DoublePair *pIn, LPVOID *ppData);
_CTF_ENTRY bool WINAPI CoordTransNativeEx (DoublePair *pIn, short iNum, LPVOID pData);
#endif // WIN32

// FunktionsPointer -----------------------------------------------------------
typedef bool (WINAPI *CTFLOADPROC)(HWND);
typedef bool (WINAPI *CTFUNLOADPROC)(void);
typedef bool (WINAPI *CTFDESCPROC)(COORDTRANSDESC *pCTD);
typedef double (WINAPI *CTFASPECTPROC)(const DoublePair *, const DoublePair *);
typedef double (WINAPI *CTFDISTANCEPROC)(const DoublePair *, const DoublePair *);
typedef bool (WINAPI *CTFRECTPROC)(const DoublePair *, const DoublePair *, DoublePair *);
typedef bool (WINAPI *CTFTRANSPROC)(DoublePair *, short);
typedef char * (WINAPI *CTFTOSTRINGPROC)(double, bool, char *, short);
typedef double (WINAPI *CTFTOVALUEPROC)(char *);
typedef bool (WINAPI *CTFISMETRICPROC)(void);
typedef bool (WINAPI *CTFTOVALUEEXPROC)(DoublePair *, const char *pBuffX, const char *pBuffY);
typedef bool (WINAPI *CTFTOSTRINGEXPROC)(char *, short, bool, const DoublePair *);
typedef bool (WINAPI *CTFMODEPROC)(COORDTRANSMODE *);
typedef bool (WINAPI *CTFDISTEXPROC)(const DoublePair *, const DoublePair *, DoublePair *);

#if defined(WIN32)
typedef bool (WINAPI *CTFTRANSPARAMPROC)(DoublePair *, LPVOID *);
typedef bool (WINAPI *CTFTRANSPROCEX)(DoublePair *, short, LPVOID);
#endif // WIN32

#if defined(__cplusplus)
}
#endif

#endif // _CTF_H



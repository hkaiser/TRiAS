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

_CTF_ENTRY BOOL WINAPI CoordTransLoad (HWND);
_CTF_ENTRY BOOL WINAPI CoordTransUnLoad (void);
_CTF_ENTRY BOOL WINAPI CoordTransDescription (COORDTRANSDESC *pCTD);
_CTF_ENTRY BOOL WINAPI CoordTransMode (COORDTRANSMODE *pCTM);
_CTF_ENTRY double WINAPI CoordTransAspectRatio (const DoublePair *pLO, const DoublePair *pRU);
_CTF_ENTRY double WINAPI CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2);
_CTF_ENTRY BOOL WINAPI CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut);
_CTF_ENTRY BOOL WINAPI Transform (DoublePair *pPoints, short iNum);
_CTF_ENTRY BOOL WINAPI InvTransform (DoublePair *pPoints, short iNum);
_CTF_ENTRY char * WINAPI CoordTransToString (double, BOOL, char *, short);
_CTF_ENTRY double WINAPI CoordTransToValue (char *);
_CTF_ENTRY BOOL WINAPI CoordTransIsMetric (void);
_CTF_ENTRY BOOL WINAPI CoordTransMetric (DoublePair *pIn, short iNum);
_CTF_ENTRY BOOL WINAPI CoordTransNative (DoublePair *pIn, short iNum);
_CTF_ENTRY BOOL WINAPI CoordTransToValueEx (DoublePair *pDP, const char *pBuffX, const char *pBuffY);
_CTF_ENTRY char *WINAPI CoordTransToStringEx (char *pBuffer, short iLen, BOOL isX, const DoublePair *pDP);
_CTF_ENTRY BOOL WINAPI CoordTransDistanceEx (const DoublePair *pP1, const DoublePair *pP2, DoublePair *pDP);

#if !defined(WIN16)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die Behandlung einer Koordinate nach externen Kriterien ermöglichen
_CTF_ENTRY BOOL WINAPI CoordTransMetricParam (DoublePair *pIn, LPVOID *ppData);
_CTF_ENTRY BOOL WINAPI CoordTransMetricEx (DoublePair *pIn, short iNum, LPVOID pData);
_CTF_ENTRY BOOL WINAPI CoordTransNativeParam (DoublePair *pIn, LPVOID *ppData);
_CTF_ENTRY BOOL WINAPI CoordTransNativeEx (DoublePair *pIn, short iNum, LPVOID pData);
#endif // WIN16

// FunktionsPointer -----------------------------------------------------------
typedef BOOL (WINAPI *CTFLOADPROC)(HWND);
typedef BOOL (WINAPI *CTFUNLOADPROC)(void);
typedef BOOL (WINAPI *CTFDESCPROC)(COORDTRANSDESC *pCTD);
typedef double (WINAPI *CTFASPECTPROC)(const DoublePair *, const DoublePair *);
typedef double (WINAPI *CTFDISTANCEPROC)(const DoublePair *, const DoublePair *);
typedef BOOL (WINAPI *CTFRECTPROC)(const DoublePair *, const DoublePair *, DoublePair *);
typedef BOOL (WINAPI *CTFTRANSPROC)(DoublePair *, short);
typedef char * (WINAPI *CTFTOSTRINGPROC)(double, BOOL, char *, short);
typedef double (WINAPI *CTFTOVALUEPROC)(char *);
typedef BOOL (WINAPI *CTFISMETRICPROC)(void);
typedef BOOL (WINAPI *CTFTOVALUEEXPROC)(DoublePair *, const char *pBuffX, const char *pBuffY);
typedef BOOL (WINAPI *CTFTOSTRINGEXPROC)(char *, short, BOOL, const DoublePair *);
typedef BOOL (WINAPI *CTFMODEPROC)(COORDTRANSMODE *);
typedef BOOL (WINAPI *CTFDISTEXPROC)(const DoublePair *, const DoublePair *, DoublePair *);

#if !defined(WIN16)
typedef BOOL (WINAPI *CTFTRANSPARAMPROC)(DoublePair *, LPVOID *);
typedef BOOL (WINAPI *CTFTRANSPROCEX)(DoublePair *, short, LPVOID);
#endif // WIN16

#if defined(__cplusplus)
}
#endif

#endif // _CTF_H



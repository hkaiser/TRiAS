// Typ- und Konstantendefinitionen für die ErweiterungsSchnittstelle von TRIAS
// File: XTENSNXX.H
// @doc
// @module XTENSNXX.H | Enthält alle Definitionen der 'C++'-Messages, Datenstrukturen, 
// Konstanten, Makro's und Funtkionen, die für den C++ - spezifischen Teil der 
// <tr>-Programmierschnittstelle notwendig sind.

#if !defined(_XTENSNXX_H)
#define _XTENSNXX_H

#include <pshpack1.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__XT)       // Module in DLL's

#if defined(__DEXPROCS)

extern DEXEXTENSIONPROC g_pDexExtensionProc;
extern DEXEXTENSIONPROC g_pDexxExtensionProc;
extern DEXNOTIFICATIONPROC g_pDexNotificationProc;

LRESULT WINAPI DexxExtensionProc (WPARAM w, LPARAM l);

#else

// in den DLL's bleibt erstmal alles beim alten
#define DexxExtensionProc(w,l)	::SendMessage(__hWndM,__DexxCmd,(WPARAM)w,(LPARAM)l)
	
#endif // __DEXPROCS

#else                   // HauptModul

// im Hauptmodul wird direkt eine exportierte Funktion gerufen
_TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexxExtensionProc (WPARAM w, LPARAM l);

#endif


// Messages -------------------------------------------------------------------
const short DEXX_MAINWINDOW 		= 1000;
const short DEXX_MAINHELPDISPLAY	= 1001;
const short DEXX_ORWINDOW		= 1002;

const short DEXX_GETACTIVEPBD		= 1202;
const short DEXX_CREATEOBJEKTINFO	= 1203;
const short DEXX_GETGEOOBJEKT		= 1204;
const short DEXX_PUTGEOOBJEKT		= 1205;

#define DEXX_GetActivePbd()	\
	(PBD_DB *)DexxExtensionProc((WPARAM)DEXX_GETACTIVEPBD,0L)
#define DEXX_CreateObjektInfo(l)	\
	(ErrCode)DexxExtensionProc((WPARAM)DEXX_CREATEOBJEKTINFO,(LPARAM)&(l))

// Struktur, welche der Abfrage eine neuen VisInfo dient ----------------------
class VisInfo;

// @struct DRAWOBJECT | Diese Struktur wird verwendet, um für einzelne Objekte die
// Darstellungsattribute zu modifizieren, bzw. einzelne Objekte vollständig durch 
// eine Erweiterung darstellen zu lassen. Diese Struktur wird im Zusammenhang mit
// der Notifikation <n DEX_DRAWOBJECT> verwendet.
// @xref <n DEX_DRAWOBJECT>

typedef struct tagDRAWOBJECT {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	long lObjNr;	// @field Die Objektnummer des zu behandelnden Objektes.
	VisInfo *pNewVI;	// @field Die Darstellungsattribute für dieses Objekt,
		// die zur Darstellung verwendet würden, wenn keine Erweiterung dieses
		// Objekt behandeln würde. 
	long lIdent;	// @field Der Identifikator des zu behandelnden Objektes.
	short m_fFlags;	// @field Dieses Feld kann folgende Werte enthalten:
		// @flag DF_Normal | Die Notifikation erfolgt im Zuge einer normalen 
		// Darstellungsoperation.
		// @flag DF_Blinking | Die Notifikation erfolgt im Zusammenhang mit 
		// dem Blinken eines Objektes, welches in einem Objektrecherche-Fenster
		// selektiert ist. In diesem Fall wird keine oder eine vereinfachte
		// Darstellung vorgenommen.
		// @flag DF_Analyze | Die Notifikation erfolgt im Zusammenhang mit 
		// dem Test, ob ein Objekt gezeichnet werden muß, weil es im zu
		// zeichnenden Bildausschnitt liegt oder nicht. In diesem Fall darf
		// keine Darstellungsoperation ausgeführt werden. Es sind lediglich 
		// die Darstellungsattribute zu modifizieren.
} DRAWOBJECT;

// @struct DRAWOBJECTEX | Diese Struktur wird verwendet, um für einzelne Objekte die
// Darstellungsattribute zu modifizieren, bzw. einzelne Objekte vollständig durch 
// eine Erweiterung darstellen zu lassen. Diese Struktur wird im Zusammenhang mit
// der Notifikation <n DEX_DRAWOBJECT> verwendet. Der Unterschied zur Struktur
// DRAWOBJECT besteht daring, daß beim Verwenden dieser Struktur der Rückgabewert
// nicht als LRESULT der Message geliefert werden muß, sondern im Feld m_lResult. 
// @xref <n DEX_DRAWOBJECT>

typedef struct tagDRAWOBJECTEX : public tagDRAWOBJECT {
	LRESULT m_lResult;	// @field Der Rückgabewert aus einer Erweiterung
} DRAWOBJECTEX;

///////////////////////////////////////////////////////////////////////////////
// Struktur für DEX_DRAWIDENTEX
typedef struct tagDRAWIDENTEX {
	DWORD dwSize;
	LONG m_lIdent;
	LRESULT m_lResult;
} DRAWIDENTEX;

class GeoObjekt;

typedef struct tagPUTGEOOBJEKT {
	DWORD dwSize;
	GeoObjekt *pGO;
	BOOL iTemp;
} PUTGEOOBJEKT;

// Struktur für ObjektRechercheFenster ----------------------------------------
class Point;
class Window;
class Color;
class Point;
class CListContainer;

typedef POINT (*OIPOSPROC)(Window *, void *);
typedef POINT (CALLBACK *OIPOSCALLBACK)(Window *, void *);

typedef struct tagDEXXCREATEOBJEKTINFO {
	DWORD dwSize;
	char *lpCaption;	// FensterÜberschrift
	CListContainer *lcObjs;	// Objekte
	Color *pcMColor;	// Markierungsfarbe
	Point *ppntPos;		// AnfangsPosition
	OIPOSPROC fcnPos;	// Funktion, die Fenster positioniert
	void *pData;		// Daten, die an fcnPos übergeben werden
} DEXXCREATEOBJEKTINFO;

typedef struct tagDEXXCREATEOBJEKTINFOEX {
	DWORD dwSize;
	char *lpCaption;	// FensterÜberschrift
	CListContainer *lcObjs;	// Objekte
	Color *pcMColor;	// Markierungsfarbe
	Point *ppntPos;		// AnfangsPosition
	OIPOSPROC fcnPos;	// Funktion, die Fenster positioniert
	void *pData;		// Daten, die an fcnPos übergeben werden
// zusätzliche Member #HK940920
	short m_iFlags;		// Bitmuster für die Abfrage
	HWND m_hWnd;		// evtl. FensterHandle für Target-ORFenster
	CMPONRPROC m_pCmpProc;	// RückrufFunktion für Reihenfolge
	DWORD m_dwData;		// Daten für SortierFunktion
} DEXXCREATEOBJEKTINFOEX;

#if defined(__cplusplus)
}	// extern "C"
#endif

#include <poppack.h>

#endif // _XTENSNXX_H

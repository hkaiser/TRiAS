// Typdeklarationen für Klassenbibliothek IRIS
// File: RISTYPES.H

// IRISWIN: %W%	%E%

#if !defined(_RISTYPES_HXX)
#define _RISTYPES_HXX

#include <KoOrd.h>		// KoordinatenDatentyp

// VersionsKontrolle innerhalb von DIRIS
#include <versions.h>

// Funktionsprototypen
#if defined(_FORCE_LEGACY_CODE)
long GetGeoDBVersion (class GeoDB *pDB = NULL);
void ResetGeoDBVersion (void);
#endif // _FORCE_LEGACY_CODE

// für Kompatibilität mit ZIPEDB
extern "C" {

#if !defined(_DB_ADDR_DEFINED)

#include <pshpack1.h>

struct db_addr {
public:
	short file_no;          /* Filenummer */
	HPROJECT db_no;		/* HPROJECT */
	long rec_no;          /* Satznummer */
	
//		db_addr (void) : db_no(0) {}
		db_addr (HPROJECT hPr) : db_no (hPr) {}
};

typedef db_addr DB_ADDR;

#include <poppack.h>

#define _DB_ADDR_DEFINED
#endif // _DB_ADDR_DEFINED
}

#if !defined(FUNCTYPE)
#if defined(DLL)
#define FUNCTYPE _pascal
#else
#define FUNCTYPE _cdecl
#endif
#endif

#if !defined(_INT_FUNC_DEFINED)
typedef int	INT_FUNC (int, int, ...);	// Funktion, die int liefert
#define _INT_FUNC_DEFINED
#endif

// Objekttypen
enum ObjTyp { 
	OT_PUNKT, 
	OT_KANTE, 
	OT_FLAECHE, 
	OT_KREIS,
	OT_KO, 
	OT_TEXT,
	OT_UNKNOWN,
	OT_LABEL,
#if !defined(NOGITTER)
	OT_GITTER, 
#endif
};

// TextTypen
enum TextObjTyp {
	TOT_TEXT,
	TOT_TEXTIND,
	TOT_TEXTINDOBJPROP,
};

// RelationsTypen
enum RelTyp {
	RT_BEGLEIT,
	RT_GLEICHR,
	RT_KOMPLEX,
};

// DatenBasisTypen
enum DBTyp { O_GEODB, O_PBDDB, };

// ZeichenFlag
enum PaintFlag { PF_INVALID, PF_NOTDRAWED, PF_NEW, PF_REDRAW, };

///////////////////////////////////////////////////////////////////////////////
// ungültige Werte für diverse Handles
#define INVALID_ONR		INT_PTR(0)
#define INVALID_IDENT	INT_PTR(0)
#define INVALID_MCODE	INT_PTR(0)

#endif // _RISTYPES_HXX

// Typdeklarationen für Klassenbibliothek IRIS
// File: RISTYPES.H

// IRISWIN: %W%	%E%

#if !defined(_RISTYPES_HXX)
#define _RISTYPES_HXX

// VersionsKontrolle innerhalb von DIRIS
#define NEWDBVERSION	0x05000003L
#define VERSION05000004	0x05000004L
#define VERSION05000005 0x05000005L
#define VERSION05000006 0x05000006L
#define VERSION05000007 0x05000007L
#define VERSION05000008 0x05000008L

// Funktionsprototypen
long GetGeoDBVersion (class GeoDB *pDB = NULL);
void ResetGeoDBVersion (void);

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

typedef long	KoOrd;		// Koordinate

#if !defined(_INT_FUNC_DEFINED)
typedef int	INT_FUNC (int, int, ...);	// Funktion, die int liefert
#define _INT_FUNC_DEFINED
#endif

// maximal möglicher KoOrdinatenwert
#if defined(MAXKOORD)
#undef MAXKOORD
#endif

const KoOrd MAXKOORD = 1073741824L;

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

// Klassendeklarationen -------------------------------------------------------
// ----------------------------------------------------------------------------
// File: PBD.HXX
class PBD_Data;
class PBD_Ident;
class PBD_Merkmal;
class PBD_Relation;

// File EDITHEAD.HXX:
class HeaderSatzListe;
class ExtTable;
class EditHeaderDialog;
class ExtControlEvt;

// File GEO_OBJ.HXX:
class ObjContainer;
class Kante;
class KoordinatenPaar;
class Punkt;
class Ausdehnung;
class Masche;
class Ellipsen;
class Kreis;
class GeoObjekt;
class GeoPunkt;
class GeoKante;
class GeoFlaeche;
class GeoKreis;

// File TRANSFRM.HXX:
class Transformation;

// File PWDIALOG.HXX:
class PassWordDlg;

// File HDRENTRY.HXX:
class HeaderEntry;

// File TOOLS.HXX:
class ToolBox;
class ToolWind;

// File DRAW_OBJ.HXX:
class ExtShapeObject;
class ExtBitmapObject;
class ObjNummer;
class ObjRigInfo;
class ObjFeld;
class ObjektListe;
class PunktObjekt;
class KantenObjekt;
class MaschenObjekt;
class KreisObjekt;
class DatenBasisObjekt;

class SchriftObjekt;
class KomplexObjekt;
class RelationsObjekt;

// File OBJEKTE.HXX:
class ObjektInfo;
class ObjektInfoListe;

// File DB.HXX:
class DBTemplate;
class GeoDB;
class PBD_DB;

// File PROFILE.HXX:
class ProFile;

// File MKRECH.HXX:
class TextRechercheParams;

// File IDENTSEL.HXX:
class CIdentifikator;
class CIdTree1;
class CIdTree2;
class CIdTree;
class IdentSelektion;

// File MERKMAL.HXX:
class TextMerkmal;
class IntMerkmal;
class FloatMerkmal;
class DoubleMerkmal;
class MerkmalsListe;

// File COORDS.HXX:
class CoordsDlg;

// File ABOUT.HXX:
class AboutDialogBox;

// File IRIS.HXX:
class OpenDBDialog;
class DragRectangleObject;
class GitterObjekt;
class ExtWndHorzScrollBar;
class IrisWind;

// File NOMENKL.HXX:
class NomenklaturDlg;

// BildDarstellung
class BildObjekt;
class BildWindow;

// File: ATTRIBS.HXX
class VisInfo;
class PVisInfo;
class LVisInfo;
class FVisInfo;
class TVisInfo;
class Sicht;

class SchrankSchnulli;

// Importierte Klasse aus DIRIS06 (Recherche)
class RStatus;		// RechercheStatus

class LegendeItem;
class LegendeObjekt;
class LegendeWindow;

class DLLBind;
class CoordTrans;

#endif // _RISTYPES_HXX

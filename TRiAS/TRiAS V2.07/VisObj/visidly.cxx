
#line 2 "visidly.y"
// Parser fuer die Speicherung von Sichten (Visualisierungsinfo's)
// File: VISIDLY.Y

#include <stdio.h>
	
#include <protos.h>

#include <risdb.h>
#include "visobj.h"
#include "resource.h"

#define RC_YY2Parse	9000	// RoutinenCode

#include <hdrentrx.hxx>
#include <attribs.hxx>
#include <rgb_hsb.hxx>

#include <strdupx.hxx>

#include "visobj.hxx"
#include "vstatus.hxx"
#include "yy2stype.hxx"

#include "cimpview.hxx"
#include "cimpview.inl"

#include "uidobj.hxx"
#include "uidobj.inl"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_MSC_VER)
#pragma warning (disable: 4102)		// unreferenced label
#endif

// globale Daten --------------------------------------------------------------
static char chViewName[SIGHTNAMESIZE+1];	// aktuelle Sicht

// allgemeine Visualisierungsattribute
static short iDefPriority, iPriority;	// DarstellungsPriorität
static short iDefType, iType;		// DarstellungsArt
static char chDefTypeString[VISNAMESIZE+1], chTypeString[VISNAMESIZE+1];
static COLORREF colDefMainColor, colMainColor;
static long lUpperScale, lLowerScale;

// objektspezifische Visualisierungsattribute
static SIZE szDefSize, szSize;
static short iDefWidth, iWidth;
static short iDefOpaque, iOpaque;
static short iDefBkConture, iBkConture;
static COLORREF colDefFillColor, colFillColor;
static short iDefTextTyp, iDefTextRot;
static short iTextTyp, iTextRot;
static short iPunktRot, iDefPunktRot;

static short fDefBits, fBits;		// reine Sichtzugehörigkeit
static bool fDefTag, fTag;

static char *cbVisModule[2] = { NULL, NULL, };

static bool fDefaultAttributes = false;	// Flag, ob DefaultSektion aktiv
static bool fFirstIdent = true;		// erster Ident (für hex-Test)
static bool fImpView = false;		// diese Sicht eingeben
static bool fSetStandardView = false;	// diese Ansicht als AnfangsAnsicht festlegen

static short cnIdents = 0;		// Zähler der IdentSätze
static short s_iDrawResult = 0;		// hier wird vermerkt, was geändert wurde

static long s_lIdent = -1L;			// bearbeiteter Identifikator
static long s_lObject = -1L;			// bearbeitetes Objekt
static long s_lLegVMCode = -1L;
static long s_lLegMCode = -1L;

// ImportOptionen -------------------------------------------------------------
extern bool g_fImpHSB;			// Eingabe als HSB interpretieren
extern bool g_fImpDefView;		// StandardSicht importieren
extern bool g_fImpObjVis;		// Objektvisualisierung importieren
extern bool g_fImpViewFeatures;		// Sichtmerkmale importieren
extern bool g_fImpLegInfo;		// Legende importieren
extern bool g_fImpExistendOnly;		// nur existierende Idents importieren

extern bool g_fDecIdent;

extern long g_lUIMCode;			// MerkmalsCode des Unique Idents
extern CStatus *g_pIS;			// StatusFenster
extern CImpViewTree *g_pVT;		// Baum, der alle Sichten enthält
extern CUIdentObjects *g_pUIObjs;	// Baum mit UIdents <--> (lONr's, iOType's)

extern int yy2lineno;

// Funktionsprototypen --------------------------------------------------------
static void InitDefaultAttributes (void);
static VisType InitAttributes (long lIdent, VisType iVTyp);
static unsigned long MakeHex (unsigned long lPseudoHex);

void yy2error (const char *, ...);
void yy2error (enum ErrCode, ...);
#define YYABORT	return(1)

#define YYLMAX	2048

// Rücksetzen aller lokalen Variablen -----------------------------------------
void InitYY2Vars (void) 
{
	fDefaultAttributes = false;	// Flag, ob DefaultSektion aktiv
	fFirstIdent = true;		// erster Ident (für hex-Test)
	fImpView = false;		// diese Sicht eingeben
	fSetStandardView = false;	// nicht als AnfangsAnsicht verwenden
	cnIdents = 0;			// Zähler der IdentSätze
	s_iDrawResult = DO_UnChanged;	// hier wird vermerkt, was geändert wurde
	cbVisModule[0] = cbVisModule[1] = NULL;

	s_lLegVMCode = -1L;		// MerkmalsCodes für Legende
	s_lLegMCode = -1L;	

	yy2lineno = 0;
		
	InitDefaultAttributes();
}


#define T_STRING 257
#define T_VIEW 258
#define T_STARTVIEW 259
#define T_NUMBER 260
#define T_DEFAULT 261
#define T_PUNKT 262
#define T_LINIE 263
#define T_FLAECHE 264
#define T_TEXT 265
#define T_PRIORITY 266
#define T_TYPE 267
#define T_MCODE 268
#define T_DESC 269
#define T_TAGGED 270
#define T_MAINCOLOR 271
#define T_SIZE 272
#define T_WIDTH 273
#define T_FILLCOLOR 274
#define T_TTYP 275
#define T_TROT 276
#define T_MAINCOLORC 277
#define T_FILLCOLORC 278
#define T_IDENT 279
#define T_EQUAL 280
#define T_HEXNUMBER 281
#define T_TVCS 282
#define T_TLEGINFO 283
#define T_OKS 284
#define T_UPPERSCALE 285
#define T_LOWERSCALE 286
#define yy2clearin yy2char = -1
#define yy2errok yy2errflag = 0
extern int yy2char;
extern short yy2errflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE (*pyy2lval), (*pyy2val);
#define YYERRCODE 256

#line 1382 "visidly.y"


// DefaultWerte voreinstellen -------------------------------------------------
static VisType InitAttributes (long lId, VisType iVTyp) 
{
ResString DefView (ResID (IDS_DEFAULTVIEW, &g_pTE -> RF()), SIGHTNAMESIZE+1);
HANDLEVISINFO *pHVI = GetIdentVisInfo (lId, short(iVTyp), (char *)DefView.Addr());
VisInfo *pVI = NULL;

	if (pHVI != NULL) 
		pVI = VisInfoFromC (*pHVI -> m_pVI, (VisType)pHVI -> m_iVTyp);

	dtHANDLEVISINFO (pHVI);		// Speicher wieder freigeben

	DELETE_OBJ (cbVisModule[0]);
	DELETE_OBJ (cbVisModule[1]);
	lUpperScale = lLowerScale = 0;

	if (pVI != NULL) {	// Id existiert
		iType = pVI -> Style();
		strncpy (chTypeString, pVI -> VisName(), VISNAMESIZE);
		chTypeString[VISNAMESIZE] = '\0';
		iPriority = pVI -> Priority();
		(Color &)colMainColor = pVI -> PrimColor();

		if (iVTyp != VT_Default &&
		    pVI -> isA() != iVTyp) {
		// DefaultTyp etspricht nicht dem geforderten
			szSize = szDefSize;
			iPunktRot = iDefPunktRot;
			iWidth = iDefWidth;
			colFillColor = colMainColor;
			iTextRot = iDefTextRot;
			iTextTyp = iDefTextTyp;
			iOpaque = iDefOpaque;
			iBkConture = iDefBkConture;
			fBits = fDefBits;
			fTag = fDefTag;
			return VT_Default;
		} else switch (pVI -> isA()) {
		// DefaultTyp entspricht gesuchtem Typ
		case VT_Punkt:
			*(Dimension *)&szSize = ((PVisInfo *)pVI) -> Size();
			iPunktRot = ((PVisInfo *)pVI) -> Rotation();
			(Color &)colFillColor = ((PVisInfo *)pVI) -> SecColor();
			return VT_Punkt;

		case VT_Linie:
			iWidth = ((LVisInfo *)pVI) -> Width();
			return VT_Linie;

		case VT_Flaeche:
			(Color &)colFillColor = ((FVisInfo *)pVI) -> SecColor();
			iWidth = ((FVisInfo *)pVI) -> Width();
			iType = ((FVisInfo *)pVI) -> Type();
			iOpaque = ((FVisInfo *)pVI) -> isOpaque() ? BMOpaque : 0;
			iBkConture = ((FVisInfo *)pVI) -> isBkConture();
			return VT_Flaeche;

		case VT_Text:
			*(Dimension *)&szSize = ((TVisInfo *)pVI) -> Size();
			iTextRot = ((TVisInfo *)pVI) -> Rotation();
			iTextTyp = ((TVisInfo *)pVI) -> Type();
			return VT_Text;

		default:
		case VT_Default:
			szSize = szDefSize;
			iPunktRot = iDefPunktRot;
			iWidth = iDefWidth;
			colFillColor = colDefFillColor;
			iTextRot = iDefTextRot;
			iTextTyp = iDefTextTyp;
			iOpaque = iDefOpaque;
			iBkConture = iDefBkConture;
			fBits = fDefBits;
			fTag = fDefTag;
			return VT_Default;
		}
	} else {
	// Sicht oder Identifikator existieren nicht 
		iType = iDefType;
		iPunktRot = iDefPunktRot;
		strncpy (chTypeString, chDefTypeString, VISNAMESIZE);
		chTypeString[VISNAMESIZE] = '\0';
		iPriority = iDefPriority;
		colMainColor = colDefMainColor;
		colFillColor = colDefFillColor;
		iWidth = iDefWidth;
		szSize = szDefSize;
		iTextRot = iDefTextRot;
		iTextTyp = iDefTextTyp;
		iOpaque = iDefOpaque;
		iBkConture = iDefBkConture;
		fBits = fDefBits;
		fTag = fDefTag;
		return VT_Default;
	}
}

// Standardwerte voreinstellen ------------------------------------------------
static void InitDefaultAttributes (void) 
{
	iDefType = 0;
	chDefTypeString[0] = '\0';
	iDefPriority = 500;
	colDefMainColor = (COLORREF &)DEF_COLOR;
	colDefFillColor = (COLORREF &)DEF_SECCOLOR;
	iDefWidth = 0;
	szDefSize.cx = DEF_SIZE_PUNKT_X;
	szDefSize.cy = DEF_SIZE_PUNKT_Y;
	iDefPunktRot = 0;
	iDefTextTyp = 0;
	iDefTextRot = 0;
	iDefOpaque = 0;
	fDefBits = 0;
	fDefTag = false;
	DELETE_OBJ (cbVisModule[0]);
	DELETE_OBJ (cbVisModule[1]);
}

void yy2error (const char *pFormat, ...) 
{
char *pszText = new char [_MAX_PATH];
bool fToDelete = false;

	if (pszText != NULL) {
		wvsprintf (pszText, (LPSTR)pFormat, (LPSTR)(&pFormat+1));
		fToDelete = true;
	} else
		pszText = (char *)pFormat;
		
char cbLineNum[20];

	ltoa (yy2lineno, cbLineNum, 10);
	strcat (pszText, ", Zeile: ");
	strcat (pszText, cbLineNum);

	MessageBox (NULL, pszText, 
		    ResString (ResID (IDS_YYERRORCAPTION, &g_pTE -> RF()), 64),
		    MB_TASKMODAL|MB_ICONSTOP|MB_OK);
		    
	if (fToDelete) DELETE_OBJ (pszText);
}

void yy2error (ErrCode EC, ...) 
{
	DEX_Error (RC_YY2Parse, EC);
}


// Finden des Objektes, welches einen vorgegebenen Unique Ident hat -----------
extern "C" 
BOOL PASCAL _XTENSN_EXPORT ImportViewObject (long lONr, BOOL, void *pData)
{
long *pObjs = (long *)pData;
short iOTyp = DEX_GetObjectType (lONr);

// ObjektNummer speichern
	pObjs[4] = lONr;		// hier immer merken (für OGUnknown)
	switch (iOTyp) {
	case OGPunkt:
		pObjs[0] = lONr;
		break;
		
	case OGLinie:
		pObjs[1] = lONr;
		break;
		
	case OGFlaeche:
		pObjs[2] = lONr;
		break;

	case OGLabel:		
	case OGText:
		pObjs[3] = lONr;
		break;
		
	default:
		break;	
	}

return true;	// alle Objekte finden
}


// Finden der ObjektNummer über den gegebenen Unique Ident --------------------
short OTypToBits (short iOTyp);

long FindObjekt (char *pUIdent, long lMCode, short iOTyp)
{
	TX_ASSERT(NULL != pUIdent);

	if (lMCode == -1) return -1;	// kein Unique Ident vorhanden

	if (g_pUIObjs) {
	// evtl. füllen
		if (!g_pUIObjs -> isFilled()) {
		char cbBuffer[65];
		ResString rsImportWait (ResID (IDS_IMPORTWAIT, &g_pTE -> RF()), 64);
		
			g_pIS -> GetComment (cbBuffer, sizeof(cbBuffer));
			g_pIS -> SetComment ((char *)rsImportWait.Addr());
			if (!g_pUIObjs -> FillTree (lMCode)) {
				g_pIS -> SetComment (cbBuffer);
				return -1L;	// Fehler
			}
			g_pIS -> SetComment (cbBuffer);
		}
			
	// Baum abfragen
	CObjUIdent *pObj = g_pUIObjs -> FFindFirstItem (pUIdent);
	bool fFoundOthers = false;

		while (pObj != NULL) {
			if (pObj -> OTyp() == OTypToBits(iOTyp))
				return pObj -> ObjNr();
			fFoundOthers = true;
			pObj = g_pUIObjs -> FFindNextItem (pUIdent);
		}

		if (fFoundOthers && (OGText == iOTyp || OGLabel == iOTyp) && *pUIdent != '$') {
		// wenn Textobjekt nicht gefunden dafür aber ein anderes Objekt 
		// anderen Typs gefunden wurde, dann UIdent mit '$' versehen und 
		// es noch einmal versuchen
		static char s_cbBuffer[1024];
		char *pT = s_cbBuffer;

			s_cbBuffer[0] = '$';
			s_cbBuffer[1] = '\0';
			strcat (s_cbBuffer, pUIdent);
			pObj = g_pUIObjs -> FFindFirstItem (pT);
			if (NULL != pObj && OTText == pObj -> OTyp())
				return pObj -> ObjNr();
		}

		return -1L;	// nichts gefunden
	} else {
	// einzeln abfragen (alte Variante)
	ENUMRECHTEXTMERKMAL ERTM;
	long cbONr[5] = { -1L, -1L, -1L, -1L, -1L, };
	
		memset (&ERTM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
		ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
		ERTM.lMCode = lMCode;
		ERTM.pMWert = pUIdent;		// SuchPattern
		ERTM.iMode = SMExactMatch;	// exact match
		ERTM.eFcn = ImportViewObject;
		ERTM.pData = cbONr;
		DEX_EnumRechTextMerkmal (ERTM);
	
	long lONrRet = -1L;
	
		switch (iOTyp) {	// ObjektNummer suchen
		case OGPunkt:	lONrRet = cbONr[0];
		case OGLinie:	lONrRet = cbONr[1];
		case OGFlaeche:	lONrRet = cbONr[2];
		case OGLabel:
		case OGText:	lONrRet = cbONr[3];
		default:	
			break;
		}
		if (lONrRet == -1L) 
			lONrRet = cbONr[4];
	
		return lONrRet;
	}
}


// Umkonvertieren einer Dezimalzahl in eine HexZahl ---------------------------
static unsigned long MakeHex (unsigned long lPseudoHex)
{
char pTmp[40];

	ultoa (lPseudoHex, pTmp, 10);

return strtoul (pTmp, NULL, 16);
}


// Hinzufügen eines Identifikators zu einer Sicht -----------------------------
bool AddIDtoSight (
	char *chViewName, long lIdent, VisInfo *pVI, long lUpper, long lLower, short iTypes)
{
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (pVI ? pVI -> isA() : VTDefault);

	if (pHVI == NULL) return false;
	
// Member setzen
	pHVI -> m_pView = chViewName;		// SichtNamen setzen
	pHVI -> m_lIdent = lIdent;		// Ident setzen
	if (!g_fImpExistendOnly)		// alle Idents Importieren
		pHVI -> m_fFlags = DF_ForceImport;

	if (pVI != NULL) {
		pVI -> CopyTo (*pHVI -> m_pVI);		// VISINFO setzen
		if (pVI -> isA() == VTDefault)
			((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = iTypes;	// sonstige IdentGeoTypen
	} else 
		((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = iTypes;	// sonstige IdentGeoTypen
	
bool iResult = (DEX_ModIdentVisInfo (*pHVI) == EC_OKAY);	// zu Sicht hinzufügen

	dtHANDLEVISINFO (pHVI);

// evtl. maßstabsbezogen ein bzw. ausblenden
	if ((0 != lUpper || 0 != lLower) && VTDefault != pVI -> isA()) {
	IDENTSCALEDATA ISD;

		INITSTRUCT(ISD, IDENTSCALEDATA);
		ISD.pcView = chViewName;
		ISD.lIdent = lIdent;
		ISD.iVTyp = pVI -> isA();
		ISD.lUpperScale = lUpper;
		ISD.lLowerScale = lLower;
		DEX_SetIdentScaleData(ISD);
	}
	return iResult;
}
 

// Schreiben einer objektbezogenen Visualisierung -----------------------------
bool AddVItoObject (char *chViewName, long lONr, VisInfo *pVI, 
		    short iDrawResult, char **cbModuleInfo)
{
	if (lONr == -1L) return false;		// Fehler
	
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (pVI ? pVI -> isA() : VTDefault);

	if (pHVI == NULL) return false;
	
// Member setzen
	pHVI -> m_pView = chViewName;		// SichtNamen setzen
	pHVI -> m_lONr = lONr;			// ObjektNummer setzen
	pHVI -> m_fFlags = iDrawResult;		// was wurde geändert
	if (fTag) {
		pHVI -> m_fFlags |= DO_Tagged;	// Objekt ist evtl. ausgeblendet
		fTag = false;			// nur einmal verwenden
	}

	if (pVI != NULL) {
		pVI -> CopyTo (*pHVI -> m_pVI);		// VISINFO setzen
		if (pVI -> isA() == VTDefault)
			((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = -1 /*iTypes*/;	// sonstige IdentGeoTypen
	} else 
		((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = -1/*iTypes*/;	// sonstige IdentGeoTypen
	
bool iResult = ChangeVisInfo (pHVI, cbModuleInfo);	

	dtHANDLEVISINFO (pHVI);
	
return iResult;
}

// wegspeichern der LegendenInfo an einem Identifikator -----------------------
bool AddLegInfoToIdent (char *pView, long lIdent, char *pLegInfo, bool fAppend)
{
	if (lIdent == -1) return false;
	
// MerkmalsCodes besorgen
	if (s_lLegVMCode == -1L) {
		s_lLegVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
				IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
		if (s_lLegVMCode == -1L)
			return false;		// Fehler
	}
	if (s_lLegMCode == -1L) {
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

		s_lLegMCode = GetObjMCodeView (pView, s_lLegVMCode, 
				ResID (IDS_LEGINFOKTEXT, &pE -> RF()), 
				ResID (IDS_LEGINFOLTEXT, &pE -> RF()), true, lIdent);
		if (s_lLegMCode == -1L)
			return false;
	}

	if (fAppend) {
	// Merkmal dranhängen
	char cbBuffer[_MAX_PATH] = { '\0' };

		ReadTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, cbBuffer, sizeof(cbBuffer));
		strcat (cbBuffer, pLegInfo);
		return WriteTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, cbBuffer);
	}

// Merkmal vollständig neu schreiben
	return WriteTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, pLegInfo);
}

// wegspeichern einer LegendenInfo an einem Objekt ----------------------------
bool AddLegInfoToObject (char *pView, long lONr, char *pLegInfo)
{
	if (lONr == -1) return false;
	
// MerkmalsCodes besorgen
	if (s_lLegVMCode == -1L) {
		s_lLegVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
				IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
		if (s_lLegVMCode == -1L)
			return false;		// Fehler
	}
	if (s_lLegMCode == -1L) {
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

		s_lLegMCode = GetObjMCodeView (pView, s_lLegVMCode, 
				ResID (IDS_LEGINFOKTEXT, &pE -> RF()), 
				ResID (IDS_LEGINFOLTEXT, &pE -> RF()), true, DEX_GetObjIdent(lONr));
		if (s_lLegMCode == -1L)
			return false;
	}

	return WriteTextMerkmal (TT_Objekt, lONr, s_lLegMCode, pLegInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Verwalten der in einer Ansicht bereits bearbeiteten Identifikatoren
#include <ospace/std/set>

namespace {

	typedef set<LONG, less<LONG> > CKnownIdents;
	CKnownIdents s_Idents;

	void ResetIdents() 
	{
		s_Idents.clear();
	}
	bool AddIdent (LONG lIdent)
	{
	CKnownIdents::iterator it = s_Idents.find (lIdent);

		if (it == s_Idents.end()) {
			s_Idents.insert (lIdent);
			return true;
		}
		return false;
	}
	bool IsFirstIdent (LONG lIdent)
	{
	CKnownIdents::iterator it = s_Idents.find (lIdent);

		return it == s_Idents.end() ? true : false;
	}
} // namespace

short yy2exca[] = {-1, 1,
	0, -1,
	-2, 0,
	};
#define YYNPROD 135
#define YYLAST 557
short yy2act[]={

 219,  56,  57,  86, 191, 176,  58,  64,  76,  88,
  99, 100,  59,  89, 191, 266, 132,  60,  61, 121,
  62,  63,  42, 104,  55, 119, 177, 123,  42, 199,
 122,  40, 263,  45,  42,  22,  34,  35,  36,  37,
   9,  41,  38,  43,  10,  86,  44,  41, 117,  43,
 191,  42,  44,  41, 115,  43, 261,  42,  44, 259,
 257, 254, 249, 231, 225, 218,  55, 214, 213, 149,
  41, 208,  43, 206, 201,  44,  41, 197,  43, 196,
 189,  44, 188,   5,   6, 247, 229, 216,  98, 250,
 129, 194, 178,  11, 198, 180,  96, 255, 252, 195,
 175, 174, 173, 172, 171, 170, 169, 168, 167,  98,
 166,  80,  94, 125, 124,  47,   8,  84,  81,  72,
 165, 108, 111, 161, 228, 160, 159,  74, 158, 154,
 153, 152,  50,  53, 148, 144, 143, 142, 141, 140,
 139,  56,  57,  75, 138, 264,  58,  64,  76,  88,
  99, 100,  59,  89, 155,  85,  85,  60,  61, 137,
  62,  63, 136, 135, 134,  40, 133, 111,  42,  22,
  34,  35,  36,  37,  75,  93,  38, 127, 126, 223,
 260, 256, 246, 245, 244, 243, 242,  41, 162,  43,
 146, 241,  44, 240, 222, 239, 238, 237, 150, 236,
 235, 234, 233, 230, 227, 156, 224,  85, 221, 145,
  56,  57, 262, 258, 253,  58,  51,  76,  88,  87,
 248,  59,  89, 232, 192, 186,  60,  61, 163,  62,
  63,  56,  57, 107, 192, 210,  58,  64, 226,  66,
  71,  65,  59,  67, 267, 203, 185,  60,  61, 200,
  62,  63,  56,  57, 265, 215, 184,  58,  78,  76,
  88,  87, 183,  59,  89, 105, 130,  91,  60,  61,
 192,  62,  63,  56,  57, 220, 186,  48,  58,  64,
  14,  66, 190,  65,  59,  67, 110,  90, 106,  60,
  61,  69,  62,  63,  46,  56,  57, 185, 102, 113,
  58, 101,  68,  97,  99, 100,  59, 184,  92, 251,
  83,  60,  61, 183,  62,  63,  56,  57,  77,  79,
   3,  58, 101,   7,  70,  99, 100,  59,  54,  56,
  57,  49,  60,  61,  58,  62,  63, 182, 112, 179,
  59, 131, 128,  20,  19,  60,  61,  18,  62,  63,
  56,  57,  17,  16,  15,  58,  13,  76,  12,   2,
  21,  59,  33,  30,  28,  26,  60,  61,  24,  62,
  63,  31,  29,  32,  56,  57,  52,  27,  25,  58,
  39,  56,  57, 112,  23,  59,  58, 103,  76,   4,
  60,  61,  59,  62,  63,   1,   0,  60,  61,   0,
  62,  63,  73,  73,  82,  82,  95,  95,   0, 109,
 109,   0,   0, 147,   0, 114, 116, 118, 120, 193,
   0,   0, 151,   0,   0,   0, 202, 204,   0,   0,
   0,   0,   0,   0,   0, 157, 209, 211,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  73,   0, 164,
   0,   0,   0,   0,   0,   0,  82,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  95,
   0, 187,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 109,   0,   0,   0, 205,   0,   0,
   0, 207,   0,   0,   0,   0,   0, 212,   0,   0,
   0,   0,   0,   0, 217, 181,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0, 181 };
short yy2pact[]={

-175,-1000,-175,-1000,  -7,-217,-164,-1000,-1000,-1000,
-1000,-1000,-226, -92,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,  -8,   7,   7, 115, 115, -14, -14,  50,
  50,-246, 108, 108,-203,-209,-232,-238,-230,  -9,
 -10, 117,-1000,-1000, 116,-1000,-1000,-1000,-1000, -35,
-254,-1000,-1000,-1000,-1000,-1000, 105, 103, 102, 101,
  98,  83,  79,  78,  77,  76,  75,  74,-1000,-1000,
  84,-254,-1000,-1000,-1000,-1000,  73,-1000,-1000, -56,
-254,-1000,-1000,-1000,-1000,-1000,-1000,  70,  69,  68,
-1000,-1000,  29,-254,-1000,-1000,-1000,-1000,-1000,  67,
  65,  64,-1000,-1000,  62,-1000,  63,-254,-1000,-1000,
-1000,-1000,  59,-1000, -13, -15, -16, -17, -18, -19,
 -20, -21, -22, -23,-1000,-1000,-255,-165,-265,-254,
-1000,-1000,-1000,-178,-180,  10,  10,-166, -24,-181,
-183, -11,-186, -26,  10,-254,-1000,-1000,-187,-254,
-1000,-1000,-189, -36,  10,-254,-1000,-1000,-192,-193,
 -11,-170,-254,-1000,-1000,-195,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-125,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000, 149, 135,
 147,-196, 194, 145,  66,-171,-1000,-1000, 144,-197,
 179, 143, 142, 141, 140,-1000, 138,-1000, 137, 136,
 134, 132,-1000, 127, 126, 125, 124,-1000, 123,-1000,
-1000,-1000,-1000,-172,-1000, 176,-198,-1000,  52, -27,
-1000, 170,-199,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000, -28,-1000, 122,-200, 169,
-201, 121,-1000,-204,-1000,-1000,-1000, 168,-228,  86,
-1000, 213,-245,-1000,-1000,-1000, 203,-1000 };
short yy2pgo[]={

   0, 395, 389, 387,  94, 282, 380, 376, 384, 378,
 377, 373, 372, 371, 368, 365, 364, 363, 362, 360,
 359, 320, 358, 356, 280, 354, 353, 352, 347, 344,
 343, 341, 342, 339,  95, 337, 277, 331, 216, 133,
 328, 291, 324, 119, 127, 258, 319, 118, 310, 117,
 267, 308, 112,  96, 303, 265, 288, 121, 286 };

short yy2r1[]={
   0,   1,  20,  20,  22,  21,   2,   2,   2,  23,
  23,  24,  24,  24,  24,  24,  24,  24,  31,  32,
  25,  33,  33,  34,  34,  26,  26,   8,  14,  36,
  36,  36,  36,  37,  37,  38,  38,  38,  38,  27,
  27,   9,  15,  41,  41,  41,  41,  42,  42,  43,
  43,  43,  28,  28,  10,  16,  45,  45,  45,  45,
  46,  46,  47,  47,  47,  47,  47,  29,  29,  12,
  17,  50,  50,  50,  50,  51,  51,  52,  52,  52,
  52,  30,  13,  13,   3,  19,  19,  11,  18,  55,
  55,  55,  55,  56,  56,  57,  57,  57,   7,   7,
   7,   7,   7,   7,   7,   7,   7,   7,  35,  35,
  35,  35,  54,  39,  40,  40,  40,  40,  44,  49,
  49,  49,  48,  58,  53,  53,   6,   6,   6,   6,
   6,   4,   4,   5,   5 };

short yy2r2[]={
   0,   1,   1,   2,   0,   5,   2,   2,   2,   1,
   2,   1,   1,   1,   1,   1,   1,   1,   1,   0,
   5,   1,   2,   1,   1,   2,   2,   3,   3,   3,
   2,   2,   1,   1,   2,   1,   1,   1,   1,   2,
   2,   3,   3,   3,   2,   2,   1,   1,   2,   1,
   1,   1,   2,   2,   3,   3,   3,   2,   2,   1,
   1,   2,   1,   1,   1,   1,   1,   2,   2,   3,
   3,   3,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   3,   3,   5,   2,   2,   2,   2,   3,
   2,   2,   1,   1,   2,   1,   1,   1,   4,   4,
   6,   4,   4,   7,   6,   5,   3,   3,   1,   1,
   1,   1,   4,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   3,   3,   1,   1,
   3,   5,   3,   7,   5 };

short yy2chk[]={
-1000,  -1, -20, -21,  -2, 258, 259, -21, 123, 257,
 261, 257, -22, -23, -24, -25, -26, -27, -28, -29,
 -30, -19, 261,  -8, -14,  -9, -15, -10, -16, -12,
 -17, -13, -11, -18, 262, 263, 264, 265, 268,  -6,
 257, 279, 260, 281, 284, 125, -24, 123, -36, -37,
 125, -38,  -7, -39, -40,  59, 266, 267, 271, 277,
 282, 283, 285, 286, 272, 276, 274, 278, -36, -41,
 -42, 125, -43,  -7, -44,  59, 273, -41, -45, -46,
 125, -47,  -7, -48, -49, -44,  59, 275, 274, 278,
 -45, -50, -51, 125, -52,  -7, -53, -54,  59, 275,
 276, 272, -50,  -3, 269, -55, -56, 125, -57,  -7,
 -58,  59, 275, -55,  -6, 257,  -6, 257,  -6, 257,
  -6, 257, 260, 257, 123, 123,  61,  61, -32, 125,
 -38, -31, 270,  61,  61,  61,  61,  61,  61,  61,
  61,  61,  61,  61,  61, 125, -43, -31,  61, 125,
 -47, -31,  61,  61,  61, 125, -52, -31,  61,  61,
  61,  61, 125, -57, -31,  61, 123, 123, 123, 123,
 123, 123, 123, 123, 123, 123, 260, 281, 257, -33,
 -34,  -7, -35, -39, -44, -49, -53, -31, 260, 260,
  -5,  40, 260,  -5, 257, 123, 260, 260,  -4,  40,
 260, 260,  -5, 271,  -5, -31, 260, -31, 260,  -5,
 271,  -5, -31, 260, 260,  -4, 257, -31, 260, 125,
 -34,  59,  59,  44,  59, 260,  44,  59,  58, 257,
  59, 260,  44,  59,  59,  59,  59,  59,  59,  59,
  59,  59,  59,  59,  59,  59,  59, 257,  44, 260,
  37, 257, 125,  44, 260, 125,  59, 260,  44, 260,
  59, 260,  44, 260,  59,  41, 260,  41 };

short yy2def[]={
   0,  -2,   1,   2,   0,   0,   0,   3,   4,   6,
   8,   7,   0,   0,   9,  11,  12,  13,  14,  15,
  16,  17,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 128, 129,   0,   5,  10,  19,  25,   0,
  32,  33,  35,  36,  37,  38,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  26,  39,
   0,  46,  47,  49,  50,  51,   0,  40,  52,   0,
  59,  60,  62,  63,  64,  65,  66,   0,   0,   0,
  53,  67,   0,  74,  75,  77,  78,  79,  80,   0,
   0,   0,  68,  81,   0,  85,   0,  92,  93,  95,
  96,  97,   0,  86,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  87,  88,   0,   0,   0,  30,
  34,  31,  18,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,  44,  48,  45,   0,  57,
  61,  58,   0,   0,   0,  72,  76,  73,   0,   0,
   0,   0,  90,  94,  91,   0,  27,  28,  41,  42,
  54,  55,  69,  70,  82,  83, 126, 127, 130,   0,
  21,  23,  24, 108, 109, 110, 111,  29,   0,   0,
   0,   0,   0,   0,   0,   0, 106, 107,   0,   0,
   0,   0,   0,   0,   0,  43,   0,  56,   0,   0,
   0,   0,  71,   0,   0,   0,   0,  89,   0,  20,
  22,  98,  99,   0, 101,   0,   0, 102,   0,   0,
 113,   0,   0, 114, 115, 117, 116, 118, 122, 119,
 121, 120, 124, 125, 112,   0, 123,   0,   0,   0,
   0,   0, 105,   0, 132,  84, 100,   0,   0,   0,
 104,   0,   0, 134, 103, 131,   0, 133 };
# define YYFLAG -1000
# define YYERROR goto yy2errlab
# define YYACCEPT return(0)
# define YYABORT return(1)

// Funktionsdefinitionen
void yy2error (const char *, ...);
void yy2error (enum ErrCode, ...);
int yy2lex (void);

/*	parser for yacc output	*/

#if defined(YYDEBUG)
int yy2debug = 0; /* 1 for debugging */
#endif

YYSTYPE *yy2v; /* where the values are stored */
int yy2char = -1; /* current input token number */
int yy2nerrs = 0;  /* number of errors */
short yy2errflag = 0;  /* error recovery flag */

int yy2parse(void) {

	short yy2s[YYMAXDEPTH];
	short yy2j, yy2m;
	register YYSTYPE *yy2pvt;
	register short yy2state, *yy2ps, yy2n;
	register YYSTYPE *yy2pv;
	register short *yy2xi;

	yy2state = 0;
	yy2char = -1;
	yy2nerrs = 0;
	yy2errflag = 0;
	yy2ps= &yy2s[0] - 1;
	yy2pv= &yy2v[-1];

 yy2stack:    /* put a state and value onto the stack */

#if defined(YYDEBUG)
	if( yy2debug  ) printf( "state %d, char 0%o\n", yy2state, yy2char );
#endif
		if( ++yy2ps> &yy2s[YYMAXDEPTH] ) { yy2error( "yacc stack overflow" ); return(1); }
		*yy2ps = yy2state;
		++yy2pv;
		*yy2pv = (*pyy2val);	

 yy2newstate:

	yy2n = yy2pact[yy2state];

	if( yy2n<= YYFLAG ) goto yy2default; /* simple state */

	if( yy2char<0 ) if( (yy2char=yy2lex())<0 ) yy2char=0;
	if( (yy2n += yy2char)<0 || yy2n >= YYLAST ) goto yy2default;

	if( yy2chk[ yy2n=yy2act[ yy2n ] ] == yy2char ){ /* valid shift */
		yy2char = -1;
		(*pyy2val) = (*pyy2lval);
		yy2state = yy2n;
		if( yy2errflag > 0 ) --yy2errflag;
		goto yy2stack;
		}

 yy2default:
	/* default state action */

	if( (yy2n=yy2def[yy2state]) == -2 ) {
		if( yy2char<0 ) if( (yy2char=yy2lex())<0 ) yy2char = 0;
		/* look through exception table */

		for( yy2xi=yy2exca; (*yy2xi!= (-1)) || (yy2xi[1]!=yy2state) ; yy2xi += 2 ) ; /* VOID */

		while( *(yy2xi+=2) >= 0 ){
			if( *yy2xi == yy2char ) break;
			}
		if( (yy2n = yy2xi[1]) < 0 ) return(0);   /* accept */
		}

	if( yy2n == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yy2errflag ){

		case 0:   /* brand new error */

			yy2error( "syntax error" );
		yy2errlab:
			++yy2nerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yy2errflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yy2ps >= yy2s ) {
			   yy2n = yy2pact[*yy2ps] + YYERRCODE;
			   if( yy2n>= 0 && yy2n < YYLAST && yy2chk[yy2act[yy2n]] == YYERRCODE ){
			      yy2state = yy2act[yy2n];  /* simulate a shift of "error" */
			      goto yy2stack;
			      }
			   yy2n = yy2pact[*yy2ps];

			   /* the current yy2ps has no shift onn "error", pop stack */

#if defined (YYDEBUG)
			   if( yy2debug ) printf( "error recovery pops state %d, uncovers %d\n", *yy2ps, yy2ps[-1] );
#endif
			   --yy2ps;
			   --yy2pv;
			   }

			/* there is no state on the stack with an error shift ... abort */

	yy2abort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#if defined(YYDEBUG)
			if( yy2debug ) printf( "error recovery discards char %d\n", yy2char );
#endif

			if( yy2char == 0 ) goto yy2abort; /* don't discard EOF, quit */
			yy2char = -1;
			goto yy2newstate;   /* try again in the same state */

			}

		}

	/* reduction by production yy2n */

#if defined(YYDEBUG)
		if( yy2debug ) printf("reduce %d\n",yy2n);
#endif
		yy2ps -= yy2r2[yy2n];
		yy2pvt = yy2pv;
		yy2pv -= yy2r2[yy2n];
		yy2m=yy2n;
			/* consult goto table to find next state */
		yy2n = yy2r1[yy2n];
		yy2j = yy2pgo[yy2n] + *yy2ps + 1;
		if( yy2j>=YYLAST || yy2chk[ yy2state = yy2act[yy2j] ] != -yy2n ) yy2state = yy2act[yy2pgo[yy2n]];
		App :: Exec (ExecWhileEvent);
		switch(yy2m){
			
case 1:
#line 152 "visidly.y"
{
			ResetIdents();
		} break;
case 4:
#line 164 "visidly.y"
{	
		char *pView = yy2pvt[-1].StringToken();
		
			if (!pView) {
				yy2error (EC_NOMEMORY);
				YYABORT;
			}
			strncpy (chViewName, pView, SIGHTNAMESIZE);
			chViewName[SIGHTNAMESIZE] = '\0';

		// sichtspezifische MerkmalsCodes rücksetzen
			s_lLegMCode = -1L;
			
		// Sichtnamen ausgeben
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				if (fImpView)
					g_pIS -> SetViewName (pView);
				else
					g_pIS -> SetViewName ("");
			}
			delete pView;

		// eingelesene Identifikatoren rücksetzen
			ResetIdents();
		} break;
case 5:
#line 191 "visidly.y"
{	
			ResString DefView (ResID (IDS_DEFAULTVIEW, &g_pTE -> RF()), SIGHTNAMESIZE+1);
	
				if (fImpView && strcmp (chViewName, DefView)) {
				// die Welt informieren, daß eine neue Ansicht generiert wurde
				VIEWCREATED VC;

					INITSTRUCT (VC, VIEWCREATED);
					VC.m_pTarget = "";
					VC.m_pNewName = chViewName;
					DEXN_SightCreated(VC);

#if defined(DEX_GetDefaultView)
				// außerdem evtl. als AnfangsAnsicht setzen
					if (fSetStandardView && !DEX_GetDefaultView(NULL)) 
						DEX_SetDefaultView (chViewName);
#endif // DEX_GetDefaultView
				}

				chViewName[0] = '\0';
				fImpView = false;
				fSetStandardView = false;
			} break;
case 6:
#line 218 "visidly.y"
{
		char *pView = yy2pvt[-0].StringToken();
		CImpView *pV = NULL;
				
			YYSTACK (pView, YYString);
			if (g_pVT == NULL || 
			    ((pV = g_pVT -> FFindItem (pView)) && pV -> Import()))
			{
				fImpView = true;
			} else 
				fImpView = false;

			fSetStandardView = false;
		} break;
case 7:
#line 233 "visidly.y"
{
		char *pView = yy2pvt[-0].StringToken();
		CImpView *pV = NULL;
				
			YYSTACK (pView, YYString);
			if (g_pVT == NULL || 
			    ((pV = g_pVT -> FFindItem (pView)) && pV -> Import()))
			{
				fImpView = true;
				fSetStandardView = true;
			} else {
				fImpView = false;
				fSetStandardView = false;
			}
		} break;
case 8:
#line 249 "visidly.y"
{
		ResString DefView (ResID (IDS_DEFAULTVIEW, &g_pTE -> RF()), SIGHTNAMESIZE+1);
		char *pView = new char [SIGHTNAMESIZE+1];
		
			if (pView) strcpy (pView, DefView.Addr());					   

			YYSTACK (pView, YYString);

			if (g_fImpDefView) fImpView = true;
			else 		   fImpView = false;

			fSetStandardView = false;
		} break;
case 9:
#line 265 "visidly.y"
{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}
		} break;
case 10:
#line 272 "visidly.y"
{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}
		} break;
case 18:
#line 290 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefTag = true;
			else
				fTag = true;
		} break;
case 19:
#line 299 "visidly.y"
{
			InitDefaultAttributes();
			fDefaultAttributes = true;
		} break;
case 20:
#line 304 "visidly.y"
{	fDefaultAttributes = false;	} break;
case 25:
#line 318 "visidly.y"
{
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, *(Dimension *)&szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor);

			if (chViewName[0] != '\0' && fImpView)
				AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &PVI, lUpperScale, lLowerScale);
			cnIdents++;
		} break;
case 26:
#line 328 "visidly.y"
{
			cnIdents++;

		// Merkmal wegschreiben (yy2pvt[-1].LongToken().intnum ist Objektnummer)
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
                
                long lONr = yy2pvt[-1].LongToken();
                
                	if (lONr == -1) break;	// Objekt nicht gefunden
                	
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, (Dimension &)szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor);

			AddVItoObject (chViewName, lONr, &PVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 27:
#line 350 "visidly.y"
{	
		long lIdent = yy2pvt[-1].LongToken();

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;
			InitAttributes (lIdent, VT_Punkt); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 28:
#line 371 "visidly.y"
{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = yy2pvt[-1].StringToken();
		long *plONr = new long (FindObjekt (pUIdent, g_lUIMCode, OGPunkt));

			s_lIdent = -1L;
			s_lObject = plONr ? *plONr : -1L;

			YYSTACK (plONr, YYLong);
			
			if (s_lObject != -1L) {
			long lIdent = DEX_GetObjIdent (s_lObject);
			short iOTyp = DEX_GetObjectType (s_lObject);
			
				InitAttributes (lIdent, (VisType)OTypToVTyp (iOTyp));
			}
			
			if (g_pIS) g_pIS -> SetHandledItem (pUIdent);
			DELETE_OBJ (pUIdent);
			s_iDrawResult = DO_UnChanged;
		} break;
case 39:
#line 413 "visidly.y"
{
		LVisInfo LVI (iType, iPriority, 
			      (Color &)colMainColor, 
			      iWidth, chTypeString);

			if (chViewName[0] != '\0' && fImpView) 
				AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &LVI, lUpperScale, lLowerScale);
			cnIdents++;
		} break;
case 40:
#line 423 "visidly.y"
{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = yy2pvt[-1].LongToken();
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		LVisInfo LVI (iType, iPriority, 
			      (Color &)colMainColor, 
			      iWidth, chTypeString);

			AddVItoObject (chViewName, lONr, &LVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 41:
#line 444 "visidly.y"
{
		long lIdent = yy2pvt[-1].LongToken();

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Linie); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 42:
#line 466 "visidly.y"
{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = yy2pvt[-1].StringToken();
		long *plONr = new long (FindObjekt (pUIdent, g_lUIMCode, OGLinie));

			s_lIdent = -1L;
			s_lObject = plONr ? *plONr : -1L;

			YYSTACK (plONr, YYLong);

			if (s_lObject != -1L) {
			long lIdent = DEX_GetObjIdent (s_lObject);
			short iOTyp = DEX_GetObjectType (s_lObject);
			
				InitAttributes (lIdent, (VisType)OTypToVTyp (iOTyp));
			}
			
			if (g_pIS) g_pIS -> SetHandledItem (pUIdent);
			DELETE_OBJ (pUIdent);
			s_iDrawResult = DO_UnChanged;
		} break;
case 52:
#line 508 "visidly.y"
{
		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor,
			      (Color &)colFillColor, iBkConture, chTypeString);

			if (chViewName[0] != '\0' && fImpView) 
				AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &FVI, lUpperScale, lLowerScale);
			cnIdents++;
		} break;
case 53:
#line 518 "visidly.y"
{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = yy2pvt[-1].LongToken();
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor,
			      (Color &)colFillColor, iBkConture, chTypeString);

			AddVItoObject (chViewName, lONr, &FVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 54:
#line 539 "visidly.y"
{	
		long lIdent = yy2pvt[-1].LongToken();

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Flaeche); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 55:
#line 561 "visidly.y"
{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = yy2pvt[-1].StringToken();
		long *plONr = new long (FindObjekt (pUIdent, g_lUIMCode, OGFlaeche));

			s_lIdent = -1L;
			s_lObject = plONr ? *plONr : -1L;

			YYSTACK (plONr, YYLong);

			if (s_lObject != -1L) {
			long lIdent = DEX_GetObjIdent (s_lObject);
			short iOTyp = DEX_GetObjectType (s_lObject);
			
				InitAttributes (lIdent, (VisType)OTypToVTyp (iOTyp));
			}
			
			if (g_pIS) g_pIS -> SetHandledItem (pUIdent);
			DELETE_OBJ (pUIdent);
			s_iDrawResult = DO_UnChanged;
		} break;
case 67:
#line 607 "visidly.y"
{
		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString);

			if (chViewName[0] != '\0' && fImpView)
				AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &TVI, lUpperScale, lLowerScale);
			cnIdents++;
		} break;
case 68:
#line 617 "visidly.y"
{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = yy2pvt[-1].LongToken();
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString);

			AddVItoObject (chViewName, lONr, &TVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 69:
#line 638 "visidly.y"
{	
		long lIdent = yy2pvt[-1].LongToken();

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Text); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 70:
#line 660 "visidly.y"
{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = yy2pvt[-1].StringToken();
		long *plONr = new long (FindObjekt (pUIdent, g_lUIMCode, OGText));

			s_lIdent = -1L;
			s_lObject = plONr ? *plONr : -1L;

			YYSTACK (plONr, YYLong);

			if (s_lObject != -1L) {
			long lIdent = DEX_GetObjIdent (s_lObject);
			short iOTyp = DEX_GetObjectType (s_lObject);
			
				InitAttributes (lIdent, (VisType)OTypToVTyp (iOTyp));
			}
			
			if (g_pIS) g_pIS -> SetHandledItem (pUIdent);
			DELETE_OBJ (pUIdent);
			s_iDrawResult = DO_UnChanged;
		} break;
case 81:
#line 704 "visidly.y"
{
			if (g_fImpViewFeatures && chViewName[0] != '\0' && fImpView) 
			{
			char *pMWert = yy2pvt[-0].StringToken();
			
				WriteTextMerkmal (TT_Sicht, (long)chViewName,
						  yy2pvt[-1].LongToken(), pMWert);
				DELETE_OBJ (pMWert);
			}
		} break;
case 82:
#line 717 "visidly.y"
{
		long *plMCode = new long (yy2pvt[-1].LongToken());
		
			YYSTACK (plMCode, YYLong);
		} break;
case 83:
#line 723 "visidly.y"
{
		// Eintrag im Header gegeben
		char *pKey = yy2pvt[-1].StringToken();
		HeaderEntryX HE (pKey);
		long lMCode = HE.EntryLong (-1L);

			if (fImpView && lMCode == -1L) {
			// Eintrag existiert nicht
			char pBuffer[20];

				lMCode = DEX_GetUniqueSysMCode();	// MerkmalsCode holen
				HE.SetEntryText (ltoa (lMCode, pBuffer, 10));
				HE.WriteBack ();

			// in PBD eintragen
				SaveMCodeInPbd (lMCode, chViewName, pKey);
			}
			DELETE_OBJ (pKey);

		// Ergebnis setzen
		long *plMCode = new long (lMCode);
		
			YYSTACK (plMCode, YYLong);
		} break;
case 84:
#line 751 "visidly.y"
{
		char *pMWert = yy2pvt[-2].StringToken();
		
			YYSTACK (pMWert, YYString);
		} break;
case 85:
#line 760 "visidly.y"
{
			if (chViewName[0] == '\0' || !fImpView)
				break;

		long lIdent = yy2pvt[-1].LongToken();
		
			VisInfo VI (iType, iPriority, 
				    (Color &)colMainColor, chTypeString);

			AddIDtoSight (chViewName, lIdent, &VI, lUpperScale, lLowerScale, fBits);
			cnIdents++;
		} break;
case 86:
#line 773 "visidly.y"
{
			if (!g_fImpObjVis || chViewName[0] == '\0' || !fImpView)
				break;

		long lONr = yy2pvt[-1].LongToken();
		
			if (lONr == -1L) break;	// Objekt existiert nicht
			
		short iOTyp = DEX_GetObjectType (lONr);
		
			switch ((VisType)OTypToVTyp (iOTyp)) {
			case VT_Punkt: {
				PVisInfo PVI (iType, iPriority,
					      (Color &)colMainColor, 
					      (Dimension &)szSize,
					      chTypeString, iPunktRot, 
					      (Color &)colFillColor);

					AddVItoObject (chViewName, lONr, &PVI, s_iDrawResult, cbVisModule);
				}
				break;

			case VT_Linie: {
				LVisInfo LVI (iType, iPriority, 
					      (Color &)colMainColor, iWidth,
					      chTypeString);

					AddVItoObject (chViewName, lONr, &LVI, s_iDrawResult, cbVisModule);
				}
				break;

			case VT_Flaeche: {
				FVisInfo FVI ((iType + 100*iWidth) | iOpaque, 
					      iPriority, 
				              (Color &)colMainColor,
					      (Color &)colFillColor,
					      iBkConture, chTypeString);

					AddVItoObject (chViewName, lONr, &FVI, s_iDrawResult, cbVisModule);
				}
				break;

			case VT_Text: {
				TVisInfo TVI (iType, iPriority, 
					      (Color &)colMainColor,
					      (Dimension &)szSize, iTextTyp, 
					      iTextRot, chTypeString);

					AddVItoObject (chViewName, lONr, &TVI, s_iDrawResult, cbVisModule);
				}
				break;

        		default:
			case VT_Default:
				break;
			}
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
			cnIdents++;
		} break;
case 87:
#line 837 "visidly.y"
{
		long lIdent = yy2pvt[-1].LongToken();

			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			s_iDrawResult = DO_UnChanged;
			InitAttributes (lIdent, VT_Default);
			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			
		} break;
case 88:
#line 853 "visidly.y"
{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = yy2pvt[-1].StringToken();
		long *plONr = new long (FindObjekt (pUIdent, g_lUIMCode, OGUnknown));

			s_lIdent = -1L;
			s_lObject = plONr ? *plONr : -1L;

			if (s_lObject != -1L) {
			long lIdent = DEX_GetObjIdent (s_lObject);
			short iOTyp = DEX_GetObjectType (s_lObject);
			
				InitAttributes (lIdent, (VisType)OTypToVTyp (iOTyp));
			}

			if (g_pIS) g_pIS -> SetHandledItem (pUIdent);
			YYSTACK (plONr, YYLong);
			DELETE_OBJ (pUIdent);
			s_iDrawResult = DO_UnChanged;
		} break;
case 98:
#line 897 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefPriority = (short)yy2pvt[-1].LongToken();
			else {
				iPriority = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_PriorityChanged;
			}
		} break;
case 99:
#line 906 "visidly.y"
{
			if (fDefaultAttributes) {
				iDefType = (short)yy2pvt[-1].LongToken();
				chDefTypeString[0] = '\0';
			} else {
				iType = (short)yy2pvt[-1].LongToken();
				chTypeString[0] = '\0';
				s_iDrawResult |= DO_StyleChanged;
			}
		} break;
case 100:
#line 917 "visidly.y"
{
			if (fDefaultAttributes) {
				iDefType = (short)yy2pvt[-3].LongToken();
				if (DEX_GetDBVersion() >= VERSION05000005) {
				char *pStr = yy2pvt[-1].StringToken();
									
					if (!pStr) {
						yy2error (EC_NOMEMORY);
						YYABORT;
					}
					strncpy (chDefTypeString, pStr, VISNAMESIZE);
					chDefTypeString[VISNAMESIZE] = '\0';
					delete pStr;
				} else
					chDefTypeString[0] = '\0';
			} else {
				iType = (short)yy2pvt[-3].LongToken();
				if (DEX_GetDBVersion() >= VERSION05000005) {
				char *pStr = yy2pvt[-1].StringToken();
									
					if (!pStr) {
						yy2error (EC_NOMEMORY);
						YYABORT;
					}
					strncpy (chTypeString, pStr, VISNAMESIZE);
					chTypeString[VISNAMESIZE] = '\0';
					delete pStr;

					s_iDrawResult |= DO_NameChanged;
				} else
					chTypeString[0] = '\0';

				s_iDrawResult |= DO_StyleChanged;
			}
		} break;
case 101:
#line 953 "visidly.y"
{
		COLORREF C = (COLORREF)yy2pvt[-1].LongToken();
		
			if (g_fImpHSB) {
			Color Col = HSBtoRGB ((long &)C);

				C = (COLORREF &)Col;
			}
			if (fDefaultAttributes)	
				colDefMainColor = C;
			else {
				colMainColor = C;
				s_iDrawResult |= DO_PrimColorChanged;
			}
		} break;
case 102:
#line 969 "visidly.y"
{
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefMainColor = (COLORREF &)Col;
			else {
				colMainColor = (COLORREF &)Col;
				s_iDrawResult |= DO_PrimColorChanged;
			}
		} break;
case 103:
#line 980 "visidly.y"
{
		char *pStr = new char [YYLMAX];
		
			if (!pStr) break;
			*pStr = '%';
			ltoa (yy2pvt[-1].LongToken(), pStr+1, 10);

			cbVisModule[0] = yy2pvt[-4].StringToken();
			cbVisModule[1] = pStr; 
			s_iDrawResult |= DT_WillDrawComplete;
		} break;
case 104:
#line 992 "visidly.y"
{
			cbVisModule[0] = yy2pvt[-3].StringToken();
			cbVisModule[1] = yy2pvt[-1].StringToken(); 
			s_iDrawResult |= DT_WillDrawComplete;
		} break;
case 105:
#line 998 "visidly.y"
{
			if (chViewName[0] == '\0' || !fImpView) 
				break;
				
			if (!fDefaultAttributes && g_fImpLegInfo) {	// nur für konkrete Sicht
			char *pLegInfo = yy2pvt[-1].StringToken();
			
				if (s_lIdent != -1L)
					AddLegInfoToIdent (chViewName, s_lIdent, pLegInfo, !IsFirstIdent(s_lIdent));

				if (s_lObject != -1L)
					AddLegInfoToObject (chViewName, s_lObject, pLegInfo);
				DELETE_OBJ (pLegInfo);
			}
		} break;
case 106:
#line 1014 "visidly.y"
{
			lUpperScale = yy2pvt[-0].LongToken();
			s_iDrawResult |= DO_OthersChanged;
		} break;
case 107:
#line 1019 "visidly.y"
{
			lLowerScale = yy2pvt[-0].LongToken();
			s_iDrawResult |= DO_OthersChanged;
		} break;
case 112:
#line 1035 "visidly.y"
{	
		long lSize = yy2pvt[-1].LongToken();

			if (fDefaultAttributes) {
				szDefSize.cx = short(LOWORD(lSize));
				szDefSize.cy = short(HIWORD(lSize));
			} else {
				szSize.cx = short(LOWORD(lSize));
				szSize.cy = short(HIWORD(lSize));
				s_iDrawResult |= DO_SizeChanged;
			}
		} break;
case 113:
#line 1051 "visidly.y"
{
		long lSize = yy2pvt[-1].LongToken();
		
			if (fDefaultAttributes) {
				szDefSize.cx = short(HIWORD(lSize));
				szDefSize.cy = short(LOWORD(lSize));
			} else {
				szSize.cx = short(HIWORD(lSize));
				szSize.cy = short(LOWORD(lSize));
				s_iDrawResult |= DO_SizeChanged;
	 		}
		} break;
case 114:
#line 1067 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefPunktRot = (short)yy2pvt[-1].LongToken();	
			else {
				iPunktRot = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 115:
#line 1076 "visidly.y"
{	
		COLORREF C = (COLORREF)yy2pvt[-1].LongToken();
		
			if (g_fImpHSB) {
			Color Col = HSBtoRGB ((long &)C);

				C = (COLORREF &)Col;
			}
			if (fDefaultAttributes)	
				colDefFillColor = C;
			else {
				colFillColor = C;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 116:
#line 1092 "visidly.y"
{	
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 117:
#line 1103 "visidly.y"
{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 118:
#line 1115 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefWidth = (short)yy2pvt[-1].LongToken();	
			else {
				iWidth = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_SizeChanged;
			}
		} break;
case 119:
#line 1127 "visidly.y"
{	
		COLORREF C = (COLORREF)yy2pvt[-1].LongToken();
		
			if (g_fImpHSB) {
			Color Col = HSBtoRGB ((long &)C);

				C = (COLORREF &)Col;
			}
			if (fDefaultAttributes)	
				colDefFillColor = C;
			else {
				colFillColor = C;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 120:
#line 1143 "visidly.y"
{	
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 121:
#line 1154 "visidly.y"
{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 122:
#line 1166 "visidly.y"
{
			if (fDefaultAttributes)	
				iDefOpaque = (short)yy2pvt[-1].LongToken() & BMOpaque;
			else {
			long lTok = yy2pvt[-1].LongToken();
			
				iOpaque = (short)(lTok & BMOpaque);
				iBkConture = (short)(lTok & BMBkConture);
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 123:
#line 1181 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefBits = (short)yy2pvt[-1].LongToken();
			else {
				fBits = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 124:
#line 1193 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefTextTyp = (short)yy2pvt[-1].LongToken();	
			else {
				iTextTyp = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 125:
#line 1202 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefTextRot = (short)yy2pvt[-1].LongToken();	
			else {
				iTextRot = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 126:
#line 1214 "visidly.y"
{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = yy2pvt[-0].LongToken();
			else
				lIdent = MakeHex (yy2pvt[-0].LongToken());

			if (fFirstIdent) fFirstIdent = false;

		long *plIdent = new long (lIdent);
		
		// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
		// importiert werden soll (OKS hat Vorrang)
		char cbBuffer[32];	// Ident als OKS interpretieren und testen, ob zugehöriger Ident 
							// verwendet ist
		long lOKSIdent = 0L;

			ultoa (lIdent, cbBuffer, g_fDecIdent ? 10 : 16);
		
		HRESULT hr = IdentFromClassX (cbBuffer, (ULONG *)&lOKSIdent);
		
			if (S_OK == hr && DEX_isIdentUsed(lOKSIdent)) 
				*plIdent = lOKSIdent;

			YYSTACK (plIdent, YYLong);
		} break;
case 127:
#line 1242 "visidly.y"
{	
		long *plIdent = new long (yy2pvt[-0].LongToken());
		
			if (g_fDecIdent && !fFirstIdent) {
				yy2error ("Inkonsistente Identifikator-Zahlenbasis.");
				YYABORT;
			}
			if (fFirstIdent) {
				fFirstIdent = false;
				g_fDecIdent = false;		// force Hex
			}

		// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
		// importiert werden soll (OKS hat Vorrang)
		char cbBuffer[32];	// Ident als OKS interpretieren und testen, ob zugehöriger Ident 
							// verwendet ist
		long lOKSIdent = 0L;

			ultoa (*plIdent, cbBuffer, 16);
		
		HRESULT hr = IdentFromClassX (cbBuffer, (ULONG *)&lOKSIdent);
			
			if (S_OK == hr && DEX_isIdentUsed(lOKSIdent)) 
				*plIdent = lOKSIdent;

			YYSTACK (plIdent, YYLong);
		} break;
case 128:
#line 1270 "visidly.y"
{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = yy2pvt[-0].LongToken();
			else
				lIdent = MakeHex (yy2pvt[-0].LongToken());

			if (fFirstIdent) fFirstIdent = false;

		long *plIdent = new long (lIdent);
		
		// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
		// importiert werden soll (OKS hat Vorrang)
		char cbBuffer[32];	// Ident als OKS interpretieren und testen, ob zugehöriger Ident 
							// verwendet ist
		long lOKSIdent = 0L;

			ultoa (lIdent, cbBuffer, g_fDecIdent ? 10 : 16);
		
		HRESULT hr = IdentFromClassX (cbBuffer, (ULONG *)&lOKSIdent);
		
			if (S_OK == hr && DEX_isIdentUsed(lOKSIdent)) 
				*plIdent = lOKSIdent;

			YYSTACK (plIdent, YYLong);
		} break;
case 129:
#line 1298 "visidly.y"
{
		long *plIdent = new long (yy2pvt[-0].LongToken());
		
			if (g_fDecIdent && !fFirstIdent) {
				yy2error ("Inkonsistente Identifikator-Zahlenbasis.");
				YYABORT;
			}
			if (fFirstIdent) {
				fFirstIdent = false;
				g_fDecIdent = false;		// force Hex
			}

		// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
		// importiert werden soll (OKS hat Vorrang)
		char cbBuffer[32];	// Ident als OKS interpretieren und testen, ob zugehöriger Ident 
							// verwendet ist
		long lOKSIdent = 0L;

			ultoa (*plIdent, cbBuffer, 16);
		
		HRESULT hr = IdentFromClassX (cbBuffer, (ULONG *)&lOKSIdent);
			
			if (S_OK == hr && DEX_isIdentUsed(lOKSIdent)) 
				*plIdent = lOKSIdent;

			YYSTACK (plIdent, YYLong);
		} break;
case 130:
#line 1326 "visidly.y"
{
		char *pOKS = yy2pvt[-0].StringToken();
		long *plIdent = new long(0);
		HRESULT hr = IdentFromClassX (pOKS, (ULONG *)plIdent, true);	// ggf. neu erzeugen

			if (FAILED(hr)) {
				yy2error("Kann Objektklassenschlüssel nicht zuordnen.");
				YYABORT;
			}
			YYSTACK (plIdent, YYLong);

			if (fFirstIdent) {
				fFirstIdent = false;
				g_fDecIdent = false;		// force Hex
			}
		} break;
case 131:
#line 1345 "visidly.y"
{
		short lHigh = short(yy2pvt[-1].LongToken());
		short lLow = short(yy2pvt[-3].LongToken());
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		} break;
case 132:
#line 1353 "visidly.y"
{
		short lHigh = short(yy2pvt[-0].LongToken());
		short lLow = short(yy2pvt[-2].LongToken());
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		} break;
case 133:
#line 1363 "visidly.y"
{
		long lHue = yy2pvt[-1].LongToken();
		long lSat = yy2pvt[-5].LongToken();
		long lBright = yy2pvt[-3].LongToken();
		long *plLong = new long (HSB((BYTE)lSat, (BYTE)lBright, (WORD)lHue));
		
			YYSTACK (plLong, YYLong);
		} break;
case 134:
#line 1372 "visidly.y"
{
		long lHue = yy2pvt[-0].LongToken();
		long lSat = yy2pvt[-4].LongToken();
		long lBright = yy2pvt[-2].LongToken();
		long *plLong = new long (HSB((BYTE)lSat, (BYTE)lBright, (WORD)lHue));
		
			YYSTACK (plLong, YYLong);
		} break;
		}
		(*pyy2val) = yy2pv[1];
		goto yy2stack;  /* stack new state and value */

	}



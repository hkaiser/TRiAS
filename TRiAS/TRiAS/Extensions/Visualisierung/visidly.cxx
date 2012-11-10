
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

#include "LegendMCodes.h"

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
static short iDefType, iType;			// DarstellungsArt
static char chDefTypeString[VISNAMESIZE+1], chTypeString[VISNAMESIZE+1];
static char cbDefGeometry[VISNAMESIZE+1], cbGeometry[VISNAMESIZE+1];
static COLORREF colDefMainColor, colMainColor;
static long lDefUpperScale, lUpperScale; 
static long lDefLowerScale, lLowerScale;
static bool fDefLocatable, fLocatable;
static bool fDefVisible, fVisible;
static char g_cbLegInfo[2048];			// evtl. LegendenInfo

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

static short cnIdents = 0;			// Zähler der IdentSätze
static short s_iDrawResult = 0;		// hier wird vermerkt, was geändert wurde

static long s_lIdent = -1L;			// bearbeiteter Identifikator
static long s_lObject = -1L;		// bearbeitetes Objekt
static long s_lLegVMCode = -1L;
static long s_lLegMCode = -1L;

// ImportOptionen -------------------------------------------------------------
extern bool g_fImpHSB;				// Eingabe als HSB interpretieren
extern bool g_fImpDefView;			// StandardSicht importieren
extern bool g_fImpObjVis;			// Objektvisualisierung importieren
extern bool g_fImpViewFeatures;		// Sichtmerkmale importieren
extern bool g_fImpLegInfo;			// Legende importieren
extern bool g_fImpExistendOnly;		// nur existierende Idents importieren

extern bool g_fDecIdent;

extern long g_lUIMCode;				// MerkmalsCode des Unique Idents
extern CStatus *g_pIS;				// StatusFenster
extern CImpViewTree *g_pVT;			// Baum, der alle Sichten enthält
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
#define T_GEOMETRY 260
#define T_NUMBER 261
#define T_DEFAULT 262
#define T_PUNKT 263
#define T_LINIE 264
#define T_FLAECHE 265
#define T_TEXT 266
#define T_PRIORITY 267
#define T_TYPE 268
#define T_MCODE 269
#define T_DESC 270
#define T_TAGGED 271
#define T_MAINCOLOR 272
#define T_SIZE 273
#define T_WIDTH 274
#define T_FILLCOLOR 275
#define T_TTYP 276
#define T_TROT 277
#define T_MAINCOLORC 278
#define T_FILLCOLORC 279
#define T_IDENT 280
#define T_EQUAL 281
#define T_HEXNUMBER 282
#define T_TVCS 283
#define T_TLEGINFO 284
#define T_OKS 285
#define T_UPPERSCALE 286
#define T_LOWERSCALE 287
#define T_LOCATABLE 288
#define T_VISIBLE 289
#define T_TLEGHEAD 290
#define yy2clearin yy2char = -1
#define yy2errok yy2errflag = 0
extern int yy2char;
extern short yy2errflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE (*pyy2lval), (*pyy2val);
#define YYERRCODE 256

#line 1721 "visidly.y"


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
	g_cbLegInfo[0] = '\0';

	if (pVI != NULL) {	// Id existiert
		iType = pVI -> Style();
		strncpy (chTypeString, pVI -> VisName(), VISNAMESIZE);
		chTypeString[VISNAMESIZE] = '\0';
		strncpy (cbGeometry, pVI -> GeometryName(), VISNAMESIZE);
		cbGeometry[VISNAMESIZE] = '\0';
		fVisible = pVI -> IsVisible();
		fLocatable = pVI -> IsLocatable();
				
		iPriority = pVI -> Priority();
		(Color &)colMainColor = pVI -> PrimColor();

		if (iVTyp != VT_Default && pVI -> isA() != iVTyp) {
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
			fVisible = fDefVisible;
			fLocatable = fDefLocatable;
			lUpperScale = lDefUpperScale;
			lLowerScale = lDefLowerScale;
			return VT_Default;
		} 
		else switch (pVI -> isA()) {
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
		strncpy (cbGeometry, cbDefGeometry, VISNAMESIZE);
		cbGeometry[VISNAMESIZE] = '\0';
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
		fVisible = fDefVisible;
		fLocatable = fDefLocatable;
		lUpperScale = lDefUpperScale;
		lLowerScale = lDefLowerScale;
		return VT_Default;
	}
}

// Standardwerte voreinstellen ------------------------------------------------
static void InitDefaultAttributes (void) 
{
	iDefType = 0;
	chDefTypeString[0] = '\0';
	cbDefGeometry[0] = '\0';
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
	fDefLocatable = true;
	fDefVisible = true;
	lDefLowerScale = 0L;
	lDefUpperScale = 0L;
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


// wegspeichern der LegendenInfo an einem Identifikator -----------------------
bool AddLegInfoToIdent (char *pView, long lIdent, char *pLegInfo, bool fAppend)
{
	if (lIdent == -1) return false;
	
// MerkmalsCodes besorgen
//	if (s_lLegVMCode == -1L) 
	{
		s_lLegVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
				IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
		if (s_lLegVMCode == -1L)
			return false;		// Fehler
	}
//	if (s_lLegMCode == -1L) 
	{
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

		ReadTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, cbBuffer, sizeof(cbBuffer), pView);
		strcat (cbBuffer, pLegInfo);
		return WriteTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, cbBuffer, pView);
	}

// Merkmal vollständig neu schreiben
	return WriteTextMerkmal (TT_Identifikator, lIdent, s_lLegMCode, pLegInfo, pView);
}

// wegspeichern einer LegendenInfo an einem Objekt ----------------------------
bool AddLegInfoToObject (char *pView, long lONr, char *pLegInfo)
{
	if (lONr == -1) return false;
	
// MerkmalsCodes besorgen
//	if (s_lLegVMCode == -1L) 
	{
		s_lLegVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
				IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
		if (s_lLegVMCode == -1L)
			return false;		// Fehler
	}
//	if (s_lLegMCode == -1L) 
	{
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

		s_lLegMCode = GetObjMCodeView (pView, s_lLegVMCode, 
				ResID (IDS_LEGINFOKTEXT, &pE -> RF()), 
				ResID (IDS_LEGINFOLTEXT, &pE -> RF()), true, DEX_GetObjIdent(lONr));
		if (s_lLegMCode == -1L)
			return false;
	}

	return WriteTextMerkmal (TT_Objekt, lONr, s_lLegMCode, pLegInfo);
}

// Hinzufügen eines Identifikators zu einer Sicht -----------------------------
bool AddIDtoSight (char *chViewName, long lIdent, VisInfo *pVI, long lUpper, long lLower, short iTypes)
{
// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
// importiert werden soll (OKS hat Vorrang)
char cbBuffer[64];		// Ident als OKS interpretieren
long lOKSIdent = 0L;

	ultoa (lIdent, cbBuffer, g_fDecIdent ? 10 : 16);
	if (AddOKStoSight (chViewName, cbBuffer, pVI, lUpper, lLower, iTypes))
		return true;

// jetzt eigentlichen Import durchführen
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
	
bool iResult = DEX_ModIdentVisInfo (*pHVI) ? true : false;	// zu Sicht hinzufügen

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
 
///////////////////////////////////////////////////////////////////////////////
// Hinzufügen eines Objektklassenschlüssels zu einer Sicht 
typedef struct tagENUMPROJECTSDATA {
	HANDLEVISINFO *pHVI;
	long lUpper;
	long lLower;
	short isA;
	bool fFoundOne;
	LPCSTR pcOKS;
} ENUMPROJECTSDATA;

extern "C"
BOOL CALLBACK EnumProjects (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData)
{
ENUMPROJECTSDATA *pData = reinterpret_cast<ENUMPROJECTSDATA *>(dwData);

	TX_ASSERT(NULL != pData);

// Ident in diesem Projekt geben lassen
ULONG lIdent = 0L;
HANDLEVISINFO *pHVI = pData -> pHVI;

	if (S_OK != IdentFromClassX (hPr, pcClass, &lIdent, !g_fImpExistendOnly))		// ggf. neu erzeugen
		return TRUE;		// trotzdem weitermachen

	if (g_fImpExistendOnly && !DEX_isIdentUsed(lIdent))
		return TRUE;

	pHVI -> m_lIdent = lIdent;
	DEX_ModIdentVisInfo (*pHVI);	// zu Sicht hinzufügen

// evtl. maßstabsbezogen ein bzw. ausblenden
	if ((0 != pData -> lUpper || 0 != pData -> lLower) && VTDefault != pData -> isA) {
	IDENTSCALEDATA ISD;

		INITSTRUCT(ISD, IDENTSCALEDATA);
		ISD.pcView = pHVI -> m_pView;
		ISD.lIdent = lIdent;
		ISD.iVTyp = pData -> isA;
		ISD.lUpperScale = pData -> lUpper;
		ISD.lLowerScale = pData -> lLower;
		DEX_SetIdentScaleData(ISD);
	}

// evtl. LegendenInfo wegschreiben
	if ('\0' != g_cbLegInfo[0]) 
		AddLegInfoToIdent (pHVI -> m_pView, lIdent, g_cbLegInfo, !IsFirstIdent(lIdent));

	AddIdent (lIdent);

	pData -> fFoundOne = TRUE;	// wenigstens einen für diesen OKS gefunden
	return TRUE;				// immer weitermachen
}

extern "C"
BOOL CALLBACK EnumProjectsAll (HPROJECT hPr, BOOL fNotLast, UINT_PTR dwData)
{
ENUMPROJECTSDATA *pData = reinterpret_cast<ENUMPROJECTSDATA *>(dwData);

	TX_ASSERT(NULL != pData);

// Ident in diesem Projekt geben lassen
ULONG lIdent = 0L;
HANDLEVISINFO *pHVI = pData -> pHVI;

	if (FAILED(IdentFromClassX (hPr, pData->pcOKS, &lIdent, true)))		// ggf. neu erzeugen
		return TRUE;		// trotzdem weitermachen

	pHVI -> m_fFlags = DF_ForceImport;		// alle Idents Importieren
	pHVI -> m_lIdent = lIdent;
	DEX_ModIdentVisInfo (*pHVI);			// zu Sicht hinzufügen

// evtl. maßstabsbezogen ein bzw. ausblenden
	if ((0 != pData -> lUpper || 0 != pData -> lLower) && VTDefault != pData -> isA) {
	IDENTSCALEDATA ISD;

		INITSTRUCT(ISD, IDENTSCALEDATA);
		ISD.pcView = pHVI -> m_pView;
		ISD.lIdent = lIdent;
		ISD.iVTyp = pData -> isA;
		ISD.lUpperScale = pData -> lUpper;
		ISD.lLowerScale = pData -> lLower;
		DEX_SetIdentScaleData(ISD);
	}

// evtl. LegendenInfo wegschreiben
	if ('\0' != g_cbLegInfo[0]) 
		AddLegInfoToIdent (pHVI -> m_pView, lIdent, g_cbLegInfo, !IsFirstIdent(lIdent));

	AddIdent (lIdent);

	pData -> fFoundOne = TRUE;	// wenigstens einen für diesen OKS gefunden
	return TRUE;				// immer weitermachen
}

bool AddOKStoSight (char *chViewName, char *pOKS, VisInfo *pVI, long lUpper, long lLower, short iTypes)
{
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (pVI ? pVI -> isA() : VTDefault);

	if (pHVI == NULL) return false;
	
// Member setzen
	pHVI -> m_pView = chViewName;	// SichtNamen setzen

	if (pVI != NULL) {
		pVI -> CopyTo (*pHVI -> m_pVI);		// VISINFO setzen
		if (pVI -> isA() == VTDefault)
			((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = iTypes;	// sonstige IdentGeoTypen
	} else 
		((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = iTypes;		// sonstige IdentGeoTypen

// alle Idents (Projekte) dieses OKS enumerieren
ENUMPROJECTSDATA Data;

	Data.pHVI = pHVI;
	Data.lUpper = lUpper;
	Data.lLower = lLower;
	Data.isA = pVI -> isA();
	Data.fFoundOne = FALSE;

	if (g_fImpExistendOnly) {
	ENUMTEXTKEY ETK;

		ETK.eKey = pOKS;
		ETK.eFcn = (ENUMLONGKEYPROC)EnumProjects;
		ETK.ePtr = &Data; 
		DEX_EnumClassProjects (ETK);
	}
	else {
	ENUMNOKEYLONG ENK;

		Data.pcOKS = pOKS;
		ENK.eFcn = (ENUMNOKEYLONGPROC)EnumProjectsAll;
		ENK.ePtr = &Data;
		DEX_EnumDataSourceHandles(ENK);
	}

	dtHANDLEVISINFO (pHVI);
	return Data.fFoundOne;
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

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen einer Zwischenüberschrift zur Legende
bool AddLegendHeadLine (LPCSTR pcView, LPCSTR pcTextToAdd)
{
// zuerst ViewMCodes besorgen
	s_lLegVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
			IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
	if (s_lLegVMCode == -1L)
		return false;		// Fehler

CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

	s_lLegMCode = GetObjMCodeView (pcView, s_lLegVMCode, 
			ResID (IDS_LEGINFOKTEXT, &pE -> RF()), 
			ResID (IDS_LEGINFOLTEXT, &pE -> RF()), true, 0L);	// last param not used any more (#HK000806)
	if (s_lLegMCode == -1L)
		return false;

// jetzt existierende Headlines einlesen und die neue hinzufügen
CLegendMCodes MCodes (s_lLegMCode, chViewName);
INT_PTR lMCode = DEX_GetUniqueSysMCode();

	MCodes.ExtractMCodes();		// evtl. Fehler ignorieren
	if (WriteTextMerkmal (TT_Sicht, (INT_PTR)pcView, lMCode, pcTextToAdd)) {
		MCodes.AddMCode(lMCode);
		MCodes.WriteMCodes();
	}
	return true;
}



short yy2exca[] = {-1, 1,
	0, -1,
	-2, 0,
	};
#define YYNPROD 149
#define YYLAST 678
short yy2act[]={

 251,  73,  98, 153, 220, 118,   9, 220,  63,  64,
 279,  10, 205,  65,  74,  87, 100, 112, 113,  66,
 101, 231, 141, 220,  67,  68,  49,  69,  70,  71,
  72,  47,  62, 206,  52,  49,  22,  40,  41,  42,
  43, 298, 138,  44, 295,  48,  49,  50, 135, 132,
  51, 143,  49,  49,  48, 142,  50,  98, 293,  51,
 291, 289, 286, 281,  36,  48, 263,  50, 173, 257,
  51,  48,  48,  50,  50, 250,  51,  51, 246, 245,
 240, 238, 233, 228, 227, 226, 225, 218, 217,  62,
   5,   6, 261, 248, 229, 223, 207,  11, 150, 287,
 282, 209, 284, 109, 230, 224, 107, 204, 203, 202,
 201, 200, 199, 198, 111, 197, 196, 195, 194, 193,
 192, 123, 191,  92, 146,  96, 145, 144,  60, 119,
  54,   8,  93, 190, 117,  73, 185, 184,  83, 111,
 183, 296,  63,  64, 182, 178, 177,  65,  74,  87,
 100, 112, 113,  66, 101,  57, 176, 172,  67,  68,
 168,  69,  70,  71,  72, 167,  47, 219, 166, 126,
  49,  22,  40,  41,  42,  43,  85, 165,  44, 164,
 179, 163, 162, 161, 160, 159, 158, 157, 156,  48,
 155,  50, 154, 148,  51, 147, 292, 288, 255,  36,
 278,  86, 277,  73, 276, 106,  97,  97,  97, 275,
  63,  64, 180, 254, 274,  65, 273,  87, 100,  99,
 170,  66, 101, 272, 174, 221,  67,  68, 221,  69,
  70,  71,  72,  73, 126, 187, 242, 271, 270, 235,
  63,  64, 232, 188, 221,  65,  74, 269,  76, 268,
  75,  66,  77, 215, 186, 267,  67,  68,  73,  69,
  70,  71,  72, 266,  86,  63,  64, 169,  97, 265,
  65, 262,  87, 100,  99, 214,  66, 101, 212, 259,
 256,  67,  68, 253,  69,  70,  71,  72, 260, 247,
  73, 294,  58, 290, 285, 280, 264,  63,  64, 258,
 122, 299,  65,  74, 297,  76, 125,  75,  66,  77,
 252, 120, 215,  67,  68,  73,  69,  70,  71,  72,
 283,   3,  63,  64,   7, 222, 213,  65, 114,  90,
  82, 112, 113,  66, 214, 234, 236, 212,  67,  68,
  73,  69,  70,  71,  72, 241, 243,  63,  64, 151,
 128, 129,  65, 114,  55, 104, 112, 113,  66,  14,
 102, 103,  45,  67,  68, 121,  69,  70,  71,  72,
  73, 110,  80,  53, 105,  95,  91,  63,  64,  78,
  79,  81,  65,  61,  56, 213, 127, 211,  66, 115,
 116, 208, 149,  67,  68,  46,  69,  70,  71,  72,
  88,  89,  73, 130, 133, 136, 139,  12,   2,  63,
  64,  20,  19,  18,  65,  17,  87,  16,  15,  13,
  66, 152,  21,  39,  34,  67,  68,  31,  69,  70,
  71,  72,  28,  25,  32,  73, 131, 134, 137, 140,
  37,  29,  63,  64,  26,  23,  38,  65,  33,  30,
  27, 127,  24,  66,  35,   4,   1,   0,  67,  68,
   0,  69,  70,  71,  72,  73,   0,   0,  59,   0,
   0,   0,  63,  64,   0,   0,   0,  65,   0,  87,
   0,   0,   0,  66,   0,   0,   0,   0,  67,  68,
   0,  69,  70,  71,  72,  84,  84,  84,  94,  94,
  94, 108, 108, 108, 171,   0, 124, 124, 124,   0,
   0,   0,   0,   0, 175,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0, 181,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 189,   0,   0,   0,   0,   0,
  84,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  94,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 216,   0, 108,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
 124, 237,   0,   0,   0, 239,   0,   0,   0,   0,
   0, 244,   0,   0,   0,   0,   0,   0,   0, 249,
   0,   0,   0,   0,   0,   0,   0,   0, 210,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0, 210 };
short yy2pact[]={

-168,-1000,-168,-1000,   8,-251,-160,-1000,-1000,-1000,
-1000,-1000,-226, -91,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,   7,  30,  30,  30, 205, 205, 205,  -2,
  -2,  -2,  80,  80,  80,-265,   6, 175, 175, 175,
-208,-209,-215,-235,-206,   4,   3,   1, 134,-1000,
-1000, 132,-1000,-1000,-1000,-1000, -27,-268,-1000,-1000,
-1000,-1000,-1000, 131, 129, 127, 126, 125, 124, 123,
 122, 121, 120, 118, 116, 107, 104,  99,-1000,-1000,
-1000, 142,-268,-1000,-1000,-1000,-1000,  96,-1000,-1000,
-1000, -57,-268,-1000,-1000,-1000,-1000,-1000,-1000,  95,
  85,  84,-1000,-1000,-1000,  55,-268,-1000,-1000,-1000,
-1000,-1000,  83,  79,  76,-1000,-1000,-1000,  75,-265,
-1000, 110,-268,-1000,-1000,-1000,-1000,  72,-1000,-1000,
  -1,  -3,  -4,  -5,  -6,  -7,  -8, -10, -11, -12,
 -13, -14, -15, -16,-1000,-1000,-1000,-249,-161,-259,
-268,-1000,-1000,-1000,-173,-174, -17, -17,-162, -18,
-175,-176,-177,-178,-163, -19,-179, -33, -17,-268,
-1000,-1000,-180,-268,-1000,-1000,-181, -36, -17,-268,
-1000,-1000,-182,-183, -19,-164,-1000,-268,-1000,-1000,
-186,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-125,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000, 224, 154, 221,
-192, 255, 220, 230,-165,-1000,-1000,-1000,-1000,-1000,
 212,-195, 252, 210, 204, 196, 190,-1000, 188,-1000,
 179, 178, 164, 157,-1000, 155, 150, 145, 143,-1000,
 141,-1000,-1000,-1000,-1000,-247,-1000, 251,-198,-1000,
  63, -23,-1000, 250,-199,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000, -26,-1000, 138,
-200, 249,-201, 137,-1000,-203,-1000,-1000,-1000, 247,
-217,  82,-1000, 263,-220,-1000,-1000,-1000, 260,-1000 };
short yy2pgo[]={

   0, 456, 455, 134, 454, 395, 452, 450, 449, 448,
 446, 104, 167, 362, 468, 445, 444, 441, 440, 434,
 433, 432, 427, 424, 423, 422, 419, 359, 418, 417,
 415, 413, 412, 411, 408, 321, 407, 421, 392, 391,
 101, 387, 354, 384, 292, 128, 383, 372, 381, 138,
 176, 329, 376, 132, 375, 125, 355, 374, 106, 103,
 371, 311, 365, 121, 306 };

short yy2r1[]={
   0,   1,  34,  34,  36,  35,   2,   2,   2,  26,
  26,  27,  27,  27,  27,  27,  27,  27,  37,  38,
  28,  39,  39,  40,  40,  29,  29,  29,  15,   6,
  20,  42,  42,  42,  42,  43,  43,  44,  44,  44,
  44,  30,  30,  30,  16,   7,  21,  47,  47,  47,
  47,  48,  48,  49,  49,  49,  31,  31,  31,  17,
   8,  22,  51,  51,  51,  51,  52,  52,  53,  53,
  53,  53,  53,  32,  32,  32,  19,   9,  23,  56,
  56,  56,  56,  57,  57,  58,  58,  58,  58,  33,
  33,   4,   4,   3,  25,  25,  25,  18,  10,  24,
  61,  61,  61,  61,  62,  62,  63,  63,  63,  14,
  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,
  14,  14,  41,  41,  41,  41,  60,  45,  46,  46,
  46,  46,  50,  55,  55,  55,  54,  64,  59,  59,
  13,  13,  13,  13,   5,  11,  11,  12,  12 };

short yy2r2[]={
   0,   1,   1,   2,   0,   5,   2,   2,   2,   1,
   2,   1,   1,   1,   1,   1,   1,   1,   1,   0,
   5,   1,   2,   1,   1,   2,   2,   2,   3,   3,
   3,   3,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   2,   2,   3,   3,   3,   3,   2,   2,
   1,   1,   2,   1,   1,   1,   2,   2,   2,   3,
   3,   3,   3,   2,   2,   1,   1,   2,   1,   1,
   1,   1,   1,   2,   2,   2,   3,   3,   3,   3,
   2,   2,   1,   1,   2,   1,   1,   1,   1,   2,
   3,   3,   3,   5,   2,   2,   2,   2,   2,   2,
   3,   2,   2,   1,   1,   2,   1,   1,   1,   4,
   4,   6,   4,   4,   7,   6,   5,   3,   3,   3,
   3,   3,   1,   1,   1,   1,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   3,   3,   1,   1,   3,   5,   3,   7,   5 };

short yy2chk[]={
-1000,  -1, -34, -35,  -2, 258, 259, -35, 123, 257,
 262, 257, -36, -26, -27, -28, -29, -30, -31, -32,
 -33, -25, 262, -15,  -6, -20, -16,  -7, -21, -17,
  -8, -22, -19,  -9, -23,  -4, 290, -18, -10, -24,
 263, 264, 265, 266, 269, -13,  -5, 257, 280, 261,
 282, 285, 125, -27, 123, -42, -43, 125, -44, -14,
 -45, -46,  59, 267, 268, 272, 278, 283, 284, 286,
 287, 288, 289, 260, 273, 277, 275, 279, -42, -42,
 -47, -48, 125, -49, -14, -50,  59, 274, -47, -47,
 -51, -52, 125, -53, -14, -54, -55, -50,  59, 276,
 275, 279, -51, -51, -56, -57, 125, -58, -14, -59,
 -60,  59, 276, 277, 273, -56, -56,  -3, 270, 123,
 -61, -62, 125, -63, -14, -64,  59, 276, -61, -61,
 -13,  -5, 257, -13,  -5, 257, -13,  -5, 257, -13,
  -5, 257, 261, 257, 123, 123, 123,  61,  61, -38,
 125, -44, -37, 271,  61,  61,  61,  61,  61,  61,
  61,  61,  61,  61,  61,  61,  61,  61,  61, 125,
 -49, -37,  61, 125, -53, -37,  61,  61,  61, 125,
 -58, -37,  61,  61,  61,  61,  -3, 125, -63, -37,
  61, 123, 123, 123, 123, 123, 123, 123, 123, 123,
 123, 123, 123, 123, 123, 261, 282, 257, -39, -40,
 -14, -41, -45, -50, -55, -59, -37, 261, 261, -12,
  40, 261, -12, 257, 123, 261, 261, 261, 261, 257,
 -11,  40, 261, 261, -12, 272, -12, -37, 261, -37,
 261, -12, 272, -12, -37, 261, 261, -11, 257, -37,
 261, 125, -40,  59,  59,  44,  59, 261,  44,  59,
  58, 257,  59, 261,  44,  59,  59,  59,  59,  59,
  59,  59,  59,  59,  59,  59,  59,  59,  59, 257,
  44, 261,  37, 257, 125,  44, 261, 125,  59, 261,
  44, 261,  59, 261,  44, 261,  59,  41, 261,  41 };

short yy2def[]={
   0,  -2,   1,   2,   0,   0,   0,   3,   4,   6,
   8,   7,   0,   0,   9,  11,  12,  13,  14,  15,
  16,  17,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 142,
 143,   0,   5,  10,  19,  25,   0,  34,  35,  37,
  38,  39,  40,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  26,  27,
  41,   0,  50,  51,  53,  54,  55,   0,  42,  43,
  56,   0,  65,  66,  68,  69,  70,  71,  72,   0,
   0,   0,  57,  58,  73,   0,  82,  83,  85,  86,
  87,  88,   0,   0,   0,  74,  75,  89,   0,   0,
  94,   0, 103, 104, 106, 107, 108,   0,  95,  96,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  97,  98,  99,   0,   0,   0,
  32,  36,  33,  18,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  48,
  52,  49,   0,  63,  67,  64,   0,   0,   0,  80,
  84,  81,   0,   0,   0,   0,  90, 101, 105, 102,
   0,  28,  29,  30,  44,  45,  46,  59,  60,  61,
  76,  77,  78,  91,  92, 140, 141, 144,   0,  21,
  23,  24, 122, 123, 124, 125,  31,   0,   0,   0,
   0,   0,   0,   0,   0, 117, 118, 119, 120, 121,
   0,   0,   0,   0,   0,   0,   0,  47,   0,  62,
   0,   0,   0,   0,  79,   0,   0,   0,   0, 100,
   0,  20,  22, 109, 110,   0, 112,   0,   0, 113,
   0,   0, 127,   0,   0, 128, 129, 131, 130, 132,
 136, 133, 135, 134, 138, 139, 126,   0, 137,   0,
   0,   0,   0,   0, 116,   0, 146,  93, 111,   0,
   0,   0, 115,   0,   0, 148, 114, 145,   0, 147 };
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
#line 164 "visidly.y"
{
			ResetIdents();
		} break;
case 4:
#line 176 "visidly.y"
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
#line 203 "visidly.y"
{	
			ResString DefView (ResID (IDS_DEFAULTVIEW, &g_pTE -> RF()), SIGHTNAMESIZE+1);
	
				if (yy2pvt[-1].LongToken() > 0 && fImpView && strcmp (chViewName, DefView)) {
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
#line 230 "visidly.y"
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
#line 245 "visidly.y"
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
#line 261 "visidly.y"
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
#line 277 "visidly.y"
{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}

		long *plCount = new long (yy2pvt[-0].LongToken() != 0 ? 1 : 0);
		
			YYSTACK (plCount, YYLong);
		} break;
case 10:
#line 288 "visidly.y"
{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}

		long *plCount = new long (yy2pvt[-1].LongToken() + (yy2pvt[-0].LongToken() != 0) ? 1 : 0);
		
			YYSTACK (plCount, YYLong);
		} break;
case 18:
#line 310 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefTag = true;
			else
				fTag = true;
		} break;
case 19:
#line 319 "visidly.y"
{
			InitDefaultAttributes();
			fDefaultAttributes = true;
		} break;
case 20:
#line 324 "visidly.y"
{	
				fDefaultAttributes = false;	

			long *plCount = new long (0);
			
				YYSTACK (plCount, YYLong);
			} break;
case 25:
#line 345 "visidly.y"
{
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, *(Dimension *)&szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor, cbGeometry);

			PVI.SetLocatable (fLocatable);
			PVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) 
				lImported = AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &PVI, lUpperScale, lLowerScale) ? 1 : 0;

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 26:
#line 364 "visidly.y"
{
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, *(Dimension *)&szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor, cbGeometry);


			PVI.SetLocatable (fLocatable);
			PVI.SetVisible (fVisible);

		// für alle Objektklassen mit diesem OKS
		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) {
			char *pOKS = yy2pvt[-1].StringToken();

				lImported = AddOKStoSight (chViewName, pOKS, &PVI, lUpperScale, lLowerScale) ? 1 : 0;
				DELETE_OBJ(pOKS);
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 27:
#line 389 "visidly.y"
{
			cnIdents++;

		// Merkmal wegschreiben (yy2pvt[-1].LongToken().intnum ist Objektnummer)
		long lImported = 0L;

			if (g_fImpObjVis && chViewName[0] != '\0' && fImpView) {
			long lONr = yy2pvt[-1].LongToken();

				if (lONr != -1 && 0 != lONr) {
				// Objekt gefunden
				PVisInfo PVI (iType, iPriority,
						  (Color &)colMainColor, (Dimension &)szSize,
						  chTypeString, iPunktRot, (Color &)colFillColor);

					lImported = AddVItoObject (chViewName, lONr, &PVI, s_iDrawResult, cbVisModule) ? 1 : 0;
				}
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 28:
#line 418 "visidly.y"
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
case 29:
#line 439 "visidly.y"
{
		char *pOKS = yy2pvt[-1].StringToken();
		 
			s_iDrawResult = DO_UnChanged;
			s_lIdent = -1L;
			s_lObject = -1L;

			InitAttributes (-1L, VT_Punkt); 
			if (g_pIS) 
				g_pIS -> SetHandledItem (pOKS);
			YYSTACK(pOKS, YYString);
		} break;
case 30:
#line 455 "visidly.y"
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
case 41:
#line 498 "visidly.y"
{
		LVisInfo LVI (iType, iPriority, (Color &)colMainColor, 
			      iWidth, chTypeString, cbGeometry);

			LVI.SetLocatable (fLocatable);
			LVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) 
				lImported = AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &LVI, lUpperScale, lLowerScale) ? 1 : 0;

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 42:
#line 516 "visidly.y"
{
		LVisInfo LVI (iType, iPriority, (Color &)colMainColor, 
			      iWidth, chTypeString, cbGeometry);

			LVI.SetLocatable (fLocatable);
			LVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) {
			char *pOKS = yy2pvt[-1].StringToken();

				lImported = AddOKStoSight (chViewName, pOKS, &LVI, lUpperScale, lLowerScale) ? 1 : 0;
				DELETE_OBJ(pOKS);
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 43:
#line 538 "visidly.y"
{
			cnIdents++;

		long lImported = 0L;

			if (g_fImpObjVis && chViewName[0] != '\0' && fImpView) {
			long lONr = yy2pvt[-1].LongToken();

				if (-1 != lONr && 0 != lONr) {
				// Objekt existiert 
				LVisInfo LVI (iType, iPriority, 
						  (Color &)colMainColor, 
						  iWidth, chTypeString);

					lImported = AddVItoObject (chViewName, lONr, &LVI, s_iDrawResult, cbVisModule) ? 1 : 0;
				}
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 44:
#line 566 "visidly.y"
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
case 45:
#line 588 "visidly.y"
{
		char *pOKS = yy2pvt[-1].StringToken();
		 
			s_iDrawResult = DO_UnChanged;
			s_lIdent = -1L;
			s_lObject = -1L;

			InitAttributes (-1L, VT_Linie); 
			if (g_pIS) 
				g_pIS -> SetHandledItem (pOKS);			

			YYSTACK(pOKS, YYString);
		} break;
case 46:
#line 605 "visidly.y"
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
case 56:
#line 648 "visidly.y"
{
		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor, (Color &)colFillColor, iBkConture, chTypeString, cbGeometry);

			FVI.SetLocatable (fLocatable);
			FVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) 
				lImported = AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &FVI, lUpperScale, lLowerScale) ? 1 : 0;

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 57:
#line 666 "visidly.y"
{
		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor, (Color &)colFillColor, iBkConture, chTypeString, cbGeometry);

			FVI.SetLocatable (fLocatable);
			FVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) {
			char *pOKS = yy2pvt[-1].StringToken();
			
				lImported = AddOKStoSight (chViewName, pOKS, &FVI, lUpperScale, lLowerScale) ? 1 : 0;
				DELETE_OBJ(pOKS);
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 58:
#line 688 "visidly.y"
{
			cnIdents++;

		long lImported = 0L;

			if (g_fImpObjVis && chViewName[0] != '\0' && fImpView) {
			long lONr = yy2pvt[-1].LongToken();
		
				if (-1 != lONr && 0 != lONr) {
				// Objekt existiert 
				FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
						  (Color &)colMainColor,
						  (Color &)colFillColor, iBkConture, chTypeString);

					lImported = AddVItoObject (chViewName, lONr, &FVI, s_iDrawResult, cbVisModule) ? 1 : 0;
				}
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 59:
#line 715 "visidly.y"
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
case 60:
#line 737 "visidly.y"
{
		char *pOKS = yy2pvt[-1].StringToken();
		 
			s_iDrawResult = DO_UnChanged;
			s_lIdent = -1L;
			s_lObject = -1L;

			InitAttributes (-1L, VT_Flaeche); 
			if (g_pIS) 
				g_pIS -> SetHandledItem (pOKS);			
			YYSTACK(pOKS, YYString);
		} break;
case 61:
#line 753 "visidly.y"
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
case 73:
#line 800 "visidly.y"
{
		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString, cbGeometry);

			TVI.SetLocatable (fLocatable);
			TVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) 
				lImported = AddIDtoSight (chViewName, yy2pvt[-1].LongToken(), &TVI, lUpperScale, lLowerScale) ? 1 : 0;

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 74:
#line 819 "visidly.y"
{
		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString, cbGeometry);

			TVI.SetLocatable (fLocatable);
			TVI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) {
			char *pOKS = yy2pvt[-1].StringToken();

				lImported = AddOKStoSight (chViewName, pOKS, &TVI, lUpperScale, lLowerScale) ? 1 : 0;
				DELETE_OBJ(pOKS);
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 75:
#line 842 "visidly.y"
{
			cnIdents++;

		long lImported = 0L;

			if (g_fImpObjVis && chViewName[0] != '\0' && fImpView) {
			long lONr = yy2pvt[-1].LongToken();
		
				if (-1 != lONr && 0 != lONr) {
				// Objekt existiert 
				TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
						  *(Dimension *)&szSize, iTextTyp, iTextRot,
						  chTypeString);

					lImported = AddVItoObject (chViewName, lONr, &TVI, s_iDrawResult, cbVisModule) ? 1 : 0;
				}
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		} break;
case 76:
#line 870 "visidly.y"
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
case 77:
#line 892 "visidly.y"
{
		char *pOKS = yy2pvt[-1].StringToken();
		 
			s_iDrawResult = DO_UnChanged;
			s_lIdent = -1L;
			s_lObject = -1L;

			InitAttributes (-1L, VT_Text); 
			if (g_pIS) 
				g_pIS -> SetHandledItem (pOKS);
			YYSTACK(pOKS, YYString);
		} break;
case 78:
#line 908 "visidly.y"
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
case 89:
#line 954 "visidly.y"
{
			if (g_fImpViewFeatures && chViewName[0] != '\0' && fImpView) 
			{
			char *pKey = yy2pvt[-1].StringToken();
			char *pMWert = yy2pvt[-0].StringToken();
			NAMEDVIEWPROPERTY NVP;

				INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
				NVP.pcView = chViewName;
				NVP.pcName = pKey;
				NVP.pBuffer = pMWert;
				NVP.iLen = (NULL != pMWert) ? strlen(pMWert) : 0;
				DEX_SetNamedViewProperty(NVP);

				DELETE_OBJ (pMWert);
				DELETE_OBJ (pKey);
			}

		long *plCount = new long (0);
		
			YYSTACK (plCount, YYLong);
		} break;
case 90:
#line 977 "visidly.y"
{
			if (g_fImpViewFeatures && chViewName[0] != '\0' && fImpView) 
			{
			char *pMWert = yy2pvt[-0].StringToken();

				AddLegendHeadLine (chViewName, pMWert);
				DELETE_OBJ(pMWert);
			}

		long *plCount = new long (0);
		
			YYSTACK (plCount, YYLong);
		} break;
case 91:
#line 1027 "visidly.y"
{
		char *plMCode = new char[32];
		
			wsprintf (plMCode, g_cbSysProperty, yy2pvt[-1].LongToken());
			YYSTACK (plMCode, YYString);
		} break;
case 92:
#line 1034 "visidly.y"
{
		// Eintrag im Header gegeben
		char *pKey = yy2pvt[-1].StringToken();
		
			YYSTACK (pKey, YYString);
		} break;
case 93:
#line 1044 "visidly.y"
{
		char *pMWert = yy2pvt[-2].StringToken();
		
			YYSTACK (pMWert, YYString);
		} break;
case 94:
#line 1053 "visidly.y"
{
			if (chViewName[0] == '\0' || !fImpView)
				break;

		long lIdent = yy2pvt[-1].LongToken();
		VisInfo VI (iType, iPriority, (Color &)colMainColor, chTypeString, cbGeometry);

			VI.SetLocatable (fLocatable);
			VI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) 
				lImported = AddIDtoSight (chViewName, lIdent, &VI, lUpperScale, lLowerScale, fBits) ? 1 : 0;

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 95:
#line 1074 "visidly.y"
{
			if (chViewName[0] == '\0' || !fImpView)
				break;

		VisInfo VI (iType, iPriority, (Color &)colMainColor, chTypeString, cbGeometry);

			VI.SetLocatable (fLocatable);
			VI.SetVisible (fVisible);

		long lImported = 0L;

			if (chViewName[0] != '\0' && fImpView) {
			char *pOKS = yy2pvt[-1].StringToken();

				lImported = AddOKStoSight (chViewName, pOKS, &VI, lUpperScale, lLowerScale, fBits) ? 1 : 0;
				DELETE_OBJ(pOKS);
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			cnIdents++;
		} break;
case 96:
#line 1098 "visidly.y"
{
		long lImported = 0;

			if (g_fImpObjVis && chViewName[0] != '\0' && fImpView) {
			long lONr = yy2pvt[-1].LongToken();
		
				if (-1 != lONr&& 0 != lONr) {
				// Objekt existiert 
				short iOTyp = DEX_GetObjectType (lONr);

					switch ((VisType)OTypToVTyp (iOTyp)) {
					case VT_Punkt: {
						PVisInfo PVI (iType, iPriority,
								  (Color &)colMainColor, 
								  (Dimension &)szSize,
								  chTypeString, iPunktRot, 
								  (Color &)colFillColor);

							lImported = AddVItoObject (chViewName, lONr, &PVI, s_iDrawResult, cbVisModule) ? 1 : 0;
						}
						break;

					case VT_Linie: {
						LVisInfo LVI (iType, iPriority, 
								  (Color &)colMainColor, iWidth,
								  chTypeString);

							lImported = AddVItoObject (chViewName, lONr, &LVI, s_iDrawResult, cbVisModule) ? 1 : 0;
						}
						break;

					case VT_Flaeche: {
						FVisInfo FVI ((iType + 100*iWidth) | iOpaque, 
								  iPriority, 
									  (Color &)colMainColor,
								  (Color &)colFillColor,
								  iBkConture, chTypeString);

							lImported = AddVItoObject (chViewName, lONr, &FVI, s_iDrawResult, cbVisModule) ? 1 : 0;
						}
						break;

					case VT_Text: {
						TVisInfo TVI (iType, iPriority, 
								  (Color &)colMainColor,
								  (Dimension &)szSize, iTextTyp, 
								  iTextRot, chTypeString);

							lImported = AddVItoObject (chViewName, lONr, &TVI, s_iDrawResult, cbVisModule) ? 1 : 0;
						}
						break;

        				default:
					case VT_Default:
						break;
					}
				}
			}

		long *plCount = new long (lImported);
		
			YYSTACK (plCount, YYLong);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
			cnIdents++;
		} break;
case 97:
#line 1168 "visidly.y"
{
		long lIdent = yy2pvt[-1].LongToken();

			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			s_iDrawResult = DO_UnChanged;
			InitAttributes (lIdent, VT_Default);
			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			
		} break;
case 98:
#line 1184 "visidly.y"
{
		char *pOKS = yy2pvt[-1].StringToken();
			
			s_iDrawResult = DO_UnChanged;
			s_lIdent = -1L;
			s_lObject = -1L;

			InitAttributes (-1L, VT_Default);
			if (g_pIS) 
				g_pIS -> SetHandledItem (pOKS);			
			YYSTACK(pOKS, YYString);
		} break;
case 99:
#line 1200 "visidly.y"
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
case 109:
#line 1244 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefPriority = (short)yy2pvt[-1].LongToken();
			else {
				iPriority = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_PriorityChanged;
			}
		} break;
case 110:
#line 1253 "visidly.y"
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
case 111:
#line 1264 "visidly.y"
{
			if (fDefaultAttributes) {
				iDefType = (short)yy2pvt[-3].LongToken();
#if _TRiAS_VER < 0x0300
				if (DEX_GetDBVersion() >= VERSION05000005) {
#endif // _TRiAS_VER < 0x0300
				char *pStr = yy2pvt[-1].StringToken();
									
					if (!pStr) {
						yy2error (EC_NOMEMORY);
						YYABORT;
					}
					strncpy (chDefTypeString, pStr, VISNAMESIZE);
					chDefTypeString[VISNAMESIZE] = '\0';
					delete pStr;
#if _TRiAS_VER < 0x0300
				} else
					chDefTypeString[0] = '\0';
#endif // _TRiAS_VER < 0x0300
			} else {
				iType = (short)yy2pvt[-3].LongToken();
#if _TRiAS_VER < 0x0300
				if (DEX_GetDBVersion() >= VERSION05000005) {
#endif // _TRiAS_VER < 0x0300
				char *pStr = yy2pvt[-1].StringToken();
									
					if (!pStr) {
						yy2error (EC_NOMEMORY);
						YYABORT;
					}
					strncpy (chTypeString, pStr, VISNAMESIZE);
					chTypeString[VISNAMESIZE] = '\0';
					delete pStr;

					s_iDrawResult |= DO_NameChanged;
#if _TRiAS_VER < 0x0300
				} else
					chDefTypeString[0] = '\0';
#endif // _TRiAS_VER < 0x0300

				s_iDrawResult |= DO_StyleChanged;
			}
		} break;
case 112:
#line 1308 "visidly.y"
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
case 113:
#line 1324 "visidly.y"
{
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefMainColor = (COLORREF &)Col;
			else {
				colMainColor = (COLORREF &)Col;
				s_iDrawResult |= DO_PrimColorChanged;
			}
		} break;
case 114:
#line 1335 "visidly.y"
{
		char *pStr = new char [YYLMAX];
		
			if (!pStr) break;
			*pStr = '%';
			ltoa (yy2pvt[-1].LongToken(), pStr+1, 10);

			cbVisModule[0] = yy2pvt[-4].StringToken();
			cbVisModule[1] = pStr; 
			s_iDrawResult |= DT_WillDrawComplete;
		} break;
case 115:
#line 1347 "visidly.y"
{
			cbVisModule[0] = yy2pvt[-3].StringToken();
			cbVisModule[1] = yy2pvt[-1].StringToken(); 
			s_iDrawResult |= DT_WillDrawComplete;
		} break;
case 116:
#line 1353 "visidly.y"
{
			if (chViewName[0] == '\0' || !fImpView) 
				break;
				
			if (!fDefaultAttributes && g_fImpLegInfo) {	// nur für konkrete Sicht
			char *pLegInfo = yy2pvt[-1].StringToken();
			
//				if (s_lIdent != -1L) 
//					AddLegInfoToIdent (chViewName, s_lIdent, pLegInfo, !IsFirstIdent(s_lIdent));

				if (s_lObject != -1L)
					AddLegInfoToObject (chViewName, s_lObject, pLegInfo);
				else {
				// Objektklasse
					strcpy (g_cbLegInfo, pLegInfo);
				}
				DELETE_OBJ (pLegInfo);
			}
		} break;
case 117:
#line 1373 "visidly.y"
{
			if (fDefaultAttributes)	
				lDefUpperScale = yy2pvt[-0].LongToken();
			else
				lUpperScale = yy2pvt[-0].LongToken();

			s_iDrawResult |= DO_OthersChanged;
		} break;
case 118:
#line 1382 "visidly.y"
{
			if (fDefaultAttributes)	
				lDefLowerScale = yy2pvt[-0].LongToken();
			else
				lLowerScale = yy2pvt[-0].LongToken();

			s_iDrawResult |= DO_OthersChanged;
		} break;
case 119:
#line 1391 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefLocatable = yy2pvt[-0].LongToken();
			else
				fLocatable = yy2pvt[-0].LongToken();

			s_iDrawResult |= DO_OthersChanged;
		} break;
case 120:
#line 1400 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefVisible = yy2pvt[-0].LongToken();
			else
				fVisible = yy2pvt[-0].LongToken();
			
			s_iDrawResult |= DO_OthersChanged;
		} break;
case 121:
#line 1409 "visidly.y"
{
		char *pStr = yy2pvt[-0].StringToken();

			if (strlen(pStr) > 0) {
				if (fDefaultAttributes)	
					strcpy (cbDefGeometry, pStr);
				else
					strcpy (cbGeometry, pStr);

				s_iDrawResult |= DO_OthersChanged;
			}
			DELETE_OBJ(pStr);
		} break;
case 126:
#line 1433 "visidly.y"
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
case 127:
#line 1449 "visidly.y"
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
case 128:
#line 1465 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefPunktRot = (short)yy2pvt[-1].LongToken();	
			else {
				iPunktRot = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 129:
#line 1474 "visidly.y"
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
case 130:
#line 1490 "visidly.y"
{	
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 131:
#line 1501 "visidly.y"
{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 132:
#line 1513 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefWidth = (short)yy2pvt[-1].LongToken();	
			else {
				iWidth = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_SizeChanged;
			}
		} break;
case 133:
#line 1525 "visidly.y"
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
case 134:
#line 1541 "visidly.y"
{	
		Color Col = HSBtoRGB (yy2pvt[-1].LongToken());

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 135:
#line 1552 "visidly.y"
{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		} break;
case 136:
#line 1564 "visidly.y"
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
case 137:
#line 1579 "visidly.y"
{
			if (fDefaultAttributes)	
				fDefBits = (short)yy2pvt[-1].LongToken();
			else {
				fBits = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 138:
#line 1591 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefTextTyp = (short)yy2pvt[-1].LongToken();	
			else {
				iTextTyp = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 139:
#line 1600 "visidly.y"
{	
			if (fDefaultAttributes)	
				iDefTextRot = (short)yy2pvt[-1].LongToken();	
			else {
				iTextRot = (short)yy2pvt[-1].LongToken();
				s_iDrawResult |= DO_OthersChanged;
			}
		} break;
case 140:
#line 1612 "visidly.y"
{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = yy2pvt[-0].LongToken();
			else
				lIdent = MakeHex (yy2pvt[-0].LongToken());

			if (fFirstIdent) fFirstIdent = false;

		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 141:
#line 1627 "visidly.y"
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
			YYSTACK (plIdent, YYLong);
		} break;
case 142:
#line 1641 "visidly.y"
{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = yy2pvt[-0].LongToken();
			else
				lIdent = MakeHex (yy2pvt[-0].LongToken());

			if (fFirstIdent) fFirstIdent = false;

		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		} break;
case 143:
#line 1656 "visidly.y"
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
			YYSTACK (plIdent, YYLong);
		} break;
case 144:
#line 1672 "visidly.y"
{
		char *pOKS = yy2pvt[-0].StringToken();

			if (fFirstIdent) {
				fFirstIdent = false;
				g_fDecIdent = false;		// force Hex
			}
			YYSTACK (pOKS, YYString);
		} break;
case 145:
#line 1684 "visidly.y"
{
		short lHigh = short(yy2pvt[-1].LongToken());
		short lLow = short(yy2pvt[-3].LongToken());
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		} break;
case 146:
#line 1692 "visidly.y"
{
		short lHigh = short(yy2pvt[-0].LongToken());
		short lLow = short(yy2pvt[-2].LongToken());
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		} break;
case 147:
#line 1702 "visidly.y"
{
		long lHue = yy2pvt[-1].LongToken();
		long lSat = yy2pvt[-5].LongToken();
		long lBright = yy2pvt[-3].LongToken();
		long *plLong = new long (HSB((BYTE)lSat, (BYTE)lBright, (WORD)lHue));
		
			YYSTACK (plLong, YYLong);
		} break;
case 148:
#line 1711 "visidly.y"
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



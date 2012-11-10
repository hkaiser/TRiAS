%{
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
#include "yystype.hxx"

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

extern int yylineno;

// Funktionsprototypen --------------------------------------------------------
static void InitDefaultAttributes (void);
static VisType InitAttributes (long lIdent, VisType iVTyp);
static unsigned long MakeHex (unsigned long lPseudoHex);

void yyerror (const char *, ...);
void yyerror (enum ErrCode, ...);
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

	yylineno = 0;
		
	InitDefaultAttributes();
}


%}

%start	VisAsciiDatei

%token	<StringToken()>	T_STRING T_VIEW T_STARTVIEW

%token	<LongToken()>	T_NUMBER T_DEFAULT T_PUNKT T_LINIE T_FLAECHE T_TEXT
%token	<LongToken()>	T_PRIORITY T_TYPE T_MCODE T_DESC T_TAGGED
%token	<LongToken()>	T_MAINCOLOR T_SIZE T_WIDTH T_FILLCOLOR
%token	<LongToken()>	T_TTYP T_TROT T_MAINCOLORC T_FILLCOLORC
%token	<LongToken()>	T_IDENT T_EQUAL T_HEXNUMBER T_TVCS T_TLEGINFO
%token	<LongToken()>	T_OKS T_UPPERSCALE T_LOWERSCALE


%type	<StringToken>	SichtKopf MerkmalsKoerper

%type	<LongToken()>	WertePaar WerteTripel Identifikator allgemeinesAttribut
%type	<LongToken()>	PunktStart LinienStart FlaechenStart UnbekannterStart
%type	<LongToken()>	TextStart MerkmalsStart
%type	<LongToken()>	PunktStartObjekt LinienStartObjekt FlaechenStartObjekt
%type	<LongToken()>	TextStartObjekt UnbekannterStartObjekt
%type 	<LongToken()>	UnbekannterSatz 

%%

VisAsciiDatei:	SichtSpezifikationen
		{
			ResetIdents();
		}
	;

SichtSpezifikationen:
		SichtSpezifikation
	|	SichtSpezifikationen SichtSpezifikation
	;

SichtSpezifikation:	
		SichtKopf '{'
		{	
		char *pView = $<StringToken()>1;
		
			if (!pView) {
				yyerror (EC_NOMEMORY);
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
		}
			AttributSaetze '}'
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
			}
	;

SichtKopf:	
	T_VIEW T_STRING
		{
		char *pView = $<StringToken()>2;
		CImpView *pV = NULL;
				
			YYSTACK (pView, YYString);
			if (g_pVT == NULL || 
			    ((pV = g_pVT -> FFindItem (pView)) && pV -> Import()))
			{
				fImpView = true;
			} else 
				fImpView = false;

			fSetStandardView = false;
		}
	| T_STARTVIEW T_STRING
		{
		char *pView = $<StringToken()>2;
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
		}
	|	T_VIEW T_DEFAULT
		{
		ResString DefView (ResID (IDS_DEFAULTVIEW, &g_pTE -> RF()), SIGHTNAMESIZE+1);
		char *pView = new char [SIGHTNAMESIZE+1];
		
			if (pView) strcpy (pView, DefView.Addr());					   

			YYSTACK (pView, YYString);

			if (g_fImpDefView) fImpView = true;
			else 		   fImpView = false;

			fSetStandardView = false;
		}
	;

AttributSaetze:	AttributSatz
		{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}
		}
	|	AttributSaetze AttributSatz
		{
			if (g_pIS) {
				if (g_pIS -> Break()) YYABORT;
				g_pIS -> SetPosition (cnIdents);
			}
		}
	;

AttributSatz:	StandardSatz
	|	PunktSatz
	|	LinienSatz
	|	FlaechenSatz
	|	TextSatz
	|	MerkmalsSatz
	|	UnbekannterSatz
	;

TagSatz:	T_TAGGED
		{
			if (fDefaultAttributes)	
				fDefTag = true;
			else
				fTag = true;
		}
	;

StandardSatz:	T_DEFAULT '{'
		{
			InitDefaultAttributes();
			fDefaultAttributes = true;
		}
			StandardAttribute '}'
			{	fDefaultAttributes = false;	}
	;

StandardAttribute:	
		StandardAttribut
	|	StandardAttribute StandardAttribut
	;

StandardAttribut:
		allgemeinesAttribut
	|	objektspezifischesAttribut
	;

PunktSatz:	PunktStart PunktKoerper
		{
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, *(Dimension *)&szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor);

			if (chViewName[0] != '\0' && fImpView)
				AddIDtoSight (chViewName, $<LongToken()>1, &PVI, lUpperScale, lLowerScale);
			cnIdents++;
		}
	|	PunktStartObjekt PunktKoerper
		{
			cnIdents++;

		// Merkmal wegschreiben ($1.intnum ist Objektnummer)
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
                
                long lONr = $<LongToken()>1;
                
                	if (lONr == -1) break;	// Objekt nicht gefunden
                	
		PVisInfo PVI (iType, iPriority,
			      (Color &)colMainColor, (Dimension &)szSize,
			      chTypeString, iPunktRot, (Color &)colFillColor);

			AddVItoObject (chViewName, lONr, &PVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		}
	;

PunktStart:	T_PUNKT Identifikator '{'
		{	
		long lIdent = $<LongToken()>2;

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;
			InitAttributes (lIdent, VT_Punkt); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		}
	;

PunktStartObjekt:	
		T_PUNKT T_STRING '{'
		{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = $<StringToken()>2;
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
		}
	;
	
PunktKoerper:	PunktAttribute '}' TagSatz
	|	PunktAttribute '}' 
	|	'}' TagSatz
	|	'}' 
	;

PunktAttribute:	PunktAttribut
	|	PunktAttribute PunktAttribut
	;

PunktAttribut:	allgemeinesAttribut
	|	punktspezifischesAttribut
	|	punktrotspezifischesAttribut
	|	';'
	;

LinienSatz:	LinienStart LinienKoerper
		{
		LVisInfo LVI (iType, iPriority, 
			      (Color &)colMainColor, 
			      iWidth, chTypeString);

			if (chViewName[0] != '\0' && fImpView) 
				AddIDtoSight (chViewName, $<LongToken()>1, &LVI, lUpperScale, lLowerScale);
			cnIdents++;
		}
	|	LinienStartObjekt LinienKoerper
		{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = $<LongToken()>1;
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		LVisInfo LVI (iType, iPriority, 
			      (Color &)colMainColor, 
			      iWidth, chTypeString);

			AddVItoObject (chViewName, lONr, &LVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		}
	;

LinienStart:	T_LINIE Identifikator '{'
		{
		long lIdent = $<LongToken()>2;

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Linie); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		}
	;

LinienStartObjekt:	
		T_LINIE T_STRING '{'
		{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = $<StringToken()>2;
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
		}
	;
	
LinienKoerper:	LinienAttribute '}' TagSatz
	|	LinienAttribute '}' 
	|	'}' TagSatz
	|	'}' 
	;

LinienAttribute:
		LinienAttribut
	|	LinienAttribute LinienAttribut
	;

LinienAttribut:	allgemeinesAttribut
	|	linienspezifischesAttribut
	| 	';'
	;

FlaechenSatz:	FlaechenStart FlaechenKoerper
		{
		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor,
			      (Color &)colFillColor, iBkConture, chTypeString);

			if (chViewName[0] != '\0' && fImpView) 
				AddIDtoSight (chViewName, $<LongToken()>1, &FVI, lUpperScale, lLowerScale);
			cnIdents++;
		}
	|	FlaechenStartObjekt FlaechenKoerper
		{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = $<LongToken()>1;
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		FVisInfo FVI ((iType + 100*iWidth) | iOpaque, iPriority, 
			      (Color &)colMainColor,
			      (Color &)colFillColor, iBkConture, chTypeString);

			AddVItoObject (chViewName, lONr, &FVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		}
	;

FlaechenStart:	T_FLAECHE Identifikator '{'
		{	
		long lIdent = $<LongToken()>2;

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Flaeche); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		}
	;

FlaechenStartObjekt:	
		T_FLAECHE T_STRING '{'
		{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = $<StringToken()>2;
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
		}
	;
	
FlaechenKoerper:	
		FlaechenAttribute '}' TagSatz
	|	FlaechenAttribute '}' 
	|	'}' TagSatz
	|	'}' 
	;

FlaechenAttribute:
		FlaechenAttribut
	|	FlaechenAttribute FlaechenAttribut
	;

FlaechenAttribut:	
		allgemeinesAttribut
	|	flaechentypspezifischesAttribut
	|	flaechenspezifischesAttribut
	|	linienspezifischesAttribut
	|	';'
	;

TextSatz:	TextStart TextKoerper
		{
		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString);

			if (chViewName[0] != '\0' && fImpView)
				AddIDtoSight (chViewName, $<LongToken()>1, &TVI, lUpperScale, lLowerScale);
			cnIdents++;
		}
	|	TextStartObjekt TextKoerper
		{
			cnIdents++;

			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;
			
		long lONr = $<LongToken()>1;
		
			if (lONr == -1L) break;	// Objekt existiert nicht

		TVisInfo TVI (iType, iPriority, (Color &)colMainColor,
			      *(Dimension *)&szSize, iTextTyp, iTextRot,
			      chTypeString);

			AddVItoObject (chViewName, lONr, &TVI, s_iDrawResult, cbVisModule);
			DELETE_OBJ (cbVisModule[0]);
			DELETE_OBJ (cbVisModule[1]);
		}
	;

TextStart:	T_TEXT Identifikator '{'
		{	
		long lIdent = $<LongToken()>2;

			s_iDrawResult = DO_UnChanged;
			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			InitAttributes (lIdent, VT_Text); 

			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			

		// Identifikator weiterreichen
		long *plIdent = new long (lIdent);
		
			YYSTACK (plIdent, YYLong);
		}
	;

TextStartObjekt:
		T_TEXT T_STRING '{'
		{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = $<StringToken()>2;
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
		}
	;
	
TextKoerper:	TextAttribute '}' TagSatz
	|	TextAttribute '}'
	|	'}' TagSatz
	|	'}'
	;

TextAttribute:
		TextAttribut
	|	TextAttribute TextAttribut
	;

TextAttribut:	
		allgemeinesAttribut
	|	textspezifischesAttribut
	|	textpunktspezifischesAttribut
	|	';'
	;

MerkmalsSatz:	MerkmalsStart MerkmalsKoerper
		{
			if (g_fImpViewFeatures && chViewName[0] != '\0' && fImpView) 
			{
			char *pMWert = $<StringToken()>2;
			
				WriteTextMerkmal (TT_Sicht, (long)chViewName,
						  $<LongToken()>1, pMWert);
				DELETE_OBJ (pMWert);
			}
		}
	;

MerkmalsStart:	T_MCODE T_NUMBER '{'
		{
		long *plMCode = new long ($<LongToken()>2);
		
			YYSTACK (plMCode, YYLong);
		}
	|	T_MCODE T_STRING '{'
		{
		// Eintrag im Header gegeben
		char *pKey = $<StringToken()>2;
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
		}
	;

MerkmalsKoerper:	
		T_DESC '=' T_STRING ';' '}'
		{
		char *pMWert = $<StringToken()>3;
		
			YYSTACK (pMWert, YYString);
		}
	;

UnbekannterSatz:	
		UnbekannterStart UnbekannterKoerper
		{
			if (chViewName[0] == '\0' || !fImpView)
				break;

		long lIdent = $<LongToken()>1;
		
			VisInfo VI (iType, iPriority, 
				    (Color &)colMainColor, chTypeString);

			AddIDtoSight (chViewName, lIdent, &VI, lUpperScale, lLowerScale, fBits);
			cnIdents++;
		}
	|	UnbekannterStartObjekt UnbekannterKoerper
		{
			if (!g_fImpObjVis || chViewName[0] == '\0' || !fImpView)
				break;

		long lONr = $<LongToken()>1;
		
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
		}
	;

UnbekannterStart:	
		Identifikator '{'
		{
		long lIdent = $<LongToken()>1;

			s_lIdent = lIdent;
			AddIdent (s_lIdent);

			s_lObject = -1L;

			s_iDrawResult = DO_UnChanged;
			InitAttributes (lIdent, VT_Default);
			if (g_pIS) g_pIS -> SetHandledItem (lIdent);			
		}
	;

UnbekannterStartObjekt:	
		T_STRING '{'
		{
			if (!g_fImpObjVis) break;
			if (chViewName[0] == '\0' || !fImpView) break;

		char *pUIdent = $<StringToken()>1;
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
		}
	;
	
UnbekannterKoerper:	
		UnbekannteAttribute '}' TagSatz
	|	UnbekannteAttribute '}' 
	|	'}' TagSatz
	|	'}' 
	;

UnbekannteAttribute:
		UnbekanntesAttribut
	|	UnbekannteAttribute UnbekanntesAttribut
	;

UnbekanntesAttribut:
		allgemeinesAttribut
	|	SichtZugehoerigkeit
	|	';'
	;

allgemeinesAttribut:
		T_PRIORITY '=' T_NUMBER ';'
		{	
			if (fDefaultAttributes)	
				iDefPriority = (short)$<LongToken()>3;
			else {
				iPriority = (short)$<LongToken()>3;
				s_iDrawResult |= DO_PriorityChanged;
			}
		}
	|	T_TYPE '=' T_NUMBER ';'
		{
			if (fDefaultAttributes) {
				iDefType = (short)$<LongToken()>3;
				chDefTypeString[0] = '\0';
			} else {
				iType = (short)$<LongToken()>3;
				chTypeString[0] = '\0';
				s_iDrawResult |= DO_StyleChanged;
			}
		}
	|	T_TYPE '=' T_NUMBER ',' T_STRING ';'
		{
			if (fDefaultAttributes) {
				iDefType = (short)$<LongToken()>3;
				if (DEX_GetDBVersion() >= VERSION05000005) {
				char *pStr = $<StringToken()>5;
									
					if (!pStr) {
						yyerror (EC_NOMEMORY);
						YYABORT;
					}
					strncpy (chDefTypeString, pStr, VISNAMESIZE);
					chDefTypeString[VISNAMESIZE] = '\0';
					delete pStr;
				} else
					chDefTypeString[0] = '\0';
			} else {
				iType = (short)$<LongToken()>3;
				if (DEX_GetDBVersion() >= VERSION05000005) {
				char *pStr = $<StringToken()>5;
									
					if (!pStr) {
						yyerror (EC_NOMEMORY);
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
		}
	|	T_MAINCOLOR '=' WerteTripel ';'
		{
		COLORREF C = (COLORREF)$<LongToken()>3;
		
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
		}
	|	T_MAINCOLORC '=' WerteTripel ';'
		{
		Color Col = HSBtoRGB ($<LongToken()>3);

			if (fDefaultAttributes)	
				colDefMainColor = (COLORREF &)Col;
			else {
				colMainColor = (COLORREF &)Col;
				s_iDrawResult |= DO_PrimColorChanged;
			}
		}
	|	T_TVCS '=' T_STRING ':' '%' T_NUMBER ';'
		{
		char *pStr = new char [YYLMAX];
		
			if (!pStr) break;
			*pStr = '%';
			ltoa ($<LongToken()>6, pStr+1, 10);

			cbVisModule[0] = $<StringToken()>3;
			cbVisModule[1] = pStr; 
			s_iDrawResult |= DT_WillDrawComplete;
		}
	|	T_TVCS '=' T_STRING ':' T_STRING ';'
		{
			cbVisModule[0] = $<StringToken()>3;
			cbVisModule[1] = $<StringToken()>5; 
			s_iDrawResult |= DT_WillDrawComplete;
		}
	|	T_TLEGINFO '=' '{' T_STRING '}'
		{
			if (chViewName[0] == '\0' || !fImpView) 
				break;
				
			if (!fDefaultAttributes && g_fImpLegInfo) {	// nur für konkrete Sicht
			char *pLegInfo = $<StringToken()>4;
			
				if (s_lIdent != -1L)
					AddLegInfoToIdent (chViewName, s_lIdent, pLegInfo, !IsFirstIdent(s_lIdent));

				if (s_lObject != -1L)
					AddLegInfoToObject (chViewName, s_lObject, pLegInfo);
				DELETE_OBJ (pLegInfo);
			}
		}
	|	T_UPPERSCALE '=' T_NUMBER
		{
			lUpperScale = $<LongToken()>3;
			s_iDrawResult |= DO_OthersChanged;
		}
	|	T_LOWERSCALE '=' T_NUMBER
		{
			lLowerScale = $<LongToken()>3;
			s_iDrawResult |= DO_OthersChanged;
		}
	;


objektspezifischesAttribut:
		punktspezifischesAttribut
	|	linienspezifischesAttribut
	|	flaechenspezifischesAttribut
	|	textspezifischesAttribut
	;

textpunktspezifischesAttribut:
		T_SIZE '=' WertePaar ';'
		{	
		long lSize = $<LongToken()>3;

			if (fDefaultAttributes) {
				szDefSize.cx = short(LOWORD(lSize));
				szDefSize.cy = short(HIWORD(lSize));
			} else {
				szSize.cx = short(LOWORD(lSize));
				szSize.cy = short(HIWORD(lSize));
				s_iDrawResult |= DO_SizeChanged;
			}
		}
	;

punktspezifischesAttribut:
		T_SIZE '=' WertePaar ';'
		{
		long lSize = $<LongToken()>3;
		
			if (fDefaultAttributes) {
				szDefSize.cx = short(HIWORD(lSize));
				szDefSize.cy = short(LOWORD(lSize));
			} else {
				szSize.cx = short(HIWORD(lSize));
				szSize.cy = short(LOWORD(lSize));
				s_iDrawResult |= DO_SizeChanged;
	 		}
		}
	;

punktrotspezifischesAttribut:
		T_TROT '=' T_NUMBER ';'
		{	
			if (fDefaultAttributes)	
				iDefPunktRot = (short)$<LongToken()>3;	
			else {
				iPunktRot = (short)$<LongToken()>3;
				s_iDrawResult |= DO_OthersChanged;
			}
		}
	|	T_FILLCOLOR '=' WerteTripel ';'
		{	
		COLORREF C = (COLORREF)$<LongToken()>3;
		
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
		}
	|	T_FILLCOLORC '=' WerteTripel ';'
		{	
		Color Col = HSBtoRGB ($<LongToken()>3);

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		}
	|	T_FILLCOLOR '=' T_MAINCOLOR ';'
		{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		}
	;

linienspezifischesAttribut:
		T_WIDTH '=' T_NUMBER ';'
		{	
			if (fDefaultAttributes)	
				iDefWidth = (short)$<LongToken()>3;	
			else {
				iWidth = (short)$<LongToken()>3;
				s_iDrawResult |= DO_SizeChanged;
			}
		}
	;

flaechenspezifischesAttribut:
		T_FILLCOLOR '=' WerteTripel ';'
		{	
		COLORREF C = (COLORREF)$<LongToken()>3;
		
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
		}
	|	T_FILLCOLORC '=' WerteTripel ';'
		{	
		Color Col = HSBtoRGB ($<LongToken()>3);

			if (fDefaultAttributes)	
				colDefFillColor = (COLORREF &)Col;
			else {
				colFillColor = (COLORREF &)Col;
				s_iDrawResult |= DO_SecColorChanged;
			}
		}
	|	T_FILLCOLOR '=' T_MAINCOLOR ';'
		{
			if (fDefaultAttributes)	
				colDefFillColor = colDefMainColor;
			else {
				colFillColor = colMainColor;
				s_iDrawResult |= DO_SecColorChanged;
			}
		}
	;

flaechentypspezifischesAttribut:
		T_TTYP '=' T_NUMBER ';'
		{
			if (fDefaultAttributes)	
				iDefOpaque = (short)$<LongToken()>3 & BMOpaque;
			else {
			long lTok = $<LongToken()>3;
			
				iOpaque = (short)(lTok & BMOpaque);
				iBkConture = (short)(lTok & BMBkConture);
				s_iDrawResult |= DO_OthersChanged;
			}
		}
	;

SichtZugehoerigkeit:
		T_TTYP '=' T_NUMBER ';'
		{
			if (fDefaultAttributes)	
				fDefBits = (short)$<LongToken()>3;
			else {
				fBits = (short)$<LongToken()>3;
				s_iDrawResult |= DO_OthersChanged;
			}
		}
	;

textspezifischesAttribut:
		T_TTYP '=' T_NUMBER ';'
		{	
			if (fDefaultAttributes)	
				iDefTextTyp = (short)$<LongToken()>3;	
			else {
				iTextTyp = (short)$<LongToken()>3;
				s_iDrawResult |= DO_OthersChanged;
			}
		}
	|	T_TROT '=' T_NUMBER ';'
		{	
			if (fDefaultAttributes)	
				iDefTextRot = (short)$<LongToken()>3;	
			else {
				iTextRot = (short)$<LongToken()>3;
				s_iDrawResult |= DO_OthersChanged;
			}
		}
	;

Identifikator:
		T_IDENT '=' T_NUMBER 
		{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = $<LongToken()>3;
			else
				lIdent = MakeHex ($<LongToken()>3);

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
		}
	|	T_IDENT '=' T_HEXNUMBER 
		{	
		long *plIdent = new long ($<LongToken()>3);
		
			if (g_fDecIdent && !fFirstIdent) {
				yyerror ("Inkonsistente Identifikator-Zahlenbasis.");
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
		}
	|	T_NUMBER
		{
		long lIdent = 0;

			if (g_fDecIdent) 
				lIdent = $<LongToken()>1;
			else
				lIdent = MakeHex ($<LongToken()>1);

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
		}
	|	T_HEXNUMBER
		{
		long *plIdent = new long ($<LongToken()>1);
		
			if (g_fDecIdent && !fFirstIdent) {
				yyerror ("Inkonsistente Identifikator-Zahlenbasis.");
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
		}
	|	T_OKS '=' T_STRING
		{
		char *pOKS = $<StringToken()>3;
		long *plIdent = new long(0);
		HRESULT hr = IdentFromClassX (pOKS, (ULONG *)plIdent, true);	// ggf. neu erzeugen

			if (FAILED(hr)) {
				yyerror("Kann Objektklassenschlüssel nicht zuordnen.");
				YYABORT;
			}
			YYSTACK (plIdent, YYLong);

			if (fFirstIdent) {
				fFirstIdent = false;
				g_fDecIdent = false;		// force Hex
			}
		}
	;

WertePaar:	'(' T_NUMBER ',' T_NUMBER ')'
		{
		short lHigh = short($<LongToken()>4);
		short lLow = short($<LongToken()>2);
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		}
	|	T_NUMBER ',' T_NUMBER
		{
		short lHigh = short($<LongToken()>3);
		short lLow = short($<LongToken()>1);
		long *plLong = new long (MAKELONG(lHigh, lLow));
		
			YYSTACK (plLong, YYLong);
		}
	;

WerteTripel:	'(' T_NUMBER ',' T_NUMBER ',' T_NUMBER ')'
		{
		long lHue = $<LongToken()>6;
		long lSat = $<LongToken()>2;
		long lBright = $<LongToken()>4;
		long *plLong = new long (HSB((BYTE)lSat, (BYTE)lBright, (WORD)lHue));
		
			YYSTACK (plLong, YYLong);
		}
	|	T_NUMBER ',' T_NUMBER ',' T_NUMBER
		{
		long lHue = $<LongToken()>5;
		long lSat = $<LongToken()>1;
		long lBright = $<LongToken()>3;
		long *plLong = new long (HSB((BYTE)lSat, (BYTE)lBright, (WORD)lHue));
		
			YYSTACK (plLong, YYLong);
		}
	;

%%

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

void yyerror (const char *pFormat, ...) 
{
char *pszText = new char [_MAX_PATH];
bool fToDelete = false;

	if (pszText != NULL) {
		wvsprintf (pszText, (LPSTR)pFormat, (LPSTR)(&pFormat+1));
		fToDelete = true;
	} else
		pszText = (char *)pFormat;
		
char cbLineNum[20];

	ltoa (yylineno, cbLineNum, 10);
	strcat (pszText, ", Zeile: ");
	strcat (pszText, cbLineNum);

	MessageBox (NULL, pszText, 
		    ResString (ResID (IDS_YYERRORCAPTION, &g_pTE -> RF()), 64),
		    MB_TASKMODAL|MB_ICONSTOP|MB_OK);
		    
	if (fToDelete) DELETE_OBJ (pszText);
}

void yyerror (ErrCode EC, ...) 
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

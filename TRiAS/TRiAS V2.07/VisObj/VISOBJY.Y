%{
// Parser fuer die Speicherung von Sichten (Visualisierungsinfo's)
// File: VIS.Y

#include <protos.h>

#include "visobj.hxx"		// Klasse für diese Erweiterung

#if defined(EXTVIS)
#include <icustom.hxx>
#include "vismtree.hxx"
#endif

#include "yystype.hxx"

#if defined(_MSC_VER)
#pragma warning (disable: 4102) 	// unrefereneced label
#endif

inline short CorrectStyle (short iBkConture)
{
	return iBkConture ? BMBkConture : 0;
}

// globale Daten --------------------------------------------------------------
// allgemeine Visualisierungsattribute
static short DrawResult;	// hier wird vermerkt, was geändert wurde

static short Priority;
static short Type;
static char TypeString[VISNAMESIZE+1];
static long int MainColor;

// objektspezifische Visualisierungsattribute
static SIZE szSize;
static short Width;
static long int FillColor;
static short TextTyp;
static short TextRot;
static short TextOrient;
static short iOpaque;
static short iBkConture;
static short PunktRot;

extern int yylineno;

// Funktionsprototypen --------------------------------------------------------
static VisType InitAttributes (VisType, VisInfo *);
static void PreFillVisInfo (VisInfo *pVI);
static void UpdateVisParams (VisInfo *pVI);

void yyerror (const char *);
void yyerror (ErrCode EC, ...);


#define YYLMAX	2048		// max. Stringlänge

%}

%start	VisInformation

%token	<StringToken()>	T_STRING

%token	<LongToken()>	T_NUMBER T_PUNKT T_LINIE T_FLAECHE T_TEXT
%token	<LongToken()>	T_PRIORITY T_TYPE T_TVCS 
%token	<LongToken()>	T_MAINCOLOR T_SIZE T_WIDTH T_FILLCOLOR
%token	<LongToken()>	T_TTYP T_TROT T_IDENT T_TAGGED T_TESC

%type	<LongToken()>	WertePaar WerteTripel allgemeinesAttribut
%type	<LongToken()>	PunktStart LinienStart FlaechenStart UnbekannterStart
%type	<LongToken()>	TextStart TagSatz


%%

VisInformation:	AttributSatz
	|	AttributSatz TagSatz
	|	TagSatz
	;

AttributSatz:	
	|	PunktSatz
	|	LinienSatz
	|	FlaechenSatz
	|	TextSatz
	|	UnbekannterSatz
	;

TagSatz:	T_TAGGED
		{
			DrawResult |= DO_Tagged;
		}
	;

PunktSatz:	PunktStart PunktKoerper
		{
			DELETE (pGlobVI);
			pGlobVI = new PVisInfo (Type, Priority,
					(Color &)MainColor, (Dimension &)szSize,
					TypeString, PunktRot, (Color &)FillColor);
		}
	;

PunktStart:	T_PUNKT '{'
		{	
			InitAttributes (VT_Punkt, pGlobVI); 
		}
	;

PunktKoerper:	PunktAttribute '}'
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
			DELETE (pGlobVI);
			pGlobVI = new LVisInfo (Type, 
						Priority, 
						(Color &)MainColor, 
						Width, TypeString);
		}
	;

LinienStart:	T_LINIE '{'
		{
			InitAttributes (VT_Linie, pGlobVI);
		}
	;

LinienKoerper:	LinienAttribute '}'
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
			DELETE (pGlobVI);
			pGlobVI = new FVisInfo ((Type + 100*Width) | iOpaque, 
						short(Priority), 
						(Color &)MainColor,
						(Color &)FillColor, 
						CorrectStyle (iBkConture),
						TypeString);
		}
	;

FlaechenStart:	T_FLAECHE '{'
		{	
			InitAttributes (VT_Flaeche, pGlobVI);
		}
	;

FlaechenKoerper:	FlaechenAttribute '}'
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
			DELETE (pGlobVI);
			pGlobVI = new TVisInfo (Type, Priority, 
						(Color &)MainColor,
						(Dimension &)szSize, 
						TextTyp, TextRot,
						TypeString);
			if (TextRot != TextOrient)
				((TVisInfo *)pGlobVI) -> Orientation() = TextOrient;
		}
	;

TextStart:	T_TEXT '{'
		{	
			InitAttributes (VT_Text, pGlobVI);
		}
	;

TextKoerper:	TextAttribute '}'
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

UnbekannterSatz:	
		UnbekannterStart UnbekannterKoerper
		{
			switch ($<LongToken()>1) {
			case VT_Punkt: 
				{
					DELETE (pGlobVI);
					pGlobVI = new PVisInfo 
						(Type, Priority, (Color &)MainColor, 
						(Dimension &)szSize, TypeString, PunktRot,
						(Color &)FillColor);
				}
				break;

			case VT_Linie: 
				{
					DELETE (pGlobVI);
					pGlobVI = new LVisInfo 
							(Type, Priority, 
							 (Color &)MainColor, 
							 Width,
							 TypeString);
				}
				break;

			case VT_Flaeche: 
				{
					DELETE (pGlobVI);
					pGlobVI = new FVisInfo 
							((Type + 100*Width) | iOpaque, 
							 Priority, 
							 (Color &)MainColor,
							 (Color &)FillColor,
							 CorrectStyle (iBkConture),
							 TypeString);
				}
				break;

			case VT_Text: 
				{
					DELETE (pGlobVI);
					pGlobVI = new TVisInfo 
							(Type, Priority, 
							 (Color &)MainColor,
							 (Dimension &)szSize, 
							 TextTyp, 
							 TextRot, TypeString);
					if (TextRot != TextOrient)
						((TVisInfo *)pGlobVI) -> Orientation() = TextOrient;
				}
				break;

			case VT_Default: 
				{
					DELETE (pGlobVI);
					pGlobVI = new VisInfo 
							(Type, Priority, 
							 (Color &)MainColor, 
							 TypeString);
				}
				break;
			}
		}
	;

UnbekannterStart:	'{'
		{	
		long *pLong = new long (InitAttributes (VT_Default, pGlobVI));
		
			YYSTACK (pLong, YYLong);
		}
	;

UnbekannterKoerper:	
		UnbekannteAttribute '}'
	|	'}'
	;

UnbekannteAttribute:
		UnbekanntesAttribut
	|	UnbekannteAttribute UnbekanntesAttribut
	;

UnbekanntesAttribut:
		allgemeinesAttribut
	|	punktspezifischesAttribut
	|	flaechenspezifischesAttribut
	|	linienspezifischesAttribut
	|	textspezifischesAttribut
	|	';'
	;

allgemeinesAttribut:
		T_PRIORITY '=' T_NUMBER ';'
		{	
		short locPrio = (short)$<LongToken()>3;
		
			if (Priority != locPrio) {
				Priority = locPrio;
				DrawResult |= DO_PriorityChanged;
			}
		}
	|	T_TYPE '=' T_NUMBER ';'
		{
		short locType = (short)$<LongToken()>3;
		
			if (Type != locType) {
				Type = locType;
				TypeString[0] = '\0';
				DrawResult |= DO_StyleChanged;
			}
		}
	|	T_TYPE '=' T_NUMBER ',' T_STRING ';'
		{
		short locType = (short)$<LongToken()>3;

			if (Type != locType) {
				Type = locType;
				DrawResult |= DO_StyleChanged;
			}
			if (DEX_GetDBVersion() >= VERSION05000005) {
			char *pcnType = $<StringToken()>5;
			
				if (strncmp (TypeString, pcnType, VISNAMESIZE)) {
					strncpy (TypeString, pcnType, VISNAMESIZE);
					TypeString[VISNAMESIZE] = '\0';
					DrawResult |= DO_NameChanged;
				}
				DELETE (pcnType);
			} else
				TypeString[0] = '\0';
		}
	|	T_MAINCOLOR '=' WerteTripel ';'
		{
		long C = $<LongToken()>3;

			if (MainColor != C) {
				MainColor = C;
				DrawResult |= DO_PrimColorChanged;
			}
		}
	|	T_TVCS '=' T_STRING ':' '%' T_NUMBER ';'
		{	// CustomVisModule
#if defined(EXTVIS)
		// bereits gesetzte Parameter übernehmen
			PreFillVisInfo (pGlobVI);

		char *pModName = $<StringToken()>3;
		long lVisMCode = $<LongToken()>6;	// MCode enthält VisString
		char *pVisStr = new char [YYLMAX];
		
			if (!ReadTextMerkmal (TT_Objekt, lGlobONr, lVisMCode, pVisStr))
			{	// Merkmal existiert nicht
				DELETE (pModName);
				DELETE (pVisStr);
				YYABORT;	// abbrechen
			}
			
		HRESULT hr = NOERROR;
		
		// VisModule starten
			if (fFlags & DF_Analyze)
				hr = ResultFromScode (VISMODULE_S_OBJECTISDRAWN);
			else if (DF_Blinking & fFlags)
				hr = ResultFromScode (VISMODULE_E_GENERALERROR);
			else
				hr = (HRESULT)DrawCustom (lGlobONr, pModName, 
							  fFlags, pGlobVI, pVisStr);
		
		// Ergebnis auswerten
			if (SUCCEEDED(hr)) {	// erfolgreich
			long iCode = SCODE_CODE(GetScode (hr));

//				DrawResult &= fFlags;
				if (2 == iCode) {	// completely drawn
				// Flags im DrawResult löschen
					DrawResult &= (fFlags | (DrawResult & DO_VisInfoChanged));
					DrawResult |= (DO_Tagged|DT_WillDrawComplete);
				} else if (1 == iCode) {
				// Flags übernehmen
					DrawResult |= ((fFlags & DO_VisInfoChanged) | DT_HasNewVI);
					UpdateVisParams (pGlobVI);
				}
			} else {
				DrawResult = DO_UnChanged;
				YYACCEPT;
			}

		// gefundene Info ggf. merken
			if (cbModuleInfo) {
			// VisStr für *.VCS generieren
				*pVisStr = '%';
				ltoa (lVisMCode, pVisStr+1, 10);
			
				cbModuleInfo[0] = pModName;
				cbModuleInfo[1] = pVisStr;
			} else {
				DELETE (pModName);
				DELETE (pVisStr);
			}
#endif
		}
	|	T_TVCS '=' T_STRING ':' T_STRING ';'
		{	// CustomVisModule
#if defined(EXTVIS)
		// bereits gesetzte Parameter übernehmen
			PreFillVisInfo (pGlobVI);

		char *pModName = $<StringToken()>3;
		char *pVisStr = $<StringToken()>5;
		HRESULT hr = NOERROR;
		
		// VisModule starten
			if (fFlags & DF_Analyze)
				hr = ResultFromScode (VISMODULE_S_OBJECTISDRAWN);
			else if (fFlags & DF_Blinking)
				hr = ResultFromScode (VISMODULE_E_GENERALERROR);
			else
				hr = (HRESULT)DrawCustom (lGlobONr, pModName, 
							  fFlags, pGlobVI, pVisStr);
		
		// Ergebnis auswerten
			if (SUCCEEDED(hr)) {	// erfolgreich
			long iCode = SCODE_CODE(GetScode (hr));

//				DrawResult &= fFlags;
				if (2 == iCode) {	// completely drawn
				// Flags im DrawResult löschen
					DrawResult &= (fFlags | (DrawResult & DO_VisInfoChanged));
					DrawResult |= (DO_Tagged|DT_WillDrawComplete);
				} else if (1 == iCode) {
				// Flags übernehmen
					DrawResult |= ((fFlags & DO_VisInfoChanged) | DT_HasNewVI);
					UpdateVisParams (pGlobVI);
				}
			} else {
				DrawResult = DO_UnChanged;
				YYACCEPT;
			}

		// gefundene Info ggf. merken
			if (cbModuleInfo) {
				cbModuleInfo[0] = pModName;
				cbModuleInfo[1] = pVisStr;
			} else {
				DELETE (pModName);
				DELETE (pVisStr);
			}
#endif
		}
	;

textpunktspezifischesAttribut:
		T_SIZE '=' WertePaar ';'
		{
		long S = $<LongToken()>3;
		
			if (szSize.cx != LOWORD(S) || szSize.cy != HIWORD(S)) {
				szSize.cx = short(LOWORD(S));
				szSize.cy = short(HIWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		}
	;

punktspezifischesAttribut:
		T_SIZE '=' WertePaar ';'
		{
		long S = $<LongToken()>3;

			if (HIWORD(S) != szSize.cx || LOWORD(S) != szSize.cy) {
				szSize.cx = short(HIWORD(S));
				szSize.cy = short(LOWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		}
	;

punktrotspezifischesAttribut:
		T_TROT '=' T_NUMBER ';'
		{	
		short locR = (short)$<LongToken()>3;
		
			if (PunktRot != locR) {
				PunktRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		}
	|	T_FILLCOLOR '=' WerteTripel ';'
		{	
		long C = $<LongToken()>3;
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		}
	|	T_FILLCOLOR '=' T_MAINCOLOR ';'
		{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		}
	;

linienspezifischesAttribut:
		T_WIDTH '=' T_NUMBER ';'
		{
		short locW = (short)$<LongToken()>3;
		
			if (Width != locW) {
				Width = locW;
				DrawResult |= DO_SizeChanged;
			}
		}
	;

flaechenspezifischesAttribut:
		T_FILLCOLOR '=' WerteTripel ';'
		{	
		long C = $<LongToken()>3;
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		}
	|	T_FILLCOLOR '=' T_MAINCOLOR ';'
		{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		}
	;

flaechentypspezifischesAttribut:
		T_TTYP '=' T_NUMBER ';'
		{
		short locT = (short)$<LongToken()>3;
		
			if (iOpaque != (locT & BMOpaque)) {
				iOpaque = locT & BMOpaque;
				DrawResult |= DO_OthersChanged;
			}
			if (iBkConture != (locT & BMBkConture)) {
				iBkConture = locT & BMBkConture;
				DrawResult |= DO_OthersChanged;
			}
		}
	;

textspezifischesAttribut:
		T_TTYP '=' T_NUMBER ';'
		{
		short locT = (short)$<LongToken()>3;
		
			if (TextTyp != locT) {
				TextTyp = locT;
				DrawResult |= DO_OthersChanged;
			}
		}
	|	T_TROT '=' T_NUMBER ';'
		{	
		short locR = (short)$<LongToken()>3;
		
			if (TextRot != locR) {
				TextRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		}
	|	T_TESC '=' T_NUMBER ';'
		{	
		short locO = (short)$<LongToken()>3;
		
			if (TextOrient != locO) {
				TextOrient = locO;
				DrawResult |= DO_OthersChanged;
			}
		}
	;

WertePaar:	T_NUMBER ',' T_NUMBER
		{
		short l1 = short($<LongToken()>1);
		short l3 = short($<LongToken()>3);
		long *pLong = new long (MAKELONG (l3, l1));
		
			YYSTACK (pLong, YYLong);
		}
	;

WerteTripel:	T_NUMBER ',' T_NUMBER ',' T_NUMBER
		{
		long l1 = $<LongToken()>1;
		long l3 = $<LongToken()>3;
		long l5 = $<LongToken()>5;
		long *pLong = new long (RGB (l1, l3, l5));
		
			YYSTACK (pLong, YYLong);
		}
	;

%%

// DefaultWerte voreinstellen
static VisType InitAttributes (VisType TokenTyp, VisInfo *pVI) 
{
	DrawResult = DO_UnChanged;	// erstmal nichts geändert

	if (pVI != NULL) {	// Id existiert
	// allgemeine Attribute kopieren
		Type = pVI -> Style();
		Priority = pVI -> Priority();
		strncpy (TypeString, pVI -> VisName(), VISNAMESIZE);
		(Color &)MainColor = pVI -> PrimColor();

	// spezifische Attribute kopieren
		if (TokenTyp != VT_Default &&
		    pVI -> isA() != TokenTyp) {
		// DefaultTyp entspricht nicht dem geforderten
			szSize.cx = 150;
			szSize.cy = 150;
			Width = 0;
			FillColor = MainColor;
			TextRot = 0;
			TextOrient = 0;
			TextTyp = 0;
			PunktRot = 0;
			iOpaque = 0;
			iBkConture = 0;
			return VT_Default;
		} else switch (pVI -> isA()) {
		// DefaultTyp entspricht gesuchtem Typ
		case VT_Punkt:
			(Dimension &)szSize = ((PVisInfo *)pVI) -> Size();
			PunktRot = ((PVisInfo *)pVI) -> Rotation();
			(Color &)FillColor = ((PVisInfo *)pVI) -> SecColor();
			return VT_Punkt;

		case VT_Linie:
			Width = ((LVisInfo *)pVI) -> Width();
			return VT_Linie;

		case VT_Flaeche:
			(Color &)FillColor = ((FVisInfo *)pVI) -> SecColor();
			Width = ((FVisInfo *)pVI) -> Width();
			Type = ((FVisInfo *)pVI) -> Type();
			iOpaque = ((FVisInfo *)pVI) -> isOpaque() ? BMOpaque : 0;
			iBkConture = ((FVisInfo *)pVI) -> isBkConture();
			return VT_Flaeche;

		case VT_Text:
			(Dimension &)szSize = ((TVisInfo *)pVI) -> Size();
			TextRot = ((TVisInfo *)pVI) -> Rotation();
			TextOrient = TextRot;
			TextTyp = ((TVisInfo *)pVI) -> Type();
			return VT_Text;

		case VT_Default:
			szSize.cx = 150;
			szSize.cy = 150;
			Width = 0;
			FillColor = MainColor;
			TextRot = 0;
			TextTyp = 0;
			TextOrient = 0;
			PunktRot = 0;
			iOpaque = 0;
			iBkConture = 0;
			return VT_Default;
		}
	} else {
	// Sicht oder Identifikator existieren nicht 
		Type = 0;
		memset (TypeString, '\0', VISNAMESIZE);
		Priority = 500;
		MainColor = 0;
		FillColor = 0;
		Width = 0;
		szSize.cx = 150;
		szSize.cy = 150;
		TextRot = 0;
		TextTyp = 0;
		TextOrient = 0;
		PunktRot = 0;
		iOpaque = 0;
		iBkConture = 0;
		return VT_Default;
	}

return VT_Default;
}

// keine Fehlerbehandlung -----------------------------------------------------
void yyerror (const char *) 
{
	return;
}

void yyerror (ErrCode, ...) 
{
	return;
}


#if defined(EXTVIS)
// Speichern der bis hierher interpretierten VisInfoWerte ---------------------
static void PreFillVisInfo (VisInfo *pVI)
{
	if (pVI == NULL) return;	// nicht gegeben
	
	pVI -> Style() = Type;	// Typ immer setzen
	if (DrawResult & DO_PrimColorChanged)
		pVI -> PrimColor() = (Color &)MainColor;
	if (DrawResult & DO_NameChanged)
		pVI -> SetVisName (TypeString);

	switch (pVI -> isA()) {
	case VT_Punkt: 
		{
			if (DrawResult & DO_SizeChanged)
				((PVisInfo *)pVI) -> Size() = (Dimension &)szSize;
			if (DrawResult & DO_SecColorChanged)
				((PVisInfo *)pVI) -> SecColor() = (Color &)FillColor;
		}
		break;
				
	case VT_Linie:
		{
			if (DrawResult & DO_SizeChanged)
				((LVisInfo *)pVI) -> Width() = Width;
		}
		break;
				
	case VT_Flaeche: 
		{
			if (DrawResult & DO_SecColorChanged)
				((FVisInfo *)pVI) -> SecColor() = (Color &)FillColor;
			if (DrawResult & DO_SizeChanged)
				((FVisInfo *)pVI) -> SetWidth (Width);
		}
		break;
				
	case VT_Text: 
		{
			if (DrawResult & DO_SizeChanged)
				((TVisInfo *)pVI) -> Size() = (Dimension &)szSize;
		}
		break;
				
	case VT_Default:
	default:
		break;
	}
}

static void UpdateVisParams (VisInfo *pVI)
{
	if (pVI == NULL) return;	// nicht gegeben
	
	if (DrawResult & DO_StyleChanged)
		Type = pVI -> Style();
	if (DrawResult & DO_PrimColorChanged)
		MainColor = (long &)pVI -> PrimColor();
	if (DrawResult & DO_NameChanged)
		strcpy (TypeString, pVI -> VisName());

	switch (pVI -> isA()) {
	case VT_Punkt: 
		{
			if (DrawResult & DO_SizeChanged)
				szSize = (SIZE &)((PVisInfo *)pVI) -> Size();
			if (DrawResult & DO_SecColorChanged)
				FillColor = (long &)((PVisInfo *)pVI) -> SecColor();
		}
		break;
				
	case VT_Linie:
		{
			if (DrawResult & DO_SizeChanged)
				Width = ((LVisInfo *)pVI) -> Width();
		}
		break;
				
	case VT_Flaeche: 
		{
			if (DrawResult & DO_SecColorChanged)
				FillColor = (long &)((FVisInfo *)pVI) -> SecColor();
			if (DrawResult & DO_SizeChanged)
				Width = ((FVisInfo *)pVI) -> Width();
		}
		break;
				
	case VT_Text: 
		{
			if (DrawResult & DO_SizeChanged)
				szSize = (SIZE &)((TVisInfo *)pVI) -> Size();
		}
		break;
				
	case VT_Default:
	default:
		break;
	}
}

#endif

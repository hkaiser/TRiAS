
// Parser fuer die Speicherung von Sichten (Visualisierungsinfo's)
// File: VIS.Y

#include <protos.h>

#include "visobj.hxx"		// Klasse für diese Erweiterung

#if defined(EXTVIS)
#include <icustom.hxx>
#include "vismtree.hxx"
#endif

#include "yy1stype.hxx"

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

static bool fVisible = true;
static bool fLocatable = true;

extern int yy1lineno;

// Funktionsprototypen --------------------------------------------------------
static VisType InitAttributes (VisType, VisInfo *);
static void PreFillVisInfo (VisInfo *pVI);
static void UpdateVisParams (VisInfo *pVI);

void yy1error (const char *);
void yy1error (ErrCode EC, ...);


#define YYLMAX	2048		// max. Stringlänge

#define T_STRING 257
#define T_NUMBER 258
#define T_PUNKT 259
#define T_LINIE 260
#define T_FLAECHE 261
#define T_TEXT 262
#define T_PRIORITY 263
#define T_TYPE 264
#define T_TVCS 265
#define T_MAINCOLOR 266
#define T_SIZE 267
#define T_WIDTH 268
#define T_FILLCOLOR 269
#define T_TTYP 270
#define T_TROT 271
#define T_IDENT 272
#define T_TAGGED 273
#define T_TESC 274
#define T_VISIBLE 275
#define T_LOCATABLE 276
#define yy1clearin yy1char = -1
#define yy1errok yy1errflag = 0
extern int yy1char;
extern short yy1errflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE (*pyy1lval), (*pyy1val);
#define YYERRCODE 256



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
		fVisible = pVI -> IsVisible();
		fLocatable = pVI -> IsLocatable();

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
		} 
		else switch (pVI -> isA()) {
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
	} 
	else {
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
		fVisible = true;
		fLocatable = true;
		return VT_Default;
	}
	return VT_Default;
}

// keine Fehlerbehandlung -----------------------------------------------------
void yy1error (const char *) 
{
	return;
}

void yy1error (ErrCode, ...) 
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

	if (DrawResult & DO_OthersChanged) {
		pVI -> SetVisible(fVisible);
		pVI -> SetLocatable(fLocatable);
	}

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
	if (DrawResult & DO_OthersChanged) {
		fVisible = pVI -> IsVisible();
		fLocatable = pVI -> IsLocatable();
	}

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

short yy1exca[] = {-1, 1,
	0, -1,
	-2, 0,
	};
#define YYNPROD 85
#define YYLAST 336
short yy1act[]={

  78,  19,   9, 112, 112, 159, 157, 154, 152, 151,
 117, 124, 120, 127,  78, 126, 125, 122, 121, 118,
 114, 113, 112, 110, 109, 150, 115,  82,  64,  81,
  80,  79, 111,  25, 116,  62,  72, 106,  43,  52,
  26, 105,  64, 104, 160,  42,  50,  61,  73, 103,
  77,  53, 100,  76,  75,  74,  54,  99,  60,  96,
  93,  92,  91,  90,  89,  88, 107,  87,  86,  85,
  28, 158, 131,  42, 155, 149, 148, 147, 146, 145,
  71,  50, 144, 143,  54, 142,  53, 130, 141, 140,
 139, 137,  61, 135, 101, 134, 132, 129,  28, 136,
  49, 156, 138,  41,  73, 133,  77, 108,  59,  76,
  75,  74,  44,   3,  70,  69,  20, 102,  44,  24,
  63,  58,  97,  57,  51,  47, 119,  46,  39,  38,
  27,  22,  21, 123,   8,   7,  83,  15,  16,  17,
  18, 128,  84,  95,   6,   5,   4,   2,  98,  13,
  48,   9,  14,  12,  11,  10,   1,   0,   0,   0,
   0,   0,   0,   0,  23,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  94,   0,
   0,   0,   0,   0,  40,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  29,  30,  34,  31,  35,  45,
  56,  65,  66,   0,   0,  67,  32,  33,  29,  30,
  34,  31,  35,  45,  56,  65,  66,   0, 153,  67,
  32,  33,  29,  30,  34,  31,  68,   0,   0,  65,
  66,   0,   0,  67,  32,  33,  29,  30,  34,  31,
  68,   0,   0,  65,  66,   0,   0,  67,  32,  33,
  29,  30,  34,  31,   0,  45,  56,  55,   0,   0,
   0,   0,  32,  33,  29,  30,  34,  31,  35,   0,
  37,   0,  36,   0,   0,   0,  32,  33,  29,  30,
  34,  31,   0,  45,  56,  55,   0,   0,   0,   0,
  32,  33,  29,  30,  34,  31,  35,   0,  37,   0,
  36,   0,   0,   0,  32,  33,  29,  30,  34,  31,
   0,  45,  29,  30,  34,  31,   0,  45,  32,  33,
   0,   0,   0,   0,  32,  33 };
short yy1pact[]={

-122,-1000,-271,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
  39,  59,  25, -17, -45, -92, -93, -94, -96,-1000,
-1000,-1000,  11,-1000,-1000,-1000,-1000,-1000,-1000,   8,
   7,   6,   4,   3,   2,   1,   0,  -1,-1000,  53,
-1000,-1000,-1000,-1000,-1000,  -2,-1000,  -3,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,  -4,  -9,-1000, -31,-1000,
-1000,-1000,-1000,-1000,-1000, -12, -18, -20, -24,-1000,
 -59,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-234,-235,-236,-237,-238,
-231,-248,-239,-254,-1000,-1000,-240,-1000,-1000,-241,
-255,-1000,-1000,-242,-243,-245,-248,-1000,-1000,  38,
  28,  37,  61,  36,  34,  41,  32,  58,  31,  30,
  29,  26,  24,  23,  20,  19,  18,  17,  16,-1000,
-1000,-232,-1000,-249,-1000,-1000, -29,-1000,-251,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
  15,  57,-252,  12,-1000,-1000,-253, -15,-1000,-1000,
-1000 };
short yy1pgo[]={

   0, 156,  34,  32,  33, 155, 154, 153, 152, 149,
 113, 147, 146, 145, 144, 135, 134, 132, 131, 119,
  40, 130, 129, 128, 103,  38, 127, 125, 100, 124,
  39, 123, 121,  58,  35, 120, 115, 114,  36 };

short yy1r1[]={
   0,   1,   1,   1,  11,  11,  11,  11,  11,  11,
  10,  12,   5,  17,  17,  18,  18,  19,  19,  19,
  19,  13,   6,  22,  22,  23,  23,  24,  24,  24,
  14,   7,  26,  26,  27,  27,  28,  28,  28,  28,
  28,  15,   9,  31,  31,  32,  32,  33,  33,  33,
  33,  16,   8,  36,  36,  37,  37,  38,  38,  38,
  38,  38,  38,   4,   4,   4,   4,   4,   4,   4,
   4,  35,  20,  21,  21,  21,  25,  30,  30,  29,
  34,  34,  34,   2,   3 };

short yy1r2[]={
   0,   1,   2,   1,   0,   1,   1,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   2,   2,   2,   1,   1,   2,   1,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   1,   2,   1,   1,   2,   1,   1,   1,
   1,   1,   1,   4,   4,   6,   4,   4,   4,   7,
   6,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   3,   5 };

short yy1chk[]={
-1000,  -1, -11, -10, -12, -13, -14, -15, -16, 273,
  -5,  -6,  -7,  -9,  -8, 259, 260, 261, 262, 123,
 -10, -17, -18, 125, -19,  -4, -20, -21,  59, 263,
 264, 266, 275, 276, 265, 267, 271, 269, -22, -23,
 125, -24,  -4, -25,  59, 268, -26, -27, 125, -28,
  -4, -29, -30, -25,  59, 270, 269, -31, -32, 125,
 -33,  -4, -34, -35,  59, 270, 271, 274, 267, -36,
 -37, 125, -38,  -4, -20, -30, -25, -34,  59, 123,
 123, 123, 123, 125, -19,  61,  61,  61,  61,  61,
  61,  61,  61,  61, 125, -24,  61, 125, -28,  61,
  61, 125, -33,  61,  61,  61,  61, 125, -38, 258,
 258,  -3, 258, 258, 258, 257,  -2, 258, 258,  -3,
 266, 258, 258,  -3, 266, 258, 258, 258,  -2,  59,
  59,  44,  59,  44,  59,  59,  58,  59,  44,  59,
  59,  59,  59,  59,  59,  59,  59,  59,  59,  59,
 257, 258,  37, 257, 258,  59,  44, 258,  59, 258,
  59 };

short yy1def[]={
   4,  -2,   1,   3,   5,   6,   7,   8,   9,  10,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  52,
   2,  11,   0,  14,  15,  17,  18,  19,  20,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  21,   0,
  24,  25,  27,  28,  29,   0,  30,   0,  33,  34,
  36,  37,  38,  39,  40,   0,   0,  41,   0,  44,
  45,  47,  48,  49,  50,   0,   0,   0,   0,  51,
   0,  54,  55,  57,  58,  59,  60,  61,  62,  12,
  22,  31,  42,  13,  16,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  23,  26,   0,  32,  35,   0,
   0,  43,  46,   0,   0,   0,   0,  53,  56,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  63,
  64,   0,  66,   0,  67,  68,   0,  72,   0,  73,
  74,  75,  76,  79,  77,  78,  80,  81,  82,  71,
   0,   0,   0,   0,  83,  65,   0,   0,  70,  84,
  69 };
# define YYFLAG -1000
# define YYERROR goto yy1errlab
# define YYACCEPT return(DrawResult)
# define YYABORT return(DO_UnChanged)

// Funktionsdefinitionen
void yy1error (const char *);
void yy1error (enum ErrCode, ...);
int yy1lex (void);

/*	parser for yacc output	*/

#if defined(YYDEBUG)
int yy1debug = 0; /* 1 for debugging */
#endif

YYSTYPE *yy1v; /* where the values are stored */
int yy1char = -1; /* current input token number */
int yy1nerrs = 0;  /* number of errors */
short yy1errflag = 0;  /* error recovery flag */

short CVisObjExtension :: ParseVisString (long lGlobONr, VisInfo *& pGlobVI, short fFlags, char **cbModuleInfo) {

	short yy1s[YYMAXDEPTH];
	short yy1j, yy1m;
	register YYSTYPE *yy1pvt;
	register short yy1state, *yy1ps, yy1n;
	register YYSTYPE *yy1pv;
	register short *yy1xi;

	yy1state = 0;
	yy1char = -1;
	yy1nerrs = 0;
	yy1errflag = 0;
	yy1ps= &yy1s[0] - 1;
	yy1pv= &yy1v[-1];

 yy1stack:    /* put a state and value onto the stack */

#if defined(YYDEBUG)
	if( yy1debug  ) printf( "state %d, char 0%o\n", yy1state, yy1char );
#endif
		if( ++yy1ps> &yy1s[YYMAXDEPTH] ) { yy1error( "yacc stack overflow" ); return(DO_UnChanged); }
		*yy1ps = yy1state;
		++yy1pv;
		*yy1pv = (*pyy1val);	

 yy1newstate:

	yy1n = yy1pact[yy1state];

	if( yy1n<= YYFLAG ) goto yy1default; /* simple state */

	if( yy1char<0 ) if( (yy1char=yy1lex())<0 ) yy1char=0;
	if( (yy1n += yy1char)<0 || yy1n >= YYLAST ) goto yy1default;

	if( yy1chk[ yy1n=yy1act[ yy1n ] ] == yy1char ){ /* valid shift */
		yy1char = -1;
		(*pyy1val) = (*pyy1lval);
		yy1state = yy1n;
		if( yy1errflag > 0 ) --yy1errflag;
		goto yy1stack;
		}

 yy1default:
	/* default state action */

	if( (yy1n=yy1def[yy1state]) == -2 ) {
		if( yy1char<0 ) if( (yy1char=yy1lex())<0 ) yy1char = 0;
		/* look through exception table */

		for( yy1xi=yy1exca; (*yy1xi!= (-1)) || (yy1xi[1]!=yy1state) ; yy1xi += 2 ) ; /* VOID */

		while( *(yy1xi+=2) >= 0 ){
			if( *yy1xi == yy1char ) break;
			}
		if( (yy1n = yy1xi[1]) < 0 ) return(DrawResult);   /* accept */
		}

	if( yy1n == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yy1errflag ){

		case 0:   /* brand new error */

			yy1error( "syntax error" );
		yy1errlab:
			++yy1nerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yy1errflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yy1ps >= yy1s ) {
			   yy1n = yy1pact[*yy1ps] + YYERRCODE;
			   if( yy1n>= 0 && yy1n < YYLAST && yy1chk[yy1act[yy1n]] == YYERRCODE ){
			      yy1state = yy1act[yy1n];  /* simulate a shift of "error" */
			      goto yy1stack;
			      }
			   yy1n = yy1pact[*yy1ps];

			   /* the current yy1ps has no shift onn "error", pop stack */

#if defined (YYDEBUG)
			   if( yy1debug ) printf( "error recovery pops state %d, uncovers %d\n", *yy1ps, yy1ps[-1] );
#endif
			   --yy1ps;
			   --yy1pv;
			   }

			/* there is no state on the stack with an error shift ... abort */

	yy1abort:
			return(DO_UnChanged);


		case 3:  /* no shift yet; clobber input char */

#if defined(YYDEBUG)
			if( yy1debug ) printf( "error recovery discards char %d\n", yy1char );
#endif

			if( yy1char == 0 ) goto yy1abort; /* don't discard EOF, quit */
			yy1char = -1;
			goto yy1newstate;   /* try again in the same state */

			}

		}

	/* reduction by production yy1n */

#if defined(YYDEBUG)
		if( yy1debug ) printf("reduce %d\n",yy1n);
#endif
		yy1ps -= yy1r2[yy1n];
		yy1pvt = yy1pv;
		yy1pv -= yy1r2[yy1n];
		yy1m=yy1n;
			/* consult goto table to find next state */
		yy1n = yy1r1[yy1n];
		yy1j = yy1pgo[yy1n] + *yy1ps + 1;
		if( yy1j>=YYLAST || yy1chk[ yy1state = yy1act[yy1j] ] != -yy1n ) yy1state = yy1act[yy1pgo[yy1n]];
		switch(yy1m){
			
case 10:
{
			DrawResult |= DO_Tagged;
		} break;
case 11:
{
			DELETE_OBJ (pGlobVI);
			pGlobVI = new PVisInfo (Type, Priority,
					(Color &)MainColor, (Dimension &)szSize,
					TypeString, PunktRot, (Color &)FillColor);
		} break;
case 12:
{	
			InitAttributes (VT_Punkt, pGlobVI); 
		} break;
case 21:
{
			DELETE_OBJ (pGlobVI);
			pGlobVI = new LVisInfo (Type, 
						Priority, 
						(Color &)MainColor, 
						Width, TypeString);
		} break;
case 22:
{
			InitAttributes (VT_Linie, pGlobVI);
		} break;
case 30:
{
			DELETE_OBJ (pGlobVI);
			pGlobVI = new FVisInfo ((Type + 100*Width) | iOpaque, 
						short(Priority), 
						(Color &)MainColor,
						(Color &)FillColor, 
						CorrectStyle (iBkConture),
						TypeString);
		} break;
case 31:
{	
			InitAttributes (VT_Flaeche, pGlobVI);
		} break;
case 41:
{
			DELETE_OBJ (pGlobVI);
			pGlobVI = new TVisInfo (Type, Priority, 
						(Color &)MainColor,
						(Dimension &)szSize, 
						TextTyp, TextRot,
						TypeString);
			if (TextRot != TextOrient)
				((TVisInfo *)pGlobVI) -> Orientation() = TextOrient;
		} break;
case 42:
{	
			InitAttributes (VT_Text, pGlobVI);
		} break;
case 51:
{
			switch (yy1pvt[-1].LongToken()) {
			case VT_Punkt: 
				{
					DELETE_OBJ (pGlobVI);
					pGlobVI = new PVisInfo 
						(Type, Priority, (Color &)MainColor, 
						(Dimension &)szSize, TypeString, PunktRot,
						(Color &)FillColor);
				}
				break;

			case VT_Linie: 
				{
					DELETE_OBJ (pGlobVI);
					pGlobVI = new LVisInfo 
							(Type, Priority, 
							 (Color &)MainColor, 
							 Width,
							 TypeString);
				}
				break;

			case VT_Flaeche: 
				{
					DELETE_OBJ (pGlobVI);
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
					DELETE_OBJ (pGlobVI);
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
					DELETE_OBJ (pGlobVI);
					pGlobVI = new VisInfo 
							(Type, Priority, 
							 (Color &)MainColor, 
							 TypeString);
				}
				break;
			}
		} break;
case 52:
{	
		long *pLong = new long (InitAttributes (VT_Default, pGlobVI));
		
			YYSTACK (pLong, YYLong);
		} break;
case 63:
{	
		short locPrio = (short)yy1pvt[-1].LongToken();
		
			if (Priority != locPrio) {
				Priority = locPrio;
				DrawResult |= DO_PriorityChanged;
			}
		} break;
case 64:
{
		short locType = (short)yy1pvt[-1].LongToken();
		
			if (Type != locType) {
				Type = locType;
				TypeString[0] = '\0';
				DrawResult |= DO_StyleChanged;
			}
		} break;
case 65:
{
		short locType = (short)yy1pvt[-3].LongToken();

			if (Type != locType) {
				Type = locType;
				DrawResult |= DO_StyleChanged;
			}
#if _TRiAS_VER < 0x0300
			if (DEX_GetDBVersion() >= VERSION05000005) {
#endif // _TRiAS_VER < 0x0300
			char *pcnType = yy1pvt[-1].StringToken();
			
				if (strncmp (TypeString, pcnType, VISNAMESIZE)) {
					strncpy (TypeString, pcnType, VISNAMESIZE);
					TypeString[VISNAMESIZE] = '\0';
					DrawResult |= DO_NameChanged;
				}
				DELETE_OBJ (pcnType);
#if _TRiAS_VER < 0x0300
			} else
				TypeString[0] = '\0';
#endif // _TRiAS_VER < 0x0300
		} break;
case 66:
{
		long C = yy1pvt[-1].LongToken();

			if (MainColor != C) {
				MainColor = C;
				DrawResult |= DO_PrimColorChanged;
			}
		} break;
case 67:
{
		long lVisible = yy1pvt[-1].LongToken();

			fVisible = lVisible ? true : false;
			DrawResult |= DO_OthersChanged;
		} break;
case 68:
{
		long lLocatable = yy1pvt[-1].LongToken();

			fLocatable = lLocatable ? true : false;
			DrawResult |= DO_OthersChanged;
		} break;
case 69:
{	// CustomVisModule
#if defined(EXTVIS)
		// bereits gesetzte Parameter übernehmen
			PreFillVisInfo (pGlobVI);

		char *pModName = yy1pvt[-4].StringToken();
		HPROJECT hPr = DEX_GetObjectProject (lGlobONr);
		MAPMCODETOHANDLE MMH;
		long lVisMCode = 0;		

			INITSTRUCT(MMH, MAPMCODETOHANDLE);
			MMH.lIdent = DEX_GetObjIdent(lGlobONr);
			MMH.lMCode = yy1pvt[-1].LongToken();			// MCode enthält VisString
			MMH.plHandle = (INT_PTR *)&lVisMCode;
			MMH.fCreate = FALSE;
			DEX_MapOrCreateMCodeToHandle(hPr, MMH);

		char *pVisStr = new char [YYLMAX];
		
			if (0 == lVisMCode || !ReadTextMerkmal (TT_Objekt, lGlobONr, lVisMCode, pVisStr))
			{	// Merkmal existiert nicht
				DELETE_OBJ (pModName);
				DELETE_OBJ (pVisStr);
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
				ltoa ((DF_Export & fFlags) ? MMH.lMCode : lVisMCode, pVisStr+1, 10);
			
				cbModuleInfo[0] = pModName;
				cbModuleInfo[1] = pVisStr;
			} else {
				DELETE_OBJ (pModName);
				DELETE_OBJ (pVisStr);
			}
#endif
		} break;
case 70:
{	// CustomVisModule
#if defined(EXTVIS)
		// bereits gesetzte Parameter übernehmen
			PreFillVisInfo (pGlobVI);

		char *pModName = yy1pvt[-3].StringToken();
		char *pVisStr = yy1pvt[-1].StringToken();
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
				DELETE_OBJ (pModName);
				DELETE_OBJ (pVisStr);
			}
#endif
		} break;
case 71:
{
		long S = yy1pvt[-1].LongToken();
		
			if (szSize.cx != LOWORD(S) || szSize.cy != HIWORD(S)) {
				szSize.cx = short(LOWORD(S));
				szSize.cy = short(HIWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 72:
{
		long S = yy1pvt[-1].LongToken();

			if (HIWORD(S) != szSize.cx || LOWORD(S) != szSize.cy) {
				szSize.cx = short(HIWORD(S));
				szSize.cy = short(LOWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 73:
{	
		short locR = (short)yy1pvt[-1].LongToken();
		
			if (PunktRot != locR) {
				PunktRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 74:
{	
		long C = yy1pvt[-1].LongToken();
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		} break;
case 75:
{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		} break;
case 76:
{
		short locW = (short)yy1pvt[-1].LongToken();
		
			if (Width != locW) {
				Width = locW;
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 77:
{	
		long C = yy1pvt[-1].LongToken();
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		} break;
case 78:
{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		} break;
case 79:
{
		short locT = (short)yy1pvt[-1].LongToken();
		
			if (iOpaque != (locT & BMOpaque)) {
				iOpaque = locT & BMOpaque;
				DrawResult |= DO_OthersChanged;
			}
			if (iBkConture != (locT & BMBkConture)) {
				iBkConture = locT & BMBkConture;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 80:
{
		short locT = (short)yy1pvt[-1].LongToken();
		
			if (TextTyp != locT) {
				TextTyp = locT;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 81:
{	
		short locR = (short)yy1pvt[-1].LongToken();
		
			if (TextRot != locR) {
				TextRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 82:
{	
		short locO = (short)yy1pvt[-1].LongToken();
		
			if (TextOrient != locO) {
				TextOrient = locO;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 83:
{
		short l1 = short(yy1pvt[-2].LongToken());
		short l3 = short(yy1pvt[-0].LongToken());
		long *pLong = new long (MAKELONG (l3, l1));
		
			YYSTACK (pLong, YYLong);
		} break;
case 84:
{
		long l1 = yy1pvt[-4].LongToken();
		long l3 = yy1pvt[-2].LongToken();
		long l5 = yy1pvt[-0].LongToken();
		long *pLong = new long (RGB (l1, l3, l5));
		
			YYSTACK (pLong, YYLong);
		} break;
		}
		(*pyy1val) = yy1pv[1];
		goto yy1stack;  /* stack new state and value */

	}



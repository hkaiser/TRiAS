
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

short yy1exca[] = {-1, 1,
	0, -1,
	-2, 0,
	};
#define YYNPROD 83
#define YYLAST 299
short yy1act[]={

  76,  19,   9, 108, 151, 108, 149, 146, 143, 111,
 121, 118,  76, 114, 120, 119, 116, 144, 115, 112,
 108, 106, 105, 142,  62, 109,  80,  79,  78,  77,
 107, 110,  70, 102,  41, 101,  62, 100,  25,  60,
  50,  26,  99,  96,  95,  92,  89,  51,  28,  74,
  40,  48,  59,  71,  75,  73,  72,  28,  88, 125,
  87,  86,  85,  84,  83, 152, 103,  52, 150, 147,
 141, 140, 139, 138, 124,  52,  40, 137,  69, 136,
  51, 135, 134,  42,  48, 133, 132, 131, 129,  42,
  97, 126, 123, 128, 148,  59,  58,  47, 130, 127,
  68, 104,  57,  74,  39,  24,  67,  71,  75,  73,
  72,  61,   3,  56,  81,  20,  55,  49,  45,  44,
 113,  37,  36,  23,  27,  22,  21, 117,  82,   8,
   7,   6,   5,  93, 122,   4,   2,  15,  16,  17,
  18,  46,  91,  94,  13,  14,  12,  11,  10,  90,
   1,   9,   0,  98,   0,  38,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  29,  30,  32,  31,  33,  43,
  54,  63,  64,   0,   0,  65,  29,  30,  32,  31,
  33,  43,  54,  63,  64,   0,   0,  65,  29,  30,
  32,  31,  66,   0,   0,  63,  64, 145,   0,  65,
  29,  30,  32,  31,  66,   0,   0,  63,  64,   0,
   0,  65,  29,  30,  32,  31,  33,   0,  35,   0,
  34,  29,  30,  32,  31,  33,   0,  35,   0,  34,
   0,  29,  30,  32,  31,   0,  43,  54,  53,  29,
  30,  32,  31,   0,  43,  54,  53,  29,  30,  32,
  31,   0,  43,  29,  30,  32,  31,   0,  43 };
short yy1pact[]={

-122,-1000,-271,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
  -2,  30,  16, -23, -47, -94, -95, -96, -97,-1000,
-1000,-1000, -11,-1000,-1000,-1000,-1000,-1000,-1000,   3,
   2,   1,   0,  -1,  -3, -15,-1000,  24,-1000,-1000,
-1000,-1000,-1000, -16,-1000,   8,-1000,-1000,-1000,-1000,
-1000,-1000,-1000, -17, -18,-1000, -35,-1000,-1000,-1000,
-1000,-1000,-1000, -19, -24, -26, -28,-1000, -59,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-236,-237,-238,-232,-249,-239,-253,
-1000,-1000,-240,-1000,-1000,-242,-255,-1000,-1000,-243,
-244,-248,-249,-1000,-1000,  33,  15,  32,  55,  35,
  29,  54,  28,  27,  26,  23,  22,  20,  18,  14,
  13,  12,  11,-1000,-1000,-234,-1000,-250, -20,-1000,
-251,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,  10,  50,-252,   9,-1000,-1000,-254,   6,
-1000,-1000,-1000 };
short yy1pgo[]={

   0, 150,  31,  30,  38, 148, 147, 146, 145, 144,
 112, 136, 135, 132, 131, 130, 129, 126, 125, 105,
  41, 124, 122, 121, 104,  34, 119, 118,  97, 117,
  40, 116, 113,  96,  39, 111, 106, 100,  32 };

short yy1r1[]={
   0,   1,   1,   1,  11,  11,  11,  11,  11,  11,
  10,  12,   5,  17,  17,  18,  18,  19,  19,  19,
  19,  13,   6,  22,  22,  23,  23,  24,  24,  24,
  14,   7,  26,  26,  27,  27,  28,  28,  28,  28,
  28,  15,   9,  31,  31,  32,  32,  33,  33,  33,
  33,  16,   8,  36,  36,  37,  37,  38,  38,  38,
  38,  38,  38,   4,   4,   4,   4,   4,   4,  35,
  20,  21,  21,  21,  25,  30,  30,  29,  34,  34,
  34,   2,   3 };

short yy1r2[]={
   0,   1,   2,   1,   0,   1,   1,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   2,   2,   2,   1,   1,   2,   1,   1,   1,   1,
   1,   2,   2,   2,   1,   1,   2,   1,   1,   1,
   1,   2,   1,   2,   1,   1,   2,   1,   1,   1,
   1,   1,   1,   4,   4,   6,   4,   7,   6,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   4,   3,   5 };

short yy1chk[]={
-1000,  -1, -11, -10, -12, -13, -14, -15, -16, 273,
  -5,  -6,  -7,  -9,  -8, 259, 260, 261, 262, 123,
 -10, -17, -18, 125, -19,  -4, -20, -21,  59, 263,
 264, 266, 265, 267, 271, 269, -22, -23, 125, -24,
  -4, -25,  59, 268, -26, -27, 125, -28,  -4, -29,
 -30, -25,  59, 270, 269, -31, -32, 125, -33,  -4,
 -34, -35,  59, 270, 271, 274, 267, -36, -37, 125,
 -38,  -4, -20, -30, -25, -34,  59, 123, 123, 123,
 123, 125, -19,  61,  61,  61,  61,  61,  61,  61,
 125, -24,  61, 125, -28,  61,  61, 125, -33,  61,
  61,  61,  61, 125, -38, 258, 258,  -3, 258, 257,
  -2, 258, 258,  -3, 266, 258, 258,  -3, 266, 258,
 258, 258,  -2,  59,  59,  44,  59,  44,  58,  59,
  44,  59,  59,  59,  59,  59,  59,  59,  59,  59,
  59,  59, 257, 258,  37, 257, 258,  59,  44, 258,
  59, 258,  59 };

short yy1def[]={
   4,  -2,   1,   3,   5,   6,   7,   8,   9,  10,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  52,
   2,  11,   0,  14,  15,  17,  18,  19,  20,   0,
   0,   0,   0,   0,   0,   0,  21,   0,  24,  25,
  27,  28,  29,   0,  30,   0,  33,  34,  36,  37,
  38,  39,  40,   0,   0,  41,   0,  44,  45,  47,
  48,  49,  50,   0,   0,   0,   0,  51,   0,  54,
  55,  57,  58,  59,  60,  61,  62,  12,  22,  31,
  42,  13,  16,   0,   0,   0,   0,   0,   0,   0,
  23,  26,   0,  32,  35,   0,   0,  43,  46,   0,
   0,   0,   0,  53,  56,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  63,  64,   0,  66,   0,   0,  70,
   0,  71,  72,  73,  74,  77,  75,  76,  78,  79,
  80,  69,   0,   0,   0,   0,  81,  65,   0,   0,
  68,  82,  67 };
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
			if (DEX_GetDBVersion() >= VERSION05000005) {
			char *pcnType = yy1pvt[-1].StringToken();
			
				if (strncmp (TypeString, pcnType, VISNAMESIZE)) {
					strncpy (TypeString, pcnType, VISNAMESIZE);
					TypeString[VISNAMESIZE] = '\0';
					DrawResult |= DO_NameChanged;
				}
				DELETE_OBJ (pcnType);
			} else
				TypeString[0] = '\0';
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
{	// CustomVisModule
#if defined(EXTVIS)
		// bereits gesetzte Parameter übernehmen
			PreFillVisInfo (pGlobVI);

		char *pModName = yy1pvt[-4].StringToken();
		long lVisMCode = yy1pvt[-1].LongToken();	// MCode enthält VisString
		char *pVisStr = new char [YYLMAX];
		
			if (!ReadTextMerkmal (TT_Objekt, lGlobONr, lVisMCode, pVisStr))
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
				ltoa (lVisMCode, pVisStr+1, 10);
			
				cbModuleInfo[0] = pModName;
				cbModuleInfo[1] = pVisStr;
			} else {
				DELETE_OBJ (pModName);
				DELETE_OBJ (pVisStr);
			}
#endif
		} break;
case 68:
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
case 69:
{
		long S = yy1pvt[-1].LongToken();
		
			if (szSize.cx != LOWORD(S) || szSize.cy != HIWORD(S)) {
				szSize.cx = short(LOWORD(S));
				szSize.cy = short(HIWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 70:
{
		long S = yy1pvt[-1].LongToken();

			if (HIWORD(S) != szSize.cx || LOWORD(S) != szSize.cy) {
				szSize.cx = short(HIWORD(S));
				szSize.cy = short(LOWORD(S));
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 71:
{	
		short locR = (short)yy1pvt[-1].LongToken();
		
			if (PunktRot != locR) {
				PunktRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 72:
{	
		long C = yy1pvt[-1].LongToken();
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		} break;
case 73:
{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		} break;
case 74:
{
		short locW = (short)yy1pvt[-1].LongToken();
		
			if (Width != locW) {
				Width = locW;
				DrawResult |= DO_SizeChanged;
			}
		} break;
case 75:
{	
		long C = yy1pvt[-1].LongToken();
		
			if (FillColor != C) {
				FillColor = C;	
				DrawResult |= DO_SecColorChanged;
			}
		} break;
case 76:
{
			if (FillColor != MainColor) {
				FillColor = MainColor;
				DrawResult |= DO_SecColorChanged;
			} 
		} break;
case 77:
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
case 78:
{
		short locT = (short)yy1pvt[-1].LongToken();
		
			if (TextTyp != locT) {
				TextTyp = locT;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 79:
{	
		short locR = (short)yy1pvt[-1].LongToken();
		
			if (TextRot != locR) {
				TextRot = locR;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 80:
{	
		short locO = (short)yy1pvt[-1].LongToken();
		
			if (TextOrient != locO) {
				TextOrient = locO;
				DrawResult |= DO_OthersChanged;
			}
		} break;
case 81:
{
		short l1 = short(yy1pvt[-2].LongToken());
		short l3 = short(yy1pvt[-0].LongToken());
		long *pLong = new long (MAKELONG (l3, l1));
		
			YYSTACK (pLong, YYLong);
		} break;
case 82:
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



#include "pheader.hpp"				//	prec. Header

#include <assert.h>					//	assert ()

#include "dxfimp.h"					//	Konstanten
#include "header.hpp"				//	Header
#include "lextypes.h"				//	lex-spezifische Typ-Definitionen
#include "rechstat.hpp"				//	RechStatus
#include "punktli.hpp"				//	Punkt
#include "tools.hpp"				//	Ausgabe-Funktionen
#include "dgeo_obj.hpp"				//	weitere Ausgabe-Funktionen
#include "layers.hpp"				//	CLayerBaum
#include "block.hpp"				//	CBlockTree

#pragma warning (disable: 4101 4102 )

extern "C" 
{
	#include "float.h"		// DBL_MAX
}

// Konstanten
static const int ValidVertex = 16;			// Vertex-Flag
static const int VKP_Vertex = 128;			// Vielflächennetz-Kontrollpunkt
static const int InValidFlag = -1;			// ungültiger Flagwert	
static const int iPolylineClosed = 1;		// Polylinie ist geschlossen
static const int iVielFlaechenNetz = 64;	
static const MaxAutoCadVersion = 1009;		//	AutoCAD Version 12

// Prototypen 
int yylex (void);
void yyerror (short ResourceID);
Bool CreateDGeoObj (DGeoTyp DGT, char *pLayerName, long lExpectedVertices = 0);
Bool CreateTextObject (char *pLayerName, long lExpectedVertices = 0);
Bool CreateSymbolObject (char *pLayerName, char *pBlockName, long lExpectedVertices = 0);
Bool EchteLinie (Punkt *pPt1, Punkt *pPt2);
Bool BildMasseOk (void);
Bool UserBlock (int iFlag);
Bool SystemBlock (int iFlag);
void IncCounter (long ObjNr = 0); 
BOOL ValidFlag (int);
Bool Output (DGeoObj *& pObj);			//	lokale Ausgabe-Funktion
Bool InsertBlock (char *pBlockName);	//	Block einfügen

// externe Variablen
extern double XMin;		 // Bildmaße
extern double YMin;
extern double XMax;
extern double YMax;
// KK000125 - LIMMIN/LIMMAX
extern double XLMin;		 // Bildmaße
extern double YLMin;
extern double XLMax;
extern double YLMax;
//
extern RechercheStatus *pRechStat;      // RechercheStatus
extern Params OptParams;
extern CLayerBaum *g_pLB;
extern CBlockTree *g_pBlockTree;

// lokale Variablen
static DGeoObj *l_pDGO = NULL;	
static CTextObject *l_pTextObject = NULL;
static CSymbolObject *l_pSymbolObject = NULL;
static Bool bInBlockSection = False;
static Bool bOutputNetzError = False;
static Bool bOutputVersionError = False;

//	Datentypen
struct tripel_struct {
	double real1;
	double real2;
	double real3;
};
struct {
	struct tripel_struct params_tripel;
	double params_real1;
	double params_real2;
	double params_real3;
	short params_integer;
} Params;		

// Inline-Funktionen
inline
void SetXCon (double X) { if (X < XMin) XMin = X; if (X > XMax) XMax = X; }
inline
void SetYCon (double Y) { if (Y < YMin) YMin = Y; if (Y > YMax) YMax = Y; }
// KK000125
inline
void SetXLCon (double X) { if (X < XLMin) XLMin = X; if (X > XLMax) XLMax = X; }
inline
void SetYLCon (double Y) { if (Y < YLMin) YLMin = Y; if (Y > YLMax) YLMax = Y; }

inline
void InitParams (void) { Params.params_real1 = Params.params_real2 = Params.params_real3 =
						 Params.params_tripel.real1 = Params.params_tripel.real2 = Params.params_tripel.real3 = 0.0; 
						 Params.params_integer = InValidFlag; }
inline
Bool EchteLinie (Punkt *pPt1, Punkt *pPt2)
{
	return ((pPt1 -> X () != pPt2 -> X ()) ||
			(pPt1 -> Y () != pPt2 -> Y ()));
			/* (pPt1 -> Z () != pPt2 -> Z ()); Höhe bisher nicht geprüft */
}
inline 
Bool BildMasseOk (void)
{
	return ((DBL_MIN != XMax) && (DBL_MIN != YMax) && (DBL_MAX != XMin) && (DBL_MAX != YMin));
}
inline
Bool ValidFlag (int fl)
{
	return 	((fl >= ValidVertex && fl != VKP_Vertex) || 
			/* fl == 1 ||*/ fl == 0 || fl == InValidFlag);
}
typedef union  {
	struct {
		double real1;
		double real2;
		double real3;
	} real_struct; 
	short integer;
	char *str_ptr;
	double real;				
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define FLAG0 257
#define FLAG1 258
#define VERTEX_COUNT 259
#define KOORD 260
#define KOORD_X 261
#define KOORD_Y 262
#define KOORD_Z 263
#define FLOAT 264
#define FLOAT1 265
#define FLOAT2 266
#define FLOAT4 267
#define FLOAT5 268
#define WINKEL0 269
#define WINKEL1 270
#define TEXT0 271
#define LAYER_NAME 272
#define NAME 273
#define WINKEL 274
#define TEXT_HOEHE 275
#define ANFANG 276
#define SECTION 277
#define END_SECT 278
#define END_OF_FILE 279
#define ENTITIES 280
#define HEADER 281
#define BLOCKS 282
#define TABLES 283
#define VERSION 284
#define EXT_MIN 285
#define EXT_MAX 286
#define LAST_EDIT 287
#define LEX_ERROR 288
#define LINE 289
#define POLY_LINE 290
#define VERTEX 291
#define SEQEND 292
#define CIRCLE 293
#define ARC 294
#define TEXT_ELEM 295
#define POINT 296
#define INSERT 297
#define TRACE_ELEM 298
#define SOLID 299
#define SHAPE 300
#define ATTRIB 301
#define LIM_MIN 302
#define LIM_MAX 303
#define BLOCK 304
#define ENDBLK 305
#define LWPOLY_LINE 306
YYSTYPE yylval, yyval;
#define YYERRCODE 256

Bool CreateDGeoObj (DGeoTyp DGT, char *pLayerName, long lExpectedVertices)
{
	if (!pLayerName)
	{
		yyerror (IDS_SYSERROR);
		return False;				
	}
	l_pDGO = new DGeoObj;
	if (l_pDGO && l_pDGO -> Init (DGT, pLayerName, lExpectedVertices))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	Text-Objekt erzeugen
Bool CreateTextObject (char *pLayerName, long lExpectedVertices)
{
//	prüfe Parameter
	if (!pLayerName || !*pLayerName)
		return False;

//	neues Objekt erzeugen
	l_pTextObject = new CTextObject;
	if (l_pTextObject && l_pTextObject->Init (DGT_Text, pLayerName, lExpectedVertices))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	Insertobjekt erzeugen (Symbol, long lExpectedVertices)
Bool CreateSymbolObject (char *pLayerName, char *pBlockName, long lExpectedVertices)
{
//	prüfe Parameter
	if (!pLayerName || !*pLayerName || !pBlockName || !*pBlockName)
		return False;

//	neues Objekt erzeugen
	l_pSymbolObject = new CSymbolObject;
	if (l_pSymbolObject && l_pSymbolObject->Init(DGT_Symbol, pLayerName, lExpectedVertices) &&
		l_pSymbolObject->SetBlockName (pBlockName))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	lokale Ausgabe-Funktion
Bool Output (DGeoObj *& pObj)
{
//	prüfe Parameter
	assert (NULL != pObj);

	if (NULL == pObj)
		return False;

	Bool bRet = False;			//	noch nichts getan

	if (bInBlockSection)
	{
		assert (NULL != g_pBlockTree);
		bRet = g_pBlockTree -> AddObject (pObj);
		IncCounter ();

	//	altes DGeoObj wird hier nicht gelöscht
		pObj = NULL;
	}
	else
	{
		bRet = pObj -> Output () != 0;
		DELETE_OBJ (pObj);		/* Objekt wieder freigeben */		
	}

	return bRet;
}

//	Block einfügen ?? 
Bool InsertBlock (char *pBlockName)
{
	if (!pBlockName || !*pBlockName)
		return False;

	Bool bIsUserBlock = pBlockName [0] != '*';
	if (bIsUserBlock)		//	diese Blöcke werden immer importiert
		return True;

//	hier entscheidet die Nutzereinstellung
	return OptParams.m_bImpSystemBlocks;
}
	
#include <stdio.h>
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

int yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  -1, 55,
  292, 99,
  301, 99,
  -2, 84,
  0,
};

#define YYNPROD 122
#define YYLAST 336

int yyact[] = {
      16,     128,      64,     147,     108,     147,     108,     134,
     132,     133,     192,      79,     148,      70,      16,      73,
      71,      72,      69,     102,     174,     100,     165,     126,
     127,     101,     162,      68,      68,     176,     169,     175,
      17,      47,      61,     166,     163,      48,      58,      59,
      49,      63,      51,      52,      54,      16,      17,      47,
      61,     164,      62,      48,      58,      59,      49,      63,
      51,      52,      54,      16,     156,     122,     123,     130,
      62,      79,     125,      84,     124,     118,     119,     121,
     120,     117,     113,      83,     191,      17,      47,      61,
     112,      33,      48,      58,      59,      49,      63,      51,
      52,      54,      16,      17,      47,      61,      16,      62,
      48,      58,      59,      49,      63,      51,      52,      54,
     103,      79,     167,      96,      92,      62,      16,      95,
      74,      93,      94,      14,      76,      15,      27,      28,
      30,      32,      17,      88,      87,      86,      17,      79,
      79,     180,     138,     158,      20,      79,     161,     135,
      29,      31,      27,      28,      30,      32,      17,     155,
     111,     186,     181,      79,     178,     160,      91,     152,
     154,      90,      35,     115,      29,      31,      78,      98,
     106,     145,      34,      66,      46,      10,      21,      10,
       3,     151,     107,      18,      57,     105,      56,     146,
      26,     114,      60,      77,      80,      81,      82,     104,
      26,      55,      75,      97,      53,      85,      89,      50,
      45,      44,      43,      42,      41,      40,      39,      38,
      37,      36,      12,      67,      99,      65,      13,      25,
      24,      23,      22,     116,      19,      11,       9,       8,
     110,       7,       6,       5,       4,       2,       1,     109,
       0,       0,       0,       0,       0,     129,     131,       0,
       0,       0,       0,       0,       0,     136,     137,     139,
       0,       0,       0,       0,     140,       0,     141,     142,
      99,       0,       0,       0,       0,       0,     144,       0,
       0,     143,     153,       0,       0,       0,       0,       0,
       0,     116,     150,     149,     157,       0,     159,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,      85,     168,
       0,     170,       0,       0,     172,     173,     171,       0,
       0,       0,       0,       0,       0,       0,     153,     177,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,     179,       0,       0,       0,
       0,       0,       0,     183,     184,     182,       0,     185,
       0,       0,       0,     187,     188,       0,     189,     190,
};

int yypact[] = {
    -162,   -1000,    -162,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -146,    -197,    -276,    -265,   -1000,
   -1000,   -1000,   -1000,    -166,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -155,    -133,    -133,    -133,    -133,
    -189,   -1000,    -211,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -147,
    -148,    -149,    -156,    -161,    -165,    -250,    -168,   -1000,
    -285,    -117,    -192,    -198,    -196,    -204,    -206,    -249,
   -1000,    -277,   -1000,    -242,    -264,    -271,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -127,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -133,    -134,
    -133,   -1000,    -156,   -1000,   -1000,   -1000,   -1000,    -133,
    -133,    -250,   -1000,   -1000,   -1000,   -1000,   -1000,    -133,
    -289,    -287,   -1000,    -114,    -212,    -117,   -1000,    -131,
   -1000,   -1000,    -196,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,    -108,    -125,    -247,    -236,
   -1000,   -1000,   -1000,    -256,    -251,    -237,   -1000,    -157,
    -133,    -234,    -133,   -1000,    -156,    -133,    -133,   -1000,
    -253,   -1000,   -1000,    -241,    -243,   -1000,   -1000,    -114,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,    -109,   -1000,   -1000,   -1000,    -128,    -111,   -1000,
   -1000,   -1000,   -1000,    -156,    -133,    -133,   -1000,   -1000,
    -133,   -1000,   -1000,    -112,    -133,    -133,   -1000,    -133,
    -133,    -195,   -1000,   -1000,   -1000,   -1000,   -1000,    -263,
   -1000,
};

int yypgo[] = {
       0,     150,     158,     223,     222,     221,     168,     220,
     219,     218,     217,     215,     214,     164,     213,     212,
     166,     210,     209,     208,     207,     206,     205,     163,
     203,     162,     202,     154,     201,     200,     199,     198,
     197,     196,     195,     194,     193,     192,     191,     190,
     153,     188,     187,     159,     185,     183,     161,     178,
     177,     155,     175,     174,     173,     172,     160,     170,
     169,     151,
};

int yyr1[] = {
       0,       4,       5,       5,       6,       6,       6,       6,
       6,       6,       6,      13,      13,      12,      10,      11,
       7,       7,      14,      15,      15,      16,      16,      16,
      16,      16,      17,      18,      18,      19,      19,      20,
       1,       1,       2,       9,       9,      21,      22,      22,
      23,      23,      24,      24,      24,       8,       8,      26,
      25,      25,      27,      27,      27,      27,      27,      27,
      27,      27,      27,      27,      27,      28,      29,      29,
      30,      31,      38,      39,      40,      40,      40,      40,
      32,      33,      33,      34,      41,      42,      42,      43,
      43,      43,      43,      35,      36,      36,      44,      47,
      47,      48,      48,      49,      49,      49,      49,      49,
      49,      49,      49,      45,      45,      50,      46,      46,
      37,      37,      51,      51,      53,      53,      52,      52,
      54,      55,      55,      56,      56,      57,      57,      57,
       3,       3,
};

int yyr2[] = {
       0,       1,       1,       2,       1,       1,       1,       1,
       1,       1,       1,       1,       1,       1,       3,       2,
       3,       2,       2,       1,       2,       1,       1,       1,
       1,       1,       2,       2,       2,       2,       2,       2,
       1,       3,       2,       2,       3,       2,       1,       2,
       2,       3,       5,       5,       5,       2,       3,       2,
       1,       2,       1,       1,       1,       1,       1,       1,
       1,       1,       1,       1,       1,       4,       4,       4,
       3,       2,       2,       4,       1,       1,       1,       1,
       6,       5,       6,       2,       2,       1,       2,       1,
       1,       1,       1,       4,       1,       3,       2,       3,
       3,       1,       2,       1,       1,       1,       1,       1,
       1,       1,       1,       0,       2,       5,       1,       2,
       3,       2,       2,       3,       3,       4,       1,       2,
       2,       1,       2,       1,       2,       1,       1,       1,
       1,       2,
};

int yychk[] = {
   -1000,      -4,      -5,      -6,      -7,      -8,      -9,     -10,
     -11,     -12,     -13,     -14,     -26,     -21,     277,     279,
     256,     288,      -6,     -15,     278,     -16,     -17,     -18,
     -19,     -20,     -13,     284,     285,     302,     286,     303,
     287,     278,     -25,     -27,     -28,     -29,     -30,     -31,
     -32,     -33,     -34,     -35,     -36,     -37,     -13,     289,
     293,     296,     -38,     298,     299,     -41,     300,     -44,
     -51,     -53,     294,     295,     -47,     290,     306,     297,
     278,     -22,     -23,     -24,     304,     283,     278,     281,
     282,     280,     278,     -16,     271,      -1,      -2,     261,
      -1,      -1,      -1,     264,     278,     -27,     272,     272,
     272,     -39,     -40,      -1,     264,     269,     270,     272,
     272,     -42,     -43,      -1,     271,     275,     269,     272,
     -45,     -52,     -54,     -55,     291,      -3,      -2,     261,
     272,     272,     -48,     -49,      -1,     269,     265,     266,
     268,     267,     257,     258,     272,     272,     272,     273,
     278,     -23,     305,     -25,     272,     273,     278,     262,
      -1,      -1,     264,      -1,     -40,      -1,      -1,     -43,
      -1,     -46,     -50,     292,     301,     -46,     -54,     -56,
     -57,      -1,     266,     257,     272,      -2,     262,     -49,
     257,     259,     273,     272,     305,     273,     272,     263,
      -1,     264,      -1,     -40,      -1,      -1,     273,     272,
     272,     -57,     257,      -1,     257,     257,     -40,      -1,
      -1,      -1,     257,      -1,      -1,      -1,      -1,     271,
     273,
};

int yydef[] = {
       0,      -2,       1,       2,       4,       5,       6,       7,
       8,       9,      10,       0,       0,       0,       0,      13,
      11,      12,       3,       0,      17,      19,      21,      22,
      23,      24,      25,       0,       0,       0,       0,       0,
       0,      45,       0,      48,      50,      51,      52,      53,
      54,      55,      56,      57,      58,      59,      60,       0,
       0,       0,       0,       0,       0,       0,       0,      -2,
       0,       0,       0,       0,       0,       0,       0,       0,
      35,       0,      38,       0,       0,       0,      15,      18,
      37,      47,      16,      20,      26,      27,      32,       0,
      28,      29,      30,      31,      46,      49,       0,       0,
       0,      65,       0,      68,      69,      70,      71,       0,
       0,      75,      77,      79,      80,      81,      82,       0,
       0,       0,     110,       0,     113,     105,     120,       0,
      66,      76,      86,      89,      91,      92,      93,      94,
      95,      96,      97,      98,     106,       0,       0,       0,
      36,      39,      40,       0,       0,       0,      14,      34,
       0,       0,       0,      64,       0,       0,       0,      78,
       0,      85,     100,     102,       0,     104,     111,     112,
     115,     117,     118,     119,     114,     121,      34,      90,
     107,     108,      87,      88,      41,       0,       0,      33,
      61,      62,      63,       0,       0,       0,      83,     103,
       0,     116,     109,       0,       0,       0,      67,       0,
      73,       0,      42,      43,      44,      72,      74,       0,
     101,
};

int *yyxi;
/*****************************************************************/
/* PCYACC LALR parser driver routine -- a table driven procedure */
/* for recognizing sentences of a language defined by the        */
/* grammar that PCYACC analyzes. An LALR parsing table is then   */
/* constructed for the grammar and the skeletal parser uses the  */
/* table when performing syntactical analysis on input source    */
/* programs. The actions associated with grammar rules are       */
/* inserted into a switch statement for execution.               */
/*****************************************************************/


#ifndef YYMAXDEPTH
#define YYMAXDEPTH 200
#endif
#ifndef YYREDMAX
#define YYREDMAX 1000
#endif
#define PCYYFLAG -1000
#define WAS0ERR 0
#define WAS1ERR 1
#define WAS2ERR 2
#define WAS3ERR 3
#define yyclearin pcyytoken = -1
#define yyerrok   pcyyerrfl = 0
YYSTYPE yyv[YYMAXDEPTH];     /* value stack */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */


yyparse()
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, tmptoken, *yyps, n;
  YYSTYPE *yypv;


  tmpstate = 0;
  pcyytoken = -1;
#ifdef YYDEBUG
  tmptoken = -1;
#endif
  pcyyerrct = 0;
  pcyyerrfl = 0;
  yyps = &statestack[-1];
  yypv = &yyv[-1];


  enstack:    /* push stack */
#ifdef YYDEBUG
    printf("at state %d, next token %d\n", tmpstate, tmptoken);
#endif
    if (++yyps - &statestack[YYMAXDEPTH-1] > 0) {
      yyerror (IDS_SYSERROR);
      return(1);
    }
    *yyps = tmpstate;
    ++yypv;
    *yypv = yyval;


  newstate:
    n = yypact[tmpstate];
    if (n <= PCYYFLAG) goto defaultact; /*  a simple state */


    if (pcyytoken < 0) if ((pcyytoken=yylex()) < 0) pcyytoken = 0;
    if ((n += pcyytoken) < 0 || n >= YYLAST) goto defaultact;


    if (yychk[n=yyact[n]] == pcyytoken) { /* a shift */
#ifdef YYDEBUG
      tmptoken  = pcyytoken;
#endif
      pcyytoken = -1;
      yyval = yylval;
      tmpstate = n;
      if (pcyyerrfl > 0) --pcyyerrfl;
      goto enstack;
    }


  defaultact:


    if ((n=yydef[tmpstate]) == -2) {
      if (pcyytoken < 0) if ((pcyytoken=yylex())<0) pcyytoken = 0;
      for (yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=tmpstate); yyxi += 2);
      while (*(yyxi+=2) >= 0) if (*yyxi == pcyytoken) break;
      if ((n=yyxi[1]) < 0) { /* an accept action */
        if (yytflag) {
          int ti; int tj;
          yytfilep = fopen(yytfilen, "w");
          if (yytfilep == NULL) {
            fprintf(stderr, "Can't open t file: %s\n", yytfilen);
            return(0);          }
          for (ti=redcnt-1; ti>=0; ti--) {
            tj = svdprd[redseq[ti]];
            while (lstrcmp(svdnams[tj], "$EOP"))
              fprintf(yytfilep, "%s ", svdnams[tj++]);
            fprintf(yytfilep, "\n");
          }
          fclose(yytfilep);
        }
        return (0);
      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror (IDS_SYNTAXERR);
          yyerrlab:
            ++pcyyerrct;
        case WAS1ERR:
        case WAS2ERR:           /* try again */
          pcyyerrfl = 3;
	   /* find a state for a legal shift action */
          while (yyps >= statestack) {
	     n = yypact[*yyps] + YYERRCODE;
	     if (n >= 0 && n < YYLAST && yychk[yyact[n]] == YYERRCODE) {
	       tmpstate = yyact[n];  /* simulate a shift of "error" */
	       goto enstack;
            }
	     n = yypact[*yyps];


	     /* the current yyps has no shift on "error", pop stack */
#ifdef YYDEBUG
            printf("error: pop state %d, recover state %d\n", *yyps, yyps[-1]);
#endif
	     --yyps;
	     --yypv;
	   }


	   yyabort:
            if (yytflag) {
              int ti; int tj;
              yytfilep = fopen(yytfilen, "w");
              if (yytfilep == NULL) {
                fprintf(stderr, "Can't open t file: %s\n", yytfilen);
                return(1);              }
              for (ti=1; ti<redcnt; ti++) {
                tj = svdprd[redseq[ti]];
                while (lstrcmp(svdnams[tj], "$EOP"))
                  fprintf(yytfilep, "%s ", svdnams[tj++]);
                fprintf(yytfilep, "\n");
              }
              fclose(yytfilep);
            }
	     return(1);


	 case WAS3ERR:  /* clobber input char */
#ifdef YYDEBUG
          printf("error: discard token %d\n", pcyytoken);
#endif
          if (pcyytoken == 0) goto yyabort; /* quit */
	   pcyytoken = -1;
	   goto newstate;      } /* switch */
    } /* if */


    /* reduction, given a production n */
#ifdef YYDEBUG
    printf("reduce with rule %d\n", n);
#endif
    if (yytflag && redcnt<YYREDMAX) redseq[redcnt++] = n;
    yyps -= yyr2[n];
    yypvt = yypv;
    yypv -= yyr2[n];
    yyval = yypv[1];
    m = n;
    /* find next state from goto table */
    n = yyr1[n];
    j = yypgo[n] + *yyps + 1;
    if (j>=YYLAST || yychk[ tmpstate = yyact[j] ] != -n) tmpstate = yyact[yypgo[n]];
    App :: Exec (ExecWhileEvent); if (pRechStat && pRechStat -> Break () ) return(0);
switch (m) { /* actions associated with grammar rules */
      
      case 11:{  
      			   yyclearin; 		
      			   // return False;
      			} break;
      case 12:{
      			   return FALSE;			// Fehler bereits ausgegeben
      			} break;
      case 13:{   // Ende
      				if (pRechStat)
      					pRechStat -> SetValue (OptParams.MaxLineNr);
      				return OptParams.BildMasseOk ? True : -1;
      			} break;
      case 16:{
      				Header HD;
      				if (! HD.GetScaleAndOffset ())	// können aber nicht ausgegegben
      					return False;				// werden
      			// 	Scale und Offset ggf.ausgeben	
      				if (!OptParams.BildMasseOk)		// Matrix vorhanden ?
      				{	// nein
      					if (BildMasseOk ())		// die ermittelten XMax usw. sind Ok
      					{
      						if (! HD.OutScaleAndOffset ())	// können aber nicht ausgegegben
      							return False;				// werden
      						OptParams.BildMasseOk = True;
      						ResString strImpText (ResID (IDS_IMPORTTEXT, &g_pTE -> RF ()), 80);
      						if (pRechStat)		// Importtext ausgeben
      							pRechStat -> _ActionText.SetText ((char *)strImpText.Addr ());
      					}
      				}					
      			} break;
      case 17:{	// leere Section: Checklauf zur Bestimmung der Bildmaße ggf. durchführen
      				// Scale und Offset ggf. ausgeben	
      			} break;
      case 26:{
      				// Version prüfen
      				if (yypvt[-0].str_ptr && (strlen (yypvt[-0].str_ptr) > 2) && (atoi (yypvt[-0].str_ptr+2) > MaxAutoCadVersion) &&
      					!bOutputVersionError)
      				{
      					bOutputVersionError = True;		//	diese Meldung nicht noch einmal
      
				//	Anfrage an Nutzer, ob weiter gemacht werden soll ?
      					:: MessageBeep (MB_OK);					
      					ResString strCaption (ResID (IDS_PARSERERRORCAP, & g_pTE -> RF ()), 20);
      					ResString strText (ResID (IDS_ACAD_VERSION, & g_pTE -> RF ()), 200);																					
      					MessBox MB (strCaption.Addr (), strText.Addr (), g_pTE -> MWind ());
      					MB.SetType (YesNoButtons | QuestionMarkIcon);
      					if (NoReply == MB.Show ())
      					{
      						DELETE_VEC (yypvt[-0].str_ptr);
      						return False;
      					}
      				}
      
				DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 27:{
      				SetXCon (yypvt[-0].real_struct.real1);
      				SetYCon (yypvt[-0].real_struct.real2);
      			} break;
      case 28:{
      				SetXLCon (yypvt[-0].real_struct.real1);
      				SetYLCon (yypvt[-0].real_struct.real2);
      			} break;
      case 29:{
      				SetXCon (yypvt[-0].real_struct.real1);
      				SetYCon (yypvt[-0].real_struct.real2);
      			} break;
      case 30:{
      				SetXLCon (yypvt[-0].real_struct.real1);
      				SetYLCon (yypvt[-0].real_struct.real2);
      			} break;
      case 31:{
      				// evtl. julianische(s) Zeit/Datum ausgeben 
      			} break;
      case 33:{
      				yyval.real_struct.real1 = yypvt[-2].real + OptParams.XOffset;
      				yyval.real_struct.real2 = yypvt[-1].real + OptParams.YOffset;
      				yyval.real_struct.real3 = yypvt[-0].real;
      				if (!OptParams.BildMasseOk)
      				{
      					SetXCon (yyval.real_struct.real1);
      					SetYCon (yyval.real_struct.real2);
      					// IncCounter ();					
      				}
      			} break;
      case 34:{
      				yyval.real_struct.real1 = yypvt[-1].real + OptParams.XOffset;
      				yyval.real_struct.real2 = yypvt[-0].real + OptParams.YOffset;
      				if (!OptParams.BildMasseOk)
      				{
      					SetXCon (yyval.real_struct.real1);
      					SetYCon (yyval.real_struct.real2);					
      					// IncCounter ();
      				}
      				yyval.real_struct.real3 = DBL_MAX;
      			} break;
      case 35:{//	ohne Blöcke	
      				bInBlockSection = False;
      			} break;
      case 36:{//	mit Blöcken
      				bInBlockSection = False;
      			} break;
      case 37:{
      				bInBlockSection = TRUE;
      			} break;
      case 42:{
      				if (OptParams.BildMasseOk)
      				{
      					if (!g_pBlockTree->CreateBlock (yypvt[-2].str_ptr, yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2))
      						return False;
      				}
      			
      				DELETE_VEC (yypvt[-3].str_ptr);
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 43:{
      				if (OptParams.BildMasseOk)
      				{
      					if (!g_pBlockTree->CreateBlock (yypvt[-2].str_ptr, yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2))
      						return False;
      				}
      
				DELETE_VEC (yypvt[-3].str_ptr);
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 44:{
      				if (OptParams.BildMasseOk)
      				{
      					if (!g_pBlockTree->CreateBlock (yypvt[-3].str_ptr, yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2))
      						return False;
      				}
      
				DELETE_VEC (yypvt[-3].str_ptr);
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 47:{
      				bInBlockSection = False;				
      			} break;
      case 61:{	// Line
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-2].str_ptr))
      				{
      					DGeoTyp Type;
      					if (EchteLinie ((Punkt *) &yypvt[-1].real_struct, (Punkt *) &yypvt[-0].real_struct))
      						Type = DGT_Linie;
      					else
      						Type = DGT_Punkt;
      					if (CreateDGeoObj (Type, yypvt[-2].str_ptr) == False)
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)
      						return False;
      					if (Type == DGT_Linie) 
      					{
      						if (l_pDGO -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False)
      						{
      							yyerror (IDS_SYSERROR);							
      							return False;
      						}
      					}
      
				//	lokale Ausgabe-Funktion
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 62:{  	// Circle 
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-2].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-2].str_ptr) == False)
      						return False;
      					if (l_pDGO -> MakePolygon (yypvt[-0].real, yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 63:{  	// Circle 
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-2].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-2].str_ptr) == False)
      						return False;
      					if (l_pDGO -> MakePolygon (yypvt[-1].real, yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False)
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-2].str_ptr);
      			} break;
      case 64:{	// Point
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-1].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Punkt, yypvt[-1].str_ptr) == False)
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False)
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-1].str_ptr);
      			} break;
      case 65:{	// Arc ausgeben
      				if (OptParams.BildMasseOk && l_pDGO)
      				{
      					if (l_pDGO -> MakePolygon (Params.params_real1, 
      											 Params.params_tripel.real1, Params.params_tripel.real2,
      											 Params.params_real2, Params.params_real3) == False)
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      			} break;
      case 66:{//	ArcKopf
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-0].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-0].str_ptr) == False)
      						return False;
      					InitParams ();
      				}
      				DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 68:{//	Zentrum-Koordinaten speichern
      				Params.params_tripel.real1 = yypvt[-0].real_struct.real1;
      				Params.params_tripel.real2 = yypvt[-0].real_struct.real2;
      				Params.params_tripel.real3 = yypvt[-0].real_struct.real3;
      			} break;
      case 69:{//	Radius
      				Params.params_real1 = yypvt[-0].real;
      			} break;
      case 70:{//	Startwinkel
      				Params.params_real2 = yypvt[-0].real;
      			} break;
      case 71:{//	Stopwinkel
      				Params.params_real3 = yypvt[-0].real;
      			} break;
      case 72:{   // Trace
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-4].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-4].str_ptr) == False)
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-3].real_struct.real1, yypvt[-3].real_struct.real2) == False) // 1.
      						return False;		
      					if (l_pDGO -> AddPunkt (yypvt[-2].real_struct.real1, yypvt[-2].real_struct.real2) == False)	// 2.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)	// 3.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False) // 4.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-3].real_struct.real1, yypvt[-3].real_struct.real2) == False) // 1.
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}			
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-4].str_ptr);
      			} break;
      case 73:{	// Dreieck (Solid)
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-3].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-3].str_ptr) == False)
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-2].real_struct.real1, yypvt[-2].real_struct.real2) == False) // 1.
      						return False;		
      					if (l_pDGO -> AddPunkt (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)	// 2.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False)	// 3.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-2].real_struct.real1, yypvt[-2].real_struct.real2) == False) // 1.
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-3].str_ptr);
      			} break;
      case 74:{	// Viereck (Solid): hier ist der 3. mit dem 1. Pkt. zu verbinden !
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-4].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Flaeche, yypvt[-4].str_ptr) == False)
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-3].real_struct.real1, yypvt[-3].real_struct.real2) == False) // 1.
      						return False;		
      					if (l_pDGO -> AddPunkt (yypvt[-2].real_struct.real1, yypvt[-2].real_struct.real2) == False)	// 2.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2) == False)	// 4.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)	// 3.
      						return False;
      					if (l_pDGO -> AddPunkt (yypvt[-3].real_struct.real1, yypvt[-3].real_struct.real2) == False) // 1.
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();					
      				DELETE_VEC (yypvt[-4].str_ptr);
      			} break;
      case 75:{	//	Text ausgeben
      				if (OptParams.BildMasseOk && l_pTextObject)
      				{
      					if (!Output ((DGeoObj*&)l_pTextObject))
      						return False;	
      				}
      				else
      					IncCounter ();					
      			} break;
      case 76:{	//	Textkopf
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-0].str_ptr))
      				{
      					Bool bRet = CreateTextObject (yypvt[-0].str_ptr);
      					DELETE_VEC (yypvt[-0].str_ptr);
      
				//	ggf. zurück
      					if (!bRet)
      					{
      						yyerror (IDS_SYSERROR);
      						return False;					
      					}
      				}
      				else
      				{
      					DELETE_VEC (yypvt[-0].str_ptr);
      					IncCounter ();	
      				}									
      			} break;
      case 79:{	// Koordinate speichern
      				if (OptParams.BildMasseOk && l_pTextObject)
      					if (!l_pTextObject -> AddPunkt (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2))
      						return False;
      			} break;
      case 80:{//	Wert speichern
      				if (OptParams.BildMasseOk && l_pTextObject)
      				{
      					Bool bRet = l_pTextObject -> SetText (yypvt[-0].str_ptr);
      				
      				//	Text löschen
      					DELETE_VEC (yypvt[-0].str_ptr);
      
					if (!bRet)
      					{
      						yyerror (IDS_SYSERROR);
      						return False;
      					}
      				}
      				else
      					DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 81:{	// Höhe speichern
      			  	if (OptParams.BildMasseOk && l_pTextObject && OptParams.m_bImpTextHoehe)
      				{
      					Bool bRet = l_pTextObject -> SetHoehe (yypvt[-0].str_ptr);
      					if (!bRet)
      					{
      						yyerror (IDS_SYSERROR);
      						return False;
      					}
      				}
      				else
      					DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 82:{	//	Winkel speichern
      				if (OptParams.BildMasseOk && l_pTextObject && OptParams.m_bImpTextDrehWi)
      					l_pTextObject -> SetWinkel (yypvt[-0].real);					
      			} break;
      case 83:{	// Shape (Symbol)
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-2].str_ptr))
      				{
      					if (CreateDGeoObj (DGT_Punkt, yypvt[-2].str_ptr) == False) 	
      						return False;						
      					if (l_pDGO -> AddPunkt (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2) == False)
      						return False;
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();	
      				DELETE_VEC (yypvt[-2].str_ptr);
      				DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 84:{	
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      				{
      					if (!Output ((DGeoObj*&)l_pSymbolObject))
      //						return False;
      						break;	// KK991230
      				}	
      				else
      					IncCounter ();								
      			} break;
      case 85:{	
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      				{
      					if (!Output ((DGeoObj*&)l_pSymbolObject))
      //						return False;
      						break;	// KK991230
      				}
      				else
      					IncCounter ();	
      			} break;
      case 87:{
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-1].str_ptr) && InsertBlock (yypvt[-0].str_ptr))
      				{
      					if (!CreateSymbolObject (yypvt[-1].str_ptr, yypvt[-0].str_ptr))
      						return False;							
      				}								
      				DELETE_VEC (yypvt[-1].str_ptr);	
      				DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 88:{
      				if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-0].str_ptr) && InsertBlock (yypvt[-1].str_ptr))
      				{
      					if (!CreateSymbolObject (yypvt[-0].str_ptr, yypvt[-1].str_ptr))
      						return False;
      				}								
      				DELETE_VEC (yypvt[-1].str_ptr);	
      				DELETE_VEC (yypvt[-0].str_ptr);
      			} break;
      case 91:{//	Einfügepunkt speichern
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      				{
      					l_pSymbolObject->XInsert () = yypvt[-0].real_struct.real1;
      					l_pSymbolObject->YInsert () = yypvt[-0].real_struct.real2;
      				}
      			} break;
      case 92:{//	Symbol-Drehwinkel
      				if (OptParams.BildMasseOk && l_pSymbolObject && 
      					OptParams.m_bImpSymDrehWi)
      					l_pSymbolObject -> SetWinkel (yypvt[-0].real);
      			} break;
      case 93:{//	X-Masstabsfaktor
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->XMasstab () = yypvt[-0].real;
      			} break;
      case 94:{// Y-Masstabsfaktor
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->YMasstab () = yypvt[-0].real;
      			} break;
      case 95:{// Zeilenabstand
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->ZeilenAbstand () = yypvt[-0].real;
      			} break;
      case 96:{// Spaltenabstand
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->SpaltenAbstand () = yypvt[-0].real;
      			} break;
      case 97:{// Spalten
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->Spalten () = yypvt[-0].integer;
      			} break;
      case 98:{//	Zeilen
      				if (OptParams.BildMasseOk && l_pSymbolObject)
      					l_pSymbolObject->Zeilen () = yypvt[-0].integer;
      			} break;
      case 101:{	// Attrib: TEXT0 ist Merkmalswert und NAME Kurztext des Merkmals
      				if (OptParams.BildMasseOk && OptParams.bImpMerkmale && l_pSymbolObject) 
      				{
      					if (l_pSymbolObject -> AddMerkmal (yypvt[-0].str_ptr, yypvt[-1].str_ptr) == False)
      						return False;										
      				}	
      				DELETE_VEC (yypvt[-3].str_ptr);	
      				DELETE_VEC (yypvt[-1].str_ptr);	
      				DELETE_VEC (yypvt[-0].str_ptr);	
      			} break;
      case 103:{	// Seqend
      				DELETE_VEC (yypvt[-0].str_ptr);					
      			} break;
      case 104:{ // PolyLine	
      				if (OptParams.BildMasseOk && l_pDGO)
      				{
      					if (l_pDGO -> isA () == DGT_Flaeche)		// Linie schließen ?
      					{
      					//	letztes Segment
      						if (!l_pDGO -> AddFirstPunkt (
      							ValidFlag (Params.params_integer) ? Params.params_real1 : 0)) 
      						{
      							return False;		
      						}
      					}					
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();	
      			} break;
      case 105:{ // LWPolyLine	
      				if (OptParams.BildMasseOk && l_pDGO)
      				{
      					if (l_pDGO -> isA () == DGT_Flaeche)		// Linie schließen ?
      					{
      						if (!l_pDGO -> AddFirstPunkt()) 
      							return False;		
      					}					
      					if (!Output (l_pDGO))
      						return False;
      				}
      				else
      					IncCounter ();	
      			} break;
      case 106:{	// PolyLine
      			  	if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-0].str_ptr))
      				{
      					if (!CreateDGeoObj(DGT_Linie, yypvt[-0].str_ptr))
      						return False;			  	
      				}
      			  	DELETE_VEC (yypvt[-0].str_ptr);					
      			} break;
      case 107:{	// PolyLine
      			  	if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-1].str_ptr))
      				{
      					if (yypvt[-0].integer & iVielFlaechenNetz)
      					{
      					//	wird hier nicht behandelt
      					//	ggf. Fehlermeldung ausgeben
      						if (!bOutputNetzError)
      						{
      							bOutputNetzError = True;
      							yyerror (IDS_CAN_NOT_IMP_NETZ);
      						}
      					}
      					else
      					{
      			  			DGeoTyp Type = (yypvt[-0].integer & iPolylineClosed) ? DGT_Flaeche : DGT_Linie;
      			  			if (CreateDGeoObj (Type, yypvt[-1].str_ptr) == False)
      							return False;
      					}						
      				}
      			   	DELETE_VEC (yypvt[-1].str_ptr);					
      			} break;
      case 108:{	// LWPolyLine
      			  	if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-1].str_ptr))
      				{
      					if (!CreateDGeoObj(DGT_Linie, yypvt[-1].str_ptr, yypvt[-0].integer))
      						return False;			  	
      				}
      			  	DELETE_VEC (yypvt[-1].str_ptr);					
      			} break;
      case 109:{	// LWPolyLine
      			  	if (OptParams.BildMasseOk && g_pLB -> IsValid (yypvt[-2].str_ptr))
      				{
      					if (yypvt[-0].integer & iVielFlaechenNetz)
      					{
      					//	wird hier nicht behandelt
      					//	ggf. Fehlermeldung ausgeben
      						if (!bOutputNetzError)
      						{
      							bOutputNetzError = True;
      							yyerror (IDS_CAN_NOT_IMP_NETZ);
      						}
      					}
      					else {
      			  		DGeoTyp Type = (yypvt[-0].integer & iPolylineClosed) ? DGT_Flaeche : DGT_Linie;
      			  		
      						if (!CreateDGeoObj (Type, yypvt[-2].str_ptr, yypvt[-1].integer))
      							return False;
      					}						
      				}
      			   	DELETE_VEC (yypvt[-2].str_ptr);					
      			} break;
      case 112:{//	Stützpunkt-Parameter auswerten und ausgeben
      			 // Stützpunkt: mit optionaler folgender Ausbuchtung (wenn != 0)
      			 // wenn Flag <= 8, dann Anpassungspunkt u. weglassen
      				if (ValidFlag (Params.params_integer) && OptParams.BildMasseOk && l_pDGO)
      				{
      					if (! l_pDGO -> AddBogen (Params.params_tripel.real1, Params.params_tripel.real2, 
      											  Params.params_real1))
      						return False;
      				}
      			} break;
      case 113:{//	Stützpunkt-Parameter rücksetzen
      				InitParams ();
      			} break;
      case 114:{//	Stützpunkt-Parameter rücksetzen
      				InitParams ();
      				DELETE_VEC (yypvt[-0].str_ptr);						
      			} break;
      case 117:{//	Stützpunkt-Koordinaten speichern
      				Params.params_tripel.real1 = yypvt[-0].real_struct.real1;
      				Params.params_tripel.real2 = yypvt[-0].real_struct.real2;
      				Params.params_tripel.real3 = yypvt[-0].real_struct.real3;
      			} break;
      case 118:{//	opt. Ausbuchtung des Stützpunktes
      				Params.params_real1 = yypvt[-0].real;
      			} break;
      case 119:{//	Stützpunkt ist Anpassungspunkt
      				Params.params_integer = yypvt[-0].integer;
      			} break;
      case 120:{//	Stützpunkt-Parameter auswerten und ausgeben
      				if (OptParams.BildMasseOk && l_pDGO)
      				{
      					if (!l_pDGO -> AddBogen (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2))
      						return False;
      				}
      			} break;
      case 121:{//	Stützpunkt-Parameter auswerten und ausgeben
      				if (OptParams.BildMasseOk && l_pDGO)
      				{
      					if (!l_pDGO -> AddBogen (yypvt[-0].real_struct.real1, yypvt[-0].real_struct.real2))
      						return False;
      				}
      			} break;    }
    goto enstack;
}

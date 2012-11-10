
#include "pheader.h"

extern "C" {
	#include <limits.h>                 // DBL_MAX, LONG_MAX
//        #include <toolhelp.h>               // TIMERINFO
}

#include <hpp/filebuff.hxx>					// CFileBuffer

#include "tools.hxx"                    // TextObject
#define NOOPTPARAM
#include "optparam.hxx"                 // Params
#include "filepos.hxx"                  // PointEntries
#include "merkmal.hxx"                  // MerkmalsBaum
#include "rechstat.hxx"                 // RechercheStatus
#include "textconn.hxx"					// CDataInfoList

#pragma warning (disable: 4101 4102 )

//  Konstanten
const short SinglePrecL = 4;          	// Längen der Datentypen
const short DoublePrecL = 8;			// (inten)
const short SinglePrecLen = 14;			// Länge einer Real-Zahl bei Single/ 
const short DoublePrecLen = 24;			// Double-Precision (Ausgabe)
const short IntegerShortL = 2;			// short Integer-Zahl (intern)
const short IntegerDoubleL = 4;			// double Integer-Zahl
const short IntegerShortLen = 6;		// Länge der short Integer Zahl	
const short IntegerDoubleLen = 11;		// Länge der double Integer Zahl (Ausgabe)	
const short DateMLength = 8;

//  externe Variablen
extern FILE *yyin;                      // Eingabe-Datei
extern MerkmalsBaum *pMDT;              // Merkmalsbaum
extern PointEntries *pPE;               // Punkte-Tabelle
extern LineEntries *pLE;                // Linien-Tabelle
extern PalEntries *pPlE;                // Pal-Tabelle
extern long SecPos;                     // Datei-Position der 1. Arc-Koordinate
extern Params *pParams;                 // Parameterfeld
extern RechercheStatus *pRechStat;      // RechercheStatus
extern HWND __hWndM;
extern CTextDatInfoList *pTDI;			// OBDC-Info speichern

//  Prototypen
int yylex ();
Bool CreateTextObj (void);
Bool AddMerkmal (long AddFlag, long Laenge, pchar pMName = NULL, Bool UserIDFeld = False);
Bool ResetTables (void);
void OutKonvMess (DGeoTyp);

//  Variablen
short Result = True;
TextObject *pTO = NULL;                 // akt. GeoObjekt
long ActFieldCnt = LONG_MAX;            // akt. Feldanzahl
Bool PolyOut = True;                    // Ausgabe-Flags (alles ausgegeben)
Bool PointOut = True;
Bool LineOut = True;
Bool TellArcs = False;                  // Arc-Positionen nicht speichern
Bool bReadText = False;					// Lese-Text-Flag
typedef union  {
	struct {
		double real1;
		double real2;
		char *p_real_str;
	} real_struct;
	struct {
		long int1;
		long int2;
		long int3;
		char *str_ptr1;
	} int_struct;
	long integer;
	char *str_ptr;
	double real;                            
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define REAL 257
#define INT 258
#define TEXTVAL 259
#define USER_ID_FIELD 260
#define QSTRING 261
#define USER_FIELD_PARAMS 262
#define PAT_FILE_NAME 263
#define AAT_FILE_NAME 264
#define TIC_FILE_NAME 265
#define BND_FILE_NAME 266
#define OTHER_FILE_NAME 267
#define COVER_BEGIN 268
#define COVER_ENDE 269
#define IFO_BEGIN 270
#define IFO_ENDE 271
#define ARC 272
#define CNT 273
#define TXT 274
#define PAL 275
#define LAB 276
#define TOL 277
#define ID_FIELD 278
#define LENGTH 279
#define FIRST_NODE 280
#define LAST_NODE 281
#define LEFT_POLY 282
#define RIGHT_POLY 283
#define XMIN 284
#define YMIN 285
#define XMAX 286
#define YMAX 287
#define ID_TIC 288
#define XTIC 289
#define YTIC 290
#define AREA 291
#define PERIMETER 292
#define EOL 293
#define COMMAND 294
#define PATH 295
#define COMMAND_ENDE 296
#define SIN_BEGIN 297
#define SIN_ENDE 298
#define LOG_BEGIN 299
#define LOG_ENDE 300
#define TX_BEGIN 301
#define LX_ERROR 302
YYSTYPE yylval, yyval;
#define YYERRCODE 256


Bool CreateTextObj (void)
{
	pTO = new TextObject;
	if (!pTO) {
		DEX_Error (RC_ArcTriasYacc, EC_NOMEMORY);
		return False;
	}
	return True;
}

//  "überwacht" Lesen der MerkmalsFelder
Bool AddMerkmal (long AddFlag, long La, pchar pMName, Bool StoreUserIdField) {
//  Merkmals-Beschreibung nur aufnehmen, wenn Sätze folgen
	if (pMDT -> Cnt () == 0)
		return True;
	if (AddFlag > 0)
	{
		if (!pMDT -> AddMerkmal ((short) La, pMName, StoreUserIdField))
			return False;
	}

//  Test: letztes Feld ?
	if (--ActFieldCnt != 0L)
		return True;

	ActFieldCnt = LONG_MAX;                         // auf ungültigen Wert setzen
	
//  Merkmale einschließlich Geometrie ausgeben
	Entries *pE = NULL;
	Bool Output = False;							// Daten explizit nicht ausgeben
	Bool CheckUniPoly = False;						// Universe-Polygon
	DGeoTyp DGT = DGT_Unknown;
	
	switch (pMDT -> _TableType)
	{
		case PatTable:
		{
			if (pParams -> PalExist)				// Polygontopologie liegt vor
			{   
				pParams -> PalExist = False;		// Topologie wird nach Abarbeitung ungültig
				CheckUniPoly = True;				// 1. Merkmalszeile überlesen           
				PolyOut = True;                  	// Flächen werden jetzt behandelt
				if (pParams -> ImpFlaechen)
				{
					Output = True;					// Flächen importieren
					DGT = DGT_Flaeche;
					
				// 	Konvertierung vorbereiten
					pLE -> Optimize ();				// Linientabelle
					pE = (Entries *) pPlE;   		// Paltabelle
					pE -> Optimize ();										            					
					
				//	Ausgabe-Flags für weitere Abarbeitung setzen
					PointOut = True;				 // Punkte werden ignoriert										
                                        DELETE_OBJ (pPE);                    // PunktListe wird nicht mehr benötigt
				}
			}
			else    								 // Punkte sind im Cover vorhanden
			{
				pE = (Entries *) pPE;
				if (pE -> Count () < (ulong) pMDT -> Cnt ())
					CheckUniPoly = True;				 // 1. Merkmalszeile überlesen           
				else
					CheckUniPoly = False;				 // 1. Merkmalszeile verarbeiten           
				PointOut = True;					 // Punkte werden jetzt behandelt
				if (pParams -> ImpPunkte)
				{
					pE -> Optimize ();
					DGT = DGT_Punkt;                               
					Output = True;
				}                               
            }
		}
		break;  
		case AatTable:								// Linien-Tabelle
		{
			LineOut = True;                         // Linien werden jetzt behandelt
			pE = (Entries *) pLE;
			if (pParams -> ImpLinien)
			{
				pE -> Optimize ();
				DGT = DGT_Linie;                                                                        
				Output = True;					
			}	
		}
		break;
		case OtherTable:							// andere Tabelle als Textdatei
		{
			if (pParams -> ImpTabellen)
			{
				pParams -> TableCnt++;				// Zähler erhöhen
				DGT = DGT_OtherTable;                                                   
				Output = True;					
			}				
		}
		break;
		default:									// sollte nicht passieren
		{
			DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
			return False;
		}
	}
	
	OutKonvMess (DGT);      						// Text an Nutzer ausgeben
	return pMDT -> OutMerkmale (pE, CheckUniPoly, Output);
}

//  Tabellen ggf. ausgeben
Bool ResetTables (void) {
	Bool Ret = True;
	if (pParams -> PalExist && pParams -> ImpFlaechen && !PolyOut)  // es gibt Flächen
	{                                                               // die noch auszugegeben sind
		pParams -> PalExist = False;
		PolyOut = PointOut = True;
		if (!pPlE) 
		{
			DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
			Ret = False;
		} 
		else 
		{
			pLE -> Optimize ();
			pPlE -> Optimize ();
			Ret = pPlE -> OutAllGeo ();                             // alle Flächen ausgeben
		}                                                           
	}   
			
	if (Ret && !LineOut && pParams -> ImpLinien)                    // Linien sind noch nicht ausg.
	{
		LineOut = False;
		if (pLE) 
		{
			pLE -> Optimize ();
			Ret = pLE -> OutAllGeo ();                              // alle Linien ausgeben
		}
	}
			
	if (Ret && !PointOut && pParams -> ImpPunkte)                   // es gibt noch Punkte
	{
		PointOut = False;                                           // die noch auszugeben sind
		if (pPE) 
		{
			pPE -> Optimize ();
			Ret = pPE -> OutAllGeo ();                              // alle Punkte ausgeben
		}
	}

        DELETE_OBJ (pPE);                                           // Punkte-Tabelle löschen
        DELETE_OBJ (pLE);                                           // Linien-Tabelle löschen
        DELETE_OBJ (pPlE);                                          // Pal-Table löschen

	return Ret;
}


#include <stdio.h>
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

short yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  -1, 164,
  257, 38,
  -2, 48,
  0,
};

#define YYNPROD 109
#define YYLAST 340

short yyact[] = {
      27,      69,      80,       2,     130,      55,     123,     124,
     125,      27,     197,      80,      97,      81,      23,     198,
      17,      18,      20,      21,      19,      22,      28,      23,
     196,      17,      18,      20,      21,      19,      22,     194,
     192,      72,     190,     187,      72,     183,     128,      27,
      33,      24,       4,      25,      51,      26,      47,      27,
      39,      80,      24,      35,      25,      23,      26,      17,
      18,      20,      21,      19,      22,      23,     180,      17,
      18,      20,      21,      19,      22,      73,      74,      75,
      73,      74,      75,     126,     113,     178,     114,      33,
      24,      33,      25,      33,      26,      76,      33,     159,
      24,     177,      25,     175,      26,      80,     112,     109,
     105,     106,     107,     108,     174,     117,     118,     119,
     120,     173,     171,     110,     111,     159,     167,     166,
     163,     141,     137,     135,     132,     123,     124,     125,
     117,     118,     119,     120,      64,      65,      68,      67,
      66,     100,      93,      90,     101,      64,      65,      68,
      67,      66,      42,      84,     195,      56,      80,     164,
     138,     133,     131,      79,     158,     116,     104,      78,
     122,      71,      58,      31,      54,      50,      46,     140,
      43,      40,      38,      34,       5,       3,     156,     121,
      29,      63,      30,     115,      62,     103,      36,      61,
      44,      48,      52,      60,      59,      57,      45,      53,
      49,      41,      37,      87,      82,     184,     181,      32,
      70,      85,      77,      29,      83,      16,      15,      96,
      86,      91,      89,      88,      92,      94,      14,      95,
      13,      98,      99,      12,     102,      11,      10,       9,
       8,       7,       6,       1,       0,       0,       0,       0,
     127,       0,       0,       0,       0,     129,       0,       0,
       0,       0,       0,       0,       0,       0,     134,       0,
       0,       0,       0,       0,     136,       0,       0,       0,
       0,       0,       0,       0,       0,       0,     139,       0,
       0,       0,       0,       0,       0,       0,       0,     150,
       0,     151,     142,     143,     144,     145,     146,     147,
     148,     149,     157,       0,       0,     152,     153,     154,
     155,       0,     165,     160,     161,     162,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,     168,       0,       0,       0,       0,       0,
       0,     169,       0,     170,       0,       0,       0,       0,
       0,     172,       0,       0,       0,       0,       0,       0,
       0,     176,       0,       0,     179,       0,       0,     182,
       0,     185,     186,       0,     188,       0,     189,       0,
       0,     191,       0,     193,
};

short yypact[] = {
    -265,   -1000,    -217,    -247,    -209,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,    -207,    -210,    -120,    -212,    -214,    -253,    -130,
    -297,    -222,    -208,   -1000,   -1000,   -1000,    -256,   -1000,
    -207,   -1000,   -1000,    -119,   -1000,    -210,   -1000,    -115,
   -1000,    -120,    -127,   -1000,   -1000,    -212,   -1000,    -128,
   -1000,    -214,   -1000,    -246,   -1000,    -253,   -1000,    -129,
   -1000,    -139,   -1000,   -1000,   -1000,    -184,    -183,    -282,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -225,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,    -255,   -1000,    -257,
    -111,   -1000,   -1000,   -1000,    -142,   -1000,   -1000,   -1000,
   -1000,   -1000,    -112,   -1000,   -1000,    -143,   -1000,   -1000,
    -115,    -144,   -1000,   -1000,    -113,   -1000,   -1000,    -184,
   -1000,    -145,    -145,    -145,    -145,    -145,    -145,    -145,
    -145,    -145,   -1000,    -164,   -1000,    -145,    -145,    -145,
    -145,    -171,   -1000,    -145,    -145,    -145,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,    -146,    -114,    -115,    -147,
   -1000,   -1000,   -1000,   -1000,   -1000,    -148,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -115,   -1000,
   -1000,   -1000,   -1000,   -1000,    -149,   -1000,   -1000,    -115,
   -1000,   -1000,   -1000,    -152,   -1000,    -115,    -153,    -158,
   -1000,   -1000,   -1000,    -167,   -1000,    -115,    -169,    -181,
    -115,    -196,   -1000,    -115,    -221,    -115,    -115,    -223,
    -115,   -1000,    -115,    -224,   -1000,    -115,    -226,    -115,
    -227,    -117,    -234,    -249,    -243,   -1000,   -1000,
};

short yypgo[] = {
       0,     147,     159,     219,     165,     164,     218,     217,
     216,     215,     214,     213,     211,     208,     206,     198,
     197,     194,     151,     192,     153,     155,     191,     163,
     190,     189,     186,     162,     161,     185,     160,     184,
     157,     183,     156,     182,     158,     181,     154,     180,
     179,     175,     173,     150,     172,     171,     149,     169,
     167,     166,     152,     148,
};

short yyr1[] = {
       0,       3,       3,       4,       4,       5,       5,       5,
       5,       5,       5,       5,       5,       5,       5,       5,
      16,      15,      15,      17,      17,      18,      13,      14,
      19,      19,      20,      20,      20,      20,       6,       6,
      22,      22,      24,      23,      25,      25,       1,      21,
       7,       7,      26,      26,      27,      27,       8,       8,
      28,      29,      29,      30,      10,      10,      31,      31,
      32,      32,      11,      11,      33,      33,      34,       9,
       9,      35,      35,      36,      12,      12,      37,      37,
      38,      38,      38,      41,      41,      41,       2,      42,
      42,      43,      43,      43,      43,      43,      43,      43,
      43,      43,      43,      39,      44,      45,      45,      46,
      46,      46,      46,      40,      47,      48,      48,      50,
      50,      50,      49,      49,      51,
};

short yyr2[] = {
       0,       3,       4,       1,       2,       1,       1,       1,
       1,       1,       1,       1,       1,       1,       1,       1,
       1,       2,       3,       1,       2,       2,       2,       3,
       1,       2,       1,       1,       1,       1,       2,       3,
       1,       2,       0,       9,       1,       2,       2,       1,
       2,       3,       1,       2,       1,       2,       2,       3,
       4,       1,       2,       5,       2,       3,       1,       2,
       3,       3,       2,       3,       1,       2,       3,       2,
       3,       1,       2,      14,       2,       3,       1,       2,
       1,       1,       2,       1,       1,       1,      12,       1,
       2,       2,       2,       2,       2,       2,       2,       2,
       2,       2,       1,       4,       1,       1,       2,       2,
       2,       2,       2,       3,       1,       1,       2,       2,
       2,       2,       1,       2,       2,
};

short yychk[] = {
   -1000,      -3,     268,      -4,     259,      -5,      -6,      -7,
      -8,      -9,     -10,     -11,     -12,     -13,     -14,     -15,
     -16,     272,     273,     276,     274,     275,     277,     270,
     297,     299,     301,     256,     269,      -5,      -4,     -21,
     -22,     293,     -23,     258,     -21,     -26,     -27,     258,
     -28,     -29,     258,     -30,     -21,     -35,     -36,     258,
     -21,     -31,     -32,     258,     -21,     -33,     -34,     258,
     271,     -37,     -38,     -39,     -40,     -41,     -44,     -47,
     263,     264,     267,     266,     265,     298,     -19,     -20,
     258,     294,     295,     296,     293,     -17,     -18,      -1,
     257,     269,     -21,     -23,     258,     -21,     -27,      -1,
     -28,     -30,     258,     -21,     -36,     258,     -21,     -32,
      -1,     258,     -21,     -34,     258,     271,     -38,     -42,
     -43,     280,     281,     282,     283,     279,     291,     292,
     278,     260,     262,     -45,     -46,     284,     285,     286,
     287,     -48,     -50,     288,     289,     290,     300,     -20,
     293,     -18,     261,     257,     258,     257,      -1,     258,
      -1,     258,     257,     -43,      -2,     258,      -2,      -2,
      -2,      -2,      -2,      -2,      -2,      -2,      -1,     -46,
      -2,      -2,      -2,      -2,     -49,     -50,     -51,     258,
      -2,      -2,      -2,     258,     257,      -1,     258,     258,
      -1,     -51,      -1,     258,      -1,     258,     258,     258,
      -1,     258,     258,      -1,     258,     -24,      -1,     258,
     -25,      -1,      -1,     258,      -1,      -1,     258,      -1,
     258,      -1,     258,     257,     258,     259,     258,
};

short yydef[] = {
       0,      -2,       0,       0,       0,       3,       5,       6,
       7,       8,       9,      10,      11,      12,      13,      14,
      15,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,      16,       1,       4,       0,      30,
       0,      39,      32,       0,      40,       0,      42,      44,
      46,       0,       0,      49,      63,       0,      65,       0,
      52,       0,      54,       0,      58,       0,      60,       0,
      68,       0,      70,      72,      73,       0,       0,       0,
      75,      76,      77,      92,     100,      22,       0,      24,
      26,      27,      28,      29,      17,       0,      19,       0,
       0,       2,      31,      33,       0,      41,      43,      45,
      47,      50,       0,      64,      66,       0,      53,      55,
       0,       0,      59,      61,       0,      69,      71,      74,
      79,       0,       0,       0,       0,       0,       0,       0,
       0,       0,      90,       0,      93,       0,       0,       0,
       0,       0,     101,       0,       0,       0,      23,      25,
      18,      20,      21,      38,       0,       0,       0,       0,
      56,      57,      62,      80,      81,       0,      82,      83,
      84,      85,      86,      87,      88,      89,       0,      94,
      95,      96,      97,      98,      99,     102,     106,       0,
     103,     104,     105,       0,      -2,       0,       0,       0,
      91,     107,     108,       0,      51,       0,       0,       0,
       0,       0,      34,       0,       0,       0,       0,       0,
      35,      36,       0,       0,      37,       0,       0,       0,
       0,       0,       0,       0,       0,      67,      78,
};

short *yyxi;
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
      DEX_Error(RC_ArcTriasYacc,EC_SYSERROR);
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
            
DEX_Error(RC_ArcTriasYacc,EC_SYSERROR);
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
          DEX_Error(RC_ArcTriasYacc,EC_SYNTAX);
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
                
DEX_Error(RC_ArcTriasYacc,EC_SYSERROR);
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
    if (pRechStat -> Break () ) return(0);
switch (m) { /* actions associated with grammar rules */
      
      case 1:{
      				return True;
      			} break;
      case 2:{
      				return True;
      			} break;
      case 16:{	         
      				char Buffer [80] = "";
      				wsprintf (Buffer, "Fehler in Zeile %ld !", pParams -> LineNr);
      				MessBox MB ("Syntax-Fehler", Buffer, pRechStat);
      				MB.SetType (OkayButton | ExclamationIcon);
      				MB.Show ();
      			  	// DEX_Error (RC_ArcTriasYacc, WC_UNKOWNTOKEN); 
      				yyclearin; 
      			} break;
      case 17:{
      				bReadText = False;        
      				OutKonvMess (DGT_Unknown);
      		      } break;
      case 18:{
      				bReadText = False;        
      				OutKonvMess (DGT_Unknown);
      			  } break;
      case 21:{
      			  	if (pParams -> ImpTexte && lstrlen (yypvt[-0].str_ptr) > 0)
      				{                                        
      					if (! CreateTextObj ())
      						return False;
      					pTO -> AddKoord (yypvt[-1].real_struct.real1, yypvt[-1].real_struct.real2);
      					pTO -> AddText (yypvt[-0].str_ptr); 
      					pTO -> Output ();
                                              DELETE_OBJ (pTO);  /* Objekt wieder freigeben */
      				}
      			  } break;
      case 31:{
      				LineOut = False;
      			} break;
      case 34:{   

      				if (pParams -> ImpFlaechen || pParams -> ImpLinien)
      				{
      					if (!pLE) 
      					{
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      					if (! pLE -> AddNrCnt (yypvt[-6].integer, yypvt[-0].integer)) // Nummer und Anz. Punkte sp.
      						return False;
      
					TellArcs = True;
      				}                                       
      			} break;
      case 36:{   
      				if (pParams -> ImpFlaechen || pParams -> ImpLinien)
      				{
      					if (!pLE) 
      					{
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      					if (! pLE -> AddPos (SecPos))    // Datei-Position speichern
      						return False;
      					TellArcs = False;
      				}                                       
      			} break;
      case 38:{
      				yyval.real_struct.real1 = yypvt[-1].real;
      				yyval.real_struct.real2 = yypvt[-0].real;
      			} break;
      case 47:{
      				PointOut = False;
      			} break;
      case 51:{
      				if (pParams -> ImpPunkte) { 
      					if (!pPE) {
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      					if (! pPE -> AddEntry (yypvt[-2].real_struct.real1, yypvt[-2].real_struct.real2))
      						return False;
      				}
      			} break;
      case 53:{              
      				pParams -> PalExist = True;
      				PolyOut = False;
      			} break;
      case 56:{
      				if (pParams -> ImpFlaechen)
      				{
      					if (! pPlE) {
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      					if (! pPlE -> AddPalVektor (yypvt[-2].integer))        // Pal-Größe
      						return False;
      				}                                               
      			} break;
      case 57:{   
      				if (pParams -> ImpFlaechen)
      				{
      					if (! pPlE) {
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      					if (! pPlE -> AddPalEntry (yypvt[-2].integer))   // ArcID
      						return False;
      				}                                               
      			} break;
      case 63:{
      			  		bReadText = False;
      			  		OutKonvMess (DGT_Unknown);
      			  } break;
      case 64:{
      			  		bReadText = False;        
      			  		OutKonvMess (DGT_Unknown);
      			  } break;
      case 67:{   
      				if (pParams -> ImpTexte && lstrlen (yypvt[-0].str_ptr) > 0)
      				{
      					if (! CreateTextObj ())
      						return False;
      					pTO -> AddKoord (yypvt[-8].real_struct.real1, yypvt[-6].real_struct.real1);
      					pTO -> AddText (yypvt[-0].str_ptr); 
      					pTO -> Output ();
                                              DELETE_OBJ (pTO);  /* Objekt wieder freigeben */
      				}                                       
      			} break;
      case 68:{
      				if (!ResetTables ())
      					return False;
      			} break;
      case 69:{
      				if (!ResetTables ())
      					return False;
      			} break;
      case 75:{     
      			  	if (!pMDT)
      			  	{
      					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      					return False;
      				}
      				if (!(pMDT -> Reset () && pMDT -> ReadMerkmale ()))
      					return False;			  	                 
      				if (pMDT -> Cnt () = yypvt[-0].int_struct.int1)
      				{
      					ActFieldCnt = yypvt[-0].int_struct.int2;			  	
      					pMDT -> _TableType = PatTable;
      				}					
      			  } break;
      case 76:{ 
      			  	if (!pMDT)
      			  	{
      					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      					return False;
      				}
      				if (!(pMDT -> Reset () && pMDT -> ReadMerkmale ()))
      					return False;

					if (0 != (pMDT -> Cnt () = yypvt[-0].int_struct.int1))
      				{
      					ActFieldCnt = yypvt[-0].int_struct.int2;			  	
      					pMDT -> _TableType = AatTable;
      				}					
      			  } break;
      case 77:{
      				if (!pMDT || !pTDI)
      			  	{
      					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      					return False;
      				}
      				if (!pMDT -> Reset ())
      					return False;			  	                 
      				if (pMDT -> Cnt () = yypvt[-0].int_struct.int1)
      				{
      					ActFieldCnt = yypvt[-0].int_struct.int2;			  				  
      					pMDT -> _TableType = OtherTable;
      				
      			 	// Tabellen-Name ggf. speichern								
      					if (pParams -> ImpTabellen)
      					{     
      						if (! pMDT -> StoreTableName (yypvt[-0].int_struct.str_ptr1) || 
      							! pTDI -> SetMaster (yypvt[-0].int_struct.str_ptr1))
      							return False;
      					}
      				}					
      			  } break;
      case 78:{
      				yyval.int_struct.int3 = yypvt[-0].integer;				// hat Feld Infos ?
      				switch ((short) yypvt[-5].integer) {
      					case 40:                        		// Float
      					case 60:
      					{       
      						switch (yypvt[-11].integer)
      						{
      							case DoublePrecL:
      								yyval.int_struct.int1 = DoublePrecLen;			// bei double Precision                                         
      							break;
      							case SinglePrecL:
      							default: 
      								yyval.int_struct.int1 = SinglePrecLen;			// Standard-Ausgabe-Länge	
      							break;
      						}							
      					}                                                                 
      					break;
      					case 50:                        		// Integer
      					{
      						switch (yypvt[-11].integer)
      						{
      							case (IntegerShortL):
      								yyval.int_struct.int1 = IntegerShortLen;
      							break; 
      							case (IntegerDoubleL):
      							default:
      								yyval.int_struct.int1 = IntegerDoubleLen;			// Standard-Ausgabe-Länge	
      							break;
      						}							
      					}
      					break;
      					case 20:                        		// String
      					case 30:
      						yyval.int_struct.int1 = yypvt[-11].integer;
      					break;
      					case 10:                        		// Datum
      						yyval.int_struct.int1 = DateMLength;
      					break;
      					default: {
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      				}
      			} break;
      case 81:{       
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 82:{    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 83:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 84:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 85:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 86:{   
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 87:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 88:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1))
      					return False;
      			} break;
      case 89:{                    
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, yypvt[-0].int_struct.int1, pParams -> UserID ? yypvt[-1].str_ptr : NULL, True))
      					return False;
      			} break;
      case 90:{   
      				short Len = 0;
      				switch ((short) yypvt[-0].int_struct.int2) 
      				{
      					case 40:                        	// Float
      					case 60:
      					{       
      						switch (yypvt[-0].int_struct.int1)
      						{
      							case DoublePrecL:
      								Len = DoublePrecLen;			// bei double Precision                                         
      							break;
      							case SinglePrecL:
      							default: 
      								Len = SinglePrecLen;			// Standard-Ausgabe-Länge	
      							break;
      						}							
      					}                                                                 
      					break;
      					case 50:                        // Integer
      					{
      						switch (yypvt[-0].int_struct.int1)
      						{
      							case (IntegerShortL):
      								Len = IntegerShortLen;
      							break; 
      							case (IntegerDoubleL):
      							default:
      								Len = IntegerDoubleLen;			// Standard-Ausgabe-Länge	
      							break;
      						}							
      					}
      					break;
      					case 20:                        // String
      					case 30:
      						Len = (short) yypvt[-0].int_struct.int1;
      					break;
      					case 10:                        // Datum
      						Len = DateMLength;
      					break;
      					default: {
      						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
      						return False;
      					}
      				}
      			
      				if (! AddMerkmal (yypvt[-0].int_struct.int3, Len, yypvt[-0].int_struct.str_ptr1))
      					return False;
      			} break;    }
    goto enstack;
}

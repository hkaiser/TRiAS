
// Grammatik für GDB-SchnittstellenEingabe
// File: GDB.Y

#include "stdafx.h"

#include "gdb.h"

#include "dgeoobj.hxx"
#include "yystype.hxx"
#include "hashtabs.hxx"

#pragma warning(disable: 4102)

//  Parameter -----------------------------------------------------------------
long ActEnum = 0;
long ActEnum2 = 0;
long ActStufe = 1;
long ActEbene = 1;
long ActStrichModus = 1;
long ActStrichDicke = 4;

// Container der Eingabedaten -------------------------------------------------
double XMin = DBL_MAX;
double XMax = 0.0;
double YMin = DBL_MAX;
double YMax = 0.0;

extern int r_flag;	// Geometrie immer mit speichern

double XPKoord = 0.0;
double YPKoord = 0.0;

// KreisParameter -------------------------------------------------------------
static double Winkel = 0.0, Radius = 0.0;
static char *KCode;
static char *KText = NULL;

// PunktAttribute -------------------------------------------------------------
static double XKoord = -1.0;
static double YKoord = -1.0;
static char PunktKennzeichen[5];
static long PunktNummer = 0;
static char *PName = NULL;
static char *PCode = NULL;
static char *PText = NULL;

// TextAttribute --------------------------------------------------------------
static char *Text = NULL;
static double THoehe = -1.0;
static double TLaenge = -1.0;
static double TModus = -1.0;	// TextModus
static int TRicht = 'M';	// Ausrichtung
static char *TCode = NULL;
static double TSWinkel = 0.0;

// Bogen und KreisAttribute ---------------------------------------------------
static double XMKoord = -1.0;
static double YMKoord = -1.0;
static double XKKoord = -1.0;
static double YKKoord = -1.0;
static double KRadius = 0.0;
static char *BCode = NULL;
static char *BText = NULL;

// Linienattribute ------------------------------------------------------------
static double LMWert = -1.0;
static char *LCode;
static char *LText = NULL;

// Flächenattribute -----------------------------------------------------------
static double XFKoord = -1.0;
static double YFKoord = -1.0;
static double SWinkel = -1.0;
static double SAbstand = -1.0;
static char *FText = NULL;
static char *FCode = NULL;
static char *FName = NULL;
static char PTCode [PointerSize];

int yylineno = 1;

extern FILE *yyout;			// AusgabeDatei
extern GDBElementTab *pGDBElemente;	// bereits ausgegebene GDBElemente

extern int k_flag;	// Kreise als Linien/Flächen

// lokale Prototypen ----------------------------------------------------------
void InitParams (void);
void CopyParams (DParam *);

// statische Daten ------------------------------------------------------------
char *TrennSatz = "; --------------------------------------"
		  "---------------------------------------\n";
#define ASCIIREAL 257
#define INTEGER 258
#define PUNKT 259
#define LINIE 260
#define KREIS 261
#define BOGEN 262
#define POLYGON 263
#define T_TEXT 264
#define FLAECHE 265
#define PUNKTKOORD 266
#define SYMBOL 267
#define PUNKT1 268
#define LINIE1 269
#define KREIS1 270
#define BOGEN1 271
#define POLYGON1 272
#define TEXT1 273
#define PUNKTKOORD1 274
#define FLAECHE1 275
#define SYMBOL1 276
#define PNRSATZ 277
#define OSSATZ 278
#define XSATZ 279
#define YSATZ 280
#define RADIUS 281
#define WINKEL 282
#define SWINKEL 283
#define NSATZ 284
#define NAMSATZ 285
#define FLDSATZ 286
#define SASATZ 287
#define FLASATZ 288
#define HSATZ 289
#define ASATZ 290
#define MSATZ 291
#define CODESATZ 292
#define SARSATZ 293
#define FSATZ 294
#define SSATZ 295
#define X1SATZ 296
#define Y1SATZ 297
#define X2SATZ 298
#define Y2SATZ 299
#define STTSATZ 300
#define TXTSATZ 301
#define PKZSATZ 302
#define CODE 303
#define POINTER 304
#define IDENT 305
#define KOMMENTAR 306
#define ENUM 307
#define EB 308
#define SM 309
#define ST 310
#define ENUMI 311
#define SICADREAL 312
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE (*pyylval), (*pyyval);
#define YYERRCODE 256



// Standards setzen -----------------------------------------------------------
void InitParams (void) {

	ActStufe = 1;	
	ActEbene = 1;
	ActStrichModus = 1;
	ActStrichDicke = 4;
	ActEnum = 0;
	ActEnum2 = 0;
}

void CopyParams (DParam *pD) {

	pD -> _Stufe = ActStufe;	
	pD -> _Ebene = ActEbene;
	pD -> _Enum = ActEnum;
	pD -> _Enum2 = ActEnum2;
	pD -> _StrichModus = ActStrichModus;
	pD -> _StrichDicke = ActStrichDicke;
}

short yyexca[] = {-1, 1,
	0, -1,
	-2, 0,
-1, 138,
	257, 170,
	258, 170,
	312, 170,
	-2, 172,
	};
#define YYNPROD 192
#define YYLAST 609
short yyact[]={

 339, 153, 338, 170, 171, 228,  55, 210, 368, 259,
  61,  64,  63,  62,  65, 367, 180,  98,  99, 100,
 366, 128, 375, 372, 353, 365, 352,  54, 129,  44,
  45, 364,  46, 351, 350,  43, 349,  47,  48,  52,
  99, 100,  49, 254, 363, 168, 172, 173, 174, 175,
 362,  51,  53, 179,  50, 358, 247, 236, 169, 235,
 357, 229, 221, 181, 286, 356,  75,  96, 279, 195,
 196, 197, 154, 156, 157, 158, 155, 278, 204, 205,
 206, 207, 208, 209, 355, 211,  36, 137,  88, 354,
 128, 216, 217, 218, 348,  37, 119, 129, 101, 347,
 223, 224,  67, 131, 226, 227, 346, 277, 276, 275,
 232, 273, 234, 140, 378, 133, 132, 139, 136,  66,
 130, 164, 377, 243, 370, 345, 246, 344, 102, 114,
 116, 166, 134, 343,  34,  97, 342, 256, 340,  74,
 260, 201, 336, 263, 264, 265, 266, 335, 331, 330,
 106, 113, 103, 104, 274, 109, 112, 202, 110,  95,
  90,  91, 111,  92, 329, 108,  89, 327, 326, 194,
 165,  76, 186,  94, 107, 105, 214, 325, 185, 187,
  77,  78,  93,  81,  82,  79, 148, 184, 241, 128,
  80,  83,  84,  86,  77,  78, 129,  81,  82,  79,
 188, 324,  85, 148,  80,  83,  84,  86, 323, 142,
 143, 144, 145, 240, 127, 322,  85, 128,  73, 321,
 242, 320, 147, 319, 129, 318, 142, 143, 144, 145,
 225, 146, 222, 317, 252, 141, 126, 316, 315, 147,
 314,  68,  69,  70, 313, 125, 312, 137, 146, 122,
 123, 311, 164, 310,  72, 201, 170, 171, 309, 124,
 308, 307, 306,  71,  61,  64,  63,  62,  65, 203,
 305, 304, 274, 274, 274, 133, 132, 139, 136, 303,
 293, 240, 274, 274, 274, 274, 274, 292, 291, 252,
 194, 290, 134, 152, 289, 288, 287, 285, 269, 268,
 274, 274, 274, 274, 274, 154, 156, 157, 158, 155,
 115, 169, 154, 156, 157, 158, 155, 154, 156, 157,
 158, 155, 154, 156, 157, 158, 155, 267, 154, 156,
 157, 158, 155, 257, 274, 274, 255, 253, 248, 245,
 369, 154, 156, 157, 158, 155, 244, 154, 156, 157,
 158, 155, 154, 156, 157, 158, 155, 154, 156, 157,
 158, 155, 154, 156, 157, 158, 155, 183, 237, 233,
 231, 225, 374, 230, 376, 220, 262, 222, 219, 215,
 213, 154, 156, 157, 158, 155, 154, 156, 157, 158,
 155, 154, 156, 157, 158, 155, 154, 156, 157, 158,
 155, 212, 200, 154, 156, 157, 158, 155, 154, 156,
 157, 158, 155,  28,  30,  25,  32,  31,  26,  29,
  24,  27, 262, 199, 198, 182, 238, 239, 178, 177,
 176, 167,   3, 373, 371,  33, 337, 258, 138, 135,
 190, 251, 162, 270, 271, 272, 250, 160, 191, 163,
 192, 261, 150, 280, 281, 282, 283, 284, 149, 189,
 161, 249, 193, 151, 159,  57,  22, 121,  20,  60,
  17,  58,  23,  59,  16,  56,  21, 120,  19,  87,
  18,  35,  15, 298, 299, 300, 301, 302,  42,   9,
   8,   7,   6,   2, 294, 295, 296, 297, 118, 117,
  41,  40,  39,  38,  14,  13,   5,  12,  11,   4,
  10,   1,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 332, 333,   0,   0,   0,   0,   0,
 328,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 334,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 341,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0, 359, 360, 361 };
short yypact[]={

 145,-1000, 145,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-250, -38, -85,-119,-239,
-127, -42,  -9, -53,-1000,-1000,-1000,-235,-1000,-1000,
-1000,-1000,-1000,-1000,   4,-250,-1000,-1000,-1000,-1000,
-1000,-1000,-1000, 421,-254,-254,-254,-254,-254, 420,
 419, 418,-254,-289,-195, 415, -42,  -9, -53, -38,
 -85,-1000,-1000,-1000,-1000,-1000, -38,-1000,-254,-254,
-254, 414, 413, 392, -99,-1000, 259,-254,-254,-254,
-254,-254,-254,-298,-254, 391, 370,-119,-1000, 369,
-254,-254,-254, 368, 365,-196,-261,-1000,-1000,-254,
-254,-127,-1000,-254,-254,-300,-197, 363, 360,-254,
 359,-254,-199,-201, 358,-238, -42,-1000,-1000,-1000,
-239,-127,-254, 336, 329,-254,-202, 328,-1000,-1000,
-169,-1000, 327,-215, 326,-1000,-254, 323,-1000,  -1,
 -70,-1000,-254,-254,-254,-254, 317, 289, 288,-235,
-235,-235, 101,-1000,  48,  47,  46,  16,   7,-235,
-235,-235,-235,-235,-1000,   4,-1000,-1000, 287,-193,
-1000,-1000, 286, 285, 284, 281,-1000,-1000,-1000, 278,
 277, 270,-1000,-238, -42,-169, -70, -38, -99,-235,
-235,-235,-235,-235,-1000, 269, 261, 260,-1000,-1000,
-1000,-1000, 259,-1000, 252, 251, 250, 248, 243, 241,
 236, 234,-1000,-1000,-1000,-1000, 230, 228, 227,-1000,
-1000, 223,-1000, 215, 213,-1000, 211, 209, 205, 198,
-1000,-1000, 191,-1000, 167, 158, 157,-1000,-1000,-238,
-1000,-261,-127, 154,-1000,-1000, 139, 138,-1000,-235,
-235,-238,-1000,-1000, 137,-1000, 132,-1000,-254,-1000,
 128,-238,-1000, 126, 123, 117, 115,-1000,-1000,-1000,
  96,  89,  84,-1000,-1000,-222,-224,-225,-232,-234,
  79,  74,  55,  50,  45,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-238,-238,-238,  40,  34,
  21,  15,  10,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,   5,  -2,-1000,-1000,-1000,-254,-1000, 114,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000, -24,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-254,-236,-254, 112,-1000, 104,-1000,-1000 };
short yypgo[]={

   0, 511, 510, 509, 508, 507, 506, 505, 504, 503,
  86, 502, 501, 500, 310, 499, 498, 493, 432, 492,
 491, 490, 489, 488, 482, 134, 481, 480, 479, 478,
  67, 477, 476, 130, 475, 474, 119, 473, 472, 113,
 471, 470, 139, 469, 468,  98, 467, 466, 120, 465,
 293,  88,   0, 464, 463, 462,  66, 461, 135, 460,
 459,  96, 458,  95, 452, 450, 102, 449, 448, 235,
 447, 446, 128, 442, 440, 103, 439, 438, 437, 436,
 434,   2, 433,   1 };

short yyr1[]={
   0,   1,  17,  17,  18,  18,  18,  18,  18,  18,
   3,   3,  14,  14,   6,   6,   6,  10,  10,  10,
  10,  10,  19,  19,  25,  25,  22,   2,  15,   5,
   5,   9,   9,  20,  13,   8,  12,  21,  23,   4,
   4,  16,  16,   7,   7,   7,  11,  11,  11,  27,
  28,  28,  51,  51,  51,  51,  51,  51,  51,  53,
  29,  54,  41,  55,  43,  42,  42,  42,  56,  56,
  56,  56,  56,  56,  56,  56,  56,  56,  56,  57,
  31,  30,  30,  30,  58,  58,  59,  32,  60,  34,
  33,  33,  61,  61,  61,  61,  61,  61,  62,  24,
  26,  26,  63,  63,  63,  63,  63,  63,  63,  63,
  63,  63,  63,  63,  63,  64,  35,  65,  37,  36,
  36,  66,  66,  66,  66,  66,  66,  67,  38,  68,
  40,  39,  39,  69,  69,  69,  69,  69,  69,  69,
  70,  44,  71,  46,  45,  45,  72,  72,  72,  72,
  72,  72,  72,  72,  72,  72,  72,  72,  73,  47,
  74,  49,  75,  75,  75,  75,  75,  75,  48,  48,
  78,  76,  76,  76,  80,  77,  79,  79,  82,  81,
  50,  50,  52,  52,  52,  52,  83,  83,  83,  83,
  83,  83 };

short yyr2[]={
   0,   1,   1,   2,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   2,   3,   1,   2,   2,   2,   2,   3,
   4,   3,   4,   2,   2,   4,   4,   2,   2,   2,
   1,   2,   1,   4,   2,   1,   4,   2,   1,   3,
   1,   2,   2,   3,   3,   3,   2,   2,   3,   0,
   4,   0,   4,   0,   4,   1,   2,   1,   3,   3,
   3,   3,   3,   3,   3,   3,   2,   2,   2,   0,
   4,   1,   2,   1,   3,   3,   0,   4,   0,   4,
   1,   2,   3,   2,   2,   3,   3,   2,   0,   4,
   1,   2,   2,   3,   3,   3,   3,   3,   2,   2,
   2,   3,   3,   3,   2,   0,   4,   0,   4,   1,
   2,   3,   3,   3,   2,   2,   2,   0,   4,   0,
   4,   1,   2,   3,   3,   3,   3,   2,   2,   2,
   0,   4,   0,   4,   1,   2,   3,   3,   3,   3,
   2,   2,   3,   2,   3,   3,   3,   2,   0,   4,
   0,   4,   2,   3,   2,   1,   3,   2,   1,   2,
   0,   3,   1,   2,   0,   6,   1,   2,   0,   5,
   1,   2,   2,   1,   1,   1,   3,   5,   3,   3,
   3,   3 };

short yychk[]={
-1000,  -1, -17, -18,  -3,  -6, -19, -20, -21, -22,
  -2,  -4,  -5,  -7,  -8, -24, -35, -41, -27, -29,
 -44, -32, -47, -38, 275, 270, 273, 276, 268, 274,
 269, 272, 271, -18, -25, -26, -10, -63,  -9, -11,
 -12, -13, -23, 285, 279, 280, 282, 287, 288, 292,
 304, 301, 289, 302, 277, 256, -34, -49, -40, -37,
 -43, 260, 263, 262, 261, 264, -36, -66, 279, 280,
 281, 301, 292, 256, -42, -56, 256, 279, 280, 284,
 289, 282, 283, 290, 291, 301, 292, -28, -51, 285,
 279, 280, 282, 301, 292, 278, -30, -58, 256, 279,
 280, -45, -72, 279, 280, 302, 277, 301, 292, 282,
 285, 289, 283, 278, 256, -14, -33, -15, -16, -61,
 -31, -46, 291, 292, 301, 287, 278, 256, 259, 266,
 -48, -75, 285, 284, 301, -76, 287, 256, -77, 286,
 -39, -69, 279, 280, 281, 282, 301, 292, 256, -62,
 -64, -54, -50, -83, 307, 311, 308, 309, 310, -53,
 -70, -59, -73, -67, -10, -25, -63,  10, -52, 312,
 257, 258, -52, -52, -52, -52,  10,  10,  10, -52,
 305, 258,  10, -14, -33, -48, -39, -36, -42, -60,
 -74, -68, -65, -55, -66, -52, -52, -52,  10,  10,
  10, -56, 256,  10, -52, -52, -52, -52, -52, -52,
 305, -52,  10,  10, -51,  10, -52, -52, -52,  10,
  10, 258, -58, -52, -52, -72, -52, -52, 305, 258,
  10,  10, -52,  10, -52, 258, 258,  10, -14, -14,
 -61, -30, -45, -52,  10,  10, -52, 258,  10, -57,
 -71, -14, -75,  10, 258,  10, -52,  10, -78,  10,
 -52, -14, -69, -52, -52, -52, -52,  10,  10,  10,
 -50, -50, -50,  10, -83,  61,  61,  61,  61,  61,
 -50, -50, -50, -50, -50,  10, 257,  10,  10,  10,
  10,  10,  10,  10, -14, -14, -14, -14, -50, -50,
 -50, -50, -50,  10,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  10,  10,  10,  10,  10, -14,  10,
  10,  10, -50, -50, -14,  10,  10, -79, -81, -52,
  10, -14,  10,  10,  10,  10,  10,  10,  10, 258,
 258, 258, 258, 258,  10,  10,  10,  10,  10, -14,
 -14, -14,  10,  10,  10,  10,  10,  10,  10, -81,
  10, -80,  47, -82, -52, 258, -52,  10,  10 };

short yydef[]={
   0,  -2,   1,   2,   4,   5,   6,   7,   8,   9,
  10,  11,  14,  15,  16,   0,   0,   0,   0,   0,
  40,   0,  45,   0,  98, 115,  61,   0,  59, 140,
  86, 158, 127,   3,  22,   0,  24, 100,  17,  18,
  19,  20,  21,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  48,   0,   0,
   0,  88, 160, 129, 117,  63,  33, 119,   0,   0,
   0,   0,   0,   0,  37,  65,  67,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  26,  50,   0,
   0,   0,   0,   0,   0,   0,  27,  81,  83,   0,
   0,  39, 144,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  12,  13,  90,
   0,  42,   0,   0,   0,   0,   0,   0,  79, 142,
  44, 168,   0,   0,   0, 165,   0,   0,  -2,   0,
   0, 131,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 180,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  25,  23, 101, 102,   0, 184,
 183, 185,   0,   0,   0,   0, 108, 109, 110,   0,
   0,   0, 114,   0,   0,  47,   0,  34,  38,   0,
   0,   0,   0,   0, 120,   0,   0,   0, 124, 125,
 126,  66,   0,  78,   0,   0,   0,   0,   0,   0,
   0,   0,  76,  77,  51,  52,   0,   0,   0,  56,
  57,   0,  82,   0,   0, 145,   0,   0,   0,   0,
 150, 151,   0, 153,   0,   0,   0, 157,  29,   0,
  91,  28,  41,   0,  93,  94,   0,   0,  97,   0,
   0,   0, 169, 162,   0, 164,   0, 167,   0, 173,
   0,   0, 132,   0,   0,   0,   0, 137, 138, 139,
   0,   0,   0,  49, 181,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 103, 182, 104, 105, 106,
 107, 111, 112, 113,  31,   0,   0,   0,   0,   0,
   0,   0,   0, 121, 122, 123,  68,  69,  70,  71,
  72,  73,  74,  75,  53,  54,  55,  58,  84,  85,
 146, 147, 148, 149, 152, 154, 155, 156,  30,  92,
  95,  96,   0,   0,  43, 163, 166, 171, 176,   0,
 174,  35, 133, 134, 135, 136,  99, 116,  62, 186,
 188, 189, 190, 191,  60, 141,  87, 159, 128,  32,
  46,  36,  89, 161, 130, 118,  64,  80, 143, 177,
 178,   0,   0,   0,   0, 187,   0, 175, 179 };
# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)
#ifdef YYIGNORE
# define yyignore *(yypi+1) = 1
#endif

// Funktionsdefinitionen
void yyerror (const char *);
int yylex (void);
int yyparse (void);

/*	parser for yacc output	*/

#if defined(YYDEBUG)
int yydebug = 0; /* 1 for debugging */
#endif

YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

int 
yyparse(void) {

	short yys[YYMAXDEPTH];
	short yyj, yym;
	register YYSTYPE *yypvt;
	register short yystate, *yyps, yyn;
	register YYSTYPE *yypv;
	register short *yyxi;
#ifdef YYIGNORE
	register char *yypi;
#endif

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];
#ifdef YYIGNORE
	yypi= &yyi[0];
#endif

 yystack:    /* put a state and value onto the stack */

#if defined(YYDEBUG)
	if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
		if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
		*yyps = yystate;
#ifdef YYIGNORE
		++yypi;
		*(yypi+1) = *yypi;
#endif
		++yypv;
//		memcpy (yypv, &(*pyyval), sizeof ((*pyyval)));
		*yypv = (*pyyval);	

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
//		memcpy (&(*pyyval), &(*pyylval), sizeof ((*pyyval)));
		(*pyyval) = (*pyylval);
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
		}

 yydefault:
	/* default state action */

	if( (yyn=yydef[yystate]) == -2 ) {
		if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
		/* look through exception table */

		for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
			}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
		}

	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yyerrflag ){

		case 0:   /* brand new error */

			yyerror( "syntax error" );
		yyerrlab:
			++yynerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yyps >= yys ) {
			   yyn = yypact[*yyps] + YYERRCODE;
			   if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
			      yystate = yyact[yyn];  /* simulate a shift of "error" */
			      goto yystack;
			      }
			   yyn = yypact[*yyps];

			   /* the current yyps has no shift onn "error", pop stack */

#if defined (YYDEBUG)
			   if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
			   --yyps;
			   --yypv;
#ifdef YYIGNORE
			   --yypi;
#endif
			   }

			/* there is no state on the stack with an error shift ... abort */

	yyabort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#if defined(YYDEBUG)
			if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */

			}

		}

	/* reduction by production yyn */

#if defined(YYDEBUG)
		if( yydebug ) printf("reduce %d\n",yyn);
#endif
		yyps -= yyr2[yyn];
		yypvt = yypv;
		yypv -= yyr2[yyn];
//		memcpy (&(*pyyval), &(yypv[1]), sizeof ((*pyyval)));
#ifdef YYIGNORE
		yypi -= yyr2[yyn];
		*(yypi+1) = *yypi;
#endif
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];

//		pCurrApp -> Exec (ExecWhileEvent);
#ifdef YYIGNORE
	if(!*yypi)
#endif
		switch(yym){
			
case 2:
{
/* --> GDBElement */
		/* DGeoObj ausgeben */	
			if ((&yypvt[-0].DGeoObjToken()) -> OutPut())
				fprintf (yyout, TrennSatz);	// TrennSatz einfügen
		} break;
case 3:
{
/* --> GDBElemente GDBElement */
			if ((&yypvt[-0].DGeoObjToken()) -> OutPut())
				fprintf (yyout, TrennSatz);	// TrennSatz einfügen
		} break;
case 12:
{
/* --> SubPunktElement */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 13:
{
/* --> SubPunktKoordinaten */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 17:
{
/* --> SubLinienFormElement */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 18:
{
/* --> SubPolygon */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 19:
{
/* --> SubBogen */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 21:
{
/* --> SubTextElement */
			(&yypvt[-0].DGeoObjToken()) -> OutPut();
		} break;
case 22:
{
/* --> FlaechenElementKopf SubLinienFormElemente */
		DFlaeche *pFL;
		DPunkt *pFirst, *pLast;

			if (yypvt[-0].DGeoObjToken().isA() == DGeoObj :: DGT_Linie) {
			// bisher ist Objekt noch Linie (nur eine Kontur)
				pFL = new DFlaeche();
			DLinie *pDL = &yypvt[-0].DLinieToken();

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pDL -> _pDPL -> FirstDPunkt();
				pLast = pDL -> _pDPL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pFL -> AddGeoObj (pDL);		// DLinie umhängen
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			} else {
			// Objekt ist bereits Fläche
				pFL = new DFlaeche (yypvt[-0].DFlaecheToken());

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pFL -> FirstDPunkt();
				pLast = pFL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			}

			pFL -> SetParams (&yypvt[-1].DParamToken());
			pFL -> SetFlaechenParams (XFKoord, YFKoord, SWinkel, SAbstand);
			pFL -> SetCode (FCode);
			pFL -> SetText (FText);
			pFL -> SetName (FName);
			pFL -> SetPointer (PTCode);

			YYSTACK (pFL, YYDFlaeche);

		// Speicher wieder freigeben
			delete pFirst;
			delete pLast;
		} break;
case 23:
{
/* --> FlaechenElementKopf MFlaechenElementParameter SubLinienFormElemente */
		DFlaeche *pFL;
		DPunkt *pFirst, *pLast;
		int DGType = yypvt[-0].DGeoObjToken().isA();

			if (DGType == DGeoObj :: DGT_Linie) {
			// bisher ist Objekt noch Linie (nur eine Kontur)
				pFL = new DFlaeche();
			DLinie *pDL = &yypvt[-0].DLinieToken();

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pDL -> _pDPL -> FirstDPunkt();
				pLast = pDL -> _pDPL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pFL -> AddGeoObj (pDL);		// DLinie umhängen
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen

			} else if (DGType == DGeoObj :: DGT_Flaeche) {
			// Objekt ist bereits Fläche
				pFL = new DFlaeche (yypvt[-0].DFlaecheToken());

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pFL -> FirstDPunkt();
				pLast = pFL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			}

			pFL -> SetParams (&yypvt[-2].DParamToken());
			pFL -> SetFlaechenParams (XFKoord, YFKoord, SWinkel, SAbstand);
			pFL -> SetCode (FCode);
			pFL -> SetText (FText);
			pFL -> SetName (FName);
			pFL -> SetPointer (PTCode);

			YYSTACK (pFL, YYDFlaeche);

		// Speicher wieder freigeben
			delete pFirst;
			delete pLast;
		} break;
case 25:
{
/* --> SubLinienFormElemente SubLinienFormElement */
			if (yypvt[-1].DGeoObjToken().isA() == DGeoObj :: DGT_Linie) {
			DLinie *pDL = new DLinie (yypvt[-1].DLinieToken());

			// nächstes Objekt als DGeoObj anhängen, da hier auch
			// DText erlaubt ist (SubTextElement)
				if (pDL -> AddGeoObj (&yypvt[-0].DGeoObjToken())) {
				// normales anhängen geglückt, kopieren und raus
					YYSTACK (pDL, YYDLinie);
					break;	// weiter
				}
			// aus Linie hier Fläche machen
			DFlaeche *pDF = new DFlaeche();

				if (!pDF) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pDF -> AddGeoObj (pDL);	// Linie umhängen
			// neue Kontur anhängen
				pDF -> AddDLinie (yypvt[-0].DLinieToken());
				YYSTACK (pDF, YYDFlaeche);
			} else {
			// SubLinienFormElement ist bereits Fläche
			DFlaeche *pDF = new DFlaeche (yypvt[-1].DFlaecheToken());

				if (yypvt[-0].DGeoObjToken().isA() == DGeoObj :: DGT_Linie) {
				// neues Objekt ist Linie
				DLinie *pDL = new DLinie (yypvt[-0].DLinieToken());

					if (!pDF -> AddGeoObj (pDL)) {
					// neue Linie anhängen gescheitert
					// neue Kontur anhängen
						pDF -> AddDLinie (*pDL);
					}
				}

				YYSTACK (pDF, YYDFlaeche);
			}
		} break;
case 26:
{
		DSymbol *pSy = new DSymbol();

			YYSTACK (pSy, YYDSymbol);
		} break;
case 27:
{
/* --> PunktElementKopf MPunktElementParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&yypvt[-1].DParamToken());

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 28:
{
/* --> SubPunktElementKopf MPunktElementParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&yypvt[-1].DParamToken());

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 29:
{
/* --> LinienElementKopf SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-2].DParamToken());
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		} break;
case 30:
{
/* --> LinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		} break;
case 31:
{
/* --> SubLinienElementKopf SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-2].DParamToken());
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		} break;
case 32:
{
/* --> SubLinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		} break;
case 33:
{
/* --> KreisKopf MKreisParameter  */
		DLinie *pObj = new DLinie ();
		DPunkt DPt (XKKoord+KRadius, YKKoord);

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> AddGeoObj (&DPt);	// 1. Punkt
			pObj -> MakePolygon (XKKoord, YKKoord, XKKoord+KRadius, YKKoord);
			pObj -> AddGeoObj (&DPt);	// Kreis schlieáen
			pObj -> SetCode (KCode);
			pObj -> SetText (KText);

			if (!k_flag) {		// Kreis ist LinienObjekt
				YYSTACK (pObj, YYDLinie);
			} else {			// Kreis als Fläche
			DFlaeche *pFL = new DFlaeche();

				pFL -> AddGeoObj (pObj); // DLinie umhängen
				YYSTACK (pFL, YYDFlaeche);
			}
		} break;
case 34:
{
/* --> SubKreisKopf MKreisParameter */
		DLinie *pObj = new DLinie ();
		DPunkt DPt (XKKoord+KRadius, YKKoord);

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> AddGeoObj (&DPt);
			pObj -> MakePolygon (XKKoord, YKKoord, XKKoord+KRadius, YKKoord);
			pObj -> AddGeoObj (&DPt);	// Kreis schlieáen
			pObj -> SetCode (KCode);
			pObj -> SetText (KText);

			if (!k_flag) {		// Kreis ist LinienObjekt
				YYSTACK (pObj, YYDLinie);
			} else {			// Kreis als Fläche
			DFlaeche *pFL = new DFlaeche();

				pFL -> AddGeoObj (pObj); // DLinie umhängen
				YYSTACK (pFL, YYDFlaeche);
			}
		} break;
case 35:
{
/* --> BogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

		// erster Punkt
		DPunkt DPt (yypvt[-1].DPunktToken());
		double X0 = DPt.X();
		double Y0 = DPt.Y();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> AddGeoObj (&DPt);	// erster Punkt
		// hier konvertierte Koordinaten einfügen
			pObj -> MakePolygon (XMKoord, YMKoord, X0, Y0, Winkel);
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());	// letzter Punkt
			pObj -> SetCode (BCode);
			pObj -> SetText (BText);

			YYSTACK (pObj, YYDLinie);
		} break;
case 36:
{
/* --> SubBogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

		// erster Punkt	
		DPunkt DPt (yypvt[-1].DPunktToken());	
		double X0 = DPt.X();
		double Y0 = DPt.Y();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> AddGeoObj (&DPt);		// erster Punkt
		// hier konvertierte Koordinaten einfügen
			pObj -> MakePolygon (XMKoord, YMKoord, X0, Y0, Winkel);
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());	// letzter Punkt
			pObj -> SetCode (BCode);
			pObj -> SetText (BText);

			YYSTACK (pObj, YYDLinie);
		} break;
case 37:
{
/* --> TextElementKopf MTextElementParameter */
		DText *pObj = new DText (XKoord, YKoord);

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> SetTextParams (TRicht, Winkel, THoehe, 
					       TLaenge, TModus, TSWinkel);
			pObj -> SetText (Text);
			pObj -> SetCode (TCode);

			YYSTACK (pObj, YYDText);
		} break;
case 38:
{
/* --> SubTextElementKopf MTextElementParameter */
		DText *pObj = new DText (XKoord, YKoord);

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> SetTextParams (TRicht, Winkel, THoehe, 
					       TLaenge, TModus, TSWinkel);
			pObj -> SetText (Text);
			pObj -> SetCode (TCode);

			YYSTACK (pObj, YYDText);
		} break;
case 39:
{
/* --> PunktKoordinatenKopf MPunktKoordinatenParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&yypvt[-1].DParamToken());
			pDPt -> SetPunktParams (PunktKennzeichen, PunktNummer);
			pDPt -> SetCode (PCode);
			pDPt -> SetText (PText);
			pDPt -> SetName (PName);

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 40:
{
/* --> PunktKoordinatenKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* Koordinaten von bereits existierenden Punkt holen */
		DPunkt *pDPt = (DPunkt *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDPt == NULL) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
			pDPt -> SetParams (&yypvt[-0].DParamToken());
			YYSTACK (pDPt, YYDPunkt);
		} break;
case 41:
{
/* --> SubPunktKoordinatenKopf MPunktKoordinatenParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&yypvt[-1].DParamToken());
			pDPt -> SetPunktParams (PunktKennzeichen, PunktNummer);
			pDPt -> SetCode (PCode);
			pDPt -> SetText (PText);
			pDPt -> SetName (PName);

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 42:
{
/* --> SubPunktKoordinatenKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* Koordinaten von bereits existierenden Punkt holen */
		DPunkt *pDPt = (DPunkt *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDPt == NULL) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
			pDPt -> SetParams (&yypvt[-0].DParamToken());
			YYSTACK (pDPt, YYDPunkt);
		} break;
case 43:
{
/* --> PolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> SetText (LText);
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());	// erster Punkt
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&yypvt[-2].DLinieToken(), AM_NoReverse);
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());	// letzter Punkt

			YYSTACK (pObj, YYDLinie);
		} break;
case 44:
{
/* --> PolygonKopf MPolygonParameter */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> SetText (LText);
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&yypvt[-0].DLinieToken(), AM_NoReverse);

			YYSTACK (pObj, YYDLinie);
		} break;
case 45:
{
/* --> PolygonKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* kopieren der bereits existierenden Geometrie */
		DLinie *pDLi = (DLinie *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDLi == NULL) {
				yyerror ("Fehlende Geometrieinformation.");
				YYABORT;
			}
			pDLi -> SetParams (&yypvt[-0].DParamToken());
			pDLi -> SetText (LText);
			YYSTACK (pDLi, YYDLinie);
		} break;
case 46:
{
/* --> SubPolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-3].DParamToken());
			pObj -> SetText (LText);
			pObj -> AddGeoObj (&yypvt[-1].DPunktToken());	// erster Punkt
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&yypvt[-2].DLinieToken(), AM_NoReverse);
		// letzter Punkt
			pObj -> AddGeoObj (&yypvt[-0].DPunktToken());	// letzter Punkt

			YYSTACK (pObj, YYDLinie);
		} break;
case 47:
{
/* --> SubPolygonKopf MPolygonParameter */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&yypvt[-1].DParamToken());
			pObj -> SetText (LText);
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&yypvt[-0].DLinieToken(), AM_NoReverse);

			YYSTACK (pObj, YYDLinie);
		} break;
case 48:
{
/* --> SubPolygonKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		// kopieren der bereits existierenden Geometrie 
		DLinie *pDLi = (DLinie *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDLi == NULL) {
				yyerror ("Fehlende Geometrieinformation.");
				YYABORT;
			}
			pDLi -> SetParams (&yypvt[-0].DParamToken());
			pDLi -> SetText (LText);

			YYSTACK (pDLi, YYDLinie);
		} break;
case 59:
{
/* --> PUNKT1 */	
			InitParams ();		
		} break;
case 60:
{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktParameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
			} break;
case 61:
{	
/* --> TEXT1 */
			InitParams ();		
		} break;
case 62:
{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				TLaenge = -1.0;
				THoehe = -1.0;
				TRicht = 'M';
				TModus = -1.0;
				Winkel = 0.0;
				TSWinkel = 0.0;
				Text = NULL;
				TCode = NULL;
			} break;
case 63:
{	
/* --> T_TEXT */
			InitParams ();		
		} break;
case 64:
{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				TLaenge = -1.0;
				THoehe = -1.0;
				TRicht = 'M';
				TModus = -1.0;
				Winkel = 0.0;
				TSWinkel = 0.0;
				Text = NULL;
				TCode = NULL;
			} break;
case 68:
{
/* --> XSATZ KoordinatenWert '\n' */
			XKoord = yypvt[-1].FloatToken();
			SetXCont (XKoord);
		} break;
case 69:
{
/* --> YSATZ KoordinatenWert '\n' */
			YKoord = yypvt[-1].FloatToken();
			SetYCont (YKoord);
		} break;
case 70:
{	TLaenge = yypvt[-1].FloatToken();	} break;
case 71:
{	THoehe = yypvt[-1].FloatToken();	} break;
case 72:
{
		/* WSatz */	Winkel = yypvt[-1].FloatToken();	
		} break;
case 73:
{
		/* SWISatz */	TSWinkel = yypvt[-1].FloatToken();	
		} break;
case 74:
{
		char *cptr = yypvt[-1].StringToken();

			if (cptr) {
				TRicht = *cptr;
				delete cptr;
			}
		} break;
case 75:
{	TModus = yypvt[-1].FloatToken();	} break;
case 76:
{	Text = yypvt[-1].StringToken();	} break;
case 77:
{
			TCode = yypvt[-1].StringToken();
		} break;
case 79:
{	InitParams ();		} break;
case 80:
{
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
			} break;
case 84:
{
			XKoord = yypvt[-1].FloatToken();
			SetXCont (XKoord);
		} break;
case 85:
{
			YKoord = yypvt[-1].FloatToken();
			SetYCont (YKoord);
		} break;
case 86:
{	InitParams ();		} break;
case 87:
{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

				LMWert = -1.0;
				LText = NULL;
				LCode = NULL;
			} break;
case 88:
{	InitParams ();		} break;
case 89:
{
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

				LMWert = -1.0;
				LText = NULL;
				LCode = NULL;
			} break;
case 92:
{	LMWert = yypvt[-1].FloatToken();	} break;
case 93:
{
			LCode = yypvt[-1].StringToken();
		} break;
case 94:
{	LText = yypvt[-1].StringToken();	} break;
case 98:
{	InitParams ();		} break;
case 99:
{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XFKoord = -1.0;
				YFKoord = -1.0;
				SWinkel = -1.0;
				SAbstand = -1.0;
				FText = NULL;
				FName = NULL;
				FCode = NULL;
				memset (PTCode, '\0', PointerSize);
			} break;
case 102:
{	FName = yypvt[-1].StringToken();	} break;
case 103:
{
			XFKoord = yypvt[-1].FloatToken();
			SetXCont (XFKoord);
		} break;
case 104:
{
			YFKoord = yypvt[-1].FloatToken();
			SetYCont (YFKoord);
		} break;
case 105:
{	SWinkel = yypvt[-1].FloatToken();	} break;
case 106:
{	SAbstand = yypvt[-1].FloatToken();	} break;
case 108:
{
			FCode = yypvt[-1].StringToken();
		} break;
case 109:
{ /* Pointer */
		char *cptr = yypvt[-1].StringToken();

			if (cptr) {
				strncpy (PTCode, cptr, PointerSize-1);
				delete cptr;
			}
		} break;
case 110:
{	FText = yypvt[-1].StringToken();	} break;
case 115:
{	InitParams ();		} break;
case 116:
{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// KreisParameter initialisieren
				XKKoord = -1.0;
				YKKoord = -1.0;
				KRadius = 0.0;
				KText = NULL;
				KCode = NULL;
			} break;
case 117:
{	InitParams ();		} break;
case 118:
{
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// KreisParameter initialisieren
				XKKoord = -1.0;
				YKKoord = -1.0;
				KRadius = 0.0;
				KText = NULL;
				KCode = NULL;
			} break;
case 121:
{
			XKKoord = yypvt[-1].FloatToken();
			SetXCont (XKKoord);
		} break;
case 122:
{
			YKKoord = yypvt[-1].FloatToken();
			SetYCont (YKKoord);
		} break;
case 123:
{	KRadius = yypvt[-1].FloatToken();	} break;
case 124:
{	KText = yypvt[-1].StringToken();	} break;
case 125:
{
			KCode = yypvt[-1].StringToken();
		} break;
case 127:
{	InitParams ();		} break;
case 128:
{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// BogenParameter initialisieren
				XMKoord = -1.0;
				YMKoord = -1.0;
				Winkel = 0.0;
				Radius = 0.0;
				BText = NULL;
				BCode = NULL;
			} break;
case 129:
{	InitParams ();		} break;
case 130:
{
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// BogenParameter initialisieren
				XMKoord = -1.0;
				YMKoord = -1.0;
				Winkel = 0.0;
				Radius = 0.0;
				BText = NULL;
				BCode = NULL;
			} break;
case 133:
{
			XMKoord = yypvt[-1].FloatToken();
			SetXCont (XMKoord);
		} break;
case 134:
{
			YMKoord = yypvt[-1].FloatToken();
			SetYCont (YMKoord);
		} break;
case 135:
{	Radius = yypvt[-1].FloatToken();	} break;
case 136:
{	Winkel = yypvt[-1].FloatToken();	} break;
case 137:
{	BText = yypvt[-1].StringToken();	} break;
case 138:
{
			BCode = yypvt[-1].StringToken();
		} break;
case 140:
{	InitParams ();		} break;
case 141:
{
			DParam *pD = new DParam;
	
				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				PText = NULL;
				PName = NULL;
				strnset (PunktKennzeichen, '\0', 5);
				PunktNummer = 0L;
				PCode = NULL;
		} break;
case 142:
{	InitParams ();		} break;
case 143:
{
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				PText = NULL;
				PName = NULL;
				strnset (PunktKennzeichen, '\0', 5);
				PunktNummer = 0L;
				PCode = NULL;
			} break;
case 146:
{
			XKoord = yypvt[-1].FloatToken();
			SetXCont (XKoord);
		} break;
case 147:
{
			YKoord = yypvt[-1].FloatToken();
			SetYCont (YKoord);
		} break;
case 148:
{
		char *cptr = yypvt[-1].StringToken();

			if (cptr) {
				strncpy (PunktKennzeichen, cptr, 4);
				delete cptr;
			}
		} break;
case 149:
{	PunktNummer = yypvt[-1].LongToken();	} break;
case 150:
{	PText = yypvt[-1].StringToken();	} break;
case 151:
{
			PCode = yypvt[-1].StringToken();
		} break;
case 153:
{	PName = yypvt[-1].StringToken();	} break;
case 158:
{	
/* --> POLYGON1 */
			InitParams ();		
		} break;
case 159:
{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);
				LText = NULL;

				YYSTACK (pD, YYDParams);
			} break;
case 160:
{	
/* --> POLYGON */
			InitParams ();		
		} break;
case 161:
{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = yypvt[-3].LongToken();
				CopyParams (pD);
				LText = NULL;

				YYSTACK (pD, YYDParams);
			} break;
case 162:
{	YYSTACK (NULL, YYUnknown);	} break;
case 163:
{	YYSTACK (NULL, YYUnknown);	} break;
case 164:
{	LText = yypvt[-1].StringToken();	
			YYSTACK (NULL, YYUnknown);	} break;
case 165:
{
		DLinie *pDLi = new DLinie ();
		
			if (!pDLi -> AddGeoObj (&yypvt[-0].DGeoObjToken())) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}
			YYSTACK (pDLi, YYDLinie);
		} break;
case 168:
{
			if (yypvt[-0].hasToken()) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&yypvt[-0].DGeoObjToken())) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
		} break;
case 169:
{
			if (yypvt[-1].hasToken()) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&yypvt[-1].DGeoObjToken())) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
			if (yypvt[-0].hasToken()) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&yypvt[-0].DGeoObjToken())) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
		} break;
case 170:
{
/* --> FeldKopf */
		DPunkt *pDPt = new DPunkt (XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 171:
{
/* --> FeldWerte */
		// Feldkopf ist noch Punkt
		DLinie *pDLi = new DLinie();
			
			if (!pDLi -> AddGeoObj (&yypvt[-1].DGeoObjToken())) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}
			if (!pDLi -> AddGeoObj (&yypvt[-0].DGeoObjToken(), AM_NoReverse)) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}

			YYSTACK (pDLi, YYDLinie);
		} break;
case 172:
{
/* --> FeldKopf */
		DPunkt *pDPt = new DPunkt(XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 173:
{
/* --> FLDSATZ '\n' */
		DPunkt *pDPt = new DPunkt();	// leerer Punkt
		
			YYSTACK (pDPt, YYDPunkt);
		} break;
case 174:
{	
/* --> FLDSATZ KoordinatenWert '\n' */
			XPKoord = yypvt[-1].FloatToken();
			SetXCont (XPKoord);
		} break;
case 175:
{
/* --> KoordinatenWert */
				YPKoord = yypvt[-1].FloatToken();
				SetYCont (YPKoord);
			} break;
case 176:
{
/* --> FeldWert */
		DPunkt *pDPt = new DPunkt(XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		} break;
case 177:
{
/* --> FeldWerte FeldWert */
		DPunkt *pDPt = new DPunkt (XPKoord, YPKoord);

			if (yypvt[-1].DGeoObjToken().isA() == DGeoObj :: DGT_Linie) {
			// Objekt ist bereits Linie
			DLinie *pDLi = new DLinie (yypvt[-1].DLinieToken());
						
				if (!pDLi -> AddGeoObj (pDPt)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			} else {
			// Objekt ist noch Punkt
			DLinie *pDLi = new DLinie();
			
				if (!pDLi -> AddGeoObj (&yypvt[-1].DGeoObjToken())) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!pDLi -> AddGeoObj (pDPt)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}

				YYSTACK (pDLi, YYDLinie);
			}	
		} break;
case 178:
{	
/* --> KoordinatenWert '\n' */
			XPKoord = yypvt[-1].FloatToken();
			SetXCont (XPKoord);
		} break;
case 179:
{
/* --> KoordinatenWert '\n' */
				YPKoord = yypvt[-1].FloatToken();
				SetYCont (YPKoord);
			} break;
case 182:
{
		double d = yypvt[-0].FloatToken();
		double *tmpVal = new double (d);

			YYSTACK (tmpVal, YYDouble);
		} break;
case 185:
{
		double d = (double)yypvt[-0].LongToken();
		double *tmpVal = new double (d);

			YYSTACK (tmpVal, YYDouble);
		} break;
case 186:
{	
			ActEnum = yypvt[-0].LongToken();
			ActEnum2 = 0;
		} break;
case 187:
{
			ActEnum = yypvt[-2].LongToken();
			ActEnum2 = yypvt[-0].LongToken();
		} break;
case 188:
{	/* sorry, not implemented */	} break;
case 189:
{	ActEbene = yypvt[-0].LongToken();	} break;
case 190:
{	ActStrichModus = yypvt[-0].LongToken();	} break;
case 191:
{	ActStrichDicke = yypvt[-0].LongToken();	} break;
		}
		(*pyyval) = yypv[1];
		goto yystack;  /* stack new state and value */

	}



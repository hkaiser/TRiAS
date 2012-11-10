
#line 2 "report.y"
/* Reportgenerator                                              */
/* File: REPORT.Y                                               */

static char SccsId[] = "uve FEZ: %W%  %E%";

#if defined(__cplusplus)
extern "C" {
#endif
	#include <stdio.h>
	#include <time.h>
	#include <string.h>
	#include <malloc.h>

	#include "report.h"
#if defined(__cplusplus)
}

#undef NULL
#define NULL 0

#endif

/* Monatsnamen */
static char *month[] = { "Jan", "Feb", "Mar", "Apr", "Mai", "Jun",
                         "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };

static VARIABLE *p;     /* Pointer auf aktuelle Eingabevariable */

long for_all_seek = 0;  /* Position von FOR_ALL */
int for_all_flag = FALSE;       /* Schleifenflag */
int for_all_line = 0;           /* Zeilennummer des Schleifenanfangs */

int ignoreflag = FALSE;         /* Flag fuer IF/ELSE */

int declaration = FALSE;        /* Deklarationssektion */

static int last_foot;
static int OutCols = 0;


#line 43 "report.y"
typedef union  {
        STRING_TOKEN strtok;
        NUMBER_TOKEN numtok;
        REAL_TOKEN realtok;
} YYSTYPE;
#define REPORT 257
#define LINES 258
#define COLUMNS 259
#define ALL 260
#define FROM 261
#define TO 262
#define BIG 263
#define PAGE 264
#define TUPLE 265
#define FOR_ONE 266
#define FOR_ALL 267
#define HEAD 268
#define TAIL 269
#define FORMAT 270
#define NUMBER 271
#define TUPLES 272
#define VARI 273
#define VARF 274
#define VARS 275
#define LASTI 276
#define VALUEI 277
#define NEXTI 278
#define LASTF 279
#define VALUEF 280
#define NEXTF 281
#define LASTS 282
#define VALUES 283
#define NEXTS 284
#define NEW 285
#define LINE 286
#define COL 287
#define BATCH 288
#define PROC 289
#define CALL 290
#define SYSTEM_VAR 291
#define SYSTEM_CONST 292
#define INT 293
#define REAL 294
#define PRINT 295
#define DECLARATION 296
#define LINEBEGIN 297
#define LINEEND 298
#define IF 299
#define ELSE 300
#define IDENT 301
#define STRING 302
#define TERMINAL 303
#define DATE 304
#define TIME 305
#define SPACE 306
#define REAL_NUMBER 307
#define EQU 308
#define OROR 309
#define ANDAND 310
#define UNOT 311
#define LT 312
#define GT 313
#define NE 314
#define LE 315
#define GE 316
#define EQ 317
#define UMINUS 318
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
#define YYERRCODE 256

#line 937 "report.y"


/* Anspringen einer YACC-Unterprogramm-Aktion */
int call (register SUBROUTINE *subr) {

        if (subr->seek != 0L) {
                subr->ret_seek = yytell (-1);
                subr->ret_line = yylineno;
                yylineno = subr->line;
                yyseek (subr->seek);
                return (FALSE);
        }
        else return (TRUE);
}

short yyexca[] = {-1, 1,
	0, -1,
	-2, 0,
-1, 80,
	256, 125,
	125, 125,
	-2, 126,
-1, 109,
	256, 55,
	125, 55,
	-2, 56,
-1, 177,
	256, 58,
	125, 58,
	-2, 59,
	};
#define YYNPROD 166
#define YYLAST 947
short yyact[]={

 121, 272, 194, 135,  60, 281, 280, 277, 278, 279,
 276, 193, 192, 167, 144,  98,  96, 147, 143, 142,
  18, 138,  32,  66,  25,  27,  26,  28,  29,  17,
  14, 188,  15, 263, 139, 326, 257,  68,  17, 117,
 313, 216, 187, 164, 146, 133, 114, 132, 270, 131,
  97,  20, 220, 264, 265, 181,  16, 197,  69, 152,
 292, 118, 115,  30,  31, 202, 203, 204, 101, 102,
 154, 156, 157, 158, 308, 251, 249,  92, 250,  90,
 252,  99, 100,  88,  86,   3,  84, 112, 310, 218,
 206, 220, 104, 103,  44, 199, 197,  42, 251, 249,
  47, 250,  43, 252,  74,   9, 303,  78,   9, 109,
  76, 288, 300, 269,  80,  77, 219, 298, 296, 267,
 297, 266, 299, 262, 239, 238, 231, 230, 229, 189,
 190, 191,  60, 228, 295, 227, 251, 249, 225, 250,
 207, 252, 186, 183, 135, 211, 212, 251, 249, 150,
 250,  66, 252, 294, 149,  80, 148, 105, 251, 249,
 222, 250, 210, 252, 268, 309, 300,  60,  23, 240,
  78, 298,  60,  76, 159, 248, 299, 163,  77, 300,
 161, 251,  21, 332, 298, 296, 252, 297, 182, 299,
  33,  66, 153,  95, 245, 116, 308, 251, 249, 137,
 250,  67, 252, 258, 259, 260, 251, 249, 215, 250,
  93, 252,  91, 197, 136, 112,  89,  87, 242,  85,
 177, 222, 222, 113,  52, 107, 111, 235,   4,  79,
 114, 176,  68,  17,  22,  36, 108,  49,  48,  50,
  35,  34,  11,  13, 245, 245,  70,  71,  72,  45,
  54,  61, 134,  69,  53,  51,  65, 174,  36,  62,
 243, 173,  24,  73,  80, 244,  56,  57,  63,  64,
  58,  10, 222, 222,  80,  80,  75, 314, 315, 316,
 317, 318, 319, 122, 140, 123, 198,  83, 128, 129,
 130, 202, 203, 204,  70,  71,  72, 245, 245, 245,
 245, 245,  12, 126, 127, 188, 254, 196, 271, 272,
 333,   8, 197,   7, 255,  57, 271, 272,  58, 200,
   6,   5, 122, 221, 123, 198,  83, 128, 129, 130,
 202, 203, 204,  70,  71,  72, 293, 273, 275,   2,
  59, 145, 126, 127,  40, 287, 286, 283, 284, 285,
 282,  55,  41,  56,  57, 124,  39,  58, 200, 243,
  68,  17, 221,  38, 244,  49,  48,  50, 287, 286,
 283, 284, 285, 282,  70,  71,  72,  45,   1,  61,
   0,  69,  53,  51,  65,   0,   0,  62, 311, 312,
   0,  73,   0, 224,  56,  57,  63,  64,  58,  37,
  68,  17,  83, 232, 233,  49,  48,  50,   0,  70,
  71,  72,   0,   0,  70,  71,  72,  45,   0,  61,
 196,  69,  53,  51,  65, 197,   0,  62,   0,  56,
  57,  73,   0,  58,  56,  57,  63,  64,  58, 122,
 125, 123, 198,  83, 128, 129, 130, 202, 203, 204,
  70,  71,  72, 201,   0,   0,   0,   0,   0, 126,
 127, 196, 301, 302,   0,  46, 197,  81,   0,   0,
  56,  57,   0,   0,  58, 200,   0,   0, 125,   0,
   0,   0,   0,   0,   0, 120,   0,   0,  46,  46,
   0, 122,   0, 123,   0,  83, 128, 129, 130,   0,
   0,   0,  70,  71,  72,   0,   0,   0,  81,  46,
   0, 126, 127, 188,  60, 327, 328, 329, 330, 331,
   0,  46, 255,  57,   0,   0,  58,   0,   0,   0,
   0,   0,   0,  66,   0,   0,   0,   0,   0,   0,
   0, 198,  83,   0,   0,   0, 202, 203, 204,  70,
  71,  72, 125,   0,   0,   0,   0,   0,   0,   0,
 188, 254,   0,   0,   0,  46,  46,  46,   0, 255,
  57,   0,   0,  58, 200, 223,   0,   0,   0,   0,
   0,   0, 166,   0, 168, 169, 170, 171, 172,   0,
 122,  46, 123,   0,  83, 128, 129, 130,   0, 214,
   0,  70,  71,  72, 184, 185,   0,   0,   0,   0,
 126, 127,   0,   0,   0,   0,   0,  81,   0,   0,
   0,  56,  57,   0,   0,  58,   0,  81,  81,   0,
  46,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0, 246, 247,   0,
   0,   0,   0, 226, 198,  83, 155,   0,   0, 202,
 203, 204,  70,  71,  72,   0,   0,   0,   0,   0,
   0, 122,   0, 123, 254,   0, 128, 129, 130,   0,
   0,   0, 255,  57,   0,   0,  58, 200,   0,  46,
   0, 126, 127,   0,   0, 198,  83, 246, 246, 110,
 202, 203, 204,  70,  71,  72,   0,   0,   0, 122,
 195, 123,  19,   0, 128, 129, 130,   0,   0,   0,
   0, 213,   0,  56,  57,   0, 119,  58, 200, 126,
 127,   0,   0,   0,   0,   0,  94,   0,   0,   0,
   0,   0,   0,   0,   0,   0, 106,   0,   0,  83,
 246, 246, 246, 246, 246, 141,  70,  71,  72,   0,
   0,  61,   0,   0,   0,  82,  65, 151, 241,  62,
   0,   0, 253, 256,   0,   0,  56,  57,  63,  64,
  58,   0,   0, 122,   0, 123,   0, 160, 128, 129,
 130, 253, 162,   0,   0,   0, 274,   0, 165,   0,
   0,   0,   0, 126, 127,   0,   0,   0,   0,   0,
   0, 178, 179, 180,   0,   0,   0,   0,   0,   0,
   0, 175,   0,   0,   0, 304, 305, 306, 307,   0,
   0,   0,   0,   0,   0,   0,   0, 205,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 208, 209,   0,   0,   0, 320, 321,
 322, 323, 324, 325, 217,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0, 234,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0, 236, 237,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0, 261,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 291,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 289, 290 };
short yypact[]={

-172,-1000,-240,-281, -74,-240,-1000,-1000,-1000,-1000,
-234, 132,-231, 474, -37, -39, -40, -44, -46,-1000,
-1000,-1000,-1000, -74,-234,-292,-208,-293,-183,-196,
 -30, -31,  98, -74, 132, -36,-1000, -61,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-225, 438,-1000,-222,-224,
-226, -56,-279,-255, 474,  92,-1000,-283,-1000,-1000,
-284,-294,-258,  97,  95,  90,-1000,  92, -64, 400,
 512, 512, 512, 134, -74,-231,-1000,-1000,-1000, -74,
-1000, 512,  85,-228,-1000, -74,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000, 512,-295, 512, 512,
 512, 512, 512,-1000,-1000,-1000,-1000,-1000, -74,-1000,
-220,  92,  92,  92, -68,-1000,-1000,  84, 512, 512,
  83,-1000,-1000,-229,-1000,-262,-1000,-1000, 512, 512,
 512,-296,-297,-306, 421,-1000,-1000,  92, -33, 512,
 -74, -74,-1000, 121, 512, 168,-1000,-230,-1000,-1000,
-1000, -74,-1000,-1000, -34,-1000,-1000,-1000,-1000,  51,
-1000,-1000,-1000, 474,-1000,-1000,  79, 512,  76,  74,
  69,  68,  67, 474, 474,-1000,  92,-1000, -74, -74,
-1000,-1000,-1000,-1000,  66,  65,-1000,-1000, 128,-1000,
-1000,-1000, 421, 319, 127, 116, 380, 421,-235,-1000,
-1000,-1000, 512, 512, 512, -74,-1000,  64,-1000,-1000,
-238,  62,  60, 105,  54, 267,-1000,-1000,-1000,   7,
  12,  51,-307,  56,-1000,-1000,  52,-1000,-1000,-1000,
-1000,-1000, -74, -74,-1000,  92,-1000,-1000,-1000,-1000,
-214,  94,  75, 220, 319,-1000,-1000,  47,-1000, 421,
 421, 421, 421, 155, 124, 121,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
 -35,  51,  51,  -1,  33,-1000, 512, 512, 512, 512,
 512, 512, 421, 421, 421, 421, 421, 421,-1000,-1000,
-1000,-1000,-236,-1000,-1000,-1000, 319, 319, 319, 319,
 319, 142,-1000,-1000, 139, 139,-1000,-1000,-1000, 512,
-1000,-309,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
 164, 164, 164, 164, 164, 164,-1000, 129, 129,-1000,
-1000,-1000,-1000,-1000 };
short yypgo[]={

   0, 378, 699, 223, 363, 485, 356,   0, 355, 712,
 218, 352, 351,  97, 102,  94, 344, 116, 229, 100,
 453, 341, 340, 575,  95, 339, 228, 321, 320, 313,
 311, 302, 104, 276, 271, 168, 262, 261, 257, 250,
 243, 242, 190, 241, 240, 236, 109, 231, 227, 226,
 224, 214, 201, 199, 177 };

short yyr1[]={
   0,   1,  25,  25,  26,  26,   9,   9,  27,  27,
  27,  27,  30,  31,  31,  32,  32,  33,  33,  33,
  15,  12,  12,  28,  34,  34,  35,  35,  36,  36,
  36,  36,  36,  36,  36,  37,  36,  38,  36,  36,
  13,  39,  39,  14,  40,  40,  29,  41,  41,  42,
  42,  43,  43,  44,  44,  45,  47,  45,  45,  48,
  45,  46,  49,  49,   2,   2,   2,   3,   3,   3,
   3,   3,   3,   3,  16,  16,  50,  51,  52,  53,
  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,
  17,  17,  17,  17,  17,  17,  11,   6,   6,   6,
   6,  23,  23,  23,  23,  23,  23,  23,  23,  23,
  23,  23,  10,  10,  10,  10,  10,  10,  10,  10,
  10,   4,   4,   4,   4,  18,  54,  18,  19,  19,
  19,  19,  19,  19,  19,  19,  19,  19,  21,  21,
   8,   8,   8,  24,  24,  24,  22,  22,  22,   5,
   5,   7,   7,   7,   7,   7,   7,   7,  20,  20,
  20,  20,  20,  20,  20,  20 };

short yyr2[]={
   0,   3,   3,   3,   1,   2,   1,   1,   1,   1,
   1,   1,   3,   2,   2,   1,   2,   1,   1,   1,
   3,   3,   2,   3,   2,   3,   1,   2,   4,   5,
   4,   4,   4,   4,   4,   0,   5,   0,   5,   2,
   3,   2,   2,   3,   2,   2,   3,   2,   2,   1,
   2,   3,   1,   2,   2,   1,   0,   3,   2,   0,
   4,   3,   2,   2,   3,   1,   2,   1,   1,   1,
   1,   1,   1,   1,   1,   2,   3,   3,   5,   2,
   3,   3,   3,   2,   3,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   4,   5,   5,   5,
   4,   3,   3,   3,   3,   3,   2,   2,   1,   4,
   1,   1,   3,   3,   3,   3,   3,   3,   2,   1,
   1,   3,   4,   4,   1,   1,   0,   3,   3,   4,
   4,   4,   4,   2,   2,   2,   2,   1,   1,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   0,
   1,   1,   2,   1,   5,   4,   1,   1,   1,   2,
   1,   1,   2,   4,   4,   4 };

short yychk[]={
-1000,  -1, -25, 257, -26, -27, -28, -29, -30, -14,
 -34, -41, -31, -40, 270, 272, 296, 269, 301,  -9,
 125, 256, -26, -35, -36, 258, 260, 259, 261, 262,
 297, 298, 256, -42, -43, -44,  -3, 267,  -4,  -6,
 -16, -11, -13, -14, -15, 285, -20, -19, 274, 273,
 275, 291, -50, 290, -39, -12, 302, 303, 306, -22,
  40, 287, 295, 304, 305, 292,  59, -52, 268, 289,
 282, 283, 284, 299, -32, -33, -13, -14, -15, -18,
 -19, -20, 291, 275, 123, 256, 123, 256, 123, 256,
 123, 256, 123, 256,  -9, -35, 308, 258, 308, 264,
 265, 264, 265, 123, 123,  59,  -9, -42, -45, -46,
  -2, -49, 123,  -3, 266, 123, 256, 264, 286, 288,
  -5,  -7, 271, 273,  -8,  40, 291, 292, 276, 277,
 278, 271, 271, 271, 308,  59, -51, -53, 300, 289,
 -18,  -2, 302, 302, 308, -21, 302, 275,  59,  59,
  59,  -2, 123, 256,  -7, 256,  -7,  -7,  -7,  40,
  -9, -32,  -9, -54, 271,  -9,  -5, 308,  -5,  -5,
  -5,  -5,  -5, -37, -38,  -9, -47, -46,  -2,  -2,
  -2, 123, 256,  59,  -5,  -5,  59, 271, 293,  -7,
  -7,  -7, 308, 308, 308, -23,  40,  45, 274, -24,
 307, -20, 279, 280, 281,  -2, 123,  -7,  -9,  -9,
  41,  -7,  -7, -23, -20,  40, 271,  -9, 123, -17,
  40, 311,  -7, -23, -18,  59,  -5,  59,  59,  59,
  59,  59, -18, -18,  -2, -48,  -9,  -9,  59,  59,
  41, -23, -10,  40,  45,  -7, -20, -20,  59,  43,
  45,  42,  47, -23, 294, 302, -23, 271,  -7,  -7,
  -7,  -9,  59, 271, 291, 292,  59,  59,  59,  59,
  41, 309, 310, -17, -23, -17, 317, 314, 315, 316,
 313, 312, 317, 314, 315, 316, 313, 312,  59,  -9,
  -9,  -2, 274, -24,  59,  59,  43,  45,  42,  47,
  37, -10, -10,  59, -23, -23, -23, -23,  41,  41,
 123, -17, -17,  41,  -7,  -7,  -7,  -7,  -7,  -7,
 -23, -23, -23, -23, -23, -23, 271, -10, -10, -10,
 -10, -10,  41,  -7 };

short yydef[]={
   0,  -2,   0,   0,   0,   4,   8,   9,  10,  11,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
   6,   7,   5,   0,  26,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  49,   0,  52,   0,  67,  68,
  69,  70,  71,  72,  73,   0, 149, 124,   0,   0,
   0,   0,  74,   0,   0,   0, 158,   0, 160, 161,
   0,   0,   0,   0,   0,   0, 137,   0,   0,   0,
   0,   0,   0,   0,   0,  15,  17,  18,  19,   0,
  -2, 149,   0,   0,  24,   0,  47,  48,  13,  14,
  44,  45,   2,   3,  23,  27, 149,   0, 149, 149,
 149, 149, 149,  35,  37,  39,  46,  50,   0,  -2,
   0,   0,   0,  65,   0,  53,  54,   0, 149, 149,
   0, 150, 151,   0, 153,   0, 156, 157,   0,   0,
   0,   0,   0, 162,   0, 135,  75,   0,   0,   0,
   0,   0, 159,   0,   0,   0, 138,   0, 133, 134,
 136,   0,  41,  42,   0,  22, 146, 147, 148,   0,
  12,  16,  43,   0, 162,  25,   0, 149,   0,   0,
   0,   0,   0,   0,   0,  51,   0,  -2,   0,   0,
  66,  62,  63, 121,   0,   0, 128, 152,   0, 140,
 141, 142,   0,   0,   0,   0,   0,   0,   0, 108,
 110, 111,   0,   0,   0,   0,  79,   0,  40,  20,
   0,   0,   0,   0, 111,   0, 139,  76,  21,   0,
   0,   0,   0,   0, 127,  28,   0,  30,  31,  33,
  32,  34,   0,   0,  57,   0,  61,  64, 122, 123,
   0,   0,   0,   0,   0, 119, 120,   0, 100,   0,
   0,   0,   0,   0,   0, 158, 106, 107, 143, 144,
 145,  77,  96, 163, 164, 165, 129, 130, 131, 132,
   0,   0,   0,   0,   0,  83,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  29,  36,
  38,  60,   0, 155,  97,  98,   0,   0,   0,   0,
   0,   0, 118,  99, 102, 103, 104, 105, 101,   0,
  78,  81,  82,  80,  84,  85,  86,  87,  88,  89,
  90,  91,  92,  93,  94,  95, 154, 113, 114, 115,
 116, 117, 112, 109 };
# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)
#ifdef YYIGNORE
# define yyignore *(yypi+1) = 1
#endif

/*	parser for yacc output	*/

#if defined(YYDEBUG)
int yydebug = 0; /* 1 for debugging */
#endif

YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
#ifdef YYIGNORE
char yyi[YYMAXDEPTH+1] = { 0 };
#endif
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

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
		++yypv;
//		memcpy (yypv, &yyval, sizeof (yyval));
		*yypv = yyval;	
#ifdef YYIGNORE
		++yypi;
		*(yypi+1) = *yypi;
#endif

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
//		memcpy (&yyval, &yylval, sizeof (yyval));
		yyval = yylval;
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
//		memcpy (&yyval, &(yypv[1]), sizeof (yyval));
		yyval = yypv[1];
#ifdef YYIGNORE
		yypi -= yyr2[yyn];
		*(yypi+1) = *yypi;
#endif
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
#ifdef YYIGNORE
	if(!*yypi)
#endif
		switch(yym){
			
case 3:
#line 92 "report.y"
{
                        r_error ("Fragwuerdige Reportspezifikation", yypvt[-1].strtok.strline);
                } break;
case 7:
#line 104 "report.y"
{
                        yyerrok;
                        r_error ("Fehlende schlieszende '}'", yylineno);
                } break;
case 12:
#line 118 "report.y"
{       declaration = FALSE;    } break;
case 13:
#line 122 "report.y"
{       declaration = TRUE;     } break;
case 14:
#line 124 "report.y"
{
                        yyerrok;
                        r_error ("Fragwuerdige Deklarationssektion", yypvt[-0].numtok.numline);
                } break;
case 20:
#line 141 "report.y"
{
                register SUBROUTINE *sr_p;

                        if (!declaration) {
                                yylineno = (sr_p = &subroutines[yypvt[-1].numtok.value])->ret_line;
                                yyseek (sr_p->ret_seek);        /* Return */
                        }
                } break;
case 21:
#line 152 "report.y"
{
                        if (declaration) {
                        register SUBROUTINE *sr_p;

                                if (yypvt[-1].numtok.value < 0 || yypvt[-1].numtok.value >= MAXSUBR) {
                                        r_error ("Nicht erlaubte Prozedurnummer", yypvt[-1].numtok.numline);
                                        break;
                                }
                                sr_p = &subroutines[yypvt[-1].numtok.value];
                                sr_p->seek = yytell (0);
                                sr_p->line = yylineno;
                                yyignore;
                        }
                        yyval.numtok.value = yypvt[-1].numtok.value;
                } break;
case 22:
#line 168 "report.y"
{
                        yyerrok;
                        r_error ("Fragwuerdige Prozedurdeklaration", yypvt[-0].numtok.numline);
                } break;
case 28:
#line 187 "report.y"
{
                        Lines = yypvt[-1].numtok.value;
                } break;
case 29:
#line 191 "report.y"
{
                        AllLines = yypvt[-1].numtok.value;
                } break;
case 30:
#line 195 "report.y"
{
                register int cols = yypvt[-1].numtok.value;

                        if (cols > MAXSTRING) Columns = MAXSTRING;
                        else Columns = cols;
                } break;
case 31:
#line 202 "report.y"
{
                        StartPage = yypvt[-1].numtok.value;
                } break;
case 32:
#line 206 "report.y"
{
                        EndPage = yypvt[-1].numtok.value;
                } break;
case 33:
#line 210 "report.y"
{
                        StartTuple = yypvt[-1].numtok.value;
                } break;
case 34:
#line 214 "report.y"
{
                        EndTuple = yypvt[-1].numtok.value;
                } break;
case 35:
#line 218 "report.y"
{
                        form_line = LineBegin;
                        memset (LineBegin, '\0', MAXSTRING);
                } break;
case 36:
#line 223 "report.y"
{
                                        form_line = OutLine;
                                } break;
case 37:
#line 227 "report.y"
{
                        form_line = LineEnd;
                        memset (LineEnd, '\0', MAXSTRING);
                } break;
case 38:
#line 232 "report.y"
{
                                        form_line = OutLine;
                                } break;
case 39:
#line 236 "report.y"
{
                        yyerrok;
                        r_error ("Fragwuerdige Formatangabe", yypvt[-0].numtok.numline);
                } break;
case 40:
#line 244 "report.y"
{
                        if (!declaration) {
                                if (!put_head ()) YYABORT;
                                form_line = OutLine;    /* normale Zeile */
                                ActCol = OutCols;
                                yylineno = head.ret_line;
                                yyseek (head.ret_seek);
                        }
                } break;
case 41:
#line 256 "report.y"
{
                        if (declaration) {
                                head.seek = yytell (0);
                                head.line = yylineno;
                                yyignore;
                        } else {
                                form_line = Header;     /* Headerzeile formatieren */
                                OutCols = ActCol;
                                ActCol = 0;
                                memset (Header, ' ', MAXSTRING);
                        }
                } break;
case 42:
#line 269 "report.y"
{
                        Header[0] = '\0';       /* keine Kopfzeile */
                        form_line = OutLine;
                        yyerrok;
                        r_error ("Fragwuerdige Kopfzeilendeklaration", yypvt[-0].numtok.numline);
                } break;
case 43:
#line 279 "report.y"
{
                        if (!declaration) {
                                if (!put_foot ()) YYABORT;
                                form_line = OutLine;    /* normale Zeile */
                                ActCol = OutCols;
                                yylineno = foot.ret_line;
                                yyseek (foot.ret_seek);
                        }
                } break;
case 44:
#line 291 "report.y"
{
                        if (declaration) {
                                foot.seek = yytell (0);
                                foot.line = yylineno;
                                yyignore;
                        } else {
                                form_line = Footer;
                                OutCols = ActCol;
                                ActCol = 0;
                                memset (Footer, ' ', MAXSTRING);
                        }
                } break;
case 45:
#line 304 "report.y"
{
                        Footer[0] = '\0';
                        form_line = OutLine;
                        yyerrok;
                        r_error ("Fragwuerdige Fussnotendeklaration", yypvt[-0].numtok.numline);
                } break;
case 46:
#line 313 "report.y"
{
                        if (ActLine > 0) {
                                skip (Lines - ActLine);
                                call (&foot);
                                last_foot = TRUE;
                        }
                        else last_foot = FALSE;
                } break;
case 47:
#line 324 "report.y"
{
                        form_line = OutLine;            /* normale Zeile */
                        memset (OutLine, ' ', MAXSTRING);
                        if (ActLine <= 0 || ActLine > Lines) {
                        /* Ausgabe der Kopfzeile */
                                call (&head);
                        }
                } break;
case 48:
#line 333 "report.y"
{
                        r_error ("Fragwuerdige Datenverarbeitungssektion", yypvt[-1].numtok.numline);
                } break;
case 51:
#line 344 "report.y"
{
                        if (for_all_flag) {
                        /* zurueckpositionieren */
                                yyseek (for_all_seek);
                                yylineno = for_all_line;
                        }
                } break;
case 53:
#line 356 "report.y"
{
                        if (for_all_flag == FALSE) {
                        /* nur beim ersten mal */
                                for_all_seek = yytell(0);       /* aktuelle Pos. merken */
                                for_all_line = yylineno;
                                for_all_flag = TRUE;            /* Schleife aktivieren */
                                act_no = lexin (act_in);        /* Lesen erstes Tupel */
                                if (act_no) ActTuple++;
                                next_no = lexin (next_in);      /* lesen naechstes Tupel */
                                last_in = NULL; last_no = 0;
                                /* Feststellen, ob Tuplenummer im erlaubten Bereich */
                                if (ActTuple >= StartTuple && ActTuple <= EndTuple) 
                                        was_allowed =
                                        allow_tuple = TRUE;
                                else
                                        allow_tuple = FALSE;
                        }
                } break;
case 54:
#line 375 "report.y"
{
                        r_error ("Fragwuerdige Tupelverarbeitung.", yypvt[-1].numtok.numline);
                } break;
case 56:
#line 382 "report.y"
{
                        if (for_all_flag == FALSE) yyignore;
                } break;
case 59:
#line 388 "report.y"
{
                        if (for_all_flag == FALSE) yyignore;
                } break;
case 61:
#line 396 "report.y"
{
                /* naechsten Datensatz einlesen */
                        last_in = act_in; last_no = act_no;
                        act_in = next_in; act_no = next_no;
                        next_no = lexin (next_in = input_tab[in_cnt]);
                        if (next_no == 0) {
                                next_in = NULL;
                                next_no = 0;
                        }
                        if (act_no == 0)
                        /* letzter Datensatz */
                                for_all_flag = FALSE;   /* Beenden */
                        else
                                ActTuple++;
                        if (++in_cnt >= 3) in_cnt = 0;
                        /* Feststellen, ob Tuplenummer im erlaubten Bereich */
                        if (ActTuple >= StartTuple && ActTuple <= EndTuple)
                                was_allowed =
                                allow_tuple = TRUE;
                        else
                                allow_tuple = FALSE;
                } break;
case 63:
#line 422 "report.y"
{
                        r_error ("Fragwuerdige Tupelverarbeitung.", yypvt[-1].numtok.numline);
                } break;
case 74:
#line 443 "report.y"
{       if (ignoreflag == TRUE) ignoreflag = FALSE;     } break;
case 75:
#line 445 "report.y"
{       if (ignoreflag == TRUE) ignoreflag = FALSE;     } break;
case 78:
#line 455 "report.y"
{
                        if (!yypvt[-2].numtok.value) {
                                ignoreflag = TRUE;
                                yyignore;
                        }
                } break;
case 79:
#line 464 "report.y"
{
                        if (ignoreflag == TRUE)
                                ignoreflag = FALSE;
                        else {
                                ignoreflag = TRUE;
                                yyignore;
                        }
                } break;
case 80:
#line 475 "report.y"
{       yyval.numtok.value = yypvt[-1].numtok.value;                    } break;
case 81:
#line 477 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value || yypvt[-0].numtok.value);      } break;
case 82:
#line 479 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value && yypvt[-0].numtok.value);      } break;
case 83:
#line 481 "report.y"
{       yyval.numtok.value = !(yypvt[-0].numtok.value);                 } break;
case 84:
#line 483 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value == yypvt[-0].numtok.value);      } break;
case 85:
#line 485 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value != yypvt[-0].numtok.value);      } break;
case 86:
#line 487 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value <= yypvt[-0].numtok.value);      } break;
case 87:
#line 489 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value >= yypvt[-0].numtok.value);      } break;
case 88:
#line 491 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value > yypvt[-0].numtok.value);       } break;
case 89:
#line 493 "report.y"
{       yyval.numtok.value = (yypvt[-2].numtok.value < yypvt[-0].numtok.value);       } break;
case 90:
#line 495 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value == yypvt[-0].realtok.value);      } break;
case 91:
#line 497 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value != yypvt[-0].realtok.value);      } break;
case 92:
#line 499 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value <= yypvt[-0].realtok.value);      } break;
case 93:
#line 501 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value >= yypvt[-0].realtok.value);      } break;
case 94:
#line 503 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value > yypvt[-0].realtok.value);       } break;
case 95:
#line 505 "report.y"
{       yyval.numtok.value = (yypvt[-2].realtok.value < yypvt[-0].realtok.value);       } break;
case 96:
#line 510 "report.y"
{
                register SUBROUTINE *sr_p;

                        if (yypvt[-2].numtok.value < 0 || yypvt[-2].numtok.value >= MAXSUBR) {
                                r_error ("Nicht erlaubte Prozedurnummer", yypvt[-2].numtok.numline);
                                break;
                        }
                        sr_p = &subroutines[yypvt[-2].numtok.value];
                        if (call (sr_p)) {      /* Abarbeiten */
                                r_error ("Nicht deklarierte Prozedur", yypvt[-2].numtok.numline);
                                break;
                        }
                        yyval.numtok.value = yypvt[-2].numtok.value;
                } break;
case 97:
#line 528 "report.y"
{
                register VARIABLE *var_p;

                        if (yypvt[-3].numtok.value < 0 || yypvt[-3].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-4].numtok.numline);
                                break;
                        }
                        if ((var_p = &var_table[yypvt[-3].numtok.value])->ptr == NULL) {
                                if ((var_p->ptr = (char *)calloc (1, sizeof(double))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'f') {
                                if ((var_p->ptr = (char *)realloc (var_p->ptr, sizeof(double))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        *(double *)(var_p->ptr) = yypvt[-1].realtok.value;
                        var_p->type = 'f';
                } break;
case 98:
#line 550 "report.y"
{
                register VARIABLE *var_p;

                        if (yypvt[-3].numtok.value < 0 || yypvt[-3].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-4].numtok.numline);
                                break;
                        }
                        if ((var_p = &var_table[yypvt[-3].numtok.value])->ptr == NULL) {
                                if ((var_p->ptr = (char *)calloc (1, sizeof(int))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'i') {
                                if ((var_p->ptr = (char *)realloc (var_p->ptr, sizeof(int))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        *(int *)(var_p->ptr) = yypvt[-1].numtok.value;
                        var_p->type = 'i';
                } break;
case 99:
#line 572 "report.y"
{
                register VARIABLE *var_p;

                        if (yypvt[-3].numtok.value < 0 || yypvt[-3].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-4].numtok.numline);
                                break;
                        }
                        if ((var_p = &var_table[yypvt[-3].numtok.value])->ptr == NULL) {
                                if ((var_p->ptr = (char *)calloc (1, MAXSTRING+1)) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'i') {
                                if ((var_p->ptr = (char *)realloc (var_p->ptr, MAXSTRING+1)) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        strncpy (var_p->ptr, yypvt[-1].strtok.str, MAXSTRING);
                        var_p->type = 's';
                } break;
case 100:
#line 594 "report.y"
{
                        system_var[yypvt[-3].numtok.index].var_wert = (int)yypvt[-1].realtok.value;
                } break;
case 101:
#line 601 "report.y"
{       yyval.realtok.value = yypvt[-1].realtok.value;    } break;
case 102:
#line 603 "report.y"
{       yyval.realtok.value = yypvt[-2].realtok.value + yypvt[-0].realtok.value; } break;
case 103:
#line 605 "report.y"
{       yyval.realtok.value = yypvt[-2].realtok.value - yypvt[-0].realtok.value; } break;
case 104:
#line 607 "report.y"
{       yyval.realtok.value = yypvt[-2].realtok.value * yypvt[-0].realtok.value; } break;
case 105:
#line 609 "report.y"
{       yyval.realtok.value = yypvt[-2].realtok.value / yypvt[-0].realtok.value; } break;
case 106:
#line 611 "report.y"
{       yyval.realtok.value = - yypvt[-0].realtok.value;          } break;
case 107:
#line 613 "report.y"
{
                        if (yypvt[-0].numtok.value < 0 || yypvt[-0].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-1].numtok.numline);
                                break;
                        }
                        if (var_table[yypvt[-0].numtok.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", yypvt[-1].numtok.numline);
                                yyval.realtok.value = 0;
                        } else if (var_table[yypvt[-0].numtok.value].type != 'f')
                                r_error ("Variable ist kein Real.", yypvt[-1].numtok.numline);
                        else
                                yyval.realtok.value = *(double *)var_table[yypvt[-0].numtok.value].ptr;
                } break;
case 108:
#line 627 "report.y"
{       yyval.realtok.value = yypvt[-0].realtok.value;    } break;
case 109:
#line 629 "report.y"
{       yyval.realtok.value = (double)yypvt[-0].numtok.value;    } break;
case 111:
#line 632 "report.y"
{
                        r_error ("String in arithmetischem Ausdruck", yypvt[-0].strtok.strline);
                } break;
case 112:
#line 640 "report.y"
{       yyval.numtok.value = yypvt[-1].numtok.value;    } break;
case 113:
#line 642 "report.y"
{       yyval.numtok.value = yypvt[-2].numtok.value + yypvt[-0].numtok.value; } break;
case 114:
#line 644 "report.y"
{       yyval.numtok.value = yypvt[-2].numtok.value - yypvt[-0].numtok.value; } break;
case 115:
#line 646 "report.y"
{       yyval.numtok.value = yypvt[-2].numtok.value * yypvt[-0].numtok.value; } break;
case 116:
#line 648 "report.y"
{       yyval.numtok.value = yypvt[-2].numtok.value / yypvt[-0].numtok.value; } break;
case 117:
#line 650 "report.y"
{       yyval.numtok.value = yypvt[-2].numtok.value % yypvt[-0].numtok.value; } break;
case 118:
#line 652 "report.y"
{       yyval.numtok.value = - yypvt[-0].numtok.value;          } break;
case 120:
#line 655 "report.y"
{
                        r_error ("String in arithmetischem Ausdruck", yypvt[-0].strtok.strline);
                } break;
case 121:
#line 663 "report.y"
{
                        if (!new_page ()) YYABORT;
                } break;
case 122:
#line 667 "report.y"
{
                /* Ausgabe der Kopf- und Fusszeile */
                        if (ActLine > Lines) {
                                call (&head);
                                call (&foot);
                        }
                        if (!new_line ((short)yypvt[-1].numtok.value)) YYABORT;
                } break;
case 123:
#line 676 "report.y"
{
                        r_error ("BATCH noch nicht verfuegbar", yypvt[-2].numtok.numline);
                } break;
case 124:
#line 680 "report.y"
{
                        out_string (yypvt[-0].strtok.str);
                } break;
case 125:
#line 686 "report.y"
{
                        out_string (yypvt[-0].strtok.str);
                } break;
case 126:
#line 691 "report.y"
{
                        out_string (yypvt[-0].strtok.str);
                } break;
case 128:
#line 698 "report.y"
{
                register int i = yypvt[-1].numtok.value, len = 0;

                        yyval.strtok.str[0] = '\0';
                        while (i-- > 0 && len < MAXSTRING) {
                                len = strlen (yyval.strtok.str);
                                strncat (yyval.strtok.str, yypvt[-2].strtok.str, MAXSTRING-len);
                        }
                } break;
case 129:
#line 708 "report.y"
{
                register int cols = yypvt[-1].numtok.value;

                        if (cols > Columns) cols = Columns;
                        ActCol = cols;
                        yyval.strtok.str[0] = '\0';
                } break;
case 130:
#line 716 "report.y"
{
                        sprintf (yyval.strtok.str, yypvt[-2].strtok.str, yypvt[-1].numtok.value);
                } break;
case 131:
#line 720 "report.y"
{
                        sprintf (yyval.strtok.str, yypvt[-2].strtok.str, yypvt[-1].realtok.value);
                } break;
case 132:
#line 724 "report.y"
{
                        sprintf (yyval.strtok.str, yypvt[-2].strtok.str, yypvt[-1].strtok.str);
                } break;
case 133:
#line 728 "report.y"
{
                long clock;
                register struct tm *tm;

                        time (&clock);
                        tm = localtime (&clock);
                        sprintf (yyval.strtok.str, "%02d-%3.3s-%02d", tm->tm_mday,
                                        month[tm->tm_mon], tm->tm_year);
                } break;
case 134:
#line 738 "report.y"
{
                long clock;
                register struct tm *tm;

                        time (&clock);
                        tm = localtime (&clock);
                        sprintf (yyval.strtok.str, "%2d.%02d.%02d", tm->tm_hour,
                                        tm->tm_min, tm->tm_sec);
                } break;
case 135:
#line 748 "report.y"
{
system_variable:
                        sprintf (yyval.strtok.str, "%d", yypvt[-1].numtok.value);
                } break;
case 136:
#line 753 "report.y"
{
                        goto system_variable;
                } break;
case 137:
#line 757 "report.y"
{
                        yyval.strtok.str[0] = '\0';       /* NOP */
                } break;
case 139:
#line 765 "report.y"
{
                        if (yypvt[-0].numtok.value < 0 || yypvt[-0].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-1].numtok.numline);
                                break;
                        }
                        if (var_table[yypvt[-0].numtok.value].type != 's')
                                r_error ("Variable ist kein String.", yypvt[-1].numtok.numline);
                        else
                                strcpy (yyval.strtok.str, var_table[yypvt[-0].numtok.value].ptr);
                } break;
case 140:
#line 780 "report.y"
{
                        p = last_in;
input_int:
                        if (p != NULL) {
                                yyval.numtok.value = *(int *)p[yypvt[-0].numtok.value].ptr;
                                yyval.numtok.numline = 'i';
                        } else memset (&yyval.numtok, '\0', sizeof(yyval.numtok));
                } break;
case 141:
#line 789 "report.y"
{
                        p = act_in;
                        goto input_int;
                } break;
case 142:
#line 794 "report.y"
{
                        p = next_in;
                        goto input_int;
                } break;
case 143:
#line 801 "report.y"
{
                        p = last_in;
input_real:
			if (p != NULL) {
                                yyval.realtok.value = *(double *)p[yypvt[-0].numtok.value].ptr;
                                yyval.realtok.numline = 'f';
                        } else memset (&yyval.realtok, '\0', sizeof(yyval.realtok));
                } break;
case 144:
#line 810 "report.y"
{
                        p = act_in;
                        goto input_real;
                } break;
case 145:
#line 815 "report.y"
{
                        p = next_in;
                        goto input_real;
                } break;
case 146:
#line 822 "report.y"
{
                        p = last_in;
input_string:
                        if (p != NULL) {
                                strcpy (yyval.strtok.str, p[yypvt[-0].numtok.value].ptr);
                                yyval.strtok.strline = 's';
                        } else memset (&yyval.strtok, '\0', sizeof(yyval.strtok));
                } break;
case 147:
#line 831 "report.y"
{
                        p = act_in;
                        goto input_string;
                } break;
case 148:
#line 836 "report.y"
{
                        p = next_in;
                        goto input_string;
                } break;
case 149:
#line 844 "report.y"
{       yyval.numtok.value = 1;   } break;
case 152:
#line 850 "report.y"
{
                        if (yypvt[-0].numtok.value < 0 || yypvt[-0].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-1].numtok.numline);
                                break;
                        }
                        if (var_table[yypvt[-0].numtok.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", yypvt[-1].numtok.numline);
                                yyval.numtok.value = 0;
                        } else if (var_table[yypvt[-0].numtok.value].type != 'i')
                                r_error ("Variable ist kein Integer.", yypvt[-1].numtok.numline);
                        else
                                yyval.numtok.value = *(int *)var_table[yypvt[-0].numtok.value].ptr;
                } break;
case 153:
#line 864 "report.y"
{
                        yyval.numtok.value = yypvt[-0].numtok.value;
                } break;
case 154:
#line 868 "report.y"
{
                        if (yypvt[-0].numtok.value < 0 || yypvt[-0].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-1].numtok.numline);
                                break;
                        }
                        if (var_table[yypvt[-0].numtok.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", yypvt[-1].numtok.numline);
                                yyval.numtok.value = 0;
                        } else if (var_table[yypvt[-0].numtok.value].type != 'f')
                                r_error ("Variable ist kein Real.", yypvt[-1].numtok.numline);
                        else
                                yyval.numtok.value = (int)(*(double *)var_table[yypvt[-0].numtok.value].ptr);
                } break;
case 155:
#line 882 "report.y"
{
                        yyval.numtok.value = (int)yypvt[-0].realtok.value;
                } break;
case 159:
#line 892 "report.y"
{
                register FILE *tty;

                        if ((tty = fopen ("/dev/tty", "w+")) == NULL)
                                r_error ("kann Terminal nicht eroeffnen",
                                                                yypvt[-1].strtok.strline);
                        fputs (yypvt[-0].strtok.str, tty);
                        fputs ("> ", tty);
                        yyval.strtok.str[0] = '\0';
                        fgets (yyval.strtok.str, sizeof(yyval.strtok.str)-1, tty);
                } break;
case 160:
#line 904 "report.y"
{
                        strcpy (yyval.strtok.str, " ");
                } break;
case 162:
#line 909 "report.y"
{
                        if (yypvt[-0].numtok.value < 0 || yypvt[-0].numtok.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", yypvt[-1].numtok.numline);
                                break;
                        }
                        if (var_table[yypvt[-0].numtok.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", yypvt[-1].numtok.numline);
                                yyval.strtok.str[0] = '\0';
                        } else if (var_table[yypvt[-0].numtok.value].type != 's')
                                r_error ("Variable ist kein String.", yypvt[-1].numtok.numline);
                        else
                                strncpy (yyval.strtok.str, var_table[yypvt[-0].numtok.value].ptr, MAXSTRING);
                } break;
case 163:
#line 923 "report.y"
{
number_cnvrt:
                        sprintf (yyval.strtok.str, "%d", yypvt[-3].numtok.value);
                } break;
case 164:
#line 928 "report.y"
{
                        goto number_cnvrt;
                } break;
case 165:
#line 932 "report.y"
{
                        goto number_cnvrt;
                } break;
		}
		goto yystack;  /* stack new state and value */

	}



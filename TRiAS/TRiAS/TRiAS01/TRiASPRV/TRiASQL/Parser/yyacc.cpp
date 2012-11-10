
/*  A Bison parser, made from sql.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	IDENTIFIER	258
#define	LEFTPAREN	259
#define	RIGHTPAREN	260
#define	COMMA	261
#define	STRING_VALUE	262
#define	FLOAT_VALUE	263
#define	NUMBER_VALUE	264
#define	DATE_VALUE	265
#define	SQL_NULL	266
#define	FROM	267
#define	AS	268
#define	WHERE	269
#define	EQUALS	270
#define	DOT	271
#define	LESS	272
#define	MORE	273
#define	LESS_EQUALS	274
#define	MORE_EQUALS	275
#define	IS	276
#define	NOT_EQUALS	277
#define	SELECT	278
#define	STAR	279
#define	COUNT	280
#define	DISTINCT	281
#define	AVG	282
#define	MAX	283
#define	MIN	284
#define	SUM	285
#define	ORDER	286
#define	BY	287
#define	ASC	288
#define	DESC	289
#define	ALL	290
#define	GROUP	291
#define	HAVING	292
#define	SQL_DELETE	293
#define	UPDATE	294
#define	SET	295
#define	INSERT	296
#define	INTO	297
#define	VALUES	298
#define	DROP	299
#define	CREATE	300
#define	TABLE	301
#define	CHAR_DATATYPE	302
#define	SMALLINT_DATATYPE	303
#define	INTEGER_DATATYPE	304
#define	FLOAT_DATATYPE	305
#define	TEXT_DATATYPE	306
#define	TOP	307
#define	PERCENT	308
#define	ASTEXT	309
#define	ASBINARY	310
#define	DIMENSION	311
#define	GEOMETRYTYPE	312
#define	SRID	313
#define	ISEMPTY	314
#define	ABS	315
#define	ROUND	316
#define	GETDATE	317
#define	MINUS	318
#define	PLUS	319
#define	LIKE	320
#define	DIVIDE	321
#define	AND	322
#define	OR	323
#define	NOT	324

			   

#include <stdio.h>
#include "stdafx.h"
#include "flexlexer.h"
#include "ParseTree.h"
#include <malloc.h>

#define YYSTYPE CSQLNode *

extern "C++" int  yylex(void);

#define YYERROR_VERBOSE
#define YYDEBUG 1


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		257
#define	YYFLAG		-32768
#define	YYNTBASE	70

#define YYTRANSLATE(x) ((unsigned)(x) <= 324 ? yytranslate[x] : 111)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,    15,    26,    31,    37,    46,    48,    55,
    59,    60,    62,    64,    65,    68,    72,    74,    78,    80,
    84,    87,    91,    92,    94,    98,   100,   104,   105,   108,
   110,   114,   118,   122,   126,   130,   132,   136,   140,   142,
   146,   150,   153,   157,   161,   165,   169,   173,   177,   181,
   186,   190,   194,   198,   202,   204,   206,   210,   212,   216,
   219,   221,   223,   227,   231,   235,   239,   243,   245,   247,
   249,   251,   253,   255,   257,   261,   265,   269,   273,   277,
   278,   282,   283,   286,   287,   291,   293,   297,   299,   302,
   305,   307,   309,   311,   313,   318,   323,   327,   332,   337,
   342,   347,   352,   357,   362,   367,   372,   377,   382,   387,
   390,   395,   400,   402,   404,   406,   408,   410,   412,   414,
   416,   418
};

static const short yyrhs[] = {    71,
     0,    72,     0,    23,    73,    74,    75,    12,    87,    80,
    94,    95,    96,     0,    23,    73,    74,    24,    12,    87,
    80,    94,    95,    96,     0,    38,    12,    89,    80,     0,
    39,    89,    40,    82,    80,     0,    41,    42,    89,    77,
    43,     4,    79,     5,     0,    89,     0,    45,    46,    89,
     4,   105,     5,     0,    44,    46,    89,     0,     0,    35,
     0,    26,     0,     0,    52,   108,     0,    52,   108,    53,
     0,    76,     0,    75,     6,    76,     0,    90,     0,    90,
    13,    89,     0,    90,    89,     0,     4,    78,     5,     0,
     0,    86,     0,    78,     6,    86,     0,    81,     0,    79,
     6,    81,     0,     0,    14,    84,     0,    99,     0,    81,
    64,    81,     0,    81,    63,    81,     0,    81,    66,    81,
     0,    81,    24,    81,     0,     4,    81,     5,     0,    83,
     0,    82,     6,    83,     0,    86,    15,    93,     0,    85,
     0,    84,    68,    84,     0,    84,    67,    84,     0,    69,
    84,     0,     4,    84,     5,     0,    93,    15,    93,     0,
    93,    22,    93,     0,    93,    17,    93,     0,    93,    18,
    93,     0,    93,    19,    93,     0,    93,    20,    93,     0,
    86,    21,    69,    11,     0,    86,    21,    11,     0,    86,
    65,   110,     0,    89,    16,    89,     0,    89,    16,    24,
     0,    89,     0,    88,     0,    87,     6,    88,     0,    89,
     0,    89,    13,    89,     0,    89,    89,     0,     3,     0,
    91,     0,    90,    64,    90,     0,    90,    63,    90,     0,
    90,    66,    90,     0,    90,    24,    90,     0,     4,    90,
     5,     0,    92,     0,   104,     0,   100,     0,    99,     0,
    86,     0,    92,     0,   100,     0,    93,    64,    93,     0,
    93,    63,    93,     0,    93,    66,    93,     0,    93,    24,
    93,     0,     4,    93,     5,     0,     0,    36,    32,    86,
     0,     0,    37,    84,     0,     0,    31,    32,    97,     0,
    98,     0,    97,     6,    98,     0,    86,     0,    86,    33,
     0,    86,    34,     0,   107,     0,   101,     0,   102,     0,
   103,     0,    60,     4,    93,     5,     0,    61,     4,    93,
     5,     0,    62,     4,     5,     0,    54,     4,    93,     5,
     0,    55,     4,    93,     5,     0,    56,     4,    93,     5,
     0,    57,     4,    93,     5,     0,    58,     4,    93,     5,
     0,    59,     4,    93,     5,     0,    30,     4,    93,     5,
     0,    27,     4,    93,     5,     0,    28,     4,    93,     5,
     0,    29,     4,    93,     5,     0,    25,     4,    93,     5,
     0,    25,     4,    24,     5,     0,    89,   106,     0,   105,
     6,    89,   106,     0,    47,     4,   108,     5,     0,    49,
     0,    50,     0,    48,     0,    51,     0,   108,     0,   109,
     0,   110,     0,     9,     0,     8,     0,     7,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    53,    59,    67,    82,    97,   104,   112,   120,   130,   137,
   145,   150,   155,   162,   167,   173,   181,   186,   194,   199,
   206,   215,   220,   227,   232,   240,   245,   253,   259,   268,
   273,   280,   287,   294,   301,   308,   313,   321,   330,   335,
   342,   349,   356,   363,   370,   377,   384,   391,   398,   405,
   412,   419,   428,   435,   444,   453,   458,   466,   471,   478,
   487,   494,   499,   506,   513,   520,   527,   534,   539,   544,
   551,   556,   563,   568,   573,   580,   587,   594,   601,   608,
   614,   621,   626,   633,   639,   646,   651,   659,   665,   671,
   679,   696,   701,   706,   713,   719,   727,   734,   741,   747,
   753,   759,   765,   773,   779,   785,   791,   797,   803,   811,
   817,   826,   832,   837,   842,   847,   854,   859,   864,   871,
   878,   885
};

static const char * const yytname[] = {   "$","error","$undefined.","IDENTIFIER",
"LEFTPAREN","RIGHTPAREN","COMMA","STRING_VALUE","FLOAT_VALUE","NUMBER_VALUE",
"DATE_VALUE","SQL_NULL","FROM","AS","WHERE","EQUALS","DOT","LESS","MORE","LESS_EQUALS",
"MORE_EQUALS","IS","NOT_EQUALS","SELECT","STAR","COUNT","DISTINCT","AVG","MAX",
"MIN","SUM","ORDER","BY","ASC","DESC","ALL","GROUP","HAVING","SQL_DELETE","UPDATE",
"SET","INSERT","INTO","VALUES","DROP","CREATE","TABLE","CHAR_DATATYPE","SMALLINT_DATATYPE",
"INTEGER_DATATYPE","FLOAT_DATATYPE","TEXT_DATATYPE","TOP","PERCENT","ASTEXT",
"ASBINARY","DIMENSION","GEOMETRYTYPE","SRID","ISEMPTY","ABS","ROUND","GETDATE",
"MINUS","PLUS","LIKE","DIVIDE","AND","OR","NOT","Command","SQL_Statement","DDL_Statement",
"AllDistinct","TopRows","SelectElementList","SelectExpressionAsName","InsertColSpec",
"ColList","InsertValueList","WhereClause","ConstantExpression","UpdateList",
"UpdateValue","WhereConditions","WherePredicate","ColName","IdentList","IdentifierWithAlias",
"Identifier","SelectExpression","SelectExpressionItem","ValueOrColName","ValueOrColNameExpression",
"GroupByClause","HavingClause","OrderClause","OrderColList","OrderCol","Value",
"Function","MathFunction","DateFunction","GeometryFunction","Aggregate","ColDataTypeList",
"DataType","LiteralValue","Number","Float","String",""
};
#endif

static const short yyr1[] = {     0,
    70,    70,    71,    71,    71,    71,    71,    71,    72,    72,
    73,    73,    73,    74,    74,    74,    75,    75,    76,    76,
    76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
    81,    81,    81,    81,    81,    82,    82,    83,    84,    84,
    84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
    85,    85,    86,    86,    86,    87,    87,    88,    88,    88,
    89,    90,    90,    90,    90,    90,    90,    91,    91,    91,
    92,    92,    93,    93,    93,    93,    93,    93,    93,    94,
    94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
    99,   100,   100,   100,   101,   101,   102,   103,   103,   103,
   103,   103,   103,   104,   104,   104,   104,   104,   104,   105,
   105,   106,   106,   106,   106,   106,   107,   107,   107,   108,
   109,   110
};

static const short yyr2[] = {     0,
     1,     1,    10,    10,     4,     5,     8,     1,     6,     3,
     0,     1,     1,     0,     2,     3,     1,     3,     1,     3,
     2,     3,     0,     1,     3,     1,     3,     0,     2,     1,
     3,     3,     3,     3,     3,     1,     3,     3,     1,     3,
     3,     2,     3,     3,     3,     3,     3,     3,     3,     4,
     3,     3,     3,     3,     1,     1,     3,     1,     3,     2,
     1,     1,     3,     3,     3,     3,     3,     1,     1,     1,
     1,     1,     1,     1,     3,     3,     3,     3,     3,     0,
     3,     0,     2,     0,     3,     1,     3,     1,     2,     2,
     1,     1,     1,     1,     4,     4,     3,     4,     4,     4,
     4,     4,     4,     4,     4,     4,     4,     4,     4,     2,
     4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1
};

static const short yydefact[] = {     0,
    61,    11,     0,     0,     0,     0,     0,     1,     2,     8,
    13,    12,    14,     0,     0,     0,     0,     0,     0,     0,
    28,     0,    23,    10,     0,   120,    15,     0,   122,   121,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    17,    72,    55,    19,
    62,    68,    71,    70,    92,    93,    94,    69,    91,   117,
   118,   119,     0,     5,    28,    36,     0,     0,     0,     0,
    16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    21,     0,     0,    29,    39,
    72,    73,     0,    74,     0,     6,     0,     0,    24,     0,
     0,     0,    67,    28,    56,    58,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    97,    18,    28,    54,    53,    20,    66,    64,    63,
    65,     0,     0,    42,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
    22,     0,     0,     0,   115,   113,   114,   116,   110,     9,
     0,     0,    80,     0,    60,     0,   109,   108,   105,   106,
   107,   104,    98,    99,   100,   101,   102,   103,    95,    96,
    80,    43,    79,    41,    40,    51,     0,    52,    44,    46,
    47,    48,    49,    45,    78,    76,    75,    77,    25,     0,
     0,    26,    30,     0,     0,    57,     0,    82,    59,    82,
    50,     0,     7,     0,     0,     0,     0,     0,     0,   111,
     0,     0,    84,    84,    35,    27,    34,    32,    31,    33,
   112,    81,    83,     0,     4,     3,     0,    88,    85,    86,
    89,    90,     0,    87,     0,     0,     0
};

static const short yydefgoto[] = {   255,
     8,     9,    13,    20,    46,    47,    69,   108,   211,    64,
   212,    65,    66,    99,   100,    48,   114,   115,    49,    50,
    51,   102,   103,   218,   233,   245,   249,   250,    53,   104,
    55,    56,    57,    58,   112,   169,    59,    60,    61,    62
};

static const short yypact[] = {   432,
-32768,   -16,     2,    39,     3,    10,    20,-32768,-32768,-32768,
-32768,-32768,     7,    39,    47,    39,    39,    39,    64,   315,
    76,    39,   107,-32768,   118,-32768,    79,   324,-32768,-32768,
   124,   140,   146,   152,   157,   160,   165,   169,   170,   173,
   187,   188,   195,   201,   212,    80,-32768,-32768,   122,   138,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   126,-32768,     1,-32768,   137,    39,   116,    39,
-32768,    91,    39,   384,   355,   355,   355,   355,   355,   355,
   355,   355,   355,   355,   355,   355,   218,   324,    39,    13,
    39,   324,   324,   324,   324,-32768,   126,   126,   -55,-32768,
   -10,-32768,   403,-32768,    39,-32768,   355,    92,-32768,   213,
   287,   104,-32768,    54,-32768,    35,   355,   222,   134,   155,
   166,   184,   189,   198,   202,   210,   215,   219,   230,   235,
   239,-32768,-32768,    54,-32768,-32768,-32768,-32768,    15,    15,
-32768,    12,   148,-32768,   126,   126,    -5,   186,   355,   355,
   355,   355,   355,   355,   355,   355,   355,   355,-32768,    -1,
-32768,    39,   229,   224,-32768,-32768,-32768,-32768,-32768,-32768,
    39,    39,   205,    39,-32768,   246,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   205,-32768,-32768,-32768,-32768,-32768,   231,-32768,    -1,    -1,
    -1,    -1,    -1,    -1,-32768,    16,    16,-32768,-32768,   229,
   108,    25,-32768,    64,   287,-32768,   174,   208,-32768,   208,
-32768,   251,-32768,   229,   229,   229,   229,   229,   241,-32768,
    39,   126,   226,   226,-32768,    25,-32768,    19,    19,-32768,
-32768,-32768,   -55,   217,-32768,-32768,    39,   109,   252,-32768,
-32768,-32768,    39,-32768,   260,   267,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   181,-32768,-32768,-32768,   -56,
    62,-32768,   172,   -95,-32768,   -22,   182,   112,     4,   -23,
-32768,    24,   -50,    89,    71,    58,-32768,    42,   -79,    33,
-32768,-32768,-32768,-32768,-32768,    82,-32768,   -18,-32768,   156
};


#define	YYLAST		477


static const short yytable[] = {    67,
    27,   142,   144,    10,    72,   196,   105,    15,   106,    11,
   147,   145,   146,    14,    63,     1,   192,    21,    12,    23,
    24,    25,   155,   119,   120,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   135,     1,    92,   155,
   101,     1,   225,    52,    16,   109,   143,   174,   225,   194,
   195,    52,    54,    96,   148,    17,   160,   173,    19,   172,
    54,   156,   157,   197,   158,    18,   176,    63,   138,   139,
   140,   141,    26,   111,   101,   101,   116,   191,   145,   146,
    95,   158,    67,   213,   228,    88,    22,   226,   227,    63,
   228,    89,   116,   136,   137,   113,   161,   162,   199,   200,
   201,   202,   203,   204,   205,   206,   207,   208,   170,   171,
    68,    52,   223,   224,    92,    52,    52,    52,    52,   175,
    54,    70,   101,   101,    54,    54,    54,    54,     1,    97,
   213,    71,    29,    30,    26,    73,   243,    90,   178,   209,
     1,   251,   252,    74,   213,   213,   213,   213,   213,    75,
    91,   107,   193,    93,    94,    76,    95,   155,   110,   179,
    77,    92,   149,    78,   150,   151,   152,   153,    79,   154,
   180,   155,    80,    81,   215,   116,    82,   219,   155,    37,
    38,    39,    40,    41,    42,    43,    44,    45,   181,   155,
    83,    84,    29,   182,    98,   229,   156,   157,    85,   158,
    93,    94,   183,    95,    86,   231,   184,   155,   242,   101,
   156,   157,   155,   158,   185,    87,   163,   156,   157,   186,
   158,   155,   132,   187,   248,   155,   177,   214,   156,   157,
   248,   158,   210,   155,   188,    29,    30,    26,   155,   189,
   217,   221,   155,   190,   232,   241,   156,   157,   247,   158,
   193,   156,   157,   155,   158,   235,   244,   253,   155,   256,
   156,   157,   155,   158,   156,   157,   257,   158,   133,   155,
   134,   222,   156,   157,   225,   158,   159,   156,   157,   220,
   158,   156,   157,   216,   158,   236,   237,   238,   239,   240,
   234,   246,   156,   157,   254,   158,   230,   156,   157,     0,
   158,   156,   157,   198,   158,     0,     0,     0,   156,   157,
     0,   158,     0,   226,   227,     0,   228,     1,    28,     0,
     0,    29,    30,    26,     0,     0,     1,    28,     0,     0,
    29,    30,    26,   164,   165,   166,   167,   168,    31,    32,
     0,    33,    34,    35,    36,     0,     0,     0,    32,     0,
    33,    34,    35,    36,     0,     0,     0,     1,   117,     0,
     0,    29,    30,    26,     0,     0,     0,     0,    37,    38,
    39,    40,    41,    42,    43,    44,    45,    37,    38,    39,
    40,    41,    42,    43,    44,    45,     1,   117,     0,     0,
    29,    30,    26,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   118,    37,    38,
    39,    40,    41,    42,    43,    44,    45,   149,     0,   150,
   151,   152,   153,     0,   154,     0,   155,     0,     0,     0,
     0,     0,     0,     0,     1,     0,     0,    37,    38,    39,
    40,    41,    42,    43,    44,    45,     0,     0,     0,     0,
     0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   156,   157,     0,   158,     3,
     4,     0,     5,     0,     0,     6,     7
};

static const short yycheck[] = {    22,
    19,    97,    98,     0,    28,    11,     6,     4,    65,    26,
    21,    67,    68,    12,    14,     3,     5,    14,    35,    16,
    17,    18,    24,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    24,     3,    24,    24,
    63,     3,    24,    20,    42,    68,    97,    13,    24,   145,
   146,    28,    20,    50,    65,    46,   107,   114,    52,     6,
    28,    63,    64,    69,    66,    46,   117,    14,    92,    93,
    94,    95,     9,    70,    97,    98,    73,   134,    67,    68,
    66,    66,   105,   163,    66,     6,    40,    63,    64,    14,
    66,    12,    89,    90,    91,     5,     5,     6,   149,   150,
   151,   152,   153,   154,   155,   156,   157,   158,     5,     6,
     4,    88,     5,     6,    24,    92,    93,    94,    95,   116,
    88,     4,   145,   146,    92,    93,    94,    95,     3,     4,
   210,    53,     7,     8,     9,    12,   232,    16,     5,   162,
     3,    33,    34,     4,   224,   225,   226,   227,   228,     4,
    13,    15,     5,    63,    64,     4,    66,    24,    43,     5,
     4,    24,    15,     4,    17,    18,    19,    20,     4,    22,
     5,    24,     4,     4,   171,   172,     4,   174,    24,    54,
    55,    56,    57,    58,    59,    60,    61,    62,     5,    24,
     4,     4,     7,     5,    69,   214,    63,    64,     4,    66,
    63,    64,     5,    66,     4,    32,     5,    24,   231,   232,
    63,    64,    24,    66,     5,     4,     4,    63,    64,     5,
    66,    24,     5,     5,   247,    24,     5,     4,    63,    64,
   253,    66,     4,    24,     5,     7,     8,     9,    24,     5,
    36,    11,    24,     5,    37,     5,    63,    64,    32,    66,
     5,    63,    64,    24,    66,     5,    31,     6,    24,     0,
    63,    64,    24,    66,    63,    64,     0,    66,    88,    24,
    89,   210,    63,    64,    24,    66,   105,    63,    64,   191,
    66,    63,    64,   172,    66,   224,   225,   226,   227,   228,
   220,   234,    63,    64,   253,    66,   215,    63,    64,    -1,
    66,    63,    64,   148,    66,    -1,    -1,    -1,    63,    64,
    -1,    66,    -1,    63,    64,    -1,    66,     3,     4,    -1,
    -1,     7,     8,     9,    -1,    -1,     3,     4,    -1,    -1,
     7,     8,     9,    47,    48,    49,    50,    51,    24,    25,
    -1,    27,    28,    29,    30,    -1,    -1,    -1,    25,    -1,
    27,    28,    29,    30,    -1,    -1,    -1,     3,     4,    -1,
    -1,     7,     8,     9,    -1,    -1,    -1,    -1,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    54,    55,    56,
    57,    58,    59,    60,    61,    62,     3,     4,    -1,    -1,
     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    15,    -1,    17,
    18,    19,    20,    -1,    22,    -1,    24,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,     3,    -1,    -1,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    66,    38,
    39,    -1,    41,    -1,    -1,    44,    45
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */


/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)

#define yyerror(s) pState->SetError(s, pLexer->YYText())

#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *froma, char *toa, int nccount)
{
  register char *f = froma;
  register char *t = toa;
  register int i = nccount;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#undef YYLEX
#define YYLEX pLexer->yylex()
//You need to change yyparse to look like this - and remove unistd.h
int yyparse(CParseTree *pState, yyFlexLexer *pLexer)
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval = 0;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
{
	// Command:  SQL_Statement
		yyval = yyvsp[0];
		pState->SetFirst (	yyval);
	;
    break;}
case 2:
{
	// Command:  DDL_Statement
		yyval = yyvsp[0];
		pState->SetFirst (	yyval);
	;
    break;}
case 3:
{
	//	SQL_Statement:	SELECT AllDistinct TopRows SelectElementList FROM IdentList 
	//				WhereClause GroupByClause HavingClause OrderClause
		yyval = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (yyvsp[-8], "Distinct");
		pState->AddNameForObject (yyvsp[-7], "TopRows");
		pState->AddNameForObject (yyvsp[-6], "SelectClause");
		pState->AddNameForObject (yyvsp[-4], "FromClause");
		pState->AddNameForObject (yyvsp[-3], "WhereClause");
		pState->AddNameForObject (yyvsp[-2], "GroupByClause");
		pState->AddNameForObject (yyvsp[-1], "HavingClause");
		pState->AddNameForObject (yyvsp[0], "OrderClause");
	;
    break;}
case 4:
{
	//	SQL_Statement:	SELECT AllDistinct TopRows STAR FROM IdentList WhereClause 
	//				GroupByClause HavingClause OrderClause
		yyval = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (yyvsp[-8], "Distinct");
		pState->AddNameForObject (yyvsp[-7], "TopRows");
		yyvsp[-6] = pState->MakeNode (NodeType_Star, "*");
		pState->AddNameForObject (yyvsp[-6], "SelectClause");
		pState->AddNameForObject (yyvsp[-4], "FromClause");
		pState->AddNameForObject (yyvsp[-3], "WhereClause");
		pState->AddNameForObject (yyvsp[-2], "GroupByClause");
		pState->AddNameForObject (yyvsp[-1], "HavingClause");
		pState->AddNameForObject (yyvsp[0], "OrderClause");
	;
    break;}
case 5:
{
	//	SQL_Statement:	SQL_DELETE FROM Identifier WhereClause
		pState->AddNameForObject (yyvsp[-1], "NameIdent");
		pState->AddNameForObject (yyvsp[0], "WhereClause");
		yyval = pState->MakeNode (NodeType_Delete, "Delete");
	;
    break;}
case 6:
{
	//	SQL_Statement:	UPDATE Identifier SET UpdateList WhereClause
		pState->AddNameForObject (yyvsp[-3], "NameIdent");
		pState->AddNameForObject (yyvsp[-1], "UpdateList");
		pState->AddNameForObject (yyvsp[0], "WhereClause");
		yyval = pState->MakeNode (NodeType_Update, "Update");
	;
    break;}
case 7:
{
	//	SQL_Statement:	INSERT INTO Identifier InsertColSpec VALUES LEFTPAREN InsertValueList RIGHTPAREN
		pState->AddNameForObject (yyvsp[-5], "NameIdent");
		pState->AddNameForObject (yyvsp[-4], "InsertColSpec");
		pState->AddNameForObject (yyvsp[-1], "InsertValueList");
		yyval = pState->MakeNode (NodeType_Insert, "Insert");
	;
    break;}
case 8:
{
	//	SQL_Statement:	Identifier
	// ein einfacher Tabellenname ist äquivalent zu 'select * from tabelle'
		yyval = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (pState->MakeNode (NodeType_Star, "*"), "SelectClause");
		pState->AddNameForObject (yyvsp[0], "FromClause");
	;
    break;}
case 9:
{
	//	DDL_Statement: CREATE TABLE Identifier LEFTPAREN ColDataTypeList RIGHTPAREN
		pState->AddNameForObject (yyvsp[-3], "NameIdent");
		pState->AddNameForObject (yyvsp[-1], "ColDataTypeList");
		yyval = pState->MakeNode (NodeType_CreateTable, "create table");
	;
    break;}
case 10:
{
	//	DDL_Statement: DROP TABLE Identifier
		pState->AddNameForObject (yyvsp[0], "NameIdent");
		yyval = pState->MakeNode (NodeType_DropTable, "drop table");
	;
    break;}
case 11:
{
	//	AllDistinct:
		yyval = NULL;
	;
    break;}
case 12:
{
	//  AllDistinct:	ALL
		yyval = NULL;
	;
    break;}
case 13:
{
	//	AllDistinct:	DISTINCT
		yyval = pState->MakeNode (NodeType_Distinct, "Distinct");
	;
    break;}
case 14:
{
	// TopRows:
		yyval = NULL;
	;
    break;}
case 15:
{
	// TopRows: TOP Number
		yyval = pState->MakeNode (NodeType_TopRows, "TopRows");
		yyval->m_pLeftChild = yyvsp[0];
	;
    break;}
case 16:
{
	// TopRows: TOP Number PERCENT
		yyval = pState->MakeNode (NodeType_TopRowsPercent, "TopRows");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 17:
{
	//	SelectElementList: SelectExpressionAsName
		yyval = yyvsp[0];
	;
    break;}
case 18:
{
	//	SelectElementList: SelectElementList COMMA SelectExpressionAsName
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 19:
{
	//	SelectExpressionAsName: SelectExpression
		yyval = yyvsp[0];
	;
    break;}
case 20:
{
	//	SelectExpressionAsName: SelectExpression AS Identifier
		yyval = pState->MakeNode (NodeType_AsName, "As name");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 21:
{
	//	SelectExpressionAsName: SelectExpression Identifier
		yyval = pState->MakeNode (NodeType_AsName, "As name");
		yyval->m_pLeftChild = yyvsp[-1];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 22:
{
	//	InsertColSpec:	LEFTPAREN ColList RIGHTPAREN
		yyval = yyvsp[-1];
	;
    break;}
case 23:
{
	// InsertColSpec:
		yyval = NULL;
	;
    break;}
case 24:
{
	//	ColList: ColName
		yyval = yyvsp[0];
	;
    break;}
case 25:
{
	//	ColList: ColList COMMA ColName
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 26:
{ 
	// InsertValueList:  ConstantExpression
		yyval=yyvsp[0];
	;
    break;}
case 27:
{
	// InsertValueList:  InsertValueList COMMA ConstantExpression
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 28:
{
	//	WhereClause: /* Empty */
		//$$ = pState->MakeNode(NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 29:
{
	// WhereClause: WHERE WhereConditions
		//$$ = pState->MakeNode (NodeType_WhereCondition, "Where");
		//$$->m_pLeftChild = $2;
		yyval = yyvsp[0];
	;
    break;}
case 30:
{
	// ConstantExpression: Value
		yyval = yyvsp[0];
	;
    break;}
case 31:
{
	// ConstantExpression: ConstantExpression PLUS ConstantExpression
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 32:
{
	// ConstantExpression: ConstantExpression MINUS ConstantExpression
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 33:
{
	// ConstantExpression: ConstantExpression DIVIDE ConstantExpression
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 34:
{
	// ConstantExpression: ConstantExpression STAR ConstantExpression
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 35:
{
	// ConstantExpression: LEFTPAREN ConstantExpression RIGHTPAREN
		yyval = yyvsp[-1];
	;
    break;}
case 36:
{
	//	UpdateList: UpdateValue
		yyval = yyvsp[0];		
	;
    break;}
case 37:
{
	//	UpdateList: UpdateList COMMA UpdateValue
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 38:
{
	//	UpdateValue: ColName EQUALS ValueOrColNameExpression
		yyval = pState->MakeNode(NodeType_UpdateValue, "UpdateValue");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 39:
{
	//	WhereConditions: WherePredicate
		yyval = yyvsp[0];		
	;
    break;}
case 40:
{
	//	WhereConditions: WhereConditions OR WhereConditions
		yyval = pState->MakeNode (NodeType_Or, "Or");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 41:
{
	//	WhereConditions: WhereConditions OR WhereConditions
		yyval = pState->MakeNode (NodeType_And, "And");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 42:
{
	//	WhereConditions: NOT WhereConditions 
		yyval = pState->MakeNode (NodeType_Not, "Not");
		yyval->m_pLeftChild = yyvsp[0];
		yyval->m_pRightChild = NULL;
	;
    break;}
case 43:
{
	//	WhereConditions: LEFTPAREN WhereConditions RIGHTPAREN
		yyval = yyvsp[-1];
	;
    break;}
case 44:
{
	//	WherePredicate: ValueOrColNameExpression EQUALS ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_Equals, "Equals");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 45:
{
	//	WherePredicate: ValueOrColNameExpression NOT_EQUALS ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_NotEquals, "NotEquals");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 46:
{
	//	WherePredicate: ValueOrColNameExpression LESS ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_Less, "Less");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 47:
{
	//	WherePredicate: ValueOrColNameExpression MORE ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_More, "More");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 48:
{
	//	WherePredicate: ValueOrColNameExpression LESS_EQUALS ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_LessEquals, "LESS_EQUALS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 49:
{
	//	WherePredicate: ValueOrColNameExpression MORE_EQUALS ValueOrColNameExpression
		yyval = pState->MakeNode (NodeType_MoreEquals, "MORE_EQUALS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 50:
{
	//	WherePredicate:  ColName IS NOT SQL_NULL
		yyval = pState->MakeNode (NodeType_IsNot, " IS NOT");
		yyval->m_pLeftChild = yyvsp[-3];
		yyval->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	;
    break;}
case 51:
{
	//	WherePredicate: ColName IS SQL_NULL
		yyval = pState->MakeNode (NodeType_Is, " IS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	;
    break;}
case 52:
{
	//	WherePredicate: ColName LIKE String
		yyval = pState->MakeNode (NodeType_Like, "LIKE");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 53:
{ 
	//	ColName: Identifier DOT Identifier
		yyval = pState->MakeNode(NodeType_Dot, "dot");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 54:
{
	//	ColName: Identifier DOT STAR
	// #HK010514: Tabelle.* ist als SpaltenId erlaubt
		yyval = pState->MakeNode(NodeType_Dot, "dot");
		yyval->m_pLeftChild = yyvsp[-2];
		yyvsp[0] = pState->MakeNode (NodeType_Star, "*");
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 55:
{ 
	//	ColName: Identifier
		yyval = pState->MakeNode(NodeType_Dot, "dot");
		yyval->m_pLeftChild = NULL;
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 56:
{
	//	IdentList: IdentifierWithAlias
		yyval = yyvsp[0];	// pState->MakeNode(NodeType_Identifier, "id");
	;
    break;}
case 57:
{
	//	IdentList: IdentList COMMA IdentifierWithAlias
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 58:
{
	// IdentifierWithAlias:	Identifier
		yyval = yyvsp[0];
	;
    break;}
case 59:
{
	// IdentifierWithAlias:	Identifier AS Identifier
		yyvsp[-2]->m_pLeftChild = NULL;
		yyvsp[-2]->m_pRightChild = yyvsp[0];
		yyval = yyvsp[-2];
	;
    break;}
case 60:
{
	// IdentifierWithAlias:	Identifier Identifier
		yyvsp[-1]->m_pLeftChild = NULL;
		yyvsp[-1]->m_pRightChild = yyvsp[0];
		yyval = yyvsp[-1];
	;
    break;}
case 61:
{ 
	//	Identifier: IDENTIFIER
		yyval = pState->MakeNode(NodeType_Identifier, "id");
	;
    break;}
case 62:
{
	//	SelectExpression: SelectExpressionItem
		yyval = yyvsp[0];
	;
    break;}
case 63:
{
	//	SelectExpression: SelectExpression PLUS SelectExpression
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 64:
{
	//	SelectExpression: SelectExpression MINUS SelectExpression
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 65:
{
	//	SelectExpression: SelectExpression DIVIDE SelectExpression
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 66:
{
	//	SelectExpression: SelectExpression STAR SelectExpression
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 67:
{
	//	SelectExpression: SelectExpression RIGHTPAREN
		yyval = yyvsp[-1];
	;
    break;}
case 68:
{
	// SelectExpressionItem: ValueOrColName
		yyval = yyvsp[0];
	;
    break;}
case 69:
{
	// SelectExpressionItem: Aggregate
		yyval = yyvsp[0];
	;
    break;}
case 70:
{
	// SelectExpressionItem: Function
		yyval = yyvsp[0];
	;
    break;}
case 71:
{
	// ValueOrColName: Value
		yyval = yyvsp[0];
	;
    break;}
case 72:
{
	// ValueOrColName: ColName
		yyval = yyvsp[0];
	;
    break;}
case 73:
{
	// ValueOrColNameExpression: ValueOrColName
		yyval = yyvsp[0];
	;
    break;}
case 74:
{
	// ValueOrColNameExpression: Function
		yyval = yyvsp[0];
	;
    break;}
case 75:
{
	// ValueOrColNameExpression: ValueOrColNameExpression PLUS ValueOrColNameExpression
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 76:
{
	// ValueOrColNameExpression: ValueOrColNameExpression MINUS ValueOrColNameExpression
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 77:
{
	// ValueOrColNameExpression: ValueOrColNameExpression DIVIDE ValueOrColNameExpression
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 78:
{
	// ValueOrColNameExpression: ValueOrColNameExpression STAR ValueOrColNameExpression
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 79:
{
	// ValueOrColNameExpression: ValueOrColNameExpression RIGHTPAREN
		yyval = yyvsp[-1];
	;
    break;}
case 80:
{
	// GroupByClause: /* Empty */
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 81:
{
	// GroupByClause: GROUP BY ColName
		yyval = yyvsp[0];
	;
    break;}
case 82:
{
	// HavingClause: /* Empty */
		yyval = NULL;
	;
    break;}
case 83:
{
	// HavingClause: HAVING WhereConditions
		yyval = yyvsp[0];
	;
    break;}
case 84:
{
	// OrderClause: /* Empty */
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 85:
{
	// OrderClause: ORDER BY OrderColList
		yyval = yyvsp[0];
	;
    break;}
case 86:
{
	// OrderColList: OrderCol
		yyval = yyvsp[0];
	;
    break;}
case 87:
{
	// OrderColList: OrderColList COMMA OrderCol
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 88:
{
	// OrderCol: ColName
		yyval = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		yyval->m_pLeftChild = yyvsp[0];
	;
    break;}
case 89:
{
	// OrderCol: ColName ASC
		yyval = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 90:
{
	// OrderCol: ColName DESC
		yyval = pState->MakeNode (NodeType_OrderDESC, "OrderDESC");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 91:
{
	// Value: LiteralValue
		 yyval=yyvsp[0];
	;
    break;}
case 92:
{
	// Function: MathFunction
		yyval = yyvsp[0];
	;
    break;}
case 93:
{
	// Function: DateFunction
		yyval = yyvsp[0];
	;
    break;}
case 94:
{
	// GeometryFunction
		yyval = yyvsp[0];
	;
    break;}
case 95:
{
	// MathFunction: ABS LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		yyval->m_pLeftChild = yyvsp[-1];	
	;
    break;}
case 96:
{
	// MathFunction: ROUND LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		yyval->m_pLeftChild = yyvsp[-1];	
	;
    break;}
case 97:
{
	// DateFunction:	GETDATE LEFTPAREN RIGHTPAREN
		yyval = pState->MakeNode (NodeType_FunctionGetDate, "GETDATE");
	;
    break;}
case 98:
{
	// ASTEXT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionAsText, "ASTEXT");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 99:
{
	// ASBINARY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionAsBinary, "ASBINARY");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 100:
{
	// DIMENSION LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionDimension, "DIMENSION");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 101:
{
	// GEOMETRYTYPE LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionGeometryType, "GEOMETRYTYPE");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 102:
{
	// SRID LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionSRID, "SRID");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 103:
{
	// ISEMPTY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_GeometryFunctionIsEmpty, "ISEMPTY");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 104:
{
	// Aggregate: SUM LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateSum, "SUM");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 105:
{
	// Aggregate: AVG LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateAvg, "AVG SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 106:
{
	// Aggregate: MAX LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateMax, "MAX SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 107:
{
	// Aggregate: MIN LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateMin, "MIN SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 108:
{
	// Aggregate: COUNT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateCount, "COUNT COLNAME");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 109:
{
	// Aggregate: COUNT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		yyval = pState->MakeNode (NodeType_AggregateCount, "COUNT *");
		yyval->m_pLeftChild = pState->MakeNode (NodeType_Star, "*");;
	;
    break;}
case 110:
{
	// ColDataTypeList: Identifier DataType
		yyvsp[-1]->m_pLeftChild = yyvsp[0];
		yyval=yyvsp[-1];
	;
    break;}
case 111:
{
	// ColDataTypeList: ColDataTypeList COMMA Identifier DataType
		yyvsp[-1]->m_pLeftChild = yyvsp[0];
		yyvsp[-3]->AddLast (yyvsp[-1]);
		yyval = yyvsp[-3];
	;
    break;}
case 112:
{
	// DataType: CHAR_DATATYPE LEFTPAREN Number RIGHTPAREN 		
		yyval = pState->MakeNode(NodeType_CharDataType, "character_typ");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 113:
{
	// DataType: INTEGER_DATATYPE	
		yyval = pState->MakeNode(NodeType_IntegerDataType, "integer_typ");
	;
    break;}
case 114:
{
	// DataType: FLOAT_DATATYPE	
		yyval = pState->MakeNode(NodeType_FloatDataType, "float_typ");
	;
    break;}
case 115:
{
	// DataType: SMALLINT_DATATYPE	
		yyval = pState->MakeNode (NodeType_IntegerDataType, "integer_typ");
	;
    break;}
case 116:
{
	// DataType: TEXT_DATATYPE	
		yyval = pState->MakeNode (NodeType_SmallIntDataType, "text_type");
	;
    break;}
case 117:
{ 
	// LiteralValue:	Number 
		yyval = yyvsp[0]; 
	;
    break;}
case 118:
{ 
	// LiteralValue:	Float 
		yyval = yyvsp[0]; 
	;
    break;}
case 119:
{ 
	// LiteralValue:	String 
		yyval = yyvsp[0]; 
	;
    break;}
case 120:
{
	// Number: NUMBER_VALUE
		yyval = pState->MakeNode(NodeType_Integer_Value, "Number");
	;
    break;}
case 121:
{
	// Float: FLOAT_VALUE
		yyval = pState->MakeNode(NodeType_Float_Value, "Float");
	;
    break;}
case 122:
{
	// String: STRING_VALUE
		yyval = pState->MakeNode(NodeType_String_Value, "String");
	;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */


  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}


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
#define	ABS	306
#define	ROUND	307
#define	GETDATE	308
#define	MINUS	309
#define	PLUS	310
#define	LIKE	311
#define	DIVIDE	312
#define	AND	313
#define	OR	314
#define	NOT	315

			   

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



#define	YYFINAL		220
#define	YYFLAG		-32768
#define	YYNTBASE	61

#define YYTRANSLATE(x) ((unsigned)(x) <= 315 ? yytranslate[x] : 99)

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
    56,    57,    58,    59,    60
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,    14,    24,    29,    35,    44,    51,    55,
    56,    58,    60,    62,    66,    68,    72,    76,    77,    79,
    83,    85,    89,    90,    93,    95,    99,   103,   107,   111,
   115,   117,   121,   125,   127,   131,   135,   138,   142,   146,
   150,   154,   158,   162,   166,   171,   175,   179,   183,   185,
   187,   191,   193,   195,   199,   203,   207,   211,   215,   217,
   219,   221,   223,   225,   227,   229,   233,   237,   241,   245,
   249,   250,   254,   255,   258,   259,   263,   265,   269,   271,
   274,   277,   279,   281,   283,   288,   293,   297,   302,   307,
   312,   317,   322,   327,   330,   335,   340,   342,   344,   346,
   348,   350,   352,   354,   356
};

static const short yyrhs[] = {    62,
     0,    63,     0,    23,    64,    65,    12,    77,    70,    83,
    84,    85,     0,    23,    64,    24,    12,    77,    70,    83,
    84,    85,     0,    38,    12,    78,    70,     0,    39,    78,
    40,    72,    70,     0,    41,    42,    78,    67,    43,     4,
    69,     5,     0,    45,    46,    78,     4,    93,     5,     0,
    44,    46,    78,     0,     0,    35,     0,    26,     0,    66,
     0,    65,     6,    66,     0,    79,     0,    79,    13,    78,
     0,     4,    68,     5,     0,     0,    76,     0,    68,     6,
    76,     0,    71,     0,    69,     6,    71,     0,     0,    14,
    74,     0,    88,     0,    71,    55,    71,     0,    71,    54,
    71,     0,    71,    57,    71,     0,    71,    24,    71,     0,
     4,    71,     5,     0,    73,     0,    72,     6,    73,     0,
    76,    15,    82,     0,    75,     0,    74,    59,    74,     0,
    74,    58,    74,     0,    60,    74,     0,     4,    74,     5,
     0,    82,    15,    82,     0,    82,    22,    82,     0,    82,
    17,    82,     0,    82,    18,    82,     0,    82,    19,    82,
     0,    82,    20,    82,     0,    76,    21,    60,    11,     0,
    76,    21,    11,     0,    76,    56,    98,     0,    78,    16,
    78,     0,    78,     0,    78,     0,    77,     6,    78,     0,
     3,     0,    80,     0,    79,    55,    79,     0,    79,    54,
    79,     0,    79,    57,    79,     0,    79,    24,    79,     0,
     4,    79,     5,     0,    81,     0,    92,     0,    89,     0,
    88,     0,    76,     0,    81,     0,    89,     0,    82,    55,
    82,     0,    82,    54,    82,     0,    82,    57,    82,     0,
    82,    24,    82,     0,     4,    82,     5,     0,     0,    36,
    32,    76,     0,     0,    37,    74,     0,     0,    31,    32,
    86,     0,    87,     0,    86,     6,    87,     0,    76,     0,
    76,    33,     0,    76,    34,     0,    95,     0,    90,     0,
    91,     0,    51,     4,    82,     5,     0,    52,     4,    82,
     5,     0,    53,     4,     5,     0,    30,     4,    82,     5,
     0,    27,     4,    82,     5,     0,    28,     4,    82,     5,
     0,    29,     4,    82,     5,     0,    25,     4,    82,     5,
     0,    25,     4,    24,     5,     0,    78,    94,     0,    93,
     6,    78,    94,     0,    47,     4,    96,     5,     0,    49,
     0,    50,     0,    48,     0,    96,     0,    97,     0,    98,
     0,     9,     0,     8,     0,     7,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    48,    53,    60,    72,    84,    90,    97,   106,   112,   119,
   123,   127,   133,   137,   144,   148,   156,   160,   166,   170,
   179,   183,   192,   197,   205,   209,   215,   221,   227,   233,
   239,   243,   250,   258,   262,   268,   274,   280,   286,   292,
   298,   304,   310,   316,   322,   328,   334,   342,   348,   356,
   360,   367,   373,   377,   383,   389,   395,   401,   407,   411,
   415,   421,   425,   431,   435,   439,   445,   451,   457,   463,
   469,   474,   481,   485,   491,   496,   502,   506,   513,   518,
   523,   530,   546,   550,   556,   561,   568,   574,   579,   584,
   589,   594,   599,   608,   613,   621,   626,   630,   634,   640,
   641,   642,   645,   651,   656
};

static const char * const yytname[] = {   "$","error","$undefined.","IDENTIFIER",
"LEFTPAREN","RIGHTPAREN","COMMA","STRING_VALUE","FLOAT_VALUE","NUMBER_VALUE",
"DATE_VALUE","SQL_NULL","FROM","AS","WHERE","EQUALS","DOT","LESS","MORE","LESS_EQUALS",
"MORE_EQUALS","IS","NOT_EQUALS","SELECT","STAR","COUNT","DISTINCT","AVG","MAX",
"MIN","SUM","ORDER","BY","ASC","DESC","ALL","GROUP","HAVING","SQL_DELETE","UPDATE",
"SET","INSERT","INTO","VALUES","DROP","CREATE","TABLE","CHAR_DATATYPE","SMALLINT_DATATYPE",
"INTEGER_DATATYPE","FLOAT_DATATYPE","ABS","ROUND","GETDATE","MINUS","PLUS","LIKE",
"DIVIDE","AND","OR","NOT","Command","SQL_Statement","DDL_Statement","AllDistinct",
"SelectElementList","SelectExpressionAsName","InsertColSpec","ColList","InsertValueList",
"WhereClause","ConstantExpression","UpdateList","UpdateValue","WhereConditions",
"WherePredicate","ColName","IdentList","Identifier","SelectExpression","SelectExpressionItem",
"ValueOrColName","ValueOrColNameExpression","GroupByClause","HavingClause","OrderClause",
"OrderColList","OrderCol","Value","Function","MathFunction","DateFunction","Aggregate",
"ColDataTypeList","DataType","LiteralValue","Number","Float","String",""
};
#endif

static const short yyr1[] = {     0,
    61,    61,    62,    62,    62,    62,    62,    63,    63,    64,
    64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
    69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
    72,    72,    73,    74,    74,    74,    74,    74,    75,    75,
    75,    75,    75,    75,    75,    75,    75,    76,    76,    77,
    77,    78,    79,    79,    79,    79,    79,    79,    80,    80,
    80,    81,    81,    82,    82,    82,    82,    82,    82,    82,
    83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
    87,    88,    89,    89,    90,    90,    91,    92,    92,    92,
    92,    92,    92,    93,    93,    94,    94,    94,    94,    95,
    95,    95,    96,    97,    98
};

static const short yyr2[] = {     0,
     1,     1,     9,     9,     4,     5,     8,     6,     3,     0,
     1,     1,     1,     3,     1,     3,     3,     0,     1,     3,
     1,     3,     0,     2,     1,     3,     3,     3,     3,     3,
     1,     3,     3,     1,     3,     3,     2,     3,     3,     3,
     3,     3,     3,     3,     4,     3,     3,     3,     1,     1,
     3,     1,     1,     3,     3,     3,     3,     3,     1,     1,
     1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
     0,     3,     0,     2,     0,     3,     1,     3,     1,     2,
     2,     1,     1,     1,     4,     4,     3,     4,     4,     4,
     4,     4,     4,     2,     4,     4,     1,     1,     1,     1,
     1,     1,     1,     1,     1
};

static const short yydefact[] = {     0,
    10,     0,     0,     0,     0,     0,     1,     2,    12,    11,
     0,     0,    52,     0,     0,     0,     0,     0,   105,   104,
   103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    13,    63,    49,    15,    53,    59,    62,    61,    83,
    84,    60,    82,   100,   101,   102,    23,     0,    18,     9,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     5,    23,    31,     0,     0,     0,     0,    58,    23,    50,
     0,     0,    64,     0,    65,     0,     0,     0,     0,     0,
     0,    87,    14,    23,    48,    16,    57,    55,    54,    56,
     0,     0,    24,    34,    63,     0,     0,     6,     0,     0,
    19,     0,     0,     0,     0,    71,     0,    93,    92,     0,
     0,     0,     0,    89,    90,    91,    88,    85,    86,    71,
     0,     0,    37,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    32,    33,    17,     0,     0,     0,    99,
    97,    98,    94,     8,     0,    51,     0,    73,    70,    69,
    67,    66,    68,    73,    38,    36,    35,    46,     0,    47,
    39,    41,    42,    43,    44,    40,    20,     0,     0,    21,
    25,     0,     0,     0,     0,    75,    75,    45,     0,     7,
     0,     0,     0,     0,     0,     0,    95,    72,    74,     0,
     4,     3,    30,    22,    29,    27,    26,    28,    96,     0,
    79,    76,    77,    80,    81,     0,    78,     0,     0,     0
};

static const short yydefgoto[] = {   218,
     7,     8,    11,    31,    32,    76,   110,   179,    71,   180,
    72,    73,   103,   104,    33,    79,    34,    35,    36,    83,
   106,   158,   186,   201,   212,   213,    38,    85,    40,    41,
    42,   114,   153,    43,    44,    45,    46
};

static const short yypact[] = {   296,
    59,    16,     6,   -16,    19,    22,-32768,-32768,-32768,-32768,
   246,     6,-32768,    30,     6,     6,     6,   253,-32768,-32768,
-32768,    86,    42,    97,   114,   142,   144,   152,   153,   157,
    90,-32768,-32768,   158,    34,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   117,     6,   175,-32768,
   183,    95,     6,    26,   260,   260,   260,   260,   260,   260,
   170,   253,     6,     6,     6,   253,   253,   253,   253,   107,
-32768,   103,-32768,   173,     6,   146,     6,-32768,   121,-32768,
   260,   187,-32768,   115,-32768,   127,   139,   149,   159,   166,
   171,-32768,-32768,   121,-32768,-32768,-32768,     0,     0,-32768,
   107,   107,   -10,-32768,    10,   269,     6,-32768,   260,   102,
-32768,   203,   -42,   124,     6,   172,   181,-32768,-32768,   260,
   260,   260,   260,-32768,-32768,-32768,-32768,-32768,-32768,   172,
    -3,   123,-32768,   107,   107,    -8,   202,   260,   260,   260,
   260,   260,   260,-32768,   261,-32768,     6,   223,   207,-32768,
-32768,-32768,-32768,-32768,     6,-32768,   180,   178,-32768,-32768,
    12,    12,-32768,   178,-32768,-32768,-32768,-32768,   206,-32768,
   261,   261,   261,   261,   261,   261,-32768,   223,   128,   276,
-32768,   209,   -42,     6,   107,   188,   188,-32768,   186,-32768,
   223,   223,   223,   223,   223,   217,-32768,-32768,   -10,   192,
-32768,-32768,-32768,   276,-32768,    36,    36,-32768,-32768,     6,
   132,   227,-32768,-32768,-32768,     6,-32768,   229,   234,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,   177,-32768,-32768,-32768,    18,  -174,
-32768,   130,   -90,-32768,   -48,   189,    -2,   179,-32768,     5,
   -17,   112,    80,    64,-32768,    43,     7,    14,-32768,-32768,
-32768,-32768,    75,-32768,    83,-32768,   129
};


#define	YYLAST		341


static const short yytable[] = {    74,
    14,   165,   168,   189,   149,   150,   151,   152,    13,    47,
   131,   133,    49,    50,    51,    37,   204,   205,   206,   207,
   208,   105,    37,    66,    39,    15,   111,    12,    13,    81,
   136,    39,    19,    20,    21,   120,    84,    86,    87,    88,
    89,    90,    91,   166,   167,    54,    65,   134,   135,    82,
    80,   169,   105,   105,   134,   135,    69,    66,    74,   192,
    80,    95,    96,   117,    16,   137,    37,    17,   123,    48,
    37,    37,    37,    37,   113,    39,    28,    29,    30,    39,
    39,    39,    39,   132,     9,   105,   105,    67,    68,   108,
    69,   145,   195,    10,   199,    62,   116,    53,   177,    78,
    55,    63,   160,   161,   162,   163,   146,   147,   107,    13,
   101,   130,   156,    19,    20,    21,    70,    56,    66,   119,
   171,   172,   173,   174,   175,   176,   115,   159,   154,   155,
    70,   124,   190,   191,    70,   198,   105,   138,   120,   139,
   140,   141,   142,   125,   143,    57,   120,    58,    67,    68,
   120,    69,   183,   126,   181,    59,    60,    28,    29,    30,
    61,   211,   120,   127,   214,   215,   102,   211,   121,   122,
   128,   123,   120,    64,    92,   129,   121,   122,    75,   123,
   121,   122,   120,   123,   181,   159,    77,   109,   112,   120,
   203,   118,   121,   122,   120,   123,    52,   181,   181,   181,
   181,   181,   121,   122,   120,   123,   148,   157,    19,   192,
   182,   184,   121,   122,   185,   123,   188,    21,   200,   121,
   122,   209,   123,   210,   121,   122,   178,   123,   219,    19,
    20,    21,   216,   220,   121,   122,   144,   123,    93,   193,
   194,   164,   195,   187,    97,    98,    99,   100,    13,    18,
   202,    94,    19,    20,    21,    13,    18,   197,   217,    19,
    20,    21,    13,    81,   196,   170,    19,    20,    21,    22,
    23,     0,    24,    25,    26,    27,     0,    23,     0,    24,
    25,    26,    27,   138,   120,   139,   140,   141,   142,     0,
   143,     0,   120,     0,     0,     0,    28,    29,    30,   192,
     0,     0,     0,    28,    29,    30,     0,     0,     0,     0,
    28,    29,    30,     0,   121,   122,     0,   123,     1,     0,
     0,     0,   121,   122,     0,   123,     0,     0,     0,   193,
   194,     0,   195,     2,     3,     0,     4,     0,     0,     5,
     6
};

static const short yycheck[] = {    48,
     3,     5,    11,   178,    47,    48,    49,    50,     3,    12,
   101,   102,    15,    16,    17,    11,   191,   192,   193,   194,
   195,    70,    18,    24,    11,    42,    75,    12,     3,     4,
    21,    18,     7,     8,     9,    24,    54,    55,    56,    57,
    58,    59,    60,   134,   135,     4,    13,    58,    59,    24,
    53,    60,   101,   102,    58,    59,    57,    24,   107,    24,
    63,    64,    65,    81,    46,    56,    62,    46,    57,    40,
    66,    67,    68,    69,    77,    62,    51,    52,    53,    66,
    67,    68,    69,   101,    26,   134,   135,    54,    55,    72,
    57,   109,    57,    35,   185,     6,    79,    12,   147,     5,
     4,    12,   120,   121,   122,   123,     5,     6,     6,     3,
     4,    94,   115,     7,     8,     9,    14,     4,    24,     5,
   138,   139,   140,   141,   142,   143,     6,     5,     5,     6,
    14,     5,     5,     6,    14,   184,   185,    15,    24,    17,
    18,    19,    20,     5,    22,     4,    24,     4,    54,    55,
    24,    57,   155,     5,   148,     4,     4,    51,    52,    53,
     4,   210,    24,     5,    33,    34,    60,   216,    54,    55,
     5,    57,    24,    16,     5,     5,    54,    55,     4,    57,
    54,    55,    24,    57,   178,     5,     4,    15,    43,    24,
     5,     5,    54,    55,    24,    57,    18,   191,   192,   193,
   194,   195,    54,    55,    24,    57,     4,    36,     7,    24,
     4,    32,    54,    55,    37,    57,    11,     9,    31,    54,
    55,     5,    57,    32,    54,    55,     4,    57,     0,     7,
     8,     9,     6,     0,    54,    55,   107,    57,    62,    54,
    55,   130,    57,   164,    66,    67,    68,    69,     3,     4,
   187,    63,     7,     8,     9,     3,     4,   183,   216,     7,
     8,     9,     3,     4,   182,   137,     7,     8,     9,    24,
    25,    -1,    27,    28,    29,    30,    -1,    25,    -1,    27,
    28,    29,    30,    15,    24,    17,    18,    19,    20,    -1,
    22,    -1,    24,    -1,    -1,    -1,    51,    52,    53,    24,
    -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,
    51,    52,    53,    -1,    54,    55,    -1,    57,    23,    -1,
    -1,    -1,    54,    55,    -1,    57,    -1,    -1,    -1,    54,
    55,    -1,    57,    38,    39,    -1,    41,    -1,    -1,    44,
    45
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

#define yyerror(s) pState->SetError(s)

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
		yyval = yyvsp[0];
		pState->SetFirst (	yyval);
	;
    break;}
case 2:
{
		yyval = yyvsp[0];
		pState->SetFirst (	yyval);
	;
    break;}
case 3:
{
		yyval = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (yyvsp[-7], "Distinct");
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
		yyval = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (yyvsp[-7], "Distinct");
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
		pState->AddNameForObject (yyvsp[-1], "NameIdent");
		pState->AddNameForObject (yyvsp[0], "WhereClause");
		yyval = pState->MakeNode (NodeType_Delete, "Delete");
	;
    break;}
case 6:
{
		pState->AddNameForObject (yyvsp[-3], "NameIdent");
		pState->AddNameForObject (yyvsp[-1], "UpdateList");
		pState->AddNameForObject (yyvsp[0], "WhereClause");
		yyval = pState->MakeNode (NodeType_Update, "Update");
	;
    break;}
case 7:
{
		pState->AddNameForObject (yyvsp[-5], "NameIdent");
		pState->AddNameForObject (yyvsp[-4], "InsertColSpec");
		pState->AddNameForObject (yyvsp[-1], "InsertValueList");
		yyval = pState->MakeNode (NodeType_Insert, "Insert");
	;
    break;}
case 8:
{
		pState->AddNameForObject (yyvsp[-3], "NameIdent");
		pState->AddNameForObject (yyvsp[-1], "ColDataTypeList");
		yyval = pState->MakeNode (NodeType_CreateTable, "create table");
	;
    break;}
case 9:
{
		pState->AddNameForObject (yyvsp[0], "NameIdent");
		yyval = pState->MakeNode (NodeType_DropTable, "drop table");
	;
    break;}
case 10:
{
		yyval = NULL;
	;
    break;}
case 11:
{
		yyval = NULL;
	;
    break;}
case 12:
{
		yyval = pState->MakeNode (NodeType_Distinct, "Distinct");
	;
    break;}
case 13:
{
		yyval = yyvsp[0];
	;
    break;}
case 14:
{
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 15:
{
		yyval = yyvsp[0];
	;
    break;}
case 16:
{
		yyval = pState->MakeNode (NodeType_AsName, "As name");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 17:
{
		yyval = yyvsp[-1];
	;
    break;}
case 18:
{
		yyval =NULL;
	;
    break;}
case 19:
{
		yyval = yyvsp[0];
	;
    break;}
case 20:
{
					yyvsp[-2]->AddLast (yyvsp[0]);
					yyval = yyvsp[-2];
	;
    break;}
case 21:
{ 
		yyval=yyvsp[0];
	;
    break;}
case 22:
{
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 23:
{
		//$$ = pState->MakeNode(NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 24:
{
		//$$ = pState->MakeNode (NodeType_WhereCondition, "Where");
		//$$->m_pLeftChild = $2;
		yyval = yyvsp[0];
	;
    break;}
case 25:
{
		yyval = yyvsp[0];
	;
    break;}
case 26:
{
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 27:
{
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 28:
{
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 29:
{
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 30:
{
		yyval = yyvsp[-1];
	;
    break;}
case 31:
{
		yyval = yyvsp[0];		
	;
    break;}
case 32:
{
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 33:
{
		yyval = pState->MakeNode(NodeType_UpdateValue, "UpdateValue");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 34:
{
		yyval = yyvsp[0];		
	;
    break;}
case 35:
{
		yyval = pState->MakeNode (NodeType_Or, "Or");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 36:
{
		yyval = pState->MakeNode (NodeType_And, "And");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 37:
{
		yyval = pState->MakeNode (NodeType_Not, "Not");
		yyval->m_pLeftChild = yyvsp[-1];
		yyval->m_pRightChild = NULL;
	;
    break;}
case 38:
{
		yyval = yyvsp[-1];
	;
    break;}
case 39:
{
		yyval = pState->MakeNode (NodeType_Equals, "Equals");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 40:
{
		yyval = pState->MakeNode (NodeType_NotEquals, "NotEquals");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 41:
{
		yyval = pState->MakeNode (NodeType_Less, "Less");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 42:
{
		yyval = pState->MakeNode (NodeType_More, "More");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 43:
{
		yyval = pState->MakeNode (NodeType_LessEquals, "LESS_EQUALS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 44:
{
		yyval = pState->MakeNode (NodeType_MoreEquals, "MORE_EQUALS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 45:
{
		yyval = pState->MakeNode (NodeType_IsNot, " IS NOT");
		yyval->m_pLeftChild = yyvsp[-3];
		yyval->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	;
    break;}
case 46:
{
		yyval = pState->MakeNode (NodeType_Is, " IS");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	;
    break;}
case 47:
{
		yyval = pState->MakeNode (NodeType_Like, "LIKE");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 48:
{ 
		yyval = pState->MakeNode(NodeType_Dot, "dot");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 49:
{ 
		yyval = pState->MakeNode(NodeType_Dot, "dot");
		yyval->m_pLeftChild = NULL;
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 50:
{
		yyval = pState->MakeNode(NodeType_Identifier, "id");
	;
    break;}
case 51:
{
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 52:
{ 
		yyval = pState->MakeNode(NodeType_Identifier, "id");
	;
    break;}
case 53:
{
		yyval = yyvsp[0];
	;
    break;}
case 54:
{
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 55:
{
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 56:
{
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 57:
{
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 58:
{
		yyval = yyvsp[-1];
	;
    break;}
case 59:
{
		yyval = yyvsp[0];
	;
    break;}
case 60:
{
		yyval = yyvsp[0];
	;
    break;}
case 61:
{
		yyval = yyvsp[0];
	;
    break;}
case 62:
{
		yyval = yyvsp[0];
	;
    break;}
case 63:
{
		yyval = yyvsp[0];
	;
    break;}
case 64:
{
		yyval = yyvsp[0];
	;
    break;}
case 65:
{
		yyval = yyvsp[0];
	;
    break;}
case 66:
{
		yyval = pState->MakeNode(NodeType_ExpressionAdd, "+");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 67:
{
		yyval = pState->MakeNode(NodeType_ExpressionMinus, "-");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 68:
{
		yyval = pState->MakeNode(NodeType_ExpressionDivide, "/");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 69:
{
		yyval = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		yyval->m_pLeftChild = yyvsp[-2];
		yyval->m_pRightChild = yyvsp[0];
	;
    break;}
case 70:
{
		yyval = yyvsp[-1];
	;
    break;}
case 71:
{
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 72:
{
	
		yyval = yyvsp[0];
	;
    break;}
case 73:
{
		yyval = NULL;
	;
    break;}
case 74:
{
		yyval = yyvsp[0];
	;
    break;}
case 75:
{
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		yyval = NULL;
	;
    break;}
case 76:
{
		yyval = yyvsp[0];
	;
    break;}
case 77:
{
		yyval = yyvsp[0];
	;
    break;}
case 78:
{
		yyvsp[-2]->AddLast (yyvsp[0]);
		yyval = yyvsp[-2];
	;
    break;}
case 79:
{
		yyval = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		yyval->m_pLeftChild = yyvsp[0];
	;
    break;}
case 80:
{
		yyval = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 81:
{
		yyval = pState->MakeNode (NodeType_OrderDESC, "OrderDESC");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 82:
{
		 yyval=yyvsp[0];
	;
    break;}
case 83:
{
		yyval=yyvsp[0];
	;
    break;}
case 84:
{
		yyval=yyvsp[0];
	;
    break;}
case 85:
{
		yyval = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		yyval->m_pLeftChild = yyvsp[-1];	
	;
    break;}
case 86:
{
		yyval = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		yyval->m_pLeftChild = yyvsp[-1];	
	;
    break;}
case 87:
{
		yyval = pState->MakeNode (NodeType_FunctionGetDate, "GETDATE");
	;
    break;}
case 88:
{
		yyval = pState->MakeNode (NodeType_AggregateSum, "SUM");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 89:
{
		yyval = pState->MakeNode (NodeType_AggregateAvg, "AVG SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 90:
{
		yyval = pState->MakeNode (NodeType_AggregateMax, "MAX SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 91:
{
		yyval = pState->MakeNode (NodeType_AggregateMin, "MIN SUBEXPR");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 92:
{
		yyval = pState->MakeNode (NodeType_AggregateCount, "COUNT COLNAME");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 93:
{
		yyval = pState->MakeNode (NodeType_AggregateCount, "COUNT *");
		yyval->m_pLeftChild = pState->MakeNode (NodeType_Star, "*");;
	;
    break;}
case 94:
{
		yyvsp[-1]->m_pLeftChild = yyvsp[0];
		yyval=yyvsp[-1];
	;
    break;}
case 95:
{
		yyvsp[-1]->m_pLeftChild = yyvsp[0];
		yyvsp[-3]->AddLast (yyvsp[-1]);
		yyval = yyvsp[-3];
	;
    break;}
case 96:
{
		yyval = pState->MakeNode(NodeType_CharDataType, "character_typ");
		yyval->m_pLeftChild = yyvsp[-1];
	;
    break;}
case 97:
{
		yyval = pState->MakeNode(NodeType_IntegerDataType, "interger_typ");
	;
    break;}
case 98:
{
		yyval = pState->MakeNode(NodeType_FloatDataType, "float_typ");
	;
    break;}
case 99:
{
		yyval = pState->MakeNode (NodeType_SmallIntDataType, "smallint_type");
	;
    break;}
case 100:
{ yyval = yyvsp[0]; ;
    break;}
case 101:
{ yyval = yyvsp[0]; ;
    break;}
case 102:
{ yyval = yyvsp[0]; ;
    break;}
case 103:
{
		yyval = pState->MakeNode(NodeType_Integer_Value, "Number");
	;
    break;}
case 104:
{
		yyval = pState->MakeNode(NodeType_Float_Value, "Float");
	;
    break;}
case 105:
{
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

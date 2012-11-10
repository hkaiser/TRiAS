
/*  A Bison parser, made from cmdline_gram.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	ID	258
#define	STRCONST	259
#define	INTCONST	260
#define	IOPARAM	261
#define	FLOATCONST	262
#define	CREATE	263
#define	INSERT	264
#define	OPEN	265
#define	CLOSE	266
#define	QUIT	267
#define	SELECT	268
#define	DELETE	269
#define	NL	270
#define	ERROR	271
#define	CHECK	272
#define	SPLIT	273
#define	HELP	274
#define	DUMP	275
#define	ONLY	276
#define	SET	277
#define	STRUCT	278
#define	WRITE	279
#define	ECHO_TOKEN	280
#define	EVALSPLIT	281
#define	EVALPENALTY	282
#define	LOADFILE	283
#define	PREDINFO	284
#define	CREATEANL	285
#define	OPENANL	286
#define	CLOSEANL	287
#define	WKLDSTATS	288
#define	SPLITSTATS	289
#define	PENALTYSTATS	290
#define	ANLINFO	291

#line 5 "cmdline_gram.y"

#include <iostream.h>

#include "gist_compat.h"	// for malloc
#include "gist_defs.h"
#include "cmdline.h"
#define YYDEBUG 1

void cmdPrompt();
int yyerror(char *msg);
int yylex();

#line 18 "cmdline_gram.y"
typedef union {
    char *string;
    shpid_t pgno;
    int number;
    float flt;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		100
#define	YYFLAG		-32768
#define	YYNTBASE	37

#define YYTRANSLATE(x) ((unsigned)(x) <= 291 ? yytranslate[x] : 43)

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
    36
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    16,    22,    26,    30,    34,    41,
    47,    52,    55,    60,    65,    70,    76,    84,    88,    92,
    97,   101,   107,   111,   117,   120,   123,   125,   126,   128,
   129,   131,   132,   134,   135
};

static const short yyrhs[] = {    -1,
    37,    38,     0,     8,     3,     3,    15,     0,     8,     3,
     3,     3,     7,    15,     0,    24,    28,     3,     3,    15,
     0,    10,     3,    15,     0,    11,     3,    15,     0,    17,
     3,    15,     0,    13,     3,    41,    42,     4,    15,     0,
     9,     3,     4,     4,    15,     0,    14,     3,     4,    15,
     0,    12,    15,     0,    20,     3,    39,    15,     0,    18,
     3,     5,    15,     0,    22,    25,     5,    15,     0,    22,
    23,     3,     5,    15,     0,    30,     3,     3,     3,     5,
     7,    15,     0,    31,     3,    15,     0,    32,     3,    15,
     0,    34,     3,    40,    15,     0,    33,     3,    15,     0,
    35,     3,     3,    40,    15,     0,    36,     3,    15,     0,
    29,     3,     5,     5,    15,     0,    19,    15,     0,     1,
    15,     0,    15,     0,     0,     5,     0,     0,     3,     0,
     0,     5,     0,     0,     6,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    46,    47,    54,    61,    69,    76,    82,    88,    94,   101,
   109,   116,   121,   127,   133,   138,   144,   152,   158,   164,
   171,   177,   185,   191,   197,   202,   207,   211,   212,   216,
   217,   221,   222,   226,   227
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ID","STRCONST",
"INTCONST","IOPARAM","FLOATCONST","CREATE","INSERT","OPEN","CLOSE","QUIT","SELECT",
"DELETE","NL","ERROR","CHECK","SPLIT","HELP","DUMP","ONLY","SET","STRUCT","WRITE",
"ECHO_TOKEN","EVALSPLIT","EVALPENALTY","LOADFILE","PREDINFO","CREATEANL","OPENANL",
"CLOSEANL","WKLDSTATS","SPLITSTATS","PENALTYSTATS","ANLINFO","commands","command",
"dump_page","opt_id","opt_k","opt_ioparam", NULL
};
#endif

static const short yyr1[] = {     0,
    37,    37,    38,    38,    38,    38,    38,    38,    38,    38,
    38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
    38,    38,    38,    38,    38,    38,    38,    39,    39,    40,
    40,    41,    41,    42,    42
};

static const short yyr2[] = {     0,
     0,     2,     4,     6,     5,     3,     3,     3,     6,     5,
     4,     2,     4,     4,     4,     5,     7,     3,     3,     4,
     3,     5,     3,     5,     2,     2,     1,     0,     1,     0,
     1,     0,     1,     0,     1
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     2,    26,     0,     0,     0,     0,
    12,    32,     0,     0,     0,    25,    28,     0,     0,     0,
     0,     0,     0,     0,     0,    30,     0,     0,     0,     0,
     6,     7,    33,    34,     0,     8,     0,    29,     0,     0,
     0,     0,     0,     0,    18,    19,    21,    31,     0,    30,
    23,     0,     3,     0,    35,     0,    11,    14,    13,     0,
    15,     0,     0,     0,    20,     0,     0,    10,     0,    16,
     5,    24,     0,    22,     4,     9,     0,    17,     0,     0
};

static const short yydefgoto[] = {     1,
    25,    59,    69,    54,    76
};

static const short yypact[] = {-32768,
     0,   -13,     3,     4,    18,    20,    10,    23,    24,-32768,
    25,    34,    26,    35,   -20,    11,    37,    39,    40,    41,
    42,    43,    44,    45,-32768,-32768,    46,    47,    38,    48,
-32768,    49,    51,    50,    52,-32768,    53,    56,    55,    58,
    57,    61,    54,    59,    60,    63,    64,    62,     1,    66,
-32768,-32768,-32768,    65,    67,-32768,    68,-32768,    69,    71,
    70,    75,    74,    77,-32768,-32768,-32768,-32768,    72,    63,
-32768,    79,-32768,    73,-32768,    85,-32768,-32768,-32768,    76,
-32768,    78,    80,    87,-32768,    81,    82,-32768,    83,-32768,
-32768,-32768,    92,-32768,-32768,-32768,    86,-32768,    90,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   -18,-32768,-32768
};


#define	YYLAST		101


static const short yytable[] = {    99,
     2,    26,    38,    72,    39,    27,    28,     3,     4,     5,
     6,     7,     8,     9,    10,    73,    11,    12,    13,    14,
    29,    15,    30,    16,    31,    32,    33,    34,    17,    18,
    19,    20,    21,    22,    23,    24,    35,    37,    40,    41,
    36,    42,    43,    44,    45,    46,    47,    48,    49,     0,
    50,    86,    51,    53,    55,     0,    57,    58,    60,    61,
    62,    63,    52,    64,    56,    68,    70,     0,    65,    74,
    75,     0,     0,    66,    67,    80,    71,    82,    83,    84,
     0,    77,    78,    79,    81,    87,    85,    88,    89,   100,
    90,    93,    91,     0,    92,    94,    95,    96,    97,     0,
    98
};

static const short yycheck[] = {     0,
     1,    15,    23,     3,    25,     3,     3,     8,     9,    10,
    11,    12,    13,    14,    15,    15,    17,    18,    19,    20,
     3,    22,     3,    24,    15,     3,     3,     3,    29,    30,
    31,    32,    33,    34,    35,    36,     3,     3,    28,     3,
    15,     3,     3,     3,     3,     3,     3,     3,     3,    -1,
     4,    70,    15,     5,     4,    -1,     5,     5,     3,     5,
     3,     5,    15,     3,    15,     3,     3,    -1,    15,     4,
     6,    -1,    -1,    15,    15,     5,    15,     3,     5,     3,
    -1,    15,    15,    15,    15,     7,    15,    15,     4,     0,
    15,     5,    15,    -1,    15,    15,    15,    15,     7,    -1,
    15
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/sww/share/lib/bison-1.25/bison.simple"

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
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
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
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/sww/share/lib/bison-1.25/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
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
  YYSTYPE yylval;
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
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
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

case 2:
#line 48 "cmdline_gram.y"
{
        cmdPrompt();
    ;
    break;}
case 3:
#line 56 "cmdline_gram.y"
{
	cmdCreate(yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 4:
#line 63 "cmdline_gram.y"
{
	cmdLoad(yyvsp[-4].string, yyvsp[-3].string, yyvsp[-2].string, yyvsp[-1].flt);
	if (yyvsp[-4].string) delete [] yyvsp[-4].string;
	if (yyvsp[-3].string) delete [] yyvsp[-3].string;
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
    ;
    break;}
case 5:
#line 71 "cmdline_gram.y"
{
        cmdWriteLoadfile(yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 6:
#line 78 "cmdline_gram.y"
{
        cmdOpen(yyvsp[-1].string);
        if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 7:
#line 84 "cmdline_gram.y"
{
        cmdClose(yyvsp[-1].string);
        if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 8:
#line 90 "cmdline_gram.y"
{
        cmdCheck(yyvsp[-1].string);
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 9:
#line 96 "cmdline_gram.y"
{
	cmdSelect(yyvsp[-4].string, yyvsp[-1].string, yyvsp[-3].number, yyvsp[-2].number);
	if (yyvsp[-4].string) delete [] yyvsp[-4].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 10:
#line 103 "cmdline_gram.y"
{
	cmdInsert(yyvsp[-3].string, yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-3].string) delete [] yyvsp[-3].string;
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 11:
#line 111 "cmdline_gram.y"
{
	cmdDelete(yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 12:
#line 118 "cmdline_gram.y"
{
        cmdQuit();
    ;
    break;}
case 13:
#line 123 "cmdline_gram.y"
{
        cmdDump(yyvsp[-2].string, yyvsp[-1].pgno);
        if (yyvsp[-2].string) delete [] yyvsp[-2].string;
    ;
    break;}
case 14:
#line 129 "cmdline_gram.y"
{
        cmdSplit(yyvsp[-2].string, yyvsp[-1].number);
        if (yyvsp[-2].string) delete [] yyvsp[-2].string;
    ;
    break;}
case 15:
#line 135 "cmdline_gram.y"
{
        cmdSetEcho(yyvsp[-1].number);
    ;
    break;}
case 16:
#line 140 "cmdline_gram.y"
{
	cmdSetStruct(yyvsp[-2].string, yyvsp[-1].number);
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
    ;
    break;}
case 17:
#line 146 "cmdline_gram.y"
{
        cmdCreateAnl(yyvsp[-5].string, yyvsp[-4].string, yyvsp[-3].string, yyvsp[-2].number, yyvsp[-1].flt);
	if (yyvsp[-5].string) delete [] yyvsp[-5].string;
	if (yyvsp[-4].string) delete [] yyvsp[-4].string;
	if (yyvsp[-3].string) delete [] yyvsp[-3].string;
    ;
    break;}
case 18:
#line 154 "cmdline_gram.y"
{
        cmdOpenAnl(yyvsp[-1].string);
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 19:
#line 160 "cmdline_gram.y"
{
        cmdCloseAnl(yyvsp[-1].string);
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 20:
#line 166 "cmdline_gram.y"
{
        cmdSplitStats(yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 21:
#line 173 "cmdline_gram.y"
{
        cmdWkldStats(yyvsp[-1].string);
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 22:
#line 179 "cmdline_gram.y"
{
        cmdPenaltyStats(yyvsp[-3].string, yyvsp[-2].string, yyvsp[-1].string);
	if (yyvsp[-3].string) delete [] yyvsp[-3].string;
	if (yyvsp[-2].string) delete [] yyvsp[-2].string;
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 23:
#line 187 "cmdline_gram.y"
{
        cmdAnlInfo(yyvsp[-1].string);
	if (yyvsp[-1].string) delete [] yyvsp[-1].string;
    ;
    break;}
case 24:
#line 193 "cmdline_gram.y"
{
        cmdPredInfo(yyvsp[-3].string, yyvsp[-2].number, yyvsp[-1].number);
	if (yyvsp[-3].string) delete [] yyvsp[-3].string;
    ;
    break;}
case 25:
#line 199 "cmdline_gram.y"
{
	cmdHelp();
    ;
    break;}
case 26:
#line 203 "cmdline_gram.y"
{
        yyclearin;
	yyerrok;
    ;
    break;}
case 28:
#line 211 "cmdline_gram.y"
{ yyval.pgno = (shpid_t) 0; ;
    break;}
case 29:
#line 212 "cmdline_gram.y"
{ yyval.pgno = (shpid_t) yyvsp[0].number; ;
    break;}
case 30:
#line 216 "cmdline_gram.y"
{ yyval.string = NULL; ;
    break;}
case 31:
#line 217 "cmdline_gram.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 32:
#line 221 "cmdline_gram.y"
{ yyval.number = 0; ;
    break;}
case 33:
#line 222 "cmdline_gram.y"
{ yyval.number = yyvsp[0].number; ;
    break;}
case 34:
#line 226 "cmdline_gram.y"
{ yyval.number = 0; ;
    break;}
case 35:
#line 227 "cmdline_gram.y"
{ yyval.number = yyvsp[0].number; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/sww/share/lib/bison-1.25/bison.simple"

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
#line 230 "cmdline_gram.y"


int yyerror(char *errmsg)
{
    extern char *yytext;

    cerr << "Parser error: " << errmsg << "!\n";

    return 1;
}

extern "C" int yywrap()
{
	return 0;
}


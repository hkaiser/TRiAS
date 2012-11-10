/*

			       D I E S E L

       Dumb Interpretively Evaluated String Expression Language

    This "Dumb Interpretively Executed String Expression Language" is  the
    kernel  of	a  macro  language  you can customise by adding C code and
    embedding it into your program.

    It is short, written in portable C, and is readily integrated into any
    program.   It  is  useful  primarily  to  programs	which  need a very
    rudimentary macro expansion facility without the complexity of a  full
    language such as Lisp or FORTH.

    DIESEL  copies  its  input	directly  to  the  output  until  a  macro
    character, "$" or quoted string is encountered.  Quoted strings may be
    used  to  suppress	evaluation  of sequences of characters which would
    otherwise be interpreted as macros.  Quote marks may  be  included	in
    quoted strings by two adjacent quote marks.  For example:

	"$(if,1,True,False)="""$(if,1,True,False)""""

    Status  retrieval,	computation,  and  display are performed by DIESEL
    functions.	The available  functions  are  as  follows.   User-defined
    functions  are  not  implemented;  what  you  see  is  all you've got.
    Naturally, if  you	embed  DIESEL  in  your  application,  you'll  add
    functions  that  provide access to information and actions within your
    own program.  DIESEL's arithmetic  functions  accept  either  floating
    point  or  integer arguments, and perform all calculations in floating
    point.

    DIESEL String Functions
    -----------------------

    $(+,<val1>,<val2>,...<valn>)
	The  sum  of  the  numbers <val1>, <val2>, ...<valn> is returned.

    $(-,<val1>,<val2>,...<valn>)
	The  result  of subtracting the numbers <val2> through <valn> from
	<val1> is returned.

    $(*,<val1>,<val2>,...<valn>)
	The result of multiplying the numbers  <val1>,<val2>,...<valn>	is
	returned.

    $(/,<val1>,<val2>,...<valn>)
	The  result of dividing the number <val1> by <val2>,...  <valn> is
	returned.

    $(=,<val1>,<val2>)
	If the	numbers  <val1>  and  <val2>  are  equal  1  is  returned,
	otherwise 0 is returned.

    $(<,<val1>,<val2>)
	If  the number <val1> is less than <val2> 1 is returned, otherwise
	0 is returned.

    $(>,<val1>,<val2>)
	If the number  <val1>  is  greater  than  <val2>  1  is  returned,
	otherwise 0 is returned.

    $(!=,<val1>,<val2>)
	If  the  numbers  <val1>  and  <val2> are not equal 1 is returned,
	otherwise 0 is returned.

    $(<=,<val1>,<val2>)
	If the number <val1>  is  less	than  or  equal  to  <val2>  1	is
	returned, otherwise 0 is returned.

    $(>=,<val1>,<val2>)
	If  the  number  <val1>  is  greater  than or equal to <val2> 1 is
	returned, otherwise 0 is returned.

    $(AND,<val1>,<val2>,...<valn>)
	The bitwise logical AND of the integers <val1> through	<valn>	is
	returned.

    $(EQ,<val1>,<val2>)
	If the strings <val1> and <val2>  are  identical  1  is  returned,
	otherwise 0.

    $(EVAL,<str>)
	The  string <str> is passed to the DIESEL evaluator and the result
	of evaluating it is returned.

    $(FIX,<value>)
	The real number <value> is truncated to an integer  by	discarding
	any fractional part.

    $(IF,<expr>,<dotrue>,<dofalse>)
	If  <expr>  is	nonzero,  <dotrue>  is	evaluated  and	 returned.
	Otherwise,  <dofalse>  is  evaluated  and returned.  Note that the
	branch not chosen by <expr> is not evaluated.

    $(INDEX,<which>,<string>)
	<string> is assumed to contain one or more values delimited by the
	macro argument separator character, comma.  <which> selects one of
	these values to be extracted, with the first item  numbered  zero.

    $(NTH,<which>,<arg0>,<arg1>,<argN>)
	Evaluates  and	returns  the  argument	selected  by  <which>.	If
	<which> is 0, <arg0> is returned, and so on.  Note the	difference
	between  $(NTH)  and  $(INDEX);  $(NTH) returns one of a series of
	arguments to the function while $(INDEX) extracts a value  from  a
	comma-delimited string passed as a single argument.  Arguments not
	selected by <which> are not evaluated.

    $(OR,<val1>,<val2>,...<valn>)
	The  bitwise  logical  OR of the integers <val1> through <valn> is
	returned.

    $(STRFILL,<string>,<ncopies>)
	Returns the result of concatenating <ncopies> of <string>.

    $(STRLEN,<string>)
	Returns the length of <string> in characters.

    $(SUBSTR,<string>,<start>,<length>)
	Returns  the  substring  of <string> starting at character <start>
	and extending for <length> characters.	Characters in  the  string
	are numbered from 1.  If <length> is omitted, the entire remaining
	length of the string is returned.

    $(UPPER,<string>)
	The  <string> is returned converted to upper case according to the
	rules of the current locale.

    $(XOR,<val1>,<val2>,...<valn>)
	The bitwise logical XOR of the integers <val1> through	<valn>	is
	returned.

    $(NL)
	Returns a single newline ('\n').

    $(QUOTE,<val>,<char>)
	Quotes the given value with the given character.

    Starting DIESEL
    ---------------

    You invoke DIESEL within your program by calling:

	int status;
	char instring[<whatever>], outstring[MAXSTR + 1];

	status = diesel(instring, outstring);

    The  output  from  the  evaluation	will  be  stored in outstring when
    control is returned to your  program.   If	no  errors  were  detected
    during  evaluation,  status  will be zero.	Otherwise status gives the
    character position within instring at which the  error  was  detected.
    If	 an  error  occurs,  DIESEL  will  include  an	error  diagnostic,
    documented below, in outstring.

    DIESEL Mechanics
    ----------------

    Generally, if you mess something up in a DIESEL expression it's pretty
    obvious  what  went  wrong.   DIESEL embeds an error indication in the
    output stream depending on the nature of the error:

	$?		Syntax error (usually a missing right  parenthesis
			or runaway string).

	$(<func>,??)	Incorrect arguments to <func>.

	$(<func>)??	Unknown function <func>.

	$++		Output string too long--evaluation truncated.

    Variable Extensions
    -------------------

    The  base-line DIESEL includes no user-defined variables.  This allows
    DIESEL to avoid allocating any local memory  and  renders  it  totally
    reentrant.	 If you compile DIESEL with the tag VARIABLES defined, the
    following additional functions are	included  which  provide  variable
    definition	and  access.   Note that these functions call malloc() and
    strdup() and thus consume heap storage.

    $(GETVAR,varname)
	Returns the value stored in <varname>.	If no  variable  with  the
	name <varname> exists, a bad argument error is reported.

    $(SETVAR,varname,value)
	Stores	the  string <value> into <varname>.  If no variable called
	<varname> exists, a new variable is created.

    Unix Extensions
    ---------------

    If you compile DIESEL with the tag UNIXTENSIONS defined, the following
    additional functions will be available:

    $(GETENV,varname)
	Returns  the  variable <varname> from the environment.	If no such
	variable is defined, returns the null string.

    $(TIME)
	Returns the current time in Unix fashion, as the number of seconds
	elapsed since 00:00:00 GMT January 1, 1970.

    $(EDTIME,<time>,<picture>)
	Edit  the  Unix  time <time> to format <picture>.  If <time> is 0,
	the current date and time is edited (this is  just  shorthand  for
	the equivalent "$(EDTIME,$(TIME),<picture>)".).

	Assume the date is: Thursday, 2 September 1993 4:53:17

	Format phrases:
	    D		    2
	    DD		    02
	    DDD 	    Thu
	    DDDD	    Thursday
	    M		    9
	    MO		    09
	    MON 	    Sep
	    MONTH	    September
	    YY		    93
	    YYYY	    1993
	    H		    4
	    HH		    04
	    MM		    53
	    SS		    17
	    AM/PM	    AM
	    am/pm	    am
	    A/P 	    A
	    a/p 	    a

	If  any  of the "AM/PM" phrases appear in the picture, the "H" and
	"HH" phrases will edit the time according to  the  12  hour  civil
	clock  (12:00-12:59-1:00-11:59)  instead  of  the  24  hour  clock
	(00:00-23:59).

*/

#include "StdAfx.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "diesel.h"

#ifdef UNIXTENSIONS
#include <stdlib.h>
#include <time.h>

#ifdef lint
/* Sun's 4.1.1 library doesn't define time() in  time.h.   This  local
   definition  is  provided  for  lint's edification in order to avoid
   natters. */
static time_t time(t) time_t *t; { return *t;}
#endif
#endif

#define FALSE	    0
#define TRUE	    1
#define DIAGNOSTIC  2

#define EOS	'\0'

#define V	(void)

/*  Globals exported  */

#ifdef TRACE_EVAL
int tracing = TRUE;		      /* Trace macro evalution */
#endif

/*  Local variables.  */

#define MAXARGS     10		      /* Maximum arguments to a macro */
#define MAXSTR	    256 	      /* Maximum string length */
#define MAXDEPTH    32		      /* Maximum recursion depth for eval */

#define MACROCHAR   '$' 	      /* Macro trigger character */
#define ARGOPEN     '(' 	      /* Argument open bracket */
#define ARGCLOSE    ')' 	      /* Argument close bracket */
#define ARGSEP	    ',' 	      /* Argument separator character */
#define QUOTE	    '"' 	      /* Literal string quote character */
#define CASEINS 			      /* Case-insensitive function names */

#define STRLIMIT    (MAXSTR - 20)     /* String output length limit */
#define OverFlow    " $(++)"	      /* Glyph indicating string overflow */

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))
#define FUZZEQ(a, b) ((((a) < (b)) ? ((b) - (a)) : ((a) - (b))) < 1E-10)

/* Get(<var>, <structure_type>) allocates a new  <structure_type>  and
   places  a  pointer  to  it  in  <var>.   The  definition  is subtly
   different depending on the setting of "lint" in order to get around
   the	infuriating "possible pointer alignment problem" natter on the
   Sun. */

#ifdef lint
#define Get(var, stype) (char *) var = malloc(sizeof(struct stype))
#else
#define Get(var, stype) var = (struct stype *) malloc(sizeof(struct stype))
#endif

struct mfent {
    char *fname;		      /* Function name */
    int (*ffunc)(int nargs, char *argv[], char *output);		      /* Evaluation function */
};

#define Mfunc(x) static int x(int nargs, char *argv[], char *output) 

#ifdef VARIABLES

struct varitem {		      /* Variable chain item */
    struct varitem *vinext;	      /* Next variable item in chain */
    char *viname;		      /* Variable name */
    char *vivalue;		      /* Variable value */
};

static struct varitem *varlist = NULL; /* Variable chain */
#endif /* VARIABLES */

/*  UCASE  --  Force letters in string to upper case.  */

static void ucase(char *c)
{
    char ch;

    while ((ch = *c) != EOS) {
	if (islower(ch)) {
	    *c = toupper(ch);
	}
	c++;
    }
}


/* The following functions are included just in case your benighted C
   library doesn't include them. */

#ifdef STRCASECMP

/*  STRCASECMP	--  Compare two strings, case insensitive.  */

static int strcasecmp(char *s1, char *s2)
{
    while ((*s1 != EOS) && (*s2 != EOS) && (toupper(*s1) == toupper(*s2))) {
	s1++;
	s2++;
    }
    if (*s1 == EOS) {
	return (*s2 == EOS) ? 0 : -1;
    }
    return (toupper(*s1) > toupper(*s2)) ? 1 : -1;
}
#endif /* STRCASECMP */

#ifdef STRNCASECMP

/*  STRNCASECMP  --  Compare two strings, length limited, case insensitive.  */

static int strncasecmp(char *s1, char *s2, int n)
{
    while ((*s1 != EOS) && (*s2 != EOS) &&
	   (n > 0) && (toupper(*s1) == toupper(*s2))) {
	s1++;
	s2++;
	n--;
    }
    if (n <= 0) {
	return 0;
    }
    if (*s1 == EOS) {
	return (*s2 == EOS) ? 0 : -1;
    }
    return (toupper(*s1) > toupper(*s2)) ? 1 : -1;
}
#endif /* STRNCASECMP */

/*  MLEDREAL  --  Edit a  double number  into  the  most  compact string
		  representation that doesn't lose significance. */

static void mledreal(double r, char *edbuf)
{
    int sprec;

    V sprintf(edbuf, "%.12f", r);
    if ((!strchr(edbuf, 'E')) && strchr(edbuf, '.')) {
	/* Trim redundant trailing zeroes off the number. */
	for (sprec = strlen(edbuf) - 1; sprec > 0; sprec--) {
	    if (edbuf[sprec] != '0' || edbuf[sprec - 1] == '.')
		break;
	    edbuf[sprec] = EOS;
	}
	/* Now, if all we're left with is a ".0", drop the decimal
	   portion entirely. */
	if ((strlen(edbuf) > 2) && (strcmp(edbuf + (strlen(edbuf) - 2),
	    ".0") == 0)) {
	    edbuf[strlen(edbuf) - 2] = EOS;
	}
    }
}

/*  IARG  --  Interpret  an  argument  as an integer.  The argument is
	      scanned according to the scanf() "%i" format.   TRUE  is
	      returned if a valid integer is scanned, FALSE otherwise. */

static int iarg(char *argstr, int *intres)
{
    char earg[MAXSTR];

    if (diesel(argstr, earg) == 0) {
		return sscanf(earg, "%i", intres) == 1;
    }
    return FALSE;
}

#define Iarg(v,n)  if (!iarg(argv[(n)], &(v))) return FALSE

/*  RARG  --  Interpret an  argument  as  a  real.   The  argument  is
	      scanned according to the sscanf() "%lf" format.  TRUE is
	      returned if a valid double is scanned, FALSE otherwise. */

static int rarg(char *argstr, double *realres)
{
    char earg[MAXSTR];

    if (diesel(argstr, earg) == 0) {
		return sscanf(earg, "%lf", realres) == 1;
    }
    return FALSE;
}

#define ArgCount(min,max) if (nargs < (min) || nargs > (max)) return FALSE

#define Rarg(v,n)  if (!rarg(argv[(n)], &(v))) return FALSE

#define Dsarg(s)   char s[MAXSTR]     /* Declare string argument */
#define Sarg(v,n)  if (diesel(argv[(n)], (v)) != 0) return FALSE

#define Rint(n)     V sprintf(output, "%d", (n)); return TRUE/* Return int */
#define Rreal(n)    mledreal((n), output); return TRUE	     /* Return double */
#define Rstr(s)     V strcpy(output, (s)); return TRUE	     /* Return str */

/*
       M A C R O   I M P L E M E N T I N G   F U N C T I O N S

    The following functions, each with a header declared with Mfunc(),
    implement the macros available to the caller of Diesel.  To add  a
    macro,  simply  define  a new implementing function using the code
    below as a guideline, then add the macro and function name to  the
    macro function table, mftab[], which appears immediately after the
    last macro implementing function.

    A macro implementing function returns TRUE upon success (in  which
    case  it  must  supply  its output string in the "output" argument
    when it returns), FALSE in case of failure when  the  contents  of
    the  "output"  argument  are to be discarded, and DIAGNOSTIC if an
    error in the macro has caused a diagnostic message to be placed in
    the "output" string.

*/

/*  $(+,<int1>,<int2>,...)  --	Add numbers together  */

Mfunc(f_plus)
{
    int i;
    double result = 0;

    for (i = 0; i < nargs; i++) {
	double varg;

	Rarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result += varg;
	}
    }
    Rreal(result);
}

/*  $(-,<int1>,<int2>,...)  --	Subtract numbers from an initial number */

Mfunc(f_minus)
{
    int i;
    double result = 0;

    for (i = 0; i < nargs; i++) {
	double varg;

	Rarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result -= varg;
	}
    }
    Rreal(result);
}

/*  $(*,<int1>,<int2>,...)  --	Multiply numbers together  */

Mfunc(f_times)
{
    int i;
    double result = 1;

    for (i = 0; i < nargs; i++) {
	double varg;

	Rarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result *= varg;
	}
    }
    Rreal(result);
}

/*  $(/,<int1>,<int2>,...)  --	Divide a number by other numbers  */

Mfunc(f_divide)
{
    int i;
    double result = 1;

    for (i = 0; i < nargs; i++) {
	double varg;

	Rarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result /= varg;
	}
    }
    Rreal(result);
}

/*  $(=,<num1>,<num2>)	--  Test two numbers equal  */

Mfunc(f_numeq)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(FUZZEQ(v1, v2));
}

/*  $(!=,<num1>,<num2>)  --  Test two numbers unequal  */

Mfunc(f_numne)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(!FUZZEQ(v1, v2));
}

/*  $(<,<num1>,<num2>)	--  Test two numbers less than	*/

Mfunc(f_numlt)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(v1 < v2);
}

/*  $(>,<num1>,<num2>)	--  Test two numbers greater than  */

Mfunc(f_numgt)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(v1 > v2);
}

/*  $(>=,<num1>,<num2>)  --  Test two numbers greater than or equal  */

Mfunc(f_numge)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(v1 >= v2);
}

/*  $(<=,<num1>,<num2>)  --  Test two numbers less than or equal  */

Mfunc(f_numle)
{
    double v1, v2;

    ArgCount(2, 2);

    Rarg(v1, 0);
    Rarg(v2, 1);

    Rint(v1 <= v2);
}

/*  $(AND,<int1>,<int2>,...)  --  Bitwise AND integers together  */

Mfunc(f_and)
{
    int i, result = 1;

    for (i = 0; i < nargs; i++) {
	int varg;

	Iarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result &= varg;
	}
    }
    Rint(result);
}

#ifdef UNIXTENSIONS

/*  $(EDTIME,<time>,<picture>)	--  Edit time to format <picture>

	Assume the date is: Thursday, 2 September 1993 4:53:17

	Format phrases:
	    D		    2
	    DD		    02
	    DDD 	    Thu
	    DDDD	    Thursday
	    M		    9
	    MO		    09
	    MON 	    Sep
	    MONTH	    September
	    YY		    93
	    YYYY	    1993
	    H		    4
	    HH		    04
	    MM		    53
	    SS		    17
	    AM/PM	    AM
	    am/pm	    am
	    A/P 	    A
	    a/p 	    a

	If any of the "AM/PM" phrases appear in the picture,  the  "H"
	and  "HH"  phrases will edit the time according to the 12 hour
	civil clock (12:00-12:59-1:00-11:59) instead of  the  24  hour
	clock (00:00-23:59).

	If <time> is 0, the current time and date is edited.
*/

Mfunc(f_edtime)
{
    double val;
    Dsarg(pic);
    long ltime;
    struct tm *jd;
    char *pp = pic;

    static int mday, min, tmon, sec, heure, year, yearmod100;

    /* Why declare it this way?  Think about the poor sucker  who  has
       to  localise  a	strncasecmp(zilch,  "MONTH",  5)  when "MONTH"
       translates into different length words in other languages! */

    static char month[] = "MONTH",
		mon[]	= "MON",
		dddd[]	= "DDDD",
		ddd[]	= "DDD",
		ampm[]	= "AM/PM",
		ap[]	= "A/P";
    int lcompl;
#define lComp(x)    x, lcompl = strlen(x)

    static struct {
	char *pname;
	char *pfmt;
	int *pitem;
    } pictab[] = {
	/* Careful!  These must be sorted by descending order of
	   picture string length. */
	{"YYYY", "%02d", &year},
	{"DD",	 "%02d", &mday},
	{"HH",	 "%02d", &heure},
	{"MM",	 "%02d", &min},
	{"MO",	 "%02d", &tmon},
	{"SS",	 "%02d", &sec},
	{"YY",	 "%02d", &yearmod100},
	{"D",	 "%d",	 &mday},
	{"H",	 "%d",	 &heure},
	{"M",	 "%d",	 &tmon}
    };

    ArgCount(2, 2);

    Rarg(val, 0);
    Sarg(pic, 1);
    V strcpy(output, "");

    /* Special gimmick: if the time argument is zero,  use the current
       date  and  time	saved  at  the	start  of  the	entire	 macro
       evaluation.   This  not	only  saves  space and time, it avoids
       embarrassment due to the time incrementing  between  individual
       calls on $(edtime) within one overall macro line. */

    if (FUZZEQ(val, 0.0)) {
		ltime = time((time_t *) NULL);
    } else {
		ltime = long(val);
    }
    jd = localtime(&ltime);
    tmon = jd->tm_mon + 1;
    mday = jd->tm_mday;
    min = jd->tm_min;
    sec = jd->tm_sec;
    year = jd->tm_year + 1900;
    yearmod100 = year % 100;	      /* Calculate year mod 100 */
#ifdef lint
    /* The variables that appear in the following bogus statement
       are set above but only referenced via their pointers in the
       pictab[] table above.  Lint doesn't understand this, and
       complains that the variables are set but never referenced.
       Handing the following statement to lint shuts it up. */
    tmon = mday + min + tmon + sec + yearmod100;
#endif

    /* If  the time picture contains any  "A" or "P" characters, which
       indicate that time is expressed in AM or  PM  (or  any  of  its
       variants), convert the hour to 12 hour civil clock time. */

    heure = jd->tm_hour;
    if (strstr(pic, "AM/PM") || strstr(pic, "A/P") ||
	strstr(pic, "am/pm") || strstr(pic, "a/p")) {
	heure = jd->tm_hour % 12;
	if (heure == 0) {
	    heure = 12;
	}
    }

    while (*pp != EOS) {

	/* Detect incipient output string overflow and escape in time. */

	if (strlen(output) > STRLIMIT) {
	    V strcat(output, OverFlow);
	    return DIAGNOSTIC;
	}

	if (strncasecmp(pp, lComp(month)) == 0) {
	    static char *mois[] = {
			"Januar",
			"Februar",
			"März",
			"April",
			"Mai",
			"Juni",
			"Juli",
			"August",
			"September",
			"Oktober",
			"November",
			"Dezember" 
	    };
	    V strcat(output, mois[jd->tm_mon]);
	    pp += lcompl;
	} else if (strncasecmp(pp, lComp(mon)) == 0) {
	    static char *mois[] = {
			"Jan",
			"Feb",
			"Mar",
			"Apr",
			"Mai",
			"Jun",
			"Jul",
			"Aug",
			"Sep",
			"Okt",
			"Nov",
			"Dez" 
	    };
	    V strcat(output, mois[jd->tm_mon]);
	    pp += lcompl;
	} else if (strncasecmp(pp, lComp(dddd)) == 0) {
	    static char *jour[] = {
			"Sonntag",
			"Montag",
			"Dienstag",
			"Mittwoch",
			"Donnerstag",
			"Freitag",
			"Sonnabend"
	    };
	    V strcat(output, jour[jd->tm_wday]);
	    pp += lcompl;
	} else if (strncasecmp(pp, lComp(ddd)) == 0) {
	    static char *jour[] = {
			"So",
			"Mo",
			"Die",
			"Mi",
			"Do",
			"Fr",
			"Sa"
	    };
	    V strcat(output, jour[jd->tm_wday]);
	    pp += lcompl;
	} else if (strncasecmp(pp, lComp(ampm)) == 0 ||
		   strncasecmp(pp, lComp(ap)) == 0) {
	    char AandP = (jd->tm_hour >= 12 ? 'P' : 'A');
	    int l = strlen(output);

	    if (islower(*pp)) {
		AandP = tolower(AandP);
	    }
	    output[l] = AandP;
	    if (pp[1] != '/') {
		output[++l] = pp[1];
	    }
	    output[l + 1] = EOS;
	    pp += lcompl;
	} else {
	    int i, foundit = FALSE;

	    for (i = 0; i < ELEMENTS(pictab); i++) {
		if (strncasecmp(pp, pictab[i].pname,
				strlen(pictab[i].pname)) == 0) {
		    V sprintf(output + strlen(output), pictab[i].pfmt,
				*pictab[i].pitem);
		    pp += strlen(pictab[i].pname);
		    foundit = TRUE;
		    break;
		}
	    }
	    if (!foundit) {
		char *op = output + strlen(output);

		*op++ = *pp++;
		*op = EOS;
	    }
	}
    }
    return TRUE;
}
#endif /* UNIXTENSIONS */

/*  $(EQ,<str1>,<str2>)  --  Return 1 if strings equal, 0 otherwise  */

Mfunc(f_equal)
{
    Dsarg(arg1);
    Dsarg(arg2);

    ArgCount(2, 2);

    Sarg(arg1, 0);
    Sarg(arg2, 1);
    Rint(strcmp(arg1, arg2) == 0);
}

/*  $(EVAL,<arg>)  --  Evaluate <arg>, re-scanning as if in input stream  */

Mfunc(f_eval)
{
    Dsarg(arg);
    int retval;

    static int depth = 0;

    if (depth >= MAXDEPTH)
	return FALSE;

    ArgCount(1, 1);

    Sarg(arg, 0);
    depth++;
    retval = (diesel(arg,output) == 0);
    depth--;
    return retval;
}

/*  $(FIX,<real>)  --  The fractional part of <real> is truncated  */

Mfunc(f_fix)
{
    double r;
    int rfix;

    ArgCount(1, 1);

    Rarg(r, 0);
    rfix = int(r);

    Rint(rfix);
}

#ifdef UNIXTENSIONS

/*  $(GETENV,varname)  --  Get environment variable value  */

Mfunc(f_getenv)
{
    Dsarg(vname);
    char *ep;

    ArgCount(1, 1);

    Sarg(vname, 0);

    ep = getenv(vname);
    if (NULL == ep || strlen(ep) >= STRLIMIT) {
	V strcpy(output, OverFlow);
	return DIAGNOSTIC;
    }
    Rstr(ep != NULL ? ep : "");
}
#endif /* UNIXTENSIONS */

#ifdef VARIABLES

/*  $(GETVAR,<varname>)  --  Returns the value for the named
			     variable.	Errors if the variable has
			     not been defined.	*/

Mfunc(f_getvar)
{
    Dsarg(vname);
    struct varitem *vp = varlist;

    ArgCount(1, 1);
    Sarg(vname, 0);

    while (vp != NULL) {
	if (strcmp(vp->viname, vname) == 0) {
	    Rstr(vp->vivalue);
	}
	vp = vp->vinext;
    }
    return FALSE;
}
#endif /* VARIABLES */

/*  $(IF,<int1>,<true>,<false>)  --  If <int1> is nonzero, evaluate and
				     return <true>, otherwise evaluate
				     and return <false>.  If <false>
				     is omitted and <int1> is zero, the
				     null string is returned. */

Mfunc(f_if)
{
    int bval;
    Dsarg(str);

    ArgCount(2, 3);

    Iarg(bval, 0);
    if (bval) {
	Sarg(str, 1);
    } else {
	if (nargs > 2) {
	    Sarg(str, 2);
	} else {
	    str[0] = EOS;
	}
    }
    Rstr(str);
}

/*  $(INDEX,<n>,<listarg>)  --	Extracts the nth item from a comma separated
				list <listarg>.  Returns the null string if
				no nth item exists. */

Mfunc(f_index)
{
    int bval;
    Dsarg(str);
    char *sp;

    ArgCount(2, 2);

    Iarg(bval, 0);
    if (bval < 0)
       return FALSE;

    Sarg(str, 1);
    sp = str;

    /* Advance the specified number of argument separators. */

    while (bval-- > 0) {
	sp = strchr(sp, ARGSEP);
	if (sp == NULL) {
	    Rstr("");
	}
	sp++;
    }

    /* If there's another argument separator, terminate the result
       string at that point. */

    if (strchr(sp, ARGSEP)) {
	*strchr(sp, ARGSEP) = EOS;
    }

    Rstr(sp);
}

/*  $(NTH,<n>,<item1>,<item2>,...<itemj>)  --  Evauates and returns <itemn>  */

Mfunc(f_nth)
{
    int n;
    Dsarg(str);

    ArgCount(2, MAXARGS);

    Iarg(n, 0);
    if ((n < 0) || ((n + 1) >= nargs))
	return FALSE;

    Sarg(str, n + 1);
    Rstr(str);
}

/*  $(OR,<int1>,<int2>,...)  --  Bitwise OR integers together  */

Mfunc(f_or)
{
    int i, result = 0;

    for (i = 0; i < nargs; i++) {
	int varg;

	Iarg(varg, i);
	if (i == 0) {
	    result = varg;
	} else {
	    result |= varg;
	}
    }
    Rint(result);
}

#ifdef VARIABLES

/*  $(SETVAR,<varname>,<value>)  --  Sets the variable named <varname>
				     to the given <value>.  If the
				     variable is not currently defined,
				     a new variable is created.  Returns
				     the null string. */

Mfunc(f_setvar)
{
    Dsarg(vname);
    Dsarg(vvalue);
    struct varitem *vp = varlist, *vi;
    char *vnew;

    ArgCount(2, 2);
    Sarg(vname, 0);
    Sarg(vvalue, 1);

    vnew = strdup(vvalue);
    if (vnew == NULL) {
	/* Out of memory--cannot define new variable. */
	return FALSE;
    }

    while (vp != NULL) {
	if (strcmp(vp->viname, vname) == 0) {
	    free(vp->vivalue);
	    vp->vivalue = vnew;
	    Rstr("");
	}
	vp = vp->vinext;
    }
    Get(vi, varitem);
    if (vi == NULL) {
	return FALSE;
    }
    vi->viname = strdup(vname);
    if (vi->viname == NULL) {
	free((char *) vi);
	return FALSE;
    }
    vi->vinext = varlist;
    vi->vivalue = vnew;
    varlist = vi;
    Rstr("");
}
#endif /* VARIABLES */

/*  $(STRFILL,<string>,<ncopies>)  --  Create a string by concatenating
				       <ncopies> of <string> together  */

Mfunc(f_strfill)
{
    Dsarg(str);
    int ncopies;

    ArgCount(2, 2);

    Sarg(str, 0);
    Iarg(ncopies, 1);
    if (ncopies < 1) {
	Rstr("");
    } else {
	output[0] = EOS;
	while (ncopies-- > 0) {
	    if ((strlen(output) + strlen(str)) >= STRLIMIT) {
		V strcpy(output, OverFlow);
		return DIAGNOSTIC;
	    }
	    V strcat(output, str);
	}
    }
    return TRUE;
}

/*  $(STRLEN,<string>)	--  Return length of string  */

Mfunc(f_strlen)
{
    Dsarg(str);

    ArgCount(1, 1);

    Sarg(str, 0);
    Rint(strlen(str));
}

/*  $(SUBSTR,<string>,<start>,<length>)  --  Extract substring	*/

Mfunc(f_substr)
{
    ArgCount(2, 3);
    V strcpy(output, "");
    if (nargs > 0) {
	Dsarg(str);
	int start, len = MAXSTR + 1, l = strlen(argv[0]);

	Sarg(str, 0);
	Iarg(start, 1);
	if (nargs > 2) {
	    Iarg(len, 2);
	}
	if ((start >= 1) && ((start - 1) < l)) {
	    char *ip = str + (start - 1), *op = output;

	    while ((len-- > 0) && *ip) {
		*op++ = *ip++;
	    }
	    *op++ = EOS;
	}
    }
    return TRUE;
}

#ifdef UNIXTENSIONS

/*  $(TIME)  --  Return Unix integer time  */

/* ARGSUSED */
Mfunc(f_time)
{
    ArgCount(0, 0);

    V sprintf(output, "%ld", (long) time((time_t *) NULL)); 
    return TRUE;
}
#endif /* UNIXTENSIONS */

/*  $(UPPER,<string>)	    --	Convert string to upper case  */

Mfunc(f_upper)
{
    ArgCount(1, 1);
    V strcpy(output, "");
    if (nargs > 0) {
	Dsarg(str);

	Sarg(str, 0);
	ucase(str);
	V strcpy(output, str);
    }
    return TRUE;
}

/*  $(XOR,<int1>,<int2>,...)  --  Bitwise XOR integers together  */

Mfunc(f_xor)
{
    int i, result = 0;

    for (i = 0; i < nargs; i++) {
	int varg;

		Iarg(varg, i);
		if (i == 0) {
			result = varg;
		} else {
			result ^= varg;
		}
    }
    Rint(result);
}

/*  $(NL)  --  inserts '\n' into the output  */

Mfunc(f_nl)
{
    strcpy (output, "\n");
	return TRUE;
}

/*  $(QUOTE,<val>,<char>)  --  quotes <val> with <char>  */

Mfunc(f_quote)
{
    Dsarg(str);
	Dsarg(quote);

    ArgCount(1, 2);

    Sarg(str, 0);
	strcpy (quote, "\""); 
	if (nargs > 1)
		Sarg(quote, 1);

	V sprintf(output, "%s%s%s", quote, str, quote);
	return TRUE;
}

/* Macro name/function table. */

static struct mfent mftab[] = {
	{"+",	    f_plus},
	{"-",	    f_minus},
	{"*",	    f_times},
	{"/",	    f_divide},
	{"=",	    f_numeq},
	{"<",	    f_numlt},
	{">",	    f_numgt},
	{"!=",	    f_numne},
	{"<=",	    f_numle},
	{">=",	    f_numge},
	{"AND",     f_and},
	{"EQ",	    f_equal},
	{"EVAL",    f_eval},
	{"FIX",     f_fix},
	{"IF",	    f_if},
	{"INDEX",   f_index},
	{"NTH",     f_nth},
	{"OR",	    f_or},
	{"STRFILL", f_strfill},
	{"STRLEN",  f_strlen},
	{"SUBSTR",  f_substr},
	{"UPPER",   f_upper},
	{"XOR",     f_xor},
	{"NL",		f_nl},
	{"QUOTE",	f_quote},

#ifdef UNIXTENSIONS
	{"EDTIME",  f_edtime},
	{"GETENV",  f_getenv},
	{"TIME",    f_time},
#endif /* UNIXTENSIONS */

#ifdef VARIABLES
	{"GETVAR",  f_getvar},
	{"SETVAR",  f_setvar},
#endif /* VARIABLES */
};

/*  COPYMODE  --  Copies  characters  from  the  input	to the output,
		  handling quoted literal strings as it  goes.	 If  a
		  nonquoted  macro  character  is encountered, returns
		  with the string  pointer  positioned	at  the  macro
		  character.   If  end	of  string is encountered, the
		  input pointer will be left  positioned  at  the  EOS
		  character.   Returns	0  if  the  end  of  string is
		  encountered, 1 if a macro is encountered, and -1  if
		  the  end  of	input  was encountered while copying a
		  quoted string. */

static int copymode(char **in, char **out)
{
    char *ip = *in, *op = *out;
    char ch;
    int instring = FALSE;

    while ((ch = *ip++) != EOS) {
	switch (ch) {
	    case QUOTE:
		if (instring) {
		    /* If we're in a string  and  hit  a  quote,  peek
		       ahead.	If the next character is a quote also,
		       then this is a forced quote.  Copy it literally
		       to  the	output	stream and leave the in-string
		       mode in effect. */
		    if (*ip == QUOTE) {
			*op++ = QUOTE;
			ip++;
		    } else {
			instring = FALSE;
		    }
		} else {
		    instring = TRUE;
		}
		break;

	    case MACROCHAR:
		if (!instring && *ip == ARGOPEN) {
		    *in = ip;
		    *out = op;
		    return 1;
		}
		/* Wheeee!!!  Note fall-through. */

	    default:
		*op++ = ch;
		break;
	}

	/* If we're in danger of overflowing the output string, attach
	   the string overflow indication and bail  out.   We  advance
	   the	input  pointer	to the end of string and signal end of
	   input  being  encountered  to   cleanly   shut   down   the
	   interpreter. */

	if ((op - *out) > STRLIMIT) {
	    V strcpy(op, OverFlow);
	    *in = ip + strlen(ip);    /* Advance input pointer to EOS */
	    *out = op + strlen(op);   /* Calculate end of string pointer */
	    return 0;		      /* Say end of string was encountered */
	}
    }
    *in = ip - 1;
    *out = op;
    return instring ? -1 : 0;
}

/*  MACROMODE  --  Scan  a  macro, identifying its arguments.  Returns
		   the number  of  arguments  scanned  (including  the
		   macro  name)  if  the macro is valid, 0 if a syntax
		   error occurs, and -1 if the end of the input string
		   was	encountered  before the matching macro bracket
		   was found.  If a positive result is	returned,  the
		   output   string   will  contain  the  arguments  as
		   successive strings, separated by EOS markers. */

static int macromode(char **in, char **out)
{
    char *ip = *in, *op = *out;
    char ch;
    int nargs = 0, instring = FALSE, depth = 0;

    if ((ch = *ip++) != ARGOPEN) {
		*op++ = MACROCHAR;
		*op++ = ch;
		*in = ip - 1;		      /* Unconsume character */
		*out = op;
		return 0;
    }

    /* Now scan the arguments of the macro, searching for the matching
       macro  bracket.	 We  recognise	quoted	strings  and  argument
       delimiter  characters  here,  but  don't  evaluate  any	of the
       arguments. */

    while ((ch = *ip++) != EOS) {
	switch (ch) {
	    case QUOTE:
		if (instring) {

		    /* If we're in a string  and  hit  a  quote,  peek
		       ahead.	If the next character is a quote also,
		       then this is a forced quote.  Copy it literally
		       to  the	output	stream and leave the in-string
		       mode in effect. */

		    if (*ip == QUOTE) {
			*op++ = QUOTE;
			ip++;
		    } else {
			instring = FALSE;
		    }
		} else {
		    instring = TRUE;
		}
		break;

	    case ARGOPEN:
		if (!instring) {
		    depth++;
		}
		*op++ = ch;
		break;

	    case ARGCLOSE:
		if (!instring) {
		    if (--depth < 0) {
			*op++ = EOS;
			nargs++;
			*out = op;
			*in = ip;
			return nargs;
		    }
		}
		*op++ = ch;
		break;

	    case ARGSEP:
		if (!instring && (depth == 0)) {
		    if (nargs >= MAXARGS - 1)
			goto errout;

		    nargs++;	      /* Increment number of arguments */
		    ch = EOS;	      /* Store argument break in output */
		}
		/* Wheeee!!!  Note fall-through. */

	    default:
		*op++ = ch;
		break;
	}

	/* If we're in danger of overflowing the output string, attach
	   the string overflow indication and bail  out.   We  advance
	   the	input  pointer	to the end of string and signal end of
	   input  being  encountered  to   cleanly   shut   down   the
	   interpreter. */

	if ((op - *out) > STRLIMIT) {
errout:
	    V strcpy(op, OverFlow);
	    *in = ip + strlen(ip);    /* Advance input pointer to EOS */
	    *out = op + strlen(op);   /* Calculate end of string pointer */
	    return -1;		      /* Call it an unmatched bracket */
	}
    }

    /* Hit end of input string without finding matching macro bracket. */

    *op++ = EOS;
    *out = op;
    *in = ip - 1;
    return -1;
}

/*  MACROVALUE	--  Determine the value of a macro.  Returns TRUE if
		    the macro was evaluated successfully, FALSE if
		    an error was detected, and DIAGNOSTIC if the macro
		    errored and supplied a diagnostic message as its
		    output. */

static int macrovalue(int nargs, char *args, char *output)
{
    char *argv[MAXARGS];
    Dsarg(macname);
    int i;

    for (i = 0; i < MAXARGS; i++) {
	argv[i] = "";
    }
    for (i = 0; i < nargs; i++) {
	argv[i] = args;
	args += strlen(args) + 1;
    }

    /* Look up the argument function in the function table. */

    Sarg(macname, 0);
#ifdef CASEINS
    ucase(macname);
#endif

#ifdef TRACE_EVAL
    if (tracing) {
	V printf("Eval: $(%s", macname);
	for (i = 1; i < nargs; i++) {
	    V printf(", %s", argv[i]);
	}
	V printf(")\n");
    }
#endif
    for (i = 0; i < ELEMENTS(mftab); i++) {
	if (strcmp(macname, mftab[i].fname) == 0) {
	    int mstat = (*mftab[i].ffunc)(nargs - 1, argv + 1, output);

	    /* If the macro bailed out without supplying a  diagnostic
	       message, make up a general-purpose message here. */

	    if (mstat == FALSE) {
		V sprintf(output, " $(%s,%c%c) ", macname, '?', '?');
	    }
	    if (mstat != TRUE) {
#ifdef TRACE_EVAL
		if (tracing) {
		    V printf("Err:  %s\n", output);
		}
#endif
		return DIAGNOSTIC;
	    }
#ifdef TRACE_EVAL
	    if (tracing) {
		V printf("===>	%s\n", output);
	    }
#endif
	    return TRUE;
	}
    }
    V sprintf(output, " $(%s)?? ", macname);
#ifdef TRACE_EVAL
    if (tracing) {
	 V printf("Err:  %s\n", output);
    }
#endif
    return DIAGNOSTIC;
}

/*  MACROEVAL  --  Evaluate a macro and place its results in the output
		   string.  Returns 1 if the macro was valid, 0 in case
		   of error.  If the macro itself detected an error which
		   placed diagnostic output in out, 2 is returned. */

static int macroeval(char **in, char **out)
{
    char *ip = *in, *op = *out;
    char margs[MAXSTR], mvalue[MAXSTR];
    char *ma = margs;
    int stat, nargs;

    nargs = stat = macromode(&ip, &ma);

    if (stat > 0) {
#ifdef ECHOMAC
	*op++ = ' ';
	*op++ = '<';
	V sprintf(op, "(%d)", stat);
	op += strlen(op);
	ma = margs;
	while (stat-- > 0) {
	    int l = strlen(ma);

	    V strcpy(op, ma);
	    op += l;
	    ma += l + 1;
	    *op++ = ';';
	}
	*op++ = '>';
	*op++ = '=';
#endif

	/* Evaluate the macro. */

	stat = macrovalue(nargs, margs, mvalue);
	V strcpy(op, mvalue);
	op += strlen(mvalue);
#ifdef ECHOMAC
	if (stat == FALSE || stat == DIAGNOSTIC) {
	    V strcpy(op, "*ERR*");
	    op += 5;
	}
	*op++ = ' ';
#endif
    } else {
	stat = FALSE;
    }

    *op++ = EOS;
    *out = op;
    *in = ip;

    return stat;
}

/*  DIESEL  --	Evaluate a string IN and  return  the  value  in  OUT.
		Returns  zero  if the evaluation was successful; if an
		error was detected, returns the column	at  which  the
		error was found. */

int diesel(char *in, char *out)
{
    int stat;
    char *inp = in, *outp = out;

    while (TRUE) {
	stat = copymode(&inp, &outp);
	if (stat == 1) {
	    char margs[MAXSTR];
	    char *ma = margs;

	    stat = macroeval(&inp, &ma);
	    if (stat > 0) {

		/* If we're about to overflow the output string,  bail
		   out of  the	evaluation  and  append  the  overflow
		   marker. */

		if (((outp - out) + strlen(margs)) > STRLIMIT) {
		    V strcpy(outp, OverFlow);
		    return inp - in;
		}
		V strcpy(outp, margs);
		outp += strlen(margs);
	    } else {
		*outp++ = MACROCHAR;
		*outp++ = '?';
		*outp++ = EOS;
		return inp - in;
	    }

	    /* Error  detected	in  macro  evaluation  which  placed a
	       diagnostic string in the output.  */

	    if (stat == DIAGNOSTIC) {
		return inp - in;
	    }
	} else {
	    *outp++ = EOS;
	    break;
	}
    }

    return stat;
}

#ifdef TESTPROG

/*  Test program.  */

main()
{
    char in[MAXSTR + 1], out[MAXSTR + 1];
    int err;

    while (TRUE) {
	if (fgets(in, sizeof in, stdin) == NULL) {
	    break;
	}

	/* Cheap way to be insensitive to EOL conventions. */

	while (isspace(in[strlen(in) - 1])) {
	    in[strlen(in) - 1] = EOS;
	}

	err = diesel(in, out);
	if (err) {
	    V printf("=> %s\n", in);
	    V printf("---");
	    while (--err > 0) {
		V printf("-");
	    }
	    V printf("^\n");
	}
	V printf("%c %s\n", err ? '*' : '<', out);
    }
    return 0;
}
#endif /* TESTPROG */

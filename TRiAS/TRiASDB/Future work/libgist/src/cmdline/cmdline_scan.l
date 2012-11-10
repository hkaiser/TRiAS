/* cmdline_scan.l					-*- Mode: c++ -*-
 * Copyright (c) 1997, Regents of the University of California
 * $Id: cmdline_scan.l,v 1.6 1999/06/15 23:36:53 marcel Exp $
 */
%{
#include <iostream.h>

/* STL */
#include <string.h>

#include "gist_defs.h"
#include "cmdline_gram_tab.h"
%}

ws		[ \t]+
comment	#[^\n]*
id		[[:graph:]]+
nl		[\r\n]
int             "-"?[[:digit:]]+
flt		"-"?[[:digit:]]+"."[[:digit:]]+
strconst	"\""[^"]*"\""
param		[[:digit:]]+
ioparam		"io="{param}

%%

{ws}	;
{comment} ;
{flt}	  { yylval.flt = strtod((const char *)yytext, NULL);
            return FLOATCONST;
          }

{int}     { yylval.number = atoi((const char *)yytext);
	    return INTCONST;
	  }

loadfile	{ return LOADFILE; }
create		{ return CREATE; }
createanl	{ return CREATEANL; }
splitstats	{ return SPLITSTATS; }
penaltystats	{ return PENALTYSTATS; }
wkldstats	{ return WKLDSTATS; }
anlinfo		{ return ANLINFO; }
predinfo	{ return PREDINFO; }
split		{ return SPLIT; }
open            { return OPEN; }
close           { return CLOSE; }
openanl         { return OPENANL; }
closeanl        { return CLOSEANL; }
check		{ return CHECK; }
set		{ return SET; }
struct		{ return STRUCT; }
echo		{ return ECHO_TOKEN; }
write		{ return WRITE; }
insert		{ return INSERT; }
delete          { return DELETE; }
select          { return SELECT; }
dump		{ return DUMP; }
help		{ return HELP; }
quit		{ return QUIT; }
{ioparam}	{ yylval.number = atoi(((const char*) yytext) + 3);
		  return IOPARAM; }
{strconst}	{ int len = strlen(yytext) - 2; /* exclude the quotes */
		  yylval.string = new char[len+1];
		  strncpy(yylval.string, yytext+1, len);
		  yylval.string[len] = '\0'; return STRCONST; }
{nl}		{ return NL; }
{id}	        { int len = strlen(yytext);
                  yylval.string = new char[len+1];
                  strcpy(yylval.string, yytext);
                  yylval.string[len] = '\0'; return ID; }
<<EOF>>         { yyterminate(); }
.		{ cerr << "Lexical error in input string: invalid character\n";
		  return ERROR; }
%%


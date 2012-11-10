// cmdline_gram.y					-*- mode: c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: cmdline_gram.y,v 1.5 1999/01/19 01:43:36 marcel Exp $

%{
#include <iostream.h>

#include "gist_compat.h"	// for malloc
#include "gist_defs.h"
#include "cmdline.h"
#define YYDEBUG 1

void cmdPrompt();
int yyerror(char *msg);
int yylex();
%}

%union {
    char *string;
    shpid_t pgno;
    int number;
    float flt;
}

%token <string> ID
%token <string> STRCONST
%token <number> INTCONST 
%token <number> IOPARAM
%token <flt> FLOATCONST
%token CREATE INSERT OPEN CLOSE QUIT SELECT DELETE NL ERROR CHECK SPLIT
%token HELP DUMP ONLY SET STRUCT WRITE
%token ECHO_TOKEN IOPARAM EVALSPLIT EVALPENALTY
%token SPLIT LOADFILE PREDINFO
%token CREATEANL OPENANL CLOSEANL WKLDSTATS SPLITSTATS PENALTYSTATS ANLINFO

%type <pgno> dump_page
%type <string> opt_id
%type <number> opt_k
%type <number> opt_ioparam

%start commands

%%

commands
    : 
    | commands command
    {
        cmdPrompt();
    }
    ;

command
    : CREATE ID ID NL
    // usage: create <indexname> <ext-name>
    {
	cmdCreate($2, $3);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
    }
    | CREATE ID ID ID FLOATCONST NL
    // usage: create <indexname> <ext-name> <data-filename> <fill-factor>
    {
	cmdLoad($2, $3, $4, $5);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
	if ($4) delete [] $4;
    }
    | WRITE LOADFILE ID ID NL
    // usage: write loadfile <indexname> <filename>
    {
        cmdWriteLoadfile($3, $4);
	if ($3) delete [] $3;
	if ($4) delete [] $4;
    }
    | OPEN ID NL
    // usage: open <indexname>
    {
        cmdOpen($2);
        if ($2) delete [] $2;
    }
    | CLOSE ID NL
    // usage: close <indexname>
    {
        cmdClose($2);
        if ($2) delete [] $2;
    }
    | CHECK ID NL
    // usage: check <indexname>
    {
        cmdCheck($2);
	if ($2) delete [] $2;
    }
    | SELECT ID opt_k opt_ioparam STRCONST NL
    // usage: select <indexname> [<k>] [io(<limit>)] "<qualification>"
    {
	cmdSelect($2, $5, $3, $4);
	if ($2) delete [] $2;
	if ($5) delete [] $5;
    }
    | INSERT ID STRCONST STRCONST NL
    // usage: insert <indexname> "<key>" "<data>"
    {
	cmdInsert($2, $3, $4);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
	if ($4) delete [] $4;
    }
    | DELETE ID STRCONST NL
    // usage: delete <indexname> "<qualification>"
    {
	cmdDelete($2, $3);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
    }
    | QUIT NL
    // usage: quit
    {
        cmdQuit();
    }
    | DUMP ID dump_page NL
    // usage: dump <indexname> [<pgno>]
    {
        cmdDump($2, $3);
        if ($2) delete [] $2;
    }
    | SPLIT ID INTCONST NL
    // usage: split <indexname> <pgno> (internal command)
    {
        cmdSplit($2, $3);
        if ($2) delete [] $2;
    }
    | SET ECHO_TOKEN INTCONST NL
    // usage: set echo (0|1)
    {
        cmdSetEcho($3);
    }
    | SET STRUCT ID INTCONST NL
    // usage: set struct <indexname> (0|1) (internal command)
    {
	cmdSetStruct($3, $4);
	if ($3) delete [] $3;
    }
    | CREATEANL ID ID ID INTCONST FLOATCONST NL
    // usage: createanl <analysisname> <indexname> <scriptfile> <#random> <targetutil>
    {
        cmdCreateAnl($2, $3, $4, $5, $6);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
	if ($4) delete [] $4;
    }
    | OPENANL ID NL
    // usage: openanl <analysis>
    {
        cmdOpenAnl($2);
	if ($2) delete [] $2;
    }
    | CLOSEANL ID NL
    // usage: closeanl <analysis>
    {
        cmdCloseAnl($2);
	if ($2) delete [] $2;
    }
    | SPLITSTATS ID opt_id NL
    // usage: splitstats <analysisname> [opt|act=default]
    {
        cmdSplitStats($2, $3);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
    }
    | WKLDSTATS ID NL
    // usage: wkldstats <analysisname>
    {
        cmdWkldStats($2);
	if ($2) delete [] $2;
    }
    | PENALTYSTATS ID ID opt_id NL
    // usage: penaltystats <analysisname> <loadfile> [opt|act=default]
    {
        cmdPenaltyStats($2, $3, $4);
	if ($2) delete [] $2;
	if ($3) delete [] $3;
	if ($4) delete [] $4;
    }
    | ANLINFO ID NL
    // usage: anlinfo <analysisname>
    {
        cmdAnlInfo($2);
	if ($2) delete [] $2;
    }
    | PREDINFO ID INTCONST INTCONST NL
    // usage: predinfo <index> <subtree-root> <#levels> (internal command)
    {
        cmdPredInfo($2, $3, $4);
	if ($2) delete [] $2;
    }
    | HELP NL
    // usage: help
    {
	cmdHelp();
    }
    | error NL
    {
        yyclearin;
	yyerrok;
    }
    | NL
    ;

dump_page
    :          { $$ = (shpid_t) 0; }
    | INTCONST { $$ = (shpid_t) $1; }
    ;

opt_id
    :    { $$ = NULL; }
    | ID { $$ = $1; }
    ;

opt_k
    :          { $$ = 0; }
    | INTCONST { $$ = $1; }
    ;

opt_ioparam
    :	      { $$ = 0; }
    | IOPARAM { $$ = $1; }
    ;

%%

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


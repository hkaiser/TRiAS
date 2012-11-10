
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yylexfix.h
//  
//  FILE DESCRIPTION:     insert file to fix LEX lexer macros
//  
//  MODIFICATION HISTORY:
//  
//    12/28/98   bz/cc    added support for FLEX lexers.
//    05/05/94   bz/cc    added lex_input for Sparcworks C++ on Solaris 2.3
//    12/10/93   bz/cc    initial coding.
//
//  This header file is NOT wrapped, so that it will have its effect each
//  time it is included.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef FLEX_SCANNER

// These definitions are for FLEX

// Tie FLEX input file to the Yacc++ lexer object's input object's file.

#ifndef yyin
#define yyin	(yy_inp_getc_ptr(yy_lex_cur_obj()->yy_lex_cur_inp())->yy_inp_cur_fp())
#endif /* yyin */

#else

// These definitions work with many versions of LEX, but not all.
// input is the LEX read-a-character (i.e. shift) macro.

#undef input
#define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):\
                   getc(yy_inp_getc_ptr(yy_lex_cur_obj()->yy_lex_cur_inp())->yy_inp_cur_fp()))=='\n'?\
                  (yy_lex_cur_obj()->yy_cur_lineno()++,yytchar):yytchar\
                  )==EOF?0:yytchar)

#undef lex_input
#define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):\
                   getc(yy_inp_getc_ptr(yy_lex_cur_obj()->yy_lex_cur_inp())->yy_inp_cur_fp()))=='\n'?\
                  (yy_lex_cur_obj()->yy_cur_lineno()++,yytchar):yytchar\
                  )==EOF?0:yytchar)

// unput is the LEX un-read-a-character (i.e. discard-lookahead) macro.

#undef unput
#define unput(c) {yytchar= (c);if(yytchar=='\n') \
                      yy_lex_cur_obj()->yy_cur_lineno()--;*yysptr++=yytchar;}

// yylval is the LEX semantic value variable

#undef yylval
#define yylval  (yy_lex_cur_obj()->yy_lex_rslt())

// yywrap is the LEX end of file processing macro.
#undef yywrap

#endif /* FLEX_SCANNER */

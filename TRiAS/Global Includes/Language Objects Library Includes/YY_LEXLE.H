
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_lexle.h
//  
//  FILE DESCRIPTION:     insert file with lexer declarations for LEX lexers.
//  
//  MODIFICATION HISTORY:
//  
//    06/03/98   cc       extracted various sub-objects from the lexer object.
//    11/15/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_lexle_h_
#define yy_lexle_h_ 1

#define yy_use_lex_ 1

#include "yy_inp.h"
#include "yy_inpge.h"
#include "yy_lex.h"
#include "yy_psr.h"
#include "yy_sym.h"

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_obj_lex
//
//  FUNCTION DECLARATIONS
// 
//  yy_lex()            is a driver for the lexer engine which lexes files.
// 
//  yy_lex_ins()        is a dummy version when using LEX lexers.  Inserting
//                      text is not supported with LEX lexers.
//
//
//  LEXER OBJECT INTERNAL DATA:
// 
//  A yy_lex_obj is an object which Yacc++ uses to represent a lexer.  Each
//  lexer is independent and contains complete state information.
// 
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_obj_lex : public yy_lex_obj
{

 public:

    yy_lex_obj_lex(
        yy_inp_ptr                  yy_new_this_file_obj,
        yy_symtab_ptr               yy_new_this_symtab_obj);
        
    virtual void yy_lex();

    virtual void yy_lex_do_action(
        int                     yy_lex_action_index
        );

    void yy_lex_engine(void);

};


extern "C" {

// yywrap is the LEX end of file processing macro.
yy_boolean yywrap(
    void
    );

// yylex is the LEX lexer.
int yylex(
    void
    );

// yylook is the LEX look-ahead routine.
int yylook(
    void
    );

// yyback is the LEX backup routine.
int yyback(
    int         *p,
    int         m
    );

}
#endif /* yy_lexle_h_ */

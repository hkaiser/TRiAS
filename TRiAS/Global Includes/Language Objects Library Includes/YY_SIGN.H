
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_sign.h
// 
//  FILE DESCRIPTION:     header file with signature enumeration for
//                        signature objects used for debugging
//  
//  MODIFICATION HISTORY:
//  
//    03/27/97   bz       Removed a trailing "," in enumeration for the
//                        stricter HP ANSI aCC++ compiler on HP-UX 10.20.
//    02/26/93   bz       native C++ version created.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_sign_h_
#define yy_sign_h_

enum yy_signatures { 
    yy_freed_object_signature_,
    yy_ast_signature_,
    yy_err_signature_,
    yy_errmsg_signature_,
    yy_inp_signature_,
    yy_lex_signature_,
    yy_psr_signature_,
    yy_sym_signature_,
    yy_symtab_signature_,
    yy_syna_signature_,
    yy_synamsg_signature_
};

#endif /* yy_sign_h_ */

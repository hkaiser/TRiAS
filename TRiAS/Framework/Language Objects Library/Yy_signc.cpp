//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1994-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_signc
//
//  FILE DESCRIPTION:     signed Yacc++ object support 
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    08/24/98   cc       Solaris C++ caught missing const -> hiding on
//			  yy_psr_valid_obj().
//    05/08/98   bz       Match changes for parser memento.
//    03/27/97   bz       Oops.  Put in type specifiers as they no longer 
//                        default without a warning with the stricter 
//                        HP ANSI aCC++ compiler on HP-UX 10.20.
//    01/19/94   bz       moved all signed object support to this file.
//
//////////////////////////////////////////////////////////////////////////////

#define yy_signc_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_errst.h"
#include "yy_inpfi.h"
#include "yy_lex.h"
#include "yy_psr.h"
#include "yy_sym.h"
#include "yy_sign.h"
#include "yy_signc.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_sign_obj::yy_errmsg_sign_obj()
//
//  This is the constructor for the error message object with signatures.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_sign_obj::yy_errmsg_sign_obj() :
    yy_errmsg_cache_obj(),
    yy_signature(yy_errmsg_signature_)
{
}   // constructor for yy_errmsg_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_sign_obj::~yy_errmsg_sign_obj()
//
//  This is the destructor for the error message object with signatures.  
//  The signature field is marked as freed for detecting pointers to objects 
//  which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_sign_obj::~yy_errmsg_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_errmsg_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_errmsg_valid_obj()
//
//  yy_errmsg_valid_obj() returns true if signed error message object has a 
//  valid signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_errmsg_sign_obj::yy_errmsg_valid_obj()
{
    return(yy_signature == yy_errmsg_signature_);

}   // yy_errmsg_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_sign_obj::yy_inp_sign_obj()
//
//  This is the no argument constructor for the input file object with
//  signatures.  
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_sign_obj::yy_inp_sign_obj() :
    yy_inp_file_obj(),
    yy_signature(yy_inp_signature_)
{
}   // no argument constructor for yy_inp_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_sign_obj::yy_inp_sign_obj(yy_this_err_ptr)
//
//  This is the constructor typically used when creating an input file
//  object with signatures which is the initial input object for a given
//  lexer and parser.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_sign_obj::yy_inp_sign_obj(
    yy_err_ptr  yy_this_err_ptr
    ) :
    yy_inp_file_obj(yy_this_err_ptr),
    yy_signature(yy_inp_signature_)
{
}   // constructor for yy_inp_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   nesting constructor yy_inp_sign_obj::yy_inp_sign_obj(
//                                      yy_this_inp_ptr)
//
//  This is the constructor for the input file object with signature field
//  whose parameter list is a pointer to an input object.  This constructor
//  is typically used when creating a signed input file object which is used
//  to process a file input nested within another input (an include file).
//
//  This constructor creates a new input file object with signature field
//  which becomes the top input object on the stack.  The new input object
//  is associated with the same lexer and error object as "yy_this_inp_ptr"
//  which is now the previous entry on the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_sign_obj::yy_inp_sign_obj(
    yy_inp_ptr  yy_this_inp_ptr
    ) :
    yy_inp_file_obj(yy_this_inp_ptr),
    yy_signature(yy_inp_signature_)
{
}   // nesting constructor for yy_inp_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_inp_sign_obj::~yy_inp_sign_obj()
//
//  This is the destructor for the input file object with signatures.  
//  The signature field is marked as freed for detecting pointers to 
//  objects which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_sign_obj::~yy_inp_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_inp_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_valid_obj()
//
//  yy_inp_valid_obj() returns true if the signed input file object has a
//  valid signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_sign_obj::yy_inp_valid_obj()
{
    return(yy_signature == yy_inp_signature_);

}   // yy_inp_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_sign_obj::yy_lex_sign_obj(...)
//
//  This is the constructor for the signed lexer object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_sign_obj::yy_lex_sign_obj(
    int                         yy_new_lex_min_type,
    int                         yy_new_lex_max_type,
    int                         *yy_new_lex_cmd,
    yy_inp_ptr                  yy_new_this_inp_obj,
    yy_symtab_ptr               yy_new_this_symtab_obj,
    int                         *yy_new_lex_start_state,
    int                         yy_new_lex_max_class,
    int                         yy_new_lex_class
    ) : 
    yy_lex_obj(
        yy_new_lex_min_type,
        yy_new_lex_max_type,
	yy_new_lex_cmd,
        yy_new_this_inp_obj,
        yy_new_this_symtab_obj,
        yy_new_lex_start_state,
        yy_new_lex_max_class,
        yy_new_lex_class),
    yy_signature(yy_lex_signature_)
{
}   // constructor for yy_lex_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_sign_obj::~yy_lex_sign_obj()
//
//  This is the destructor for the lexer object with signatures.  
//  The signature field is marked as freed for detecting pointers to 
//  objects which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_sign_obj::~yy_lex_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_lex_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_lex_valid_obj()
//
//  yy_lex_valid_obj() returns true if the signed lexer object has a
//  valid signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_lex_sign_obj::yy_lex_valid_obj()
{
    return(yy_signature == yy_lex_signature_);

}   // yy_lex_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_sign_obj::yy_psr_sign_obj(...)
//
//  This is the constructor for the signed parser object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_sign_obj::yy_psr_sign_obj(
    yy_boolean                  yy_new_psr_abort_on_error,
    int                         yy_new_psr_min_type,
    int                         yy_new_psr_max_type,
    int                         yy_new_psr_tkn_max_type,
    yy_lex_ptr                  yy_new_lex_obj,
    int                         yy_new_psr_num_states,
    int                         *yy_new_psr_cmd,
    int                         *yy_new_syna,
    char                        **yy_new_spelling_tbl,
    yy_psr_start_state_tbl      *yy_new_psr_start_state,
    int                         *yy_new_psr_last_start,
    const yy_ref_factory_obj    &yy_new_ref_factory,
    int                         yy_new_psr_max_class,
    int                         yy_new_psr_left_max,
    int                         yy_new_psr_rt_max,
    int                         yy_new_psr_rdc_max
    ) : 
    yy_psr_obj(
        yy_new_psr_abort_on_error,
        yy_new_psr_min_type,
        yy_new_psr_max_type,
        yy_new_psr_tkn_max_type,
        yy_new_lex_obj,
        yy_new_psr_num_states,
	yy_new_psr_cmd,
        yy_new_syna,
        yy_new_spelling_tbl,
        yy_new_psr_start_state,
        yy_new_psr_last_start,
	yy_new_ref_factory,
        yy_new_psr_max_class,
        yy_new_psr_left_max,
        yy_new_psr_rt_max,
        yy_new_psr_rdc_max),
    yy_signature(yy_psr_signature_)
{
}   // constructor for yy_psr_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_sign_obj::~yy_psr_sign_obj()
//
//  This is the destructor for the parser object with signatures.  
//  The signature field is marked as freed for detecting pointers to 
//  objects which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_sign_obj::~yy_psr_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_psr_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_valid_obj()
//
//  yy_psr_valid_obj() returns true if the signed parser object has a
//  valid signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_psr_sign_obj::yy_psr_valid_obj(void) const
{
    return(yy_signature == yy_psr_signature_);

}   // yy_psr_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_symtab_sign_obj::yy_symtab_sign_obj()
//
//  This is the constructor for the symbol table object with signatures.
//
//////////////////////////////////////////////////////////////////////////////

yy_symtab_sign_obj::yy_symtab_sign_obj() :
    yy_symtab_dflt_obj(),
    yy_signature(yy_symtab_signature_)
{
}   // constructor for yy_symtab_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_symtab_sign_obj::~yy_symtab_sign_obj()
//
//  This is the destructor for the symbol table object with signatures.  The
//  signature field is marked as freed for detecting pointers to objects 
//  which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_symtab_sign_obj::~yy_symtab_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_symtab_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_dflt_ptr yy_new_sym_obj(...)
//
//  yy_new_sym_obj() creates a new signed symbol object in the symbol table.  
//  Since the lookup functions add symbols by to the symbol table by calling
//  this function instead of directly calling new, we didn't need to redefine
//  the lookup functions.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_dflt_ptr yy_symtab_sign_obj::yy_new_sym_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        )
{
    yy_sym_dflt_ptr new_sym_ptr = new yy_sym_sign_obj(
            yy_new_next_ptr,
            yy_new_str_ptr,
            yy_new_len,
            yy_new_tkn_type,
            yy_new_type,
            yy_new_flags
            );

    if (new_sym_ptr == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        }

    return (new_sym_ptr);

}   // yy_new_sym_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_symtab_valid_obj()
//
//  yy_symtab_valid_obj() returns true if signed symbol table object has a
//  valid signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_symtab_sign_obj::yy_symtab_valid_obj()
{
    return(yy_signature == yy_symtab_signature_);

}   // yy_symtab_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_sign_obj::yy_sym_sign_obj()
//
//  This is the no argument constructor for the symbol object with signatures.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_sign_obj::yy_sym_sign_obj() :
    yy_sym_dflt_obj(),
    yy_signature(yy_sym_signature_)
{
}   // constructor for yy_sym_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_sign_obj::yy_sym_sign_obj(...)
//
//  This is the constructor for the symbol object with signature field
//  whose parameter list corresponds to the fields in the symbol object.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_sign_obj::yy_sym_sign_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
    ) :
    yy_sym_dflt_obj(
        yy_new_next_ptr,
        yy_new_str_ptr,
        yy_new_len,
        yy_new_tkn_type,
        yy_new_type,
        yy_new_flags),
    yy_signature(yy_sym_signature_)
{
}   // constructor for yy_sym_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_sign_obj::~yy_sym_sign_obj()
//
//  This is the destructor for the symbol object with signatures.  The
//  signature field is marked as freed for detecting pointers to objects
//  which have already been destroyed.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_sign_obj::~yy_sym_sign_obj()
{
    yy_signature = yy_freed_object_signature_;

}   // destructor for yy_sym_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_sym_valid_obj()
//
//  yy_sym_valid_obj() returns true if the signed symbol object has a valid 
//  signature data member.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_sym_sign_obj::yy_sym_valid_obj()
{
    return(yy_signature == yy_sym_signature_);

}   // yy_sym_valid_obj

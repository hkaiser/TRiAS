
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1994, Compiler Resources, Inc.
//
//  FILENAME:             yy_signc.h
// 
//  FILE DESCRIPTION:     header file with signed class declarations for
//                        Yacc++ objects
//  
//  CLASS HIERARCHY:
//
//  The signature classes are objects with signature fields for debugging.
//  See appropriate header files for class hierarchy diagrams.  For example,
//  for symbol class hierarchy, see "yy_sym.h", for file input class 
//  hierarchy, see "yy_inpfi.h", etc.
//
//  MODIFICATION HISTORY:
//  
//    08/24/98   cc       Solaris C++ caught missing const -> hiding on
//			  yy_psr_valid_obj().
//    05/08/98   bz       Match changes for parser memento.
//    01/19/94   bz       moved all signed class declarations to this file.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_signc_h_
#define yy_signc_h_

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_errst.h"
#include "yy_inp.h"
#include "yy_lex.h"
#include "yy_psr.h"
#include "yy_trace.h"
#include "yy_sign.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_err_sign_ptr      is a typedef which defines a pointer to an error
//                       reporting object with signatures.
//
//  yy_errmsg_sign_ptr   is a typedef which defines a pointer to an error
//                       message object with signatures.
//
//  yy_inp_sign_ptr      is a typedef which defines a pointer to a signed
//                       input file object.
//
//  yy_sym_sign_ptr      is a typedef which defines a pointer to a symbol
//                       using the implementation with signatures.
//
//  yy_symtab_sign_ptr   is a typedef which defines a pointer to a symbol
//                       table using the implementation with signatures.
//
//  yy_syna_msg_sign_ptr 
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_err_sign_obj     *yy_err_sign_ptr;
typedef class yy_export yy_errmsg_sign_obj  *yy_errmsg_sign_ptr;
typedef class yy_export yy_inp_sign_obj     *yy_inp_sign_ptr;
typedef class yy_export yy_lex_sign_obj     *yy_lex_sign_ptr;
typedef class yy_export yy_psr_sign_obj     *yy_psr_sign_ptr;
typedef class yy_export yy_sym_sign_obj     *yy_sym_sign_ptr;
typedef class yy_export yy_symtab_sign_obj  *yy_symtab_sign_ptr;
typedef class yy_export yy_synamsg_sign_obj *yy_synamsg_sign_ptr;


//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_errmsg_sign_obj 
// 
//  The yy_errmsg_sign_obj is the error message object class with a
//  signature data member.  A signature field is a debugging aid.  It
//  provides runtime-type-identification.  At object creation, an 
//  identifying number for this type of object is stored in the signature
//  field.  In this way the value can be checked at any time to assure that
//  the pointer is referencing an object of the expected type.
// 
//  The default Yacc++ objects are created without signature fields.  
//
//  PUBLIC FUNCTIONS:
//
//  yy_errmsg_sign_obj()            constructor for a error message object
//                                  with signatures.
//                                  
//  ~yy_errmsg_sign_obj()           destructor for a error message object
//                                  with signatures.
//
//  yy_errmsg_valid_obj()           returns true if signed error message 
//                                  object has a valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_errmsg_sign_obj : public yy_errmsg_cache_obj {

 public:

    yy_errmsg_sign_obj();
        
    virtual ~yy_errmsg_sign_obj();

    virtual yy_boolean yy_errmsg_valid_obj();
    
 protected:

    int                 yy_signature;

    };  // yy_errmsg_sign_obj



//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_sign_obj
//
//  The yy_inp_sign_obj is the input file object with a signature data member.
//
//  PUBLIC FUNCTIONS:
//
//  yy_inp_sign_obj()         constructors for an input file object with
//                            signatures.
//                                  
//  ~yy_inp_sign_obj()        destructor for an input file object with
//                            signatures.
//
//  yy_inp_valid_obj()        returns true if signed input file object
//                            has a valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_sign_obj : public yy_inp_file_obj {
    
 public:

    yy_inp_sign_obj();

    yy_inp_sign_obj(yy_err_ptr yy_this_err_ptr);

    yy_inp_sign_obj(yy_inp_ptr yy_this_inp_ptr);

    virtual ~yy_inp_sign_obj();

    virtual yy_boolean yy_inp_valid_obj();
 
 protected:

    int                 yy_signature; 
    
    };  // yy_inp_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_sign_obj
//
//  The yy_lex_sign_obj is the lexer object with a signature data member.
//
//  PUBLIC FUNCTIONS:
//
//  yy_lex_sign_obj()         constructors for a lexer object with signatures.
//                                  
//  ~yy_lex_sign_obj()        destructor for a lexer object with signatures.
//
//  yy_lex_valid_obj()        returns true if signed lexer object has a
//                            valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_sign_obj : public yy_lex_obj {
    
 public:

    yy_lex_sign_obj();

    yy_lex_sign_obj(
        int                         yy_new_lex_min_type,
        int                         yy_new_lex_max_type,
        int                         *yy_new_lex_cmd,
        yy_inp_ptr                  yy_new_this_inp_obj,
        yy_symtab_ptr               yy_new_this_symtab_obj,
        int                         *yy_new_lex_start_state,
        int                         yy_new_lex_max_class,
        int                         yy_new_lex_class);
    
    virtual ~yy_lex_sign_obj();

    virtual yy_boolean yy_lex_valid_obj();
 
 protected:

    int                 yy_signature; 
    
    };  // yy_lex_sign_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_sign_obj
//
//  The yy_psr_sign_obj is the parser object with a signature data member.
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_sign_obj()       constructors for a parser object with signatures.
//                          
//                                  
//  ~yy_psr_sign_obj()      destructor for a parser object with signatures.
//
//  yy_psr_valid_obj()      returns true if signed parser object has a
//                          valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_sign_obj : public yy_psr_obj {
    
 public:

    yy_psr_sign_obj();

    yy_psr_sign_obj(
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
        );
    
    virtual ~yy_psr_sign_obj();

    virtual yy_boolean yy_psr_valid_obj(void) const;
 
 protected:

    int                 yy_signature; 
    
    };  // yy_psr_sign_obj


//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_sym_sign_obj 
// 
//  The yy_sym_sign_obj is the symbol table object class with a signature
//  data member.  A signature field is a debugging aid.  It provides 
//  runtime-type-identification.  At object creation, an identifying number
//  for this type of object is stored in the signature field.  In this way
//  the value can be checked at any time to assure that the pointer is 
//  referencing an object of the expected type.
// 
//  The default Yacc++ objects are created without signature fields.  
//
//  PUBLIC FUNCTIONS:
//
//  yy_sym_sign_obj()            constructor for a symbol object with
//                               signatures.
//                                  
//  ~yy_sym_sign_obj()           destructor for a symbol object with
//                               signatures.
//
//  yy_sym_valid_obj()           returns true if signed symbol object
//                               has a valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_sym_sign_obj : public yy_sym_dflt_obj {

 public:
 
    yy_sym_sign_obj();
    
    yy_sym_sign_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        );

    virtual ~yy_sym_sign_obj();

    virtual yy_boolean yy_sym_valid_obj();
        
 protected:
 
    int                 yy_signature;
    
    };  // yy_sym_sign_obj
    

//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_symtab_sign_obj 
// 
//  The yy_symtab_sign_obj is the symbol table object class with a
//  signature data member.  A signature field is a debugging aid.  It
//  provides runtime-type-identification.  At object creation, an 
//  identifying number for this type of object is stored in the signature
//  field.  In this way the value can be checked at any time to assure that
//  the pointer is referencing an object of the expected type.
// 
//  The default Yacc++ objects are created without signature fields.  
//
//  PUBLIC FUNCTIONS:
//
//  yy_symtab_sign_obj()            constructor for a symbol table object
//                                  with signatures.
//                                  
//  ~yy_symtab_sign_obj()           destructor for a symbol table object
//                                  with signatures.
//
//  yy_symtab_valid_obj()           returns true if signed symbol table 
//                                  object has a valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_symtab_sign_obj : public yy_symtab_dflt_obj {

 public:

    yy_symtab_sign_obj();
        
    virtual ~yy_symtab_sign_obj();

    virtual yy_boolean yy_symtab_valid_obj();
    
 protected:

    virtual yy_sym_dflt_ptr yy_new_sym_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        );
        
    int                 yy_signature;

    
    };  // yy_symtab_sign_obj

    
//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_synamsg_sign_obj 
// 
//  The yy_synamsg_sign_obj is the error message object class with a
//  signature data member.  A signature field is a debugging aid.  It
//  provides runtime-type-identification.  At object creation, an 
//  identifying number for this type of object is stored in the signature
//  field.  In this way the value can be checked at any time to assure that
//  the pointer is referencing an object of the expected type.
// 
//  The default Yacc++ objects are created without signature fields.  
//
//  PUBLIC FUNCTIONS:
//
//  yy_synamsg_sign_obj()            constructor for a error message object
//                                  with signatures.
//                                  
//  ~yy_synamsg_sign_obj()           destructor for a error message object
//                                  with signatures.
//
//  yy_synamsg_valid_obj()           returns true if signed error message 
//                                  object has a valid signature data member.
//
//  INTERNAL STATE:  
//
//  yy_signature        is the object type signature field.  This is a form
//                      of runtime-type-identification and can aid in 
//                      detecting pointer problems or can be used for 
//                      typesafe casting.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_synamsg_sign_obj : public yy_synamsg_cache_obj {

 public:

    yy_synamsg_sign_obj();
        
    virtual ~yy_synamsg_sign_obj();

    virtual yy_boolean yy_synamsg_valid_obj();
    
 protected:

    int                 yy_signature;

    };  // yy_synamsg_sign_obj


#endif /* yy_signc_h_ */

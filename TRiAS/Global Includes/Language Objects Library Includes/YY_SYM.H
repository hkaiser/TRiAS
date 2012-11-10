
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_sym.h
// 
//  FILE DESCRIPTION:     header file with symbol table object and
//                        symbol object class declarations
//  
//  CLASS HIERARCHY:
//
//    +------------------------+       +------------------------+
//    |      symbol table      |  -->  |        symbol          |
//    |  abstract base class   |       |  abstract base class   |
//    +------------------------+       +------------------------+
//               | derives                        | derives
//    +------------------------+       +------------------------+
//    |     symbol table       |  -->  |        symbol          |
//    | default implementation |       | default implementation |
//    +------------------------+       +------------------------+
//               | derives                        | derives
//    +------------------------+       +------------------------+
//    |     symbol table       |  -->  |        symbol          |
//    |    with signatures     |       |    with signatures     |
//    |    (see yy_signc.h)    |       |    (see yy_signc.h)    |   
//    +------------------------+       +------------------------+
//
//  The symbol table class and the symbol class define the abstractions
//  for symbol manipulation.  Symbol table objects contain symbol objects.
//
//  The abstract base classes define the interface used by other parts
//  of the Language Objects Library.  If you are using your own symbol
//  table, you need to define an interface matching the abstract base
//  classes. 
//
//  Objects of the default implementation classes are created in yy_main.cxx
//  in the Language Objects Library.  To use your own classes, replace
//  the object creation calls in yy_main.cxx.
//  
//  MODIFICATION HISTORY:
//  
//    08/19/97   bz       added overloaded yy_symtab_install_kw() to allow
//                        for the possibility of initial yy_type values.
//    10/14/93   bz       added include of yy_stdio.h for NULL.
//    04/13/93   bz       change dumps now that native C++ rewrite of error
//                        object is completed.  Some name changes to parms
//                        to match yy_sym.cpp.
//    03/31/93   bz       added yy_symtab_remove_sym().
//    03/22/93   bz       added yy_export for use of classes in a DLL.
//    03/15/93   bz       fixed get/set name inconsistency on yy_sym_next.
//    02/26/93   bz       consolidated yy_sym.h, yy_sym1.h, and yy_sym2.h
//                        into this one yy_sym.h header.  Numerous changes 
//                        for native C++ version.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_sym_h_
#define yy_sym_h_

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_trace.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_sym_ptr           is a typedef which defines a pointer to a symbol.
//                       (This references the abstract base class).
// 
//  yy_symtab_ptr        is a typedef which defines a pointer to a symbol
//                       table.  (This references the abstract base class).
//
//  yy_sym_dflt_ptr      is a typedef which defines a pointer to a symbol
//                       using the default implementation.
//
//  yy_symtab_dflt_ptr   is a typedef which defines a pointer to a symbol
//                       table using the default implementation.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_sym_obj            *yy_sym_ptr;
typedef class yy_export yy_symtab_obj         *yy_symtab_ptr;

typedef class yy_export yy_sym_dflt_obj       *yy_sym_dflt_ptr;
typedef class yy_export yy_symtab_dflt_obj    *yy_symtab_dflt_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_symtab_obj
//
//  The yy_symtab_obj is the abstract base class for the symbol table
//  object.  It represents the interface of the entire symbol table of 
//  symbol objects and is associated with a lexer object.  If you are
//  replacing the symbol table at the most fundamental level, this class
//  provides the minimal interface which you must support.
//
//  You need to create a symbol table object before you create a lexer
//  object.  The lexer object installs its keywords using the install
//  keyword function.  User action code in the lexer will call the various
//  lookup functions to add and query the symbol table.
//      
//  PUBLIC FUNCTIONS:
//
//  ~yy_symtab_obj()        destructor for a symbol table object.
//
//  yy_symtab_dmp()         dumps the contents of a symbol table object.
//
//  yy_symtab_insensitive_kws([yy_boolean])
//                          gets (or sets with an argument) whether the symbol
//                          table allows case insensitive keywords.  Lexer 
//                          objects which have keywords call the form with
//                          an argument.
//
//  yy_symtab_install_kw()  installs a keyword symbol.  This is used by
//                          lexer objects which have keywords.
//
//  yy_symtab_lookup()      performs a table lookup for a symbol and adds
//                          the symbol if it doesn't exist.  This lookup is
//                          always case sensitive.
//
//  yy_symtab_lookup_kw()   performs a table lookup for a symbol and adds
//                          the symbol if it doesn't exist.  This lookup 
//                          supports case insensitive keywords.
//
//  yy_symtab_lookup_only() performs a table lookup for an existing symbol.
//                          It returns NULL if the symbol doesn't exist.
//                          This lookup is always case sensitive.
//
//  yy_symtab_lookup_only_kw() performs a table lookup for an existing symbol.
//                          It returns NULL if the symbol doesn't exist.
//                          This lookup supports case insensitive keywords.
//
//  yy_symtab_remove_sym()  removes the reference to a symbol object in the
//                          symbol table and then deletes it.
//
//  yy_symtab_valid_obj()   supports yy_symtab_valid_ptr(symtab_ptr) by 
//                          returning TRUE for a valid symbol table object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_symtab_obj {

 public:

    virtual ~yy_symtab_obj() {}

    virtual void yy_symtab_dmp(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dmp_title) = 0;

    virtual yy_boolean yy_symtab_insensitive_kws() = 0;

    virtual yy_boolean yy_symtab_insensitive_kws(yy_boolean) = 0;

    virtual yy_sym_ptr yy_symtab_install_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type,
        yy_boolean          yy_case_sensitive
        ) = 0;

    virtual yy_sym_ptr yy_symtab_install_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type,
        yy_boolean          yy_case_sensitive,
        int                 yy_type
        ) = 0;

    virtual yy_sym_ptr yy_symtab_lookup(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        ) = 0;

    virtual yy_sym_ptr yy_symtab_lookup_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        ) = 0;

    virtual yy_sym_ptr yy_symtab_lookup_only(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        ) = 0;

    virtual yy_sym_ptr yy_symtab_lookup_only_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        ) = 0;

    virtual yy_boolean yy_symtab_remove_sym(
        yy_sym_ptr      yy_this_sym
        ) = 0;

    virtual yy_boolean yy_symtab_valid_obj() 
        { return(yy_true); }
        
    };  // yy_symtab_obj

    
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_symtab_valid_ptr(yy_this_symtab)
//
//  yy_symtab_valid_ptr checks the validity of a pointer to a yy_symtab_obj.
//  Before calling the virtual function in the symbol table object which
//  performs the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_symtab_valid_ptr(yy_symtab_ptr  yy_this_symtab)
{
   if (yy_this_symtab != NULL) {
      return(yy_this_symtab->yy_symtab_valid_obj());       
      }
   else {
      return(yy_false);
      }
   
}  // yy_symtab_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_sym_obj
//
//  The yy_sym_obj is the abstract base class for the symbol object.  
//  It represents a token in the grammar whose spelling is significant.  
//  For example, an identifier or keyword name.
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_sym_obj()       destructor for a symbol object.
//
//  yy_sym_dmp()        dumps the contents of a symbol object.
//
//  yy_sym_flags([int]) gets (or sets with an argument) the simple attribute 
//                      bits of the symbol.
//
//  yy_sym_len([int])   gets (or sets with an argument) the length of the 
//                      spelling of the symbol.
//
//  yy_sym_str([char *])
//                      gets (or sets with an argument) the spelling of the
//                      symbol.  
//
//                      Note that you must make a copy of your string with
//                      new before doing a set call.  The reason is the 
//                      destructor will delete this string when deleting the
//                      symbol object.
//
//  yy_sym_tkn_type([int])
//                      gets (or sets with an argument) the syntactic type of 
//                      the symbol.
//
//  yy_sym_type([int])  gets (or sets with an argument) the semantic type of 
//                      the symbol.
//
//  yy_sym_valid_obj()  supports yy_sym_valid_ptr(sym_ptr) by returning TRUE
//                      for a valid symbol object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_sym_obj {

 public:

    virtual ~yy_sym_obj() {}

    virtual void yy_sym_dmp(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dmp_title) = 0;

    virtual int yy_sym_flags() = 0;

    virtual int yy_sym_flags(int yy_new_flags) = 0;

    virtual int yy_sym_len() = 0;

    virtual int yy_sym_len(int yy_new_len) = 0;

    virtual const char *yy_sym_str() = 0;
        
    virtual const char *yy_sym_str(char *yy_new_str_ptr) = 0;

    virtual int yy_sym_tkn_type() = 0;

    virtual int yy_sym_tkn_type(int yy_new_tkn_type) = 0;
 
    virtual int yy_sym_type() = 0;

    virtual int yy_sym_type(int yy_new_type) = 0;

    virtual yy_boolean yy_sym_valid_obj()
        { return(yy_true); }

    };  // yy_sym_obj

    
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_sym_valid_ptr(yy_this_sym)
//
//  yy_sym_valid_ptr checks the validity of a pointer to a yy_sym_obj.
//  Before calling the virtual function in the symbol table object which
//  performs the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_sym_valid_ptr(yy_sym_ptr  yy_this_sym)
{
   if (yy_this_sym != NULL) {
      return(yy_this_sym->yy_sym_valid_obj());       
      }
   else {
      return(yy_false);
      }
   
}  // yy_sym_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_symtab_dflt_obj
//
//  The yy_symtab_dflt_obj is the default implementation class for the Yacc++
//  symbol table object.  It represents an entire symbol table of symbol 
//  objects and is associated with a lexer object.
//
//  A yy_symtab_dflt_obj is the symbol table object the Language Objects 
//  Library provides as its default.  It is derived from the abstract base
//  symbol table object. 
//
//  CONFIGURATION CONSTANTS:
//
//  yy_hash_max_ix_     is the size of the hash table in the symbol table.
//                      This constant can be sized down if you are trying
//                      to reduce space.
//   
//  PUBLIC FUNCTIONS:
//
//  yy_symtab_dflt_obj()            no argument constructor for the default 
//                                  implementation of a symbol table object.
//                                  
//  ~yy_symtab_dflt_obj()           destructor for a default symbol table 
//                                  object.
//                                  
//  INTERNAL STATE:  
//
//  yy_hash_tbl                     is the hash table.
//
//  yy_symtab_has_insensitive_kws   is a flag which indicates whether this
//                                  symbol table has any insensitive keyword
//                                  symbol objects.  
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_symtab_dflt_obj : public yy_symtab_obj {

 public:

    yy_symtab_dflt_obj();
        
    virtual ~yy_symtab_dflt_obj();

    virtual void yy_symtab_dmp(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dmp_title);

    virtual yy_boolean yy_symtab_insensitive_kws() 
        { return(yy_symtab_has_insensitive_kws); }

    virtual yy_boolean yy_symtab_insensitive_kws(yy_boolean yy_new_value) 
        { return(yy_symtab_has_insensitive_kws = yy_new_value); }

    virtual yy_sym_ptr yy_symtab_install_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type,
        yy_boolean          yy_case_sensitive
        );

    virtual yy_sym_ptr yy_symtab_install_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type,
        yy_boolean          yy_case_sensitive,
        int                 yy_type
        );

    virtual yy_sym_ptr yy_symtab_lookup(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type
        );

    virtual yy_sym_ptr yy_symtab_lookup_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type
        );

    virtual yy_sym_ptr yy_symtab_lookup_only(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type
        );

    virtual yy_sym_ptr yy_symtab_lookup_only_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_tkn_type
        );

    virtual yy_boolean yy_symtab_remove_sym(
        yy_sym_ptr      yy_this_sym
        );

 protected:

    enum yy_hash_max_ix_enum { yy_hash_max_ix_ = 8191 };

    virtual yy_sym_dflt_ptr yy_new_sym_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        );
        
    virtual int yy_hash_str(
        const char       *yy_text_ptr,
        int              yy_len
        );
        
    yy_boolean           yy_symtab_has_insensitive_kws;
    yy_sym_dflt_ptr      yy_hash_tbl[yy_hash_max_ix_];

    };  // yy_symtab_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_sym_dflt_obj
//
//  The yy_sym_dflt_obj is the default implementation class for the Yacc++ 
//  symbol object.  A symbol object represents a token in the grammar whose 
//  spelling is significant.  For example, an identifier or keyword name.
//
//  A yy_sym_dflt_obj is the symbol object the Language Objects Library 
//  provides as its default.  It is derived from the abstract base symbol 
//  object.  If you need additional members, you can derive your own symbol
//  object from either this or the abstract base symbol object.
//
//  CONFIGURATION CONSTANTS:
//
//  yy_sym_tkn_type_init_ is the initial value for the yy_tkn_type data
//                      member of a default symbol object whose syntactic
//                      type is not yet known.  A later call to 
//                      yy_symtab_lookup or yy_symtab_lookup_kw with the
//                      same spelling can override this type and change 
//                      the yy_tkn_type field to the appropriate type.
//                      
//  yy_sym_type_init_   is the initial value for the yy_type data member of
//                      a default symbol object.  
//
//  yy_sym_case_insensitive_  is the yy_flags given to a newly created
//                      default symbol object for a case insensitive keyword.
//
//  PUBLIC FUNCTIONS:
//
//  yy_sym_dflt_obj()   no argument constructor for the default implementation
//                      of a symbol object.  This constructor fills in a 
//                      default symbol object with the default values for all
//                      of the members.
//
//  yy_sym_dflt_obj([...])  
//                      complete constructor which fills in a symbol object
//                      with the exact values given in the argument list.  
//                      This constructor is used by the default symbol table 
//                      object when adding symbols to the table.
//
//  ~yy_sym_dflt_obj()  destructor for a default symbol object.
//
//  yy_sym_next([yy_sym_ptr])   
//                      gets (or sets with an argument) the yy_next_ptr of 
//                      the symbol.
//
//  INTERNAL STATE:  
//  
//  yy_next_ptr         is a pointer to another symbol object that hashed to 
//                      this entry.  This can be a different spelling which 
//                      collided, or it can be the same spelling but a 
//                      different type or scope.
//
//  yy_str_ptr          is the starting point of spelling.
//  
//  yy_len              is the length of the spelling.
//  
//  yy_tkn_type         is the syntactic type field.
//                      The syntactic type field is used to support keyword
//                      processing.
//
//  yy_type             is the semantic type field.  For example, a variable
//                      may have a syntactic type of identifier and its 
//                      semantic type may be char, float, or integer.  This 
//                      field is for application manipulation.
//
//  yy_flags            is a set of bits to represent simple flags for
//                      yy_boolean attributes (such as whether the symbol is
//                      referenced).  This field is for client manipulation.  
//
//  Note:               The built-in keyword processing uses the lower order
//                      bit to indicate whether they are case insensitive (1)
//                      or sensitive (0).  The bit used can be changed by 
//                      redefining the value of the manifest constant 
//                      yy_sym_case_insensitive_.  The flags field is
//                      required to support keyword processing.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_sym_dflt_obj : public yy_sym_obj {

 public:
 
    enum yy_sym_tkn_type_enum { yy_sym_tkn_type_init_ = 0 };

    enum yy_sym_type_enum { yy_sym_type_init_ = 0 };

    enum yy_sym_flags_enum { yy_sym_case_insensitive_ = 1 };

    yy_sym_dflt_obj();
    
    yy_sym_dflt_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        );
    
    virtual ~yy_sym_dflt_obj();

    virtual void yy_sym_dmp(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dmp_title);

    virtual int yy_sym_flags()                         
        { return(yy_flags); }

    virtual int yy_sym_flags(int yy_new_flags)                         
        { return(yy_flags = yy_new_flags); }

    virtual int yy_sym_len()
        { return(yy_len); }

    virtual int yy_sym_len(int yy_new_len)
        { return(yy_len = yy_new_len); }

    virtual yy_sym_dflt_ptr yy_sym_next()
        { return(yy_next_ptr); }

    virtual yy_sym_ptr yy_sym_next(yy_sym_dflt_ptr yy_new_next_ptr)
        { return(yy_next_ptr = yy_new_next_ptr); }

    virtual const char *yy_sym_str()
        { return(yy_str_ptr); }
        
    virtual const char *yy_sym_str(char *yy_new_str_ptr)
        { return(yy_str_ptr = yy_new_str_ptr); }

    virtual int yy_sym_tkn_type()
        { return(yy_tkn_type); }

    virtual int yy_sym_tkn_type(int yy_new_tkn_type)
        { return(yy_tkn_type = yy_new_tkn_type); }
 
    virtual int yy_sym_type()
        { return(yy_type); }

    virtual int yy_sym_type(int yy_new_type)
        { return(yy_type = yy_new_type); }

 protected:

    yy_sym_dflt_ptr       yy_next_ptr;
    char                  *yy_str_ptr;
    int                   yy_len;
    int                   yy_tkn_type;
    int                   yy_type;
    int                   yy_flags;
    };  // yy_sym_dflt_obj

    
//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_lookup           ==> calls yy_symtab_lookup
//
//  yy_lookup_kw        ==> calls yy_symtab_lookup_kw
//   
//////////////////////////////////////////////////////////////////////////////

#define yy_lookup       yy_symtab_lookup
#define yy_lookup_kw    yy_symtab_lookup_kw

#endif /* yy_sym_h_ */

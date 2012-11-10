
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_sym
//
//  FILE DESCRIPTION:     symbol and symbol table object support 
//
//  MODIFICATION HISTORY:
//
//    12/21/98   bz       fixed return value on yy_symtab_remove_sym to a
//			  yy_boolean from a NULL pointer.
//    08/19/97   bz       added overloaded yy_symtab_install_kw() to allow
//                        for the possibility of initial yy_type values
//                        and make sure we copy the yy_type and flag fields
//                        on keyword lookups.
//    07/28/97   bz/cc    added yy_tolower_ok_ to use tolower() in place
//			  of explicit ASCII character tests which were not
//                        portable for environments such as EBCDIC.
//    04/13/93   bz       change dumps now that native C++ rewrite of error
//                        object is completed.  Some name changes to parms
//                        to match yy_sym.h.  Return after assertion failures.
//    03/31/93   bz       added yy_symtab_remove_sym().
//    02/26/93   bz       native C++ rewrite of the symbol table and symbol
//                        object.  This file consolidates what was formerly
//                        yy_sym.cpp, yy_sym1.cpp, yy_sym2.cpp, yy_sym3.cpp,
//                        yy_hash.cpp, yy_lkp.cpp, and yy_lkpk.cpp.  
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_sym_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_ctype.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_sym.h"

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_symtab_dflt_obj::yy_symtab_dflt_obj()
//
//  This is the constructor for the default implementation symbol table 
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_symtab_dflt_obj::yy_symtab_dflt_obj() :
    yy_symtab_has_insensitive_kws(yy_false)
{
    int         i;

    for (i = 0; i < yy_hash_max_ix_; ++i) {
        yy_hash_tbl[i] = NULL;
        }

}  // constructor for yy_symtab_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_symtab_dflt_obj::~yy_symtab_dflt_obj()
//
//  This is the destructor for the default implementation symbol table object.
//
//////////////////////////////////////////////////////////////////////////////

yy_symtab_dflt_obj::~yy_symtab_dflt_obj()
{
    int                i;
    yy_sym_dflt_ptr    sym_to_free, next_sym;

    for (i = 0; i < yy_hash_max_ix_; ++i) {
        sym_to_free = yy_hash_tbl[i];
        while (sym_to_free != NULL) {
            next_sym = sym_to_free -> yy_sym_next();
            delete sym_to_free;
            sym_to_free = next_sym;
            }
        }

}   // destructor for yy_symtab_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_dflt_ptr yy_new_sym_obj(...)
//
//  yy_new_sym_obj() creates a new symbol object in the symbol table.  It
//  is used by the lookup functions when adding a symbol to the symbol
//  table instead of directly calling new.  This allows derived classes
//  to add new data members to the symbol object without redefining the 
//  lookup functions.  Simply redefine this function in your derived
//  symbol table object to call the constructor for your derived symbol 
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_dflt_ptr yy_symtab_dflt_obj::yy_new_sym_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
        )
{
    yy_sym_dflt_ptr new_sym_ptr = new yy_sym_dflt_obj(
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
//  FUNCTION:   void yy_symtab_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_symtab_dmp() displays the values of the entire symbol table object.  It
//  is a debugging function we used when developing Yacc++.  We have included
//  this function as a member of the symbol table object in case you need
//  to dump the internal state of the symbol table.
//
//  yy_this_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title  a character string to identify the dump.  For example, 
//                sometimes you might want to identify your symbol table dump
//                with the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

void yy_symtab_dflt_obj::yy_symtab_dmp(
    yy_err_ptr yy_this_err_obj,
    const char *yy_dmp_title)
{
    yy_sym_dflt_ptr sym_to_dump;
    int             i;

    if (yy_dmp_title != NULL) {
        yy_this_err_obj -> yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

    yy_this_err_obj -> yy_err_puts(" dump of all symbols in symbol table\n");

    for (i = 0; i < yy_hash_max_ix_; ++i) {
        sym_to_dump = yy_hash_tbl[i];
        while (sym_to_dump != NULL) {
            sym_to_dump -> yy_sym_dmp(yy_this_err_obj, NULL);
            sym_to_dump = sym_to_dump -> yy_sym_next();
            }
        }

    yy_this_err_obj -> yy_err_puts("dump completed.\n");

}   // yy_symtab_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS:   yy_sym_ptr yy_symtab_install_kw(yy_text_ptr, yy_len, 
//                  yy_tkn_type, yy_case_sensitive)
// 
//               yy_sym_ptr yy_symtab_install_kw(yy_text_ptr, yy_len, 
//                  yy_tkn_type, yy_case_sensitive, yy_type)
//
//  yy_symtab_install_kw() is a lexing utility routine which installs a case 
//  insensitive or sensitive keyword symbol.  
//
//  yy_text_ptr        is the spelling of the keyword.  
// 
//  yy_len             is the length of the spelling of the keyword string at 
//                     yy_text_ptr.
//
//  yy_tkn_type        is the token type of the keyword.
//
//  yy_case_sensitive  is TRUE if this is a case sensitive keyword.
//
//  yy_type            is the semantic type of the keyword (if present,
//                     overloaded version of yy_symtab_install_kw is used).
//
//  yy_symtab_install_kw() returns the pointer to the symbol object for the
//  keyword symbol.  If a new hashed symbol object is needed, it is created.
//  If a symbol object already exists for this keyword symbol, it returns
//  it.
//
//  Keywords are either case sensitive or case insensitive.  
//
//  For case insensitive keywords, we install keywords in lower case.  
//  The text pointed to by "yy_text_ptr" must be in lower case for case 
//  insensitive keywords.  The keyword tables created by Yacc++ have 
//  the spellings of case insensitive keywords in lower case.  
//
//  For case sensitive keywords, we install keywords in the same case as
//  they are passed to this function.  Case sensitive keywords in a
//  symbol table which supports case insensitive keywords are hashed in
//  lower case, but stored in the case passed in.
//
//  Algorithm  
//
//  obtain the integer hash value for keyword
//  
//      - case sensitive match, return already existing symbol.  Give an
//        error if it had a different token type.
//
//      - no matching symbol, create a new symbol object with a copy of
//        the text pointed to by "yy_text_ptr".
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_install_kw(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type,
    yy_boolean          yy_case_sensitive
    )
{
    yy_sym_dflt_ptr     sy_ptr;
    int                 hash_ix;
    int                 i;
    char                *new_str;

    assert(yy_text_ptr != NULL);
    assert(yy_text_ptr[yy_len] == '\0');

    new_str = new char[yy_len + 1];

    if (new_str == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(NULL);
        }

//  hash the string
// 
//  typically we just hash the string from the incoming spelling as is.
//  
//  however, for the special case of case sensitive keywords in a grammar
//  which also has case insensitive keywords, we convert it to lower case.

    if (yy_symtab_has_insensitive_kws & yy_case_sensitive) {
        for (i = 0; i < yy_len; ++i) {
#ifdef yy_tolower_ok_
	    new_str[i] = tolower(yy_text_ptr[i]);
#else
            if ('A' <= yy_text_ptr[i] && yy_text_ptr[i] <= 'Z') {
                new_str[i] = (char)((int)(yy_text_ptr[i]) -
                             (int)('A')+(int)('a'));
                }
            else {
                new_str[i] = yy_text_ptr[i];
                }
#endif /* yy_tolower_ok_ */
            }
        new_str[i] = '\0';
        hash_ix = yy_hash_str(new_str, yy_len);
        }
    else {
        hash_ix = yy_hash_str(yy_text_ptr, yy_len);
        }

    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

    //  symbol object matches while installing a keyword??  Ok, 
    //  just return it as long as it's the same keyword type.  If not,
    //  give an error before returning it.

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {
            if (sy_ptr -> yy_sym_tkn_type() != yy_tkn_type) {
                yy_err_report(407, yy_text_ptr);
                }
            delete [] new_str;
            return(sy_ptr);
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }

//  no matching symbol object already exists, so create one with a copy
//  of the exact case spelling as passed in

    memcpy(new_str, yy_text_ptr, yy_len);
    new_str[yy_len] = '\0';

    return(yy_hash_tbl[hash_ix] = yy_new_sym_obj(
            yy_hash_tbl[hash_ix],                   // yy_next_ptr
            new_str,                                // yy_str_ptr
            yy_len,                                 // yy_len
            yy_tkn_type,                            // yy_tkn_type
            yy_sym_dflt_obj::yy_sym_type_init_,     // yy_type
            yy_case_sensitive? 0: yy_sym_dflt_obj::yy_sym_case_insensitive_
                                                    // yy_flags
            ));

}   // yy_symtab_install_kw


// See full description above.

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_install_kw(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type,
    yy_boolean          yy_case_sensitive,
    int                 yy_type
    )
{
    yy_sym_dflt_ptr     sy_ptr;
    int                 hash_ix;
    int                 i;
    char                *new_str;

    assert(yy_text_ptr != NULL);
    assert(yy_text_ptr[yy_len] == '\0');

    new_str = new char[yy_len + 1];

    if (new_str == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(NULL);
        }

//  hash the string
// 
//  typically we just hash the string from the incoming spelling as is.
//  
//  however, for the special case of case sensitive keywords in a grammar
//  which also has case insensitive keywords, we convert it to lower case.

    if (yy_symtab_has_insensitive_kws & yy_case_sensitive) {
        for (i = 0; i < yy_len; ++i) {
            if ('A' <= yy_text_ptr[i] && yy_text_ptr[i] <= 'Z') {
                new_str[i] = (char)((int)(yy_text_ptr[i]) -
                             (int)('A')+(int)('a'));
                }
            else {
                new_str[i] = yy_text_ptr[i];
                }
            }
        new_str[i] = '\0';
        hash_ix = yy_hash_str(new_str, yy_len);
        }
    else {
        hash_ix = yy_hash_str(yy_text_ptr, yy_len);
        }

    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

    //  symbol object matches while installing a keyword??  Ok, 
    //  just return it as long as it's the same keyword type.  If not,
    //  give an error before returning it.

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {
            if (sy_ptr -> yy_sym_tkn_type() != yy_tkn_type) {
                yy_err_report(407, yy_text_ptr);
                }
            delete [] new_str;
            return(sy_ptr);
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }

//  no matching symbol object already exists, so create one with a copy
//  of the exact case spelling as passed in

    memcpy(new_str, yy_text_ptr, yy_len);
    new_str[yy_len] = '\0';

    return(yy_hash_tbl[hash_ix] = yy_new_sym_obj(
            yy_hash_tbl[hash_ix],                   // yy_next_ptr
            new_str,                                // yy_str_ptr
            yy_len,                                 // yy_len
            yy_tkn_type,                            // yy_tkn_type
            yy_type,                                // yy_type
            yy_case_sensitive? 0: yy_sym_dflt_obj::yy_sym_case_insensitive_
                                                    // yy_flags
            ));

}   // yy_symtab_install_kw


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_ptr yy_symtab_lookup(yy_text_ptr, yy_len, yy_tkn_type)
//  
//  yy_symtab_lookup() is a lexing utility routine which performs a table 
//  lookup for a symbol.  If a symbol object already exists which matches 
//  the symbol spelling, it is returned.  Otherwise, a new hashed 
//  symbol object is created.  This function provides case sensitive 
//  lookup.  It should not be used in your grammar for lookups for case 
//  insensitive keywords.  (use yy_symtab_lookup_kw()).
//
//  yy_text_ptr  is the spelling of the symbol.
//
//  yy_len       is the length of the spelling of the string at yy_text_ptr.
//
//  yy_tkn_type  is the default token type of the symbol.  This value is
//               used if a matching symbol object is found which does not
//               have a token type already or if a new symbol object is
//               created.
//
//  yy_symtab_lookup() returns the pointer to the symbol object.
//
//  Algorithm
//    
//  hash the string "yy_text_ptr"
//
//  search for the matching symbol in the list of symbol objects in the 
//  hash bucket
//  
//   -  if we find a matching symbol, return it
//  
//   -  if we do not find a matching symbol, create a new one with a copy 
//      of the spelling "yy_text_ptr" and with token type "yy_tkn_type".  
//      Add the symbol object to the beginning of the hash list so most 
//      recently seen symbols get the quickest access.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_lookup(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type
    )
{
    yy_sym_dflt_ptr     sy_ptr;
    int                 hash_ix;
    char                *new_str;

    assert(yy_text_ptr != NULL);

//  obtain the integer hash value of the string 

    hash_ix = yy_hash_str(yy_text_ptr, yy_len);
    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

//  attempt to find a match

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

    //  found a symbol object that matches, return it

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {

        //  if no token type yet, give it "yy_tkn_type"

            if (sy_ptr -> yy_sym_tkn_type() == 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_) { 
                sy_ptr -> yy_sym_tkn_type(yy_tkn_type);
                }
            return(sy_ptr);
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }
 
//  no symbol object that matches, create a new one

    new_str = new char[yy_len + 1];

    if (new_str == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(NULL);
        }

    memcpy(new_str, yy_text_ptr, yy_len);
    new_str[yy_len] = '\0';

    return(yy_hash_tbl[hash_ix] = yy_new_sym_obj(
            yy_hash_tbl[hash_ix],                   // yy_next_ptr
            new_str,                                // yy_str_ptr
            yy_len,                                 // yy_len
            yy_tkn_type,                            // yy_tkn_type
            yy_sym_dflt_obj::yy_sym_type_init_,     // yy_type
            0                                       // yy_flags
            ));

}   // yy_symtab_lookup


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_ptr yy_symtab_lookup_kw(yy_text_ptr, yy_len, 
//                  yy_tkn_type)
//  
//  yy_symtab_lookup_kw() is a lexing utility routine which performs a table
//  lookup for a symbol.  If a symbol object already exists which matches 
//  the symbol spelling, it is returned.  Otherwise, a new hashed 
//  symbol object is created.  This function provides for both case 
//  sensitive and case insensitive lookup.  You can always use this lookup
//  function, but if you know you won't be matching a case insensitive 
//  keyword, use yy_symtab_lookup() instead for better performance.
//
//   yy_text_ptr  is the spelling of the symbol.
//
//   yy_len       is the length of the spelling of the string at yy_text_ptr.
//
//   yy_tkn_type  is the default token type.  This value is used if a
//                matching symbol object is found which does not have a
//                token type already or if a new symbol object is created 
//                and no case insensitive keyword was matched.
//
//  yy_symtab_lookup_kw() returns the pointer to the symbol object.
//
//  yy_symtab_lookup_kw() is used specifically for looking up symbols which
//  can match keywords, because it provides case insensitivity on keywords
//  and case sensitivity for other symbol names.
//
//  To achieve case insensitivity:  the spelling is hashed in lower case.  
//  When searching the hash chain, a lower case version of the spelling 
//  "yy_text_ptr" is compared to the entries in the hash chain which have 
//  keywords hashed in lower case.  If we find a lower case match and the 
//  entry is a keyword, the token type for the symbol object to be created
//  is changed from the incoming token type to the appropriate keyword type.
//
//  To achieve case sensitivity:  the spelling "yy_text_ptr" is kept in its 
//  original case.  When inserting a new symbol in the hash chain, we use 
//  the spelling in "yy_text_ptr" thus matching only on exact case.
//
//  NOTE: you will get multiple copies of symbols with just different case.
//  This is necessary to support languages with case sensitive identifier 
//  names but case insensitive keywords.  (Like Yacc++ and PL/1).
//
//  If your identifiers and keywords are both case insensitive, lower case
//  your spelling before calling this function and this will prevent getting
//  multiple copies of symbols.
//
//  Algorithm
//  
//  create lower case version of "yy_text_ptr" for keyword case insensitive
//  check
//  
//  obtain integer hash value for the case insensitive version
//  
//  try to find a matching symbol
//
//     - using incoming spelling, an exact case match, return the matching 
//       symbol object
//  
//     - using lower cased spelling, a case insensitive match, use the
//       keyword type instead of incoming token type when creating new symbol
//       with the incoming spelling (see NOTE above)
//
//     - no matching symbol so create a new symbol object for the original 
//       spelling "yy_text_ptr" and "yy_tkn_type"
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_lookup_kw(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type
    )
{
    yy_sym_dflt_ptr     sy_ptr;
    char                *new_str;
    int                 hash_ix;
    int                 new_tkn_type, new_type, new_flags;
    int                 i;

    assert(yy_text_ptr != NULL);

    new_str = new char[yy_len + 1];

    if (new_str == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(NULL);
        }

    new_type = yy_sym_dflt_obj::yy_sym_type_init_; // yy_type
    new_flags = 0;

//  for case insensitive keyword matching, we create a lower case version
//  of yy_text_ptr for keyword case insensitive check.  For case sensitive
//  keywords, we use the spelling exactly as is.

    if (yy_symtab_has_insensitive_kws) {
        for (i = 0; i < yy_len; ++i) {
#ifdef yy_tolower_ok_
	    new_str[i] = tolower(yy_text_ptr[i]);
#else
            if ('A' <= yy_text_ptr[i] && yy_text_ptr[i] <= 'Z') {
                new_str[i] = (char)((int)(yy_text_ptr[i]) - 
                             (int)('A')+(int)('a'));
                }
            else {
                new_str[i] = yy_text_ptr[i];
                }
#endif /* yy_to_lower_ok_ */
            }
        new_str[i] = '\0';
        }
    else {
        memcpy(new_str, yy_text_ptr, yy_len);
        new_str[yy_len] = '\0';
        }

//  obtain integer hash value for spelling

    hash_ix = yy_hash_str(new_str, yy_len);
    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

//  save the incoming token type, in case we do not find a keyword match

    new_tkn_type = yy_tkn_type;

//  try to find a match

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

        assert(sy_ptr -> yy_sym_str()[sy_ptr -> yy_sym_len()] == '\0');

    //  if we have an exact case match, return it

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {

        //  if no token type yet, give it "yy_tkn_type"

            if (sy_ptr -> yy_sym_tkn_type() == 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_) { 
                sy_ptr -> yy_sym_tkn_type(yy_tkn_type);
                }

            delete [] new_str;

            return(sy_ptr);
            }

    //  if we are doing case insensitive keyword lookup and we have a
    //  case insensitive match, change the token type for the symbol to
    //  be created on no exact match from the input token type to the 
    //  keyword type.  This type change will only happen on the first match.

        else if (yy_symtab_has_insensitive_kws && yy_tkn_type == new_tkn_type
                 && (sy_ptr -> yy_sym_flags() & 
                    yy_sym_dflt_obj::yy_sym_case_insensitive_) &&
                 sy_ptr -> yy_sym_tkn_type() != 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_ && 
                 sy_ptr -> yy_sym_tkn_type() != yy_tkn_type && 
                 yy_len == sy_ptr -> yy_sym_len() && 
                 memcmp(new_str, sy_ptr -> yy_sym_str(), yy_len) == 0) {
            new_tkn_type = sy_ptr -> yy_sym_tkn_type();
            new_type = sy_ptr -> yy_sym_type();
            new_flags = sy_ptr -> yy_sym_flags();
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }

//  no symbol object that matches, create a symbol object with a copy of the
//  original spelling 

    memcpy(new_str, yy_text_ptr, yy_len);
    new_str[yy_len] = '\0';

    return(yy_hash_tbl[hash_ix] = yy_new_sym_obj(
            yy_hash_tbl[hash_ix],               // yy_next_ptr
            new_str,                            // yy_str_ptr
            yy_len,                             // yy_len
            new_tkn_type,                       // yy_tkn_type
            new_type,                           // yy_type
            new_flags                           // yy_flags
            ));

}   // yy_symtab_lookup_kw


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_ptr yy_symtab_lookup_only(yy_text_ptr, yy_len, 
//                  yy_tkn_type)
//  
//  yy_symtab_lookup_only() is a lexing utility routine which performs a table
//  lookup for a symbol.  If a symbol object already exists which matches 
//  the symbol spelling, it is returned.  Otherwise, NULL is returned.
//  This function provides case sensitive lookup.  It should not be used 
//  in your grammar for lookups for case insensitive keywords.  
//  (use yy_symtab_lookup_only_kw()).
//
//  yy_text_ptr  is the spelling of the symbol.
//
//  yy_len       is the length of the spelling of the string at yy_text_ptr.
//
//  yy_tkn_type  is the default token type of the symbol.  This value is
//               used if a matching symbol object is found which does not
//               have a token type already.
//
//  yy_symtab_lookup_only() returns the ptr to the symbol object or NULL.
//
//  Algorithm
//    
//  hash the string "yy_text_ptr"
//
//  search for the matching symbol in the list of symbol objects in the 
//  hash bucket
//  
//   -  if we find a matching symbol, return pointer to symbol
//  
//   -  if we do not find a matching symbol, return NULL
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_lookup_only(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type
    )
{
    yy_sym_dflt_ptr     sy_ptr;
    int                 hash_ix;

    assert(yy_text_ptr != NULL);

//  obtain the integer hash value of the string 

    hash_ix = yy_hash_str(yy_text_ptr, yy_len);
    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

//  attempt to find a match

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

    //  found a symbol object that matches, return it

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {

        //  if no token type yet, give it "yy_tkn_type"

            if (sy_ptr -> yy_sym_tkn_type() == 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_) { 
                sy_ptr -> yy_sym_tkn_type(yy_tkn_type);
                }
            return(sy_ptr);
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }
 
//  no symbol object that matches, return NULL

    return(NULL);

}   // yy_symtab_lookup_only


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_ptr yy_symtab_lookup_only_kw(yy_text_ptr, yy_len, 
//                  yy_tkn_type)
//  
//  yy_symtab_lookup_only_kw() is a lexing utility routine which performs a 
//  table lookup for a symbol.  If a symbol object already exists which 
//  matches the symbol spelling, it is returned.  Otherwise, NULL is returned.
//  This function provides for both case sensitive and case insensitive 
//  lookup.  You can always use this lookup function, but if you know you 
//  won't be matching a case insensitive keyword, use yy_symtab_lookup_only 
//  instead for better performance.
//
//   yy_text_ptr  is the spelling of the symbol.
//
//   yy_len       is the length of the spelling of the string at yy_text_ptr.
//
//   yy_tkn_type  is the default token type of the symbol.  This value is
//                used if a matching symbol object is found which does not
//                have a token type already.
//
//  yy_symtab_lookup_only_kw() returns the pointer to the matching symbol
//  object or NULL if no match was found.
//
//  yy_symtab_lookup_only_kw() is used specifically for looking up symbols 
//  which can match keywords, because it provides case insensitivity on 
//  keywords and case sensitivity for other symbol names.
//
//  To achieve case insensitivity:  the spelling is hashed in lower case.  
//  When searching the hash chain, a lower case version of the spelling 
//  "yy_text_ptr" is compared to the entries in the hash chain which have 
//  keywords hashed in lower case.  If we find a lower case match and the 
//  entry is a keyword, return this symbol if we don't later find an exact
//  case match.
//
//  Algorithm
//  
//  create lower case version of "yy_text_ptr" for keyword case insensitive
//  check
//  
//  obtain integer hash value for the case insensitive version
//  
//  try to find a matching sym
//
//     - case sensitive match, return the symbol object that matches
//  
//     - case insensitive match, save it
//
//     - no matching sym, return case insensitive match or NULL if none
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_ptr yy_symtab_dflt_obj::yy_symtab_lookup_only_kw(
    const char          *yy_text_ptr,
    int                 yy_len,
    int                 yy_tkn_type
    )
{
    yy_sym_dflt_ptr     sy_ptr, new_sym_ptr;
    char                *new_str;
    int                 hash_ix;
    int                 i;

    assert(yy_text_ptr != NULL);

    new_sym_ptr = NULL;

    new_str = new char[yy_len + 1];

    if (new_str == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(NULL);
        }

//  for case insensitive keyword matching, we create a lower case version
//  of yy_text_ptr for keyword case insensitive check.  For case sensitive
//  keywords, we use the incoming spelling exactly as is.

    if (yy_symtab_has_insensitive_kws) {
        for (i = 0; i < yy_len; ++i) {
#ifdef yy_tolower_ok_
	    new_str[i] = tolower(yy_text_ptr[i]);
#else
            if ('A' <= yy_text_ptr[i] && yy_text_ptr[i] <= 'Z') {
                new_str[i] = (char)((int)(yy_text_ptr[i]) - 
                             (int)('A')+(int)('a'));
                }
            else {
                new_str[i] = yy_text_ptr[i];
                }
#endif /* yy_to_lower_ok_ */
            }
        new_str[i] = '\0';
        }
    else {
        memcpy(new_str, yy_text_ptr, yy_len);
        new_str[yy_len] = '\0';
        }

//  obtain integer hash value for spelling

    hash_ix = yy_hash_str(new_str, yy_len);
    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

//  try to find a match

    sy_ptr = yy_hash_tbl[hash_ix];  
    while (sy_ptr != NULL) {

        assert(sy_ptr -> yy_sym_str()[sy_ptr -> yy_sym_len()] == '\0');

    //  if we have an exact case match, return it

        if (yy_len == sy_ptr -> yy_sym_len() && 
            memcmp(yy_text_ptr, sy_ptr -> yy_sym_str(), yy_len) == 0) {

        //  if no token type yet, give it "yy_tkn_type"

            if (sy_ptr -> yy_sym_tkn_type() == 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_) { 
                sy_ptr -> yy_sym_tkn_type(yy_tkn_type);
                }

            delete [] new_str;

            return(sy_ptr);
            }

//  if we are doing a case insensitive keyword lookup and we have a
//  case insensitive match, save it.  Then continue checking for an
//  exact case match.  We return the exact case match if we have one;
//  otherwise the case insensitive match is returned.

        else if (yy_symtab_has_insensitive_kws && 
                 (sy_ptr -> yy_sym_flags() & 
                    yy_sym_dflt_obj::yy_sym_case_insensitive_) &&
                 sy_ptr -> yy_sym_tkn_type() != 
                    yy_sym_dflt_obj::yy_sym_tkn_type_init_ && 
                 sy_ptr -> yy_sym_tkn_type() != yy_tkn_type && 
                 yy_len == sy_ptr -> yy_sym_len() && 
                 memcmp(new_str, sy_ptr -> yy_sym_str(), yy_len) == 0) {
            new_sym_ptr = sy_ptr;
            }

        sy_ptr = sy_ptr -> yy_sym_next();
        }

//  new_sym_ptr has either a symbol object from a case insensitive match
//  or NULL if there was no symbol_object match.

    delete [] new_str;

    return(new_sym_ptr);
    
}   // yy_symtab_lookup_only_kw


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_symtab_remove_sym(yy_this_sym)
//  
//  yy_symtab_remove_sym() removes the reference to a symbol object in
//  the symbol table and then deletes the symbol object.
//
//  yy_this_sym     is the symbol object.
//
//  yy_symtab_remove_sym() returns true if it dereferenced a symbol in the
//  symbol table or returns yy_false if it didn't locate the symbol object.  
//  In either case, the symbol gets deleted.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_symtab_dflt_obj::yy_symtab_remove_sym(
    yy_sym_ptr      yy_this_sym
    )
{
    yy_sym_dflt_ptr     prev_sy_ptr, cur_sy_ptr;
    char                *new_str;
    int                 hash_ix, i;

    if (yy_this_sym == NULL) {
        return(yy_false);
        }

//  obtain the integer hash value for symbol object

    if (!yy_symtab_has_insensitive_kws) {
        hash_ix = yy_hash_str(yy_this_sym -> yy_sym_str(), 
                    yy_this_sym -> yy_sym_len());
        }

//  this is the special case of insensitive keywords in the symbol table
//  which means the spelling in the symbol needs to be lower cased to 
//  obtain its actual hash value.

    else {
        new_str = new char[yy_this_sym -> yy_sym_len() + 1]; 

        if (new_str == NULL) {  // new() failure
            yy_err_report(406);
            yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
            return(yy_false);
            }

        for (i = 0; i < yy_this_sym -> yy_sym_len(); ++i) {
#ifdef yy_tolower_ok_
	    new_str[i] = tolower(yy_this_sym -> yy_sym_str()[i]);
#else
            if ('A' <= yy_this_sym -> yy_sym_str()[i] && 
                yy_this_sym -> yy_sym_str()[i] <= 'Z') {

                new_str[i] = (char)((int) (yy_this_sym -> yy_sym_str()[i])
                                           -(int)('A')+(int)('a'));
                }
            else {
                new_str[i] = yy_this_sym -> yy_sym_str()[i];
                }
#endif /* yy_to_lower_ok_ */
            }
        new_str[i] = '\0';
        hash_ix = yy_hash_str(new_str, yy_this_sym -> yy_sym_len());
        delete [] new_str;
        }

    assert(0 <= hash_ix && hash_ix <= yy_hash_max_ix_);

//  search for the symbol object in the symbol table

    prev_sy_ptr = NULL;
    cur_sy_ptr = yy_hash_tbl[hash_ix];  

    while (cur_sy_ptr != NULL) {
        if (cur_sy_ptr == yy_this_sym) {
            break;
            }
        prev_sy_ptr = cur_sy_ptr;
        cur_sy_ptr = cur_sy_ptr -> yy_sym_next();
        }

//  didn't find it in the symbol table

    if (cur_sy_ptr != yy_this_sym) {
        delete yy_this_sym;
        return(yy_false);
        }

//  found it at the beginning of hash chain

    if (prev_sy_ptr == NULL) {
        yy_hash_tbl[hash_ix] = cur_sy_ptr -> yy_sym_next();
        }

//  found it either in the middle or last in the hash chain

    else {
        prev_sy_ptr -> yy_sym_next(cur_sy_ptr -> yy_sym_next());
        }

    delete yy_this_sym;
    
    return(yy_true);

}   // yy_symtab_remove_sym


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_hash_str(yy_text_ptr, yy_len)
//  
//  yy_hash_str() hashes the string "yy_text_ptr" with length "yy_len" and 
//  produces an integer hashed value.  Hashing is done with the 
//  "shift and add" hashing algorithm.
//  
//  yy_text_ptr   is the string to be hashed
//  
//  yy_len        is the length of the string to be hashed
//  
//  yy_hash_str   returns the hash_value, an integer representing the string.
//  
//  Algorithm:
//
//  initializes hash value to 1st character of the string
//
//  takes each subsequent character out of the string moving left to right
//
//  with each character, shifts the value of the current hash and adds the 
//  character
//
//  takes the modulo of hash value to keep within the range of 
//       0 .. yy_hash_max_ix - 1.
//
//////////////////////////////////////////////////////////////////////////////

int yy_symtab_dflt_obj::yy_hash_str(
    const char  *yy_text_ptr,
    int         yy_len)
{
    int     hash_value;

    assert(yy_text_ptr != NULL);
    assert(yy_len >= 0);

    if (yy_len == 0) {
        return(0);
        }

    hash_value = (int) *yy_text_ptr;
    --yy_len;

    while(yy_len > 0) {
        ++yy_text_ptr;
        hash_value = (hash_value << 1) + (int) *yy_text_ptr;        
        --yy_len;
        }

    hash_value = abs(hash_value) % yy_hash_max_ix_;

    return(hash_value);
        
}   // yy_hash_str


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_dflt_obj::yy_sym_dflt_obj()
//
//  This is the no argument constructor for the default implementation 
//  symbol object.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_dflt_obj::yy_sym_dflt_obj() :
    yy_next_ptr(NULL),
    yy_str_ptr(NULL),
    yy_len(0),
    yy_tkn_type(yy_sym_tkn_type_init_),
    yy_type(yy_sym_type_init_),
    yy_flags(0)
{
}   // constructor for yy_sym_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_dflt_obj::yy_sym_dflt_obj(...)
//
//  This is the constructor for the default implementation symbol object
//  whose parameter list corresponds to the fields in the symbol object.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_dflt_obj::yy_sym_dflt_obj(
        yy_sym_dflt_ptr  yy_new_next_ptr,
        char             *yy_new_str_ptr,
        int              yy_new_len,
        int              yy_new_tkn_type,
        int              yy_new_type,
        int              yy_new_flags
    ) :
    yy_next_ptr(yy_new_next_ptr),
    yy_str_ptr(yy_new_str_ptr),
    yy_len(yy_new_len),
    yy_tkn_type(yy_new_tkn_type),
    yy_type(yy_new_type),
    yy_flags(yy_new_flags)
{
}   // constructor for yy_sym_dflt_obj


/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_sym_dflt_obj::~yy_sym_dflt_obj()
//
//  This is the destructor for the default implementation symbol object.
//
//////////////////////////////////////////////////////////////////////////////

yy_sym_dflt_obj::~yy_sym_dflt_obj()
{
    if (yy_str_ptr != NULL) {
        delete [] yy_str_ptr;
        yy_str_ptr = NULL;
        }

}   // destructor for yy_sym_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_sym_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_sym_dmp() displays the values of the symbol object.  It is a debugging
//  function we used when developing Yacc++.  We have included this function
//  as a member of the symbol object in case you need to dump the internal 
//  state of a symbol.
//
//  yy_this_err_obj  is an error object where this dump is to be displayed.
//
//  yy_dmp_title    a character string to identify the dump.  For example, 
//                  sometimes you might want to identify your symbol dump with
//                  the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

void yy_sym_dflt_obj::yy_sym_dmp(
    yy_err_ptr yy_this_err_obj, 
    const char *yy_dmp_title)
{
    char  *char_ptr;

    if (yy_dmp_title != NULL) {
        yy_this_err_obj -> yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

    yy_this_err_obj -> yy_err_puts(" symbol name ");

    for (char_ptr = yy_str_ptr; 
         char_ptr < yy_str_ptr + yy_len; char_ptr++) {
        if (*char_ptr == '\n') {
            yy_this_err_obj -> yy_err_puts("\\n");
            }
        else {
            yy_this_err_obj -> yy_err_printf("%c", *char_ptr);
            }
        }

    yy_this_err_obj -> yy_err_printf("\n\ttoken type %d\n", yy_tkn_type);
    yy_this_err_obj -> yy_err_printf("\ttype %d\n", yy_type);
    yy_this_err_obj -> yy_err_printf("\tflags %d\n\n", yy_flags);

}   // yy_sym_dmp

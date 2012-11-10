
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_ansi.h
//
//  FILE DESCRIPTION:     insert file with ANSI C conformance macros.
//
//  MODIFICATION HISTORY:
//
//    02/27/98   bz       merged yy_size_t and yy_free_ptr.
//    08/06/93   bz/cc    added yy_export and yy_far.
//    06/17/93   bz       removed setjmp stuff.
//    10/23/92   bz       Microsoft C7 support for __ prefixes.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_ansi.h" contains the manifest constants which control the use of 
//  ANSI C and other potentially non-portable features.  These constants 
//  customize the code provided in the Yacc++ Language Objects Library to 
//  work in either an C++, ANSI C, or a pre-ANSI (K&R) environment.
// 
//  The main features of ANSI C in the library are the use of function 
//  prototypes, stringizing (in macros), and the types void and void *.  
//  Use of each feature can be enabled individually.  The presence of an 
//  ANSI compliant C compiler  (__STDC__ defined to the value 1) enables
//  the use of all ANSI compliant features.
//
//  When the code is compiled with C++ compiler, the code compiles into
//  classes with member functions.  Inheritance and function overloading
//  are also used.  The use of ANSI C preprocessor features, such as
//  stringizing and token pasting, are not automatically enabled by the
//  presence of a C++ compiler.
//
//  yy_ansi_ok_         enables the use of all ANSI C features.  
//
//  yy_cxx_ok_          enables the use of all C++ features.  
//
//  yy_blue_ok_         enables the use of macros which require "blue" 
//                      substitution, where recursive expansions are 
//                      prevented.  If not defined, the macros which 
//                      require "blue" substitution are defined to avoid
//                      potentialy recursive expansions, but provide less
//                      functionality.  This is generally done by changing
//                      the name of the underlying function.  Therefore, if
//                      your compiler does not support blue macros, the 
//                      names of certain functions will be different than 
//                      the default name.
//
//  yy_class_ok_        enables the use of class.  If not defined, class 
//                      is defined to be struct.
//
//  yy_const_ok_        enables the use of const.  If not defined, const 
//                      is defined to have an empty replacement.
//
//  yy_export_ok_       enables the use of yy_export as export.  If not 
//                      defined, yy_export is defined to have an empty 
//                      replacement.
//
//  yy_extern_wrapper_ok_
//                      enables the use of the extern "C" wrapper 
//                      surrounding C and system library functions .  If 
//                      not defined, the C and system library functions are
//                      merely declared as external.
//
//  yy_friend_ok_       enables the use of the friend function qualifier.  If
//                      not defined, friend is defined to have an empty 
//                      replacement.
//
//  yy_function_members_ok_ 
//                      causes object specific functions to be declared as 
//                      members of the class.  If not defined, the functions 
//                      are declared as external.
//
//  yy_memcpy_ok_       defined if memcpy protects against overlapping memory
//                      moves.  Otherwise, memmove is used.
//
//  yy_paste_ok_        enables features in macros which require ANSI token 
//                      pasting.   If not defined, the macros are defined in 
//                      a manner which does not require token pasting, but
//                      provides less functionality.
//
//  yy_protos_ok_       enables declaring all library functions and macros
//                      with function prototypes.  If not defined, functions
//                      are declared by "old-style" function declarations and
//                      macros are declared only by their #define statements.
//
//  yy_scope_name_ok_   enables the use of the :: operator to specify class
//                      member names.  If not defined, each externally visible
//                      name is given a unique name distinct from all other 
//                      externally visible names.
//
//  yy_size_t_ok_       enables the use of the type size_t.  If not defined,
//                      the type size_t is defined to be long.
//
//  yy_static_members_ok_
//                      causes data which is shared between distinct objects 
//                      in a class to be declared as static members of the 
//                      class.  If not defined, the shared objects are 
//                      declared as external variables.
//
//  yy_stdarg_ok_       enables the use of stdarg macro for variable argument
//                      lists.  If not defined, the vararg macros are used 
//                      for variable argument lists.
//
//  yy_stddef_ok_       enables the inclusion of the stddef header file. If
//                      not defined, the stddef header file is not included.
//
//  yy_stdlib_ok_       enables the inclusion of the stdlib header file. If
//                      not defined, the stdlib header file is not included.
//
//  yy_string_ok_       enables the inclusion of the string header file. If 
//                      not defined, the string header file is not included.
//
//  yy_stringize_ok_    enables features in macros which require ANSI string-
//                      izing.  If not defined, the macros are defined in a
//                      manner which does not require stringizing, but 
//                      provides less functionality.
//
//  yy_struct_assign_ok_
//                      enables assignment statements which copy a whole
//                      structure at a time.  If not defined, the structures 
//                      are copied field by field, or with memcpy.
//
//  yy_sys5_files_ok_   enables the inclusion of the "System V" file defini-
//                      tion header files. If not defined, the "BSD" file 
//                      definition header files are included.
//
//  yy_this_ok_         enables the use of the implicit this pointer.  If not
//                      defined, the member functions are defined to take an 
//                      explicit this pointer.  Special macros simulate the 
//                      implicit this pointer for functions commonly used in 
//                      lexer and parser action code.
//
//  yy_time_t_ok_       enables the use of the type time_t.  If not defined,
//                      the type time_t is defined to be long.
//
//  yy_virtual_ok_      enables the use of the member qualifier virtual.  If
//                      not defined, virtual is defined to have an empty 
//                      replacement.
//
//  yy_void_ok_         enables the use of void (yy_void_ptr for "void *").
//                      If not defined, void is defined to have an empty 
//                      replacement and yy_void_ptr is defined to be "char *".
//
//  yy_volatile_ok_     enables the use of volatile.  If not defined, 
//                      volatile is defined to have an empty replacement.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_ansi_h_
#define yy_ansi_h_

#ifdef yy_user_config_
#include "yy_all.cfg"
#endif /* yy_user_config_ */

#ifndef yy_ansi_ok_
#ifdef __STDC__
#if __STDC__ == 1
#define yy_ansi_ok_ 1
#endif /* __STDC__ == 1 */
#endif /* __STDC__ */
#ifdef __TURBOC__
#define yy_ansi_ok_ 1
#endif /* __TURBOC__ */
#ifdef __ZTC__
#define yy_ansi_ok_ 1
#endif /* __ZTC__ */
#endif /* yy_ansi_ok_ */

#ifndef yy_cxx_ok_
#ifdef __cplusplus
#define yy_cxx_ok_ 1
#endif /* __cplusplus */
#ifdef c_plusplus
#define yy_cxx_ok_ 1
#endif /* c_plusplus */
#endif /* yy_cxx_ok_ */

#ifndef yy_cfg_h_
#include "yy_cfg.h"
#endif /* yy_cfg_h_ */

#ifndef yy_msdos_
#ifdef MSDOS
#define yy_msdos_ 1
#endif /* MSDOS */
#ifdef __MSDOS__
#define yy_msdos_ 1
#endif /* __MSDOS__ */
#endif /* yy_msdos_ */

#ifndef yy_blue_ok_
#ifdef yy_ansi_ok_
#define yy_blue_ok_ 1
#endif /* yy_ansi_ok_ */
#endif /* yy_blue_ok_ */

#ifndef yy_class_ok_
#ifdef yy_cxx_ok_
#define yy_class_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_class_ok_ */

#ifndef yy_class_ok_
#ifndef class
#define class struct
#endif /* class */
#ifndef yy_class
#define yy_class struct
#endif /* class */
#else /* yy_class_ok_ */
#ifndef yy_class
#define yy_class class
#endif /* class */
#endif /* yy_class_ok_ */

#ifndef yy_const_ok_
#ifdef yy_ansi_ok_
#define yy_const_ok_ 1
#endif /* yy_ansi_ok_ */
#ifdef yy_cxx_ok_
#define yy_const_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_const_ok_ */

#ifndef yy_const_ok_
#ifndef const
#define const
#endif /* const */
#endif /* yy_const_ok_ */

#ifndef yy_ctype_ok_
#ifdef yy_ansi_ok_
#define yy_ctype_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_ctype_ok_ 1
#endif
#endif

#ifdef yy_dummy_use_required_
#define yy_dummy_use(x) x=x
#else /* yy_dummy_use_required_ */
#define yy_dummy_use(x)
#endif /* yy_dummy_use_required_ */

#ifndef yy_extern_wrapper_ok_
#ifdef yy_cxx_ok_
#define yy_extern_wrapper_ok_
#endif /* yy_cxx_ok_ */
#endif /* yy_extern_wrapper_ok_ */

#ifndef yy_extern_wrapper_ok_
#undef yy_extern_wrapper_reqd_
#endif /* yy_extern_wrapper_ok_ */

//  32 bit systems like Sparc do not have the export attribute,
//  compilers such as Microsoft Visual C++ need __export,
//  other compilers such as Borland C++ need _export,
//  and some compilers use plain export.

#ifndef yy_export
#ifndef yy_export_ok_
#define yy_export
#else /* yy_export_ok_ */
#ifdef yy_c700_extended_kws_
#define yy_export __export
#else
#ifdef yy_prefix_extended_kws_
#define yy_export _export
#else
#define yy_export export
#endif /* yy_prefix_extended_kws_ */
#endif /* yy_c700_extended_kws_ */
#endif /* yy_export_ok_ */
#endif /* yy_export */

//  32 bit systems like Sparc do not have the far attribute,
//  compilers such as Microsoft Visual C++ need __far,
//  other compilers such as Borland C++ need _far,
//  and some compilers use plain far.

#ifndef yy_far
#ifndef yy_far_ok_
#define yy_far
#else /* yy_far_ok_ */
#ifdef yy_c700_extended_kws_
#define yy_far __far
#else
#ifdef yy_prefix_extended_kws_
#define yy_far _far
#else
#define yy_far far
#endif /* yy_prefix_extended_kws_ */
#endif /* yy_c700_extended_kws_ */
#endif /* yy_far_ok_ */
#endif /* yy_far */

#ifndef yy_friend_ok_
#ifdef yy_cxx_ok_
#define yy_friend_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_friend_ok_ */

#ifndef yy_friend_ok_
#ifndef friend
#define friend 
#endif /* friend */
#endif /* yy_friend_ok_ */

#ifndef yy_function_members_ok_
#ifdef yy_cxx_ok_
#define yy_function_members_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_function_members_ok_ */

#ifndef yy_inherit_ok_
#ifdef yy_cxx_ok_
#define yy_inherit_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_inherit_ok_ */

#ifndef yy_inline_ok_
#ifdef yy_cxx_ok_
#define yy_inline_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_inline_ok_ */

#ifndef yy_inline_ok_
#ifndef inline
#define inline
#endif /* inline */
#endif /* yy_inline_ok_ */

#ifndef yy_inline_return_ok_
#ifdef __GNUG__
#define yy_inline_return_ok_ 1
#endif /* __GNUG__ */
#endif /* yy_inline_return_ok_ */

#ifndef yy_max
#define yy_max(a,b) ((a) < (b) ? (b) : (a))
#endif /* yy_max */

#ifndef yy_memory_hdr_
#ifdef yy_bsd_hdrs_
#define yy_memory_hdr_ 1
#endif
#endif /* yy_memory_hdr_ */

#ifdef yy_memcpy_ok_ 
#define yy_memmove memcpy
#else
#define yy_memmove memmove
#endif  /* yy_memcpy_ok_ */

#ifndef yy_min
#define yy_min(a,b) ((a) < (b) ? (a) : (b))
#endif /* yy_min */

//  32 bit systems like Sparc do not have the near attribute,
//  compilers such as Microsoft Visual C++ need __near,
//  other compilers such as Borland C++ need _near,
//  and some compilers use plain near.

#ifndef yy_near
#ifndef yy_near_ok_
#define yy_near
#else /* yy_near_ok_ */
#ifdef yy_c700_extended_kws_
#define yy_near __near
#else
#ifdef yy_prefix_extended_kws_
#define yy_near _near
#else
#define yy_near near
#endif /* yy_prefix_extended_kws_ */
#endif /* yy_c700_extended_kws_ */
#endif /* yy_near_ok_ */
#endif /* yy_near */

#ifndef yy_new_ok_
#ifdef yy_cxx_ok_
#define yy_new_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_new_ok_ */

#ifndef yy_overload_ok_
#ifdef yy_cxx_ok_
#define yy_overload_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_overload_ok_ */

//  32 bit systems like Sparc do not have the pascal attribute,
//  compilers such as Microsoft Visual C++ need __pascal,
//  other compilers such as Borland C++ need _pascal,
//  and some compilers use plain pascal.

#ifndef yy_pascal
#ifndef yy_pascal_ok_
#define yy_pascal
#else /* yy_pascal_ok_ */
#ifdef yy_c700_extended_kws_
#define yy_pascal __pascal
#else
#ifdef yy_prefix_extended_kws_
#define yy_pascal _pascal
#else
#define yy_pascal pascal
#endif /* yy_prefix_extended_kws_ */
#endif /* yy_c700_extended_kws_ */
#endif /* yy_pascal_ok_ */
#endif /* yy_pascal */

#ifndef yy_paste_ok_
#ifdef yy_ansi_ok_
#define yy_paste_ok_ 1
#endif /* yy_ansi_ok_ */
#endif /* yy_paste_ok_ */

#ifndef yy_protected_members_ok_
#ifdef yy_cxx_ok_
#define yy_protected_members_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_protected_members_ok_ */

#ifndef yy_public_members_ok_
#ifdef yy_cxx_ok_
#define yy_public_members_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_public_members_ok_ */

#ifndef yy_private_members_ok_
#ifdef yy_cxx_ok_
#define yy_private_members_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_private_members_ok_ */

#ifndef yy_protos_ok_
#ifdef yy_ansi_ok_
#define yy_protos_ok_ 1
#endif
#ifdef __GNUC__
#define yy_protos_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_protos_ok_ 1
#endif
#endif

#ifndef yy_ptr_sized_int
#define yy_ptr_sized_int int
#endif /* yy_ptr_sized_int */

#ifndef yy_ref_ok_
#ifdef yy_cxx_ok_
#define yy_ref_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_ref_ok_ */

#ifndef yy_scope_name_ok_
#ifdef yy_cxx_ok_
#define yy_scope_name_ok_
#endif /* yy_cxx_ok_ */
#endif /* yy_scope_name_ok_ */

#ifndef yy_static_members_ok_
#ifdef yy_cxx_ok_
#define yy_static_members_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_static_members_ok_ */

#ifndef yy_stdarg_ok_
#ifndef yy_use_vararg_
#ifdef yy_ansi_ok_
#define yy_stdarg_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_stdarg_ok_ 1
#endif
#endif
#endif

#ifndef yy_stdlib_ok_
#ifdef yy_ansi_ok_
#define yy_stdlib_ok_ 1
#endif
#ifdef yy_bsd_hdrs_
#define yy_stdlib_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_stdlib_ok_ 1
#endif
#endif

#ifndef yy_stddef_ok_
#ifdef yy_ansi_ok_
#define yy_stddef_ok_ 1
#endif
#ifdef yy_bsd_hdrs_
#define yy_stddef_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_stddef_ok_ 1
#endif
#endif

#ifndef yy_string_ok_
#ifdef yy_ansi_ok_
#define yy_string_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_string_ok_ 1
#endif
#endif

#ifndef yy_stringize_ok_
#ifdef yy_ansi_ok_
#define yy_stringize_ok_ 1
#endif /* yy_ansi_ok_ */
#endif /* yy_stringize_ok_ */

#ifndef yy_struct_assign_ok_
#ifdef yy_ansi_ok_
#define yy_struct_assign_ok_ 1
#endif
#ifdef __GNUC__
#define yy_struct_assign_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_struct_assign_ok_ 1
#endif
#endif

#ifndef yy_sys5_files_
#ifdef yy_msdos_
#define yy_sys5_files_ 1
#endif
#endif

#ifndef yy_size_t_ok_
#ifdef yy_ansi_ok_
#define yy_size_t_ok_ 1
#endif
#ifdef yy_use_sunview_
#define yy_size_t_ok_ 1
#endif
#ifdef yy_use_xview_
#define yy_size_t_ok_ 1
#endif
#ifdef __GNUG__
#define yy_size_t_ok_ 1
#endif
#endif

#ifndef yy_size_t_ok_
#ifndef size_t
typedef long size_t;
#endif /* size_t */
#endif /* yy_size_t_ok_ */

#ifndef yy_this_ok_
#ifdef yy_cxx_ok_
#define yy_this_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_this_ok_ */

#ifdef yy_this_ok_
#define yy_this_one_param(yy_type)      void
#define yy_this_param(yy_type)
#define yy_this(yy_this_var)
#define yy_this_ref(yy_this_var)        (this)
#define yy_this_one_arg(yy_param)
#define yy_this_arg(yy_param)
#define yy_this_ptr(yy_param)           (yy_param)->
#else /* yy_this_ok_ */
#define yy_this_one_param(yy_type)      yy_type yy_this_var
#define yy_this_param(yy_type)          yy_type yy_this_var,
#define yy_this(yy_this_var)            (yy_this_var)->
#define yy_this_ref(yy_this_var)        (yy_this_var)
#define yy_this_one_arg(yy_param)       (yy_param)
#define yy_this_arg(yy_param)           (yy_param),
#define yy_this_ptr(yy_param)   
#endif /* yy_this_ok_ */

#ifndef yy_time_t_ok_
#ifdef yy_ansi_ok_
#define yy_time_t_ok_ 1
#endif
#ifdef yy_use_sunview_
#define yy_time_t_ok_ 1
#endif
#ifdef yy_use_xview_
#define yy_time_t_ok_ 1
#endif
#endif

#ifndef yy_time_t_ok_
#ifndef time_t
typedef long time_t;
#endif /* time_t */
#endif /* yy_time_t_ok_ */

#ifndef yy_virtual_ok_
#ifdef yy_cxx_ok_
#define yy_virtual_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_virtual_ok_ */

#ifndef yy_virtual_ok_
#ifndef virtual
#define virtual 
#endif /* virtual */
#endif /* yy_virtual_ok_ */

#ifndef yy_void_ok_
#ifdef yy_ansi_ok_
#define yy_void_ok_ 1
#endif
#ifdef yy_cxx_ok_
#define yy_void_ok_ 1
#endif
#ifdef yy_use_sunview_
#define yy_void_ok_ 1
#endif
#ifdef yy_use_xview_
#define yy_void_ok_ 1
#endif
#ifdef __GNUC__
#define yy_void_ok_ 1
#endif
#endif

#ifndef yy_void_ok_
#ifndef void
#define void
#endif
#ifndef yy_void_ptr
typedef char *yy_void_ptr;
#endif
#else
#ifndef yy_void_ptr
typedef void *yy_void_ptr;
#endif
#endif

#ifndef yy_volatile_ok_
#ifdef yy_ansi_ok_
#define yy_volatile_ok_ 1
#endif /* yy_ansi_ok_ */
#ifdef yy_cxx_ok_
#define yy_volatile_ok_ 1
#endif /* yy_cxx_ok_ */
#endif /* yy_volatile_ok_ */

#ifndef yy_volatile_ok_
#ifndef volatile
#define volatile
#endif /* volatile */
#endif /* yy_volatile_ok_ */

#ifndef yy_free_ptr
#ifdef yy_free_uses_char_ptr_
typedef char *yy_free_ptr;
#else
typedef yy_void_ptr yy_free_ptr;
#endif
#endif

#endif /* yy_ansi_h_ */

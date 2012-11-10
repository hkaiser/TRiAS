
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_cfg.h (Microsoft Visual C++ 8.0 -- 32 bit)
//
//  FILE DESCRIPTION:     insert file with system configuration macros.
//
//  MODIFICATION HISTORY:
//
//    09/11/97   bz/cc    added yy_streampos_minus_needs_temp_.
//    07/28/97   bz/cc    added yy_tolower_ok_ to use tolower() in place
//			  of explicit ASCII character tests which were not
//                        portable for environments such as EBCDIC.
//    07/28/97   bz/cc    added yy_io_h_ok_, yy_stringize_ok_, 
//                        yy_short_filenames_ to handle AIX changes
//			  to header files.
//    10/15/93   bz       added yy_ansi_ok_ (previously always done on
//                        the command line).  Disable that tiresome
//                        warning 4505 which lists functions in a class
//                        not called in a module.
//    10/08/92   bz       added yy_prefix_file_funcs_ and 
//                        yy_lseek_decl_needed_ to get C7 ANSI compatible
//                        names for UNIX file functions.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_cfg.h" contains the manifest constants which control the use of 
//  potentially non-portable features.  These constants customize the code
//  provided in the Yacc++ Language Objects Library to work with a specific
//  system.
// 
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_cfg_h_
#define yy_cfg_h_

#define yy_msdos_

#ifndef yy_ansi_ok_
#define yy_ansi_ok_
#endif

#pragma warning(disable:4505)
#pragma warning(disable:4514)
#pragma warning(disable:4705)

#define yy_ptr_sized_int long

#define yy_malloc_h_ok_

#define yy_memory_hdr_

#define yy_struct_assign_ok_

#define yy_size_t_ok_

#define yy_time_t_ok_

#define yy_setjmp_ok_

#define yy_systypes_ok_

#define yy_io_h_ok_

#define yy_prefix_extended_kws_

#define yy_short_filenames_

#define yy_tolower_ok_

#define yy_streampos_minus_needs_temp_

//
//  If your compiler supports standard Ansi C++ headers
//  and you are using them in your application (via STL
//  for example), you will need to turn on yy_use_ansicxx_hdrs_.
//  This will prevent mismatches of new and old headers
//  that cause compilation errors.  For example, <iostream> 
//  and <iostream.h> in the same app using MVC++.
//
//  #define yy_use_ansicxx_hdrs_

#ifdef _MSC_VER
#if 700 <= _MSC_VER
#define yy_prefix_file_funcs_
#define yy_c700_extended_kws_
#define yy_stringize_ok_
#endif
#endif

#endif /* yy_cfg_h_ */

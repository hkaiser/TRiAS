
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_bool.h
//
//  FILE DESCRIPTION:     insert file with boolean type definitions.
//
//  MODIFICATION HISTORY:
//
//    01/19/94   bz       added yy_ prefixes to boolean, true, and false
//                        to avoid redefinitions when LOL is combined with
//                        other class libraries.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_bool_h_
#define yy_bool_h_

//////////////////////////////////////////////////////////////////////////////
//
//  MANIFEST CONSTANTS
//
//  yy_false
//
//  yy_true
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_false
#define yy_false           (0)
#endif

#ifndef yy_true
#define yy_true            (1)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  DATA STRUCTURES
//
//  yy_boolean    type for a variable whose value can either be true or false.
//
//////////////////////////////////////////////////////////////////////////////

typedef int yy_boolean;

#endif

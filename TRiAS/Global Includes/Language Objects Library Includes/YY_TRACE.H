
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_trace.h
//
//  FILE DESCRIPTION:     insert file with trace flag for debugging
//                        with trace statements
//
//  MODIFICATION HISTORY:
//
//    06/08/98	 cc	  added yy_trace_(lex|psr)_user_actions_.
//    10/04/92   cc       print yy_trace_name when not using internal 
//                        debugger.
//    02/08/92   bz       added conditional define for yy_sym_dmp_.  
//    03/30/90   bz/cc    coding and final review completed.
//
//
//  Note : debugging traces are controlled by the #define constant yy_trace
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_trace_h_
#define yy_trace_h_

#include "yy_ansi.h"

//////////////////////////////////////////////////////////////////////////////
//
//  MANIFEST CONSTANTS
//
//  yy_trace_           is the debugging trace flag for Yacc++.  The higher
//                      the level number, the more trace information is 
//                      displayed as the lexer and parser are executing.  
//
//                      Each new level adds to the previous traces.  Customize
//                      the traces to suit your needs.  Re-arrange levels.  
//                      Insert tracing levels for your own code (we have left 
//                      gaps for that purpose)
//
//////////////////////////////////////////////////////////////////////////////

#define  yy_trace_none_            	0
#define  yy_trace_after_error_    	10

#define  yy_trace_cmd_line_       	20
#define  yy_trace_psr_rdc_        	30
#define  yy_trace_lex_rdc_        	40
#define  yy_trace_psr_user_actions_	50
#define  yy_trace_psr_actions_    	60
#define  yy_trace_lex_user_actions_    	70
#define  yy_trace_lex_actions_    	80
#define  yy_trace_all_            	90

#ifndef yy_trace_
#define  yy_trace_                yy_trace_none_
#endif /* yy_trace_ */

// for compatibility with old code

#define yy_trace_actions_	  yy_trace_lex_actions_

#endif /* yy_trace_h_ */

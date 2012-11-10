
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_help
//  
//  FILE DESCRIPTION:     prints help messages for prog
//
//  CALLING INTERFACE:  
//
//    void yy_help(void);
//        prints help message for invocation and command line options
//
//  MODIFICATION HISTORY:
//  
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.  
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_stdio.h"

#include "yy_help.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_help(void);
//  
//  yy_help prints help messages for the invocation and command line options.
//
//  yy_help has no input parameters.
//
//  yy_help has no return value.
//
//////////////////////////////////////////////////////////////////////////////

void yy_help(void)
{
    printf("\nInvoking PROG\n\n");
    printf("    prog ( -option )* filename ( -option )* \n\n");
    printf("Example:   prog prog.tst -nef -max_errors 15\n\n");
    printf("OPTIONS (asterisk indicates default)\n");
    printf("         2nd line shows abbreviated form\n\n");

    printf("-assist*, -no_assist\n");
    printf("-a*,      -na\n");
    printf("    provides syntax assists on error messages\n\n");

    printf("-assistfile pathname, -no_assistfile*\n");
    printf("-af pathname,         -naf*\n");
    printf("    provides alternate syntax assist file\n\n");

    printf("-errorfile pathname, -no_errorfile*\n");
    printf("-ef pathname,        -nef*\n");
    printf("    provides alternate errorfile\n\n");

    printf("-max_errors n  (defaults to -max_errors 25)\n");
    printf("-me n\n");
    printf("    instructs prog to abort after \"n\" errors\n\n");

    printf("-max_warnings n  (defaults to -max_warnings 100)\n");
    printf("-mw n\n");
    printf("    instructs prog to abort after \"n\" warnings\n\n");

    printf("-min_display n (defaults to -min_display 1)\n");
    printf("-md n\n");
    printf("    instructs prog to report errors of severity \"n\" and above\n\n");

    printf("-help\n");
    printf("-h\n");
    printf("    generates this message\n\n");

}   // yy_help

//  e4error.h  (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.  

#ifndef E4ERROR

#define E4ERROR

#ifndef D4DATA
   #include "d4data.h"
#endif

#ifdef __ZTC__
#ifdef WINDOWS
#ifdef _CONIO_H
   Error -- do not use conio.h with Windows
#endif
#endif
#endif


void D4DLL_EXP e4severe( const int, char *, ... ) ;    // Displays messages and exits

const double d4accuracy =  1e-13 ;

#define ERROR_HANDLING

#ifndef ERROR_HANDLING
// General Disk Access Errors
const int e4close  = -10 ;
const int e4create = -20 ;
const int e4length = -30 ;
const int e4length_set = -40 ;
const int e4lock   = -50 ;
const int e4open   = -60 ;
const int e4read   = -70 ;
const int e4remove = -80 ;
const int e4rename = -90 ;
const int e4seek   = -100 ;
const int e4unlock = -110 ;
const int e4write  = -120 ;

// Database Specific Errors
const int e4data = -200 ;
const int e4field_name= -210 ;  // Invalid field name
const int e4field_type= -220 ;
const int e4record_len= -230 ;

// Index File Specific Errors
const int e4entry = -300 ; // Tag entry not located
const int e4index = -310 ;
const int e4tag_name = -330 ;
const int e4unique   = -340 ; // Key is not unique


// Expression Errors
const int e4comma_expected =  -400 ;
const int e4complete  = -410 ;
const int e4data_name = -420 ;
const int e4num_parms =  -430 ;
const int e4overflow= -440 ; // Overflow while evaluating expression
const int e4right_missing =  -450 ;
const int e4type    =  -460 ;
const int e4unrec_function =  -470 ;
const int e4unrec_operator =  -480 ;
const int e4unrec_value =  -490 ;
const int e4unterminated =  -500 ;


// Critical Errors
const int e4info    = -910 ; // Unexpeceted information in internal variable
const int e4memory  = -920 ; // Out of memory
const int e4new     = -930 ; // Unexpected 'new' call
const int e4parm    = -940 ; // Unexpected parameter
const int e4result  = -950 ; // Unexpected result
#else
#include "errcodes.hxx"
#endif

#endif


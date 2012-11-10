// precompiled header für TRATIR ----------------------------------------------
// File: TRATASP.H

#if !defined(_TRATASP_H)
#define _TRATASP_H

#include <windows.h>
#include <containr.hxx>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <tstring>

#include <ospace/com/ComErrorMacros.h>
#include <Atl20.h>

//#include "dbtypes.h"
#include "atlpars.h" 
#include "atlerrs.h"

///////////////////////////////////////////////////////////////////////////////
//
#import "ExtDataConv.tlb" no_namespace named_guids raw_interfaces_only

///////////////////////////////////////////////////////////////////////////////
// usefull macros
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){}else{delete(x); (x)=NULL;}
#endif // DELETE_OBJ

#endif // _TRATASP_H

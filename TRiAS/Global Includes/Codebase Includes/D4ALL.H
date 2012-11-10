#ifndef D4ALL_INC
#define D4ALL_INC

#include <windows.h>

#ifdef WIN32
        #include <pshpack1.h>        
	#define __export
	#define __far
	#define huge  
#else
	#include <memory.h>
	#include <compobj.h>
	#include <scode.h>
#endif

#include <dbasedlm.h>

#ifdef MDX
#ifndef INDEX_EXTENSION
#define INDEX_EXTENSION "MDC"
#endif
#endif

#ifdef _DEBUG
	#define DEBUG
#endif

#ifndef D4DATA
#include "D4DATA.H"
#endif

#ifndef C4HINCL
#include "C4.H"
#endif

#ifndef D4DATAFI
#include "D4DATAFI.H"
#endif

#ifndef D4DATE
#include "D4DATE.H"
#endif

#ifndef E4ERROR
#include "E4ERROR.H"
#endif

#ifndef E4EXPR
#include "E4EXPR.H"
#endif

#ifndef E4PARSE
#include "E4PARSE.H"
#endif

#ifndef F4FILESE
#include "F4FILESE.H"
#endif

#ifndef I4INDEX
#include "I4INDEX.H"
#endif

#ifndef L4LINK
#include "L4LINK.H"
#endif

#ifndef M4MEMO
#include "M4MEMO.H"
#endif

#ifndef M4MEMORY
#include "M4MEMORY.H"
#endif

#ifndef S4SORT
#include "S4SORT.H"
#endif

#ifndef U4UTIL
#include "U4UTIL.H"
#endif

#ifdef WIN32
#include <poppack.h>               
#endif

#endif  // D4ALL_INC

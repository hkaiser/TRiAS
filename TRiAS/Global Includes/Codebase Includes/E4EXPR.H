// e4expr.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef E4EXPR

#define  E4EXPR

#ifndef D4DATA
#include "d4data.h"
#endif

class E4EXPORT Expr
{
   friend class Parse ;

public:   
   Expr( Data * ) ;
   operator double() ;      // Evaluates the expression as a double

   // The expression evaluation type is returned
   void  free()             { parsed.set_len(0) ; }
   int   key( Str& );       // Evaluates the expression as an index key
   int   parse() ;          // Parses the expression if necessary
   int   string( Str& );    // Evaluates the expression as an ASCII string
   int   ExprTrue( Str& ) ;     // Evaluates a logical expression to True/False
   int   vary( Str& );      // Evaluates the expression.  Result type varies.

   String    source ;       // The character version of the expression
   Data     *data ;         // The selected database when originally parsed
   CodeBase *code_base; 

   int   num_decimals ;         // used for CLIPPER version
private:
   String   parsed ;       // The parsed version of the expression
} ;

/* Integer Codes for Function/Operator parameters and returns */
const int  t4num_str   = int('n') ;
const int  t4num_doub  = int('F') ;
const int  t4num_clip  = int('c') ;
const int  t4num_bcd   = int('N') ;
const int  t4date_doub = int('D') ;
const int  t4date_str  = int('d') ;
const int  t4str       = int('C') ;
const int  t4log       = int('L') ;


#endif

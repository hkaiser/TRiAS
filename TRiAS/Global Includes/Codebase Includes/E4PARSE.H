//  e4parse.h  (c)Copyright Sequiter Software Inc., 1990-1991. All rights reserved.

#include <d4all.h>

#ifndef E4PARSE

#define E4PARSE

#ifndef D4DATA
#include "d4data.h"
#endif

#ifndef E4EXPR
#include "e4expr.h"
#endif

// This first section specifies the breakdown of the functions in file 'e4functi.c'.

// Codes for Immediate Data in Compile String
#define  I_FIELD_STR        0
#define  I_FIELD_LOG        1
#define  I_FIELD_DATE_D     2
#define  I_FIELD_DATE_S     3
#define  I_FIELD_NUM_D      4
#define  I_FIELD_NUM_S      5
#define  I_FIELD_MEMO       6

#define  LAST_I_FIELD       5

#define  I_STRING           6
#define  I_DOUBLE           7

#define  LAST_IMMEDIATE     7


#define  FIRST_LOG          8  // Range of Logical Operators
#define  LAST_LOG     	   12

#define  FIRST_OPERATOR    13  /* Range of Other Operators */
#define  LAST_OPERATOR     48

#define  FIRST_FUNCTION    49  /* Start of the List of Functions */

/* Additional Definitions */

#define   MAX_PARMS         3
#define   PARM_STACK_SIZE  20

class E4EXPORT  Data ;
class E4EXPORT  Field ;

class E4EXPORT Scan
{
public:
   void init( char *p, int p_len ) { source = p; len = p_len; pos = 0; }

   operator char() ;     // Returns the current character
   char     pop() ;      // Returns the current character and goes to the next
   void     skip()       { pos++ ; }
   void     skip(int l)  { pos+= l ; }
   char    *ptr()        { return source+pos ; }
   int      search( char ) ; // Returns # of characters scanned
   int      scan( char start_char, char end_char ) ;

   char    *source ;      // The original string
   int      pos, len ;    // Source expression position and length
} ;

class E4EXPORT Stack
{
public:
   void init( String *s_parm ) ;

   int  cur() ;
   int  pop() ;
   int  push(int) ;
   int  push( void *, int ) ;

public:
   String *s ;
} ;

typedef struct parse_parm_st
{
   char    *ptr ;
   int      type ;
} PARSE_PARM ;

class E4EXPORT ExprParm
{
public:
   unsigned pos ;       // Parameter position within the string
   int      type ;      // The type of the parameter
   unsigned len ;       // The number of bytes in the parameter
} ;

class E4EXPORT Parse
{
public:
   Parse( Expr& ) ;
   int      parse_do() ;

private:
   int      field_function(Field&) ;
   int      get_f_code( char *f_code_ptr, PARSE_PARM *parms ) ;
   int      get_operator(int *) ;
   int      lookup(char *,int,int,int) ;
   int      parse_expr() ;
   int      parse_function(char*,int) ;
   int      parse_value() ;
   int      type_check() ;

   Scan     s ;     // Character Expression
   Stack    op ;    // Operation stack
   String   op_string ;
   Stack    result ;

   CodeBase *code_base ;
   Data     *data ;
} ;

class E4EXPORT ExprParmList
{
public:
   ExprParmList(Data *, Str *result ) ;

   void      set( void *, unsigned len, int type ) ;
   void      set_logical( int i ) ;
   void      set_double( double d) ;
   void      set_type( int t )          { parms[on_parm].type =  t ; }
   void      set_len( unsigned new_len) ;

   void      fix_pos() ;    // undoes a pos_align if required!
   void      pos_align() ;
   int       parm_check() ;
   int       pop_parms( int ) ;
   int       push_parm() ;
   int       space_reserve( unsigned len ) ;

   char     *ptr( int i_parm ) ;
   int       len( int i_parm )        { return parms[on_parm+i_parm].len ; }
   int       pos()                    { return parms[on_parm].pos ; }
   int       n_parms()                { return on_parm ; }
   int       type( int i_parm )       { return parms[on_parm+i_parm].type ; }

   double   *double_ptr( int i_parm ) ;
   int      *int_ptr( int i_parm ) ;

   char     *date_format()            { return code_base->date_format() ; }
   Data     *data_ptr()               { return data ; }

private:
   ExprParm  parms[PARM_STACK_SIZE] ;
   Str      *result ;
   int       on_parm ;
   Data     *data ;
   CodeBase *code_base ;
} ;

typedef struct
{
   int      code ;
   int      name_len ;
   char     name[12] ;
   void     (*function_ptr)(ExprParmList&) ;
   int      priority ;
   int      return_type ;
   int      num_parms ;	     /* 0 - No Return;  -1 First Parm. Specifies # */
   int      type[MAX_PARMS] ;        /* type[0] is the return type */
}  E4FUNCTIONS ;

extern E4FUNCTIONS  __far v4functions[] ;

typedef void (*E4F)(ExprParmList &);

#define OPERATOR_LEN  128

/* Quasi Operators */
#define  Q_NO_FUNCTION  -2
#define  Q_L_BRACKET    -3
#define  Q_R_BRACKET    -4
#define  Q_COMMA        -5

void D4DLL_EXP  e4true(ExprParmList&) ;
void D4DLL_EXP  e4false(ExprParmList&) ;
void D4DLL_EXP  e4add(ExprParmList&) ;
void D4DLL_EXP  e4add(ExprParmList&) ;
void D4DLL_EXP  e4concatenate(ExprParmList&) ;
void D4DLL_EXP  e4sub(ExprParmList&) ;
void D4DLL_EXP  e4concat_two(ExprParmList&) ;
void D4DLL_EXP  e4multiply(ExprParmList&) ;
void D4DLL_EXP  e4divide(ExprParmList&) ;
void D4DLL_EXP  e4power(ExprParmList&) ;
void D4DLL_EXP  e4not_equal(ExprParmList&) ;
void D4DLL_EXP  e4equal(ExprParmList&) ;
void D4DLL_EXP  e4greater(ExprParmList&) ;
void D4DLL_EXP  e4less(ExprParmList&) ;
void D4DLL_EXP  e4greater_eq(ExprParmList&) ;
void D4DLL_EXP  e4less_eq(ExprParmList&) ;
void D4DLL_EXP  e4not(ExprParmList&) ;
void D4DLL_EXP  e4or(ExprParmList&) ;
void D4DLL_EXP  e4and(ExprParmList&) ;
void D4DLL_EXP  e4ctod(ExprParmList&) ;
void D4DLL_EXP  e4dtoc(ExprParmList&) ;
void D4DLL_EXP  e4dtos(ExprParmList&) ;
void D4DLL_EXP  e4stod(ExprParmList&) ;
void D4DLL_EXP  e4date(ExprParmList&) ;
void D4DLL_EXP  e4year(ExprParmList&) ;
void D4DLL_EXP  e4month(ExprParmList&) ;
void D4DLL_EXP  e4day(ExprParmList&) ;
void D4DLL_EXP  e4del(ExprParmList&) ;
void D4DLL_EXP  e4deleted(ExprParmList&) ;
void D4DLL_EXP  e4iif(ExprParmList&) ;
void D4DLL_EXP  e4reccount(ExprParmList&) ;
void D4DLL_EXP  e4recno(ExprParmList&) ;
void D4DLL_EXP  e4str(ExprParmList&) ;
void D4DLL_EXP  e4substr(ExprParmList&) ;
void D4DLL_EXP  e4time(ExprParmList&) ;
void D4DLL_EXP  e4upper(ExprParmList&) ;
void D4DLL_EXP  e4val(ExprParmList&) ;
void D4DLL_EXP  e4contain(ExprParmList&) ;
void D4DLL_EXP  e4trim(ExprParmList&);		//#JB930111

#endif

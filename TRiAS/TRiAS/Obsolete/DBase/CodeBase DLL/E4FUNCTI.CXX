// e4functi.c  (c)Copyright Sequiter Software Inc., 1990-1991.		All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <time.h>
#include <limits.h>
}

#ifndef NO_POW
#ifndef WIN32
extern "C" {
#endif
#include <math.h>
#ifndef WIN32
}
#endif
#endif

E4FUNCTIONS  __far v4functions[] =
{
   /* I_FIELD_STR, 0 */
   {  0, 0,	 "",  (E4F)0,	  0,  t4str, 0 },

   /* I_FIELD_LOG, 1 */
   {  1, 0,	 "",  (E4F)0,	  0,  t4log, 0 },

   /* I_FIELD_DATE_D, 2 */
   {  2, 0,	 "",  (E4F)0,	  0,  t4date_doub, 0 },

   /* I_FIELD_DATE_S, 3 */
   {  3, 0,	 "",  (E4F)0,	  0,  t4date_str, 0 },

   /* I_FIELD_NUM_D, 4 */
   {  4, 0,	 "",  (E4F)0,	  0,  t4num_doub, 0 },

   /* I_FIELD_NUM_S, 5 */
   {  5, 0,	 "",  (E4F)0,	  0,  t4num_str, 0 },

   /* I_STRING, 6 */
   {  6, 0,	 "",  (E4F)0,	  0,  t4str, 0 },

   /* I_DOUBLE, 7 */
   {  7, 0,	 "",  (E4F)0,	  0,  t4num_doub, 0 },

   {  8, 6,	 ".TRUE.", (E4F)e4true,  0,  t4log, 0 },
   {  8, 3,	 ".T.",	(E4F)e4true,  0,  t4log, 0 },
   { 10, 7,	 ".FALSE.",(E4F)e4false, 0,  t4log, 0 },
   { 10, 3,	 ".F.",	(E4F)e4false, 0,  t4log, 0 },
   { 12, 5,	 ".NOT.",  (E4F)e4not,   5,  t4log, 1, { t4log } },

   #ifdef NO_POW
   { 17, 0,"", (E4FUNC *) 0,	   9, t4num_doub, 2, { t4num_doub, t4num_doub } },
   { 17, 0,"", (E4FUNC *) 0,	   9, t4num_doub, 2, { t4num_doub, t4num_doub } },
   #else
   { 17, 1,"^",	   (E4F)e4power,	   9, t4num_doub, 2, { t4num_doub, t4num_doub } },
   { 17, 2,"**",	  (E4F)e4power,	   9, t4num_doub, 2, { t4num_doub, t4num_doub } },
   #endif

   { 19, 1,"#",	   (E4F)e4not_equal,  6, t4log, 2, { t4str, t4str } },
   { 19, 2,"<>",	  (E4F)e4not_equal,  6, t4log, 2, { t4str, t4str } },
   { 19, 2,"<>",	  (E4F)e4not_equal,  6, t4log, 2, { t4num_doub, t4num_doub } },
   { 19, 2,"<>",	  (E4F)e4not_equal,  6, t4log, 2, { t4date_doub, t4date_doub } },
   { 19, 2,"<>",	  (E4F)e4not_equal,  6, t4log, 2, { t4log, t4log } },

   { 21, 2,">=",	  (E4F)e4greater_eq, 6, t4log, 2, { t4str, t4str } },
   { 21, 2,">=",	  (E4F)e4greater_eq, 6, t4log, 2, { t4num_doub, t4num_doub } },
   { 21, 2,">=",	  (E4F)e4greater_eq, 6, t4log, 2, { t4date_doub, t4date_doub } },

   { 23, 2,"<=",	  (E4F)e4less_eq,	6, t4log, 2, { t4str, t4str } },
   { 23, 2,"<=",	  (E4F)e4less_eq,	6, t4log, 2, { t4num_doub, t4num_doub } },
   { 23, 2,"<=",	  (E4F)e4less_eq,	6, t4log, 2, { t4date_doub, t4date_doub } },

   { 25, 1,"+",	   (E4F)e4add,		 7, t4num_doub,  2, { t4num_doub, t4num_doub } },
   { 25, 1,"+",	   (E4F)e4add,		 7, t4date_doub, 2, { t4num_doub, t4date_doub } },
   { 25, 1,"+",	   (E4F)e4add,		 7, t4date_doub, 2, { t4date_doub, t4num_doub } },
   { 25, 1,"+",	   (E4F)e4concatenate, 7, t4str,	   2, { t4str, t4str } },

   { 30, 1,"-",	   (E4F)e4sub,		 7, t4num_doub,  2, { t4num_doub,	t4num_doub } },
   { 30, 1,"-",	   (E4F)e4sub,		 7, t4num_doub,  2, { t4date_doub, t4date_doub } },
   { 30, 1,"-",	   (E4F)e4sub,		 7, t4date_doub, 2, { t4date_doub, t4num_doub } },
   { 30, 1,"-",	   (E4F)e4concat_two,  7, t4str, 2, { t4str, t4str } },

   { 40, 1,"*",	   (E4F)e4multiply,	8, t4num_doub, 2, { t4num_doub, t4num_doub } },
   { 50, 1,"/",	   (E4F)e4divide,	  8, t4num_doub, 2, { t4num_doub, t4num_doub } },

   { 70, 1,"$",	   (E4F)e4contain,	6, t4log, 2, { t4str, t4str } },

   { 80, 1,"=",	   (E4F)e4equal,	  6, t4log, 2, { t4str, t4str } },
   { 80, 1,"=",	   (E4F)e4equal,	  6, t4log, 2, { t4num_doub, t4num_doub } },
   { 80, 1,"=",	   (E4F)e4equal,	  6, t4log, 2, { t4date_doub, t4date_doub } },
   { 80, 1,"=",	   (E4F)e4equal,	  6, t4log, 2, { t4log, t4log } },

   {100, 1,">",	   (E4F)e4greater,	6, t4log, 2, { t4str, t4str } },
   {100, 1,">",	   (E4F)e4greater,	6, t4log, 2, { t4num_doub, t4num_doub } },
   {100, 1,">",	   (E4F)e4greater,	6, t4log, 2, { t4date_doub, t4date_doub } },

   {110, 1,"<",	   (E4F)e4less,	   6, t4log, 2, { t4str, t4str } },
   {110, 1,"<",	   (E4F)e4less,	   6, t4log, 2, { t4num_doub, t4num_doub } },
   {110, 1,"<",	   (E4F)e4less,	   6, t4log, 2, { t4date_doub, t4date_doub } },
   {150, 4,".OR.",	(E4F)e4or,		 3, t4log, 2, { t4log, t4log } },
   {160, 5,".AND.",   (E4F)e4and,		4, t4log, 2, { t4log, t4log } },

   {170, 4,"STOD",	(E4F)e4stod,	0,  t4date_doub, 1, { t4str } },
   {175, 4,"CTOD",	(E4F)e4ctod,	0,  t4date_doub, 1, { t4str } },
   {180, 4,"DTOS",	(E4F)e4dtos,	0,  t4str, 1, { t4date_str } },
   {180, 4,"DTOS",	(E4F)e4dtos,	0,  t4str, 1, { t4date_doub } },
   {185, 4,"DTOC",	(E4F)e4dtoc,	0,  t4str, 1, { t4date_str } },
   {185, 4,"DTOC",	(E4F)e4dtoc,	0,  t4str, 1, { t4date_doub } },
   {190, 4,"DATE",	(E4F)e4date,	0,  t4date_doub, 0 },
   {194, 3,"DAY",	 (E4F)e4day,	 0,  t4num_doub, 1, { t4date_doub } },
   {194, 3,"DAY",	 (E4F)e4day,	 0,  t4num_doub, 1, { t4date_str } },
   {196, 5,"MONTH",   (E4F)e4month,   0,  t4num_doub, 1, { t4date_doub } },
   {196, 5,"MONTH",   (E4F)e4month,   0,  t4num_doub, 1, { t4date_str } },
   {198, 4,"YEAR",	(E4F)e4year,	0,  t4num_doub, 1, { t4date_doub } },
   {198, 4,"YEAR",	(E4F)e4year,	0,  t4num_doub, 1, { t4date_str } },

   {200, 7,"DELETED", (E4F)e4deleted, 0,  t4log, 0 },
   {210, 3,"DEL",	 (E4F)e4del,	 0,  t4str, 0 },
   {220, 3,"IIF",	 (E4F)e4iif,	 0,  t4str, 3, { t4log, t4str, t4str } },
   {220, 3,"IIF",	 (E4F)e4iif,	 0,  t4num_doub, 3, { t4log, t4num_doub, t4num_doub } },
   {220, 3,"IIF",	 (E4F)e4iif,	 0,  t4log, 3, { t4log, t4log, t4log } },
   {220, 3,"IIF",	 (E4F)e4iif,	 0,  t4date_doub, 3, { t4log, t4date_doub, t4date_doub } },
   {230, 8,"RECCOUNT",(E4F)e4reccount,0,  t4num_doub,  0 },
   {240, 5,"RECNO",   (E4F)e4recno,   0,  t4num_doub,  0 },
   {250, 3,"STR",	 (E4F)e4str,	 0,  t4str, 3, { t4num_doub, t4num_doub, t4num_doub } },
   {260, 6,"SUBSTR",  (E4F)e4substr,  0,  t4str, 3, { t4str, t4num_doub, t4num_doub } },
   {270, 4,"TIME",	(E4F)e4time,	0,  t4str, 0 },
   {280, 5,"UPPER",   (E4F)e4upper,   0,  t4str, 1, { t4str } },
   {290, 3,"VAL",	 (E4F)e4val,	 0,  t4num_doub, 1, { t4str } },
   {300, 4,"TRIM",   (E4F)e4trim,   0,  t4str, 1, { t4str } }, //#JB930111
   {-1},
} ;

ExprParmList::ExprParmList( Data *data_parm, Str *str )
{
   result =  str ;
   data   =  data_parm ;
   code_base = data->code_base ;
   on_parm=  0 ;
   memset( parms, 0, sizeof(parms) ) ;
}

int  ExprParmList::space_reserve( unsigned new_len )
{
   if ( code_base->error() )  return -1 ;
   set_len( new_len ) ;
   if ( result->len() < new_len+ pos() )
	  if ( result->set_len( new_len+ pos() ) < 0  )
		 return code_base->error( e4overflow, "Allocating space for expression evaluation.", (char *) 0 ) ;
   return  0 ;
}

void ExprParmList::set( void *data_ptr, unsigned len, int parm_type )
{
   if ( space_reserve(len) < 0 )  return ;

   memmove( ptr(0), data_ptr, len ) ;
   set_type( parm_type ) ;
}

void ExprParmList::set_len( unsigned new_len )
{
   parms[on_parm].len =  new_len ;
}

void ExprParmList::set_logical( int true_or_false )
{
   pos_align() ;
   if ( space_reserve(sizeof(int)) < 0 )  return ;

   int *i_ptr =  int_ptr(0) ;
   *i_ptr	 =  true_or_false ;
   set_type( t4log ) ;
}

void ExprParmList::set_double( double d )
{
   pos_align() ;
   if ( space_reserve(sizeof(double)) < 0 )  return ;
   *double_ptr(0) =  d ;
   set_type( t4num_doub ) ;
}

char *ExprParmList::ptr( int i_parm )
{
   return result->ptr()+parms[on_parm+i_parm].pos ;
}

void ExprParmList::fix_pos()
{
   if ( parms[on_parm+1].pos != ( parms[on_parm].pos + parms[on_parm].len ) )
   {
	  memcpy( ptr(0)+parms[on_parm].len, ptr(1), parms[on_parm+1].len ) ;
	  parms[on_parm+1].pos = parms[on_parm].pos + parms[on_parm].len ;
   }
}

void ExprParmList::pos_align()
{
   int  extra_len = sizeof(double) - parms[on_parm].pos % sizeof(double) ;
   if ( extra_len == sizeof(double) )  extra_len =  0 ;
   parms[on_parm].pos   +=  extra_len ;
}

ExprParmList::parm_check()
{
   if ( code_base->error() )  return -1 ;
   if ( on_parm+2 >= PARM_STACK_SIZE || on_parm < 0 )
	  return code_base->error( e4overflow, (char *) 0 ) ;
   return 0 ;
}

int *ExprParmList::int_ptr( int i_parm )
{
   return (int *) ptr(i_parm) ;
}

double *ExprParmList::double_ptr( int i_parm )
{
   return (double *) ptr(i_parm) ; 
}

ExprParmList::pop_parms( int n )
{
   on_parm -= n ;
   if ( parm_check() < 0 )  return -1 ;
   return 0 ;
}

int  ExprParmList::push_parm()
{
   if ( parm_check() < 0 )  return -1 ;
   parms[on_parm+1].pos =  parms[on_parm].pos + parms[on_parm].len ;
   on_parm++ ;
   return 0 ;
}


/* Function rules

   1.  Place the result back into the first parameter.
   2.  If the result is of length greater than the length of
	   the first parameter, be aware that the result will overwrite
	   the second, ...
   3.  If the type of the result is different than the type
	   of the first parameter, set the type.
   4.  If the length of the result is different from the length
	   of the first parameter, set the resulting length.
   5.  If there is an error, set a length of '-1'.
*/

void  e4true( ExprParmList& list )
{
   list.set_logical( 1 ) ;
}

void  e4false( ExprParmList& list )
{
   list.set_logical( 0 ) ;
}

void  e4add( ExprParmList& list )
{
   list.set_double( *list.double_ptr(0) + *list.double_ptr(1) ) ;
   if ( list.type(1) == t4date_doub )
	  list.set_type( t4date_doub ) ;
}

void  e4concatenate( ExprParmList& list )
{
   list.fix_pos() ;
   list.set_len( list.len(0) + list.len(1) ) ;
}

void  e4sub( ExprParmList& list )
{
   int final_type =  t4date_doub ;
   if ( list.type(0) == list.type(1) )
	  final_type =  t4num_doub ; 

   list.set_double( *list.double_ptr(0) - *list.double_ptr(1) ) ;
   list.set_type( final_type ) ;
}

void  e4concat_two( ExprParmList& list )
{
   char *ptr =  list.ptr(0) ;
   int pos ;
   for ( pos = list.len(0)-1; pos >= 0; pos-- )
	  if ( ptr[pos] != ' ' && ptr[pos] != 0 )  break ;

   int n_blanks =   list.len(0) - ++pos ;
   ptr +=  pos ;

   memmove( ptr, list.ptr(1), list.len(1) ) ;
   memset( ptr+list.len(1), (int) ' ', (size_t) n_blanks ) ;
   list.set_len( list.len(0) + list.len(1) ) ;
}

void  e4multiply( ExprParmList& list )
{
   *list.double_ptr(0) *=  *list.double_ptr(1) ;
}

void  e4divide( ExprParmList& list )
{
   *list.double_ptr(0) /= *list.double_ptr(1) ;
}

#ifndef NO_POW
void  e4power( ExprParmList& list )
{
   *list.double_ptr(0) =  pow( *list.double_ptr(0), *list.double_ptr(1) ) ;
}
#endif

void  e4not_equal( ExprParmList& list )
{
   int  rc ;

   switch( list.type(1) )
   {
	  case t4str:
	  {				
		 int len =  (list.len(0) < list.len(1)) ? list.len(0) : list.len(1) ;
		 rc =  memcmp( list.ptr(0), list.ptr(1), (size_t) len) ;

		 if ( rc == 0 )
			if ( list.len(0) != list.len(1) ) //#JB920310
			   rc = -1 ;
	   }				
		 break ;

	  case t4num_doub:
	  case t4date_doub:
	  {				
		 if ( *list.double_ptr(0) <  *list.double_ptr(1) )
			rc =  -1 ;
		 else
		 {
			if ( *list.double_ptr(0) == *list.double_ptr(1) )
			   rc =  0 ;
			else
			   rc =  1 ;
		 }
	  }				
		 break ;

	  case t4log:
	  {				
		 /*  Equal if .T. and .T. or .F. .and .F. */
		 rc = ! (*list.int_ptr(0) &&  *list.int_ptr(1) ||
			   ! *list.int_ptr(0) &&  ! *list.int_ptr(1) ) ;
	  }				
		 break ;
   }	   

   list.set_logical( rc ) ;
}

void  e4equal( ExprParmList& list )
{
   e4not_equal( list ) ;
   *list.int_ptr(0) =  ! *list.int_ptr(0) ;
}

void  e4greater( ExprParmList& list )
{
   e4not_equal( list ) ;
   *list.int_ptr(0) =  *list.int_ptr(0) > 0 ;
}

void  e4less( ExprParmList& list )
{
   e4not_equal( list ) ;
   *list.int_ptr(0) =  *list.int_ptr(0) < 0 ;
}

void  e4greater_eq( ExprParmList& list )
{
   e4not_equal( list ) ;
   *list.int_ptr(0) =  *list.int_ptr(0) >= 0 ;
}

void  e4less_eq( ExprParmList& list )
{
   e4not_equal( list ) ;
   *list.int_ptr(0) =  *list.int_ptr(0) <= 0 ;
}

void  e4not( ExprParmList& list )
{
   *list.int_ptr(0) =   ! *list.int_ptr(0) ;
}

void  e4or( ExprParmList& list )
{
   *list.int_ptr(0) =   *list.int_ptr(0)  ||  *list.int_ptr(1) ;
}

void  e4and( ExprParmList& list )
{
   *list.int_ptr(0) =   *list.int_ptr(0)  &&  *list.int_ptr(1) ;
}

void  e4stod( ExprParmList& list )
{
   list.set_double( double(long( Date(list.ptr(0)) )) ) ;
   list.set_type( t4date_doub ) ;
}

void  e4dtos( ExprParmList& list )
{
   if ( list.type(0) == t4date_doub )
   {
	  double d =  *list.double_ptr(0) ;
	  long l =  long(d) ;
	  Date dt( l ) ;
	  void *temp_ptr =  dt.ptr() ;
	  unsigned temp_len = dt.len() ;
	  list.set( temp_ptr, temp_len, t4str ) ;
   }
   else
	  list.set_type( t4str ) ;
}

void  e4ctod( ExprParmList& list )
{
   Date dt ;
   dt.init( list.ptr(0), list.date_format() ) ;
   list.set_double( double(long(dt)) ) ;
   list.set_type( t4date_doub ) ;
}

void  e4dtoc( ExprParmList& list )
{
   e4dtos( list ) ;
   Date dt( list.ptr(0) ) ;

   int len =  strlen( list.date_format() ) ;
   if ( list.space_reserve( len ) < 0 ) return ;
   dt.format( StrLen(list.ptr(0),len), list.date_format() ) ;
   list.set_len( len ) ;
}

void  e4date( ExprParmList& list )
{
   Date dt ;
   dt.init_today() ;
   list.set_double( double( long(dt)) ) ;
   list.set_type( t4date_doub ) ;
}

void  e4day( ExprParmList& list )
{
   e4dtos( list ) ;
   list.set_double( c4atod( list.ptr(0)+6, 2) ) ;
}

void  e4month( ExprParmList& list )
{
   e4dtos( list ) ;
   list.set_double( c4atod( list.ptr(0)+4, 2) ) ;
}

void  e4year( ExprParmList& list )
{
   e4dtos( list ) ;
   list.set_double( c4atod( list.ptr(0), 4) ) ;
}

void  e4del( ExprParmList& list )
{
   list.set( list.data_ptr()->record.ptr(), 1, t4str ) ;
}

void  e4deleted( ExprParmList& list )
{
   list.set_logical( list.data_ptr()->deleted() ) ;
}

void  e4iif( ExprParmList& list )
{
   int i =  *list.int_ptr(0) ? 1 : 2 ;
   list.set( list.ptr(i), list.len(i), list.type(i) ) ;
}

void  e4reccount( ExprParmList& list )
{
   list.set_double( (double) list.data_ptr()->reccount() ) ;
}

void  e4recno( ExprParmList& list )
{
   list.set_double( (double) list.data_ptr()->recno() ) ;
}

void  e4str( ExprParmList& list )
{
   int len =  (int) *list.double_ptr(1) ;

   if ( list.space_reserve( len ) < 0 )  return ;
   int i_temp = (int) *list.double_ptr(2) ;
   c4dtoa( *list.double_ptr(0), list.ptr(0), len, i_temp) ;

   list.set_type( t4str ) ;
   list.set_len( len ) ;
}

void  e4substr( ExprParmList& list )
{
   int i_temp = (int) *list.double_ptr(1) ;
   int start_pos =  i_temp - 1 ;
   if ( start_pos < 0 )  start_pos =  0 ;
   if ( start_pos > list.len(0) )  start_pos =  list.len(0) ;

   int len = (int) *list.double_ptr(2) ;
   if ( len > list.len(0) - start_pos )
	  len =  list.len(0) - start_pos ;

   list.set( list.ptr(0)+start_pos, len, t4str ) ;
}

void  e4time( ExprParmList& list )
{
   Time ti ;
   ti.init_now() ;
   list.set( ti.ptr(), ti.len(), t4str ) ;
}

void  e4upper( ExprParmList& list )
{
   if ( list.space_reserve( list.len(0)+1 ) < 0 )  return ;   // allocate for \0
   list.set_len( list.len(0) - 1 ) ;  // remove extra '\0' space for dBASE IV compatibility
   list.ptr(0)[list.len(0)] = 0 ;
   strupr( list.ptr(0) ) ;
}

//#JB930111 abschneiden abschließender Nullen
void e4trim (ExprParmList& list)
{
	register char *pBeg = list.ptr (0);
	register char *pEnd = pBeg + list.len (0) - 1;
	register short Count = 0;		// Anz. Leerzeichen

//  Anzahl Leerzeichen zählen
	while (pBeg <= pEnd && *pEnd == ' ') {
		Count++;
		pEnd--;
	}

//  ggf. neue Länge setzen
	if (Count) {
		list.set_len (list.len (0) - Count);
		*++pEnd = '\0';
	}
}

void  e4val( ExprParmList& list )
{
   list.set_double( c4atod(list.ptr(0), list.len(0)) );
}

/* Is the first string contained in the second */
void  e4contain( ExprParmList& list )  
{
   StrLen s1( list.ptr(0), list.len(0) ) ;
   StrLen s2( list.ptr(1), list.len(1) ) ;

   if ( s2.search( s1 ) >= 0 )
	  list.set_logical(1) ;
   else
	  list.set_logical(0) ;
}

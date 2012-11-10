// e4expr.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

extern "C" {
#include <string.h>
#include <stdlib.h>
}

__export Expr::Expr( Data *d ) : source( d->code_base ), parsed( d->code_base )
{
   data =  d ;
   code_base=  d->code_base ;
}

int Expr::key( Str& result)
{
   if ( code_base->error() )  return -1 ;

   #ifndef OTHER_NDX
	  BCD  bcd ;  StrMax sbcd( &bcd, sizeof(bcd) ) ;
   #endif
   int result_type =  vary( result ) ;

   switch( result_type )
   {
	  case t4num_str:
	  {
		 #ifdef NDX
			 double d_num = c4atod( result.ptr(), result.len() ) ;
			 if ( result.assign( StrLen((char *) &d_num, sizeof(d_num))) < 0 )
			   return code_base->error( e4memory, "Evaluating Tag Expression", (char *) 0 ) ;
			 result_type = t4num_doub ;
			 result.set_len( 8 ) ;
		  #elif defined CLIPPER
			 c4clip( result.ptr(), result.len() ) ;
			 result_type = t4num_clip ;
		 #else
			 c4stob( sbcd, result ) ;
			if ( result.assign(sbcd) < 0 )  
			   return code_base->error( e4memory, "Evaluating Tag Expression", (char *) 0 ) ;
			result_type =  t4num_bcd ;
		  #endif
	  }		 
		 break ;

	  case t4num_clip:
	  {
		 #ifndef CLIPPER
			 e4severe( e4info, "Clipper numeric format in non-Clipper index file", (char *) 0 ) ;
		  #endif
	   }
		  break ;

	  case t4num_doub:
	  {
		 #ifdef NDX
		  #elif defined CLIPPER
			 result.set_len( 8 ) ;
			 if ( string( result ) != t4num_str )
			   return code_base->error( e4info, "Evaluating Tag Expression", (char *) 0 ) ;
			 result_type = t4num_clip ;
		 #else
			 double *d_ptr =  (double *) result.ptr() ;
			c4dtob( sbcd, *d_ptr ) ;
			 if ( result.assign(sbcd) < 0 )
			   return code_base->error( e4memory, "Evaluating Tag Expression", (char *) 0 ) ;
			result_type =  t4num_bcd ;
		  #endif
	  } 
		 break ;

	  #ifdef CLIPPER
		 case t4date_doub:
		 {
			double  index_date ;
			memcpy( &index_date, result.ptr(), sizeof(double) ) ;
			long  l =  index_date ;
			Date dt( l ) ;
			result.assign( dt ) ;
			result_type = t4date_str ;
		  }
			break ;
	  #else
		 case t4date_str:
		 {
			 double d =  double( long(Date(result.ptr())) ) ;
			 if ( result.assign( StrLen((char *) &d, sizeof(d))) < 0 )
			   return code_base->error( e4memory, "Evaluating Tag Expression", (char *) 0 ) ;
			 result_type =  t4date_doub ;
		  }
			break ;
	  #endif
   }

   return result_type ;
}

int __export Expr::parse()
{
   if ( source.null_ensure() < 0 )  return -1 ;
   free() ;
   Parse parse_data( *this ) ;
   return parse_data.parse_do() ;
}

Expr::string( Str& result )
{
   int result_type =  vary(result) ;

   if ( result_type == t4num_doub )
   {												
	  int   dig_len, is_neg, zeros_len, i, dec_pos, /*dig_pos, */dec_len ;

	  #ifdef CLIPPER
		 int result_len =  data->code_base->numeric_str_len ;
		  if ( num_decimals > 0 ) result_len += ( 1 + num_decimals ) ;
	  #else
		 int result_len =  data->code_base->numeric_str_len ;
	  #endif
	  if ( result.set_len( result_len+1 ) < 0 )
		 return code_base->error( e4memory, "Evaluating Expression", (char *) 0 ) ;
	  result.ptr()[result_len] =  0 ;
	  result.set_len( result_len ) ;
	  #ifndef CLIPPER
		 num_decimals =  data->code_base->decimals ;
	  #endif
	  char *str =  fcvt( *((double *) result.ptr()), num_decimals, &dig_len, &is_neg) ;

	  zeros_len =  result_len - dig_len - 1 - num_decimals ;

	  #ifdef CLIPPER
		 memset( result.ptr(), '0',zeros_len ) ;
	  #else
		 memset( result.ptr(), ' ',zeros_len ) ;
	  #endif

	  if ( num_decimals > 0 )
	  {
		 dec_pos =  result_len - num_decimals - 1 ;
		 result.replace( StrChar( '.' ), dec_pos) ;
	  }
	  else
		 dec_pos =  result_len ;

	  char *ptr =  result.ptr() + zeros_len ;

	  if ( dig_len >= 0 )
	  {
		 if ( (dec_pos - dig_len) < 0 )
		 {
			memset( ptr, (int) '*', (size_t) result_len) ;
			return t4num_str ;
		 }
		 memcpy( ptr, str, (size_t) dig_len ) ;
		 ptr += dig_len ;
		 *ptr = '.' ;
		 memcpy( ++ptr, str+dig_len, (size_t) num_decimals ) ;
	  }
	  else
	  {
		 dec_len =  num_decimals + dig_len ;
		 if ( dec_len > 0 )
			memcpy( ptr - dig_len, str, dec_len ) ;
	  }

	  if ( is_neg )
	  {
		 for ( i=0; i< result_len; i++ )
		   ptr[i] = (char) 0x5c - ptr[i] ;
	  }
	  return t4num_str ;
   }

   if ( result_type == t4date_doub )
   {
	  double  index_date ;
	  memcpy( &index_date, result.ptr(), sizeof(double) ) ;
	  long  l =  (long) index_date ;		// #JB959626
	  Date dt( l ) ;
	  result.assign( dt ) ;
	  return  t4date_str ;
   }

   if ( result_type == t4log )
   {
	  int *i_ptr =  (int *) result.ptr() ;
	  if ( *i_ptr )
		 result.assign( StrChar('Y') ) ;
	  else
		 result.assign( StrChar('N') ) ;
   }

   return( result_type ) ;
}

__export Expr::ExprTrue( Str& result )
{
   int rc = vary( result ) ;  if ( rc < 0 )  return -1 ;
   if ( rc != t4log )
	  return code_base->error( e4result, "Expr::ExprTrue()", "Expecting logical result.", (char *) 0 ) ;

   int *i_ptr =  (int *) result.ptr() ;
   return *i_ptr ;
}

/*   1.  Get function type and parameter information.
	 2.  Recursively call to get the parameters.
	 3.  Call function with the parameters.
	 4.  Return the result.

	 result_ptr   points to where the value should be returned.
	 return_len   is the length of the available space.

	 If the function returns a value of a specific length, the
	 parameter space will not overlap the last parameter.  Otherwise,
	 64 bytes of space will be allocated for the return value.  If
	 more is returned, the expression evaluation function return
	 will overlap the last parameter and perhaps other parameters as well.

	 Returns
		 -1	Error
		>= 0   The length of the return value.
*/

int  Expr::vary( Str& result )
{
   #ifdef CLIPPER
	  int old_dec = code_base->decimals ;
   #endif
   if ( code_base->error() )  return -1 ;
   #ifdef DEBUG
	  if ( source.len() == 0 )  e4severe( e4info, "Expr::vary", "No expression", (char *) 0 ) ;
   #endif

   if ( parsed.len() == 0 )  if ( parse() < 0 )  return -1 ;

   char *compile_ptr = parsed.ptr() ;

   ExprParmList list( data, &result ) ;

   for (;;)
   {
	  int f_code ;
	  memcpy( &f_code, compile_ptr, sizeof(int) ) ;
	  compile_ptr +=  sizeof(int) ;
  
	  if ( f_code > LAST_IMMEDIATE )
	  {
		 if ( list.pop_parms( v4functions[f_code].num_parms ) < 0 ) return -1 ;
		 (*v4functions[f_code].function_ptr)( list ) ;
		 if ( code_base->error() )  return -1 ;
		 list.push_parm() ;
		 continue ;
	  }

	  if ( f_code < 0 )
	  {
		 if ( list.pop_parms(1) < 0 )  return -1 ;

		 #ifdef DEBUG
			if ( list.n_parms() != 0  &&  list.pos() != 0 )
			   e4severe( e4info, "Expr::vary", (char *) 0 ) ;
		 #endif

		 unsigned final_len =  list.len(0) ;
		  if ( result.set_len( final_len+1 ) < 0 )  return -1 ;
		 result.ptr()[final_len] =  0 ;
		 result.set_len( final_len ) ;
		 #ifdef CLIPPER
			code_base->decimals = old_dec ;
		 #endif
		 return  list.type(0) ;
	  }

	  /* Field or Immediate Data */
	  if ( f_code <= LAST_I_FIELD )
	  {
		 Field *field ;
		  memcpy( &field, compile_ptr, sizeof(field) ) ;
		  compile_ptr +=  sizeof(field) ;

		  #ifdef CLIPPER
			  num_decimals = field->decimals() ;
			  if ( num_decimals == 0 ) num_decimals = code_base->decimals ;
			  else if ( code_base->decimals == 0 )
				 code_base->decimals = 2 ;
		  #endif

		 switch( f_code )
		 {
			case I_FIELD_STR:
			case I_FIELD_NUM_S:
			case I_FIELD_DATE_S:
			{
			   list.set( field->ptr(), field->len(), -1 ) ;
				if ( f_code == I_FIELD_NUM_S )
				   if ( field->decimals() > 0 )
					 list.ptr(0)[field->len() - field->decimals()-1] = '.' ;
			}		   
				break ;

			case I_FIELD_NUM_D:
			{		   
//			  #ifdef CLIPPER
//				 e4severe( e4info, "expr:vary()", "invalid type", (char *) 0 ) ;
//			  #endif
			   list.set_double( double(*field) ) ;
			 }		  
			   break ;

			case I_FIELD_DATE_D:
			{
//			  #ifdef CLIPPER
//				 e4severe( e4info, "expr:vary()", "invalid type", (char *) 0 ) ;
//			  #endif
			   list.set_double( double( long(*field) ) ) ;
			}
				break ;

			case I_FIELD_LOG:
			{
			   list.set_logical( field->StrTrue() ) ;
			   break ;
			}
		 }

		  list.set_type( v4functions[f_code].return_type ) ;
		 if ( list.push_parm() < 0 )  return -1 ;
		  continue ;
	  }

	  /* Immediate Data */
	  switch( f_code )
	  {
		  case  I_STRING:
		  {
			int string_len ;
			memcpy( &string_len, compile_ptr, sizeof(int) ) ;
			 compile_ptr +=  sizeof(int) ;
			list.set( compile_ptr, string_len, t4str ) ;
			compile_ptr +=  string_len ;
		  }
			 break ;

		  case  I_DOUBLE:
		  {
			list.pos_align() ;
			list.set( compile_ptr, sizeof(double), t4num_doub ) ;
			compile_ptr +=  sizeof(double) ;
		  }
			 break ;
	  }

	  if ( list.push_parm() < 0 )  return -1 ;
	  continue ;
   }
}

Expr::operator double()
{
   String temp( code_base ) ;
   int result_type =  vary( temp ) ;

   switch( result_type )
   {
	  case t4num_doub:
	  case t4date_doub:
	  { 
		 return  *((double *) temp.ptr()) ;
	  }		 

	  case t4num_str:
	  case t4str:
	  {		 
		 return double(temp) ;
	  } 

	  case t4date_str:
	  {		 
		 Date dt( temp.ptr() ) ;
		 return double(long(dt)) ;
	  }
   }

   return 0.0 ;
}

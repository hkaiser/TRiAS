// p4parse.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
}

Parse::Parse( Expr& expr_parm ) : op_string( expr_parm.code_base )
{
   s.init( expr_parm.source.ptr(), expr_parm.source.len() ) ;
   op.init( &op_string ) ;
   result.init( &expr_parm.parsed ) ;
   data =  expr_parm.data ;
   code_base = data->code_base ;
}

int  Parse::field_function( Field& field )
{
   switch( field.type() )
   {
	  case (int) 'C':
	  case (int) 'M':
		 return  I_FIELD_STR ;

	  case (int) 'N':
	  case (int) 'F':
		 return  I_FIELD_NUM_S ;

	  case (int) 'D':
		 return  I_FIELD_DATE_S ;

	  case (int) 'L':
		 return  I_FIELD_LOG ;
   }
   return -1 ;
}

int  Parse::get_f_code( char *f_code_ptr, PARSE_PARM *parms )
{
   int  i, p_no, flg, i_functions ;

   /* flg Values
	 -1 -  Error
	  0 -  OK
	  1 -  Conversion Required
   */

   memcpy( &i_functions, f_code_ptr, sizeof(int)) ;

   for ( i= i_functions; ; i++ )
   {
	  if ( v4functions[i].code == 0 ||
		   v4functions[i].code != v4functions[i_functions].code )
		 break ;

	  /* Check the Type Match */
	  for ( p_no = 0, flg = 0; p_no < v4functions[i].num_parms; p_no++ )
	  {
		 int  i_temp ;

		  if ( v4functions[i].type[p_no] == parms[p_no].type )   continue ;

		 memcpy( &i_temp, parms[p_no].ptr, sizeof(int) ) ;

/*
		  #ifdef CLIPPER
				 if ( v4functions[i].type[p_no] == t4num_doub )
			 {
				if ( i_temp == I_FIELD_NUM_S )
				{
				   flg =  1 ;
				   continue ;
				}
			 }
				 if ( v4functions[i].type[p_no] == t4num_doub )
			 {
			 }
		  #else
*/
				 if ( v4functions[i].type[p_no] == t4num_doub )
			 {
				if ( i_temp == I_FIELD_NUM_S )
				{
				   flg =  1 ;
				   continue ;
				}
			 }
/*
		  #endif
*/

		  if ( v4functions[i].type[p_no] == t4date_doub )
		  {
			 if ( i_temp == I_FIELD_DATE_S ) 
			 {
				flg =  1 ;
				continue ;
			 }
		  }

		  flg =  -1 ;  /* No Match */
		  break ;
	  }

	  if ( flg >= 0 )
	  {
		  /* Success */
		  if ( flg > 0 )
		  {
			 /* Parameter Change Required First */
			for ( p_no = 0, flg = 0; p_no < v4functions[i].num_parms; p_no++) 
			{
			   int  i_temp ;

				if ( v4functions[i].type[p_no] == parms[p_no].type )   continue ;

			   memcpy( &i_temp, parms[p_no].ptr, sizeof(int) ) ;
				if ( i_temp == I_FIELD_DATE_S )
				  i_temp = I_FIELD_DATE_D ;
			   else
			   {
				   if ( i_temp == I_FIELD_NUM_S )
					 i_temp = I_FIELD_NUM_D ;
			   }
			   memcpy( parms[p_no].ptr, &i_temp, sizeof(int) ) ;
			}
		  }

		 memcpy( f_code_ptr, &i, sizeof(int) ) ;
		 f_code_ptr +=  sizeof(int) ;

		  parms[0].type =  v4functions[i].return_type ;
		  parms[0].ptr  =  f_code_ptr ;

		 return( 0 ) ;
	  }
   }

   code_base->error( e4type, "Expression:", s.source, "",
					"Function:", v4functions[i_functions].name, (char *) 0 ) ;
   return( -1 ) ;
}

/*	Looks at the input string and returns and puts a character code on the
   result stack corresponding to the next operator.  The operators all operate
   on two operands.  Ex. +,-,*,/, >=, <, .AND., ...

	  If the operator is ambiguous, return the arithmatic choice.

   Returns -2 (Done), 0, -1 (Error)
*/

int  Parse::get_operator( int *op_return)
{
   s.scan( char(1), ' ' ) ;
   if (char(s)==0 || char(s)==')' || char(s)==',') 
   {
	  *op_return =  -2 ;
	  return(0) ; /* Done */
   }

   int op  =  lookup( s.ptr(), -1, FIRST_OPERATOR, LAST_OPERATOR ) ;
   if ( op < 0 )
	  return code_base->error( e4unrec_operator, s.source, (char *) 0 ) ;

   s.skip( v4functions[op].name_len ) ;
   *op_return = op ;

   return 0 ;
}

/* Parse::lookup, searches 'v4functions' for an operator or function.

	   str - the function name
	   len - the number of characters in the function name

   len <= 0

	  Needs Exact Lookup.  All of the characters in 'v4functions'
	  must be present in 'str'.

   len > 0 

	  Only examines 'len' characters in 'str'.  It needs an exact
	  match on 'len' characters.  If 'len <= 3', there cannot
	  be any extra characters in 'v4functions'.

   Returns:  
	   >= 0   The index into v4functions.
		 -1   Not Located
*/

int  Parse::lookup( char *str, int len, int start_i, int end_i )
{
   char u_str[20] ;
   int  i, exact_lookup ;

   if ( len <= 0 )
   {
	  exact_lookup =  1 ;

	  /* Determine 'len' */
	  for ( len=0; str[len] != ' ' && str[len] != '\0'; len++ ) ;
   }
   else
	  exact_lookup =  0 ;

   if (len >= sizeof(u_str))  len = sizeof(u_str)-1 ;
   memcpy( u_str, str, (size_t) len ) ;
   u_str[len] =  '\0' ;
   strupr( u_str ) ;

   for( i=start_i; i<= end_i; i++)
   {
	  if ( v4functions[i].code < 0 )  break ;

	  if ( v4functions[i].name[0] == u_str[0] )
	  {
		 if ( exact_lookup )
		 {
			if ( v4functions[i].name_len <= len && v4functions[i].name_len > 0 )
			   if (memcmp(u_str, v4functions[i].name, (size_t) v4functions[i].name_len) == 0)
				  return( i ) ;
		 }
		 else
			if ( memcmp(u_str, v4functions[i].name, (size_t) len) == 0)
			{
			   if ( len >= 4 )  return( i ) ;
			   if ( v4functions[i].name_len == len )  return(i) ;
			}
	  }
   }
   return -1 ;
}


int  Parse::parse_do()
{
   if ( parse_expr() < 0 )  return -1 ;
   if ( op.cur() != Q_NO_FUNCTION )
	  return code_base->error( e4complete, s.source, (char *) 0 ) ;
   result.push( -1 ) ;

   if ( type_check() < 0 )   return  -1 ;
   return  0 ;
}

/*
   Parses an expression constisting of		 value [[operator value] ...]
   The expression is ended by a ')', a ',' or a '\0'.
   Operators are only popped until a '(', a ',' or the start of the stack.
   Left to right evaluation for operators of equal priority.

	  An ambiguous operator is one which can be interpreted differently
   depending on its operands.  However, its operands depend on the
   priority of the operators and the evaluation order.		Fortunately, the
   priority of an ambigous operator is constant regardless of its
   interpretation.  Consequently, the evaluation order is determined first.
   Then ambiguous operators can be exactly determined.

   Ambigous operators:		+, -,  >, <, <=, >=, =, <>, #

   Return

	   0  Normal
	  -1  Error
*/

int Parse::parse_expr()
{
   if ( parse_value() < 0 )  return -1 ;

   for(;;)
   {
	  int  op_value, rc ;
	  if ( (rc =  get_operator(&op_value)) < 0 )  return -1 ;
	  if (op_value  == -2)
	  {
		 /* Done */
		 while( op.cur() != Q_L_BRACKET
				&& op.cur() != Q_COMMA
				&& op.cur() != Q_NO_FUNCTION )
			if ( result.push( op.pop() ) < 0 )  return -1 ;
		 return( 0) ;
	  }

	  /* Everything with a higher or equal priority than 'op_value' must be
		 exectuted first. (equal because of left to right evaluation order)
		 Consequently, all high priority operators are sent to the result
		 stack.
	  */
	  while ( op.cur() >= 0 )
	  {
		 if ( v4functions[op_value].priority <=  v4functions[op.cur()].priority)
		 {
			if ( result.push( op.pop() ) < 0 )  return -1 ;
		 }
		 else
			break ;
	  }
	  op.push( op_value) ;

	  if ( parse_value() < 0 )  return -1 ;
   }
}

int  Parse::parse_function( char *start_ptr, int f_len )
{
   if ( code_base->error() )  return -1 ;

   int f_num =  lookup( start_ptr, f_len, FIRST_FUNCTION, 0x7FFF) ;
   if (f_num== Q_NO_FUNCTION) return code_base->error( e4unrec_function, s.source, (char *) 0 ) ;

   op.push( Q_L_BRACKET ) ;
   s.skip() ;

   int num_parms = 0 ;
   for(;;)
   {
	  if (char(s) == 0 ) return code_base->error( e4right_missing, s.source, (char *) 0 ) ;
	  if (char(s) == ')')
	  {
		 s.skip() ;
		 break ;
	  }

	  if ( parse_expr() < 0 )  return -1 ;
	  num_parms++ ;

	  while (char(s) <= ' ' &&  char(s)>='\1')  s.skip() ;
	  if (char(s) == ')')
	  {
		 s.skip() ;
		 break ;
	  }
	  if (char(s) != ',') return code_base->error( e4comma_expected, s.source, (char *) 0) ;
	  s.skip() ;
   }
   op.pop() ;  /* pop the left bracket */

   if ( num_parms != v4functions[f_num].num_parms )
   {
	  if ( strcmp( v4functions[f_num].name, "STR" ) == 0 )
	  {
		 if ( num_parms == 1 )
		 {
			double d = 10.0 ;
			result.push( I_DOUBLE ) ;
			result.push( &d, sizeof(double) ) ;
			num_parms++ ;
		 }
		 if ( num_parms == 2 )
		 {
			double d = 0.0 ;
			result.push( I_DOUBLE ) ;
			result.push( &d, sizeof(double) ) ;
			num_parms++ ;
		 }
	  }
	  if ( strcmp( v4functions[f_num].name, "SUBSTR" ) == 0 )
	  {
		 if ( num_parms == 2 )
		 {
			double d = (double) 0x7FFF ;
			result.push( I_DOUBLE ) ;
			result.push( &d, sizeof(double) ) ;
			num_parms++ ;
		 }
	  }
   }

   if ( num_parms != v4functions[f_num].num_parms )
	  return code_base->error( e4num_parms, s.source, "Function", v4functions[f_num].name, (char *) 0 ) ;

   return result.push( f_num ) ;
}

int  Parse::parse_value()
{
   if ( code_base->error() )  return -1 ;
   s.scan( ' ', ' ' ) ;

   /* expression */
   if ( char(s) == '(')
   {
	  s.skip() ;
	  op.push( Q_L_BRACKET) ;
	  if ( parse_expr() < 0 )  return( -1 ) ;
	  while (char(s) <= ' ' && char(s) != 0)  s.skip() ;
	  if (char(s) != ')' ) return code_base->error( e4right_missing, s.source, (char *) 0 ) ;
	  s.skip() ;
	  op.pop() ;
	  return( 0 ) ;
   }

   // logical
   if ( char(s) == '.' )
   {
	  int  i_functions ;

	  i_functions =  lookup( s.ptr(), -1, FIRST_LOG, LAST_LOG ) ;

	  if ( i_functions >= 0 )
	  {
		 s.pos +=  v4functions[i_functions].name_len ;

		 if ( strcmp( v4functions[i_functions].name, ".NOT." ) == 0 )
			if ( parse_expr() < 0 )  return( -1 ) ; // One operand operation

		 return result.push( i_functions ) ;
	  }
   }

   // real
   if (char(s)>='0' && char(s)<='9' || char(s) == '-' || char(s) == '+' || char(s) == '.' )
   {
	  char *start_ptr =  s.ptr() ;

	  s.skip() ;
	  int len = 1 ;

	  while( char(s) >= '0' && char(s) <= '9' || char(s) == '.' )
	  { 
		 if ( char(s) == '.' )
			if ( strnicmp(s.ptr(), ".AND.",5) == 0 ||
				 strnicmp(s.ptr(), ".OR.",4) == 0 ||
				 strnicmp(s.ptr(), ".NOT.",5) == 0 )
			   break ;
		 len++ ;
		 s.skip() ;
	  } 

	  StrLen temp_str(start_ptr,len) ;
	  double d = temp_str.operator double() ;
	  result.push( I_DOUBLE ) ;
	  return result.push( &d, sizeof(d) ) ;
   }

   // string
   if (char(s) == '\'' || char(s) == '\"')
   {
	  char search_char =  char(s) ;

	  s.skip() ;
	  char *start_ptr =  s.ptr() ;

	  int   len =  s.search( search_char ) ;
	  if ( char(s) != search_char )
	  if ( len < 0 )
		 return code_base->error( e4unterminated, s.source, (char *) 0 ) ;
	  s.skip() ;

	  result.push( I_STRING ) ;
	  result.push( len ) ;
	  return result.push( start_ptr, len ) ;
   }

   // function or field
   if (f4name_char(char(s)) )
   {
	  char *start_ptr =  s.ptr() ;

	  int  len ;
	  for( len=0; f4name_char(char(s)); len++ )  s.skip() ;
	  #ifdef OTHER_NDX
		 s.scan( (char) 1, ' ' ) ;
	  #else
		 s.scan( (char) 0, ' ' ) ;
	  #endif

	  if ( char(s) == '(' )  return parse_function( start_ptr, len ) ;

	  Data *base_ptr ;
	  char b_name[11], f_name[11] ;
	  if ( char(s) == '-'  &&  s.ptr()[1] == '>')
	  {
		 if ( len > 10 )  len =  10 ;
		 memmove( b_name, start_ptr, (size_t) len ) ;
		 b_name[len] = '\0' ;

		 base_ptr =  code_base->data(b_name) ;
		 if ( base_ptr == 0 )
			return code_base->error( e4data_name, b_name, s.source, (char *) 0 ) ;
		 s.skip() ;
		 s.skip() ;

		 start_ptr =  s.ptr() ;
		 for( len=0; f4name_char(char(s)); len++ )  s.skip() ;
	  }
	  else
		 base_ptr =  (Data *) data ;

	  if ( len <= 10)
	  {
		 memmove( f_name, start_ptr, (size_t) len ) ;
		 f_name[len] =  0 ;

		 Field *field_ptr =  base_ptr->field( f_name ) ;
		 if ( field_ptr == 0 )  return -1 ;
		 result.push( field_function( *field_ptr ) ) ;
		 return result.push( &field_ptr, sizeof(field_ptr)) ;
	  }
   }

   return code_base->error( e4unrec_value, s.source, (char *) 0 ) ;
}

int  Parse::type_check()
{
   int		 f_code ;
   char	   *f_code_ptr ;
   int		 n_parms, len ;
   PARSE_PARM  parms[PARM_STACK_SIZE] ;

   if ( code_base->error() )  return -1 ;

   parms[0].type =  0 ;
   char *compile_ptr =  result.s->ptr() ;

   for ( n_parms= 0;; )
   {
	  f_code_ptr =  compile_ptr ;
	  memcpy( &f_code, f_code_ptr, sizeof(int) ) ;

	  if ( f_code == -1 )
	  {
		 #ifdef DEBUG
			if (n_parms != 1)  e4severe( e4info, "Parse::type_check() 1", s.source, (char *) 0 ) ;
		 #endif
		 return  parms[0].type ;
	  }

	  if ( f_code <= LAST_IMMEDIATE )
	  {
		 parms[n_parms].type =  v4functions[f_code].return_type ;
		 parms[n_parms].ptr  =  compile_ptr ;
		 compile_ptr +=  sizeof(int) ;

		 if ( f_code <= LAST_I_FIELD )
			compile_ptr = compile_ptr + sizeof(Field *) ;
		 else
		 {
			if ( f_code == I_DOUBLE )
			   len = sizeof(double) ;
			else
			{
			   memcpy( &len, compile_ptr, sizeof(int) ) ;
			   compile_ptr += sizeof(int) ;
			}

			compile_ptr +=  len ;
		 }
	  }
	  else
	  {
		 n_parms -=  v4functions[f_code].num_parms ;
		 #ifdef DEBUG
			if ( n_parms < 0 )
			   e4severe( e4info, "Parse::type_check() 2", s.source, (char *) 0 ) ;
		 #endif

		 if ( get_f_code( f_code_ptr, parms+ n_parms ) < 0 )  return -1 ;
		 compile_ptr +=  sizeof(int) ;
	  }
	  n_parms++ ;

	  if ( n_parms+1 >= PARM_STACK_SIZE )
		 return code_base->error( e4overflow, s.source, (char *) 0 ) ;
   }
}

void Stack::init( String *s_parm )
{
   s =  s_parm ;
}

int Stack::pop()
{
   int ret_value =  cur() ;
   unsigned cur_len =  s->len() ;
   if ( cur_len >= sizeof(int) )
	  s->set_len( cur_len - sizeof(int) ) ;
   return ret_value ;
}

int  Stack::cur()
{
   if ( s->len() < sizeof(int) )  return Q_NO_FUNCTION ;
   char *p =  s->ptr()+ s->len() - sizeof(int) ;
   int cur_data ;
   memcpy( &cur_data, p, sizeof(int) ) ;
   return cur_data ;
}

int  Stack::push( int i )
{
   return s->add( StrLen(&i, sizeof(i)) ) ;
}

int  Stack::push( void *p, int len )
{
   return s->add( StrLen(p,len) ) ;
}

Scan::operator char()
{
   if ( pos >= len )  return 0 ;
   return source[pos] ;
}

int Scan::scan( char start_char, char end_char )
{
   int count ;

   for ( count = 0; pos < len; pos++, count++ )
   {
	  if ( source[pos] < start_char || source[pos] > end_char )  return count ;
   }
   return count ;
}

int Scan::search( char search_char )
{
   int count ;
   for ( count = 0; pos < len; pos++, count++ )
   {
	  if ( source[pos] == search_char )  return count ;
   }
   return count ;
}

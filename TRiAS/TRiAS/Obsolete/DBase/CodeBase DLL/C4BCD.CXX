//  c4bcd.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

// bcd conversion functions only needed for the standard MDX version of CodeBase++

#include <d4all.h>

extern "C" {
#include <string.h>
#include <stdlib.h>
}

extern "C" {
TAG_CMP_FUNC c4bcd_cmp( const void *a_ptr, const void *b_ptr, size_t)
{
   int a_sign, b_sign ;

   if ( ((BCD *)a_ptr)->sign )
	  a_sign =  -1 ;
   else
	  a_sign =   1 ;

   if ( ((BCD *)b_ptr)->sign )
	  b_sign =  -1 ;
   else
	  b_sign =   1 ;

   if ( a_sign != b_sign )
	  return a_sign ;

   int a_len =  ((BCD *)a_ptr)->len ;
   int b_len =  ((BCD *)b_ptr)->len ;

   int a_sig_dig, b_sig_dig ;
   if ( a_len == 0 )
	  a_sig_dig =  0 ;
   else
	  a_sig_dig =  ((BCD *) a_ptr)->sig_dig ;

   if ( b_len == 0 )
	  b_sig_dig =  0 ;
   else
	  b_sig_dig =  ((BCD *) b_ptr)->sig_dig ;

   if ( a_sig_dig != b_sig_dig )
   {
	  if ( a_sig_dig < b_sig_dig )
		 return -a_sign ;
	  else
		 return a_sign ;
   }

   int compare_len =  (a_len < b_len) ? b_len : a_len ;  // Use Max

   compare_len =  (compare_len+1)/2 ;

   int rc =  memcmp( ((BCD *)a_ptr)->bcd, ((BCD *)b_ptr)->bcd, compare_len ) ;
   if ( a_sign < 0 )  return -rc ;

   return rc ;
}
}		// extern "C"

void c4stob( Str& str_result, Str& input )
{
   BCD  *result ;
   unsigned char  *ptr ;
   int   n ;

   if ( str_result.set_len(sizeof(BCD)) < 0 )
	  e4severe( e4memory, "c4atob", (char *) 0 ) ;
   str_result.set(0) ;
   result =  (BCD *) str_result.ptr() ;

   char *input_ptr =  input.ptr() ;
   unsigned last_pos = input.len()-1 ;
   unsigned pos = 0 ;
   for ( ; pos <= last_pos; pos++ )
	  if ( input_ptr[pos] != ' ' )  break ;

   if ( pos <= last_pos )
   {
	  if ( input_ptr[pos] == '-' )
	  {
		 result->sign =  1 ;
		 pos++ ;
	  }
	  else
	  {
		 if ( input_ptr[pos] == '+' )  pos++ ;
	  }
   }

   for ( ; pos <= last_pos; pos++ )
	  if ( input_ptr[pos] != ' ' && input_ptr[pos] != '0' )  break ;

   int is_before_dec =  1 ;

   result->sig_dig =  0x34 ;
   if ( pos <= last_pos )
	  if ( input_ptr[pos] == '.' )
	  {
		 is_before_dec =  0 ;
		 pos++ ;
		 for ( ; pos <= last_pos; pos++ )
		 {
			if ( input_ptr[pos] != '0' )  break ;
			result->sig_dig-- ;
		 }
	  }

   ptr =  (unsigned char *) result->bcd ;
   int zero_count =  0 ;

   for ( n=0; pos <= last_pos; pos++ )
   {
	  if ( input_ptr[pos] >= '0' && input_ptr[pos] <= '9' )
	  {
		 if ( input_ptr[pos] == '0' )
			zero_count++ ;
		 else
			zero_count =  0 ;
		 if ( n >= 20 )  break ;
		 if ( n & 1 )
			*ptr++ |=  input_ptr[pos] - '0' ;
		 else
			*ptr  +=  (unsigned char)(input_ptr[pos]-'0') << 4 ;
	  }
	  else
	  {
		 if ( input_ptr[pos] == '.'  &&  is_before_dec )
		 {
			is_before_dec =  0 ;
			continue ;
		 }
		 break ;
	  }
	  if ( is_before_dec )
		 result->sig_dig++ ;

	  n++ ;
   }

   result->one =  1 ;
   result->len =  n - zero_count ;
   if ( result->len == 0 )
	  result->sign =  0 ;
}

void  c4dtob( Str& str_result, double doub )
{
   Str255 temp_str ;
   int sign,dec ;

   int accuracy = M4MAX_DBL_ACCURACY ;

   char *from_ptr = ecvt( doub, accuracy, &dec, &sign ) ;

   char *to_ptr = temp_str.ptr() ;

   if ( sign )
   {
	  *to_ptr = '-' ;
	  to_ptr++ ;
   }

   if ( dec < 0 )
   {
	  *to_ptr = '.' ;
	  to_ptr++ ;
	  for ( int rep = 0 ; rep > dec ; rep--, to_ptr++, accuracy-- )
		  *to_ptr = '0' ;
   }
   else if ( dec < M4MAX_DBL_ACCURACY )
   {
	  memcpy( to_ptr, from_ptr, dec ) ;
	  to_ptr += dec ;
	  from_ptr += dec ;
	  *to_ptr = '.' ;
	  to_ptr++ ;
	  accuracy -= (dec-1) ;
   }

   memcpy( to_ptr, from_ptr, accuracy ) ;
   temp_str.set_len( (to_ptr - temp_str.ptr()) + accuracy ) ;

   c4stob( str_result, temp_str ) ;
}


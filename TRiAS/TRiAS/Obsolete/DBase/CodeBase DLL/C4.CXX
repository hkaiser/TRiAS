// c4.c  Conversion Routines  (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

extern "C" {
#include <string.h>
#include <stdlib.h>
}

/* c4atod

   Converts a string to a double
*/

double c4atod( char *char_string, int string_len )
{
   char buffer[50] ;
   int		len ;

   len =  (string_len >= 50 )  ?  49 : string_len ;
   memcpy( buffer, char_string, (size_t) len ) ;
   buffer[len] = '\0' ;

   return( strtod( buffer, (char **) 0)   ) ;
}

/* c4atoi.c  */

int c4atoi( char *ptr,  int n)
{
   char buf[128] ;
   if ( n >= sizeof(buf) )  n= sizeof(buf) -1 ;
   memcpy(buf, ptr, (size_t) n) ;
   buf[n] = '\0' ;
   return (atoi(buf) ) ;
}

/* c4atol  */

long c4atol( char *ptr, int n)
{
   char buf[128] ;
   if ( n >= sizeof(buf) )  n= sizeof(buf) -1 ;
   memcpy(buf, ptr, (size_t) n) ;
   buf[n] = '\0' ;
   return (atol(buf) ) ;
}

/*  c4ltoa

	Converts a RECNUM to a string.  Fill with '0's rather than blanks if
	'num' is less than zero.
*/

void c4ltoa( long l_val, char *ptr, int num)
{
   int		 n, num_pos ;
   long  i_long ;

   i_long =  (l_val>0) ? l_val : -l_val ;
   num_pos =  n =  (num > 0) ? num : -num ;

   while (n-- > 0)
   {
	  ptr[n] = (char) ('0'+ i_long%10) ;
	  i_long = i_long/10 ;
   }

   if ( i_long > 0 )
   {
	 memset( ptr, (int) '*', (size_t) num_pos ) ;
	 return ;
   }

   num--;
   for (n=0; n<num; n++)
	  if (ptr[n]=='0')
		 ptr[n]= ' ';
	  else
		 break ;

   if (l_val < 0)
   {
	  if ( ptr[0] != ' ' )
	  {
		 memset( ptr, (int) '*', (size_t) num_pos ) ;
		 return ;
	  }
	  for (n=num; n>=0; n--)
		 if (ptr[n]==' ')
		 {
			ptr[n]= '-' ;
			break ;
		 }
   }
}


/* c4encode

   - From CCYYMMDD to CCYY.MM.DD

   Ex.		c4encode( to, from, "CCYY.MM.DD", "CCYYMMDD" ) ;
*/

void c4encode( char *to, char *from, char *t_to, char *t_from)
{
   int		pos ;
   char chr ;
   char * chr_pos ;

   strcpy( to, t_to ) ;

   while ( (chr=*t_from++)  != 0)
   {
	  if (  (chr_pos= strchr(t_to,chr)) ==0)
	  {
		 from++;
		 continue ;
	  }

	  pos = (int) (chr_pos - t_to) ;
	  to[pos++] = *from++ ;

	  while (chr== *t_from)
	  {
		 if (chr== t_to[pos])
			to[pos++] = *from ;
		 t_from++ ;
		 from++ ;
	  }
   }
}

/* c4dtoa
   - formats a double to a string
   - if there is an overflow, '*' are returned
*/

void c4dtoa( double doub_val, char *out_buffer, int len, int dec)
{
   int		 dec_val, sign_val ;
   int		 pre_len, post_len, sign_pos ; /* pre and post decimal point lengths */
   char *result ;

   #ifdef DEBUG
	  if ( len < 0 || len >128 || dec < 0 || dec >= len )
		 e4severe( e4info, "c4dtoa", (char *) 0 ) ;
   #endif

   memset( out_buffer, (int) '0', (size_t) len) ;

   if (dec > 0)
   {
	  post_len =  dec ;
	  if (post_len > 15)	 post_len =  15 ;
	  if (post_len > len-1)  post_len =  len-1 ;
	  pre_len  =  len -post_len -1 ;

	  out_buffer[ pre_len] = '.' ;
   }
   else
   {
	  pre_len  =  len ;
	  post_len = 0 ;
   }

   result =  fcvt( doub_val, post_len, &dec_val, &sign_val) ;

   if (dec_val > 0)
	  sign_pos =   pre_len-dec_val -1 ;
   else
   {
	  sign_pos =   pre_len - 2 ;
	  if ( pre_len == 1) sign_pos = 0 ;
   }

   if ( dec_val > pre_len ||  pre_len<0  ||  sign_pos< 0 && sign_val)
   {
	  /* overflow */
	  memset( out_buffer, (int) '*', (size_t) len) ;
	  return ;
   }

   if (dec_val > 0)
   {
	  memset( out_buffer, (int) ' ', (size_t) pre_len- dec_val) ;
	  memmove( out_buffer+ pre_len- dec_val, result, (size_t) dec_val) ;
   }
   else
   {
	  if (pre_len> 0)  memset( out_buffer, (int) ' ', (size_t) (pre_len-1)) ;
   }
   if ( sign_val)  out_buffer[sign_pos] = '-' ;


   out_buffer += pre_len+1 ;
   if (dec_val >= 0)
   {
	  result+= dec_val ;
   }
   else
   {
	  out_buffer	-= dec_val ;
	  post_len += dec_val ;
   }

   if ( post_len > (int) strlen(result) )
	  post_len =  (int) strlen( result) ;

   /*  - out_buffer   points to where the digits go to
	   - result	   points to where the digits are to be copied from
	   - post_len	 is the number to be copied
   */

   if (post_len > 0)   memmove( out_buffer, result, (size_t) post_len) ;
}


#ifdef CLIPPER
/* Numeric Key Database Output is Converted to Numeric Key Index File format */
int c4clip( char *ptr, int len)
{
   int		 i, negative ;
   char *p ;

   for ( i= negative= 0, p= ptr; i< len; i++, p++ )
   {
	  if ( *p == ' ' )
	  {
		 *p =  '0' ;
	  }
	  else
	  {
		 if ( *p == '-' )
		 {
			*p =  '0' ;
			negative =		1 ;
		 }
		 else
			break ;
	  }
   }

   if ( negative )
   {
	  for ( i= 0, p= ptr; i< len; i++, p++ )
		 *p =  (char) 0x5c - *p ;
   }

   return 0 ;
}
#endif


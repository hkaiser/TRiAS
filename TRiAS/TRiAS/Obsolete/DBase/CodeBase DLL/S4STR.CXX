// s4str.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
	#include <string.h>
	#include <ctype.h>
	#include <limits.h>
}

#ifdef DEBUG
#if !defined (__ZTC__)
extern "C" {		// #JB920619
	static char huge *s1_ptr;
	static char huge *s2_ptr;
	static char huge *s1_end_ptr;
	static char huge *s2_end_ptr;
}
#endif

// Ensure the strings do not overlap
void s4asser_no_overlap( Str& s1, Str& s2 )
{
   if ( s1.maximum() == 0  ||  s2.maximum() == 0 )  
   	  return ;

   unsigned s1_end_pos =  s1.maximum()-1 ;
   unsigned s2_end_pos =  s2.maximum()-1 ;
#if defined (__ZTC__)
	  long  s1_ptr =  long( s1.ptr() ) ;
	  long  s2_ptr =  long( s2.ptr() ) ;
#else
	  s1_ptr = s1.ptr() ;
	  s2_ptr = s2.ptr() ;
#endif

   if ( s1_ptr == 0  ||  s2_ptr == 0 )
	  e4severe( e4parm, "Null String Detected", (char *) 0 ) ;

#if defined (__ZTC__)
	  long  s1_end_ptr =  s1_ptr + s1_end_pos ;
	  long  s2_end_ptr =  s2_ptr + s2_end_pos ;
#else
	  s1_end_ptr = s1_ptr + s1_end_pos ;
	  s2_end_ptr = s2_ptr + s2_end_pos ;
#endif

   if ( s1_ptr	 >= s2_ptr  && s1_ptr	 <= s2_end_ptr	  ||
		s1_end_ptr >= s2_ptr  && s1_end_ptr <= s2_end_ptr	  ||
		s2_ptr	 >= s1_ptr  && s2_ptr	 <= s1_end_ptr	  ||
		s2_end_ptr >= s1_ptr  && s2_end_ptr <= s1_end_ptr )
	  e4severe( e4parm, "Overlapping Strings Detected", (char *) 0 ) ;
}
#endif


Str::operator char()
{
   if ( len() < 1 || ptr() == 0 )  return 0 ;
   return  *ptr() ;
}

Str::operator double()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::operator double() called with a null pointer", (char *) 0 ) ;
   #endif
   return c4atod( ptr(), len()) ;
}

Str::operator int()
{
   char *p =  ptr() ;
   #ifdef DEBUG
	  if( p == 0 ) e4severe( e4parm, "Str::operator int() called with a null pointer", (char *) 0 ) ;
   #endif
   int i =  len() ;
   int   r =  (int) c4atol( p,i ) ;
   return r ;
}

__export Str::operator long()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::operator long() called with a null pointer", (char *) 0 ) ;
   #endif
   return c4atol( ptr(), len()) ;
}

int __export Str::operator==( Str& s )
{
   #ifdef DEBUG
	  if( ptr() == 0 || s.ptr() == 0 ) e4severe( e4parm, "Str::operator == called with a null pointer", (char *) 0 ) ;
   #endif
   unsigned l =  len() ;
   if ( l != s.len() )  return 0 ;

   if ( memcmp( ptr(), s.ptr(), l) == 0 )
	  return 1 ;
   else
	  return 0 ;
}

int Str::operator< ( Str& s )
{
   #ifdef DEBUG
	  if( ptr() == 0 || s.ptr() == 0 ) e4severe( e4parm, "Str::operator < called with a null pointer", (char *) 0 ) ;
   #endif
   unsigned cmp_len ;
   int	  result ;
   unsigned l1 =  len() ;
   unsigned l2 =  s.len() ;

   cmp_len =  (l1<l2) ? l1 : l2 ;
   result =  memcmp( ptr(), s.ptr(), cmp_len ) ;
   if ( result == 0 )  return  l1 < l2 ;
   return result < 0 ;
}

int Str::operator> ( Str& s )
{
   #ifdef DEBUG
	  if( ptr() == 0 || s.ptr() == 0 ) e4severe( e4parm, "Str::operator > called with a null pointer", (char *) 0 ) ;
   #endif
   unsigned cmp_len ;
   int	  result ;
   unsigned l1 =  len() ;
   unsigned l2 =  s.len() ;

   cmp_len =  (l1<l2) ? l1 : l2 ;
   result =  memcmp( ptr(), s.ptr(), cmp_len ) ;
   if ( result == 0 )  return  l1 > l2 ;
   return result > 0 ;
}

int __export Str::operator<= ( Str& s )
{
   #ifdef DEBUG
	  if( ptr() == 0 || s.ptr() == 0 ) e4severe( e4parm, "Str::operator <= called with a null pointer", (char *) 0 ) ;
   #endif
   return ! ( *this > s ) ;
}

int __export Str::operator>= ( Str& s )
{
   #ifdef DEBUG
	  if( ptr() == 0 || s.ptr() == 0 ) e4severe( e4parm, "Str::operator >= called with a null pointer", (char *) 0 ) ;
   #endif
   return ! ( *this < s ) ;
}

int __export Str::assign( char *p )
{
   #ifdef DEBUG
	  if( p == 0 ) e4severe( e4parm, "Str::assign() called with a null pointer", (char *) 0 ) ;
   #endif  
   return assign (StrPtr (p));
}

int __export Str::assign( Str& str_from )
{         
   #ifdef DEBUG 			
	  s4asser_no_overlap( *this, str_from ) ;
   #endif   
   
   changed() ;

   unsigned from_len =  str_from.len() ;
   int rc = set_len( from_len ) ;
   unsigned to_len, cur_len ;
   to_len =  cur_len =  len() ;
   if ( to_len > from_len )
   {
	  set( ' ' ) ;
	  to_len =  from_len ;
   }

   char *p = ptr() ;
   memcpy( p, str_from.ptr(), to_len ) ;
   if ( cur_len < maximum() )  
   		p[cur_len] =  0 ;
   return rc ;
}

void Str::assign_double( double d, int dec )
{
   changed() ;

   char *p =  ptr() ;
   #ifdef DEBUG
	  if( p == 0 ) e4severe( e4parm, "Str::assign_double() called, but has a null pointer", (char *) 0 ) ;
   #endif
   unsigned l = len() ;

   if ( dec < 0 )  dec =  decimals() ;
   c4dtoa( d, p, l, dec ) ;

   if ( l < maximum() )
	  p[l] =  0 ;
}

void __export Str::assign_long( long lval, int zeros_in_front )
{
   changed() ;

   char *p =  ptr() ;
   #ifdef DEBUG
	  if( p == 0 ) e4severe( e4parm, "Str::assign_long() called, but has a null pointer", (char *) 0 ) ;
   #endif
   unsigned l = len() ;		

   if ( zeros_in_front )
	  c4ltoa( lval, p, - (signed)l ) ;		// #JB962606
   else
	  c4ltoa( lval, p, l ) ;

   if ( l < maximum() )
	  p[l] =  0 ;
}


int Str::StrTrue()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::true() called, but has a null pointer", (char *) 0 ) ;
   #endif
   char ch =  char(*this) ;
   if ( ch == 'Y' || ch == 'y' || ch == 'T' || ch == 't' )
	  return 1 ;
   else
	  return 0 ;
}

unsigned __export Str::len()
{  
   if ( ptr() == 0 ) return 0 ;
   return strlen(ptr()) ;
}

int __export StrMax::set_len( unsigned new_len )
{
   if ( new_len <= max_len )
   {
	  cur_len =  new_len ;
	  if ( cur_len < max_len )
		 p[cur_len] =  0 ;
	  return 0 ;
   }
   if ( set_max( new_len )  < 0 )  return -1 ;
   return set_len( new_len ) ;
}

int  __export Str10::set_len( unsigned new_len )
{
   return (new_len <= 10) ? ( cur_len = new_len,0) : -1 ;
}

int __export Str255::set_len( unsigned new_len )
{
   return (new_len <= 255) ? (cur_len = new_len,0) : -1 ;
}

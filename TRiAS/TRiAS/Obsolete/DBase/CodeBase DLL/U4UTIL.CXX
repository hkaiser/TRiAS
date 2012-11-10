// u4util.c   (c)Copyright Sequiter Software Inc., 1990-1991. All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <time.h>
}

void u4ncpy( char *to, char *from, int len )
{
   memset( to, 0, len ) ;
   for ( int i = 0; i < len  &&  from[i] != 0; i++ )
	  to[i] =  from[i] ;
}

int  u4ptr_equal( void *p1, void *p2 )
{
   return( p1 == p2 ) ;
}

void u4yymmdd( char *yymmdd )
{
   time_t time_val ;
   time( (time_t *) &time_val ) ;
   struct tm  *tm_ptr =   localtime( (time_t *) &time_val ) ;
   yymmdd[0] =  (char) tm_ptr->tm_year ;
   yymmdd[1] =  (char) tm_ptr->tm_mon+ (char) 1 ;
   yymmdd[2] =  (char) tm_ptr->tm_mday ;
}

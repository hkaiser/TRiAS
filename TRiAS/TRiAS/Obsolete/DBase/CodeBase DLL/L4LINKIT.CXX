// l4linkit.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

Link *LinkIteratorPrev::operator()()
{
   Link *link_ret =  prev ;

   if ( prev == first )
	  prev = first = 0 ;
   else
	  prev = prev->prev() ;

   return  link_ret ;
}

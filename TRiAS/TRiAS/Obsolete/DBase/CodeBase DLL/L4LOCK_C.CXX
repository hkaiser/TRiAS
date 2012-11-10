// l4lock_c.c (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"                  
                  
#ifdef L4LOCK_CHECK

extern "C" {
#include <stdio.h>
}

// Saves information about all current locks 
class LockInfo : public Link
{
public:
   int	 next ;   
   int	 prev ;   
   int	 hand ;
   long	start_pos ;
   long	len ;
   long	end_pos ;
} ;

static LinkAlloc lock_list ( 20, sizeof(LockInfo), 5, 0 ) ;

l4lock_check()
{
   return lock_list.nlinks() ;
}


// Returns true or false; true means found

static LockInfo *l4lock_find( int h, long p, long l )
{
   LinkIterator next( lock_list ) ;

   for ( LockInfo *l_ptr; l_ptr = (LockInfo *) next(); )
   {
	  if ( l_ptr->hand == h  && l_ptr->start_pos == p && l_ptr->len == l )
		 return l_ptr ;
	  if ( l_ptr->hand == h )
	  {
		 /* Check for Overlap. */
		 if ( l_ptr->start_pos >= p && l_ptr->start_pos <= p+l-1  ||
			  l_ptr->end_pos >= p   && l_ptr->end_pos   <= p+l-1  ||
			  p >= l_ptr->start_pos && p <= l_ptr->end_pos		||
			  p+l-1 >= l_ptr->start_pos && p+l-1 <= l_ptr->end_pos )
			e4severe( e4result, "Locking Overlap Detected", (char *) 0 ) ;
	  }
   }
   return 0 ;
}

void l4lock_remove( int h, long p, long l )
{
   #ifndef WINDOWS
	  printf( "\nUnlock  Handle %d   Start Pos %ld   Length %ld", h, p, l ) ;
   #endif

   LockInfo *l_ptr =  l4lock_find( h,p,l ) ;
   if ( l_ptr == 0 )   
	  e4severe( e4result, "Removing Lock which was never placed.", (char *) 0 ) ;

   lock_list.remove( l_ptr ) ;
}

void l4lock_save( int h, long p, long l )
{
   #ifndef WINDOWS
	  printf( "\nLock	Handle %d   Start Pos %ld   Length %ld", h, p, l ) ;
   #endif

   if ( l4lock_find(h,p,l) != 0 )
	  e4severe( e4result, "l4lock_save()", "Locking Overlap Detected", (char *) 0 ) ;

   LockInfo *l_ptr =  (LockInfo *) lock_list.add() ;
   if ( l_ptr == 0 )
	  e4severe( e4memory, "l4lock_save(), Saving Lock Information", (char *) 0 ) ;

   l_ptr->hand = h ;
   l_ptr->start_pos = p ;
   l_ptr->len  = l ;
   l_ptr->end_pos =  p+l-1 ;
}

#endif // L4LOCK_CHECK	
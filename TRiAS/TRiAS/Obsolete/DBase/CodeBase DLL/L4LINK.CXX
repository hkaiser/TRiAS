// l4link.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

LinkList::LinkList()
{
   reset() ;
}

void LinkList::reset()
{
   l =  0 ;
   #ifdef DEBUG
	  n_link =  0 ;
	  check() ;
   #endif
}

Link *LinkList::first()
{
   if ( l == 0 )  return 0 ;
   return l->n ;
}

Link *LinkList::last()
{
   return l ;
}

void  LinkList::add_before( Link *anchor, Link *new_link )
{
   #ifdef DEBUG
	  if ( new_link == 0 )
		 e4severe( e4parm, "LinkList::add_after", (char *) 0 ) ;
   #endif

   if ( l == 0 )
   {
	  l =  new_link->p =  new_link->n =  new_link ;
   }
   else
   {
	  new_link->n =  anchor ;
	  new_link->p =  anchor->p ;
	  anchor->p->n=  new_link ;
	  anchor->p   =  new_link ;
   }

   #ifdef DEBUG
	  n_link++ ;
	  check() ;
   #endif

   return ;
}


void LinkList::add_after( Link *anchor, Link *new_link )
{
   #ifdef DEBUG
	  if ( new_link == 0 )
		 e4severe( e4parm, "LinkList::add_after", (char *) 0 ) ;
   #endif

   if ( l == 0 )
   {
	  l =  new_link->p =  new_link->n =  new_link ;
   }
   else
   {
	  new_link->p =  anchor ;
	  new_link->n =  anchor->n ;
	  anchor->n->p=  new_link ;
	  anchor->n   =  new_link ;
	  if ( anchor == l )  l =  new_link ;
   }

   #ifdef DEBUG
	  n_link++ ;
	  check() ;
   #endif

   return ;
}

void LinkList::add( Link *new_link ) 
{
   add_after( l, new_link ) ;
}

void LinkList::remove( Link *new_link )
{
   if ( new_link == 0 )  return ;

   #ifdef DEBUG
	  // Make sure the link being removed is on the linked list !
	  LinkIterator next( *this ) ;

	  for ( Link *link_on; link_on =  next(); )
		 if ( link_on == new_link )  break ;

	  if ( link_on != new_link )
		 e4severe( e4info, "LinkList::remove()", "Link not on list", (char *) 0 ) ;
   #endif

   new_link->p->n = new_link->n ;
   new_link->n->p = new_link->p ;
   if ( new_link == l )
   {
	  if ( l->p == l )
		 l =  0 ;
	  else
		 l =  l->p ;
   }

   #ifdef DEBUG
	  n_link-- ;
	  check() ;
   #endif

   return ;
}

Link *LinkList::pop()
{
   Link *p = l ;
   remove( l ) ;
   return p ;
}

#ifdef DEBUG
void LinkList::check()
{
   // Check the Linked List
   Link *on_link =  l ;
   if ( on_link == 0 )
   {
	  if ( n_link != 0 )  e4severe( e4info, "LinkList::check 1", "Corrupted LinkList", (char *) 0) ;
	  return ;
   }

   for ( int i = 1; i <= n_link; i++ )
   {
	  if ( on_link->n->p != on_link  ||  on_link->p->n != on_link )
		 e4severe( e4info, "Link::check 2", "Corrupted LinkList", (char *) 0 ) ;

	  on_link =  on_link->n ;

	  if ( i == n_link || on_link == l )
		 if ( i != n_link || on_link != l )
			e4severe( e4info, "Link::check", "Wrong number of Links in LinkList", (char *) 0 ) ;
   }
}
#endif

Link *LinkIterator::operator()()
{
   	Link *link_ret =  next ;

   	if ( next == last )
	  	next = last = 0 ;
   	else
   	{
   		if (next)						// #JB950622
	  		next = next->next() ;
	}	  	

   return  link_ret ;
}

// l4linksl.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

LinkSelect::LinkSelect()
{
   n_link   =  0 ;
   selected =  0 ;
}

void LinkSelect::add_before( Link *anchor, Link *new_link )
{
   LinkList::add_before( anchor, new_link ) ;
   n_link++ ;
}

void LinkSelect::add_after( Link *anchor, Link *new_link )
{
   LinkList::add_after( anchor, new_link ) ;
   n_link++ ;
}

void LinkSelect::add( Link *new_link )
{
   LinkList::add( new_link ) ;
   n_link++ ;
}

Link *LinkSelect::pop()
{
   Link *p = last() ;
   remove( last() ) ;
   return p ;
}

void LinkSelect::remove( Link *remove_link )
{
   if ( remove_link == 0 )  return ;
   if ( selected == remove_link )
   {
	  selected =  remove_link->prev() ;
	  if ( selected == remove_link )  selected =  0 ;
   }
   LinkList::remove( remove_link ) ;
   n_link-- ;
}

void LinkSelect::reset()
{
   LinkList::reset() ;
   selected =  0 ;
   n_link =  0 ;
}



// l4link.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef L4LINK

#define L4LINK

#ifndef D4DATA
#include "d4data.h"
#endif

class E4EXPORT  LinkAlloc : public LinkSelect
{
   friend class  Link ;

public:
   LinkAlloc() ;
   LinkAlloc( int units_start, unsigned unit_size, int unit_expand, int is_temp = 0);
  ~LinkAlloc() ;
   int    init( int units_start, unsigned unit_size, int unit_expand, int is_temp=0);

   Link  *add();                 // Allocates and adds
   void   reset() ;
   void   remove( Link * ) ;     // Removes and deallocates

private:
   void   *type_ptr ;            // MemoryType *
} ;

class E4EXPORT LinkIterator  // First to Last, must survive remove of current item
{
public:
   LinkIterator( LinkList& list ) { last = list.last(); next = list.first() ; }
   Link    *operator()()  ;

private:
   Link    *last, *next ;
} ;

class E4EXPORT LinkIteratorPrev   // Last to First, must survive remove of current item
{
public:
   LinkIteratorPrev( LinkList& list ) { first= list.first(); prev = list.last() ; }
   Link    *operator()()  ;

private:
   Link    *first, *prev ;
} ;


#endif

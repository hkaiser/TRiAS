// m4memory.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef M4MEMORY

#define M4MEMORY

#ifndef D4DATA
#include "d4data.h"
#endif

typedef unsigned size_t ;
class E4EXPORT  MemoryType ;

void  D4DLL_EXP m4stats() ;
void  D4DLL_EXP m4reset() ;          // Frees memory and resets the MemoryType module

MemoryType * D4DLL_EXP m4memory_type( int units_start, unsigned unit_size, 
			   int units_expand, int force_temporary = 0 ) ;
void  D4DLL_EXP m4release( MemoryType * ) ;


class E4EXPORT  Chunk : public Link
{
public:
   void *operator new( size_t, MemoryType * ) ;
   void operator delete (void* ); // #JB911210 #JB940923 alten Zustand hergestellt
   double  data ;  // Make sure it is on a boundry good for at least a double 
} ;

class E4EXPORT  MemoryType : public Link
{
   friend class Chunk ;
   friend void m4stats(), m4reset() ;
   friend void m4release( MemoryType * ) ;
   friend MemoryType *m4memory_type(int,unsigned,int,int) ;

public:
   void *operator  new( size_t ) ;
   void *operator  new( size_t, int units_start,  unsigned unit_size, 
				int units_expand ) ;
   void  operator delete( void * ) ;

   void *alloc() ;        // Allocate a piece corresponding to MemoryType
   void  free( void * ) ; // Free a piece

private:
   LinkList    chunks ;      // Chunks of pieces
   LinkList    pieces ;      // A list of available memory pieces

   int         unit_start;   // The starting # of entries for the Memory Type
   unsigned    unit_size ;   // The size of each allocated piece
   int         unit_expand ; // The expansion # of entries for the Memory Type
   int         n_repeat ;    // The number of times entry returned for 'new'
   int         n_used ;      // The number of entries used
} ;

void * D4DLL_EXP m4alloc( long ) ;
void D4DLL_EXP  m4free( void * ) ;

int  D4DLL_EXP  m4free_check( int ) ;
void D4DLL_EXP  m4check_memory() ;   // Checks MemoryType allocations



#endif

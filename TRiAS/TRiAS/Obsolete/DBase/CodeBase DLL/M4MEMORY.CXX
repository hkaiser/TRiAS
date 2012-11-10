// m4memory.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <limits.h>

#include <stdlib.h>
#include <stdio.h>
}

const int  m4num_types = 10 ;

class MemoryGroup : public Link
{
public:
   MemoryType  types[m4num_types] ;
} ; 

static LinkList  avail;   // A list of available MemoryType entries
static LinkList  used ;   // A list of used MemoryType entries
static LinkList  groups ; // A list of Allocated MemoryType groups

#ifdef DEBUG

static char **m4test_pointers ;
static int	m4num_pointer =  -1 ;
static int	m4num_used =  0 ;

static const int	m4extra_chars = 10 ;
static const char   m4check_char =  0x55 ;

// Returns the pointer to be returned; is passed the pointer allocated by malloc ...
static char *m4fix_pointer( char *start_ptr, unsigned large_len )
{
   memset( start_ptr, m4check_char, m4extra_chars ) ;
   char *return_ptr =  start_ptr + m4extra_chars ;

   memcpy( return_ptr, &large_len, sizeof(large_len) ) ;
   unsigned pos =  large_len-m4extra_chars ;
   memset( start_ptr+ pos, m4check_char, m4extra_chars ) ;

   return return_ptr + sizeof(unsigned) ;
}

// Returns the pointer allocated by malloc; 
// passed by pointer returned by 'm4fix_pointer'
static char *m4check_pointer( char *return_ptr )
{
   unsigned *large_len_ptr =  (unsigned *) (return_ptr - sizeof(unsigned)) ;
   char *malloc_ptr =  return_ptr - sizeof(unsigned) - m4extra_chars ;

   for ( int j =0; j < 2; j++ )
   {
	  char *test_ptr ;
	  if (j == 0)
		 test_ptr =  malloc_ptr ;
	  else
	  {
		 unsigned pos =  *large_len_ptr - m4extra_chars ;
		 test_ptr =  malloc_ptr + pos ;
	  }

	  for ( int i=0; i<m4extra_chars; i++ )
		 if ( test_ptr[i] != m4check_char )  
			e4severe( e4result, "Corrupted Memory Detected", (char *) 0 ) ;
   }
   return malloc_ptr ;
}

static void m4push_pointer( char *ptr )
{
   #ifdef WINDOWS
	  HANDLE  handle, *h_ptr ;
	  h_ptr =  (HANDLE *) 0 ;
   #endif

   if ( m4num_pointer < 0 )
   {
	  #ifdef WINDOWS
		 #ifdef MEDIUM
			handle =  LocalAlloc( LMEM_FIXED | LMEM_ZEROINIT, (WORD) sizeof(char *) * 100 + sizeof(HANDLE) ) ;

			if ( handle == (HANDLE) 0 )
			   e4severe( e4memory, "m4push_pointer()", "out of memory", (char *) 0 ) ;

			h_ptr =  (HANDLE *) LocalLock( handle ) ;
		 #else
			#ifdef __DLL__
			   handle =  GlobalAlloc( GMEM_FIXED | GMEM_DDESHARE | GMEM_ZEROINIT, (DWORD) sizeof(char *) * 100 + sizeof(HANDLE) ) ;
			#else
			   handle =  GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, (DWORD) sizeof(char *) * 100 + sizeof(HANDLE) ) ;
			#endif

			if ( handle == (HANDLE) 0 )
			   e4severe( e4memory, "m4push_pointer()", "out of memory", (char *) 0 ) ;

			h_ptr =  (HANDLE *) GlobalLock( handle ) ;
		 #endif
		 *h_ptr++ =  handle ;
		 m4test_pointers = (char **) h_ptr ;
	  #else
		 m4test_pointers =  (char **) malloc( sizeof(char *) * 100 ) ;
	  #endif

	  m4num_pointer =  100 ;
   }
   if ( m4num_pointer == m4num_used )
   {
	  m4num_pointer += 100 ;
	  if ( m4num_pointer > 10000 )
		 e4severe( e4result, "m4push_pointer()", "Too many pointers", (char *) 0 ) ;


	  #ifdef WINDOWS
		 HANDLE  *old_h_ptr ;
		 old_h_ptr =  (HANDLE *) (m4test_pointers) ;
		 old_h_ptr-- ;  // get the actual handle

		 #ifdef MEDIUM
			handle =  LocalReAlloc( *old_h_ptr, (WORD) sizeof(char *) * m4num_pointer + sizeof(HANDLE), LMEM_MOVEABLE ) ;

			if ( handle == (HANDLE) 0 )
			   e4severe( e4memory, "m4push_pointer()", "out of memory", (char *) 0 ) ;

			h_ptr =  (HANDLE *) LocalLock( handle ) ;
		 #else
			#ifdef __DLL__
			   handle =  GlobalReAlloc( *old_h_ptr, (DWORD) sizeof(char *) * m4num_pointer + sizeof(HANDLE), GMEM_MOVEABLE ) ;
			#else
			   handle =  GlobalReAlloc( *old_h_ptr, (DWORD) sizeof(char *) * m4num_pointer + sizeof(HANDLE), GMEM_MOVEABLE ) ;
			#endif

			if ( handle == (HANDLE) 0 )
			   e4severe( e4memory, "m4push_pointer()", "out of memory", (char *) 0 ) ;

			h_ptr =  (HANDLE *) GlobalLock( handle ) ;
		 #endif
		 *h_ptr++ =  handle ;
		 m4test_pointers = (char **) h_ptr ;
	  #else
		 m4test_pointers = (char **) realloc( m4test_pointers, sizeof(char *) *m4num_pointer ) ;
	  #endif
   }

   if ( m4test_pointers == 0 )
	  e4severe( e4memory, "m4push_pointer()", "out of memory", (char *) 0 ) ;

   m4test_pointers[m4num_used++] =  ptr ;
}

static void m4pop_pointer( char *ptr )
{
   for ( int i=m4num_used-1; i>=0; i-- )
	  if ( m4test_pointers[i] == ptr )
	  {
		 // This 'memmove' may create compile warning
		 memmove( m4test_pointers+i, m4test_pointers+i+1, (size_t) (sizeof(char *) * (m4num_used-i-1))) ;
		 m4num_used-- ;
		 return ;
	  }

   e4severe( e4result, "m4pop_pointer().", "Free value not found", (char *) 0 ) ;
}

void m4check_memory()
{
   for ( int i = 0; i < m4num_used; i++ )
	  m4check_pointer( m4test_pointers[i] ) ;
}

int m4free_check( int max_left )
{
   if ( m4num_used > max_left )
	  e4severe( e4result, "m4free_check()", "Free value not found", (char *) 0 ) ;

   return ( m4num_used ) ;
}
#endif

void *MemoryType::operator new( size_t )
{
   return 0 ;
}

MemoryType *m4memory_type( int start, unsigned unit_size, int expand, int is_temp)
{
   #ifdef DEBUG
	  unit_size += 2*m4extra_chars + sizeof(unsigned) ;
   #endif

   LinkIterator next( used ) ;

   MemoryType *on_type ;
   if ( ! is_temp )
	  while ( on_type =  (MemoryType *) next() )
	  {
		 if ( on_type->unit_size == unit_size )
		 {
			// Match
			if ( start > on_type->unit_start )
			   on_type->unit_start =  start ;
			if ( expand> on_type->unit_expand)
			   on_type->unit_expand=  expand ;
			on_type->n_repeat++ ;
			return on_type ;
		 }
	  }

   return new( start, unit_size, expand ) MemoryType ;
}

void *MemoryType::operator new( size_t, int start, unsigned unit_size, 
								int expand )
{
   // Allocate a new memory type ;
   MemoryType  *new_type =  (MemoryType *) avail.last() ;
   if ( new_type == 0 )
   {
	  MemoryGroup *group = (MemoryGroup *) m4alloc(sizeof(MemoryGroup)) ;
	  if ( group == 0 )  return 0 ;
	  for ( int i = 0; i<m4num_types; i++ )  avail.add( group->types+i ) ;
	  new_type =  (MemoryType *) avail.last() ;
	  groups.add( group ) ;
   }

   avail.remove( new_type ) ;
   used.add( new_type ) ;

   new_type->unit_start =  start ;
   new_type->unit_size  =  unit_size ;
   new_type->unit_expand=  expand ;
   new_type->n_repeat =  1 ;
   new_type->n_used   =  0 ;

   return new_type ;
}

void MemoryType::operator delete( void *p )
{
   used.remove( (Link *) p ) ;
   avail.add( (Link *) p ) ;
}

void m4release( MemoryType *memory_type )
{
   if ( memory_type == 0 )  return ;

   memory_type->n_repeat-- ;
   if ( memory_type->n_repeat == 0 )
   {
	  LinkIterator next(memory_type->chunks) ;
	  Link *ptr ;
	  while ( ptr = next() )
		 m4free( ptr ) ;

	  delete memory_type ;
   }
}

void *MemoryType::alloc()
{
   Link *next_piece =  pieces.pop() ;
   if ( next_piece != 0 )
   {
	  #ifdef DEBUG
		 n_used++ ;
		 char *ptr =  m4fix_pointer( (char *) next_piece, unit_size ) ;
		 m4push_pointer( ptr ) ;
		 return ptr ;
	  #else
		 return next_piece ;
	  #endif
   }

   Chunk *new_chunk =  new(this) Chunk ;
   if ( new_chunk == 0 )  return 0 ;
   chunks.add( (Link *) new_chunk ) ;

   n_used++ ;
   #ifdef DEBUG
	  char *ptr =  m4fix_pointer( (char *) pieces.pop(), unit_size ) ;
	  m4push_pointer( ptr ) ;
	  return ptr ;
   #else
	  return pieces.pop() ;
   #endif
}

void MemoryType::free( void *free_ptr )
{
   n_used-- ;
   #ifdef DEBUG
	  if ( n_used < 0 )  e4severe( e4result, "MemoryType::free()", (char *) 0 ) ;
	  m4pop_pointer( (char *) free_ptr ) ;
	  pieces.add( (Link *) m4check_pointer( (char *) free_ptr )   ) ;
   #else
	  pieces.add( (Link *) free_ptr ) ;
   #endif
}

void *Chunk::operator new( size_t, MemoryType *type_ptr )
{
   int  n_allocate = type_ptr->unit_expand ;
   if ( type_ptr->chunks.last() == 0 )  n_allocate =  type_ptr->unit_start ;

   Chunk *chunk_ptr =  (Chunk *) 
	  m4alloc( sizeof(Link)+ (long)n_allocate*type_ptr->unit_size ) ; 
   if ( chunk_ptr == 0 )  return 0 ;

   char *ptr =  (char *) &chunk_ptr->data ;
   for ( int i = 0; i < n_allocate; i++ )
	  type_ptr->pieces.add( (Link *) (ptr+i*type_ptr->unit_size) ) ;

   return  chunk_ptr ;
}

#ifdef M4STATS
void m4stats()
{
   #ifndef WINDOWS
	  printf( "\nSize   Start   Expand   # Avail   # Used   # Chunks\n" ) ;
   #endif

   LinkIterator  next( used ) ;
   MemoryType *on_type ;
   while ( on_type = (MemoryType *) next() )
   {
	  #ifndef WINDOWS
		 printf( " %d	 %d  ", on_type->unit_size, on_type->unit_start ) ;
		 printf( " %d	 ", on_type->unit_expand ) ;

		 printf( " %d	 ",	on_type->pieces.n_link ) ;
		 printf( " %d	 ",	on_type->n_used ) ;
		 printf( " %d	 \n",  on_type->chunks.n_link ) ;
	  #endif

	  on_type->chunks.check() ;
	  on_type->pieces.check() ;
   }

   avail.check() ;
   used.check() ;
}
#endif

#ifdef M4MAX
   long  m4max_memory =  0x4000 ;
   long  m4allocated  =  0L ;
   #ifndef DEBUG
	  DEBUG should be set with M4MAX (force compile error.)
   #endif
#endif

void * m4alloc( long n )
{
   #ifdef DEBUG
	  if ( n == 0L )  e4severe( e4parm, "m4alloc()", "Zero parameter", (char *) 0 ) ;
	  n += m4extra_chars*2 + sizeof(unsigned) ;
   #endif

   #ifdef M4MAX
	  // Assumes 'm4max_memory' is less than the actual maximum
	  if ( m4allocated + n >  m4max_memory )  return 0 ;
	  m4allocated +=  n ;
   #endif

   size_t s = (size_t) n ;
   if ( n > (long) s )  return 0 ;

   char *ptr ;

   #ifdef WINDOWS
	  HANDLE  handle, *h_ptr ;
	  h_ptr =  (HANDLE *) 0 ;

	  #ifdef MEDIUM
		 #ifdef __DLL__
			Error, cannot create a Medium memory model DLL with Borland C++ 2.0
		 #endif
		 handle =  LocalAlloc( LMEM_FIXED | LMEM_ZEROINIT, (WORD) s+ sizeof(HANDLE) ) ;

		 if ( handle == (HANDLE) 0 )  return 0 ;

		 h_ptr =  (HANDLE *) LocalLock( handle ) ;
	  #else
		 #ifdef __DLL__
			handle =  GlobalAlloc( GMEM_FIXED | GMEM_DDESHARE | GMEM_ZEROINIT, (DWORD) s+ sizeof(HANDLE) ) ;
		 #else
			handle =  GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, (DWORD) s+ sizeof(HANDLE) ) ;
		 #endif

		 if ( handle == (HANDLE) 0 )  return 0 ;

		 h_ptr =  (HANDLE *) GlobalLock( handle ) ;
	  #endif
	  *h_ptr++ =  handle ;
	  ptr = (char *) h_ptr ;
   #else
	  ptr =  (char *) malloc( s ) ;
	  if ( ptr == 0 )  return 0 ;
	  #ifndef DEBUG
		 memset( ptr, 0, s ) ;
	  #endif
   #endif

   #ifdef DEBUG
	  ptr =  m4fix_pointer( ptr, s ) ;
	  m4push_pointer( ptr ) ;
	  memset( ptr, 0, s-m4extra_chars*2 - sizeof(unsigned) ) ;
   #endif

   return (char *) ptr ;
}

void m4free( void *ptr )
{
   #ifdef M4MAX
	  unsigned *amount =  (unsigned *) ptr ;
	  m4allocated -=  amount[-1] ;
   #endif

   #ifdef WINDOWS
	  HANDLE  hand ;

	  #ifdef DEBUG
		 m4pop_pointer( (char *) ptr ) ;
		 hand =  ((HANDLE *) m4check_pointer( (char *) ptr ))[-1] ;
	  #else
		 hand =  ((HANDLE *) ptr)[-1] ;
	  #endif

	  #ifdef MEDIUM
		 hand =  LocalFree( hand ) ;
	  #else
		 hand =  GlobalFree( hand ) ;
	  #endif

	  if ( hand != (HANDLE) 0 )	
		 e4severe( e4memory, "memory error", (char *) 0 ) ;
   #else
	  #ifdef DEBUG
		 m4pop_pointer( (char *) ptr ) ;
		 free( m4check_pointer( (char *) ptr )  ) ;
	  #else
		 free( ptr ) ;
	  #endif
   #endif
}

void m4reset()
{
   #ifdef L4LOCK_CHECK
	  e4severe( e4result, "m4reset()", "L4LOCK_CHECK cannot be used with 'm4reset'", (char *) 0 ) ;
   #endif

   LinkIterator  next_type( used ) ;

   for ( MemoryType *on_type; on_type =  (MemoryType *) next_type(); )
   {
	  LinkIterator  next_chunk( on_type->chunks ) ;

	  for ( Link *on_chunk; on_chunk = next_chunk(); )
		 m4free( on_chunk ) ;
   }

   LinkIterator  next_group( groups ) ;

   for ( Link *on_group; on_group =  next_group(); )
	  m4free( on_group ) ;

   avail.reset() ;
   used.reset() ;
   groups.reset() ;
}

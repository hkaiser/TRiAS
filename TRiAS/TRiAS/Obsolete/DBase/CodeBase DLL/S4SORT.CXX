// s4sort.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

// Internal sort information is saved as follows:  
//	Sort Info, Rec Num, Other Info

// s4quick assumes there is an extra four bytes where the record number
// is put.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <limits.h>
}

#ifdef D4DLLS
   extern "C" {
   SORT_FUNCTION dll_memcmp( const void *a, const void *b, size_t c ) // #JB920611 #JB940923 --> Attribut reaktiviert
   {
	  return memcmp( a,b,c ) ; }
   }
#endif

#ifdef __ZTC__
   SORT_FUNCTION zc_memcmp( const void *a, const void *b, size_t c )
   {
	  return memcmp( a,b,c ) ;
   }
#endif

Sort::Sort( CodeBase *cb ) : seqwrite_buffer( 0,0 ), file(cb)
{
   code_base =  cb ;
   pointers  =  0 ;
   spool_pointer =  0 ;
   #ifdef __ZTC__
	  cmp =  zc_memcmp ;
   #else
	  #ifdef D4DLLS
		 cmp =  /*(T4CMP_ROUTINE*)*/ dll_memcmp ;   // #JB911218; #JB940923 --> typecast aufgehoben
	  #else
		 cmp =  memcmp ;
	  #endif
   #endif
}

Sort::~Sort()
{
   free() ;
}

void Sort::delete_spool_entry()
{
   memcpy( spool_pointer, spool_pointer+1, --spools_n * sizeof(Spool) ) ;
}

Sort::flush()
{
   s4quick( (void **) pointers, pointers_used, cmp, sort_len ) ;

   if ( spools_max == 0 )  // Temporary file must be created.
   {
	  file.temp() ;
	  seqwrite.init( file, 0L, seqwrite_buffer) ;
   }

   for ( int i = 0; i < pointers_used; i++ )
	  if ( seqwrite.write( StrLen(pointers[i], tot_len) ) < 0 ) return -1 ;

   pointers_used =  0 ;
   if ( (long) spools_max * (long) sizeof(Spool) >= (long) UINT_MAX )
   {
	  free() ;
	  code_base->error( e4memory, "Sorting", (char *) 0 ) ;
	  return e4memory ;
   }
   spools_max++ ;

   return 0 ;
}

int  Sort::free()
{
   if ( spool_pointer != 0 )
   {
	  m4free( spool_pointer ) ;
	  spool_pointer =  0 ;
   }

   if ( pointers != 0 )
   {
	  m4free( pointers ) ;
	  pointers =  0 ;
   }

   if ( seqwrite_buffer.p != 0 )
   {
	  m4free( seqwrite_buffer.p ) ;
	  seqwrite_buffer.p =  0 ;
   }

   pool.reset() ;
   return file.close() ;
}

int Sort::get_init()
{
   if ( code_base->error() )  return -1 ;
   if ( spools_max > 0 )
   {
	  flush() ;
	  if ( seqwrite.flush() < 0 )  return -1 ;
	  #ifdef DEBUG
		 if (seqwrite_buffer.p == 0 )  e4severe( e4info, "Sort::get_init", (char *) 0 ) ;
	  #endif
	  m4free( seqwrite_buffer.p ) ;
	  seqwrite_buffer.p =  0 ;
   
	  m4free( pointers ) ;
	  pointers =  0 ;
   
	  for (;;)
	  {
		 spool_pointer =  (Spool *) m4alloc( sizeof(Spool) * (unsigned) spools_max ) ;
		 if ( spool_pointer != 0 )  break ;

		 if ( pool.last() == 0 )
		 {
			free() ;
			return code_base->error( e4memory, "Sorting", (char *) 0 ) ;
		 }

		 pool.remove( pool.last() ) ;
		 pool_n-- ;
	  }

	  int entries_per_spool, spools_per_pool ;
	  for(;;)
	  {
		 // Split up the pools between the spools
		 if ( pool_n == 0 )
			spools_per_pool =  spools_max ;
		 else
			spools_per_pool =  (spools_max+pool_n-1) / pool_n ;

		 entries_per_spool =  pool_entries/spools_per_pool ;
		 if ( entries_per_spool == 0 )
		 {
			free() ;
			return code_base->error( e4memory, "Sorting", (char *) 0 ) ;
		 }
		 if ( pool_n != 0 )  break ;

		 if ( pool.add() != 0 ) 
			pool_n++ ;
		 else
		 {
			pool_entries /= 2 ;
			pool.reset() ;
			pool.init( 1, unsigned(pool_entries)*tot_len+sizeof(Link), 1, 1 ) ;
		 }
	  }

	  spool_mem_len  =   entries_per_spool*tot_len ;
	  spool_disk_len =   long(pointers_init) * tot_len ;

	  LinkIterator  next(pool) ;
	  int entries_used =  pool_entries+1 ;  // Entries used in current pool.
	  char *pool_entry ;

	  for ( long spool_disk_i = 0L; spools_n < spools_max; )
	  {
		 memmove( spool_pointer+1, spool_pointer, sizeof(Spool)*spools_n ) ;
		 if ( entries_used + entries_per_spool > pool_entries )
		 {
			entries_used =  0 ;
			pool_entry   =  (char *) (next()+1) ;
		 }
		 spool_pointer->ptr =  pool_entry ;
		 pool_entry   +=  (tot_len*entries_per_spool) ;
		 entries_used +=  entries_per_spool ;

		 spool_pointer->spool_i =  spools_n++ ;
		 spool_pointer->disk	=  spool_disk_i ;
		 spool_disk_i +=  spool_disk_len ;

		 spool_pointer->len = 0 ;
		 if ( spools_n < spools_max )
			next_spool_entry() ;
	  }
   }
   else
   {
	  s4quick( (void **) pointers, pointers_used, cmp, sort_len ) ;
	  #ifdef DEBUG
		 if (seqwrite_buffer.p == 0 )  e4severe( e4info, "Sort::get_init", (char *) 0 ) ;
	  #endif
	  m4free( seqwrite_buffer.p ) ;
	  seqwrite_buffer.p =  0 ;
   }
   return 0 ;
}

int Sort::get( long *rec_ptr, void **sort_data, void **info_ptr )
{
   char *ptr ;
   int rc =  get_ptr_ptr( &ptr ) ;   if ( rc != 0 )  return rc ;

   memcpy( rec_ptr, ptr+ sort_len, sizeof(long) ) ;
   *sort_data=  (void *) ptr ;
   *info_ptr =  (void *) (ptr + info_offset) ;

   return 0 ;
}

int Sort::get_ptr_ptr( char **ptr_ptr )
{
   if ( pointers != 0 )  // then no spooling was done
   {
	  if ( pointers_i < pointers_used )
	  {
		 *ptr_ptr =  (char *) pointers[pointers_i++] ;
		 return 0 ;
	  }
	  if ( free() < 0 )  return -1 ;
	  return 1 ;
   }

   if ( spools_n <= 0 )
   {
	  if ( free() < 0 )  return -1 ;
	  return 1 ;  // None available
   }

   if ( next_spool_entry() < 0 )  return -1 ;
   if ( spools_n <= 0 )  return 1 ;
   *ptr_ptr =  spool_pointer->ptr+spool_pointer->pos ;

   return 0 ;
}

int Sort::init( int sort_l, int info_l )
{
   int rc ;
   if ( (rc = free()) < 0 )  return rc ;

   file.name.set_max( 12 ) ; // Allocate name memory now.

   spool_pointer = 0 ;
   pointers = 0 ;

   spools_max =  spools_n = pointers_i = pointers_used = pointers_init =
			  pool_n = spool_mem_len = 0 ;
   spool_disk_len =  0L ;

   sort_len =  sort_l ;
   info_len =  info_l ;
   info_offset =  sort_len + sizeof(long) ;
   tot_len  =  info_offset + info_len ;
   #ifdef PORTABLE
	  if ( tot_len % sizeof(double) != 0 )
		 tot_len +=  sizeof(double) -  tot_len % sizeof(double) ;
   #endif
   pool_entries =  (code_base->sort_pool_size-sizeof(Link))/ tot_len ;

   pointers_max =  code_base->sort_pool_size/sizeof(char*) ;

   is_mem_avail =  1 ;

   char *temp_ptr =  (char *) m4alloc( code_base->sort_buffer_size) ;
   if ( temp_ptr == 0 )  return code_base->error( e4memory, (char *) 0 ) ;

   seqwrite_buffer.init( temp_ptr, code_base->sort_buffer_size ) ;
   seqwrite.init( file, 0L, seqwrite_buffer ) ;

   for(;;)
   {
	  pointers =  (char **) m4alloc( pointers_max * sizeof(char *) ) ;
	  if ( pointers != 0 )  break ;

	  pointers_max /= 2 ;
	  if ( pointers_max < 256 )
	  {
		 free() ;
		 return code_base->error( e4memory, "Sorting", (char *) 0 ) ;
	  }
   }

   if ( pool.init( 1, code_base->sort_pool_size, 1, 1 ) < 0 )
   {
	  free() ;
	  return code_base->error( e4memory, "Sorting", (char *) 0 ) ;
   }

   return 0 ;
}

void Sort::init_pointers( char *avail_mem, unsigned len )
{
   // Assign 'pointers'
   int n =  len / tot_len ;
   int i =  pointers_init ;

   pointers_init +=  n ;
   if ( pointers_init > pointers_max )
	  pointers_init =  pointers_max ;

   for ( ; i < pointers_init; i++, avail_mem += tot_len )
	  pointers[i] =  avail_mem ;
}

int Sort::next_spool_entry()
{
   spool_pointer->pos  +=  tot_len ;

   if ( spool_pointer->pos >= spool_pointer->len )
   {
	  spool_pointer->pos =  0 ;
	  if ( spool_pointer->disk >= 0L )
	  {
		 long last_disk_pos  =  (spool_pointer->spool_i+1) * spool_disk_len  ;
		 long disk_data_left =  last_disk_pos - spool_pointer->disk ;
		 unsigned max_read =  spool_mem_len ;
		 if (spool_mem_len > (unsigned) disk_data_left )		// #JB950623	
			max_read =  unsigned(disk_data_left) ;
		 unsigned len_read =  max_read ;
		 if ( file.read( spool_pointer->disk,
				  StrLen(spool_pointer->ptr,spool_mem_len), &len_read) < 0 )
		 {
			free() ;
			return -1 ;
		 }

		 spool_pointer->len   =  len_read ;
		 spool_pointer->disk +=  len_read ;
		 if ( len_read != max_read  ||  len_read == 0 )
		 {
			if ( len_read % tot_len  != 0 )
			{
			   free() ;
			   return code_base->error( e4read, file.name.ptr(), (char *)  0) ;
			}
			spool_pointer->disk =  -1 ;
			if ( len_read == 0 )
			{
			   delete_spool_entry() ;
			   return 0 ;
			}
			else
			   spool_pointer->len =  len_read ;
		 }
		 else
			// Check if we are out of disk entries for the spool
			if ( spool_pointer->disk >= last_disk_pos )
			   spool_pointer->disk =  -1L ;
	  }
	  else
	  {
		 delete_spool_entry() ;
		 return 0 ;
	  }
   }

   // Position the new entry to the sorted location using a binary search
   // New entry is placed before 'result':  int pos >= 1  when complete
   int low   =  1 ;
   int high  =  spools_n ;
   char *new_data =  spool_pointer->ptr + spool_pointer->pos ;
   long  new_rec ;
   memcpy( &new_rec, new_data + sort_len, sizeof(new_rec) ) ;

   for(;;)
   {
	  int pos =  (low+high)/2 ;
	  if ( pos == low && pos == high )  // then found
	  {
		 Spool save_spool ;
		 memcpy( &save_spool, spool_pointer, sizeof(Spool) ) ;
		 memmove( spool_pointer, spool_pointer+1, sizeof(Spool)*(pos-1) ) ;
		 memcpy( spool_pointer+pos-1, &save_spool, sizeof(Spool) ) ;
		 return 0 ;
	  }
	  int rc = (*cmp)(new_data, spool_pointer[pos].ptr + spool_pointer[pos].pos, sort_len) ;
	  if ( rc == 0 )
	  {
		 long  spool_rec ;
		 memcpy( &spool_rec, spool_pointer[pos].ptr + spool_pointer[pos].pos + sort_len, sizeof(spool_rec) ) ;
		 if ( new_rec > spool_rec )  rc =  1 ;
	  }

	  if ( rc > 0 )
		 low =  pos+1 ;
	  else
		 high = pos ;
	  #ifdef DEBUG
		 if ( high < low )  e4severe( e4result, "Sort::next_spool_entry()", (char *) 0 ) ;
	  #endif
   }
}

int Sort::put( long rec, void *sort_data, void *info )
{
   if ( pointers_used >= pointers_init )
   {
	  if ( pointers_used < pointers_max  && is_mem_avail )
	  {
		 char  *ptr =  (char *) pool.add() ;
		 if ( ptr == 0 )
		 {
			#ifndef PORTABLE
			   int  ptr_mem_avail = (pointers_max-pointers_used)*sizeof(char *) - sizeof(long) ;
			   int  new_entries   = ptr_mem_avail/(sizeof(char *)+tot_len) ;

			   pointers_max =  pointers_used+ new_entries ;

			   init_pointers( (char *) (pointers+pointers_max), new_entries*tot_len);
			#endif

			is_mem_avail = 0  ;
		 }
		 else
		 {
			pool_n++ ;
			init_pointers( ptr+sizeof(Link), code_base->sort_pool_size-sizeof(Link)) ;
		 }
	  }
   }

   int rc ;
   if ( pointers_used >= pointers_init )
	  if ( (rc = flush()) < 0 )  return rc ;

   #ifdef DEBUG
	  if ( pointers_used >= pointers_init )
		 e4severe( e4result, "Sort::put", (char *) 0 ) ;
   #endif

   char *ptr =  pointers[pointers_used++] ;
   memcpy( ptr, sort_data, sort_len ) ;
   memcpy( ptr+ sort_len, &rec, sizeof(rec) ) ;
   memcpy( ptr+ info_offset, info, info_len ) ;

   return 0 ;
}


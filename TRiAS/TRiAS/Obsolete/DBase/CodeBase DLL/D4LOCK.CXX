// d4lock.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

const long lock_pos =  1000000000L ;

int  Data::lock_append()
{
   if ( lock_test_append() > 0 )  return 0 ;
   unlock_index() ;
   int rc =  file.lock( lock_pos, 1L ) ;
   if ( rc != 0 )  return rc ;
   append_lock =  1 ;
   return 0 ;
}

int  Data::lock_file()
{
   if ( lock_test_file() > 0 )  return 0 ;
   unlock_all() ;
   int rc ;
   if ( (rc = file.lock(lock_pos,lock_pos)) != 0 )  return rc ;
   file_lock =  1 ;
   return 0 ;
}

int  Data::lock( long rec )
{
   #ifdef DEBUG
	  if ( rec <= 0 )
		 e4severe( e4parm, "Data::lock()", (char *) 0 ) ;
   #endif
   if ( lock_test(rec) > 0 )  return 0 ;
   unlock_append() ;
   unlock_index() ;
   unlock_records() ;
   int rc ;
   if ( (rc = file.lock( lock_pos+rec, 1L) ) != 0 )  return rc ;

   num_locked =  1 ;
   *locks =  rec ;
   return 0 ;
}

int  Data::lock( long *recs, int n_recs )
{
   if ( lock_test_file() > 0 )  return 0 ;
   unlock_append() ;
   unlock_index() ;
   if ( unlock_records() < 0 )  return -1 ;

   if ( n_locks < n_recs )
   {
	  if (n_locks > 1)  m4free(locks) ;
	  locks =  (long *) m4alloc( sizeof(long) * n_recs ) ;
	  if ( locks == 0 )
	  {
		 n_locks =  1 ;
		 locks =  &locked_record ;
		 return  code_base->error( e4memory, (char *) 0 ) ;
	  }
	  n_locks =  n_recs ;
   }

   num_locked =  n_recs ;
   for ( int i = 0; i < n_recs; i++ )
   {
	  int rc ;
	  if ( (rc = file.lock( lock_pos+recs[i], 1L )) != 0 )
	  {
		 num_locked =  i ;
		 return rc ;
	  }
	  locks[i] =  recs[i] ;
   }

   return 0 ;
}

int Data::lock_test_file()
{
   if ( code_base->error() ) return -1 ;
   return  file_lock ? 1 : 0 ;
}

int Data::lock_test_append()
{
   if ( code_base->error() ) return -1 ;
   return  (file_lock || append_lock)  ?  1 : 0 ;
}

int Data::lock_test( long rec )
{
   if ( code_base->error() ) return -1 ;
   if ( file_lock )  return 1 ;
   for ( int i = 0; i < num_locked; i++ )
	  if ( locks[i] == rec )  return 1 ;
   return 0 ;
}

Data::unlock_all()
{
   unlock_file() ;
   unlock_append() ;
   return  unlock_records() ;
}

int Data::unlock_append()
{
   if ( append_lock )
   {
	  if ( file.unlock( lock_pos, 1L ) < 0 )  return -1 ;
	  append_lock =  0 ;
	  header.num_recs =  -1 ;
   }
   return code_base->error() ;
}

int Data::unlock_file()
{
   if ( file_lock )
   {
	  if ( file.unlock( lock_pos, lock_pos ) < 0 )  return -1 ;
	  rec_num_old =  -1 ;
	  file_lock =  0 ;
	  header.num_recs =  -1 ;
   }
   return code_base->error() ;
}

int Data::unlock_records()
{
   if ( code_base->error() )  return -1 ;
   rec_num_old =  -1 ;

   while ( --num_locked >= 0 )
	  if ( file.unlock( lock_pos+ locks[num_locked], 1L ) < 0 )  return -1 ;
   return 0 ;
}



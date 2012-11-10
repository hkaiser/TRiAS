// d4DataIndex.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

__export DataIndex::DataIndex( CodeBase *cb, char *name ) : Data( cb, name )
{
   bof_flag =  eof_flag =  0 ;
   production =  0 ;
   production_group = 0 ;
   #ifdef OTHER_NDX
	  if ( name != 0 && cb->auto_open )   // no has_mdx flag for NDX/CLIPPER
   #else
	  if ( name != 0 && has_mdx && cb->auto_open )
   #endif
   {
	  #ifdef OTHER_NDX
		  production_group = new( cb ) IndexGroupFile( this ) ;
	  #else
		 Index *index_ptr =  new( cb ) Index( this ) ;
		 if ( index_ptr == 0 )
		 {
			code_base->error( e4memory, (char *) 0 ) ;
			return ;
		 }
		 index_ptr->open() ;
	  #endif
   }
}

__export DataIndex::~DataIndex()
{
   close() ;
}

int __export DataIndex::close()
{
   int final_rc =  code_base->error_set(0) ;
   int save_wait =  code_base->wait ;
   code_base->wait =  1 ;

   if ( file.open_test() )
   {
	  if ( flush_all() < 0 )  final_rc =  code_base->error_set(0) ;

	  if ( file_changed )
	  {
		 lock_append() ;
		 if ( update_header(1,1) < 0 )  final_rc =  code_base->error_set(0) ;
	  }
	  if ( unlock_all() < 0 )  final_rc =  code_base->error_set(0) ;
   }

   LinkIterator next( indexes ) ;

   Index *index_on ;
   while ( index_on =  (Index *) next() ) {
	  if ( index_on->close() < 0 )  
		 final_rc =  code_base->error_set(0) ;
	  #ifdef OTHER_NDX
		 if ( index_on->need_delete ) delete index_on ;
	  #endif
   }

   if ( Data::close() < 0 )  final_rc =  code_base->error_set(0) ;
   #ifdef OTHER_NDX
	  if ( production_group != 0 )
	  {
		 delete production_group ;
		 production_group = 0 ;
	  }
   #else
	  if ( production != 0 )
	  {
		 delete production ;
		 production = 0 ;
	  }
   #endif

   code_base->wait =  save_wait ;
   code_base->error_set( final_rc ) ;
   return  final_rc ;
}

int __export DataIndex::eof()
{
   if ( code_base->error() )  return -1 ;
   return eof_flag ;
}

int __export DataIndex::open( char *name )
{
   if ( close() < 0 )  return -1 ;
   int rc =  Data::open(name) ;  if ( rc != 0 )  return rc ;
   bof_flag =  eof_flag =  num_locked =  file_lock =  append_lock =  0 ;

   #ifdef OTHER_NDX
	  if ( code_base->auto_open )
   #else
	  if ( has_mdx && code_base->auto_open )
   #endif
   {
	  #ifdef OTHER_NDX
		 production_group = new( code_base ) IndexGroupFile( this ) ;
		 if ( production_group == 0 )  return code_base->error( e4memory, (char *) 0 ) ;
		  rc = production_group->open( name ) ;
		  if ( rc ==  r4no_open )   // group file doesn't exist! (just don't open!)
		  {
			delete production_group ;
			production_group = 0 ;
			 rc = 0 ;	// mark as continue!
		  }
	  #else
		 production =   new(code_base) Index( this, 0 ) ;
		 if ( production == 0 )  return code_base->error( e4memory, (char *) 0 ) ;
		 rc =  production->open() ;
	  #endif
	  if ( rc != 0 )
	  {
		 close() ;
		 return rc ;
	  }
	  #ifndef OTHER_NDX
		 if ( !production->is_production() )   // non-production index
		  {
			 production->close() ;
			delete production ;
			production = 0 ;
		  }
	  #endif
   }

   return 0 ;
}




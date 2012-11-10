// d4datafilt.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

__export DataFilter::DataFilter()
{
   data =  0 ;
   routine =  0 ;
   routine_data =  0 ;
}

int DataFilter::bottom()
{
   int rc ;

   if ( (rc = data->bottom()) != 0 )  return rc ;
   rc = find_good(-1) ;
   if ( rc == r4keep )
	  return 0 ;
   if ( rc == r4bof )
   {
	  data->bof_flag =  1 ;
	  return filter_go_eof() ;
   }
   return rc ;
}


DataFilter::filter_test()
{
   #ifdef DEBUG
	  #if ! defined(__ZTC__) && defined (MEDIUM)
		 if (u4ptr_equal( routine, 0)) e4severe( e4info, "DataFilter::filter_test", (char *) 0);
	  #endif
   #endif
   return (*routine)( routine_data ) ;
}

DataFilter::find_good( int sign )
{
   int rc ;
   for(;;)
   {
	  rc = filter_test() ;
	  if ( rc != r4ignore )   return rc ;
	  if ( (rc = data->skip((long) sign)) != 0 )  return rc ;
   }
}

DataFilter::filter_go_eof()
{
   int rc =  data->go_eof() ;  
   if ( rc != r4eof )  return rc ;
   rc = filter_test() ;
   if ( rc != r4keep  &&  rc != r4ignore )  return rc ;
   return r4eof ;
}

int __export DataFilter::go( long new_rec )
{
   int rc =  data->go(new_rec) ;
   if ( rc != 0 )  return rc ;

   rc =  (*routine)( routine_data ) ;
   if ( rc == r4ignore )
	  return r4entry ;
   if ( rc == r4keep )
	  return 0 ;
   return rc ;
}

__export DataFilter::seek( double d )
{
   int rc =  seek_do( data->seek(d) ) ;
   if ( rc != 0 )  return rc ;

   // 0 may become r4after
   #ifdef OTHER_NDX
	  Index *tag_ptr =  data->index_default() ;
   #else
	  Tag *tag_ptr =  data->tag_default() ;
   #endif

   double d_on =  double(tag_ptr->expr) ;
   if ( code_base->error() )  return -1 ;

   double diff = d_on - d ;
   if ( diff < -d4accuracy || diff > d4accuracy )  
	  return r4after ;

   return 0 ;
}

__export DataFilter::seek( Str& s )
{
   int rc =  seek_do( data->seek(s) ) ;
   if ( rc != 0 )  return rc ;

   // 0 may become r4after
   String final_str( code_base ) ;

   #ifdef OTHER_NDX
	  Index *tag_ptr =  data->index_default() ;
   #else
	  Tag *tag_ptr =  data->tag_default() ;
   #endif

   // do the search according to the tag-type
   switch ( tag_ptr->type() )
   {
	  case ( t4num_doub ) :
	  { 
		 double d = c4atod( s.ptr(), s.len() ) ;
		 double d_on =  double(tag_ptr->expr) ;
		 if ( code_base->error() )  return -1 ;

		 double diff = d_on - d ;
		 if ( diff < -d4accuracy || diff > d4accuracy )  
			return r4after ;

		 return 0 ;
	  }		 
		  break ;
	  case ( t4num_bcd ) :
	  { 
		  #ifdef OTHER_NDX
			 #ifdef DEBUG
				e4severe( e4info, "NDX or NTX index file encountering MDX structures!", (char *) 0 ) ;
			 #else
				return -1 ;
			 #endif
		  #else
			BCD bcd ;   StrMax sbcd( &bcd, sizeof(bcd) ) ;
			c4stob( sbcd, s ) ;
			String key_bcd( code_base ) ;
			 
			if( tag_ptr->expr.key( key_bcd ) != t4num_bcd )
			   return -1 ;
			 
			if ( sbcd == key_bcd )
			return 0 ;
			break ;
		  #endif
	  } 
	  default :
	  { 
		 rc = tag_ptr->expr.string( final_str ) ;
		 if ( rc < 0 )  return -1 ;

		 unsigned compare_len =  s.len() ;
		 if ( compare_len > final_str.len() )
			compare_len =  final_str.len() ;

		 StrLen compare_str( final_str.ptr(), compare_len ) ;
		 if ( compare_str == s )
			return 0 ;
	  }
		  break ;
   }

   return r4after ;
}

DataFilter::seek_do( int seek_rc )
{
   if ( seek_rc != r4after  &&  seek_rc != 0 )
	  return seek_rc ;

   int rc =  find_good(1) ;
   if ( rc != r4keep )  return rc ;

   return seek_rc ;
}

__export DataFilter::skip( long n )
{
   if ( code_base->error() )  return -1 ;

   int  sign ;
   if ( n < 0 )
   {
	  n = -n ;
	  sign = -1 ;
   }
   else
	  sign =  1 ;

   long good_rec ; 

   while ( n-- )  // skip a record
   {
	  int rc ;

	  good_rec =  data->recno() ;
	  data->skip(sign) ;
	  rc = find_good(sign) ;

	  if ( rc != r4keep )
	  {
		 if ( rc != r4eof && rc != r4bof )  return rc ;

		 if ( sign > 0 )
		 {
			if ( (rc = filter_go_eof()) != r4eof )  return rc ;
			return r4eof ;
		 }
   
		 int  save_flag =  code_base->go_error ;
		 code_base->go_error =  0 ;
		 rc = data->go(good_rec) ;
		 code_base->go_error =  save_flag ;
		 data->bof_flag =  1 ;
		 if ( rc != 0 )  return rc ;
		 return r4bof ;
	  }
   }
   return 0 ;
}

__export DataFilter::top()
{
   int  rc ;
   if ( (rc = data->top()) != 0 )  return rc ;
   rc =  find_good(1) ;
   if ( rc == r4keep )
	  return 0 ;
   if ( rc == r4eof )
   {
	  data->bof_flag =  1 ;
	  if ( (rc = filter_go_eof()) != r4eof )  return rc ;
	  return r4eof ;
   }
   return rc ;
}

// folgende Funktionen wurden speziell für die Komplex-Recherche geschaffen
int __export ExtDataFilter :: seek_on (double d, long SkipValue)
{
// prüfe Filter-Bedingung
   int rc = skip (SkipValue);
   if ( rc != 0 )  return rc ;

// prüfe akt. KeyValue
   #ifdef OTHER_NDX
	  Index *tag_ptr =  data->index_default() ;
   #else
	  Tag *tag_ptr =  data->tag_default() ;
   #endif

   double d_on =  double(tag_ptr->expr) ;
   if ( code_base->error() )  return -1 ;

   double diff = d_on - d ;
   if ( diff < -d4accuracy || diff > d4accuracy )  
	  return r4after ;

   return 0 ;
}

int __export ExtDataFilter :: seek_on (Str &s, long SkipValue)
{
// prüfe Filter-Bedingung
   int rc = skip (SkipValue);
   if ( rc != 0 )  return rc ;

// prüfe akt. KeyValue
   String final_str( code_base ) ;

   #ifdef OTHER_NDX
	  Index *tag_ptr =  data->index_default() ;
   #else
	  Tag *tag_ptr =  data->tag_default() ;
   #endif

   // do the search according to the tag-type
   switch ( tag_ptr->type() )
   {
	  case ( t4num_doub ) :
	  {
		 double d = c4atod( s.ptr(), s.len() ) ;
		 double d_on =  double(tag_ptr->expr) ;
		 if ( code_base->error() )  return -1 ;

		 double diff = d_on - d ;
		 if ( diff < -d4accuracy || diff > d4accuracy )  
			return r4after ;

		 return 0 ;
	  }
		  break ;
	  case ( t4num_bcd ) :
	  {
		  #ifdef OTHER_NDX
			 #ifdef DEBUG
				e4severe( e4info, "NDX or NTX index file encountering MDX structures!", (char *) 0 ) ;
			 #else
				return -1 ;
			 #endif
		  #else
			BCD bcd ;   StrMax sbcd( &bcd, sizeof(bcd) ) ;
			c4stob( sbcd, s ) ;
			String key_bcd( code_base ) ;
			 
			if( tag_ptr->expr.key( key_bcd ) != t4num_bcd )
			   return -1 ;
			 
			if ( sbcd == key_bcd )
			return 0 ;
			break ;
		  #endif
	  } 
	  default :
	  {
		 rc = tag_ptr->expr.string( final_str ) ;
		 if ( rc < 0 )  return -1 ;

		 unsigned compare_len =  s.len() ;
		 if ( compare_len > final_str.len() )
			compare_len =  final_str.len() ;

		 StrLen compare_str( final_str.ptr(), compare_len ) ;
		 if ( compare_str == s )
			return 0 ;
	  } 
		  break ;
   }

   return r4after ;
}

int __export ExtDataFilter :: seek_on (char *p, long SkipVal)
{
	return seek_on (StrPtr (p), SkipVal);
}

__export ExtDataFilter :: ExtDataFilter() : DataFilter ()
{
	// nothing to do
}

__export ExtDataFilter :: ~ ExtDataFilter()
{
	// nothing to do
}


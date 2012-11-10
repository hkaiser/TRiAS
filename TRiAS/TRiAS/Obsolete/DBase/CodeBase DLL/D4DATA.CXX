// d4data.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

extern "C" {
#include <string.h>
#include <limits.h>
}

__export Data::Data( CodeBase *cb, char *dbf_name ) : file( cb )
{
   record.p  = 0 ;
   record.cur_len =  0  ;
   code_base =  cb ;

   locks =  &locked_record ;
   n_locks = 1 ;
   num_locked =  file_lock = append_lock = 0 ;

   rec_num  =  -1L ;
   fields =  0 ;
   n_fields = 0 ;

   memo_fields =  0 ;
   n_memo_fields = 0 ;

   memset( &header, 0, sizeof(header) ) ;

   rec_num_old =  -1 ;
   has_mdx =  0 ;
   file_changed  =  0 ;

   if ( dbf_name != 0 )   open( dbf_name ) ;
}

__export Data::~Data()
{
   close() ;
}

Record::Record() : StrLen(0,0)
{
   is_changed =  0 ;
}

Data::close()
{
   int  save_error =  code_base->error_set(0) ;

   if ( file.open_test() )
	  code_base->data_list.remove( this ) ;

   if ( file.close() < 0 )  save_error =  code_base->error_set(0) ;

   if ( record.p != 0 )
   {  
//		hier bitte nicht dem gespeicherten Zeiger löschen !		#JB940923		
		  if (record.p == record_old.p)		// #JB940923		
				record_old.p = 0;						// #JB940923		
	  m4free( record.p ) ;
	  record.p =  0 ;
	  record.cur_len =  0 ;
   }
   if ( record_old.p != 0 )
   {
	  m4free( record_old.p ) ;
	  record_old.p =  0 ;
	  record_old.cur_len =  0 ;
   }
   if ( fields != 0 )
   {
	  for ( int i = 0; i < n_fields; i++ )
		 if ( fields[i] != 0 )
			delete( fields[i] ) ;
	  m4free( fields ) ;
	  fields =  0 ;
	  n_fields = 0 ;
   }
   if ( n_locks > 1 )
   {
	  m4free( locks ) ;
	  n_locks =  1 ;
	  locks =  &locked_record ;
   }

   n_memo_fields =  0 ;

   code_base->error_set(save_error) ;
   return save_error ;
}


Field * __export Data::field_create( Data *d, FieldDataImage *image, unsigned *u_ptr)
{
   switch ( image->type )
   {
	  case (int) 'N':
	  case (int) 'F': 
	  {
		 return  new( d->code_base ) NField( d, image, u_ptr ) ;
	  } 
	  case (int) 'D': 
	  {
		 return  new( d->code_base ) DField( d, image, u_ptr ) ;
	  } 
	  default: 
	  {
		 return  new( d->code_base ) Field( d, image, u_ptr ) ;
	  } 
   }
}

int __export Data::num_fields()
{
   if ( code_base->error() )  return -1 ;
   return n_fields ;
}

Data::open( char *dbf_name )
{
   close() ;
   num_locked = 0 ;   // set any locks to off
   if ( dbf_name != 0 )  file.name.assign( dbf_name ) ;
   file.name.extension( "DBF", 0 ) ;
   int rc =  file.open() ;  if ( rc != 0 )  return rc ;
   code_base->data_list.add( this ) ;

   file.name.piece( alias, 0, 0 ) ;

   FullHeader full_header ;
   if ( file.read( 0L, StrLen((char *)&full_header,sizeof(full_header))) < 0 )
   {
	  close() ;
	  return -1 ;
   }
   memcpy( &header, &full_header, sizeof(header) ) ;
   header.num_recs =  -1L ;
#if defined (MDX)
   has_mdx =  (short) (char) full_header.has_mdx ;
#else
   has_mdx =  full_header.has_mdx ;
#endif

   unsigned  field_data_len =  header.header_len-sizeof(full_header) ;
   if ( header.header_len <= sizeof(full_header) )
   {
	  close() ;
	  return code_base->error( e4data, file.name.ptr(), (char *) 0 ) ;
   }

   char *data =  (char *) m4alloc(field_data_len) ;
   if ( data == 0 )
   {
	  close() ;
	  return code_base->error( e4memory, (char *) 0 ) ;
   }

   if ( file.read( sizeof(full_header), StrLen(data,field_data_len)) < 0 )
   {
	  m4free(data) ;
	  close() ;
	  return -1 ;
   }

   /* count the number of fields */
   for (unsigned count=0; count < field_data_len; count+= 32)
	  if ( data[count] ==  0xD )  break ;
   n_fields =  (int) (count/32) ;
   if (field_data_len/32 < (unsigned) n_fields )	// #JB960623
   {
	  m4free(data) ;
	  close() ;
	  return code_base->error( e4data, file.name.ptr(), (char *) 0 ) ;
   }

   fields =  (Field **) m4alloc( sizeof(Field *) * (long)n_fields ) ;
   if ( fields == 0 )  code_base->error( e4memory, (char *) 0 ) ;

   record.cur_len = 1 ;

   for ( int i_fields =  0; i_fields < n_fields; i_fields++ )
   {
	  if ( code_base->error()  )  break ;
	  FieldDataImage *image = (FieldDataImage *) (data+ i_fields*32) ;
	  StrLen(&image->type,1).upper() ;
	  fields[i_fields] =  field_create( this, image, &record.cur_len ) ;
	  if ( fields[i_fields] == 0 )  code_base->error( e4memory, (char *) 0 ) ;
   }

   m4free( data ) ;

   if ( record.cur_len != full_header.record_len )
	  code_base->error( e4data, file.name.ptr(), (char *) 0 ) ;

   if ( code_base->error() )
   {
	  close() ;
	  return -1 ;
   }

   record_old.cur_len =  record.cur_len ;
   record.p =  (char *) m4alloc( record.cur_len+1 ) ;
   record_old.p =  (char *) m4alloc( record.cur_len+1 ) ;
   if ( record.p == 0  ||  record_old.p == 0 )
   {
	  close() ;
	  return code_base->error( e4memory, (char *) 0 ) ;
   }
   record.set( ' ' ) ;
   record_old.set( ' ' ) ;

   rec_num =  -1 ;
   rec_num_old =  -1 ;

   return( 0 ) ;
}

int Data::read( long rec, Str& str )
{
   unsigned len =  record.len() ;
   if ( file.read( recpos(rec), str, &len ) < 0 )  return -1 ;
   if ( len != record.len() )   return r4entry ;
   return 0 ;
}

int Data::read_old( long rec )
{
   if ( rec <= 0 )
   {
	  rec_num_old =  rec ;
	  record_old.set( ' ' ) ;
   }
   if ( rec_num_old == rec )  return 0 ;

   rec_num_old =  -1 ;
   int rc =  Data::read(rec, record_old) ;  
   if ( rc < 0 )  return -1 ;
   if ( rc > 0 )
	  // Must be  DataMemo::append() to  DataMemo::validate_memo_ids()
	  record_old.set( ' ' ) ;
   rec_num_old =  rec ;

   return 0 ;
}



// m4create.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

DataMemo::create( char *name, FieldInfo *field_info, TagInfo *tag_info )
{
   int rc =  DataIndex::create( name, field_info, tag_info ) ;
   if ( rc != 0 )  return rc ;

   if ( header.version & 0x80 )
   {
	  if ( init() < 0 )  return -1 ;
	  return memo_file.create( 0 ) ;
   }

   return 0 ;
}

#ifdef OTHER_NDX
   int DataMemo::create_ndx( TagInfo *tag_info )
   {
	  return DataIndex::create_ndx( tag_info ) ;
   }
#endif

Field *DataMemo::field_create( Data *data, FieldDataImage *image, unsigned *u_ptr )
{
   if ( image->type == 'M' )
   {
	  MField *p =  (MField *) new(data->code_base) MField( (DataMemo *) data, image, u_ptr ) ;
	  return p ;
   }
   else
	  return Data::field_create( data, image, u_ptr ) ;
}

int MemoFile::create( char *name, int is_temp )
{
   MemoHeader *header_ptr ;
   String header_str( code_base ) ;
   #ifdef DEBUG
	  if (sizeof(MemoHeader) > code_base->block_size )
		 e4severe( e4info, "MemoFile::create()", (char *) 0 ) ;
   #endif
   if ( header_str.set_len( code_base->block_size ) < 0 )  return -1 ;
   header_str.set(0) ;
   header_ptr =  (MemoHeader *) header_str.ptr() ;
   header_ptr->next_block =  1 ;
   header_ptr->x102 =  0x102 ;
   block_size =  header_ptr->block_size =  code_base->block_size ;

   if ( name != 0 )
   {
	  file.name.assign( name ) ;
	  file.name.extension( "DBT", 0 ) ;
   }
   file.name.piece( StrLen(header_ptr->file_name,sizeof(header_ptr->file_name)),0,0) ;

   if ( is_temp )
   {
	  if ( file.temp(0) < 0 )  return -1 ;
   }
   else
   {
	  if ( file.create() < 0 )  return -1 ;
   }

   return file.write( 0L, header_str ) ;
}

// d4create.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <limits.h>
}

class  CreateHeader : public DataHeader
{
public:
   unsigned short  record_len ;
   char filler[20] ;
} ;

__export Data::create( char *name, FieldInfo *field_data )
{
   if ( close() < 0 )  return -1 ;

   unsigned int n_flds = 0 ;
   int is_memo =  0 ;
   long calc_record_len = 0L ;
   for (; field_data[n_flds].name; n_flds++ )
   {
	  if ( field_data[n_flds].type == 'M' )  is_memo =  1 ;
	  calc_record_len +=  field_data[n_flds].len_field ;
   }

   if ( ++calc_record_len >= USHRT_MAX ) // Increment for deletion flag.
   {
	  code_base->error( e4record_len, name, (char *) 0 ) ;
	  return -1 ;
   }

   long lheader_len =  (long)n_flds * 32  + 34 ;
   if ( lheader_len >= USHRT_MAX )
   {
	  code_base->error( e4create, "Too Many Fields", name, (char *) 0 ) ;
	  return -1 ;
   }

   if ( name != 0 )  file.name.assign( name ) ;
   file.name.extension( "DBF", 0 ) ;
   int rc =  file.create() ;  if ( rc != 0 )  return rc ;

   FileSeqWrite seqwrite ;
   char buffer[0x800] ;
   seqwrite.init( file, 0L, StrLen(buffer,sizeof(buffer)) ) ;

   {  // Write the header
	  CreateHeader	create_header ;
	  memset( &create_header, 0, sizeof(create_header) ) ;
	  if ( is_memo )
		 create_header.version =  (unsigned char) 0x83 ;	// #JB950627 (unsigned char)	
	  else
		 create_header.version =  0x03 ;

	  u4yymmdd( &create_header.yy ) ;
	  create_header.header_len =  (unsigned short) (32*(n_flds+1) + 1) ;
	  create_header.record_len =  (unsigned short) calc_record_len ;

	  seqwrite.write( StrLen((char *)&create_header, sizeof(create_header)) ) ;
   }

   for (unsigned int i=0; i< n_flds; i++ )  // #JB950623: unsigned
   {
	  FieldDataImage  create_field_data ;

	  memset( &create_field_data, 0, sizeof(field_data) ) ;
	  u4ncpy( create_field_data.name, field_data[i].name, sizeof(create_field_data.name)) ;
	  StrLen temp_field_name( create_field_data.name, sizeof(create_field_data.name) ) ;
	  temp_field_name.trim() ;
	  strupr( (char *) create_field_data.name ) ;

	  create_field_data.type =  field_data[i].type ;
	  strupr( &create_field_data.type ) ;

	  if ( create_field_data.type == 'C' )
		 memcpy( &create_field_data.len, &field_data[i].len_field, sizeof(short)) ;
	  else
	  {
		 create_field_data.len =  (unsigned char) field_data[i].len_field ;
		 create_field_data.decimals =  (unsigned char) field_data[i].dec ; // #JB950626 (unsigned char)
	  }

	  #ifdef DEBUG
	  {
		 char t =  create_field_data.type ;
		 int  is_illegal =  0 ;
		 if ( t != 'D' && t != 'L' && t != 'N' && t != 'M' && t != 'F'  && t != 'C' )  is_illegal =  1 ;
		 if ( create_field_data.type == 'L' && create_field_data.len != 1  ||
			  create_field_data.type == 'D' && create_field_data.len != 8  ||
			  create_field_data.type == 'M' && create_field_data.len != 10 )
			is_illegal =  1 ;

   
		 if ( create_field_data.type == 'N' || create_field_data.type == 'F' )
		{
			int len =  field_data[i].len_field ;
			int dec =  field_data[i].dec ;
			if ( len > 19 || len < 1 || len <= 2 && dec != 0 || dec < 0) is_illegal =  1 ;
		   if ( dec >= len-1  && dec > 0 )  is_illegal = 1 ;
		}

		 if ( is_illegal )
			e4severe( e4data, "Illegal field data.", (char *) 0 ) ;
	  }
	  #endif

	  if ( seqwrite.write( StrLen((char *)&create_field_data, sizeof(create_field_data))) < 0 )  break ;
   }

   seqwrite.write( StrLen("\x0D\x1A", 2) ) ;
   seqwrite.flush() ;
   file.close() ;

   return( open(0) ) ;
}

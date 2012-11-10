// r4reindex.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
   #include <string.h>
   #include <limits.h>
}


int DataIndex::create( char *name, FieldInfo *field_info, TagInfo *tag_info )
{
   int rc =  Data::create( name, field_info ) ;  if ( rc != 0 )  return rc ;
   if ( tag_info == 0 )  return 0 ;

   production =  new( code_base )  Index( this, 0 ) ;
   if ( production == 0 )  return  -1 ;

   production->file.name.assign( name ) ;
   production->file.name.remove_extension() ;

   rc =  production->create( 0, tag_info ) ;
   if ( rc != 0 )
   {
	  if ( production->close() < 0 )  rc =  -1 ;
	  delete( production ) ;
	  production = 0 ;
   }
   return rc ;
}

int DataIndex::pack()
{
   int rc =  lock_file() ;   if ( rc != 0 )  return rc ;
   if ( (rc  =  lock_index()) != 0 )  return rc ;
   if ( (rc = flush_record()) != 0 )  return rc ;
   Data::pack() ;
   bof_flag =  eof_flag =  0 ;
   return reindex() ;
}

DataIndex::zap( long r1, long r2 )
{
   int rc =  lock_file() ;   if ( rc != 0 )  return rc ;
   rc  =  lock_index() ;	 if ( rc != 0 )  return rc ;
   Data::zap( r1, r2 ) ;
   if ( reccount() == 0 )
	  bof_flag =  eof_flag =  1 ;
   else
	  bof_flag =  eof_flag = 0 ;
   return reindex() ;
}

__export DataIndex::reindex()
{
   LinkIterator next( indexes ) ;

   for ( Index *index_on; index_on =  (Index *) next(); )
	  if ( index_on->reindex() < 0 )  return -1 ;

   return 0 ;
}

class BlockData
{
public:
   KeyData   *key(int i, int keylen) { return (KeyData *) (&data+i*keylen) ; }

   short  n_keys ;
   char   dummy[6] ;
   char   data;
} ;

class Reindex  // For 'Index::reindex'
{
public:
   Reindex( CodeBase *, Index * ) ;
  ~Reindex() ;

   blocks_alloc() ;
   Tag *find_i_tag( int ) ;
   int supply_keys() ;
   tag_headers_calc() ;
   tag_headers_write() ;
   write_keys() ;

   // Write key functions
   add( long, char * ) ;
   finish() ;
   todisk() ;

   Tag *tag ;

private:
   int  grouplen ;			 // Entire key length
   int  valuelen ;			 // Length of sorted portion of key
   int  keysmax ;
   unsigned  blocklen ;
   long lastblock ;			// The block last written to
   int  lastblock_inc ;		// How much to increment 'lastblock' by

   long  key_count ;

   Sort		  sort ;

   FileSeqWrite  seqwrite ;	
   FileSeqRead   seqread ;
   char		 *buffer ;	  // Buffer for 'seqwrite' and 'seqread'
   int		   buffer_len ;

   BlockData	*start_block ;
   int		   n_blocks ;
   int		   min_keysmax;  // To calculate the number of blocks

   Index		*index ;
   int		   n_tags ;
   DataIndex	*data ;
   CodeBase	 *code_base ;
} ;

int __export Index::create( char *file_name, TagInfo *tag_data )
{
   if ( close() < 0 )  return -1 ;

   code_base =  data->code_base ;

   if ( file_name != 0 )
	  file.name.assign( file_name ) ;
   file.name.extension( INDEX_EXTENSION, 0 ) ;			// #JB951108  "MDX" --> "MDC"
   file.name.upper() ;
   if ( file.create() < 0 )  return -1 ;
   if ( data != 0 )
   {
	  int rc =  data->lock_file() ;  if ( rc != 0 )  return rc ;
	  data->indexes.add( this ) ;
   }

   header.two =  2 ;
   u4yymmdd( header.yymmdd ) ;

   if( data->production == this ) header.is_production = 1 ;

   header.num_slots = 0x30 ;
   header.slot_size = 0x20 ;

   FileName temp_name( code_base ) ;
   temp_name.assign( data->file.name.ptr() ) ;
   temp_name.upper() ;
   temp_name.piece( StrLen(header.data_name,sizeof(header.data_name)), 0,0 ) ;

   header.block_chunks =  code_base->block_size/512 ;

   if ( header.block_chunks < 2 )   // disallowed for compatibility reasons
	  header.block_chunks = 2 ;  // minimum of 2 for dBASE compatibility

   header.block_rw	 =  header.block_chunks*i4multiply ;

   block_alloc = m4memory_type( code_base->blocks_start,
						  sizeof(Block) + header.block_rw -
						  sizeof(KeyData) - sizeof(short) - sizeof(char[6]),
						  code_base->blocks_expand, 0 ) ;
   if ( block_alloc == 0 )
   {
	  close() ;
	  return  code_base->error( e4memory, (char *) 0 ) ;
   }

   for ( int i = 0; tag_data[i].name; i++ )
   {
	  header.num_tags++ ;

	  Tag *tag_ptr =  new( tags.add() )  Tag( this ) ;
	  if ( tag_ptr == 0 )
	  {
		 close() ;
		 return code_base->error( e4memory, (char *) 0 ) ;
	  }

	  tag_ptr->alias.assign( tag_data[i].name ) ;
	  tag_ptr->alias.upper() ;

	  tag_ptr->header.type_code  =  0x10 ;
	  if ( tag_data[i].unique )
	  {
		 tag_ptr->header.type_code +=  0x40 ;
		 tag_ptr->header.unique	 =  0x4000 ;
		 tag_ptr->unique_error =  tag_data[i].unique ;
		 #ifdef DEBUG
			if ( tag_data[i].unique != e4unique &&
				 tag_data[i].unique != r4unique &&
				 tag_data[i].unique != r4unique_continue )
			   e4severe( e4parm, "Index::create()", "Unique flag data is an unrecognized value in TagInfo class.", (char *) 0 ) ;
		 #endif
	  }
	  if ( tag_data[i].descending)
	  {
		 tag_ptr->header.type_code += 0x08 ;
		 #ifdef DEBUG
			if ( tag_data[i].descending != r4descending )
			   e4severe( e4parm, "Index::create()", "Flag should be 'r4descending' in TagInfo class.", (char *) 0 ) ;
		 #endif
	  }

	  #ifdef DEBUG
		 if ( tag_data[i].expression == 0 )
			 e4severe( e4info, "Void Expression not Allowed in Tag List", (char *) 0 ) ;
		 if ( *(tag_data[i].expression) == '\0' )
			 e4severe( e4info, "Void Expression not Allowed in Tag List", (char *) 0 ) ;
	  #endif

	  tag_ptr->expr.source.assign( StrLen( tag_data[i].expression,
								strlen(tag_data[i].expression))  ) ;

	  if ( tag_data[i].filter != 0 )
		 if ( *(tag_data[i].filter) != '\0' )
			 tag_ptr->filter.source.assign( StrLen( tag_data[i].filter,
											strlen(tag_data[i].filter))  ) ;

	  tag_ptr->lock_pos =  l4lock_pos + i ;
	  if ( code_base->error() )  return -1 ;
   }

   #ifdef DEBUG
	  if ( header.num_tags > 47 )
		 e4severe( e4parm, "Index::create", (char *) 0 ) ;
   #endif

   int rc =  reindex() ;  if ( rc != 0 )  return rc ;
   if ( data != 0 )
   {
	  Str10 data_name, index_name ;
	  file.name.piece( index_name, 0, 0 ) ;
	  data->file.name.piece( data_name, 0, 0 ) ;
	  if ( data_name == index_name )
	  {
		 data->has_mdx =  1 ;
		  header.is_production = 1 ;
		 if (data->file.write(sizeof(DataHeader)+sizeof(short)+sizeof(char[16]),
				StrLen(&data->has_mdx,sizeof(data->has_mdx))) < 0 )  return -1 ;
	  }
   }
   return 0 ;
}

int __export Index::reindex()
{
   if ( ! file_locked )
   {
	  if ( unlock() < 0 )  return -1 ;
	  int rc = file.lock( l4lock_pos, l4lock_pos ) ;  if ( rc != 0 )  return rc ;
	  file_locked =  1 ;
   }

   Reindex reindex( code_base, this ) ;
   if ( code_base->error() )  return -1 ;

   reindex.tag_headers_calc() ;
   if ( reindex.blocks_alloc() < 0 )  return -1 ;

   LinkIterator  next_tag(tags) ;
   for(; reindex.tag = (Tag *) next_tag(); )
   {
	  reindex.supply_keys() ;
	  int rc ;
	  if ( (rc = reindex.write_keys()) != 0 )
		 return rc ;  // May return r4unqiue
   }

   return  reindex.tag_headers_write() ;
}

Reindex::Reindex( CodeBase *cb, Index *index_parm ) : sort(cb)
{
   code_base =  cb ;
   index =  index_parm ;
   data  =  index->data ;

   min_keysmax = INT_MAX ;
   start_block =  0 ;
   blocklen =  index->block_rw_len() ;

   buffer_len =  index->code_base->sort_buffer_size ;
   if ( buffer_len < 1024 )  buffer_len =  1024 ;

   buffer =  (char *) m4alloc( buffer_len ) ;
   if ( buffer == 0 )  code_base->error( e4memory, (char *) 0 ) ;
}

Reindex::~Reindex()
{
   if ( buffer != 0 )
	  m4free( buffer ) ;
   if ( start_block != 0 )
	  m4free( start_block ) ;
}

Reindex::blocks_alloc()
{
   if ( code_base->error() )  return -1 ;
   tag =  (Tag *) index->tags.last() ;

   #ifdef DEBUG
	  if ( min_keysmax >= INT_MAX )
		 e4severe( e4info, "Reindex::blocks_alloc()", (char *) 0 ) ;
   #endif

   // Calculate the block stack height
   long  on_count =  data->reccount() ;
   for ( n_blocks = 2; on_count != 0L; n_blocks++ )
	  on_count /=  min_keysmax ;

   start_block =  (BlockData *) m4alloc( long(blocklen) * n_blocks ) ;
   if ( start_block == 0 )
	  return code_base->error( e4memory, "Block Size too Large for Indexing", (char *) 0 ) ;

   return 0 ;
}

int Reindex::supply_keys()
{
   #ifdef DEBUG
	  key_count =  0L ;
   #endif

   seqread.init( data->file, data->recpos(1L), StrLen( buffer,buffer_len) ) ;
   if ( sort.init( tag->valuelen(), 0 ) < 0 )  return -1 ;
   sort.assign_cmp ( tag->cmp ) ;			  

   Expr& expr	=  tag->expr ;
   Expr& filter  =  tag->filter ;
   int do_filter =  filter.source.len() > 0 ;
   String  result( code_base ) ;
   int	 rc = 0 ;
   long	count =  data->reccount() ;

   for ( long i_rec = 1L; i_rec <= count; i_rec++ )
   {
	  if ( seqread.read( data->record ) < 0 ) return -1 ;
	  data->rec_num =  i_rec ;
   
	  for ( int i = 0; i < data->n_memo_fields; i++ )
		 data->memo_fields[i]->reset() ;

	  if ( do_filter )
	  {
		 int filter_type =  filter.vary(result) ;  if ( filter_type < 0 )  return -1 ;
		 #ifdef DEBUG
			if ( filter_type != t4log )  e4severe( e4result, "Reindex::supply_keys", (char *) 0 ) ;
		 #endif
		 int *is_true =  (int *) result.ptr() ;
		 if ( ! *is_true )  continue ;
	  }

	  if ( expr.key( result ) < 0 )  return -1 ;

	  if ( (rc = sort.put( i_rec, result.ptr(), "" )) < 0) return rc ;
	  #ifdef DEBUG
		 key_count++ ;
	  #endif
   }
   return 0 ;
}

int  Reindex::tag_headers_calc()
{
   int  rc ;
   String result( code_base ) ;

   LinkIterator  next( index->tags ) ;
   for( n_tags = 0; tag = (Tag *) next(); n_tags++ )
   {
	  if ( (rc = tag->free()) < 0 )  return rc ;

	  tag->header.type	  =  tag->expr.key( result ) ;
	  if ( tag->header.type < 0 )  return -1 ;

	  tag->init_seek_conv( tag->header.type ) ;
	  tag->header.value_len =  result.len() ;
	  tag->header.group_len =  tag->header.value_len+ 2*sizeof(long)-1 ;
	  tag->header.group_len-=  tag->header.group_len % sizeof(long) ;

	  tag->header.keys_max =
			   (index->block_rw_len() - sizeof(short)-6-sizeof(long)) / tag->header.group_len ;
	  if ( tag->header.keys_max < min_keysmax )
		 min_keysmax =  tag->header.keys_max ;
   }
   lastblock_inc =  index->block_rw_len()/ 512 ;
   lastblock =  4 + (n_tags-1)*lastblock_inc ;
   return 0 ;
}

Tag *Reindex::find_i_tag( int i_tag )
{
   // First 'i_tag' starts at '1' for this specific routine
   LinkIterator  next_tag( index->tags ) ;
   Tag *tag_on =  0 ;
   while ( --i_tag >= 0 )
   {
	  tag_on =  (Tag *) next_tag() ;
	  if ( tag_on == 0 )  return 0 ;
   }
   return tag_on ;
}

int Reindex::tag_headers_write()
{
   // First, calculate the TAG_INFO::left_chld, TAG_INFO::right_chld values, TAG_INFO::parent values
   int  higher[49], lower[49], parent[49] ;
   memset( higher, 0, sizeof(higher) ) ;
   memset( lower,  0, sizeof(lower) ) ;
   memset( parent, 0, sizeof(parent) ) ;

   LinkIterator  next_tag( index->tags ) ;
   if ( next_tag() != 0 )
   {
	  int n_tag = 1 ;

	  for ( Tag *tag_on; tag_on =  (Tag *) next_tag(); )
	  {
		 n_tag++ ;
		 int i_tag = 1 ;
   
		 for (;;)
		 {
			Tag *tag_ptr =  find_i_tag( i_tag ) ;
			#ifdef DEBUG
			   if ( n_tag >= 48 || tag_ptr == 0 )
				  e4severe( e4result, "Reindex::tag_headers_write()", (char *) 0 );
			#endif
			if ( tag_on->alias < tag_ptr->alias )
			{
			   if ( lower[i_tag] == 0 )
			   {
				  lower[i_tag] =  n_tag ;
				  parent[n_tag] = i_tag ;
				  break ;
			   }
			   else
				  i_tag =  lower[i_tag] ;
			}
			else
			{
			   if ( higher[i_tag] == 0 )
			   {
				  higher[i_tag] =  n_tag ;
				  parent[n_tag] =  i_tag ;
				  break ;
			   }
			   else
				  i_tag =  higher[i_tag] ;
			}
		 }
	  }
   }

   // Now write the headers
   seqwrite.init( index->file, 0L, StrLen( buffer, buffer_len) ) ;

   index->header.eof =  lastblock+lastblock_inc ;
   index->header.free_list = 0L ;
   seqwrite.write( StrLen(&index->header, sizeof(INDEX_HEADER)) ) ;

   seqwrite.repeat( 512-sizeof(INDEX_HEADER)+17, 0 ) ;
   // There is a 0x01 on byte 17 of the first 32 bytes.
   seqwrite.write( StrChar(1) ) ;  
   seqwrite.repeat(14,0) ;

   TAG_INFO tag_info ;
   StrLen tag_info_str( &tag_info, sizeof(TAG_INFO) ) ;
   LinkIterator  next_info( index->tags ) ;

   for ( int i_tag = 0; i_tag < 47; i_tag++ )
   {
	  tag_info_str.set(0) ;

	  if ( i_tag < n_tags )
	  {
		 tag =  (Tag *) next_info() ;
		 tag_info.header_pos =  4 + long(i_tag)*lastblock_inc ;
		 tag->header_offset =  tag_info.header_pos * 512 ;
		 StrLen temp( tag_info.tag, sizeof(tag_info.tag) ) ;
		 temp = tag->alias ;
		 temp.trim() ;
		 tag_info.index_type =  tag->header.type ;
		 tag_info.x1000  =  0x1000 ;
		 tag_info.x2	 =  2 ;
		 tag_info.left_chld =  lower[i_tag+1] ;
		 tag_info.right_chld  =  higher[i_tag+1] ;
		 tag_info.parent = parent[i_tag+1] ;

		 if ( data->production == index )
		 {
			int j_field=  data->jfield( tag->expr.source.ptr() ) ;
			if ( j_field > 0 )
			   data->file.write( (j_field+1)*sizeof(FieldDataImage)-1, StrChar(1) ) ;
		 }
	  }

	  if ( seqwrite.write(tag_info_str) < 0 )  return -1 ;
   }

   LinkIterator  next_header( index->tags ) ;
   for (; tag =  (Tag *) next_header() ;)
   {
	  if ( seqwrite.write( StrLen(&tag->header,sizeof(tag->header)) ) < 0 )  return -1 ;

	  seqwrite.write( tag->expr.source ) ;
	  seqwrite.repeat( 220-tag->expr.source.len(), 0 ) ;

	  seqwrite.repeat( 1, 0 ) ;
	  if( tag->filter.source.len() > 0 ) 
		 seqwrite.repeat( 2, 1 ) ;
	  else
		  seqwrite.repeat( 2, 0 ) ;

	  // write extra space up to filter write point
	  seqwrite.repeat( GARBAGE_LEN-3 , 0 ) ;

	  seqwrite.write( tag->filter.source ) ;
	  seqwrite.repeat( blocklen - GARBAGE_LEN - tag->filter.source.len() - 220 - sizeof(tag->header), 0 ) ;
   }
   index->file.set_len( index->header.eof * 512) ;

   if ( seqwrite.flush() < 0 ) return -1 ;
   return 0 ;
}

int Reindex::write_keys()
{
   grouplen  =  tag->grouplen() ;
   valuelen  =  tag->valuelen() ;
   keysmax =  tag->keysmax() ;
   memset( start_block, 0, n_blocks*blocklen ) ;

   if ( sort.get_init() < 0 )  return -1 ;
   seqwrite.init( index->file, (lastblock+lastblock_inc)*512, StrLen(buffer,buffer_len)) ;

   char last_key[i4max_key_size] ;
   #ifdef DEBUG
	  if ( i4max_key_size < sort.sort_len )  e4severe( e4info, "Reindex::write_keys", (char *) 0 ) ;
   #endif
   memset( last_key, 0, sizeof(last_key) ) ;
   int   is_unique =  tag->unique() ;

   for(;;)  // For each key to write
   {
	  char *key_data ;
	  void *dummy_ptr ;
	  long  key_rec ;
	  int   rc ;

	  if ( (rc = sort.get(&key_rec, (void **) &key_data, &dummy_ptr)) < 0)  return -1 ;

	  #ifdef DEBUG
		 if ( key_count < 0L  ||  key_count == 0L && rc != 1  
							 ||  key_count > 0L && rc == 1 )
			e4severe( e4info, "Reindex::write_keys", (char *) 0 ) ;
		 key_count-- ;
	  #endif

	  if ( rc == 1 )  // No more keys
	  {
		 if ( finish() < 0) return -1 ;
		 if ( seqwrite.flush() < 0 )  return -1 ;
		 break ;
	  }

	  if ( is_unique )
	  {
		 if ( (*tag->cmp)( key_data, last_key, sort.sort_len) == 0 )
		 {
			switch( tag->unique_error )
			{
			   case e4unique:
				  return code_base->error( e4unique, "Creating Tag", tag->alias.ptr(), (char *) 0 ) ;

			   case r4unique:
				  return r4unique ;

			   default:
				  continue ;
			}
		 }
		 memcpy( last_key, key_data, sort.sort_len ) ;
	  }

	  // Add the key
	  if ( add(key_rec, key_data) < 0 )  return -1 ;
   }

   // Now complete the tag header info.
   tag->header.root =  lastblock ;
   return 0 ;
}

Reindex::add( long rec, char *key_value )
{
   if ( start_block->n_keys >= keysmax )
   {
	  if ( todisk() < 0 )  return -1 ;
	  memset( start_block, 0, blocklen ) ;
   }

   KeyData *key_to =  start_block->key(start_block->n_keys++,grouplen) ;
   #ifdef DEBUG
	  long dif =  (char *) key_to -  (char *) start_block ;
	  if ( (unsigned) dif+grouplen > blocklen || dif < 0 )		// #JB950623
		 e4severe( e4result, "Reindex::add()", (char *) 0 ) ;
   #endif
   key_to->rec_num =  rec ;
   memcpy( key_to->value, key_value, valuelen ) ;

   return 0 ;
}

Reindex::finish()
{
   if ( seqwrite.write(StrLen(start_block,blocklen)) < 0 ) return -1 ;
   lastblock +=  lastblock_inc ;
   BlockData *block =  start_block ;

   for(int i_block=1; i_block < n_blocks; i_block++ )
   {
	  block =  (BlockData *) ((char *)block + blocklen) ;
	  if ( block->n_keys >= 1 )
	  {
		 KeyData *key_to =  block->key( block->n_keys,grouplen ) ;
		 #ifdef DEBUG
			long dif =  (char *) key_to  -  (char *) block ;
			if ((unsigned) dif+sizeof(long) > blocklen  ||  dif<0 )		// #JB950623
			   e4severe( e4result, "Reindex::finish()", (char *) 0 ) ;
		 #endif
		 key_to->rec_num =  lastblock ;
   
		 if ( seqwrite.write(StrLen(block,blocklen)) < 0 ) return -1 ;
		 lastblock +=  lastblock_inc ;
	  }
   }
   return 0 ;
}

Reindex::todisk()
{
   // Writes out the current block and adds references to higher blocks
   BlockData *block   =  start_block ;
   int		i_block =  0 ;
   KeyData   *key_on  =  block->key( block->n_keys-1, grouplen ) ;
   #ifdef DEBUG
	  long dif =  (char *) key_on -  (char *) block ;
	  if ((unsigned) dif+grouplen > blocklen || dif < 0 )		// #JB950623
		 e4severe( e4result, "Reindex::to_disk()", (char *) 0 ) ;
   #endif

   for(;;)
   {
	  StrLen block_str(block,blocklen) ;
	  if ( seqwrite.write(block_str) < 0 ) return -1 ;
	  if ( i_block != 0 )  block_str.set(0) ;
	  lastblock +=  lastblock_inc ;
   
	  block =  (BlockData *) ((char *)block + blocklen) ;
	  i_block++ ;
	  #ifdef DEBUG
		 if ( i_block >= n_blocks )  e4severe( e4info, "Reindex::todisk()", (char *) 0 ) ;
	  #endif

	  KeyData *keyto =  block->key( block->n_keys, grouplen) ;
	  #ifdef DEBUG
		 long dif =  (char *) keyto -  (char *) block  ;
		 if ((unsigned) dif+sizeof(long) > blocklen || dif < 0 )	// #JB950623
			e4severe( e4result, "Reindex::to_disk()", (char *) 0 ) ;
	  #endif
	  keyto->rec_num =  lastblock ;

	  if ( block->n_keys < keysmax )
	  {
		 block->n_keys++ ;
		 #ifdef DEBUG
			if ((unsigned) dif+grouplen > blocklen )			// #JB950623
			   e4severe( e4result, "Reindex::to_disk()", (char *) 0 ) ;
		 #endif
		 memcpy( keyto->value, key_on->value, valuelen ) ;
		 return 0 ;
	  }
   }
}

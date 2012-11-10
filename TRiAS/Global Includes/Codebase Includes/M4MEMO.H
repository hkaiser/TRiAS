// m4memo.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef M4MEMO

#define M4MEMO

#ifndef D4DATA
#include "d4data.h"
#endif

class E4EXPORT MemoHeader
{
public:
   long  next_block ;  // Memo Entry 1,2, ...
   long  zero ;
   char  file_name[8] ;
   short zero2 ;
   short x102 ;
   short block_size ;  // Bytes
   short zero3 ;
} ;

class E4EXPORT MemoFile 
{
public:
   MemoFile( CodeBase *, Data * ) ;

   int   check() ;
   int   close()    { return file.close() ; }
   int   create( char *name, int is_temp = 0 ) ;
   int   dump( long memo_id, Str& ) ;
   int   open( char *name ) ;
   int   read( long memo_id, Str& ) ;
   int   write( long *memo_id, Str& ) ;  // Pass the old memo id,
                                         // Returns the new memo id
   File       file ;
   short      block_size ;               // Bytes
   Data      *data ;
   CodeBase  *code_base ;
} ;

class E4EXPORT DataMemo : public DataIndex
{
public:
   DataMemo( CodeBase *, char *name = 0 ) ;
   ~DataMemo() ;

   int   append() ;
   int   append_blank() ;
   int   append_start( int use_memo_entries = 0 ) ;
   int   close() ;
   int   compress() ;
   int   create_ndx( TagInfo *t ) ;
   int   create( char *name, FieldInfo *, TagInfo *t = 0 ) ;
   Field  *field_create( Data *, FieldDataImage *, unsigned * ) ;
   MField *mfield( char *name ) ;
   int   open( char *name = 0 ) ;
   int   init() ;
   int   pack() ;
   int   validate_memo_ids() ;   // Makes sure the database memo ids are valid
   int   write( long rec ) ;
   int   zap( long, long ) ;

   MemoFile  memo_file ;
} ;

class E4EXPORT MField : public Field, public Link
{
friend  DataMemo::append() ;

public:
   MField( DataMemo *d, FieldDataImage *, unsigned * ) ;
   void *operator new( size_t ) ;
   void *operator new( size_t, CodeBase * ) ;
   void operator delete( void * ) ;
   void do_delete( void * ) ;

   MField& operator=( Str& ) ;
   MField& operator=( MField& ) ;
   MField& operator=( char * ) ;

   void   changed() ;
   int    flush() ;
   void   free() ;
   long   id() ;            // Returns the memo id of the memo field
   void   id( long ) ;      // Sets the memo id inside the memo field
   unsigned len() ;
   char  *ptr() ;
//   char *str() ;
   int    read( Str *str= 0 ) ;
   void   reset() ;          // Resets to 'Unknown state'
   int    set_len( unsigned new_len ) ;
   int    write() ;

   int    is_changed ;

   int    status ;           // 0 - Current contents, 1 - Unknown
   String contents ;
} ;

class E4EXPORT ChainEntry : public Str
{
public:
   ChainEntry( MemoFile *m ) ;

   unsigned  len()    { return sizeof(next)+sizeof(num) ; }
   char     *ptr()    { return (char *) &next ; }

   int   flush() ;
   int   skip() ;
   
   long  next ;       /* The next free block area */
   long  num ;        /* The number of free blocks in the free block area */
   int   to_disk ;    /* TRUE if this information needs to be written to disk */
   long  block_no ;   /* The current block number */
   MemoFile *memo ;
} ;

class E4EXPORT MemoBlock : public Str
{
public:
   void init( unsigned n_chars ) ;

   unsigned len() { return sizeof(short)+sizeof(short)+sizeof(long) ; }
   char    *ptr() { return (char *) &minus_one ; }

   short minus_one ;    // '-1' for dBASE IV
   short start_pos ;
   long  num_chars ;    // Including the 'MemoBlock'
} ;



#endif

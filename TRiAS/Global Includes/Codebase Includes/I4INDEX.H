// i4index.h  (c)Copyright Sequiter Software Inc., 1990.  All rights reserved.
// MDX-, NDX- und CLIPPER-Format, Stand vom 2.10.1992

#ifndef I4INDEX
#define I4INDEX

#if defined (NDX) || defined (CLIPPER)

#ifndef D4DATA
#include "d4data.h"
#endif

//  IndexInfo is an NDX alias for TagInfo
#define IndexInfo TagInfo
#define OTHER_INDEX

#ifndef E4EXPR
#include "e4expr.h"
#endif

#ifndef L4LINK
#include "l4link.h"
#endif

#ifndef F4FILESE
#include "f4filese.h"
#endif

#ifndef M4MEMORY
#include "m4memory.h"
#endif


class E4EXPORT  Tag ;
class E4EXPORT  Index ;
class E4EXPORT  Reindex ;
class E4EXPORT  MemoryType ;

typedef unsigned size_t ;
#ifdef CLIPPER
   const int i4multiply =  1024 ;
   const int i4max_key_size =  338 ;
#elif defined NDX
   const int i4multiply =  512 ;
   const int i4max_key_size =  100 ;
#endif
const int i4max_expr_size = 256 ;
const long l4lock_pos =  1000000000L ;
const double e4accuracy =  1.0e-13 ;

typedef void STOK( Str& result, Str& str ) ;
typedef void DTOK( Str& result, double ) ;
#ifdef __ZTC__
   #define TAG_CMP_FUNC int
   typedef int T4CMP_ROUTINE(const void *, const void *, size_t ) ;
#else
   #ifdef D4DLLS
   extern "C" {
      typedef int FAR PASCAL T4CMP_ROUTINE(const void *, const void *, size_t ); //#JB931601 PASCAL gestr.; #JB940923: PASCAL aktiviert
      #define TAG_CMP_FUNC int  FAR PASCAL FN_EXP //#JB931601; #JB940923 --> PASCAL FN_EXP aktiviert
   }    
   #else
   extern "C" { 
      #define TAG_CMP_FUNC int cdecl
      typedef int cdecl T4CMP_ROUTINE(const void *, const void *, size_t ) ;
   }    
   #endif
#endif

class E4EXPORT KeyData
{
public:
   long fileblock()  { return pointer ; }
   long recno()      { return rec_num ; }
   char *ptr()       { return value ; }

   long  pointer ;    // =0L if record, not pointer
   long  rec_num ;
   char  value[1] ;  // The key size is variable 
} ;

class IndexGroupLink : public Link
{
friend IndexGroupFile ;
public:
   IndexGroupLink( CodeBase *cb ) : name( cb ) {}
   void *operator new( size_t, void *mem ) ;
   void *operator new( size_t ) ;
   void  operator delete( void *) ;
private:
   int     len ;
   String  name ;
} ;

class IndexGroupFile : public LinkList
{
public:
   IndexGroupFile( DataIndex * ) ;
   ~IndexGroupFile() ;
   void *operator new( size_t ) ;
   void *operator new( size_t, CodeBase * ) ;
   void  operator delete( void *) ;

   int create( char *, TagInfo *, int index_create = 1 ) ;
   int open( char *name=0 ) ;
private:
   CodeBase    *code_base ;
   DataIndex   *data ;
   File        file ;
   MemoryType  *item_memory ;
   int         num_files ;
} ;

class E4EXPORT Block : public Link              
{
friend class Tag ;
friend class Index ;
public:
   void *operator new( size_t ) ;
   void *operator new( size_t, Tag&, long) ;
   void  operator delete( void *) ;

   void  Block::append( long ) ;
   void  Block::append( void *, long, long ) ;
   long  blockdown()   { return key()->pointer ; }
   long  fileblock()   { return file_block ; }
   int   eof()         { return key_on >= n_keys ; }
   int   flush() ;
   int   get_last_key( char *key_info ) ;
   void  go( int i)    { key_on = i ; }
   void  go_eof()      { key_on = n_keys ; }
   void  Block::insert( void *, long, long ) ;
   KeyData  *key( int ) ;  // The specified key no.
   KeyData  *key()     { return key( key_on ) ; }
   char     *key_data(int) ;
   int   keypos()      { return key_on ; }
   int   lastpos() ;   // The last position available, adjusts for branches
   unsigned len() ;
   int Block::memfind( long, Block * ) ;
   int   numkeys()     { return n_keys ; }
   void  numkeys(int i){ n_keys =  (short) i ; }
   int   leaf() ;      // Is the block a leaf block
   long  recno() ;     // The current record number
   void  remove() ;    // Removes current key
   int   room() ;      // True if there is room for another key
   int   seek( Str& ) ;
   int   skip( long ) ;
   void  zero() ;      // Initialize all values to zero

   int   changed ;     // True if the block data has been changed

private:
   Index  *index ;
   long  file_block ;  // Identifies block within index file
   int   key_on ;      // The current key within the block


   // Block Image starts here
   short      n_keys ;
   #ifdef NDX
      char       dummy[2] ;
      KeyData    data ;
   #elif defined CLIPPER
      short pointers[511] ;
      KeyData    *data ;  // position depends on #keys in block!
   #endif
} ;

typedef struct
{
#ifdef NDX
   long     root ;
   long     eof ;
   char     n1_dummy ;
   char     db_type ;
   char     n2_dummy[2] ;
   short    key_len  ;
   short    keys_max ;           // Maximum # of keys per block;  <= 100 
   short    int_or_date ;        // TRUE (1) if Numeric or Date Key 
   short    group_len ;          // key_len plus 8 increased to a multiple of 2 
   short    dummy ;
   short    unique ;             // TRUE if Unique 
//   char     expression[256] ;
//   long     version ;
#elif defined CLIPPER
   short          sign ;
   short          version ;
   long           root ;          /* Root Block */
   long           eof ;           /* First Free Block Pointer */
   short          group_len ;     /* Key Length + 2*sizeof(long) */
   short          key_len ;       /* Key Length */
   short          key_dec ;       /* Number of Decimals in Key */
   short          keys_max ;      /* Maximum # of keys per block;  <= 100 */
   short          keys_half ;     /* Maximum # of keys per half block */
//   char           expression[256];/* The index expression corresponding to the database. */
//   short          unique   ;      /* TRUE if Unique */
#else
   #error - must define either NDX or CLIPPER switch for this compile
#endif
} IND_HEAD_WRITE;

class E4EXPORT INDEX_HEADER
{
public:
   long     old_version ;
   int      header_offset ;
   char     type ;
   unsigned block_rw ;

#ifdef NDX
   long     root ;
   long     eof ;
   char     n1_dummy ;
   char     db_type ;
   char     n2_dummy[2] ;
   short    key_len  ;
   short    keys_max ;           // Maximum # of keys per block;  <= 100 
   short    int_or_date ;        // TRUE (1) if Numeric or Date Key 
   short    group_len ;          // key_len plus 8 increased to a multiple of 2 
   short    dummy ;
   short    unique ;             // TRUE if Unique 
//   char     expression[256] ;
   long     version ;
#elif defined CLIPPER
//   short          old_version ;  // already defined above
   long           virtual_eof ;   /* The next available file block */

   short          sign ;
   short          version ;
   long           root ;          /* Root Block */
   long           eof ;           /* First Free Block Pointer */
   short          group_len ;     /* Key Length + 2*sizeof(long) */
   short          key_len ;       /* Key Length */
   short          key_dec ;       /* Number of Decimals in Key */
   short          keys_max ;      /* Maximum # of keys per block;  <= 100 */
   short          keys_half ;     /* Maximum # of keys per half block */
//   char           expression[256];/* The index expression corresponding to the database. */
   short          unique   ;      /* TRUE if Unique */
#endif
} ;

class E4EXPORT Tag : public Link
{
public:
friend class Index ;
friend class Reindex ;
   Tag( Data *d ) ;                         
  ~Tag() ;

   Block *block() ;
   int   bottom() ;
   int   check() ;
   #ifdef CLIPPER
      int   decimals() { return header.key_dec ; }
   #endif
   int   down() ;
   int   dump( int handle, int display_all = 1 ) ;
   int   dump_do(int,int,int) ;
   int   eof() ;
   int   flush() ;
   int   free() ;
   int   free_saved() ;
   int   grouplen()                   { return header.group_len ; }
   void  init_seek_conv(int) ;         // Initialize 'stok' and 'dtok'
   KeyData  *key() ;                  // The current key
   int   lock() ;
   int   position( double ) ;         // Positions a percentage down the file.
   double position(void) ;            // Returns the position as a percentage.
   long  recno() ;
   int   seek( Str& ) ;             // r4success, r4found, r4after, r4eof
   long  skip( long ) ;
   Block *split( Block * ) ;
   int   top() ;
   int   type() ;
   int   up() ;
   int   up_to_root() ;
   int   unique()             { return (int) header.unique ; }
   int   valuelen()                   { return header.key_len ; }

   Expr  expr ;
   int   unique_error ;            // Is rewriting a unique key an error ?
   T4CMP_ROUTINE  *cmp ;           // Compares two key values
   STOK  *stok ;                   // Conversion for 'seek'
   DTOK  *dtok ;                   // Conversion for 'seek'
   CodeBase *code_base ;
   Str10       alias ;

   LinkList    blocks ;
   LinkList    saved ;
   Index     *index ;              // in NDX, must be pointer to only index
   DataIndex *data ;

private:
   int         root_write ;        // True if 'header.root' needs to be written
   INDEX_HEADER header;

   long        lock_pos ;          // The file offset to physically lock
   void       *compile ;           // A pseudo compiled version of the expression 
public:
   File  file ;
} ;

class E4EXPORT TagInfo
{
public:
   char *name ;
   char *expression ;
   char *filter ;    // should be blank (0) for  NDX
   int   unique ;
   int   descending ; // should be blank (0) for NDX
} ;

class E4EXPORT Index : public Tag
{
   friend class Tag ;
   friend class Block ;
   friend class Reindex ;

public:
   Index( DataIndex *, char *name=0 ) ;
  ~Index() ;

   void *operator new( size_t ) ;  // Do not use
   void *operator new( size_t, CodeBase * ) ;  
   void  operator delete( void * ) ;

   int   add_calc( Str&, long rec ) ; // Calculates expression and adds
   int   add( Str&, long rec ) ;    // Returns r4unique, r4success, r4repeat
   unsigned  block_rw_len()           { return (unsigned) header.block_rw ; }
   int   check_blocks() ;      
   int   close() ;
   int   create( TagInfo * ) ;
   int   create( char *, TagInfo * ) ;
   long  extend() ;                // Allocates a block at the end of the file
   int   get_replace_entry( KeyData *insert_spot, Block *block_on ) ;
   int   go( Str&, long ) ;
   int   iget_last_key( char *key_data, long for_block ) ;
   int   keysmax()                    { return header.keys_max ; }
   int   lock_file() ;
   int   open() ;
   int   open( char *file ) ;
   int   reindex() ;
   int   remove() ;                   // Remove the current key
   int   remove( Str&, long rec ) ;   // Remove the specified key
   int   remove_calc( Str&, long rec ) ; // Calculates expression and removes
   void  remove_ref() ;
   int   shrink( long ) ;
   int   unlock() ;
   int   update_header() ;
   int   version_check() ;
   int   need_delete ;    // True if allocated by dataindex::create

private:
   MemoryType  *block_alloc ;

   int   file_locked ;    // True if locked
   long  version_old ;

} ;

#elif defined MDX           // MDX-Version

#ifndef D4DATA
#include "d4data.h"
#endif

#ifndef E4EXPR
#include "e4expr.h"
#endif

#ifndef L4LINK
#include "l4link.h"
#endif

// garbage between expression and filter is length:
#define GARBAGE_LEN 518

class E4EXPORT  Tag ;
class E4EXPORT  Index ;
class E4EXPORT  Reindex ;
class E4EXPORT  MemoryType ;

typedef unsigned size_t ;
const int i4multiply =  512 ;
const int i4max_key_size =  102 ;
const long l4lock_pos =  1000000000L ;
const double e4accuracy =  1.0e-13 ;

typedef void STOK( Str& result, Str& str ) ;
typedef void DTOK( Str& result, double ) ;

#ifdef __ZTC__
   #define TAG_CMP_FUNC int
   typedef int T4CMP_ROUTINE(const void *, const void *, size_t ) ;
#else
   #ifdef D4DLLS
      extern "C" {
      typedef int FAR PASCAL T4CMP_ROUTINE(const void *, const void *, size_t ); //#JB931601 PASCAL gestr., JB940923 --> PASCAL aktiviert
      #define TAG_CMP_FUNC int FAR PASCAL FN_EXP //#JB931601; JB940923 --> PASCAL aktiviert
      }         
   #else
      #define TAG_CMP_FUNC int 
      extern "C" {
      typedef int T4CMP_ROUTINE(const void *, const void *, size_t ) ;
      }
   #endif
#endif

class E4EXPORT KeyData
{
public:
   long fileblock()  { return rec_num ; }
   long recno()      { return rec_num ; }
   char *ptr()       { return value ; }

   long  rec_num ;
   char  value[1] ;  // The key size is variable 
} ;

class E4EXPORT Block : public Link       
{
friend class Tag ;
public:
   void *operator new( size_t ) ;
   void *operator new( size_t, Tag&, long) ;
   void  operator delete( void *) ;

   long  blockdown()   { return key()->rec_num ; }
   long  fileblock()   { return file_block ; }
   int   eof()         { return key_on >= n_keys ; }
   int   flush() ;
   void  go( int i)    { key_on = i ; }
   void  go_eof()      { key_on = n_keys ; }
   void  insert( void *, long ) ; // Inserts before current key
   KeyData  *key( int ) ;  // The specified key no.
   KeyData  *key()     { return key( key_on ) ; }
   char     *key_data(int) ;
   int   keypos()      { return key_on ; }
   int   lastpos() ;   // The last position available, adjusts for branches
   unsigned len() ;
   int   numkeys()     { return n_keys ; }
   void  numkeys(int i){ n_keys =  (short) i ; }
   int   leaf() ;      // Is the block a leaf block
   long  recno() ;     // The current record number
   void  remove() ;    // Removes current key
   int   room() ;      // True if there is room for another key
   int   seek( Str& ) ;
   int   skip( long );
   void  zero() ;      // Initialize all values to zero

   int   changed ;     // True if the block data has been changed

private:
   Tag  *tag ;
   long  file_block ;  // Identifies block within index file
   int   key_on ;      // The current key within the block

   short      n_keys ; // Block Image starts here
   char       dummy[6] ;
   KeyData    data ;
} ;

typedef struct
{
   long  header_pos ;          // Header position (in 512 byte chunks)
   char  tag[10] ;
   short x1000 ;               // used for dBASE/SQL expression type - dBASE only allowed for CBPP 1.0x
   char  left_chld ;
   char  right_chld ;
   char  parent ;
   char  x2 ;
   char  index_type ;
   char  zeros[11] ;
}  TAG_INFO ;

typedef struct
{
   long           root ;          // -1 means unknown
   char           dummy1[4] ;
   char           type_code;      // 0x10 Normal; 0x58 Uniq,Desc;
				  // 0x50 Uniq; 0x18 Desc
   char           type ;          // N,D, or C (F is type N) 
   char           dummy2[2] ;
   short          value_len ;
   short          keys_max ;      // Maximum # of keys per block;  <= 100 
   char           dummy3[2] ;     // 1 if Numeric or Date Key (NDX only) 
   short          group_len ;     // value_len plus 4 (MDX); plus 8 (NDX) 
   char           version ;
   char           dummy4 ;
   short          unique   ;      // 0x4000 (TRUE)if Unique 
   // Note, 'expr_key[220]' comes after 'unique' and
   //       'expr_filter[220]' comes at position 0x2FA
}  TAG_HEADER ;

class E4EXPORT Tag : public Link
{
public:
friend class Reindex ;
friend class Index ;
   Tag( Index * ) ; 
  ~Tag() ;
   void *operator new( size_t z ) ;
   void *operator new( size_t, void * ) ;
   void  operator delete( void * ) ;

   int   add( Str&, long rec ) ;    // Returns r4unique, r4success, r4repeat
   int   add_calc( Str&, long rec ) ; // Calculates expression and adds
   Block *block() ;
   int   bottom() ;
   int   check() ;
   int   descending()   { return ( header.type_code & 0x08 ? 1 : 0 ) ; }
   int   down() ;
   int   dump( int handle, int display_all = 1 ) ;
   int   dump_do(int,int,int) ;
   int   eof() ;
   int   flush() ;
   int   free() ;
   int   free_saved() ;
   int   go( Str&, long ) ;
   int   grouplen()                   { return header.group_len ; }
   int   init( Index&, TAG_INFO&, long ) ;
   void  init_seek_conv(int) ;         // Initialize 'stok' and 'dtok'
   KeyData  *key() ;                  // The current key
   int   keysmax()                    { return header.keys_max ; }
   int   valuelen()                   { return header.value_len ; }
   int   lock() ;
   int   position( double ) ;         // Positions a percentage down the file.
   double position(void) ;            // Returns the position as a percentage.
   long  recno() ;
   int   remove() ;                   // Remove the current key
   int   remove( Str&, long rec ) ;   // Remove the specified key
   int   remove_calc( Str&, long rec ) ; // Calculates expression and removes
   int   seek( Str& ) ;             // r4success, r4found, r4after, r4eof
   long  skip( long ) ;
   Block *split( Block * ) ;
   int   top() ;
   int   type() ;
   int   up() ;
   int   up_to_root() ;
   int   unique()             { return (int) header.unique ; }

   Expr  expr ;
   Expr  filter ;
   int   unique_error;            // Is rewriting a unique key an error ?
   Index *index ;
   T4CMP_ROUTINE  *cmp ;           // Compares two key values
   STOK  *stok ;                   // Conversion for 'seek'
   DTOK  *dtok ;                   // Conversion for 'seek'
   CodeBase   *code_base ;
   Str10       alias ;

   LinkList    blocks ;

private:
   TAG_HEADER  header ;
   long        header_offset ;     // Offset in file to the tag's header info.
   int         root_write ;        // True if 'header.root' needs to be written

   long        lock_pos ;          // The file offset to physically lock
   void       *compile ;           // A pseudo compiled version of the expression 
   int         key_dec ;

   LinkList    saved ;
} ;

class E4EXPORT TagInfo
{
public:
   char *name ;
   char *expression ;
   char *filter ;
   int   unique ;
   int   descending ;
} ;

typedef struct
{
   char   two ;                // Version number (currently 2)
   char   yymmdd[3] ;          // Date of last reindex 
   char   data_name[12] ;
   char   dummy1[4] ;          // extra 4 bytes for data-names-not used in DOS
   short  block_chunks ;       // Block Size 1 to 32 (512 byte chunks) 
   short  block_rw ;           // Block Read/Write Size in bytes
   char   is_production ;     // 1 if production index, else 0
   char   num_slots ;          // number possible tags (48)
   short  slot_size ;          // number bytes/tag slot (32)
   long   num_tags ;
   long   eof ;
   long   free_list ;          // start of the free list
   char   zero[4] ;
   char   create_date[3];      // not used by CodeBase++
   char   blank ;
   long   version ;
}  INDEX_HEADER ;

class E4EXPORT Index : public Link
{
   friend class Tag ;
   friend class Block ;
   friend class Reindex ;

public:
   Index( DataIndex *, char *name = 0 ) ;
  ~Index() ;

   void *operator new( size_t ) ;  // Do not use
   void *operator new( size_t, CodeBase * ) ;  
   void  operator delete( void * ) ;

   unsigned  block_rw_len()           { return (unsigned) header.block_rw ; }
   int   check_blocks() ;      
   int   close() ;
   int   create( char *name, TagInfo * ) ;
   long  extend() ;                // Allocates a block at the end of the file
   int   is_production() { return header.is_production ; }
   int   lock_file() ;
   int   open( char *file = 0 ) ;
   int   reindex() ;
   int   shrink( long ) ;          // Returns a block of disk space
   Tag  *tag( char *) ;
   int   unlock() ;
   int   update_header() ;
   int   version_check() ;

   File  file ;
   DataIndex *data ;
   CodeBase *code_base ;
   LinkAlloc tags ;

private:
   INDEX_HEADER header ;
   MemoryType  *block_alloc ;

   Tag  *tag_locked ;     // The locked tag.  Null if none.
   int   file_locked ;    // True if locked
   long  version_old ;
} ;

class E4EXPORT TagIterator
{
public:
   TagIterator( DataIndex& ) ;
   Tag *next_tag() ;   // Moves to the next
   Tag *prev_tag() ;   // Traces back to the beginning.  Starts with the
		       // last tag returned by 'next_tag()'.

private:
   DataIndex  *data ;  
   Index *cur_index ;  // The last index used.
   Tag   *cur_tag ;    // The last tag used for 'prev_tag()'
		       // The next tag to use for 'prev_tag()'
} ;

#else
    #error - entweder NDX, CLIPPER oder MDX definieren
#endif      // dBase-Version

#endif      // I4INDEX

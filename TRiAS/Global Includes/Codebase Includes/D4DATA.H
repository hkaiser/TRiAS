// d4data.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef D4DATA
#define D4DATA

extern "C" {
E4EXPORT_FCT void FAR PASCAL __export
InitDBaseDLL (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify);
}

// Integer Return Codes
const int r4success = 0 ;   // 
const int r4found   = 1 ;   // Primary Key Match
const int r4after   = 2 ;   //
const int r4eof     = 3 ;   //
const int r4bof     = 4 ;   //
const int r4entry   = 5 ;   // No index file entry or no record (go)
const int r4descending =  10 ;
const int r4unique  = 20 ;  // Key is not unique, do not write/append
const int r4unique_continue = 25 ;   // Key is not unique, write/append anyway
const int r4date    = 30 ;  // Illegal Date
const int r4date_null = 35; // Null Date
const int r4ignore  = 40 ;
const int r4keep    = 45 ;
const int r4locked  = 50;   //
const int r4no_create=60 ;  // Could not create file
const int r4no_open = 70 ;  // Could not open file
const int r4no_tag  = 80 ;  // DataIndex::seek, with no default tag

class E4EXPORT  Tag ;
class E4EXPORT  TagInfo ;
class E4EXPORT  Index ;
class E4EXPORT  IndexGroupFile ;
class E4EXPORT  DataFilter ;
class E4EXPORT  DField ; class E4EXPORT  MField ;
typedef unsigned size_t ;

class E4EXPORT LinkList ;
class E4EXPORT String ;

class E4EXPORT Link
{
   friend class LinkList ;
public:
   Link    *next() { return n ; }
   Link    *prev() { return p ; }

private:
   Link *n, *p ;
} ;

class E4EXPORT LinkList
{
public:
   LinkList() ;

   void    add(  Link * ) ;        // Adds link to end of list
   void    add_before( Link *anchor, Link *new_link ) ;
   void    add_after( Link *anchor,  Link *new_link ) ;
   Link   *first() ;
   Link   *last() ;
   Link   *pop() ;                 // Removes last link and return pointer
   void    remove( Link * ) ;      // Removes link from list
   void    reset() ;               // Resets the linked list

   int  n_link ;
   void check() ;
private:
   Link   *l ;     // The last Link
} ;

class E4EXPORT LinkSelect : public LinkList    // Keeps track of selected item
{
public:
   LinkSelect() ;   
   Link   *selected ;

   void    add(  Link * ) ;        // Adds link to end of list
   void    add_before( Link *anchor, Link *new_link ) ;
   void    add_after( Link *anchor,  Link *new_link ) ;
   int     nlinks()                { return n_link ; }
   Link   *pop() ;                 // Adds link to end of list
   void    remove( Link * ) ;      // Removes link from list
   void    reset() ;

private:
   int     n_link ;                // The number of links in the list
} ;

class E4EXPORT Data ;
class E4EXPORT MemoryType ;

class E4EXPORT CodeBase
{
public:
   CodeBase() ;
  ~CodeBase() ;
   Data *data( char *alias_name ) ;
   char *date_format( char *new_format = 0 ) ; // 0 only return current format

   int  close_all() ;
   int  error()               { return error_code ; }
   int  error( const int err_code, char *desc, ... ) ;
   int  error_set( int ) ;    // Returns previous error setting
   void exit_test() ;
   void exit() ;

   short block_size ;      // Block size (bytes) for memo and index files
   int blocks_expand ;     // Expanding block memory allocation
   int blocks_start ;      // Initial block memory allocation for index files

   int decimals ;          // The default number of decimals
   int numeric_str_len ;   // The default numeric string length

   unsigned sort_pool_size ;    // The default pool size for sorting
   unsigned sort_buffer_size ;  // The default file buffer size when sorting
   unsigned buffer_size ;       // Pack, Zap

   unsigned hWnd ;            // For use under Microsoft Windows
   unsigned hInst ;

   LinkList   data_list ;     // A list of open data files.
   int default_unique_error ; // e4unique, r4unique, r4unique_continue
   char date_format_info[19]; // Longest is September 15, 1990

   // True/False Flags
   int  field_name_error ;    
   int  go_error ;             // Do 'Data::go' error ?
   int  open_error ;           // Do 'File::open' error ?
   int  create_error ;         // Do 'File::create' error ?
   int  read_lock ;            // Do lock when reading database ?
   int  skip_error ;           // Do 'DataIndex::skip' error ?
   int  tag_name_error ;     
   int  safety ;               // File create with safety ?
   int  wait   ;               // Wait when locking ?
   int  auto_open ;            // Automatic production index file opening

   MemoryType *otherndx_memory ; // NDX/NTX version only!
   MemoryType *index_memory ;
   MemoryType *field_memory ;
   MemoryType *dfield_memory ;
   MemoryType *mfield_memory ;
   MemoryType *nfield_memory ;
   MemoryType *string_types[16] ;

//   String     *str_buffer ;     // used as a buffer for field values
private:
   int  error_code ;
} ;


class E4EXPORT StrLen ;

class E4EXPORT Str
{
public:
   operator char() ;
   operator double() ;
   operator int() ;
   virtual operator long() ;

   int  operator==( Str  & ) ;  // Equal, including length
   int  operator>=( Str  & ) ;
   int  operator<=( Str  & ) ;
   int  operator< ( Str  & ) ;
   int  operator> ( Str  & ) ;

   int    add( Str& ) ;
   int    assign( char *) ;
   int    assign( Str& ) ; 
   void   assign_double( double, int n_dec = -1 ) ;
   void   assign_long( long, int zeros_in_front = 0 ) ;
   char  *end_ptr() ;
   int    null_ensure() ;
   int    insert( Str&, unsigned pos= 0 ) ;
   void   lower() ;
   int    replace( Str&, unsigned pos= 0 ) ; 
   void   set( int chr_value ) ;                  
   void   trim() ;
   void   upper() ;

   // Get information 
   int    search( Str& ) ;
   StrLen substr( unsigned pos, unsigned len ) ;
   int    StrTrue() ;

   virtual void      changed()     {}
   virtual int       decimals()         { return 0 ; }
   virtual unsigned  len() ;
   virtual unsigned  maximum()              { return len() ; }
   virtual int       null_ended()       { return 0 ; }  // 1 means true
   virtual char     *ptr()  = 0 ;
   virtual int       set_len(unsigned)  { return -1 ; }
   virtual int       set_max(unsigned)  { return -1 ; }
} ;

void s4asser_no_overlap( Str&, Str& ) ;

class E4EXPORT StrChar : public Str
{
public:
   StrChar( char ch ) { c = ch ; }
   StrChar& operator=( char ch )  { c = ch ; return *this ; }
   StrChar& operator=( Str &s )     { c = char(s) ; return *this ; }
   char    *ptr()     { return &c ; }
   unsigned len()     { return 1 ; }

private:
   char c ;
} ;

class E4EXPORT StrPtr : public Str
{
public:
   StrPtr( char *ptr ) { p =   ptr ; }

   StrPtr& operator=( Str& s )     { assign(s) ; return *this ; }
   StrPtr& operator=( char *ptr )  { assign(ptr) ; return *this ; }

   void     init( char *ptr )  { p =  ptr ; }
   int      null_ended()   { return 1 ; }
   char    *ptr()          { return p ; }

   char *p ;
} ;

class E4EXPORT StrLen : public StrPtr
{
public:
   StrLen( void *ptr, unsigned ptr_len ) : StrPtr((char *)ptr) { cur_len =  ptr_len; }

   StrLen& operator=( Str& s )     { assign(s); return *this ; }
   StrLen& operator=( char *ptr )  { assign(ptr) ; return *this ; }

   void     init( void *ptr, unsigned ptr_len )  { p = (char *) ptr; cur_len =  ptr_len;}
   unsigned len()  { return cur_len ; }
   int      null_ended()   { return 0 ; }

   unsigned cur_len ;
} ;

class E4EXPORT StrMax : public StrLen
{
public:
   StrMax( void *ptr, unsigned m ) : StrLen(ptr,m)  { max_len = m; }

   StrMax& operator=( Str& s )     { assign(s); return *this ; }
   StrMax& operator=( char *ptr )  { assign(ptr) ; return *this ; }

   void     init( void *ptr, unsigned m ) { p = (char *)ptr; max_len = m ; }
   unsigned maximum() { return max_len ; }
   int      null_ended()   { return 0 ; }
   int      set_len( unsigned) ;

   unsigned max_len ;
} ;

// The following classes  are always guaranteed to be null ended.
class E4EXPORT Str10 : public Str
{
public:
   Str10()          { cur_len = 0; buf[0] = 0; buf[10] = 0; }
   Str10( char *p ) { cur_len = 0; buf[10] = 0; assign(StrPtr(p)); }

   Str10& operator=( Str& s )   { assign(s); return *this ; }
   Str10& operator=( char *ptr )  { assign(ptr) ; return *this ; }

   unsigned maximum()     { return 10 ; }
   int      null_ended()   { return 1 ; }
   unsigned len()     { return cur_len; }
   char    *ptr()     { return buf ; }
   int      set_len(unsigned new_len) ;

private:
   unsigned cur_len ;
   char buf[12] ;
} ;

class E4EXPORT Str255: public Str
{
public:
   Str255()          { cur_len = 0; buf[0] = 0; buf[255] = 0; }
   Str255( char *p ) { cur_len = 0; buf[255] = 0; assign(StrPtr(p)); }

   Str255& operator=( Str& s )   { assign(s); return *this ; }
   Str255& operator=( char *ptr )  { assign(ptr) ; return *this ; }

   unsigned maximum()     { return 255 ; }
   unsigned len()     { return cur_len; }
   int      null_ended()   { return 1 ; }
   char    *ptr()     { return buf ; }
   int      set_len(unsigned len) ;

private:
   unsigned cur_len ;
   char buf[256] ;
} ;

class E4EXPORT String : public StrMax
{
public:
   String( CodeBase * ) ;
   String( String& ) ;
  ~String() ;

   void *operator new( size_t ) ;
   void operator delete( void * ) ;

   String& operator=( Str& s )  { assign(s); return *this ; }
   String& operator=( char *p ) { assign(p); return *this ; }

   void  free() ;
   int   set_max( unsigned ) ;

   CodeBase *code_base ;
} ;


class E4EXPORT FileSeqWrite ;
class E4EXPORT FileSeqRead ;

class E4EXPORT  FileName : public String
{
public:
   FileName( CodeBase *cb ) : String( cb ) {}
   FileName& operator=( char  *p )  { assign(p); return *this ; }

   // File name manipulation
   int   assign( char  * ) ;
   int   extension( char  *, int do_replace = 0 ) ;
   int   path( char  * ) ;         // Preceed the file with the path
   int   piece( Str&, int give_path, int give_ext ) ;
   void  remove_extension() ;
} ;

class E4EXPORT File
{
public:
friend FileSeqWrite ;
friend FileSeqRead ;
   File( CodeBase * ) ;

   int  close() ;                 // Executes regardless of error setting
   int  create() ;
   long len() ;
   int  lock( long, long ) ;
   int  open() ;
   int  open_test()   { return hand >= 0 ; }
   int  read( long pos, Str& ) ;
   int  read( long pos, Str&, unsigned *len ) ;
   int  read_error() ;            // Generates a read error message
   int  remove() ;                // Executes regardless of error setting
   int  rename( FileName& ) ;
   int  set_len( long ) ;
   int  temp( int auto_remove = 1 ) ; // Create a temporary file
   int  unlock( long, long ) ;
   int  write( long pos, Str& ) ;

   FileName  name ;
   CodeBase *code_base ;

   int   hand ;
   int   is_temp ;      // True if it is a temporary file
} ;

class E4EXPORT FieldDataImage 
{
public:
   char    name[11] ;
   char    type ;
   char    filler[4] ;
   unsigned char  len ;
   unsigned char  decimals ;
   char    filler2[13] ;
   char    has_tag ;
}  ;

class E4EXPORT Field : public Str
{
friend class Data ;
public:
   Field( Data *, FieldDataImage *, unsigned *last_offset_ptr ) ;
   void *operator new( size_t ) ;
   void *operator new( size_t, CodeBase * ) ;
   void operator delete( void * ) ;
   virtual void do_delete( void * ) ;

   Field&  operator=( Str& s )  { assign(s); return *this ; }
   Field&  operator=( Field& s) { assign(s); return *this ; }
   Field&  operator=( char  * ) ;
   Field&  operator=( double d) { assign(d); return *this ; }

   virtual void  assign (double);
   virtual int   assign (Str&) ;

   virtual void  changed() ;
   int           decimals()  { return dec ; }
   virtual int   flush()     { return 0 ; }
   virtual unsigned  len()   { return len_field ; }
   virtual char *ptr() ;
//   virtual char *str() ;
   virtual void  reset()     {}
   int           type()      { return type_field ; }

   Str10       name ;

protected:
   Data       *data ;

private:
   unsigned    len_field ;
   int         dec ;
   int         type_field ;
   unsigned    offset ;
} ;

class E4EXPORT NField : public Field
{
public:
   NField( Data *, FieldDataImage *, unsigned *last_offset_ptr ) ;
   void *operator new( size_t ) ;
   void *operator new( size_t, CodeBase * ) ;
   void operator delete( void * ) ;
   void do_delete( void * ) ;

   NField() : Field(0,0,0) {}
   NField&  operator=( NField& f ) ;
   NField&  operator=( Str& ) ;
   NField&  operator=( double ) ;

   void      assign (double d) { Field :: assign (d); }
   int       assign( Str& ) ;
} ;

class E4EXPORT FieldInfo
{
public:
   char   *name ;
   char    type ;
   short   len_field ;
   short   dec ;
} ;

class E4EXPORT DataHeader
{
public:
   /* Database Header Information */
   char     version ;        /* 83H with .dbt, 03H without */
   char     yy ;             /* Last Update */
   char     mm ;
   char     dd ;
   long     num_recs ;       
   unsigned short header_len; // Header Length, Indicates start of data
} ;

class E4EXPORT FullHeader : public DataHeader
{
public:
   unsigned short record_len;
   char     zero[16] ;
   short    has_mdx ;    // 1 for true
   char     zero2[2] ;
} ;

class E4EXPORT Record : public StrLen
{
public:
   Record() ;
   Record& operator=( Str& s )     { assign(s); return *this ; }
   void changed() { is_changed = 1 ; }

   int  is_changed ;
} ;

// Never automatically locks or flushes due to change, does not keep
// track of locked or unlocked records.
class E4EXPORT Data : public Link
{
public:
   Data( CodeBase  *, char  *name = 0 ) ;
  ~Data() ;

   int   append() ;
   void  changed()          { record.changed() ; }
   virtual int   close() ;          // Executed regardless of error setting
   int   create( char  *name, FieldInfo  * ) ;
   int   deleted()          { return *record.ptr() != ' ' ; }
   void  delete_rec()       { *record.ptr() = '*' ; changed() ; }
   virtual Field *field_create( Data *, FieldDataImage *, unsigned * ) ;
   Field  *field( char  *name ) ;
   Field  *field( int j ) ;
   DField *dfield( char  *name ) ;
   int     jfield( char  *name ) ;
   NField *nfield( char  *name ) ;
   int   go( long ) ;
   int   lock( long );                // Locks a record
   int   lock( long *, int ) ;        // An array of records to lock
   int   lock_append() ;              // Locks for appending
   int   lock_file() ;                // Locks a complete data file
   int   lock_test( long ) ;          // 1 if locked; 0 parm for count   
   int   lock_test_file() ;           // 1 if the data file is locked
   int   lock_test_append() ;         // 1 if locked for appending
   int   num_fields() ;
   int   open( char  *name = 0 ) ;
   int   pack() ;
   int   read( long, Str& ) ;         // No lock, no error display
   int   read_old( long ) ;
   void  recall()           { *record.ptr() =  ' ' ; changed() ; }
   long  reccount() ;       // Calculates from file length
   long  recno()            { return rec_num ; }
   long  recpos( long r )   { return header.header_len + (r-1)*record.len() ; }
   int   unlock_all() ;         // Unlocks append, file and record
   int   unlock_append() ;      // Unlocks the append bytes
   int   unlock_file() ;        // Unlocks any complete file locks
   virtual int  unlock_index()  { return 0 ; }
   int   unlock_records() ;     // Unlocks any specific records
   int   update_header( int do_time_stamp, int do_count ) ;
   int   write( long ) ;
   int   zap( long, long ) ;

   Record record_old ;          // Data allocated with 'm4alloc'
   Record record ;              // Data allocated with 'm4alloc'
				// Extra byte added for temporary CTRL_Z
   long   rec_num ;             // Record number; -1 unknown; 0 for append
   long   rec_num_old ;         // Record number, -1 none present; 0 for append

   File  file ;
   Str10 alias ;

   CodeBase *code_base ;
   short       has_mdx ;        // Has an MDX file attached to it

   Field     **memo_fields ;    // A list of fields to be flushed
   int         n_memo_fields ;  // The number of memo files in the database

protected:
   long        locked_record ;  // 'locks' data when 'n_locks <= 1'
   long       *locks ;
   int         n_locks ;        // Number of elements in 'locks' allocated
   int         num_locked ;     // Number of records locked
   int         file_lock ;      // True if entire file is locked
   int         append_lock ;    // True if the file is locked for appending

   Field     **fields ;         // An array of field pointers
   int         n_fields ;       // The number of data fields in the database
   int         file_changed ;   // True if the file has been changed since
				// the header has been updated.
public:
   DataHeader  header ;
} ;

class E4EXPORT DataIndex : public Data
{
friend class DataFilter ;
public:
   DataIndex ( CodeBase *, char *name = 0 ) ;
  ~DataIndex() ;

   virtual int   append() ;
   int   append_blank() ;
   int   append_start() ;
   int   bof()                        { return bof_flag ; }
   int   bottom() ;
   void  change_reset() ;
   int   check() ;
   virtual int   close() ;
   int   create( char *name, FieldInfo *, TagInfo *t= 0 ) ;
   int   create_ndx( TagInfo *ind_data ) ;  // NDX Only.  Creates index files.
   int   eof() ;
   int   flush_all() ;                // Flushes index file & data information
   int   flush_record() ;             // Flushes data record & memo fields
				      // Updates index files if present
   int   go( long ) ;
   int   go_eof() ;
   int   lock_index() ;               // Index files are locked.
   int   open( char *name = 0 ) ;     // with MDX if possible
   int   pack() ;
   int   position( double ) ;         // Positions a percentage down the file.
   double position() ;                // Returns the position as a percentage.
   int   reindex() ;
   int   seek( double ) ;
   int   seek( Str& ) ;         
   int   seek( char *p )              { return seek(StrPtr(p)) ; }
   void  select( Tag * ) ;
   int   select( char *tag_name = 0 ) ;
   int   skip( long n_skip = 1L ) ;
   Index  *index_default() ;          // NDX Version Only
   Index  *index_selected();          // NDX Version Only
   Tag  *tag( char *, Index *index_ptr =  0 ) ;
   Tag  *tag_default() ;
   Tag  *tag_selected() ;
   int   top() ;
   int   unlock_all() ;               // Unlocks data file and index files
   int   unlock_index() ;             // Unlocks all index files
   virtual int   write( long ) ;
   int   write_keys(long) ;
   int   zap( long, long ) ;

   IndexGroupFile *production_group ;       // NDX/NTX only!
   LinkSelect indexes ;
   Index *production ;           // Production index allocated with 'new'
				 // by Code Base
private:
   int   bof_flag, eof_flag ;    // Beginning/End of File flags
} ;

#endif		// D4DATA


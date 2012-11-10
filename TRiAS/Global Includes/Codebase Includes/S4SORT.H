// s4sort.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef S4SORT

#define S4SORT

#ifndef D4DATA
#include "d4data.h"
#endif

#ifndef F4FILESE
#include "f4filese.h"
#endif

#ifndef L4LINK
#include "l4link.h"
#endif

#ifdef D4DLLS
extern "C" {
   typedef int FAR PASCAL SORT_CALL_BACK( const void *, const void*, size_t ) ; // #JB940921; #JB940923 --> PASCAL aktiviert
   #define SORT_FUNCTION int FAR PASCAL FN_EXP //#JB920106; #JB940923 --> PACAL FN_EXP aktiviert
   SORT_FUNCTION dll_memcmp( const void *a, const void *b, size_t c ) ; //#JB920611
}
   #include "e4error.h"
#else
   typedef int SORT_CALL_BACK( const void *, const void*, size_t ) ;
   #define SORT_FUNCTION int
   #ifdef __ZTC__
      SORT_FUNCTION zc_memcmp( const void *a, const void *b, size_t c) ;
   #endif
#endif

class E4EXPORT Spool  // Partially in memory and partially on disk.
{
public:
   char  *ptr ;       // Pointer to the starting memory
   unsigned  pos ;    // The current position withing 'ptr'
   unsigned  len ;    // The current data length pointed to by 'ptr'

   long   disk ;      // Current Disk Position, Offset from start of 'spool'
		      // >= 'spool_bytes' means nothing is on disk.
   int    spool_i ;   // The spool number of this spool 
} ;

class E4EXPORT Sort
{
public:
   Sort( CodeBase *cb ) ;
  ~Sort() ;                // Frees any allocated memory

   void  assign_cmp( SORT_CALL_BACK *scb )
      {
         #ifndef WINDOWS
                #ifdef DLL
                     if ( code_base->hInst == (HANDLE) 0 ) 
                        e4severe( e4info, "Error: must set CodeBase.hInst if using a DLL", (char *) 0 ) ;
                        FARPROC lpfnfilter_routine = MakeProcInstance( (FARPROC) scb,
                                                     code_base->hInst ) ;
                        cmp = (SORT_CALL_BACK *)lpfnfilter_routine ;
                #else
                    //  normal case or dll library case
                        cmp = scb ;
                #endif  // DLL
        #else   // WINDOWS
                cmp = scb ;                
        #endif         
      }
   void  delete_spool_entry() ;
   int   flush() ;         // Flushes current entries to disk
   int   free() ;          // Uninitializes
   int   get_init() ;
   int   get( long *rec_ptr, void **sort_data, void **other_data ) ;
   int   get_ptr_ptr( char **ptr_ptr ) ;
   int   init( int, int ) ;
   void  init_pointers( char *, unsigned ) ;
   long  needed() ;        // Returns an estimate on the amount of memory needed
   int   next_spool_entry() ;
   int   put( long rec, void  *sort_data, void *other_data ) ;

   int   sort_len ;

private:
   FileSeqWrite  seqwrite ;
   File          file ;
   StrLen        seqwrite_buffer ;
   Spool  *spool_pointer ;
   int     spools_n ;      // The current # of "spools"
   int     spools_max ;    // The # of "spools" memory is allocated for

   char **pointers ;
   int   pointers_i ;    // The next pointers to return using 'get'.
   int   pointers_used ; // The number of pointers assigned so far.
   int   pointers_init ; // The number of pointers initialied so far.
   int   pointers_max ;  // The number of pointers for which memory 
			 // has been allocated.

   LinkAlloc pool ;      // A number of memory pools for sorting
   int   pool_n ;        // The number of pools
   int   pool_entries ;  // Number of record entries in each pool

   long     spool_disk_len ; // The # of bytes in each disk spool
   unsigned spool_mem_len ;  // The # of bytes in each memory spool

   int   info_offset ;   // The spot to put the corresponding info.
   int   info_len ;
   int   tot_len ;       // The total length of each pool entry.

   long  is_mem_avail ;
   SORT_CALL_BACK *cmp ;
   CodeBase *code_base ;
} ;

// The 'len' is passed to the compare function as its third parameter
// The compare function returns '(int) 1' iff 'v1>v2'.
// s4quick also assumes that there is a record number after the sort data
extern void s4quick( void **p, int p_n, SORT_CALL_BACK *, int sort_data_len ) ;


#endif

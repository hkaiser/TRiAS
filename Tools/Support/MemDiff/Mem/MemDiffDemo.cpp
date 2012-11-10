//==================================================
// MemDiff - Matt Pietrek 1999
// Microsoft Systems Journal, December 1999
// FILE: MemDiffDemo.cpp
//==================================================
#include <windows.h>
#include "memdiff.h"

int main()
{
    HANDLE h1, h2;


    //
    // Create a new heap, and allocate a bunch of memory.  The
    // HEAP_ZERO_MEMORY forces all the allocated pages in
    //    
    HANDLE hHeap1 = HeapCreate( 0, 0, 0 );
    HeapAlloc( hHeap1, HEAP_ZERO_MEMORY, 0x7000 );

    //
    // Take the initial snapshot
    //
    h1 = MDTakeSnapshot( GetCurrentProcess() );


    // Get rid of hHeap1.  This test ensures that we see something in
    // the Snapshot1 details report
    HeapDestroy( hHeap1 );

    //
    // Load, then free a DLL.  Extra memory paged into the
    // working set, but not freed *should* show up.
    //
    HMODULE hModule = LoadLibrary( "WININET.DLL" );
    FreeLibrary( hModule );

    //
    // Allocate some memory, and leave it around
    //
    PVOID p = VirtualAlloc( 0, 0x1000, MEM_COMMIT, PAGE_READWRITE );
    memset( p, 0, 0x1000 ); // Touch it!


    HANDLE hHeap2 = HeapCreate( 0, 0, 0 );

    HeapAlloc( hHeap2, HEAP_ZERO_MEMORY, 0x1234 );

    HANDLE hFileMapping = CreateFileMapping( INVALID_HANDLE_VALUE, 0,
                                             PAGE_READWRITE, 0, 0x2000, 0 );
    if ( hFileMapping )
    {
        PVOID p2 = MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0x2000);
        if ( p2 )
            memset( p2, 0, 0x2000 );
    }

    //
    // Take the second snapshot
    //
    h2 = MDTakeSnapshot( GetCurrentProcess() );

    //
    // Compare the two snapshots to generate a report
    //
    MDCompareSnapshot( h1, h2, GetStdHandle(STD_OUTPUT_HANDLE), false );
    
    //
    // Free the snapshot handles (aka "memory")
    //
    MDFreeSnapshot( h1 );
    MDFreeSnapshot( h2 );

    return 0;
}

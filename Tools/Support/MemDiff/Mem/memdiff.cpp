//==================================================
// MemDiff - Matt Pietrek 1999
// Microsoft Systems Journal, December 1999
// FILE: memdiff.cpp
//==================================================
#include "StdAfx.h"
#include <stdarg.h>
#include "memdiff.h"

//===================================================================
static int __cdecl MDSort( const void *pElem1, const void *pElem2 );

void FilterOutCommonPages( HANDLE hSnapshot1, HANDLE hSnapshot2 );

void SummaryReport( HANDLE hSnapshot1,
                    HANDLE hSnapshot2,
                    MDOUTPUTPROC pOutputFile );

void DetailedReport(HANDLE hSnapshot1,
                    HANDLE hSnapshot2,
                    MDOUTPUTPROC pOutputFile,
                    bool fVerbose = false );

void MDPrintf( MDOUTPUTPROC pOutputFile, char * pszFmt, ... );

//===================================================================

typedef struct MEMDIFF_SNAPSHOT
{
    DWORD   m_signature;
    DWORD   m_dwAllocSize;
    DWORD   m_fCompared;    // 0 initially, 1 after filtering common pages
    DWORD   m_nPages;       // Must come last!!!
} * PMEMDIFF_SNAPSHOT;

#define SNAPSHOT_SIGNATURE 0x50594F52

static DWORD g_kbMultiplier;

//===================================================================

extern "C"
HANDLE
__stdcall
MDTakeSnapshot( HANDLE hProcess )
{
    unsigned dwAlloc = 0;

top:

    dwAlloc += 0x2000;

    PMEMDIFF_SNAPSHOT pSnapshot;
    pSnapshot = (PMEMDIFF_SNAPSHOT)VirtualAlloc(0,
                                                dwAlloc,
                                                MEM_COMMIT,
                                                PAGE_READWRITE);

    if ( !pSnapshot )
        return 0;

    PVOID pPageInfoStart = &pSnapshot->m_nPages;

    if ( 0 == QueryWorkingSet(  hProcess, pPageInfoStart,
                                dwAlloc - sizeof(*pSnapshot) ) )
    {
        VirtualFree( pSnapshot, 0, MEM_RELEASE );
        return 0;
    }
    else    // It succeded.... But...
    {
        // Were there more pages than we had buffer size for?
        if ( pSnapshot->m_nPages > (dwAlloc / sizeof(DWORD)) )
        {
            if ( dwAlloc < 0x20000 )    // Limits us to 128MB on an x86
            {
                VirtualFree( pSnapshot, 0, MEM_RELEASE );
                pSnapshot = 0;
                goto top;
            }
            else
                return 0;
        }
    }

    pSnapshot->m_signature = SNAPSHOT_SIGNATURE;
    pSnapshot->m_fCompared = 0;
    pSnapshot->m_dwAllocSize = dwAlloc;

    return (HANDLE) pSnapshot;
}


extern "C"
BOOL
__stdcall
MDCompareSnapshot(  HANDLE hSnapshot1,
                    HANDLE hSnapshot2,
                    MDOUTPUTPROC pOutputFile,
                    bool fVerbose )
{
    if ( !hSnapshot1 || !hSnapshot2 )
        return false;

    if ( IsBadReadPtr( (PVOID)hSnapshot1, sizeof(MEMDIFF_SNAPSHOT) ) )
        return false;

    if ( IsBadReadPtr( (PVOID)hSnapshot2, sizeof(MEMDIFF_SNAPSHOT) ) )
        return false;

    if ( ((PMEMDIFF_SNAPSHOT)hSnapshot1)->m_signature != SNAPSHOT_SIGNATURE )
        return false;

    if ( ((PMEMDIFF_SNAPSHOT)hSnapshot2)->m_signature != SNAPSHOT_SIGNATURE )
        return false;

    if (    ((PMEMDIFF_SNAPSHOT)hSnapshot1)->m_fCompared
        ||  ((PMEMDIFF_SNAPSHOT)hSnapshot2)->m_fCompared )
    {
        MDPrintf( pOutputFile,
                  "One or both snapshots has already been compared against."
                  "\r\nSnapshots are only good for one compare.\r\n" );

        return false;
    }


    MDPrintf( pOutputFile,  "\r\nBegin of memory snapshot compare =============="
                            "================================\r\n" );
	SYSTEM_INFO sysInfo;
    GetSystemInfo( &sysInfo );
    g_kbMultiplier = sysInfo.dwPageSize/1024;

    FilterOutCommonPages( hSnapshot1, hSnapshot2 );

    SummaryReport( hSnapshot1, hSnapshot2, pOutputFile );

    MDPrintf( pOutputFile, "\r\n" );

    DetailedReport( hSnapshot1, hSnapshot2, pOutputFile, fVerbose );

    MDPrintf( pOutputFile,  "End of memory snapshot compare ================"
                            "================================\r\n\r\n" );

    return true;
}

extern "C"
BOOL
__stdcall
MDFreeSnapshot( HANDLE hSnapshot )
{
    if ( ((PMEMDIFF_SNAPSHOT)hSnapshot)->m_signature != SNAPSHOT_SIGNATURE )
        return false;

    return VirtualFree( hSnapshot, 0, MEM_RELEASE );
}

/*========================================================================*/
// Helper function routines
//

static int __cdecl MDSort( const void *pElem1, const void *pElem2 )
{
    DWORD elem1 = *(PDWORD)pElem1;
    DWORD elem2 = *(PDWORD)pElem2;

    if ( elem1 > elem2 )
        return 1;
    else if ( elem1 < elem2 )
        return -1;
    else
        return 0;
}

void FilterOutCommonPages( HANDLE hSnapshot1, HANDLE hSnapshot2 )
{
    PMEMDIFF_SNAPSHOT pSnapshot1 = (PMEMDIFF_SNAPSHOT)hSnapshot1;
    PMEMDIFF_SNAPSHOT pSnapshot2 = (PMEMDIFF_SNAPSHOT)hSnapshot2;

    pSnapshot1->m_fCompared = 1;    // So we don't use it again
    pSnapshot2->m_fCompared = 1;    // So we don't use it again

    DWORD nPages1 = pSnapshot1->m_nPages;
    DWORD nPages2 = pSnapshot2->m_nPages;

    PDWORD pPages1 = (PDWORD)(pSnapshot1 + 1);
    PDWORD pPages2 = (PDWORD)(pSnapshot2 + 1);

    qsort( pPages1, nPages1, sizeof(DWORD), MDSort );

    qsort( pPages2, nPages2, sizeof(DWORD), MDSort );

    //
    // Clean this up!  Basically, set all pages that are the same
    // in both snapshots to the value '0'
    //
    DWORD jStart = 0;

    for ( DWORD i = 0; i < nPages1; i++ )
    {
        DWORD pAddr1 = pPages1[i] & 0xFFFFF000;

        for ( DWORD j = jStart; j < nPages2; j++ )
        {
            DWORD pAddr2 = pPages2[j] & 0xFFFFF000;

            if ( pAddr1 == pAddr2 )
            {
                pPages1[i] = pPages2[j] = 0;
                jStart = j+1;
                break;
            }

            if ( pAddr2 > pAddr1 )
                break;
        }
    }

    // now filter out the pages used by snapshot1 for snapshot1's data
    for ( i = 0; i < nPages1; i++ )
    {
        DWORD pAddr1 = pPages1[i] & 0xFFFFF000;
    
        if ( (pAddr1 >= (DWORD)pSnapshot1) &&
             (pAddr1 < ((DWORD)pSnapshot1 + pSnapshot1->m_dwAllocSize)) )
        {
             pPages1[i] = 0;
        }
    }

    // now filter out the pages used by snapshot2 for snapshot2's data
    for ( i = 0; i < nPages2; i++ )
    {
        DWORD pAddr2 = pPages2[i] & 0xFFFFF000;
    
        if ( (pAddr2 >= (DWORD)pSnapshot2) &&
             (pAddr2 < ((DWORD)pSnapshot2 + pSnapshot2->m_dwAllocSize)) )
        {
             pPages2[i] = 0;
        }
    }
}

void SummaryReport( HANDLE hSnapshot1,
                    HANDLE hSnapshot2,
                    MDOUTPUTPROC pOutputFile )
{
    PMEMDIFF_SNAPSHOT pSnapshot1 = (PMEMDIFF_SNAPSHOT)hSnapshot1;
    PMEMDIFF_SNAPSHOT pSnapshot2 = (PMEMDIFF_SNAPSHOT)hSnapshot2;

    DWORD nPages1 = pSnapshot1->m_nPages;
    DWORD nPages2 = pSnapshot2->m_nPages;

    PDWORD pPages1 = (PDWORD)(pSnapshot1 + 1);
    PDWORD pPages2 = (PDWORD)(pSnapshot2 + 1);

    DWORD nPagesLeft1 = 0, nPagesShared1 = 0;
    DWORD nPagesLeft2 = 0, nPagesShared2 = 0;

    for ( DWORD i = 0; i < nPages1; i++ )
    {
        if ( 0 == pPages1[i] )
            continue;

        nPagesLeft1++;
        if ( pPages1[i] & 0x100 )
            nPagesShared1++;
    }

    for ( i = 0; i < nPages2; i++ )
    {
        if ( 0 == pPages2[i] )
            continue;

        nPagesLeft2++;
        if ( pPages2[i] & 0x100 )
            nPagesShared2++;
    }

    MDPrintf( pOutputFile, "Memory Difference: %uKB\r\n",
            (long)((nPagesLeft2 - nPagesLeft1)) * g_kbMultiplier );

    MDPrintf( pOutputFile, "Memory allocated: %uKB\r\n",
            nPagesLeft2 * g_kbMultiplier );

    MDPrintf( pOutputFile, "Memory freed: %uKB\r\n",
            nPagesLeft1 * g_kbMultiplier );

    MDPrintf(   pOutputFile,
                "Private memory: %uKB    Shared(potentially): %uKB\r\n",
                (nPagesLeft2 - nPagesShared2) * g_kbMultiplier,
                (nPagesShared2 * g_kbMultiplier) );
}

void DetailedReportHelper(HANDLE hSnapshot, MDOUTPUTPROC pOutputFile, bool fVerbose)
{
    MDPrintf( pOutputFile,  "==============================================="
                            "================================\r\n" );

    if ( fVerbose )
    {
        MDPrintf( pOutputFile,  "RW:read-write  RO:read-only  EX:executable  "
                                "CW:copy-on-write  SH:shared\r\n" );
        MDPrintf( pOutputFile, "Address    Size Attribute Owner\r\n" );
    }
    else
    {
        MDPrintf( pOutputFile, "Address    Size Owner\r\n" );
    }

    PMEMDIFF_SNAPSHOT pSnapshot = (PMEMDIFF_SNAPSHOT)hSnapshot;

    DWORD nPages = pSnapshot->m_nPages;
    PDWORD pPages = (PDWORD)(pSnapshot + 1);

    CProcessHeaps heaps;

    for ( DWORD i = 0; i < nPages; )    // we bump up 'i' at end
    {
        if ( 0 == pPages[i] )   // Skip empty (common) pages
        {
            i++;
            continue;
        }

        //
        // Gather basic information about this page
        //
        PVOID pAddr = (PVOID)(pPages[i] & 0xFFFFF000);
        DWORD pageAttrib = pPages[i] & 0x00000FFF;

        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(pAddr, &mbi, sizeof(mbi));

        PVOID allocationBase = mbi.AllocationBase;

        //
        // Now coalesce this page with adjoining, similar pages
        //
        DWORD nCoalescedPages = 1;
        DWORD j;

        if ( fVerbose ) // Pages must be contiguous, and share the same
        {               // attributes and allocation base
            for ( j=i+1; j < nPages; j++ )
            {
                if ( 0 == pPages[j] )
                    break;
                
                if ( (pPages[j] & 0x00000FFF) != pageAttrib )
                    break;
                
                VirtualQuery( (PVOID)pPages[j], &mbi, sizeof(mbi));
                if ( mbi.AllocationBase != allocationBase )
                    break;
                
                nCoalescedPages++;
            }
        }
        else    // Pages must share the same allocation base
        {
            for ( j=i+1; j < nPages; j++ )
            {
                if ( 0 == pPages[j] )
                    continue;
                            
                VirtualQuery( (PVOID)pPages[j], &mbi, sizeof(mbi));
                if ( mbi.AllocationBase != allocationBase )
                    break;
                
                nCoalescedPages++;
            }
        }

        DWORD nProcessedPages = j - i;

        char szPageAttrib[128] = {0};

        if ( (pageAttrib & 5) == 5 )
        {
            strcat( szPageAttrib, "CW " );
        }
        else
        {
            if ( pageAttrib & 1 )
                strcat( szPageAttrib, "RO " );

            if ( pageAttrib & 2 )
                strcat( szPageAttrib, "EX " );

            if ( pageAttrib & 4 )
                strcat( szPageAttrib, "RW " );
        }

        if ( pageAttrib & 0x100 )
        {
            strcat( szPageAttrib, "SH " );
        }

        char szPageOwner[MAX_PATH];
        szPageOwner[0] = 0;

		if ( 0 == allocationBase )
		{
			strcpy( szPageOwner, "<unknown>" );
		}
        else if ( !GetModuleFileName((HINSTANCE)allocationBase, szPageOwner,
                                sizeof(szPageOwner)) )
        {
            if ( heaps.IsAddressInHeaps( allocationBase) )
            {
                wsprintf( szPageOwner, "Heap" );
            }
            else if ( GetMappedFileNameA( GetCurrentProcess(), allocationBase,
                                          szPageOwner, sizeof(szPageOwner)))
            {
                // GetMappedFileNameW is just a call to
                // NtQueryVirtualMemory( 2 ).  (0 is VirtualQueryEx)
                ;
            }
            else
                wsprintf( szPageOwner, "VirtualAlloc/Stack/Other" );
        }

        if ( fVerbose )
        {
            MDPrintf( pOutputFile, "%08X %5uK %-9s %s\r\n",
                pAddr, nCoalescedPages * g_kbMultiplier,
                szPageAttrib, szPageOwner );
        }
        else
        {
            MDPrintf( pOutputFile, "%08X %5uK %s\r\n",
                pAddr, nCoalescedPages * g_kbMultiplier, szPageOwner );
        }

        i += nProcessedPages;
    }
}

void DetailedReport(HANDLE hSnapshot1,
                    HANDLE hSnapshot2,
                    MDOUTPUTPROC pOutputFile,
                    bool fVerbose)
{
    MDPrintf(pOutputFile, "Snapshot1 (items are no longer in memory)\r\n");

    DetailedReportHelper( hSnapshot1, pOutputFile, fVerbose );

    MDPrintf( pOutputFile, "\r\n" );

    MDPrintf(pOutputFile, "Snapshot2 (these items have been paged in)\r\n");

    DetailedReportHelper( hSnapshot2, pOutputFile, fVerbose );
}

void MDPrintf( MDOUTPUTPROC pOutputFile, char * pszFmt, ... )
{
   va_list marker;
   va_start( marker, pszFmt );

   char szBuffer[1024];

   int retValue = wvsprintf( szBuffer, pszFmt, marker );

   if ( retValue )
       pOutputFile (szBuffer, retValue);

   va_end( marker );              
}

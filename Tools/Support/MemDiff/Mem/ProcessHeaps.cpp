//==================================================
// MemDiff - Matt Pietrek 1999
// Microsoft Systems Journal, December 1999
// FILE: ProcessHeaps.cpp
//==================================================
#include "stdafx.h"
#include "ProcessHeaps.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessHeaps::CProcessHeaps()
{
    m_aHeaps[0] = 0;
    
    m_nHeaps = GetProcessHeaps(sizeof(m_aHeaps)/sizeof(m_aHeaps[0]),m_aHeaps);

    // For each heap, get starting and ending address
    for ( unsigned i=0; i < m_nHeaps; i++ )
    {
        MEMORY_BASIC_INFORMATION mbi;

        // This is fundamentally flawed, since heaps can have multiple
        // segments.  Nonetheless, it's a decent choice for a quick'n'dirty
        // solution.
        VirtualQuery( m_aHeaps[i], &mbi, sizeof(mbi) );
        m_aHeapInfo[i].m_pStart = mbi.AllocationBase;
        m_aHeapInfo[i].m_pEnd =
                (PVOID)((DWORD)mbi.AllocationBase + mbi.RegionSize);
    }
}

bool CProcessHeaps::IsAddressInHeaps( PVOID pAddr )
{
    // Iterate through each heap, and see if the passed in address
    // is within the range of the heap.  If so, return true.
    //
    // NOTE:  A more complete (but much slower algorithm) would be to
    // use HeapWalk to enumerate through each heap block.
    for ( unsigned i=0; i < m_nHeaps; i++ )
    {
        if ( pAddr >= m_aHeapInfo[i].m_pStart )
            if ( pAddr <= m_aHeapInfo[i].m_pEnd )
                return true;
    }

    return false;
}

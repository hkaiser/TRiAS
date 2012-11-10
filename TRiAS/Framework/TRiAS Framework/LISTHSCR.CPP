/*
 * LISTHSCR.CPP
 *
 * Added functions to support horizontal listbox scrolling.  This
 * DLL is generalized to support any listbox.  The FInitListboxExtents
 * function allocates local memory (from the DLLs DATA segment) for
 * the list of string extents to go in the listbox.  The local handle
 * is then assigned as a property of the window, so every other
 * function first looks at this property.
 *
 * This means that any number of horizontal scrolling listboxes can
 * be used in the system and make use of these functions, as long
 * as the DLLs memory is not full.
 *
 */

#include "tfrmpre.hxx"

// Unit of allocation for extent list.
#define CBALLOCUNIT     (sizeof(DWORD)<<7)

// Number of units per allocation unit.
#define CALLOCUNITS     128

/*
 * Private prototypes
 */
#if defined(_FORCE_LEGACY_CODE)
BOOL FReAllocExtentList(HANDLE, BOOL);
WORD IFindExtentInList(WORD *, WORD, WORD);
#else
BOOL FReAllocExtentList(DWORD *, DWORD, DWORD **);
WORD IFindExtentInList(WORD *, WORD, DWORD);
#endif // defined(_FORCE_LEGACY_CODE)
WORD WGetListboxStringExtent(HWND, LPCSTR);


/*
 * This is just the label of the property given to each listbox
 * that asks for an extent list.
 */

char szXTList[]="XTList";

/*
 * FInitListboxExtents
 *
 * Purpose:
 *  Simple helper function to initialize everything for maintaining
 *  horizontal extents in a listbox.  This function allocates memory
 *  to hold the list of extents and assigns it to the window as a property.
 *
 * Parameters:
 *  hList       HWND of the listbox concerned.
 *
 * Return Value:
 *  BOOL        TRUE if the function was successful.
 *              FALSE if memory could not be allocated.
 */

BOOL BaseListBox::InitListboxExtents()
{
HWND hList = Handle();

#if defined(_FORCE_LEGACY_CODE)
    HANDLE      hMem;
    WORD        *pw;

    /*
     * Initially allocate 260 bytes, or 130 WORDs since the majority
     * of listbox usage will not require a reallocation, and
     * allocating 256 bytes is just as efficient as allocating 2
     * bytes, if not more so because of reduces overhead.
     *
     * The extra two words store the current number of extent entries
     * and the maximum number possible in this memory block.
     *
     */

    hMem=LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, CBALLOCUNIT + (sizeof(WORD)<<1));

    if (hMem==NULL)
        return FALSE;

    /*
     * Set the first two words in the memory to the appropriate values.
     * If we can't lock it we can;'t use it!
     */
    pw=(WORD *)LocalLock(hMem);

    if (pw==NULL)
    {
        LocalFree(hMem);
        return FALSE;
    }

    *pw=0;                  //cExtentEntries
    *(pw+1)=CALLOCUNITS;    //cExtentEntriesMax

    LocalUnlock(hMem);

    /*
     * Assign the memory handle as a property of the listbox.  This allows
     * this code to take any hList and get it's extent entry list,
     * therefore having full support for multiple listboxes.
     */
    SetProp(hList, (LPSTR)szXTList, hMem);
#else
    /*
     * Initially allocate 260 bytes, or 130 WORDs since the majority
     * of listbox usage will not require a reallocation, and
     * allocating 256 bytes is just as efficient as allocating 2
     * bytes, if not more so because of reduces overhead.
     *
     * The extra two words store the current number of extent entries
     * and the maximum number possible in this memory block.
     *
     */

WORD *pw = (WORD *)malloc (CBALLOCUNIT + 2*sizeof(DWORD));

    if (NULL == pw)
        return FALSE;

    /*
     * Set the first two words in the memory to the appropriate values.
     * If we can't lock it we can;'t use it!
     */
DWORD *pdwHdr = reinterpret_cast<DWORD *>(pw);

    *pdwHdr = 0;                  //cExtentEntries
    *(pdwHdr+1) = CALLOCUNITS;    //cExtentEntriesMax

    /*
     * Assign the memory handle as a property of the listbox.  This allows
     * this code to take any hList and get it's extent entry list,
     * therefore having full support for multiple listboxes.
     */
    SetProp(hList, (LPSTR)szXTList, (HANDLE)pw);
#endif // defined(_FORCE_LEGACY_CODE)
    return TRUE;
}


/*
 * FFreeListboxExtents
 *
 * Purpose:
 *  Release any memory used for storing the extents of the
 *  horizontal listbox.  This MUST be called when the listbox
 *  is destroyed, like in the WM_DESTROY case of the parent window.
 *
 * Parameters:
 *  hList       HWND of the listbox concerned.
 *
 * Return Value:
 *  BOOL        TRUE if the function was successful.
 *              FALSE if there is an error.
 */

BOOL BaseListBox::FreeListboxExtents()
{
HWND hList = Handle();

#if defined(_FORCE_LEGACY_CODE)
    HANDLE      hMem;
    BOOL        fSuccess;

    //Load the handle to free.
    hMem=GetProp(hList, (LPSTR)szXTList);

    /*
     * Return a BOOL on the result.  An app could keep calling this
     * function until it worked since hMem is still around.
     */
    fSuccess=(BOOL)LocalFree(hMem);

    if (fSuccess)
        RemoveProp(hList, (LPSTR)szXTList); //Only if handle was freed!

    return fSuccess;
#else
//Load the handle to free.
WORD *pw = (WORD *)GetProp (hList, (LPSTR)szXTList);

	if (NULL != pw) {
		free (pw);
		RemoveProp (hList, (LPSTR)szXTList); //Only if handle was freed!
		return TRUE;
	}
	return FALSE;
#endif // defined(_FORCE_LEGACY_CODE)
}


/*
 * ResetListboxExtents
 *
 * Purpose:
 *  Deletes all extents in the extent list to be used AFTER an
 *  LB_RESETCONTENT is sent to the listbox.
 *
 * Parameters:
 *  hList       HWND of the listbox.
 *
 * Return Value:
 *  none
 *
 */

void BaseListBox::ResetListboxExtents()
{
HWND hList = Handle();

    FreeListboxExtents();
    InitListboxExtents();

    SendMessage(hList, LB_SETHORIZONTALEXTENT, 0, 0L);

    //This is required to remove the scrollbar.
    SendMessage(hList, LB_DELETESTRING, 0, 0L);
    return;
}


/*
 * WAddExtentEntry
 *
 * Purpose:
 *  Facilitates handling of the horizontal listbox by keeping
 *  track of the pixel width of the longest string in the listbox.
 *  The number of pixels that the listbox scrolls is the width
 *  of the longest string.
 *
 * Parameters:
 *  hList       HWND of the listbox.
 *  psz         Pointer to string that is added.  This must be passed
 *              instead of an index into the listbox since this must
 *              be called before the string is added if the scrollbar
 *              is to be maintained properly.
 *
 * Return Value:
 *  DWORD        0 if the string added was not the longest string in
 *              the listbox and therefore did not change the visibility
 *              of the horizontal scrollbar.
 *
 *              wExtent if the added string was the longest, thus either
 *              making the scrollbar visible or changing the extent.
 *
 *              -1 on an error.
 *
 */

DWORD BaseListBox::AddExtentEntry(LPCSTR psz)
{
HWND hList = Handle();

#if defined(_FORCE_LEGACY_CODE)
    HANDLE      hMem;
    WORD        cExtentEntries;
    WORD        cExtentEntriesMax;
#else
    DWORD        cExtentEntries;
    DWORD        cExtentEntriesMax;
#endif // defined(_FORCE_LEGACY_CODE)
    WORD        *pw;       //Pointer to extent memory.
    WORD        wExtent;
    WORD        i=0;
    DWORD        iRev;

#if defined(_FORCE_LEGACY_CODE)
    hMem=GetProp(hList, (LPSTR)szXTList);
    if (hMem==NULL)
		return ((WORD)-1);

    pw=(WORD *)LocalLock(hMem);
#else
	pw = (WORD *)GetProp(hList, (LPSTR)szXTList);
#endif // defined(_FORCE_LEGACY_CODE)

    if (pw == NULL)
		return ((WORD)-1);

// Load the values and set pointer to start of list.
#if defined(_FORCE_LEGACY_CODE)
    cExtentEntries = *pw++;
    cExtentEntriesMax = *pw++;
#else
DWORD *pdwHdr = reinterpret_cast<DWORD *>(pw);

    cExtentEntries = *pdwHdr++;
    cExtentEntriesMax = *pdwHdr++;
    pw = reinterpret_cast<WORD *>(pdwHdr);
#endif // defined(_FORCE_LEGACY_CODE)

    //Reallocate if necessary.
    if (cExtentEntries == cExtentEntriesMax) {
#if defined(_FORCE_LEGACY_CODE)
        LocalUnlock(hMem);

        //This call takes care of cExtentEntriesMax
        if (!FReAllocExtentList(hMem, TRUE))
		    return ((WORD)-1);

        cExtentEntriesMax += CALLOCUNITS;

        pw=(WORD *)LocalLock(hMem);
        if (pw==NULL)
		    return ((WORD)-1);

        pw+=2;  //Skip the two counters.
#else
	DWORD *pnew = NULL;

        //This call takes care of cExtentEntriesMax
        if (!FReAllocExtentList(pdwHdr-2, cExtentEntriesMax * sizeof(WORD) + 2*sizeof(DWORD), &pnew))
		    return ((WORD)-1);
        if (pnew==NULL)
		    return ((WORD)-1);

	    SetProp(hList, (LPSTR)szXTList, (HANDLE)pnew);
        cExtentEntriesMax += CALLOCUNITS;
        pw = reinterpret_cast<WORD *>(pnew+2);  // Skip the two counters.
#endif // defined(_FORCE_LEGACY_CODE)
    }

    wExtent=WGetListboxStringExtent(hList, psz);


    /*
     * Insert the new extent into the list.  This list is just a sorted
     * list (descending) of the largest to smallest extents in the
     * listbox.  When deleting a string, we just need to look in this
     * list for it's extent and remove that entry.
     *
     * Yeah, this can be inefficient, but this is not a real case for
     * optimization.
     *
     */

    if (cExtentEntries==0)
        pw[0] = wExtent;
    else
    {
        i=IFindExtentInList(pw, wExtent, cExtentEntries);

	bool fMoved = false; 

        for (iRev=cExtentEntries/*+1*/; iRev > i; iRev--) {
            pw[iRev]=pw[iRev-1];
			fMoved = true;
		}

		if (fMoved)
			pw[i] = wExtent;
		else
			pw[i-1] = wExtent;
    }

    cExtentEntries++;

    //Save these values back.  pw must be decremented first.
#if defined(_FORCE_LEGACY_CODE)
    *(--pw)=cExtentEntriesMax;
    *(--pw)=cExtentEntries;

    LocalUnlock(hMem);
#else
	{
	DWORD *pdwHdr = reinterpret_cast<DWORD *>(pw);

	    *(--pdwHdr) = cExtentEntriesMax;
	    *(--pdwHdr) = cExtentEntries;
	}
#endif // defined(_FORCE_LEGACY_CODE)

    /*
     * Check if the one we added is now the first.  If so, then
     * we need to reset the horizontal extent.
     */

    if (i==0) {
        SendMessage(hList, LB_SETHORIZONTALEXTENT, wExtent, 0L);
        return wExtent;
    }
    return ((DWORD)0);
}


/*
 * WRemoveExtentEntry
 *
 * Purpose:
 *  Facilitates handling of the horizontal listbox by keeping
 *  track of the pixel width of the longest string in the listbox.
 *  The number of pixels that the listbox scrolls is the width
 *  of the longest string.
 *
 * Parameters:
 *  hList       HWND of the listbox.
 *  iSel        DWORD index of the string to be removed.
 *
 * Return Value:
 *  DWORD        0 if the string removed did not affect the visibilty
 *              of the horizontal scrollbar, i.e. if there still is
 *              a longer string or there is no scrollbar in the first
 *              place.
 *
 *              wExtent of the new longest string if the one removed
 *              was the longest.
 *
 *              -1 on an error.
 */

DWORD BaseListBox::RemoveExtentEntry(LPCSTR pcText)
{
HWND hList = Handle();

    WORD        *pw;       //Pointer to extent memory.
    DWORD        cExtentEntries;
    DWORD        cExtentEntriesMax;
    WORD        wExtent;
    WORD        i;
    WORD        iSave;
#if defined(_FORCE_LEGACY_CODE)
    HANDLE      hMem;

    hMem=GetProp(hList, (LPSTR)szXTList);
    if (hMem==NULL)
		return ((WORD)-1);

    pw=(WORD *)LocalLock(hMem);
#else
	pw = (WORD *)GetProp(hList, (LPSTR)szXTList);
#endif // defined(_FORCE_LEGACY_CODE)

    if (pw==NULL)
		return ((WORD)-1);

    //Load the values and set pointer to start of list.
#if defined(_FORCE_LEGACY_CODE)
    cExtentEntries = *pw++;
    cExtentEntriesMax = *pw++;
#else
DWORD *pdwHdr = reinterpret_cast<DWORD *>(pw);

    cExtentEntries = *pdwHdr++;
    cExtentEntriesMax = *pdwHdr++;
    pw = reinterpret_cast<WORD *>(pdwHdr);
#endif defined(_FORCE_LEGACY_CODE)

    if (cExtentEntries==0)
    {
#if defined(_FORCE_LEGACY_CODE)
        LocalUnlock(hMem);
#endif // defined(_FORCE_LEGACY_CODE)
		return ((WORD)-1);
    }

#if defined(_FORCE_LEGACY_CODE)
//Free up memory if necessary.  No reallocating smaller is not fatal.
    if ((cExtentEntriesMax-cExtentEntries)==CALLOCUNITS)
    {
        LocalUnlock(hMem);

        if (!FReAllocExtentList(hMem, FALSE))
		    return ((WORD)-1);

        cExtentEntriesMax -= CALLOCUNITS;
        pw=(WORD *)LocalLock(hMem);

        if (pw==NULL)
		    return ((WORD)-1);

        pw+=2;  //Skip the two counters.
    }
#endif // defined(_FORCE_LEGACY_CODE)

    wExtent=WGetListboxStringExtent(hList, pcText);

    /*
     * Find the extent in the list and remove it.  If it's the first,
     * then reset the horizontal extent to the second.
     */

    i = IFindExtentInList(pw, wExtent, cExtentEntries);
    iSave=i;

    while (i < cExtentEntries)
        pw[i++]=pw[i+1];

    cExtentEntries--;

    //Save these values back.  pw must be decremented first.
#if defined(_FORCE_LEGACY_CODE)
    *(pw-1)=cExtentEntriesMax;
    *(pw-2)=cExtentEntries;

    LocalUnlock(hMem);
#else
	{
	DWORD *pdwHdr = reinterpret_cast<DWORD *>(pw);
	
	    *(--pdwHdr) = cExtentEntriesMax;
	    *(--pdwHdr) = cExtentEntries;
	}
#endif // defined(_FORCE_LEGACY_CODE)

    if (iSave==0)
    {
        /*
         * Before we change the horizontal extent, we must make sure that
         * the origin of the listbox is visible through forcing a scroll.
         * If this is not done, and the listbox is scrolled one or
         * more pixels to the right, the scrollbar WILL NOT disappear
         * even if all remaining strings fit inside the client area
         * of the listbox.
         *
         * This is only done here since this the only case where this
         * might happen is when we change the extent.
         */
        SendMessage(hList, WM_HSCROLL, SB_TOP, MAKELONG(0, hList));
        SendMessage(hList, LB_SETHORIZONTALEXTENT, pw[0], 0L);

        return pw[0];
    }

    return ((WORD)0);
}


/*
 * FReAllocExtentList
 *
 * Purpose:
 *  Handles reallocation of the list in blocks of +/- CBALLOCUNIT
 *
 * Parameters:
 *  fGrow       BOOL if TRUE, instructs this function to allocate
 *              an additional ALLOCUNIT.
 *              If FALSE, shrinks the memory block by an ALLOCUNIT.
 *
 * Return Value:
 *  BOOL        TRUE if successfully reallocated.  FALSE otherwise.
 *
 */
#if defined(_FORCE_LEGACY_CODE)
BOOL FReAllocExtentList(HANDLE hMem, BOOL fGrow)
{
    WORD	wSize;

    /*
     * Allocate an additional 128 entries.  A 256 byte block is a
     * decent reallocation size.
     */
    wSize=LocalSize((HLOCAL)hMem);
    wSize+=(fGrow) ?  ((int)CBALLOCUNIT) : (-(int)CBALLOCUNIT);

    /*
     * This returns FALSE if the realloc was unsuccessful.  TRUE
     * otherwise because the return handle is  !=0
     *
     */
    return (BOOL)LocalReAlloc(hMem, wSize, LMEM_MOVEABLE | LMEM_ZEROINIT);
}
#else
BOOL FReAllocExtentList(DWORD *pw, DWORD wSize, DWORD **ppw)
{
    /*
     * This returns FALSE if the realloc was unsuccessful.  TRUE
     * otherwise because the return handle is  !=0
     *
     */
	*ppw = (DWORD *)realloc (pw, 2*wSize);
	return (NULL != *ppw) ? TRUE : FALSE;
}
#endif // defined(_FORCE_LEGACY_CODE)


/*
 * WGetListboxStringExtent
 *
 * Purpose:
 *  Returns the extent, in pixels, of a string that will be or is
 *  in a listbox.  The hDC of the listbox is used and an extra
 *  average character width is added to the extent to insure that
 *  a horizontal scrolling listbox that is based on this extent
 *  will scroll such that the end of the string is visible.
 *
 * Parameters:
 *  hList       HWND handle to the listbox.
 *  psz         LPSTR pointer to string in question.
 *
 * Return Value:
 *  DWORD        Extent of the string relative to listbox.
 *
 */

WORD WGetListboxStringExtent(HWND hList, LPCSTR psz)
{
    TEXTMETRIC  tm;
    HDC         hDC;
    HFONT       hFont;
    WORD        wExtent;


    /*
     * Make sure we are using the correct font.
     */
    hDC=GetDC(hList);
    hFont=(HFONT)SendMessage(hList, WM_GETFONT, 0, 0L);

    if (hFont!=NULL)
        SelectObject(hDC, hFont);

    GetTextMetrics(hDC, &tm);

    /*
     * Add one average text width to insure that we see the end of the
     * string when scrolled horizontally.
     */
SIZE sz;

	GetTextExtentPoint32(hDC, psz, lstrlen(psz), &sz);
	wExtent = (WORD)(sz.cx + tm.tmAveCharWidth);

    ReleaseDC(hList, hDC);
    return wExtent;
}


/*
 * IFindExtentInList
 *
 * Purpose:
 *  Does an binary search on the sorted extent list and returns
 *  an index to the one that matches.  If there is no match,
 *  the index gives the point where the extent entry should go.
 *
 *  Note that an altered search algorithm is used since the list
 *  is descending instead of ascending.
 *
 * Parameters:
 *  pw             DWORD * pointer to extent list.
 *  wExtent        DWORD extent to find or find an index for.
 *  cExtentEntries DWORD count of entries in list.
 *
 * Return Value:
 *  iExtent    DWORD index into lpw where wExtent exists or where
 *             it should be inserted.
 *
 */

WORD IFindExtentInList(WORD *pw, WORD wExtent, DWORD cExtentEntries)
{
    int     i=0;      //These MUST be signed!
    int     iPrev;
    int     iMin;
    int     iMax;

    //Set upper limits on search.
    iMin=0;
    iMax=cExtentEntries+1;


    do {
        iPrev=i;
        i=(iMin + iMax) >> 1;

        if (i==iPrev)
        {
            i++;
            break;
        }

        //Change the min and max depending on which way we need to look.
        if (wExtent < pw[i])   // < since list is descending. > otherwise
            iMin=i;
        else
            iMax=i;

        if (iMax==iMin)
            break;
    }
    while (wExtent != pw[i]);


    /*
     * When we get here, i is either where wExtent is or where it should
     * go--so return it.
     */
    return i;
}

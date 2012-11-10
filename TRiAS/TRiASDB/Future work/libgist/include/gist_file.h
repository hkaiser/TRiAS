// gist_file.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_file.h,v 1.10 1998/10/21 03:56:25 marcel Exp $


#ifndef GIST_FILE_H
#define GIST_FILE_H

#ifdef __GNUG__
#pragma interface "gist_file.h"
#endif

#include "gist_ext.h"	// for gist_ext_t::gist_ext_ids
#include "gist_htab.h"	// for gist_htab

class gist_file {

public:
    

    gist_file();
    ~gist_file();

    // Creates an 'empty' file (except for header info) with given name.
    // Header info contains a "magic string" and the extension ID and name as well 
    // as a pointer to the free page list (the first free page no).
    rc_t create(const char *filename, const gist_ext_t* ext);

    rc_t open(const char *filename, const gist_ext_t*& ext);
    // open this file as a Gist file for subsequent operations;
    // the extension ID is extracted from the header info and the 
    // corresponding extension returned in 'ext'

    rc_t flush(); 
    // write out all dirtied pages

    rc_t close();
    // flush and empty buffers

    int size() { return fileSize; }

    static const int invalidIdx;

    struct page_descr {
        shpid_t pageNo; // pageno on disk
	char *page; // pointer to in-mem page
	bool isDirty; // true if modified since pinned
	int pinCount; 

	page_descr() : pageNo(0), page(NULL), isDirty(false), pinCount(0) {}
    };

    // return true if no descriptor is pinned
    bool allUnpinned();

    page_descr *pinPage(shpid_t page);
    // bring the page into memory, if not already present,
    // and return its descriptor

    void unpinPage(page_descr *descr);
    // decrement the page's pincount and toss it out if = 0

    page_descr *allocPage();
    // find a fresh page on disk, reserve it, allocate a buffer
    // for it and return that buffer's descriptor

    rc_t freePage(page_descr *descr);
    // dealloc that page; the page descriptor shouldn't be used anymore

    void setDirty(page_descr *descr, bool isDirty);
    // change that page's status

    // Returns the IDs of the pages on the freelist in 'list' and the number of 
    // those pages in 'len'. 'len' must be set to the number of elements in 'list'
    // by the caller.
    rc_t freelist(shpid_t list[], int& len);

protected:

    bool isOpen; // true if file has been opened
    int fileHandle;
    shpid_t fileSize; // in pages
    gist_htab htab; // maps page no to index into buffer pool

    static const char* magic;

    struct header_info {
        char* magicStr; // should be gist_file::magic
	gist_ext_t::gist_ext_ids extId; // this file's extension ID
	shpid_t freeList; // first free page in file
	char* extName; // this file's extension name

	header_info() :
	    magicStr(NULL), extId(gist_ext_t::gist_numext), freeList(0), extName(NULL) {}
    };
    header_info header;
    rc_t _read_header();
    rc_t _write_header();

    // each file has its own buffer pool;
    // make sure the buffers are aligned on 8-byte boundaries
    page_descr descrs[GISTBUFS]; // descriptors
    void _resetDescrs();

    union {
        double d;
	char buf[GISTBUFS * SM_PAGESIZE]; // buffers
    } x;
    char *buffers;

    rc_t _write_page(shpid_t pageNo, char *page);
    rc_t _read_page(shpid_t pageNo, char *page);
    int findFreeBuffer();
    shpid_t findFreePage();
    rc_t returnPage(shpid_t page);

};

#include "gist_ext.h"

#endif

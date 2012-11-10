// gist_file.cc
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_file.cc,v 1.17 2000/03/15 00:24:25 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_file.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#include <errno.h>

#include "gist_compat.h"	// for O_BINARY
#include "gist_file.h"

const int gist_file::invalidIdx = -1;


const char* gist_file::magic = "Gist data file";


gist_file::gist_file() :
    isOpen(false), fileHandle(0), fileSize(0), htab(), header()
{
    // set up page descriptors
    buffers = x.buf;
    _resetDescrs();
}

void
gist_file::_resetDescrs()
{
    for (int i = 0; i < GISTBUFS; i++) {
        descrs[i].pageNo = 0;
        descrs[i].page = &(buffers[i * SM_PAGESIZE]);
        descrs[i].isDirty = false;
        descrs[i].pinCount = 0;
    }
}

gist_file::~gist_file()
{
    if (isOpen) close();
}

rc_t
gist_file::create(
    const char *filename,
    const gist_ext_t* ext)
{
    assert(!isOpen);
    fileHandle = ::open(filename, O_RDWR | O_BINARY);
    if (fileHandle >= 0) { // filename exists
        ::close(fileHandle);
        return (eFILEERROR);
    }

    fileHandle = ::open(filename, O_BINARY | O_RDWR | O_CREAT | O_TRUNC,
        S_IREAD | S_IWRITE);

    if (fileHandle < 0) {
        return (fileHandle);  // error: couldn't create
    }

    isOpen = true;

    // page 0 contains header info: magic string,
    // extension ID and name
    header.magicStr = strdup(magic);
    header.extId = ext->myId;
    header.freeList = 0;
    header.extName = strdup(ext->myName);
    W_DO(_write_header());
    fileSize = 1;

    // re-initialize the page descriptors to get rid off remnants from 
    // prior index file
    _resetDescrs();
    htab.reset();

    return(RCOK);
}

rc_t
gist_file::open(
    const char *filename,
    const gist_ext_t*& ext)
{
    if (isOpen) {
	return (eFILEERROR);
    }

    fileHandle = ::open(filename, O_RDWR | O_BINARY);

    if (fileHandle < 0) {
	cerr << "couldn't open " << filename << endl;
        return (eFILEERROR); // error: couldn't open
    }

    W_DO(_read_header());

    // Verify that everything is as expected
    if (strcmp(header.magicStr, magic) != 0) {
        ::close(fileHandle);
	cerr << "magic words not found in " << filename << endl;
        return(eFILEERROR); // error: magic words not found
    }
    // verify that the ext ID still 'means' the same extension
    if (strcmp(header.extName, gist_ext_t::gist_ext_list[header.extId]->myName) != 0) {
	cerr << "extension name changed in " << filename << endl;
        ::close(fileHandle);
	return(eFILEERROR);
    }

    // success!
    isOpen = true;
    fileSize = (lseek(fileHandle, 0, SEEK_END) + 1) / SM_PAGESIZE;
        // + 1: 0-based offset
    ext = gist_ext_t::gist_ext_list[header.extId];

    // re-initialize the page descriptors to get rid off remnants from 
    // prior index file
    _resetDescrs();
    htab.reset();

    return(RCOK);
}

rc_t
gist_file::flush()
{
    if (!isOpen) {
        return (eFILEERROR);
    }

    W_DO(_write_header());
    for (int i = 0; i < GISTBUFS; i++) {
        if (descrs[i].isDirty) {
	    // write out dirty buffer
	    W_DO(_write_page(descrs[i].pageNo, descrs[i].page));
	    descrs[i].isDirty = false;
	}
    }
    return RCOK;
}

rc_t
gist_file::close()
{
    W_DO(flush());
    isOpen = false;
    // strdup() uses malloc()
    free(header.magicStr);
    free(header.extName);

	// VCPORT_B
	// Just in case you free or delete again
	// Under other platforms, this is unnecessary.
#ifdef WIN32
	header.magicStr = NULL;
	header.extName = NULL;
#endif
	// VCPORT_E

    return(::close(fileHandle));
}

rc_t
gist_file::freelist(shpid_t list[], int& len)
{
    int freeCnt = 0;
    shpid_t freePage = header.freeList;
    while (freePage != 0) {
	if (freeCnt < len) {
	    list[freeCnt] = freePage;
	}
	freeCnt++;
	char buf[SM_PAGESIZE];
	W_DO(_read_page(freePage, buf));
	(void) memcpy(&freePage, buf, sizeof(freePage));
    }
    len = freeCnt;
    return RCOK;
}

int
gist_file::findFreeBuffer()
{
    int i;

    // free buffers have pin count = 0 (first look for virgin buffers)
    for (i = 0; i < GISTBUFS; i++) {
        if (descrs[i].pinCount == 0 && descrs[i].pageNo == 0) {
	    return i;
	}
    }
    for (i = 0; i < GISTBUFS; i++) {
        if (descrs[i].pinCount == 0) {
	    return i;
	}
    }
    return invalidIdx;
}

rc_t
gist_file::_write_page(shpid_t pageNo, char *page)
{
    int status = lseek(fileHandle, pageNo * SM_PAGESIZE, SEEK_SET);
    if (status < 0) return (eFILEERROR);
    status = write(fileHandle, page, SM_PAGESIZE);
    if (status < 0) return (eFILEERROR);
    return RCOK;
}

rc_t
gist_file::_read_page(shpid_t pageNo, char *page)
{
    int status = lseek(fileHandle, pageNo * SM_PAGESIZE, SEEK_SET);
    if (status < 0) {
	cerr << "couldn't lseek()" << endl;
        return (eFILEERROR);
    }
    status = read(fileHandle, page, SM_PAGESIZE);
    if (status < 0) {
	cerr << "couldn't read()" << endl;
        return (eFILEERROR);
    }
    return RCOK;
}

rc_t
gist_file::_write_header()
{
    char page[SM_PAGESIZE];
    (void) memset(page, 0, sizeof(page));
    char* pos = page;
    (void) memcpy(pos, header.magicStr, strlen(header.magicStr) + 1);
    pos += strlen(header.magicStr) + 1;
    (void) memcpy(pos, (void *) &header.extId, sizeof(header.extId));
    pos += sizeof(header.extId);
    (void) memcpy(pos, (void *) &header.freeList, sizeof(header.freeList));
    pos += sizeof(header.freeList);
    (void) memcpy(pos, header.extName, strlen(header.extName) + 1);
    return _write_page(0, page);
}

rc_t
gist_file::_read_header()
{
    char page[SM_PAGESIZE];
    W_DO(_read_page(0, page));

    delete [] header.magicStr;
    delete [] header.extName;

    char* pos = page;
    header.magicStr = strdup(pos);
    pos += strlen(header.magicStr) + 1;
    (void ) memcpy((void *) &header.extId, pos, sizeof(header.extId));
    pos += sizeof(header.extId);
    (void ) memcpy((void *) &header.freeList, pos, sizeof(header.freeList));
    pos += sizeof(header.freeList);
    header.extName = strdup(pos);
    return RCOK;
}

bool
gist_file::allUnpinned()
{
    for (int i = 0; i < GISTBUFS; i++) {
        if (descrs[i].pinCount > 0) return false;
    }
    return true;
}

gist_file::page_descr *
gist_file::pinPage(shpid_t page)
{
    page_descr *descr;

    if (page >= fileSize) {
        return (NULL);
    }
    int index = htab[page];
    if (index == invalidIdx) {
        // this is not in the buffer pool; load it
	index = findFreeBuffer();
	if (index == invalidIdx) return (NULL);

	// prepare the descr
	descr = &descrs[index];
	// write out page if dirty
	if (descr->isDirty) { 
	    if (_write_page(descr->pageNo, descr->page) != RCOK) {
	        return NULL;
	    }
	}
	htab.remove(descr->pageNo); // mapping is now obsolete
	descr->pageNo = page;
	descr->isDirty = false;
	descr->pinCount = 1;

	// load the page
	if (_read_page(descr->pageNo, descr->page) != RCOK) {
	    return NULL;
	}
	// record the mapping
	htab.add(page, index);
    } else {
        descr = &descrs[index];
	descr->pinCount++;
    }
    return descr;
}

void
gist_file::unpinPage(page_descr *descr)
{
    assert(descr != NULL);
    descr->pinCount--;
}

void
gist_file::setDirty(page_descr *descr, bool isDirty)
{
    assert(descr != NULL);
    descr->isDirty = isDirty;
}

gist_file::page_descr *
gist_file::allocPage()
{
    shpid_t page;
    int index;
    page_descr *descr;

    if (!isOpen) return (NULL);
    page = findFreePage();
    index = findFreeBuffer();
    if (index == invalidIdx) return (NULL);
    descr = &descrs[index];
    // write out page if dirty
    if (descr->isDirty) { 
	if (_write_page(descr->pageNo, descr->page) != RCOK) {
	    return NULL;
	}
    }
    htab.remove(descr->pageNo); // mapping is now obsolete
    // set up descriptor
    descr->pageNo = page;
    descr->isDirty = false;
    descr->pinCount = 1;
    htab.add(page, index); // record new mapping
    (void) memset(descr->page, 0, SM_PAGESIZE); // create blank page
    if (page == fileSize) {
	// if the page was reclaimed from the free list, we don't need
	// to extend the file!
	fileSize++;
    }
    assert(page < fileSize);

    return (descr);
}

rc_t
gist_file::freePage(page_descr *descr)
{
    W_DO(returnPage(descr->pageNo));

    descr->isDirty = false;
    descr->pinCount = 0;
    // don't reduce the fileSize;
    // it specifies the extent of the file, not the # of used pages
    return RCOK;
}


shpid_t 
gist_file::findFreePage()
{
    assert(isOpen);

    if (header.freeList != 0) {
	// Reclaim the first page on the free page list,
	// it contains a pointer to the next free page.
	char buf[SM_PAGESIZE];
	shpid_t res = header.freeList;
	W_DO(_read_page(header.freeList, buf));
	(void) memcpy(&header.freeList, buf, sizeof(header.freeList));
	//W_DO(_write_header());
	return res;
    } else {
	// add a page to the end of the file
	return fileSize;
    }
}

rc_t
gist_file::returnPage(shpid_t page)
{
    char buf[SM_PAGESIZE];
//    shpid_t temp;

    // error checking: page must be valid and file must be open
    assert(isOpen);

    // Insert page at head of freelist 
    (void) memset(buf, 0, sizeof(buf));
    (void) memcpy(buf, &header.freeList, sizeof(header.freeList));
    W_DO(_write_page(page, buf));
    header.freeList = page;
    //W_DO(_write_header());

    return RCOK;
}

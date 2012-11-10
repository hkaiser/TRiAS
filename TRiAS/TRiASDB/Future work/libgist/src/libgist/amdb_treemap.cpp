// amdb_treemap.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_treemap.cc,v 1.2 2000/03/15 00:24:22 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_treemap.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786)
#endif
// VCPORT_E

#include "amdb_treemap.h"

// VCPORT_B
#ifdef WIN32

#include <fstream>
#include <iostream>

using namespace std;

#else

#include "fstream.h"

#endif
// VCPORT_E

/////////////////////////////////////////////////////////////////////////
// amdb_treemap - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

amdb_treemap::amdb_treemap() : pageMap(), itemMap()
{
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::~amdb_treemap - destructor
//
// Description:
/////////////////////////////////////////////////////////////////////////

amdb_treemap::~amdb_treemap()
{
    clear();
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::addPage - add PageInfo
//
// Description:
//	- called after items have been recorded in itemMap: offset of 
//	  first item on the page is itemMap.size() minus the number of 
//	  page entries
///////////////////////////////////////////////////////////////////////////////

void
amdb_treemap::addPage(
    shpid_t pgno,
    unsigned cnt,
    int level,
    int minPredLen,
    float avgPredLen,
    int maxPredLen,
    float util)
{
    PageInfo* pageInfo = new PageInfo(itemMap.size() - cnt, cnt, level, minPredLen,
        avgPredLen, maxPredLen, util);
    pageMap[pgno] = (void *) pageInfo;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::addTreeItem - record indidiv. item in tree
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_treemap::addTreeItem(
    shpid_t page,
    int idx,
    smsize_t size)
{
    RecInfo* info = new RecInfo();
    itemMap.push_back((void *) info);
    info->loc.treeLoc.page = page;
    info->loc.treeLoc.slot = idx;
    info->size = size;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::addFileItem - record indidiv. item in file
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_treemap::addFileItem(
    streampos pos,
    smsize_t size)
{
    RecInfo* info = new RecInfo();
    itemMap.push_back((void *) info);
    info->loc.fileLoc = pos;
    info->size = size;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::write - write treemap to output stream
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_treemap::write(
    ostream& s,
    bool ascii)
{
    // save pageMap
    PageMap::size_type pageMapSize = pageMap.size();
    s.write((char *) &pageMapSize, sizeof(pageMapSize));
    PageMap::iterator pmit;
    for (pmit = pageMap.begin(); pmit != pageMap.end(); pmit++) {
	shpid_t pageno = (shpid_t) (*pmit).first;
	PageInfo* info = (PageInfo *) (*pmit).second;
	s.write((char *) &pageno, sizeof(pageno));
	s.write((char *) info, sizeof(*info));
    }

    // save itemMap
    ItemMap::size_type itemMapSize = itemMap.size();
    s.write((char *) &itemMapSize, sizeof(itemMapSize));
    ItemMap::iterator imit;
    for (imit = itemMap.begin(); imit != itemMap.end(); imit++) {
        s.write((char *) *imit, sizeof(RecInfo));
    }

    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::read - read treemap from input stream
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_treemap::read(
    istream& s)
{
    // read pageMap
    PageMap::size_type pageMapSize;
    s.read((char *) &pageMapSize, sizeof(pageMapSize));
    int i;
    for (i = 0; i < pageMapSize; i++) {
        shpid_t pageno;
	s.read((char *) &pageno, sizeof(pageno));
	PageInfo* info = new PageInfo();
	s.read((char *) info, sizeof(*info));
	pageMap[pageno] = (void *) info;
    }

    // read itemMap
    ItemMap::size_type itemMapSize;
    s.read((char *) &itemMapSize, sizeof(itemMapSize));
    for (i = 0; i < itemMapSize; i++) {
	RecInfo* info = new RecInfo();
	s.read((char *) info, sizeof(*info));
	itemMap.push_back((void *) info);
    }
    
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_treemap::clear - reset treemap state
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_treemap::clear()
{
    cout << "itemmap::clear() " << endl;

    PageMap::iterator pmit;
    for (pmit = pageMap.begin(); pmit != pageMap.end(); pmit++) {
	delete (PageInfo *) (*pmit).second;
    }
    pageMap.erase(pageMap.begin(), pageMap.end());
    //cout << "erase pageMap" << endl;

    ItemMap::iterator imit;
    for (imit = itemMap.begin(); imit != itemMap.end(); imit++) {
        delete (RecInfo *) *imit;
    }
    itemMap.erase(itemMap.begin(), itemMap.end());
    //cout << "erase itemMap" << endl;
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::size - return size of entry on 'page' in 'slot'
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

smsize_t
amdb_treemap::size(
    shpid_t page,
    int slot) const
{
    PageInfo *info =  (PageInfo *) (*pageMap.find(page)).second;
    ItemId itemno = info->itemOffset + slot;
    return ((RecInfo *) (itemMap[itemno]))->size;
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::itemCnt - return number of slots on page
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

int
amdb_treemap::itemCnt(
    shpid_t page) const
{
    PageInfo* info = (PageInfo *) (*pageMap.find(page)).second;
    assert(info != NULL);
    return (info->itemCnt);
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::util - return utilization of page
//
// Description:
/////////////////////////////////////////////////////////////////////////

float
amdb_treemap::util(
    shpid_t page) const
{
    PageInfo* info = (PageInfo *) (*pageMap.find(page)).second;
    assert(info != NULL);
    return (info->util);
}

/////////////////////////////////////////////////////////////////////////
// amdb_treemap::itemOffset - return item number of first slot on page
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

ItemId
amdb_treemap::itemOffset(
    shpid_t page) const
{
    PageInfo* info = (PageInfo *) (*pageMap.find(page)).second;
    assert(info != NULL);
    return (info->itemOffset);
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::pageInfo - return PageInfo of given page
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

const amdb_treemap::PageInfo*
amdb_treemap::pageInfo(
    shpid_t pageno) const
{
    return ((PageInfo *) (*pageMap.find(pageno)).second);
}


/////////////////////////////////////////////////////////////////////////
// amdb_treemap::itemInfo - return RecInfo of given item ID
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

const amdb_treemap::RecInfo*
amdb_treemap::itemInfo(
    ItemId id) const
{
    return ((RecInfo *) itemMap[id]);
}

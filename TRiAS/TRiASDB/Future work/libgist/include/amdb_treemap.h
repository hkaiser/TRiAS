// amdb_treemap.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_treemap.h,v 1.2 2000/03/10 01:39:00 mashah Exp $

#ifndef AMDB_TREEMAP_H
#define AMDB_TREEMAP_H

#ifdef __GNUG__
#pragma interface "amdb_treemap.h"
#endif

#include "gist_defs.h"		// for smsize_t
#include "amdb_defs.h"		// for Vector

// VCPORT_B
#ifndef WIN32
class ostream;
class istream;
#endif
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// amdb_treemap - record per-item location information
//
// Description:
//	- for tree-resident items, records their page location and 
//	  size as well as the item offset and number of items for 
//	  each page
//	- for file-resident items, records their size and file position
///////////////////////////////////////////////////////////////////////////////

class amdb_treemap
{

public:

    // per-page info (only for tree itemmaps)
    struct PageInfo {
        ItemId itemOffset; // item number of first item on page
	int itemCnt; // # of items on page
	int level; // level in tree (leaf level = 1)
        int minPredLen; // size of smallest pred (in bytes)
	float avgPredLen; // avg pred size
	int maxPredLen; // size of largest pred
	float util; // percentage of total page capacity (gist_p::data_sz)

	PageInfo() : itemOffset(0), itemCnt(0) {}
	PageInfo(ItemId offset, int cnt, int level, int minPredLen,
            float avgPredLen, int maxPredLen, float util) :
	    itemOffset(offset), itemCnt(cnt), level(level), minPredLen(minPredLen),
	    avgPredLen(avgPredLen), maxPredLen(maxPredLen), util(util) {}
    };
    //typedef map<shpid_t, PageInfo*> PageMap;
    typedef Map PageMap;
    PageMap pageMap;

    // per-record info (both tree and file itemmaps)
    struct RecInfo { // record info

		// VCPORT_B
		// Since streampos has uses a default 
// #ifdef WIN32
		struct loc_struct {
			Rid treeLoc;
			streampos fileLoc;
		} loc;
// #else
//		union {
//		    Rid treeLoc;
//			streampos fileLoc; // pos of item in file
//		} loc;
// #endif
		// VCPORT_E

        smsize_t size;
    };
    //typedef vector<RecInfo *> ItemMap;
    typedef Vector ItemMap;
    ItemMap itemMap;

    // record a leaf page
    void addPage(
        shpid_t pgno,
	unsigned cnt,
	int level,
	int minPredLen,
	float avgPredLen,
	int maxPredLen,
	float util);

    // record an item
    void addTreeItem(
        shpid_t page,
	int idx,
	smsize_t size);
    void addFileItem(
        streampos pos,
	smsize_t size);

    // binary data, to and from files
    rc_t write(ostream& s, bool ascii);
    rc_t read(istream& s);

    void clear(); // clears maps

    amdb_treemap();
    ~amdb_treemap();

    // some shortcuts
    smsize_t size(shpid_t page, int slot) const; // RecInfo.size
    int itemCnt(shpid_t page) const; // PageInfo.itemCnt
    float util(shpid_t page) const; // PageInfo.util
    ItemId itemOffset(shpid_t page) const; // PageInfo.itemOffset
    int nodeCnt() const { return(pageMap.size()); }
    const PageInfo* pageInfo(shpid_t pageno) const;
    const RecInfo* itemInfo(ItemId id) const;

};

#endif

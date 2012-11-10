// amdb_itemset.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_itemset.cc,v 1.2 2000/03/15 00:24:20 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_itemset.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786)
#endif
// VCPORT_E

// VCPORT_B
#ifdef HAVE_VALUES_H
#include <values.h>
#endif
// VCPORT_E

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "amdb_itemset.h"
#include "amdb_treemap.h"

// STL
// VCPORT_B
#ifdef WIN32

#include <vector>
#include <algorithm>

#else

#include <vector.h>
#include <algo.h>

#endif
// VCPORT E

/////////////////////////////////////////////////////////////////////////
// amdb_itemset::pageItems - initialize with item IDs on page
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

// VCPORT_B
// Changed map to tmap ... VC++ thinks you are using map template.
// VCPORT_E
void
amdb_itemset::pageItems(
    const amdb_treemap& tmap,
    shpid_t pgno)
{
    ItemId id, start = tmap.itemOffset(pgno);
    int cnt = tmap.itemCnt(pgno);
    for (id = start; id < start + cnt; id++) {
        itemIds.push_back(id);
    }
    // this needs to be sorted for intersection to work
    sort(itemIds.begin(), itemIds.end()); 
}


/////////////////////////////////////////////////////////////////////////
// amdb_itemset::splitItemSets - 
// 	initialize itemsets for left and right page of split
//
// Description:
/////////////////////////////////////////////////////////////////////////

// VCPORT_B
// Changed map to tmap ... VC++ thinks you are using map template.
// VCPORT_E

void
amdb_itemset::splitItemSets(
    shpid_t pgno,
    const amdb_treemap& tmap,
    int rightEntries[],
    int numRight,
    amdb_itemset& leftSet,
    amdb_itemset& rightSet)
{
    ItemId start = tmap.itemOffset(pgno);
    int cnt = tmap.itemCnt(pgno);
    int i, slot;
    for (slot = 0, i = 0; slot < cnt; slot++) {
	if (i < numRight && rightEntries[i] == slot) {
	    rightSet.itemIds.push_back(slot + start);
	    i++;
	} else {
	    leftSet.itemIds.push_back(slot + start);
	}
    }

    // these need to be sorted for intersection to work
    sort(leftSet.itemIds.begin(), leftSet.itemIds.end()); 
    sort(rightSet.itemIds.begin(), rightSet.itemIds.end()); 
}


/////////////////////////////////////////////////////////////////////////
// amdb_itemset::intersection - 
// 	initialize with intersection of itemset and result set;
//
// Description:
// 	- return true if intersection is non-empty
//
// Return Values:
//      true if itemset and result set intersect
/////////////////////////////////////////////////////////////////////////

bool
amdb_itemset::intersection(
    const amdb_itemset& itemSet,
    const ItemId* resultSet,
    int resultSetSize)
{
    back_insert_iterator<ItemIdVect> it(itemIds);

    itemIds.erase(itemIds.begin(), itemIds.end());
    set_intersection(itemSet.itemIds.begin(), itemSet.itemIds.end(),
        resultSet, resultSet + resultSetSize, it);
    return(itemIds.size() != 0);
}

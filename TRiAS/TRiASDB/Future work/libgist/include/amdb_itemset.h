// amdb_itemset.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_itemset.h,v 1.1 1998/12/08 02:46:18 marcel Exp $

#ifndef AMDB_PROFILE_H
#define AMDB_PROFILE_H

// the following 3 lines somehow make the vector<int> '=' operator go away
//#ifdef __GNUG__
//#pragma interface "amdb_itemset.h"
//#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t
#include "amdb_clustering.h"	// for ResultSet

/*
 * amdb_itemset:
 *
 */
class amdb_treemap;

class amdb_itemset
{

public:

    // initialize with item IDs on page
    void pageItems(
        const amdb_treemap& map,
	shpid_t pgno);

    // initialize itemsets for left and right page of split
    static void splitItemSets(
        shpid_t pgno,
	const amdb_treemap& map,
	int rightEntries[],
	int numRight,
	amdb_itemset& leftSet,
	amdb_itemset& rightSet);

    // initialize with intersection of itemset and result set;
    // return true if intersection is non-empty
    bool intersection(
        const amdb_itemset& itemSet,
	const ItemId* resultSet,
	int resultSetSize);

    // need this to be vector<int>, not vector<void *>, for set_intersection()
    // to work
    typedef vector<ItemId> ItemIdVect;
    //typedef Vector ItemIdVect;

    ItemIdVect itemIds;

};

#endif

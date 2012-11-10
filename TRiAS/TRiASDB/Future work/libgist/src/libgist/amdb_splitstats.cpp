// amdb_splitstats.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_splitstats.cc,v 1.7 2000/03/15 00:24:21 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_splitstats.h"
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
#include "amdb_splitstats.h"
#include "amdb_clustering.h"

#include <assert.h>
#include "gist.h"
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_ext.h"
#include "amdb_itemset.h"
#include "amdb_treemap.h"
#include "amdb_wkldprofile.h"

// STL
// VCPORT_B
#ifdef WIN32
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;
#else
#include <vector.h>
#include <algo.h>
#include <fstream.h>
#endif
// VCPORT_E

/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::amdb_splitstats - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

amdb_splitstats::amdb_splitstats() : splitStats()
{
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::clear - reset state
//
// Description:
// 	- don't deallocate anything, we might still need it for 
//	  subsequent read() calls
/////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::clear()
{
    SplitStatsMap::iterator ssit;
    for (ssit = splitStats.begin(); ssit != splitStats.end(); ssit++) {
        SplitStats* stats = (SplitStats *) (*ssit).second;
	shpid_t pageno = (shpid_t) (*ssit).first;
	//cout << "page " << pageno << " " << stats << endl;
	delete stats;
    }
    splitStats.erase(splitStats.begin(), splitStats.end());
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::~amdb_splitstats - destructor
//
// Description:
/////////////////////////////////////////////////////////////////////////

amdb_splitstats::~amdb_splitstats()
{
    cout << "~amdb_splitstats()" << endl;

    clear();
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::write - write to output stream
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t 
amdb_splitstats::write(
    ostream& s,
    bool ascii)
{
    cout << "amdb_splitstats::write()" << endl;

    if (!ascii) {
      // save splitStats
      SplitStatsMap::size_type splitStatsSize = splitStats.size();
      s.write((char *) &splitStatsSize, sizeof(splitStatsSize));
      SplitStatsMap::iterator sit;
      for (sit = splitStats.begin(); sit != splitStats.end(); sit++) {
	shpid_t pageno = (shpid_t) (*sit).first;
	SplitStats* stats = (SplitStats *) (*sit).second;
	s.write((char *) &pageno, sizeof(pageno));
	stats->actualSplit.write(s, ascii);
	stats->optSplit.write(s, ascii);
	
	// don't write out actual- and optSplit again
	s.write((char *) &stats->preIos,
		sizeof(*stats) - ((char *) &stats->preIos - (char *) stats));
      }
      
      // save avgStats
      s.write((char *) &avgStats, sizeof(avgStats));
      
      // check for errors
      if (!s) return(eFILEERROR);
    }
    else {
      // save splitStats
      SplitStatsMap::size_type splitStatsSize = splitStats.size();
      s << splitStatsSize;
      SplitStatsMap::iterator sit;
      for (sit = splitStats.begin(); sit != splitStats.end(); sit++) {
	shpid_t pageno = (shpid_t) (*sit).first;
	SplitStats* stats = (SplitStats *) (*sit).second;
	s << pageno;
	stats->actualSplit.write(s, ascii);
	stats->optSplit.write(s, ascii);
	
	// don't write out actual- and optSplit again
	s << stats->preIos;
		
      }
      
      // save avgStats
      //s << avgStats;
      
      // check for errors
      if (!s) return(eFILEERROR);
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::read - read binary profile from input stream
//
// Description:
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_splitstats::read(
    istream& s)
{
    cout << "amdb_splitstats::read()" << endl;

    clear(); // delete current data, if there is any 

    // read splitStats
    SplitStatsMap::size_type splitStatsSize;
    s.read((char *) &splitStatsSize, sizeof(splitStatsSize));
    int i;
    for (i = 0; i < splitStatsSize; i++) {
	shpid_t pageno;
	SplitStats* stats = new SplitStats();
	s.read((char *) &pageno, sizeof(pageno));
	stats->actualSplit.read(s);
	stats->optSplit.read(s);

	// don't overwrite actual- and optSplit
	s.read((char *) &stats->preIos,
	    sizeof(*stats) - ((char *) &stats->preIos - (char *) stats));
	splitStats[pageno] = (void *) stats;
    }

    // read avgStats
    s.read((char *) &avgStats, sizeof(avgStats));

    // check for errors
    if (!s) {
        return(eFILEERROR);
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::evalSplit - compute SplitStats of single split
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_splitstats::evalSplit(
    gist& tree, // in: calling tree
    amdb_wkldprofile& profile, // in 
    const amdb_treemap& tmap, // in
    const Vector& queryStructs, // in: vector<gist_query_t *>
    shpid_t leaf, // in: node to evaluate
    int rightEntries[], // in: slot indices of entries for right node
    int numRight,  // in: number of entries in array
    vec_t& leftBp, // in: BP of left node
    vec_t& rightBp) // in: BP of right node
{
    sort(rightEntries, rightEntries + numRight); // we need this sorted
    profile.setTreeMap(&tmap); // make sure valid map is set
    gist_ext_t* ext = tree.extension();
    amdb_ext_t* amdbext = amdb_ext_t::extension(ext);

    SplitStats* stats = new SplitStats();
    // set actualSplit
    _splitInfoInit(stats->actualSplit, leaf, tmap, rightEntries, numRight, leftBp,
        rightBp);

    // for opt split, use the same balance we achieved with the pickSplit()
    // extension function
    double balance = (double) stats->actualSplit.leftData /
        (double) (stats->actualSplit.leftData + stats->actualSplit.rightData);
    // hmetis' ubfactor param specifies by how much the larger partition exceeds
    // 50% of the combined size, specified in percentage points (if the  split is 70/30,
    // ubfactor is 20)
    if (balance < 0.5) {
        balance = 0.5 - balance;
    } else {
        balance = balance - 0.5;
    }
    int ubfactor = (int) floor(balance * 100.0);
    if (ubfactor <= 0) {
        ubfactor = 1;
    }
    if (ubfactor >= 49) {
        ubfactor = 49;
    }

    int optRightEntries[gist_p::max_scnt];
    int numOptRight;
    gist::AlignedPred x, y;
    vec_t optLeftBp(x.pred, gist_p::max_tup_sz);
    vec_t optRightBp(x.pred, gist_p::max_tup_sz);
    W_DO(optSplit(tree, profile, tmap, leaf, ubfactor, optRightEntries,
        numOptRight, optLeftBp, optRightBp));
    _splitInfoInit(stats->optSplit, leaf, tmap, optRightEntries, numOptRight, optLeftBp,
        optRightBp);

    // add computed stats to stats map
    splitStats[leaf] = (void *) stats;

    // construct item sets for the nodes we want to look at (pre- and post-split)
    amdb_itemset preSplitContents; // in terms of item numbers of targetTree (in targetMap)
    preSplitContents.pageItems(tmap, leaf);
    amdb_itemset actualLeftContents, actualRightContents;
    amdb_itemset::splitItemSets(leaf, tmap, rightEntries, numRight, actualLeftContents,
        actualRightContents);
    amdb_itemset optLeftContents, optRightContents;
    amdb_itemset::splitItemSets(leaf, tmap, optRightEntries, numOptRight, optLeftContents,
        optRightContents);

    // go through queries and compare their result sets
    // with the pre- and post-split nodes;
    // also compare query predicate with BPs (when calling amdbext->consistent(), we always
    // set level = 2, because the computed BPs would be stored at level 2)
    int i;
    amdb_wkldprofile::QueryVect::const_iterator qit;
    for (qit = profile.queries.begin(), i = 0; qit != profile.queries.end();
        qit++, i++) {

	const amdb_wkldprofile::Query* query =
	    (amdb_wkldprofile::Query const *) *qit;
	ItemId* resSet = query->resultSet;
	int resSetSize = query->resultSetSize;
	amdb_itemset intersection;

        if (intersection.intersection(preSplitContents, resSet, resSetSize)) {
	    // query accesses original node, now check if it accesses
	    // any of the post-split left and right nodes

	    // XXX debug 
	    //copy(intersection.begin(), intersection.end(),
	        //ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;

	    //cout << " " << i;
	    stats->preIos++;

	    if (intersection.intersection(actualLeftContents, resSet, resSetSize)) {
	        stats->actualLeftIos++;
	    } else {
	        // check if query accesses left node anyway (empty access)
		if (amdbext->consistent(ext, (gist_query_t*) queryStructs[i], leftBp, 2)) {
		    stats->actualExcCovLoss++;
		}
	    }
	    // XXX debug 
	    //copy(intersection.begin(), intersection.end(),
	        //ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;

	    if (intersection.intersection(actualRightContents, resSet, resSetSize)) {
	        stats->actualRightIos++;
	    } else {
	        // check if query accesses left node anyway (empty access)
		if (amdbext->consistent(ext, (gist_query_t*) queryStructs[i], rightBp, 2)) {
		    stats->actualExcCovLoss++;
		}
	    }
	    // XXX debug 
	    //copy(intersection.begin(), intersection.end(),
	        //ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;

	    if (intersection.intersection(optLeftContents, resSet, resSetSize)) {
	        stats->optLeftIos++;
	    }
	    // XXX debug 
	    //copy(intersection.begin(), intersection.end(),
	        //ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;

	    if (intersection.intersection(optRightContents, resSet, resSetSize)) {
	        stats->optRightIos++;
	    }
	    // XXX debug 
	    //copy(intersection.begin(), intersection.end(),
	        //ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;

	} else {
	    // query doesn't retrieve items on original node, now check if it
	    // accesses any of the nodes anyway

	    // check if query accesses leaf anyway (empty access)
	    gist::AlignedPred z;
	    vec_t bp(z.pred, gist_p::max_tup_sz);
	    tree.getBp(leaf, bp);
	    bool preConsistent = false; // XXX debug
	    if (amdbext->consistent(ext, (gist_query_t*) queryStructs[i], bp, 2)) {
	        stats->preExcCovLoss++;
		preConsistent = true;
	    }
	    if (amdbext->consistent(ext, (gist_query_t*) queryStructs[i], leftBp, 2)) {
		stats->actualExcCovLoss++;
		assert(preConsistent); // XXX debug: leftBp shouldn't be bigger than 'bp'
	    }
	    if (amdbext->consistent(ext, (gist_query_t*) queryStructs[i], rightBp, 2)) {
		stats->actualExcCovLoss++;
		assert(preConsistent); // XXX debug
	    }
	}
    }
    cout << endl;

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::initSplitInfo - set SplitInfo data
//
// Description:
//	- make copies of rightEntries, left- and rightBp
//	- can't be done in SplitInfo member function, because we need
//	  the optTree item map to compute left- and rightData
/////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::_splitInfoInit(
    SplitInfo& info, // out
    shpid_t page, // in
    const amdb_treemap& tmap, // in
    int rightEntries[], // in
    int numRight, // in
    const vec_t& leftBp, // in
    const vec_t& rightBp) // in
{

    info.rightEntries = new int[numRight];
    (void) memcpy((void *) info.rightEntries, rightEntries, sizeof(int) * numRight);
    info.numRight = numRight;
    info.leftBp = new char[leftBp.len(0)];
    (void) memcpy((void *) info.leftBp, leftBp.ptr(0), leftBp.len(0));
    info.leftLen = leftBp.len(0);
    info.rightBp = new char[rightBp.len(0)];
    (void) memcpy((void *) info.rightBp, rightBp.ptr(0), rightBp.len(0));
    info.rightLen = rightBp.len(0);

    info.leftData = info.rightData = 0;
    int itemCnt = tmap.itemCnt(page);
    int i, j = 0;
    for (i = 0; i < itemCnt; i++) {
        if (j < info.numRight && i == rightEntries[j]) {
	    info.rightData += tmap.size(page, i);
	    j++;
	} else {
	    info.leftData += tmap.size(page, i);
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::optSplit - produce 'optimal' split
//
// Description:
//	- 'optimal' split: derived by hypergraph partitioning
//	  of result sets projected onto node
//	- projection doesn't contain queries that don't retrieve anything from
//	  node or only retrieved single item
//	- returns sorted array containing the slot indices of items
//	  to be moved to the right sibling
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_splitstats::optSplit(
    gist& tree, // in
    const amdb_wkldprofile& profile, // in
    const amdb_treemap& tmap, // in
    shpid_t leaf, // in: leaf to be split
    int ubfactor, // in: hmetis balance parameter
    int rightEntries[], // out: slot indices of entries for right sib
    int& numRight,  // out
    vec_t& leftBp, // out
    vec_t& rightBp) // out
{
    // project the query result sets onto items contained in node
    amdb_clustering::ResultSet* projectedSets =
        new amdb_clustering::ResultSet[profile.queries.size()];
	// alloc. max number of result sets, we might end up with fewer
    int numProjectedSets;

    // project translated query result sets onto leaf (translate item numbers
    // in result sets in the process)
    profile.projectToNode(leaf, projectedSets, numProjectedSets);

    // produce bisection (clustering sorted in clusterNo)
    amdb_clustering::Clustering clustering;
    int numClusters;
    int numRetrieved;
    W_DO(amdb_clustering::optClustering(projectedSets, numProjectedSets, 0.5, 2, 10,
        ubfactor, tmap, clustering, numClusters, numRetrieved));
	// numClusters = 2: we want to split it in 2 parts
    clustering.sortClusterNo();

    // fill rightEntries with slot indices of cluster 1
    int pageOffset = tmap.itemOffset(leaf);
    int itemCnt = tmap.itemCnt(leaf);
    numRight = 0;
    amdb_clustering::ClusterInfoVect::iterator cit;
    for (cit = clustering.info.begin(); cit != clustering.info.end(); cit++) {
        if (cit->clusterNo == 1) {
	    rightEntries[numRight] = cit->itemNo - pageOffset;
	    assert(rightEntries[numRight] < itemCnt); // sanity check
	    numRight++;
	}
    }
    sort(rightEntries, rightEntries + numRight);

    // construct left and right page for BP computation
    gist_p leftPg, rightPg;
    tree.splitNode(leaf, leftPg, rightPg, rightEntries, numRight);
    gist_ext_t* ext = tree.extension();
    vec_t dummyPred; // don't have one, either
    bool bpChanged;
    ext->unionBp(leftPg, leftBp, false, dummyPred, dummyPred, bpChanged);
    ext->unionBp(rightPg, rightBp, false, dummyPred, dummyPred, bpChanged);

    // don't need projectedSets anymore
    amdb_clustering::freeResultSets(projectedSets, numProjectedSets);

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::SplitInfo::write - write SplitInfo out in binary
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::SplitInfo::write(
    ostream& s, // in
    bool ascii) // in
{
    s.write((char *) this, sizeof(*this));

    // write rightEntries
    s.write((char *) rightEntries, numRight * sizeof(*rightEntries));

    // write leftBp
    s.write((char *) leftBp, leftLen);

    // write rightBp
    s.write((char *) rightBp, rightLen);
}


/////////////////////////////////////////////////////////////////////////
// amdb_splitstats::SplitInfo::read - read SplitInfo in binary
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::SplitInfo::read(
    istream& s)
{
    s.read((char *) this, sizeof(*this));

    // read rightEntries
    rightEntries = new int[numRight];
    s.read((char *) rightEntries, numRight * sizeof(*rightEntries));

    // read leftBp
    leftBp = new char[leftLen];
    s.read((char *) leftBp, leftLen);

    // read rightBp
    rightBp = new char[rightLen];
    s.read((char *) rightBp, rightLen);
}

amdb_splitstats::SplitInfo::~SplitInfo()
{
	// VCPORT_B
#ifndef WIN32
	if (numRight == 95)
		cout << "amdb_splitstats::SplitInfo::~SplitInfo()" << endl;
#endif
	// VCPORT_E
    delete [] rightEntries;
    delete [] leftBp;
    delete [] rightBp;
}

///////////////////////////////////////////////////////////////////////////////
// amdb_splitstats::SplitStats::add
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::SplitStats::add(
    const SplitStats& s)
{
    preIos += s.preIos;
    actualLeftIos += s.actualLeftIos;
    actualRightIos += s.actualRightIos;
    optLeftIos += s.optLeftIos;
    optRightIos += s.optRightIos;
    preExcCovLoss += s.preExcCovLoss;
    actualExcCovLoss += s.actualExcCovLoss;
}

amdb_splitstats::SplitStats::~SplitStats()
{
	// VCPORT_B
#ifndef WIN32
  //    actualSplit.~SplitInfo();
  //   optSplit.~SplitInfo();
#endif
	// VCPORT_E

}

///////////////////////////////////////////////////////////////////////////////
// amdb_splitstats::FullSplitStats::add
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::FullSplitStats::add(
    const SplitStats& stats, // in
    float targetUtil, // in: target util parameter for analysis
    float pageUtil) // in: actual util. in page
{
    _preIos += (float) stats.preIos;
    _preWeighted += (float) stats.preIos * pageUtil / targetUtil;
    _actualIos += (float) (stats.actualLeftIos + stats.actualRightIos);
    _actualWeighted += (float) stats.actualLeftIos *
        (float) stats.actualSplit.leftData / ((float) gist_p::data_sz * targetUtil) +
	(float) stats.actualRightIos * 
        (float) stats.actualSplit.rightData / ((float) gist_p::data_sz * targetUtil);
    _optIos += (float) (stats.optLeftIos + stats.optRightIos);
    _optWeighted += (float) stats.optLeftIos *
        (float) stats.optSplit.leftData / ((float) gist_p::data_sz * targetUtil) +
	(float) stats.optRightIos * 
        (float) stats.optSplit.rightData / ((float) gist_p::data_sz * targetUtil);
    preExcCovLoss += (float) stats.preExcCovLoss;
    actualExcCovLoss += (float) stats.actualExcCovLoss;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_splitstats::FullSplitStats::clear
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::FullSplitStats::clear()
{
    _preIos = 0.0;
    _preWeighted = 0.0;
    _actualIos = 0.0;
    _actualWeighted = 0.0;
    _optIos = 0.0;
    _optWeighted = 0.0;
    preExcCovLoss = 0.0;
    actualExcCovLoss = 0.0;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_splitstats::FullSplitStats::set
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::FullSplitStats::set(
    const SplitStats& s,
    float targetUtil,
    float pageUtil)
{
    clear();
    add(s, targetUtil, pageUtil);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_splitstats::computeAvgStats - set avgStats
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_splitstats::computeAvgStats(
    float targetUtil,
    amdb_treemap& tmap)
{
    avgStats.clear();
    SplitStatsMap::iterator it;
    for (it = splitStats.begin(); it != splitStats.end(); it++) {
        shpid_t pageno = (shpid_t) (*it).first;
        SplitStats* s = (SplitStats *) (*it).second;
	avgStats.add(*s, targetUtil, tmap.util(pageno));
    }
    int cnt = splitStats.size();
    avgStats._preIos /= (float) cnt;
    avgStats._preWeighted /= (float) cnt;
    avgStats._optIos /= (float) cnt;
    avgStats._optWeighted /= (float) cnt;
    avgStats._actualIos /= (float) cnt;
    avgStats._actualWeighted /= (float) cnt;
    avgStats.preExcCovLoss /= (float) cnt;
    avgStats.actualExcCovLoss /= (float) cnt;
}

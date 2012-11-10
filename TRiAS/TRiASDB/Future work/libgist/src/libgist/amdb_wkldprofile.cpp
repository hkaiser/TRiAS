// amdb_wkldprofile.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_wkldprofile.cc,v 1.3 2000/03/15 00:24:22 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_wkldprofile.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#ifdef HAVE_VALUES_H
#include <values.h>
#endif
// VCPORT_E

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "amdb_wkldprofile.h"
#include "amdb_clustering.h"

#include <assert.h>
#include "gist.h"
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_ext.h"
#include "amdb_treemap.h"
#include "amdb_itemset.h"

// STL
// VCPORT_B
#ifndef WIN32

#include <vector.h>
#include <algo.h>
#include <fstream.h>

#else

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

#endif
// VCPORT_E

// size w/o 'children' component (needed when reading/writing
// TraversalStats)
static amdb_wkldprofile::TraversalStats _dummyTs;
const int amdb_wkldprofile::TraversalStats::SIZE =
    sizeof(amdb_wkldprofile::TraversalStats) - 
    ((char *) &_dummyTs.pageno - (char *) &_dummyTs);


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::TraversalStats::add - add up traversal stats
//
// Description:
//	- adds up traversal stats for same page (for statsTotals)
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::TraversalStats::add(
    const TraversalStats& 	stats) 
{
    assert(pageno == stats.pageno);
    traversalCnt += stats.traversalCnt;
    retrievalCnt += stats.retrievalCnt;
    retrievalVol += stats.retrievalVol;
    emptyNode += stats.emptyNode;
    emptySubtree += stats.emptyNode;
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::InternalTraversalStats::operator= -
//	copy data from TraversalStats
//
// Description:
//
// Return Values:
//      *this
/////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::InternalTraversalStats&
amdb_wkldprofile::InternalTraversalStats::operator=(
    const TraversalStats& s)
{
    pageno = s.pageno;
    retrievalCnt = s.retrievalCnt;
    emptyNode = s.emptyNode == 1;
    return *this;
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::TraversalStats::operator= - 
//
// Description:
//
// Return Values:
//      *this
/////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::TraversalStats&
amdb_wkldprofile::TraversalStats::operator=(
    const TraversalStats& s)
{
    pageno = s.pageno;
    isLeaf = s.isLeaf;
    children.erase(children.begin(), children.end());
    traversalCnt = s.traversalCnt;
    retrievalCnt = s.retrievalCnt;
    retrievalVol = s.retrievalVol;
    emptyNode = s.emptyNode;
    emptySubtree = s.emptySubtree;
    return(*this);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::TraversalStats::TraversalStats - constructor
//
// Description:
//	- called when reading TraversalStats from input stream
/////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::TraversalStats::TraversalStats()
{
    TraversalStats(0);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::TraversalStats::TraversalStats - constructor
//
// Description:
//	- called when allocating TraversalStats for specific page
/////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::TraversalStats::TraversalStats(
    shpid_t 	pageno) :
    pageno(pageno), isLeaf(false), children(), traversalCnt(0), retrievalCnt(0),
    retrievalVol(0), emptyNode(0), emptySubtree(0)
{
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::StatsTotals::StatsTotals - constructor
//
// Description:
//	- leaves traversalStats empty, entries are allocated and inserted
//	  as needed in finalizeQuery()
///////////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::StatsTotals::StatsTotals() : 
    retrievedCnt(0), dataCoverage(0), traversalStats(), stats()
{
}

amdb_wkldprofile::StatsTotals::~StatsTotals()
{
    //cout << "~StatsTotals()" << endl;
    TraversalStatsMap::iterator it;
    for (it = traversalStats.begin(); it != traversalStats.end(); it++) {
	TraversalStats* stats = (TraversalStats *) (*it).second;
	delete stats;
    }
}


amdb_wkldprofile::Query::Query() :
    retrLimit(0), qual(NULL), resultSetSize(0), resultSet(NULL),
    numEmptyLeaves(0), emptyLeaves(NULL), traversalStatsSize(0),
    traversalStats(NULL)
{
}

amdb_wkldprofile::Query::~Query()
{
    //cout << "~Query()" << endl;
    delete [] qual;
    delete [] resultSet;
    delete [] emptyLeaves;
    delete [] traversalStats;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::amdb_wkldprofile - constructor
//
// Description:
///////////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::amdb_wkldprofile() :
    queries(), statsTotals(), _resultSet(), _traversalStats(), _treeMap(NULL)
{
}

#if 0
///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::amdb_wkldprofile - constructor
//
// Description:
//	- construct profile that will subsequently be used on specific tree
///////////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::amdb_wkldprofile(const amdb_treemap* map) :
    queries(), statsTotals(), _resultSet(), _traversalStats(), _treeMap(map)
{
    assert(map != NULL);
}
#endif


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::clear - reset state
//
// Description:
// 	- don't deallocate anything, we might still need it for 
//	  subsequent read() calls
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::clear()
{
    cout << "amdb_wkldprofile::clear()" << endl;

    int numQueries = queries.size(); // needed for optResultSets
    QueryVect::iterator qit;
    for (qit = queries.begin(); qit != queries.end(); qit++) {
	Query* query = (Query *) *qit;
	delete query;
    }
    queries.erase(queries.begin(), queries.end());
    //cout << "delete queries" << endl;

    TraversalStatsMap::iterator tmit;
    for (tmit = statsTotals.traversalStats.begin();
        tmit != statsTotals.traversalStats.end(); tmit++) {
        
	TraversalStats* stats = (TraversalStats *) (*tmit).second;
	delete stats;
    }
    statsTotals.traversalStats.erase(statsTotals.traversalStats.begin(),
        statsTotals.traversalStats.end());
    //cout << "delete statsTotals.traversalStats" << endl;

    _resultSet.erase(_resultSet.begin(), _resultSet.end());

    for (tmit = _traversalStats.begin(); tmit != _traversalStats.end(); tmit++) {
        TraversalStats* stats = (TraversalStats *) (*tmit).second;
	delete stats;
    }
    _traversalStats.erase(_traversalStats.begin(), _traversalStats.end());

    _treeMap = NULL;

}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::~amdb_wkldprofile - destructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

amdb_wkldprofile::~amdb_wkldprofile()
{
    cout << "~amdb_wkldprofile()" << endl;

    clear();
    //cout << "    delete queries" << endl;
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::write - write out profile
//
// Description:
//	- don't save _treeMap, only used when accumulating data
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t 
amdb_wkldprofile::write(
    ostream& 	s, // in: name of file to save to
    bool		ascii) // in: if true, write out in ASCII
{
    cout << "amdb_wkldprofile::write()" << endl;

    // save queries
    QueryVect::size_type queriesSize = queries.size();
    s.write((char *) &queriesSize, sizeof(queriesSize));

    int curQuery = 0;
    QueryVect::iterator qit;
    for (qit = queries.begin(); qit != queries.end(); qit++) {
	Query* query = (Query *) *qit;

	// save queries.retrLimit
	s.write((char *) &query->retrLimit, sizeof(query->retrLimit));

	// save queries.qual
	int len = (query->qual == 0 ? 0 : strlen(query->qual));
	s.write((char *) &len, sizeof(len));
	if (query->qual != NULL) {
	    s.write(query->qual, strlen(query->qual));
	}

	// save queries.resultSet
	s.write((char *) &query->resultSetSize,
	    sizeof(query->resultSetSize));
	int i;
	for (i = 0; i < query->resultSetSize; i++) {
	    s.write((char *) &query->resultSet[i],
		sizeof(query->resultSet[i]));
	}

	// save queries.emptyLeaves
	s.write((char *) &query->numEmptyLeaves,
	    sizeof(query->numEmptyLeaves));
	for (i = 0; i < query->numEmptyLeaves; i++) {
	    s.write((char *) &query->emptyLeaves[i],
		sizeof(query->emptyLeaves[i]));
	}

	// save queries.traversalStats
	s.write((char *) &query->traversalStatsSize,
	    sizeof(query->traversalStatsSize));
	int statno;
	for (statno = 0; statno < query->traversalStatsSize; statno++) {
	    s.write((char *) &query->traversalStats[statno],
		sizeof(query->traversalStats[statno]));
	}

	// write queries.stats
	s.write((char *) &query->stats, sizeof(query->stats));
    }

    // save statsTotals.retrievedCnt
    s.write((char *) &statsTotals.retrievedCnt, sizeof(statsTotals.retrievedCnt));

    // save statsTotals.dataCoverage
    s.write((char *) &statsTotals.dataCoverage, sizeof(statsTotals.dataCoverage));

    // save statsTotals.traversalStats
    // (don't save TraversalStats.children)
    TraversalStatsMap& tsMap = statsTotals.traversalStats;
    TraversalStatsMap::size_type traversalStatsSize = tsMap.size();
    s.write((char *) &traversalStatsSize, sizeof(traversalStatsSize));
    TraversalStatsMap::iterator it;
    for (it = tsMap.begin(); it != tsMap.end(); it++) {
	TraversalStats* ts = (TraversalStats *) (*it).second;
	s.write((char *) &ts->pageno, TraversalStats::SIZE);
    }

    // save statsTotals.stats
    s.write((char *) &statsTotals.stats, sizeof(statsTotals.stats));

    // check for errors
    if (!s) return(eFILEERROR);

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::read - read binary profile from file
//
// Description:
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_wkldprofile::read(
    istream& 	s) // in
{
    cout << "amdb_wkldprofile::read()" << endl;

    clear(); // delete current data, if there is any 

    // read queries
    //cout << "read queries" << endl;
    QueryVect::size_type queriesSize;
    s.read((char *) &queriesSize, sizeof(queriesSize));
    queries.reserve(queriesSize);
    unsigned queryno;
    for (queryno = 0; queryno < queriesSize; queryno++) {
        Query* q = new Query();
	queries.push_back((void *) q);

	// read queries.retrLimit
	s.read((char *) &q->retrLimit, sizeof(q->retrLimit));

	// read queries.qual
	int len;
	s.read((char *) &len, sizeof(len));
	if (len > 0) {
	    q->qual = new char[len+1];
	    s.read(q->qual, len);
	    q->qual[len] = '\0';
	}

	// read queries.resultSet
	s.read((char *) &q->resultSetSize, sizeof(q->resultSetSize));
	q->resultSet = new ItemId[q->resultSetSize];
	int i;
	for (i = 0; i < q->resultSetSize; i++) {
	    s.read((char *) &q->resultSet[i], sizeof(q->resultSet[i]));
	}

	// read queries.emptyLeaves
	s.read((char *) &q->numEmptyLeaves, sizeof(q->numEmptyLeaves));
	q->emptyLeaves = new shpid_t[q->numEmptyLeaves];
	for (i = 0; i < q->numEmptyLeaves; i++) {
	    s.read((char *) &q->emptyLeaves[i], sizeof(q->emptyLeaves[i]));
	}

	// read queries.traversalStats
	s.read((char *) &q->traversalStatsSize, sizeof(q->traversalStatsSize));
	q->traversalStats = new InternalTraversalStats[q->traversalStatsSize];
	int statno;
	for (statno = 0; statno < q->traversalStatsSize; statno++) {
	    InternalTraversalStats& ts = q->traversalStats[statno];
	    s.read((char *) &ts, sizeof(ts));
	}

	// read queries.stats
	s.read((char *) &q->stats, sizeof(q->stats));

    }

    // read statsTotals.retrievedCnt
    s.read((char *) &statsTotals.retrievedCnt, sizeof(statsTotals.retrievedCnt));

    // read statsTotals.dataCoverage
    s.read((char *) &statsTotals.dataCoverage, sizeof(statsTotals.dataCoverage));

    // read statsTotals.traversalStats
    //cout << "read statsTotals.traversalStats" << endl;
    TraversalStatsMap::size_type traversalStatsSize;
    s.read((char *) &traversalStatsSize, sizeof(traversalStatsSize));
    unsigned i;
    for (i = 0; i < traversalStatsSize; i++) {
        TraversalStats* ts = new TraversalStats();
	s.read((char *) &ts->pageno, TraversalStats::SIZE);
	statsTotals.traversalStats[ts->pageno] = (void *) ts;
    }

    // read statsTotals.stats
    s.read((char *) &statsTotals.stats, sizeof(statsTotals.stats));

    // check for errors
    if (!s) {
        return(eFILEERROR);
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::traversePage - record newly traversed page
//
// Description:
// 	- create new entry for traversed page and updates its 
//	  parent's child info
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::traversePage(
    shpid_t 	pageno,
    bool 	isLeaf,
    shpid_t 	parentno)
{
    // create new entry for node
    TraversalStats* stats = new TraversalStats(pageno);
    // record in TraversalStats map for currently executing query
    _traversalStats[pageno] = (void *) stats;
    stats->traversalCnt = 1;
    stats->isLeaf = isLeaf;

    if (pageno != parentno) {
	// update parent's child info
	TraversalStats* parent = (TraversalStats *) _traversalStats[parentno];
	parent->children.push_back((void *) pageno);
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::countRetrievals -
//	record # of retrieved items and total size in bytes
//
// Description:
/////////////////////////////////////////////////////////////////////////

void 
amdb_wkldprofile::countRetrievals(
    shpid_t 	pageno,
    int 	numMatches,
    int 	matches[])
{
    TraversalStats* stats = (TraversalStats *) _traversalStats[pageno];
    stats->retrievalCnt += numMatches;

    // for the retrieved data volume, consult the tree map
    int i;
    for (i = 0; i < numMatches; i++) {
        const amdb_treemap::PageInfo *pageInfo = NULL;
	pageInfo = _treeMap->pageInfo(pageno);
	assert(pageInfo != NULL);
	const amdb_treemap::RecInfo *recInfo = NULL;
	recInfo = _treeMap->itemInfo(pageInfo->itemOffset + matches[i]);
	stats->retrievalVol += recInfo->size;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::_finalizeQuery - recursively complete TraversalStats
//
// Description:
// 	- recursively complete TraversalStats.emptyNode, .emptySubtree and
// 	  .retrievalCnt of current query
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::_finalizeQuery(
    shpid_t 	subtreeRoot)
{
    TraversalStats* stats = (TraversalStats *) _traversalStats[subtreeRoot];
    assert(stats != NULL);
    if (!stats->isLeaf) {
	// finalize child subtrees and add up this node's retrieval count
	for (TraversalStats::ChildVector::iterator it = stats->children.begin();
	    it != stats->children.end(); it++) {

	    _finalizeQuery((shpid_t) *it);
	    TraversalStats* childStats =
	        (TraversalStats *) _traversalStats[(shpid_t) *it];
	    stats->retrievalCnt += childStats->retrievalCnt; // parent = sum of children
	}
    }
    if (stats->retrievalCnt == 0) {
	stats->emptySubtree = 1;
        if (stats->children.size() == 0) {
	    stats->emptyNode = 1;
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::addQuery - append new query to 'queries'
//
// Description:
//	- new query becomes current query
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::addQuery()
{
    Query* query = new Query();
    queries.push_back((void *) query);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::addToResultSet - add item to res. set of current query
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::addToResultSet(
    shpid_t 	leaf,
    unsigned 	idx)
{
    // update result set of current query
    unsigned itemNo = _treeMap->itemOffset(leaf) + idx;
    _resultSet.push_back((void *) itemNo);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::computeTotals - compute statsTotals.*, except for traversalStats
//
// Description:
//	- for dataCoverage, first extract result sets, then use those
//	  to compute a map of retrieved items; its size is the data coverage
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::computeTotals()
{
    QueryVect::iterator it;
    for (it = queries.begin(); it != queries.end(); it++) {
	Query* query = (Query *) *it;
        statsTotals.retrievedCnt += query->resultSetSize;

	// statsTotals.traversalStats updated in finalizeQuery()

	// update statsTotals.stats
	statsTotals.stats.leafStats.avgUtil += query->stats.leafStats.avgUtil;
	statsTotals.stats.leafStats.retrievalVol += query->stats.leafStats.retrievalVol;
	statsTotals.stats.leafStats.totalIos += query->stats.leafStats.totalIos;
	statsTotals.stats.internalStats.totalIos += query->stats.internalStats.totalIos;
    }
    
    // finalize avgUtil
    statsTotals.stats.leafStats.avgUtil /= queries.size();

    // compute dataCoverage
    amdb_clustering::ResultSet* resultSets;
    extractResultSets(resultSets);
    Map retrMap; // map<itemno, itemno>: from orig to condensed item no.
    int dummyInt;
    amdb_clustering::extractRetrieved(resultSets, queries.size(), retrMap,
        dummyInt);
    statsTotals.dataCoverage = retrMap.size();
    delete [] resultSets; // not needed any longer
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::finalizeQuery - compute query stats after query terminates
//
// Description:
//	- compute TraversalStats.retrievalCnt for internal nodes, .emptyNodes
//	  and .emptySubtree for all nodes. Compute QueryStats.
// 	- copy _resultSet and traversalStats to Query struct of finished query and
// 	  store empty leaf traversals in emptyLeaves
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::finalizeQuery(
    shpid_t 	rootNo)
{
    _finalizeQuery(rootNo);

    // compute part of Query.stats (avgUtil, excCovLoss)
    Query* query = (Query *) queries.back();
    float avgUtil = 0.0;
    int numNonEmptyLeaves = 0;
    int numEmptyLeaves = 0;
    TraversalStatsMap::iterator tsIt;
    for (tsIt = _traversalStats.begin(); tsIt != _traversalStats.end(); tsIt++) {
	TraversalStats* ts = (TraversalStats *) (*tsIt).second;

	// update QueryStats.leafStats and .internalStats (totalIos, excCovLoss,
	// utilLoss)
	if (ts->isLeaf) {
	    query->stats.leafStats.totalIos++;
	    if (ts->retrievalCnt != 0) {
		// determine avg util and retrieval vol. for non-empty leaves
		// only compute avg util for non-empty leaves
		avgUtil += _treeMap->util(ts->pageno);
		numNonEmptyLeaves++;
		query->stats.leafStats.retrievalVol += ts->retrievalVol;
	    } else {
	        numEmptyLeaves++;
	    }
	} else {
	    query->stats.internalStats.totalIos++;
	}
    }
    query->stats.leafStats.avgUtil = avgUtil / (float) numNonEmptyLeaves;

    // copy _resultSet and traversalStats to query and update statsTotals
    sort(_resultSet.begin(), _resultSet.end()); // needs to be sorted for evalSplit()
    query->resultSetSize = _resultSet.size();
    query->resultSet = new ItemId[query->resultSetSize];
    int i = 0;
    _ResultSet::iterator rsit;
    for (rsit = _resultSet.begin(); rsit != _resultSet.end(); rsit++, i++) {
	query->resultSet[i] = (ItemId) *rsit;
    }

    // save empty leaves and traversal stats for internal nodes
    query->numEmptyLeaves = numEmptyLeaves;
    if (query->numEmptyLeaves > 0) {
	query->emptyLeaves = new shpid_t[query->numEmptyLeaves];
    }
    query->traversalStatsSize = query->stats.internalStats.totalIos;
    query->traversalStats = new InternalTraversalStats[query->traversalStatsSize];
    i = 0;
    int j = 0;
    TraversalStatsMap::iterator tsit;
    for (tsit = _traversalStats.begin(); tsit != _traversalStats.end(); tsit++) {
	// update statsTotals.traversalStats
	TraversalStats* ts = (TraversalStats *) (*tsit).second;
	TraversalStats* totalsStats =
	    (TraversalStats *) statsTotals.traversalStats[ts->pageno];
	
	// we didn't pre-allocate statsTotals.traversalStats, so there
	// might not be an entry for 'pageno'; in that case, allocate and
	// register it now
	if (totalsStats == NULL) {
	    totalsStats = new TraversalStats(ts->pageno);
	    statsTotals.traversalStats[ts->pageno] = (void *) totalsStats;
	}

	totalsStats->isLeaf = ts->isLeaf;
	totalsStats->add(*ts);

	if (!ts->isLeaf) {
	    // record internal nodes only
	    query->traversalStats[i] = *ts;
	    i++;
	} else if (ts->emptyNode == 1) {
	    query->emptyLeaves[j] = ts->pageno;
	    j++;
	}
    }

    // reset _resultSet and traversalStats
    _resultSet.erase(_resultSet.begin(), _resultSet.end());
    for (tsit = _traversalStats.begin(); tsit != _traversalStats.end(); tsit++) {
	delete (TraversalStats *) (*tsit).second;
    }
    _traversalStats.erase(_traversalStats.begin(), _traversalStats.end());
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::createTraversalStats - 
//	generate map of traversal stats out of Query
//
// Description:
//	- always leaves retrievalVol = 0 for internal nodes
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::createTraversalStats(
    const Query& query,
    TraversalStatsMap& tsMap) const
{
    // reset map
    clearTraversalStatsMap(tsMap);

    // convert emptyLeaves
    int i;
    for (i = 0; i < query.numEmptyLeaves; i++) {
        TraversalStats* stats = new TraversalStats(query.emptyLeaves[i]);
	tsMap[stats->pageno] = (void *) stats;
	stats->isLeaf = true;
	stats->traversalCnt = 1;
	stats->retrievalCnt = 0;
	stats->retrievalVol = 0;
	stats->emptyNode = 1;
	stats->emptySubtree = 1;
    }

    // convert traversalStats
    for (i = 0; i < query.traversalStatsSize; i++) {
        InternalTraversalStats* qstats = &query.traversalStats[i];
        TraversalStats* stats = new TraversalStats(qstats->pageno);
	tsMap[stats->pageno] = (void *) stats;
	stats->isLeaf = false;
	stats->traversalCnt = 1;
	stats->retrievalCnt = qstats->retrievalCnt;
	stats->retrievalVol = 0; // not recorded for internal nodes
	stats->emptyNode = (qstats->emptyNode ? 1 : 0);
	stats->emptySubtree = ((qstats->retrievalCnt == 0) ? 1 : 0);
    }

    // convert resultSet
    for (i = 0; i < query.resultSetSize; i++) {
	const amdb_treemap::RecInfo* info =
	      _treeMap->itemInfo(query.resultSet[i]);
        shpid_t pageno = info->loc.treeLoc.page;
	TraversalStats* stats = (TraversalStats *) tsMap[pageno];
	if (stats == NULL) {
	    // entry doesn\'t exist yet
	    stats = new TraversalStats(pageno);
	    tsMap[pageno] = (void *) stats;
	    stats->isLeaf = true;
	    stats->traversalCnt = 1;
	}
	// add item to corresponding TraversalStat
	stats->retrievalCnt++;
	stats->retrievalVol += 
            _treeMap->itemInfo(query.resultSet[i])->size;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::clearTraversalStatsMap - resets map
//
// Description:
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::clearTraversalStatsMap(TraversalStatsMap& tmap)
{
    TraversalStatsMap::iterator it;
    for (it = tmap.begin(); it != tmap.end(); it++) {
	TraversalStats* stats = (TraversalStats *) (*it).second;
	delete stats;
    }
    tmap.erase(tmap.begin(), tmap.end());
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::extractResultSets - extract result sets from 'queries'
//
// Description:
//	- doesn't allocate storage for the items, only stores a 
//	  pointer to them in the amdb_clustering::ResultSet
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::extractResultSets(
    amdb_clustering::ResultSet *&resultSets) const
{
    resultSets = new amdb_clustering::ResultSet[queries.size()];
    assert(resultSets != NULL);

    QueryVect::const_iterator it;
    int i;
    for (it = queries.begin(), i = 0; it != queries.end(); it++, i++) {
	Query *query = (Query *) *it;
        resultSets[i].itemCnt = query->resultSetSize;
        resultSets[i].items = query->resultSet;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::projectToClusters - project query result sets onto clusters
//
// Description:
//	- allocates result sets (as many as queries.size())
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::projectToClusters(
    const amdb_clustering::Clustering&		clustering, // in
    amdb_clustering::ResultSet*&		resultSets) const // out
{
    int numResultSets = queries.size();
    resultSets = new amdb_clustering::ResultSet[numResultSets];
    QueryVect::const_iterator qit;
    IoCntMap map;
    // for each query, determine how many clusters it accesses
    int i;
    for (qit = queries.begin(), i = 0; qit != queries.end(); qit++, i++) {
	Query* query = (Query *) *qit;
	// compute the clusters
        computeIoCntMap(query, clustering, map);

	// construct the query's result set (in terms of the clustering)
	resultSets[i].itemCnt = map.size();
	resultSets[i].items = new ItemId[resultSets[i].itemCnt];
	IoCntMap::iterator mit;
	int j;
	for (mit = map.begin(), j = 0; mit != map.end(); mit++, j++) {
	    resultSets[i].items[j] = (ItemId) (*mit).first;
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::computeIoCnt -
//	computes # of I/Os for single query and given clustering
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

int
amdb_wkldprofile::computeIoCnt(
    Query* query,
    const amdb_clustering::Clustering& clustering)
{
    IoCntMap map;
    computeIoCntMap(query, clustering, map);
    return(map.size());
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::computeIoCntMap - computes IoCntMap for single query
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::computeIoCntMap(
    Query* 				query,
    const amdb_clustering::Clustering& 	clustering,
    IoCntMap&				cntMap) // out
{
    int i;
    for (i = 0; i < query->resultSetSize; i++) {
	ItemId itemNo = query->resultSet[i];
	int clustNo = (int) clustering[itemNo].clusterNo;
	assert(clustNo != amdb_clustering::invalidNo); // can't happen: invalid clust no
	cntMap[(unsigned int) clustNo] = (void *) 1;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::retrievalVolume -
// 	return size of data that query returns from given page
//
// Description:
//
// Return Values:
//      size of data in bytes
/////////////////////////////////////////////////////////////////////////

int 
amdb_wkldprofile::retrievalVolume(
    const Query& query,
    shpid_t pgno) const
{
    smsize_t vol = 0;

    int i;
    for (i = 0; i < query.resultSetSize; i++) {
	const amdb_treemap::RecInfo* info = 
	    _treeMap->itemInfo(query.resultSet[i]);
        if (info->loc.treeLoc.page == pgno) {
	    vol += _treeMap->itemInfo(query.resultSet[i])->size;
        }
    }
    return (int) vol;
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::projectToNode - project result sets onto node
//
// Description:
//	- returned projected result sets contain item numbers recorded in
//	  'map'
//	- only return non-empty projections
//	- allocates projectedSets[].items
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::projectToNode(
    shpid_t node, // in
    amdb_clustering::ResultSet projectedSets[], // out
    int& numProjected) const // out
{
    // XXX debug: record retrieval status of node items (map<ItemId, [01]>)
    Map nodeCnt;

    // construct itemset for contents of node
    amdb_itemset nodeContents;
    nodeContents.pageItems(*_treeMap, node);

    // XXX debug: init all to 0
    amdb_itemset::ItemIdVect::iterator iit;
    for (iit = nodeContents.itemIds.begin(); iit != nodeContents.itemIds.end(); iit++) {
        nodeCnt[*iit] = (void *) 0;
    }

    QueryVect::const_iterator qit;
    amdb_itemset intersection;
    bool intersects;
    int i = 0;
    numProjected = 0;
    for (qit = queries.begin(); qit != queries.end(); qit++, i++) {
	Query* query = (Query *) *qit;
        intersects = intersection.intersection(nodeContents, query->resultSet,
	    query->resultSetSize);

	// copy intersection to resultSet
	if (intersects) {
	    // XXX debug
	    //cout << i << " ";

	    projectedSets[numProjected].itemCnt = intersection.itemIds.size();
	    projectedSets[numProjected].items = new ItemId[intersection.itemIds.size()];
	    amdb_itemset::ItemIdVect::iterator it;
	    int j;
	    for (it = intersection.itemIds.begin(), j = 0;
	        it != intersection.itemIds.end(); it++, j++) {

		projectedSets[numProjected].items[j] = *it;
		nodeCnt[*it] = (void *) 1;
	    }
	    numProjected++;
	}
    }
    //cout << endl;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::copyResultSets - copy and translate result sets
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::copyResultSets(
    const amdb_wkldprofile& source,
    const TranslationMap& tmap)
{
    // create empty queries
    queries.reserve(source.queries.size());

    // create each Query and copy and translate the result set, given
    // the translation map
    QueryVect::const_iterator it;
    for (it = source.queries.begin(); it != source.queries.end(); it++) {
	Query* query = (Query *) *it;
	Query* newQuery = new Query();
	queries.push_back((void *) newQuery);
	newQuery->resultSetSize = query->resultSetSize;
	newQuery->resultSet = new ItemId[newQuery->resultSetSize];

	int i;
	for (i = 0; i < newQuery->resultSetSize; i++) {
	    newQuery->resultSet[i] = (ItemId) (*tmap.find(query->resultSet[i])).second;
	}
	sort(newQuery->resultSet, newQuery->resultSet + newQuery->resultSetSize);
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldprofile::setQual - sets Query.qual and .retrLimit
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
amdb_wkldprofile::setQual(
    int queryNo,
    const char* qual,
    int retrLimit)
{
    assert(queryNo < queries.size());
    Query* query = (Query *) queries[queryNo];
    query->retrLimit = retrLimit;
    int len = strlen(qual) + 1;
    query->qual = new char[len];
    (void) memcpy(query->qual, qual, len);
}

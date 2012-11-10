// amdb_wkldstat.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_wkldstats.cc,v 1.2 2000/03/15 00:24:23 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_wkldstats.h"
#endif

// VCPORT_B
#ifdef HAVE_VALUES_H
#include <values.h>
#endif

#ifdef WIN32
#pragma warning(disable:4786) // Templates can cause names to get too long for
							  // debug information. Disables this warning.
#endif
// VCPORT_E

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "amdb_wkldstats.h"
#include "amdb_clustering.h"

#include <assert.h>
#include "gist.h"
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_ext.h"
#include "amdb_wkldprofile.h"
#include "amdb_treemap.h"

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
#endif
// VCPORT_E

/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::NodeStats::NodeStats() - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

amdb_wkldstats::NodeStats::NodeStats() :
    utilLoss(0.0), utilOh(0.0), optClusterLoss(0.0), optClusterOh(0.0),
    minClusterLoss(0.0), minClusterOh(0.0), excCovLoss(0.0), excCovOh(0.0)
{
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::amdb_wkldstats - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

amdb_wkldstats::amdb_wkldstats() :
    nodeStats(), queryStats(), statsTotals()
{
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::clear - reset state
//
// Description:
// 	- don't deallocate anything, we might still need it for 
//	  subsequent read() calls
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::clear()
{
    cout << "amdb_wkldstats::clear()" << endl;
    NodeStatsMap::iterator nsit;
    for (nsit = nodeStats.begin(); nsit != nodeStats.end(); nsit++) {
	NodeStats* s = (NodeStats *) (*nsit).second;
        delete s;
    }
    //cout << "delete NodeStats: " << endl;
    nodeStats.erase(nodeStats.begin(), nodeStats.end());

    QueryStatsVect::iterator qit;
    for (qit = queryStats.begin(); qit != queryStats.end(); qit++) {
	QueryStats* qs = (QueryStats *) *qit;
	delete qs;
    }
    queryStats.erase(queryStats.begin(), queryStats.end());
    //cout << "delete queries" << endl;

}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::~wkldstats - free dynamically allocated state
//
// Description:
/////////////////////////////////////////////////////////////////////////

amdb_wkldstats::~amdb_wkldstats()
{
    cout << "~amdb_wkldstat()" << endl;

    clear();
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::write - write out state
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t 
amdb_wkldstats::write(
    ostream& s,
    bool ascii)
{
    cout << "amdb_wkldstats::write()" << endl;

    // save nodeStats
    NodeStatsMap::size_type nodeStatsSize = nodeStats.size();
    s.write((char *) &nodeStatsSize, sizeof(nodeStatsSize));

    shpid_t tmpPg;
    NodeStatsMap::iterator nsit;
    for (nsit = nodeStats.begin(); nsit != nodeStats.end(); nsit++) {
	shpid_t pgno = (shpid_t) (*nsit).first;
	NodeStats* ns = (NodeStats*) (*nsit).second;
	s.write((char *) &pgno, sizeof(pgno));
	s.write((char *) ns, sizeof(*ns));
    }

    // save queryStats
    QueryStatsVect::size_type queryStatsSize = queryStats.size();
    s.write((char *) &queryStatsSize, sizeof(queryStatsSize));

    int curQuery = 0;
    QueryStatsVect::iterator qit;
    for (qit = queryStats.begin(); qit != queryStats.end(); qit++) {
	QueryStats* qs = (QueryStats *) *qit;
	s.write((char *) qs, sizeof(*qs));
    }

    // save statsTotals
    s.write((char *) &statsTotals, sizeof(statsTotals));

    // check for errors
    if (!s) return(eFILEERROR);

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::read - read binary profile from file
//
// Description:
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_wkldstats::read(
    istream& 	s)
{
    cout << "amdb_wkldstats::read()" << endl;

    clear(); // delete current data, if there is any 

    // read nodeStats;
    //cout << "read nodeStats" << endl;
    NodeStatsMap::size_type nodeStatsSize;
    s.read((char *) &nodeStatsSize, sizeof(nodeStatsSize));
    int cnt;
    for (cnt = 0; cnt < nodeStatsSize; cnt++) {
	shpid_t pgno;
	s.read((char *) &pgno, sizeof(pgno));
	NodeStats* ns = new NodeStats();
	s.read((char *) ns, sizeof(*ns));
	nodeStats[pgno] = (void *) ns;
    }

    // read queryStats
    //cout << "read queries" << endl;
    QueryStatsVect::size_type queryStatsSize;
    s.read((char *) &queryStatsSize, sizeof(queryStatsSize));
    queryStats.reserve(queryStatsSize);
    unsigned queryno;
    for (queryno = 0; queryno < queryStatsSize; queryno++) {
        QueryStats* q = new QueryStats();
	queryStats.push_back((void *) q);
	s.read((char *) q, sizeof(*q));
    }

    // read statsTotals
    s.read((char *) &statsTotals, sizeof(statsTotals));

    // check for errors
    if (!s) {
        return(eFILEERROR);
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::_computeRandomIos
//
// Description:
//  	- Computes I/O numbers for random clusterings. Stores the result of
//	  each run in a local variable and computes avg and std dev at the end.
//
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::_computeRandomIos(
    const amdb_wkldprofile&		profile, // in
    const amdb_treemap& 		tmap, // in
    int					runs, // in
    float				fillFactor) // in
{
    typedef Vector* VectorPtr; // used as vector<int>: # of I/Os
    VectorPtr* tempResults = new VectorPtr[runs];
    assert(tempResults != NULL);
    int numQueries = profile.queries.size(); // one record per query
    int run;
    amdb_clustering::Clustering clustering;

    // temporarily need the result sets separated from profile
    amdb_clustering::ResultSet* resultSets;
    profile.extractResultSets(resultSets);

    for (run = 0; run < runs; run++) {
        amdb_clustering::randomClustering(resultSets, numQueries, fillFactor,
	    false, tmap, clustering);

	// evaluate queries against clustering
        tempResults[run] = new Vector(numQueries+1); // +1: for totalIos
	int queryCnt = 0;
	amdb_wkldprofile::QueryVect::const_iterator it;
	for (it = profile.queries.begin(); it != profile.queries.end();
	    it++, queryCnt++) {

	    // compute I/Os for single query
	    amdb_wkldprofile::Query* query = (amdb_wkldprofile::Query *) *it;
	    (*tempResults[run])[queryCnt] =
	        (void *) profile.computeIoCnt(query, clustering);
	    // add to total
	    int* total = (int *) &(*tempResults[run])[numQueries];
	    *total += (int) (*tempResults[run])[queryCnt];
	}
    }

    // summarize the I/O results for each query and for total (compute avg. and std. dev.)
    int qno;
    for (qno = 0; qno <= numQueries; qno++) {
	QueryStats* stats;
        if (qno < numQueries) {
	    stats = (QueryStats *) queryStats[qno];
	} else {
	    stats = &statsTotals;
	}

        int ioCnt = 0;
	for (run = 0; run < runs; run++) {
	    ioCnt += (int) (*tempResults[run])[qno];
	}
	stats->leafStats.randomIos = (float) ioCnt / (float) runs;
	// compute std dev
	float var = 0.0;
	for (run = 0; run < runs; run++) {
	    int res = (int) (*tempResults[run])[qno];
	    float diff = (float) res - stats->leafStats.randomIos;
	    var += diff * diff;
	}
	var /= (float) runs;
	stats->leafStats.randomStdDev = sqrt(var);
    }

    // deallocate tempResults
    for (run = 0; run < runs; run++) {
        tempResults[run]->erase(tempResults[run]->begin(), tempResults[run]->end());
	delete tempResults[run];
    }
    delete [] tempResults;

    delete [] resultSets;
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::_computeOptimalIos
//
// Description:
//	- computes optimal clustering and I/O counts for all queries
//	  as well as total
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::_computeOptimalIos(
    const amdb_wkldprofile& profile,
    const amdb_clustering::Clustering& optClustering)
{
    // compute optimalIos for each query and the total
    amdb_wkldprofile::QueryVect::const_iterator qit;
    QueryStatsVect::iterator qsit;
    for (qit = profile.queries.begin(), qsit = queryStats.begin();
        qit != profile.queries.end(); qit++, qsit++) {

	amdb_wkldprofile::Query* query = (amdb_wkldprofile::Query *) *qit;
	QueryStats* qs = (QueryStats *) *qsit;
	qs->leafStats.optimalIos = profile.computeIoCnt(query, optClustering);
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::_computeQueryStats - complete QueryStats
//
// Description:
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::_computeQueryStats(
    const amdb_wkldprofile& profile, // in
    const amdb_treemap& tmap, // in
    float targetUtil) // in
{
    QueryStatsVect::iterator it;
    amdb_wkldprofile::QueryVect::const_iterator pit;
    for (it = queryStats.begin(), pit = profile.queries.begin();
        it != queryStats.end(); it++, pit++) {

	QueryStats* qs = (QueryStats *) *it;
	amdb_wkldprofile::Query* query = (amdb_wkldprofile::Query *) *pit;
	int nonEmptyLeaves =
	    query->stats.leafStats.totalIos - query->numEmptyLeaves;

	// compute excCovLoss, utilLoss of leaves and internal nodes
	qs->leafStats.excCovLoss = query->numEmptyLeaves;
	qs->leafStats.utilLoss =
	    ((float) query->stats.leafStats.totalIos - qs->leafStats.excCovLoss) *
	    (1.0 - query->stats.leafStats.avgUtil / targetUtil);
	// for internal nodes, we don't have an avg. util., so we need to look
	// at the traversed pages (only the non-empty ones)
	qs->internalStats.utilLoss = 0.0;
	int i;
	for (i = 0; i < query->traversalStatsSize; i++) {
	    amdb_wkldprofile::InternalTraversalStats *ts = &query->traversalStats[i];
	    if (ts->emptyNode) {
		// nothing retrieved, no children traversed: counts fully
		// as excess coverage
	        qs->internalStats.excCovLoss += 1.0;
	    } else {
		// we count util loss in non-empty nodes
		qs->internalStats.utilLoss +=
		    1.0 - tmap.util(ts->pageno) / targetUtil;
		// we count root nodes of empty subtrees as util loss and
		// exch. cov. loss
		if (ts->retrievalCnt == 0) {
		    qs->internalStats.excCovLoss +=
		        tmap.util(ts->pageno) / targetUtil;
		}
	    }
	}

	// compute minIos = ceil(total volume retrieved / target page capacity)
	qs->leafStats.minIos =
	    (int) ceil((float) query->stats.leafStats.retrievalVol /
	    (targetUtil * (float) gist_p::data_sz));

	// optimalIos set in _computeOptimalIos()
	qs->leafStats.optimalOh = (float) qs->leafStats.optimalIos /
	    (float) qs->leafStats.minIos;
	qs->leafStats.optLeafOh = (float) nonEmptyLeaves /
	    (float) qs->leafStats.optimalIos;
	qs->leafStats.minLeafOh = (float) nonEmptyLeaves /
	    (float) qs->leafStats.minIos;
	qs->leafStats.optRandomOh = (float) qs->leafStats.randomIos /
	    (float) qs->leafStats.optimalIos;
	qs->leafStats.minRandomOh = (float) qs->leafStats.randomIos /
	    (float) qs->leafStats.minIos;
	qs->leafStats.optClusterLoss = (query->stats.leafStats.avgUtil /
	    targetUtil * (float) nonEmptyLeaves -
	    (float) qs->leafStats.optimalIos);
	qs->leafStats.optClusterOh = (query->stats.leafStats.avgUtil /
	    targetUtil * (float) nonEmptyLeaves) /
	    (float) qs->leafStats.optimalIos;
	qs->leafStats.minClusterLoss = query->stats.leafStats.avgUtil /
	    targetUtil * nonEmptyLeaves - qs->leafStats.minIos;
	qs->leafStats.minClusterOh = (query->stats.leafStats.avgUtil /
	    targetUtil * (float) nonEmptyLeaves) /
	    (float) qs->leafStats.minIos;
	qs->leafStats.utilOh = targetUtil / query->stats.leafStats.avgUtil;

	qs->leafStats.excCovOh = (float) query->stats.leafStats.totalIos /
	    (float) nonEmptyLeaves;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::_computeStatsTotals
//
// Description:
/////////////////////////////////////////////////////////////////////////

// compute statsTotals
void 
amdb_wkldstats::_computeStatsTotals(
    const amdb_wkldprofile& profile,
    float targetUtil)
{
    QueryStatsVect::iterator it;
    for (it = queryStats.begin(); it != queryStats.end(); it++) {
	QueryStats* qs = (QueryStats *) *it;

	statsTotals.leafStats.minIos += qs->leafStats.minIos;
	statsTotals.leafStats.optimalIos += qs->leafStats.optimalIos;
	statsTotals.leafStats.optClusterLoss +=
	    qs->leafStats.optClusterLoss;
	statsTotals.leafStats.minClusterLoss +=
	    qs->leafStats.minClusterLoss;
	statsTotals.leafStats.utilLoss += qs->leafStats.utilLoss;
	statsTotals.leafStats.excCovLoss += qs->leafStats.excCovLoss;

	statsTotals.internalStats.excCovLoss +=
	    qs->internalStats.excCovLoss;
	statsTotals.internalStats.utilLoss += qs->internalStats.utilLoss;
    }
    
    // finalize some aggregates

    statsTotals.leafStats.optimalOh =
	(float) statsTotals.leafStats.optimalIos /
        (float) statsTotals.leafStats.minIos;
    statsTotals.leafStats.optLeafOh =
        (float) profile.statsTotals.stats.leafStats.totalIos /
	((float) statsTotals.leafStats.optimalIos);
    statsTotals.leafStats.minLeafOh =
        (float) profile.statsTotals.stats.leafStats.totalIos /
	(float) statsTotals.leafStats.minIos;

    // randomIos and randomStdDev are computed in computeRandomClustering()
    statsTotals.leafStats.optRandomOh =
        (float) statsTotals.leafStats.randomIos /
        (float) statsTotals.leafStats.optimalIos;
    statsTotals.leafStats.minRandomOh =
        (float) statsTotals.leafStats.randomIos /
        (float) statsTotals.leafStats.minIos;

    statsTotals.leafStats.optClusterOh =
        (float) (statsTotals.leafStats.optClusterLoss +
	statsTotals.leafStats.optimalIos) /
        statsTotals.leafStats.optimalIos;
    statsTotals.leafStats.minClusterOh =
        (float) (statsTotals.leafStats.minClusterLoss +
	statsTotals.leafStats.minIos) /
        statsTotals.leafStats.minIos;
    statsTotals.leafStats.utilOh = targetUtil /
        profile.statsTotals.stats.leafStats.avgUtil;

    statsTotals.leafStats.excCovOh = 
        (float) profile.statsTotals.stats.leafStats.totalIos /
        (float) (profile.statsTotals.stats.leafStats.totalIos -
	statsTotals.leafStats.excCovLoss);
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::_computeNodeStats - 
//
// Description:
//	- allocate NodeStats for each traversed node and compute
//	  stats
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::_computeNodeStats(
    const amdb_wkldprofile& profile,
    const amdb_treemap& tmap,
    float targetUtil)
{
    int targetCap = (int) (targetUtil * (float) gist_p::data_sz); // target capacity
    amdb_wkldprofile::TraversalStatsMap::const_iterator tsit;
    for (tsit = profile.statsTotals.traversalStats.begin();
        tsit != profile.statsTotals.traversalStats.end(); tsit++) {

	NodeStats* ns = new NodeStats();
	const amdb_wkldprofile::TraversalStats* ts =
	    (amdb_wkldprofile::TraversalStats *) (*tsit).second;
	shpid_t pgno = ts->pageno;
	nodeStats[pgno] = (void *) ns;

	float util = tmap.util(pgno);
	int nonEmpty = ts->traversalCnt - ts->emptyNode; // non-empty accesses
	if (ts->isLeaf) {
	    ns->utilLoss = (float) nonEmpty * (1.0 - util / targetUtil);
	    ns->utilOh = targetUtil / util;
	    // optClusterLoss for page p = sum over all queries q: (data-vol(p) - 
	    // ratio(q) * retrieval-vol(p, q)) / B,
	    // with B = targetUtil * data_sz and ratio(q) = optimalIos(q) * B /
	    // retrieval-vol(q) (the benchmark retrieval ratio);
	    // optClusterOh for page p = |Q| * data-vol(p) / sum over all queries:
	    // ratio(q) * retrieval-vol(p, q)
	    ns->optClusterLoss = 0.0;
	    ns->optClusterOh = 0.0;
	    ns->minClusterLoss = 0.0;
	    ns->minClusterOh = 0.0;
	    int pgFill = (int) (util * (float) gist_p::data_sz);
	    amdb_wkldprofile::QueryVect::const_iterator qit;
	    QueryStatsVect::iterator qsit;
	    for (qit = profile.queries.begin(), qsit = queryStats.begin();
	        qit != profile.queries.end(); qit++, qsit++) {

		amdb_wkldprofile::Query* query = (amdb_wkldprofile::Query *) *qit;
		QueryStats* qs = (QueryStats *) *qsit;
		int vol = profile.retrievalVolume(*query, pgno);
		if (vol > 0) {
		    // this query accessed page pgno

		    // r = benchmark ratio of data accessed / data retrieved in opt
		    // clustering
		    float r_opt = (float) (qs->leafStats.optimalIos * targetCap) /
			(float) query->stats.leafStats.retrievalVol;
		    float r_min = (float) (qs->leafStats.minIos * targetCap) /
			(float) query->stats.leafStats.retrievalVol;
		    ns->optClusterLoss += ((float) pgFill - r_opt * (float) vol)
			/ (float) targetCap;
		    ns->minClusterLoss += ((float) pgFill - r_min * (float) vol)
			/ (float) targetCap;
		    // overhead: we sum up the denominator
		    ns->optClusterOh += r_opt * (float) vol;
		    ns->minClusterOh += r_min * (float) vol;
		}
	    }
	    if (ns->optClusterOh != 0.0) {
		ns->optClusterOh = ((float) (nonEmpty * gist_p::data_sz) * util) /
		    ns->optClusterOh;
	    } else {
		// the leaf was never accessed
		ns->optClusterOh = 1.0;
	    }
	    if (ns->minClusterOh != 0.0) {
		ns->minClusterOh = ((float) (nonEmpty * gist_p::data_sz) * util) /
		    ns->minClusterOh;
	    } else {
		ns->minClusterOh = 1.0;
	    }

	} else {
	    // we don't have numbers for internal nodes yet
	    ns->utilLoss = 0.0;
	    ns->utilOh = 1.0;
	    ns->optClusterLoss = 0.0;
	    ns->optClusterOh = 1.0;
	    ns->minClusterLoss = 0.0;
	    ns->minClusterOh = 1.0;
	}

	ns->excCovLoss = ts->emptyNode;
	if (ts->traversalCnt != 0) {
	    ns->excCovOh = (float) ts->traversalCnt / (float) nonEmpty; // could be \infty
	    ns->excCovOh = (float) ts->traversalCnt / (float) nonEmpty; // could be \infty
	} else {
	    ns->excCovOh = -1.0; // mark it
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::computeStats - compute all wkld stats
//
// Description:
//	- first, compute random clustering stats (randomIos, randomStdDev,
//	  opt-/minRandomOh)
//	- compute queryStats, statsTotals and nodeStats
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::computeStats(
    amdb_wkldprofile& profile, // in: input profile
    const amdb_treemap& tmap, // in: map of input tree
    const amdb_clustering::Clustering& optClustering, // in: optimal clustering
    const amdb_analysis::Parameters& parameters) // in: analysis parameters
{
    // allocate queryStats
    queryStats.reserve(profile.queries.size());
    int i;
    for (i = 0; i < profile.queries.size(); i++) {
        queryStats.push_back((void *) new QueryStats());
    }

    float fillFactor;
    if  (parameters.targetUtil == 0.0) {
	// take the avg. of the query avg.
        fillFactor = profile.statsTotals.stats.leafStats.avgUtil;
    } else {
         fillFactor = parameters.targetUtil;
    }

    profile.setTreeMap(&tmap); // make sure valid map is set

    // set randomIos in queryStats[]
    _computeRandomIos(profile, tmap, parameters.randomRuns, fillFactor);

    // set optIos in queryStats[]
    _computeOptimalIos(profile, optClustering);

    // computes remaining QueryStats
    _computeQueryStats(profile, tmap, parameters.targetUtil);

    // aggregates QueryStats
    _computeStatsTotals(profile, parameters.targetUtil);

    // computes nodeStats, using the profile's aggregated traversal stats
    _computeNodeStats(profile, tmap, parameters.targetUtil);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::createNodeStats -
// 	create full NodeStats for given query
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::createNodeStats(
    int queryNo, // in
    const amdb_wkldprofile& profile, // in
    const amdb_treemap& treeMap, // in
    const amdb_analysis::Parameters& parameters, // in
    NodeStatsMap& nsMap) const // out
{
    clearNodeStatsMap(nsMap);

    amdb_wkldprofile::Query* query =
        (amdb_wkldprofile::Query *) profile.queries[queryNo];
    QueryStats* qs = (QueryStats *) queryStats[queryNo];
    assert(query != NULL);
    amdb_wkldprofile::TraversalStatsMap tsMap;
    // compute traversal stats just to see which nodes where visited
    profile.createTraversalStats(*query, tsMap);

    amdb_wkldprofile::TraversalStatsMap::const_iterator it;
    for (it = tsMap.begin(); it != tsMap.end(); it++) {
	shpid_t pageno = (shpid_t) (*it).first;
	amdb_wkldprofile::TraversalStats* ts =
	    (amdb_wkldprofile::TraversalStats* ) (*it).second;
	float util = treeMap.util(pageno);
        NodeStats* stats = new NodeStats();
	nsMap[pageno] = (void *) stats;

	stats->utilLoss = 1.0 - util / parameters.targetUtil;
	stats->utilOh = parameters.targetUtil / util;

	if (!ts->isLeaf || ts->retrievalCnt == 0) {
	    // these stats don't apply here
	    stats->optClusterLoss = 0.0;
	    stats->optClusterOh = 1.0;
	    stats->minClusterLoss = 0.0;
	    stats->minClusterOh = 1.0;
	} else {
	    int targetCap = (int) (parameters.targetUtil * (float) gist_p::data_sz);
	    int pgFill = (int) (util * (float) gist_p::data_sz);
	    float r_min = (float) (qs->leafStats.minIos * targetCap) /
		(float) query->stats.leafStats.retrievalVol;
	    stats->minClusterLoss = ((float) pgFill - r_min * (float) ts->retrievalVol)
		/ (float) targetCap;
	    stats->minClusterOh = (float) pgFill / (r_min * (float) ts->retrievalVol);
	    float r_opt = (float) (qs->leafStats.optimalIos * targetCap) /
		(float) query->stats.leafStats.retrievalVol;
	    stats->optClusterLoss = ((float) pgFill - r_opt * (float) ts->retrievalVol)
		/ (float) targetCap;
	    stats->optClusterOh = (float) pgFill / (r_opt * (float) ts->retrievalVol);
	}

	stats->excCovLoss = (float) ts->emptyNode;
	stats->excCovOh = (float) ts->traversalCnt /
	    (float) (ts->traversalCnt - ts->emptyNode);
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_wkldstats::clearNodeStats -
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_wkldstats::clearNodeStatsMap(
    NodeStatsMap& tmap)
{
    NodeStatsMap::const_iterator it;
    for (it = tmap.begin(); it != tmap.end(); it++) {
        NodeStats* stats = (NodeStats *) (*it).second;
	delete stats;
    }
    tmap.erase(tmap.begin(), tmap.end());
}

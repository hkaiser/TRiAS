// amdb_penaltystats.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_penaltystats.cc,v 1.7 2000/03/15 00:24:20 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_penaltystats.h"
#endif

// VCPORT_B
#ifdef  WIN32
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
#include "amdb_penaltystats.h"
#include "amdb_clustering.h"
#include <assert.h>
#include "gist.h"
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_ext.h"
#include "amdb_treemap.h"
#include "amdb_wkldprofile.h"
#include "amdb_itemset.h"
#include "amdb_splitstats.h"

// STL
// VCPORT_B
#ifdef WIN32

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

#else

#include <fstream.h>
#include <vector.h>
#include <algo.h>

#endif
// VCPORT_E

/////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::clear - reset state
//
// Description:
// 	- don't deallocate anything, we might still need it for 
//	  subsequent read() calls
/////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::clear()
{
    cout << "amdb_penaltystats::clear()" << endl;
    PenaltyStatsVect::iterator psit;
    for (psit = penaltyStats.begin(); psit != penaltyStats.end(); psit++) {
        PenaltyStats* stats = (PenaltyStats *) *psit;
	delete stats;
    }
    penaltyStats.erase(penaltyStats.begin(), penaltyStats.end());
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::amdb_penaltystats - constructor
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

amdb_penaltystats::amdb_penaltystats() : penaltyStats()
{
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::~amdb_penaltystats - destructor
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

// free all dynamically allocated stuff
amdb_penaltystats::~amdb_penaltystats()
{
    cout << "~amdb_penaltystats()" << endl;

    clear();
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::write - write to output stream
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t 
amdb_penaltystats::write(
    ostream& s,
    bool ascii)
{
    cout << "amdb_penaltystats::write()" << endl;

    if (!ascii) {
      // save penaltyStats
      PenaltyStatsVect::size_type penaltyStatsSize = penaltyStats.size();
      s.write((char *) &penaltyStatsSize, sizeof(penaltyStatsSize));
      PenaltyStatsVect::iterator pit;
      for (pit = penaltyStats.begin(); pit != penaltyStats.end(); pit++) {
	PenaltyStats* stats = (PenaltyStats *) *pit;
	
	// save stats
	s.write((char *) stats, sizeof(*stats));
	
	// save key
	int klen = stats->key->len(0);
	s.write((char *) &klen, sizeof(klen));
	s.write((char *) stats->key->ptr(0), klen);
      }
      
      // write avgStats
      s.write((char *) &avgStats, sizeof(avgStats));
      
      // check for errors
      if (!s) return(eFILEERROR);
    }
    else {
      // save penaltyStats
      PenaltyStatsVect::size_type penaltyStatsSize = penaltyStats.size();
      s << penaltyStatsSize << "\n";
      PenaltyStatsVect::iterator pit;
      for (pit = penaltyStats.begin(); pit != penaltyStats.end(); pit++) {
	PenaltyStats* stats = (PenaltyStats *) *pit;
	
	// save stats
	s << stats << "\n";
	
	// save key
	int klen = stats->key->len(0);
	s << klen;
	s << stats->key->ptr(0);
      }
      
      // write avgStats
      //s << avgStats;
      
      // check for errors
      if (!s) return(eFILEERROR);
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::read - read binary profile from input stream
//
// Description:
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_penaltystats::read(
    istream& s)
{
    cout << "amdb_penaltystats::read()" << endl;

    clear(); // delete current data, if there is any 

    // read penaltyStats
    PenaltyStatsVect::size_type penaltyStatsSize;
    s.read((char *) &penaltyStatsSize, sizeof(penaltyStatsSize));
    int i;
    for (i = 0; i < penaltyStatsSize; i++) {
	PenaltyStats* stats = new PenaltyStats();
	s.read((char *) stats, sizeof(*stats));

	// read key
	int klen;
	s.read((char *) &klen, sizeof(klen));
	char* keyptr = new char[klen];
	s.read(keyptr, klen);
	stats->key = new vec_t(keyptr, klen);

	penaltyStats.push_back((void *) stats);
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
// amdb_penaltystats::evalPenalty - compute PenaltyStats of single insertion
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_penaltystats::evalPenalty(
    gist& tree, // in: target tree
    amdb_wkldprofile& profile, // in
    const amdb_treemap& tmap, // in
    const Vector& queryStructs, // vector<gist_query_t *>
    shpid_t leaf, // in: target leaf chosen by penalty metric
    const vec_t& key) // in: test key
{
    PenaltyStats* stats = new PenaltyStats();
    profile.setTreeMap(&tmap); // make sure valid map is set
    gist_ext_t* ext = tree.extension();
    amdb_ext_t* amdbext = amdb_ext_t::extension(ext);

    // copy key and set actualLeaf
    char* keyptr = new char[key.len(0)];
    (void) memcpy(keyptr, key.ptr(0), key.len(0));
    stats->key = new vec_t(keyptr, key.len(0));
    stats->actualLeaf = leaf;

    // determine which queries would retrieve key
    Vector matches; // vector<int>: indices of matching queries for 'queries'
    _computeMatches(tree, queryStructs, key, matches);

    // determine optLeaf and actual- and optAddIos: 
    // compute additional I/Os for every leaf
    stats->optAddIos = MAXINT;
    amdb_treemap::PageMap::const_iterator pmit;
    for (pmit = tmap.pageMap.begin(); pmit != tmap.pageMap.end(); pmit++) {
	amdb_treemap::PageInfo* info = (amdb_treemap::PageInfo *) (*pmit).second;
	if (info->level > 1) {
	    // this isn't a leaf, ignore it
	    continue;
	}
        shpid_t pageno = (shpid_t) (*pmit).first;
	int addIos = _computeExtraIos(tree, profile, tmap, pageno, key, matches);

	if (pageno == leaf) {
	    // we just looked at the actual target leaf
	    stats->actualAddIos = addIos;
	}
	if (addIos < stats->optAddIos) {
	    // we found a better leaf to insert on
	    stats->optAddIos = addIos;
	    stats->optLeaf = pageno;
	}
    }

    // determine pre- and actualExcCovLoss:
    // first, construct pre- and post-insertion BP
    gist::AlignedPred x, y;
    vec_t preBp(x.pred, gist_p::max_tup_sz);
    vec_t postBp(y.pred, gist_p::max_tup_sz);
    W_DO(tree.getBp(leaf, preBp));
    (void) memcpy(postBp.ptr(0), preBp.ptr(0), preBp.len(0));
    postBp.set(y.pred, preBp.len(0));
    bool dummyBool;
    tree.unionBp(leaf, postBp, true, key, vec_t(), dummyBool);

    // set pre- and actualExcCovLoss
    _computeExcCovLoss(tree, profile, tmap, leaf, preBp, postBp,
        key, matches, queryStructs, stats->preExcCovLoss, stats->actualExcCovLoss);

    penaltyStats.push_back((void *) stats);

    return(RCOK);
}

/////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::_computeExtraIos - 
//	return additional I/Os to leaf after (virtual) insertion
//
// Description:
//	- counts those queries that don't retrieve anything from 
//	  currently but their gist_query_t intersects with the new key
//
// Return Values:
//      number of additional I/Os
/////////////////////////////////////////////////////////////////////////

int
amdb_penaltystats::_computeExtraIos(
    const gist& tree, // in: supplies extension
    const amdb_wkldprofile& profile, // in
    const amdb_treemap& tmap, // in
    shpid_t leaf, // in: node we're inserting on
    const vec_t& key, // in: key that's being inserted
    const Vector& matches) // in: vector<int>, indices of matching queries
{
    amdb_itemset leafSet;
    leafSet.pageItems(tmap, leaf);

    int debug = 0;

    if (debug) {
	//copy(leafSet.itemIds.begin(), leafSet.itemIds.end(),
	    //ostream_iterator<ItemId>(cout, " "));
	//cout << endl;
    }

    gist_ext_t* ext = tree.extension();
    amdb_ext_t* amdbext = amdb_ext_t::extension(ext);

    int cnt = 0;
    Vector::const_iterator it;
    amdb_itemset intersection;
    for (it = matches.begin(); it != matches.end(); it++) {
	int index = (int) *it;
	amdb_wkldprofile::Query* query = (amdb_wkldprofile::Query *)
	    profile.queries[index];
	// count those queries that so far don't visit the leaf in question,
	if (!intersection.intersection(leafSet, query->resultSet,
	    query->resultSetSize)) {

	    cnt++;
	}

	if (debug) {
	    // XXX debug 
	    //copy(optResultSets[index], optResultSets[index] + query->resultSetSize,
		//ostream_iterator<ItemId>(cout, " "));
	    //cout << endl;
	    //copy(intersection.itemIds.begin(), intersection.itemIds.end(),
		//ostream_iterator<ItemId>(cout, " "));
	    cout << endl;
	}
    }
    return(cnt);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::_computeExcCovLoss -
// 	compute pre- and post-insertion excess coverage loss for evalPenalty()
//
// Description:
//	- construct post-insertion BP with unionBp()
//	- computations based on optTree (optMap and optResultSets)
//	- ignore queries that already retrieve something from the node in
//	  question or would retrieve the new item (which would change an excess
//	  coverage I/O into data access, even if the BP didn't change at all)
///////////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::_computeExcCovLoss(
    const gist& tree, // in: target tree
    const amdb_wkldprofile& profile, // in
    const amdb_treemap& tmap, // in: map of target tree
    shpid_t leaf, // in: node we're inserting on
    const vec_t& preBp, // in: pre-insertion BP
    const vec_t& postBp, // in: post-insertion BP
    const vec_t& key, // in: key we're inserting
    const Vector& matches, // in: vector<int>, indices of queries matching key
    const Vector& queryStructs, // in: vector<gist_query_t *>
    int& preExcCovLoss, // out: pre-insertion loss
    int& postExcCovLoss) // out: post-insertion loss
{
    amdb_itemset leafSet;
    leafSet.pageItems(tmap, leaf);

    gist_ext_t* ext = tree.extension();
    amdb_ext_t* amdbext = amdb_ext_t::extension(ext);

    preExcCovLoss = postExcCovLoss = 0;
    amdb_itemset intersection;
    int i, j = 0;
    for (i = 0; i < profile.queries.size(); i++) {
        if (j < matches.size() && i == (int) matches[j]) {
	    // query i would retrieve 'key', we ignore it
	    j++;
	    continue;
	}

	amdb_wkldprofile::Query* queryInfo = (amdb_wkldprofile::Query *)
	    profile.queries[i];
	gist_query_t* query = (gist_query_t *) queryStructs[i];
	if (!intersection.intersection(leafSet, queryInfo->resultSet,
	    queryInfo->resultSetSize)) {

	    if (amdbext->consistent(ext, query, preBp, 2)) {
	        preExcCovLoss++;
	    }
	    if (amdbext->consistent(ext, query, postBp, 2)) {
	        postExcCovLoss++;
	    }
	}

	// XXX debug
	//copy(intersection.begin(), intersection.end(),
	    //ostream_iterator<ItemId>(cout, " "));
	//cout << endl;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::_computeMatches - compute indices of queries matching given key
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::_computeMatches(
    const gist& tree, // in
    const Vector& queryStructs, // in: vector<gist_query_t *>
    const vec_t& key, // in
    Vector& matches) // out: vector<int> of indices into queryStructs
{
    gist_ext_t* ext = tree.extension();
    amdb_ext_t* amdbext = amdb_ext_t::extension(ext);

    Vector::const_iterator it;
    int i;
    matches.erase(matches.begin(), matches.end());
    for (it = queryStructs.begin(), i = 0; it != queryStructs.end(); it++, i++) {
	if (amdbext->consistent(ext, (gist_query_t *) *it, key, 1)) {
	    matches.push_back((void *) i);
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::PenaltyStats::add
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void 
amdb_penaltystats::PenaltyStats::add(
    const PenaltyStats& s)
{
    actualAddIos += s.actualAddIos;
    optAddIos += s.optAddIos;
    preExcCovLoss += s.preExcCovLoss;
    actualExcCovLoss += s.actualExcCovLoss;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::FullPenaltyStats::clear
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void 
amdb_penaltystats::FullPenaltyStats::clear()
{
    _actualIos = 0.0;
    _actualAddIos = 0.0;
    _actualAddWeighted = 0.0;
    _optAddIos = 0.0;
    _optAddWeighted = 0.0;
    preExcCovLoss = 0.0;
    actualExcCovLoss = 0.0;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::FullPenaltyStats::set
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::FullPenaltyStats::set(
    const PenaltyStats& stats, // in
    float targetUtil, // in
    const amdb_splitstats& splitStats, // in: needed for preIos
    const amdb_treemap& tmap) // in: needed for util
{
    clear();
    add(stats, targetUtil, splitStats, tmap);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::FullPenaltyStats::add
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::FullPenaltyStats::add(
    const PenaltyStats& stats, // in
    float targetUtil, // in
    const amdb_splitstats& splitStats, // in: needed for preIos
    const amdb_treemap& tmap) // in: needed for util
{
    amdb_splitstats::SplitStats* ss = (amdb_splitstats::SplitStats *) 
        (*splitStats.splitStats.find(stats.actualLeaf)).second;
    assert(ss != NULL);
    _actualIos += (float) (ss->preIos + stats.actualAddIos);
    _actualAddIos += (float) stats.actualAddIos;
    _actualAddWeighted += (float) stats.actualAddIos *
        tmap.util(stats.actualLeaf) / targetUtil;
    _optAddIos += (float) stats.optAddIos;
    _optAddWeighted += (float) stats.optAddIos *
        tmap.util(stats.optLeaf) / targetUtil;
    preExcCovLoss += (float) stats.preExcCovLoss;
    actualExcCovLoss += (float) stats.actualExcCovLoss;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_penaltystats::computeAvgStats - 
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
amdb_penaltystats::computeAvgStats(
    float targetUtil,
    const amdb_splitstats& splitStats,
    const amdb_treemap& tmap)
{
    avgStats.clear();
    PenaltyStatsVect::iterator it;
    for (it = penaltyStats.begin(); it != penaltyStats.end(); it++) {
	PenaltyStats* s = (PenaltyStats *) *it;
	avgStats.add(*s, targetUtil, splitStats, tmap);
    }
    int cnt = penaltyStats.size();
    avgStats._actualIos /= (float) cnt;
    avgStats._actualAddIos /= (float) cnt;
    avgStats._actualAddWeighted /= (float) cnt;
    avgStats._optAddIos /= (float) cnt;
    avgStats._optAddWeighted /= (float) cnt;
    avgStats.preExcCovLoss /= (float) cnt;
    avgStats.actualExcCovLoss /= (float) cnt;
}

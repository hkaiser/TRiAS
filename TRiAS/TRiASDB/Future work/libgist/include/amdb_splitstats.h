// amdb_splitstats.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_splitstats.h,v 1.5 2000/03/10 01:38:59 mashah Exp $

#ifndef AMDB_SPLITSTATS_H
#define AMDB_SPLITSTATS_H

#ifdef __GNUG__
#pragma interface "amdb_splitstats.h"
#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t
#include "vec_t.h"		// for vec_t

// VCPORT_B
#ifndef WIN32
class ostream;
class istream;
#endif
// VCPORT_E

class gist;
class gist_query_t;
class gist_p;
class amdb_wkldprofile;
class amdb_treemap;

/*
 * amdb_splitstats:
 *
 */

class amdb_splitstats
{

public:

    // info for single split
    struct SplitInfo {
	int* rightEntries; // slots that split moved right
	int numRight; // how many
	void* leftBp; // data of BP for left page
	int leftLen; // length of BP for left page
	void* rightBp; // data of BP for right page
	int rightLen; // length of BP for right page
	int leftData; // bytes of data on left page (of all tuples)
	int rightData; // bytes of data on right page (of all tuples)

        SplitInfo() : rightEntries(NULL), numRight(0), leftBp(NULL), leftLen(0),
	    rightBp(NULL), rightLen(0), leftData(0), rightData(0)
	{
	}

	~SplitInfo();


	void write(ostream& s, bool ascii);
	void read(istream& s);

    };

    // statistics of single-page split
    struct SplitStats { 
        SplitInfo actualSplit; // info for gist_ext_t::pickSplit
	SplitInfo optSplit; // hypergraph-partitioning-computed split info

	// clustering-related stats; empty I/Os excluded
	// (keep track of exact location of accesses, so we can reconstruct
	// the metrics in terms of accessed data, which
	// corresponds to the clustering metrics for the static tree, and
	// full I/Os)
	int preIos; // pre-split accesses
	int actualLeftIos; // to left page of actual split
	int actualRightIos; // to right page of actual split
	int optLeftIos; // to left page of opt split
	int optRightIos; // to right page of opt split

	// excess coverage stats
	int preExcCovLoss; // empty I/Os prior to split
	int actualExcCovLoss; // combined empty I/Os after actual split

	SplitStats() : actualSplit(), optSplit(), preIos(0), actualLeftIos(0),
	    actualRightIos(0), optLeftIos(0), optRightIos(0), preExcCovLoss(0),
	    actualExcCovLoss(0) {}

	~SplitStats();

	void add(const SplitStats& s);
    };

    // split statistics (possibly aggregated), fully materialized;
    // all values are floats because FullSplitStats may also represent averages
    struct FullSplitStats { 
	// clustering-related stats; empty I/Os excluded
	// (keep track of exact location of accesses, so we can reconstruct
	// the metrics in terms of accessed data (full = false), which
	// corresponds to the clustering metrics for the static tree, and
	// full I/Os (full = true))
	float _preIos; // pre-split accesses
	float _preWeighted;
	float _actualIos; // after actual split, total
	float _actualWeighted;
	float _optIos; // after opt split, total
	float _optWeighted;

	// excess coverage stats
	float preExcCovLoss; // empty I/Os prior to split
	float actualExcCovLoss; // combined empty I/Os after actual split

	FullSplitStats() : _preIos(0), _preWeighted(0), _actualIos(0), _actualWeighted(0),
	    _optIos(0), _optWeighted(0), preExcCovLoss(0), actualExcCovLoss(0) {}

	void add(const SplitStats& s, float targetUtil, float pageUtil);
	void set(const SplitStats& s, float targetUtil, float pageUtil);
	void clear();

	// for convenience
	float preIos(bool weighted)
	{ return(weighted ? _preWeighted : (float) _preIos); }
	float optIos(bool weighted)
	{ return(weighted ? _optWeighted : (float) _optIos); }
	float actualIos(bool weighted)
	{ return(weighted ? _actualWeighted : (float) _actualIos); }
	float optClusterDelta(bool weighted)
	{
	    return (weighted ? 
	        (_optWeighted - _preWeighted) : (float) (_optIos - _preIos));
	}
	float actualClusterDelta(bool weighted)
	{
	    return (weighted ? 
	        (_actualWeighted - _preWeighted) : (float) (_actualIos - _preIos));
	}
	float clusterLoss(bool weighted)
	{
	    // return positive value
	    return(actualClusterDelta(weighted) - optClusterDelta(weighted));
	}
	float clusterOh(bool weighted)
	{
	    return(actualIos(weighted)/optIos(weighted));
	}
	float clusterSuccess(bool weighted)
	{
	    return(actualClusterDelta(weighted) / optClusterDelta(weighted));
	}
	float excCovDelta() { return(actualExcCovLoss - preExcCovLoss); }
	float excCovLoss() { return(actualExcCovLoss); }
	float excCovOh()
	{
	    return((float) (_actualIos + actualExcCovLoss)/(float) _actualIos);
	}
	float excCovSuccess() { return(-1.0 * excCovDelta()/(float) preExcCovLoss); }

    };

    //////////////////////////////////////////////////////////////////////////
    //
    // Profile State
    //
    //////////////////////////////////////////////////////////////////////////

    // split stats
    //typedef map<shpid_t, SplitStats* > SplitStatsMap: from page no to split stats
    typedef Map SplitStatsMap;
    SplitStatsMap splitStats;
    FullSplitStats avgStats; // averaged over all nodes split so far


    //////////////////////////////////////////////////////////////////////////
    //
    // Profile Interface
    //
    //////////////////////////////////////////////////////////////////////////
    // binary data to and from files
    rc_t write(
        ostream& s,
	bool ascii);
    rc_t read(
        istream& s);

    // compute stats and metrics for single split
    rc_t evalSplit(
	gist& tree, // in: calling tree
	amdb_wkldprofile& profile, // in
	const amdb_treemap& map, // in
	const Vector& queryStructs, // in: vector<gist_query_t *>
        shpid_t leaf, // in: node to evaluate
	int rightEntries[], // in: slot indices of entries for right node
	int numRight,  // in: number of entries in array
	vec_t& leftBp, // in: BP of left node
	vec_t& rightBp); // in: BP of right node

    // produce 'optimal' (derived by hypergraph partitioning) split
    rc_t optSplit(
        gist& tree, // in
	const amdb_wkldprofile& profile, // in
	const amdb_treemap& map, // in
	shpid_t leaf, // in
	int ubfactor, // in: hmetis balance parameter
	int rightEntries[], // out: slot indices of entries for right sib
	int& numRight,  // out
	vec_t& leftBp, // out
	vec_t& rightBp); // out

    // set avgStats
    void computeAvgStats(
	float targetUtil,
	amdb_treemap& map);

    amdb_splitstats();
    ~amdb_splitstats();
    void clear(); // delete all stored data

private:

    void _splitInfoInit(
	SplitInfo& info, // out
	shpid_t page, // in
	const amdb_treemap& map, // in
	int rightEntries[], // in
	int numRight, // in
	const vec_t& leftBp, // in
	const vec_t& rightBp); // in

};

#endif

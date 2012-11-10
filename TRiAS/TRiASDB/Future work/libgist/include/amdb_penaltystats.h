// amdb_penaltystats.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_penaltystats.h,v 1.3 2000/03/10 01:38:59 mashah Exp $

#ifndef AMDB_PENALTYSTATS_H
#define AMDB_PENALTYSTATS_H

#ifdef __GNUG__
#pragma interface "amdb_penaltystats.h"
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
class amdb_treemap;
class amdb_wkldprofile;
class amdb_splitstats;

/*
 * amdb_penaltystats:
 */

class amdb_penaltystats
{

public:
    
    // penalty stats and metrics
    struct PenaltyStats {
	vec_t* key; // "inserted" key
        shpid_t actualLeaf; // actual target leaf
        shpid_t optLeaf; // optimal target leaf

	// clustering-related stats; empty I/Os excluded
	int actualAddIos; // additional I/Os to actual target leaf
	int optAddIos; // additional I/Os to opt target leaf

	// excess coverage stats, only for actual target leaf
	int preExcCovLoss;
	    // pre-insertion loss (excludes queries that retrieve only the inserted
	    // item)
	int actualExcCovLoss; // exc. cov. loss on actual target leaf after insertion

	PenaltyStats() : key(NULL), actualLeaf(0), optLeaf(0), actualAddIos(0),
	    optAddIos(0), preExcCovLoss(0), actualExcCovLoss(0) {}

	~PenaltyStats() 
	{
	    if (key != NULL) {
		delete [] key->ptr(0);
		delete key;
	    }
	}

	void add(const PenaltyStats& stats);

    };

    
    // penalty statistics (possibly aggregated), fully materialized
    struct FullPenaltyStats {
	// clustering-related stats; empty I/Os excluded
	float _actualIos; // total I/Os to actual target leaf
	float _actualAddIos; // additional I/Os to actual target leaf
	float _actualAddWeighted; // additional I/Os to actual target leaf
	float _optAddIos; // additional I/Os to opt target leaf
	float _optAddWeighted; // additional I/Os to opt target leaf

	// excess coverage stats, only for actual target leaf
	float preExcCovLoss;
	    // pre-insertion loss (excludes queries that retrieve only the inserted
	    // item)
	float actualExcCovLoss; // exc. cov. loss on actual target leaf after insertion

	FullPenaltyStats() : _actualIos(0.0), _actualAddIos(0.0),
	    _actualAddWeighted(0.0), _optAddIos(0.0), _optAddWeighted(0.0),
	    preExcCovLoss(0.0), actualExcCovLoss(0.0) {}

	void add(
	    const PenaltyStats& s,
	    float targetUtil,
	    const amdb_splitstats& splitStats,
	    const amdb_treemap& map);
 	void set(
	    const PenaltyStats& s,
	    float targetUtil,
	    const amdb_splitstats& splitStats,
	    const amdb_treemap& map);
	void clear();


	// for convenience
	float actualAddIos(bool weighted) 
	{ return(weighted ? _actualAddWeighted : _actualAddIos); }
	float optAddIos(bool weighted) 
	{ return(weighted ? _optAddWeighted : _optAddIos); }
	float excCovDelta() { return(preExcCovLoss - actualExcCovLoss); }
	float clusterLoss(bool weighted) 
	{ return(actualAddIos(weighted) - optAddIos(weighted)); }
	float excCovOh()
	{ return((_actualIos + actualExcCovLoss)/(_actualIos + preExcCovLoss)); }
	float excCovSuccess()
	{ return((preExcCovLoss - actualExcCovLoss)/preExcCovLoss); }
    };


    //////////////////////////////////////////////////////////////////////////
    //
    // Profile State
    //
    //////////////////////////////////////////////////////////////////////////
    // penalty stats
    // typedef vector<PenaltyStats *> PenaltyStatsVect;
    typedef Vector PenaltyStatsVect;
    PenaltyStatsVect penaltyStats;
    FullPenaltyStats avgStats; // averaged over all insertions analyzed so far


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

    // compute penalty stats for single insertion
    rc_t evalPenalty(
	gist& tree, // in: target tree
	amdb_wkldprofile& profile, // in
	const amdb_treemap& map, // in
	const Vector& queryStructs, // vector<gist_query_t *>
        shpid_t leaf, // in: target leaf chosen by penalty metric
	const vec_t& key); // in: test key

    // set avgStats
    void computeAvgStats(
        float targetUtil,
	const amdb_splitstats& splitStats,
	const amdb_treemap& map);

    amdb_penaltystats();
    ~amdb_penaltystats();
    void clear(); // delete all stored data

private:

    void _computeMatches(
	const gist& tree, // in
	const Vector& queryStructs, // in: vector<gist_query_t *>
	const vec_t& key, // in
	Vector& matches); // out: vector<int> of indices into queryStructs

    int _computeExtraIos(
	const gist& tree, // in: supplies extension
	const amdb_wkldprofile& profile, // in
	const amdb_treemap& map, // in
	shpid_t leaf, // in: node we're inserting on
	const vec_t& key, // in: key that's being inserted
	const Vector& matches); // in: vector<int>, indices of matching queries

    void _computeExcCovLoss(
	const gist& tree, // in: target tree
	const amdb_wkldprofile& profile, // in
	const amdb_treemap& map, // in: map of target tree
	shpid_t leaf, // in: node we're inserting on
	const vec_t& preBp, // in: pre-insertion BP
	const vec_t& postBp, // in: post-insertion BP
	const vec_t& key, // in: key we're inserting
	const Vector& matches, // in: vector<int>, indices of queries matching key
	const Vector& queryStructs, // in: vector<gist_query_t *>
	int& preExcCovLoss, // out: pre-insertion loss
	int& postExcCovLoss); // out: post-insertion loss

};

#endif

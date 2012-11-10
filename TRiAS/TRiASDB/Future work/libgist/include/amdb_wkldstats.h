// amdb_wkldstats.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_wkldstats.h,v 1.2 2000/03/10 01:39:01 mashah Exp $

#ifndef AMDB_WKLDSTATS_H
#define AMDB_WKLDSTATS_H

#ifdef __GNUG__
#pragma interface "amdb_wkldstats.h"
#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t
#include "amdb_clustering.h"	// for ResultSet
#include "amdb_analysis.h"	// for Parameters

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
 * amdb_wkldstats:
 *
 * Collects all workload performance metrics.
 *
 * About the performance metrics:
 *
 * - 2 versions of the metrics are computed: relative to the optimal
 *   clustering (opt-) and relative to the theoretical minimum
 *   (min-). Although the optimal clustering is the correct basis for
 *   comparisons, we can't be sure that what the hypergraph clustering
 *   comes up with is anywhere near the optimum.
 *
 * - Loss: specifies the loss in performance, measured in I/Os.
 *
 * - Overheads: specify counted I/Os / necessary I/Os, where the
 *   necessary I/Os are derived from the ideal structure (either
 *   theoretical minimum or optimal clustering).
 *
 * The containers used are STL vectors and maps, but there's only a
 * single Vector and Map type that's suitable for integer keys and
 * void* data. The reason is that full use of the template facility
 * resulted in gigantic .o's. The original definitions of the various
 * container fields are left in place for documentation purposes.
 */

class amdb_wkldstats
{

public:

    // per-node performance metrics
    struct NodeStats {
	float utilLoss;
	float utilOh;
	float optClusterLoss;
	float optClusterOh;
	float minClusterLoss;
	float minClusterOh;
	float excCovLoss;
	float excCovOh;

	NodeStats();
    };
    //typedef map<shpid_t, NodeStats *> NodeStatsMap;
    typedef Map NodeStatsMap;

    // per-query statistics and performance metrics
    struct QueryStats {

	// leaf-level metrics
	struct LeafStats {
	    int minIos; // ceil(total volume retrieved / target page capacity)
	    int optimalIos; // # of leaf accesses for optimal clustering
	    float optimalOh; // overhead of optimal clustering w.r.t. theoretical minimum
	    float optLeafOh; // overhead of leafIos
	    float minLeafOh;
	    float randomIos; // avg. # of leaf accesses for random clustering
	    float randomStdDev; // std. dev. of randomIos
	    float optRandomOh; // overhead of randomIos
	    float minRandomOh;
	    float optClusterLoss; // loss due to clustering
	    float optClusterOh; // overhead introduced by clustering
	    float minClusterLoss;
	    float minClusterOh;
	    float utilLoss; // loss due to utilization
	    float utilOh; // overhead introduced by utilization
	    float excCovLoss;
	    float excCovOh;

	    LeafStats() : minIos(0),
	        optimalIos(0), optimalOh(0.0), optLeafOh(0.0),
		minLeafOh(0.0), randomIos(0.0), randomStdDev(0.0), optRandomOh(0.0),
		minRandomOh(0.0), optClusterLoss(0.0), optClusterOh(0.0), 
		minClusterLoss(0.0), minClusterOh(0.0), utilLoss(0.0), utilOh(0.0),
		excCovLoss(0.0), excCovOh(0.0)
	    {
	    }
	};

	// metrics for internal nodes
	struct InternalStats {
	    float utilLoss; // loss due to utilization
	    float excCovLoss;

	    InternalStats() : utilLoss(0.0), excCovLoss(0.0)
	    {
	    }
	};

	LeafStats leafStats;
	InternalStats internalStats;

	QueryStats() : leafStats(), internalStats()
	{
	}
    };


    //////////////////////////////////////////////////////////////////////////
    //
    // Profile State
    //
    //////////////////////////////////////////////////////////////////////////

    // global tree metrics
    NodeStatsMap nodeStats; // per-node metrics, indexed by node number

    // per-query metrics
    //typedef vector<QueryStats *> QueryStatsVect;
    typedef Vector QueryStatsVect;
    QueryStatsVect queryStats;

    // workload summary statistics
    QueryStats statsTotals;


    //////////////////////////////////////////////////////////////////////////
    //
    // Interface
    //
    //////////////////////////////////////////////////////////////////////////

    // binary data to and from files
    rc_t write(
        ostream& s,
	bool ascii);
    rc_t read(
        istream& s);

    void computeStats(
        amdb_wkldprofile& profile,
	const amdb_treemap& map,
	const amdb_clustering::Clustering& optClustering,
	const amdb_analysis::Parameters& parameters);

    // create full NodeStats for given query
    void createNodeStats(
	int queryNo,
        const amdb_wkldprofile& profile,
	const amdb_treemap& treeMap,
	const amdb_analysis::Parameters& parameters,
	NodeStatsMap& map2) const;
    static void clearNodeStatsMap(
        NodeStatsMap& nsMap);

    amdb_wkldstats();
    ~amdb_wkldstats();
    void clear(); // delete all stored data


private:

    void _computeRandomIos(
	const amdb_wkldprofile&	profile,
	const amdb_treemap& map,
	int runs,
	float fillFactor);

    void _computeOptimalIos(
	const amdb_wkldprofile&	profile,
	const amdb_clustering::Clustering& optClustering);

    void _computeQueryStats(
        const amdb_wkldprofile& profile,
	const amdb_treemap& map,
	float targetUtil);

    void _computeStatsTotals(
        const amdb_wkldprofile& profile,
	float targetUtil);

    void _computeNodeStats(
	const amdb_wkldprofile&	profile,
	const amdb_treemap& map,
        float targetUtil);
};

#endif

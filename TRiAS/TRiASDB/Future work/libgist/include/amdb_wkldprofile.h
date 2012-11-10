// amdb_wkldprofile.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_wkldprofile.h,v 1.2 2000/03/10 01:39:01 mashah Exp $

#ifndef AMDB_WKLDPROFILE_H
#define AMDB_WKLDPROFILE_H

#ifdef __GNUG__
#pragma interface "amdb_wkldprofile.h"
#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t
#include "amdb_clustering.h"	// for ResultSet
#include "vec_t.h"		// for vec_t

// VCPORT_B
#ifndef WIN32
class ostream;
#endif
// VCPORT_E

class gist;
class gist_query_t;
class gist_p;
class amdb_treemap;

/*
 * amdb_wkldprofile:
 *
 * Collects all relevant statistics for an entire workload: global I/O
 * and traversal statistics, all result sets, per-query I/O and
 * traversal statistics; excludes performance metrics.
 *
 * The containers used are STL vectors and maps, but there's only a
 * single Vector and Map type that's suitable for integer keys and
 * void* data. The reason is that full use of the template facility
 * resulted in gigantic .o's. The original definitions of the various
 * container fields are left in place for documentation purposes.
 */

class amdb_wkldprofile
{

public:

    // per-query statistics
    struct QueryStats {

	// leaf-level stats
	struct LeafStats {
	    float avgUtil; // avg. util
	    int retrievalVol; // size (in bytes) of all retrieved items
	    int totalIos; // total # of leaves accessed

	    LeafStats() : avgUtil(0.0), retrievalVol(0), totalIos(0)
	    {
	    }
	};

	// stats for internal nodes
	struct InternalStats {
	    int totalIos; // total # of internal nodes accessed

	    InternalStats() : totalIos(0)
	    {
	    }
	};

	LeafStats leafStats;
	InternalStats internalStats;

	QueryStats() : leafStats(), internalStats()
	{
	}
    };

    // aggregate per-node traversal statistics
    struct TraversalStats {
	// typedef vector<shpid_t> ChildVector;
	typedef Vector ChildVector;
	ChildVector children; // traversed child nodes
	// tree structure info, needed for finalizeStats()
	shpid_t pageno; // page # of this node
	bool isLeaf; // true if this is a leaf

	// counters
        int traversalCnt; // # of times traversed
	int retrievalCnt; // # of items retrieved from this subtree
	int retrievalVol; // for leaves: sum of sizes of returned items
	int emptyNode; // # of times we didnt traverse children or return anything
	int emptySubtree; // # of times we didnt return anything from node's subtree
	    // (includes empty nodes)

	// size w/o 'children'
	static const int SIZE;

	// add node stats of query to global node stats
	void add(
	    const TraversalStats& stats);

	TraversalStats& operator=(
	    const TraversalStats& s);

	// == for STL count
	friend bool operator==(
	    const TraversalStats& s1,
	    const TraversalStats& s2)
	{
	    return s1.pageno == s2.pageno;
	}

	TraversalStats();
	TraversalStats(shpid_t pageno);

	friend ostream& operator<<(
	    ostream& os,
	    const TraversalStats& stats);
    };

    // traversal statistics for internal nodes, per-query
    // (slimmed-down version of TraversalStats)
    struct InternalTraversalStats {
	shpid_t pageno; // page # of this node

	// counters
	int retrievalCnt; // # of items retrieved from this subtree
	bool emptyNode; // # of times we didnt traverse children or return anything

        // copy data from TraversalStats
	InternalTraversalStats& operator=(const TraversalStats& s);
	// == for STL count
	friend bool operator==(
	    const InternalTraversalStats& s1,
	    const InternalTraversalStats& s2)
	{
	    return s1.pageno == s2.pageno;
	}

	InternalTraversalStats(): pageno(0), retrievalCnt(0), emptyNode(false)
	{
	}
    };

    // several stats maintained per query
    // Note: We don\'t use STL containers here, because they seem to allocate
    // memory in larger chunks than is necessary and increase the memory consumption
    // of a profile
    struct Query {
	int retrLimit; // retrieval limit (param 'k' in gist::fetch_init())
	char* qual; // qualification used to construct gist_query_t
	int resultSetSize; // # of items in resultSet
	ItemId* resultSet; // array of ItemIds, sorted
        int numEmptyLeaves; // # of items in emptyLeaves
        shpid_t* emptyLeaves; // array of leaves we visited w/o matching data

        // we only keep InternalTraversalStats for internal nodes that we visited,
        // all other nodes can be derived from the result set or emptyLeaves
	int traversalStatsSize; // # of pages recorded in traversalStats
	InternalTraversalStats* traversalStats; // array of TraversalStats, sorted on pageno

	QueryStats stats;

	Query();
	~Query();
    };

    //typedef map<shpid_t, TraversalStats *, less<shpid_t> > TraversalStatsMap;
    typedef Map TraversalStatsMap;
    // totals of stats for entire workload
    struct StatsTotals {
	int retrievedCnt; // sum of result set cardinalities
	int dataCoverage; // number of distinct data items retrieved by queries
	TraversalStatsMap traversalStats;
	    // accumulated over all queries, indexed by page no
	QueryStats stats;

	StatsTotals();
	~StatsTotals();
    };



    //////////////////////////////////////////////////////////////////////////
    //
    // Profile State
    //
    //////////////////////////////////////////////////////////////////////////

    // per-query statistics
    //typedef vector<Query *> QueryVect;
    typedef Vector QueryVect;
    QueryVect queries;

    // workload summary statistics
    StatsTotals statsTotals;

private:

    // containers for currently executing query
    //typedef vector<unsigned int> ResultSet; // contains retrieved item #s of single query
    typedef Vector _ResultSet;
    _ResultSet _resultSet;
    TraversalStatsMap _traversalStats; // single entry for each traversed page

    // use this map to translate retrieved items into their IDs
    const amdb_treemap* _treeMap;


    //////////////////////////////////////////////////////////////////////////
    //
    // Profile Interface
    //
    //////////////////////////////////////////////////////////////////////////

public:

    amdb_wkldprofile();
    //amdb_wkldprofile(const amdb_treemap* map);
    ~amdb_wkldprofile();
    void clear(); // delete all stored data

    rc_t write(
	ostream& s,
	bool ascii);
    rc_t read(
	istream& s);

    /*
     * Trace data gathering
     */

    // adds a new query to the end of queries and makes this the current query
    void addQuery();

    // add item in slot 'idx' on 'page' to result set of current query
    void addToResultSet(
        shpid_t page,
	unsigned idx);

    // update current query with newly traversed page (creates TraversalStats object and sets
    // TraversalStats.traversalCnt to 1)
    void traversePage(
        shpid_t pageno,
	bool isLeaf,
	shpid_t parent);

    // update current query: increase TraversalStats.retrievalCnt by 'count' items
    // returned from leaf 'pageno' and 'volume' bytes to the total retrieval volume
    void countRetrievals(
        shpid_t pageno,
	int numMatches,
	int matches[]);

    // complete traversal stats (TraversalStats.emptyNode) of 
    // current query and compute part of QueryStats
    void finalizeQuery(
        shpid_t rootNo);


    /* 
     * Miscellaneous
     */

    // compute statsTotals.*, except for traversalStats
    void computeTotals();

    // sets Query.qual and .retrLimit
    void setQual(
        int queryNo,
	const char* qual,
	int retrLimit);

    // create full traversal stats for given query (from resultSet, emptyLeaves
    // and traversalStats)
    void createTraversalStats(
        const Query& query,
        TraversalStatsMap& tsMap) const;
    static void clearTraversalStatsMap(
        TraversalStatsMap& map);

    // project query result sets onto clusters
    void projectToClusters(
        const amdb_clustering::Clustering& clustering,
	amdb_clustering::ResultSet*& resultSets) const;

    // avg of avg utils seen by queries
    float avgUtil() const;

    // extract result sets from Query
    void extractResultSets(
        amdb_clustering::ResultSet*& resSets) const;

    void setTreeMap(const amdb_treemap* map) { _treeMap = map; }

    //typedef map<int, int, less<int> > IoCntMap: 
    // records IDs (of items, pages) for the purpose of counting them
    typedef Map IoCntMap;

    // Compute IoCntMap for a single query and a given clustering.
    static void computeIoCntMap(
	Query* query,
	const amdb_clustering::Clustering& clustering,
	IoCntMap& cntMap);

    // Compute # of I/Os for a single query and a given clustering.
    static int computeIoCnt(
	Query* query,
	const amdb_clustering::Clustering& clustering);

    // return size of data that query returns from given page
    int retrievalVolume(
	const Query& query,
	shpid_t pgno) const;

    void projectToNode(
	shpid_t node, // in
	amdb_clustering::ResultSet projectedSets[], // out
	int& numProjected) const; // out

    void copyResultSets(
        const amdb_wkldprofile& source,
	const TranslationMap& map);


private:

    // recursively complete TraversalStats.empty*
    void _finalizeQuery(
        shpid_t subtreeRoot);

};

#endif

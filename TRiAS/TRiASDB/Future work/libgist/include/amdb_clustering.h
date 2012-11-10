// amdb_clustering.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_clustering.h,v 1.4 2000/03/10 01:38:58 mashah Exp $

#ifndef AMDB_CLUSTERING_H
#define AMDB_CLUSTERING_H

//#ifdef __GNUG__
//#pragma interface "amdb_clustering.h"
//#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t

// VCPORT_B
#ifndef WIN32
class ostream;
#endif
// VCPORT_E

class amdb_treemap;

/*
 * amdb_clustering:
 *
 */

class amdb_clustering
{

public:

    static const int invalidNo; // = -1

    // record cluster number for each item
    struct ClusterInfo {
        ItemId itemNo;
	int clusterNo;

	ClusterInfo() : itemNo(invalidNo), clusterNo(invalidNo) {} 
	ClusterInfo(ItemId itemno, int clusterNo) : itemNo(itemNo), clusterNo(clusterNo) {} 
    };
    typedef vector<ClusterInfo> ClusterInfoVect;
    struct Clustering {
        ClusterInfoVect info;

	rc_t read(istream& s);
	rc_t write(ostream& s, bool ascii);
	void sortClusterNo();
	void sortItemNo();
	const ClusterInfo& operator[](int index)  const { return(info[index]); }
	int size() const { return(info.size()); }
	void copy(const Clustering& cl);
    };

    struct ResultSet {
        int itemCnt;
	ItemId *items;

	ResultSet(int cnt, ItemId *items) : itemCnt(cnt), items(items) {}

	ResultSet() : itemCnt(0), items(NULL) {}
    };

    // careful with this one: deallocates 'sets[].items' as well as 'sets'
    static void freeResultSets(
        ResultSet* sets,
	int numResultSets);

    static rc_t optClustering(
        ResultSet *resultSets, // in
	int numResultSets, // in
	float fillFactor, // in
	int numClusters, // in: hmetis param
	int runs, // in: hmetis paramcc
	int ubfactor, // in: hmetis param to specify balance betw. partitions
	const amdb_treemap& map, // in
	Clustering &clustering, // out
	int& numClustersCreated, // out
	int& numRetrieved); // out

    static void randomClustering(
        ResultSet *resultSets,
	int numResultSets,
	float fillFactor,
	bool allItems,
	const amdb_treemap& map,
	Clustering &clustering);

    static void extractRetrieved(
	ResultSet resultSets[],
	int numResultSets,
	Map& retrievedMap,
	int& numNonEmpty);

private:

    // used to arrange retrieved items in random order
    struct RandClustAux {
        ItemId itemNo;
	double rand;

	RandClustAux(ItemId itemNo = 0, double rand = 0.0)
	    : itemNo(itemNo), rand(rand) {}
    };

    struct _less_RandClustAux : binary_function<RandClustAux, RandClustAux, bool> {
        bool operator()(const RandClustAux& x, const RandClustAux& y) {
	    return x.rand < y.rand;
	}
    };

    // sort clustering in ascending cluster number order
    struct _less_clusterNo : binary_function<ClusterInfo, ClusterInfo, bool> {
        bool operator()(const ClusterInfo& x, const ClusterInfo& y) {
	    return x.clusterNo < y.clusterNo;
	}
    };

    // sort clustering in ascending item number order
    struct _less_itemNo : binary_function<ClusterInfo, ClusterInfo, bool> {
        bool operator()(const ClusterInfo& x, const ClusterInfo& y) {
	    return x.itemNo < y.itemNo;
	}
    };

};

#endif

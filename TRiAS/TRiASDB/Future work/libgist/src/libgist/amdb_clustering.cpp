// amdb_clustering.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_clustering.cc,v 1.5 2000/03/15 00:24:19 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_clustering.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable: 4786)
#endif
// VCPORT_E

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "amdb_clustering.h"
#include <assert.h>
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_treemap.h"

// VCPORT_B
#ifndef WIN32

#include <fstream.h>

// STL
#include <vector.h>
#include <algo.h>

#else

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <process.h> /* For _getpid() */

using namespace std;

#endif
// VCPORT_E

const int amdb_clustering::invalidNo = -1;


/////////////////////////////////////////////////////////////////////////
// amdb_clustering::_computeRandomClustering
//
// Description:
// 	- if !allItems, condense items to those that were actually retrieved
//
/////////////////////////////////////////////////////////////////////////

// VCPORT_B
// Rename map to tmap ... VC++ thinks you are referring to the map template
// VCPORT_E

void
amdb_clustering::randomClustering(
    ResultSet *resultSets,
    int numResultSets,
    float fillFactor,
    bool allItems,
    const amdb_treemap &tmap,	// needed for item sizes
    Clustering &clustering)
{
    int minPageFill = (int) ((float) gist_p::data_sz * fillFactor);

    Map retrievedMap; // map<itemno, itemno> : maps original to condensed item no
    if (!allItems) {
	// extract the retrieved item numbers; we don't really need the 
	// condensed item numbers, so there's no invertedMap to translate
	// back to original item numbers
	int dummyInt;
        extractRetrieved(resultSets, numResultSets, retrievedMap, dummyInt);
    }
    if (retrievedMap.size() == tmap.itemMap.size()) {
        allItems = true; // we retrieved all of them anyway
    }

    // reset clustering
    clustering.info.reserve(tmap.itemMap.size());
    ClusterInfoVect::iterator cit;
    for (cit = clustering.info.begin(); cit < clustering.info.end(); cit++) {
	ClusterInfo* info = (ClusterInfo *) cit;
        info->itemNo = invalidNo;
        info->clusterNo = invalidNo;
    }

    // do the random clustering
    typedef vector<RandClustAux> RandVect;
    RandVect clustTmp;

    // load clustTmp
    if (!allItems) {
	// load retrieved data items only from retrievedMap
	Map::iterator it;
	for (it = retrievedMap.begin(); it != retrievedMap.end(); it++) {
	    RandClustAux t((int) (*it).first, drand48()); // first: orig. item #s
	    clustTmp.push_back(t);
	}
    } else {
        // load all existing data items
	ItemId itemNo;
	for (itemNo = 0; itemNo < tmap.itemMap.size(); itemNo++) {
	    RandClustAux t(itemNo, drand48());
	    clustTmp.push_back(t);
	}
    }

    // XXX debug
    RandVect::iterator rit2;
    for (rit2 = clustTmp.begin(); rit2 != clustTmp.end(); rit2++) {
        int x = rit2->itemNo;
	double r = rit2->rand;
    }

    _less_RandClustAux comp;
    sort(clustTmp.begin(), clustTmp.end(), comp);

    // partition items into clusters that stay within page boundaries
    // (>= minPageFill && <= gist_p::data_sz)
    int clustNo = 0;
    int pageUtil = 0;
    RandVect::iterator rit;
    for (rit = clustTmp.begin(); rit != clustTmp.end(); rit++) {
	ItemId itemNo = (*rit).itemNo;
	smsize_t size = tmap.itemInfo(itemNo)->size;
	if (size + pageUtil > gist_p::data_sz) {
	    // start new cluster
	    clustNo++;
	    pageUtil = 0;
	}
	// 'add' item to cluster and record assignment
	pageUtil += size;
	clustering.info[itemNo].itemNo = itemNo;
	clustering.info[itemNo].clusterNo = clustNo;
	if (pageUtil >= minPageFill) {
	    // start new cluster
	    clustNo++;
	    pageUtil = 0;
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_clustering::optClustering - compute hypergraph clustering
//
// Description:
//	- prepares a hypergraph, writes it to a file and calls
//	  hmetis to do the clustering
//	- we don't call the hmetis clustering routine directly, because it
//	  is not available on all the platforms we need; instead, we call
//	  the hmetis frontend
// 	- The set of hyperedges consists of all the queries in the clustering and
// 	  the set of vertices is restricted to those items that are retrieved by any of
// 	  the queries. This is necessary for hmetis to accept the graph. The
// 	  non-retrieved items are assigned an invalid page number in the clustering.
//	- The resultSets must contain ItemIds that are recorded in the map
//	  (map needed to find items' sizes)
//	- if numClusters != 0, we produce that many clusters, otherwise we  compute the
//	  required number of clusters from the fill factor and the amount of data present
//	- if numClusters != 0, we use the fill factor to specify the allowed degree
//	  of imbalance (hmetis command line parameter)
//
// Return Values:
//      RCOK
//	eFILEERROR
//	eCLUSTERERROR
/////////////////////////////////////////////////////////////////////////

// VCPORT_B
// Replaces map with tmap ... VC++ thinks you are referring to the map template
// VCPORT_E

rc_t
amdb_clustering::optClustering(
    ResultSet *resultSets,	  	// result sets 
    int numResultSets,			// number of result sets 
    float fillFactor,			// target page utilization
    int numClusters,			// target number of clusters
    int runs,				// hmetis param: # of runs
    int ubfactor, 			// in: hmetis param to specify balance betw. partitions
    const amdb_treemap &tmap,		// tree's item map
    Clustering &clustering,		// out: optimal clustering
    int& numCreated,			// out: number of clusters created
    int& numRetr)			// out: number of retrieved items
{
    // write workload out as hypergraph
    char filename[1024];

	// VCPORT_B
#ifndef WIN32
    (void) sprintf(filename, "%x.hgr", getpid());
#else
	(void) sprintf(filename, "%x.hgr", _getpid());
#endif
	// VCPORT_E

    ofstream hgraph(filename);

    if (!hgraph.good()) {
        return eFILEERROR;
    }

    Map retrievedMap; // map<itemno, itemno>: from orig. item no to condensed item no.
    int numNonEmpty;
    extractRetrieved(resultSets, numResultSets, retrievedMap, numNonEmpty);
        // collect retrieved items and assign contig. numbers
    // don't use numRetr here, it might point to the same variable as
    // numClustersCreated
    int numRetrieved = retrievedMap.size();
    numRetr = numRetrieved; // explicit copy is safer

    // preamble: # of data items and # of queries, file in format 10 (weighted vertices)
    hgraph << numNonEmpty << " " << numRetrieved << " 10" << endl;

    // the hyperedges = result sets
    int i, j;
    for (i = 0; i < numResultSets; i++) {
	if (resultSets[i].itemCnt == 0) {
	    // hypergraph file must not contain blank lines
	    continue;
	}
	for (j = 0; j < resultSets[i].itemCnt; j++) {
	    ItemId item = resultSets[i].items[j];
	    hgraph << ((unsigned) retrievedMap[item])  << " ";
	        // hmetis wants vertices starting from 1, condensed item numbers
		// are 1-based
	}
	hgraph << endl;
    }

    // the weights for the vertices (retrieved data item sizes);
    // compute the total size in bytes
    smsize_t totalSize = 0;
    Map::iterator mit;
    for (mit = retrievedMap.begin(); mit != retrievedMap.end(); mit++) {
	unsigned int itemNo = (*mit).first;
	smsize_t size = tmap.itemInfo(itemNo)->size;
        hgraph << size << endl;
	totalSize += size;
    }

    // check for errors
    if (!hgraph) {
        return eFILEERROR;
    }
    hgraph.close();

    int numClustersCreated;
    if (numClusters == 0) {
	// determine the required number of clusters
	smsize_t avgSize = totalSize / retrievedMap.size();
	smsize_t clustSize =
	    (int) ((double) gist_p::data_sz / (double) avgSize * fillFactor);
	numClustersCreated = (int) ceil((double) retrievedMap.size() / (double) clustSize);
	printf("avg size: %d, clust size: %d, # clusters: %d\n", (int) avgSize,
	    (int) clustSize, numClustersCreated);
    } else {
        // need to do something with fillFactor
	numClustersCreated = numClusters;
    }
    numCreated = numClustersCreated;

    if (numClustersCreated < 2) {
	// we only have one "cluster", we don't have to call hmetis

	// reset clustering
	clustering.info.erase(clustering.info.begin(), clustering.info.end());
	clustering.info.reserve(tmap.itemMap.size());

	// copy 'retrievedMap' to 'clustering' (iterator will walk through retrievedMap
	// in itemNo order), filling up gaps (caused by non-retrieved items);
	// assign clusterNo 0
	int nextItemNo = 0; // items start at 0
	ClusterInfo info;
	for (mit = retrievedMap.begin(); mit != retrievedMap.end(); mit++) {
	    int itemNo = (*mit).first;
	    while (nextItemNo < itemNo) {
		// fill up gaps
		info.itemNo = nextItemNo;
		info.clusterNo = invalidNo;
		clustering.info.push_back(info);
		nextItemNo++;
	    }
	    info.itemNo = itemNo;
	    info.clusterNo = 0;
	    clustering.info.push_back(info);
	    nextItemNo = itemNo + 1;
	}
	// fill up with remaining non-retrieved items
	int i;
	for (i = nextItemNo; i < tmap.itemMap.size(); i++) {
	    info.itemNo = i;
	    info.clusterNo = invalidNo;
	    clustering.info.push_back(info);
	}

	return (RCOK);
    }

    char hmetiscmd[1024];
    sprintf(hmetiscmd, "hmetis %s %d %d %d 3 3 1 1 0", filename, numClustersCreated,
        ubfactor, runs);
    printf("%s\n", hmetiscmd);
    int res = system(hmetiscmd);
    if (res == -1) {
	// hmetis crashed
	return eCLUSTERERROR;
    }

    // First, load the clustering information into clusterMap, then copy the contents of 
    // this map to an array. We must do it in two steps, because the 
    // clustering info reflects the condensed item numbering we obtained from 
    // retrievedMap. In order to convert the condensed item numbers into the original 
    // item numbers, we need to invert retrievedMap (into invertedMap).
    Map invertedMap; // map<itemno, itemno, less<itemno>>: condensed to orig. item no
    for (mit = retrievedMap.begin(); mit != retrievedMap.end(); mit++) {
        invertedMap[(unsigned int) (*mit).second] = (void *) (*mit).first;
    }

// VCPORT_B
#ifndef WIN32
    (void) sprintf(filename, "%x.hgr.part.%-d", getpid(), numClustersCreated);
#else
    (void) sprintf(filename, "%x.hgr.part.%-d", _getpid(), numClustersCreated);
#endif
// VCPORT_E

    printf("reading clustering: %s\n", filename);
    ifstream clustfile(filename);
    if (!clustfile.good()) {
        return eFILEERROR;
    }
    const int BUFLEN = 16;
    char buf[BUFLEN];
    // map<shpid_t, int, less<shpid_t> > clusterMap: translate from the
    // (original, non-condensed) item number to the cluster number
    Map clusterMap;
    for (i = 1; i <= numRetrieved; i++) {
        clustfile.getline(buf, BUFLEN);
	unsigned int clust;
	sscanf(buf, "%u", &clust);
	unsigned int itemNo = (unsigned int) invertedMap[i]; // 1-based
	clusterMap[itemNo] = (void *) clust;
    }


    // reset clustering
    clustering.info.erase(clustering.info.begin(), clustering.info.end());
    clustering.info.reserve(tmap.itemMap.size());

    // copy 'clusterMap' to 'clustering' (iterator will walk through clusterMap
    // in itemNo order), filling up gaps (caused by non-retrieved items)
    int nextItemNo = 0; // items start at 0
    ClusterInfo info;
    for (mit = clusterMap.begin(); mit != clusterMap.end(); mit++) {
	int itemNo = (*mit).first;
	while (nextItemNo < itemNo) {
	    // fill up gaps
	    info.itemNo = nextItemNo;
	    info.clusterNo = invalidNo;
	    clustering.info.push_back(info);
	    nextItemNo++;
	}
	info.itemNo = itemNo;
	info.clusterNo = (int) (*mit).second;
	clustering.info.push_back(info);
	nextItemNo = itemNo + 1;
    }
    // fill up with remaining non-retrieved items
    for (i = nextItemNo; i < tmap.itemMap.size(); i++) {
	info.itemNo = i;
	info.clusterNo = invalidNo;
	clustering.info.push_back(info);
    }

    // XXX debug: find entries with itemno = 0
    amdb_clustering::ClusterInfoVect::iterator cit;
    int cnt = 0;
    int cntInv = 0;
    for (cit = clustering.info.begin(); cit != clustering.info.end(); cit++) {
        if (cit->itemNo == 0) cnt++;
        if (cit->clusterNo == invalidNo) {
	    cntInv++;
	}
	assert(cnt <= 1);
    }
    cout << "non-retrieved: " << cntInv << endl;

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// amdb_clustering::extractRetrieved - extract item numbers for result sets
//
// Description:
//	- creates a map from original item numbers (those give in the 
//	  result sets) to condensed item numbers (which are a contiguous
//	  numbering of the items)
//
/////////////////////////////////////////////////////////////////////////

void
amdb_clustering::extractRetrieved(
    ResultSet resultSets[],	// hypergraph 
    int numResultSets,		// number of edges in hypergraph
    Map& retrievedMap,		// out: map of orig. itemno to condensed itemno
    int& numNonEmpty)		// out: number of non-empty result sets
{
    ItemId itemCounter = 1; // start at 1, otherwise can't distinguish from NULL
    int i;
    numNonEmpty = 0;
    for (i = 0; i < numResultSets; i++) {
	ResultSet *rs = &resultSets[i];
	int j;
	if (rs->itemCnt > 0) {
	    numNonEmpty++;
	}
	for (j = 0; j < rs->itemCnt; j++) {
	    ItemId item = rs->items[j];
	    if (retrievedMap[item] == NULL) {
		// This item hasn't been retrieved yet. Assign it the next number.
		retrievedMap[item] = (void *) itemCounter;
		itemCounter++;
	    }
	}
    }
    assert(retrievedMap.size() == itemCounter -1);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_clustering::freeResultSets - dealloc array of ResultSet
//
// Description:
//	- also deallocates sets[].items
///////////////////////////////////////////////////////////////////////////////

void
amdb_clustering::freeResultSets(
    ResultSet* sets,
    int numResultSets)
{
    int i;
    for (i = 0; i < numResultSets; i++) {
        delete [] sets[i].items;
    }
    delete [] sets;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_clustering::Clustering::sortClusterNo - sort on clusterNo
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_clustering::Clustering::sortClusterNo()
{
    _less_clusterNo comp;
    sort(info.begin(), info.end(), comp);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_clustering::Clustering::sortItemNo - sort on itemNo
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_clustering::Clustering::sortItemNo()
{
    _less_itemNo comp;
    sort(info.begin(), info.end(), comp);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_clustering::Clustering::read - read from input stream
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_clustering::Clustering::read(
    istream& s)
{
    ClusterInfoVect::size_type size;
    s.read((char *) &size, sizeof(size));
    info.reserve(size);
    int i;
    for (i = 0; i < size; i++) {
	ClusterInfo cinfo;
        s.read((char *) &cinfo, sizeof(cinfo));
	info.push_back(cinfo);
    }
    return(RCOK);
}

///////////////////////////////////////////////////////////////////////////////
// amdb_clustering::Clustering::write - write to output stream
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_clustering::Clustering::write(
    ostream& s,
    bool ascii)
{
    
  if (!ascii) {
    ClusterInfoVect::size_type size = info.size();
    s.write((char *) &size, sizeof(size));
    ClusterInfoVect::iterator cit;
    for (cit = info.begin(); cit != info.end(); cit++) {
      s.write((char *) cit, sizeof(*cit));
    }
    return(RCOK);
  }
  else {
    ClusterInfoVect::size_type size = info.size();
    s << size << "\n";
    ClusterInfoVect::iterator cit;
    for (cit = info.begin(); cit != info.end(); cit++) {
      s << cit << "\n"; 
    }
    return(RCOK);
  }
}

void
amdb_clustering::Clustering::copy(
    const Clustering& cl)
{
    info.erase(info.begin(), info.end());
    info.insert(info.end(), cl.info.begin(), cl.info.end());
}

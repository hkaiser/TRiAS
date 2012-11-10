// gist_amdb.cc
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_amdb.cc,v 1.12 2000/03/15 00:24:24 mashah Exp $

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786) // Templates can cause names to get too long for
							  // debug information. Disables this warning.
#endif
// VCPORT_E

#include <math.h>
#include <stdlib.h>

#include <stdio.h>

#include "gist_compat.h"	// for MAXDOUBLE
#include "gist_defs.h"

#include "gist_ext.h"
#include "gist_cursor.h"
#include "gist_cursorext.h"
#include "gist_disppredcursor.h"
#include "gist_ustk.h"
#include "amdb_wkldprofile.h"
#include "amdb_treemap.h"
#include "amdb_ext.h"
#include "gist.h"

// STL
// VCPORT_B
#ifdef WIN32

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#else

#include <iostream.h>
#include <fstream.h>
#include <vector.h>
#include <algo.h>

#endif
// VCPORT_E


amdb_ext_t* amdb_ext_t::amdb_ext_list[gist_ext_t::gist_numext];

// debug

void 
pclust(amdb_clustering::Clustering* clust, int beg, int end)
{
    if (end == 0 || end >= clust->size()) {
        end = clust->size() - 1;
    }
    amdb_clustering::ClusterInfoVect::iterator it = clust->info.begin() + beg;
    int i;
    for (i = beg; i <= end; i++, it++) {
        cout << i << " [i: " << it->itemNo << "  c: " << it->clusterNo;
	cout << "] ";
    }
    cout << endl; // flush to see on screen
}


/////////////////////////////////////////////////////////////////////////
// amdb_ext_t - Constructor
//
// Description:
//	- registers amdb extension in extension list
//
/////////////////////////////////////////////////////////////////////////

amdb_ext_t::amdb_ext_t(
    gist_ext_t::gist_ext_ids 	id,
    PenaltyFct 			p,
    DisplayFct 			d,
    DisplayPredsFct 		dp,
    ConsistentFct		consistent)
    : id(id), penalty(p), display(d), displayPreds(dp), consistent(consistent)
{
    amdb_ext_list[id] = this;
}


/////////////////////////////////////////////////////////////////////////
// gist::_optBreakNotify - _build_level inserted a page break
//
// Description:
//	- _build_level inserted a page break after 'itemCnt' items
//	  that is not part of our clustering, we must now update the clustering
//	- increase cluster numbers for all items starting from itemCnt+1 (in 
//	  optClustering) by 1
/////////////////////////////////////////////////////////////////////////

void
gist::_optBreakNotify(
    int		itemCnt,
    void*	param)
{
    _OptTreeBuildState* state = (_OptTreeBuildState *) param;
    amdb_clustering::ClusterInfoVect::iterator it;
    for (it = state->optClustering->info.begin() + itemCnt;
        it != state->optClustering->info.end(); it++) {

	it->clusterNo++;
    }
}


/////////////////////////////////////////////////////////////////////////
// gist::_constructBpMap - construct treemap for BP file stream
//
// Description:
//	- read bpStream from beginning to end and record all BPs
//	  in map (only read the recorded key lengths and skip the keys)
/////////////////////////////////////////////////////////////////////////

void
gist::_constructBpMap(
    ifstream&		bpStream,
    amdb_treemap&	bpMap)
{
    bpStream.seekg(0); // start from beginning
    int itemCnt = 0;
    for (;;) {
        streampos pos = bpStream.tellg(); // position of next BP
	int klen;

// VCPORT_B
#ifdef WIN32
	bpStream.read((char *) &klen, sizeof(klen));
#else
	bpStream.read((void *) &klen, sizeof(klen));
#endif
// VCPORT_E

	if (bpStream.fail()) {
	    // we seeked past EOF: we're done
	    break;
	}
	int size = gist_p::rec_size(klen, sizeof(shpid_t));
	bpMap.addFileItem(pos, size);
	itemCnt++;
	// skip to next BP
	bpStream.seekg(klen + sizeof(shpid_t), ios::cur);
    }
    bpStream.clear(); // reset state for scan in _optBpStream()
    bpStream.seekg(0); // ... and go back to beginning
}


/////////////////////////////////////////////////////////////////////////
// gist::_initLeafBuildState - initialize state for _optItemStream()
//
// Description:
//	- sort the optimal clustering we obtain from the profile in
//	  ascending cluster number order
//	- our leafItemMap is also our optimal clustering, since we're 
//	  dealing with leaf-level items
/////////////////////////////////////////////////////////////////////////

void
gist::_initLeafBuildState(
    const amdb_clustering::Clustering* optClustering, // in
    const amdb_treemap* tmap, // in
    _OptTreeBuildState&	    state) // out
{
    state.level = 0;
    state.leafItemMap = new amdb_clustering::Clustering();
    state.leafItemMap->copy(*optClustering);
    state.tupMap = tmap;
    state.deallocMap = false;
    state.optClustering = state.leafItemMap;
    state.optClustering->sortClusterNo();
}


/////////////////////////////////////////////////////////////////////////
// gist::_OptTreeBuildState::update - update leafItemMap with optClustering
//
// Description:
//	- after building an internal level, we need to update leafItemMap
//	  to reflect the clustering at the level just build, which 
//	  is the input for the next level
//	- also, delete tupMap and optClustering
//
/////////////////////////////////////////////////////////////////////////

void
gist::_OptTreeBuildState::update()
{
    if (level == 0) {
	// nothing to update or deallocate for leaf level
        return;
    }

    // we just built an internal level:
    // update leafItemMap with the clustering of this
    // level
    optClustering->sortItemNo();
	// the itemNo of optClustering is the current clusterNo of leafItemMap
    amdb_clustering::ClusterInfoVect::iterator it;
    for (it = leafItemMap->info.begin(); it != leafItemMap->info.end(); it++) {
	if (it->clusterNo != amdb_clustering::invalidNo) {
	    it->clusterNo = (*optClustering)[it->clusterNo].clusterNo;
	}
    }

    // clean up stuff from previous level
    clear();
}


/////////////////////////////////////////////////////////////////////////
// gist::_initInternalBuildState - initialize state for _optBpStream()
//
// Description:
//	- if the previous level was the leaf level, sort leafItemMap on
//	  the itemNo
//	- produce an optimal clustering of the items of this level,
//	  which is sorted on the clusterNo and stored in optClustering
//
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_initInternalBuildState(
    _OptTreeBuildState&	    state)
{
    if (state.level == 0) {
        // we just finished the leaf level, for which we sorted leafItemMap
	// on the clusterNo; we go back to the itemNo ordering now in order
	// to allow us to project the query result sets
	state.leafItemMap->sortItemNo();
    }

    state.level++;

    amdb_clustering::ResultSet* resultSets = NULL;
    state.profile->projectToClusters(*state.leafItemMap, resultSets);
    amdb_treemap* bpMap = new amdb_treemap();
    _constructBpMap(*state.bpStream, *bpMap);

    // cluster BPs according to traversal patterns in workload (equal-sized 
    // partitions)
    amdb_clustering::Clustering* optClustering = new amdb_clustering::Clustering();
    int numRetrieved, numClusters;
    W_DO(amdb_clustering::optClustering(resultSets, state.profile->queries.size(), 
        state.fillFactor, 0, 10, 1, *bpMap, *optClustering, numClusters, numRetrieved));
    // we must traverse every BP
    assert(numRetrieved == bpMap->itemMap.size());

    // sort the optimal clustering on the cluster number, we return
    // tuples in that order
    if (state.optClustering != state.leafItemMap) {
	// we allocated this in a previous call
        delete state.optClustering;
    }
    state.optClustering = optClustering;
    state.optClustering->sortClusterNo();
    state.tupMap = bpMap;
    state.deallocMap = true;

    // don't need resultSets anymore
    amdb_clustering::freeResultSets(resultSets, state.profile->queries.size());

    return (RCOK);
}


/////////////////////////////////////////////////////////////////////////
// gist::_optBpStream - returns BPs in order of optimal clustering
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_optBpStream(
    void* 	key,
    int&	klen,
    void* 	data,
    int&	dlen,
    shpid_t&	child,
    void* 	param)
{
    _OptTreeBuildState* state = (_OptTreeBuildState *) param;

    if (state->nextItem == state->optClustering->size()) {
        // no more tuples left, we're done
	return (eEOF);
    }

    const amdb_clustering::ClusterInfo* cinfo = &(*state->optClustering)[state->nextItem];
    // see if we crossed a page boundary
    if (state->nextItem > 0) {
        if ((*state->optClustering)[state->nextItem - 1].clusterNo != cinfo->clusterNo) {
	    if (!state->returnedBreak) {
		// we crossed a page boundary and haven't returned a page break to 
		// _build_level yet; we'll do that now (without advancing nextItem)
		state->returnedBreak = true;
		klen = 0;
		return(RCOK);
	    } else {
		// we already returned the break, we must now return the next tuple
		state->returnedBreak = false;
	    }
	}
    }

    // fetch next item from bpStream
    state->nextItem++;
    const amdb_treemap::RecInfo *info =
        state->tupMap->itemInfo(cinfo->itemNo);
    ifstream& s = *state->bpStream;
    s.seekg(info->loc.fileLoc, ios::beg);

// VCPORT_B
#ifdef WIN32
	s.read((char *) &klen, sizeof(klen));
#else
    s.read((void *) &klen, sizeof(klen));
#endif
// VCPORT_E

    if (s.bad()) {
	// bad: we seeked past EOF
        return(eFILEERROR);
    }

// VCPORT_B
#ifdef WIN32
	s.read((char *)key, klen);
#else
	s.read(key, klen);
#endif
// VCPORT_E
    
    dlen = 0;

// VCPORT_B
#ifdef WIN32
    s.read((char *) &child, sizeof(child));
#else
    s.read((void *) &child, sizeof(child));
#endif
// VCPORT_E

    if (!(s.eof() || s.good())) {
        return(eFILEERROR);
    }

    return(RCOK);
}

void
tstr(ifstream& s, streampos loc)
{
    int x;
    streampos oldpos = s.tellg();
    s.seekg(loc);

// VCPORT_B
#ifdef WIN32
	s.read((char *) &x, sizeof(x));
#else
    s.read((void *) &x, sizeof(x));
#endif
// VCPORT_E

    streampos pos = s.tellg();
    cout << x << endl;
    s.seekg(oldpos);
}


/////////////////////////////////////////////////////////////////////////
// gist::_optItemStream - returns items in order of optimal clustering
//
// Description:
//	- optClustering of profile might contain non-retrieved items (clusterNo
//	  == invalidNo), we need to skip those
//
// Return Values:
//      RCOK: with klen == 0: force page break, klen != 0: return tuple
//	eEOF: no more tuples
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_optItemStream(
    void* 	key,
    int&	klen,
    void* 	data,
    int&	dlen,
    shpid_t&	child,
    void* 	param)
{
    _OptTreeBuildState* state = (_OptTreeBuildState *) param;

    if (state->nextItem == state->leafItemMap->size()) {
        // no more tuples left, we're done
	return (eEOF);
    }

    // skip non-retrieved items (with clusterno == invalidNo == -1):
    // they precede all retrieved items in leafItemMap
    const amdb_clustering::ClusterInfo* cinfo;
    if (state->nextItem == 0) {
	do {
	    cinfo = &(*state->leafItemMap)[state->nextItem];
	    state->nextItem++;
	} while (cinfo->clusterNo == amdb_clustering::invalidNo &&
	    state->nextItem < state->leafItemMap->size());

	if (state->nextItem == state->leafItemMap->size()) {
	    // there were no retrieved items
	    return(eEOF);
	}

	// rewind nextItem to point to current item
	state->nextItem--;
    } else {
        // fetch the next item
	cinfo = &(*state->leafItemMap)[state->nextItem];
    }

    // see if we crossed a page boundary (and the previous item wasn't skipped 
    // because it has an invalid cluster number)
    if (state->nextItem > 0) {
        if ((*state->leafItemMap)[state->nextItem - 1].clusterNo != cinfo->clusterNo &&
            (*state->leafItemMap)[state->nextItem - 1].clusterNo !=
	    amdb_clustering::invalidNo) {

	    if (!state->returnedBreak) {
		// we crossed a page boundary and haven't returned a page break to 
		// _build_level yet; we'll do that now (without advancing nextItem)
		state->returnedBreak = true;
		klen = 0;
		return (RCOK);
	    } else {
		// we already returned the break, we must now return the next tuple
		state->returnedBreak = false;
	    }
	}
    }

    // safe to advance nextItem
    state->nextItem++;

    // fetch next item from its leaf page
    const amdb_treemap::RecInfo *info =
        state->tupMap->itemInfo(cinfo->itemNo);

    gist_p page;
    W_DO(_static_fix_page(*state->file, page, info->loc.treeLoc.page, LATCH_SH));
    
    // make a copy of the key
    vec_t tup(key, klen);
    state->ext->getKey(page, info->loc.treeLoc.slot, tup);
    if (tup.ptr(0) != key) {
        // getKey() changed tup to point to the page, we 
	// need to make a copy 
	(void) memcpy(key, tup.ptr(0), tup.len(0));
    }
    klen = tup.len(0);

    // make a copy of the data
    const keyrec_t& rec = page.rec(info->loc.treeLoc.slot);
    (void) memcpy(data, rec.elem(), rec.elen());
    dlen = rec.elen();

    child = 0;
    _static_unfix_page(*state->file, page);

    return (RCOK);
}


/////////////////////////////////////////////////////////////////////////
// gist::createOpt - create 'optimal' tree based on opt. clustering
//
// Description:
//	- bulk-load tree level by level, using the hypergraph clustering
//	  to produce an ordered input stream
//	- when calling _build_level(), specify a fill factor of 1.0 regardless
//	  of the actual fill factor (a lot of times, the hypergraph clustering
//	  produces clusters that are just a bit large, and we don't want to break
//	  those up)
//	- installs opt tree and translation map in profile
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::createOpt(
    const char* 			fileName, // in
    float				fillFactor, // in
    const amdb_wkldprofile&	    	profile, // in
    const amdb_clustering::Clustering& 	optClustering, // in: hypergraph clustering
    const amdb_treemap&			tmap, // in: our amdb_treemap
    Rid2ItemIdMap& 		    	ridMap) // out
{
    _OptTreeBuildState buildState;
    char* temp1 = "cotemp1"; // to be changed later
    char* temp2 = "cotemp2";
    bool toTemp1 = true; // true: write BPs to temp1

	// VCPORT_B
#ifdef WIN32
	ofstream bpOutStream(temp1, ios_base::out | ios_base::binary );
	ofstream tmpfile(temp2, ios_base::out | ios_base::binary );
#else
    ofstream bpOutStream(temp1); // creates empty file
    ofstream tmpfile(temp2); // creates empty file
#endif

    tmpfile.close();

	// This is just a precaution, in case tmpfile is used again in this function
#ifdef WIN32
	tmpfile.clear();
#endif

#ifdef WIN32
	ifstream bpInStream(temp2, ios_base::in | ios_base::binary );
#else
    ifstream bpInStream(temp2); // opens empty file
#endif
	// VCPORT_E

    if (fillFactor > 1.0) fillFactor = 1.0; // can't fill page more than once
    gist* optTree = new gist(); // the one we're building

    // these don't change between levels
    buildState.profile = &profile;
    buildState.file = &_file;
    buildState.ext = _ext;
    buildState.fillFactor = fillFactor;
    buildState.bpStream = &bpInStream;

    // create the root (must be in page 1)
    rc_t status;
    if ((status = optTree->create(fileName, _ext)) != RCOK) {
        delete optTree;
	return(status);
    }

    int level = 0;
    for (;;) {
        level++;
	TupleStream tstream;
	if (level == 1) {
	    // read the leaf items in opt clustering order
	    tstream = _optItemStream;
	    _initLeafBuildState(&optClustering, &tmap, buildState);
	} else {
	    // read BPs in opt clustering order
	    tstream = _optBpStream;
	    W_DO(_initInternalBuildState(buildState));
	}
	buildState.nextItem = 0;

	int pageCnt;
	gist_p lastPage;
	W_DO(optTree->_build_level(tstream, (void *) &buildState, 1.0, level, 
	    rootNo, bpOutStream, _optBreakNotify, pageCnt, lastPage));

	// build rid map, now that the leaf level is build (and the exact
	// clustering known)
	if (level == 1) {
	    amdb_clustering::ClusterInfoVect::iterator it;
	    int slot = 0;
	    int prevClusterNo = 0;
	    for (it = buildState.leafItemMap->info.begin();
	        it != buildState.leafItemMap->info.end();
		it++, slot++) {

		if (prevClusterNo != it->clusterNo) {
		    // we crossed a cluster boundary, reset slot 
		    slot = 0;
		    prevClusterNo = it->clusterNo;
		}
		Rid rid;
		rid.page = it->clusterNo + 2; // + 2: cluster 0 is on page 2
		rid.slot = slot;
		ridMap[rid] = it->itemNo;
	    }
	}

	// leave buildState intact, we need optClustering for the next level
	buildState.update();

	// finished with streams for now
	bpOutStream.close();
	bpInStream.close();

	// VCPORT_B
	// Because the stream state doesn't get rest when file is closed.
#ifdef WIN32
	bpOutStream.clear();
	bpInStream.clear();
#endif
	// VCPORT_E

	if (pageCnt == 1) {
	    // The last level we produced contains only 1 page: this
	    // is the root level. We must copy the last page of this
	    // level to the (fixed-location) root page, adjust the
	    // level in the root page's header and then delete the
	    // last page.
	    gist_p rootPage;
	    W_DO(optTree->_fix_page(rootPage, rootNo, LATCH_EX));
	    W_DO(lastPage.copy(rootPage));
	    rootPage.set_level(level);
	    optTree->_unfix_page(rootPage);
	    W_DO(optTree->_file.freePage(lastPage._descr));
	    lastPage._pp = NULL;

	    if (unlink(temp1) != 0) return eFILEERROR;
	    if (unlink(temp2) != 0) return eFILEERROR;

	    optTree->close();
	    break;
	} else {
	    // lastPage is still fixed
	    optTree->_unfix_page(lastPage);

	    // switch BP input and output for the next level
	    toTemp1 = (toTemp1 ? false : true);
	    if (toTemp1) {
		// write to temp1, read from temp2

		// VCPORT_B
#ifdef WIN32
			bpOutStream.open(temp1, ios::out | ios::binary );
			bpInStream.open(temp2, ios::in | ios::binary );
#else
			bpOutStream.open(temp1);
			bpInStream.open(temp2);
#endif
	
	    } else {
#ifdef WIN32
			bpOutStream.open(temp2, ios::out | ios::binary );
			bpInStream.open(temp1, ios::in | ios::binary );
#else
			bpOutStream.open(temp2);
			bpInStream.open(temp1);
#endif
	    }
		// VCPORT_E
	}
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// setBreakHandler - set amdb break handler
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

void
gist::setBreakHandler(
    amdb_breakpoints::BreakHandler handler) 
{
    _breakHandler = handler;
}


/////////////////////////////////////////////////////////////////////////
// gist::computeTreeMap - driver for _computeTreeMap
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::computeTreeMap(
    amdb_treemap* tmap) // out
{
    assert(tmap != NULL);
    return (_computeTreeMap(tmap, rootNo));
}


/////////////////////////////////////////////////////////////////////////
// computeTreeMap - traverse tree recursively to compute stats
//
// Description:
// 	- computes item map and/or node stats (not computed if 
//	  corresponding parameter is NULL)
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_computeTreeMap(
    amdb_treemap* tmap, // out
    shpid_t pgno) // in: root of subtree
{
    gist_p page;
    W_DO(_fix_page(page, pgno, LATCH_SH));

    int recCnt = page.nrecs();
    unsigned int min = MAXINT, max = 0;
    float avg = 0;
    for (int i = 0; i < recCnt; i++) {
	const keyrec_t& tup = page.rec(i);

	// compute min, max and avg of key lengths
	min = (min <= tup.klen() ? min : tup.klen());
	max = (max >= tup.klen() ? max : tup.klen());
	avg += (float) tup.klen();

	if (!page.is_leaf()) {
	    _computeTreeMap(tmap, tup.child());
	} else if (tmap != NULL) {
	    // record every item in map; we cannot use
	    // gist_p::rec_size(idx) to compute the size, because this
	    // ignores alignment requirements and the slot index
	    tmap->addTreeItem(pgno, i, gist_p::rec_size(tup.klen(), tup.elen()));
	}
    }

    // record page (also for non-leaf pages, might be necessary in
    // amdb_wkldstats::_computeQueryStats())
    tmap->addPage(pgno, page.nrecs(), page.level(), min, avg / (float) recCnt, max,
	1.0 - ((float) page.usable_space()/(float) gist_p::data_sz));

    _unfix_page(page);
    return RCOK;
}


///////////////////////////////////////////////////////////////////////////////
// gist::getPredInfo -
//	get display-relevant information about predicates in subtree
//
// Description:
//	- returns info about all predicates, including BPs
//	- initialize 'color' to 0
//
// Return Values:
//      RCOK
//	eARRAYSIZE: 'predInfo' is too small
///////////////////////////////////////////////////////////////////////////////

rc_t
gist::getPredInfo(
    shpid_t		subtreeRoot, // in
    int			levels, // in: # of levels to look at
    DisplayPredInfo	predInfo[], // out
    int& 		numPredInfo) // in/out
{
    int next = 0; // start filling predInfo at 0

    // we pass off ROOTPAGE as this page's parent, because we don't know the
    // real parent; for the purposes of tree vis, this inaccuracy doesn't
    // matter
    rc_t status = _getPredInfo(subtreeRoot, ROOTPAGE, levels, predInfo, next,
        numPredInfo);
    if (status != RCOK) {
        return(status);
    }
    numPredInfo = next; // _getPredInfo() maintains next
    return(RCOK);
}

///////////////////////////////////////////////////////////////////////////////
// gist::_getPredInfo - recursive traversal of subtree
//	get display-relevant information about predicates in subtree
//
// Description:
//
// Return Values:
//      RCOK
//	eARRAYSIZE: 'predInfo' is too small
///////////////////////////////////////////////////////////////////////////////

rc_t
gist::_getPredInfo(
    shpid_t		subtreeRoot, // in
    shpid_t		parent, // in
    int			levels, // in: # of levels still to look at
    DisplayPredInfo	predInfo[], // out
    int&	    	next, // in: next element in predInfo to set
    int 		numPredInfo) // in
{
    gist_p page;

    W_DO(_fix_page(page, subtreeRoot, LATCH_SH));
    int recCnt = page.nrecs();

    // record pred info in predInfo
    int i;
    for (i = 0; i < recCnt; i++) {
	if (next >= numPredInfo) {
	    // predInfo is too small
	    _unfix_page(page);
	    return(eARRAYSIZE);
	}
        predInfo[next].node = subtreeRoot;
        predInfo[next].parent = parent;
        predInfo[next].level = page.level();
        predInfo[next].slot = i;
        predInfo[next].color = 0;
	next++;
    }

    // traverse children
    if (levels > 1 && page.level() > 1) {
	for (i = 0; i < recCnt; i++) {
	    const keyrec_t &tup = page.rec(i);
	    W_DO(_getPredInfo(tup.child(), subtreeRoot, levels-1, predInfo,
	        next, numPredInfo));
	}
    }
    _unfix_page(page);
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// gist::displayPreds - display predicates in Java canvas
//
// Description:
//	- construct a gist_predcursor_t out of predInfo and call 
//	  amdb_ext_t::displayPreds()
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
gist::displayPreds(
    JNIEnv*		env, // in
    jint		width, // in
    jint		height, // in
    jobject 		graphicsContext, // in: java.awt.Graphics
    jobject		colors[], // in: array of java.awt.Color objects
    DisplayPredInfo	predInfo[], // in
    int			numPredInfo) // in
{
    // construct predcursor
    gist_disppredcursor_t pcursor(this);
    int i;
    for (i = 0; i < numPredInfo; i++) {
        pcursor.add(predInfo[i].node, predInfo[i].slot, predInfo[i].level,
            predInfo[i].color);
    }

    // call amdb_ext_t
    amdb_ext_t* amdbExt = amdb_ext_t::amdb_ext_list[_ext->myId];
    assert(amdbExt != NULL);
    assert(amdbExt->displayPreds != NULL);
    W_DO(amdbExt->displayPreds(env, width, height, graphicsContext,
        colors, pcursor));
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// display - call amdb extension to display page contents
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
gist::display(
    shpid_t	pgno,
    JNIEnv*	env,
    jint*	highlights,
    jint	numHighlights,
    jobject	graphics,
    jobject	normalColor,
    jobject	highlightColor,
    jint	width,
    jint	height)
{
    gist_p page;
    W_DO(_fix_page(page, pgno, LATCH_SH));

    // dispatch through amdb_ext_t
    amdb_ext_t* amdbExt = amdb_ext_t::amdb_ext_list[_ext->myId];
    amdbExt->display(page, env, highlights, numHighlights, graphics, normalColor,
        highlightColor, width, height);

    _unfix_page(page);
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// getChildren - return child pointers of internal node
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
gist::getChildren(
    shpid_t 	pageno,
    int& 	level,
    Vector* 	children) // vector<shpid_t> *
{
    gist_p page;
    W_DO(_fix_page(page, pageno, LATCH_SH));
    _getChildren(page, children);
    level = page.level();
    _unfix_page(page);
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _getChildren - return child pointers of internal node
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

void
gist::_getChildren(
    const gist_p& page,
    Vector* /* vector<shpid_t> */ children)
{
    if (page.is_leaf()) return; // doesnt have children

    int cnt = page.nrecs();
    for (int i = 0; i < cnt; i++) {
        const keyrec_t& tup = page.rec(i);
	children->push_back((void *) tup.child());
    }
}


/////////////////////////////////////////////////////////////////////////
// pickSplit - compute split info for given node
//
// Description:
//	- call extension to compute split info
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t		
gist::pickSplit(
    shpid_t	pageno,
    int*	splitEntries, // entry #s, starting at 0
    int&	numSplit, // # of items that go right
    vec_t&	leftBp, // computed BP of left node
    vec_t&	rightBp) // computed BP of right node
{
    gist_p page;
    W_DO(_fix_page(page, pageno, LATCH_SH));

    // get BP from parent
    AlignedPred w;
    vec_t bpv(w.pred, gist_p::max_tup_sz);
    getBp(pageno, bpv);

    // find out which entries go right
    numSplit = gist_p::max_scnt;
    bool dummyBool1, dummyBool2;
    W_DO(_ext->pickSplit(page, splitEntries, numSplit, bpv, leftBp, rightBp,
	vec_t(), dummyBool1, vec_t(), dummyBool2));
    assert(numSplit <= gist_p::max_scnt);

    _unfix_page(page);
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// gist::unionBp - wrapper for gist_ext_t::unionBp()
//
// Description:
/////////////////////////////////////////////////////////////////////////

rc_t
gist::unionBp(
    shpid_t 		pageno, // in
    vec_t& 		bp, // in/out
    bool 		bpIsValid, // in
    const vec_t& 	pred1, // in
    const vec_t& 	pred2, // in
    bool& 		bpChanged) // out
{
    gist_p page;
    W_DO(_fix_page(page, pageno, LATCH_SH));
    _ext->unionBp(page, bp, bpIsValid, pred1, pred2, bpChanged);
    _unfix_page(page);
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// gist::getBp - make copy of BP
//
// Description:
//	- currently, simply calls unionBp()
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::getBp(
    shpid_t	pageno,
    vec_t&	bp)
{
    gist_p page;
    W_DO(_fix_page(page, pageno, LATCH_SH));
    vec_t dummyPred;
    bool dummyBool;
    _ext->unionBp(page, bp, false, dummyPred, dummyPred, dummyBool);
    _unfix_page(page);
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// gist::splitNode - split node into (private) left and right page
//
// Description:
//	- leftPg and rightPg point to buffers that are in static memory
//	  instead of under gist_file's control, so the caller doesn't 
//	  need to unfix or free any pages
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::splitNode(
    shpid_t 	node,
    gist_p&	leftPg,
    gist_p&	rightPg,
    const int	rightEntries[],
    int		numRight)
{
    gist_p page;
    W_DO(_fix_page(page, node, LATCH_SH));

    // create leftPg and rightPg, make them point to local mem
    // (we don't want to allocate a page that the caller then 
    // needs to free later on)
    static union {
        double d;
	char buf[SM_PAGESIZE];
    } leftBuf, rightBuf;
    static gist_file::page_descr leftDescr, rightDescr;
    leftDescr.page = leftBuf.buf;
    rightDescr.page = rightBuf.buf;
    (void) _new_page(rootNo, leftPg, page.level(), &leftDescr);
    (void) _new_page(rootNo, rightPg, page.level(), &rightDescr);

    // make copy of node, _split_node() expects leftPg to contain items
    page.copy(leftPg);

    W_DO(_split_node(leftPg, rightPg, rightEntries, numRight));

    _unfix_page(page);
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// gist::locateTargetLeaf - find target leaf of key insertion
//
// Description:
//	- presently, simply calls _locate_leaf() for top-down traversal
//	- unfixes the pages on the stack
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
gist::locateTargetLeaf(
    const vec_t& key, // in: key to find leaf for
    shpid_t& leaf) // out: target leaf
{
    gist_ustk stack;
    vec_t noData;
    W_DO(_locate_leaf(rootNo, stack, key, noData));
    leaf = stack.top()->page.pid();

    // unfix pages
    while (!stack.is_empty()) {
        gist_ustk_entry *e = stack.pop();
        if (e->page.is_fixed()) {
            _unfix_page(e->page);
        }
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// gist::writeLoadfile - write leaf level out as load file
//
// Description:
//	- does a top-down traversal of tree, writing out leaf
//	  data items as they are encountered (does a left-to-right
//	  scan of the entries within each node)
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::writeLoadfile(
    ostream&	s)
{
    return(RCOK);

#if 0
    amdb_clustering::Clustering::iterator cinfo;
    int prevClusterNo = amdb_clustering::invalidNo;
    for (cinfo = clustering->begin(); cinfo != clustering->end(); cinfo++) {
	// skip non-retrieved items (with clusterno == invalidNo == -1):
	// they precede all retrieved items in optClustering
        if (cinfo->clusterNo == amdb_clustering::invalidNo) {
	    continue;
	}

	if (prevClusterNo != amdb_clustering::invalidNo &&
	    prevClusterNo != cinfo->clusterNo) {

	    // we crossed a cluster boundary, write a blank line to indicate this
	    s << endl;
	}
	prevClusterNo = cinfo->clusterNo;

	// fetch next item from its leaf page
	const amdb_treemap::RecInfo *info =
	    profile->itemMap.itemInfo(cinfo->itemNo);

	gist_p page;
	W_DO(_fix_page(page, info->loc.treeLoc.page, LATCH_SH));

	// extract and write key and data in ASCII
	AlignedPred x;
	vec_t pred(x.pred, gist_p::max_tup_sz);
	ext->getKey(page, info->loc.treeLoc.slot, pred);
	s << "\"";
	ext->printPred(s, pred, 1);
	const keyrec_t& rec = page.rec(info->loc.treeLoc.slot);
	vec_t data(rec.elem(), rec.elen());
	s << "\" \"";
	ext->printData(s, data);
	s << "\"" << endl;

	_unfix_page(page);
    }
#endif

    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// gist::_OptTreeBuildState::clear - 
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
gist::_OptTreeBuildState::clear()
{
    delete optClustering;
    optClustering = NULL;
    if (deallocMap) {
	delete tupMap;
	tupMap = NULL;
    }
}

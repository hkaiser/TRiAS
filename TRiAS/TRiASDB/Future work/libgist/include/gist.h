// gist.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist.h,v 1.33 2000/03/10 01:39:01 mashah Exp $


#ifndef GIST_H
#define GIST_H


#ifdef __GNUG__
#pragma interface "gist.h"
#endif

#include "gist_p.h"		// for gist_p::max_tup_sz
#include "gist_defs.h"		// for rc_t
#include "gist_file.h"		// for gist_file

#ifdef AMDB
#include "amdb_defs.h"		// for Map
#include "amdb_breakpoints.h"	// for BreakInfo
#include "amdb_clustering.h"	// for amdb_clustering
#include "jni.h"		// for display() prototype
#endif

class gist_disppredcursor_t;
class gist_ext_t;
class gist_cursor_t;
class gist_cursorext_t;
class gist_lstk;
class gist_ustk;

// VCPORT_B
#ifndef WIN32
class ostream;
class ofstream;
class istrstream;
#endif
// VCPORT_E

class cvec_t;
class vec_t;
#ifdef AMDB
class amdb_wkldprofile;
class amdb_treemap;

// VCPORT_B
#ifndef WIN32
class ifstream;
#endif
// VCPORT_E

#endif

class gist {

    // needs to all _fix_page()/_unfix_page()
    friend class gist_disppredcursor_t;

public:

    gist();
    ~gist();

    // create an empty Gist
    rc_t			create(
	const char*		    filename,
	gist_ext_t*		    ext);

    // Produce tuple/data pairs for bulk-loading.  Returns RCOK if call was
    // successful, eEOF if there are no more tuples, and an error indication
    // otherwise. For leaf-level records, 'child' can be set to 0. For internal
    // records, 'data' need not be set. To force a page break, return ePAGEBREAK.
    typedef rc_t 		(*TupleStream)(
        void* 		    	    key,
	int& 			    klen,
        void* 		    	    data,
	int& 			    dlen,
	shpid_t&		    child,
	void* 			    param);

    // Create an index and bulk-load it. The argument 'sParam'
    // is passed to 's' unchanged. Pages are filled up with at least
    // 'fillFactor' * page capacity bytes.
    rc_t			create(
	const char*		    filename,
	gist_ext_t*		    ext,
	TupleStream		    s,
	void*			    sParam,
	float			    fillFactor);

    // open an existing Gist
    rc_t			open(
	const char*		    filename);

    rc_t			close();
    rc_t			flush(); 

    // insert a single key
    rc_t			insert(
	const void*		    key, 
	int	    	    	    klen,
	const void*		    data,
	int		            dlen);

    // remove all keys matching the query
    rc_t			remove(
	const gist_query_t*    	    query);

    // Initialize the cursor. If 'prio' == true, perform a nearest-neighbor
    // search based on gist_ext_t::prioritize().
    // 'k' is the max. # of tuples returned.
    // Initialize profiling information for amdb (if profiling enabled).
    rc_t			fetch_init(
	gist_cursor_t& 	    	    cursor,
	const gist_query_t*	    query,
	int			    k = 0,
	int			    io = 0);

    // fetch the next data item; 
    // gather profiling information for amdb (if profiling enabled)
    rc_t			fetch(
	gist_cursor_t& 	    	    cursor,
	void*			    key,
	smsize_t&		    keyLen,
	void*			    dataPtr,
	smsize_t&		    dataPtrLen,
	bool& 	   	 	    eof);

    // returns true if tree contains no data
    bool 			is_empty();

    // checks structural and data integrity of the tree;
    // outputs violations to stderr
    rc_t 			check();

    // dumps the content of a page to some output stream;
    // if 0 is specified as the pgno, dumps out the tree
    rc_t 			dump(
	std::ostream&		    s,
        shpid_t 	    	    pgno = 0);

    // XX debug
    rc_t dmp(shpid_t pgno);

    gist_ext_t* 		extension() const { return _ext; }

    // 8-byte aligned temp storage for arbitrary predicate
    union AlignedPred {
        double d;
	char pred[gist_p::max_tup_sz];
    };

protected: 
    // State
    gist_ext_t *_ext;
    bool _isOpen; // true if opened successfully
    gist_file _file;

//#define rootNo 1
    static const shpid_t rootNo;


#ifdef AMDB
public:

    /*
     * Index structure 
     */

    bool			isOpen() { return _isOpen; }

    // returns root #
    shpid_t 			getRootNo() const { return rootNo; }

    // returns child() of entries on page (in 'children'); leaves have no children
    rc_t 			getChildren(
    	shpid_t 		    pageno, 
	int&			    level, // of requested page
	Vector* 		    children); // vector<shpid_t> *

    // makes copy of BP (currently, calls unionPage())
    rc_t			getBp(
        shpid_t			    pageno,
	vec_t&			    bp);

    // wrapper for gist_ext_t::unionBp()
    rc_t 			unionBp(
        shpid_t 		    pageno, // in
	vec_t& 			    bp, // in/out
	bool 			    bpIsValid, // in
	const vec_t& 		    pred1, // in
	const vec_t& 		    pred2, // in
	bool& 		    	    bpChanged); // out

    // determines which items would go right if given page split;
    // (splitEntries must have at least gist_p::max_scnt elements)
    rc_t			pickSplit(
        shpid_t			    pageno,
	int			    splitEntries[], // entry #s, starting at 0
	int&			    numSplit, // # of items that go right
	vec_t&			    leftBp,
	vec_t&			    rightBp);

    // determines 'optimal' split according to hypergraph partitioning
    // (splitEntries must have at least gist_p::max_scnt elements)
    rc_t			pickOptSplit(
        shpid_t			    pageno,
	int			    splitEntries[], // entry #s, starting at 0
	int&			    numSplit, // # of items that go right
	vec_t&			    leftBp,
	vec_t&			    rightBp);


    // split 'node' into (newly allocated) leftPg and rightPg
    rc_t			splitNode(
        shpid_t 		    node,
	gist_p&			    leftPg,
	gist_p&			    rightPg,
	const int		    rightEntries[],
	int			    numRight);

#endif // AMDB

    // RID for index entry plus color index
    struct DisplayPredInfo {
        shpid_t node;
	int slot;
        shpid_t parent;
	int level; // level in tree
	int color; // index into 'colors' in displayPreds()

	DisplayPredInfo() {}
	DisplayPredInfo(shpid_t node, int slot, int level, int color) :
	    node(node), slot(slot), level(level), color(color) {}
    };

#if defined(AMDB)
    // get display-relevant information about predicates in subtree
    rc_t			getPredInfo(
    	shpid_t			    subtreeRoot, // in
	int 			    levels, // in
	DisplayPredInfo		    predInfo[], // out
	int 			    &numPredInfo); // in/out

    // displays predicates in Java canvas
    rc_t			displayPreds(
        JNIEnv*			    env, // in
	jint			    width, // in
	jint			    height, // in
	jobject 		    graphicsContext, // in: java.awt.Graphics
	jobject			    colors[], // in: array of java.awt.Color objects
	DisplayPredInfo		    predInfo[], // in
	int			    numPredInfo); // in

    // Displays content of node in Java canvas;
    // highlights[] specifies slot indices of entries to be shown highlighted
    // and those indices are assumed to be supplied in ascending order
    rc_t 			display(
    	shpid_t			    pgno,
	JNIEnv*			    env,
	jint*			    highlights,
	jint			    numHighlights,
	jobject			    graphics,
	jobject			    normalColor,
	jobject			    highlightColor,
	jint			    width,
	jint			    height);

protected:

    void 			_getChildren(
        const gist_p& 		    page,
	Vector* 		    children); // vector<shpid_t> *


    rc_t			_getPredInfo(
    	shpid_t			    subtreeRoot, // in
    	shpid_t			    parent, // in
	int			    levels,
	DisplayPredInfo		    predInfo[], // out
	int&			    next, // in
	int 			    numPredInfo); // in/out
    /*
     * Breakpoint support
     */

public:

    // install breakpoint handler
    void setBreakHandler(amdb_breakpoints::BreakHandler handler);

protected:

    amdb_breakpoints::BreakHandler _breakHandler;


    /* 
     * Profiling
     */

private:

    amdb_wkldprofile* _profile; // current profile

public:

    // if profile == NULL, disables profiling
    // if profile != NULL, computes the item map and accumulates 
    // profiling information in that profile;
    void 			setProfilingEnabled(
        amdb_wkldprofile*	    profile)
    {
        _profile = profile;
    }

    bool			profilingEnabled() { return (_profile != NULL); }

    int 			pageCount() { return _file.size(); }

    // traverse the tree and compute the conversion maps
    // and profile->nodeStats recursively for single subtree
    // (assumes nodeStats has at least pageCount() elements)
    rc_t 			computeTreeMap(
	amdb_treemap* 		    	map);

    
    /*
     * pickSplit() and penalty() evaluation
     */

    // creates an 'optimal' tree based on the computed optimal clustering
    rc_t			createOpt(
	const char *		    fileName,
        float			    fillFactor,
	const amdb_wkldprofile&	    profile,
	const amdb_clustering::Clustering&
				    optClustering,
	const amdb_treemap& 	    map,
        Rid2ItemIdMap& 		    ridMap);

    // write leaf level out as load file (ASCII)
    rc_t			writeLoadfile(
        ostream&		    s);

    // locate target leaf, given insertion key
    rc_t			locateTargetLeaf(
	const vec_t& 		    key, // in: key to find leaf for
	shpid_t& 		    leaf); // out: target leaf

private:

    // traverse the tree and compute the conversion maps
    // and profile->nodeStats recursively for single subtree
    rc_t 			_computeTreeMap(
	amdb_treemap* 		    	map,
        shpid_t 		    	pgno);

#endif

    /*
     * libgist implementation details
     */

private:

    // 
    enum {
        bpUpdated = 0x01,
	itemInserted = 0x02,
	leftItemUpdated = 0x04,
	rightItemInserted = 0x08
    };

    rc_t 			_locate_leaf(
	shpid_t 		    root,
	gist_ustk& 		    stack,
	const vec_t&		    key,
	const vec_t&		    data);

    rc_t 			_fetch(
	gist_cursor_t&		    cursor,
	void*			    key,
	smsize_t&		    keyLen,
	void*		  	    dataPtr,
	smsize_t&		    dataPtrLen,
	shpid_t&		    leafNo,
	unsigned int&		    idx,
	bool&			    eof);

    rc_t 			_fetch_nn(
	gist_cursor_t&		    cursor,
	void*			    key,
	smsize_t&		    keyLen,
	void*		  	    dataPtr,
	smsize_t&		    dataPtrLen,
	shpid_t&		    leafNo,
	unsigned int&		    idx,
	bool&			    eof);

    rc_t 			_insert_leaf(
	gist_p&			    page,
	const vec_t&		    key,
	const vec_t&		    data,
    	vec_t&			    bp,
	bool&			    bpChanged);

    rc_t 			_apply_update(
	gist_p&			    page,
	int& 			    leftIdx,
	const vec_t&		    leftBp,
	const vec_t&		    rightBp,
	shpid_t 		    rightChild,
    	vec_t&			    bp,
	bool&			    bpChanged);

    void			_extract_bp(
    	gist_ustk&		    stack,
	int			    stkIdx,
	vec_t&			    bp);

    rc_t 			_split_node(
	gist_p&			    left,
	gist_p&			    right,
	const int 		    rightEntries[],
	int 			    numRight);

    rc_t 			_split(
	shpid_t 		    root,
	gist_p&			    page,
	gist_ustk&		    stack,
	int 			    stkIdx,
	const int 		    rightEntries[], 
	int 			    numRight, 
	gist_p&			    rightPage,
	vec_t&			    leftBp,
	vec_t&			    rightBp);

    rc_t 			_update_parent(
	shpid_t 		    root,
	gist_ustk&		    stack,
	int 			    stkIdx,
	const vec_t&		    leftBp,
	const vec_t&		    rightBp,
	shpid_t 		    rightChild);

    rc_t 			_new_page(
	shpid_t 		    root,
        gist_p&			    p,
	int2 			    level,
	gist_file::page_descr*	    descr = NULL);

    rc_t 			_fix_page(
        gist_p&			    page,
        shpid_t 		    pageNo,
	latch_mode_t		    mode)
    {
        return (_static_fix_page(_file, page, pageNo, mode));
    }

    void 			_unfix_page(
        gist_p&			    page)
    {
        _static_unfix_page(_file, page);
    }

    static rc_t 		_static_fix_page(
	gist_file&	    	    file,
        gist_p&			    page,
        shpid_t 		    pageNo,
	latch_mode_t		    mode);

    static void 		_static_unfix_page(
	gist_file&	    	    file,
        gist_p&			    page);

    struct ReachInfo {
	shpid_t parent;
        int count;
	bool isFree; // true if free page
    };

    void 			_check_node(
        gist_p&			    node,
	const vec_t&		    bpv);

    rc_t 			_check_sub(
        shpid_t 		    pgno,
	const vec_t&		    pred,
	shpid_t			    parent,
	int			    slot,
	ReachInfo 		    reached[]);

    // called by _build_level to inform createOpt of 
    // involuntary page break; 'param' is the streamParam
    // passed into _build_level
    typedef void (*BreakNotifyFct)(int itemCnt, void* param);

    rc_t			_build_level(
        TupleStream&		    tupStream,
	void*			    streamParam,
	float			    fillFactor,
	int			    level,
	shpid_t 		    rootPid,
	std::ostream&		    bpOutStream,
	BreakNotifyFct		    breakNotify,
	int&			    pageCnt,
	gist_p&			    lastPage);

    rc_t			_finalize_page(
        gist_p& 		    page,
	std::ostream&		    outStream);

    rc_t			_prepare_page(
        gist_p&			    page,
	shpid_t		    	    rootPid,
	int 			    level);


    void 			_dump_pg(
	std::ostream& 		    s,
        gist_p&			    page);

    rc_t 			_dump_sub(
	std::ostream& 		    s,
        shpid_t 	    	    pgno);

    static rc_t 		_readBpFromTemp(
        void* 			    key,
        int&			    klen,
        void* 			    data,
        int&			    dlen,
        shpid_t&		    child,
        void* 			    param);

#ifdef AMDB

    // state needed during construction of 'optimal' tree
    // ('param' parameter of _optItemStream() and _optBpStream())
    struct _OptTreeBuildState {
	const amdb_wkldprofile* profile;
	    // result sets need to create hypergraphs for internal levels
        amdb_clustering::Clustering* leafItemMap;
	    // maps itemNo to current-level cluster numbers
        amdb_clustering::Clustering* optClustering;
	    // of current-level tuples (BPs for internal levels)
	int nextItem; // next item to return (starting at 0)
	const amdb_treemap* tupMap; // records leaf items or BPs
	bool deallocMap; // true if we allocated tupMap ourselves (not tree's map)
	float fillFactor; // target page util.
	gist_ext_t* ext; // for getKey()
	gist_file* file; // for _static_fix/unfix_page()
	ifstream* bpStream; // BPs written during build of previous level
	int level; // level that's currently under construction, leaves = 0
	bool returnedBreak; // true if we just returned a page break

	_OptTreeBuildState() :
	    profile(NULL), leafItemMap(NULL), optClustering(NULL), nextItem(0),
	    tupMap(NULL), deallocMap(false), fillFactor(0.0), ext(NULL),
	    file(NULL), bpStream(NULL), level(0), returnedBreak(false)
	{
	}

	~_OptTreeBuildState()
	{
	    clear();
	}

	void clear(); // only called for internal levels, I think
	void update();

    };

    static rc_t 		_optItemStream(
	void* 			    key,
	int&			    klen,
	void* 			    data,
	int&			    dlen,
	shpid_t&		    child,
	void* 			    param);

    static rc_t 		_optBpStream(
	void* 			    key,
	int&			    klen,
	void* 			    data,
	int&			    dlen,
	shpid_t&		    child,
	void* 			    param);

    void			_initLeafBuildState(
	const amdb_clustering::Clustering*
				    optClustering,
	const amdb_treemap* 	    map,
        _OptTreeBuildState&	    state);

    rc_t			_initInternalBuildState(
        _OptTreeBuildState&	    state);


    static void			_optBreakNotify(
        int			    itemCnt,
	void*			    param);

    void			_constructBpMap(
        ifstream&		    bpStream,
	amdb_treemap&		    bpMap);

#endif

};

//extern size_t totalMem; // debugging

#endif // GIST_H

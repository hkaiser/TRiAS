// Libgist.java
// Copyright (c) 1998, Regents of the University of California
// $Id: Libgist.java,v 1.3 1999/12/14 06:07:09 marcel Exp $

import javax.swing.*;
import java.lang.*;
import java.awt.Graphics;
import java.awt.Color;

/*
 * Libgist.java - 
 * Interface class to libgist, enhanced with a couple of extra functions to support amdb.
 * This class only works on one index at a time (has a single global gist_m object at
 * the C++ layer).
 */

class Libgist 
{

// array of extension info records
public static ExtensionInfo[] extInfo;

private static ExtensionInfo[]
getExtensionInfo()
{
    return libGetExtensionInfo();
}

static {
    System.loadLibrary("amdb");
    libInit();
    extInfo = getExtensionInfo();
}

public static void
cleanup()
{
    libCleanup();
}

static boolean closed = true; // no Libgist open at beginning

// Per-node tree statistics, set by getNodeStats.
// The size is increased dynamically, if necessary, to match the current size of
// the tree. 'nodeStats' holds the node stats and 'display stats' holds the 
// particular value that treeView is supposed to display (extracted from 'nodeStats').
public static float[] displayStats = new float[1];
//public static NodeStats[] nodeStats = new NodeStats[1]; // currently not used!
public static int nodeCnt = 0; // set to the node count by abovementioned functions

/* 
 * standard libgist interface functions
 */


// all of these must raise some exception to indicate errors
public static void
create(String fileName, int extId) throws LibgistException
{
    libCreate(fileName, extId);
    closed = false;
}

public static void
open(String fileName) throws LibgistException
{
    libOpen(fileName);
    closed = false;
}

public static void
close() throws LibgistException
{
    if (!closed) {
	libClose();
	closed = true;
    }
}

public static void
flush() throws LibgistException
{
    libFlush();
}

public static void
saveToFile(String filename) throws LibgistException
{
    // first save all changes, then copy file
    libSave(filename);
}

public static void
insert(String key, String data) throws LibgistException
{
    libInsert(key, data);
}

public static void
remove(String query) throws LibgistException
{
    libRemove(query);
}

public static void
fetch(String query, int limit, ResultProcessor procResult) throws LibgistException
{
    libFetch(query, limit, procResult);
}

public static void
check() throws LibgistException
{
    libCheck();
}

// Dumps the content of the node in ASCII to the text area and
// returns the length of the dump output.
public static int
dump(JTextArea area, int pgNo) throws LibgistException
{
    return libDump(area, pgNo);
}


///////////////////////////////////////////////////////////////////////////////
// getPredInfo - load information about predicates in subtree
//
// Description:
//
// Exceptions: LibgistException for errors in libgist calls
//
// Returns:
//	number of elements in predInfo that were set
///////////////////////////////////////////////////////////////////////////////

public static void
getPredInfo(
    int root, // in: page # of root of subtree
    int levels) // in: # of levels to look at
{
    libGetPredInfo(root, levels);
}


///////////////////////////////////////////////////////////////////////////////
// highlightSubtree - mark a subtree portion in the current predInfo array
//
// Description:
//
// Exceptions: LibgistException for errors in libgist calls
//
// Returns:
//	number of elements in predInfo that were set
///////////////////////////////////////////////////////////////////////////////

public static void
highlightSubtree(
    int root, // in: page # of root of subtree
    int levels, // in: # of levels to look at
    int color) // in: highlight color
{
    libHighlightSubtree(root, levels, color);
}


///////////////////////////////////////////////////////////////////////////////
// highlightSplit - mark a set of right entries in the current predInfo array
//
// Description:
//
// Exceptions: LibgistException for errors in libgist calls
//
// Returns:
//	number of elements in predInfo that were set
///////////////////////////////////////////////////////////////////////////////

public static void
highlightSplit(
    int[] rightEntries, // in: slot #s of entries to go right
    int numRight, // in: # entries in 'rightEntries'
    int color) // in: highlight color
{
    libHighlightSplit(rightEntries, numRight, color);
}


///////////////////////////////////////////////////////////////////////////////
// highlightPath - mark a path in the current predInfo array
//
// Description:
//
// Exceptions: LibgistException for errors in libgist calls
//
// Returns:
//	number of elements in predInfo that were set
///////////////////////////////////////////////////////////////////////////////

public static void
highlightPath(
    int topNode, // in: highest node in path
    int bottomNode, // in: lowest node in path
    int color) // in: highlight color
{
    libHighlightPath(topNode, bottomNode, color);
}


///////////////////////////////////////////////////////////////////////////////
// displayPreds - display predicates in window
//
// Description:
//	- explicitly specifies the number of predicates identified in
//	  predInfo to display, because predInfo might contain more elements
//	  than necessary
//
// Exceptions: LibgistException
///////////////////////////////////////////////////////////////////////////////

public static void
displayPreds(
    Graphics 		g, // in: graphics context needed for drawing
    int 		width, // in: width of window
    int 		height, // in: height of window
    Color[] 		colors) // in: drawing colors
    throws LibgistException
{
    LibgistException exc = new LibgistException();
    // exc.printStackTrace();
    libDisplayPreds(g, width, height, colors);
}


// Determines which entries in the given node would go to the right sibling if
// the node gets split ('splitItems' contains number of split-off items,
// starting with 0 for the 'leftmost' item on the page). Returns the number of
// items that are split off.
public static int
pickSplit(int pgno, int splitItems[])
{
    return libPickSplit(pgno, splitItems);
}


/* 
 * tree info functions
 */

// returns the number of pages in the index
public static int
getPageCount()
{
    return libGetPageCount();
}

// returns the page no of the root page
public static int
getRoot()
{
    return libGetRoot();
}

// returns the page no of the parent of the given page
public static int
getParent(int pgNo)
{
    return libGetParent(pgNo);
}

// returns the page no of the parent of the given page
// retuens (-1) if it isn't a node ...
public static int
getLevel(int pgNo)
{
    return libGetLevel(pgNo);
}

// returns the position in the parent node of the entry pointing to pgno 
// (or -1 if pgno = rootno)
public static int
getParentPos(int pgNo) throws LibgistException
{
    return libGetParentPos(pgNo);
}

// Determines the page no's of the children of the given page
// and returns them through 'children' (which is assumed to hold at
// least gist_p::max_scnt integers). Returns the number of children.
public static int
getChildren(int parent, int[] children) throws LibgistException
{
    return libGetChildren(parent, children);
}

// Returns the maximum number of a children any node can have.
public static int
maxChildren()
{
    return libMaxChildren();
}

// Determines the page #s of the nodes on the path from pgNo to the root
// including the pgNo and the root itself (path[0] holds pgNo). Returns the 
// number of nodes on the path.
public static int
getPath(int pgNo, int[] path) throws LibgistException
{
    return libGetPath(pgNo, path);
}

// returns the nonce of the node with pgNo.
public static int
getNonce(int pgNo) throws LibgistException
{
    return libGetNonce(pgNo);
}


/*
 * breakpoints etc.
 */

// creates a new C++ breakpoint for the given info and returns its ID
public static void
createBp(Breakpoint bp)
{
    libCreateBp(bp);
}

// delete all breakpoints
public static void
deleteBps()
{
    libDeleteBps();
}

// installs the Java break handler object 
public static void
setBreakHandler(BreakHandler handler)
{
    libSetBreakHandler(handler);
}

public static void
disableBps(boolean disable)
{
    libDisableAll(disable);
}

// immediately turns on single-stepping; the next time the C break handler is called,
// it will pass control to the Java break handler
public static void
singleStep()
{
    libSingleStep();
}


/*
 * Analysis
 */


///////////////////////////////////////////////////////////////////////////////
// createAnalysis -
//	run queries in script and create analysis with treemap and profile
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// openAnalysis - read analysis from file
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
openAnalysis(String name) throws LibgistException
{
    libOpenAnalysis(name);
}


///////////////////////////////////////////////////////////////////////////////
// closeAnalysis - discard in-memory analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
closeAnalysis() throws LibgistException
{
    libCloseAnalysis();
}

///////////////////////////////////////////////////////////////////////////////
// writeAnalysis - write analysis back to file
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
writeAnalysis() throws LibgistException
{
    libWriteAnalysis();
}


///////////////////////////////////////////////////////////////////////////////
// getAnalysisInfo - return info about progress of analysis, etc.
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
getAnalysisInfo(
    AnalysisInfo info)
    throws OutOfMemoryError
{
    //LibgistException exc = new LibgistException();
    //exc.printStackTrace();
    libGetAnalysisInfo(info);
}


///////////////////////////////////////////////////////////////////////////////
// getQueryStats - get query stats from analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
getQueryStats(
    int queryNo, // in: number of query; = 0: cumulative stats
    QueryStats stats) // out
{
    stats.reset();
    libGetQueryStats(queryNo, stats);
}

///////////////////////////////////////////////////////////////////////////////
// getSplitStats - get split stats from analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
getSplitStats(
    int leafNo, // in: page # of split leaf; = 0: cumulative stats
    boolean weighted, // in: if true, return weighted I/O values
    SplitStats stats) // out
{
    stats.reset();
    libGetSplitStats(leafNo, weighted, stats);
}

///////////////////////////////////////////////////////////////////////////////
// getSplitLeaves - returns page numbers of leaves whose split was analyzed
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
getSplitLeaves(
    int[] leafNos) // out
{
    libGetSplitLeaves(leafNos);
}


///////////////////////////////////////////////////////////////////////////////
// getPenaltyStats - get penalty stats from analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static void
getPenaltyStats(
    int keyNo, // in: # of key used for insertion
    boolean weighted, // in: if true, return weighted I/O values
    PenaltyStats stats) // out
{
    stats.reset();
    libGetPenaltyStats(keyNo, weighted, stats);
}

///////////////////////////////////////////////////////////////////////////////
// getNumInsertions - get # of insertions analyzed in penalty stats
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

public static int
getNumInsertions()
{
    return(libGetNumInsertions());
}


///////////////////////////////////////////////////////////////////////////////
// getWkldNodeStats - get per-node stats from amdb_wkldprofile/-stats
//
// Description:
//	- resize displayStats and nodeStats to match the number of 
//	  pages in the tree
///////////////////////////////////////////////////////////////////////////////

static public final int TRAVERSALS = 		0;
    // amdb_wkldprofile::TraversalStats.traversalCnt
static public final int RETRIEVALS = 		1;
    // amdb_wkldprofile::TraversalStats.retrievalCnt
static public final int EMPTYSUBTREES = 	2;
    // amdb_wkldprofile::TraversalStats.emptySubtree
static public final int CLUSTERLOSS = 		3;
    // amdb_wkldstats::NodeStats.[min|opt]ClusterLoss
static public final int CLUSTEROH = 		4;
    // amdb_wkldstats::NodeStats.[min|opt]ClusterOh
static public final int UTILLOSS = 		5;
    // amdb_wkldstats::NodeStats.[min|opt]UtilLoss
static public final int UTILOH = 		6;
    // amdb_wkldstats::NodeStats.[min|opt]UtilOh
static public final int EXCCOVLOSS = 		7;
    // amdb_wkldstats::NodeStats.[min|opt]ExcCovLoss
static public final int EXCCOVOH = 		8;
    // amdb_wkldstats::NodeStats.[min|opt]ExcCovOh
static public final int NODEUTIL = 		9;
    // amdb_treemap::PageInfo.util
static public final int SLOTCNT = 		10;
    // amdb_treemap::PageInfo.itemCnt
static public final int PREDSIZE = 		11;
    // amdb_treemap::PageInfo.avgPredLen

public static void
getWkldNodeStats(
    int statType, // in: one of the above constants
    int queryNo, // in: number of query, = 0: cumulative stats
    boolean minBased) // in: if true, return min-, not opt-based statistic
{
    if (nodeCnt < libPageCount()) {
        nodeCnt = libPageCount();
	displayStats = new float[nodeCnt];
	//nodeStats = new NodeStats[nodeCnt];
    }
    libGetWkldNodeStats(statType, queryNo, minBased, displayStats);
}


///////////////////////////////////////////////////////////////////////////////
// getSplitNodeStats - get per-node stats from amdb_splitstats
//
// Description:
//	- resize displayStats and nodeStats to match the number of 
//	  pages in the tree
//	- split stats are always aggregates over all queries
///////////////////////////////////////////////////////////////////////////////

static public final int SPLITCLUSTLOSS = 	0;
    // amdb_splitstats::FullSplitStats::clustLoss()
static public final int SPLITEXCCOVLOSS = 	1;
    // amdb_splitstats::FullSplitStats::excCovLoss()
static public final int SPLITCLUSTSUCC = 	2;
    // amdb_splitstats::FullSplitStats::clustSuccess()
static public final int SPLITEXCCOVSUCC = 	3;
    // amdb_splitstats::FullSplitStats::excCovSuccess()
static public final int OPTCLUSTDELTA = 	4;
    // amdb_splitstats::FullSplitStats::optClustDelta()
static public final int ACTCLUSTDELTA = 	5;
    // amdb_splitstats::FullSplitStats::actualClustDelta
static public final int EXCCOVDELTA = 		6;
    // amdb_splitstats::FullSplitStats::excCovDelta()

public static void
getSplitNodeStats(
    int statType, // in: one of the above constants
    boolean delta, // in: if true, return deltas, not abs. values
    boolean weighted) // in: if true, return weighted I/O numbers
{
    if (nodeCnt < libPageCount()) {
        nodeCnt = libPageCount();
	displayStats = new float[nodeCnt];
	//nodeStats = new NodeStats[nodeCnt];
    }
    libGetSplitNodeStats(statType, delta, weighted, displayStats);
}



/*
 * Scripts
 */

// returns script ID
public static int
openScript(String filename) throws LibgistException
{
    return libOpenScript(filename);
}


///////////////////////////////////////////////////////////////////////////////
// gist::insert - insert a new entry into the tree
//
// Description:
//
// Exceptions:
//
// Return Values:
//	< 0: error
//	>= 0: cmd
///////////////////////////////////////////////////////////////////////////////

// command constants (return values of getCommand())
static final int FILEERROR =  -3;
static final int PARSEERROR =  -2;
static final int EOF =  -1;

public static int
getCommand(int scriptId, LibgistCommand cmd) throws LibgistException
{
    cmd.reset();
    return libGetCommand(scriptId, cmd);
}


/*
 * Scripts
 */

public static void
setDbgLevel(int dbgLevel)
{
    libSetDbgLevel(dbgLevel);
}

/*
 * JNI stuff
 */

private static native ExtensionInfo[]
libGetExtensionInfo();

private static native void
libCreate(String fileName, int extId) throws LibgistException;

private static native void
libOpen(String fileName) throws LibgistException; 

private static native void
libClose() throws LibgistException;

private static native void
libFlush() throws LibgistException;

private static native void
libSave(String filename) throws LibgistException; 

private static native void
libInsert(String key, String data) throws LibgistException;

private static native void
libRemove(String query) throws LibgistException;

private static native void
libFetch(String query, int limit, ResultProcessor procResult) throws LibgistException;

private static native void
libCheck() throws LibgistException;

private static native int
libDump(JTextArea area, int pgNo) throws LibgistException;

private static native void
libDisplayPreds(Graphics g, int width, int height, Color[] colors)
    throws LibgistException;

// returns root page no
private static native int
libGetRoot();

// returns root page no
private static native int
libGetPageCount();

// returns pageno of parent
private static native int
libGetParent(int pgNo);

// returns level of page (leaf level = 1)
private static native int
libGetLevel(int pgNo);

// returns position in  parent
private static native int
libGetParentPos(int pgNo) throws LibgistException;

// returns pgnos of all children
private static native int
libGetChildren(int parent, int[] children) throws LibgistException;

private static native int
libMaxChildren();

// returns path from root to node with pgNo
private static native int
libGetPath(int pgNo, int[] path) throws LibgistException;

// returns the nonce of the node with pgNo
private static native int
libGetNonce(int pgNo) throws LibgistException;

private static native void
libInit();

private static native void
libSetBreakHandler(BreakHandler handler);

private static native void
libSingleStep();

private static native void
libDeleteBps();

private static native void
libCreateBp(Breakpoint bp);

private static native void
libDisableAll(boolean disable);

private static native void
libOpenAnalysis(String name);

private static native void
libCloseAnalysis();

private static native void
libWriteAnalysis() throws LibgistException;

private static native void
libGetAnalysisInfo(AnalysisInfo info);

private static native void
libGetQueryStats(int queryNo, QueryStats stats);

private static native void
libGetSplitStats(int leafNo, boolean weighted, SplitStats stats);

private static native void
libGetSplitLeaves(int[] leafNos);

private static native void
libGetPenaltyStats(int keyNo, boolean weighted, PenaltyStats stats);

private static native void
libGetWkldNodeStats(int statsType, int queryNo, boolean minBased,
    float[] stats);

private static native void
libGetSplitNodeStats(int statsType, boolean delta, boolean weighted,
    float[] stats);

private static native int
libPageCount();

private static native int
libPickSplit(int pgno, int splitItems[]);

private static native int
libOpenScript(String filename) throws LibgistException;

private static native int
libGetCommand(int scriptId, LibgistCommand cmd) throws LibgistException;

// ignore LibgistException in this case, we're exiting
private static native void
libCleanup();

private static native void
libGetPredInfo(int root, int levels);

private static native void
libDisplay(int pgno, int highlights[], int numHighlights, Graphics g,
    Color normalColor, Color highlightColor, int width, int height)
    throws LibgistException;

private static native int
libGetNumInsertions();

private static native void
libSetDbgLevel(int dbgLevel);

private static native void
libHighlightSubtree(int root, int levels, int color);

private static native void
libHighlightSplit(int[] rightEntries, int numRight, int color);

private static native void
libHighlightPath(int topNode, int bottomNode, int color);

}

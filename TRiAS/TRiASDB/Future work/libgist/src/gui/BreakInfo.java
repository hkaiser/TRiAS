// BreakInfo.java
// Copyright (c) 1998, Regents of the University of California
// $Header: /usr/local/devel/GiST/libgist/src/gui/BreakInfo.java,v 1.2 2000/03/15 00:23:57 mashah Exp $

import java.lang.String;
import java.io.Serializable;

/*
 * BreakInfo:
 *
 * Info for a break event, reported by libgist via break handler.
 */

public class BreakInfo implements Cloneable, Serializable
{

// event values
static final int INSERT = 0;
static final int REMOVE = 1;
static final int FETCH = 2;
static final int NODESPLIT = 3;
static final int TRAVERSAL = 4;
static final int NODEINSERT = 5; // insert item on a node
static final int NODEDELETE = 6; // delete item from a node
static final int BPUPDATE = 7;
static final int LOCATELEAF = 8;
static final int NEWNODE = 9;
static final int NEWROOT = 10;
static final int RELOCATECHILD = 11;
static final int ITEMINSERTED = 12;
static final int ITEMDELETED = 13;
static final int BPUPDATED = 14;
static final int NUMEVENTS = 15;

static String[] eventDescrs = {
    "Insert", "Delete", "Select", "Node Split", "Node Traversal", 
    "Item Insertion", "Item Deletion", "BP Update", "Leaf Located",
    "New Node", "New Root", "Child Relocated", "Item Inserted",
    "Item Deleted", "BP Updated"
};

int id; // C++ ID of breakpoint that was triggered
int event; // break event
int nodeId; // at which node (only for NODESPLIT, ...)

// for LOCATELEAF, if penalty checking is turned on
// fields correspond to amdb_breakpoints::PenaltyCheckResults
double targetPenalty;
double minPenalty;
int minLeaf; 

public
BreakInfo()
{
}

// make a copy
BreakInfo(BreakInfo info)
{
    id = info.id;
    event = info.event;
    nodeId = info.nodeId;
    targetPenalty = info.targetPenalty;
    minPenalty = info.minPenalty;
}

}

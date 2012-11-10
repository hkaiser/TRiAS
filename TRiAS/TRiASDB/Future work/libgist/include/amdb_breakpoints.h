// amdb_breakpoints.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_breakpoints.h,v 1.10 1998/12/11 05:04:02 marcel Exp $

#ifndef AMDB_BREAKPOINTS_H
#define AMDB_BREAKPOINTS_H

#include "gist_defs.h"
#include "amdb_defs.h"

/*
 * amdb_breakpoints:
 *
 * Collection of breakpoint-related structs. 'Breakpoint' is used to specify breakpoints,
 * whereas 'EventInfo' is reported by libgist to the breakpoint handler in Gist.cc.
 */

class amdb_breakpoints {

public:

    // type of breakpoint
    enum BreakEvents {
	// events reported to user (amdb)
        insertEvent = 0, // call to gist::insert()
	removeEvent, // call to gist::remove()
	fetchEvent, // call to gist::fetch_init()
	splitEvent, // node about to get split
	traversalEvent, // node is currently being traversed
	nodeInsertEvent, // item about to be inserted on node
	nodeDeleteEvent, // item about to be deleted from node
	bpUpdateEvent, // BP about to be updated 
	locateLeafEvent, // target leaf for insertion has just been located

	// these are not reported to the amdb user (used for in-core index structure)
	newNodeEvent, // node just got split
	newRootEvent, // root just got split
	relocateChildEvent, // child entry goes to final destination
	itemInsertedEvent, // item just got inserted into node
	itemDeletedEvent, // item just got deleted into node
	bpUpdatedEvent, // BP just got updated
	numEvents
    };

    // true if this event tells us to update the in-core representation of the tree struct
    static bool isStructureUpdate(BreakEvents event) {
	return (event == newNodeEvent || event == newRootEvent ||
	    event == relocateChildEvent || event == itemInsertedEvent || 
	    event == itemDeletedEvent || event == bpUpdatedEvent);
    }

    // true if this is an event triggered by entry into an interface function
    static bool isEntryPoint(BreakEvents event) {
	return (event == insertEvent || event == removeEvent || event == fetchEvent);
    }


    // parameters of locateLeaf event
    struct PenaltyCheckResults {
	//should be gist_penalty_t instead of double, but can't call its constructor in union
	double targetPenalty; // insertion penalty at target leaf node
	double minPenalty; // minimum insertion penalty of all the leaves checked
	shpid_t minLeaf; // leaf that scored minPenalty
    };

    // parameters of newNodeEvent
    // typedef vector<shpid_t>  ChildVect; 
    typedef Vector ChildVect; // child page #'s
    struct NodeSplitInfo {
        shpid_t origNode; // node that split
	shpid_t rightSib; // its new right sibling
	ChildVect* rightChildren; // the child nodes delegated to the right sibling
    };

    // parameters of newRootEvent
    struct RootSplitInfo {
        shpid_t leftNode; // left node below root
        shpid_t rightNode; // right node below root
	ChildVect* rightChildren; // children of right node
	// children of left node = children of orig. root - rightChildren
    };

    // parameters of relocateChildEvent
    // A child is relocated when it splits and as a result its parent also
    // splits: when the parent splits, it temporarily does not contain an entry
    // for either the original child or the new sibling (when the parent node
    // splits, the entry for the original child is deleted for the duration of
    // the split). When the parent split is completed, including BP
    // update/installation of new entry in ancestors, the entry for the original
    // child and the new child entry are finally inserted into the parent (or
    // its new right sibling). For the internal index structure maintained by
    // amdb, this looks like the two child entries are relocated, since they
    // were originally assumed to be on the parent.
    struct RelocateChildInfo {
        shpid_t child;
	shpid_t oldParent; // original parent
	shpid_t newParent; // new parent
    };

    // info for particular break event
    struct BreakInfo {
        BreakEvents event;
	shpid_t node; // set for node-specific events reported to user
	union {
	    struct {
	        char* key;
		char* data;
	    } updateParam; // parameters of update operations (insert, remove)
	    PenaltyCheckResults locateLeafParam;
	        // parameters of locateLeaf or hiPenalty event
	    NodeSplitInfo newNodeParam; // parameters of newNodeEvent
	    RootSplitInfo newRootParam; // parameters of newRootEvent
	    RelocateChildInfo relocateChildParam; // parameters of relocateChildEvent
	    shpid_t updNodeParam;
	        // node that was updated (events: itemInserted/-Deleted and bpUpdated)
	} param;
    };

    // breakpoint specification parameters
    struct Breakpoint {
	int id; // numerical ID for this breakpoint
        BreakEvents event;
	shpid_t node;
	union {
	    struct {
	        void* key;
		int klen; 
		void* data;
		int dlen;
	    } updateParam; // parameters of update operations (insert, remove)
	    struct {
	        int maxDeviation; // perc. of max (target penalty - min. penalty)
	    } penaltyParam; // parameters of hiPenalty event
	} param;
    };

    // breakpoint handler type
    typedef bool (*BreakHandler)(BreakInfo*);

};

#endif

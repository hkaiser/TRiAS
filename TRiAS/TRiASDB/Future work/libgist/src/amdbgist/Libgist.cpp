// Gist.cc -*- c++ -*--
// Copyright (c) 1998, Regents of the University of California
// $Id: Libgist.cc,v 1.7 2000/03/15 00:23:21 mashah Exp $

/*
 * Gist.cc - native implementation of interface Gist.java
 * contains wrapper functions for the libgist interface, manages breakpoints
 */

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786) // Templates can cause names to get too long for
							  // debug information. Disables this warning.
#endif
// VCPORT_E

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <malloc.h>
#include "jni.h"
#include "gist_query.h"
#include "gist_cursor.h"
#include "amdb_wkldprofile.h"
#include "amdb_analysis.h"
#include "amdb_wkldstats.h"
#include "amdb_splitstats.h"
#include "amdb_penaltystats.h"
#include "amdb_treemap.h"
#include "gist.h"
#include <stdio.h>

// VCPORT_B
#ifdef WIN32

#include <iostream>
#include <strstream>
#include <fstream>

// STL 
#include <functional>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#else

#include <iostream.h>
#include <strstream.h>
#include <fstream.h>

// STL 
#include <function.h>
#include <algo.h>
#include <vector.h>
#include <multimap.h>

#endif

#include "Libgist.h"
#include "amdb_idxstruct.h"
#include "amdb_ext.h"

// include for extensions
#include "gist_extensions.h"

#define DUMPBUFLEN 64*1024
#define MAXCMDLEN 1024

// debugging support
static int Gist_dbgLevel = 0;

#define DBGPRINT(x,y)	\
{	\
    if ((x) <= Gist_dbgLevel) {	\
        (y);	\
    }	\
}


extern "C" {

// forward declarations
static void stringBufferAppend(JNIEnv* env, jobject buf, const char* str);
static void copyCharArray(jchar* to, char* from);
static void _highlightChildSubtrees( int parent, int levels, int& index, int color);

/* 
 * General macros for detecting errors and Java exceptions and/or throwing them.
 */


///////////////////////////////////////////////////////////////////////////////
// HANDLEEXC - handle Java exception and return
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define HANDLEEXC(env)	\
{	\
    jthrowable exc = (env)->ExceptionOccurred();	\
    if (exc) {	\
        (env)->ExceptionDescribe();	\
	return;	\
    }	\
}


///////////////////////////////////////////////////////////////////////////////
// HANDLEEXCR - handle Java exception and return value
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define HANDLEEXCR(env, retval)	\
{	\
    jthrowable exc = (env)->ExceptionOccurred();	\
    if (exc) {	\
        (env)->ExceptionDescribe();	\
	return (retval);	\
    }	\
}


///////////////////////////////////////////////////////////////////////////////
// ERRORRETURNV - generate LibgistException and return value
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define ERRORRETURNV(str, retval) \
{	\
    jclass excCl = (env)->FindClass("LibgistException");	\
    if (excCl == NULL) {	\
	return (retval);	\
    }	\
    (env)->ThrowNew(excCl, (str));	\
    return (retval);	\
}


///////////////////////////////////////////////////////////////////////////////
// ERRORRETURN - generate LibgistException and return
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define ERRORRETURN(str) \
{	\
    jclass excCl = (env)->FindClass("LibgistException");	\
    if (excCl == NULL) {	\
	return;	\
    }	\
    (env)->ThrowNew(excCl, (str));	\
    return;	\
}


///////////////////////////////////////////////////////////////////////////////
// CHECKSTATUS - check execution status, generate LibgistException and return
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define CHECKSTATUS(status, env, str)	\
{	\
    if ((status) != RCOK) {	\
	DBGPRINT(1, fprintf(stderr, "status: %d\n", status)); 	\
        jclass excCl = (env)->FindClass("LibgistException");	\
	if (excCl == NULL) {	\
	    return;	\
	}	\
	(env)->ThrowNew(excCl, (str));	\
	return;	\
    }	\
}


///////////////////////////////////////////////////////////////////////////////
// CHECKSTATUSR -
//	check execution status, generate LibgistException and return value
//
// Description:
///////////////////////////////////////////////////////////////////////////////

#define CHECKSTATUSR(status, env, str, retval)	\
{	\
    if ((status) != RCOK) {	\
	DBGPRINT(1, fprintf(stderr, "status: %d\n", status)); 	\
        jclass excCl = (env)->FindClass("LibgistException");	\
	if (excCl == NULL) {	\
	    return (retval);	\
	}	\
	(env)->ThrowNew(excCl, (str));	\
	return (retval);	\
    }	\
}


// miscellaneous static variables
static gist *Gist_gist = new gist();
static amdb_analysis* Gist_analysis;
static amdb_idxstruct* Gist_indexStruct = NULL; // created when index created/opened
static char* Gist_filename = NULL;
static char* Gist_analysisname = NULL;
static jobject Gist_handler;
static amdb_treemap* _treeMap = NULL; // allocated and computed on demand
static gist::DisplayPredInfo* Gist_predInfo = NULL;
static int Gist_predInfoSize = 0;
static int Gist_numPredInfo = 0;
static int Gist_numPredInfoColors = 0;


// cached class objects and method and field IDs
static jclass Gist_handlerClass;
static jmethodID Gist_handlerId;

static jclass Gist_breakpointClass;
//static jmethodID Gist_breakpointConstrId;
static jfieldID Gist_bpEventId;
static jfieldID Gist_bpIdId;
static jfieldID Gist_bpNodeId;
static jfieldID Gist_bpParam1Id;
static jfieldID Gist_bpParam2Id;

static jclass Gist_breakInfoClass;
static jmethodID Gist_breakInfoConstrId;
static jfieldID Gist_biEventId;
static jfieldID Gist_biIdId;
static jfieldID Gist_biNodeId;
static jfieldID Gist_biTargetPenaltyId;
static jfieldID Gist_biMinPenaltyId;
static jfieldID Gist_biMinLeafId;
static jobject Gist_infoObj = NULL; // single Java BreakInfo object, passed to handler

static jclass Gist_queryStatsClass;
static jfieldID Gist_qsResultSetLimitId;
static jfieldID Gist_qsQualId;
static jfieldID Gist_qsResultSetSizeId;
static jfieldID Gist_qsAvgUtilId;
static jfieldID Gist_qsRetrievalVolId;
static jfieldID Gist_qsTotalLeafIosId;
static jfieldID Gist_qsTotalInternalIosId;
static jfieldID Gist_qsMinIosId;
static jfieldID Gist_qsOptimalIosId;
static jfieldID Gist_qsOptimalOhId;
static jfieldID Gist_qsOptLeafOhId;
static jfieldID Gist_qsMinLeafOhId;
static jfieldID Gist_qsRandomIosId;
static jfieldID Gist_qsRandomStdDevId;
static jfieldID Gist_qsOptRandomOhId;
static jfieldID Gist_qsMinRandomOhId;
static jfieldID Gist_qsOptClusterLossId;
static jfieldID Gist_qsOptClusterOhId;
static jfieldID Gist_qsMinClusterLossId;
static jfieldID Gist_qsMinClusterOhId;
static jfieldID Gist_qsLeafUtilLossId;
static jfieldID Gist_qsUtilOhId;
static jfieldID Gist_qsLeafExcCovLossId;
static jfieldID Gist_qsExcCovOhId;
static jfieldID Gist_qsInternalUtilLossId;
static jfieldID Gist_qsInternalExcCovLossId;

static jclass Gist_splitStatsClass;
static jfieldID Gist_ssPreIosId;
static jfieldID Gist_ssOptIosId;
static jfieldID Gist_ssActualIosId;
static jfieldID Gist_ssPreExcCovLossId;
static jfieldID Gist_ssActualExcCovLossId;
static jfieldID Gist_ssOptClusterDeltaId;
static jfieldID Gist_ssActualClusterDeltaId;
static jfieldID Gist_ssClusterLossId;
static jfieldID Gist_ssClusterOhId;
static jfieldID Gist_ssClusterSuccessId;
static jfieldID Gist_ssExcCovDeltaId;
static jfieldID Gist_ssExcCovLossId;
static jfieldID Gist_ssExcCovOhId;
static jfieldID Gist_ssExcCovSuccessId;

static jclass Gist_penaltyStatsClass;
static jfieldID Gist_psActualAddIosId;
static jfieldID Gist_psOptAddIosId;
static jfieldID Gist_psActualExcCovId;
static jfieldID Gist_psExcCovDeltaId;
static jfieldID Gist_psClusterLossId;
static jfieldID Gist_psExcCovOhId;
static jfieldID Gist_psExcCovSuccessId;
static jfieldID Gist_psKeyId;

static jclass Gist_analysisInfoClass;
static jfieldID Gist_aiActualNameId;
static jfieldID Gist_aiActualHasWkldStatsId;
static jfieldID Gist_aiActualHasSplitStatsId;
static jfieldID Gist_aiActualHasPenaltyStatsId;
static jfieldID Gist_aiOptNameId;
static jfieldID Gist_aiOptHasWkldStatsId;
static jfieldID Gist_aiOptHasSplitStatsId;
static jfieldID Gist_aiOptHasPenaltyStatsId;
static jfieldID Gist_aiRandomRunsId;
static jfieldID Gist_aiTargetUtilId;
static jfieldID Gist_aiQueryFileId;
static jfieldID Gist_aiNumQueriesId;
static jfieldID Gist_aiNumRetrievedId;
static jfieldID Gist_aiNumItemsId;

static jclass Gist_libgistCommandClass;
static jfieldID Gist_lcCmdTypeId;
static jfieldID Gist_lcFetchLimitId;
static jfieldID Gist_lcQualId; 
static jfieldID Gist_lcKeyId; 
static jfieldID Gist_lcDataId;
static jfieldID Gist_lcIndexNameId;
static jfieldID Gist_lcExtensionId;
static jfieldID Gist_lcFillFactorId;
static jfieldID Gist_lcLoadFileId;
static jfieldID Gist_lcScriptFileId;
static jfieldID Gist_lcAnalysisFileId;
static jfieldID Gist_lcNumRandomRunsId;

static jclass Gist_displayPredInfoClass;
static jfieldID Gist_dpiNodeId;
static jfieldID Gist_dpiSlotId;
static jfieldID Gist_dpiLevelId;
static jfieldID Gist_dpiColorId;

static jclass Gist_jTextAreaClass;
static jmethodID Gist_taAppendId;
static jclass Gist_stringBufferClass;
static jmethodID Gist_sbAppendId;

static jclass Gist_fileClass;
static jmethodID Gist_fInitId;


/*
 * Breakpoints: 
 * Each event has two sets of breakpoints: one multiset, indexed on the node ID specified
 * for the breakpoints, and one list, if it is a general, non-node related breakpoint.
 */

typedef vector<amdb_breakpoints::Breakpoint *> BpVect;
typedef multimap<int, amdb_breakpoints::Breakpoint *, less<int> > BpMap;
typedef pair<const int, amdb_breakpoints::Breakpoint *> BpPair;
BpVect genBps[amdb_breakpoints::numEvents]; // bps without node attachment
BpMap nodeBps[amdb_breakpoints::numEvents]; // bps specific to a node

// return value from Java breakpoint handler
enum WhatToDo {
    nowContinue = 0,
    nowStep, // run until we hit the next step unit
    nowNext, // run until we hit the next entry point
    nowCancel // cancel current function
};
static WhatToDo Gist_whatNow = nowContinue;
static bool Gist_allDisabled = false; // all breakpoints disabled
static JNIEnv* Gist_env; // 'passed' to breakHandler
static int Gist_bpCounter = 0; // ID generator


/*
 * Breakpoint stuff
 */

static void
printBps()
{
    amdb_breakpoints::Breakpoint* bp;
    int i;
    for (i = 0; i < amdb_breakpoints::numEvents; i++) {
        BpMap::iterator it;
        for (it = nodeBps[i].begin(); it != nodeBps[i].end(); it++) {
	    bp = (*it).second;
	    printf("map %d: id: %d, event: %d, node: %d\n",
	        i, bp->id, bp->event, bp->node);
	}
	BpVect::iterator vit;
        for (vit = genBps[i].begin(); vit != genBps[i].end(); vit++) {
	    bp = (*vit);
	    printf("gen %d: id: %d, event: %d, node: %d\n",
	        i, bp->id, bp->event, bp->node);
	}
    }
}

// Converts data in Java Breakpoint object to amdb_breakpoints::Breakpoint.
static void
convertBreakpoint(
    amdb_breakpoints::Breakpoint* bp,
    jobject info,
    JNIEnv* env)
{
    printf("convertBreakpoint\n");
    bp->id = Gist_bpCounter;
    bp->event = (amdb_breakpoints::BreakEvents) env->GetIntField(info, Gist_bpEventId);
    bp->node = env->GetIntField(info, Gist_bpNodeId);
    printf("bp: id=%d, event=%d, node=%d\n", bp->id, bp->event, bp->node);

    jstring param1String = (jstring) env->GetObjectField(info, Gist_bpParam1Id);
    const char* param1 = env->GetStringUTFChars(param1String, NULL);
    jstring param2String = (jstring) env->GetObjectField(info, Gist_bpParam2Id);
    const char* param2 = env->GetStringUTFChars(param2String, NULL);

    // some break events have associated parameters, which are specified as a java.lang.String
    if (bp->event == amdb_breakpoints::locateLeafEvent) {
	if (strcmp(param1, "") == 0) {
	    bp->param.penaltyParam.maxDeviation = -1; // meaning: ignore this
	} else {
	    bp->param.penaltyParam.maxDeviation = atoi(param1);
	}
	printf("locateLeaf: maxDev=%d\n", bp->param.penaltyParam.maxDeviation);
    }
    if (bp->event == amdb_breakpoints::insertEvent) {
	if (strcmp(param1, "") != 0) {
	    bp->param.updateParam.key =
	        strcpy((char *) malloc(strlen(param1) + 1), param1);
	} else {
	    bp->param.updateParam.key = NULL;
	}
	if (strcmp(param2, "") != 0) {
	    bp->param.updateParam.data =
	        strcpy((char *) malloc(strlen(param2) + 1), param2);
	} else {
	    bp->param.updateParam.data = NULL;
	}
	//printf("insert: key=%s, data=%s\n", bp->param.updateParam.key,
	    //bp->param.updateParam.data);
    }

    env->ReleaseStringUTFChars(param1String, param1);
    env->ReleaseStringUTFChars(param2String, param2);
}

// create new breakpoint and return its ID
JNIEXPORT void JNICALL
Java_Libgist_libCreateBp(
    JNIEnv* env,
    jclass cl,
    jobject jbp)
{
    Gist_bpCounter++;
    amdb_breakpoints::Breakpoint *bp = new amdb_breakpoints::Breakpoint();
    convertBreakpoint(bp, jbp, env);
    env->SetIntField(jbp, Gist_bpIdId, bp->id);
    if (bp->node == 0 || amdb_breakpoints::isEntryPoint(bp->event)) {
        // general breakpoint, for no particular node
	BpVect& vect = genBps[bp->event];
	vect.push_back(bp);
	//printf("new vect bp (%d): %d, %d\n", bp, bp->event, bp->node);
    } else {
        // applies to node
	BpMap& map = nodeBps[bp->event];
	map.insert(BpPair(bp->node, bp));
	//printf("new map bp (%d): %d, %d\n", bp, bp->event, bp->node);
    }
}

// get rid of all breakpoints
JNIEXPORT void JNICALL
Java_Libgist_libDeleteBps(
    JNIEnv* env,
    jclass cl)
{
    // empty all vectors/multimaps; also delete the Breakpoint objects
    int i;
    for (i = 0; i < amdb_breakpoints::numEvents; i++) {
	BpVect::iterator it;
	for (it = genBps[i].begin(); it != genBps[i].end(); it++) {
	    amdb_breakpoints::Breakpoint* bp = *it;
	    if (bp->event == amdb_breakpoints::insertEvent) {
	        free(bp->param.updateParam.key);
	        free(bp->param.updateParam.data);
	    }
	    delete bp;
	}
	BpMap::iterator mit;
	for (mit = nodeBps[i].begin(); mit != nodeBps[i].end(); mit++) {
	    amdb_breakpoints::Breakpoint* bp = (*mit).second;
	    if (bp->event == amdb_breakpoints::insertEvent) {
	        free(bp->param.updateParam.key);
	        free(bp->param.updateParam.data);
	    }
	    delete bp;
	}
        genBps[i].erase(genBps[i].begin(), genBps[i].end());
	nodeBps[i].erase(nodeBps[i].begin(), nodeBps[i].end());
    }
    Gist_bpCounter = 0; // start from 0 again
}

JNIEXPORT void JNICALL
Java_Libgist_libSingleStep(
    JNIEnv *env,
    jclass cl)
{
    Gist_whatNow = nowStep;
}

JNIEXPORT void JNICALL
Java_Libgist_libDisableAll(
    JNIEnv *env,
    jclass cl,
    jboolean disable)
{
    printf("all disabled: %d\n", (disable ? 1 : 0));
    Gist_allDisabled = disable;
}

// initialize Gist_infoObj with an amdb_breakpoints::BreakInfo structure
static jobject
createBreakInfo(
    amdb_breakpoints::BreakInfo* info,
    int id)
{
    printf("new BreakInfo\n");
    if (Gist_infoObj == NULL) {
	jobject infoObj = Gist_env->NewObject(Gist_breakInfoClass, Gist_breakInfoConstrId);
	Gist_infoObj = Gist_env->NewGlobalRef(infoObj);
    }
    jobject& result = Gist_infoObj;
    Gist_env->SetIntField(result, Gist_biIdId, id);
    Gist_env->SetIntField(result, Gist_biEventId, info->event);
    Gist_env->SetIntField(result, Gist_biNodeId, (int) info->node);
    if (info->event == amdb_breakpoints::locateLeafEvent) {
	Gist_env->SetDoubleField(result, Gist_biTargetPenaltyId,
	    info->param.locateLeafParam.targetPenalty);
	Gist_env->SetDoubleField(result, Gist_biMinPenaltyId,
	    info->param.locateLeafParam.minPenalty);
	Gist_env->SetIntField(result, Gist_biMinLeafId,
	    info->param.locateLeafParam.minLeaf);
    }
    printf("id=%d, event=%d, node=%d\n", id, info->event, info->node);
    return result;
}

// Test whether the break info triggers the given breakpoint. If it does, call the 
// Java break handler and set whatNow. If no breakpoint is specified, the handler
// is also called.
static bool
testBp(
    amdb_breakpoints::Breakpoint* bp,
    amdb_breakpoints::BreakInfo* info,
    WhatToDo& whatNow)
{
    bool triggersBp = true;
    int bpId = 0; // set to ID of the breakpoint, if it was triggered
    if (bp != NULL) {
	// locateLeaf: check if insertion penalty deviates too much from minimum
	int maxDev = bp->param.penaltyParam.maxDeviation;
	bpId = bp->id;
        if (bp->event == amdb_breakpoints::locateLeafEvent && maxDev != -1) {
	    triggersBp = (info->param.locateLeafParam.targetPenalty /
	        info->param.locateLeafParam.minPenalty) >   
		(1.0 + (double) maxDev / 100.0);
	}
    }
    if (triggersBp) {
	jobject infoObj = createBreakInfo(info, bpId);
	//HANDLEEXCR(Gist_env, false);
	whatNow = (WhatToDo) Gist_env->CallIntMethod(Gist_handler, Gist_handlerId, infoObj);
	//HANDLEEXCR(Gist_env, false);
	return true;
    } else {
        return false;
    }
}

// the C++ breakpoint handler, called from within libgist;
// returns true if the currently executing libgist interface function should
// be cancelled (because the user is tired of executing a script)
static bool
breakHandler(
    amdb_breakpoints::BreakInfo* info)
{

    // see if event signals a structure change
    if (amdb_breakpoints::isStructureUpdate(info->event)) {
	switch (info->event) { 
	case amdb_breakpoints::newNodeEvent: {
	    Gist_indexStruct->splitNode(info->param.newNodeParam.origNode,
		info->param.newNodeParam.rightSib,
		info->param.newNodeParam.rightChildren);
	    break;
	}
	case amdb_breakpoints::newRootEvent: {
	    Gist_indexStruct->splitRoot(info->param.newRootParam.leftNode,
		info->param.newRootParam.rightNode,
		info->param.newRootParam.rightChildren);
	    break;
	}
	case amdb_breakpoints::relocateChildEvent: {
	    Gist_indexStruct->splitRoot(info->param.newRootParam.leftNode,
		info->param.newRootParam.rightNode,
		info->param.newRootParam.rightChildren);
	    break;
	}
	case amdb_breakpoints::itemInsertedEvent:
	case amdb_breakpoints::itemDeletedEvent:
	case amdb_breakpoints::bpUpdatedEvent: {
	    // cout << "Node changed: " << info->param.updNodeParam << endl;
	    Gist_indexStruct->updateNode(info->param.updNodeParam);
	    break;
	}
	default: 
	    assert(0);
	}
	// structure has changed: this invalidates existing tree map
	delete _treeMap;
	_treeMap = NULL;
        // return false;
    }

    if (Gist_whatNow == nowStep) {
        // we're single-stepping
	(void) testBp(NULL, info, Gist_whatNow);
	HANDLEEXCR(Gist_env, false);
	return (Gist_whatNow == nowCancel);
    }
    if (Gist_allDisabled) {
        return false;
    }
    if (Gist_whatNow == nowNext && amdb_breakpoints::isEntryPoint(info->event)) {
        // we stop at the beginning of every interface function
	(void) testBp(NULL, info, Gist_whatNow);
	HANDLEEXCR(Gist_env, false);
	return (Gist_whatNow == nowCancel);
    }

    // see if we hit any breakpoints
    BpVect& vect = genBps[info->event];
    // check the general breakpoint(s)
    int i;
    for (i = 0; i < 2; i++) {
	// two rounds: first with original event...
	BpVect::iterator it;
	for (it = vect.begin(); it != vect.end(); it++) {
	    bool triggeredBp = testBp(vect.front(), info, Gist_whatNow);
	    HANDLEEXCR(Gist_env, false);
	    if (triggeredBp) { return Gist_whatNow == nowCancel; }
	}
	// .. the second with a traversalEvent instead of the locateLeafEvent
	if (info->event == amdb_breakpoints::locateLeafEvent) {
	    // Locating an insertion target leaf implies a node traversal, therefore
	    // all (more general) traversalEvent breakpoints also apply to (more specific)
	    // locateLeafEvents
	    vect = genBps[amdb_breakpoints::traversalEvent];
	} else {
	    // skip the 2nd round if no locateLeafEvent
	    break;
	}
    }

    // check the node-specific breakpoints
    BpMap& map = nodeBps[info->event];
    for (i = 0; i < 2; i++) {
        // two rounds again
	BpMap::iterator it;
	for (it = map.find(info->node); it != map.end(); it++) {
	    bool triggeredBp = testBp((*it).second, info, Gist_whatNow);
	    HANDLEEXCR(Gist_env, false);
	    if (triggeredBp) { return Gist_whatNow == nowCancel; }
	}
	if (info->event == amdb_breakpoints::locateLeafEvent) {
	    // Locating an insertion target leaf implies a node traversal, therefore
	    // all (more general) traversalEvent breakpoints also apply to (more specific)
	    // locateLeafEvents
	    map = nodeBps[amdb_breakpoints::traversalEvent];
	} else {
	    // skip the 2nd round if no locateLeafEvent
	    break;
	}
    }

    return false;
}

// determine class object and handler routine ID for later reference
JNIEXPORT void JNICALL
Java_Libgist_libSetBreakHandler(
    JNIEnv *env,
    jclass cl,
    jobject handler)
{
    Gist_handler = env->NewGlobalRef(handler);
    if (Gist_handler == NULL) {
        ERRORRETURN("out of memory");
    }
    jclass handlerClass = env->GetObjectClass(handler);
    Gist_handlerClass = (jclass) env->NewGlobalRef(handlerClass);
    if (Gist_handlerClass == NULL) {
        ERRORRETURN("out of memory");
    }
    Gist_handlerId = env->GetMethodID(Gist_handlerClass, "breakHandler", "(LBreakInfo;)I");
    HANDLEEXC(env);
}


/*
 * Libgist interface functions
 */

// precompute a couple of class and method IDs
JNIEXPORT void JNICALL
Java_Libgist_libInit(
    JNIEnv *env,
    jclass cl)
{
    Gist_gist->setBreakHandler(breakHandler);

    // get global ref to StringBuffer method ID
    DBGPRINT(3, cout << "find StringBuffer" << endl);
    //DBGPRINT(3, cout << "find StringBuffer" << endl);
    jclass stringBufferClass = env->FindClass("java/lang/StringBuffer");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found StringBuffer" << endl);
    Gist_stringBufferClass = (jclass) env->NewGlobalRef(stringBufferClass);
    Gist_sbAppendId = env->GetMethodID(Gist_stringBufferClass, "append",
        "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
    HANDLEEXC(env);

    // get global ref to JTextArea method ID
    DBGPRINT(3, cout << "find JTextArea" << endl);
    jclass jTextAreaClass = env->FindClass("javax/swing/JTextArea");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found JTextArea" << endl);
    Gist_jTextAreaClass = (jclass) env->NewGlobalRef(jTextAreaClass);
    Gist_taAppendId = env->GetMethodID(Gist_jTextAreaClass, "append", "(Ljava/lang/String;)V");
    HANDLEEXC(env);

    // get global ref to File class and constructor
    DBGPRINT(3, cout << "find File" << endl);
    jclass fileClass = env->FindClass("java/io/File");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found File" << endl);
    Gist_fileClass = (jclass) env->NewGlobalRef(fileClass);
    Gist_fInitId = env->GetMethodID(Gist_fileClass, "<init>", "(Ljava/lang/String;)V");
    HANDLEEXC(env);

    // get global ref to Breakpoint class and field IDs
    jclass bpClass = env->FindClass("Breakpoint");
    HANDLEEXC(env);
    Gist_breakpointClass = (jclass) env->NewGlobalRef(bpClass);
    //Gist_breakpointConstrId = env->GetMethodID(Gist_breakpointClass, "<init>", "()V");
    //HANDLEEXC(env);
    Gist_bpIdId = env->GetFieldID(Gist_breakpointClass, "id", "I");
    HANDLEEXC(env);
    Gist_bpEventId = env->GetFieldID(Gist_breakpointClass, "event", "I");
    HANDLEEXC(env);
    Gist_bpNodeId = env->GetFieldID(Gist_breakpointClass, "nodeId", "I");
    HANDLEEXC(env);
    Gist_bpParam1Id = env->GetFieldID(Gist_breakpointClass, "param1", "Ljava/lang/String;");
    HANDLEEXC(env);
    Gist_bpParam2Id = env->GetFieldID(Gist_breakpointClass, "param1", "Ljava/lang/String;");
    HANDLEEXC(env);

    // get global ref to BreakInfo class and field IDs
    jclass biClass = env->FindClass("BreakInfo");
    HANDLEEXC(env);
    Gist_breakInfoClass = (jclass) env->NewGlobalRef(biClass);
    Gist_breakInfoConstrId = env->GetMethodID(Gist_breakInfoClass, "<init>", "()V");
    HANDLEEXC(env);
    Gist_biIdId = env->GetFieldID(Gist_breakInfoClass, "id", "I");
    HANDLEEXC(env);
    Gist_biEventId = env->GetFieldID(Gist_breakInfoClass, "event", "I");
    HANDLEEXC(env);
    Gist_biNodeId = env->GetFieldID(Gist_breakInfoClass, "nodeId", "I");
    HANDLEEXC(env);
    Gist_biTargetPenaltyId = env->GetFieldID(Gist_breakInfoClass, "targetPenalty", "D");
    HANDLEEXC(env);
    Gist_biMinPenaltyId = env->GetFieldID(Gist_breakInfoClass, "minPenalty", "D");
    HANDLEEXC(env);
    Gist_biMinLeafId = env->GetFieldID(Gist_breakInfoClass, "minLeaf", "I");
    HANDLEEXC(env);
    //jobject infoObj = Gist_env->NewObject(Gist_breakInfoClass, Gist_breakInfoConstrId);
    //Gist_infoObj = env->NewGlobalRef(infoObj);

    // get global ref to QueryStats class
    jclass queryStatsClass = env->FindClass("QueryStats");
    HANDLEEXC(env);
    Gist_queryStatsClass = (jclass) env->NewGlobalRef(queryStatsClass);
    Gist_qsResultSetLimitId = env->GetFieldID(Gist_queryStatsClass,
        "resultSetLimit", "I");
    HANDLEEXC(env);
    Gist_qsQualId = env->GetFieldID(Gist_queryStatsClass, "qual",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_qsResultSetSizeId = env->GetFieldID(Gist_queryStatsClass, "resultSetSize", "I");
    HANDLEEXC(env);
    Gist_qsAvgUtilId = env->GetFieldID(Gist_queryStatsClass, "avgUtil", "F");
    HANDLEEXC(env);
    Gist_qsRetrievalVolId = env->GetFieldID(Gist_queryStatsClass, "retrievalVol", "I");
    HANDLEEXC(env);
    Gist_qsTotalLeafIosId = env->GetFieldID(Gist_queryStatsClass, "totalLeafIos", "I");
    HANDLEEXC(env);
    Gist_qsMinIosId = env->GetFieldID(Gist_queryStatsClass, "minIos", "I");
    HANDLEEXC(env);
    Gist_qsOptimalIosId = env->GetFieldID(Gist_queryStatsClass, "optimalIos", "I");
    HANDLEEXC(env);
    Gist_qsOptimalOhId = env->GetFieldID(Gist_queryStatsClass, "optimalOh", "F");
    HANDLEEXC(env);
    Gist_qsOptLeafOhId = env->GetFieldID(Gist_queryStatsClass, "optLeafOh", "F");
    HANDLEEXC(env);
    Gist_qsMinLeafOhId = env->GetFieldID(Gist_queryStatsClass, "minLeafOh", "F");
    HANDLEEXC(env);
    Gist_qsRandomIosId = env->GetFieldID(Gist_queryStatsClass, "randomIos", "F");
    HANDLEEXC(env);
    Gist_qsRandomStdDevId = env->GetFieldID(Gist_queryStatsClass, "randomStdDev", "F");
    HANDLEEXC(env);
    Gist_qsOptRandomOhId = env->GetFieldID(Gist_queryStatsClass, "optRandomOh", "F");
    HANDLEEXC(env);
    Gist_qsMinRandomOhId = env->GetFieldID(Gist_queryStatsClass, "minRandomOh", "F");
    HANDLEEXC(env);
    Gist_qsOptClusterLossId = env->GetFieldID(Gist_queryStatsClass, "optClusterLoss", "F");
    HANDLEEXC(env);
    Gist_qsMinClusterLossId = env->GetFieldID(Gist_queryStatsClass, "minClusterLoss", "F");
    HANDLEEXC(env);
    Gist_qsOptClusterOhId = env->GetFieldID(Gist_queryStatsClass, "optClusterOh", "F");
    HANDLEEXC(env);
    Gist_qsMinClusterOhId = env->GetFieldID(Gist_queryStatsClass, "minClusterOh", "F");
    HANDLEEXC(env);
    Gist_qsLeafUtilLossId = env->GetFieldID(Gist_queryStatsClass, "leafUtilLoss", "F");
    HANDLEEXC(env);
    Gist_qsUtilOhId = env->GetFieldID(Gist_queryStatsClass, "utilOh", "F");
    HANDLEEXC(env);
    Gist_qsLeafExcCovLossId = env->GetFieldID(Gist_queryStatsClass, "leafExcCovLoss", "F");
    HANDLEEXC(env);
    Gist_qsExcCovOhId = env->GetFieldID(Gist_queryStatsClass, "excCovOh", "F");
    HANDLEEXC(env);
    Gist_qsTotalInternalIosId = env->GetFieldID(Gist_queryStatsClass,
        "totalInternalIos", "I");
    HANDLEEXC(env);
    Gist_qsInternalUtilLossId = env->GetFieldID(Gist_queryStatsClass,
        "internalUtilLoss", "F");
    HANDLEEXC(env);
    Gist_qsInternalExcCovLossId = env->GetFieldID(Gist_queryStatsClass,
        "internalExcCovLoss", "F");
    HANDLEEXC(env);

    // get global ref to AnalysisInfo class
    DBGPRINT(3, cout << "find AnalysisInfo" << endl);
    jclass analysisInfoClass = env->FindClass("AnalysisInfo");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found AnalysisInfo" << endl);
    Gist_analysisInfoClass = (jclass) env->NewGlobalRef(analysisInfoClass);
    Gist_aiActualNameId = env->GetFieldID(Gist_analysisInfoClass, "actualName",
        "Ljava/lang/String;");
    HANDLEEXC(env);
    Gist_aiActualHasWkldStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "actualHasWkldStats", "Z");
    HANDLEEXC(env);
    Gist_aiActualHasSplitStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "actualHasSplitStats", "Z");
    HANDLEEXC(env);
    Gist_aiActualHasPenaltyStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "actualHasPenaltyStats", "Z");
    HANDLEEXC(env);
    Gist_aiOptNameId = env->GetFieldID(Gist_analysisInfoClass, "optName",
        "Ljava/lang/String;");
    HANDLEEXC(env);
    Gist_aiOptHasWkldStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "optHasWkldStats", "Z");
    HANDLEEXC(env);
    Gist_aiOptHasSplitStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "optHasSplitStats", "Z");
    HANDLEEXC(env);
    Gist_aiOptHasPenaltyStatsId = env->GetFieldID(Gist_analysisInfoClass,
        "optHasPenaltyStats", "Z");
    HANDLEEXC(env);
    Gist_aiRandomRunsId = env->GetFieldID(Gist_analysisInfoClass, "randomRuns", "I");
    HANDLEEXC(env);
    Gist_aiTargetUtilId = env->GetFieldID(Gist_analysisInfoClass, "targetUtil", "F");
    HANDLEEXC(env);
    Gist_aiQueryFileId = env->GetFieldID(Gist_analysisInfoClass, "queryFile",
        "Ljava/lang/String;");
    HANDLEEXC(env);
    Gist_aiNumQueriesId = env->GetFieldID(Gist_analysisInfoClass, "numQueries", "I");
    HANDLEEXC(env);
    Gist_aiNumRetrievedId = env->GetFieldID(Gist_analysisInfoClass, "numRetrieved", "I");
    HANDLEEXC(env);
    Gist_aiNumItemsId = env->GetFieldID(Gist_analysisInfoClass, "numItems", "I");
    HANDLEEXC(env);

    // get global ref to LibgistCommand class
    DBGPRINT(3, cout << "find LibgistCommand" << endl);
    jclass libgistCommandClass = env->FindClass("LibgistCommand");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found LibgistCommand" << endl);
    Gist_libgistCommandClass = (jclass) env->NewGlobalRef(libgistCommandClass);
    Gist_lcCmdTypeId = env->GetFieldID(Gist_libgistCommandClass, "cmdType", "I");
    HANDLEEXC(env);
    Gist_lcFetchLimitId = env->GetFieldID(Gist_libgistCommandClass, "fetchLimit", "I");
    HANDLEEXC(env);
    Gist_lcQualId = env->GetFieldID(Gist_libgistCommandClass, "qual",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcKeyId = env->GetFieldID(Gist_libgistCommandClass, "key",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcDataId = env->GetFieldID(Gist_libgistCommandClass, "data",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcIndexNameId = env->GetFieldID(Gist_libgistCommandClass, "indexName",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcExtensionId = env->GetFieldID(Gist_libgistCommandClass, "data",
        "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcFillFactorId = env->GetFieldID(Gist_libgistCommandClass, "fillFactor", "F");
    HANDLEEXC(env);
    Gist_lcLoadFileId = env->GetFieldID(Gist_libgistCommandClass,
        "loadFile", "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcScriptFileId = env->GetFieldID(Gist_libgistCommandClass,
        "scriptFile", "Ljava/lang/StringBuffer;");
    HANDLEEXC(env);
    Gist_lcAnalysisFileId = env->GetFieldID(Gist_libgistCommandClass,
        "analysisFile", "Ljava/io/File;");
    HANDLEEXC(env);
    Gist_lcNumRandomRunsId = env->GetFieldID(Gist_libgistCommandClass,
        "numRandomRuns", "I");
    HANDLEEXC(env);

    DBGPRINT(3, cout << "find DisplayPredInfo" << endl);
    jclass displayPredInfoClass = env->FindClass("DisplayPredInfo");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found DisplayPredInfo" << endl);
    Gist_displayPredInfoClass =
        (jclass) env->NewGlobalRef(displayPredInfoClass);
    Gist_dpiNodeId = env->GetFieldID(Gist_displayPredInfoClass, "node", "I");
    HANDLEEXC(env);
    Gist_dpiSlotId = env->GetFieldID(Gist_displayPredInfoClass, "slot", "I");
    HANDLEEXC(env);
    Gist_dpiLevelId = env->GetFieldID(Gist_displayPredInfoClass, "level", "I");
    HANDLEEXC(env);
    Gist_dpiColorId = env->GetFieldID(Gist_displayPredInfoClass, "color", "I");
    HANDLEEXC(env);

    // get global ref to SplitStats class
    DBGPRINT(3, cout << "find SplitStats" << endl);
    jclass splitStatsClass = env->FindClass("SplitStats");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found SplitStats" << endl);
    Gist_splitStatsClass = (jclass) env->NewGlobalRef(splitStatsClass);
    Gist_ssPreIosId = env->GetFieldID(Gist_splitStatsClass, "preIos", "F");
    HANDLEEXC(env);
    Gist_ssOptIosId = env->GetFieldID(Gist_splitStatsClass, "optIos", "F");
    HANDLEEXC(env);
    Gist_ssActualIosId = env->GetFieldID(Gist_splitStatsClass, "actualIos", "F");
    HANDLEEXC(env);
    Gist_ssPreExcCovLossId = env->GetFieldID(Gist_splitStatsClass, "preExcCovLoss",
        "F");
    HANDLEEXC(env);
    Gist_ssActualExcCovLossId = env->GetFieldID(Gist_splitStatsClass,
        "actualExcCovLoss", "F");
    HANDLEEXC(env);
    Gist_ssOptClusterDeltaId = env->GetFieldID(Gist_splitStatsClass,
        "optClusterDelta", "F");
    HANDLEEXC(env);
    Gist_ssActualClusterDeltaId = env->GetFieldID(Gist_splitStatsClass,
        "actualClusterDelta", "F");
    HANDLEEXC(env);
    Gist_ssClusterLossId = env->GetFieldID(Gist_splitStatsClass,
        "clusterLoss", "F");
    HANDLEEXC(env);
    Gist_ssClusterOhId = env->GetFieldID(Gist_splitStatsClass,
        "clusterOh", "F");
    HANDLEEXC(env);
    Gist_ssClusterSuccessId = env->GetFieldID(Gist_splitStatsClass,
        "clusterSuccess", "F");
    HANDLEEXC(env);
    Gist_ssExcCovDeltaId = env->GetFieldID(Gist_splitStatsClass,
        "excCovDelta", "F");
    HANDLEEXC(env);
    Gist_ssExcCovLossId = env->GetFieldID(Gist_splitStatsClass,
        "excCovLoss", "F");
    HANDLEEXC(env);
    Gist_ssExcCovOhId = env->GetFieldID(Gist_splitStatsClass,
        "excCovOh", "F");
    HANDLEEXC(env);
    Gist_ssExcCovSuccessId = env->GetFieldID(Gist_splitStatsClass,
        "excCovSuccess", "F");
    HANDLEEXC(env);

    // get global ref to PenaltyStats class
    DBGPRINT(3, cout << "find PenaltyStats" << endl);
    jclass penaltyStatsClass = env->FindClass("PenaltyStats");
    HANDLEEXC(env);
    DBGPRINT(3, cout << "found PenaltyStats" << endl);
    Gist_penaltyStatsClass = (jclass) env->NewGlobalRef(penaltyStatsClass);
    Gist_psActualAddIosId = env->GetFieldID(Gist_penaltyStatsClass, "actualAddIos", "F");
    HANDLEEXC(env);
    Gist_psOptAddIosId = env->GetFieldID(Gist_penaltyStatsClass, "optAddIos", "F");
    HANDLEEXC(env);
    Gist_psActualExcCovId = env->GetFieldID(Gist_penaltyStatsClass, "actualExcCov", "F");
    HANDLEEXC(env);
    Gist_psExcCovDeltaId = env->GetFieldID(Gist_penaltyStatsClass, "excCovDelta", "F");
    HANDLEEXC(env);
    Gist_psClusterLossId = env->GetFieldID(Gist_penaltyStatsClass, "clusterLoss", "F");
    HANDLEEXC(env);
    Gist_psExcCovOhId = env->GetFieldID(Gist_penaltyStatsClass, "excCovOh", "F");
    HANDLEEXC(env);
    Gist_psExcCovSuccessId = env->GetFieldID(Gist_penaltyStatsClass, "excCovSuccess", "F");
    HANDLEEXC(env);
    Gist_psKeyId = env->GetFieldID(Gist_penaltyStatsClass, "key", "Ljava/lang/String;");
    HANDLEEXC(env);

}

JNIEXPORT jobjectArray JNICALL
Java_Libgist_libGetExtensionInfo(
    JNIEnv *env,
    jclass cl)
{
    jclass extInfoClass;
    jobjectArray extArray;
    jobject extInfo;
    jmethodID initMethod;
    const char *name;
    int id;

    extInfoClass = env->FindClass("ExtensionInfo");
    HANDLEEXCR(env, NULL);
    assert(extInfoClass);
    extArray = env->NewObjectArray(gist_ext_t::gist_numext, extInfoClass, NULL);
    HANDLEEXCR(env, NULL);
    assert(extArray);
    initMethod = env->GetMethodID(extInfoClass, "<init>", "(Ljava/lang/String;I)V");
    HANDLEEXCR(env, NULL);
    int i;
    for (i = 0; i < gist_ext_t::gist_numext; i++) {
        // construct the new ExtInfo object
	DBGPRINT(3, cout << "ext_list[" << i << "]: " << gist_ext_t::gist_ext_list[i] << endl);
	name = gist_ext_t::gist_ext_list[i]->myName;
	id = gist_ext_t::gist_ext_list[i]->myId;
	extInfo = env->NewObject(extInfoClass, initMethod, env->NewStringUTF(name), id);
	HANDLEEXCR(env, NULL);
	env->SetObjectArrayElement(extArray, i, extInfo);
	HANDLEEXCR(env, NULL);
    }

    //printf("x finished!\n");
    return extArray;
}

JNIEXPORT void JNICALL
Java_Libgist_libCreate(
    JNIEnv *env,
    jclass cl,
    jstring fileName,
    jint extId)
{
    DBGPRINT(1, cout << "libCreate()" << endl);
    const char* fname = env->GetStringUTFChars(fileName, NULL);
    //printf("creating: %s with %s\n", fname, gist_ext_t::gist_ext_list[extId]->myName);
    Gist_env = env;
    rc_t status = Gist_gist->create(fname, gist_ext_t::gist_ext_list[extId]);
    CHECKSTATUS(status, env, "gist::create failed");

    // remember the filename, in case we need to copy the file
    free(Gist_filename);
    Gist_filename = strdup(fname);

    // create a main-memory representation of the index structure
    delete Gist_indexStruct;
    Gist_indexStruct = new amdb_idxstruct(Gist_gist);

    env->ReleaseStringUTFChars(fileName, fname);
}


///////////////////////////////////////////////////////////////////////////////
// libOppen - open index, create amdb_idxstruct_t and reset treemap
//
// Description:
//
// Exceptions:
//      LibgistException
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libOpen(
    JNIEnv *env,
    jclass cl,
    jstring fileName)
{
    DBGPRINT(1, cout << "libOpen()" << endl);
    const char* fname = env->GetStringUTFChars(fileName, NULL);
    cout << "opening: " << fname << endl;
    if (Gist_gist != NULL) {
        Java_Libgist_libClose(env, cl);
    }
    Gist_env = env;
    rc_t status = Gist_gist->open(fname);
    CHECKSTATUS(status, env, "gist::open failed");

    // remember the filename, in case we need to copy the file
    free(Gist_filename);
    Gist_filename = strdup(fname);

    // create a main-memory representation of the index structure
    delete Gist_indexStruct;
    Gist_indexStruct = new amdb_idxstruct(Gist_gist);

    // reset nodeStats to force recomputation
    delete _treeMap;
    _treeMap = NULL;

    env->ReleaseStringUTFChars(fileName, fname);
}


///////////////////////////////////////////////////////////////////////////////
// libCleanup - close index and analysis and free associated resources
//
// Description:
//
// Exceptions:
//      LibgistException
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libCleanup(
    JNIEnv* env,
    jclass cl)
{
    if (Gist_analysis != NULL) {
	Java_Libgist_libCloseAnalysis(env, cl);
    }
    if (Gist_gist != NULL) {
        Java_Libgist_libClose(env, cl);
    }
}


///////////////////////////////////////////////////////////////////////////////
// libOpenAnalysis - allocate and read analysis
//
// Description:
//
// Exceptions:
//      LibgistException
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libOpenAnalysis(
    JNIEnv *env,
    jclass cl,
    jstring name)
{
    DBGPRINT(1, cout << "libOpenAnalysis()" << endl);
    const char* fname = env->GetStringUTFChars(name, NULL);
    cout << "opening analysis: " << fname << endl;
    if (Gist_analysis != NULL) {
	Java_Libgist_libCloseAnalysis(env, cl);
    }
    Gist_analysis = new amdb_analysis();
    rc_t status = Gist_analysis->read(fname);
    CHECKSTATUS(status, env, "amdb_analysis::read() failed");

    // remember the filename in order to be able to write it back later
    free(Gist_analysisname);
    Gist_analysisname = strdup(fname);

    env->ReleaseStringUTFChars(name, fname);
    DBGPRINT(1, cout << "exit libOpenAnalysis()" << endl);
}


///////////////////////////////////////////////////////////////////////////////
// libClose - close index and free associated resources
//
// Description:
//
// Exceptions:
//      LibgistException
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libClose(
    JNIEnv *env,
    jclass cl)
{
    DBGPRINT(1, cout << "libClose()" << endl);
    //printf("closing\n");
    Gist_env = env;
    rc_t status = Gist_gist->close();
    CHECKSTATUS(status, env, "gist::close failed");

    free(Gist_filename);
    Gist_filename = NULL;
    delete Gist_indexStruct;
    Gist_indexStruct = NULL;
    delete _treeMap;
    _treeMap = NULL;
    DBGPRINT(1, cout << "exit libClose()" << endl);
}


///////////////////////////////////////////////////////////////////////////////
// libWriteAnalysis - write analysis back to file
//
// Description:
// Exceptions: LibgistException
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libWriteAnalysis(
    JNIEnv *env,
    jclass cl)
{
    DBGPRINT(1, cout << "libWriteAnalysis()" << endl);
    //printf("closing\n");
    assert(Gist_analysis != NULL);
    rc_t status = Gist_analysis->write(Gist_analysisname, false);
    CHECKSTATUS(status, env, "amdb_analysis::write() failed");
}


///////////////////////////////////////////////////////////////////////////////
// libCloseAnalysis - deallocate analysis
//
// Description:
// Exceptions: LibgistException
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libCloseAnalysis(
    JNIEnv *env,
    jclass cl)
{
    DBGPRINT(1, cout << "libCloseAnalysis()" << endl);
    free(Gist_analysisname);
    Gist_analysisname = NULL;
    delete Gist_analysis;
    Gist_analysis = NULL;
}

JNIEXPORT void JNICALL
Java_Libgist_libFlush(
    JNIEnv *env,
    jclass cl)
{
    DBGPRINT(1, cout << "libFlush()" << endl);
    //printf("flushing\n");
    Gist_env = env;
    rc_t status = Gist_gist->flush();
    CHECKSTATUS(status, env, "gist::flush failed");
}

JNIEXPORT void JNICALL
Java_Libgist_libSave(
    JNIEnv *env,
    jclass cl,
    jstring filename)
{
    DBGPRINT(1, cout << "libSave()" << endl);
    // first save all changes, then make a copy of the file
    //printf("save\n");
    Gist_env = env;
    rc_t status = Gist_gist->flush();
    CHECKSTATUS(status, env, "gist::flush failed");

    const char* dest = env->GetStringUTFChars(filename, NULL);
    assert(Gist_filename != NULL);
    char buf[1024];
    sprintf(buf, "cp %s %s", Gist_filename, dest);
    env->ReleaseStringUTFChars(filename, dest);
    int res = system(buf);
    if (res == -1) {
        // something went wrong
        jclass excCl = (env)->FindClass("LibgistException");
	if (excCl == NULL) {
	    return;
	}
	(env)->ThrowNew(excCl, strerror(errno));
	return;
    }
}

JNIEXPORT void JNICALL
Java_Libgist_libInsert(
    JNIEnv *env,
    jclass cl,
    jstring jkey,
    jstring jdata)
{
    DBGPRINT(1, cout << "libInsert()" << endl);

    char _key[gist_p::max_tup_sz];
    void* key = (void *) _key;
    char _data[gist_p::max_tup_sz];
    void* data = (void *) _data;
    int klen, dlen;
    Gist_env = env;
    gist_ext_t::gist_ext_ids extId = Gist_gist->extension()->myId;
    gist_ext_t* ext = gist_ext_t::gist_ext_list[extId];

    // parse key
    const char *keyStr = env->GetStringUTFChars(jkey, NULL);
    rc_t status = ext->parsePred(keyStr, key, klen);
    CHECKSTATUS(status, env, "could not parse key");

    // parse data
    const char *dataStr = env->GetStringUTFChars(jdata, NULL);
    status = ext->parseData(dataStr, data, dlen);
    CHECKSTATUS(status, env, "could not parse data");

    printf("inserting %s, %s\n", keyStr, dataStr);

    printf("parsed: ");
    vec_t keyv(key, klen);
    ext->printPred(cout, keyv, 0);
    printf(", ");
    vec_t datav(data, dlen);
    ext->printData(cout, datav);
    printf("\n");

    status = Gist_gist->insert(key, klen, data, dlen);
    CHECKSTATUS(status, env, "gist::insert failed");

    env->ReleaseStringUTFChars(jkey, keyStr);
    env->ReleaseStringUTFChars(jdata, dataStr);
}

JNIEXPORT void JNICALL
Java_Libgist_libRemove(
    JNIEnv *env,
    jclass cl,
    jstring query)
{
    DBGPRINT(1, cout << "libRemove()" << endl);

    gist_query_t* q;
    Gist_env = env;
    gist_ext_t::gist_ext_ids extId = Gist_gist->extension()->myId;
    gist_ext_t* ext = gist_ext_t::gist_ext_list[extId];

    // parse query
    const char* qStr = env->GetStringUTFChars(query, NULL);
    rc_t status = ext->parseQuery(qStr, q);
    CHECKSTATUS(status, env, "could not parse query");

    //printf("removing %s\n", qStr);

    status = Gist_gist->remove(q);
    CHECKSTATUS(status, env, "gist::remove failed");

    env->ReleaseStringUTFChars(query, qStr);
    delete q;
}

JNIEXPORT void JNICALL
Java_Libgist_libFetch(
    JNIEnv *env,
    jclass cl,
    jstring query,
    jint limit,
    jobject procResult)
{
    DBGPRINT(1, cout << "libFetch()" << endl);

    gist_query_t* q;
    Gist_env = env;
    gist_ext_t::gist_ext_ids extId = Gist_gist->extension()->myId;
    gist_ext_t* ext = gist_ext_t::gist_ext_list[extId];

    // parse query
    const char* qStr = env->GetStringUTFChars(query, NULL);
    rc_t status = ext->parseQuery(qStr, q);
    CHECKSTATUS(status, env, "could not parse query");

    // find processing function
    jclass objCl = env->GetObjectClass(procResult);
    jmethodID procId = env->GetMethodID(objCl, "processItem",
        "(Ljava/lang/String;Ljava/lang/String;)V");
    if (procId == 0) {
        // what's wrong now?
	ERRORRETURN("Couldn't find ResultProcessor.processItem method ID");
    }

    //printf("searching %s\n", qStr);

    gist_cursor_t cursor;
    status = Gist_gist->fetch_init(cursor, q, limit);
    CHECKSTATUS(status, env, "gist::fetch_init failed");
    bool eof = false;
    char _key[gist_p::max_tup_sz];
    void* key = (void *) _key;
    char _data[gist_p::max_tup_sz];
    void* data = (void *) _data;
    smsize_t klen, dlen;
    for (;;) {
	klen = gist_p::max_tup_sz;
	dlen = gist_p::max_tup_sz;
        status = Gist_gist->fetch(cursor, key, klen, data, dlen, eof);
	CHECKSTATUS(status, env, "gist::fetch failed");

	if (eof) break; // done

	// convert to jstrings
	vec_t keyv(key, klen);
	char buf[gist_p::max_tup_sz];
	(void) memset(buf, 0, sizeof(buf));
	ostrstream predStream(buf, gist_p::max_tup_sz);
	ext->printPred(predStream, keyv, 0);
	//cout << "fetched " <<  buf << ": ";
	jstring jkey = env->NewStringUTF(buf);
	HANDLEEXC(env);
	(void) memset(buf, 0, sizeof(buf));
	ostrstream dataStream(buf, gist_p::max_tup_sz);
	vec_t datav(data, dlen);
	ext->printData(dataStream, datav);
	//cout << buf << endl;;
	jstring jdata = env->NewStringUTF(buf);
	HANDLEEXC(env);

	env->CallVoidMethod(procResult, procId, jkey, jdata);
	HANDLEEXC(env);
    }

    env->ReleaseStringUTFChars(query, qStr);
    delete q;
}

JNIEXPORT void JNICALL
Java_Libgist_libCheck(
    JNIEnv *env,
    jclass cl)
{
}

JNIEXPORT jint JNICALL
Java_Libgist_libDump(
    JNIEnv *env,
    jclass cl,
    jobject textArea,
    jint pgNo)
{
    char buf[DUMPBUFLEN];
    (void) memset(buf, 0, DUMPBUFLEN);
    ostrstream dumpStr(buf, DUMPBUFLEN);
    Gist_gist->dump(dumpStr, pgNo);

    // transfer content of buf to text area
    jstring bufString = env->NewStringUTF(buf);
    env->CallVoidMethod(textArea, Gist_taAppendId, bufString);
    return strlen(buf);
}

JNIEXPORT jint JNICALL
Java_Libgist_libPickSplit(
    JNIEnv* env,
    jclass cl,
    jint pgno,
    jintArray splitEntries)
{
    jsize maxEntries = env->GetArrayLength(splitEntries);
    jint* entriesCopy = env->GetIntArrayElements(splitEntries, NULL);
    gist::AlignedPred x, y;
    vec_t leftBp(x.pred, gist_p::max_tup_sz);
    vec_t rightBp(y.pred, gist_p::max_tup_sz);

    assert(Gist_gist != NULL);
    int entries[gist_p::max_scnt]; // jint is long int, so we need to copy those
    int numSplit;
    rc_t status = Gist_gist->pickSplit((shpid_t) pgno, entries, numSplit, leftBp, rightBp);
    CHECKSTATUSR(status, env, "gist::pickSplit failed", 0);
    int i;
    for (i = 0; i < numSplit; i++) {
        entriesCopy[i] = (jint) entries[i];
    }

    env->ReleaseIntArrayElements(splitEntries, entriesCopy, 0);
    return numSplit;
}

static int 
jintCmp(
    const void* a,
    const void* b)
{
    const jint* l = (jint*) a;
    const jint* r = (jint*) b;
    return ((*l < *r) ? -1 : ((*l > *r) ? 1 : 0));
}

/*
 * Tree info functions
 */

JNIEXPORT jint JNICALL
Java_Libgist_libGetPageCount(
    JNIEnv *en,
    jclass cl)
{
    DBGPRINT(1, cout << "libGetPageCount()" << endl);
    assert(Gist_gist != NULL);
    return Gist_gist->pageCount();
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetRoot(
    JNIEnv *en,
    jclass cl)
{
    DBGPRINT(1, cout << "libGetRoot()" << endl);
    assert(Gist_indexStruct != NULL);
    return Gist_indexStruct->rootNo;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetParent(
    JNIEnv *env,
    jclass cl,
    jint pgNo)
{
    DBGPRINT(1, cout << "libGetParent()" << endl);
    assert(Gist_indexStruct != NULL);
    return ((amdb_idxstruct::NodeStruct *) Gist_indexStruct->nodeMap[pgNo])->parent;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetLevel(
    JNIEnv *env,
    jclass cl,
    jint pgNo)
{
    assert(Gist_indexStruct != NULL);
    amdb_idxstruct::NodeStruct* ns = 
        (amdb_idxstruct::NodeStruct*) Gist_indexStruct->nodeMap[pgNo];
    if (ns == NULL) {
        return(-1);
    } else {
        return(ns->level);
    }
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetParentPos(
    JNIEnv *env,
    jclass cl,
    jint pgNo)
{
    DBGPRINT(1, cout << "libGetParentPos()" << endl);

    assert(Gist_indexStruct != NULL);
    if (pgNo == (jint) Gist_indexStruct->rootNo) return -1;

    // We can't look at the position of the pgNo pointer in the amdb_idxstruct,
    // because NodeStruct.children might not reflect the actual order of the entries
    // on the page (due to relocateChild(), I believe).
    shpid_t parent =
        ((amdb_idxstruct::NodeStruct *) Gist_indexStruct->nodeMap[pgNo])->parent;
    Vector children; // vector<shpid_t>
    // gist::getChildren() returns the children in the order they're in on the page
    int dummy;
    rc_t status = Gist_gist->getChildren(parent, dummy, &children);
    CHECKSTATUSR(status, env, "gist::getChildren failed", -1);

    // locate child pointer
    int pos = 0;
    Vector::iterator it;
    for (it = children.begin(); it != children.end(); it++, pos++) {
        shpid_t childNo = (shpid_t) *it;
	if ((shpid_t) pgNo == childNo) return pos;
    }
    assert(0); // pgNo not a child of parent?
    return 0;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetChildren(
    JNIEnv *env,
    jclass cl,
    jint parent,
    jintArray children)
{
    DBGPRINT(1, cout << "libGetChildren()" << endl);

    amdb_idxstruct::NodeStruct* ns =
        (amdb_idxstruct::NodeStruct *) Gist_indexStruct->nodeMap[parent];
    if (ns == NULL) {
        // request for a non-existent node
	ERRORRETURNV("node doesn't exist", 0);
    }
    jsize maxChildren = env->GetArrayLength(children);
    jint* childCopy = env->GetIntArrayElements(children, NULL);
    if (childCopy == NULL) {
        ERRORRETURNV("couldn't copy child array", 0);
    }
    jint* pos = childCopy;
    amdb_idxstruct::ChildIterator it;
    for (it = ns->children.begin(); it != ns->children.end(); it++, pos++) {
	*pos = (int) *it;
    }
    env->ReleaseIntArrayElements(children, childCopy, 0);
    return(ns->children.size());
}

JNIEXPORT jint JNICALL
Java_Libgist_libMaxChildren(
    JNIEnv* env,
    jclass cl)
{
    return gist_p::max_scnt;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetPath(
    JNIEnv *env,
    jclass cl,
    jint pgno,
    jintArray path)
{
    DBGPRINT(1, cout << "libGetPath()" << endl);
    jsize pLen = env->GetArrayLength(path);
    jint* pathCopy = env->GetIntArrayElements(path, NULL);
    int cnt = 0;
    for (;;) {
        pathCopy[cnt] = pgno;
	cnt++;
	if ((unsigned int) pgno == Gist_indexStruct->rootNo) break;
	amdb_idxstruct::NodeStruct* ns =
	    (amdb_idxstruct::NodeStruct *) Gist_indexStruct->nodeMap[pgno];
	if (ns == NULL) {
	    // request for non-existent node
	    ERRORRETURNV("node doesn't exist", 0);
	}
	pgno = ns->parent;
    }
    env->ReleaseIntArrayElements(path, pathCopy, 0);
    return cnt;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetNonce(
    JNIEnv *env,
    jclass cl,
    jint pgno)
{
    DBGPRINT(1, cout << "libGetNonce()" << endl);

    amdb_idxstruct::NodeStruct* ns =
	(amdb_idxstruct::NodeStruct *) Gist_indexStruct->nodeMap[pgno];
    if (ns == NULL) {
	// request for non-existent node
	ERRORRETURNV("node doesn't exist", 0);
    }
    return ns->nonce;
}


/*
 * Profiling
 */

// return # of pages in index
JNIEXPORT jint JNICALL
Java_Libgist_libPageCount(
    JNIEnv* env,
    jclass cl)
{
    return Gist_gist->pageCount();
}


///////////////////////////////////////////////////////////////////////////////
// libGetWkldNodeStats - return amdb_wkldprofile/-stats node stats
//
// Description:
//	- query-dependent node stats are extracted from analysis
//	- structural stats are extract from tree map, which is computed
// 	  on demand
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

// corresponds to constants in Gist.java
enum WkldStatTypes {
    traversals = 0,
    retrievals,
    emptySubtrees,
    clusterLoss,
    clusterOh,
    utilLoss,
    utilOh,
    excCovLoss,
    excCovOh,
    nodeUtil,
    slotCnt,
    predSize,
    numWkldStatsTypes
};

JNIEXPORT void JNICALL
Java_Libgist_libGetWkldNodeStats(
    JNIEnv* env,
    jclass cl,
    jint statsType,
    jint queryNo,
    jboolean minStats,
    jfloatArray stats)
{
    DBGPRINT(1, cout << "libGetWkldNodeStats()" << endl);
    jsize statsSize = env->GetArrayLength(stats);
    if (statsSize < Gist_gist->pageCount()) {
        cerr << "statsSize < pageCount (" << statsSize << " < " << 
	    Gist_gist->pageCount() << ")" << endl;
        assert(statsSize >= Gist_gist->pageCount());
    }
    jfloat* statsCopy = env->GetFloatArrayElements(stats, NULL);

    // initialize stats array to statsType-specific value
    int initVal[numWkldStatsTypes] = {
        0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0
    };
    int i;
    for (i = 0; i < statsSize; i++) {
        statsCopy[i] = initVal[statsType];
    }

    // for now, we only deal with the actual tree
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;

    // extract from amdb_wkldprofile::TraversalStats
    if (statsType == traversals || statsType == retrievals ||
        statsType == emptySubtrees) {

	assert(Gist_analysis != NULL);
	assert(target.profile != NULL);

	amdb_wkldprofile::TraversalStatsMap* tsMap;
	if (queryNo == 0) {
	    // we want totals
	    tsMap = &target.profile->statsTotals.traversalStats;
	} else {
	    tsMap = new amdb_wkldprofile::TraversalStatsMap();
	    amdb_wkldprofile::Query* query =
	        (amdb_wkldprofile::Query *) target.profile->queries[queryNo-1];
	    target.profile->createTraversalStats(*query, *tsMap);
	}

	amdb_wkldprofile::TraversalStatsMap::const_iterator it;
	for (it = tsMap->begin(); it != tsMap->end(); it++) {
	    shpid_t pageno = (shpid_t) (*it).first;
	    amdb_wkldprofile::TraversalStats* ts = 
	        (amdb_wkldprofile::TraversalStats *) (*it).second;

	    switch (statsType) {
	    case traversals:
	        statsCopy[pageno] = (float) ts->traversalCnt;
		break;
	    case retrievals:
	        statsCopy[pageno] = (float) ts->retrievalCnt;
		break;
	    case emptySubtrees:
	        statsCopy[pageno] = (float) ts->emptySubtree;
		break;
	    default: assert(0); // this isn't right
	    }
	}

	if (queryNo != 0) {
	    // get rid of tsMap
	    amdb_wkldprofile::clearTraversalStatsMap(*tsMap);
	    delete tsMap;
	}
    }

    // extract from amdb_wkldstats::NodeStats
    if (statsType == clusterLoss || statsType == clusterOh ||
        statsType == utilLoss || statsType == utilOh ||
	statsType == excCovLoss || statsType == excCovOh) {

	assert(Gist_analysis != NULL);
	assert(target.wkldStats != NULL);

	amdb_wkldstats::NodeStatsMap* nsMap;
	if (queryNo == 0) {
	    // we want totals
	    nsMap = &target.wkldStats->nodeStats;
	} else {
	    nsMap = new amdb_wkldstats::NodeStatsMap();
	    target.wkldStats->createNodeStats(queryNo, *target.profile,
	        *target.map, Gist_analysis->parameters, *nsMap);
	}

	amdb_wkldstats::NodeStatsMap::const_iterator it;
	for (it = nsMap->begin(); it != nsMap->end(); it++) {
	    shpid_t pageno = (shpid_t) (*it).first;
	    amdb_wkldstats::NodeStats* ns = 
	        (amdb_wkldstats::NodeStats *) (*it).second;

	    switch (statsType) {
	    case clusterLoss:
	        statsCopy[pageno] =
		    (minStats ? ns->minClusterLoss : ns->optClusterLoss);
		break;
	    case clusterOh:
	        statsCopy[pageno] =
		    (minStats ? ns->minClusterOh : ns->optClusterOh);
		break;
	    case utilLoss:
	        statsCopy[pageno] = ns->utilLoss;
		break;
	    case utilOh:
	        statsCopy[pageno] = ns->utilOh;
		break;
	    case excCovLoss:
	        statsCopy[pageno] = ns->excCovLoss;
		break;
	    case excCovOh:
	        statsCopy[pageno] = ns->excCovOh;
		break;
	    default: assert(0); // this isn't right
	    }
	}

	if (queryNo != 0) {
	    // get rid of tsMap
	    amdb_wkldstats::clearNodeStatsMap(*nsMap);
	    delete nsMap;
	}
    }

    // extract from amdb_treemap::PageInfo
    if (statsType == nodeUtil || statsType == slotCnt ||
        statsType == predSize) {

	if (_treeMap == NULL) {
	    // not computed yet
	    _treeMap = new amdb_treemap();
	    Gist_gist->computeTreeMap(_treeMap);
	}

	amdb_treemap::PageMap::const_iterator it;
	for (it = _treeMap->pageMap.begin(); it != _treeMap->pageMap.end(); it++) {

	    shpid_t pageno = (shpid_t) (*it).first;
	    amdb_treemap::PageInfo* info =
	        (amdb_treemap::PageInfo *) (*it).second;

	    switch (statsType) {
	    case nodeUtil:
	        statsCopy[pageno] = info->util;
		break;
	    case slotCnt:
	        statsCopy[pageno] = (float) info->itemCnt;
		break;
	    case predSize:
	        statsCopy[pageno] = info->avgPredLen;
		break;
	    default: assert(0); // this isn't right
	    }
	}
    }

    env->ReleaseFloatArrayElements(stats, statsCopy, 0);
}


///////////////////////////////////////////////////////////////////////////////
// libGetSplitNodeStats - return amdb_splitstats node stats
//
// Description:
//	- only set those array elements that correspond to leaves,
//	  leave rest unchanged
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

// corresponds to constants in Gist.java
enum SplitStatsTypes {
    clustLossStats = 0,
    excCovLossStats,
    clustSuccessStats,
    excCovSuccessStats,
    optClustDeltaStats,
    actualClustDeltaStats,
    excCovDeltaStats,
    numSplitStatsTypes
};

JNIEXPORT void JNICALL
Java_Libgist_libGetSplitNodeStats(
    JNIEnv* env,
    jclass cl,
    jint statsType,
    jboolean delta,
    jboolean weighted,
    jfloatArray statsArray)
{
    DBGPRINT(1, cout << "libGetSplitNodeStats()" << endl);
    jsize statsSize = env->GetArrayLength(statsArray);
    if (statsSize < Gist_gist->pageCount()) {
        cerr << "statsSize < pageCount (" << statsSize << " < " << 
	    Gist_gist->pageCount() << ")" << endl;
        assert(statsSize >= Gist_gist->pageCount());
    }
    jfloat* statsCopy = env->GetFloatArrayElements(statsArray, NULL);

    // initialize stats array to statsType-specific value
    int initVal[numSplitStatsTypes] = {
        0, 0, 0, 0, 0, 0, 0
    };
    int i;
    for (i = 0; i < statsSize; i++) {
        statsCopy[i] = initVal[statsType];
    }

    // for now, we only deal with the actual tree
    assert(Gist_analysis != NULL);
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;
    assert(target.splitStats != NULL);
    assert(target.map != NULL);

    amdb_splitstats::SplitStatsMap::const_iterator it;
    amdb_splitstats::FullSplitStats stats;
    for (it = target.splitStats->splitStats.begin();
        it != target.splitStats->splitStats.end(); it++) {

	shpid_t pageno = (shpid_t) (*it).first;
	DBGPRINT(3, cout << "pageno " << pageno << endl);
	amdb_splitstats::SplitStats* st =
	    (amdb_splitstats::SplitStats *) (*it).second;
	assert(st != NULL);
        // compute display values
	stats.set(*st, Gist_analysis->parameters.targetUtil,
	    target.map->util(pageno));

	switch (statsType) {
	case clustLossStats:
	    statsCopy[pageno] = stats.clusterLoss(weighted);
	    break;
	case excCovLossStats:
	    statsCopy[pageno] = stats.excCovLoss();
	    break;
	case clustSuccessStats:
	    statsCopy[pageno] = stats.clusterSuccess(weighted);
	    break;
	case excCovSuccessStats:
	    statsCopy[pageno] = stats.excCovSuccess();
	    break;
	case optClustDeltaStats:
	    statsCopy[pageno] = stats.optClusterDelta(weighted);
	    break;
	case actualClustDeltaStats:
	    statsCopy[pageno] = stats.actualClusterDelta(weighted);
	    break;
	case excCovDeltaStats:
	    statsCopy[pageno] =
	        (float) (stats.actualExcCovLoss - stats.preExcCovLoss);;
	    break;

	default: assert(0); // this isn't right
	}
    }
    env->ReleaseFloatArrayElements(statsArray, statsCopy, 0);
}


///////////////////////////////////////////////////////////////////////////////
// libGetAnalysisInfo - set fields in  Java AnalysisInfo
//
// Description:
//
// Exception:
//	OutOfMemoryError
///////////////////////////////////////////////////////////////////////////////

// return Java ProfileParams
JNIEXPORT void JNICALL
Java_Libgist_libGetAnalysisInfo(
    JNIEnv* env,
    jclass cl,
    jobject info)
{
    DBGPRINT(1, cout << "libGetProfileParams()" << endl);
    assert(Gist_analysis != NULL);

    if (Gist_analysis->actualAnalysis.filename != NULL) {
	jobject str = env->NewStringUTF(Gist_analysis->actualAnalysis.filename);
	HANDLEEXC(env);
	env->SetObjectField(info, Gist_aiActualNameId, str);
    }
    env->SetBooleanField(info, Gist_aiActualHasWkldStatsId,
        (jboolean) (Gist_analysis->actualAnalysis.wkldStats != NULL));
    env->SetBooleanField(info, Gist_aiActualHasSplitStatsId,
        (jboolean) (Gist_analysis->actualAnalysis.splitStats != NULL));
    env->SetBooleanField(info, Gist_aiActualHasPenaltyStatsId,
        (jboolean) (Gist_analysis->actualAnalysis.penaltyStats != NULL));
    if (Gist_analysis->optAnalysis.filename != NULL) {
	jobject str = env->NewStringUTF(Gist_analysis->optAnalysis.filename);
	HANDLEEXC(env);
	env->SetObjectField(info, Gist_aiOptNameId, str);
    }
    env->SetBooleanField(info, Gist_aiOptHasWkldStatsId,
        (jboolean) (Gist_analysis->optAnalysis.wkldStats != NULL));
    env->SetBooleanField(info, Gist_aiOptHasSplitStatsId,
        (jboolean) (Gist_analysis->optAnalysis.splitStats != NULL));
    env->SetBooleanField(info, Gist_aiOptHasPenaltyStatsId,
        (jboolean) (Gist_analysis->optAnalysis.penaltyStats != NULL));
    env->SetIntField(info, Gist_aiRandomRunsId, Gist_analysis->parameters.randomRuns);
    env->SetFloatField(info, Gist_aiTargetUtilId, Gist_analysis->parameters.targetUtil);
    if (Gist_analysis->queryFile != NULL) {
	jobject str = env->NewStringUTF(Gist_analysis->queryFile);
	HANDLEEXC(env);
	env->SetObjectField(info, Gist_aiQueryFileId, str);
    }
    env->SetIntField(info, Gist_aiNumQueriesId,
        Gist_analysis->actualAnalysis.profile->queries.size());
    env->SetIntField(info, Gist_aiNumRetrievedId,
        Gist_analysis->actualAnalysis.profile->statsTotals.dataCoverage);
    env->SetIntField(info, Gist_aiNumItemsId,
        Gist_analysis->actualAnalysis.map->itemMap.size());

}


///////////////////////////////////////////////////////////////////////////////
// libGetQueryStats  -
//	return Java QueryStats for individual query or totals
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libGetQueryStats(
    JNIEnv* env,
    jclass cl,
    jint queryNo,
    jobject s)
{
    DBGPRINT(1, cout << "libGetQueryStats()" << endl);
    assert(Gist_analysis != NULL);
    assert(Gist_analysis->actualAnalysis.profile != NULL);
    assert((unsigned) queryNo <=
        Gist_analysis->actualAnalysis.profile->queries.size());
    amdb_wkldprofile::QueryStats* pqs;
    amdb_wkldstats::QueryStats* qs;
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;

    if (queryNo == 0) {
	// no resultSetLimit or qual
        // we want cumulative stats
	env->SetIntField(s, Gist_qsResultSetSizeId,
	    target.profile->statsTotals.retrievedCnt);
	pqs = &target.profile->statsTotals.stats;
	qs = &target.wkldStats->statsTotals;
    } else {
	amdb_wkldprofile::Query* query =
	    (amdb_wkldprofile::Query *) target.profile->queries[queryNo-1];
	assert(query != NULL);
	env->SetIntField(s, Gist_qsResultSetLimitId, query->retrLimit);
	stringBufferAppend(env, env->GetObjectField(s, Gist_qsQualId), query->qual);
	env->SetIntField(s, Gist_qsResultSetSizeId, (int) query->resultSetSize);
	pqs = &query->stats;
	qs = (amdb_wkldstats::QueryStats *)
	    target.wkldStats->queryStats[queryNo-1];
	//cout << "query->resultSet->size(): " << query->resultSetSize << endl;
    }
    assert(pqs != NULL); // we need those 

    env->SetFloatField(s, Gist_qsAvgUtilId, pqs->leafStats.avgUtil);
    env->SetIntField(s, Gist_qsRetrievalVolId, pqs->leafStats.retrievalVol);
    env->SetIntField(s, Gist_qsTotalLeafIosId, pqs->leafStats.totalIos);
    env->SetIntField(s, Gist_qsTotalInternalIosId, pqs->internalStats.totalIos);

    bool isNull = (qs == NULL);
    env->SetIntField(s, Gist_qsMinIosId,
        (isNull ? 0 : qs->leafStats.minIos));
    env->SetIntField(s, Gist_qsOptimalIosId,
        (isNull ? 0 : qs->leafStats.optimalIos));
    env->SetFloatField(s, Gist_qsOptimalOhId,
        (isNull ? 0.0 : qs->leafStats.optimalOh));
    env->SetFloatField(s, Gist_qsOptLeafOhId,
        (isNull ? 0.0 : qs->leafStats.optLeafOh));
    env->SetFloatField(s, Gist_qsMinLeafOhId,
        (isNull ? 0.0 : qs->leafStats.minLeafOh));
    env->SetFloatField(s, Gist_qsRandomIosId,
        (isNull ? 0.0 : qs->leafStats.randomIos));
    env->SetFloatField(s, Gist_qsRandomStdDevId,
        (isNull ? 0.0 : qs->leafStats.randomStdDev));
    env->SetFloatField(s, Gist_qsOptRandomOhId,
        (isNull ? 0.0 : qs->leafStats.optRandomOh));
    env->SetFloatField(s, Gist_qsMinRandomOhId,
        (isNull ? 0.0 : qs->leafStats.minRandomOh));
    env->SetFloatField(s, Gist_qsOptClusterLossId,
        (isNull ? 0.0 : qs->leafStats.optClusterLoss));
    env->SetFloatField(s, Gist_qsOptClusterOhId,
        (isNull ? 0.0 : qs->leafStats.optClusterOh));
    env->SetFloatField(s, Gist_qsMinClusterLossId,
        (isNull ? 0.0 : qs->leafStats.minClusterLoss));
    env->SetFloatField(s, Gist_qsMinClusterOhId,
        (isNull ? 0.0 : qs->leafStats.minClusterOh));
    env->SetFloatField(s, Gist_qsLeafUtilLossId,
        (isNull ? 0.0 : qs->leafStats.utilLoss));
    env->SetFloatField(s, Gist_qsUtilOhId,
        (isNull ? 0.0 : qs->leafStats.utilOh));
    env->SetFloatField(s, Gist_qsLeafExcCovLossId,
        (isNull ? 0.0 : qs->leafStats.excCovLoss));
    env->SetFloatField(s, Gist_qsExcCovOhId,
        (isNull ? 0.0 : qs->leafStats.excCovOh));
    env->SetFloatField(s, Gist_qsInternalUtilLossId,
        (isNull ? 0.0 : qs->internalStats.utilLoss));
    env->SetFloatField(s, Gist_qsInternalExcCovLossId,
        (isNull ? 0.0 : qs->internalStats.excCovLoss));
}


///////////////////////////////////////////////////////////////////////////////
// libGetSplitStats  -
//	return Java SplitStats for individual leaf or totals
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libGetSplitStats(
    JNIEnv* env,
    jclass cl,
    jint leafNo,
    jboolean weighted,
    jobject s)
{
    DBGPRINT(1, cout << "libGetSplitStats()" << endl);
    assert(Gist_analysis != NULL);
    amdb_splitstats::SplitStats* stats;
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;
    assert(target.splitStats != NULL);
    assert(target.map != NULL);

    amdb_splitstats::FullSplitStats fs;
    if (leafNo == 0) {
	// we want splitStats.avgStats
	fs = target.splitStats->avgStats;
    } else {
	// use find(), not operator[], the latter will create a NULL entry
	// if it can't find the entry
	stats = (amdb_splitstats::SplitStats *)
	    (*target.splitStats->splitStats.find(leafNo)).second;
	//assert(stats != NULL);
	if (stats == NULL) {
	    // don't have stats for this node
	    return;
	}
	fs.set(*stats, Gist_analysis->parameters.targetUtil, 
	    target.map->util(leafNo)); // compute display values
    }

    env->SetFloatField(s, Gist_ssPreIosId, fs.preIos(weighted));
    env->SetFloatField(s, Gist_ssOptIosId, fs.optIos(weighted));
    env->SetFloatField(s, Gist_ssActualIosId, fs.actualIos(weighted));
    env->SetFloatField(s, Gist_ssPreExcCovLossId, fs.preExcCovLoss);
    env->SetFloatField(s, Gist_ssActualExcCovLossId, fs.actualExcCovLoss);
    env->SetFloatField(s, Gist_ssOptClusterDeltaId,
        fs.optClusterDelta(weighted));
    env->SetFloatField(s, Gist_ssActualClusterDeltaId,
        fs.actualClusterDelta(weighted));
    env->SetFloatField(s, Gist_ssClusterLossId, fs.clusterLoss(weighted));
    env->SetFloatField(s, Gist_ssClusterOhId, fs.clusterOh(weighted));
    env->SetFloatField(s, Gist_ssClusterSuccessId, fs.clusterSuccess(weighted));
    env->SetFloatField(s, Gist_ssExcCovDeltaId, fs.excCovDelta());
    env->SetFloatField(s, Gist_ssExcCovLossId, fs.excCovLoss());
    env->SetFloatField(s, Gist_ssExcCovOhId, fs.excCovOh());
    env->SetFloatField(s, Gist_ssExcCovSuccessId, fs.excCovSuccess());

}


///////////////////////////////////////////////////////////////////////////////
// libGetPenaltyStats  -
//	return Java PenaltyStats for individual insertion or totals
//
// Description:
//	- try to parse key and return it
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libGetPenaltyStats(
    JNIEnv* env,
    jclass cl,
    jint keyNo,
    jboolean weighted,
    jobject s)
{
    DBGPRINT(1, cout << "libGetPenaltyStats()" << endl);
    assert(Gist_analysis != NULL);
    amdb_penaltystats::PenaltyStats* stats;
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;
    assert(target.splitStats != NULL); // we also need split stats
    assert(target.penaltyStats != NULL);
    assert(target.map != NULL);

    amdb_penaltystats::FullPenaltyStats fs;
    if (keyNo == 0) {
	// we want penaltyStats.avgStats
	fs = target.penaltyStats->avgStats;
    } else {
	stats = (amdb_penaltystats::PenaltyStats *)
	    target.penaltyStats->penaltyStats[keyNo];
	assert(stats != NULL);
	fs.set(*stats, Gist_analysis->parameters.targetUtil, 
	    *target.splitStats, *target.map); // compute display values
    }

    env->SetFloatField(s, Gist_psActualAddIosId, fs.actualAddIos(weighted));
    env->SetFloatField(s, Gist_psOptAddIosId, fs.optAddIos(weighted));
    env->SetFloatField(s, Gist_psActualExcCovId, fs.actualExcCovLoss);
    env->SetFloatField(s, Gist_psExcCovDeltaId, fs.excCovDelta());
    env->SetFloatField(s, Gist_psClusterLossId, fs.clusterLoss(weighted));
    env->SetFloatField(s, Gist_psExcCovOhId, fs.excCovOh());
    env->SetFloatField(s, Gist_psExcCovSuccessId, fs.excCovSuccess());

    if (keyNo > 0) {
        // extract the inserted key
	char buf[MAXCMDLEN];
	(void) memset(buf, 0, sizeof(buf));
	ostrstream os(buf, MAXCMDLEN);
	Gist_gist->extension()->printPred(os, *stats->key, 1);
	env->SetObjectField(s, Gist_psKeyId, env->NewStringUTF(buf));
	DBGPRINT(2, cout << "key: " << buf << endl);
    }

}


///////////////////////////////////////////////////////////////////////////////
// libGetSplitLeaves - return numbers of leaf pages recorded in splitStats
//
// Description:
//	- marks entry after last valid leaf no with 0
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libGetSplitLeaves(
    JNIEnv* env,
    jclass cl,
    jintArray leafNos)
{
    DBGPRINT(1, cout << "libGetSplitLeaves()" << endl);
    assert(Gist_analysis != NULL);
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;
    assert(target.splitStats != NULL);

    jsize leafNosSize = env->GetArrayLength(leafNos);
    // need extra entry to last leaf no
    assert(leafNosSize > target.splitStats->splitStats.size());
    jint* copy = env->GetIntArrayElements(leafNos, NULL);
    amdb_splitstats::SplitStatsMap::iterator it;
    int i;
    for (it = target.splitStats->splitStats.begin(), i = 0;
        it != target.splitStats->splitStats.end(); it++, i++) {

	copy[i] = (shpid_t) (*it).first;
    }
    copy[i] = 0; // i-1 is last valid leaf no
    env->ReleaseIntArrayElements(leafNos, copy, 0);
}


/*
 * Scripts
 */

static const int maxScript = 5;
static ifstream script[maxScript];


///////////////////////////////////////////////////////////////////////////////
// libOpenScript - open script file and assign it ID
//
// Description:
//	- returns index of first non-open stream
//
// Exceptions:
//	LibgistException
//
// Return Values:
//      script ID (integer)
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL
Java_Libgist_libOpenScript(
    JNIEnv* env,
    jclass cl,
    jstring filename)
{
    const char* fname = env->GetStringUTFChars(filename, NULL);
    DBGPRINT(1, cout << "libOpenScript() " << fname << endl);
    int scriptId;
    for (scriptId = 0; scriptId < maxScript; scriptId++) {
        if (!script[scriptId].is_open()) break; // found one
    }
    if (scriptId == maxScript) {
        ERRORRETURNV("out of script ids", 0);
    }
    script[scriptId].open(fname, ios::in);
    env->ReleaseStringUTFChars(filename, fname);
    if (!script[scriptId].good()) {
        ERRORRETURNV("couldn't open file", 0);
    }
    DBGPRINT(1, cout << "exit libOpenScript() " << scriptId << endl);
    return(scriptId);
}


///////////////////////////////////////////////////////////////////////////////
// getToken - read next token from input stream
//
// Description:
//	- skip initial whitespace
//	- token is either string (delimited by '"') or 
//	  non-string (non-ws characters)
//
// Return Values:
//	true if !eof()
///////////////////////////////////////////////////////////////////////////////

static bool
getToken(
    istream& s,
    char* val,
    bool& isString)
{
    s >> ws; // get rid of whitespace
    int i = 0;
    static bool wasSemicolon = false; // last char seen was \';\'
    if (s.eof()) {
        return(true);
    }

    s.get(val[i]);
    if (val[i] == '"') {
        isString = true;
        // parse a string (to next \'"\'), omit "
        do {
	    s.get(val[i]);
	    i++;
	} while (val[i-1] != '"' && !s.eof());
	val[i-1] = '\0';
    } else {
        isString = false;
        // parse a word/filename
        do {
	    i++;
	    s.get(val[i]);
	} while (!isspace(val[i]) && !s.eof());
	val[i] = '\0';
    }
    return(false);
}

static void
copyCharArray(
    jchar* to,
    char* from)
{
    int i = -1;
    do {
	i++;
	to[i] = from[i];
    } while (from[i] != '\0');
}


///////////////////////////////////////////////////////////////////////////////
// libGetCommand - parse single line of script and return command
//
// Description:
//
// Exceptions: LibgistException 
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL
Java_Libgist_libGetCommand(
    JNIEnv* env,
    jclass cl,
    jint scriptId,
    jobject cmd)
{
    DBGPRINT(1, cout << "libGetCommand() " << scriptId << endl);

    // return values
    enum OpCodes {
        fileError = -3,
        parseError,
        endOfScript,
        insertOp,
	removeOp,
	fetchOp,
	createOp,
	openOp,
	closeOp,
	flushOp,
	openAnlOp,
	closeAnlOp,
	createAnlOp,
	wkldStatsOp,
	splitStatsOp,
	penaltyStatsOp
    };

    if (!script[scriptId].is_open()) {
        cout << "no script opened" << endl;
        return(endOfScript);
    }

    char tokenval[MAXCMDLEN];
    char line[MAXCMDLEN];
    char stmt[MAXCMDLEN];
    char table[MAXCMDLEN];
    char errormsg[MAXCMDLEN];
    bool isString;
    OpCodes opCode;

    for (;;) {
        script[scriptId].getline(line, MAXCMDLEN);
	if (script[scriptId].eof()) {
	    // done with script
	    script[scriptId].close();
	    cout << "EOF" << endl;
	    return(endOfScript);
	}
	if (script[scriptId].fail()) {
	    ERRORRETURNV("file error", fileError);
	}
	//cout << line << endl;
	istrstream s(line);
	s >> ws;
	if (s.eof()) {
	    continue; // skip blank lines
	}

	(void) getToken(s, stmt, isString);
	(void) getToken(s, table, isString); // mostly ignored
	if (strcmp(stmt, "select") == 0) {
	    opCode = fetchOp;
	    // parse 'select [limit] "<qual>"'
	    (void) getToken(s, tokenval, isString);
	    //cout << "select " << tokenval;
	    if (!isString) {
	        // must be the fetch limit; set cmd.fetchLimit
		env->SetIntField(cmd, Gist_lcFetchLimitId, atoi(tokenval));
		(void) getToken(s, tokenval, isString);
		//cout << " " << tokenval;
	    }
	    // set cmd.qual
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcQualId),
	        tokenval);
	    //cout << endl;
	    break;

	} else if (strcmp(stmt, "open") == 0) {
	    opCode = openOp;
	    // parse 'open <indexname>', 'table' contains the index name
	    // set cmd.indexName
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcIndexNameId),
	        table);
	    //cout << "open " << tokenval << endl;
	    break;

	} else if (strcmp(stmt, "insert") == 0) {
	    opCode = insertOp;
	    // parse 'insert "<key>" "<data>"
	    (void) getToken(s, tokenval, isString);
	    if (!isString) {
		sprintf(errormsg, "key %s is missing quotes", tokenval);
	        ERRORRETURNV(errormsg, parseError);
	    }
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcKeyId),
	        tokenval);
	    (void) getToken(s, tokenval, isString);
	    if (!isString) {
		sprintf(errormsg, "data %s is missing quotes", tokenval);
	        ERRORRETURNV(errormsg, parseError);
	    }
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcDataId),
	        tokenval);
	    break;

	} else if (strcmp(stmt, "delete") == 0) {
	    opCode = removeOp;
	    (void) getToken(s, tokenval, isString);
	    //cout << "delete " << tokenval;
	    if (!isString) {
		sprintf(errormsg, "qual %s is missing quotes", tokenval);
	        ERRORRETURNV(errormsg, parseError);
	    }
	    // set cmd.qual
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcQualId),
	        tokenval);
	    //cout << endl;
	    break;

	} else if (strcmp(stmt, "close") == 0) {
	    opCode = closeOp;
	    // parse 'close'
	    break;

	} else if (strcmp(stmt, "create") == 0) {
	    opCode = createOp;
	    // parse 'create <indexname> <extname>', 'table' contains the index name
	    // set cmd.indexName
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcIndexNameId),
	        table);
	    (void) getToken(s, tokenval, isString);
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcExtensionId),
	        table);
	    //cout << "open " << tokenval << endl;
	    break;

	} else if (strcmp(stmt, "flush") == 0) {
	    opCode = flushOp;
	    // parse 'flush'
	    break;

	} else if (strcmp(stmt, "openanl") == 0) {
	    opCode = openAnlOp;
	    // parse 'openanl <analysisname>', 'table' contains analysisname
	    // set cmd.analysisName
	    env->SetObjectField(cmd, Gist_lcAnalysisFileId,
	        env->NewObject(Gist_fileClass, Gist_fInitId, env->NewStringUTF(table)));
	    //cout << "open " << tokenval << endl;
	    break;

	} else if (strcmp(stmt, "closeanl") == 0) {
	    opCode = closeAnlOp;
	    // parse 'closeanl'
	    break;

	} else if (strcmp(stmt, "createanl") == 0) {
	    opCode = createAnlOp;
	    // parse 'createanl <analysisname> <indexname> <script> <#random> <fill-factor>'
	    // 'table' contains analysisname
	    env->SetObjectField(cmd, Gist_lcAnalysisFileId,
	        env->NewObject(Gist_fileClass, Gist_fInitId, env->NewStringUTF(table)));
	    (void) getToken(s, tokenval, isString);
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcIndexNameId),
	        tokenval);
	    (void) getToken(s, tokenval, isString);
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcScriptFileId),
	        tokenval);
	    (void) getToken(s, tokenval, isString);
	    env->SetIntField(cmd, Gist_lcNumRandomRunsId, atoi(tokenval));
	    (void) getToken(s, tokenval, isString);
	    env->SetFloatField(cmd, Gist_lcFillFactorId, atof(tokenval));
	    break;

	} else if (strcmp(stmt, "wkldstats") == 0) {
	    opCode = wkldStatsOp;
	    // parse 'wkldstats'
	    break;

	} else if (strcmp(stmt, "splitstats") == 0) {
	    opCode = splitStatsOp;
	    break;

	} else if (strcmp(stmt, "penaltystats") == 0) {
	    opCode = penaltyStatsOp;
	    // parse 'penaltystats <key-file>', 'table' contains key-file
	    stringBufferAppend(env, env->GetObjectField(cmd, Gist_lcLoadFileId),
	        tokenval);
	    break;

	} else {
	    // didn't recognize that command
	    sprintf(errormsg, "command %s not recognized", stmt);
	    ERRORRETURNV(errormsg, parseError);
	}
    }

    env->SetIntField(cmd, Gist_lcCmdTypeId, opCode);
    DBGPRINT(1, cout << "exit libGetCommand() " << opCode << endl);
    return(opCode);
}

static void
stringBufferAppend(
    JNIEnv* env,
    jobject buf,
    const char* str)
{
    jstring s = env->NewStringUTF(str);
    jobject dummy = env->CallObjectMethod(buf, Gist_sbAppendId, s);
}




///////////////////////////////////////////////////////////////////////////////
// libGetPredInfo - wrapper for gist::getPredInfo
//
// Description: loads predicate info into internal array
//
// Exceptions:
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libGetPredInfo(
    JNIEnv* env,
    jclass cl,
    jint root,
    jint levels)
{
    DBGPRINT(1, cout << "libGetPredInfo()" << endl);
    assert(Gist_gist != NULL);

    Gist_numPredInfoColors = 1; // gist::getPredInfo() presets 'color' to 0
    for (;;) {
	Gist_numPredInfo = Gist_predInfoSize;
	rc_t status = Gist_gist->getPredInfo(root, levels, Gist_predInfo, Gist_numPredInfo);
	DBGPRINT(2, cout << "status: " << status << endl);
	if (status == eARRAYSIZE) {
	    // Gist_predInfo is too small, double it
	    if (Gist_predInfoSize == 0) {
	        Gist_predInfoSize = 1000;
	    } else {
	        Gist_predInfoSize *= 2;
	    }
	    DBGPRINT(3, cout << "predInfoSize: " << Gist_predInfoSize << endl);
	    delete [] Gist_predInfo;
	    Gist_predInfo = new gist::DisplayPredInfo[Gist_predInfoSize] ;
	} else {
	    // got everything, we're done
	    DBGPRINT(2, cout << "numPredInfo: " << Gist_numPredInfo << endl);
	    return;
	}
    }
}



///////////////////////////////////////////////////////////////////////////////
// predInfoColorCmp - compare gist::DisplayPredInfo.color
//
// Description:
//	- used for qsort()
//
///////////////////////////////////////////////////////////////////////////////

static int 
predInfoColorCmp(
    const void* a,
    const void* b)
{
    const gist::DisplayPredInfo* l = (gist::DisplayPredInfo*) a;
    const gist::DisplayPredInfo* r = (gist::DisplayPredInfo*) b;
    return ((l->color < r->color) ? -1 : ((l->color > r->color) ? 1 : 0));
}


///////////////////////////////////////////////////////////////////////////////
// libDisplayPreds - wrapper for gist::displayPreds()
//
// Description:
//	- sorts Gist_predInfo[] by color and displays it
//	- sorting is done so that displayPreds() can display highlighted 
//	  entries after the non-highlighted ones, otherwise the highlighted 
//	  ones might get obscured
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libDisplayPreds(
    JNIEnv* env, // in
    jclass cl, // in
    jobject graphicsContext, // in: java.awt.Graphics
    jint width, // in: width of canvas
    jint height, // in: height of canvas
    jobjectArray col) // in: array of java.awt.colors
{
    DBGPRINT(1, cout << "libDisplayPreds()" << endl);
    assert(Gist_gist != NULL);
    jobject* colors = NULL; // to hold 'col' Java array

    if (Gist_numPredInfo == 0) {
        // nothing to display
	return;
    }

    // extract colors
    DBGPRINT(2, cout << "extract colors" << endl);
    jsize colSize = env->GetArrayLength(col);
    colors = new jobject[colSize];
    assert(colors != NULL);
    int i;
    for (i = 0; i < colSize; i++) {
        colors[i] = env->GetObjectArrayElement(col, i);
    }

    // sort predInfo, if needed
    if (Gist_numPredInfoColors > 1) {
	qsort(Gist_predInfo, Gist_numPredInfo, sizeof(gist::DisplayPredInfo),
	    predInfoColorCmp);
    }

    DBGPRINT(2, cout << "call displayPreds()" << endl);
    assert(Gist_predInfo != NULL);
    rc_t status = Gist_gist->displayPreds(env, width, height, graphicsContext,
        colors, Gist_predInfo, Gist_numPredInfo);
    CHECKSTATUS(status, env, "gist::displayPreds() failed");

    delete [] colors;
}

JNIEXPORT jint JNICALL
Java_Libgist_libGetNumInsertions(
    JNIEnv* env,
    jclass cl)
{
    DBGPRINT(1, cout << "libGetNumInsertions()" << endl);
    assert(Gist_analysis != NULL);
    amdb_analysis::TreeAnalysis& target = Gist_analysis->actualAnalysis;
    assert(target.penaltyStats != NULL);

    return(target.penaltyStats->penaltyStats.size());
}

JNIEXPORT void JNICALL
Java_Libgist_libSetDbgLevel(
    JNIEnv* env,
    jclass cl,
    jint dbgLevel)
{
    DBGPRINT(1, cout << "libSetDbgLevel()" << endl);
    Gist_dbgLevel = dbgLevel;
}


///////////////////////////////////////////////////////////////////////////////
// _highlightChildSubtree - highlight children of subtree root in predInfo arr.
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

static void
_highlightChildSubtrees(
    int parent,	// in: root of subtree
    int levels,	// in: remaining number of levels to traverse
    int& index, // in/out: running index in Gist_predInfo
    int color)	// in: highlight color index
{
    while (index < Gist_numPredInfo &&
        Gist_predInfo[index].parent == parent) {

	// mark entries in direct descendents
	while (index < Gist_numPredInfo &&
	    Gist_predInfo[index].parent == parent) {

	    Gist_predInfo[index].color = color;
	    index++;
	}

	if (levels > 1 || levels <= 0) {
	    // mark entries in the descendent's subtree;
	    // first, determine the current descendent
	    int node = Gist_predInfo[index - 1].node;
	    _highlightChildSubtrees(node, levels - 1, index, color);
	}

	// done with the subtree of the previous descendent of 'parent',
	// now on to the next descendent (if there are any left, i.e., if
	// predInfo[index].parent is still 'parent')
    }
}


///////////////////////////////////////////////////////////////////////////////
// libHighlighSubtree - highlight subtree of node in predInfo array
//
// Description:
//	- set color index of all predicates in subtree (leaf and internal)
//	  to highlight color; include subtree pred of subtree root
//
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libHighlightSubtree(
    JNIEnv* env,
    jclass cl,
    jint root,
    jint levels,
    jint color)
{
    DBGPRINT(1, cout << "libHighlightSubtree()" << endl);
    int index = 0;

    Gist_numPredInfoColors = 2; // we're introducing a 2nd color

    if (root != Java_Libgist_libGetRoot(env, cl)) {
	// locate SP of subtree root
	int parent = Java_Libgist_libGetParent(env, cl, root);
	int parentPos = Java_Libgist_libGetParentPos(env, cl, root);
	if (parentPos == -1) {
	    // there was some error;
	    // the exception has already been set up, return now
	    return;
	}

	// scan until we hit root's SP entry
	while (index < Gist_numPredInfo && !(Gist_predInfo[index].node == parent &&
	    Gist_predInfo[index].slot == parentPos)) {

	    index++;
	}
	// mark parent SP highlighted
	if (index < Gist_numPredInfo && Gist_predInfo[index].node == parent &&
	    Gist_predInfo[index].slot == parentPos) {

	    Gist_predInfo[index].color = color;
	}
    }

    // scan until we hit the first entry for the subtree root
    while (index < Gist_numPredInfo && Gist_predInfo[index].node != root) {
        index++;
    }
    // mark all entries in subtree root
    while (index < Gist_numPredInfo && Gist_predInfo[index].node == root) {
	Gist_predInfo[index].color = color;
        index++;
    }

    // now highlight the child nodes
    if (levels > 1 || levels == 0) {
        _highlightChildSubtrees(root, levels - 1, index, color);
    }
}

JNIEXPORT void JNICALL
Java_Libgist_libHighlightSplit(
    JNIEnv* env,
    jclass cl,
    jintArray rightEntries,
    jint numRight,
    jint color)
{
    DBGPRINT(1, cout << "libHighlightSplit(numRight = " << numRight
        << ")" << endl);
    int i, j = 0;
    jsize len = env->GetArrayLength(rightEntries);
    assert(len >= numRight);
    jint* copy = env->GetIntArrayElements(rightEntries, NULL);

    Gist_numPredInfoColors = 2; // we're introducing a 2nd color

    // make sure that rightEntries is sorted in ascending order
    qsort(copy, numRight, sizeof(jint), jintCmp);
    for (i = 0; i < Gist_numPredInfo; i++) {
        if (Gist_predInfo[i].slot == copy[j]) {
	    // found a slot that's in rightEntries, now mark it
	    Gist_predInfo[i].color = color;
	    j++; // done with this rightEntry
	} 
    }
    DBGPRINT(2, cout << "marked " << j << " entries" << endl);
    env->ReleaseIntArrayElements(rightEntries, copy, 0);
}


///////////////////////////////////////////////////////////////////////////////
// libHighlightPath - highlight all SPs on a path
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL
Java_Libgist_libHighlightPath(
    JNIEnv* env,
    jclass cl,
    jint topNode,
    jint bottomNode,
    jint color)
{
    DBGPRINT(1, cout << "libHighlightPath()" << endl);

    if (bottomNode == topNode ||
        bottomNode == Java_Libgist_libGetRoot(env, cl)) {

        // there is no path, we're done
	return;
    }

    // determine the path from root to bottomNode
    int parentPos = Java_Libgist_libGetParentPos(env, cl, bottomNode);
    if (parentPos == -1) {
	// there was some error;
	// the exception has already been set up, return now
	return;
    }
    int parent = Java_Libgist_libGetParent(env, cl, bottomNode);
    DBGPRINT(2, cout << "parent: " << parent << " pos: " << parentPos << endl);

    Gist_numPredInfoColors = 2; // we're introducing a 2nd color

    int i = Gist_numPredInfo; // index into predInfo
    while (i >= 0) {
	i--;
        if (Gist_predInfo[i].node == parent && 
	    Gist_predInfo[i].slot == parentPos) {

	    // we're looking at an SP on the path, highlight it
	    Gist_predInfo[i].color = color;

	    if (parent == topNode) {
	        // we arrived at the topmost node, we're done
		return;
	    }

	    // determine coords of the next SP
	    parentPos = Java_Libgist_libGetParentPos(env, cl, parent);
	    if (parentPos == -1) {
		// there was some error;
		// the exception has already been set up, return now
		return;
	    }
	    parent = Java_Libgist_libGetParent(env, cl, parent);
	}
    }

}

}

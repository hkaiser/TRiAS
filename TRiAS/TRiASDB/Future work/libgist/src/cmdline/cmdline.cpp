// cmdline.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: cmdline.cc,v 1.15 2000/03/15 00:23:48 mashah Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786)

#include <fstream>
#include <iostream>
#include <strstream>

using namespace std;
#else
#include <fstream.h>
#include <iostream.h>
#include <strstream.h>
#endif
// VCPORT_E

#include "gist.h"
#include "gist_extensions.h"
#include "gist_defs.h"
#include "gist_compat.h"
#include "gist_cursor.h"
#include "gist_cursorext.h"
#include "gist_btree.h"
#include "gist_rtree.h"
#include "gist_rstartree.h"
#include "gist_nptree.h"
#include "gist_rrtree.h"
#include "gist_sptree.h"
#include "gist_sstree.h"
#include "gist_srtree.h"
#include "gist_rtreecext.h"
#include "cmdline.h"
#include "cmdline_help.h"	// generated at compile-time
#include "cmdline_ts.h"		// generated at compile-time

#ifdef AMDB
#include "amdb_defs.h"
#include "amdb_analysis.h"
#include "amdb_wkldprofile.h"
#include "amdb_treemap.h"
#include "amdb_breakpoints.h"
#include "amdb_idxstruct.h"
#endif

extern int yyparse();

#define NOT_FOUND (-1)
static const int MAXLINE = 8192;

static const int MAXIDX = sizeof(_gist_exts)/sizeof(gist_ext_t*);

static gist_cursorext_t* gist_cexts[] = {
    &stack_cext,
    &rt_point_nn_cext,
    &rt_rect_nn_cext,
    &rr_point_nn_cext,
    &sp_point_nn_cext,
    &ss_point_nn_cext,
    &sr_point_nn_cext,
};

struct Table {
    char* name;
    gist* index;
#ifdef AMDB
    amdb_idxstruct* strct;
#endif
};
static Table tables[MAXIDX];
static int numTables = 0;
static bool echoOutput = true; // true: echos inserted/retrieved keys
static bool noPrompt = false; // true: don't print prompt (simplifies tests)

#ifdef AMDB
struct Analysis {
    char* name;
    amdb_analysis* analysis;
};
static Analysis analyses[MAXIDX];
static int numAnalyses = 0;
#endif


// forward declarations

static rc_t runQuery(gist& index, const gist_query_t* query, 
    int k, int io, int& numRetrieved);
static void printDatum(void* key, int klen, void* data, int dlen,
    gist_ext_t* ext);
static rc_t closeTable(int idx);
static void closeAnalysis(int idx);
static int getTable(const char* name);
static int getAnalysis(const char* name);
static gist_ext_t* getExtension(const char* extname);
static rc_t scanString(istream& s, char* str);
static rc_t scanTup(void* key, int& klen, void* data, int& dlen,
    shpid_t& child, void* param);


static rc_t
runQuery(
    gist& 	index,
    const 	gist_query_t* query, // in: query to run
    int 	k, // in: max. number of tuples to retrieve
    int 	io, // in: max. number of page accesses
    int& 	numRetrieved) // out: number of retrieved tuples
{
    gist_cursor_t cursor;
    if (index.fetch_init(cursor, query, k, io) != RCOK) {
	cout << "can't initialize cursor" << endl;
	return(eERROR);
    }
    gist_ext_t* ext = index.extension();

    bool eof = false;
    char key[gist_p::max_tup_sz];
    smsize_t klen;
    char data[gist_p::max_tup_sz];
    smsize_t dlen;
    int cnt = 0;
    for (;;) {
	klen = gist_p::max_tup_sz;
	dlen = gist_p::max_tup_sz;
	if (index.fetch(cursor, (void *) key, klen, (void *) data, dlen, eof) != RCOK) {
	    cerr << "can't fetch from cursor" << endl;
	    return(eERROR);
	}
	if (eof) break;
	// print key and data
	if (echoOutput) {
	    printDatum(key, klen, data, dlen, ext);
	    cout << endl;
	}
	cnt++;
    }
    numRetrieved = cnt;
    return(RCOK);
}

static void
printDatum(
    void* 	key,
    int 	klen,
    void* 	data,
    int 	dlen,
    gist_ext_t* ext)
{
    vec_t keyv(key, klen);
    vec_t datav(data, dlen);
    ext->printPred(cout, keyv, 1);
    cout << ": ";
    ext->printData(cout, datav);
}

static rc_t
closeTable(
    int 	idx)
{
#ifdef AMDB
    delete tables[idx].strct;
    tables[idx].strct = NULL;
#endif

    free(tables[idx].name);
    rc_t status = tables[idx].index->close();
    delete tables[idx].index;
    tables[idx].index = NULL;

    for ( ; idx < numTables-1; idx++) {
	tables[idx] = tables[idx+1];
    }
    numTables--;
    
    return(status);
}


static void
closeAnalysis(
    int 	idx)
{
#ifdef AMDB
    free(analyses[idx].name);
    delete analyses[idx].analysis;
    analyses[idx].analysis = NULL;

    for ( ; idx < numAnalyses-1; idx++) {
	analyses[idx] = analyses[idx+1];
    }
    numAnalyses--;
#endif
}

static int
getTable(
    const char* 	name)
{
    int i;
    for (i = 0; i < numTables; i++) {
	if (strcmp(tables[i].name, name) == 0) break; 
    }
    return (i == numTables ? NOT_FOUND : i);
}

static int
getAnalysis(
    const char* 	name)
{
#ifdef AMDB
    int i;
    for (i = 0; i < numAnalyses; i++) {
	if (strcmp(analyses[i].name, name) == 0) break; 
    }
    return (i == numAnalyses ? NOT_FOUND : i);
#endif
}

static gist_ext_t*
getExtension(
    const char* 	extname)
{
    int i;
    for (i = 0; i < gist_ext_t::gist_numext; i++) {
        if (strcmp(extname, gist_ext_t::gist_ext_list[i]->myName) == 0) break;
    }
    return (i == gist_ext_t::gist_numext ? (gist_ext_t *) NULL : gist_ext_t::gist_ext_list[i]);
}

struct TupStreamParam {
    int idx; // into gist table
    istream& s; // read tuples from there
    TupStreamParam(int idx, istream&s) : idx(idx), s(s) {}
};

static rc_t
scanString(
    istream& 	s, // in: input stream
    char* 	str) // out: string stripped off '"'s
{
    char ch;
    s >> ws; // discard whitespace
    s >> ch;
    if (ch != '"') return(ePARSEERROR);
    int i = 0;
    do {
	s.get(ch);
	str[i] = ch;
	i++;
    } while (!s.eof() && ch != '"');
    if (s.eof()) return(ePARSEERROR); // key isn't terminated
    assert(ch == '"');
    str[i-1] = '\0'; // replace terminating double quote
    if (i == 1) return(ePARSEERROR); // no key specified
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// scanTup - scan single line in load file
//
// Description:
//	- line format: "<key>" "<data"\n
//
// Preconditions:
//	- ext->printPred/-Data must not be NULL
//
// Return Values:
//      RCOK
//	eEOF
//	eFILEERROR
//	ePAGEBREAK
/////////////////////////////////////////////////////////////////////////

static rc_t
scanTup(
    void* 	key,
    int& 	klen,
    void* 	data,
    int& 	dlen,
    shpid_t&	child,
    void* 	param)
{
    static int itemCnt = 0;

    TupStreamParam* p = (TupStreamParam *) param;
    char line[MAXLINE];
    p->s.getline(line, MAXLINE);
    if (p->s.eof()) {
	// we're done with this load file
	cout << "read " << itemCnt << " items" << endl;
	itemCnt = 0; // reset for next bulk load
        return eEOF;
    }
    if (p->s.fail()) return eFILEERROR;
    if (strlen(line) == 0) {
        // we read a page break marker (empty line)
	klen = dlen = 0;
	if (echoOutput) {
	    cout << "BREAK" << endl;
	}
	return ePAGEBREAK;
    }

    istrstream s(line); // scan input line for "<key>" "<data>"
//    char ch;
    char keystr[MAXLINE];
    W_DO(scanString(s, keystr));
    char datastr[MAXLINE];
    W_DO(scanString(s, datastr));

    // now, convert key and data strings
    gist *index = tables[p->idx].index;
    gist_ext_t* ext = tables[p->idx].index->extension();
    if (ext->parsePred(keystr, key, klen) != RCOK) {
        cout << "can't parse key " << keystr << endl;
	return ePARSEERROR;
    }
    if (ext->parseData(datastr, data, dlen) != RCOK) {
        cout << "can't parse data " << datastr << endl;
	return ePARSEERROR;
    }
    if (echoOutput) {
	printDatum(key, klen, data, dlen, ext);
	cout << endl;
    }
    child = 0;
    itemCnt++;
    return RCOK;
}


///////////////////////////////////////////////////////////////////////////////
// cmdCreate - call gist::create()
//
// Description:
//	- records new index in tables[]
///////////////////////////////////////////////////////////////////////////////

void
cmdCreate(
    const char* 	table,
    const char* 	extname)
{
    if (numTables == MAXIDX) { 
	cout << "Capacity exceeded (" << MAXIDX << ")" << endl;
	return; 
    }

    gist_ext_t* ext = getExtension(extname);
    if (ext == NULL) {
        cout << "Extension not recognized\n";
	return;
    }

    gist *index = new gist();

    rc_t status = index->create(table, ext);
    index->flush();
    if (status != RCOK) {
	cout << "Error creating table." << endl;
	delete index;
	return;
    }

    tables[numTables].name = strdup(table);
    tables[numTables].index = index;
    numTables++;
}


///////////////////////////////////////////////////////////////////////////////
// cmdLoad - call gist::create() to bulk-load index
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdLoad(
    const char* 	table,
    const char* 	extname,
    const char* 	filename,
    float 		fillFactor)
{
    if (numTables == MAXIDX) { 
	cout << "Capacity exceeded (" << MAXIDX << ")" << endl;
	return; 
    }

    gist_ext_t* ext = getExtension(extname);
    if (ext == NULL) {
        cout << "Extension not recognized\n";
	return;
    }

    // check if we have the required parsing functions
    if (ext->parsePred == NULL) {
        cout << "Extension can't parse predicates." << endl;
	return;
    }
    if (ext->parseData == NULL) {
        cout << "Extension can't parse data." << endl;
	return;
    }

    ifstream s(filename);
    if (s.fail()) {
        cout << "Error opening data file." << endl;
	return;
    }

    gist *index = new gist();

    tables[numTables].name = strdup(table);
    tables[numTables].index = index;
    numTables++;

    TupStreamParam param(numTables-1, s);
    rc_t status = index->create(table, ext, scanTup, (void *) &param, fillFactor);
    s.close();
    index->flush();

    if (status != RCOK) {
	cout << "Error loading table." << endl;
	delete index;
	return;
    }

}


///////////////////////////////////////////////////////////////////////////////
// cmdWriteLoadFile - call gist::writeLoadFile
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdWriteLoadfile(
    const char* 	table,
    const char* 	filename)
{
#ifdef AMDB
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
        cerr << "Table not open" << endl;
	return;
    }

    ofstream s(filename);
    if (s.fail()) {
        cout << "Error opening file." << endl;
	return;
    }

    if (tables[i].index->writeLoadfile(s) != RCOK) {
        cout << "Error writing load file." << endl;
    }

    s.close();
#endif
}


///////////////////////////////////////////////////////////////////////////////
// cmdOpen - call gist::open()
//
// Description:
// 	- record index in tables[]
///////////////////////////////////////////////////////////////////////////////

void
cmdOpen(
    const char* 	table)
{
    if (numTables == MAXIDX) { 
	cout << "Capacity exceeded (" << MAXIDX << ")" << endl;
	return; 
    }

    if (getTable(table) != NOT_FOUND) {
	cout << "Index already open" << endl;
	return;
    }

    gist *index = new gist();

    rc_t status = index->open(table);

    if (status != RCOK) {
	delete index;
	cout << "Error opening index." << endl;
	return;
    }

    tables[numTables].index = index;
    tables[numTables].name = strdup(table);
    numTables++;
}


///////////////////////////////////////////////////////////////////////////////
// cmdClose - call gist::close
//
// Description:
//      - remove index from tables[]
///////////////////////////////////////////////////////////////////////////////

void
cmdClose(
    const char* 	table)
{
    int i;

    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    if (closeTable(i) != RCOK) {
        cout << "can't close" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
// cmdCheck - call gist::check()
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdCheck(
    const char* 	table)
{
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    gist *index = tables[i].index;
    if (index->check() != RCOK) {
        cout << "can't check" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
// cmdSelect - call gist::fetch()
//
// Description:
// 	- select max of k tuples with given query
//
///////////////////////////////////////////////////////////////////////////////

void
cmdSelect(
    const char* 	table,
    const char* 	qstr,
    int 		k,
    int 		io)
{
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    gist* index = tables[i].index;
    gist_ext_t* ext = tables[i].index->extension();
    // make sure extension can parse queries
    if (ext->parseQuery == NULL) {
        cout << "Extension can't parse queries." << endl;
	return;
    }

    gist_query_t* query;
    rc_t status = ext->parseQuery(qstr, query);
    if (status != RCOK) {
        cout << "Error parsing qualification" << endl;
	return;
    }

    int numRetrieved;
    if (runQuery(*index, query, k, io, numRetrieved) != RCOK) {
        return;
    }
    cout << "retrieved " << numRetrieved << " items" << endl;
    delete query;
}


///////////////////////////////////////////////////////////////////////////////
// cmdInsert - call gist::insert
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
cmdInsert(
    const char* 	table,
    const char* 	kstr,
    const char* 	dstr)
{
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    gist *index = tables[i].index;
    gist_ext_t* ext = tables[i].index->extension();
    // make sure extension can parse predicates and data
    if (ext->parsePred == NULL) {
        cout << "Extension can't parse predicates." << endl;
	return;
    }
    if (ext->parseData == NULL) {
        cout << "Extension can't parse data." << endl;
	return;
    }

    char key[gist_p::max_tup_sz];
    int klen;
    char data[gist_p::max_tup_sz];
    int dlen;
    if (ext->parsePred(kstr, key, klen) != RCOK) {
        cout << "can't parse key" << endl;
	return;
    }
    if (ext->parseData(dstr, data, dlen) != RCOK) {
        cout << "can't parse data" << endl;
	return;
    }
    if (echoOutput) { 
	printDatum(key, klen, data, dlen, ext);
	cout << endl;
    }
    if (index->insert(key, klen, data, dlen) != RCOK) {
	cout << "can't insert" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
// cmdDelete - call gist::delete
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
cmdDelete(
    const char* 	table,
    const char* 	qstr)
{
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    gist *index = tables[i].index;
    gist_ext_t* ext = tables[i].index->extension();
    // make sure extension can parse queries
    if (ext->parseQuery == NULL) {
        cout << "Extension can't parse queries." << endl;
	return;
    }

    gist_cursor_t cursor;

    gist_query_t* query;
    rc_t status = ext->parseQuery(qstr, query);

    if (tables[i].index->remove(query) != RCOK) {
        cout << "can't delete" << endl;
    }

    delete query;
}


///////////////////////////////////////////////////////////////////////////////
// cmdQuit - close tables and analysis and exit
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdQuit()
{
    while (numTables > 0) {
	(void) closeTable(0);
    }
#ifdef AMDB
    while (numAnalyses > 0) {
	closeAnalysis(0);
    }
#endif
    cout << "Goodbye." << endl;
    exit(0);
}


///////////////////////////////////////////////////////////////////////////////
// cmdDump - call gist::dump
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdDump(
    const char* 	table,
    shpid_t 		pgno)
{
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    if (tables[i].index->dump(cout, pgno) != RCOK) {
        cerr << "can't dump" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
// cmdSplit - call gist::split
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdSplit(
    const char* 	table,
    shpid_t 		pgno)
{
#ifdef AMDB
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
	cout << "Index not opened" << endl;
	return;
    }

    int splitEntries[gist_p::max_scnt];
    int numSplit;
    gist::AlignedPred x, y;
    vec_t leftBp(x.pred, gist_p::max_tup_sz);
    vec_t rightBp(x.pred, gist_p::max_tup_sz);
    rc_t status = tables[i].index->pickSplit(pgno, splitEntries, numSplit, leftBp, rightBp);
    if (status != RCOK) {
        cout << "Can't split page " << pgno << endl;
	return;
    }
    cout << "Entries for right sibling (" << numSplit << ") :" << endl;
    if (numSplit > 0) {
        cout << splitEntries[0];
	for (i = 1; i < numSplit; i++) {
	    cout << ", " << splitEntries[i];
	}
	cout << endl;
    }
#endif
}

void
cmdSetEcho(
    int 	state)
{
    echoOutput = (state == 1);
}

#ifdef AMDB
// hack: index of last 'table' that had its amdb_idxstruct enabled
static int structIdx;


///////////////////////////////////////////////////////////////////////////////
// breakHandler - amdb break handler
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

static bool
breakHandler(
    amdb_breakpoints::BreakInfo* 	info)
{
    // see if event signals a structure change
    if (!amdb_breakpoints::isStructureUpdate(info->event)) {
	return false;
    }
    amdb_idxstruct* strct = tables[structIdx].strct;
    switch (info->event) { 
	case amdb_breakpoints::newNodeEvent: {
	    strct->splitNode(info->param.newNodeParam.origNode,
		info->param.newNodeParam.rightSib,
		info->param.newNodeParam.rightChildren);
	    break;
	}
	case amdb_breakpoints::newRootEvent: {
	    strct->splitRoot(info->param.newRootParam.leftNode,
		info->param.newRootParam.rightNode,
		info->param.newRootParam.rightChildren);
	    break;
	}
	case amdb_breakpoints::relocateChildEvent: {
	    strct->relocateChild(info->param.relocateChildParam.child,
		info->param.relocateChildParam.oldParent,
		info->param.relocateChildParam.newParent);
	    break;
	}
	case amdb_breakpoints::itemInsertedEvent:
	case amdb_breakpoints::itemDeletedEvent:
	case amdb_breakpoints::bpUpdatedEvent: {
	    strct->updateNode(info->param.updNodeParam);
	    break;
	}
	default: 
	    assert(0);
    }
    return false;
}
#endif


///////////////////////////////////////////////////////////////////////////////
// cmdSetStruct - creates amdb_idxstruct
//
// Description:
///////////////////////////////////////////////////////////////////////////////

void
cmdSetStruct(
    const char* 	table,
    int 		state)
{
#ifdef AMDB
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
        cerr << "Table not open" << endl;
	return;
    }

    gist* index = tables[i].index;
    if (state != 0) {
	if (tables[i].strct == NULL) {
	    tables[i].strct = new amdb_idxstruct(index);
	} else {
	    delete tables[i].strct;
	    tables[i].strct = new amdb_idxstruct(index);
	}
	index->setBreakHandler(breakHandler);
	structIdx = i;
    } else {
	index->setBreakHandler(NULL);
    }
#endif
}


///////////////////////////////////////////////////////////////////////////////
// cmdCreateAnl - run queries and create amdb_analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
cmdCreateAnl(
    const char* 	analysisname,
    const char* 	indexname,
    const char* 	scriptfile,
    int 		numRandomRuns,
    float 		targetUtil)
{
#ifdef AMDB
    // make sure we don't overflow analyses[]
    if (numAnalyses == MAXIDX) { 
	cout << "Capacity exceeded (" << MAXIDX << ")" << endl;
	return; 
    }

    // open index and create empty amdb_wkldprofile
    gist* index = new gist();
    if (index->open(indexname) != RCOK) {
        cerr << "Can't open index " << indexname << endl;
	return;
    }

    // need a tree map for profiling
    amdb_treemap* map = new amdb_treemap();
    index->computeTreeMap(map);

    // create profile
    amdb_wkldprofile* profile = new amdb_wkldprofile();
    profile->setTreeMap(map);
    index->setProfilingEnabled(profile);

    // make sure we can parse queries
    gist_ext_t* ext = index->extension();
    if (ext->parseQuery == NULL) {
        cerr << "Extension of " << indexname << " can't parse queries" << endl;
	return;
    }

    // scan scriptfile and run queries
    ifstream s(scriptfile);
    if (s.fail()) {
        cout << "Error opening " << scriptfile << endl;
        return;
    }
    char buf[1024];
	char *b;
	int maxR = 0;
    while (s.getline(buf, sizeof(buf))) {

		b = buf;

		// if buf starts with maxR then its a nearest neighbor query ...
		if (strncmp("maxR:",b,5) == 0) {
			char *tmp;
			b += 5;
			maxR = strtol(b, &tmp, 0);
			b = tmp;
		}

        gist_query_t* query;
        rc_t status = ext->parseQuery(b, query);
        if (status != RCOK) {
            cout << "Error parsing qualification (" << b << ")" << endl;
            return;
        }

	// run query
	int dummyInt;
	if (runQuery(*index, query, maxR, 0, dummyInt) != RCOK) {
	    return;
	}

	delete query;
    }
    s.close();
    delete index;
    delete map;

    amdb_analysis* analysis = new amdb_analysis();
    if (analysis->init(indexname, profile, scriptfile, numRandomRuns, targetUtil)
        != RCOK) {

	cerr << "can't initialize analysis" << endl;
	delete analysis;
	return;
    }
    if (analysis->write(analysisname, false) != RCOK) {
        cerr << "can't write analysis" << endl;
	delete analysis;
	return;
    }

    analyses[numAnalyses].name = strdup(analysisname);
    analyses[numAnalyses].analysis = analysis;
    numAnalyses++;
#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdOpenAnl - read amdb_analysis from file
//
// Description:
/////////////////////////////////////////////////////////////////////////

void
cmdOpenAnl(
    const char* 	filename)
{
#ifdef AMDB
    // make sure we don't overrun analyses[]
    if (numAnalyses == MAXIDX) { 
	cout << "Capacity exceeded (" << MAXIDX << ")" << endl;
	return; 
    }

    amdb_analysis* analysis = new amdb_analysis();

    if (analysis->read(filename) != RCOK) {
        cerr << "Error reading analysis (file " << filename << ")" << endl;
	delete analysis;
	return;
    }

    analyses[numAnalyses].name = strdup(filename);
    analyses[numAnalyses].analysis = analysis;
    numAnalyses++;
#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdCloseAnl - write amdb_analysis to file
//
// Description:
/////////////////////////////////////////////////////////////////////////

void
cmdCloseAnl(
    const char* 	analysisname)
{
#ifdef AMDB
    int i;
    if ((i = getAnalysis(analysisname)) == NOT_FOUND) {
        cerr << "Analysis not open" << endl;
	return;
    }

    amdb_analysis* analysis = analyses[i].analysis;
    if (analysis->write(analyses[i].name, false) != RCOK) {
        cerr << "Error writing analysis (file " << analyses[i].name << ")" << endl;
	return;
    }

    closeAnalysis(i);
#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdSplitStats - call amdb_analysis::analyzeSplit
//
// Description:
//	- needs loaded analysis
//
/////////////////////////////////////////////////////////////////////////

void
cmdSplitStats(
    const char* 	analysis,
    const char* 	option)
{
#ifdef AMDB
    int i;
    if ((i = getAnalysis(analysis)) == NOT_FOUND) {
        cerr << "Analysis not open" << endl;
	return;
    }

    if (option != NULL &&
        strcmp(option, "opt") != 0 && strcmp(option, "act") != 0) {

	cout << "Option " << option << " not recognized" << endl;
	return;
    }
    bool evalOpt = (option != NULL && strcmp(option, "opt") == 0);

    if (analyses[i].analysis->analyzeSplit(evalOpt) != RCOK) {
	cout << "can't analyze splits" << endl;
    }
#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdPenaltyStats - call amdb_analysis::analyzePenalty
//
// Description:
//	- needs loaded analysis
//
/////////////////////////////////////////////////////////////////////////

void
cmdPenaltyStats(
    const char* 	analysis,
    const char* 	loadfile,
    const char* 	option)
{
#ifdef AMDB
    int i;
    if ((i = getAnalysis(analysis)) == NOT_FOUND) {
        cerr << "Analysis not open" << endl;
	return;
    }

    if (option != NULL &&
        strcmp(option, "opt") != 0 && strcmp(option, "act") != 0) {

	cout << "Option " << option << " not recognized" << endl;
	return;
    }
    bool evalOpt = (option != NULL && strcmp(option, "opt") == 0);

    if (analyses[i].analysis->analyzePenalty(evalOpt, loadfile) != RCOK) {
        cerr << "can't analyze penalty" << endl;
	return;
    }

#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdWkldStats - call amdb_analysis::analyzeWkld
//
// Description:
//	- needs loaded analysis
//
/////////////////////////////////////////////////////////////////////////

void
cmdWkldStats(
    const char* 	analysis)
{
#ifdef AMDB
    int i;
    if ((i = getAnalysis(analysis)) == NOT_FOUND) {
        cerr << "Analysis not open" << endl;
	return;
    }

    if (analyses[i].analysis->analyzeWkld(false) != RCOK) {
	cout << "can't analyze workload" << endl;
    }
#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdAnlInfo - print info about analysis
//
// Description:
//	- needs loaded analysis
//
/////////////////////////////////////////////////////////////////////////

void
cmdAnlInfo(
    const char* 	analysis)
{
#ifdef AMDB
    int i;
    if ((i = getAnalysis(analysis)) == NOT_FOUND) {
        cerr << "Analysis not open" << endl;
	return;
    }

    amdb_analysis* anl = analyses[i].analysis;

    cout << "actual: ";
    if (anl->actualAnalysis.profile != NULL) {
        cout << "profile ";
    }
    if (anl->actualAnalysis.map != NULL) {
        cout << "map ";
    }
    if (anl->actualAnalysis.wkldStats != NULL) {
        cout << "wkldstats ";
    }
    if (anl->actualAnalysis.splitStats != NULL) {
        cout << "splitstats ";
    }
    if (anl->actualAnalysis.penaltyStats != NULL) {
        cout << "penaltystats ";
    }
    cout << endl;

    cout << "opt: ";
    if (anl->optAnalysis.profile != NULL) {
        cout << "profile ";
    }
    if (anl->optAnalysis.map != NULL) {
        cout << "map ";
    }
    if (anl->optAnalysis.wkldStats != NULL) {
        cout << "wkldstats ";
    }
    if (anl->optAnalysis.splitStats != NULL) {
        cout << "splitstats ";
    }
    if (anl->optAnalysis.penaltyStats != NULL) {
        cout << "penaltystats ";
    }
    cout << endl;

#endif
}


/////////////////////////////////////////////////////////////////////////
// cmdPredInfo - construct gist::DisplayPredInfo array
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
cmdPredInfo(
    const char* 	table,
    int 		subtreeRoot,
    int 		levels)
{
#ifdef AMDB
    int i;
    if ((i = getTable(table)) == NOT_FOUND) {
        cerr << "Table not open" << endl;
	return;
    }

    gist* index = tables[i].index;
    rc_t status = eARRAYSIZE;
    int numPredInfo = 50;
    gist::DisplayPredInfo* predInfo = NULL;
    while (status == eARRAYSIZE) {
	delete [] predInfo;
	numPredInfo *= 2;
	predInfo = new gist::DisplayPredInfo[numPredInfo];
        status = index->getPredInfo(subtreeRoot, levels, predInfo, numPredInfo);
    }

    if (status != RCOK) {
        cerr << "gist::getPredInfo() failed" << endl;
    }
    delete [] predInfo;
#endif
}

void
cmdHelp()
{
    int i;
    cout << "gistcmdline was built on " << timestamp << endl;
    cout << "Valid commands:" << endl << usage << endl;

    cout << "Valid extension names:" << endl;
    for (i = 0; i < gist_ext_t::gist_numext; ++i) {
        cout << '\t' << gist_ext_t::gist_ext_list[i]->myName << endl;
    }
}

void
cmdPrompt()
{
    if (!noPrompt) {
	cout << "libgist" << "> ";
	cout.flush();
    }
}

int
main(
    int argc,
    char* argv[])
{
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
	    // print help
	    cout << argv[0] << " [-hs]" << endl;
	    exit(0);
	} else if (strcmp(argv[i], "-s") == 0) {
	    // 'silent' option (no prompt)
	    noPrompt = true;
	}
    }
    cout.setf(ios::fixed);
    cmdPrompt();
    yyparse();
	return 0;
}

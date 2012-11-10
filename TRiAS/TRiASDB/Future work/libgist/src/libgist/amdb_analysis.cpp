// amdb_analysis.cc -*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_analysis.cc,v 1.7 2000/03/15 00:24:18 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_analysis.h"
#endif

// VCPORT_B
#ifdef HAVE_VALUES_H
#include <values.h>
#endif
// VCPORT_E

// VCPORT_B
#ifdef WIN32

// Disable debug warnings for classes that get too long because of templates.
#pragma warning(disable: 4786)

#include <fstream>
#include <iostream>
#include <strstream>

#include <vector>
#include <algorithm>

using namespace std;

#else

#include <fstream.h>
#include <iostream.h>
#include <strstream.h>

// STL
#include <vector.h>
#include <algo.h>

#endif
// VCPORT_E

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "amdb_analysis.h"
#include "amdb_clustering.h"

//#include <netinet/in.h> this doesn't work
//#include <arpa/inet.h> this doesn't work either
#include <assert.h>
#include "gist.h"
#include "gist_compat.h"
#include "gist_p.h"
#include "amdb_ext.h"
#include "amdb_wkldprofile.h"
#include "amdb_wkldstats.h"
#include "amdb_splitstats.h"
#include "amdb_penaltystats.h"
#include "amdb_treemap.h"
#include "gist_query.h"



const int amdb_analysis::_MAXLINE = 8192;


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::init - initialize after generating profile
//
// Description:
//	- initialize analysis with tree and profile, compute treemap
//	  for tree
//	- call profile->computeTotals()
//	- read queryFile and store qualification and limit in profile.queries[]
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::init(
    const char* filename, // in: of tree
    amdb_wkldprofile* prof, // in: of tree/queryFile
    const char* queryFile, // in: name of script file
    int numRandomRuns, // in
    float targetUtil) // in
{
    parameters.randomRuns = numRandomRuns;
    parameters.targetUtil = targetUtil;
    actualAnalysis.tree = new gist();
    rc_t status = actualAnalysis.tree->open(filename);
    if (status != RCOK) {
        return(status);
    }
    actualAnalysis.filename = new char[strlen(filename)+1];
    (void) memcpy(actualAnalysis.filename, filename, strlen(filename)+1);
    actualAnalysis.profile = prof;
    actualAnalysis.map = new amdb_treemap();
    actualAnalysis.tree->computeTreeMap(actualAnalysis.map);
    this->queryFile = new char[strlen(queryFile)+1];
    (void) memcpy(this->queryFile, queryFile, strlen(queryFile)+1);

    actualAnalysis.profile->computeTotals();

    // scan scriptfile
    ifstream s(queryFile);
    if (s.fail()) {
        return(eFILEERROR);
    }
    char buf[1024];
    int i = 0;
    while (s.getline(buf, sizeof(buf))) {
	// XXX we should be parsing regular scripts
	prof->setQual(i, buf, 0);
	i++;
    }
    s.close();
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::~amdb_analysis - Destructor
//
// Description:
//	- free all state
/////////////////////////////////////////////////////////////////////////

amdb_analysis::~amdb_analysis()
{
    clear();
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::TreeAnalysis::clear - free state
//
// Description:
//	- only free 'tree' if explicitly requestd (not requested
//	  for actual tree)
/////////////////////////////////////////////////////////////////////////

void
amdb_analysis::TreeAnalysis::clear()
{
    if (tree != NULL) {
	delete tree;
	tree = NULL;
    }
    if (filename != NULL) {
        delete [] filename;
	filename = NULL;
    }
    if (map != NULL) {
        delete map;
	map = NULL;
    }
    if (profile != NULL) {
        delete profile;
	profile = NULL;
    }
    if (wkldStats != NULL) {
        delete wkldStats;
	wkldStats = NULL;
    }
    if (splitStats != NULL) {
        delete splitStats;
	splitStats = NULL;
    }
    if (penaltyStats != NULL) {
        delete penaltyStats;
	penaltyStats = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::clear - Free state
//
// Description:
/////////////////////////////////////////////////////////////////////////

void
amdb_analysis::clear()
{
    actualAnalysis.clear();
    optAnalysis.clear();
    if (optClustering != NULL) {
        delete optClustering;
	optClustering = NULL;
    }
    delete [] queryFile;
    if (_queries != NULL) {
        Vector::const_iterator it;
	for (it = _queries->begin(); it != _queries->end(); it++) {
	    gist_query_t* query = (gist_query_t *) *it;
	    delete query;
	}
	delete _queries;
	_queries = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::read - Read analysis in binary
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::read(
    const char* filename) // in: input filename
{

	// VCPORT_B
#ifdef WIN32
	ifstream s(filename, ios_base::in | ios_base::binary);
#else
    ifstream s(filename);
#endif
	// VCPORT_E

    if (!s.good()) {
        return eFILEERROR;
    }

    clear();

    // read parameters, actualAnalysis and optAnalysis
    W_DO(parameters.read(s));
    W_DO(actualAnalysis.read(s));
    W_DO(optAnalysis.read(s));

    // read optClustering (indicator stored in network order)
    int hasOptClustering;
    s.read((char *) &hasOptClustering, sizeof(hasOptClustering));
    hasOptClustering = ntohl(hasOptClustering);
    if (hasOptClustering) {
	optClustering = new amdb_clustering::Clustering();
        W_DO(optClustering->read(s));
    }

    // read queryFile (length stored in network order)
    int len;
    s.read((char *) &len, sizeof(len));
    len = ntohl(len);
    if (len > 0) {
        queryFile = new char[len+1];
	(void) memset(queryFile, 0, len+1);
	s.read(queryFile, len);
    } else {
        queryFile = NULL;
    }

    // check for errors
    if (!s) {
        return(eFILEERROR);
    }

    s.close();

    return(RCOK);

}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::write - Write analysis to file
//
// Description:
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::write(
    const char* filename, // in: output filename
    bool ascii) // in: if true, write out in ASCII
{
	// VCPORT_B
#ifdef WIN32
	ofstream s(filename, ios_base::out | ios_base::binary);
#else
    ofstream s(filename);
#endif
	// VCPORT_E

    if (!s.good()) {
        return eFILEERROR;
    }

    // write parameters, actualAnalysis and optAnalysis
    W_DO(parameters.write(s, ascii));
    W_DO(actualAnalysis.write(s, ascii));
    W_DO(optAnalysis.write(s, ascii));

    if (!ascii) {
      
      // write indicator (in network order) and optClustering
      int hasOptClustering = htonl(optClustering != NULL);
      s.write((char *) &hasOptClustering, sizeof(hasOptClustering));
      if (optClustering != NULL) {
        W_DO(optClustering->write(s, ascii));
      }
      
      // write queryFile (its size in network order)
      int len = htonl(strlen(queryFile));
      s.write((char *) &len, sizeof(len));
      s.write(queryFile, strlen(queryFile)); // don't use len here!

    }
    else {
      int hasOptClustering = htonl(optClustering != NULL);
      s << hasOptClustering << "\n";
      if (optClustering != NULL) {
        W_DO(optClustering->write(s, ascii));
      }

      s << queryFile << "\n";
    }
      
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::TreeAnalysis::read - read TreeAnalysis in binary
//
// Description:
//	- doesn't open tree
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::TreeAnalysis::read(
    istream& s)
{
    // read filename (length stored in network order)
    int len;
    s.read((char *) &len, sizeof(len));
    len = ntohl(len);
    if (len > 0) {
        filename = new char[len+1];
	(void) memset(filename, 0, len+1);
	s.read(filename, len);
    } else {
        filename = NULL;
    }

    tree = NULL;
#if 0
    // open tree
    if (filename != NULL) {
	tree = new gist();
	rc_t status;
	if ((status = tree->open(filename)) != RCOK) {
	    return(status);
	}
    }
#endif

    // read map, profile, wkldStats, splitStats and penaltyStats,
    // together with indicators
    int notNull;
    s.read((char *) &notNull, sizeof(notNull));
    notNull = ntohl(notNull);
    if (notNull) {
	map = new amdb_treemap();
        W_DO(map->read(s));
    } else {
        map = NULL;
    }

    s.read((char *) &notNull, sizeof(notNull));
    notNull = ntohl(notNull);
    if (notNull) {
	profile = new amdb_wkldprofile();
	W_DO(profile->read(s));
	if (map != NULL) {
	    // might be needed for further analyses
	    profile->setTreeMap(map);
	}
    } else {
        profile = NULL;
    }

    s.read((char *) &notNull, sizeof(notNull));
    notNull = ntohl(notNull);
    if (notNull) {
	wkldStats = new amdb_wkldstats();
        W_DO(wkldStats->read(s));
    } else {
        wkldStats = NULL;
    }

    s.read((char *) &notNull, sizeof(notNull));
    notNull = ntohl(notNull);
    if (notNull) {
	splitStats = new amdb_splitstats();
        W_DO(splitStats->read(s));
    } else {
        splitStats = NULL;
    }

    s.read((char *) &notNull, sizeof(notNull));
    notNull = ntohl(notNull);
    if (notNull) {
	penaltyStats = new amdb_penaltystats();
        W_DO(penaltyStats->read(s));
    } else {
        penaltyStats = NULL;
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::TreeAnalysis::write - write TreeAnalysis in binary
//
// Description:
//	- doesn't save tree, assumed to be done independently
//
// Return Values:
//      RCOK
//	eFILEERROR
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::TreeAnalysis::write(
    ostream& s,
    bool ascii)
{
    // write filename (length in network order)
    int len = (filename == NULL ? 0 : strlen(filename));
    len = htonl(len);
    s.write((char *) &len, sizeof(len));
    if (filename != NULL) {
        s.write(filename, strlen(filename)); // don't use len!
    }

    // write map, profile, wkldStats, splitStats and penaltyStats,
    // together with indicators
    int notNull = htonl(map != NULL);
    s.write((char *) &notNull, sizeof(notNull));
    if (map != NULL) {
	W_DO(map->write(s, ascii));
    }
    notNull = htonl(profile != NULL);
    s.write((char *) &notNull, sizeof(notNull));
    if (profile != NULL) {
	W_DO(profile->write(s, ascii));
    }
    notNull = htonl(wkldStats != NULL);
    s.write((char *) &notNull, sizeof(notNull));
    if (wkldStats != NULL) {
	W_DO(wkldStats->write(s, ascii));
    }
    notNull = htonl(splitStats != NULL);
    s.write((char *) &notNull, sizeof(notNull));
    if (splitStats != NULL) {
	W_DO(splitStats->write(s, ascii));
    }
    notNull = htonl(penaltyStats != NULL);
    s.write((char *) &notNull, sizeof(notNull));
    if (penaltyStats != NULL) {
	W_DO(penaltyStats->write(s, ascii));
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::analyzeWkld - compute wkld stats
//
// Description:
//	- for now, we ignore 'optTree'
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::analyzeWkld(
    bool optTree) // in: if true, analyze opt. tree
{
    TreeAnalysis* target = (optTree ? &optAnalysis : &actualAnalysis);;

    // need optClustering to compute metrics
    W_DO(_computeOptClustering());

    target->wkldStats = new amdb_wkldstats();
    target->wkldStats->computeStats(*target->profile, *target->map, *optClustering,
        parameters);
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::analyzeSplit - run splits on leaves and compute metrics
//
// Description:
//	- if done for optTree and optTree doesn't exist yet, compute it
//	  (give it same name as actual tree, plus "opt-" prefix)
//	- compute averages when done with all leaves
//
// Return Values:
//      RCOK
//	eHASSPLITSTATS
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::analyzeSplit(
    bool optTree) // in: if true, analyze split in opt. tree
{
    TreeAnalysis* target = (optTree ? &optAnalysis : &actualAnalysis);;
    //if (target->splitStats != NULL) {
        //return(eHASSPLITSTATS);
    //}

    if (optTree && target->tree == NULL) {
        W_DO(_createOptTree());
    }
    W_DO(_openTree(*target));

    if (_queries == NULL) {
        W_DO(_loadQueries());
    }

    int rightEntries[gist_p::max_scnt];
    int numRight;
    gist::AlignedPred x, y;
    vec_t leftBp(x.pred, gist_p::max_tup_sz);
    vec_t rightBp(y.pred, gist_p::max_tup_sz);

    target->splitStats = new amdb_splitstats();
    amdb_treemap::PageMap::iterator it;
    for (it = target->map->pageMap.begin();
        it != target->map->pageMap.end(); it++) {

	amdb_treemap::PageInfo* info = (amdb_treemap::PageInfo *)
	    (*it).second;
	if (info->level > 1) {
	    // this is not a leaf, ignore it
	    continue;
	}
	shpid_t pageno = (shpid_t) (*it).first;
	W_DO(target->tree->pickSplit(pageno, rightEntries, numRight,
	    leftBp, rightBp));
	W_DO(target->splitStats->evalSplit(*target->tree, *target->profile,
	    *target->map, *_queries, pageno, rightEntries, numRight, leftBp,
	    rightBp));
    }
    target->splitStats->computeAvgStats(parameters.targetUtil, *target->map);

    return(RCOK);
}


////////////////////////////////////////////////////////////////////////////////
// amdb_analysis::analyzePenalty - compute penalty metrics for sample insertions
//
// Description:
//	- evaluates insertions of keys in loadfile
//
// Return Values:
//      RCOK
//	eHASPENALTYSTATS
//	eCANTPARSEPRED
//	eFILEERROR
//	ePARSEERROR
////////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::analyzePenalty(
    bool optTree, // in: if true, analyze split in opt. tree
    const char* loadfile) // in: name of file containing keys
{
    TreeAnalysis* target = (optTree ? &optAnalysis : &actualAnalysis);;
    if (target->penaltyStats != NULL) {
        return(eHASPENALTYSTATS);
    }

    if (optTree && target->tree == NULL) {
        W_DO(_createOptTree());
    }
    W_DO(_openTree(*target));

    if (_queries == NULL) {
        W_DO(_loadQueries());
    }

    // make sure extension can parse predicates
    gist_ext_t* ext = target->tree->extension();
    if (ext->parsePred == NULL) {
	return(eCANTPARSEPRED);
    }

    ifstream s(loadfile);
    if (s.fail()) {
	return(eFILEERROR);;
    }

    target->penaltyStats = new amdb_penaltystats();
    // read lines and parse them
    // (format: "\"<key>\"")
    char buf[_MAXLINE];
    char keystr[_MAXLINE];
    char key[gist_p::max_tup_sz];
    int klen;
    vec_t keyv;
    shpid_t targetLeaf;
    while (s.getline(buf, sizeof(buf))) {
	istrstream s(buf); // scan input line for "<key>"
	if (_scanString(s, keystr) != RCOK) {
	    return(ePARSEERROR);
	}

	if (ext->parsePred(keystr, (void *) key, klen) != RCOK) {
	    return(ePARSEERROR);
	}

	// find the target leaf, then evaluate it
	keyv.set(key, klen);
	W_DO(target->tree->locateTargetLeaf(keyv, targetLeaf));
	W_DO(target->penaltyStats->evalPenalty(*target->tree, *target->profile,
	    *target->map, *_queries, targetLeaf, keyv));
    }

    s.close();

    target->penaltyStats->computeAvgStats(parameters.targetUtil,
        *target->splitStats, *target->map);

    return(RCOK);
}

/////////////////////////////////////////////////////////////////////////
// amdb_analysis::_computeOptClustering - compute hypergraph clustering
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::_computeOptClustering()
{
    if (optClustering != NULL) {
	// it's already been computed
        return(RCOK);
    }
    amdb_clustering::ResultSet* resultSets;
    actualAnalysis.profile->extractResultSets(resultSets);

    int dummyInt;
    optClustering = new amdb_clustering::Clustering();
    W_DO(amdb_clustering::optClustering(resultSets, actualAnalysis.profile->queries.size(),
        parameters.targetUtil, 0, 10, 1, *actualAnalysis.map, *optClustering,
	dummyInt, dummyInt));

    delete [] resultSets;

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// amdb_analysis::_createOptTree - create and save optAnalysis.tree
//
// Description:
//	- opt tree saved in file "opt-" + actualAnalysis.filename
//	- also creates the tree map and translateMap
//	- create optAnalysis.profile and copy result sets from 
//	  actualAnalysis.profile
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::_createOptTree()
{
    if (optClustering == NULL) {
        W_DO(_computeOptClustering());
    }

    // construct filename and create opt tree
    char* prefix = "opt-";
    int totalLen = strlen(actualAnalysis.filename) + strlen(prefix) + 1;
    optAnalysis.filename = new char[totalLen];
    (void) strcpy(optAnalysis.filename, prefix);
    char* rest = optAnalysis.filename + strlen(prefix);
    (void) strcpy(rest, actualAnalysis.filename);
    optAnalysis.tree = new gist();
    assert(optAnalysis.tree != NULL);
    Rid2ItemIdMap ridMap;
    W_DO(actualAnalysis.tree->createOpt(optAnalysis.filename, parameters.targetUtil,
        *actualAnalysis.profile, *optClustering, *actualAnalysis.map, ridMap));
    W_DO(optAnalysis.tree->open(optAnalysis.filename));

    // create tree map
    optAnalysis.map = new amdb_treemap();
    W_DO(optAnalysis.tree->computeTreeMap(optAnalysis.map));

    // compute translateMap
    TranslationMap* translateMap = new TranslationMap();
    //translateMap = new TranslationMap();
    amdb_treemap::ItemMap::iterator it;
    ItemId optId; // index into optAnalysis.map->itemMap
    for (it = optAnalysis.map->itemMap.begin(), optId = 0;
        it != optAnalysis.map->itemMap.end(); it++, optId++) {

	amdb_treemap::RecInfo* info = (amdb_treemap::RecInfo*) *it;
	ItemId origId = ridMap[info->loc.treeLoc];
	// should I do Rid2ItemIdMap::iterator rit = ridMap->find(info->treeLoc]?
	(*translateMap)[origId] = (void *) optId;
    }

    // create profile with result sets
    optAnalysis.profile = new amdb_wkldprofile();
    optAnalysis.profile->copyResultSets(*actualAnalysis.profile, *translateMap);
    delete translateMap; // no longer needed

    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::_scanString
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::_scanString(
    istream& s, // in: input stream
    char* str) // out: string stripped off '"'s
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


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::_loadQueries - parse qualifications stored in profile
//
// Description:
//	- allocate _queries as well as the gist_query_t objects
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::_loadQueries()
{
    _queries = new Vector();
    amdb_wkldprofile::QueryVect::const_iterator it;
    amdb_wkldprofile* prof = actualAnalysis.profile;
    for (it = prof->queries.begin(); it != prof->queries.end(); it++) {
	const amdb_wkldprofile::Query* query =
	    (amdb_wkldprofile::Query *) *it;
        gist_query_t* queryStruct;
        rc_t status = actualAnalysis.tree->extension()->parseQuery(
	    query->qual, queryStruct);
        if (status != RCOK) {
            return(ePARSEERROR);
        }
	_queries->push_back((void *) queryStruct);
    }
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::TreeAnalysis::~TreeAnalysis - destructor
//
// Description:
//	- dealloc state and close tree
///////////////////////////////////////////////////////////////////////////////

amdb_analysis::TreeAnalysis::~TreeAnalysis()
{
    delete tree;
    delete [] filename;
    delete map;
    delete profile;
    delete wkldStats;
    delete splitStats;
    delete penaltyStats;
}


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::Parameters::write - write to output stream
//
// Description:
//	- write integer in network order
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::Parameters::write(
    ostream& s,
    bool ascii)
{
    int runs = htonl(randomRuns);
    s.write((char *) &runs, sizeof(runs));
    s.write((char *) &targetUtil, sizeof(targetUtil));
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::Parameters::read - read from input stream
//
// Description:
//	- convert integers from network to host order
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::Parameters::read(
    istream& s)
{
    s.read((char *) &randomRuns, sizeof(randomRuns));
    randomRuns = ntohl(randomRuns);
    s.read((char *) &targetUtil, sizeof(targetUtil));
    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_analysis::_openTree - open target tree
//
// Description:
//	- open tree in target analysis if it's not already open
///////////////////////////////////////////////////////////////////////////////

rc_t
amdb_analysis::_openTree(
    TreeAnalysis& target)
{
    if (target.tree != NULL) {
        // it's already open
	return(RCOK);
    }
    // open tree
    assert(target.filename != NULL);
    target.tree = new gist();
    W_DO(target.tree->open(target.filename));
    return(RCOK);
}

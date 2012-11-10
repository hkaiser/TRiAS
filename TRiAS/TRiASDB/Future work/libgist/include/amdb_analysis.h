// amdb_analysis.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_analysis.h,v 1.3 2000/03/10 01:38:58 mashah Exp $

#ifndef AMDB_ANALYSIS_H
#define AMDB_ANALYSIS_H

#ifdef __GNUG__
#pragma interface "amdb_analysis.h"
#endif


#include "amdb_defs.h"		// for Map, Vector, ItemId
#include "gist_defs.h"		// for shpid_t
#include "amdb_clustering.h"	// for Clustering


/*
 * amdb_analysis:
 *
 */

class gist;
class amdb_treemap;
class amdb_wkldprofile;
class amdb_wkldstats;
class amdb_splitstats;
class amdb_penaltystats;

// VCPORT_B
#ifndef WIN32
class istream;
class ostream;
#endif
// VCPORT_E

class amdb_analysis
{

public:

    // info about profile
    struct Parameters {
        int randomRuns; // # of runs of random clustering
	float targetUtil; // target utilization for clustering (both opt. and random)

	Parameters(int runs, float util) : randomRuns(runs), targetUtil(util) {}
	rc_t write(ostream& s, bool);
	rc_t read(istream& s);
    };

    struct TreeAnalysis {
        gist* tree;
	char* filename; // of tree
	amdb_treemap* map;
	amdb_wkldprofile* profile;
	amdb_wkldstats* wkldStats;
	amdb_splitstats* splitStats;
	amdb_penaltystats* penaltyStats;

	TreeAnalysis() : tree(NULL), filename(NULL), map(NULL), profile(NULL),
	    wkldStats(NULL), splitStats(NULL), penaltyStats(NULL) {}

	~TreeAnalysis();

	rc_t read(istream& s);
	rc_t write(ostream& s, bool ascii);
	void clear();
    };

    ///////////////////////////////////////////////////////////////////////////
    // State
    ///////////////////////////////////////////////////////////////////////////

    Parameters parameters;
    TreeAnalysis actualAnalysis; // of actual tree
    TreeAnalysis optAnalysis; // of hypergraph-generated tree
    amdb_clustering::Clustering* optClustering;
    char* queryFile; // name of script file


    ///////////////////////////////////////////////////////////////////////////
    // Interface
    ///////////////////////////////////////////////////////////////////////////

    // create analysis which will be read from file
    amdb_analysis() :
       parameters(0, 0.0), actualAnalysis(), optAnalysis(), optClustering(NULL),
       queryFile(NULL), _queries(NULL) {}

    // create virgin analysis with profile
    rc_t init(
	const char* filename,
	amdb_wkldprofile* prof,
	const char* queryFile,
	int numRandomRuns,
	float targetUtil);

    ~amdb_analysis();
    void clear(); // delete all stored data

    rc_t read(const char* filename);
    rc_t write(const char* filename, bool ascii);

    rc_t analyzeWkld(bool optTree);
    rc_t analyzeSplit(bool optTree);
    rc_t analyzePenalty(bool optTree, const char* loadfile);

private:

    static const int _MAXLINE; // = 8192, needed in analyzePenalty

    rc_t _computeOptClustering();
    rc_t _createOptTree();
    static rc_t _scanString(
	istream& s, // in: input stream
	char* str); // out: string stripped off '"'s

    Vector* _queries; // vector<gist_query_t *>
    rc_t _loadQueries();
    rc_t _openTree(TreeAnalysis& analysis);

};

#endif

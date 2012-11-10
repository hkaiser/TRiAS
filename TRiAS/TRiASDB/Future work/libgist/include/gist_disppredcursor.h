// gist_disppredcursor.h						-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_disppredcursor.h,v 1.2 1998/12/15 00:41:03 marcel Exp $


#ifndef GIST_PREDCURSOR_H
#define GIST_PREDCURSOR_H

#include "gist_defs.h" // for Vector
#include "gist_p.h" // for gist_p

class gist;

// this pred cursor class is used purely for display purposes
// (amdb_ext_t::displayPreds)
class gist_disppredcursor_t {
public:

    gist_disppredcursor_t(gist* index);
    ~gist_disppredcursor_t(); 

    // returns next pred info
    rc_t getNext(void*& key, int& klen, int& level, int& color);

    // returns remaining number of predicates in cursor
    int numPreds();

    // add single predicate
    void add(shpid_t pageno, int level, int slot, int color);

    // add all predicates on page
    rc_t add(shpid_t pageno, int level, int color);

    // start from the beginning
    void reset() { _next = 0; }

private:

    gist* _index;

    typedef Vector PredInfoVector; // vector<gist::DisplayPredInfo *> 
    PredInfoVector _predInfo;
    int _next; // index of next entry to return

    // scratch state
    gist_p _page; // current page
    char _key[gist_p::max_tup_sz]; // most recently returned key

};

#endif // GIST_PREDCURSOR_H

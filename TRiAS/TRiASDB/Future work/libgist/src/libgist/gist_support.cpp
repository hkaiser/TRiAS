// gist_support.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_support.cc,v 1.7 2000/03/15 00:24:26 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_support.h"
#endif

#include <stdio.h>

// VCPORT_B
#ifdef WIN32
#include <iostream>
#include <strstream>

using namespace std;
#else
#include <iostream.h>
#include <strstream.h>
#endif
// VCPORT_E

#include "gist_defs.h"
#include "gist_ext.h"
#include "gist_compat.h"
#include "gist_unorderedn.h"
#include "gist_unordered.h"
#include "gist_support.h"
#include "gist_rtpred_point.h"
#include "gist_rtpred_rect.h"
#include "gist_rtpred_sphere.h"
#include "gist_rtpred_ss.h"
#include "gist_rtpred_sr.h"
#include "gist_rtree.h"		// for rt_query_t
#include "gist_btree.h"		// for rt_query_t
#include <math.h>
#include <stdlib.h>

static rc_t _parseBtOp(istrstream& s, bt_query_t::bt_oper& oper);

void
_printRect(
    ostream& s,
    const double *coord,
    int dim)
{
    s << "(";
    for (int i = 0; i < dim; i++) {
	s << coord[2*i] << ", " <<  coord[2*i+1];
	if (i < dim - 1) s << ", ";
    }
    s << ")";
}

void
_printPt(
    ostream& s,
    const double *coord,
    int dim)
{
    s << "(";
    for (int i = 0; i < dim; i++) {
	s << coord[i];
	if (i < dim - 1) s << ", ";
    }
    s << ")";
}


/////////////////////////////////////////////////////////////////////////
// gist_support::printRectRt - print predicates of rectangle R-tree
//
// Description:
//	- stores rects on leaves and internal nodes
//
/////////////////////////////////////////////////////////////////////////

void
gist_support::printRectRtPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    _printRect(s, (const double *) pred.ptr(0), rt_rect::size2dim(pred.len(0)));
}


/////////////////////////////////////////////////////////////////////////
// gist_support::printPtRt - print predicates of point R-tree
//
// Description:
//	- stores points on leaves and rects on internal nodes
//
/////////////////////////////////////////////////////////////////////////

void
gist_support::printPtRtPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    if (level == 1) {
	_printPt(s, (const double *) pred.ptr(0), rt_point::size2dim(pred.len(0)));
    } else {
	_printRect(s, (const double *) pred.ptr(0), rt_rect::size2dim(pred.len(0)));
    }
}

void
gist_support::printSrPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    _printPt(s, (const double *) pred.ptr(0), rt_point::size2dim(pred.len(0)));
}

void
gist_support::printSsPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    _printPt(s, (const double *) pred.ptr(0), rt_point::size2dim(pred.len(0)));
}


/////////////////////////////////////////////////////////////////////////
// gist_support::printStringBtPred - print predicates of string B-tree
//
// Description:
//	- predicates are '\0'-delimited strings (-\infty encoded as '\1')
//
/////////////////////////////////////////////////////////////////////////

void
gist_support::printStringBtPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    const char* str = (const char *) pred.ptr(0);
    if (str[0] == 1) {
        // this is -\infty
	s << "-INFTY";
    }
    s << "'" << str << "'"; 
}

void
gist_support::printIntBtPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    s << *((int *) pred.ptr(0));
}


/////////////////////////////////////////////////////////////////////////
// gist_support::printInt - print integer data
//
// Description:
//	- data need not be 4-byte aligned
//
/////////////////////////////////////////////////////////////////////////

void
gist_support::printInt(
    ostream& s, 
    const vec_t& data)
{
    int i;
    (void) memcpy((void *) &i, data.ptr(0), sizeof(int));
    assert(data.len(0) == sizeof(int));
    s << i;
}


///////////////////////////////////////////////////////////////////////////////
// gist_support::parseString -  parse quote-delimited string
//
// Description:
//	- recognizes input of the form "'<string>'" (<string> can contain
//	  \-escaped "'"s)
//	- we assume that 'out' is big enough to hold entire string
//	- returned length includes terminating '\0'
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
gist_support::parseString(
    const char* str,
    void* outparam,
    int& len)
{
    istrstream s(str, strlen(str));
    return(parseString(s, outparam, len));
}

rc_t
gist_support::parseString(
    istream& s,
    void* outparam,
    int& len)
{
//    rc_t status;
    char* out = (char*) outparam;

    s >> ws; // skip over preceding whitespace
    char ch;
    s.get(ch);
    if (ch != '\'') {
	// string must start with "'"
        return(ePARSEERROR);
    }

    len = 0;
    // read chars until we hit the next '\''
    bool escaped; // true if last char was escaped
    do {
	escaped = false;
        s.get(ch);
	if (ch == '\\') {
	    escaped = true;
	    s.get(ch);
	}
	out[len] = ch;
	len++;
    } while ((ch != '\'' || escaped) && !s.eof());
    if (ch != '\'') {
	// right quote missing
        return(ePARSEERROR);
    }
    out[len-1] = '\0'; // -1: get rid of right quote
    return(RCOK);
}


rc_t
gist_support::parseInt(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parseInt(s, out, len);
}

rc_t
gist_support::parseInt(
    istream& s,
    void* out,
    int& len)
{
    s >> *((int *) out);
    if (s.fail()) return ePARSEERROR;
    len = sizeof(int);
    return RCOK;
}

rc_t
gist_support::parsePoint(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parsePoint(s, out, len);
}

rc_t
gist_support::parsePoint(
    istream& s,
    void* out,
    int& len)
{
    double* coords = (double *) out;
    int dims = 0;
    while (s >> *coords) {
	coords++;
	dims++;
    }
    if (dims == 0) {
        return(ePARSEERROR); // can't have point with 0 dimensions
    }
    len = dims * sizeof(double);
    return(RCOK);
}
rc_t
gist_support::parseRect(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parseRect(s, out, len);
}

rc_t
gist_support::parseRect(
    istream& s,
    void* out,
    int& len)
{
    double* coords = (double *) out;
    int dims = 0;
    while (s >> *coords) {
	coords++;
	dims++; // for now, count every coord as a dimension
    }
    if (dims == 0 || (dims % 2) != 0) {
        return(ePARSEERROR);
    }
    dims /= 2;
    len = dims * 2 * sizeof(double);
    return RCOK;
}

rc_t
gist_support::parseGeoQuery(
    const char* str,
    gist_query_t*& query)
{
    if (strcmp(str, "") == 0) {
        // no qualification
	query = new rt_query_t(rt_query_t::rt_nooper, 
	    rt_query_t::rt_pointarg, NULL);
	return RCOK;
    }

    istrstream s(str, strlen(str));

    s >> ws; // remove leading whitespace
    char op; // operator (&, <, >, =)
    s >> op;
    if (s.fail()) return ePARSEERROR;
    rt_query_t::rt_oper oper;
    switch (op) {
	case '&':
	    oper = rt_query_t::rt_overlap;
	    break;
	case '<':
	    oper = rt_query_t::rt_contained;
	    break;
	case '>':
	    oper = rt_query_t::rt_contains;
	    break;
	case '=':
	    oper = rt_query_t::rt_equal;
	    break;
	case '~':
	    oper = rt_query_t::rt_nearest;
	    break;
	case '#':
	    oper = rt_query_t::rt_count_overlap;
	    break;
	case '!':
	    oper = rt_query_t::rt_count_sample;
	    break;
	case '@':
	    oper = rt_query_t::rt_count_combo;
	    break;
	default:
	    return ePARSEERROR;
    }

    s >> ws;
    char arg; // point ('p') or rectangle ('r')
    s >> arg;
    if (s.fail()) return ePARSEERROR;
    if ((arg != 'p' && arg != 'r') ||
        (arg == 'r' && oper == rt_query_t::rt_nearest)) {

	// cannot run NN search with rectangle as center:
	// need to write rt_rect::dist_rect() and rt_point::dist_rect()
	// and register those in the prioTbl's
	return(ePARSEERROR);
    }

    double coord[gist_p::max_tup_sz/sizeof(double)];
    int len;
    if (arg == 'p') {
        // construct point argument
	if (parsePoint(s, (void *) coord, len) != RCOK) {
	    return(ePARSEERROR);
	}
	int dim = len / sizeof(double);
	rt_point* pt = new rt_point(dim);
	for (int i = 0; i < dim; i++) {
	    pt->co(i) = coord[i];
	}

	query = new rt_query_t(oper, rt_query_t::rt_pointarg, pt);
    } else {
        // construct rectangle argument
	if (parseRect(s, (void *) coord, len) != RCOK) {
	    return(ePARSEERROR);
	}
	int dim = len / (2 * sizeof(double));
	rt_rect* rect = new rt_rect(dim);
	for (int i = 0; i < dim; i++) {
	    rect->lo(i) = coord[2*i];
	    rect->hi(i) = coord[2*i+1];
	}

	query = new rt_query_t(oper, rt_query_t::rt_rectarg, rect);
    }

    return RCOK;
}

// query: any of the btree operators followed by integer
rc_t
gist_support::parseIntQuery(
    const char* str,
    gist_query_t*& query)
{
    istrstream s(str, strlen(str));
    rc_t status;
    bt_query_t::bt_oper oper;
    if ((status = _parseBtOp(s, oper)) != RCOK) {
        return status;
    }

    if (oper == bt_query_t::bt_nooper) {
        // no qualification, nothing to parse
	bt_query_t* q = new bt_query_t(oper, NULL, NULL);
	query = q;
	return(RCOK);
    }

    int arg1, arg2;
    int dummy; // len not needed

    W_DO(parseInt(s, (void*) &arg1, dummy));
    if (oper == bt_query_t::bt_betw) {
	W_DO(parseInt(s, (void*) &arg2, dummy));
    }

    // construct query
    int* int1 = new int(arg1);
    int* int2 = NULL;
    if (oper == bt_query_t::bt_betw) {
        int2 = new int(arg2);
    }
    bt_query_t* q = new bt_query_t(oper, int1, int2);
    query = q;
    return(RCOK);
}

static rc_t
_parseBtOp(
    istrstream& s,
    bt_query_t::bt_oper& oper)
{
    s >> ws; // remove leading whitespace
    char op[16]; // operator (=, <, <=, >, >=, between)
    s >> op;
    if (s.fail()) {
        // no qualification
	oper = bt_query_t::bt_nooper;
	return RCOK;
    }
    if (strcmp(op, "=") == 0) {
        oper = bt_query_t::bt_eq;
    } else if (strcmp(op, "<") == 0) {
        oper = bt_query_t::bt_lt;
    } else if (strcmp(op, "<=") == 0) {
        oper = bt_query_t::bt_le;
    } else if (strcmp(op, ">") == 0) {
        oper = bt_query_t::bt_gt;
    } else if (strcmp(op, ">=") == 0) {
        oper = bt_query_t::bt_ge;
    } else if (strcmp(op, "between") == 0) {
        oper = bt_query_t::bt_betw;
    } else {
        // didn't recognize that operator 
	return ePARSEERROR;
    }

    return RCOK;
}

// string are enclosed in single quotes (the qualification itself is 
// enclosed in double quotes) and single quotes within a string are escaped
// with '\'
rc_t
gist_support::parseStringQuery(
    const char* str,
    gist_query_t*& query)
{
    istrstream s(str, strlen(str));
    rc_t status;
    bt_query_t::bt_oper oper;
    if ((status = _parseBtOp(s, oper)) != RCOK) {
        return status;
    }

    if (oper == bt_query_t::bt_nooper) {
        // no qualification, nothing to parse
	bt_query_t* q = new bt_query_t(oper, NULL, NULL);
	query = q;
	return(RCOK);
    }

    const int MAXSTRLEN = 8192;
    char arg1[MAXSTRLEN];
    char arg2[MAXSTRLEN];
    int dummy; // len not needed

    // parse first argument
    W_DO(parseString(s, arg1, dummy));
    if (oper == bt_query_t::bt_betw) {
	// parse second argument
	W_DO(parseString(s, arg2, dummy));
    }

    // construct query
    char* str1 = new char[strlen(arg1)+1];
    char* str2 = NULL;
    (void) memcpy(str1, arg1, strlen(arg1)+1);
    if (oper == bt_query_t::bt_betw) {
	str2 = new char[strlen(arg2)+1];
	(void) memcpy(str2, arg2, strlen(arg2)+1);
    } 
    bt_query_t* q = new bt_query_t(oper, str1, str2);
    query = q;
    return(RCOK);
}


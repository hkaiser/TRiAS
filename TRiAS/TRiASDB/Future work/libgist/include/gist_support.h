// gist_support.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_support.h,v 1.2 1998/12/14 00:46:04 marcel Exp $

#ifndef GIST_SUPPORT_H
#define GIST_SUPPORT_H

#ifdef __GNUG__
#pragma interface "gist_support.h"
#endif

#include <stdio.h>		// for NULL

#include "gist_defs.h"		// for rc_t

/*
 * gist_support:
 *
 * Collection of static routines that can be used for the data-specific
 * interface routines of the gist_ext_t extension (those that print and parse stuff).
 * They are made public through this interface so they can
 * be used for a variety of extensions.
 */

class gist_support
{

public:

    ////////////////////////////////////////////////////////
    // printing predicates
    ////////////////////////////////////////////////////////

    // point R-trees: leaves: points, internal nodes: rects
    static void printPtRtPred(
        std::ostream& s,
	const vec_t& pred,
	int level);

    // rectangle R-trees: leaves and internal nodes: rects
    static void printRectRtPred(
        std::ostream& s,
	const vec_t& pred,
	int level);

    static void printSrPred(
        std::ostream& s,
	const vec_t& pred,
	int level);

    static void printSsPred(
        std::ostream& s,
	const vec_t& pred,
	int level);

    // integer B-tree: leaves: ints, internal nodes: int ranges
    static void printIntBtPred(
        std::ostream& s,
	const vec_t& pred,
	int level);

    // string B-tree: leaves: strings, internal nodes: string ranges
    static void printStringBtPred(
        std::ostream& s,
	const vec_t& pred,
	int level);


    ////////////////////////////////////////////////////////
    // printing data
    ////////////////////////////////////////////////////////

    static void printInt(
	std::ostream& s, 
	const vec_t& data);


    ////////////////////////////////////////////////////////
    // parsing predicates and data
    ////////////////////////////////////////////////////////

    // parse single integer
    static rc_t parseInt(
	const char* str,
	void* out,
	int& len);

    // parse single integer
    static rc_t parseInt(
	std::istream& s,
	void* out,
	int& len);

    static rc_t parseString(
	const char* str,
	void* out,
	int& len);

    static rc_t parseString(
	std::istream& s,
	void* out,
	int& len);

    // parse sequence of doubles, one for each dimension
    static rc_t parsePoint(
	const char* str,
	void* out,
	int& len);

    // same, reading from an istream
    static rc_t parsePoint(
	std::istream& s,
	void* out,
	int& len);

    // parse sequence of doubles, two for each dimension
    static rc_t parseRect(
	const char* str,
	void* out,
	int& len);

    // same, reading from an istream
    static rc_t parseRect(
	std::istream& s,
	void* out,
	int& len);


    ////////////////////////////////////////////////////////
    // parsing queries
    ////////////////////////////////////////////////////////

    static rc_t parseStringQuery(
	const char* str,
	gist_query_t*& query);

    static rc_t parseIntQuery(
	const char* str,
	gist_query_t*& query);

    // parse query for spatial AMs; returns an rt_query_t in 'query';
    // query looks like "<op> <arg> (<point> | <rect>)", where <op> = [&<>=]
    // and arg = [pr]
    static rc_t parseGeoQuery(
	const char* str,
	gist_query_t*& query);

};

#endif

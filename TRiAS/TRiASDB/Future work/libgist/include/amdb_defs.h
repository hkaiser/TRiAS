// amdb_defs.h							-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_defs.h,v 1.12 1999/06/27 00:17:13 marcel Exp $

#ifndef AMDB_DEFS_H
#define AMDB_DEFS_H

#ifdef __GNUG__
#pragma interface "amdb_defs.h"
#endif

#include "gist_defs.h"		// for size_t

// STL
#include <map>

// general containers, mainly used for profiles
typedef std::map<unsigned int, void *, std::less<unsigned int> > Map;

// for clustering purposes, leaf data items are numbered consecutively
typedef int ItemId;

// translation map: from orig. item no. to item no. in optTree
// needed for interpreting result sets in context of optTree
// typedef map<ItemId, ItemId> 
typedef Map TranslationMap;

// miscellaneous stuff
struct Rid {
    shpid_t page;
    int slot;
};

// sort clustering in ascending cluster number order
struct less_Rid : std::binary_function<Rid, Rid, bool> {
    bool operator()(const Rid& x, const Rid& y) const 
    {
        if (x.page == y.page) {
	    return(x.slot < y.slot);
	} else {
	    return(x.page < y.page);
	}
    }
};

// map constructed in gist::createOpt()
typedef std::map<Rid, ItemId, less_Rid> Rid2ItemIdMap;

// this shouldn't really be necessary, but I couldn't get libgist to build
// with the recommended include file (<arpa/inet.h>) for the following 2 functions
// (and it wouldn't build with <netinet/in.h> either):

// why doesn't this work on melt all of a sudden
#define ntohl(int) (int) 
#define htonl(int) (int)
extern "C" {
//extern int ntohl(int);
//extern int htonl(int);
}


#if 0
/*
 * _Vector:
 * 
 */
class _Vector 
{
public:

    Vector v;
    typedef Vector::value_type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Vector::iterator iterator;
    typedef Vector::const_iterator const_iterator;
    typedef Vector::size_type size_type;

    _Vector() : v() {}
    _Vector(size_type n) : v(n) {}
    _Vector(size_type n, const value_type& t) : v(n, t) {} 

    void reserve(size_type n) { v.reserve(n); }
    size_type size() const { return v.size(); }
    bool empty() const { return v.empty(); }
    void push_back(const value_type& t) { v.push_back(t); }
#ifdef HAVE_STL_3
    iterator erase(iterator first, iterator last) { return v.erase(first, last); }
#else
    void erase(iterator first, iterator last) { v.erase(first, last); }
#endif
    reference operator[](size_type n) { return v[n]; }
    const_reference operator[](size_type n) const { return v[n]; }
    iterator begin() { return v.begin(); }
    const_iterator begin() const { return v.begin(); }
    iterator end() { return v.end(); }
    const_iterator end() const { return v.end(); }
    reference front() { return v.front(); }
    const_reference front() const { return v.front(); }
    reference back() { return v.back(); }
    const_reference back() const { return v.back(); }
    
};

template <class T>
class Vector1 : private _Vector
{
public:

    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

    Vector1() : _Vector() {}
    Vector1(size_type n) : _Vector(n) {}
    Vector1(size_type n, const T& t) : _Vector(n, (const _Vector::value_type&) t) {}

    void reserve(size_type n) { _Vector::reserve(n); }
    size_type size() const { return _Vector::size(); }
    bool empty() const { return _Vector::empty(); }
    void push_back(const value_type& t) { _Vector::push_back((const _Vector::value_type&) t); }
    iterator erase(iterator first, iterator last) { return _Vector::erase(first, last); }
    reference operator[](size_type n) { return _Vector::operator[](n); }
    const_reference operator[](size_type n) const { return _Vector::operator[](n); }
    iterator begin() { return (iterator) _Vector::begin(); }
    const_iterator begin() const { return (iterator) _Vector::begin(); }
    iterator end() { return (iterator) _Vector::end(); }
    const_iterator end() const { return (iterator) _Vector::end(); }
    reference front() { return (reference) _Vector::front(); }
    const_reference front() const { return (reference) _Vector::front(); }
    reference back() { return (reference) _Vector::back(); }
    const_reference back() const { return (reference) _Vector::back(); }

};
#endif

#endif // AMDB_DEFS_H

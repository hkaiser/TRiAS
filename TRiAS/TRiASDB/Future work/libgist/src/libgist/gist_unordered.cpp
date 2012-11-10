// gist_unordered.cc
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_unordered.cc,v 1.6 1998/09/24 05:21:40 marcel Exp $


#include <assert.h>
#include "gist_p.h"

#ifdef __GNUG__
#pragma implementation "gist_unordered.h"
#endif
#include "gist_unordered.h"

void
gist_predcursor_t::add(
    const void*		data,
    int 		len)
{
    assert(numElems < maxElems);
    elems[numElems].key = data;
    elems[numElems].keyLen = len;
    numElems++;
}

void
gist_predcursor_t::add(
    const gist_p&	page)
{
    int cnt = page.nrecs();
    assert(numElems + cnt <= maxElems);
    for (int i = 0; i < cnt; i++) {
        elems[numElems].key = (void *) page.rec(i).key();
        elems[numElems].keyLen = page.rec(i).klen();
	numElems++;
    }
}

gist_predcursor_t::~gist_predcursor_t()
{
}

gist_predcursor_t::gist_predcursor_t() : numElems(0)
{
}


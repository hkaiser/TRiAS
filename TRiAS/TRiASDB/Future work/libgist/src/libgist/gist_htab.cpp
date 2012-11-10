// gist_htab.cc
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_htab.cc,v 1.4 1998/06/18 00:54:26 aoki Exp $

#ifdef __GNUG__
#pragma implementation "gist_htab.h"
#endif

#include "gist_htab.h"

gist_htab::gist_htab()
{
    reset();
}

void
gist_htab::reset()
{
    for (int i = 0; i < GISTBUFS; i++) {
        tab[i].key = 0;
        tab[i].value = 0;
        tab[i].inUse = false;
    }
}

gist_htab::~gist_htab()
{
}

int
gist_htab::hash(shpid_t key)
{
    return key % GISTBUFS;
}

int
gist_htab::operator[](shpid_t page)
{
    int index = hash(page);
    int cnt = 0;

    while ((!tab[index].inUse || tab[index].key != page) && cnt < GISTBUFS) {
	index = (index + 1) % GISTBUFS;
        cnt++;
    }
    if (cnt == GISTBUFS) {
        return -1;
    } else {
        return tab[index].value;
    }
}

void
gist_htab::add(shpid_t key, int value)
{
    int index = hash(key);
    int cnt = 0;

    while (tab[index].inUse && cnt < GISTBUFS) {
        index = (index + 1) % GISTBUFS;
	cnt++;
    }
    assert(cnt != GISTBUFS);
    assert(!tab[index].inUse);
    tab[index].key = key;
    tab[index].value = value;
    tab[index].inUse = true;
}

void
gist_htab::remove(shpid_t key)
{
    int index = hash(key);
    int cnt = 0;

    while ((!tab[index].inUse || tab[index].key != key) && cnt < GISTBUFS) {
        index = (index + 1) % GISTBUFS;
	cnt++;
    }
    if (tab[index].key == key) {
        tab[index].inUse = false;
    }
}


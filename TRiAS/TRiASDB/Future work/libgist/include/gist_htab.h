// gist_htab.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_htab.h,v 1.5 1998/07/31 01:14:29 aoki Exp $

#ifdef __GNUG__
#pragma interface "gist_htab.h"
#endif

#ifndef GIST_HTAB_H
#define GIST_HTAB_H

#include "gist_defs.h"

class gist_htab {

public:

    gist_htab();
    ~gist_htab();

    void reset();
    int operator[](shpid_t page);
    void add(shpid_t key, int value);
    void remove(shpid_t key);

protected:
    
    struct entry {
        shpid_t key;
	int value;
	bool inUse;
    };

    entry tab[GISTBUFS];

    int hash(shpid_t key);
};

#endif // GIST_HTAB_H

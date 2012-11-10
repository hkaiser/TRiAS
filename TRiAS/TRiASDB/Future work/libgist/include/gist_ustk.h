// gist_ustk.h							-*- c++ -*-
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_ustk.h,v 1.5 1998/07/31 01:14:33 aoki Exp $


#ifndef GIST_USTK_H
#define GIST_USTK_H

#ifdef __GNUG__
#pragma interface "gist_ustk.h"
#endif

#include "gist_p.h"		// for gist_p

/*
 * gist_ustk_entry (update stack entry):
 *
 * Records a single page on the path to a leaf (with the page # and the index of the
 * item that was followed)
 */
struct gist_ustk_entry {
    gist_p page;
    int idx;
};

/*
 * gist_ustk (update stack)
 *
 * This stack is used during insert operations (theoretically also during delete, but
 * we don't contract the BPs yet). It records the path to the current node, with the 
 * root being at the bottom of the stack 
 */
class gist_ustk {
protected:
    enum { // MSVC 5.0 doesn't allow "const int ..." here
        max_ustk_sz = 10
    };

    gist_ustk_entry _stack[max_ustk_sz];
    int _top;

public:

    gist_ustk() : _top(0) {}
    ~gist_ustk();

    void push(const gist_p &page, int2 idx);

    // return entry n levels down from top of stack
    // (n = 0: top)
    gist_ustk_entry *top(int fromTop = 0);

    gist_ustk_entry *pop();

    bool is_full();
    bool is_empty();
    bool is_root(int fromTop);
    int size() { return _top; }
};

#endif

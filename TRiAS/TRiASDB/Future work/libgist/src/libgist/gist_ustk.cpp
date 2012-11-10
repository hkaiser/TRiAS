// gist_ustk.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_ustk.cc,v 1.4 1998/09/24 05:21:43 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_ustk.h"
#endif

#include "gist_ustk.h"

gist_ustk::~gist_ustk()
{
}

void 
gist_ustk::push(
    const gist_p&	page,
    int2 		idx)
{
    assert(_top < max_ustk_sz);
    _stack[_top].page = page;
    _stack[_top].idx = idx;
    _top++;
}

gist_ustk_entry *
gist_ustk::top(
    int 		fromTop)
{
    assert(_top - fromTop > 0);
    return (&_stack[_top-fromTop-1]);
}

gist_ustk_entry *
gist_ustk::pop()
{
    assert(_top > 0);
    _top--;
    return (&_stack[_top]);
}

bool
gist_ustk::is_full()
{
    return _top >= max_ustk_sz;
}

bool
gist_ustk::is_empty()
{
    return _top == 0;
}

bool
gist_ustk::is_root(int fromTop)
{
    return fromTop == _top - 1;
}


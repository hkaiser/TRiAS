//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// transform.h - useful transformation functions                           
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that this notice appears unmodified in all derivative
// works.
//
// The author makes no representations about the suitability of 
// this software for any purpose.  It is provided "as is" 
// without express or implied warranty.
//
// For more information about this software, refer to:
//
//   http://www.zeta.org.au/~jon/STL/views/doc/views.html
//
// Please send comments about this software to:
//
//   Jon Seymour (jon@zeta.org.au)
//

#ifndef _transform_h
#define _transform_h
#include <ospace/stl/function.h>
#include <ospace/stl/pair.h>
//
// identity
//
// A unary function that generates a reference to
// the argument
//

template <class T>
struct identity : unary_function<T, T> {
    T & operator()(T &t) const { return t; }
};

//
// pair_first 
//
// A transformation function that answers the first 
// member of a pair
//

template <class Key, class T>
   struct pair_first : unary_function<pair<Key, T>, Key>
{
   Key & operator()(pair<Key, T> &p) const { return (p.first); };
};

//
// pair_second
//
// A transformation function that answers the second
// member of a pair
//

template <class Key, class T>
   struct pair_second : unary_function<pair<Key, T>, T>
{
   T & operator()(pair<Key, T> &p) const { return (p.second); };
};
#endif

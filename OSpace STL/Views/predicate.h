//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// predicate.h - useful predicates                              
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

#ifndef _predicate_h
#define _predicate_h
#include <ospace/stl/function.h>
//
// unary_tautology
//
// A unary predicate that is always true.
//

template <class T>
   struct unary_tautology : unary_function<T, bool>
{
   bool operator()(T const &) const { return (true); }
};
#endif

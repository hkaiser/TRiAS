

// STL helper header.
// Copyright (c) 1994,1995 by ObjectSpace, Inc.  All rights reserved.
// Email: sales@objectspace.com

#ifndef EZ_STL_H
#define EZ_STL_H

#include <ospace/stl/algo.h>





// This header defines several "helper" algorithms that can be used
// with STL implementations.  The idea is to make some of the more
// common operations easier to use and less error prone.

// Permission is granted to anyone to use this software for any
// purpose on any computer system, and to redistribute it freely,
// as long as the ObjectSpace copyright is included in the source.
// There is no guarantee provided or implied for these algorithms.

// If your compiler has problems with the Container::size_type and
// Container::difference_type typedefs, try changing them to
// size_t and ptrdiff_t respectively.





// Forward declarations.

template< class T, class InputIterator >
void ez_find_value( InputIterator, InputIterator, const T&, T*& );

template< class T, class Predicate, class InputIterator >
void ez_find_predicate( InputIterator, InputIterator, Predicate, T*& );

template< class InputIterator, class T >
void ez_min_element_aux( InputIterator, InputIterator, T*& );

template< class InputIterator, class T >
void ez_max_element_aux( InputIterator, InputIterator, T*& );

template< class ForwardIterator >
void ez_release( ForwardIterator first, ForwardIterator last );





// Helper algos.

// SYNOPSIS
//    Locate an item in a sorted container.
// DESCRIPTION
//    Return `true` if `value` is in the container `c`.  This algorithm
//    assumes that the elements in the container are sorted using
//    `operator<()`.
// SEE ALSO
//    binary_search()

template< class Container, class T >
inline bool
ez_binary_search( const Container& c, const T& value )
  {
  return binary_search( c.begin(), c.end(), value );
  }





// SYNOPSIS
//    Count items in a container that match a particular value.
// DESCRIPTION
//    Return the number of elements in the container `c` that match
//    `value` using `operator==()`.
// SEE ALSO
//    count()

template< class Container, class T >
inline Container::size_type
ez_count( const Container& c, const T& value )
  {
  Container::size_type n = 0;
  count( c.begin(), c.end(), value, n );
  return n;
  }





// SYNOPSIS
//    Count items in a container that satisfy a predicate.
// DESCRIPTION
//    Return the number of elements in container `c` that cause
//    predicate `pred` to return `true`.
// SEE ALSO
//    count_if()

template< class Container, class Predicate >
inline Container::size_type
ez_count_if( const Container& c, Predicate pred )
  {
  Container::size_type n = 0;
  count_if( c.begin(), c.end(), pred, n );
  return n;
  }





// SYNOPSIS
//    Erase all matching items from a container.
// DESCRIPTION
//    Erase all occurrences of `t` from the container `c`.  Unlike `remove()`,
//    the size og the container decreases by the number of items that are
//    erased.
// SEE ALSO
//    erase(), remove()

template< class Container, class T >
inline void
ez_erase( Container& c, const T& t )
  {
  c.erase( remove( c.begin(), c.end(), t ), c.end() );
  }





// SYNOPSIS
//    Erase items from a container that satisfy a predicate.
// DESCRIPTION
//    Erase all elements that satisfy `pred` from the container `c`.  Unlike
//    `remove_if()`, the size og the container decreases by the number of
//    items that are erased.
// SEE ALSO
//    erase(), remove_if

template< class Container, class Predicate >
inline void
ez_erase_if( Container& c, Predicate pred )
  {
  c.erase( remove_if( c.begin(), c.end(), pred ), c.end() );
  }





// SYNOPSIS
//    Locate an item in a container.
// DESCRIPTION
//    Searches for an element in container `c` that matches `value` using
//    `operator==()`.  `result` is set to point to the first matching
//    element, or `0` if no match is found.
// SEE ALSO
//    find()

template< class Container, class T >
inline void
ez_find( Container& c, const T& value, T*& result )
  {
  ez_find_value( c.begin(), c.end(), value, result );
  }





// SYNOPSIS
//    Locate an item that satisfies a predicate in a container.
// DESCRIPTION
//    Set `result` to point to the first element in container `c`
//    that causes `pred` to evaulate to `true`, or `0` if no such
//    element exists.
// SEE ALSO
//    find_if()

template< class Container, class Predicate, class T >
inline void
ez_find_if( Container& c, Predicate pred, T*& result )
  {
  ez_find_predicate( c.begin(), c.end(), pred, result );
  }





// SYNOPSIS
//    Apply a function to every element in a container.
// DESCRIPTION
//    Apply `f` to every element in container `c` and return the
//    input parameter `f`.
// SEE ALSO
//    for_each()

template< class Container, class Function >
inline Function
ez_for_each( Container& c, Function f )
  {
  return for_each( c.begin(), c.end(), f );
  }





// SYNOPSIS
//    Searches for one container in another.
// DESCRIPTION
//    Return `true` if container `c1` is embedded in container `c2`.
//    This algorithm assumes that both sequences are sorted using
//    `operator<()`.
// SEE ALSO
//    includes()

template< class Container1, class Container2 >
inline bool
ez_includes( const Container1& c1, const Container2& c2 )
  {
  return includes( c1.begin(), c1.end(), c2.begin(), c2.end() );
  }





// SYNOPSIS
//    Searches for one container in another.
// DESCRIPTION
//    Return `true` if container `c1` is embedded in container `c2`.
//    This algorithm assumes that both sequences are sorted using
//    the comparitor `compare`.
// SEE ALSO
//    includes()

template< class Container1, class Container2, class Compare >
inline bool
ez_includes( const Container1& c1, const Container2& c2, Compare compare )
  {
  return includes( c1.begin(), c1.end(), c2.begin(), c2.end(), compare );
  }





// SYNOPSIS
//    Find the maximum element in a container.
// DESCRIPTION
//    Set `t` to point to the maximum valued element of container `c`,
//    or `0` if `c` is empty.
// SEE ALSO
//    max_element()

template< class Container, class T >
inline void
ez_max_element( Container& c, T*& t )
  {
  ez_max_element_aux( c.begin(), c.end(), t );
  }





// SYNOPSIS
//    Find the maximum element in a container.
// DESCRIPTION
//    Set `t` to maximum valued element of container `c` and return `true`,
//    or simply return `false` if `c` is empty.
// SEE ALSO
//    max_element()

template< class Container, class T >
inline bool
ez_max_element_value( Container& c, T& t )
  {
  T* e = 0;
  if ( !c.empty() )
    {
    ez_max_element_aux( c.begin(), c.end(), e );
    if ( e != 0 )
      t = *e;
    }
  return e != 0;
  }





// SYNOPSIS
//    Find the minimum element in a container.
// DESCRIPTION
//    Set `t` to point to the minimum valued element of container `c`,
//    or `0` if `c` is empty.
// SEE ALSO
//    min_element()

template< class Container, class T >
inline void
ez_min_element( Container& c, T*& t )
  {
  ez_min_element_aux( c.begin(), c.end(), t );
  }





// SYNOPSIS
//    Find the minimum element in a container.
// DESCRIPTION
//    Set `t` to minimum valued element of container `c` and return `true`,
//    or simply return `false` if `c` is empty.
// SEE ALSO
//    min_element()

template< class Container, class T >
inline bool
ez_min_element_value( Container& c, T& t )
  {
  T* e = 0;
  if ( !c.empty() )
    {
    ez_min_element_aux( c.begin(), c.end(), e );
    if ( e != 0 )
      t = *e;
    }
  return e != 0;
  }





// SYNOPSIS
//    Randomize the order of elements in a container.
// DESCRIPTION
//    Shuffle all elements in the container `c` using uniformly
//    selected random swaps.  Use `operator=()` to perform the swaps.
// SEE ALSO
//    random_shuffle()

template< class Container >
inline void
ez_random_shuffle( Container& c )
  {
  random_shuffle( c.begin(), c.end() );
  }





// SYNOPSIS
//    Delete a container consisting of heap-based objects.
// DESCRIPTION
//    Calls `operator delete()` on every item in the container `c`.
//    Assume that each item is a pointer to a unique heap-based object.
//    The values of the pointers do not change, only what they point do
//    changes.  `c` has the same number of elements after the call as it
//    does before.  This algorithm will have unpredictable results if
//    two elements point to the same object on the heap.

template< class Container >
inline void
ez_release( Container& c )
  {
  ez_release( c.begin(), c.end() );
  }





// SYNOPSIS
//    Replace a specified value in a sequence with another.
// DESCRIPTION
//    Replaces every occurrence of `old_value` in the container `c`
//    with `new_value`.
// SEE ALSO
//    replace()

template< class Container, class T >
inline void
ez_replace( Container& c, const T& old_value, const T& new_value )
  {
  replace( c.begin(), c.end(), old_value, new_value );
  }





// SYNOPSIS
//    Replace specified values in a container that satisfy a predicate.
// DESCRIPTION
//    Replaces every element in the container `c` that causes `pred`
//    to evaluate to `true` with `new_value`.
// SEE ALSO
//    replace_if()

template< class Container, class Predicate, class T >
inline void
ez_replace_if( Container& c, Predicate pred, const T& new_value )
  {
  replace_if( c.begin(), c.end(), pred, new_value );
  }





// SYNOPSIS
//    Rotate a sequence.
// DESCRIPTION
//    If `n` is positive, rotate the container to the left by `n`
//    positions; otherwise, rotate the container to the right by `n`
//    positions.
// SEE ALSO
//    rotate()

template< class Container >
inline void
ez_rotate( Container& c, Container::difference_type n )
  {
  Container::size_type size = c.size();
  if ( n < 0 )
    n = size - ( -n % size );
  else
    n %= size;
  Container::iterator midpoint = c.begin();
  advance( midpoint, n );
  rotate( c.begin(), midpoint, c.end() );
  }





// SYNOPSIS
//    Sort a sequence.
// DESCRIPTION
//    Sort all elements in the container `c` using `operator<()` to
//    compare values.
// SEE ALSO
//    sort()

template< class Container >
inline void
ez_sort( Container& c )
  {
  sort( c.begin(), c.end() );
  }





// SYNOPSIS
//    Sort a sequence.
// DESCRIPTION
//    Sort all elements in the container `c` using `compare` to
//    compare values.
// SEE ALSO
//    sort()

template< class Container, class Compare >
inline void
ez_sort( Container& c, Compare compare )
  {
  sort( c.begin(), c.end(), compare );
  }





// Non-inlined helpers.

// SYNOPSIS
//    Locate an item in a container.
// DESCRIPTION
//    Searches for the first element in the range [`first`..`last`) that
//    matches `value` using `operator==()`.  `result` is set to point to
//    the first matching element, or `0` if no match is found.
// SEE ALSO
//    find()

template< class T, class InputIterator >
void ez_find_value
  (
  InputIterator first,
  InputIterator last,
  const T& value,
  T*& result
  )
  {
  first = find( first, last, value );
  if ( first != last )
    result = &*first;
  else
    result = 0;
  }





// SYNOPSIS
//    Locate an item in a container.
// DESCRIPTION
//    Searches for the first element in the range [`first`..`last`) that
//    matches `value` using `pred`.  `result` is set to point to
//    the first matching element, or `0` if no match is found.
// SEE ALSO
//    find_if()

template< class T, class Predicate, class InputIterator >
void ez_find_predicate
  (
  InputIterator first,
  InputIterator last,
  Predicate pred,
  T*& result
  )
  {
  first = find_if( first, last, pred );
  if ( first != last )
    result = &*first;
  else
    result = 0;
  }





// SYNOPSIS
//    Find the minimum element in a container.
// DESCRIPTION
//    Set `t` to point to the minimum valued element of the range
//    [`first`..`last) or `0` if `c` is empty.
// SEE ALSO
//    min_element()

template< class InputIterator, class T >
void ez_min_element_aux( InputIterator first, InputIterator last, T*& t )
  {
  t = 0;
  InputIterator result = min_element( first, last );
  if ( result != last )
    t = &*result;
  }





// SYNOPSIS
//    Find the maximum element in a container.
// DESCRIPTION
//    Set `t` to point to the maximum valued element of the range
//    [`first`..`last) or `0` if `c` is empty.
// SEE ALSO
//    max_element()

template< class InputIterator, class T >
void ez_max_element_aux( InputIterator first, InputIterator last, T*& t )
  {
  t = 0;
  InputIterator result = max_element( first, last );
  if ( result != last )
    t = &*result;
  }





// SYNOPSIS
//    Delete a range of heap-based objects.
// DESCRIPTION
//    Calls `operator delete()` on every item in the range [`first`..`last`).
//    Assume that each item is a pointer to a unique heap-based object.
//    The values of the pointers do not change, only what they point do
//    changes.  This algorithm will have unpredictable results if two
//    elements point to the same object on the heap.

template< class ForwardIterator >
void
ez_release( ForwardIterator first, ForwardIterator last )
  {
  while ( first != last )
    {
    delete *first;
    ++first;
    }
  }
#endif

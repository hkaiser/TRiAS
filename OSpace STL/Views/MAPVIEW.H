//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// mapview.h - support for views over maps
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

#ifndef _mapview_h
#define _mapview_h

#include <ospace\views\view.h>
#include <ospace\views\predicate.h>
#include <ospace\views\transform.h>

//
// map_keys
//
// A transforming view that defines an abstract container
// containing the keys in a map.
//

template <class Key, class T, class Compare>
    struct map_keys : public view<const Key,
                                  map<Key, T, Compare>,
                                  unary_tautology< pair<Key, T> >,
                                  pair_first<Key, T> >
{
    typedef view<const Key,
                 map<Key, T, Compare>,
                 unary_tautology< pair<Key, T> >,
                 pair_first<Key, T> > super;
	typedef super::domain_t domain_t;
	typedef super::domain_iterator_t domain_iterator_t;

    map_keys(domain_t &domain) 
      : super(domain, predicate_t(), transform_t()) {};
    map_keys(domain_t &domain, domain_iterator_t begin_it, domain_iterator_t end_it) 
      : super(domain, predicate_t(), transform_t(), begin_it, end_it) {};
};

//
// map_values
//
// A transforming view that defines an abstract container
// containing the values in a map.
//

template <class Key, class T, class Compare>
    struct map_values : public view<T,
                                    map<Key, T, Compare>,
                                    unary_tautology< pair<Key, T> >,
                                    pair_second<Key, T> >
{
    typedef view<T,
                 map<Key, T, Compare>,
                 unary_tautology< pair<Key, T> >,
                 pair_second<Key, T> > super;
	typedef super::domain_t domain_t;
	typedef super:: domain_iterator_t domain_iterator_t;

    map_values(domain_t &domain) 
      : super(domain, predicate_t(), transform_t()) {};
    map_values(domain_t &domain, domain_iterator_t begin_it, domain_iterator_t end_it) 
      : super(domain, predicate_t(), transform_t(), begin_it, end_it) {};
};

//
// multimap_keys
//
// A transforming view that defines an abstract container
// containing the keys in a multimap.
//

template <class Key, class T, class Compare>
    struct multimap_keys : public view<const Key,
                                  multimap<Key, T, Compare>,
                                  unary_tautology< pair<Key, T> >,
                                  pair_first<Key, T> >
{
    typedef view<const Key,
                 multimap<Key, T, Compare>,
                 unary_tautology< pair<Key, T> >,
                 pair_first<Key, T> > super;
	typedef super::domain_t domain_t;
	typedef super::domain_iterator_t domain_iterator_t;

    multimap_keys(domain_t &domain) 
      : super(domain, predicate_t(), transform_t()) {};
    multimap_keys(domain_t &domain, domain_iterator_t begin_it, domain_iterator_t end_it) 
      : super(domain, predicate_t(), transform_t(), begin_it, end_it) {};
};

//
// multimap_values
//
// A transforming view that defines an abstract container
// containing the values in a map.
//

template <class Key, class T, class Compare>
    struct multimap_values : public view<T,
                                    multimap<Key, T, Compare>,
                                    unary_tautology< pair<Key, T> >,
                                    pair_second<Key, T> >
{
    typedef view<T,
                 multimap<Key, T, Compare>,
                 unary_tautology< pair<Key, T> >,
                 pair_second<Key, T> > super;
	typedef super::domain_t domain_t;
	typedef super::domain_iterator_t domain_iterator_t;
	
    multimap_values(domain_t &domain) 
      : super(domain, predicate_t(), transform_t()) {};
    multimap_values(domain_t &domain, domain_iterator_t begin_it, domain_iterator_t end_it) 
      : super(domain, predicate_t(), transform_t(), begin_it, end_it) {};
};

#endif


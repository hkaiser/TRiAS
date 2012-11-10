//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// domain.h - domain templates                               
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

//
// CHANGES
//
// 1.0  951230 js - initial version (jon seymour)
// 2.0  960106 js - reworked based on view changes
//

#ifndef _domain_h 
#define _domain_h 

#include <ospace\views\view.h>
#include <ospace\views\transform.h>

//
// scalar_domain
//
// Defines a scalar domain. That is, a domain of a scalar type
// that is delimited by two scalar values.
//

template <class T> class scalar_domain
{
   typedef scalar_domain<T> self;

   T const & lower;
   T const & upper;

public:
   typedef T value_type;
   typedef T &reference;

   class iterator {

   protected:
      T val;

      iterator(T const &t) : val(t) {};

      friend class scalar_domain<T>;

   public:

      iterator() {};

      iterator &operator++() {
         ++val;
         return (*this);
      }

      iterator operator++(int) {
         iterator tmp(val);
         ++val;
         return (tmp);
      }

      iterator &operator--() {
         --val;
         return (*this);
      }

      iterator operator--(int) {
         iterator tmp(val);
         --val;
         return (tmp);
      }

      T &operator*() {
         return (val);
      }

      bool operator==(iterator const &other) const {

         return (val == other.val);

      }

      bool operator!=(iterator const &other) const {

         return !(val == other.val);

      }

   };

   iterator begin() {
      return iterator(lower);
   }

   iterator end() {
      T tmp(upper);
      return iterator(++tmp);
   }

   scalar_domain(T const &l, T const &u) : upper(u), lower(l) {}
};

typedef scalar_domain<int>  int_domain;
typedef scalar_domain<char> char_domain;


//
// subrange_domain
//
// A domain formed by the range of iterators 
// between begin and end.
//

template <class T, class Iterator> 
   class subrange_domain 
{
public:
   typedef Iterator    iterator;
   typedef T           value_type;
   typedef T &         reference;

protected:
   iterator _begin;
   iterator _end;

public:
   iterator begin() { return _begin; };
   iterator end()   { return _end;   };

   subrange_domain(iterator const &b, iterator const &e)
      : _begin(b), _end(e) {}
};

//
// subdomain
//
// A view of a domain in which the transformation function is 
// implemented with the identity function.
//
// A domain can be any STL container that supports a bidirectional iterator.
//

template <class Domain, class Predicate> 
   class subdomain : public  view<Domain::value_type,
                                  Domain, 
                                  Predicate, 
                                  identity<Domain::value_type> >
{
    typedef view<Domain::value_type, 
                 Domain, 
                 Predicate, 
                 identity<Domain::value_type> > super;

public:

   subdomain(domain_t &domain, predicate_t const &predicate) 
     : super(domain, predicate, transform_t()) {}
};



#endif


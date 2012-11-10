//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// view.h - view templates                               
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
// 2.0  960104 js - introduced view and subdomain templates
//                  (moved most iterator function from filterit.h)
//

#ifndef _view_h
#define _view_h 

//
// view
//
// Represents a view formed by applying a filtering predicate and 
// transformation function to the elements of a domain.
//

template <class T, class Domain, class Predicate, class Transform> 
class view;

template <class T, class Domain, class Predicate, class Transform> 
class view_iterator 
{
	typedef class view<T, Domain, Predicate, Transform> view_t;
	friend class  view<T, Domain, Predicate, Transform>;

protected:
	typedef view_iterator				self;
	typedef view_t::domain_iterator_t	domain_iterator_t;
	typedef view_t::transform_t			transform_t;
	typedef view_t::reference			reference; 


	view_t								*view;
	view_t::domain_iterator_t			iter;
  

//
// The invariant of the view iterator is:
//
//    (*iter == view->domain().end()) || view->predicate()(*iter)
//

//
// adjust_forward()
//
// Re-establish the iterator's invariant by moving it
// forwards (if necessary).
//
	void adjust_forward() {
		while ( iter != view->domain().end() && !view->predicate()(*iter) )
		++iter;
	};

//
// adjust_back()
//
// Re-establish the iterator's invariant by moving it
// backwards (if necessary).
//
// Since there is no guarantee that there is an
// element in the domain between the present position
// and the beginning of the domain that satisfies the
// invariant it is necessary to apply adjust_forward()
// which is guaranteed to always establish the invariant.
//
	void adjust_back() {
		while ( iter != view->domain().begin() && !view->predicate()(*iter) )
			--iter;

		adjust_forward();
	};

	view_iterator (view_t &v, domain_iterator_t const &i)
		: view(&v), iter(i) { adjust_forward(); }

public:
	view_iterator (void) : view(0) {}

//
// reference operator*()
//
	reference &operator*() { return (view->transform())(*iter); }
	domain_iterator_t domain_iterator() { return (iter); }

public:   
	self& operator++() {
		++iter;
		adjust_forward();
		return(*this);
	};

	self operator++(int) {
	self tmp(*this);

		++(*this);
		return(tmp);
	};

	self & operator--() {
		--iter;
		adjust_back();
		return(*this);
	};

	self operator--(int) {
	self tmp(*this);

		--(*this);
		return(tmp);
	};

//
// iterator == iterator
//
// Two view iterators are equal if their 
// domain iterators are equal
//
	bool operator==(self const &comparand) const 
	{
		return (iter == comparand.iter);
	};

//
// view iterator == domain iterator
//
// A view iterator is equivalent to a domain
// iterator if its own domain iterator is equal
// to the comparand.
//
	bool operator==(domain_iterator_t const &comparand)
	{
		return (iter == comparand);
	}

	bool operator!=(domain_iterator_t const &comparand)
	{
		return !(iter == comparand);
	}
};

template <class T, class Domain, class Predicate, class Transform> 
   class view 
{
public:

	typedef Domain                 domain_t;
	typedef Predicate              predicate_t;
	typedef Transform              transform_t;
	typedef Transform::result_type reference;

	typedef T                      value_type;

	typedef domain_t::iterator     domain_iterator_t;

	typedef view<T, Domain, Predicate, Transform> self;
	typedef view_iterator<T, Domain, Predicate, Transform> iterator;

protected:
	domain_t      &_domain;
	transform_t    _transform;
	predicate_t    _predicate;
	domain_iterator_t _begin_it;
	domain_iterator_t _end_it;

public:
	iterator begin() { return iterator(*this, _begin_it); }
	iterator end()	{ return iterator(*this, _end_it); }

	domain_t    &domain()    { return _domain;    }
	transform_t &transform() { return _transform; }
	predicate_t &predicate() { return _predicate; }

	view (domain_t &domain, predicate_t const &predicate, transform_t const &transform) :
		_domain(domain), _predicate(predicate), _transform(transform), 
		_begin_it(domain.begin()), _end_it(domain.end())
	{};
	
	view (domain_t &domain, predicate_t const &predicate, transform_t const &transform, domain_iterator_t begin_it, domain_iterator_t end_it) :
		_domain(domain), _predicate(predicate), _transform(transform), 
		_begin_it(begin_it), _end_it(end_it)
	{};
};

#endif

/*
 *
 * Copyright (c) 1997
 * Infomedia Ed.
 *
 * www.infomedia.it
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Infomedia Ed. makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
    Any comment, suggestion and bug report should be addressed to:
    Graziano Lo Russo, lorusso@programmers.it
    I do not guarantee that I will fix it - but I will try!

   	Warning: I do not claim that this software is in any way useful.
    DISCLAIMER:
    Trying to figure out how this software works can seriously damage your brain.
*/
/*
	File: mathops.h
	A bunch of useful (I hope), basic mathematical generic functions.
	Tested with BC++ 5.0 on Win/NT and with SPARC C++ 4.0.1
	on Solaris 2.5.

==================================================================

    T average(Iterator first, Iterator last, T t0)
    T average(Iterator first, Iterator last, T t0, UnaryOperation operation)
    Calculates the generic average of a sequence; defaults
    to arithmetic average. Heavily optimized.
    
==================================================================
	T sqr(T x) -> x^2 (what else?)
	
==================================================================
	void series(OutputIterator begin, OutputIterator end,
	const T& init, UnaryOperation unOp):
	
    fills: *begin = init; than *<position ith>=
    unOp(*<position (i-1)th>)
    Similar to partial_sum but lets specify initial value.
	
==================================================================
	void binomdst(OutputIterator begin, OutputIterator end,
		double p, double nElem)
	evaluates the Poisson distribution P(k) k=[0..nElem] (heavily optimized)
		
==================================================================

	class SD : function object to calculate the standard
	deviation. See a use example in the following:
	
==================================================================
	averages_t averages(FwdIterator begin,
		FwdIterator end)
	fills a structure with average and SD of a sequence
==================================================================

	GLR
*/
#ifndef __MATHOPS_H
#define __MATHOPS_H

#include <math.h>

#include <ospace/stl/algo.h>
#define __STL_NAME(x)	x

template < class RandomIterator, class T, class UnaryOperation, class Distance >
T _average1(RandomIterator first, RandomIterator last, T t0,
	UnaryOperation operation, Distance * )
{
	Distance n=0;
	distance(first, last, n );
	for (; first != last; )
	{
		t0= t0 + operation(*first++);
	}
	return t0/n;
}

template < class InputIterator, class T, class UnaryOperation, class Distance>
T _average2(InputIterator first, InputIterator last, T t0,
	UnaryOperation operation, Distance *)
{
	Distance n=0;
	for (; first != last; n++)
		t0= t0 + operation(*first++);
	return t0/n;
}

template < class RandomIterator, class T, class Distance >
T _average1(RandomIterator first, RandomIterator last, T t0, Distance * )
{
	Distance n=0;
	distance(first, last, n );
	t0= t0+ accumulate(first, last, t0);
	return t0/n;
}

template < class InputIterator, class T, class Distance>
T _average2(InputIterator first, InputIterator last, T t0, Distance *)
{
	Distance n=0;
	for (; first != last; n++)
		t0= t0+ *first++;
	return t0/ n;
}

///////////////////////////////////////////////////////////////

template < class RandomIterator, class T , class UnaryOperation, class Distance >
inline T _average(RandomIterator first, RandomIterator last,
	T  t0, UnaryOperation operation , Distance * d,
    __STL_NAME(random_access_iterator_tag))
{
	return _average1(first, last, t0, operation, d);
}
template < class InputIterator, class T, class UnaryOperation, class Distance >
inline T _average(InputIterator first, InputIterator last,
	T  t0, UnaryOperation operation, Distance * d, __STL_NAME(input_iterator_tag))
{
	return _average2(first, last, t0, operation, d);
}

template < class ForwardIterator, class T, class UnaryOperation, class Distance >
inline T _average(ForwardIterator first, ForwardIterator last,
	T  t0, UnaryOperation operation, Distance * d,
    __STL_NAME(forward_iterator_tag))
{
	return _average2(first, last, t0, operation, d);
}

template < class BidIterator, class T, class UnaryOperation, class Distance >
inline T _average(BidIterator first, BidIterator last,
	T  t0, UnaryOperation operation, Distance * d,
    __STL_NAME(bidirectional_iterator_tag))
{
	return _average2(first, last, t0, operation, d);
}

template < class RandomIterator, class T, class Distance >
inline T _average(RandomIterator first, RandomIterator last,
	T  t0, Distance * d, __STL_NAME(random_access_iterator_tag))
{
	return _average1(first, last, t0, d);
}
template < class InputIterator, class T, class Distance >
inline T _average(InputIterator first, InputIterator last,
	T  t0, Distance * d, __STL_NAME(input_iterator_tag))
{
	return _average2(first, last, t0, d);
}

template < class ForwardIterator, class T, class Distance >
inline T _average(ForwardIterator first, ForwardIterator last,
	T t0, Distance * d, __STL_NAME(forward_iterator_tag))
{
	return _average2(first, last, t0, d));
}

template < class BidIterator, class T, class Distance >
inline T _average(BidIterator first, BidIterator last,
	T t0, Distance * d, __STL_NAME(bidirectional_iterator_tag))
{
	return _average2(first, last, t0, d);
}

////////////////////////////////////////////////////////////////////

template < class Iterator, class T, class UnaryOperation >
inline T average(Iterator first, Iterator last, T t0, UnaryOperation operation)
{
	return _average(first, last, t0, operation,
		distance_type(first), iterator_category(first));
}

template < class Iterator, class T>
inline T average(Iterator first, Iterator last, T t0)
{
	return _average(first, last, t0,
		distance_type(first), iterator_category(first));
}

//==================================================================
template <class OutputIterator, class T, class UnaryOperation>
void series(OutputIterator begin, OutputIterator end,
	T init, UnaryOperation unOp)
{
	if (begin == end)
		return;
	*begin = init;
	while (++ begin != end)
	{
		init = unOp(init);
		*begin= init;
	}
}


//==================================================================

template <class OutputIterator>
void binomdst(OutputIterator begin, OutputIterator end,
	double p, double nElem)
{
	class Binomdst {
		double m_pbar;
		double m_n1; // n+1
		double m_i;
	public:
		Binomdst(double p, int nElem):
			m_pbar(p/(1-p)), m_n1(nElem+1),
			m_i(0){}
		double operator()(double dPrev)
		{return dPrev*(--m_n1)*m_pbar/++m_i;}
	} ;

	series(begin, end, pow(1-p, nElem),
		Binomdst(p, nElem));
}

//==================================================================
template <class T>
inline T sqr(T x)
{return x*x;}

template <class T>
class SD {
  T m_ave;
public:
  SD(T ave): m_ave(ave) {}
  T operator()(T x) {return sqr(x-m_ave);}
};


//==================================================================
struct averages_t {
	double ave, sd;
};

template <class FwdIterator>
averages_t averages(FwdIterator begin,
	FwdIterator end)
{
  averages_t ave;
  ave.ave= average(begin, end, double(0));
  ave.sd = sqrt(average(begin, end, double(0), SD<double>(ave.ave)));
  return ave;
}

#endif
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
	File: Slist.h
	A STL compatible singly linked list
	Rationale: this is a minimum footprint singly linked
	list; the overhead is only 1 pointer/node + 1
	pointer/list. It is suited as bucket in hash tables or
	similar things.
    Compare this with the 2 pointer/node + 2 pointer+1
    int/list overhead of standard	STL lists.
    All STL list's functions are supported with the
    following exceptions:
    1) Slist's iterators are forward iterators, not bid.
    iterators;
    2) only LIFO (stack) access is supported; push_back() and
    pop_back() are NOT supported
    3) size() is not supported (because it would have been
    impossible to implement it with linear complexity); use
    the count() algorithm if you need.
    Still, empty() is supported.
    4) for the same reason, the splice() family is not supported
    5) insert() and erase() ARE supported with the usual STL meaning.

    Supporting insert() and erase() with STL semantics on a singly
    linked list has been rather tricky. This is resson why
    Slist's iterators are pointer-to-pointer-to nodes
    instead of simple pointer-to nodes. In turns, this
    determined the unusual representation of the end()
    iterator: a pointer to a statically allocated null pointer.

    The interface is consistent with main stlport conventions.
    Tested with BC++ 5.0 on NT machine.

	GLR
*/
#ifndef __Slist_H
#define __Slist_H


#include <stdlib.h>
#include <iterator.h>

__BEGIN_STL_NAMESPACE
__BEGIN_STL_FULL_NAMESPACE

#  define  Slist  __WORKAROUND_RENAME(Slist)


template <class T, __DFL_TYPE_PARAM(Alloc,alloc) >
class Slist {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
protected :

	struct Item {
		Item *pNext ;
		T data ;
		Item(Item* _pNext, const T& _data):
		pNext(_pNext), data(_data) {}
		void * operator new(size_t );
		void operator delete(void *pv);
	}* m_pFirst;
	friend struct Item;
    typedef simple_alloc<Item, Alloc> item_allocator;
public :

	class const_iterator:
	public forward_iterator<T, ptrdiff_t> {
		typedef Item* node_p;
		const node_p* m_ppNode ;
		friend class Slist<T, alloc> ;
	public :
		const_iterator(const node_p * ppNode)
			: m_ppNode(ppNode) {}
		const_iterator();
		const_iterator& operator++() {
			m_ppNode= &((*m_ppNode)->pNext) ;
			return *this ;}
		const_iterator operator++(int){
			const_iterator it= *this ;
			m_ppNode= &((*m_ppNode)->pNext) ;
			return it ;}
		const T& operator*() const
			{return (*m_ppNode)->data;}
		bool operator==(const const_iterator& it) const
			{ return *m_ppNode == *it.m_ppNode ;}
	} ;

	class iterator :
	public forward_iterator<T, ptrdiff_t> {
		Item** m_ppNode ;
		friend class Slist<T, alloc> ;
public :
		iterator(Item** ppNode) :
			m_ppNode(ppNode) {}
		iterator() ;
		iterator& operator++() {
			m_ppNode= &((*m_ppNode)->pNext) ;
			return *this ;}
		iterator operator++(int){
			iterator it= *this ;
			m_ppNode= &((*m_ppNode)->pNext) ;
			return it ;}
		T& operator*() {return (*m_ppNode)->data;}
		bool operator==(const iterator& it) const
			{ return *m_ppNode == *it.m_ppNode ;}
		operator const_iterator() const
			{return const_iterator(m_ppNode);}
	} ;

	void operator=(const Slist&);

	Slist() : m_pFirst(0) { }
	Slist(const Slist& l) : m_pFirst(0)
		{*this = l ;}
	Slist(size_type n, const T& value )
		: m_pFirst(0)
	{insert(begin(), n, value);}
	Slist(size_type n)
		: m_pFirst(0)
	{T value; insert(begin(), n, value);}
	Slist(const T* first, const T* last)
		: m_pFirst(0)
	{insert(begin(), first, last);}
    Slist(const_iterator first, const_iterator last) 
	{insert(begin(), first, last);}


	T& front() {return m_pFirst->data ;}
	const T& front() const {return m_pFirst->data ;}
	bool empty() {return m_pFirst == 0 ;}

	iterator begin() {return iterator(&m_pFirst) ;}
	iterator end() {return iterator();}
	const_iterator begin() const
		{return const_iterator(&m_pFirst) ;}
	const_iterator end() const {return const_iterator();}


	void erase(iterator i)
	{
		Item * tmp= *i.m_ppNode ;
		*i.m_ppNode= tmp->pNext ;
		delete tmp ;
	}
	void erase(iterator first, iterator last);

	iterator insert(iterator i, const T& x)
	{
		*i.m_ppNode= new Item(*i.m_ppNode, x) ;
		return i ;
	}
	void insert(iterator position, const_iterator first,
		const_iterator last);
	void insert(iterator position, const T* first, const T* last);
	void insert(iterator position, size_type n, const T& x);
	void swap(Slist& x) {
		__STL_NAME(swap)(m_pFirst, x.m_pFirst);
	}
	void push_front(const T& data)
		{ insert(begin(), data);}
	T pop_front()
		{T ret= *begin(); erase(begin()); return ret;}
	~Slist()
		{erase(begin(), end());}
} ;

template <class T, class Alloc>
inline void* Slist<T, Alloc>::Item::operator new(size_t)
{
	return item_allocator::allocate();
}

template <class T, class Alloc>
inline void Slist<T, Alloc>::Item::operator delete(void *pv)
{
	item_allocator::deallocate((Item*)pv);
}

template <class T, class Alloc>
inline Slist<T, Alloc>::iterator::iterator()
{
	static Item * nul= 0 ;
	m_ppNode= &nul ;
}

template <class T, class Alloc>
inline Slist<T, Alloc>::const_iterator::const_iterator()
{
	static Item * nul= 0 ;
	m_ppNode= &nul ;
}

template <class T, class Alloc>
void Slist<T, Alloc>::erase(iterator first, iterator last) {
	while (first != last) erase(first);
}


template <class T, class Alloc>
void Slist<T, Alloc>::insert(iterator position, const_iterator first,
		const_iterator last)
{
	while (first != last)
	{
		insert(position, *first++);
		++position;
	}
}

template <class T, class Alloc>
void Slist<T, Alloc>::insert(iterator position,
	const T* first, const T* last)
{
	while (first != last)
	{
		insert(position, *first++);
		++position;
	}
}
template <class T, class Alloc>
void Slist<T, Alloc>::insert(iterator position, size_type n, const T& x)
{
	for (;n;--n )
		insert(position, x);
}
template <class T, class Alloc>
void Slist<T, Alloc>::operator=(const Slist& l)
{
	if (this != &l) {
		erase(begin(), end());
		insert(begin(), l.begin(), l.end());
	}
}
template <class T, class Alloc>
inline bool operator<(const Slist<T, Alloc>& x,
	const Slist<T, Alloc>& y)
{
	    return lexicographical_compare
		(x.begin(), x.end(), y.begin(), y.end());
}

template <class T, class Alloc>
bool operator==(const Slist<T, Alloc>& x,
	const Slist<T, Alloc>& y) {
	Slist2<T, Alloc>::iterator i1= x.begin() ;
	Slist2<T, Alloc>::iterator i2= y.begin() ;
	for ( ; i1 != x.end() && i2 != y.end() ;)
		if (*i1 != *i2) return false ;
		else { ++i1 ; ++i2 ;}
	return i1 == x.end() && i2 == y.end() ;
}

# undef Slist
#  define __Slist__ __FULL_NAME(Slist)
__END_STL_FULL_NAMESPACE

# if !defined ( __STL_DEFAULT_TYPE_PARAM )
// provide a "default" Slist adaptor
template <class T>
class Slist : public __Slist__<T,alloc>
{
    typedef Slist<T> self;
public:
    typedef __Slist__<T,alloc> super;
    __CONTAINER_SUPER_TYPEDEFS
    __IMPORT_SUPER_COPY_ASSIGNMENT(Slist)
    Slist() { }
    explicit Slist(size_type n, const T& value) : super(n, value) { }
    explicit Slist(size_type n) :  super(n) { } 
    Slist(const T* first, const T* last) : super(first, last) { } 
    Slist(const_iterator first, const_iterator last) : super(first, last) { }
};

#  if defined (__STL_BASE_MATCH_BUG)
template <class T>
inline bool operator==(const Slist<T>& x, const Slist<T>& y) {
    typedef typename Slist<T>::super super;
    return operator == ((const super&)x,(const super&)y);
}

template <class T>
inline bool operator<(const Slist<T>& x, const Slist<T>& y) {
    typedef typename Slist<T>::super super;
    return operator < ((const super&)x,(const super&)y);
}
#  endif

template <class T, class Alloc>
inline bool operator==(const __Slist__<T, Alloc>& x, const __Slist__<T, Alloc>& y) {
    return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc>
inline bool operator<(const __Slist__<T, Alloc>& x, const __Slist__<T, Alloc>& y) {
    return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

# endif /*  __STL_DEFAULT_TEMPLATE_PARAM */

__END_STL_NAMESPACE

#endif

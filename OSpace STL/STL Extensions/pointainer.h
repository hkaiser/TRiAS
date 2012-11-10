/*
 * pointainer - auto-cleaning container of pointers
 *
 * Example usage:
 * {
 *     pointainer< std::vector<int*> > v;
 *     // v can be manipulated like any std::vector<int*>.
 *
 *     v.push_back(new int(42));
 *     v.push_back(new int(17));
 *     // v now owns the allocated int-s
 *
 *     v.erase(v.begin());
 *     // frees the memory allocated for the int 42, and then removes the
 *     // first element of v.
 * }
 * // v's destructor is called, and it frees the memory allocated for
 * // the int 17.
 *
 * Notes:
 * 1. Assumes all elements are unique (you don't have two elements
 *    pointing to the same object, otherwise you might delete it twice).
 * 2. Not usable with pair associative containers (map and multimap).
 * 3. For ANSI-challenged compilers, you may want to #define
 *    NO_MEMBER_TEMPLATES.
 *
 * Now supports even associative containers: pointainer<map<...>, clean_pair_second<map<...> >
 *
 * Written 10-Jan-1999 by Yonat Sharon <yonat@usa.net>
 * Last updated 07-Feb-1999
 */

#ifndef POINTAINER_H
#define POINTAINER_H

#ifdef NO_MEMBER_TEMPLATES
#include <ospace/std/functional> // for binder2nd
#endif

///////////////////////////////////////////////////////////////////////////////
// trait classes for cleaning up for different containertypes
template<typename Cnt>
struct clean_list : 
	public os_unary_function<Cnt::iterator, bool>
{
	bool operator() (Cnt::iterator it) { delete (*it); return true; }
};

template<typename Cnt>
struct clean_pair_second : 
	public os_unary_function<Cnt::iterator, bool>
{
	bool operator() (Cnt::iterator it) { delete (*it).second; return true; }
};

///////////////////////////////////////////////////////////////////////////////
// wrapper class
template<typename Cnt, typename cleanpred = clean_list<Cnt> >
class pointainer : public Cnt
{
public:
    using typename Cnt::size_type;
    using typename Cnt::difference_type;
    using typename Cnt::reference;
    using typename Cnt::const_reference;
    using typename Cnt::value_type;
    using typename Cnt::iterator;
    using typename Cnt::const_iterator;
    using typename Cnt::reverse_iterator;
    using typename Cnt::const_reverse_iterator;
    typedef pointainer<Cnt, cleanpred> its_type;

    pointainer()                            {}
    pointainer(const Cnt& c)                : Cnt(c) {}
    its_type& operator=(const Cnt& c)       {Cnt::operator=(c); return *this;}
    ~pointainer()                           {clean_all();}

    void clear()                            {clean_all(); Cnt::clear();}
    iterator erase(iterator i)       
	{
		iterator it = i;
		++it;
		clean(i); 
		Cnt::erase(i); 
		return it;
	}
    iterator erase(iterator f, iterator l)  {clean(f,l); return Cnt::erase(f,l);}

    // for associative containers: erase() a value
    size_type erase(const value_type& v)
    {
        iterator i = find(v);
        size_type found(i != end()); // can't have more than 1
        if (found)
            erase(i);
        return found;
    }

    // for sequence containers: pop_front(), pop_back(), resize() and assign()
    void pop_front()    {clean(begin()); Cnt::pop_front();}
    void pop_back()     {iterator i(end()); clean(--i); Cnt::pop_back();}
    void resize(size_type s, value_type c = value_type())
    {
        if (s < size())
            clean(begin()+s, end());
        Cnt::resize(s, c);
    }
#ifndef NO_MEMBER_TEMPLATES
    template <class InIter> void assign(InIter f, InIter l)
#else
    void assign(iterator f, iterator l)
#endif
    {
        clean_all();
        Cnt::assign(f,l);
    }
#ifndef NO_MEMBER_TEMPLATES
    template <class Size, class T> void assign(Size n, const T& t = T())
#else
    void assign(size_t n, const value_type& t = value_type())
#endif
    {
        clean_all();
        Cnt::assign(n,t);
    }
    
    // for std::list: remove() and remove_if()
    void remove(const value_type& v)
    {
        clean( std::find(begin(), end(), v) );
        Cnt::remove(v);
    }
#ifndef NO_MEMBER_TEMPLATES
    template <class Pred>
#else
    typedef std::binder2nd<std::not_equal_to<value_type> > Pred;
#endif
    void remove_if(Pred pr)
    {
        for (iterator i = begin(); i != end(); ++i)
            if (pr(*i))
                clean(i);
        Cnt::remove_if(pr);
    }

private:
    void clean(iterator i)                  {cleanpred()(i);}
    void clean(iterator f, iterator l)      {while (f != l) clean(f++);}
    void clean_all()                        {clean( begin(), end() );}

    // we can't have two pointainers own the same objects:
    pointainer(const its_type&) {}
    its_type& operator=(const its_type&) {}
};

#endif // POINTAINER_H

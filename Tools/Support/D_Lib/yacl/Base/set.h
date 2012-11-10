

#ifndef _set_h_
#define _set_h_





/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */



// Set is a class template that  maintains   a  set of objects of type
// BaseType. Duplicate objects  are, of course,  not allowed.  The Set
// allows addition and removal of objects and membership tests.
// 
// The implementation performs all  BaseType-related operations via
// the Basics class template (see {\tt base/basicops.h}. The Set template
// assumes that (a) the default constructor for the BaseType
// class produces a value that can  be treated as  the ``null value'' of that
// class, (b)   the BaseType  class  supports a  copy  constructor   and an
// assignment operator, and (c)  the BaseType class supports the    Compare
// method. (This is because the set uses  a sorted array representation for
// maximum efficiency.)   Primitive  objects    that do not     support the
// {\tt Compare} method, such as {\tt long} and {\tt int}, are provided with
// ``template override'' methods in {\tt basicops.h}.
//
// All the methods that modify the Set consult the pre-change dependents
// before the modification, and notify post-change dependents afterwards.
//
// A SetIterator object is also provided; this object allows inspecting the
// objects contained in  a Set, in   ascending order.  It provides  methods
// Reset(), More() and Next(), so  that iteration in  the following form is
// possible:
// \par\begin{verbatim}
//           CL_StringSetIterator iter (my_set);
//           CL_String s;
//           for (iter.Reset(); iter.More(); ) {
//               s = iter.Next();
//               // Process the string s here....
//           }
// \end{verbatim}
// 
// Objects returned by the Iterator's {\tt Next()}  method may {\it not\/}  be
// modified. It is not advisable to add or remove elements from a set while  an
// iterator on the set is active.
// 
// When the Set is instantiated as a container for pointers (as are
// {\tt CL_Set<CL_ObjectPtr>} or {\tt CL_ObjectSet}), the set
// does  not own the objects that the pointers point to, and
// therefore does not delete them when it is destroyed. The {\tt
// DestroyContents} method is provided on {\tt CL_ObjectSet} to
// provide explicit control over destruction of contents.
//
// The implementation uses a sorted {\small\tt CL_Sequence}, so that it is
// possible to create sets with size up to about 89
// million, even under MS-Windows, thus alleviating the 64K  limitation
// under MS-Windows (provided, of course, there is enough main memory
// available).




#ifdef __GNUC__
#pragma interface
#endif

#ifdef __IBMCPP__
#pragma implementation("setimp.cxx")
#endif

#include "base/object.h"
#include "base/sequence.h"
#include "base/iterator.h"



template <class BaseType> class YACL_BASE CL_SetIterator;

template <class BaseType>
class YACL_BASE  CL_Set: public CL_Object {

public:

    // ------------------------ Creation and destruction --------------

    CL_Set ();
    // Construct an empty set. 

    // CL_Set (const CL_Sequence<BaseType>& s); Borland doesn't like this!
    // Create a set from the given Sequence, using the assignment operator.
    
    CL_Set (const CL_Set<BaseType>&);
    // Copy constructor. If the template parameter {\small\tt BaseType}
    // is a class object, the copy constructor of the {\small\tt
    // BaseType} is used to copy each entry in the set; if it's a
    // pointer or a {\tt long}, the object is copied directly.

    ~CL_Set ();

    //
    // ------------------------ Element access ---------------------------

    long Size() const;
    // Return the number of objects in the set.

    virtual bool Add (const BaseType& o);
    // Add an object to the set. Return true on success, FALSE on failure,
    // if either memory allocation failed or a pre-change dependent refused
    // permission to change.

    void operator+= (const BaseType& value) {Add (value);};
    // Add the given value to the Set. The implementation simply forwards
    // the call to {\tt Add}.

    virtual BaseType Remove (const BaseType& o);
    // Remove the object equal to {\tt o} from the set (if it's there). Return
    // the removed object if successful, and the null value of BaseType
    // if failed. If this is a pointer-based Set, the return
    // value must be destroyed by the caller of this method.

    virtual bool Includes (const BaseType& o) const;
    // Determine if {\tt o} is in the set.

    virtual void MakeEmpty ();
    // Empty the set (i.e., remove all its elements). If this is a
    // pointer-based set, the contained objects are {\it not\/} deleted.

    // ------------------- Miscellaneous methods -------------------------

    virtual long RankOf (const BaseType& v) const;
    // Return the number of elements in this Set that are less than {\tt v}.
    // The parameter {\tt v} need not be in the Set. The ordering
    // relationship used is that defined by {\tt BaseType};
    // if the latter does not define a {\tt Compare} method or an {\tt
    // operator<} method, then {\tt RankOf} does not return anything useful.
    
    virtual const BaseType& ItemWithRank (long i) const;
    // Given an index $i$ between 0 and ${\tt Size()}-1$, return the element
    // of rank $i$, i.e., the element that has $i$ elements less than it in
    // the set. If $i \le 0$, this returns the 
    // smallest element, and if $i \ge {\tt Size()}$, this returns the
    // largest element.
    //
    // This is a {\tt const} method; even if this
    // is a set of pointers, it is not safe to modify the object pointed
    // to by the return value because the set's internal representation
    // may be affected and its algorithms may perform incorrectly.
    //
    //   Note that it is possible to iterate through the elements of the set
    // via calls to this method, varying the index from 0 to ${\tt Size()}-1$;
    // however, depending on the implementation, this may lead to very
    // inefficient iteration. Use of the SetIterator is the recommended way
    // to inspect all elements of the set.

    const BaseType& Smallest () const {return ItemWithRank(0);};
    // Return the smallest element in the Set; return the null value of
    // BaseType if the Set is empty. The implementation simply calls
    // {\tt ItemWithRank(0)}.
    
    inline const BaseType& Largest () const;
    // Return the largest element in the set; return the null value of
    // the base type if the set is empty.

    // ------------------- Manipulation of sets ------------------------

    virtual bool operator== (const CL_Set<BaseType>& o) const;
    // Check if Set {\tt o} is the same as this set, i.e., if each of {\tt o}'s
    // elements equals the corresponding element in this Set.

    virtual bool operator== (const CL_Object& o) const;
    // Check if {\tt o} is the same as this Set. The implementation checks
    // for type, casts {\tt o} down to a {\tt CL_Set<BaseType>} and calls
    // the other {\tt operator==}.

    
    // ----- Assignments

    virtual CL_Set<BaseType>& operator= (const CL_Set<BaseType>& s);
    // Assign the  given Set to this one. If the template
    // parameter {\tt BaseType} is a class, the copy constructor of the {\tt
    // BaseType} is used to copy each entry in the set s; if it's a
    // pointer, just the pointer is copied.


    void operator= (const CL_Object& o);
    // Cast {\tt o} to a Set and assign it to this object.

    virtual CL_Set<BaseType> operator+   (const CL_Set<BaseType>& o) const;
    // Return the Set containing all elements in either this Set or {\tt o}.
    // The implementation uses an algorithm that performs $m + n$ pointer
    // moves and as many comparisons, where $m$ and $n$ are the sizes of
    // this Set and {\tt o}.
    
    virtual CL_Set<BaseType>& operator+= (const CL_Set<BaseType>& o);
    // Add all elements in {\tt o} to this Set; return a reference to this
    // Set.
    
    virtual CL_Set<BaseType> operator* (const CL_Set<BaseType>& o) const; 
    // Intersection: Return the set containing the elements common between
    // this set and o. The
    // implementation uses an algorithm that performs $m + n$ pointer
    // moves and as many comparisons, where $m$ and $n$ are the sizes of
    // this set and {\tt o}.
        
    virtual CL_Set<BaseType>& operator*= (const CL_Set<BaseType>& o);
    // Replace this set by its intersection with {\tt o}.
    
    virtual CL_Set<BaseType> operator-   (const CL_Set<BaseType>& o) const;
    // Difference: return the set obtained by removing from this set those
    // elements that are common with o. The
    // implementation uses an algorithm that performs $m + n$ pointer
    // moves and as many comparisons, where $m$ and $n$ are the sizes of
    // this set and {\tt o}.
    
    virtual CL_Set<BaseType>& operator-= (const CL_Set<BaseType>& o);
    // Remove from this set the elements in common with o.

    virtual CL_Set<BaseType> operator^   (const CL_Set<BaseType>& o) const;
    // Symmetric difference (exclusive-or): return the set containing those
    // elements that are either in this set or in {\tt o}, but nor both. The
    // implementation uses an algorithm that performs $m + n$ pointer
    // moves and as many comparisons, where $m$ and $n$ are the sizes of
    // this set and {\tt o}.
    
    virtual CL_Set<BaseType>& operator^= (const CL_Set<BaseType>& o);
    // Assign to this Set the symmetric difference between this Set and {\tt
    // o}.

    virtual bool IncludesAll (const CL_Set<BaseType>& s) const;
    // Return true if this Set contains all elements of the given Set. The
    // algorithm performs as many comparisons as the sum of the sizes of
    // this Set and the given Set.
    
    //
    // ---------------------- Storage and retrieval ----------------------
    //

    long StorableFormWidth() const;
    // Override the method inherited from Object. The
    // implementation returns the sum of the storable form widths of the
    // contained objects plus some constant overhead for Set size and class
    // id.

    bool ReadFrom (const CL_Stream&);
    // Override the method inherited from {\tt CL_Object}. The
    // implementation reads a binary representation of this Set from the
    // parameter Stream.

    bool WriteTo  (CL_Stream&) const;
    // Override the method inherited from {\tt CL_Object}. The
    // implementation writes a binary representation of this Set to the
    // parameter Stream.

    

    //
    // ------------------------- Basic methods --------------------
    //
    CL_Object* Clone () const
        {return new CL_Set<BaseType> (*this);};
    // Overrides the method inherited from {\tt CL_Object}. The
    // implementation returns a copy of this Set.
    
    const char* ClassName() const {return "CL_Set";};
    
    CL_ClassId ClassId() const
        { return _CL_Set_CLASSID;};



    // -------------------- End public protocol ---------------------------

    
protected:

    // ---------------------- Friend declarations -----------------------
    
    friend CL_SetIterator<BaseType>;

    
    // ----------------------- Instance variables -----------------------
    
    void*              _idata;       // Representation of the Set
    BaseType           _nullValue;
    
    // ------------------------ Protected methods ----------------------
    
    CL_Set (void* p);
    // Protected constructor, for use by derived classes. This constructor
    // assumes that its parameter p is the data representation, and sets
    // _idata to p.

    virtual bool       _ReadElement (const CL_Stream& s, BaseType& e);
    // Read an element e of the set from the stream. This method
    // is used by {\tt ReadFrom}. The return value is TRUE if the
    // operation succeeds, and FALSE otherwise. The default implementation
    // simply calls {\tt CL_RestoreFrom} in {\tt basicops.h}.
    
    virtual bool       _WriteElement (CL_Stream& s, const BaseType& e) const;
    // Write an element e of the set to the stream. This method
    // is used by {\tt WriteTo}. The return value is TRUE if the
    // operation succeeds, and FALSE otherwise. The default implementation
    // simply calls {\tt CL_SaveTo} in {\tt basicops.h}.
    
    virtual bool       _FindPos (const BaseType& o, long& pos) const;
    // Find and return the position in the Sequence at which {\tt o} occurs
    // in {\tt pos}. Return TRUE if found, FALSE otherwise.
    
    
};



// SetIterator is a class template that provides iteration over a Set. The
// {\tt Reset} method resets the iteration to the beginning, and the {\tt
// More} method tells if there are more objects in the iteration. The {\tt
// Next} method returns the contents of the set in ascending order.

template <class BaseType>
class YACL_BASE  CL_SetIterator: public CL_Iterator <BaseType> {

public:

    CL_SetIterator (const CL_Set<BaseType>& s);
    // Constructor. The parameter specifies the set to be inspected.

    ~CL_SetIterator ();
    
    CL_SetIterator (const CL_SetIterator<BaseType>& itr);
    // Copy constructor. The copy inspects the same set as {\tt itr}, and
    // (unless reset) begins  its iteration at the object at which {\tt
    // itr} is currently positioned.
    
    virtual void Reset();
    // Reset the Iterator to the beginning. 

    virtual void BeginFromRank (long i);
    // Start the iteration so that the first call to {\tt Next} returns the
    // element of rank {\tt i}. Thus {\tt BeginFromRank(0)} is equivalent to
    // {\tt Reset()}.
    
    virtual bool More();
    // Return TRUE if there are objects left in the  iteration.

    virtual const BaseType& Next();
    // Return the next object in the iteration.

    virtual const char* ClassName () const {return "CL_SetIterator";};
    

protected:
    const CL_Set<BaseType>& _set;
    long                    _index;

    virtual bool            _SetModified ();
    // Called by our Set to tell us that someone is trying to modify it.
    
};




// Borland 3.1 doesn't like this:
// template <class BaseType>
// inline CL_Set<BaseType>::CL_Set  (const CL_Sequence<BaseType>& seq)
// {
//     *this = seq;
// }




template <class BaseType>
inline const BaseType& CL_Set<BaseType>::Largest () const
{
    return ItemWithRank(Size()-1);
}



template <class BaseType>
inline bool CL_Set<BaseType>::operator== (const CL_Object& o) const
{
    return ClassId() == o.ClassId() && *this == ((const CL_Set<BaseType>&) o);
}



#endif /* _set_h_ */



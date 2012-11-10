

#ifndef _sequence_h_ /* Tue Dec 22 11:41:35 1992 */
#define _sequence_h_





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




// Sequence is a class template  representing a sequence whose elements
// can be  accessed and modified  via the subscript  operator. In addition,
// the Sequence container supports the  {\tt Add}, {\tt Insert} and {\tt
// Remove} operations 
// that provide for  automatic growth  and shrinkage   of the  Sequence,
// and the  {\tt InsertByRank} method  for  insertion in sorted  order
// assuming that the sequence is sorted. YACL uses Sequences instead of
// lists and arrays.
// 
// The Sequence provides {\tt Sort} as  well as {\tt
// LinearSearch} and {\tt BinarySearch} methods for sorting and searching
// for elements. 
// 
// The Sequence  is  a class template,  and its base  type  is required to
// support  the {\tt Compare} method  as  well as a   copy constructor, a
// default constructor (that takes no parameters) and an assignment operator.
// 
// Methods that modify the   sequence (i.e., {\tt Insert},  {\tt
// InsertByRank}, {\tt Remove},
// {\tt Add}, {\tt Sort}) will return  without modifying the sequence  if
// any of  the
// pre-change dependents refuses permission. However, the Sequence does not
// check for modification of the    contained objects (those returned   via
// {\tt operator[\,]}).
//
// When the Sequence is instantiated  as a container for pointers (as  are
// {\tt CL_Sequence <CL_ObjectPtr>} or CL_ObjectSequence), the
// Sequence does {\it not\/} own the objects  that the pointers  point to,
// and  therefore 
// does not  delete them when  it is  destroyed.  The {\tt DestroyContents}
// method  is provided  on  ObjectSequence  to  provide  explicit
// control over destruction of contents.
//
// The implementation uses a ``segmented array'' technique that allows
// creating sequences with size up to  approximately 89 million,
// even under MS-Windows, thus alleviating the 64K  limitation under
// MS-Windows (provided, of course, there is enough main memory available).



#if defined(__GNUC__)
#pragma interface
#elif defined(__IBMCPP__)
#pragma implementation("seqimp.cxx")
#endif


#include "base/object.h"
#include "base/iterator.h"

template <class T> class YACL_BASE CL_Set;
class YACL_BASE CL_IntegerSet;



template <class BaseType>
class YACL_BASE  CL_Sequence: public CL_Object {

public:
    //
    // ------------------------ Creation and destruction --------------
    //
    CL_Sequence (long initial_size = 0);
    // Create a sequence with given size.

    CL_Sequence (const BaseType data[], long count);
    // Convenience constructor: create this sequence from a C-style array.
    
    CL_Sequence (const CL_Sequence<BaseType>& seq);
    // Copy constructor. If the template parameter {\tt BaseType}
    // is a class object, the copy constructor of the {\tt
    // BaseType} is used to copy each entry in the sequence; if it's a
    // pointer, just the pointer is copied. 

    ~CL_Sequence();

    //
    // ------------------------ Element access ---------------------------

    long Size() const {return _size;};
    // Return the number of elements in the Sequence. This is an inline
    // method that takes small constant time.

    virtual BaseType& operator[] (long i) const;
    // Return the $i$-th element. The index $i$ must be in the range 0
    // to ${\tt Size}-1$; this is checked by the method, and a fatal error
    // is caused if the index is out of range. (This check can be compiled
    // out using a preprocessor symbol --- see {\tt seqimp.cxx}.) The
    // return value is a reference that may be modified by the caller.
    //
    // This method is implemented with merely two shift operations and two
    // indexed accesses on the segmented sequence, so it is quite efficient.

    virtual BaseType& operator() (long i) const;
    // Return the $i$-th element. The index $i$ must be in the range 0
    // to ${\tt Size}-1$, but this condition is {\it not\/} checked by the
    // method. This method must be used where efficiency is more important
    // than range checking. The
    // return value is a reference that may be modified by the caller.
    //
    // This method is implemented with merely two shift operations and two
    // indexed accesses on the segmented sequence, so it is quite efficient.

    virtual bool Insert (const BaseType& o, long index = -1);
    // Insert the given element into the Sequence, immediately to the right of
    // the given index, and expand the sequence size by 1. Return TRUE if
    // successful, FALSE if failed for some reason (e.g. the index was
    // less than $-1$ or greater than ${\tt Size()}-1$). Specifying an index of
    // $-1$ inserts the element at the left end of the sequence.
    //
    // The implementation performs {\tt Size() - index} pointer
    // movements. These are pointer movements even when the {\tt
    // BaseType} is a class object.

    virtual long InsertByRank (const BaseType& o);
    // Insert the given object {\tt o} into the Sequence at the smallest
    // position $i$ such that all elements in the sequence between indices
    // 0 and $i-1 $
    // are less than {\tt o}, according to the {\tt Compare} method on
    // {\tt o}. (Note that
    // this formulation does not assume that the Sequence is sorted,
    // although InsertByRank maintains sorted order if it were.) Return the
    // index $i$ at which it was inserted, after increasing the size of the
    // sequence by 1.
    //    This method returns $-1$ if memory allocation failed or a
    // pre-change dependent refused permission to change.
    //
    // The implementation performs {\tt Size() - index} pointer
    // movements, where {\tt index} is the position at which the
    // insertion occurs. These are pointer movements even when the {\tt
    // BaseType} is a class object.
    
    virtual long Add (const BaseType& o);
    // Append an element to the end of the sequence, expanding the sequence
    // automatically if needed. Return the index at which the element
    // was added.
    //
    // This method is very efficient (constant-time) in most cases; it
    // needs extra time only when the internal capacity has to increase, and
    // that happens very infrequently.

    virtual BaseType Remove (long i);
    // Remove the $i$-th element of the Sequence, and close the hole, so
    // that all elements formerly at indices higher than $i$ will now
    // have their indices decremented by 1. Return the removed element,
    // and return the null value of the BaseType if removal failed (e.g.,
    // for an invalid index i).
    //
    // The implementation performs {\tt Size() - index} pointer
    // movements. These are pointer movements even when the {\tt
    // BaseType} is a class object.

    virtual BaseType ExtractLeftmost ();
    // Remove and return the leftmost element of the Sequence. Return the
    // null value of the base type if failed (e.g. because the Sequence is
    // empty).
    //
    // The implementation performs {\tt Size()} pointer
    // movements. These are pointer movements even when the {\tt
    // BaseType} is a class object.

    virtual BaseType ExtractRightmost ();
    // Remove and return the rightmost element of the Sequence. Return the
    // null value of the base type if failed.
    //
    // This method is very efficient (constant-time) in most cases; it
    // needs extra time only when the size has to decrease, and that
    // happens very infrequently.


    long LinearSearch (const BaseType& o) const;
    // Do a linear search for the given object in the Sequence. Return
    // the index at which it was found, or $-1$ if not found.

    bool BinarySearch (const BaseType& o, long& index) const;
    // Assuming that the Sequence is sorted, search for a given element,
    // and return a boolean whether it was found. Return the index of
    // the greatest element not exceeding {\tt o} in the
    // second parameter. If there are multiple occurrences of {\tt o} in the
    // Sequence, the index of the one with least index is returned.
    //
    // This method performs a binary search for
    // sequences larger than 7 elements, but does not check whether the
    // sequence is sorted; so it must only be used on Sequences that are
    // known to be sorted. (See the {\tt Sort} method.)

    
    // ------------------- Sequence methods ------------------------

    virtual CL_Sequence<BaseType>& operator= (const CL_Sequence<BaseType>&);
    // Assign to this sequence from the given Sequence. If the template
    // parameter {\tt BaseType} 
    // is a class object, the copy constructor of the {\tt
    // BaseType} is used to copy each entry in the Sequence; if it's a
    // pointer, just the pointer is copied.


    void operator= (const CL_Object& o);
    // Check that the given object has the same class id as the Sequence,
    // and then perform a Sequence assignment after casting down.
    

    virtual CL_Sequence<BaseType>& operator+= (const CL_Sequence<BaseType>& s);
    // Concatenate the given Sequence onto the end of this Sequence. If
    // the template parameter {\tt BaseType} 
    // is a class object, the copy constructor of the {\tt
    // BaseType} is used to copy each entry in the Sequence {\tt s};
    // if it's a pointer, just the pointer is copied.

    CL_Sequence<BaseType> Subsequence (const CL_IntegerSet& s) const;
    // Return the subsequence  of this Sequence containing those
    // elements whose positions are in the given Set.
        
    CL_Sequence<BaseType> operator- (const CL_IntegerSet& s) const;
    // Return the Sequence obtained by removing from this Sequence those
    // elements whose indices are in the given Set. If the {\tt
    // BaseType} of this Sequence is a pointer,
    // the pointers are copied into the returned
    // Sequence; if the {\tt BaseType} is a class, the copy
    // constructor of the {\tt BaseType} is used to copy the objects
    // into the returned Sequence.


    virtual void operator-= (const CL_IntegerSet& s);
    // Remove from this Sequence those elements whose indices are in the
    // given set. The implementation uses no more than $n = {\tt Size()}$
    // pointer movements, regardless of how big {\tt s} is.

    CL_Sequence<BaseType> Remove (const CL_IntegerSet& s);
    // Remove from this Sequence those elements whose indices are in the
    // given set, and return the removed elements. The implementation uses
    // the {\tt Move} method with a temporary sequence as target.

    virtual long Move (const CL_IntegerSet& s, CL_Sequence<BaseType>& target);
    // Remove from this Sequence the elements whose indices are in the Set
    // {\tt s}, in ascending order, and append them to {\tt target}, thus
    // shrinking this Sequence and growing {\tt target}. Since this
    // operation involves structural change in both this Sequence and {\tt
    // target}, the pre-change dependents of both are consulted before the
    // operation, and the post-change dependents of both are notified after
    // the operation.
    //
    // The method returns the number of
    // elements moved. The implementation uses no more than $n = {\tt Size()}$
    // pointer movements, regardless of how big {\tt s} is.

    virtual bool ChangeSize (long new_size);
    // Expand this Sequence to the given size. If {\tt new_size} is less than
    // the current size, this operation truncates the Sequence, i.e. the
    // elements with higher indices are lost. If the new Sequence is
    // longer, the additional elements are initialized with the null value
    // of the {\tt BaseType} (i.e., the NULL pointer for pointer
    // types, and the value returned by the default constructor for
    // class objects).
    //    The method returns TRUE if successful, FALSE if no more memory.

    virtual void MakeEmpty ();
    // Delete all contained objects, and set our size to 0. If this is a
    // sequence of Object pointers, the contained objects are {\it not\/}
    // deleted.

    virtual bool ShiftRightAt (long pos, long amount = 1);
    // Shift all elements, beginning at position {\tt pos}, right by
    // {\tt amount} cells; then set the cells {\tt pos} through {\tt
    // pos+amount-1}  to
    // the null value of the base type. The new Sequence will have its size
    // increased by {\tt amount}. The value {\tt pos} must be in the range 0 to
    // {\tt Size()-1}.
    //    This method returns TRUE on success, FALSE on failure (e.g., memory
    // allocation failure).
    //
    // The implementation performs {\tt Size() - pos} pointer
    // movements. These are pointer movements even when the {\tt
    // BaseType} is a class object.
    
    virtual bool ShiftLeftAt (long pos, long amount = 1);
    // Shift all elements, beginning at position {\tt pos} upto our last
    // element, left by {\tt amount} cells; this causes the Sequence to
    // lose the elements that were at positions {\tt pos - amount} through
    // {\tt pos - 1}.
    // The new Sequence will have its size decreased by {\tt amount}.
    //    Return TRUE on success, false on failure (e.g., memory
    // allocation failure).
    //
    // The implementation performs {\tt Size() - pos} pointer
    // movements. These are pointer movements even when the {\tt
    // BaseType} is a class object.
    

    bool Sort ();
    // Sort the elements into ascending order. Return FALSE if either the
    // Sequence was already sorted, memory allocation failed, or one of
    // the pre-change dependents refused permission, and TRUE otherwise. The
    // implementation forwards the call to the two-parameter version of {\tt
    // Sort}.

    virtual bool Sort (long pos, long len);
    // Sort the segment of the Sequence beginning at position {\tt pos},
    // containing {\tt len} elements. The implementation uses 
    // the {\tt _QuickSort} method, and the latter uses the {\tt _Compare}
    // method for comparison.
    
    virtual bool IsSorted () const;
    // Is this sequence sorted?


    // -------------------- Storage and retrieval ---------------------

    long StorableFormWidth () const;

    bool ReadFrom (const CL_Stream&);
    // Read the objects in this Sequence from the given Stream in binary
    // form. This overrides the inherited method.

    bool WriteTo  (CL_Stream&) const;
    // Write the objects in this Sequence into the given Stream in binary
    // form. This overrides the inherited method.

    
    // -------------------- Basic methods --------------------

    CL_Object* Clone () const;
    
    const char* ClassName() const {return "CL_Sequence";};

    CL_ClassId ClassId() const { return _CL_Sequence_CLASSID;};



    // -------------------- End public protocol ---------------------------

    
protected:

    //
    // Instance variables
    //
    void*              _idata;
    long               _size;
    BaseType           _nullValue;

    virtual bool       _QuickSort (long left, long right);
    // Apply QuickSort on the  segment of the Sequence beginning at {\tt
    // left} and ending at {\tt right}. Return FALSE if this segment was
    // already sorted, and TRUE otherwise. This method does not perform
    // notification.

    virtual bool       _ReadElement (const CL_Stream& s, long i);
    // Read the $i$-th element of the Sequence from the stream. This method is
    // provided as a ``hook,'' and
    // is used by {\tt ReadFrom}. For class objects, the return value is a
    // pointer to a newly-created object read in from the stream. The
    // default implementation uses the basic operation {\tt Read}.
    
    virtual bool       _WriteElement (CL_Stream& s, long i) const;
    // Write the $i$-th element of the Sequence to the stream. This method os
    // provided as a ``hook'' for derived classes, and 
    // is used by {\tt WriteTo}. The return value is TRUE if the
    // operation succeeds, and FALSE otherwise. The default implementation
    // uses the basic operation {\tt Write}.
    
    virtual short      _Compare (const BaseType&, const BaseType&) const;
    // Compare two objects. All comparisons needed by all methods in the
    // Sequence are done by this method. The default implementation uses
    // the CL_Basics<BaseType>::Compare function.
    


private:

    bool           _ShiftRightAt (long pos, long amount);
    // Do the ShiftRight without notifying clients.

    bool          _ShiftLeftAt  (long pos, long amount);
    // Do the ShiftLeft without notifying clients.

    // short          _ChangeSize (long new_size);
    // Do the ChangeSize without notifying clients.
    
    short          _DoInsert (const BaseType& o, long index);
    // Do the Insert without notifying clients.

    void           _DoMakeEmpty ();
    // Do the MakeEmpty without notifying clients.

};




// A SequenceIterator iterates through a Sequence. It is used only to fit
// into the framework of iterators, so that algorithms may be expressed
// entirely in terms of iterators.

template <class BaseType>
class YACL_BASE CL_SequenceIterator: public CL_Iterator<BaseType> {

public:
    CL_SequenceIterator (const CL_Sequence<BaseType>&);
    // Constructor. The parameter specifies the Sequence to be inspected.

    CL_SequenceIterator (const CL_SequenceIterator<BaseType>& itr);
    // Copy constructor. The copy inspects the same Sequence as {\tt itr}, and
    // (unless reset) begins  its iteration at the same object that itr is
    // currently positioned.
    
    virtual void Reset();

    virtual bool More();

    virtual const BaseType& Next();

    virtual const char* ClassName () const {return "CL_SequenceIterator";};
    

protected:
    const CL_Sequence<BaseType>& _sequence;
    long                         _index;

};




template <class BaseType>
inline CL_Object* CL_Sequence<BaseType>::Clone () const
{
    return new CL_Sequence<BaseType> (*this);
}


template <class BaseType>
inline bool CL_Sequence<BaseType>::Sort ()
{
    return Sort (0, Size());
}

#endif  /* _sequence_h_ */


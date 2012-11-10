

#ifndef _bitset_h_ /* Mon Nov  8 09:02:26 1993 */
#define _bitset_h_





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


// This is a class encapsulating the notion of a {\it BitSet,} a set of
// integers represented by a bit vector. It can store a set of integers in
// the range $0 .. max-1$, where $max$ is the {\it universe size\/} for the
// BitSet. The universe size is a parameter to the constructor. The BitSet
// includes all the usual set operations such as union, intersection and
// membership testing. In addition, the BitSetIterator class can be used to
// inspect all the elements in a BitSet.
//
// The BitSet is said to be {\it universal\/} (i.e., equal to its universal
// set) if it currently contains all integers between 0 and $max-1$.
//
// The bit-vector representation allows very efficient storage and access
// algorithms for small, dense sets of integers. (Dense sets are those in
// which the number of elements is a significant proportion of the maximum
// size.)
//


#ifdef __GNUC__
#pragma interface
#endif


#include "base/intset.h"
#include "base/bytstrng.h"
#include "base/iterator.h"


class YACL_BASE CL_BitSet: public CL_Object {

public:

    // --------------------- Construction and destruction -------

    CL_BitSet  (long universeSize = 128);
    // Construct a bitset that can contain at most the elements between 0
    // and ${\tt universeSize} - 1$. The given {\tt universeSize} value is
    // rounded up to the nearest higher multiple of 32.

    CL_BitSet (long low, long hi, long universeSize = 128);
    // Build a set with containing all the numbers in the range
    // {\tt low} through {\tt hi}. If {\tt lo < hi}, the empty set is built.
    // The given {\tt universeSize} value is rounded up to the nearest
    // higher multiple of 32; it determines the universe size of the BitSet
    // regardless of what {\tt low} and {\tt hi} are, i.e., even if they are
    // larger than {\tt universeSize}.
    
    CL_BitSet  (CL_ByteArray& b);
    // Restore this BitSet from the given byte array. The latter should
    // contain the passive representation of a BitSet, produced by the
    // WriteTo method on a ByteStream.

    CL_BitSet  (const CL_BitSet& b);
    // Copy constructor.

    ~CL_BitSet();
    // Destructor.
    
    

    // ----------------------- Element methods ------------------

    virtual bool Add       (long value);
    // Add a value. Return TRUE on success, FALSE if the element was already
    // in the set.

    virtual long Remove    (long value);
    // Remove a value. Return the removed value if it was in the
    // set, and $-1$ otherwise.

    bool Includes          (long value) const;
    // Check whether the given element is in the set.

    long Smallest () const;
    // Return the smallest integer in the set. Return $-1$ if the set is
    // empty.
    
    long Largest () const;
    // Return the largest integer in the set. Return $-1$ if the set is
    // empty.
    
    long RankOf (long v) const;
    // Return the number of elements in this set that are less than {\tt v}.
    // The parameter {\tt v} need not be in the set.
    
    long ItemWithRank (long i) const;
    // Given an index $i$ between 0 and ${\tt Size()}-1$, return the element
    // of rank 
    // $i$, i.e., the element that has $i$ elements less than it in the set.
    // If $i \le 0$, this returns the 
    // smallest element, and if $i \ge {\tt Size()}$, this returns the
    // largest element. If the set is empty, return $-1$.
    //
    //   Note that it is possible to iterate through the elements of the set
    // via calls to this method, varying the index from 0 to {\tt Size()$-1$};
    // however, this is very inefficient iteration. Use of the BitSetIterator
    // is the recommended way to inspect all elements of the BitSet.

    long Successor (long n) const;
    // Return the least number in the set that is larger than {\tt n}.
    // The set need not contain {\tt n}.
    // Return $-1$ if the parameter equals or exceeds the largest value in the
    // set.
    
    long SmallestNonMember () const;
    // Return the smallest non-negative number that is {\it not\/} in the set.
    
    bool IsEmpty   () const;
    // Return TRUE if the BitSet is empty, FALSE otherwise.

    virtual long Size     () const;
    // Return the current cardinality of (i.e., number of integers in) the set.

    CL_BitSet operator+ (long value) const;
    // Return a  BitSet which contains our contents augmented with the given
    // value.
    
    // ----------------------- Set methods ----------------------

    virtual void MakeEmpty ();
    // Make this the empty set, i.e., remove all its elements.
    
    virtual void MakeUniversal ();
    // Make this the universal set (i.e., the set containing all elements
    // between 0 and our universe size).

    bool IsUniversal () const;
    // Return TRUE if this is this the universal set, FALSE otherwise.

    CL_IntegerSet AsSet () const;
    // Convert this BitSet into a set of long values, and return the result.
    // The contents of this BitSet are not affected.

    operator CL_IntegerSet() const {return AsSet();};
    // Convert this BitSet into a set of long values, and return the result.
    // The contents of this BitSet are not affected.

    // ----- Comparisons:
    
    bool operator== (const CL_BitSet& o) const;
    // Return TRUE if this BitSet contains the same elements as does {\tt
    // o}, and FALSE otherwise.
    
    bool operator== (const CL_IntegerSet& o) const;
    // Return TRUE if this BitSet contains the same elements as does {\tt o}
    // and FALSE otherwise.
    
    // ----- Assignment operators:
    
    virtual void operator= (const CL_Object& o);
    // Check that the class id of the given object is the same as ours,
    // and assign the result to this class. An invalid class id results in
    // a runtime error message.
                     
    virtual CL_BitSet& operator= (const CL_BitSet& s);
    // Assign the given BitSet to this object.

    // ----- Binary set operators:
    
    // The binary set operations union, intersection and difference all
    // yield sets whose maximum size is the larger of the maximum sizes of
    // the two operands.

    CL_BitSet operator+ (const CL_BitSet& s) const;
    // Return the union of this set and s. The universe size of the returned
    // BitSet is the larger of the universe sizes of this set and {\tt s}.

    virtual void operator+= (const CL_BitSet& o);
    // Add the elements of {\tt o} to this set.

    CL_BitSet operator- (const CL_BitSet& o) const;
    // Difference: return the set obtained by removing from this set those
    // elements that are common with {\tt o}.  The universe size of the
    // returned BitSet is the larger of the universe sizes of this set and
    // {\tt o}.

    virtual void operator-= (const CL_BitSet& o);
    // Remove from this set the elements in common with {\tt o}.

    CL_BitSet operator* (const CL_BitSet& o) const;
    // Intersection: Return the set containing the elements common between
    // this set and {\tt o}.  The universe size of the returned
    // BitSet is the larger of the universe sizes of this set and {\tt o}.

    virtual void operator*= (const CL_BitSet& o);
    // Replace this set by its intersection with {\tt o}.

    CL_BitSet operator^ (const CL_BitSet& o) const;
    // Exclusive-or: Return the set containing the elements that are either
    // in this set or in {\tt o} but not both.  The universe size of the
    // returned 
    // BitSet is the larger of the universe sizes of this set and {\tt s}.

    virtual void operator^= (const CL_BitSet& o);
    // Replace this set by its exclusive-or with o.

    CL_BitSet operator~ () const;
    // Complementation: Return a BitSet containing those elements not in
    // this set, but in this set's universal set.

    bool IncludesAll (const CL_BitSet& o) const;
    // Return TRUE if this BitSet contains all the elements that the BitSet
    // {\tt o} does, and FALSE otherwise.
    
    bool IncludesAll (const CL_IntegerSet& o) const;
    // Return TRUE if this BitSet contains all the elements that the
    // IntegerSet {\tt o} does, and FALSE otherwise.
    
    // --------------------- Saving and restoring -----------------------
    
    long StorableFormWidth () const;
    // Return the number of bytes need to store this BitSet in binary form.
    // This value is $n/8 + 12$ where $n$ is the universe size for this
    // BitSet.
    
    virtual bool ReadFrom (const CL_Stream&);
    // Read this BitSet from the given Stream.

    virtual bool WriteTo  (CL_Stream&) const;
    // Write this BitSet to the given Stream.
    


    // -------------------- Basic inherited methods ---------------------

    const char* ClassName() const { return "CL_BitSet";};
    // Return the string ``{\tt CL_BitSet}.''
    
    CL_ClassId ClassId () const {return _CL_BitSet_CLASSID;};

    bool operator== (const CL_Object& o) const;
    // Cast down {\tt o} to a BitSet and check if it contains the same
    // elements as this BitSet. Return TRUE if so and FALSE otherwise.

    CL_String AsString () const {return AsSet().AsString (); };
    // Return a String containing a printable representation of the
    // contents, in the form \verb:{1, 3, 4}:.
    
    // --------------------- End public protocol ------------------------

    
protected:

    friend class CL_BitSetIterator;
    
    ulong*  _rep;
    long    _size;  // Current cardinality
    long    _count; // # ulongs in representation

    CL_BitSet (long wordCount, ulong array[]);
    // Protected constructor, for internal use only.

    CL_BitSet _DoOp (const CL_BitSet&, void (*o)(ulong&, ulong)) const;
    // Used by the binary operation methods.
    
};






// This is an object that allows iteration over a BitSet, and provides the
// usual iteration methods Reset, More and Next. This is the most efficient
// way of iterating over a BitSet.

class YACL_BASE CL_BitSetIterator: public CL_Iterator<long> {

public:
    CL_BitSetIterator (const CL_BitSet& o);
    // Constructor: tells us which set we're inspecting.

    void Reset();
    // Reset the cursor to the beginning of the BitSet.

    void BeginFromRank (long l);
    // Begin the iteration from the element of rank {\tt l}. After calling
    // this method, the first call to {\tt Next()} returns the element of
    // rank {\tt l}.
    
    bool More ();
    // Are there more elements in the iteration?

    const long& Next();
    // Return the next integer in the iteration. Return $-1$ if no more. The
    // contents of the BitSet are returned in ascending order.

protected:
    const CL_BitSet& _set;         // Our set
    long             _index;       // Index of word being looked at
    long             _count;       // Number of elements returned so far
    long             _tblIndex;    // Index into table of bits
    long             _data;
};





inline long CL_BitSet::Size   () const
{
    return _size;
}


inline bool CL_BitSet::IsEmpty () const
{
    return Size() == 0;
}

inline void CL_BitSet::operator = (const CL_Object& o)
{
    if (CheckClassType (o, "CL_BitSet::op= (CL_Object&)"))
        *this = ((const CL_BitSet&) o);
}



inline bool CL_BitSet::operator == (const CL_Object& o) const
{
    return IsA(o) ? *this == ((const CL_BitSet&) o) : FALSE;
}


inline void CL_BitSet::operator += (const CL_BitSet& o)
{
    *this = *this + o;
}

inline void CL_BitSet::operator -= (const CL_BitSet& o)
{
    *this = *this - o;
}

inline void CL_BitSet::operator *= (const CL_BitSet& o)
{
    *this = *this * o;
}


inline void CL_BitSet::operator ^= (const CL_BitSet& o)
{
    *this = *this ^ o;
}


#endif /* _bitset_h_ */



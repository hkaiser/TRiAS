

#ifndef _bytarray_h_
#define _bytarray_h_





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



// A ByteArray is an object that provides access to  an array of bytes.
// This class is intended to manage a byte array owned by some {\it
// client\/} object
// {\it other than\/} this object; therefore, if the client is derived
// from CL_Object, then the client's dependents must be consulted and
// notified when this ByteArray is being modified. For this reason, the
// constructors for CL_ByteArray require a pointer to the client. If this
// pointer is \NULL, then the ByteArray assumes that the client does not
// need dependent notification.

#include "base/object.h"


#ifdef __GNUC__
#pragma interface
#endif


class YACL_BASE  CL_ByteString;

class YACL_BASE  CL_ByteArray: public CL_Object {

public:

    //
    // ---------------- Construction, destruction, conversion --------------
    //
    
    CL_ByteArray (CL_Object* client = NULL);
    // Default constructor that creates a zero-length ByteArray. The
    // parameter specifies the client who must be
    // notified if the data in the byte array changes.

    CL_ByteArray (uchar *buf, long size, CL_Object* client = NULL);
    // Constructor: assume that the array of bytes in question begins
    // at the given address, and is of the given size.


    CL_ByteArray (const CL_ByteArray& b);
    // Copy constructor: make copy of array address and size (i.e.,
    // the {\it same\/} array is used by the copy).

    ~CL_ByteArray ();
    // Destructor. The implementation does nothing; it is provided because
    // the {\tt CL_Object} destructor is pure virtual.

    // ------------------------- Access -----------------------------------

    void SetAllBytesTo (uchar b);
    // Set all the bytes in the byte array to the given value.
    
    virtual long Size() const;
    // Return the number of bytes in the byte array.

    long Length () const;
    // Return the number of bytes in the byte array (synonym for {\tt Size}).

    operator uchar* () const;
    // Return the address of the byte array.

    uchar* AsPtr () const;
    // Return the address of the byte array.

    
#ifndef _MSC_VER
    // Microsoft Visual C++ has trouble with this operator, because it
    // thinks the operator conflicts with a global one implicitly provided
    // by the char* conversion. So I've ifdef'ed it out. It should not
    // affect the use of operator[] on ByteArrays, though.
    
    uchar operator[] (long index);
    // Retrieve the byte at the given index. As usual, 
    // zero-origin indexing is assumed. Specifying an index outside
    // the legal range causes a fatal error.

#endif
    
    //
    // ----------------------- Conversion ---------------------------------
    //
    CL_String AsString () const;
    // Return the contents of this ByteArray, with a null byte appended,
    // as a String.

    //
    // ------------------------- Comparison --------------------------------
    //
    
    virtual bool operator== (const CL_Object& b) const;
    // Check that {\tt b} is a ByteArray, cast it down and use ByteArray
    // comparison for equality (i.e., the {\tt memcmp} function).

    virtual bool operator== (const CL_ByteArray& b) const;
    // Check if this ByteArray's contents are identical to those of {\tt b}
    // using the {\tt memcmp} function.

    virtual bool operator== (const uchar* b) const;
    // This and other comparison methods that take character pointer
    // arguments assume that the size of the memory segment pointed to by
    // the parameter is the same as the
    // size of this ByteArray.

    virtual bool operator!= (const CL_Object& b) const;

    virtual bool operator!= (const CL_ByteArray& b) const;

    virtual bool operator!= (const uchar* b) const;
    

    virtual bool operator>= (const CL_Object& b) const;

    virtual bool operator>= (const CL_ByteArray& b) const;

    virtual bool operator>= (const uchar* b) const;
    

    virtual bool operator<= (const CL_Object& b) const;

    virtual bool operator<= (const CL_ByteArray& b) const;

    virtual bool operator<= (const uchar* b) const;
    

    virtual bool operator> (const CL_Object& b) const;

    virtual bool operator> (const CL_ByteArray& b) const;

    virtual bool operator> (const uchar* b) const;
    

    virtual bool operator< (const CL_Object& b) const;

    virtual bool operator< (const CL_ByteArray& b) const;

    virtual bool operator< (const uchar* b) const;


    
    virtual short Compare (const CL_ByteArray& obj) const;
    // {\tt memcmp}-style comparison: return $-1$, 0 or $+1$ depending on
    // whether this ByteArray is less than, equal to or greater than {\tt
    // obj}.

    virtual short Compare (const CL_Object& obj) const;
    // Override the method inherited from {\tt CL_Object}. The parameter
    // is type-checked (via the {\tt IsA} method) and cast into a ByteArray
    // before the comparison is made. 

    //
    // ------------------ Sub-structure manipulation ------------------
    //
    
    CL_ByteArray operator() (long index, long size) const;
    // Return the sub-array beginning at the given index (using
    // 0-origin indexing) and of the given size. Note that the
    // returned ByteArray uses (part of) the same memory as this object,
    // so it is possible to assign to the returned sub-array to effect
    // copying into parts of this object. For example, with a ByteArray {\tt
    // anArray},  you can write
    // \begin{verbatim}
    //      anArray(5, 4) = (ulong) 23;
    // \end{verbatim}
    // \par\noindent to put the value 23 as an unsigned long value  (usually
    // 4 bytes) in the cells 5 through 8.
    //
    // Also, assignment to sub-arrays does not change the size of the
    // array itself.

    CL_ByteArray Suffix (long index) const;
    // Return the suffix beginning at the given index (using
    // 0-origin indexing). Note that the
    // returned ByteArray uses (part of) the same memory as this
    // ByteArray does.

    long LongValueAt (long index) const;
    // Obtain a long value from our array, beginning at the given
    // position (i.e., treat the sizeof(long) bytes beginning at the
    // given position as a long), and return it.
    
    short ShortValueAt (long index) const;
    // Extract a short value from our array, beginning at the given
    // position, and return it.

    long CommonPrefixLength (const uchar* p);
    // Return the size of the longest common prefix with the
    // parameter.


    // ----------------- Assignment, copying, modification ----------------

    virtual void operator= (const CL_ByteArray& b);
    // Assign another byte array to this one.

    virtual void operator= (const uchar* p);
    // Copy {\tt Size()} bytes from the given pointer position into this
    // ByteArray.

    virtual CL_ByteArray& operator= (long);
    // Copy the given long value into this ByteArray, beginning at position
    // 0. Do not copy more than {\tt Size()} bytes. This method, as well
    // as the operator= on short and String, can be used in conjunction with
    // the {\tt operator()} to put values at arbitrary positions in the
    // ByteArray.

    virtual CL_ByteArray& operator= (short);

    virtual void operator= (const CL_String&);
    // Copy a String, including the null byte at the end. No more than
    // {\tt Size()} bytes are copied. 


    virtual void operator= (const CL_Object&);
    // Generic assignment: Check that the parameter object has the same class
    // id as this object does, and perform a ByteArray assignment. This
    // method overrides the one inherited from Object.

    CL_ByteString operator+ (const CL_ByteArray& b) const;
    // Return the result of concatenating {\tt b} to the end of this ByteArray.

    virtual long CopyFrom (uchar* buffer, long count, long position = 0) const;
    // Copy {\tt count} bytes from {\tt buffer} into our data segment,
    // beginning at {\tt position} in our data. But do not copy any
    // more than ${\tt Size()} - {\tt position}$ bytes. Return the actual
    // number of bytes copied.
    
    long CopyTo (uchar* buffer, long count, long position = 0);
    // Copy {\tt count} bytes of our data, beginning at position {\tt pos},
    // into {\tt buffer}. But do not copy any more than ${\tt Size()} - {\tt
    // position}$ bytes. Return the actual number of bytes copied.


    virtual bool ChangeSize (long newSize);
    // Tell us to change our size, and return TRUE if successful.  Since
    // the ByteArray manages someone else's space and therefore cannot
    // change its size, this method always returns FALSE. It is overridden
    // by the derived class ByteString.

    // -------------------- Storage and restoration --------------
    
    virtual long StorableFormWidth () const;
    // Return the number of bytes needed to write a binary form of this
    // ByteArray into a Stream.

    bool ReadFrom (const CL_Stream&);
    // Overrides the method inherited from Object. The implementation reads
    // a passive representation of a ByteArray from the parameter Stream.

    bool WriteTo  (CL_Stream&) const;
    // Overrides the method inherited from Object. The implementation writes
    // a passive representation of a ByteArray to the parameter Stream.

    //
    // --------------------- Basic methods --------------------
    //
    
    virtual const char*      ClassName () const {return "CL_ByteArray";};
    // Returns the string ``{\tt CL_ByteArray}.''
    
    virtual CL_ClassId ClassId   () const {return _CL_ByteArray_CLASSID;};

    // ----------------------- End public protocol ------------------
    


protected:
    long       _size;
    uchar*     _array;
    CL_Object* _client;
};


inline void CL_ByteArray::operator= (const CL_Object& s)
{
    if (CheckClassType (s, "CL_ByteArray::operator= (CL_Object&)"))
        *this = (const CL_ByteArray&) s;
}


inline long CL_ByteArray::Size() const
{
    return _size;
}

inline long CL_ByteArray::Length () const
{
    return _size;
}


inline CL_ByteArray::operator uchar* () const
{
    return _array;
}


inline uchar* CL_ByteArray::AsPtr () const
{
    return _array;
}

inline bool CL_ByteArray::ChangeSize (long)
{
    return FALSE;
}



    
#endif


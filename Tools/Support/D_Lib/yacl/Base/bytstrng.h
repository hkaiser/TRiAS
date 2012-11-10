


#ifndef _bytstrng_h_
#define _bytstrng_h_





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



// The  ByteString class differs from the base 
// ByteArray class in that the former owns the memory it works with. As such,
// the ByteString supports growing and shrinking of the byte
// array and concatenation of ByteString objects.


#ifdef __GNUC__
#pragma interface
#endif


#include "base/bytarray.h"
#include "base/string.h"


class YACL_BASE  CL_ByteString: public CL_ByteArray {

public:

    // ------------------ Construction and destruction ---------------
    
    CL_ByteString();
    // Default constructor: create with zero length.

    CL_ByteString (long length);
    // Constructor: build a ByteString of the given length. All bytes
    // of the byte string will be zero.

    CL_ByteString (const CL_ByteArray& b);
    // Convert from a ByteArray.
    
    CL_ByteString (uchar* b, long length);
    // Copy (convert) from a {\tt uchar} array.

    CL_ByteString (const CL_String& s);
    // Convert from a String. This ByteString's length will be one more than
    // that of the String, and its contents will include the null terminator
    // byte.
    
    CL_ByteString (const CL_ByteString& b);
    // Copy constructor.

    ~CL_ByteString();


    // ------------------------ Byte string operations ------------
    
    
    virtual void operator= (const CL_ByteArray& b);
    // Assignment operator inherited from ByteArray. We need to
    // declare these here because of the peculiar definition of
    // inheritance for the assignment operator.

    void operator= (const uchar* p) {CL_ByteArray::operator= (p);};
    // This assignment operator forwards the call to the inherited operator
    // with the same signature.
  
    virtual void  operator= (const CL_String&);
    // Copy a String, including the null byte at the end. Grow
    // this ByteString if necessary.
    
    virtual CL_ByteArray& operator= (long p);
    // Copy the given long value into ourselves, beginning at position 0.

    virtual CL_ByteArray& operator= (short p);
    // Copy the given short value into ourselves, beginning at position 0.


    virtual void operator= (const CL_Object& p);


    virtual CL_ByteString& operator+= (const CL_ByteArray& b);
    // Append the contents of b to this ByteString, thereby growing the
    // latter. Return a reference to this ByteString.


    virtual bool ChangeSize (long newSize);
    // Tell us to change our size.  If the new size is less than our
    // current size, we lose the appropriate suffix. The return value
    // tells if the change was successful; a FALSE return value
    // indicates memory allocation failure.

    // -------------------- Storage and restoration --------------
    
    virtual long StorableFormWidth () const;
    // Overrides the method inherited from Object.
    
    bool ReadFrom (const CL_Stream&);
    // Overrides the method inherited from Object.

    bool WriteTo  (CL_Stream&) const;
    // Overrides the method inherited from Object.

    // ---------------- Basic methods ----------------------
    
    const char* ClassName() const {return "CL_ByteString";};

    CL_ClassId ClassId() const {return _CL_ByteString_CLASSID;};

    CL_Object* Clone() const {return new CL_ByteString (*this);}
    // Return a copy of this ByteString.
    
    
};


inline void CL_ByteString::operator= (const CL_Object& s)
{
    if (CheckClassType (s, "CL_ByteString::operator= (CL_Object&)"))
        *this = (const CL_ByteString&) s;
}




#endif


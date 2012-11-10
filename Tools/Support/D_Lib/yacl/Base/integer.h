
#ifndef _integer_h_
#define _integer_h_





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



// This class is intended to make an integer look like a first-class YACL
// object, complete with notification capabilities. It supports all of the
// usual integer operators as well as the protocol inherited from
// CL_Object. The representation uses a {\tt long} value.


#ifdef __GNUC__
#pragma interface
#endif

#include "base/object.h"
#include "base/string.h"
    


class YACL_BASE  CL_Integer: public CL_Object {

public:

    //
    // ------------------------ Construction and destruction -----------------
    //
    CL_Integer (long l) {_value = l;}
    // Make an Integer with value {\tt l}.

    CL_Integer () {_value = 0;}
    // Make a zero-valued Integer.

    CL_Integer (const CL_Integer& i) {_value = i.Value();};
    // Copy constructor.
    
    ~CL_Integer();
    // Destructor.


    //
    // ------------------------- Conversions ------------------------------
    //

    long Value() const {return _value;};
    // Return the value of the integer (synonym for type-casting {\tt
    // operator long}).

    operator long() const {return _value;};
    // Return the value of the Integer.

    CL_String InRadix (short r) const;
    // Return a String containing the radix-$r$ representation of this
    // Integer. The radix must be in the range 2..16; otherwise, the null
    // String is returned.  For a non-decimal radix, this Integer is
    // treated as unsigned.
    
    //
    // Comparison
    //
    bool operator<  (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // less than {\tt o}.

    bool operator<= (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // less than  or equal to {\tt o}.

    bool operator>  (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // greater than {\tt o}.

    bool operator>= (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // greater than or equal to {\tt o}.

    bool operator== (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // equal to {\tt o}.

    bool operator!= (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and check if this Integer is
    // different from {\tt o}.


    short Compare (const CL_Object& o) const;
    // Cast down {\tt o} into an Integer and call the Integer-specific {\tt
    // Compare} method.

    short Compare (const CL_Integer& o) const;
    // Return $-1$ if this Integer is less than {\tt o}, 0 if the two are
    // equal and $+1$ if this Integer exceeds {\tt o}.


    CL_Integer operator++ ();
    // Prefix increment.

    CL_Integer operator++ (int);
    // Postfix increment.

    CL_Integer operator-- ();
    // Prefix decrement.

    CL_Integer operator-- (int);
    // Postfix decrement.

    
    //
    // ------------------ Assignments of various kinds --------------------
    //
    virtual void operator= (const CL_Object&);
    // Cast the parameter down to an Integer and assign it to this object.

    virtual CL_Integer& operator= (long i);
    // Assign {\tt i} to this object.

    // Notice, in the following inline assignment methods, that we use
    // constructs such as
    //               *this = blah;
    // rather than
    //               _value = blah;
    // This is because we want the assignment operator to do notification.
    
    CL_Integer& operator= (const CL_Integer& v)
        {*this = v._value; return *this;};
    // Assign {\tt v} to this Integer.
    
    CL_Integer& operator+= (long i) 
        {*this = _value+i; return *this;};
    // Add {\tt i} to this object.

    CL_Integer& operator-= (long i) 
        {*this = _value-i; return *this;};
    // Subtract {\tt i} from this Integer;

    CL_Integer& operator*= (long i) 
        {*this = _value*i; return *this;};
    // Multiply this Integer by {\tt i}.

    CL_Integer& operator/= (long i) 
        {*this = _value/i; return *this;};
    // Divide this Integer by {\tt i}.

    CL_Integer& operator%= (long i) 
        {*this = _value%i; return *this;};
    // Assign to this Integer the remainder when it is divided by {\tt i}.

    CL_Integer& operator|= (long i) 
        {*this = _value | i; return *this;};
    // Assign to this Integer the bitwise {\sc or} of its value and {\tt i}.

    CL_Integer& operator&= (long i) 
        {*this = _value & i; return *this;};
    // Assign to this Integer the bitwise {\sc and} of its value and {\tt i}.

    CL_Integer& operator^= (long i) 
        {*this = _value ^ i; return *this;};
    // Assign to this Integer the bitwise exclusive {\sc or} of its value
    // and {\tt i}.

    CL_Integer& operator<<= (long i) 
        {*this = _value << i; return *this;};
    // Shift this Integer left {\tt i} bits.

    CL_Integer& operator>>= (long i) 
        {*this = _value >> i; return *this;};
    // Shift this Integer right {\tt i} bits.



    // --------------- Storage and retrieval ----------------------------

    long StorableFormWidth () const
        { return sizeof (CL_ClassId) + sizeof  _value; };
    // Return the number of bytes needed to store an Integer on a Stream.
    // This method overrides the one inherited from Object.

    bool ReadFrom (const CL_Stream&);
    // Read this Integer's value from the Stream. 
    // This method overrides the one inherited from Object.

    bool WriteTo  (CL_Stream&) const;
    // This method overrides the one inherited from Object.

    CL_String AsString () const;
    // Return a String containing the decimal representation of this Integer.
    // This method overrides the one inherited from Object.

    void FromStream (istream& stream);
    // Override the method inherited from Object. 

    // --------------------------- Basic methods -------------------
    
    CL_ClassId ClassId() const { return _CL_Integer_CLASSID;};
    
    const char* ClassName() const {return "CL_Integer";};

    CL_Object* Clone() const {return new CL_Integer (*this);};

    // ------------------ End public protocol ----------------------

    

protected:
    long _value;
};



inline short CL_Integer::Compare (const  CL_Integer& o) const
{
    return _value < o._value  ? -1 :  ((_value == o._value) ? 0 : 1);
}

inline short CL_Integer::Compare (const  CL_Object& o) const
{
    return IsA (o) ? Compare ((const CL_Integer&) o)
        : (this < (CL_Integer*) &o ? -1 :  1);
}

inline bool CL_Integer::operator< (const CL_Object& o) const
{
    return IsA (o) && _value < ((CL_Integer&) o).Value();
}

    

inline bool CL_Integer::operator<= (const CL_Object& o) const
{
    return IsA(o) && _value <= ((CL_Integer&) o).Value();
}

    

inline bool CL_Integer::operator== (const CL_Object& o) const
{
    return IsA (o) && _value == ((CL_Integer&) o).Value();
}

    

inline bool CL_Integer::operator>= (const CL_Object& o) const
{
    return IsA(o) && _value >= ((CL_Integer&) o).Value();
}

    

inline bool CL_Integer::operator> (const CL_Object& o) const
{
    return IsA(o) && _value > ((CL_Integer&) o).Value();
}

    

inline bool CL_Integer::operator!= (const CL_Object& o) const
{
    return !IsA(o) || _value != ((CL_Integer&) o).Value();
}


inline void CL_Integer::operator= (const CL_Object& s)
{
    if (CheckClassType (s, "CL_Integer::operator="))
        *this = ((const CL_Integer&) s)._value;
}

    

#endif
    


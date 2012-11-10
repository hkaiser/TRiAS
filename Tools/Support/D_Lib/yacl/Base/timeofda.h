

#ifndef _timeofday_h_
#define _timeofday_h_





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




// This is an encapsulation of a particular time of day. It supports
// TimeOfDay arithmetic and comparison. The static {\tt Now} method returns
// the current time. The printable
// form of a TimeOfDay is one of the following:
// \par{\tt\begin{tabular}{ll}
//            Time_Normal    &    1:30 pm   \\
//            Time_Military  &    13:30:23  \\
// \end{tabular}}




#ifdef __GNUC__
#pragma interface
#endif

#include "base/string.h"

//[ Global
enum TimePrintForm { Time_Normal, Time_Military};
// The {\tt TimePrintForm} enumeration specifies the formats of the {\tt
// PrintString} method's return value.
//] Global

class YACL_BASE  CL_TimeOfDay: public CL_Object {

public:

    //
    // ------------- Constructors and destructors ----------------------
    //

    CL_TimeOfDay ();
    // Construct an empty time object, representing midnight.

    CL_TimeOfDay (short hour, short minute, short second);
    // Construct the given time. The parameters must all be in the correct
    // ranges: $0 \le {\tt hour} \le 23$, $0 \le {\tt minute} \le 59$ and $0
    // \le {\tt second} \le 59$. If all three are zero, it represents midnight.

    CL_TimeOfDay (const char* s);
    // Construct a TimeOfDay from the given string, assuming that it
    // contains a representation in one of the following four forms: {\tt
    // Time_Normal}, {\tt Time_Military}, four digits ({\tt hhmm}) or six
    // digits ({\tt hhmmdd}).
    
    CL_TimeOfDay (long nsecs);
    // Construct a TimeOfDay with the given number of seconds since
    // midnight.
    
    CL_TimeOfDay (const CL_TimeOfDay&);
    // Copy constructor.
    
    ~CL_TimeOfDay ();
    // Destructor.

    //
    // ---------------------- Access ----------------------------------
    //

    short Hour() const;
    // Return our hour.

    short Minute () const;
    // Return our minute.

    short Second () const;
    // Return our second.

    CL_String PrintString (TimePrintForm form = Time_Normal) const;
    // Return a printable form of this TimeOfDay, according to the
    // parameter.


    //
    // --------------------- Comparison ------------------------------
    //

    bool operator<  (const CL_TimeOfDay& t) const
        {return _numSecs < t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is earlier than {\tt t}.

    bool operator<= (const CL_TimeOfDay& t) const
        {return _numSecs <= t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is earlier than or equal to {\tt t}.

    bool operator>  (const CL_TimeOfDay& t) const
        {return _numSecs > t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is later than {\tt t}.

    bool operator>= (const CL_TimeOfDay& t) const
        {return _numSecs >= t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is no earlier than {\tt t}.

    bool operator== (const CL_TimeOfDay& t) const
        {return _numSecs == t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is the same as {\tt t}.

    bool operator!= (const CL_TimeOfDay& t) const
        {return _numSecs != t._numSecs ? TRUE : FALSE;};
    // Return TRUE if this  TimeOfDay is not the same as {\tt t}.

    bool operator<  (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is earlier than it.

    bool operator<= (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is earlier than or the same as it.

    bool operator>  (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is later than it.

    bool operator>= (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is no earlier than it.

    bool operator== (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is equal to it.

    bool operator!= (const CL_Object& obj) const;
    // Cast the parameter down to a TimeOfDay and return TRUE if this
    // TimeOfDay is not equal to it.

    short Compare (const CL_TimeOfDay&) const;
    // Return $-1$, 0 or $+1$ according to whether this TimeOfDay is earlier
    // than, equal to or later than the parameter.

    short Compare (const CL_Object&) const;
    // Cast the parameter down to a TImeOfDay, call the other {\tt
    // Compare} method and return the result.

    bool IsBetween (const CL_TimeOfDay& t1, const CL_TimeOfDay& t2) const;
    // Return TRUE if this time is between the two given times. The
    // parameters need not necessarily be in any order.
    

    //
    // -------------------------- Modification ----------------------
    //

    // Assignment
    
    CL_TimeOfDay& operator= (const CL_TimeOfDay&);
    // Assign the parameter to this TimeOfDay.
    
    virtual void operator= (const char*);
    // Convert the given string into a TimeOfDay via {\tt ParseAndConvert}
    // and assign the result to this TimeOfDay. If the string is not
    // syntactically correct, the time is set to midnight.

    virtual void operator= (const CL_Object&);
    // Check that the given object is a TimeOfDay (via {\tt IsA()}), downcast
    // it and assign it to this TimeOfDay.

    //
    // -------------------------- TimeOfDay arithmetic -------------------
    //

    
    // add or subtract the given number of seconds
    
    CL_TimeOfDay  operator+  (long num_secs) const;
    // Return a TimeOfDay obtained by adding {\tt num_secs} seconds to this
    // TimeOfDay. The result may ``roll over'' to a smaller value.

    CL_TimeOfDay& operator+= (long num_secs);
    // Add {\tt num_secs} seconds to this
    // TimeOfDay. Return this TimeOfDay.

    CL_TimeOfDay  operator-  (long num_secs) const
        {return operator+ (-num_secs);};
    // Return a TimeOfDay obtained by subtracting {\tt num_secs} seconds from
    // this TimeOfDay. The result may ``roll over'' to a larger value.

    CL_TimeOfDay& operator-= (long num_secs);
    // Subtract  {\tt num_secs} seconds from
    // this TimeOfDay. Return this TImeOfDay.

    long operator-   (const CL_TimeOfDay& t) const
        {return (_numSecs - t._numSecs);};
    // Return the number of seconds between this TimeOfDay and the given time.


    //
    // ------------------------ Static  methods --------------------------
    //

    static CL_TimeOfDay Now ();
    // Return a time object containing the current time

    static long ParseAndConvert (const char* s);
    // Validate the given string as representing a given time of day,
    // and return either $-1$ if it's not a valid time, or else the
    // number of seconds since midnight. The given string must
    // contain a time representation in any of four forms: {\tt Time_Normal},
    // {\tt Time_Military}, four digits ({\tt hhmm}) or six
    // digits ({\tt hhmmdd}).

    // ----------------- Saving and restoration --------------------

    void FromStream (istream&);
    // Override the method inherited from {\small\tt CL_Object}. The
    // implementation skips fill characters, and them collects numerics and
    // ':' characters; the result is then assumed to be in Time_Military
    // form and parsed.
    
    long StorableFormWidth () const;
    // Return the number of bytes needed to store this TimeOfDay in binary
    // form. The representation uses two {\tt long} cells.
    
    bool ReadFrom (const CL_Stream&);
    // Read the value of this TimeOfDay from the parameter Stream. Return
    // TRUE on success. This method overrides the inherited one.

    bool WriteTo  (CL_Stream&) const;
    // Write the value of this TimeOfDay to the parameter Stream. Return
    // TRUE on success. This method overrides the inherited one.

    CL_String AsString () const;
    // Override the method inherited from {\small\tt CL_Object}. Returns
    // TImeOfDay in {\tt Time_Military} form.


    // ----------------------- Basic methods --------------

    const char* ClassName() const { return "CL_TimeOfDay";};
    
    CL_ClassId ClassId () const {return _CL_TimeOfDay_CLASSID;};

    CL_Object* Clone () const {return new CL_TimeOfDay (*this);};
    // Return a copy of this TimeOfDay. The caller of this method is
    // responsible for destroying the returned object.
    
    //
    // -------------------- End public protocol ---------------------
    //
    

protected:

    // The representation used is the number of seconds since midnight:
    long _numSecs;
};




inline CL_String CL_TimeOfDay::AsString() const
{
    return PrintString (Time_Military);
}


inline void CL_TimeOfDay::operator= (const CL_Object& obj)
{
    if (CheckClassType (obj, "CL_TimeOfDay::op= (CL_Object&)"))
        *this = (const CL_TimeOfDay&) obj;
}



inline short CL_TimeOfDay::Compare (const CL_TimeOfDay& d) const
{
    return _numSecs < d._numSecs ? -1 : (_numSecs == d._numSecs ? 0 : 1);
}


inline short CL_TimeOfDay::Compare (const CL_Object& obj) const
{
    return (!IsA (obj)) ? (this < (CL_TimeOfDay*) &obj ? -1 :  1)
        : Compare ((const CL_TimeOfDay&) obj);
}






#endif

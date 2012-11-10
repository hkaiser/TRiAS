



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





#ifdef __GNUC__
#pragma implementation
#endif



#include <iostream.h>

#include "base/integer.h"
#include "base/bytarray.h"
#include "base/bytstrng.h"
#include "base/string.h"
#include "base/stream.h"

#if defined(__SGI_DELTA_CC__)
#include "base/basicops.h"
#include "base/cmparatr.h"
#include "base/binding.h"
#pragma instantiate CL_Binding0<CL_Integer>
#pragma instantiate CL_Comparator<CL_Integer>
#pragma instantiate CL_Basics<CL_Integer>
#endif




CL_String CL_Integer::AsString () const
{
    return CL_String (_value, 1, ' ');
}


const char digits[] = "0123456789ABCDEF";

CL_String CL_Integer::InRadix (short radix) const
{
    if (radix == 10 || _value == 0)
        return AsString();
    if (radix < 2 || radix > 16)
        return "";
    unsigned long v = _value;
    char buffer[50]; // Can't have more than 50 digits
    buffer[49] = '\0';
    short n = 49;
    while (v != 0) {
        buffer[--n] = digits[v % radix];
        v /= radix;
    }
    return CL_String(&buffer[n]);
}







bool CL_Integer::WriteTo (CL_Stream& s) const
{
    return s.Write (ClassId())  && s.Write (_value);
}


bool CL_Integer::ReadFrom  (const CL_Stream& s)
{
    if (!PrepareToChange() || !ReadClassId (s) || !s.Read (_value))
        return FALSE;
    Notify ();
    return TRUE;
}

CL_Integer::~CL_Integer ()
{
}




CL_Integer CL_Integer::operator++ () // Prefix increment
{
    if (PrepareToChange ()) {
        ++_value;
        Notify();
    }
    return _value;
}


CL_Integer CL_Integer::operator++ (int) // Postfix increment
{
    long l = _value;
    if (PrepareToChange ()) {
        l = _value++;
        Notify();
    }
    return l;
}


CL_Integer CL_Integer::operator-- () // Prefix decrement
{
    if (PrepareToChange ()) {
        --_value;
        Notify();
    }
    return _value;
}


CL_Integer CL_Integer::operator-- (int) // Postfix decrement
{
    long l = _value;
    if (PrepareToChange ()) {
        l = _value--;
        Notify();
    }
    return l;
}





CL_Integer& CL_Integer::operator= (long i)
{
    if (!PrepareToChange())
        return *this;
    _value = i;
    Notify ();
    return *this;
}




void CL_Integer::FromStream (istream& stream)
{
    stream >> _value;
}



#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#include "base/binding.h"
#include "base/cmparatr.cxx"

template class CL_Binding0<CL_Integer>;
template class CL_Comparator<CL_Integer>;
template class CL_Basics<CL_Integer>;
#endif

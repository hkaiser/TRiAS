

#ifndef _strsplit_h_ /* Mon Dec 27 13:28:53 1993 */
#define _strsplit_h_





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



// This is a simple string parser that allows one to view a given String
// as made up of fields, separated by one or more occurrences of field
// separator characters This class provides the ability to iterate over
// the fields of the String.
//   More precisely, this class remembers a set of characters that are
// treated as the field separators. It provides methods {\tt Reset}, {\tt
// Next}, {\tt Scan} and {\tt Remaining}.
//
// {\tt Reset} is used to set the cursor of the StringSplitter to the
// beginning of the String being inspected.
//
// The method {\tt Next} updates the remembered field
// separators if its parameter is non-null, skips past any
// occurrences of any of the field separators, until a non-separator is
// found; it then collects characters until it finds a character that is in
// its parameter. The collected characters are returned as the field
// value.
//
//   The method {\tt Scan} collects characters in the set specified by its
// parameter (i.e., scans until finding a character not it its parameter
// set), and returns the resulting string.
//
// The method {\tt Remaining} returns what's left of the String.
//
// The functionality is provided by this class is similar to the {\tt
// Split} and {\tt Field} methods of the class String, with two differences:
// iterating through the fields is more efficient with the StringSplitter
// class, and the StringSplitter class allows to vary the field separator
// set while the
// String is being inspected. The StringSplitter does not modify the String
// it inspects.



#ifdef __GNUC__
#pragma interface
#endif


#include "base/string.h"

class YACL_BASE CL_StringSplitter: public CL_Object {

public:

    // ------------------- Construction ------------------------

    CL_StringSplitter (const CL_String& string,
                       const char* field_seps = " \t");
    // Construct a StringSplitter on the given String. and use the
    // characters in {\tt field_seps} as the set of field separator characters.
    // Remember this set of characters.

    ~CL_StringSplitter () {};
    
    // ------------------- Access ----------------------------
    
    void Reset ();
    // Reset the cursor to the beginning of the String.

    CL_String Next (const char* field_seps = NULL);
    // Return the next field, upto but not including any of the characters
    // in the specified field separator set. If the parameter is NULL, the
    // set of field separators used is unaltered. Return a null string if
    // the string has been exhausted.

    CL_String Scan (const char* char_set);
    // Scan the String until a character not in {\tt char_set} is found;
    // return the part of the String passed over during this scan.
    
    CL_String Remaining ();
    // Return what's left of the String, beginning at the current point.
    // This includes the field separator characters following the field
    // returned by the most recent call to {\tt Next}. A call to this method
    // terminates iteration; subsequent calls to Next will return the null
    // string.

    const char* ClassName () const {return "CL_StringSplitter";};
    
protected:
    long       _index;          // Right end of most recently returned field
    const CL_String& _string;   // Our string
    CL_String  _fieldSeps;      // Field separators currently used
};



#endif /* _strsplit_h_ */



#ifndef _string_h_
#define _string_h_





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



// This class provides the basic functionality for manipulating a
// printable string of characters.




#ifdef __GNUC__
#pragma interface
#endif

#include "base/object.h"

class YACL_BASE CL_StringSequence;
class YACL_BASE CL_Substring;
class YACL_BASE CL_StringSplitter;

class YACL_BASE  CL_String: public CL_Object {

public:
    //
    // ----------------------------- Constructors -------------------------
    //

    CL_String ();
    // Default constructor: constructs the null string of zero length.

    CL_String (const char* strg);
    // Construct a string from the given null-terminated char array.

    CL_String (long value, short minwidth = 1, char padChar = ' ');
    // Construct a string containing the digits of {\tt value} in a field
    // at least {\tt minwidth} characters wide. Pad, if necessary, with as
    // many of the given padding characters {\tt padChar} as necessary on
    // the left.

    CL_String (CL_ByteArray& b);
    // Copy b's contents and append a null byte.
    
    CL_String (char c, short n);
    // Construct a String containing {\tt c}  repeated {\tt n} times.
                
    CL_String (const CL_String& strg);
    // Copy constructor.
    
    ~CL_String();

    //
    // -------------------------- Conversion -------------------------------
    //

    operator const char* () const;
    // Return pointer to null-terminated {\tt char} array representation.
    // The caller of this method should not modify the returned {\tt char}
    // array.

    const char* AsPtr() const;
    // Synonym for {\tt operator const char*}.

    long AsLong() const;
    // Find the longest prefix that is all digits and return them as
    // a {\tt long} value.

    double AsDouble () const;
    // Find the longest prefix that looks like a {\tt double} number and
    // return it as a {\tt double} value.
    

    bool ConvertToLong (long& l) const;
    // Convert this String to a long and return the result in the
    // parameter. The method returns TRUE if the string was entirely
    // numeric, and FALSE otherwise.
    
    // ----------- Structural manipulations, substrings ------------------

    long Size() const {return _size;} ;
    // Return the number of characters in the string.

    long Length() const { return _size; };
    // Return the number of characters in the string.
    
#ifndef _MSC_VER
    // Microsoft Visual C++ has trouble with this operator, because it
    // thinks the operator conflicts with a global one implicitly provided
    // by the char* conversion. So I've ifdef'ed it out. It should not
    // affect the use of operator[] on Strings, though.
    
    char operator[] (long index) const;
    // Return character at given index. Indices are reckoned from 0,  as is
    // usual in C. This method checks that the parameter is in the legal
    // range.

#endif

    char operator() (long index) const;
    // Same as operator[], but without bounds checking. 

    CL_String operator() (long position, long size) const;
    // Return the substring beginning at the given position and of the
    // given size. This is a const method, so its return value cannot be
    // modified.
    
    CL_Substring operator() (long position, long size);
    // Return the substring beginning at the given position and of the
    // given size. The position is reckoned from 0. Note that this is not a
    // const method, because the returned substring can be assigned to, thus
    // modifying this String. For example, you can write
    //
    // \begin{verbatim}
    //         CL_String myString ("Hello, world!");
    //         myString(0, 6) = "Goodbye, cruel";
    // \end{verbatim}
    //
    // \noindent
    // thus modifying {\tt myString} to become ``{\tt Goodbye, cruel world}.''

    CL_Substring Suffix (long position);
    // Return the suffix beginning at the given position. Note that this
    // is not a {\tt const} method, because the returned substring can be
    // assigned to. The implementation simply forwards to call to {\tt
    // operator()}.

    CL_String Suffix (long position) const;
    // Return the substring beginning at the given position and of the
    // given size. The position is reckoned from 0. This is a const method,
    // so its return value cannot be modified.
    
    // -------------------- Search-related methods ---------------------


    // --- Character searches --
    
    long CharIndex (char c, long pos = 0L) const;
    // Return the index of the first position, at or right of {\tt pos}, that
    // contains the character {\tt c}. Return $-1$ if no such position exists.

    long NCharIndex (char c, long pos = 0L) const;
    // Return the index of the first position, at or right of {\tt pos}, that
    // {\it does not\/} contain the character {\tt c}. Return $-1$ if no
    // such position exists.

         
    long CharIndex (const char* s, long pos = 0L) const;
    // Return the index of the first position, at or right of {\tt pos}, that
    // contains {\it any one\/} of the characters in {\tt s}. Return $-1$ if
    // no such position exists.

    long NCharIndex (const char* s, long pos = 0L) const;
    // Return the index of the first position, at or right of {\tt pos}, that
    // contains none of the characters in {\tt s}. Return $-1$ if no such
    // position exists.

    
    // ---- String searches ---

    
    bool IsPrefixOf (const char* p) const;
    // Return TRUE if this String is a prefix of {\tt p}, and FALSE otherwise.

    long Index (const char* s, long pos = 0, long n = 1) const;
    // Return the left end of the $n$-th occurrence of the string {\tt s} in
    // this String; begin the search for {\tt s} at position pos. Return
    // $-1$ if  no more than $n-1$ such occurrences of {\tt s} were found.

    virtual bool Replace (long pos, char c);
    // Replace the character at position {\tt pos} with {\tt c}. Return
    // TRUE on success, FALSE if failed (i.e., if {\tt pos} is out of
    // range or if a pre-change dependent refused permission to change).

    virtual bool Replace (long pos, long n, const char* strg);
    // Replace the $n$-character substring beginning at position {\tt pos}
    // with the character string {\tt strg}. If $n$ is
    // zero, {\tt strg} will be inserted into this string
    // just before position {\tt pos}.
    //
    // Return TRUE on success, FALSE if failed (i.e., if {\tt pos} is out of
    // range, memory allocation failed or a pre-change dependent refused
    // permission to change).
    
    virtual long Replace (const char* s1, const char* s2, long pos = 0,
                          long n = 1);
    // Scan this String beginning at position {\tt pos}, and replace the
    // first $n$ occurrences of {\tt s1} with {\tt s2}. 
    // Return the number of successful replacements that occurred.
    // Note that if {\tt s2} is NULL or points to a null string, the
    // occurrences of {\tt s1} are removed. If s1 is null, no replacements
    // will be made.
    //
    //    This method returns 0 if memory allocation fails.

    virtual long ReplaceAll (const char* s1, const char* s2, long pos = 0);
    // Beginning at position {\tt pos}, replace all occurrences of {\tt s1}
    // with {\tt s2}, as in the {\tt Replace} method. Return the number of
    // replacements that were made.

    

    // ------------------------ Decomposition ----------------------------
    //
    
    CL_String Field (long n, const char field_seps[] = " \t") const;
    // View this string as being made up of fields, separated by one or
    // more characters from the null-terminated string {\tt field_seps}. Return
    // the $n$-th field. Fields are indexed from 1, i.e., $n = 1$ returns the
    // leftmost field. If $n$ is 0, the entire String is returned. (This
    // function is similar to the functionality in {\tt awk}.)
    //
    // This is a {\tt const} method, since it does not modify this String.

    CL_StringSequence Split (const char field_seps[] = " \t") const;
    // View this String as being made up of fields, separated by one or
    // more characters from the null-terminated string {\tt field_seps}. Return
    // the sequence of fields in the String. For example, if  {\tt field_seps}
    // contains the string ``\verb|! ,|'' then the sequence of
    // fields in the String ``{\tt Hello, world!}''  contains the two
    // Strings ``{\tt Hello}'' and ``{\tt world}.''
    //
    // This is a {\tt const} method, since it does not modify this String.
    
    CL_StringSequence Split (char field_sep) const;
    // View this String as being made up of fields, separated by {\it one\/}
    // occurence of the given character. Return the sequence of fields in
    // this string. For example, if {\tt field_sep} is the semicolon and
    // this String contains ``\verb|c:\dos;;c:\windows|,'' then the returned
    // StringSequence contains the three Strings
    // ``\verb|c:\dos|,''  ``'' and
    // ``\verb|c:\windows|.'' (Note that the second element of the
    // Sequence is the null String.)
    //
    // This is a {\tt const} method, since it does not modify this String.
    
    long Split (CL_String fld[], long n, const char field_seps[] = " \t")
        const;
    // View this String as being made up of fields, separated by one or
    // more characters from the string {\tt field_seps}. Return the value of
    // {\tt fld} as follows:
    //
    // \begin{tabular}{ll}
    //  {\tt fld[0..n-2]} &   contains the first $n-1$ fields, if there are
    //                     that many fields\\
    //  {\tt fld[n-1]}    &  contains the remaining part of the String\\
    // \end{tabular}
    // 
    // Return the actual number of cells used in {\tt fld} as the function
    // value.
    // Note that {\tt fld} is an array of String objects provided by the
    // caller, and must have at least $n$ Strings in it.
    //
    // This is a {\tt const} method, since it does not modify this String.

    
    //
    // ------------------------ Comparison -----------------------------------
    
    bool operator<  (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // less than it, and FALSE otherwise.

    bool operator<= (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // less than or equal to it, and FALSE otherwise.

    bool operator>  (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // greater than it, and FALSE otherwise.

    bool operator>= (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // greater than or equal to it, and FALSE otherwise.

    bool operator== (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // equal to it, and FALSE otherwise.

    bool operator!= (const CL_Object& strg) const;
    // Cast {\tt strg} down to a String; then return TRUE if this String is
    // different from it, and FALSE otherwise.

    

    bool operator<  (const char* strg) const;
    // Return TRUE if this String occurs earlier than {\tt strg} in
    // dictionary order, and FALSE otherwise.

    bool operator<= (const char* strg) const;
    // Return TRUE if this String is less than or equal to {\tt strg} in
    // dictionary order, and FALSE otherwise.

    bool operator>  (const char* strg) const;
    // Return TRUE if this String occurs later than {\tt strg} in
    // dictionary order, and FALSE otherwise.

    virtual bool operator>= (const char* strg) const;
    // Return TRUE if this String is equal or larger than {\tt strg} in
    // dictionary order, and FALSE otherwise.

    virtual bool operator== (const char* strg) const;
    // Return TRUE if this String equals {\tt strg}, and FALSE otherwise.

    virtual bool operator!= (const char* strg) const;
    // Return TRUE if this String differs from {\tt strg}, and FALSE otherwise.

    short Compare (const CL_Object& obj) const;
    // Compare returns $-1$ if this String less than the given string, 0 if
    // the two are equal, and $+1$ if this String is greater in dictionary
    // order. The method issues a
    // runtime error message if the given object does not have the class id
    // of a String.
    
    short Compare (const CL_String& s) const;
    // Compare returns $-1$ if this String less than {\tt s}, 0 if
    // the two are equal and $+1$ if this String is greater in dictionary
    // order.

    short CompareIgnoringCase (const char* s) const
        {return InLowerCase().Compare (CL_String (s).InLowerCase());};
    // Compare this String with {\tt s}, ignoring case. The return value is
    // as in the {\tt Compare} method.
    
    bool CompareWith (const CL_String& obj, CL_ComparisonOperator op) const;
    // ``Indirect'' comparison: return TRUE if the relationship described by
    // {\tt op} holds between this object and {\tt obj}. This method
    // overrides the inherited method. For example, \par
    // {\tt   CL_String ("Two").CompareWith ("Three", CL_CMP_LESSTHAN)}\par
    // \noindent
    // returns FALSE, since the string ``{\tt Two}'' occurs later than
    // ``{\tt Three}'' in dictionary order.
    
    bool CompareWith (const CL_Object& obj, CL_ComparisonOperator op) const;
    // Overrides Object's {\tt CompareWith} method. Checks that {\tt obj}'s
    // class id is the same as String's and then invokes {\tt Compare} with
    // {\tt obj} cast down to String. Returns FALSE if class id does not
    // match.



    // --------------------------String modification ----------------------

    virtual bool Insert (char c, long position = -1);
    // Insert a character into the String, immediately to the right of the
    // given position, thus expanding the String. The default position of
    // $-1$ specifies insertion at the left end of the String. 
    // Return TRUE if successful, FALSE if either an invalid position is
    // specified, a pre-change dependent refused change, or memory
    // allocation failed.

    virtual bool Insert (const char* p, long position = -1);
    // Insert a null-terminated character string into this String.
    // The effect is equivalent to assigning to the null substring at the
    // given position; i.e., {\tt s.Insert (p, pos)} is the same as {\tt s
    // (pos+1, 0) = p}.

    inline bool Append (char c);
    // Append the given character to the String. This method is equivalent
    // to using the {\tt +=} operator, but is a little more efficient when
    // appending a single character.
    //
    // Return TRUE if a deletion was carried out, FALSE otherwise
    // (e.g., if the given position was outside the range of positions for
    // the string).
    

    virtual bool Delete (long pos, long len = 1);
    // Delete the substring of length {\tt len} beginning at position {\tt
    // pos}. Return TRUE if a deletion was carried out, FALSE otherwise
    // (e.g., if the given position was outside the range of positions for
    // the string).
    
    bool AssignWithFormat (const char* format, ...);
    // Create a {\tt char} buffer whose contents are identical to those
    // produced if the parameters were passed to {\tt sprintf}; assign the
    // result to this 
    // String. The resulting String should not exceed 1000 chars in
    // length, and (unfortunately) this cannot be checked by this method
    // because not all platforms allow such a check reliably.
    
    // --------- Assignments of various kinds
    
    virtual void operator= (const char* strg);
    // Assign the null-terminated string {\tt strg} to this String.

    virtual CL_String& operator= (const CL_String& strg);

    virtual void operator= (const CL_Object& strg);
    // Check that the given parameter is really a String (via the
    // inherited {\tt IsA} method), and
    // assign its value to this String.
    
    virtual void operator= (long l);
    // Assign to this String the decimal representation of {\tt l}.

    virtual void operator= (double d);
    // Convert the given double value into a String and assign it to
    // this String.

    

    // Concatenations of various kinds
    
    virtual CL_String operator+  (const char* strg) const;
    // Return the String obtained by concatenating the null-terminated
    // parameter {\tt strg} to this String.

    virtual CL_String operator+  (const CL_String& strg) const;
    // Return the String obtained by concatenating {\tt strg} to this String.

    virtual CL_String& operator+= (const char* strg);
    // Append the given (null-terminated) string {\tt strg} to this String,
    // and return this String.

    virtual CL_String& operator+= (const CL_String& strg);
    // Append  {\tt strg} to this String and return this String.

    CL_String operator+ (long v) const;
    // Convert the long value in decimal to a String and return the result of
    // appending it to this String.

    CL_String& operator+= (long v);
    // Append the string representation of the long value (in decimal) to
    // this String, and return this String.

    CL_String& operator+= (char c) {Append (c); return *this;};
    // Append {\tt c} to this String, and return this String.
    
    virtual CL_String operator- (const char* s) const;
    // ``Subtraction'' operator:
    // Return the String resulting from the removal of the suffix
    // beginning with the first occurrence of the given string.
    // Thus ``{\tt Alpha Beta Gamma}'' - ``{\tt Beta}'' yields ``{\tt
    // Alpha }''. If the given
    // string {\tt s} does not occur in this String, simply return (a copy
    // of) this String. 

    CL_String& operator-= (const char* s)
        { *this = *this - s; return *this;};
    // ``Subtract'' {\tt s} from this String. Return this String.
    

    // --------------------- Storage and restoration -------------------
    
    virtual long StorableFormWidth () const;
    // Override the method inherited from Object.

    virtual bool ReadFrom (const CL_Stream&);
    // Read and reconstruct this String from the binary representation in
    // the given stream. Return TRUE on success, FALSE if failed for any
    // reason, including when a pre-change dependent disallows the change.

    virtual bool WriteTo  (CL_Stream&) const;
    // Write the passive binary representation of this String into the
    // given stream. Return TRUE if successful, FALSE otherwise.

    CL_String AsString () const
        { return *this; };
    // Return a copy of this String. This method overrides the inherited
    // one.

    void FromStream (istream& stream);
    // Override the method inherited from Object. The
    // implementation skips any occurrences of the current fill character
    // of {\tt stream}, and then collects non-fill characters into this
    // String.

    virtual istream& ReadLine (istream& stream);
    // Read everything upto (but not including) the next end-of-line marker (or
    // end-of-file) on {\tt stream}, and set this String's value to the
    // result. Return the parameter {\tt stream}.

    virtual bool ReadStream (istream& stream);
    // Read in the entire contents of {\tt stream}, beginning at its
    // current position, into this String. Return TRUE on success, FALSE
    // on failure (e.g., empty stream, memory allocation failure, stream
    // too big, or a pre-change dependent refused permission). Under DOS
    // and Windows, this method fails if the stream is bigger than 65000
    // characters.
    
    // ------------------------ Miscellaneous methods ----------------
    
    virtual bool PadTo (long n, char pad_char = ' ',
                        bool left_justified = TRUE);
    // Pad this String (if necessary)  to fill out  to $n$
    // characters.   The padding  character is the second parameter, and  the
    // third parameter specifies whether the padding occurs on the right side
    // (i.e.,  left   justification)   or   the   left   side   (i.e.,  right
    // justification).   If $n$ is smaller than this String's size, it remains
    // unchanged. Return TRUE if padding occurred, FALSE if either the String
    // remained unchanged or memory allocation failed.

    CL_String InUpperCase () const;
    // Return this String with all lower-case letters replaced by upper-case
    // ones.

    CL_String InLowerCase () const;
    // Return this String with all upper-case letters replaced by
    // lower-case ones.

    virtual long ToUpper ();
    // Convert all lower-case characters to upper case. Return the number of
    // characters converted. Note that this can be combined with the
    // {\tt operator()} to operate on substrings; e.g.,
    //
    // \begin{verbatim}
    //               myString (10,3).ToUpper();
    // \end{verbatim}
    //
    // converts all lower-case characters between positions 10 and 12 to
    // upper-case.

    virtual long ToLower ();
    // Convert all upper-case characters to lower case. Return the number of
    // characters converted.

    virtual bool WordCapitalize ();
    // If this String begins with an alphabet, render the first letter
    // of the first word upper case, and all other letters in that
    // word lower case. Return TRUE if this change was effected, and
    // FALSE otherwise.
    
    //
    // ------------- Basic methods -------------------------
    //

    const char* ClassName() const {return "CL_String";};

    CL_ClassId ClassId() const { return _CL_String_CLASSID;};

    CL_Object* Clone() const {return new CL_String (*this);};

    // -------------------- End public protocol ------------------


    
protected:

    CL_String (const char* s, long n);
    // Protected constructor, for internal use only. Builds and returns a
    // String containing  the first {\tt n} bytes from {\tt s}.

    bool _Init (long size);

    bool _DoInsert (const char*, long);
    // Do insertion without notification.
    
    friend CL_Substring;
    friend CL_StringSplitter;
    
    char* _string;
    long  _capacity;
    long  _size;
};



// The Substring class represents a substring of some String. A Substring
// instance can only be created by String methods, because Substring's
// constructor and destructor are protected and String is a friend of
// Substring. Substring declares assignment operators inorder to ensure that
// all are properly inherited from String.
//
// Substring does its magic using the notification mechanism.




class YACL_BASE CL_Substring: public CL_String {

public:

    virtual void operator= (const char* strg)
        {CL_String::operator= (strg);};
    // Override all  assignment operators with methods that forward
    // their calls to the inherited methods. This is necessary because the
    // assignment operator is not inherited.
    
    virtual CL_String& operator= (const CL_String& strg)
        {return CL_String::operator= (strg);};

    virtual void operator= (const CL_Object& strg);

    virtual void operator= (long l)
        {CL_String::operator= (l);};

    virtual void operator= (double d)
        {CL_String::operator= (d);};
    
    ~CL_Substring ();

protected:
    
    CL_Substring (CL_String& s, long pos, long length);
    // The constructor is protected, so that a Substring cannot be directly
    // constructed.

    CL_Substring (const CL_Substring&);
    // The copy constructor is protected, so that a Substring cannot be
    // copied.

    bool _Modified ();
    // The method called to notify this Substring when its value changes, so
    // that it may  modify the real client.

    friend CL_String;
    CL_String& _client; // The String that we are a substring of
    long       _pos;    // Where the substring begins
    long       _len;    // How long the substring was when constructed
};



inline const char* CL_String::AsPtr() const
{
    return _string;
}

inline CL_String::operator const char* () const
{
    return _string;
}


#ifndef _MSC_VER
// Return character at given index
inline char CL_String::operator[] (long index) const
{
    assert (index >= 0 && index < _size,
            ("CL_String::operator[]:"
            " invalid index %ld string size %ld", index, Size()));
#if defined(__DOS__) || defined(__MS_WINDOWS__)
    return _string[(short) index];
#else
    return _string[index];
#endif
}
#endif



inline char CL_String::operator() (long index) const
{
#if defined(__DOS__) || defined(__MS_WINDOWS__)
    return _string[(short) index];
#else
    return _string[index];
#endif
}


inline CL_String CL_String::operator() (long index, long len) const
{
    return CL_String (_string+index, len);
}


inline CL_String CL_String::Suffix (long position) const
{
    return (*this) (position, Size() - position);
}


inline void CL_String::operator= (const CL_Object& s)
{
    if (CheckClassType (s, "CL_String::op="))
        *this = (const CL_String&) s;
}


inline CL_Substring CL_String::Suffix (long position)
{
    return (*this) (position, Size() - position);
}


inline CL_String operator+ (const char* s1, const CL_String& s2)
{
    return CL_String (s1) + s2;
}

inline bool CL_String::Append (char c)
{
    return Insert (c, Size() - 1);
}


inline CL_String& CL_String::operator+= (long v)
{
    *this = *this + v;
    return *this;
}


inline bool CL_String::CompareWith (const CL_Object& obj,
                                    CL_ComparisonOperator op) const
{
    return ClassId() == obj.ClassId() ?
        CompareWith ((const CL_String&) obj, op) : FALSE;
}

inline void CL_Substring::operator= (const CL_Object& strg)
{
    CL_String::operator= (strg);
}

#endif

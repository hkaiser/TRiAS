

#ifndef _stream_h_ /* Tue Feb 22 11:29:17 1994 */
#define _stream_h_





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




// {\tt CL_Stream} is an abstract class representing the notion of a
// positionable binary data stream. It provides operators and methods for
// data transfer between objects and the stream. All operators and methods
// are expressed in terms of six {\it core\/} pure-virtual methods:
//
// \begin{itemize}
// \item {\tt Read (uchar*, long}, which reads a given number of bytes from
// the stream;
// \item {\tt Write (uchar*, long}, which writes a given number of bytes to
// the stream;
// \item {\tt SeekTo (long)}, which positions the Stream's cursor;
// \item {\tt Size()}, which returns the Stream's current size in bytes;
// \item {\tt ChangeSize (long)}, which changes the Stream's size;
// \item {\tt Offset ()}, which returns the cursor position.
// \end{itemize}
//
// \noindent
// When the {\tt Remember} method is called, the Stream begins to remember
// addresses of all instances of objects derived
// from {\tt CL_Object}  that have been written to it.
// An attempt to  write an object that has already been written
// results in writing a reference to the previously-written object. This
// is so that cyclic data structures can be
// written and read from the Stream without danger of infinite recursion.
// When it is necessary to make the Stream forget the remembered object
// addresses, its {\tt Forget} method must be called.



#ifdef __GNUC__
#pragma interface
#endif

#include "base/object.h"



typedef long CL_Offset;

class YACL_BASE CL_Stream: public CL_Object {
 
public:

    CL_Stream ();
    // Constructor: create an empty Stream.

    ~CL_Stream ();

  
    // ----------------- Read operations -------------------------

    virtual long Read (uchar* buffer, long n) const = 0;
    // [Pure virtual.] Read {\tt n} bytes from current position. Must return
    // number of bytes read, 0 on eof, $-1$ on error.
 
    inline long Read (CL_Offset offset, uchar* buffer, long
                      num_bytes) const;
    // Read num_bytes bytes into buffer, starting at the given offset.
    // Returns number of bytes read, 0 on eof, $-1$ on error. The
    // implementation executes {\tt SeekTo} followed by (the pure virtual)
    // {\tt Read}.

    inline bool Read (long& value) const;
    // Read a long value. Return TRUE on success, FALSE on failure
    // (i.e., end of file or i/o error). 
    
    const CL_Stream& operator>> (long& value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (long&)}.
    
    inline bool Read (CL_Offset offset, long& value) const;
    // Read a {\tt long} value from the given position. Return TRUE on
    // success, FALSE on failure (i.e., end of file or I/O error). The
    // implementation uses {\tt SeekTo} followed by  {\tt Read (long&)}.
    

    inline bool Read (short& value) const;
    // Read a {\tt short} value. Return TRUE on success, FALSE on failure. The
    // implementation uses the pure virtual {\tt Read}.
    
    const CL_Stream& operator>> (short& value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (short&)}.
    
    
    inline bool Read (char& value) const;
    // Read a {\tt char} value. Return TRUE on success, FALSE on failure.  The
    // implementation uses the pure virtual {\tt Read}.
    
    const CL_Stream& operator>> (char& value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (char&)}.
    
    inline bool Read (uchar& value) const;
    // Read an {\tt unsigned char} value. Return TRUE on success, FALSE on
    // failure.
    
    const CL_Stream& operator>> (uchar& value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (uchar&)}.
    
    inline bool Read (CL_Offset offset, short& value) const;
    // Read a short value from the given position. Return TRUE on
    // success, FALSE on failure (i.e., end of file or I/O error).


    bool Read (CL_Object& obj) const;
    // Generic reading: uses the virtual {\tt ReadFrom} method. {\tt obj}'s
    // {\tt ReadFrom} is called only if {\tt obj} has not already been
    // read from the Stream; this is to prevent duplication.  The address
    // of each read object is remembered by the Stream.


    const CL_Stream& operator>> (CL_Object& value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (CL_Object&)}.
    
    bool Read (CL_Offset offset, CL_Object& obj) const;
    // Position this Stream to {\tt offset} and read {\tt obj}. The
    // implementation uses {\tt SeekTo} followed by {\tt Read (CL_Object&)}.


    bool Read (CL_ObjectPtr& p) const;
    // Read the value in the Stream, construct an object from it, and
    // assign it to the parameter. If the Stream contains the ``null
    // pointer'' indicator, then {\tt p} is assigned NULL. The caller of
    // this method owns the returned object.
    
    const CL_Stream& operator>> (CL_ObjectPtr value) const
        {Read (value); return *this;};
    // Implemented using {\tt Read (CL_ObjectPtr&)}.

    bool Read (CL_Offset offset, CL_ObjectPtr obj) const;
    // Position the Stream at {\tt offset}, read the object at that position
    // and return it in {\tt obj}.  The caller of
    // this method owns the returned object.
    
    // ----------------- Write operations ------------------------

    virtual bool Write (uchar* buffer, long num_bytes) = 0;
    // [Pure virtual] Write at current position. 
    // This is a core method, and must be overridden by the
    // derived class.

    inline bool Write (CL_Offset offset, uchar* buffer, long n);
    // Seek to position {\tt offset}, and
    // write {\tt n} bytes from {\tt buffer}. Offset 0 is the beginning of
    // the Stream.


    inline bool Write (long v);
    // Write the {\tt long} value {\tt v} at the current position. Return
    // TRUE on success, FALSE on failure  (e.g., I/O error).
    
    CL_Stream& operator<< (long value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (long)}.
    
    inline bool Write (CL_Offset offset, long v);
    // Write the {\tt long} value {\tt v} at the given position. Return TRUE on
    // success, FALSE on failure (e.g., I/O error).
    
    inline bool Write (short value);
    // Write the given short value at the current position. Return TRUE on
    // success, FALSE on failure.
    
    CL_Stream& operator<< (short value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (short)}.
    
    inline bool Write (CL_Offset offset, short value);
    // Write {\tt value} at the given position {\tt offset}. Return TRUE on
    // success, FALSE on failure (i.e., end of file or I/O error).

    inline bool Write (uchar value);
    // Write an {\tt unsigned char} value. Return TRUE on success, FALSE on
    // failure.
    
    CL_Stream& operator<< (uchar value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (uchar)}.
    
    inline bool Write (char value);
    // Write a char value. Return TRUE on success, FALSE on failure.
    
    CL_Stream& operator<< (char value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (char)}.


    bool Write (CL_ObjectPtr p);
    // Write the object pointed to by p to the stream. If the parameter is
    // NULL, write the ``null pointer'' indicator. Otherwise, use the object's
    // WriteTo method.
    
    CL_Stream& operator<< (CL_ObjectPtr value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (CL_ObjectPtr)}.

    bool Write (const CL_Object& obj);
    // Generic writing: uses the WriteTo method. The parameter's
    // {\tt WriteTo} is called only if the object has not already been
    // written to the Stream; this is to prevent duplication. The address
    // of each written object is remembered by the Stream.

    CL_Stream& operator<< (const CL_Object& value)
        {Write (value); return *this;};
    // Implemented using {\tt Write (const CL_Object&)}.

    inline bool Write (CL_Offset offset, const CL_Object& obj);
    //  Position the Stream at {\tt offset}, via {\tt SeekTo}, and write
    //  {\tt  obj}.
    
    bool Append (uchar* buffer, long num_bytes);
    // Write at the end of the Stream.
    
    
    // ------------- Positioning and sizing operations ----------
    
    virtual bool SeekTo (CL_Offset position) const = 0;
    // [Pure virtual] Change the current position to the given one. Returns
    // TRUE on success. 

    virtual bool SeekRelative (long change) const;
    // Seek relative to the current position, i.e., forwards if {\tt change}
    // is positive and backwards if it is negative. This method positions
    // the Stream at its beginning if {\tt change} is smaller than the
    // negative of the current position. 
    
    bool SeekToBegin() const;
    // Change the current position to the beginning of the Stream.

    virtual bool SeekToEnd () const;
    // Change the current position to the end of the Stream.

    virtual bool ChangeSize (long new_size) = 0;
    // [Pure virtual] Change the size of the stream to the given size.
    // Return TRUE if successful. 

    virtual long Size () const = 0;
    // [Pure virtual] Return the current size of the stream.
    
    virtual bool Eof () const {return Size() <= Offset();};
    // Return TRUE if the stream's cursor is at the end of the stream.
    
    virtual long Offset () const = 0;
    // [Pure virtual] Return the current position.

    virtual CL_String ErrorString () const;
    // Return the error message string associated with the current error
    // status, if any.

    // ------------------- History-related operations ------------

    virtual void Remember ();
    // Begin remembering the addresses of objects written into this
    // stream.
    
    virtual void Forget ();
    // Forget the remembered addresses.

    bool IsRemembering () const {return _remembering;};
    // Return the current state, whether this stream is currently
    // remembering object addresses.
    
    // -------------- Basic methods  ----------------------

    const char* ClassName() const {return "CL_Stream";};

    CL_ClassId ClassId() const { return _CL_Stream_CLASSID;};

    // ------------------- End public protocol ------------------------ 
 
protected:

    virtual CL_ObjectPtr _BuildObject () const;
    // Read a class id from this Stream, construct an empty object of
    // that type and return it. Return NULL on error (e.g., no such type).
    
    bool          _remembering;
    void*         _maps;
};
 
 

inline long CL_Stream::Read (uchar* , long ) const
{
    return 0;
} 


inline bool CL_Stream::Write (uchar* , long )
{
    return FALSE;
}


inline bool CL_Stream::SeekTo (CL_Offset ) const
{
    return FALSE;
}


inline long CL_Stream::Read (CL_Offset offset, uchar* buffer, long
                           num_bytes) const
{
    return SeekTo (offset) ? Read (buffer, num_bytes) : -1;
}

inline bool CL_Stream::Read (long& value) const
{
    return Read ((uchar*) &value, sizeof value) == sizeof value;
}

inline bool CL_Stream::Read (CL_Offset offset, long& value) const
{
    return SeekTo (offset) && (Read ((uchar*) &value, sizeof value) ==
                               sizeof value); 
}

inline bool CL_Stream::Read (short& value) const
{
    return Read ((uchar*) &value, sizeof value) == sizeof value;
}

inline bool CL_Stream::Read (CL_Offset offset, short& value) const
{
    return SeekTo (offset) && (Read (offset, (uchar*) &value, sizeof
                                     value) == sizeof value);
}

inline bool CL_Stream::Read (char& value) const
{
    return Read ((uchar*) &value, sizeof value) == sizeof value;
}

inline bool CL_Stream::Read (uchar& value) const
{
    return Read ((uchar*) &value, sizeof value) == sizeof value;
}

inline bool CL_Stream::Read (CL_Offset offset, CL_Object& o) const
{
    return (SeekTo (offset)) &&  Read (o);
}



inline bool CL_Stream::Write (CL_Offset offset, uchar* buffer, long
                            num_bytes)
{
    return SeekTo (offset) && Write (buffer, num_bytes);
}

inline bool CL_Stream::Write (long value)
{
    return Write ((uchar*) &value, sizeof value);
}

inline bool CL_Stream::Write (CL_Offset offset, long value)
{
    return SeekTo (offset) && Write ((uchar*) &value, sizeof value);
}

inline bool CL_Stream::Write (short value)
{
    return Write ((uchar*) &value, sizeof value);
}

inline bool CL_Stream::Write (char value)
{
    return Write ((uchar*) &value, sizeof value);
}

inline bool CL_Stream::Write (uchar value)
{
    return Write ((uchar*) &value, sizeof value);
}

inline bool CL_Stream::Write (CL_Offset offset, short value)
{
    return SeekTo (offset) && Write ((uchar*) &value, sizeof value);
}


inline bool CL_Stream::Write (CL_Offset offset, const CL_Object& o)
{
    return SeekTo (offset) && Write (o);
}



inline bool CL_Stream::SeekToEnd () const 
{
    return SeekTo (Size());
}

inline bool CL_Stream::Append (uchar* buffer, long num_bytes)
{
    return SeekToEnd() && Write (buffer, num_bytes);
}


inline bool CL_Stream::SeekRelative (long change) const
{
    return SeekTo (maxl (0, Offset() + change));
}

inline bool CL_Stream::SeekToBegin() const
{
    return SeekTo (0L);
}

#endif /* _stream_h_ */

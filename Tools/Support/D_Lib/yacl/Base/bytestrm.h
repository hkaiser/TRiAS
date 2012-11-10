

#ifndef _bytestrm_h_ /* Tue Feb 22 12:15:35 1994 */
#define _bytestrm_h_





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



// This class defines a ByteArray-based in-memory data
// stream. Its constructor needs a ByteArray or ByteString as parameter.
// It overrides all the pure virtual methods inherited from {\tt CL_Stream}.
// If the  ByteStream overflows, it attempts to expand its underlying
// ByteArray via the latter's {\tt ChangeSize} method.

#ifdef __GNUC__
#pragma interface
#endif

#include "base/stream.h"
#include "base/bytstrng.h"

class YACL_BASE CL_ByteStreamData;

class YACL_BASE CL_ByteStream: public CL_Stream {

public:
    CL_ByteStream (CL_ByteArray& b);
    // Create a ByteStream that uses the given ByteArray.

    
    // ----------------- Read operations -------------------------

    virtual long Read (uchar* buffer, long num_bytes) const; 
    // Read from current position. Returns number of bytes read, 0 on eof,
    // $-1$ on error.
 
    
    // ----------------- Write operations ------------------------

    virtual bool Write (uchar* buffer, long n);
    // Write {\tt n} bytes from {\tt buffer} beginning at the current position.
    // Return TRUE on success, FALSE if fewer than {\tt n} were written.

    
    // ----------------- Seek operations -------------------------
    
    virtual bool SeekTo (CL_Offset pos) const;
    // Change the current position to {\tt pos}. Returns TRUE on success.
    // This method returns FALSE if either {\tt pos} is negative or {\tt
    // pos} is larger than {\tt Size()} and the
    // underlying data stream is a ByteArray that could not expand.
 
    virtual bool SeekToEnd () const;
    // Seek to the end of this ByteStream.

    virtual bool SeekRelative (long change) const;
    // Seek relative to the current position; i.e., if currently positioned
    // at $p$, the new position is $p + {\tt change}$.
    
    virtual bool ChangeSize (long new_size);
    // Change the size of the ByteStream. This is similar to changing the
    // size of a file, i.e., it changes the size of the underlying data
    // stream. If the data stream is a ByteArray, this change is not
    // possible and the method returns FALSE. If it is a ByteString, and the
    // latter succeeds in changing size, this method returns TRUE.

    virtual long Size () const;
    // Return the current size of the stream.
    
    virtual bool Eof () const;
    // Is the ByteStream positioned at its end?
    
    virtual long Offset () const;
    // Return the current position.


    // ------------------ Basic functions ------------------------------
    
    const char* ClassName() const {return "CL_ByteStream";};

    CL_ClassId ClassId() const { return _CL_ByteStream_CLASSID;};

    // ------------------- End public protocol ------------------------ 
 



    
protected:
    CL_ByteArray& _buffer;
    long          _position;
};





// ---------------------- Querying ----------------------


inline bool CL_ByteStream::Eof () const
{
    return _position >= _buffer.Size();
}


// Return the current position
inline long CL_ByteStream::Offset () const
{
    return _position;
}


// Return the size of the byte block
inline long CL_ByteStream::Size () const
{
    return _buffer.Size();
}


inline bool CL_ByteStream::ChangeSize (long new_size)
{
    return _buffer.ChangeSize (new_size);
}


#endif /* _bytestrm_h_ */

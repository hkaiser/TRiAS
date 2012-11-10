/***
*olebuf.cpp - core olebuf member functions
*
*       Copyright (c) 1991-1995, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the core member functions for olebuf class.
*
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <crtdbg.h>
#include <sys\types.h>
#include <io.h>

#include <ole2.h>

#include <ospace\config.h>
#include <ospace\olestrea.h>

#include <sys\stat.h>

const int olebuf::openprot     = 0644;

const int olebuf::sh_none      = 04000;        // deny rw
const int olebuf::sh_read      = 05000;        // deny wr
const int olebuf::sh_write     = 06000;        // deny rd

const int olebuf::binary       = 0;
const int olebuf::text         = 1;

/***
*olebuf::olebuf() - olebuf default constructor
*
*Purpose:
*       Default constructor.
*
*Entry:
*
*******************************************************************************/
	olebuf::olebuf()
: streambuf()
{
    x_fOpened = 0;
    x_pIStrm = NULL;
}


/***
*olebuf::olebuf(IStream *pIStrm) - olebuf constructor
*
*Purpose:
*       Constructor.  Initialize olebuf and attach to OLE-stream.
*
*Entry:
*       pIStrm = OLE-stream to attach to olebuf
*
*******************************************************************************/
        olebuf::olebuf(IStream *pIStrm)
: streambuf()
{
    x_fOpened = 0;
    x_pIStrm=pIStrm;
	if (pIStrm)
		pIStrm -> AddRef();
}


/***
*olebuf::olebuf(IStream *pIStrm, char* p, int len) - olebuf constructor
*
*Purpose:
*       Constructor.  Initialize olebuf and attach to OLE-stream.
*
*Entry:
*       pIStrm  = OLE-stream to attach to olebuf
*       p   = user-supplied buffer
*       len = length of buffer
*
*******************************************************************************/
        olebuf::olebuf(IStream *pIStrm, char* p, int len)
:    streambuf()
{
    olebuf::setbuf(p,len);
    x_fOpened = 0;
    x_pIStrm=pIStrm;
	if (pIStrm)
		pIStrm -> AddRef();
}


/***
*olebuf::~olebuf() - olebuf destructor
*
*Purpose:
*       Destructor.  Close attached file only if we opened it.
*
*Entry:
*       None.
*
*******************************************************************************/
        olebuf::~olebuf()
{
        lock();         // no need to unlock...
        if (x_fOpened)
            close();    // calls olebuf::sync()
        else
            olebuf::sync();
	if (x_pIStrm)
		x_pIStrm -> Release();
}


/***
*olebuf* olebuf::close() - close an attached file
*
*Purpose:
*       Close attached file.
*
*Entry:
*       None.
*Exit:
*       Returns NULL if error, otherwise returns "this" pointer.
*
*******************************************************************************/
olebuf* olebuf::close()
{
    int retval;
    if (x_pIStrm==NULL)
        return NULL;

    lock();
    retval = sync();

    if ((x_pIStrm -> Release()) || (retval==EOF))
        {
		  x_pIStrm = NULL;
        unlock();
        return NULL;
        }
    x_pIStrm = NULL;
    unlock();
    return this;
}

/***
*virtual int olebuf::overflow(int c) - overflow virtual function
*
*Purpose:
*       flush any characters in the reserve area and handle 'c'.
*
*Entry:
*       c = character to output (if not EOF)
*
*Exit:
*       Returns EOF if error, otherwise returns something else.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int olebuf::overflow(int c)
{
    if (allocate()==EOF)        // make sure there is a reserve area
        return EOF;
    if (olebuf::sync()==EOF) // sync before new buffer created below
        return EOF;

    if (!unbuffered())
        setp(base(),ebuf());

    if (c!=EOF)
        {
        if ((!unbuffered()) && (pptr() < epptr())) // guard against recursion
            sputc(c);
        else
            {
			unsigned long ulWritten = 0;

				if (FAILED(x_pIStrm -> Write (&c, 1, &ulWritten)) || ulWritten != 1)
					return EOF;
            }
        }
    return(1);  // return something other than EOF if successful
}

/***
*virtual int olebuf::underflow() - underflow virtual function
*
*Purpose:
*       return next character in get area, or get more characters from source.
*
*Entry:
*       None.
*
*Exit:
*       Returns current character in file.  Does not advance get pointer.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int olebuf::underflow()
{
    unsigned char tbuf;

    if (in_avail())
        return (int)(unsigned char) *gptr();

    if (allocate()==EOF)        // make sure there is a reserve area
        return EOF;
    if (olebuf::sync()==EOF)
        return EOF;

unsigned long ulRead = 0;

    if (unbuffered())
        {
			if (FAILED(x_pIStrm -> Read ((void *)&tbuf, 1, &ulRead)) || ulRead != 1)
				return EOF;

        return (int)tbuf;
        }

	if (FAILED(x_pIStrm -> Read ((void *)base(), blen(), &ulRead)) || ulRead <= 0)
		return EOF;		// reached EOF
	
    setg(base(),base(),base()+ulRead);
    return (int)(unsigned char) *gptr();
}


/***
*virtual streampos olebuf::seekoff() - seekoff virtual function
*
*Purpose:
*       Seeks to given absolute or relative file offset.
*
*Entry:
*       off = offset to seek to relative to beginning, end or current
*               position in the file.
*       dir = one of ios::beg, ios::cur, or ios::end
*
*Exit:
*       Returns current file position after seek.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
streampos olebuf::seekoff(streamoff off, ios::seek_dir dir, int)
{
    int fdir;
    switch (dir) {
        case ios::beg :
            fdir = STREAM_SEEK_SET;
            break;
        case ios::cur :
            fdir = STREAM_SEEK_CUR;
            break;
        case ios::end :
            fdir = STREAM_SEEK_END;
            break;
        default:
        // error
            return(EOF);
        }

    if (olebuf::sync()==EOF)
        return EOF;

LARGE_INTEGER li;
ULARGE_INTEGER uli;

	LISet32 (li, off);
	if (FAILED(x_pIStrm -> Seek (li, fdir, &uli)))
		return EOF;

    return((streampos)uli.LowPart);
}

/***
*virtual int olebuf::sync() - synchronize buffers with external file postion.
*
*Purpose:
*       Synchronizes buffer with external file, by flushing any output and/or
*       discarding any unread input data.  Discards any get or put area(s).
*
*Entry:
*       None.
*
*Exit:
*       Returns EOF if error, else 0.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int olebuf::sync()
{
        long count;
        if (x_pIStrm==NULL)
            return(EOF);

        if (!unbuffered())
        {
            if ((count=out_waiting())!=0)
            {
			unsigned long ulWritten = 0;

				if (FAILED(x_pIStrm -> Write ((void *)pbase(), count, &ulWritten)) || ulWritten != (unsigned long)count)
                {
                    if (ulWritten > 0) {
                        // should set _pptr -= nout
                        pbump(-(int)ulWritten);
                        memmove(pbase(), pbase()+ulWritten, (int)(count-ulWritten));
                    }
                    return(EOF);
                }
            }
            setp(0,0); // empty put area

            if ((count=in_avail()) > 0)
            {
                // can't use seekoff here!!
			LARGE_INTEGER li;

				LISet32(li, -count);
				if (FAILED(x_pIStrm -> Seek(li, STREAM_SEEK_CUR, NULL)))
                {
//                  unlock();
                    return (EOF);
                }
            }
            setg(0,0,0); // empty get area
        }
//      unlock();
        return(0);
}

/***
*virtual streambuf* olebuf::setbuf(char* ptr, int len) - set reserve area.
*
*Purpose:
*       Synchronizes buffer with external file, by flushing any output and/or
*       discarding any unread input data.  Discards any get or put area(s).
*
*Entry:
*       ptr = requested reserve area.  If NULL, request is for unbuffered.
*       len = size of reserve area.  If <= 0, request is for unbuffered.
*
*Exit:
*       Returns this pointer if request is honored, else NULL.
*
*Exceptions:
*       Returns NULL if request is not honored.
*
*******************************************************************************/
streambuf * olebuf::setbuf(char * ptr, int len)
{
    if (is_open() && (ebuf()))
        return NULL;
    if ((!ptr) || (len <= 0))
        unbuffered(1);
    else
        {
        lock();
        setb(ptr, ptr+len, 0);
        unlock();
        }
    return this;
}

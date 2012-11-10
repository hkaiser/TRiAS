/***
*iolestream.cpp - iolestream member function definitions
*
*       Copyright (c) 1991-1995, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the member functions for the iolestream class.
*
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys\types.h>
#include <io.h>

#include <ole2.h>

#include <ospace\config.h>
#include <ospace\olestrea.h>

#include <sys\stat.h>

/***
*iolestream::iolestream() - iolestream default constructor
*
*Purpose:
*       Default constructor for iolestream objects.
*
*Entry:
*       None.
*
*Exit:
*       None.
*
*Exceptions:
*
*******************************************************************************/
        iolestream::iolestream()
: istream(new olebuf)
{
    delbuf(1);  // schedule automatic deletion too...
}

/***
*iolestream::iolestream(const char * name, int mode, int prot) - iolestream ctor
*
*Purpose:
*       Constructor for iolestream objects.  Creates an associated filebuf object,
*       opens a named file and attaches it to the new filebuf.
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument.  ios::in is implied.
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if open fails.
*
*******************************************************************************/
        iolestream::iolestream(IStorage *pIStg, const wchar_t *name, int mode, int prot)
: istream(new olebuf)
{
    delbuf(1);  // schedule automatic deletion too...
    if (!(rdbuf()->open(pIStg, name, (mode|ios::in), prot)))
        state |= ios::failbit;
}

/***
*iolestream::iolestream(filedesc fd) - iolestream constructor
*
*Purpose:
*       Constructor for iolestream objects.  Creates an associated filebuf object
*       and attaches it to the given file descriptor.
*
*Entry:
*       fd = file descriptor of file previously opened using _open or _sopen.
*
*Exit:
*       None.
*
*Exceptions:
*
*******************************************************************************/
        iolestream::iolestream(IStream *pIStrm)
: istream(new olebuf(pIStrm))
{
    delbuf(1);
}

/***
*iolestream::iolestream(filedesc fd, char * sbuf, int len) - iolestream constructor
*
*Purpose:
*       Constructor for iolestream objects.  Creates an associated filebuf object
*       and attaches it to the given file descriptor.  Filebuf object uses
*       user-supplied buffer or is unbuffered if sbuf or len = 0.
*
*Entry:
*       fd   = file descriptor of file previously opened using _open or _sopen.
*       sbuf = pointer to character buffer or NULL if request for unbuffered.
*       len  = lenght of character buffer sbuf or 0 if request for unbuffered.
*
*Exit:
*       None.
*
*Exceptions:
*
*******************************************************************************/
        iolestream::iolestream(IStream *pIStrm, char * sbuf, int len)
: istream(new olebuf(pIStrm, sbuf, len))
//: istream(new filebuf);
{
    delbuf(1);
}

/***
*iolestream::~iolestream() - iolestream destructor
*
*Purpose:
*       iolestream destructor.
*
*Entry:
*       None.
*
*Exit:
*       None.
*
*Exceptions:
*
*******************************************************************************/
        iolestream::~iolestream()
{
}

/***
*streambuf* iolestream::setbuf(char * ptr, int len) - setbuf function
*
*Purpose:
*       iolestream setbuf function
*
*Entry:
*       ptr = pointer to buffer or NULL for unbuffered.
*       len = length of buffer or zero for unbuffered.
*
*Exit:
*       Returns rdbuf() or NULL if error.
*
*Exceptions:
*       If iolestream is already open or if rdbuf()->setbuf fails, sets failbit
*       and returns NULL.
*
*******************************************************************************/
streambuf * iolestream::setbuf(char * ptr, int len)
{
    if ((is_open()) || (!(rdbuf()->setbuf(ptr, len))))
        {
        clear(state | ios::failbit);
        return NULL;
        }
    return rdbuf();
}

/***
*void iolestream::attach(filedesc _fd) - attach member function
*
*Purpose:
*       iolestream attach member function.  Just calls rdbuf()->attach().
*
*Entry:
*       _fd = file descriptor of previously opened file.
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if rdbuf()->attach fails.
*
*******************************************************************************/
void iolestream::attach(IStream *pIStrm)
{
    if (!(rdbuf()->attach(pIStrm)))
        clear(state | ios::failbit);
}

/***
*void iolestream::open(const char * name, int mode, int prot) - iolestream open()
*
*Purpose:
*       Opens a named file and attaches it to the associated filebuf.
*       Just calls rdbuf()->open().
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument.  ios::in is implied.
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if already open or rdbuf()->open() fails.
*
*******************************************************************************/
void iolestream::open(IStorage *pIStg, const wchar_t * name, int mode, int prot)
{
    if (is_open() || !(rdbuf()->open(pIStg, name, (mode|ios::in), prot)))
        clear(state | ios::failbit);
}

/***
*void iolestream::close() - close member function
*
*Purpose:
*       iolestream close member function.  Just calls rdbuf()->close().
*       Clears rdstate() error bits if successful.
*
*Entry:
*       None.
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if rdbuf()->close fails.
*
*******************************************************************************/
void iolestream::close()
{
    clear((rdbuf()->close()) ? 0 : (state | ios::failbit));
}

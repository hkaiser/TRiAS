/***
*oolestream.cpp -
*
*       Copyright (c) 1991-1995, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the member functions for the oolestream class.
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
*oolestream::oolestream() - oolestream default constructor
*
*Purpose:
*       Default constructor for oolestream objects.
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
        oolestream::oolestream()
: ostream(new olebuf)
{
    delbuf(1);
}

/***
*oolestream::oolestream(const char * name, int mode, int prot) - oolestream ctor
*
*Purpose:
*       Constructor for oolestream objects.  Creates an associated filebuf object,
*       opens a named file and attaches it to the new filebuf.
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument.  ios::out is implied.
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if open fails.
*
*******************************************************************************/
        oolestream::oolestream(IStorage *pIStg, const wchar_t * name, int mode, int prot)
: ostream(new olebuf)
{
    delbuf(1);
    if (!(rdbuf()->open(pIStg, name, (mode|ios::out), prot)))
        state |= ios::failbit;
}

/***
*oolestream::oolestream(filedesc fd) - oolestream constructor
*
*Purpose:
*       Constructor for oolestream objects.  Creates an associated filebuf object
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
        oolestream::oolestream(IStream *pIStrm)
: ostream(new olebuf(pIStrm))
{
    delbuf(1);
}

/***
*oolestream::oolestream(filedesc fd, char * sbuf, int len) - oolestream constructor
*
*Purpose:
*       Constructor for oolestream objects.  Creates an associated filebuf object
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
        oolestream::oolestream(IStream *pIStrm, char * sbuf, int len)
: ostream(new olebuf(pIStrm, sbuf, len))
{
    delbuf(1);
}

/***
*oolestream::~oolestream() - oolestream destructor
*
*Purpose:
*       oolestream destructor.
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
        oolestream::~oolestream()
{
}

/***
*streambuf* oolestream::setbuf(char * ptr, int len) - setbuf function
*
*Purpose:
*       oolestream setbuf function
*
*Entry:
*       ptr = pointer to buffer or NULL for unbuffered.
*       len = length of buffer or zero for unbuffered.
*
*Exit:
*       Returns rdbuf() or NULL if error.
*
*Exceptions:
*       If oolestream is already open or if rdbuf()->setbuf fails, sets failbit
*       and returns NULL.
*
*******************************************************************************/
streambuf * oolestream::setbuf(char * ptr, int len)
{
    if ((is_open()) || (!(rdbuf()->setbuf(ptr, len))))
        {
        clear(state | ios::failbit);
        return NULL;
        }
    return rdbuf();
}

/***
*void oolestream::attach(filedesc _fd) - attach member function
*
*Purpose:
*       oolestream attach member function.  Just calls rdbuf()->attach().
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
void oolestream::attach(IStream *pIStrm)
{
    if (!(rdbuf()->attach(pIStrm)))
        clear(state | ios::failbit);
}

/***
*void oolestream::open(const char * name, int mode, int prot) - oolestream open()
*
*Purpose:
*       Opens a named file and attaches it to the associated filebuf.
*       Just calls rdbuf()->open().
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument.  ios::out is implied.
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if already open or rdbuf()->open() fails.
*
*******************************************************************************/
void oolestream::open(IStorage *pIStg, const wchar_t * name, int mode, int prot)
{
    if (is_open() || !(rdbuf()->open(pIStg, name, (mode|ios::out), prot)))
        clear(state | ios::failbit);
}

/***
*void oolestream::close() - close member function
*
*Purpose:
*       oolestream close member function.  Just calls rdbuf()->close().
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
void oolestream::close()
{
    clear((rdbuf()->close()) ? 0 : (state | ios::failbit));
}

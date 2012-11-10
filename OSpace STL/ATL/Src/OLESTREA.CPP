/***
*olestream.cpp -
*
*       Copyright (c) 1991-1995, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the member functions for the olestream class.
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
*olestream::olestream() - olestream default constructor
*
*Purpose:
*       Default constructor for olestream objects.
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
        olestream::olestream()
: iostream(new olebuf)
{
    istream::delbuf(1);
    ostream::delbuf(1);
}

/***
*olestream::olestream(const char * name, int mode, int prot) - olestream constructor
*
*Purpose:
*       Constructor for olestream objects.  Creates an associated filebuf object,
*       opens a named file and attaches it to the new filebuf.
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if open fails.
*
*******************************************************************************/
        olestream::olestream(IStorage *pIStg, const wchar_t * name, int mode, int prot)
: iostream(new olebuf)
{
    istream::delbuf(1);
    ostream::delbuf(1);
    if (!(rdbuf()->open(pIStg, name, mode, prot)))
        {
        istream::state = istream::failbit;
        ostream::state = ostream::failbit;
        }
}

/***
*olestream::olestream(filedesc fd) - olestream constructor
*
*Purpose:
*       Constructor for olestream objects.  Creates an associated filebuf object
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
        olestream::olestream(IStream *pIStrm)
: iostream(new olebuf(pIStrm))
{
    istream::delbuf(1);
    ostream::delbuf(1);
}

/***
*olestream::olestream(filedesc fd, char * sbuf, int len) - olestream constructor
*
*Purpose:
*       Constructor for olestream objects.  Creates an associated filebuf object
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
        olestream::olestream(IStream *pIStrm, char * sbuf, int len)
: iostream(new olebuf(pIStrm, sbuf, len))
{
    istream::delbuf(1);
    ostream::delbuf(1);
}

/***
*olestream::~olestream() - olestream destructor
*
*Purpose:
*       olestream destructor.
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
        olestream::~olestream()
{
}

/***
*streambuf* olestream::setbuf(char * ptr, int len) - setbuf function
*
*Purpose:
*       olestream setbuf function
*
*Entry:
*       ptr = pointer to buffer or NULL for unbuffered.
*       len = length of buffer or zero for unbuffered.
*
*Exit:
*       Returns rdbuf() or NULL if error.
*
*Exceptions:
*       If olestream is already open or if rdbuf()->setbuf fails, sets failbit
*       and returns NULL.
*
*******************************************************************************/
streambuf * olestream::setbuf(char * ptr, int len)
{
    if ((is_open()) || (!(rdbuf()->setbuf(ptr, len))))
        {
        istream::clear(istream::state | istream::failbit);
        ostream::clear(ostream::state | ostream::failbit);
        return NULL;
        }
    return rdbuf();
}

/***
*void olestream::attach(filedesc _fd) - attach member function
*
*Purpose:
*       olestream attach member function.  Just calls rdbuf()->attach().
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
void olestream::attach(IStream *pIStrm)
{
    if (!(rdbuf()->attach(pIStrm)))
        {
        istream::clear(istream::state | istream::failbit);
        ostream::clear(ostream::state | ostream::failbit);
        }
}

/***
*void olestream::open(const char * name, int mode, int prot) - olestream open()
*
*Purpose:
*       Opens a named file and attaches it to the associated filebuf.
*       Just calls rdbuf()->open().
*
*Entry:
*       name = filename to open.
*       mode = see filebuf::open mode argument
*       prot = see filebuf::open share argument
*
*Exit:
*       None.
*
*Exceptions:
*       Sets failbit if already open or rdbuf()->open() fails.
*
*******************************************************************************/
void olestream::open(IStorage *pIStg, const wchar_t * name, int mode, int prot)
{
    if (is_open() || !(rdbuf()->open(pIStg, name, mode, prot)))
        {
        istream::clear(istream::state | istream::failbit);
        ostream::clear(ostream::state | ostream::failbit);
        }
}

/***
*void olestream::close() - close member function
*
*Purpose:
*       olestream close member function.  Just calls rdbuf()->close().
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
void olestream::close()
{
    if (rdbuf()->close())
        {
        istream::clear();
        ostream::clear();
        }
    else
        {
        istream::clear(istream::state | istream::failbit);
        ostream::clear(ostream::state | ostream::failbit);
        }
}

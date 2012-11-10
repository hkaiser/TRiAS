/***
*olebuf1.cpp - non-core olebuf member functions.
*
*       Copyright (c) 1991-1995, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains optional member functions for olebuf class.
*
*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <io.h>

#include <ole2.h>

#include <ospace\config.h>
#include <ospace\olestrea.h>

#include <sys\stat.h>

/***
*olebuf* olebuf::attach(filedesc fd) - olebuf attach function
*
*Purpose:
*       olebuf attach() member function.  Attach olebuf object to the
*       given file descriptor previously obtained from _open() or _sopen().
*
*Entry:
*       fd = file descriptor.
*
*Exit:
*       Returns this pointer or NULL if error.
*
*Exceptions:
*       Returns NULL if fd = -1.
*
*******************************************************************************/
olebuf* olebuf::attach(IStream *pIStrm)
{
    if (x_pIStrm!=NULL)
        return NULL;    // error if already attached

    lock();
	x_pIStrm = pIStrm;
	if (x_pIStrm) x_pIStrm -> AddRef();

    if ((pIStrm!=NULL) && (!unbuffered()) && (!ebuf()))
        {
        char * sbuf = new char[BUFSIZ];
        if (!sbuf)
            {
            unbuffered(1);
            }
        else
            {
            streambuf::setb(sbuf,sbuf+BUFSIZ,1);
            }
        }
    unlock();
    return this;
}

/***
*olebuf* olebuf::open(const char* name, int mode, int share) - olebuf open
*
*Purpose:
*       olebuf open() member function.  Open a file and attach to olebuf
*       object.
*
*Entry:
*       name  = file name string.
*       mode  = open mode: Combination of ios:: in, out, binary, nocreate, app,
*               ate, noreplace and trunc.  See spec. for details on behavior.
*       share = share mode (optional).  sh_compat, sh_none, sh_read, sh_write.
*
*Exit:
*       Returns this pointer or NULL if error.
*
*Exceptions:
*       Returns NULL if olebuf is already attached to an open file, or if
*       invalid mode options, or if call to _sopen or olebuf::seekoff() fails.
*
*******************************************************************************/
olebuf* olebuf::open(IStorage *pIStg, const wchar_t* name, int mode, int share)
{
    DWORD ole_mode = 0;
    if (x_pIStrm!=NULL)
        return NULL;    // error if already open

// translate mode argument
    if (!(mode & ios::nocreate))
        ole_mode |= STGM_CREATE;
    if (mode & ios::noreplace)
        ole_mode |= STGM_FAILIFTHERE;
    if (mode & ios::app)
        {
        mode |= ios::out;
//        ole_mode |= O_APPEND;
        }
    if (mode & ios::trunc)
        {
        mode |= ios::out;  // IMPLIED
//        ole_mode |= O_TRUNC;
        }
    if (mode & ios::out)
        {
        if (mode & ios::in)
            {
            ole_mode |= STGM_READWRITE;
            }
        else
            {
            ole_mode |= STGM_WRITE;
            }
        if (!(mode & (ios::in|ios::app|ios::ate|ios::noreplace)))
            {
            mode |= ios::trunc; // IMPLIED
//            ole_mode |= O_TRUNC;
            }
        }
    else if (mode & ios::in)
        ole_mode |= STGM_READ;
    else
        return NULL;    // error if not ios:in or ios::out

    share &= (sh_read|sh_write|sh_none); // ignore other bits
    if (share)  // optimization  openprot serves as default
        {
        switch (share)
            {
/*          case 03000 : Reserved for sh_compat  */

//          case sh_none :
            case 04000 :
                ole_mode |= STGM_SHARE_EXCLUSIVE;
                break;
//          case sh_read :
            case 05000 :
                ole_mode |= STGM_SHARE_DENY_WRITE;
                break;
//          case sh_write :
            case 06000 :
                ole_mode |= STGM_SHARE_DENY_READ;
                break;
//          case (sh_read|sh_write) :
            case 07000 :
                ole_mode |= STGM_SHARE_DENY_NONE;
                break;
            default :   // unrecognized value same as default
                break;
            };
        }

HRESULT hr;

	if (ole_mode & STGM_CREATE)		// create new substream
		hr = pIStg -> CreateStream (name, ole_mode, 0L, 0L, &x_pIStrm);
	else							// open existing stream
		hr = pIStg -> OpenStream (name, NULL, ole_mode, 0L, &x_pIStrm);
	if (FAILED(hr)) {
		SetLastError (hr);
		return NULL;
	}

    lock();
    x_fOpened = 1;
    if ((!unbuffered()) && (!ebuf()))
        {
        char * sbuf = new char[BUFSIZ];
        if (!sbuf)
            {
            unbuffered(1);
            }
        else
            {
            streambuf::setb(sbuf,sbuf+BUFSIZ,1);
            }
        }
    if (mode & ios::ate)
        if (seekoff(0,ios::end,mode)==EOF)
            {
            close();
            unlock();
            return NULL;
            }
    unlock();
    return this;
}

/***
*int olebuf::setmode(int mode) - olebuf setmode function
*
*Purpose:
*       olebuf setmode() member function.  Set binary or text access mode.
*       Calls _setmode().
*
*       MS-specific extension.
*
*Entry:
*       mode = olebuf::binary or olebuf::text.
*
*Exit:
*       Returns previous mode, or -1 error.
*
*Exceptions:
*       Return -1 (EOF) if invalid argument or _setmode fails.
*
*******************************************************************************/
int olebuf::setmode(int mode)
{
    int retval;
    if ((mode!=olebuf::binary) && (mode!=olebuf::text))
        return -1;

    lock();
    if ((x_pIStrm == NULL) || (sync()==EOF))
        {
        retval = -1;
        }
    else
        {
        retval = olebuf::binary;		// _setmode(x_fd,mode);
        }

    unlock();
    return retval;
}


int	olebuf::fd (IStream **ppIStrm) const
{
	if (x_pIStrm==NULL) 
		return EOF;
	*ppIStrm = x_pIStrm; 
	if (x_pIStrm) 
		x_pIStrm -> AddRef(); 
		
return 0; 
}

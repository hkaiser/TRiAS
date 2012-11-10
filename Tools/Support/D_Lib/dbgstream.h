// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.10.1999 09:50:19 
//
// @doc
// @module dbgstream.h | Declaration of the <c dbgstream> class

#if !defined(_DBGSTREAM_H__125AAD4B_202C_407C_AA9F_2A7695A8ECF2__INCLUDED_)
#define _DBGSTREAM_H__125AAD4B_202C_407C_AA9F_2A7695A8ECF2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <windows.h>		// for OutputDebugString
#include <iostream.h>		// for streambuf and ostream et.al.

// The important part is the declaration of a class derived from streambuf.
// This class is used to put characters into and get characters from some 
// "external representation", e.g. a file. In this case characters are put 
// into the debug output.. Thus the derived class is called 'debugbuf'. 
// Currently only the putting of characters is implemented...
class debugbuf : 
	public streambuf
{
private:
// output characters to debug output
	void put_buffer (void)
    {
		if (pbase() != pptr()) {
		int	len = (pptr() - pbase());
		char *buffer = new char[len + 1];

			strncpy(buffer, pbase(), len);
			buffer[len] = 0;
			OutputDebugString(buffer);
			delete [] buffer;
			setp(pbase(), epptr());
		}
    }
// output a single character (for unbufferd output)
	void put_char (int chr)
    {
	char app[2];

		app[0] = chr;
		app[1] = 0;
		OutputDebugString (app);
    }

protected:
// output buffer is full, flush characters
	int overflow (int chr)
	{
		put_buffer();
		if (EOF != chr) {
			if (pbase() == epptr())
				put_char(chr);
			else
				sputc(chr);
		}
		return 0;
	}
	int underflow() 
	{ 
		return EOF; 
	}

// send pending characters to debug output
	int sync()
	{
		put_buffer();
		return 0;
	}

public:
	debugbuf (int bsize = 1024) :
		streambuf()
	{
		if (0 != bsize) {
		char *ptr = new char[bsize];
	
			setp(ptr, ptr + bsize);
		} else
			setp(0, 0);

		setg(0, 0, 0);
	}
	~debugbuf() { sync(); }
};

// To make the use of the debugbuf more convinient a class derived from
// ostream is supported which only initializes an ostream with a debugbuf
// as streambuf. It is also possible to directly allocate a debugbuf and
// initialize an ostream with it. Thus this class is not really necessary:
class odbgstream :
	public ostream
{
public:
	odbgstream (int bsize = 1024) :
		ostream (new debugbuf(bsize))
	{
	}
};

#endif // !defined(_DBGSTREAM_H__125AAD4B_202C_407C_AA9F_2A7695A8ECF2__INCLUDED_)

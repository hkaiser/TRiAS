/***
*olestrea.h - definitions/declarations for olebuf and olestream classes
*
*Purpose:
*	This file defines the classes, values, macros, and functions
*	used by the olebuf and olestream classes.
*	[AT&T C++]
*
*       [Public]
*
****/

#ifdef __cplusplus

#ifndef _INC_OLESTREAM
#define _INC_OLESTREAM

#if !defined(_WIN32) && !defined(_MAC)
#error ERROR: Only Mac or Win32 targets supported!
#endif


#ifdef	_MSC_VER
// Currently, all MS C compilers for Win32 platforms default to 8 byte
// alignment.
#pragma pack(push,8)
#endif	// _MSC_VER

/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef	_NTSDK
/* definition compatible with NT SDK */
#define _CRTIMP
#else	/* ndef _NTSDK */
/* current definition */
#ifdef	_DLL
#define _CRTIMP __declspec(dllimport)
#else	/* ndef _DLL */
#define _CRTIMP
#endif	/* _DLL */
#endif	/* _NTSDK */
#endif	/* _CRTIMP */


#include <iostream.h>

#ifdef _MSC_VER
// C4514: "unreferenced inline function has been removed"
#pragma warning(disable:4514) // disable C4514 warning
// #pragma warning(default:4514)	// use this to reenable, if desired
#endif	// _MSC_VER

class OS_PUBLIC olebuf : public streambuf {
public:
static	const int	openprot;	// default share/prot mode for open

// optional share values for 3rd argument (prot) of open or constructor
static	const int	sh_none;	// exclusive mode no sharing
static	const int	sh_read;	// allow read sharing
static	const int	sh_write;	// allow write sharing
// use (sh_read | sh_write) to allow both read and write sharing

static	const int	binary;
static	const int	text;

			olebuf();
			olebuf(IStream *pIStrm);
			olebuf(IStream *pIStrm, char *, int);
			~olebuf();

	olebuf*	attach(IStream *pIStrm);
	int		fd (IStream **ppIStrm) const;
	int		is_open() const { return (x_pIStrm!=NULL); }
	olebuf*	open(IStorage *pIStg, const wchar_t *, int, int = olebuf::openprot);
	olebuf*	close();
	int		setmode(int = olebuf::text);

virtual	int		overflow(int=EOF);
virtual	int		underflow();

virtual	streambuf*	setbuf(char *, int);
virtual	streampos	seekoff(streamoff, ios::seek_dir, int);
// virtual	streampos	seekpos(streampos, int);
virtual	int		sync();

private:
	IStream	*x_pIStrm;
	int		 x_fOpened;
};

class OS_PUBLIC iolestream : public istream {
public:
	iolestream();
	iolestream(IStorage *pIStg, const wchar_t *, int =ios::in, int = olebuf::openprot);
	iolestream(IStream *pIStrm);
	iolestream(IStream *pIStrm, char *, int);
	~iolestream();

	streambuf * setbuf(char *, int);
	olebuf* rdbuf() const { return (olebuf*) ios::rdbuf(); }

	void attach(IStream *pIStrm);
	int	fd (IStream **ppIStrm) const { return rdbuf()->fd(ppIStrm); }

	int is_open() const { return rdbuf()->is_open(); }
	void open(IStorage *pIStg, const wchar_t *, int =ios::in, int = olebuf::openprot);
	void close();
	int setmode(int mode = olebuf::text) { return rdbuf()->setmode(olebuf::binary); }
};

class OS_PUBLIC oolestream : public ostream {
public:
	oolestream();
	oolestream(IStorage *pIStg, const wchar_t *, int =ios::out, int = olebuf::openprot);
	oolestream(IStream *pIStrm);
	oolestream(IStream *pIStrm, char *, int);
	~oolestream();

	streambuf * setbuf(char *, int);
	olebuf* rdbuf() const { return (olebuf*) ios::rdbuf(); }

	void attach(IStream *pIStrm);
	int	fd (IStream **ppIStrm) const { return rdbuf()->fd(ppIStrm); }

	int is_open() const { return rdbuf()->is_open(); }
	void open(IStorage *pIStg, const wchar_t *, int =ios::out, int = olebuf::openprot);
	void close();
	int setmode(int mode = olebuf::text) { return rdbuf()->setmode(olebuf::binary); }
};
	
class OS_PUBLIC olestream : public iostream {
public:
	olestream();
	olestream(IStorage *pIStg, const wchar_t *, int, int = olebuf::openprot);
	olestream(IStream *pIStrm);
	olestream(IStream *pIStrm, char *, int);
	~olestream();

	streambuf * setbuf(char *, int);
	olebuf* rdbuf() const { return (olebuf*) ostream::rdbuf(); }

	void attach(IStream *pIStrm);
	int	fd (IStream **ppIStrm) const { return rdbuf()->fd(ppIStrm); }

	int is_open() const { return rdbuf()->is_open(); }
	void open(IStorage *pIStg, const wchar_t *, int, int = olebuf::openprot);
	void close();
	int setmode(int mode = olebuf::text) { return rdbuf()->setmode(olebuf::binary); }
};
	
// manipulators to dynamically change file access mode (olebufs only)
//inline	ios& binary(ios& _olestrm) \
   //{ ((olebuf*)_olestrm.rdbuf())->setmode(olebuf::binary); return _olestrm; }
//inline	ios& text(ios& _olestrm) \
   //{ ((olebuf*)_olestrm.rdbuf())->setmode(olebuf::binary); return _olestrm; }

#ifdef	_MSC_VER
#pragma pack(pop)
#endif	// _MSC_VER

#endif	// _INC_OLESTREAM

#endif /* __cplusplus */

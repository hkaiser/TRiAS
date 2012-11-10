// <!-*-C++-*- file: wstream.h --->
// <!-------------------------------------------------------------------------->
// <! Copyright (C) 1995 Dietmar Kuehl >
// <!>
// <! This file is free software; you can redistribute it and/or modify >
// <! it under the terms of the GNU General Public License as published by >
// <! the Free Software Foundation; either version 2 of the License, or >
// <! (at your option) any later version. >
// <!>
// <! This program is distributed in the hope that it will be useful, >
// <! but WITHOUT ANY WARRANTY; without even the implied warranty of >
// <! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the >
// <! GNU General Public License for more details. >
//----------------------------------------------------------------------------
// <HTML>
// <HEAD>
// <TITLE> wstream.h - Header File for a Specialized IOstream </TITLE>
// <H1>Header File for a Specialized IOstream</H1>
// <H2>Writing into a Motif Text Widget</H2>
// <HR>
// </HEAD>

// <BODY>
// This page includes a header file used to declare a specialized
// ostream and streambuf: The debugbuf derived from streambuf is used
// to write text to a Motif text widget. A Motif text widget is used
// as external representation because I needed such an ostream myself
// and because I have seen several request how to solve a similar 
// problem in conjunction with MS Windows. I couldn't write an MS Windows
// example because I haven't any experience with that (thus there is also
// no point in asking me for MS Windows related code doing a similar thing).
// However, it should not be a problem to change the code to write to another
// external representation.
// <P>
// For further information about iostreams see a documentation of this stuff.
// Most of the knowledge I have about iostreams comes from
// <BR> C++ IOStreams Handbook
// <BR> Steve Teale
// <BR> Addison-Wesley
// <BR> ISBN 0-201-59641-5
// <HR>
// First prevent that the body of this file is included twice:
// <PRE>
#ifndef	_DBGSTREAM_H_
#define	_DBGSTREAM_H_
// </PRE>

//----------------------------------------------------------------------------

// Next the necessary header files are included: iostream.h is needed for
// the declaration of ostream and streambuf. In the headerfile Intrinsic.h
// declaration of Widget is found.
// <PRE>
#include <iostream.h>
// </PRE>

//----------------------------------------------------------------------------

// The important part is the declaration of a class derived from streambuf.
// This class is used to put characters into and get characters from some "extrenal representation",
// e.g. a file. In this case characters are put into a widget. Thus the derived
// class is called 'debugbuf'. Currently only the putting of characters is
// implemented...
// <BR>
// The important functions for this class are 'overflow()' which is called
// if the internal buffer of the debugbuf is full and some character should
// be placed in there and the 'sync()' which is called when the external
// representation is to be brought into synchronization with the buffers
// representation (e.g. if an 'endl' or an '\n' is put into a stream). The
// other functions are used for construction/destruction of the object and
// for uses internal to the implementation (see
// <A HREF="http://www.informatik.uni-konstanz.de/~kuehl/iostream/wstream.cc.html">
// wstream.cc</A>):
// <PRE>
class debugbuf: public streambuf
{
private:
  void	put_buffer(void);
  void	put_char(int);

protected:
  int	overflow(int);
  int	underflow() { return EOF; }
  int	sync();

public:
  debugbuf(int = 1024);
  ~debugbuf();
};
// </PRE>

//----------------------------------------------------------------------------
// To make the use of the debugbuf more convinient a class derived from
// ostream is supported which only initializes an ostream with a debugbuf
// as streambuf. It is also possible to directly allocate a debugbuf and
// initialize an ostream with it. Thus this class is not really necessary:
// <PRE>

class odbgstream: public ostream
{
public:
  odbgstream(int = 1024);
};

// </PRE>

//----------------------------------------------------------------------------
// Finally there has to be a proper termination of the header file:
// <PRE>

#include "dbgstream.ipp"

#endif /* _DBGSTREAM_H_ */

// </PRE>
// <HR>
// Please send comments, suggestions, problem reports, bug fixes etc. to 
// <BR>
// <A HREF="http://www.informatik.uni-konstanz.de/~kuehl"><I>Dietmar K&uuml;hl</I></A>:
// <A HREF="mailto:dietmar.kuehl@uni-konstanz.de">Dietmar.Kuehl@uni-konstanz.de</A>
// </BODY>
// </HTML>


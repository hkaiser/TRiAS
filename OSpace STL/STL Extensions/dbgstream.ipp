// <!-*-C++-*- file: wstream.cc --->
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
// <HTML>
// <HEAD>
// <TITLE> wstream.cc - Implementation File for a Specialized IOstream </TITLE>
// <H1>Implementation File for a Specialized IOstream</H1>
// <H2>Writing into a Motif Text Widget</H2>
// <HR>
// </HEAD>
    
// <BODY>
// This page includes a C++ file used to implement a specialized
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
// First a declaration of the classes debugbuf and odbgstream (out widget stream)
// are needed. These can be found in the file
// <A HREF="http://www.informatik.uni-konstanz.de/~kuehl/iostream/wstream.h.html">
// wstream.h</A>. In addition there are some declarations needed in conjunction
// with Motif's text widget which are found in Xm/Text.h.
// <PRE>
    #include "dbgstream.h"
// </PRE>
    
// Next the only memeber function of the class 'odbgstream' (a constructor) is implemented.
// All this constructor does is to create a debugbuf and hand this debugbuf
// to the constructor of ostream. Thus the debugbuf will become the streambuf
// used to put characters into:
// <PRE>
    odbgstream::odbgstream(int bsize):
      ostream(new debugbuf(bsize))
    {
    }
// </PRE>
    
    
// The constructor for the class debugbuf has something more to do:
// <UL>
// <LI> Initialize the 'text' member which identifies into which Widget the
//      output has to go
// <LI> If buffering is desired allocate a buffer
// <LI> Setup the buffer pointers from streambuf
// </UL>
// The function 'streambuf::setp()' is used to setup the pointers of the put area
// while 'streambuf::setg()' is used for the pointers of the get area. Since
// the current implementation of debugbuf can't be used for input from a Widget
// (I don't know exactly what is desired when trying to 'read' from a Widget)
// the pointers of the get area are initialized to be 0.
// <PRE>
    debugbuf::debugbuf(int bsize):
      streambuf()
    {
      if (bsize)
      {
        char	*ptr = new char[bsize];
        setp(ptr, ptr + bsize);
      }
      else
        setp(0, 0);
    
      setg(0, 0, 0);
    }
// </PRE>
// The destructor of debugbuf simply makes sure that every output is
// really send to the widget. This is done by calling 'sync()'.
// <PRE>
    debugbuf::~debugbuf()
    {
      sync();
    }
// </PRE>
// Whenever the put area of a streambuf is full, 'overflow()' is called.
// The argument to 'overflow()' is the character which didn't fit into the
// put area or EOF, if there is no such character. 'overflow()' is simply
// implemented by calling 'put_buffer()' which writes the current contents
// of the put area to the widget and then putting the single missing
// character. The argument to overflow is put into the put area if
// the debugbuf is operating buffered: 'streambuf::sputc()' puts a
// single character into the put area. Otherwise the character is directly
// put into the Widget with 'put_char()'. To check whether the output
// is buffered or unbuffered, the length of the put area is used:
// 'streambuf::pbase()' points to the start of the put area and
// 'streambuf::epptr()' points to the end of the put area.

// <PRE>
    int	debugbuf::overflow(int c)
    {
      put_buffer();
    
      if (c != EOF)
        if (pbase() == epptr())
          put_char(c);
        else
          sputc(c);
    
      return 0;
    }
// </PRE>
// To bring the internal representation of a streambuf into synchronization
// with its external representation (remember that a streambuf represents
// a sequence of characters), the function 'sync()' is called. Since
// only writing to a debugbuf is supported this means that the internal
// buffer has to be put into the widget. This is done by calling 'put_buffer()'.
// <PRE>
    int	debugbuf::sync()
    {
      put_buffer();
      return 0;
    }
// </PRE>
// 'put_char()' appends its argument (a single character) to a widget's text.
// The details of this process are quite obvious and are only of minor interest
// to the topic of this page (implementing a specialized streambuf).
// <PRE>
    void	debugbuf::put_char(int chr)
    {
      char	app[2];
    
      app[0] = chr;
      app[1] = 0;
    
	  OutputDebugString (app);
    }
// </PRE>
// 'put_buffer()' appends the debugbuf's buffer to the text Widget. This
// is done by first retrieving a string from the put area (the character
// sequence in the put area is not necessarily 0 terminated), then appending
// this string to the widget and finally resetting the pointers to the put
// area.
// <BR>
// The number of characters currently found in the put area is is calculated
// as the difference between the next put position (returned by
// 'streambuf::pptr()') and the beginning of the put area ('streambuf::pbase()').
// The details how to append the string to the Widget's text are obvious.
// To reset the pointers into the put area (mainly the pointer to the put positin)
// the values returned by 'pbase()' and 'epptr()' are used.
// <PRE>
    void	debugbuf::put_buffer()
    {
      if (pbase() != pptr())
      {
        int		len = (pptr() - pbase());
        char *buffer = new char[len + 1];
    
        strncpy(buffer, pbase(), len);
        buffer[len] = 0;
        OutputDebugString(buffer);
    
		delete [] buffer;
        setp(pbase(), epptr());
      }
    }
// </PRE>
// <HR>
// Please send comments, suggestions, problem reports, bug fixes etc. to 
// <BR>
// <A HREF="http://www.informatik.uni-konstanz.de/~kuehl"><I>Dietmar K&uuml;hl</I></A>:
// <A HREF="mailto:dietmar.kuehl@uni-konstanz.de">Dietmar.Kuehl@uni-konstanz.de</A>
// </BODY>
// </HTML>


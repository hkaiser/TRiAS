--- README --- D_Lib --- v.3.2b ----------------------------------


1. Introduction

The D_Lib library provides a set of easy-to-use but powerful and
easily configurable tools to perform a C++ programmer's daily debug
as well as diagnostics needed by a system tester/maintainer.
In fact the use of the D_Lib library gives very flexible debug
printing with both compile-time and run-time management and also
possibility to turn on/off (even run-time) some pieces of
code without any recompilation. It was tested and used for several
UNIX platforms as well as MS Windows NT/95.

Its documentation is contained in the plain text file d_lib.txt.


2. Supported platforms.

For now the D_Lib library was tested and used in the following
environments:
- HP HP-UX B.10.20, HP C++ B.11.00
- Windows NT(Intel), MSVC++ 6.0

Currently I don't have other platforms to test the last version
but in past the library was used on: SGI IRIX (Gnu C++), Sun Solaris
(Sun C++, Gnu C++), Win95/NT (MSVC 4.0, 4.1, 4.2, 5.0),
Linux (Gnu C++), etc. So it seems to be moreless portable (at least
for various 32-bit UNIXes and Win32 OSes).

Anyway due to the lack of possibility to perform a really thorough
testing on a wide set of platforms, I called this version 3.2b, i.e.
3.2-beta. I hope that there is no serious bugs, so this version
seems to usable and useful as if without the letter 'b' :-).

3. System requirements

1) You must have C++ compiler (naturally :-).

2) The library uses regular expressions that I was too lazy to
   implement by myself. So it may be built with use of some
   3rd-party library implementing this feature.

   There are 3 such libraries that D_Lib can use without any
   modification:

   - If you are a "commercial" user then you can buy RogueWave's
   Tools.h++ library (an excellent product supporting so many
   platforms that I don't know how many :-). All the necessary
   information may be found here:

	http://www.roguewave.com/products/tools/tools.html

   - If you don't want to buy anything then you can use the YACL
   (Yet-Another-C++-library) that is in public domain and may
   be obtained from:

	http://www.cs.sc.edu/~sridhar/yacl.html

   (If you want to use the YACL for D_Lib only then please note:
   it is enough to build just the "base" part of it.) BTW, this
   is also very-very good library.

   - If you are too lazy to get some "big" library then you can
   obtain RE_Lib from my collection of public domain software:

   	http://www.geocities.com/SiliconValley/Peaks/8778/pubdom.html

   This is a slightly modified version of the REGEXP library by
   Henry Spencer (the original sources may be obtained from many
   sources but they are useless for D_Lib). The modifications were:
   1. now it is compiled by C++; 2. it does not require external
   function regerror() but you can set your error handler using
   new (my :-) function set_regerror_func() (see regexp.h). These
   are the only changes.

   - If you have your favorite regular expression implementation
   then you have to modify file d_regexpr.h (class D_RegExpImpl_c)
   to use your regular expressions. If you do this please send me
   your changes.


4. How to build the D_Lib library

There are almost ready-to-use makefiles having suffixes corresponding
to the supported platforms (msc and unix). If you platform is something
else then take one of the makefiles (most similar to your platform).
Look into the makefile (don't be afraid - it is very simple) and make
necessary changes (mostly for directories of the 3rd-party library
used and for compile/etc. flags). Then run make (gmake/nmake/whatever
you have). You must succeed!


5. Known bugs and problems

1) There is no bugs known to me. Of course, this does not mean that
   there is no bugs at all :-).

2) There are several things that I'm going to implement in future:

   - inter-thread synchronization for more platforms - currently
     supported are WindowsNT/95 and UNIX having POSIX-threads

   - inter-process synchronization when the output is redirected to
     a file (using file locking mechanism) - currently not implemented,
     the problem can be avoided by sending output from different
     processes to different files (see d_lib.txt for details)

   If somebody could implement any of the abovementioned things -
   I'd be very glad to get a copy.

3) MSVC++ 6.0 has a problem: if you use its debug info mode
   "Program Database for Edit and Continue" (command line
   option /ZI), which is the default mode for Debug project
   configuration, then it will refuse to compile D_STACK
   macro. The solution is to use the simple "Program Database"
   debug info instead (command line option /Zi).

Anyway if you find any bug/problem please send me email:
anatoly-k@geocities.com. If you change the sources then also: please
send me a copy of your changes (to the same address).


6. Try to enjoy the D_Lib library!


Good luck!

Anatoly Kardash
anatoly-k@geocities.com
19 August 1999

--- Version history ----------------------------------------------

v.3.2b
- Got rid of use of templates - it causes too many problems on many
  UNIX C++ compilers.
- Fixed bug with too small buffers for file names (FILENAME_MAX
  has a small value on some UNIXes).
- Added possibility for run-time generating of outpur file name.
- Added possibility to shut up the internal diagnostics.
- Added macros families for formatted printing D_PF, D_SF, D_PRINTF
  and D_OUTF.
- Added support of use from C-sources.

v.3.1
- Added possibility to use RE_lib instead RogueWave/YACL for regular
  expressions.
- Added support of POSIX-threads on UNIX platforms.

v.3.0
- Completely rewritten from the version 2.0.
- Added possibility to use YACL instead RogueWave for regular
  expressions.
- Added support of scopes "class" (D_CLASS macro) and "stack" (D_STACK
  macro).
- Added distinguishing of GUI/CUI application for MSWindows OSes.

v.1.0 and 2.0
- Versions written during the work in a commercial companies, so they
  were not publically available. The basic functionality is
  implemented.

--- README --- D_Lib --- v.3.2b --- EOF --------------------------

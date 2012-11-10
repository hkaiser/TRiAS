                              THE U2NT PROJECT
                         Porting UNIX to Microsoft Win32

                                  Release 1.3


ADDRESS
	http://www.ede.com/free/u2nt . Mailing list, archives, etc.

SPECIAL NOTE
	The original name for U2NT was 'downhill.' Think about it. :-)
	The name is being changed to better reflect the project's purpose.
	The next release will include a full rename.

PURPOSE
	The Downhill Project is a collection of Win32-compatible
	routines designed to emulate UNIX API calls.  These routines
	allow UNIX code to run under Win32 OS's (Windows 95, Windows
	NT and Windows 3.1 with Win32s) with as little modification as
	possible, without a lot of ugly #ifdefs.

INSTALLATION
	Untar the Downhill directory tree someplace where it will be
	out of the way ("\DOWNHILL", for example).  Change the makefile
	variables to point the appropriate places or values:
		
		CMP_SYSTEM_DIR	Where the system include files are
		CMP_POSIX	Compile POSIX-compliant functions only?
		CMP_DEBUG	Turn on debugging for library?

	Add the include directory ("\DOWNHILL\INCLUDE") to your
	compiler's include path.  Add the library
	("\DOWNHILL\DOWNHILL.LIB") to your linker's library list.

	After Downhill is installed, when your compiler isn't able to
	resolve a reference (say, "#include <sys/param.h>"), it will
	continue to check through any additional include directories,
	eventually stumbling across the Downhill Project, where it will
	(hopefully) find the file it is looking for.  This will then be
	included as normal and things will continue on their way.

	If you're planning on using any of the Downhill-specific
	functions (or want a single include that does all the foo()-
	to-_foo() work), include "downhill.h".  You should never have
	to inlcude anything in the "DOWNHILL\INCLUDE\DOWNHILL"
	directory -- it's all internal stuff.

	Note: You don't need to change your #include <>'s to
	#include ""'s.  The compiler will search the additional paths
	anyway.


DISCLAIMER
	Ede Development Enterprises, Incorporated makes no representations
	about the suitability of this software for any purpose. It is
	provided "AS IS" without express or implied warranty.

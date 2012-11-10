How to Build libtiff, libgeotif and the geotiff executables on WindowsNT 
with Visual C++ ver 2.x.  This is a command line version of the makefiles.
You should easily be able to build an IDE version of them by seeing what 
files are necessary for the build.

NOTE: This does not build the libtiff executables ("tools" directory), 
      just the library.  It does build the libgeotiff executables.

NOTE2: Changes may have to be made if a different version of libtiff is 
       used. These instructions apply to v3.4beta031


BACKGROUND

Visual C++ 2.x requires that DLLs be built with some idea of the eventual 
application that will use the DLLs.  There are two types of DLLs, "CONSOLE"
and "GUI".  It is recommended that command line based applications use 
CONSOLE dlls, and applications that use the WIMP interface (Windows, Icons, 
Mouse Pointer) should use the GUI dlls.  In practice, the difference comes 
down to availability of stdin/stdout/stderr.  CONSOLE dlls can read from 
stdin and write to stdout. GUI dlls must use message boxes etc for user 
interface. Also, Win32s applications (32bit app on 16bit windows) must use 
the GUI dlls.  Libtiff itself does use stdin/out/err for warnings and errors, 
so we must take this into consideration in building the libraries and apps.
As built below, the staticly linked (archive) library is only good for 
console apps since it does I/O to stdin/out/err.  See the build option 
-DCONSOLE_BUILD in tif_win32.c for more info. 

I have built makefiles that, given the correct environment variables etc.,
will build either static, console, or gui dlls.  The distribution also
contains batch files that set up the environment properly for each type of
build. Please use the batch files until you are certain that you know how
the batch files and makefiles interoperate to build each type.  by default,
the makefiles build static libraries, not DLLs.





INITIAL PROCEDURES

* Get the libtiff and libgeotiff distributions.

* Open a command window to do most of the following.

* Unzip using "gzip -d <filename>"

* Untar using "tar -xvf <filename>"
  You will get many "permission denied" messages. Ignore them.

* Most of the files will have "read-only" attributes.  Since you will need
  to edit some files, you can change them all to "read-write" by typing
  "attrib/s -r" in a command window at the top level directory of this
  distribution.

* Move the libgeotiff directory down into the tiff-v3.4beta031
  directory. (Using file manager, you can just drag-and-drop)

* Create a directory under tiff-v3.4beta031 for the NT specific stuff.
  I'll call it "NTextras", but you may name it anything you like. Copy or
  move all the files in the NT-geotiff distribution into that directory.

* Now, cd to "tiff-v3.4beta031" and then to "NTextras" (or whatever you
  have called it).

* Run install.bat.  This copies batch and makefiles to the necessary places
  and gets you ready to build libtiff, libgeotiff, and the executables.


* Now see README2.TXT for the rest of the instructions.  Note, INSTALL.BAT
  automatically pages this file out for you during the installation.







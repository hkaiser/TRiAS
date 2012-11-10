@echo off
REM	Batchfile to make libgist 
REM	$$

if %1 == clean goto clean

:all
nmake /f Makefile.java.NT
msdev .\projects\gist\gist.dsw /MAKE "gistcmdline - Win32 Debug" /USEENV
msdev .\projects\gist\gist.dsw /MAKE "amdb - Win32 Debug" /USEENV

goto done

:clean 
nmake /f Makefile.java.NT clean RECURSE=1
msdev .\projects\gist\gist.dsw /MAKE "gistcmdline - Win32 Debug" /CLEAN /USEENV
msdev .\projects\gist\gist.dsw /MAKE "amdb - Win32 Debug" /CLEAN /USEENV

:done
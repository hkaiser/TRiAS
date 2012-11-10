# Makefile zur Erstellung von TRiAS3 - Buffer

$(TRIASDIR_D)\bufferd.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Buffer.dsp
	SET T3CONFIG="Buffer - Win32 Debug"
	SET T3LOGFILE=Buffer.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\buffer.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Buffer.dsp
	SET T3CONFIG="Buffer - Win32 Release"
	SET T3LOGFILE=Buffer.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

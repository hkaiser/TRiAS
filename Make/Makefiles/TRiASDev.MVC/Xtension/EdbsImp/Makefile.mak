# Makefile zur Erstellung von TRiAS3 - EDBSimp

$(TRIASDIR_D)\edbsimpd.ext :
#	nmake /F MAKEFILE. new formake
	copy .\win32\edbs.rcv
	SET T3PROJECT=edbsimp.dsp
	SET T3CONFIG="Edbsimp - Win32 Debug"
	SET T3LOGFILE=EDBSimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\edbsimp.ext:
#	nmake /F MAKEFILE. new formake
	copy .\win32\edbs.rcv
	SET T3PROJECT=edbsimp.dsp
	SET T3CONFIG="Edbsimp - Win32 Release"
	SET T3LOGFILE=EDBSimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

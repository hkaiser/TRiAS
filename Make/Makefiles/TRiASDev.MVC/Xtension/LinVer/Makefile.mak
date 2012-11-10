# Makefile zur Erstellung von TRiAS3 - Linver

$(TRIASDIR_D)\maschbld.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Linver.dsp
	SET T3CONFIG="linver - Win32 Debug"
	SET T3LOGFILE=Linver.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\maschblr.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Linver.dsp
	SET T3CONFIG="linver - Win32 Release"
	SET T3LOGFILE=Linver.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

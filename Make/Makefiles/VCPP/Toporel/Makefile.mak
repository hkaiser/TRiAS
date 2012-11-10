# Makefile zur Erstellung von TRiAS3 - Toporel

$(TRIASDIR_D)\toporeld.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Toporel.dsp
	SET T3CONFIG="Toporel - Win32 Debug"
	SET T3LOGFILE=Toporel.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\toporel.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Toporel.dsp
	SET T3CONFIG="Toporel - Win32 Release"
	SET T3LOGFILE=Toporel.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

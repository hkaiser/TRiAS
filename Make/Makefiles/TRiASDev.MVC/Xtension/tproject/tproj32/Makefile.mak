# Makefile zur Erstellung von TRiAS3 - TProject

$(TRIASDIR_D)\tprojecd.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Tproj32.dsp
	SET T3CONFIG="Tproj32 - Win32 Debug"
	SET T3LOGFILE=Tproject.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\tproject.ext:
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Tproj32.dsp
	SET T3CONFIG="Tproj32 - Win32 Release"
	SET T3LOGFILE=Tproject.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

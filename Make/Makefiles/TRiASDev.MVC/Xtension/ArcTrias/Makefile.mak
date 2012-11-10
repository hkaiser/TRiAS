# Makefile zur Erstellung von TRiAS3 - Arctrias

$(TRIASDIR_D)\arctriad.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Arctrias.dsp
	SET T3CONFIG="Arctrias - Win32 Debug"
	SET T3LOGFILE=Arctrias.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\arctrias.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=Arctrias.dsp
	SET T3CONFIG="Arctrias - Win32 Release"
	SET T3LOGFILE=Arctrias.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

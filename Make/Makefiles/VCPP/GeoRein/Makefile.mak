# Makefile zur Erstellung von TRiAS3 - Georein

$(TRIASDIR_D)\georeind.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Georein.dsp
	SET T3CONFIG="Georein - Win32 Debug"
	SET T3LOGFILE=Georein.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\georein.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Georein.dsp
	SET T3CONFIG="Georein - Win32 Release"
	SET T3LOGFILE=Georein.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

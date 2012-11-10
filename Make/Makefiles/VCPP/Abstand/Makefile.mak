# Makefile zur Erstellung von TRiAS3 - Abstand

$(TRIASDIR_D)\abstandd.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Abstand.dsp
	SET T3CONFIG="Abstand - Win32 Debug"
	SET T3LOGFILE=Abstand.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\abstand.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Abstand.dsp
	SET T3CONFIG="Abstand - Win32 Release"
	SET T3LOGFILE=Abstand.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

# Makefile zur Erstellung von TRiAS3 - Kompias

$(TRIASDIR_D)\TRiASIGM.ext :
	nmake /F kompak36.mak new formake
	SET T3PROJECT=komp32.dsp
	SET T3CONFIG="komp32 - Win32 Debug"
	SET T3LOGFILE=TRiASIGM.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiASIGM.ext:
	nmake /F kompak36.mak new formake
	SET T3PROJECT=komp32.dsp
	SET T3CONFIG="komp32 - Win32 Release"
	SET T3LOGFILE=TRiASIGM.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

# Makefile zur Erstellung von TRiAS - Splitting

$(TRIASDIR_D)\Splittid.ext :
	SET T3PROJECT=Berlin.dsp
	SET T3CONFIG="Berlin - Win32 Debug"
	SET T3LOGFILE=Splitting.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Splitting.ext :
	SET T3PROJECT=Berlin.dsp
	SET T3CONFIG="Berlin - Win32 Release"
	SET T3LOGFILE=Splitting.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

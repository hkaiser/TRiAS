# Makefile zur Erstellung von TRiAS - Statist

$(TRIASDIR_D)\statistd.ext :
	SET T3PROJECT=Statist.dsp
	SET T3CONFIG="Statist - Win32 Debug"
	SET T3LOGFILE=Statist.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Statist.ext :
	SET T3PROJECT=Statist.dsp
	SET T3CONFIG="Statist - Win32 Release"
	SET T3LOGFILE=Statist.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

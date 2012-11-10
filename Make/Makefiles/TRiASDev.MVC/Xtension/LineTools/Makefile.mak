# Makefile zur Erstellung von TRiAS - LineTools

$(TRIASDIR_D)\LineToold.ext :
	SET T3PROJECT=LineTools.dsp
	SET T3CONFIG="LineTools - Win32 Debug"
	SET T3LOGFILE=LineTools.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\LineTools.ext :
	SET T3PROJECT=LineTools.dsp
	SET T3CONFIG="LineTools - Win32 Release"
	SET T3LOGFILE=LineTools.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

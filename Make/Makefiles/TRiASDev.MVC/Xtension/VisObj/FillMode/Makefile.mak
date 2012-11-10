# Makefile zur Erstellung von TRiAS3 - FillMode

$(TRIASDIR_D)\FillMode.vmd :
	SET T3PROJECT=FillMode.dsp
	SET T3CONFIG="FillMode - Win32 Debug"
	SET T3LOGFILE=FillMode.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\FillMode.vmd :
	SET T3PROJECT=FillMode.dsp
	SET T3CONFIG="FillMode - Win32 Release"
	SET T3LOGFILE=FillMode.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

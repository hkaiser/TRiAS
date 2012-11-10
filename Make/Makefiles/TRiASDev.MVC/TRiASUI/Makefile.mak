# Makefile zur Erstellung von TRiAS3 - TRiASUI

$(TRIASDIR_D)\TRiASUId.dll :
	SET T3PROJECT=triasui.dsp
	SET T3CONFIG="TRiASUI - Win32 Debug"
	SET T3LOGFILE=TRiASUI.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiASUI.dll :
	SET T3PROJECT=triasui.dsp
	SET T3CONFIG="TRiASUI - Win32 Release MinSize"
	SET T3LOGFILE=TRiASUI.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

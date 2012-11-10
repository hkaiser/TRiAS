# Makefile zur Erstellung von TRiAS3 - TRiASICN

$(TRIASDIR_D)\TRiASICN.dll :
	SET T3PROJECT=triasicn.dsp
	SET T3CONFIG="TRiASICN - Win32 Debug"
	SET T3LOGFILE=TRiASICN.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiASICN.dll :
	SET T3PROJECT=triasicn.dsp
	SET T3CONFIG="TRiASICN - Win32 Release MinSize"
	SET T3LOGFILE=TRiASICN.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

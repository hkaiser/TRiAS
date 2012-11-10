# Makefile zur Erstellung von TRiAS3 - TRiASHP

$(TRIASDIR_D)\TRiASDBD.dll :
	SET T3PROJECT=triashp.dsp
	SET T3CONFIG="TRiASHP - Win32 Debug"
	SET T3LOGFILE=triashp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiASDB.dll :
	SET T3PROJECT=triashp.dsp
	SET T3CONFIG="TRiASHP - Win32 Release MinSize"
	SET T3LOGFILE=triashp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	


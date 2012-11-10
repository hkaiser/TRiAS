# Makefile zur Erstellung von TRiAS3 - TRiASDB

$(TRIASDIR_D)\TRiASDBD.dll :
	SET T3PROJECT=triasdb.dsp
	SET T3CONFIG="TriasDB - Win32 Debug"
	SET T3LOGFILE=triasdb.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiASDB.dll :
	SET T3PROJECT=triasdb.dsp
	SET T3CONFIG="TriasDB - Win32 Release MinSize"
	SET T3LOGFILE=triasdb.log
!INCLUDE C:\MAKE\MkMSDEV.mak	


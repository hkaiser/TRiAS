# Makefile zur Erstellung von TRiAS3 - TRiAS02

$(TRIASDIR_D)\trias32d.dll $(TRIASLIB)\trias32d.lib :
	SET T3PROJECT=trias422.dsp
	SET T3CONFIG="Trias322 - Win32 Debug"
	SET T3LOGFILE=TRiAS02.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\trias322.dll $(TRIASLIB)\trias322.lib :
	SET T3PROJECT=trias422.dsp
	SET T3CONFIG="Trias322 - Win32 Release"
	SET T3LOGFILE=TRiAS02.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

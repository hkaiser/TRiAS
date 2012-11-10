# Makefile zur Erstellung von TRiAS3 - TRiAS

$(TRIASDIR_D)\TRiAS32d.exe :
	SET T3PROJECT=trias42.dsp
	SET T3CONFIG="Trias32 - Win32 Debug"
	SET T3LOGFILE=TRiAS.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TRiAS32.exe :
	SET T3PROJECT=trias42.dsp
	SET T3CONFIG="Trias32 - Win32 Release"
	SET T3LOGFILE=TRiAS.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

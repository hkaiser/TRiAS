# Makefile zur Erstellung von TRiAS3 - TRiAS01

$(TRIASDIR_D)\trias31d.dll $(TRIASLIB)\trias31d.lib :
	SET T3PROJECT=trias421.dsp
	SET T3CONFIG="Trias321 - Win32 Debug"
	SET T3LOGFILE=TRiAS01.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\trias321.dll $(TRIASLIB)\trias321.lib :
	SET T3PROJECT=trias421.dsp
	SET T3CONFIG="Trias321 - Win32 Release"
	SET T3LOGFILE=TRiAS01.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

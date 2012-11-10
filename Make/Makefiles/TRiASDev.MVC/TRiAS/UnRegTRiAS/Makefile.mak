# Makefile zur Erstellung von TRiAS - UnRegTRiAS

$(TRIASDIR_D)\UnRegTRiASd.exe :
	SET T3PROJECT=UnRegTRiAS.dsp
	SET T3CONFIG="UnRegTRiAS - Win32 Debug"
	SET T3LOGFILE=UnRegTRiAS.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\UnRegTRiAS.exe :
	SET T3PROJECT=UnRegTRiAS.dsp
	SET T3CONFIG="UnRegTRiAS - Win32 Release"
	SET T3LOGFILE=UnRegTRiAS.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

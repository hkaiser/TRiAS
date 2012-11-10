# Makefile zur Erstellung von TRiAS3 - Lol

$(TRIASDIR_D)\lol50d.dll $(TRIASLIB)\lol50d.lib :
	SET T3PROJECT=lol32.dsp
	SET T3CONFIG="lol32 - Win32 LOL Win32DLL Debug"
	SET T3LOGFILE=lol.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\lol.dll $(TRIASLIB)\lol.lib :
	SET T3PROJECT=lol32.dsp
	SET T3CONFIG="lol32 - Win32 LOL Win32DLL Release"
	SET T3LOGFILE=lol.log
!INCLUDE C:\MAKE\MkMSDEV.mak	


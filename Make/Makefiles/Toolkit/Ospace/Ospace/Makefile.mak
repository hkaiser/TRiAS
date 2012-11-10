# Makefile zur Erstellung von TRiAS3 - Ospace

#=== STL DLL
$(TRIASDIR_D)\Ospace5d.dll $(TRIASLIB)\Ospace5d.lib :
	SET T3PROJECT=Ospace.dsp
	SET T3CONFIG="standards - Win32 MT Debug"
	SET T3LOGFILE=Ospace.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\ospace.dll $(TRIASLIB)\Ospace5r.lib :
	SET T3PROJECT=Ospace.dsp
	SET T3CONFIG="standards - Win32 MT Release"
	SET T3LOGFILE=Ospace.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

#=== Streaming library
$(TRIASLIB)\StdStr5d.lib :
	SET T3PROJECT="Standards uss.dsp"
	SET T3CONFIG="standards uss - Win32 Debug"
	SET T3LOGFILE=OspaceUss.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\StdStr5r.lib :
	SET T3PROJECT="Standards uss.dsp"
	SET T3CONFIG="standards uss - Win32 Release"
	SET T3LOGFILE=OspaceUss.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

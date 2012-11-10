# Makefile zur Erstellung von TRiAS3 - Helper

$(TRIASDIR_D)\Helperd.dll :
	SET T3PROJECT=helper.dsp
	SET T3CONFIG="Helper - Win32 Debug"
	SET T3LOGFILE=Helper.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Helper.dll :
	SET T3PROJECT=helper.dsp
	SET T3CONFIG="Helper - Win32 Release MinSize"
	SET T3LOGFILE=Helper.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

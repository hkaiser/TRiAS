# Makefile zur Erstellung von TRiAS3 - LibCtrlExt

$(TRIASLIB)\LibCtrlExtD.lib :
	SET T3PROJECT=LibCtrlExt.dsp
	SET T3CONFIG="LibCtrlExt - Win32 Debug"
	SET T3LOGFILE=LibCtrlExt.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\LibCtrlExt.lib :
	SET T3PROJECT=LibCtrlExt.dsp
	SET T3CONFIG="LibCtrlExt - Win32 Release"
	SET T3LOGFILE=LibCtrlExt.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

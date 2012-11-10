# Makefile zur Erstellung von TRiAS3 - Objman

$(TRIASDIR_D)\Objmand.dll :
	SET T3PROJECT=Objman.dsp
	SET T3CONFIG="ObjMan - Win32 Debug"
	SET T3LOGFILE=Objman.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Objman.dll :
	SET T3PROJECT=Objman.dsp
	SET T3CONFIG="ObjMan - Win32 Release"
	SET T3LOGFILE=Objman.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

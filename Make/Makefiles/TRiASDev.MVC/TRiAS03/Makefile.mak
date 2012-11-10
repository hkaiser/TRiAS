# Makefile zur Erstellung von TRiAS3 - TRiAS03

$(TRIASDIR_D)\trias33d.dll $(TRIASLIB)\trias33d.lib $(TRIASINCLUDE)\TRiASHelper.h ::
	SET T3PROJECT=trias423.dsp
	SET T3CONFIG="Trias323 - Win32 Debug"
	SET T3LOGFILE=TRiAS03.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\trias323.dll $(TRIASLIB)\trias323.lib $(TRIASINCLUDE)\TRiASHelper.h ::
	SET T3PROJECT=trias423.dsp
	SET T3CONFIG="Trias323 - Win32 Release"
	SET T3LOGFILE=TRiAS03.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

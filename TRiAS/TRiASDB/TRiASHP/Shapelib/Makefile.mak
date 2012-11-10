# Makefile zur Erstellung von TRiAS3 - ShapeLib

$(TRIASLIB)\ShapeLibD.lib :
	SET T3PROJECT=ShapeLib.dsp
	SET T3CONFIG="ShapeLib - Win32 Debug"
	SET T3LOGFILE=ShapeLib.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ShapeLib.lib :
	SET T3PROJECT=ShapeLib.dsp
	SET T3CONFIG="ShapeLib - Win32 Release"
	SET T3LOGFILE=ShapeLib.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

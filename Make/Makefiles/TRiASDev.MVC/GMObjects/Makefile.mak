# Makefile zur Erstellung von TRiAS3 - GMObjects

$(TRIASLIB)\GMObjectsD.lib :
	SET T3PROJECT=GMObjects.dsp
	SET T3CONFIG="GMObjects - Win32 Debug"
	SET T3LOGFILE=GMObjects.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\GMObjects.lib :
	SET T3PROJECT=GMObjects.dsp
	SET T3CONFIG="GMObjects - Win32 Release"
	SET T3LOGFILE=GMObjects.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

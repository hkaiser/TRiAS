# Makefile zur Erstellung von TRiAS3 - Colors

$(TRIASDIR_D)\Colorsd.ebn :
	SET T3PROJECT=Colors.dsp
	SET T3CONFIG="Colors - Win32 Debug"
	SET T3LOGFILE=Colors.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Colors.ebn :
	SET T3PROJECT=Colors.dsp
	SET T3CONFIG="Colors - Win32 Release"
	SET T3LOGFILE=Colors.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

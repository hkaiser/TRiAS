# Makefile zur Erstellung von TRiAS3 - Geometr

$(TRIASDIR_D)\geometd.dll $(TRIASLIB)\geometd.lib :
#	CD WIN32
	nmake /F Makefile new formake
#	CD ..
	SET T3PROJECT=Geometr.dsp
	SET T3CONFIG="Geometr - Win32 Debug"
	SET T3LOGFILE=Geometr.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\geometr.dll $(TRIASLIB)\geometr.lib :
#	CD WIN32
	nmake /F Makefile new formake
#	CD ..
	SET T3PROJECT=Geometr.dsp
	SET T3CONFIG="Geometr - Win32 Release"
	SET T3LOGFILE=Geometr.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

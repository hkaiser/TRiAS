# Makefile zur Erstellung von TRiAS3 - Torten

$(TRIASDIR_D)\Tortend.vmd :
#	CD OBJ32
#	nmake /F Torten16.MAK /nologo formake
#	CD ..
	SET T3PROJECT=Torten4.dsp
	SET T3CONFIG="torten - Win32 Debug"
	SET T3LOGFILE=Torten.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Torten.vmd :
#	CD OBJ32
#	nmake /F Torten16.MAK /nologo formake
#	CD ..
	SET T3PROJECT=Torten4.dsp
	SET T3CONFIG="torten - Win32 Release"
	SET T3LOGFILE=Torten.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

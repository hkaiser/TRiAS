# Makefile zur Erstellung von TRiAS3 - Identsdb

$(TRIASDIR_D)\Identdbd.ext :
#	CD OBJ32
#	nmake /F IDNTDB16.MAK new formake
#	CD ..
	SET T3PROJECT=Idntdb32.dsp
	SET T3CONFIG="Idntdb32 - Win32 Debug"
	SET T3LOGFILE=Idntdb32.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Identsdb.ext :
#	CD OBJ32
#	nmake /F IDNTDB16.MAK new formake
#	CD ..
	SET T3PROJECT=Idntdb32.dsp
	SET T3CONFIG="Idntdb32 - Win32 Release"
	SET T3LOGFILE=Idntdb32.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

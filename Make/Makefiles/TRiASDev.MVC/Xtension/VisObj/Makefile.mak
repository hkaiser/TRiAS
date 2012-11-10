# Makefile zur Erstellung von TRiAS3 - VisObj

$(TRIASDIR_D)\visobjd.ext :
	CD OBJ32
	nmake /F VISOBJ16.MAK /nologo formake
	CD ..
	SET T3PROJECT=VisObj42.dsp
	SET T3CONFIG="visobj32 - Win32 Debug"
	SET T3LOGFILE=VisObj.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\visobj.ext :
	CD OBJ32
	nmake /F VISOBJ16.MAK /nologo formake
	CD ..
	SET T3PROJECT=VisObj42.dsp
	SET T3CONFIG="visobj32 - Win32 Release"
	SET T3LOGFILE=VisObj.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

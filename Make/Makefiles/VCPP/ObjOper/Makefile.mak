# Makefile zur Erstellung von TRiAS3 - ObjOper

$(TRIASDIR_D)\objoperd.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Objoper.dsp
	SET T3CONFIG="Objoper - Win32 Debug"
	SET T3LOGFILE=Objoper.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\objoper.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Objoper.dsp
	SET T3CONFIG="Objoper - Win32 Release"
	SET T3LOGFILE=Objoper.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

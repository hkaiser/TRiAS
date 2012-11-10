# Makefile zur Erstellung von TRiAS3 - GeoEdit

$(TRIASDIR_D)\GeoEditD.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=geoedit.dsp
	SET T3CONFIG="Geoedit - Win32 Debug"
	SET T3LOGFILE=GeoEdit.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\GeoEdit.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=geoedit.dsp
	SET T3CONFIG="Geoedit - Win32 Release"
	SET T3LOGFILE=GeoEdit.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

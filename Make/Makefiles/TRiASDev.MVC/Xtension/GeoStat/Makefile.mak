# Makefile zur Erstellung von TRiAS3 - GeoStat

$(TRIASDIR_D)\geostatd.ext :
	nmake /F STAT16.MAK new formake
	SET T3PROJECT=stat32.dsp
	SET T3CONFIG="Stat32 - Win32 Debug"
	SET T3LOGFILE=Statistik.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\geostat.ext :
	nmake /F STAT16.MAK new formake
	SET T3PROJECT=stat32.dsp
	SET T3CONFIG="Stat32 - Win32 Release"
	SET T3LOGFILE=Statistik.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

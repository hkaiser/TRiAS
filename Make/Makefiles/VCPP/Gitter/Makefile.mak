# Makefile zur Erstellung von TRiAS3 - Gitter

$(TRIASDIR_D)\gitterd.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Raster.dsp
	SET T3CONFIG="Raster - Win32 Debug"
	SET T3LOGFILE=Raster.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\gitter.ext :
	nmake /F Makefile new formake
	SET T3PROJECT=Raster.dsp
	SET T3CONFIG="Raster - Win32 Release"
	SET T3LOGFILE=Raster.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

# Makefile zur Erstellung von TRiAS3 - DXFimp

$(TRIASDIR_D)\dxfimpd.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=dxfimp.dsp
	SET T3CONFIG="Dxfimp - Win32 Debug"
	SET T3LOGFILE=DXFimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\dxfimp.ext:
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=dxfimp.dsp
	SET T3CONFIG="Dxfimp - Win32 Release"
	SET T3LOGFILE=DXFimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

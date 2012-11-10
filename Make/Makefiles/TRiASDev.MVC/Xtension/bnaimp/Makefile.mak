# Makefile zur Erstellung von TRiAS3 - BnaImp

$(TRIASDIR_D)\bnaimpd.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=bnaimp.dsp
	SET T3CONFIG="bnaimp - Win32 Debug"
	SET T3LOGFILE=bnaimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\bnaimp.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=bnaimp.dsp
	SET T3CONFIG="bnaimp - Win32 Release MinSize"
	SET T3LOGFILE=bnaimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

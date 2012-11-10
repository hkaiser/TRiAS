# Makefile zur Erstellung von TRiAS3 - Bscript

$(TRIASDIR_D)\Bscriptd.ext :
	nmake /F Bscrip16.MAK new formake
	SET T3PROJECT=Bscript4.dsp
	SET T3CONFIG="Bscriptn - Win32 Debug"
	SET T3LOGFILE=Bscript.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\bscript.ext :
	nmake /F Bscrip16.MAK new formake
	SET T3PROJECT=Bscript4.dsp
	SET T3CONFIG="Bscriptn - Win32 Release"
	SET T3LOGFILE=Bscript.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

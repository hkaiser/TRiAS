# Makefile zur Erstellung von TRiAS3 - ASCImp

$(TRIASDIR_D)\ascimpd.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=ASCimp4.dsp
	SET T3CONFIG="Ascimp - Win32 Debug"
	SET T3LOGFILE=ASCimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\ascimp.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=ASCimp4.dsp
	SET T3CONFIG="Ascimp - Win32 Release"
	SET T3LOGFILE=ASCimp.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

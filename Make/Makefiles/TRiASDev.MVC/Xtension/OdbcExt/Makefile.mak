# Makefile zur Erstellung von TRiAS3 - ODBC-Anbindung

$(TRIASDIR_D)\odbcextd.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=odbcext.dsp
	SET T3CONFIG="Odbcext - Win32 Debug"
	SET T3LOGFILE=ODBCext.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\odbcext.ext :
	nmake /F MAKEFILE. new formake
	SET T3PROJECT=odbcext.dsp
	SET T3CONFIG="Odbcext - Win32 Release"
	SET T3LOGFILE=ODBCext.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

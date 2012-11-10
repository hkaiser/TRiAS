# Makefile zur Erstellung von TRiAS3 - EDBSAlk

$(TRIASDIR_D)\edbsalkd.ext :
#	nmake /F MAKEFILE. new formake
#	copy .\win32\edbs.rcv
	SET T3PROJECT=edbsalk.dsp
	SET T3CONFIG="EdbsAlk - Win32 Debug"
	SET T3LOGFILE=EDBSAlk.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\edbsalk.ext:
#	nmake /F MAKEFILE. new formake
#	copy .\win32\edbs.rcv
	SET T3PROJECT=edbsalk.dsp
	SET T3CONFIG="EdbsAlk - Win32 Release"
	SET T3LOGFILE=EDBSAlk.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

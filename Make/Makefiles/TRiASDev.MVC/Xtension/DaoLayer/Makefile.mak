# Makefile zur Erstellung von TRiAS3 - Daolayer

$(TRIASDIR_D)\Daolayed.ebn :
	nmake /F Daolay16.MAK new formake
	SET T3PROJECT=Daolayer.dsp
	SET T3CONFIG="Daolayer - Win32 Debug"
	SET T3LOGFILE=Daolayer.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\daolayer.ebn :
	nmake /F Daolay16.MAK new formake
	SET T3PROJECT=Daolayer.dsp
	SET T3CONFIG="Daolayer - Win32 Release"
	SET T3LOGFILE=Daolayer.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

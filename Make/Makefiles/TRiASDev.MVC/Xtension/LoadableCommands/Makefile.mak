# Makefile zur Erstellung von TRiAS - LoadableCommands

$(TRIASDIR_D)\LoadableCommandsd.ext :
	SET T3PROJECT=LoadableCommands.dsp
	SET T3CONFIG="LoadableCommands - Win32 Debug"
	SET T3LOGFILE=LoadableCommands.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\LoadableCommands.ext :
	SET T3PROJECT=LoadableCommands.dsp
	SET T3CONFIG="LoadableCommands - Win32 Release"
	SET T3LOGFILE=LoadableCommands.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

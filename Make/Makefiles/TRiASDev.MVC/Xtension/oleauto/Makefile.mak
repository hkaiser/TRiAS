# Makefile zur Erstellung von TRiAS3 - Oleauto

$(TRIASDIR_D)\oleautod.ext :
	SET T3PROJECT=Oleauto4.dsp
	SET T3CONFIG="Oleauto - Win32 Debug with BasicScript"
	SET T3LOGFILE=Oleauto4.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\oleauto.ext :
	SET T3PROJECT=Oleauto4.dsp
	SET T3CONFIG="Oleauto - Win32 Release with BasicScript"
	SET T3LOGFILE=Oleauto4.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

# Makefile zur Erstellung von TRiAS3 - FakeMFC

$(TRIASDIR_D)\fakemfcd.ext :
	SET T3PROJECT=fakemfc.dsp
	SET T3CONFIG="fakemfc - Win32 Debug with OT"
	SET T3LOGFILE=FakeMFC.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\fakemfc.ext :
	SET T3PROJECT=fakemfc.dsp
	SET T3CONFIG="fakemfc - Win32 Release with OT"
	SET T3LOGFILE=FakeMFC.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

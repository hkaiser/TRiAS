# Makefile zur Erstellung von TRiAS3 - TxtRotl

$(TRIASDIR_D)\TxtRotl.vmd :
	SET T3PROJECT=TxtRotl.dsp
	SET T3CONFIG="TxtRotl - Win32 Debug"
	SET T3LOGFILE=TxtRotl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\TxtRotl.vmd :
	SET T3PROJECT=TxtRotl.dsp
	SET T3CONFIG="TxtRotl - Win32 Release"
	SET T3LOGFILE=TxtRotl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

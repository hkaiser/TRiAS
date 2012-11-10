# Makefile zur Erstellung von TRiAS3 - Container

$(TRIASDIR_D)\containd.dll $(TRIASLIB)\cont50d.lib:
	SET T3PROJECT=cont4.dsp
	SET T3CONFIG="cont32 - Win32 Container Debug"
	SET T3LOGFILE=Container.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\containr.dll $(TRIASLIB)\containr.lib:
	SET T3PROJECT=cont4.dsp
	SET T3CONFIG="cont32 - Win32 Container Release"
	SET T3LOGFILE=Container.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

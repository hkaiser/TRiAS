# Makefile zur Erstellung von TRiAS3 - Common View

$(TRIASDIR_D)\Tfrm32d.dll $(TRIASLIB)\tfrm32d.lib :
	SET T3PROJECT=tfrm4.dsp
	SET T3CONFIG="Tfrm32 - Win32 Framework DLL Debug"
	SET T3LOGFILE=CommonView.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\Tfrmwork.dll $(TRIASLIB)\Tfrmwork.lib :
	SET T3PROJECT=tfrm4.dsp
	SET T3CONFIG="Tfrm32 - Win32 Framework DLL Release"
	SET T3LOGFILE=CommonView.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\tfrmld.lib :
	SET T3PROJECT=tfrm4l.dsp
	SET T3CONFIG="Tfrm32l - Win32 Framework LIB Debug"
	SET T3LOGFILE=CommonViewL.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\Tfrmlr.lib :
	SET T3PROJECT=tfrm4l.dsp
	SET T3CONFIG="Tfrm32l - Win32 Framework LIB Release"
	SET T3LOGFILE=CommonViewL.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

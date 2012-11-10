# Makefile zur Erstellung von TRiAS3 - Coords

$(TRIASDIR_D)\DefCtfsd.css :
	SET T3PROJECT=default4.dsp
	SET T3CONFIG="Default - Win32 Debug"
	SET T3LOGFILE=CoordsDef.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\DefCtfs.css :
	SET T3PROJECT=default4.dsp
	SET T3CONFIG="Default - Win32 Release"
	SET T3LOGFILE=CoordsDef.log
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

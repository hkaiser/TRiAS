# Makefile zur Erstellung von TRiAS3 - GKCTF

$(TRIASDIR_D)\GKCtfsd.css :
	SET T3PROJECT=GKCtf_COM.dsp
	SET T3CONFIG="GKCtf_COM - Win32 Debug"
	SET T3LOGFILE=GKCtf.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\GKCtfs.css :
	SET T3PROJECT=GKCtf_COM.dsp
	SET T3CONFIG="GKCtf_COM - Win32 Release MinSize"
	SET T3LOGFILE=GKCtf.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

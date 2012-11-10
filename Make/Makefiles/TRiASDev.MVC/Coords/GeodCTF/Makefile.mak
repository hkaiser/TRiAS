# Makefile zur Erstellung von TRiAS3 - GeodCTF

$(TRIASDIR_D)\GeodCtfd.css :
	SET T3PROJECT=GeodCtf_COM.dsp
	SET T3CONFIG="GeodCtf_COM - Win32 Debug"
	SET T3LOGFILE=GeodCtf.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\GeodCtfs.css :
	SET T3PROJECT=GeodCtf_COM.dsp
	SET T3CONFIG="GeodCtf_COM - Win32 Release MinSize"
	SET T3LOGFILE=GeodCtf.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

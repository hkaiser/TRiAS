# Makefile zur Erstellung von TRiAS3 - Ixtensn

$(TRIASLIB)\Ixtmad50.lib :
	SET T3PROJECT=Ixtatl50.dsp
	SET T3CONFIG="Ixtatl50 - Win32 Debug"
	SET T3LOGFILE=Ixtatl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\Ixtmar50.lib :
	SET T3PROJECT=Ixtatl50.dsp
	SET T3CONFIG="Ixtatl50 - Win32 Release"
	SET T3LOGFILE=Ixtatl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtmfd50.lib :
	SET T3PROJECT=Ixtmfc50.dsp
	SET T3CONFIG="ixtmfc32 - Win32 Debug New"
	SET T3LOGFILE=Ixtmfc.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtmfr50.lib :
	SET T3PROJECT=Ixtmfc50.dsp
	SET T3CONFIG="ixtmfc32 - Win32 Release New"
	SET T3LOGFILE=Ixtmfc.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtnsd50.lib :
	SET T3PROJECT=Ixtnsn42.dsp
	SET T3CONFIG="ixtnsn32 - Win32 Debug New"
	SET T3LOGFILE=Ixtnsn42.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtnsr50.lib :
	SET T3PROJECT=Ixtnsn42.dsp
	SET T3CONFIG="ixtnsn32 - Win32 Release New"
	SET T3LOGFILE=Ixtnsn42.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtatd50.lib :
	SET T3PROJECT=Ixtnsn42.dsp
	SET T3CONFIG="ixtnsn32 - Win32 Debug ATL Base"
	SET T3LOGFILE=Ixtnsn42.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtatr50.lib :
	SET T3PROJECT=Ixtnsn42.dsp
	SET T3CONFIG="ixtnsn32 - Win32 Release ATL Base"
	SET T3LOGFILE=Ixtnsn42.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtwtld.lib :
	SET T3PROJECT=Ixtatl50.dsp
	SET T3CONFIG="ixtatl50 - Win32 Debug WTL"
	SET T3LOGFILE=Ixtwtl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\ixtwtlr.lib :
	SET T3PROJECT=Ixtatl50.dsp
	SET T3CONFIG="ixtatl50 - Win32 Release WTL"
	SET T3LOGFILE=Ixtwtl.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

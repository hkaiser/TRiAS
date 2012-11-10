# Makefile zur Erstellung von TRiAS3 - Esnecil

$(TRIASLIB)\EsnecilD.lib :
	SET T3PROJECT=Esnecil.dsp
	SET T3CONFIG="Esnecil - Win32 Debug"
	SET T3LOGFILE=Esnecil.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASLIB)\Esnecil.lib :
	SET T3PROJECT=Esnecil.dsp
	SET T3CONFIG="Esnecil - Win32 Release"
	SET T3LOGFILE=Esnecil.log
!INCLUDE C:\MAKE\MkMSDEV.mak	
